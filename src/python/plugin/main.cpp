/*

Copyright (C) 2010  Gaetan Guidet

This file is part of ofxpp.

ofxpp is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at
your option) any later version.

ofxpp is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
USA.

*/

#include <ofx/ofx.h>
#include <ofx/plugin.h>
#include <gcore/path.h>
#include <gcore/env.h>
#include <Python.h>
#include <sstream>

typedef struct
{
  PyObject_HEAD
  ofx::Plugin *plugin;
} PyOFXPlugin;

// NOTE: calling this will clear the error (PyErr_Fetch)
void LogPythonError()
{
  if (PyErr_Occurred() == 0)
  {
    return;
  }
  
  std::ostringstream oss;
    
  PyObject *et=0, *ev=0, *etb=0, *s=0;
  
  PyErr_Fetch(&et, &ev, &etb);
  
  //s = PyObject_Str(et);
  //oss << std::endl << "--- Python --- " << PyString_AsString(s);
  //Py_DECREF(s);
  
  if (ev)
  {
    s = PyObject_Str(ev);
    oss << PyString_AsString(s);
    Py_DECREF(s);
  }
  
  if (etb)
  {
    PyObject *tbmn = PyString_FromString("traceback");
    PyObject *tbm = PyImport_Import(tbmn);
    Py_DECREF(tbmn);
    if (tbm)
    {
      PyObject *mdict = PyModule_GetDict(tbm);
      PyObject *func = PyDict_GetItemString(mdict, "format_tb"); // borrowed reference
      if (func && PyCallable_Check(func))
      {
        PyObject *tbargs = PyTuple_New(1);
        PyTuple_SetItem(tbargs, 0, etb);
        PyObject *tbl = PyObject_CallObject(func, tbargs);
        if (tbl)
        {
          Py_ssize_t nf = PyList_Size(tbl);
          for (Py_ssize_t f=0; f<nf; ++f)
          {
            PyObject *fs = PyList_GetItem(tbl, f);
            std::string lines = PyString_AsString(fs);
            size_t p0 = 0, p1 = lines.find('\n', p0);
            while (p1 != std::string::npos)
            {
              std::string line = lines.substr(p0, p1-p0);
              oss << std::endl << line;
              p0 = p1 + 1;
              p1 = lines.find('\n', p0);
            }
            oss << std::endl << lines.substr(p0);
          }
          Py_DECREF(tbl);
        }
        Py_DECREF(tbargs);
      }
      Py_DECREF(tbm);
    }
  }
  
  Py_XDECREF(et);
  Py_XDECREF(ev);
  Py_XDECREF(etb);
  
  oss << std::endl;
  
  ofx::Log("pyplugin.ofx:\n*** Python Error ***\n%s", oss.str().c_str());
}

class PathLister
{
  public:
    
    struct Entry
    {
      int startIndex;
      gcore::Path pyFile;
      std::vector<PyObject*> plugins;
    };
    
  public:
    
    PathLister()
      : mPyOFX(NULL)
    {
    }
    
    ~PathLister()
    {
      for (size_t i=0; i<mPluginEntries.size(); ++i)
      {
        for (size_t j=0; j<mPluginEntries[i].plugins.size(); ++j)
        {
          Py_XDECREF(mPluginEntries[i].plugins[j]);
        }
        mPluginEntries[i].plugins.clear();
      }
      mPluginEntries.clear();
      Py_XDECREF(mPyOFX);
    }
    
