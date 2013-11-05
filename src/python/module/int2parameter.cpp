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

PyTypeObject PyOFXInt2ParameterDescriptorType;
PyTypeObject PyOFXInt2ParameterType;

// ---

int PyOFXInt2ParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::Int2ParameterDescriptor();
  return 0;
}

PyObject* PyOFXInt2ParameterDescriptor_GetDefault(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int2ParameterDescriptor *desc = (ofx::Int2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int x, y;
  
  CATCH({desc->defaultValue(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ii", x, y);
}

int PyOFXInt2ParameterDescriptor_SetDefault(PyObject *self, PyObject *val, void*)
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
  
  if (PyTuple_Size(val) != 2)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 2 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  
  ofx::Int2ParameterDescriptor *desc = (ofx::Int2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->defaultValue(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXInt2ParameterDescriptor_GetMin(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int2ParameterDescriptor *desc = (ofx::Int2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int x, y;
  
  CATCH({desc->min(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ii", x, y);
}

int PyOFXInt2ParameterDescriptor_SetMin(PyObject *self, PyObject *val, void*)
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
  
  if (PyTuple_Size(val) != 2)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 2 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  
  ofx::Int2ParameterDescriptor *desc = (ofx::Int2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->min(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXInt2ParameterDescriptor_GetMax(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int2ParameterDescriptor *desc = (ofx::Int2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int x, y;
  
  CATCH({desc->max(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ii", x, y);
}

int PyOFXInt2ParameterDescriptor_SetMax(PyObject *self, PyObject *val, void*)
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
  
  if (PyTuple_Size(val) != 2)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 2 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  
  ofx::Int2ParameterDescriptor *desc = (ofx::Int2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->max(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXInt2ParameterDescriptor_GetDisplayMin(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int2ParameterDescriptor *desc = (ofx::Int2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int x, y;
  
  CATCH({desc->displayMin(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ii", x, y);
}

int PyOFXInt2ParameterDescriptor_SetDisplayMin(PyObject *self, PyObject *val, void*)
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
  
  if (PyTuple_Size(val) != 2)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 2 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  
  ofx::Int2ParameterDescriptor *desc = (ofx::Int2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->displayMin(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXInt2ParameterDescriptor_GetDisplayMax(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int2ParameterDescriptor *desc = (ofx::Int2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int x, y;
  
  CATCH({desc->displayMax(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ii", x, y);
}

int PyOFXInt2ParameterDescriptor_SetDisplayMax(PyObject *self, PyObject *val, void*)
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
  
  if (PyTuple_Size(val) != 2)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 2 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  
  ofx::Int2ParameterDescriptor *desc = (ofx::Int2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->displayMax(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXInt2ParameterDescriptor_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXInt2ParameterDescriptor_GetDefault, PyOFXInt2ParameterDescriptor_SetDefault, NULL, NULL},
  {(char*)"min", PyOFXInt2ParameterDescriptor_GetMin, PyOFXInt2ParameterDescriptor_SetMin, NULL, NULL},
  {(char*)"max", PyOFXInt2ParameterDescriptor_GetMax, PyOFXInt2ParameterDescriptor_SetMax, NULL, NULL},
  {(char*)"displayMin", PyOFXInt2ParameterDescriptor_GetDisplayMin, PyOFXInt2ParameterDescriptor_SetDisplayMin, NULL, NULL},
  {(char*)"displayMax", PyOFXInt2ParameterDescriptor_GetDisplayMax, PyOFXInt2ParameterDescriptor_SetDisplayMax, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};


PyObject* PyOFXInt2ParameterDescriptor_DimensionLabel(PyObject *self, PyObject *args)
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
  
  ofx::Int2ParameterDescriptor *desc = (ofx::Int2ParameterDescriptor*) pdesc->desc;
  
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

static PyMethodDef PyOFXInt2ParameterDescriptor_Methods[] =
{
  {"dimensionLabel", PyOFXInt2ParameterDescriptor_DimensionLabel, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

// ---

int PyOFXInt2Parameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::Int2Parameter();
  return 0;
}

PyObject* PyOFXInt2Parameter_GetDefault(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y;
  
  CATCH({param->defaultValue(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ii", x, y);
}

PyObject* PyOFXInt2Parameter_GetMin(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y;
  
  CATCH({param->min(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ii", x, y);
}

int PyOFXInt2Parameter_SetMin(PyObject *self, PyObject *val, void*)
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
  
  if (PyTuple_Size(val) != 2)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 2 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->min(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXInt2Parameter_GetMax(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y;
  
  CATCH({param->max(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ii", x, y);
}

int PyOFXInt2Parameter_SetMax(PyObject *self, PyObject *val, void*)
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
  
  if (PyTuple_Size(val) != 2)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 2 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->max(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXInt2Parameter_GetDisplayMin(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y;
  
  CATCH({param->displayMin(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ii", x, y);
}

int PyOFXInt2Parameter_SetDisplayMin(PyObject *self, PyObject *val, void*)
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
  
  if (PyTuple_Size(val) != 2)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 2 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->displayMin(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXInt2Parameter_GetDisplayMax(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y;
  
  CATCH({param->displayMax(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ii", x, y);
}

int PyOFXInt2Parameter_SetDisplayMax(PyObject *self, PyObject *val, void*)
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
  
  if (PyTuple_Size(val) != 2)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 2 values");
    return -1;
  }
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->displayMax(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXInt2Parameter_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXInt2Parameter_GetDefault, NULL, NULL, NULL},
  {(char*)"min", PyOFXInt2Parameter_GetMin, PyOFXInt2Parameter_SetMin, NULL, NULL},
  {(char*)"max", PyOFXInt2Parameter_GetMax, PyOFXInt2Parameter_SetMax, NULL, NULL},
  {(char*)"displayMin", PyOFXInt2Parameter_GetDisplayMin, PyOFXInt2Parameter_SetDisplayMin, NULL, NULL},
  {(char*)"displayMax", PyOFXInt2Parameter_GetDisplayMax, PyOFXInt2Parameter_SetDisplayMax, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXInt2Parameter_DimensionLabel(PyObject *self, PyObject *args)
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
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = param->dimensionLabel(idx);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXInt2Parameter_GetValue(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y;
  
  CATCH({param->getValue(&x, &y);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("ii", x, y);
}

PyObject* PyOFXInt2Parameter_GetValueAtTime(PyObject *self, PyObject *args)
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
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y;
  
  CATCH({param->getValueAtTime(t, &x, &y);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("ii", x, y);
}

PyObject* PyOFXInt2Parameter_GetDerivative(PyObject *self, PyObject *args)
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
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y;
  
  CATCH({param->getDerivative(t, &x, &y);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("ii", x, y);
}

PyObject* PyOFXInt2Parameter_GetIntegral(PyObject *self, PyObject *args)
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
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  int x, y;
  
  CATCH({param->getIntegral(t0, t1, &x, &y);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("ii", x, y);
}

PyObject* PyOFXInt2Parameter_SetValue(PyObject *self, PyObject *args)
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
  
  if (PyTuple_Size(val) != 2)
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple of 2 values");
    return NULL;
  }
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  
  CATCH({param->setValue(x, y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXInt2Parameter_SetValueAtTime(PyObject *self, PyObject *args)
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
  
  if (PyTuple_Size(val) != 2)
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple of 2 values");
    return NULL;
  }
  
  ofx::Int2Parameter *param = (ofx::Int2Parameter*) pparam->param;
  
  bool failed = false;
  
  int x = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int y = PyInt_AsLong(PyTuple_GetItem(val, 1));
  
  CATCH({param->setValueAtTime(t, x, y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

static PyMethodDef PyOFXInt2Parameter_Methods[] =
{
  {"dimensionLabel", PyOFXInt2Parameter_DimensionLabel, METH_VARARGS, NULL},
  {"setValue", PyOFXInt2Parameter_SetValue, METH_VARARGS, NULL},
  {"getValue", PyOFXInt2Parameter_GetValue, METH_VARARGS, NULL},
  {"setValueAtTime", PyOFXInt2Parameter_SetValueAtTime, METH_VARARGS, NULL},
  {"getValueAtTime", PyOFXInt2Parameter_GetValueAtTime, METH_VARARGS, NULL},
  {"getDerivative", PyOFXInt2Parameter_GetDerivative, METH_VARARGS, NULL},
  {"getIntegral", PyOFXInt2Parameter_GetIntegral, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

// ---

bool PyOFX_InitParameter_Int2(PyObject *mod)
{
  INIT_TYPE(PyOFXInt2ParameterDescriptorType, "ofx.Int2ParameterDescriptor", PyOFXInt2ParameterDescriptor);
  PyOFXInt2ParameterDescriptorType.tp_base = &PyOFXValueParameterDescriptorType;
  PyOFXInt2ParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXInt2ParameterDescriptorType.tp_init = PyOFXInt2ParameterDescriptor_Init;
  PyOFXInt2ParameterDescriptorType.tp_getset = PyOFXInt2ParameterDescriptor_GetSeters;
  PyOFXInt2ParameterDescriptorType.tp_methods = PyOFXInt2ParameterDescriptor_Methods;
  if (PyType_Ready(&PyOFXInt2ParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXInt2ParameterType, "ofx.Int2Parameter", PyOFXInt2Parameter);
  PyOFXInt2ParameterType.tp_base = &PyOFXValueParameterType;
  PyOFXInt2ParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXInt2ParameterType.tp_init = PyOFXInt2Parameter_Init;
  PyOFXInt2ParameterType.tp_getset = PyOFXInt2Parameter_GetSeters;
  PyOFXInt2ParameterType.tp_methods = PyOFXInt2Parameter_Methods;
  if (PyType_Ready(&PyOFXInt2ParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXInt2ParameterDescriptorType);
  PyModule_AddObject(mod, "Int2ParameterDescriptor", (PyObject*)&PyOFXInt2ParameterDescriptorType);
  
  Py_INCREF(&PyOFXInt2ParameterType);
  PyModule_AddObject(mod, "Int2Parameter", (PyObject*)&PyOFXInt2ParameterType);
  
  return true;
}
