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

PyTypeObject PyOFXDouble2ParameterDescriptorType;
PyTypeObject PyOFXDouble2ParameterType;

// ---

int PyOFXDouble2ParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::Double2ParameterDescriptor();
  return 0;
}

PyObject* PyOFXDouble2ParameterDescriptor_GetDefault(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double x, y;
  
  CATCH({desc->defaultValue(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", x, y);
}

int PyOFXDouble2ParameterDescriptor_SetDefault(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->defaultValue(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble2ParameterDescriptor_GetMin(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double x, y;
  
  CATCH({desc->min(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", x, y);
}

int PyOFXDouble2ParameterDescriptor_SetMin(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->min(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble2ParameterDescriptor_GetMax(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double x, y;
  
  CATCH({desc->max(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", x, y);
}

int PyOFXDouble2ParameterDescriptor_SetMax(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->max(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble2ParameterDescriptor_GetDisplayMin(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double x, y;
  
  CATCH({desc->displayMin(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", x, y);
}

int PyOFXDouble2ParameterDescriptor_SetDisplayMin(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->displayMin(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble2ParameterDescriptor_GetDisplayMax(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double x, y;
  
  CATCH({desc->displayMax(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", x, y);
}

int PyOFXDouble2ParameterDescriptor_SetDisplayMax(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->displayMax(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble2ParameterDescriptor_GetIncrement(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double rv = 0.0;
  
  CATCH({rv = desc->increment();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXDouble2ParameterDescriptor_SetIncrement(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  double i = PyFloat_AsDouble(val);
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->increment(i);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble2ParameterDescriptor_GetDigits(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = desc->digits();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXDouble2ParameterDescriptor_SetDigits(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int d = PyInt_AsLong(val);
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->digits(d);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble2ParameterDescriptor_GetDoubleType(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(desc->doubleType());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXDouble2ParameterDescriptor_SetDoubleType(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int d = PyInt_AsLong(val);
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->doubleType(ofx::DoubleParamType(d));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

#ifdef OFX_API_1_2

PyObject* PyOFXDouble2ParameterDescriptor_GetDefaultCoordinateSystem(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(desc->defaultCoordinateSystem());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXDouble2ParameterDescriptor_SetDefaultCoordinateSystem(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int d = PyInt_AsLong(val);
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->defaultCoordinateSystem(ofx::Coordinates(d));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

#endif

static PyGetSetDef PyOFXDouble2ParameterDescriptor_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXDouble2ParameterDescriptor_GetDefault, PyOFXDouble2ParameterDescriptor_SetDefault, NULL, NULL},
  {(char*)"min", PyOFXDouble2ParameterDescriptor_GetMin, PyOFXDouble2ParameterDescriptor_SetMin, NULL, NULL},
  {(char*)"max", PyOFXDouble2ParameterDescriptor_GetMax, PyOFXDouble2ParameterDescriptor_SetMax, NULL, NULL},
  {(char*)"displayMin", PyOFXDouble2ParameterDescriptor_GetDisplayMin, PyOFXDouble2ParameterDescriptor_SetDisplayMin, NULL, NULL},
  {(char*)"displayMax", PyOFXDouble2ParameterDescriptor_GetDisplayMax, PyOFXDouble2ParameterDescriptor_SetDisplayMax, NULL, NULL},
  {(char*)"increment", PyOFXDouble2ParameterDescriptor_GetIncrement, PyOFXDouble2ParameterDescriptor_SetIncrement, NULL, NULL},
  {(char*)"digits", PyOFXDouble2ParameterDescriptor_GetDigits, PyOFXDouble2ParameterDescriptor_SetDigits, NULL, NULL},
  {(char*)"doubleType", PyOFXDouble2ParameterDescriptor_GetDoubleType, PyOFXDouble2ParameterDescriptor_SetDoubleType, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"defaultCoordinateSystem", PyOFXDouble2ParameterDescriptor_GetDefaultCoordinateSystem, PyOFXDouble2ParameterDescriptor_SetDefaultCoordinateSystem, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};


PyObject* PyOFXDouble2ParameterDescriptor_DimensionLabel(PyObject *self, PyObject *args)
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
  
  ofx::Double2ParameterDescriptor *desc = (ofx::Double2ParameterDescriptor*) pdesc->desc;
  
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

static PyMethodDef PyOFXDouble2ParameterDescriptor_Methods[] =
{
  {"dimensionLabel", PyOFXDouble2ParameterDescriptor_DimensionLabel, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

// ---

int PyOFXDouble2Parameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::Double2Parameter();
  return 0;
}

PyObject* PyOFXDouble2Parameter_GetDefault(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y;
  
  CATCH({param->defaultValue(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", x, y);
}

PyObject* PyOFXDouble2Parameter_GetMin(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y;
  
  CATCH({param->min(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", x, y);
}

int PyOFXDouble2Parameter_SetMin(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->min(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble2Parameter_GetMax(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y;
  
  CATCH({param->max(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", x, y);
}

int PyOFXDouble2Parameter_SetMax(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->max(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble2Parameter_GetDisplayMin(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y;
  
  CATCH({param->displayMin(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", x, y);
}

int PyOFXDouble2Parameter_SetDisplayMin(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->displayMin(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble2Parameter_GetDisplayMax(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y;
  
  CATCH({param->displayMax(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", x, y);
}

int PyOFXDouble2Parameter_SetDisplayMax(PyObject *self, PyObject *val, void*)
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
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->displayMax(x, y);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble2Parameter_GetIncrement(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  double rv = 0.0;
  
  CATCH({rv = param->increment();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXDouble2Parameter_SetIncrement(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  double i = PyFloat_AsDouble(val);
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->increment(i);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble2Parameter_GetDigits(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->digits();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXDouble2Parameter_SetDigits(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int d = PyInt_AsLong(val);
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->digits(d);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDouble2Parameter_GetDoubleType(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(param->doubleType());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

#ifdef OFX_API_1_2

PyObject* PyOFXDouble2Parameter_GetDefaultCoordinateSystem(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(param->defaultCoordinateSystem());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

#endif

static PyGetSetDef PyOFXDouble2Parameter_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXDouble2Parameter_GetDefault, NULL, NULL, NULL},
  {(char*)"min", PyOFXDouble2Parameter_GetMin, PyOFXDouble2Parameter_SetMin, NULL, NULL},
  {(char*)"max", PyOFXDouble2Parameter_GetMax, PyOFXDouble2Parameter_SetMax, NULL, NULL},
  {(char*)"displayMin", PyOFXDouble2Parameter_GetDisplayMin, PyOFXDouble2Parameter_SetDisplayMin, NULL, NULL},
  {(char*)"displayMax", PyOFXDouble2Parameter_GetDisplayMax, PyOFXDouble2Parameter_SetDisplayMax, NULL, NULL},
  {(char*)"increment", PyOFXDouble2Parameter_GetIncrement, PyOFXDouble2Parameter_SetIncrement, NULL, NULL},
  {(char*)"digits", PyOFXDouble2Parameter_GetDigits, PyOFXDouble2Parameter_SetDigits, NULL, NULL},
  {(char*)"doubleType", PyOFXDouble2Parameter_GetDoubleType, NULL, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"defaultCoordinateSystem", PyOFXDouble2Parameter_GetDefaultCoordinateSystem, NULL, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXDouble2Parameter_DimensionLabel(PyObject *self, PyObject *args)
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
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = param->dimensionLabel(idx);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXDouble2Parameter_GetValue(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y;
  
  CATCH({param->getValue(&x, &y);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("dd", x, y);
}

PyObject* PyOFXDouble2Parameter_GetValueAtTime(PyObject *self, PyObject *args)
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
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y;
  
  CATCH({param->getValueAtTime(t, &x, &y);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("dd", x, y);
}

PyObject* PyOFXDouble2Parameter_GetDerivative(PyObject *self, PyObject *args)
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
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y;
  
  CATCH({param->getDerivative(t, &x, &y);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("dd", x, y);
}

PyObject* PyOFXDouble2Parameter_GetIntegral(PyObject *self, PyObject *args)
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
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  double x, y;
  
  CATCH({param->getIntegral(t0, t1, &x, &y);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return Py_BuildValue("dd", x, y);
}

PyObject* PyOFXDouble2Parameter_SetValue(PyObject *self, PyObject *args)
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
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  
  CATCH({param->setValue(x, y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXDouble2Parameter_SetValueAtTime(PyObject *self, PyObject *args)
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
  
  ofx::Double2Parameter *param = (ofx::Double2Parameter*) pparam->param;
  
  bool failed = false;
  
  double x = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double y = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  
  CATCH({param->setValueAtTime(t, x, y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

static PyMethodDef PyOFXDouble2Parameter_Methods[] =
{
  {"dimensionLabel", PyOFXDouble2Parameter_DimensionLabel, METH_VARARGS, NULL},
  {"setValue", PyOFXDouble2Parameter_SetValue, METH_VARARGS, NULL},
  {"getValue", PyOFXDouble2Parameter_GetValue, METH_VARARGS, NULL},
  {"setValueAtTime", PyOFXDouble2Parameter_SetValueAtTime, METH_VARARGS, NULL},
  {"getValueAtTime", PyOFXDouble2Parameter_GetValueAtTime, METH_VARARGS, NULL},
  {"getDerivative", PyOFXDouble2Parameter_GetDerivative, METH_VARARGS, NULL},
  {"getIntegral", PyOFXDouble2Parameter_GetIntegral, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

// ---

bool PyOFX_InitParameter_Double2(PyObject *mod)
{
  INIT_TYPE(PyOFXDouble2ParameterDescriptorType, "ofx.Double2ParameterDescriptor", PyOFXDouble2ParameterDescriptor);
  PyOFXDouble2ParameterDescriptorType.tp_base = &PyOFXValueParameterDescriptorType;
  PyOFXDouble2ParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXDouble2ParameterDescriptorType.tp_init = PyOFXDouble2ParameterDescriptor_Init;
  PyOFXDouble2ParameterDescriptorType.tp_getset = PyOFXDouble2ParameterDescriptor_GetSeters;
  PyOFXDouble2ParameterDescriptorType.tp_methods = PyOFXDouble2ParameterDescriptor_Methods;
  if (PyType_Ready(&PyOFXDouble2ParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXDouble2ParameterType, "ofx.Double2Parameter", PyOFXDouble2Parameter);
  PyOFXDouble2ParameterType.tp_base = &PyOFXValueParameterType;
  PyOFXDouble2ParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXDouble2ParameterType.tp_init = PyOFXDouble2Parameter_Init;
  PyOFXDouble2ParameterType.tp_getset = PyOFXDouble2Parameter_GetSeters;
  PyOFXDouble2ParameterType.tp_methods = PyOFXDouble2Parameter_Methods;
  if (PyType_Ready(&PyOFXDouble2ParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXDouble2ParameterDescriptorType);
  PyModule_AddObject(mod, "Double2ParameterDescriptor", (PyObject*)&PyOFXDouble2ParameterDescriptorType);
  
  Py_INCREF(&PyOFXDouble2ParameterType);
  PyModule_AddObject(mod, "Double2Parameter", (PyObject*)&PyOFXDouble2ParameterType);
  
  return true;
}
