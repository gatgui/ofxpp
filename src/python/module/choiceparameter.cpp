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

PyTypeObject PyOFXChoiceParameterDescriptorType;
PyTypeObject PyOFXChoiceParameterType;

// ---

int PyOFXChoiceParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::ChoiceParameterDescriptor();
  return 0;
}

PyObject* PyOFXChoiceParameterDescriptor_GetDefault(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ChoiceParameterDescriptor *desc = (ofx::ChoiceParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = desc->defaultValue();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXChoiceParameterDescriptor_SetDefault(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ChoiceParameterDescriptor *desc = (ofx::ChoiceParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->defaultValue(PyInt_AsLong(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXChoiceParameterDescriptor_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXChoiceParameterDescriptor_GetDefault, PyOFXChoiceParameterDescriptor_SetDefault, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXChoiceParameterDescriptor_ChoiceOptionCount(PyObject *self, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ChoiceParameterDescriptor *desc = (ofx::ChoiceParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = desc->choiceOptionCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXChoiceParameterDescriptor_ChoiceOption(PyObject *self, PyObject *args)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx;
  PyObject *pval = 0;
  
  if (!PyArg_ParseTuple(args, "i|O", &idx, &pval))
  {
    return NULL;
  }
  
  ofx::ChoiceParameterDescriptor *desc = (ofx::ChoiceParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  if (pval == 0)
  {
    std::string rv;
    
    CATCH({rv = desc->choiceOption(idx);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    return PyString_FromString(rv.c_str());
  }
  else
  {
    if (!PyString_Check(pval))
    {
      PyErr_SetString(PyExc_TypeError, "Exepected a string");
      return NULL;
    }

    std::string val = PyString_AsString(pval);
    
    CATCH({desc->choiceOption(idx, val);}, failed);

    if (failed)
    {
      return NULL;
    }

    Py_RETURN_NONE;
  }
}

static PyMethodDef PyOFXChoiceParameterDescriptor_Methods[] =
{
  {"choiceOption", PyOFXChoiceParameterDescriptor_ChoiceOption, METH_VARARGS, NULL},
  {"choiceOptionCount", PyOFXChoiceParameterDescriptor_ChoiceOptionCount, METH_VARARGS, NULL},
  {NULL, NULL, NULL, NULL}
};

// ---

int PyOFXChoiceParameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::ChoiceParameter();
  return 0;
}

PyObject* PyOFXChoiceParameter_GetDefault(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ChoiceParameter *param = (ofx::ChoiceParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->defaultValue();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

static PyGetSetDef PyOFXChoiceParameter_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXChoiceParameter_GetDefault, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXChoiceParameter_GetValue(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ChoiceParameter *param = (ofx::ChoiceParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->getValue();}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXChoiceParameter_GetValueAtTime(PyObject *self, PyObject *args)
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
  
  ofx::ChoiceParameter *param = (ofx::ChoiceParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->getValueAtTime(t);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXChoiceParameter_SetValue(PyObject *self, PyObject *args)
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
  
  ofx::ChoiceParameter *param = (ofx::ChoiceParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->setValue(PyInt_AsLong(val));}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXChoiceParameter_SetValueAtTime(PyObject *self, PyObject *args)
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
  
  ofx::ChoiceParameter *param = (ofx::ChoiceParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->setValueAtTime(t, PyInt_AsLong(val));}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXChoiceParameter_ChoiceOptionCount(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ChoiceParameter *param = (ofx::ChoiceParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->choiceOptionCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXChoiceParameter_ChoiceOption(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx;
  PyObject *pval = 0;
  
  if (!PyArg_ParseTuple(args, "i|O", &idx, &pval))
  {
    return NULL;
  }
  
  ofx::ChoiceParameter *param = (ofx::ChoiceParameter*) pparam->param;
  
  bool failed = false;
  
  if (pval == 0)
  {
    std::string rv;
  
    CATCH({rv = param->choiceOption(idx);}, failed);
  
    if (failed)
    {
      return NULL;
    }
  
    return PyString_FromString(rv.c_str());
  }
  else
  {
    if (!PyString_Check(pval))
    {
      PyErr_SetString(PyExc_TypeError, "Exepected a string");
      return NULL;
    }

    std::string val = PyString_AsString(pval);
    
    CATCH({param->choiceOption(idx, val);}, failed);

    if (failed)
    {
      return NULL;
    }

    Py_RETURN_NONE;
  }
}

static PyMethodDef PyOFXChoiceParameter_Methods[] =
{
  {"setValue", PyOFXChoiceParameter_SetValue, METH_VARARGS, NULL},
  {"getValue", PyOFXChoiceParameter_GetValue, METH_VARARGS, NULL},
  {"setValueAtTime", PyOFXChoiceParameter_SetValueAtTime, METH_VARARGS, NULL},
  {"getValueAtTime", PyOFXChoiceParameter_GetValueAtTime, METH_VARARGS, NULL},
  {"choiceOptionCount", PyOFXChoiceParameter_ChoiceOptionCount, METH_VARARGS, NULL},
  {"choiceOption", PyOFXChoiceParameter_ChoiceOption, METH_VARARGS, NULL},
  {NULL, NULL, NULL, NULL}
};

// ---

bool PyOFX_InitParameter_Choice(PyObject *mod)
{
  INIT_TYPE(PyOFXChoiceParameterDescriptorType, "ofx.ChoiceParameterDescriptor", PyOFXChoiceParameterDescriptor);
  PyOFXChoiceParameterDescriptorType.tp_base = &PyOFXValueParameterDescriptorType;
  PyOFXChoiceParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXChoiceParameterDescriptorType.tp_init = PyOFXChoiceParameterDescriptor_Init;
  PyOFXChoiceParameterDescriptorType.tp_getset = PyOFXChoiceParameterDescriptor_GetSeters;
  PyOFXChoiceParameterDescriptorType.tp_methods = PyOFXChoiceParameterDescriptor_Methods;
  if (PyType_Ready(&PyOFXChoiceParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXChoiceParameterType, "ofx.ChoiceParameter", PyOFXChoiceParameter);
  PyOFXChoiceParameterType.tp_base = &PyOFXValueParameterType;
  PyOFXChoiceParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXChoiceParameterType.tp_init = PyOFXChoiceParameter_Init;
  PyOFXChoiceParameterType.tp_getset = PyOFXChoiceParameter_GetSeters;
  PyOFXChoiceParameterType.tp_methods = PyOFXChoiceParameter_Methods;
  if (PyType_Ready(&PyOFXChoiceParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXChoiceParameterDescriptorType);
  PyModule_AddObject(mod, "ChoiceParameterDescriptor", (PyObject*)&PyOFXChoiceParameterDescriptorType);
  
  Py_INCREF(&PyOFXChoiceParameterType);
  PyModule_AddObject(mod, "ChoiceParameter", (PyObject*)&PyOFXChoiceParameterType);
  
  return true;
}
