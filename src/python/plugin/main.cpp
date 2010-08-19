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

/* Snippets from lwx

void addToSysPath(const std::string &dirname) {
  PyObject *modname = PyString_FromString("sys");
  PyObject *mod = PyImport_Import(modname);
  Py_DECREF(modname);
  if (mod) {
    PyObject *path = PyObject_GetAttrString(mod, "path");
    if (path) {
      long sz = PyList_Size(path);
      for (long i=0; i<sz; ++i) {
        PyObject *item = PyList_GetItem(path, i);
        char *n = PyString_AsString(item);
        if (lwc::file::IsSamePath(dirname, n)) {
          Py_DECREF(path);
          Py_DECREF(mod);
          return;
        }
      }
      PyList_Append(path, PyString_FromString(dirname.c_str()));
      Py_DECREF(path);
    }
    Py_DECREF(mod);
  }
}

void loadModule(const std::string &path) {
  std::string modulename = lwc::file::Basename(path);
  modulename = modulename.substr(0, modulename.length()-3);

  std::string dirname = lwc::file::NormalizePath(lwc::file::MakeAbsolutePath(lwc::file::Dirname(path)));

  addToSysPath(dirname);

  PyObject *pymodname;
  pymodname = PyString_FromString(modulename.c_str());
  PyObject *mod = PyImport_Import(pymodname);
  Py_DECREF(pymodname);
}

*/

#include <ofx/ofx.h>
#include <gcore/path.h>
#include <gcore/env.h>

class PathLister
{
  public:
    
    PathLister()
    {
      
    }
    
    ~PathLister()
    {
      
    }
    
    bool pathEntry(const Path &p)
    {
      
    }
    
  protected:
    
    struct Entry
    {
      size_t startIndex;
      gcore::Path pyFile;
    };
    
    gcore::List<Entry> mPathEntry;
};

OfxExport int OfxGetNumberOfPlugins(void)
{
  gcore::Env::EachInPathFunc func;
  gcore::MakeCallback(&PathEntry, func);
  gcore::Env::EachInPath("OFX_PLUGIN_PATH", func);
  return 1;
}

OfxExport OfxPlugin* OfxGetPlugin(int i)
{
  if (i == 0)
  {
  }
  return NULL;
}


