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

PyTypeObject PyOFXDouble3ParameterDescriptorType;
PyTypeObject PyOFXDouble3ParameterType;

// ---

int PyOFXDouble3ParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::Double3ParameterDescriptor();
  return 0;
}

PyObject* PyOFXDouble3ParameterDescriptor_GetDefault(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double x, y, z;
  
  CATCH({desc->defaultValue(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ddd", x, y, z);
}

int PyOFXDouble3ParameterDescriptor_SetDefault(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  double z = PyFloat_AsDouble(PyTuple_GetItem(val, 2));
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->defaultValue(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble3ParameterDescriptor_GetMin(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double x, y, z;
  
  CATCH({desc->min(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ddd", x, y, z);
}

int PyOFXDouble3ParameterDescriptor_SetMin(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  double z = PyFloat_AsDouble(PyTuple_GetItem(val, 2));
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->min(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble3ParameterDescriptor_GetMax(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double x, y, z;
  
  CATCH({desc->max(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ddd", x, y, z);
}

int PyOFXDouble3ParameterDescriptor_SetMax(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  double z = PyFloat_AsDouble(PyTuple_GetItem(val, 2));
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->max(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble3ParameterDescriptor_GetDisplayMin(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double x, y, z;
  
  CATCH({desc->displayMin(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ddd", x, y, z);
}

int PyOFXDouble3ParameterDescriptor_SetDisplayMin(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  double z = PyFloat_AsDouble(PyTuple_GetItem(val, 2));
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->displayMin(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble3ParameterDescriptor_GetDisplayMax(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double x, y, z;
  
  CATCH({desc->displayMax(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ddd", x, y, z);
}

int PyOFXDouble3ParameterDescriptor_SetDisplayMax(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  double z = PyFloat_AsDouble(PyTuple_GetItem(val, 2));
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->displayMax(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble3ParameterDescriptor_GetIncrement(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double rv = 0.0;
  
  CATCH({rv = desc->increment();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXDouble3ParameterDescriptor_SetIncrement(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  double i = PyFloat_AsDouble(val);
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->increment(i);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble3ParameterDescriptor_GetDigits(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = desc->digits();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXDouble3ParameterDescriptor_SetDigits(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int d = PyInt_AsLong(val);
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->digits(d);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble3ParameterDescriptor_GetDoubleType(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(desc->doubleType());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXDouble3ParameterDescriptor_SetDoubleType(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int d = PyInt_AsLong(val);
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->doubleType(ofx::DoubleParamType(d));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXDouble3ParameterDescriptor_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXDouble3ParameterDescriptor_GetDefault, PyOFXDouble3ParameterDescriptor_SetDefault, NULL, NULL},
  {(char*)"min", PyOFXDouble3ParameterDescriptor_GetMin, PyOFXDouble3ParameterDescriptor_SetMin, NULL, NULL},
  {(char*)"max", PyOFXDouble3ParameterDescriptor_GetMax, PyOFXDouble3ParameterDescriptor_SetMax, NULL, NULL},
  {(char*)"displayMin", PyOFXDouble3ParameterDescriptor_GetDisplayMin, PyOFXDouble3ParameterDescriptor_SetDisplayMin, NULL, NULL},
  {(char*)"displayMax", PyOFXDouble3ParameterDescriptor_GetDisplayMax, PyOFXDouble3ParameterDescriptor_SetDisplayMax, NULL, NULL},
  {(char*)"increment", PyOFXDouble3ParameterDescriptor_GetIncrement, PyOFXDouble3ParameterDescriptor_SetIncrement, NULL, NULL},
  {(char*)"digits", PyOFXDouble3ParameterDescriptor_GetDigits, PyOFXDouble3ParameterDescriptor_SetDigits, NULL, NULL},
  {(char*)"doubleType", PyOFXDouble3ParameterDescriptor_GetDoubleType, PyOFXDouble3ParameterDescriptor_SetDoubleType, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};


PyObject* PyOFXDouble3ParameterDescriptor_DimensionLabel(PyObject *self, PyObject *args)
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
  
  ofx::Double3ParameterDescriptor *desc = (ofx::Double3ParameterDescriptor*) pdesc->desc;
  
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

static PyMethodDef PyOFXDouble3ParameterDescriptor_Methods[] =
{
  {"dimensionLabel", PyOFXDouble3ParameterDescriptor_DimensionLabel, METH_VARARGS, NULL},
  {NULL, NULL, NULL, NULL}
};

// ---

int PyOFXDouble3Parameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::Double3Parameter();
  return 0;
}

PyObject* PyOFXDouble3Parameter_GetDefault(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y, z;
  
  CATCH({param->defaultValue(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ddd", x, y, z);
}

PyObject* PyOFXDouble3Parameter_GetMin(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y, z;
  
  CATCH({param->min(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ddd", x, y, z);
}

int PyOFXDouble3Parameter_SetMin(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  double z = PyFloat_AsDouble(PyTuple_GetItem(val, 2));
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->min(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble3Parameter_GetMax(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y, z;
  
  CATCH({param->max(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ddd", x, y, z);
}

int PyOFXDouble3Parameter_SetMax(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  double z = PyFloat_AsDouble(PyTuple_GetItem(val, 3));
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->max(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble3Parameter_GetDisplayMin(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y, z;
  
  CATCH({param->displayMin(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ddd", x, y, z);
}

int PyOFXDouble3Parameter_SetDisplayMin(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  double z = PyFloat_AsDouble(PyTuple_GetItem(val, 2));
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->displayMin(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble3Parameter_GetDisplayMax(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y, z;
  
  CATCH({param->displayMax(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ddd", x, y, z);
}

int PyOFXDouble3Parameter_SetDisplayMax(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  double z = PyFloat_AsDouble(PyTuple_GetItem(val, 2));
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->displayMax(x, y, z);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble3Parameter_GetIncrement(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  double rv = 0.0;
  
  CATCH({rv = param->increment();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXDouble3Parameter_SetIncrement(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  double i = PyFloat_AsDouble(val);
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->increment(i);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble3Parameter_GetDigits(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->digits();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXDouble3Parameter_SetDigits(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int d = PyInt_AsLong(val);
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->digits(d);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble3Parameter_GetDoubleType(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(param->doubleType());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

static PyGetSetDef PyOFXDouble3Parameter_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXDouble3Parameter_GetDefault, NULL, NULL, NULL},
  {(char*)"min", PyOFXDouble3Parameter_GetMin, PyOFXDouble3Parameter_SetMin, NULL, NULL},
  {(char*)"max", PyOFXDouble3Parameter_GetMax, PyOFXDouble3Parameter_SetMax, NULL, NULL},
  {(char*)"displayMin", PyOFXDouble3Parameter_GetDisplayMin, PyOFXDouble3Parameter_SetDisplayMin, NULL, NULL},
  {(char*)"displayMax", PyOFXDouble3Parameter_GetDisplayMax, PyOFXDouble3Parameter_SetDisplayMax, NULL, NULL},
  {(char*)"increment", PyOFXDouble3Parameter_GetIncrement, PyOFXDouble3Parameter_SetIncrement, NULL, NULL},
  {(char*)"digits", PyOFXDouble3Parameter_GetDigits, PyOFXDouble3Parameter_SetDigits, NULL, NULL},
  {(char*)"doubleType", PyOFXDouble3Parameter_GetDoubleType, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXDouble3Parameter_DimensionLabel(PyObject *self, PyObject *args)
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
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = param->dimensionLabel(idx);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXDouble3Parameter_GetValue(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y, z;
  
  CATCH({param->getValue(&x, &y, &z);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("ddd", x, y, z);
}

PyObject* PyOFXDouble3Parameter_GetValueAtTime(PyObject *self, PyObject *args)
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
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y, z;
  
  CATCH({param->getValueAtTime(t, &x, &y, &z);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("ddd", x, y, z);
}

PyObject* PyOFXDouble3Parameter_GetDerivative(PyObject *self, PyObject *args)
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
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y, z;
  
  CATCH({param->getDerivative(t, &x, &y, &z);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("ddd", x, y, z);
}

PyObject* PyOFXDouble3Parameter_GetIntegral(PyObject *self, PyObject *args)
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
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y, z;
  
  CATCH({param->getIntegral(t0, t1, &x, &y, &z);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("ddd", x, y, z);
}

PyObject* PyOFXDouble3Parameter_SetValue(PyObject *self, PyObject *args)
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
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  double z = PyFloat_AsDouble(PyTuple_GetItem(val, 2));
  
  CATCH({param->setValue(x, y, z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXDouble3Parameter_SetValueAtTime(PyObject *self, PyObject *args)
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
  
  ofx::Double3Parameter *param = (ofx::Double3Parameter*) pparam->param;
  
  bool failed = false;
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  double z = PyFloat_AsDouble(PyTuple_GetItem(val, 2));
  
  CATCH({param->setValueAtTime(t, x, y, z);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

static PyMethodDef PyOFXDouble3Parameter_Methods[] =
{
  {"dimensionLabel", PyOFXDouble3Parameter_DimensionLabel, METH_VARARGS, NULL},
  {"setValue", PyOFXDouble3Parameter_SetValue, METH_VARARGS, NULL},
  {"getValue", PyOFXDouble3Parameter_GetValue, METH_VARARGS, NULL},
  {"setValueAtTime", PyOFXDouble3Parameter_SetValueAtTime, METH_VARARGS, NULL},
  {"getValueAtTime", PyOFXDouble3Parameter_GetValueAtTime, METH_VARARGS, NULL},
  {"getDerivative", PyOFXDouble3Parameter_GetDerivative, METH_VARARGS, NULL},
  {"getIntegral", PyOFXDouble3Parameter_GetIntegral, METH_VARARGS, NULL},
  {NULL, NULL, NULL, NULL}
};

// ---

bool PyOFX_InitParameter_Double3(PyObject *mod)
{
  INIT_TYPE(PyOFXDouble3ParameterDescriptorType, "ofx.Double3ParameterDescriptor", PyOFXDouble3ParameterDescriptor);
  PyOFXDouble3ParameterDescriptorType.tp_base = &PyOFXValueParameterDescriptorType;
  PyOFXDouble3ParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXDouble3ParameterDescriptorType.tp_init = PyOFXDouble3ParameterDescriptor_Init;
  PyOFXDouble3ParameterDescriptorType.tp_getset = PyOFXDouble3ParameterDescriptor_GetSeters;
  PyOFXDouble3ParameterDescriptorType.tp_methods = PyOFXDouble3ParameterDescriptor_Methods;
  if (PyType_Ready(&PyOFXDouble3ParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXDouble3ParameterType, "ofx.Double3Parameter", PyOFXDouble3Parameter);
  PyOFXDouble3ParameterType.tp_base = &PyOFXValueParameterType;
  PyOFXDouble3ParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXDouble3ParameterType.tp_init = PyOFXDouble3Parameter_Init;
  PyOFXDouble3ParameterType.tp_getset = PyOFXDouble3Parameter_GetSeters;
  PyOFXDouble3ParameterType.tp_methods = PyOFXDouble3Parameter_Methods;
  if (PyType_Ready(&PyOFXDouble3ParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXDouble3ParameterDescriptorType);
  PyModule_AddObject(mod, "Double3ParameterDescriptor", (PyObject*)&PyOFXDouble3ParameterDescriptorType);
  
  Py_INCREF(&PyOFXDouble3ParameterType);
  PyModule_AddObject(mod, "Double3Parameter", (PyObject*)&PyOFXDouble3ParameterType);
  
  return true;
}
