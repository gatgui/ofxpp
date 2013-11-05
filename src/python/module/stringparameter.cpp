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

PyTypeObject PyOFXStringParameterDescriptorType;
PyTypeObject PyOFXStringParameterType;

// ---

int PyOFXStringParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::StringParameterDescriptor();
  return 0;
}

PyObject* PyOFXStringParameterDescriptor_GetDefault(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::StringParameterDescriptor *desc = (ofx::StringParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = desc->defaultValue();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

int PyOFXStringParameterDescriptor_SetDefault(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::StringParameterDescriptor *desc = (ofx::StringParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  char *v = PyString_AsString(val);
  
  CATCH({desc->defaultValue(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXStringParameterDescriptor_GetMode(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::StringParameterDescriptor *desc = (ofx::StringParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  ofx::StringParamMode rv = ofx::MaxStringParamMode;
  
  CATCH({rv = desc->mode();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(int(rv));
}

int PyOFXStringParameterDescriptor_SetMode(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::StringParameterDescriptor *desc = (ofx::StringParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int m = PyInt_AsLong(val);
  
  CATCH({desc->mode(ofx::StringParamMode(m));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXStringParameterDescriptor_GetFilePathExists(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::StringParameterDescriptor *desc = (ofx::StringParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = desc->filePathExists();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_RETURN_TRUE;
  }
  else
  {
    Py_RETURN_FALSE;
  }
}

int PyOFXStringParameterDescriptor_SetFilePathExists(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::StringParameterDescriptor *desc = (ofx::StringParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->filePathExists(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXStringParameterDescriptor_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXStringParameterDescriptor_GetDefault, PyOFXStringParameterDescriptor_SetDefault, NULL, NULL},
  {(char*)"mode", PyOFXStringParameterDescriptor_GetMode, PyOFXStringParameterDescriptor_SetMode, NULL, NULL},
  {(char*)"filePathExists", PyOFXStringParameterDescriptor_GetFilePathExists, PyOFXStringParameterDescriptor_SetFilePathExists, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXStringParameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::StringParameter();
  return 0;
}

PyObject* PyOFXStringParameter_GetDefault(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::StringParameter *param = (ofx::StringParameter*) pparam->param;
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = param->defaultValue();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXStringParameter_GetMode(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::StringParameter *param = (ofx::StringParameter*) pparam->param;
  
  bool failed = false;
  
  ofx::StringParamMode rv = ofx::MaxStringParamMode;
  
  CATCH({rv = param->mode();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(int(rv));
}

PyObject* PyOFXStringParameter_GetFilePathExists(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::StringParameter *param = (ofx::StringParameter*) pparam->param;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = param->filePathExists();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_RETURN_TRUE;
  }
  else
  {
    Py_RETURN_FALSE;
  }
}

static PyGetSetDef PyOFXStringParameter_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXStringParameter_GetDefault, NULL, NULL, NULL},
  {(char*)"mode", PyOFXStringParameter_GetMode, NULL, NULL, NULL},
  {(char*)"filePathExists", PyOFXStringParameter_GetFilePathExists, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXStringParameter_GetValue(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::StringParameter *param = (ofx::StringParameter*) pparam->param;
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = param->getValue();}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXStringParameter_GetValueAtTime(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  double t;
  
  if (!PyArg_ParseTuple(args, "d", &t))
  {
    return NULL;
  }
  
  ofx::StringParameter *param = (ofx::StringParameter*) pparam->param;
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = param->getValueAtTime(t);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXStringParameter_SetValue(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyObject *val = 0;
  
  if (!PyArg_ParseTuple(args, "O", &val))
  {
    return NULL;
  }
  
  ofx::StringParameter *param = (ofx::StringParameter*) pparam->param;
  
  bool failed = false;
  
  char *v = PyString_AsString(val);
  
  CATCH({param->setValue(v);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXStringParameter_SetValueAtTime(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyObject *val = 0;
  double t = 0.0;
  
  if (!PyArg_ParseTuple(args, "dO", &t, &val))
  {
    return NULL;
  }
  
  ofx::StringParameter *param = (ofx::StringParameter*) pparam->param;
  
  bool failed = false;
  
  char *v = PyString_AsString(val);
  
  CATCH({param->setValueAtTime(t, v);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

static PyMethodDef PyOFXStringParameter_Methods[] =
{
  {"setValue", PyOFXStringParameter_SetValue, METH_VARARGS, NULL},
  {"getValue", PyOFXStringParameter_GetValue, METH_VARARGS, NULL},
  {"setValueAtTime", PyOFXStringParameter_SetValueAtTime, METH_VARARGS, NULL},
  {"getValueAtTime", PyOFXStringParameter_GetValueAtTime, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

// ---

bool PyOFX_InitParameter_String(PyObject *mod)
{
  INIT_TYPE(PyOFXStringParameterDescriptorType, "ofx.StringParameterDescriptor", PyOFXStringParameterDescriptor);
  PyOFXStringParameterDescriptorType.tp_base = &PyOFXValueParameterDescriptorType;
  PyOFXStringParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXStringParameterDescriptorType.tp_init = PyOFXStringParameterDescriptor_Init;
  PyOFXStringParameterDescriptorType.tp_getset = PyOFXStringParameterDescriptor_GetSeters;
  if (PyType_Ready(&PyOFXStringParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXStringParameterType, "ofx.StringParameter", PyOFXStringParameter);
  PyOFXStringParameterType.tp_base = &PyOFXValueParameterType;
  PyOFXStringParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXStringParameterType.tp_init = PyOFXStringParameter_Init;
  PyOFXStringParameterType.tp_getset = PyOFXStringParameter_GetSeters;
  PyOFXStringParameterType.tp_methods = PyOFXStringParameter_Methods;
  if (PyType_Ready(&PyOFXStringParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXStringParameterDescriptorType);
  PyModule_AddObject(mod, "StringParameterDescriptor", (PyObject*)&PyOFXStringParameterDescriptorType);
  
  Py_INCREF(&PyOFXStringParameterType);
  PyModule_AddObject(mod, "StringParameter", (PyObject*)&PyOFXStringParameterType);
  
  return true;
}
