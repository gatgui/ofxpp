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

PyTypeObject PyOFXIntParameterDescriptorType;
PyTypeObject PyOFXIntParameterType;

// ---

int PyOFXIntParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::IntParameterDescriptor();
  return 0;
}

PyObject* PyOFXIntParameterDescriptor_GetDefault(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::IntParameterDescriptor *desc = (ofx::IntParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = desc->defaultValue();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXIntParameterDescriptor_SetDefault(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int v = PyInt_AsLong(val);
  
  ofx::IntParameterDescriptor *desc = (ofx::IntParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->defaultValue(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXIntParameterDescriptor_GetMin(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::IntParameterDescriptor *desc = (ofx::IntParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = desc->min();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXIntParameterDescriptor_SetMin(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int v = PyInt_AsLong(val);
  
  ofx::IntParameterDescriptor *desc = (ofx::IntParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->min(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXIntParameterDescriptor_GetMax(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::IntParameterDescriptor *desc = (ofx::IntParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = desc->max();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXIntParameterDescriptor_SetMax(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int v = PyInt_AsLong(val);
  
  ofx::IntParameterDescriptor *desc = (ofx::IntParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->max(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXIntParameterDescriptor_GetDisplayMin(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::IntParameterDescriptor *desc = (ofx::IntParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = desc->displayMin();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXIntParameterDescriptor_SetDisplayMin(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int v = PyInt_AsLong(val);
  
  ofx::IntParameterDescriptor *desc = (ofx::IntParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->displayMin(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXIntParameterDescriptor_GetDisplayMax(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::IntParameterDescriptor *desc = (ofx::IntParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = desc->displayMax();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXIntParameterDescriptor_SetDisplayMax(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int v = PyInt_AsLong(val);
  
  ofx::IntParameterDescriptor *desc = (ofx::IntParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->displayMax(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXIntParameterDescriptor_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXIntParameterDescriptor_GetDefault, PyOFXIntParameterDescriptor_SetDefault, NULL, NULL},
  {(char*)"min", PyOFXIntParameterDescriptor_GetMin, PyOFXIntParameterDescriptor_SetMin, NULL, NULL},
  {(char*)"max", PyOFXIntParameterDescriptor_GetMax, PyOFXIntParameterDescriptor_SetMax, NULL, NULL},
  {(char*)"displayMin", PyOFXIntParameterDescriptor_GetDisplayMin, PyOFXIntParameterDescriptor_SetDisplayMin, NULL, NULL},
  {(char*)"displayMax", PyOFXIntParameterDescriptor_GetDisplayMax, PyOFXIntParameterDescriptor_SetDisplayMax, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXIntParameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::IntParameter();
  return 0;
}

PyObject* PyOFXIntParameter_GetDefault(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::IntParameter *param = (ofx::IntParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->defaultValue();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXIntParameter_GetMin(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::IntParameter *param = (ofx::IntParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->min();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXIntParameter_SetMin(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int v = PyInt_AsLong(val);
  
  ofx::IntParameter *param = (ofx::IntParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->min(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXIntParameter_GetMax(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::IntParameter *param = (ofx::IntParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->max();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXIntParameter_SetMax(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int v = PyInt_AsLong(val);
  
  ofx::IntParameter *param = (ofx::IntParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->max(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXIntParameter_GetDisplayMin(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::IntParameter *param = (ofx::IntParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->displayMin();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXIntParameter_SetDisplayMin(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int v = PyInt_AsLong(val);
  
  ofx::IntParameter *param = (ofx::IntParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->displayMin(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXIntParameter_GetDisplayMax(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::IntParameter *param = (ofx::IntParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->displayMax();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXIntParameter_SetDisplayMax(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int v = PyInt_AsLong(val);
  
  ofx::IntParameter *param = (ofx::IntParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->displayMax(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXIntParameter_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXIntParameter_GetDefault, NULL, NULL, NULL},
  {(char*)"min", PyOFXIntParameter_GetMin, PyOFXIntParameter_SetMin, NULL, NULL},
  {(char*)"max", PyOFXIntParameter_GetMax, PyOFXIntParameter_SetMax, NULL, NULL},
  {(char*)"displayMin", PyOFXIntParameter_GetDisplayMin, PyOFXIntParameter_SetDisplayMin, NULL, NULL},
  {(char*)"displayMax", PyOFXIntParameter_GetDisplayMax, PyOFXIntParameter_SetDisplayMax, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXIntParameter_GetValue(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::IntParameter *param = (ofx::IntParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->getValue();}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXIntParameter_GetValueAtTime(PyObject *self, PyObject *args)
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
  
  ofx::IntParameter *param = (ofx::IntParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->getValueAtTime(t);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXIntParameter_GetDerivative(PyObject *self, PyObject *args)
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
  
  ofx::IntParameter *param = (ofx::IntParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->getDerivative(t);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXIntParameter_GetIntegral(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  double t0, t1;
  
  if (!PyArg_ParseTuple(args, "dd", &t0, &t1))
  {
    return NULL;
  }
  
  ofx::IntParameter *param = (ofx::IntParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->getIntegral(t0, t1);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXIntParameter_SetValue(PyObject *self, PyObject *args)
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
  
  ofx::IntParameter *param = (ofx::IntParameter*) pparam->param;
  
  bool failed = false;
  
  int v = PyInt_AsLong(val);
  
  CATCH({param->setValue(v);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXIntParameter_SetValueAtTime(PyObject *self, PyObject *args)
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
  
  ofx::IntParameter *param = (ofx::IntParameter*) pparam->param;
  
  bool failed = false;
  
  int v = PyInt_AsLong(val);
  
  CATCH({param->setValueAtTime(t, v);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

static PyMethodDef PyOFXIntParameter_Methods[] =
{
  {"setValue", PyOFXIntParameter_SetValue, METH_VARARGS, NULL},
  {"getValue", PyOFXIntParameter_GetValue, METH_VARARGS, NULL},
  {"setValueAtTime", PyOFXIntParameter_SetValueAtTime, METH_VARARGS, NULL},
  {"getValueAtTime", PyOFXIntParameter_GetValueAtTime, METH_VARARGS, NULL},
  {"getDerivative", PyOFXIntParameter_GetDerivative, METH_VARARGS, NULL},
  {"getIntegral", PyOFXIntParameter_GetIntegral, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

// ---

bool PyOFX_InitParameter_Int(PyObject *mod)
{
  INIT_TYPE(PyOFXIntParameterDescriptorType, "ofx.IntParameterDescriptor", PyOFXIntParameterDescriptor);
  PyOFXIntParameterDescriptorType.tp_base = &PyOFXValueParameterDescriptorType;
  PyOFXIntParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXIntParameterDescriptorType.tp_init = PyOFXIntParameterDescriptor_Init;
  PyOFXIntParameterDescriptorType.tp_getset = PyOFXIntParameterDescriptor_GetSeters;
  if (PyType_Ready(&PyOFXIntParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXIntParameterType, "ofx.IntParameter", PyOFXIntParameter);
  PyOFXIntParameterType.tp_base = &PyOFXValueParameterType;
  PyOFXIntParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXIntParameterType.tp_init = PyOFXIntParameter_Init;
  PyOFXIntParameterType.tp_getset = PyOFXIntParameter_GetSeters;
  PyOFXIntParameterType.tp_methods = PyOFXIntParameter_Methods;
  if (PyType_Ready(&PyOFXIntParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXIntParameterDescriptorType);
  PyModule_AddObject(mod, "IntParameterDescriptor", (PyObject*)&PyOFXIntParameterDescriptorType);
  
  Py_INCREF(&PyOFXIntParameterType);
  PyModule_AddObject(mod, "IntParameter", (PyObject*)&PyOFXIntParameterType);
  
  return true;
}
