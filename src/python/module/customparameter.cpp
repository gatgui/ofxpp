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

PyTypeObject PyOFXCustomParameterDescriptorType;
PyTypeObject PyOFXCustomParameterType;

// ---

std::map<PyInterpolatorKey, PyObject*> gPyInterpolators;

std::string PyInterpolator(ofx::ParameterSet &params,
                           const std::string &paramName,
                           ofx::Time t,
                           ofx::Time t0, const std::string &v0,
                           ofx::Time t1, const std::string &v1,
                           double amount)
{
  PyInterpolatorKey key = {params.handle(), paramName};
  
  std::map<PyInterpolatorKey, PyObject*>::iterator it = gPyInterpolators.find(key);
  
  if (it == gPyInterpolators.end())
  {
    throw ofx::FailedError("No associated python interpolation function");
  }
  
  PyObject *ppset = PyObject_CallObject((PyObject*)&PyOFXParameterSetType, NULL);
  ofx::ParameterSet *pset = ((PyOFXParameterSet*)ppset)->pset;
  *pset = params;
  
  PyObject *args = Py_BuildValue("Osddsdsd", ppset, paramName.c_str(), t, t0, v0.c_str(), t1, v1.c_str(), amount);
  
  PyObject *iv = PyObject_CallObject(it->second, args);
  
  Py_DECREF(args);
  Py_DECREF(ppset);
  
  if (!PyString_Check(iv))
  {
    Py_DECREF(iv);
    throw ofx::ValueError("Python interpolation function should return a string");
  }
  
  std::string rv = PyString_AsString(iv);
  Py_DECREF(iv);
  
  return rv;
}

OfxInterpFunc PyOFXInterpolator = &ofx::InterpFuncWrap<PyInterpolator>;

// ---

int PyOFXCustomParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::CustomParameterDescriptor();
  return 0;
}

PyObject* PyOFXCustomParameterDescriptor_GetDefault(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::CustomParameterDescriptor *desc = (ofx::CustomParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = desc->defaultValue();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

int PyOFXCustomParameterDescriptor_SetDefault(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  ofx::CustomParameterDescriptor *desc = (ofx::CustomParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  std::string s = PyString_AsString(val);
  
  CATCH({desc->defaultValue(s);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXCustomParameterDescriptor_GetInterpCallback(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  //ofx::CustomParameterDescriptor *desc = (ofx::CustomParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  // this -> need to get PyInterpolatorKey from this... 
  //      -> need to get parameter set handle and parameter name 
  //      -> for descriptor, we don't have yet and parametersethandle anyway
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

int PyOFXCustomParameterDescriptor_SetInterpCallback(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyFunction_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a funcion");
    return -1;
  }
  
  ofx::CustomParameterDescriptor *desc = (ofx::CustomParameterDescriptor*) pdesc->desc;
  
  /*
  PyInterpolatorKey key = {desc->getHandle(), desc->getName()};
  if (gPyInterpolators.find(key) == gPyInterpolators.end())
  {
    gPyInterpolators[key] = val;
  }
  */
  
  desc->interpCallback(PyOFXInterpolator);
  
  return 0;
}

static PyGetSetDef PyOFXCustomParameterDescriptor_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXCustomParameterDescriptor_GetDefault, PyOFXCustomParameterDescriptor_SetDefault, NULL, NULL},
  {(char*)"interpCallback", PyOFXCustomParameterDescriptor_GetInterpCallback, PyOFXCustomParameterDescriptor_SetInterpCallback, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXCustomParameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::CustomParameter();
  return 0;
}

PyObject* PyOFXCustomParameter_GetDefault(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::CustomParameter *param = (ofx::CustomParameter*) pparam->param;
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = param->defaultValue();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXCustomParameter_GetInterpCallback(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  //ofx::CustomParameter *param = (ofx::CustomParameter*) pparam->param;
  
  bool failed = false;
  
  // this -> need to get PyInterpolatorKey from this... 
  //      -> need to get parameter set handle and parameter name 
  //      -> for descriptor, we don't have yet and parametersethandle anyway
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

static PyGetSetDef PyOFXCustomParameter_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXCustomParameter_GetDefault, NULL, NULL, NULL},
  {(char*)"interpCallback", PyOFXCustomParameter_GetInterpCallback, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXCustomParameter_GetValue(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::CustomParameter *param = (ofx::CustomParameter*) pparam->param;
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = param->getValue();}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXCustomParameter_GetValueAtTime(PyObject *self, PyObject *args)
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
  
  ofx::CustomParameter *param = (ofx::CustomParameter*) pparam->param;
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = param->getValueAtTime(t);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXCustomParameter_SetValue(PyObject *self, PyObject *args)
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
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Exepected a string");
    return NULL;
  }
  
  ofx::CustomParameter *param = (ofx::CustomParameter*) pparam->param;
  
  bool failed = false;
  
  std::string s = PyString_AsString(val);
  
  CATCH({param->setValue(s);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXCustomParameter_SetValueAtTime(PyObject *self, PyObject *args)
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
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Exepected a string");
    return NULL;
  }
  
  ofx::CustomParameter *param = (ofx::CustomParameter*) pparam->param;
  
  bool failed = false;
  
  std::string s = PyString_AsString(val);
  
  CATCH({param->setValueAtTime(t, s);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

static PyMethodDef PyOFXCustomParameter_Methods[] =
{
  {"setValue", PyOFXCustomParameter_SetValue, METH_VARARGS, NULL},
  {"getValue", PyOFXCustomParameter_GetValue, METH_VARARGS, NULL},
  {"setValueAtTime", PyOFXCustomParameter_SetValueAtTime, METH_VARARGS, NULL},
  {"getValueAtTime", PyOFXCustomParameter_GetValueAtTime, METH_VARARGS, NULL},
  {NULL, NULL, NULL, NULL}
};

// ---

bool PyOFX_InitParameter_Custom(PyObject *mod)
{
  INIT_TYPE(PyOFXCustomParameterDescriptorType, "ofx.CustomParameterDescriptor", PyOFXCustomParameterDescriptor);
  PyOFXCustomParameterDescriptorType.tp_base = &PyOFXValueParameterDescriptorType;
  PyOFXCustomParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXCustomParameterDescriptorType.tp_init = PyOFXCustomParameterDescriptor_Init;
  PyOFXCustomParameterDescriptorType.tp_getset = PyOFXCustomParameterDescriptor_GetSeters;
  if (PyType_Ready(&PyOFXCustomParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXCustomParameterType, "ofx.CustomParameter", PyOFXCustomParameter);
  PyOFXCustomParameterType.tp_base = &PyOFXValueParameterType;
  PyOFXCustomParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXCustomParameterType.tp_init = PyOFXCustomParameter_Init;
  PyOFXCustomParameterType.tp_getset = PyOFXCustomParameter_GetSeters;
  PyOFXCustomParameterType.tp_methods = PyOFXCustomParameter_Methods;
  if (PyType_Ready(&PyOFXCustomParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXCustomParameterDescriptorType);
  PyModule_AddObject(mod, "CustomParameterDescriptor", (PyObject*)&PyOFXCustomParameterDescriptorType);
  
  Py_INCREF(&PyOFXCustomParameterType);
  PyModule_AddObject(mod, "CustomParameter", (PyObject*)&PyOFXCustomParameterType);
  
  return true;
}

