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

typedef struct
{
  PyObject_HEAD
  ofx::Plugin *plugin;
} PyOFXPlugin;

class PathLister
{
  public:
    
    struct Entry
    {
      int startIndex;
      int numberOfPlugins;
      gcore::Path pyFile;
      PyObject *getPlugin;
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
        Py_XDECREF(mPluginEntries[i].getPlugin);
      }
      mPluginEntries.clear();
      Py_XDECREF(mPyOFX);
    }
    
    bool fileEntry(const gcore::Path &p)
    {
      if (p.checkExtension("py"))
      {
        PyObject *mod = loadModule(p);
        
        if (mod)
        {
          PyObject *getNumberOfPlugins = PyObject_GetAttrString(mod, "OfxGetNumberOfPlugins");
          
          if (!getNumberOfPlugins)
          {
            PyErr_Clear();
            Py_DECREF(mod);
            return true;
          }
          
          PyObject *getPlugin = PyObject_GetAttrString(mod, "getPlugin");
          
          if (!getPlugin)
          {
            Py_DECREF(getNumberOfPlugins);
            Py_DECREF(mod);
            PyErr_Clear();
            return true;
          }
          
          Entry entry;
          
          entry.pyFile = p;
          entry.getPlugin = 0;
          entry.startIndex = 0;
          entry.numberOfPlugins = 0;
          
          if (mPluginEntries.size() > 0)
          {
            entry.startIndex = mPluginEntries.back().startIndex + mPluginEntries.back().numberOfPlugins;
          }
          
          PyObject *rv = PyObject_CallObject(getNumberOfPlugins, NULL);
          
          if (!rv || !PyInt_Check(rv))
          {
            PyErr_Clear();
          }
          else
          {
            entry.numberOfPlugins = PyInt_AsLong(rv);
            entry.getPlugin = getPlugin;
            Py_INCREF(getPlugin);
            mPluginEntries.push_back(entry);
          }
          
          Py_XDECREF(rv);
          Py_DECREF(getPlugin);
          Py_DECREF(getNumberOfPlugins);
          Py_DECREF(mod);
        }
      }
      
      return true;
    }
    
    bool pathEntry(const gcore::Path &p)
    {
      gcore::Path::EachFunc func;
      
      gcore::Bind(this, METHOD(PathLister, fileEntry), func);
      
      p.each(func, false);
      
      return true;
    }
    
    int numberOfPlugins()
    {
      int n = 0;
      
      for (size_t i=0; i<mPluginEntries.size(); ++i)
      {
        n += mPluginEntries[i].numberOfPlugins;
      }
      
      return n;
    }
    
    OfxPlugin* getPlugin(int i)
    {
      if (!mPyOFX)
      {
        PyObject *modName = PyString_FromString("ofx");
        mPyOFX = PyImport_Import(modName);
        Py_DECREF(modName);
        
        if (!mPyOFX)
        {
          PyErr_Clear();
          return NULL;
        }
      }
      
      OfxPlugin *plugin = 0;
      
      for (size_t j=0; j<mPluginEntries.size(); ++j)
      {
        if (i < (mPluginEntries[j].startIndex))
        {
          break;
        }
        
        if (i < (mPluginEntries[j].startIndex + mPluginEntries[j].numberOfPlugins))
        {
          int idx = i - mPluginEntries[j].startIndex;
            
          PyObject *args = Py_BuildValue("(i)", idx);
          
          PyObject *rv = PyObject_CallObject(mPluginEntries[j].getPlugin, args);
          
          if (PyErr_Occurred() == 0)
          {
            PyObject *pluginClass = PyObject_GetAttrString(mPyOFX, "Plugin");
            
            if (pluginClass && PyObject_TypeCheck(rv, (PyTypeObject*)pluginClass))
            {
              ofx::Plugin *op = ((PyOFXPlugin*)rv)->plugin;
              plugin = op->description();
            }
            
            Py_XDECREF(pluginClass);
          }
          
          PyErr_Clear();
          
          Py_XDECREF(rv);
          Py_DECREF(args);
          
          break;
        }
      }
      
      return plugin;
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
              // already in path
              Py_DECREF(path);
              Py_DECREF(mod);
              return true;
            }
          }
          
          PyList_Append(path, PyString_FromString(dirname.fullname().c_str()));
          
          Py_DECREF(path);
          
          return true;
        }
        else
        {
          PyErr_Clear();
        }
        
        Py_DECREF(mod);
      }
      else
      {
        PyErr_Clear();
      }
      
      return false;
    }
    
    PyObject* loadModule(const gcore::Path &path)
    {
      PyObject *mod = 0;
      
      gcore::String modulename = path.basename();
      
      modulename = modulename.substr(0, modulename.length()-3);
      
      gcore::Path moduledir = path;
      moduledir.pop();
      moduledir.makeAbsolute();
      moduledir.normalize();
      
      if (addToSysPath(moduledir))
      {
        PyObject *pymodname = PyString_FromString(modulename.c_str());
        mod = PyImport_Import(pymodname);
        Py_DECREF(pymodname);
        
        // if any error occured, clear it
        if (PyErr_Occurred() != 0 && mod)
        {
          Py_DECREF(mod);
          mod = 0;
        }
        
        PyErr_Clear();
      }
      
      return mod;
    }
    
  protected:
    
    gcore::List<Entry> mPluginEntries;
    PyObject *mPyOFX;
};

// ---

PathLister gPathLister; // when will this be destroyed?

OfxExport int OfxGetNumberOfPlugins(void)
{
  gcore::Env::EachInPathFunc func;
  
  gcore::Bind(&gPathLister, METHOD(PathLister, pathEntry), func);
  
  gcore::Env::EachInPath("OFX_PLUGIN_PATH", func);
  
  return gPathLister.numberOfPlugins();
}

OfxExport OfxPlugin* OfxGetPlugin(int i)
{
  return gPathLister.getPlugin(i);
}