    bool fileEntry(const gcore::Path &p)
    {
      if (p.checkExtension("py"))
      {
        ofx::Log("pyplugin.ofx: Found possible python plugin: \"%s\"", p.fullname().c_str());
        
        PyObject *mod = loadModule(p);
        
        if (mod)
        {
          PyObject *getNumberOfPluginsFunc = PyObject_GetAttrString(mod, "OfxGetNumberOfPlugins");
          
          if (!getNumberOfPluginsFunc)
          {
            LogPythonError();
            Py_DECREF(mod);
            //PyErr_Clear();
            return true;
          }
          
          PyObject *getPluginFunc = PyObject_GetAttrString(mod, "OfxGetPlugin");
          
          if (!getPluginFunc)
          {
            LogPythonError();
            Py_DECREF(getNumberOfPluginsFunc);
            Py_DECREF(mod);
            //PyErr_Clear();
            return true;
          }
          
          Entry entry;
          
          entry.pyFile = p;
          entry.startIndex = 0;
          
          if (mPluginEntries.size() > 0)
          {
            entry.startIndex = mPluginEntries.back().startIndex + int(mPluginEntries.back().plugins.size());
          }
          
          PyObject *rv = PyObject_CallObject(getNumberOfPluginsFunc, NULL);
          
          if (!rv || !PyInt_Check(rv))
          {
            LogPythonError();
            //PyErr_Clear();
          }
          else
          {
            long n = PyInt_AsLong(rv);
            
            for (int i=0; i<n; ++i)
            {
              PyObject *po = getPluginObject(getPluginFunc, i);
              if (po != 0)
              {
                entry.plugins.push_back(po);
              }
            }
            
            if (entry.plugins.size() > 0)
            {
              mPluginEntries.push_back(entry);
            }
          }
          
          Py_XDECREF(rv);
          Py_DECREF(getPluginFunc);
          Py_DECREF(getNumberOfPluginsFunc);
          Py_DECREF(mod);
        }
        else
        {
          ofx::Log("pyplugin.ofx: -> Could not load module");
        }
      }
      
      return true;
    }
    
    bool pathEntry(const gcore::Path &p)
    {
      ofx::Log("pyplugin.ofx: Check directory \"%s\" for python plugins...", p.fullname().c_str());
      
      gcore::Path::EachFunc func;
      
      gcore::Bind(this, METHOD(PathLister, fileEntry), func);
      
      p.each(func, false);
      
      return true;
    }
    
    int numberOfPlugins()
    {
      size_t n = 0;
      
      for (size_t i=0; i<mPluginEntries.size(); ++i)
      {
        n += mPluginEntries[i].plugins.size();
      }
      
      return int(n);
    }
    
    OfxPlugin* getPlugin(int i)
    {
      for (size_t j=0; j<mPluginEntries.size(); ++j)
      {
        if (i < (mPluginEntries[j].startIndex))
        {
          break;
        }
        
        if (i < (mPluginEntries[j].startIndex + int(mPluginEntries[j].plugins.size())))
        {
          PyObject *rv = mPluginEntries[j].plugins[i - mPluginEntries[j].startIndex];
          return ((PyOFXPlugin*)rv)->plugin->description();
        }
      }
      
      return 0;
    }
    
  protected:
    
    bool addToSysPath(const gcore::Path &dirname)
    {
      PyObject *modname = PyString_FromString("sys");
      PyObject *mod = PyImport_Import(modname);
      Py_DECREF(modname);
      
      if (mod)
      {
        PyObject *path = PyObject_GetAttrString(mod, "path");
        
        if (path)
        {
          Py_ssize_t sz = PyList_Size(path);
          
          for (Py_ssize_t i=0; i<sz; ++i)
          {
            PyObject *item = PyList_GetItem(path, i);
            char *n = PyString_AsString(item);
            gcore::Path p(n);
            
            if (dirname == p)
            {
              ofx::Log("pyplugin.ofx: Directory \"%s\" already in sys.path", dirname.fullname().c_str());
              // already in path
              Py_DECREF(path);
              Py_DECREF(mod);
              return true;
            }
          }
          
          ofx::Log("pyplugin.ofx: Add directory \"%s\" to sys.path", dirname.fullname().c_str());
          
          PyList_Append(path, PyString_FromString(dirname.fullname().c_str()));
          
          Py_DECREF(path);
          
          return true;
        }
        else
        {
          LogPythonError();
          //PyErr_Clear();
        }
        
        Py_DECREF(mod);
      }
      else
      {
        LogPythonError();
        //PyErr_Clear();
      }
      
      return false;
    }
    
