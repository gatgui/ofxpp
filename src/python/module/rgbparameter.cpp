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

PyTypeObject PyOFXRGBParameterDescriptorType;
PyTypeObject PyOFXRGBParameterType;

// ---

int PyOFXRGBParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::RGBParameterDescriptor();
  return 0;
}

PyObject* PyOFXRGBParameterDescriptor_GetDefault(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::RGBParameterDescriptor *desc = (ofx::RGBParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  ofx::RGBColour<double> rv = {0, 0, 0};
  
  CATCH({rv = desc->defaultValue();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *prv = PyObject_CallObject((PyObject*)&PyOFXRGBColourDType, NULL);
  ((PyOFXRGBColourD*)prv)->colour = rv;
  return prv;
}

int PyOFXRGBParameterDescriptor_SetDefault(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyObject_TypeCheck(val, &PyOFXRGBColourDType))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a ofx.RGBColourD object");
    return 0;
  }
  
  ofx::RGBParameterDescriptor *desc = (ofx::RGBParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->defaultValue(((PyOFXRGBColourD*)val)->colour);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXRGBParameterDescriptor_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXRGBParameterDescriptor_GetDefault, PyOFXRGBParameterDescriptor_SetDefault, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXRGBParameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::RGBParameter();
  return 0;
}

PyObject* PyOFXRGBParameter_GetDefault(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::RGBParameter *param = (ofx::RGBParameter*) pparam->param;
  
  bool failed = false;
  
  ofx::RGBColour<double> rv = {0, 0, 0};
  
  CATCH({rv = param->defaultValue();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *prv = PyObject_CallObject((PyObject*)&PyOFXRGBColourDType, NULL);
  ((PyOFXRGBColourD*)prv)->colour = rv;
  return prv;
}

static PyGetSetDef PyOFXRGBParameter_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXRGBParameter_GetDefault, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXRGBParameter_GetValue(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::RGBParameter *param = (ofx::RGBParameter*) pparam->param;
  
  bool failed = false;
  
  ofx::RGBColour<double> rv = {0, 0, 0};
  
  CATCH({rv = param->getValue();}, failed);
  
  if (failed)
  {
    return false;
  }
  
  PyObject *prv = PyObject_CallObject((PyObject*)&PyOFXRGBColourDType, NULL);
  ((PyOFXRGBColourD*)prv)->colour = rv;
  return prv;
}

PyObject* PyOFXRGBParameter_GetValueAtTime(PyObject *self, PyObject *args)
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
  
  ofx::RGBParameter *param = (ofx::RGBParameter*) pparam->param;
  
  bool failed = false;
  
  ofx::RGBColour<double> rv = {0, 0, 0};
  
  CATCH({rv = param->getValueAtTime(t);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  PyObject *prv = PyObject_CallObject((PyObject*)&PyOFXRGBColourDType, NULL);
  ((PyOFXRGBColourD*)prv)->colour = rv;
  return prv;
}

PyObject* PyOFXRGBParameter_SetValue(PyObject *self, PyObject *args)
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
  
  if (!PyObject_TypeCheck(val, &PyOFXRGBColourDType))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a ofx.RGBColourD object");
    return NULL;
  }
  
  ofx::RGBParameter *param = (ofx::RGBParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->setValue(((PyOFXRGBColourD*)val)->colour);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXRGBParameter_SetValueAtTime(PyObject *self, PyObject *args)
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
  
  if (!PyObject_TypeCheck(val, &PyOFXRGBColourDType))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a ofx.RGBColourD object");
    return NULL;
  }
  
  ofx::RGBParameter *param = (ofx::RGBParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->setValueAtTime(t, ((PyOFXRGBColourD*)val)->colour);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXRGBParameter_GetIntegral(PyObject *self, PyObject *args)
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
  
  ofx::RGBParameter *param = (ofx::RGBParameter*) pparam->param;
  
  bool failed = false;
  
  ofx::RGBColour<double> rv = {0, 0, 0};
  
  CATCH({rv = param->getIntegral(t0, t1);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  PyObject *prv = PyObject_CallObject((PyObject*)&PyOFXRGBColourDType, NULL);
  ((PyOFXRGBColourD*)prv)->colour = rv;
  return prv;
}

PyObject* PyOFXRGBParameter_GetDerivative(PyObject *self, PyObject *args)
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
  
  ofx::RGBParameter *param = (ofx::RGBParameter*) pparam->param;
  
  bool failed = false;
  
  ofx::RGBColour<double> rv = {0, 0, 0};
  
  CATCH({rv = param->getDerivative(t);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  PyObject *prv = PyObject_CallObject((PyObject*)&PyOFXRGBColourDType, NULL);
  ((PyOFXRGBColourD*)prv)->colour = rv;
  return prv;
}

static PyMethodDef PyOFXRGBParameter_Methods[] =
{
  {"setValue", PyOFXRGBParameter_SetValue, METH_VARARGS, NULL},
  {"getValue", PyOFXRGBParameter_GetValue, METH_VARARGS, NULL},
  {"setValueAtTime", PyOFXRGBParameter_SetValueAtTime, METH_VARARGS, NULL},
  {"getValueAtTime", PyOFXRGBParameter_GetValueAtTime, METH_VARARGS, NULL},
  {"getIntegral", PyOFXRGBParameter_GetIntegral, METH_VARARGS, NULL},
  {"getDerivative", PyOFXRGBParameter_GetDerivative, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

// ---

bool PyOFX_InitParameter_RGB(PyObject *mod)
{
  INIT_TYPE(PyOFXRGBParameterDescriptorType, "ofx.RGBParameterDescriptor", PyOFXRGBParameterDescriptor);
  PyOFXRGBParameterDescriptorType.tp_base = &PyOFXValueParameterDescriptorType;
  PyOFXRGBParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXRGBParameterDescriptorType.tp_init = PyOFXRGBParameterDescriptor_Init;
  PyOFXRGBParameterDescriptorType.tp_getset = PyOFXRGBParameterDescriptor_GetSeters;
  if (PyType_Ready(&PyOFXRGBParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXRGBParameterType, "ofx.RGBParameter", PyOFXRGBParameter);
  PyOFXRGBParameterType.tp_base = &PyOFXValueParameterType;
  PyOFXRGBParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXRGBParameterType.tp_init = PyOFXRGBParameter_Init;
  PyOFXRGBParameterType.tp_getset = PyOFXRGBParameter_GetSeters;
  PyOFXRGBParameterType.tp_methods = PyOFXRGBParameter_Methods;
  if (PyType_Ready(&PyOFXRGBParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXRGBParameterDescriptorType);
  PyModule_AddObject(mod, "RGBParameterDescriptor", (PyObject*)&PyOFXRGBParameterDescriptorType);
  
  Py_INCREF(&PyOFXRGBParameterType);
  PyModule_AddObject(mod, "RGBParameter", (PyObject*)&PyOFXRGBParameterType);
  
  return true;
}
