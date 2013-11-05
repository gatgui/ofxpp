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

PyTypeObject PyOFXRGBAParameterDescriptorType;
PyTypeObject PyOFXRGBAParameterType;

// ---

int PyOFXRGBAParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::RGBAParameterDescriptor();
  return 0;
}

PyObject* PyOFXRGBAParameterDescriptor_GetDefault(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::RGBAParameterDescriptor *desc = (ofx::RGBAParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  ofx::RGBAColour<double> rv = {0, 0, 0, 1};
  
  CATCH({rv = desc->defaultValue();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *prv = PyObject_CallObject((PyObject*)&PyOFXRGBAColourDType, NULL);
  ((PyOFXRGBAColourD*)prv)->colour = rv;
  return prv;
}

int PyOFXRGBAParameterDescriptor_SetDefault(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyObject_TypeCheck(val, &PyOFXRGBAColourDType))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a ofx.RGBAColourD object");
    return 0;
  }
  
  ofx::RGBAParameterDescriptor *desc = (ofx::RGBAParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->defaultValue(((PyOFXRGBAColourD*)val)->colour);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXRGBAParameterDescriptor_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXRGBAParameterDescriptor_GetDefault, PyOFXRGBAParameterDescriptor_SetDefault, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXRGBAParameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::RGBAParameter();
  return 0;
}

PyObject* PyOFXRGBAParameter_GetDefault(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::RGBAParameter *param = (ofx::RGBAParameter*) pparam->param;
  
  bool failed = false;
  
  ofx::RGBAColour<double> rv = {0, 0, 0, 1};
  
  CATCH({rv = param->defaultValue();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *prv = PyObject_CallObject((PyObject*)&PyOFXRGBAColourDType, NULL);
  ((PyOFXRGBAColourD*)prv)->colour = rv;
  return prv;
}

static PyGetSetDef PyOFXRGBAParameter_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXRGBAParameter_GetDefault, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXRGBAParameter_GetValue(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::RGBAParameter *param = (ofx::RGBAParameter*) pparam->param;
  
  bool failed = false;
  
  ofx::RGBAColour<double> rv = {0, 0, 0, 1};
  
  CATCH({rv = param->getValue();}, failed);
  
  if (failed)
  {
    return false;
  }
  
  PyObject *prv = PyObject_CallObject((PyObject*)&PyOFXRGBAColourDType, NULL);
  ((PyOFXRGBAColourD*)prv)->colour = rv;
  return prv;
}

PyObject* PyOFXRGBAParameter_GetValueAtTime(PyObject *self, PyObject *args)
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
  
  ofx::RGBAParameter *param = (ofx::RGBAParameter*) pparam->param;
  
  bool failed = false;
  
  ofx::RGBAColour<double> rv = {0, 0, 0, 1};
  
  CATCH({rv = param->getValueAtTime(t);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  PyObject *prv = PyObject_CallObject((PyObject*)&PyOFXRGBAColourDType, NULL);
  ((PyOFXRGBAColourD*)prv)->colour = rv;
  return prv;
}

PyObject* PyOFXRGBAParameter_SetValue(PyObject *self, PyObject *args)
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
  
  if (!PyObject_TypeCheck(val, &PyOFXRGBAColourDType))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a ofx.RGBAColourD object");
    return NULL;
  }
  
  ofx::RGBAParameter *param = (ofx::RGBAParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->setValue(((PyOFXRGBAColourD*)val)->colour);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXRGBAParameter_SetValueAtTime(PyObject *self, PyObject *args)
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
  
  if (!PyObject_TypeCheck(val, &PyOFXRGBAColourDType))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a ofx.RGBAColourD object");
    return NULL;
  }
  
  ofx::RGBAParameter *param = (ofx::RGBAParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->setValueAtTime(t, ((PyOFXRGBAColourD*)val)->colour);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXRGBAParameter_GetIntegral(PyObject *self, PyObject *args)
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
  
  ofx::RGBAParameter *param = (ofx::RGBAParameter*) pparam->param;
  
  bool failed = false;
  
  ofx::RGBAColour<double> rv = {0, 0, 0, 1};
  
  CATCH({rv = param->getIntegral(t0, t1);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  PyObject *prv = PyObject_CallObject((PyObject*)&PyOFXRGBAColourDType, NULL);
  ((PyOFXRGBAColourD*)prv)->colour = rv;
  return prv;
}

PyObject* PyOFXRGBAParameter_GetDerivative(PyObject *self, PyObject *args)
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
  
  ofx::RGBAParameter *param = (ofx::RGBAParameter*) pparam->param;
  
  bool failed = false;
  
  ofx::RGBAColour<double> rv = {0, 0, 0, 1};
  
  CATCH({rv = param->getDerivative(t);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  PyObject *prv = PyObject_CallObject((PyObject*)&PyOFXRGBAColourDType, NULL);
  ((PyOFXRGBAColourD*)prv)->colour = rv;
  return prv;
}

static PyMethodDef PyOFXRGBAParameter_Methods[] =
{
  {"setValue", PyOFXRGBAParameter_SetValue, METH_VARARGS, NULL},
  {"getValue", PyOFXRGBAParameter_GetValue, METH_VARARGS, NULL},
  {"setValueAtTime", PyOFXRGBAParameter_SetValueAtTime, METH_VARARGS, NULL},
  {"getValueAtTime", PyOFXRGBAParameter_GetValueAtTime, METH_VARARGS, NULL},
  {"getIntegral", PyOFXRGBAParameter_GetIntegral, METH_VARARGS, NULL},
  {"getDerivative", PyOFXRGBAParameter_GetDerivative, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

// ---

bool PyOFX_InitParameter_RGBA(PyObject *mod)
{
  INIT_TYPE(PyOFXRGBAParameterDescriptorType, "ofx.RGBAParameterDescriptor", PyOFXRGBAParameterDescriptor);
  PyOFXRGBAParameterDescriptorType.tp_base = &PyOFXValueParameterDescriptorType;
  PyOFXRGBAParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXRGBAParameterDescriptorType.tp_init = PyOFXRGBAParameterDescriptor_Init;
  PyOFXRGBAParameterDescriptorType.tp_getset = PyOFXRGBAParameterDescriptor_GetSeters;
  if (PyType_Ready(&PyOFXRGBAParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXRGBAParameterType, "ofx.RGBAParameter", PyOFXRGBAParameter);
  PyOFXRGBAParameterType.tp_base = &PyOFXValueParameterType;
  PyOFXRGBAParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXRGBAParameterType.tp_init = PyOFXRGBAParameter_Init;
  PyOFXRGBAParameterType.tp_getset = PyOFXRGBAParameter_GetSeters;
  PyOFXRGBAParameterType.tp_methods = PyOFXRGBAParameter_Methods;
  if (PyType_Ready(&PyOFXRGBAParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXRGBAParameterDescriptorType);
  PyModule_AddObject(mod, "RGBAParameterDescriptor", (PyObject*)&PyOFXRGBAParameterDescriptorType);
  
  Py_INCREF(&PyOFXRGBAParameterType);
  PyModule_AddObject(mod, "RGBAParameter", (PyObject*)&PyOFXRGBAParameterType);
  
  return true;
}