    PyObject* loadModule(const gcore::Path &path)
    {
      PyObject *mod = 0;
      
      gcore::String modulename = path.basename();
      
      modulename = modulename.substr(0, modulename.length()-3);
      
      ofx::Log("pyplugin.ofx: Module name \"%s\"", modulename.c_str());
      
      gcore::Path moduledir = path;
      moduledir.pop();
      moduledir.makeAbsolute();
      moduledir.normalize();
      
      ofx::Log("pyplugin.ofx: Module directory \"%s\"", moduledir.fullname().c_str());
      
      if (addToSysPath(moduledir))
      {
        PyObject *pymodname = PyString_FromString(modulename.c_str());
        mod = PyImport_Import(pymodname);
        Py_DECREF(pymodname);
        
        // if any error occured, clear it
        if (PyErr_Occurred() != 0)
        {
          if (mod)
          {
            Py_DECREF(mod);
            mod = 0;
          }
          LogPythonError();
          //PyErr_Clear();
        }
      }
      
      return mod;
    }
    
    PyObject* getPluginObject(PyObject *getPluginFunc, int i)
    {
      if (!mPyOFX)
      {
        PyObject *modName = PyString_FromString("ofx");
        mPyOFX = PyImport_Import(modName);
        Py_DECREF(modName);
        
        if (!mPyOFX)
        {
          LogPythonError();
          return NULL;
        }
      }
      
      PyObject *plugin = 0;
      
      PyObject *args = Py_BuildValue("(i)", i);
      
      plugin = PyObject_CallObject(getPluginFunc, args);
      
      if (PyErr_Occurred() == 0)
      {
        PyObject *pluginClass = PyObject_GetAttrString(mPyOFX, "Plugin");
        
        if (pluginClass)
        {
          if (PyObject_TypeCheck(plugin, (PyTypeObject*)pluginClass))
          {
            if (((PyOFXPlugin*)plugin)->plugin == 0)
            {
              ofx::Log("pyplugin.ofx: getPluginObject: Underlying object not created");
              
              Py_DECREF(plugin);
              plugin = 0;
            }
          }
          else
          {
            ofx::Log("pyplugin.ofx: getPluginObject: Invalid return type");
            
            Py_DECREF(plugin);
            plugin = 0;
          }
        }
        else
        {
          LogPythonError();
          
          Py_DECREF(plugin);
          plugin = 0;
        }
        
        Py_XDECREF(pluginClass);
      }
      else
      {
        LogPythonError();
        
        // just in case
        Py_XDECREF(plugin);
        plugin = 0;
      }
      
      Py_DECREF(args);
      
      return plugin;
    }
    
  protected:
    
    gcore::List<Entry> mPluginEntries;
    PyObject *mPyOFX;
};

// ---

PathLister gPathLister; // when will this be destroyed?

OfxExport int OfxGetNumberOfPlugins(void)
{
  // Initialize python if needed
  if (!Py_IsInitialized())
  {
    ofx::Log("pyplugin.ofx: Init python interpreter");
#if !defined(_WIN32) && !defined(__APPLE__)
    // On Ubunty (9.04 at least), without this hack, python binary modules fail to load
    // After a little search on the web, it seems that Ubuntu's python is compiled a weird way
    char ver[32];
    sprintf(ver, "%.1f", PY_VER);
    std::string pyso = "libpython";
    pyso += ver;
    pyso += ".so";
    dlopen((char*) pyso.c_str(), RTLD_LAZY|RTLD_GLOBAL);
#endif
    Py_SetProgramName("pyOFX");
    Py_Initialize();
  }
  
  PyGILState_STATE gstate = PyGILState_Ensure();
  
  gcore::Env::EachInPathFunc func;
  
  gcore::Bind(&gPathLister, METHOD(PathLister, pathEntry), func);
  
  gcore::Env::EachInPath("OFX_PLUGIN_PATH", func);
  
  int rv = gPathLister.numberOfPlugins();
  
  ofx::Log("pyplugin.ofx: Found %d python plugins", rv);
  
  PyGILState_Release(gstate);
  
  return rv;
}

OfxExport OfxPlugin* OfxGetPlugin(int i)
{
  PyGILState_STATE gstate = PyGILState_Ensure();
  
  OfxPlugin *rv = gPathLister.getPlugin(i);
  
  PyGILState_Release(gstate);
  
  return rv;
}


