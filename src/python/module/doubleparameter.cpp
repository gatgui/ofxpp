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

PyTypeObject PyOFXDoubleParameterDescriptorType;
PyTypeObject PyOFXDoubleParameterType;

// ---

int PyOFXDoubleParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::DoubleParameterDescriptor();
  return 0;
}

PyObject* PyOFXDoubleParameterDescriptor_GetDefault(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = desc->defaultValue();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXDoubleParameterDescriptor_SetDefault(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  double v = PyFloat_AsDouble(val);
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->defaultValue(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDoubleParameterDescriptor_GetMin(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = desc->min();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXDoubleParameterDescriptor_SetMin(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  double v = PyFloat_AsDouble(val);
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->min(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDoubleParameterDescriptor_GetMax(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = desc->max();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXDoubleParameterDescriptor_SetMax(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  double v = PyFloat_AsDouble(val);
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->max(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDoubleParameterDescriptor_GetDisplayMin(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = desc->displayMin();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXDoubleParameterDescriptor_SetDisplayMin(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  double v = PyFloat_AsDouble(val);
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->displayMin(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDoubleParameterDescriptor_GetDisplayMax(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = desc->displayMax();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXDoubleParameterDescriptor_SetDisplayMax(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  double v = PyFloat_AsDouble(val);
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->displayMax(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDoubleParameterDescriptor_GetIncrement(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = desc->increment();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXDoubleParameterDescriptor_SetIncrement(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  double i = PyFloat_AsDouble(val);
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->increment(i);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDoubleParameterDescriptor_GetDigits(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv;
  
  CATCH({rv = desc->digits();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXDoubleParameterDescriptor_SetDigits(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int d = PyInt_AsLong(val);
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->digits(d);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDoubleParameterDescriptor_GetDoubleType(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv;
  
  CATCH({rv = int(desc->doubleType());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXDoubleParameterDescriptor_SetDoubleType(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int d = PyInt_AsLong(val);
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->doubleType(ofx::DoubleParamType(d));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDoubleParameterDescriptor_GetShowTimeMarker(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  bool rv;
  
  CATCH({rv = desc->showTimeMarker();}, failed);
  
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

int PyOFXDoubleParameterDescriptor_SetShowTimeMarker(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->showTimeMarker(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

#ifdef OFX_API_1_2

PyObject* PyOFXDoubleParameterDescriptor_GetDefaultCoordinateSystem(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv;
  
  CATCH({rv = int(desc->defaultCoordinateSystem());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXDoubleParameterDescriptor_SetDefaultCoordinateSystem(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int d = PyInt_AsLong(val);
  
  ofx::DoubleParameterDescriptor *desc = (ofx::DoubleParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->defaultCoordinateSystem(ofx::Coordinates(d));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

#endif

static PyGetSetDef PyOFXDoubleParameterDescriptor_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXDoubleParameterDescriptor_GetDefault, PyOFXDoubleParameterDescriptor_SetDefault, NULL, NULL},
  {(char*)"min", PyOFXDoubleParameterDescriptor_GetMin, PyOFXDoubleParameterDescriptor_SetMin, NULL, NULL},
  {(char*)"max", PyOFXDoubleParameterDescriptor_GetMax, PyOFXDoubleParameterDescriptor_SetMax, NULL, NULL},
  {(char*)"displayMin", PyOFXDoubleParameterDescriptor_GetDisplayMin, PyOFXDoubleParameterDescriptor_SetDisplayMin, NULL, NULL},
  {(char*)"displayMax", PyOFXDoubleParameterDescriptor_GetDisplayMax, PyOFXDoubleParameterDescriptor_SetDisplayMax, NULL, NULL},
  {(char*)"increment", PyOFXDoubleParameterDescriptor_GetIncrement, PyOFXDoubleParameterDescriptor_SetIncrement, NULL, NULL},
  {(char*)"digits", PyOFXDoubleParameterDescriptor_GetDigits, PyOFXDoubleParameterDescriptor_SetDigits, NULL, NULL},
  {(char*)"doubleType", PyOFXDoubleParameterDescriptor_GetDoubleType, PyOFXDoubleParameterDescriptor_SetDoubleType, NULL, NULL},
  {(char*)"showTimeMarker", PyOFXDoubleParameterDescriptor_GetShowTimeMarker, PyOFXDoubleParameterDescriptor_SetShowTimeMarker, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"defaultCoordinateSystem", PyOFXDoubleParameterDescriptor_GetDefaultCoordinateSystem, PyOFXDoubleParameterDescriptor_SetDefaultCoordinateSystem, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXDoubleParameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::DoubleParameter();
  return 0;
}

PyObject* PyOFXDoubleParameter_GetDefault(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = param->defaultValue();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXDoubleParameter_GetMin(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = param->min();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXDoubleParameter_SetMin(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  double v = PyFloat_AsDouble(val);
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->min(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDoubleParameter_GetMax(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = param->max();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXDoubleParameter_SetMax(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  double v = PyFloat_AsDouble(val);
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->max(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDoubleParameter_GetDisplayMin(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = param->displayMin();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXDoubleParameter_SetDisplayMin(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  double v = PyFloat_AsDouble(val);
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->displayMin(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDoubleParameter_GetDisplayMax(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = param->displayMax();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXDoubleParameter_SetDisplayMax(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  double v = PyFloat_AsDouble(val);
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->displayMax(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDoubleParameter_GetIncrement(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = param->increment();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXDoubleParameter_SetIncrement(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  double i = PyFloat_AsDouble(val);
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->increment(i);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDoubleParameter_GetDigits(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  int rv;
  
  CATCH({rv = param->digits();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXDoubleParameter_SetDigits(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  int d = PyInt_AsLong(val);
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->digits(d);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXDoubleParameter_GetDoubleType(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  int rv;
  
  CATCH({rv = int(param->doubleType());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXDoubleParameter_GetShowTimeMarker(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  bool rv;
  
  CATCH({rv = param->showTimeMarker();}, failed);
  
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

int PyOFXDoubleParameter_SetShowTimeMarker(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->showTimeMarker(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

#ifdef OFX_API_1_2

PyObject* PyOFXDoubleParameter_GetDefaultCoordinateSystem(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  int rv;
  
  CATCH({rv = int(param->defaultCoordinateSystem());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

#endif

static PyGetSetDef PyOFXDoubleParameter_GetSeters[] =
{
  {(char*)"defaultValue", PyOFXDoubleParameter_GetDefault, NULL, NULL, NULL},
  {(char*)"min", PyOFXDoubleParameter_GetMin, PyOFXDoubleParameter_SetMin, NULL, NULL},
  {(char*)"max", PyOFXDoubleParameter_GetMax, PyOFXDoubleParameter_SetMax, NULL, NULL},
  {(char*)"displayMin", PyOFXDoubleParameter_GetDisplayMin, PyOFXDoubleParameter_SetDisplayMin, NULL, NULL},
  {(char*)"displayMax", PyOFXDoubleParameter_GetDisplayMax, PyOFXDoubleParameter_SetDisplayMax, NULL, NULL},
  {(char*)"increment", PyOFXDoubleParameter_GetIncrement, PyOFXDoubleParameter_SetIncrement, NULL, NULL},
  {(char*)"digits", PyOFXDoubleParameter_GetDigits, PyOFXDoubleParameter_SetDigits, NULL, NULL},
  {(char*)"doubleType", PyOFXDoubleParameter_GetDoubleType, NULL, NULL, NULL},
  {(char*)"showTimeMarker", PyOFXDoubleParameter_GetShowTimeMarker, PyOFXDoubleParameter_SetShowTimeMarker, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"defaultCoordinateSystem", PyOFXDoubleParameter_GetDefaultCoordinateSystem, NULL, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXDoubleParameter_GetValue(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = param->getValue();}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXDoubleParameter_GetValueAtTime(PyObject *self, PyObject *args)
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
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = param->getValueAtTime(t);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXDoubleParameter_GetDerivative(PyObject *self, PyObject *args)
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
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = param->getDerivative(t);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXDoubleParameter_GetIntegral(PyObject *self, PyObject *args)
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
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  double rv;
  
  CATCH({rv = param->getIntegral(t0, t1);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXDoubleParameter_SetValue(PyObject *self, PyObject *args)
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
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  double v = PyFloat_AsDouble(val);
  
  CATCH({param->setValue(v);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXDoubleParameter_SetValueAtTime(PyObject *self, PyObject *args)
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
  
  ofx::DoubleParameter *param = (ofx::DoubleParameter*) pparam->param;
  
  bool failed = false;
  
  double v = PyFloat_AsDouble(val);
  
  CATCH({param->setValueAtTime(t, v);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

static PyMethodDef PyOFXDoubleParameter_Methods[] =
{
  {"setValue", PyOFXDoubleParameter_SetValue, METH_VARARGS, NULL},
  {"getValue", PyOFXDoubleParameter_GetValue, METH_VARARGS, NULL},
  {"setValueAtTime", PyOFXDoubleParameter_SetValueAtTime, METH_VARARGS, NULL},
  {"getValueAtTime", PyOFXDoubleParameter_GetValueAtTime, METH_VARARGS, NULL},
  {"getDerivative", PyOFXDoubleParameter_GetDerivative, METH_VARARGS, NULL},
  {"getIntegral", PyOFXDoubleParameter_GetIntegral, METH_VARARGS, NULL},
  {NULL, NULL, NULL, NULL}
};

// ---

bool PyOFX_InitParameter_Double(PyObject *mod)
{
  INIT_TYPE(PyOFXDoubleParameterDescriptorType, "ofx.DoubleParameterDescriptor", PyOFXDoubleParameterDescriptor);
  PyOFXDoubleParameterDescriptorType.tp_base = &PyOFXValueParameterDescriptorType;
  PyOFXDoubleParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXDoubleParameterDescriptorType.tp_init = PyOFXDoubleParameterDescriptor_Init;
  PyOFXDoubleParameterDescriptorType.tp_getset = PyOFXDoubleParameterDescriptor_GetSeters;
  if (PyType_Ready(&PyOFXDoubleParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXDoubleParameterType, "ofx.DoubleParameter", PyOFXDoubleParameter);
  PyOFXDoubleParameterType.tp_base = &PyOFXValueParameterType;
  PyOFXDoubleParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXDoubleParameterType.tp_init = PyOFXDoubleParameter_Init;
  PyOFXDoubleParameterType.tp_getset = PyOFXDoubleParameter_GetSeters;
  PyOFXDoubleParameterType.tp_methods = PyOFXDoubleParameter_Methods;
  if (PyType_Ready(&PyOFXDoubleParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXDoubleParameterDescriptorType);
  PyModule_AddObject(mod, "DoubleParameterDescriptor", (PyObject*)&PyOFXDoubleParameterDescriptorType);
  
  Py_INCREF(&PyOFXDoubleParameterType);
  PyModule_AddObject(mod, "DoubleParameter", (PyObject*)&PyOFXDoubleParameterType);
  
  return true;
}
