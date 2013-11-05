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

#include "common.h"

PyTypeObject PyOFXPageParameterDescriptorType;
PyTypeObject PyOFXPageParameterType;

// ---

int PyOFXPageParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::PageParameterDescriptor();
  return 0;
}

PyObject* PyOFXPageParameterDescriptor_ChildCount(PyObject *self, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::PageParameterDescriptor *desc = (ofx::PageParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = desc->childCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXPageParameterDescriptor_Child(PyObject *self, PyObject *args)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  Py_ssize_t nargs = PyTuple_Size(args);
  if (nargs < 1 || nargs > 2)
  {
    PyErr_SetString(PyExc_RuntimeError, "At least 1 argument, at most 2");
    return NULL;
  }
  
  if (!PyInt_Check(PyTuple_GetItem(args, 0)))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer for first argument");
    return NULL;
  }
  
  int idx = PyInt_AsLong(PyTuple_GetItem(args, 0));
  PyObject *pval = 0;
  
  if (nargs == 2)
  {
    pval = PyTuple_GetItem(args, 1);
  }
  
  ofx::PageParameterDescriptor *desc = (ofx::PageParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  if (pval)
  {
    if (!PyString_Check(pval))
    {
      PyErr_SetString(PyExc_TypeError, "Expected a string");
      return NULL;
    }
    
    char *val = PyString_AsString(pval);
    
    CATCH({desc->child(idx, val);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    Py_RETURN_NONE;
  }
  else
  {
    std::string rv;
    
    CATCH({rv = desc->child(idx);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    return PyString_FromString(rv.c_str());
  }
}

static PyMethodDef PyOFXPageParameterDescriptor_Methods[] =
{
  {"childCount", PyOFXPageParameterDescriptor_ChildCount, METH_VARARGS, NULL},
  {"child", PyOFXPageParameterDescriptor_Child, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

// ---

int PyOFXPageParameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::PageParameter();
  return 0;
}

PyObject* PyOFXPageParameter_ChildCount(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::PageParameter *param = (ofx::PageParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->childCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXPageParameter_Child(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx = 0;
  
  if (!PyArg_ParseTuple(args, "i", &idx))
  {
    return NULL;
  }
  
  ofx::PageParameter *param = (ofx::PageParameter*) pparam->param;
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = param->child(idx);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

static PyMethodDef PyOFXPageParameter_Methods[] =
{
  {"childCount", PyOFXPageParameter_ChildCount, METH_VARARGS, NULL},
  {"child", PyOFXPageParameter_Child, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

// ---

bool PyOFX_InitParameter_Page(PyObject *mod)
{
  INIT_TYPE(PyOFXPageParameterDescriptorType, "ofx.PageParameterDescriptor", PyOFXPageParameterDescriptor);
  PyOFXPageParameterDescriptorType.tp_base = &PyOFXParameterDescriptorType;
  PyOFXPageParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXPageParameterDescriptorType.tp_init = PyOFXPageParameterDescriptor_Init;
  PyOFXPageParameterDescriptorType.tp_methods = PyOFXPageParameterDescriptor_Methods;
  if (PyType_Ready(&PyOFXPageParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXPageParameterType, "ofx.PageParameter", PyOFXPageParameter);
  PyOFXPageParameterType.tp_base = &PyOFXParameterType;
  PyOFXPageParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXPageParameterType.tp_init = PyOFXPageParameter_Init;
  PyOFXPageParameterType.tp_methods = PyOFXPageParameter_Methods;
  if (PyType_Ready(&PyOFXPageParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXPageParameterDescriptorType);
  PyModule_AddObject(mod, "PageParameterDescriptor", (PyObject*)&PyOFXPageParameterDescriptorType);
  
  Py_INCREF(&PyOFXPageParameterType);
  PyModule_AddObject(mod, "PageParameter", (PyObject*)&PyOFXPageParameterType);
  
  return true;
}
