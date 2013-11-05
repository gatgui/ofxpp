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

PyTypeObject PyOFXInt3ParameterDescriptorType;
PyTypeObject PyOFXInt3ParameterType;

// ---

int PyOFXInt3ParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::Int3ParameterDescriptor();
  return 0;
}

PyObject* PyOFXInt3ParameterDescriptor_GetDefault(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int3ParameterDescriptor *desc = (ofx::Int3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int x, y, z;
  
  CATCH({desc->defaultValue(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("iii", x, y, z);
}

int PyOFXInt3ParameterDescriptor_SetDefault(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyTuple_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple");
    return -1;
  }
  
  if (PyTuple_Size(val) != 3)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 3 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  int z = PyInt_AsLong(PyTuple_GetItem(val, 2));
  
  ofx::Int3ParameterDescriptor *desc = (ofx::Int3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->defaultValue(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXInt3ParameterDescriptor_GetMin(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int3ParameterDescriptor *desc = (ofx::Int3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int x, y, z;
  
  CATCH({desc->min(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("iii", x, y, z);
}

int PyOFXInt3ParameterDescriptor_SetMin(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyTuple_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple");
    return -1;
  }
  
  if (PyTuple_Size(val) != 3)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 3 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  int z = PyInt_AsLong(PyTuple_GetItem(val, 2));
  
  ofx::Int3ParameterDescriptor *desc = (ofx::Int3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->min(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXInt3ParameterDescriptor_GetMax(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int3ParameterDescriptor *desc = (ofx::Int3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int x, y, z;
  
  CATCH({desc->max(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("iii", x, y, z);
}

int PyOFXInt3ParameterDescriptor_SetMax(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyTuple_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple");
    return -1;
  }
  
  if (PyTuple_Size(val) != 3)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 3 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  int z = PyInt_AsLong(PyTuple_GetItem(val, 2));
  
  ofx::Int3ParameterDescriptor *desc = (ofx::Int3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->max(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXInt3ParameterDescriptor_GetDisplayMin(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int3ParameterDescriptor *desc = (ofx::Int3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int x, y, z;
  
  CATCH({desc->displayMin(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("iii", x, y, z);
}

int PyOFXInt3ParameterDescriptor_SetDisplayMin(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyTuple_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple");
    return -1;
  }
  
  if (PyTuple_Size(val) != 3)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 3 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  int z = PyInt_AsLong(PyTuple_GetItem(val, 2));
  
  ofx::Int3ParameterDescriptor *desc = (ofx::Int3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->displayMin(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXInt3ParameterDescriptor_GetDisplayMax(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int3ParameterDescriptor *desc = (ofx::Int3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int x, y, z;
  
  CATCH({desc->displayMax(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("iii", x, y, z);
}

int PyOFXInt3ParameterDescriptor_SetDisplayMax(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyTuple_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple");
    return -1;
  }
  
  if (PyTuple_Size(val) != 3)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 3 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  int z = PyInt_AsLong(PyTuple_GetItem(val, 2));
  
  ofx::Int3ParameterDescriptor *desc = (ofx::Int3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->displayMax(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXInt3ParameterDescriptor_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXInt3ParameterDescriptor_GetDefault, PyOFXInt3ParameterDescriptor_SetDefault, NULL, NULL},
  {(char*)"min", PyOFXInt3ParameterDescriptor_GetMin, PyOFXInt3ParameterDescriptor_SetMin, NULL, NULL},
  {(char*)"max", PyOFXInt3ParameterDescriptor_GetMax, PyOFXInt3ParameterDescriptor_SetMax, NULL, NULL},
  {(char*)"displayMin", PyOFXInt3ParameterDescriptor_GetDisplayMin, PyOFXInt3ParameterDescriptor_SetDisplayMin, NULL, NULL},
  {(char*)"displayMax", PyOFXInt3ParameterDescriptor_GetDisplayMax, PyOFXInt3ParameterDescriptor_SetDisplayMax, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};


PyObject* PyOFXInt3ParameterDescriptor_DimensionLabel(PyObject *self, PyObject *args)
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
  
  ofx::Int3ParameterDescriptor *desc = (ofx::Int3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  if (pval == 0)
  {
    std::string rv;
  
    CATCH({rv = desc->dimensionLabel(idx);}, failed);
  
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
      PyErr_SetString(PyExc_TypeError, "Expected a string");
      return NULL;
    }
    
    std::string label = PyString_AsString(pval);
    
    CATCH({desc->dimensionLabel(idx, label);}, failed);
  
    if (failed)
    {
      return NULL;
    }
    
    Py_RETURN_NONE;
  }
}

static PyMethodDef PyOFXInt3ParameterDescriptor_Methods[] =
{
  {"dimensionLabel", PyOFXInt3ParameterDescriptor_DimensionLabel, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

// ---

int PyOFXInt3Parameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::Int3Parameter();
  return 0;
}

PyObject* PyOFXInt3Parameter_GetDefault(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y, z;
  
  CATCH({param->defaultValue(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("iii", x, y, z);
}

PyObject* PyOFXInt3Parameter_GetMin(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y, z;
  
  CATCH({param->min(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("iii", x, y, z);
}

int PyOFXInt3Parameter_SetMin(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyTuple_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple");
    return -1;
  }
  
  if (PyTuple_Size(val) != 3)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 3 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  int z = PyInt_AsLong(PyTuple_GetItem(val, 2));
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->min(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXInt3Parameter_GetMax(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y, z;
  
  CATCH({param->max(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("iii", x, y, z);
}

int PyOFXInt3Parameter_SetMax(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyTuple_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple");
    return -1;
  }
  
  if (PyTuple_Size(val) != 3)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 3 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  int z = PyInt_AsLong(PyTuple_GetItem(val, 3));
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->max(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXInt3Parameter_GetDisplayMin(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y, z;
  
  CATCH({param->displayMin(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("iii", x, y, z);
}

int PyOFXInt3Parameter_SetDisplayMin(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyTuple_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple");
    return -1;
  }
  
  if (PyTuple_Size(val) != 3)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 3 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  int z = PyInt_AsLong(PyTuple_GetItem(val, 2));
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->displayMin(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXInt3Parameter_GetDisplayMax(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y, z;
  
  CATCH({param->displayMax(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("iii", x, y, z);
}

int PyOFXInt3Parameter_SetDisplayMax(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyTuple_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple");
    return -1;
  }
  
  if (PyTuple_Size(val) != 3)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 3 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  int z = PyInt_AsLong(PyTuple_GetItem(val, 2));
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->displayMax(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXInt3Parameter_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXInt3Parameter_GetDefault, NULL, NULL, NULL},
  {(char*)"min", PyOFXInt3Parameter_GetMin, PyOFXInt3Parameter_SetMin, NULL, NULL},
  {(char*)"max", PyOFXInt3Parameter_GetMax, PyOFXInt3Parameter_SetMax, NULL, NULL},
  {(char*)"displayMin", PyOFXInt3Parameter_GetDisplayMin, PyOFXInt3Parameter_SetDisplayMin, NULL, NULL},
  {(char*)"displayMax", PyOFXInt3Parameter_GetDisplayMax, PyOFXInt3Parameter_SetDisplayMax, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXInt3Parameter_DimensionLabel(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx;
  
  if (!PyArg_ParseTuple(args, "i", &idx))
  {
    return NULL;
  }
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = param->dimensionLabel(idx);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXInt3Parameter_GetValue(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y, z;
  
  CATCH({param->getValue(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("iii", x, y, z);
}

PyObject* PyOFXInt3Parameter_GetValueAtTime(PyObject *self, PyObject *args)
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
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y, z;
  
  CATCH({param->getValueAtTime(t, &x, &y, &z);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("iii", x, y, z);
}

PyObject* PyOFXInt3Parameter_GetDerivative(PyObject *self, PyObject *args)
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
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y, z;
  
  CATCH({param->getDerivative(t, &x, &y, &z);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("iii", x, y, z);
}

PyObject* PyOFXInt3Parameter_GetIntegral(PyObject *self, PyObject *args)
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
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y, z;
  
  CATCH({param->getIntegral(t0, t1, &x, &y, &z);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("iii", x, y, z);
}

PyObject* PyOFXInt3Parameter_SetValue(PyObject *self, PyObject *args)
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
  
  if (!PyTuple_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple");
    return NULL;
  }
  
  if (PyTuple_Size(val) != 3)
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple of 3 values");
    return NULL;
  }
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  int z = PyInt_AsLong(PyTuple_GetItem(val, 2));
  
  CATCH({param->setValue(x, y, z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXInt3Parameter_SetValueAtTime(PyObject *self, PyObject *args)
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
  
  if (!PyTuple_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple");
    return NULL;
  }
  
  if (PyTuple_Size(val) != 3)
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple of 3 values");
    return NULL;
  }
  
  ofx::Int3Parameter *param = (ofx::Int3Parameter*) pparam->param;
  
  bool failed = false;
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  int z = PyInt_AsLong(PyTuple_GetItem(val, 2));
  
  CATCH({param->setValueAtTime(t, x, y, z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

static PyMethodDef PyOFXInt3Parameter_Methods[] =
{
  {"dimensionLabel", PyOFXInt3Parameter_DimensionLabel, METH_VARARGS, NULL},
  {"setValue", PyOFXInt3Parameter_SetValue, METH_VARARGS, NULL},
  {"getValue", PyOFXInt3Parameter_GetValue, METH_VARARGS, NULL},
  {"setValueAtTime", PyOFXInt3Parameter_SetValueAtTime, METH_VARARGS, NULL},
  {"getValueAtTime", PyOFXInt3Parameter_GetValueAtTime, METH_VARARGS, NULL},
  {"getDerivative", PyOFXInt3Parameter_GetDerivative, METH_VARARGS, NULL},
  {"getIntegral", PyOFXInt3Parameter_GetIntegral, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

// ---

bool PyOFX_InitParameter_Int3(PyObject *mod)
{
  INIT_TYPE(PyOFXInt3ParameterDescriptorType, "ofx.Int3ParameterDescriptor", PyOFXInt3ParameterDescriptor);
  PyOFXInt3ParameterDescriptorType.tp_base = &PyOFXValueParameterDescriptorType;
  PyOFXInt3ParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXInt3ParameterDescriptorType.tp_init = PyOFXInt3ParameterDescriptor_Init;
  PyOFXInt3ParameterDescriptorType.tp_getset = PyOFXInt3ParameterDescriptor_GetSeters;
  PyOFXInt3ParameterDescriptorType.tp_methods = PyOFXInt3ParameterDescriptor_Methods;
  if (PyType_Ready(&PyOFXInt3ParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXInt3ParameterType, "ofx.Int3Parameter", PyOFXInt3Parameter);
  PyOFXInt3ParameterType.tp_base = &PyOFXValueParameterType;
  PyOFXInt3ParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXInt3ParameterType.tp_init = PyOFXInt3Parameter_Init;
  PyOFXInt3ParameterType.tp_getset = PyOFXInt3Parameter_GetSeters;
  PyOFXInt3ParameterType.tp_methods = PyOFXInt3Parameter_Methods;
  if (PyType_Ready(&PyOFXInt3ParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXInt3ParameterDescriptorType);
  PyModule_AddObject(mod, "Int3ParameterDescriptor", (PyObject*)&PyOFXInt3ParameterDescriptorType);
  
  Py_INCREF(&PyOFXInt3ParameterType);
  PyModule_AddObject(mod, "Int3Parameter", (PyObject*)&PyOFXInt3ParameterType);
  
  return true;
}
