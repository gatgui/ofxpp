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

PyTypeObject PyOFXTimeLineSuiteType;

static PyObject* PyOFXTimeLineSuite_New(PyTypeObject *type, PyObject *, PyObject *)
{
  PyObject *self = type->tp_alloc(type, 0);
  ((PyOFXTimeLineSuite*)self)->suite = 0;
  return self;
}

static int PyOFXTimeLineSuite_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

static void PyOFXTimeLineSuite_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

static PyObject* PyOFXTimeLineSuite_GetTime(PyObject *self, PyObject *args)
{
  PyObject *prcv = 0;
  
  if (!PyArg_ParseTuple(args, "O", &prcv))
  {
    return NULL;
  }
  
  Receiver rcv(prcv);
  
  PyOFXTimeLineSuite *psuite = (PyOFXTimeLineSuite*)self;
  
  if (!psuite->suite)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  double t = 0.0;
  
  CATCH({t = psuite->suite->getTime(&rcv);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(t);
}

static PyObject* PyOFXTimeLineSuite_GotoTime(PyObject *self, PyObject *args)
{
  PyObject *prcv = 0;
  double t = 0.0;
  
  if (!PyArg_ParseTuple(args, "Od", &prcv, &t))
  {
    return NULL;
  }
  
  Receiver rcv(prcv);
  
  PyOFXTimeLineSuite *psuite = (PyOFXTimeLineSuite*)self;
  
  if (!psuite->suite)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({psuite->suite->gotoTime(&rcv, t);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* PyOFXTimeLineSuite_GetTimeBounds(PyObject *self, PyObject *args)
{
  PyObject *prcv = 0;
  
  if (!PyArg_ParseTuple(args, "O", &prcv))
  {
    return NULL;
  }
  
  Receiver rcv(prcv);
  
  PyOFXTimeLineSuite *psuite = (PyOFXTimeLineSuite*)self;
  
  if (!psuite->suite)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  ofx::FrameRange r = {0.0, 0.0};
  
  CATCH({r = psuite->suite->getTimeBounds(&rcv);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXRangeDType, NULL);
  ((PyOFXRangeD*)rv)->range = r;
  return rv;
}

static PyMethodDef PyOFXTimeLineSuite_Methods[] =
{
  {"getTime", PyOFXTimeLineSuite_GetTime, METH_VARARGS, 0},
  {"gotoTime", PyOFXTimeLineSuite_GotoTime, METH_VARARGS, 0},
  {"getTimeBounds", PyOFXTimeLineSuite_GetTimeBounds, METH_VARARGS, 0},
  {NULL, NULL, 0, NULL}
};

bool PyOFX_InitTimeLine(PyObject *mod)
{
  INIT_TYPE(PyOFXTimeLineSuiteType, "ofx.TimeLineSuite", PyOFXTimeLineSuite);
  PyOFXTimeLineSuiteType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXTimeLineSuiteType.tp_init = PyOFXTimeLineSuite_Init;
  PyOFXTimeLineSuiteType.tp_new = PyOFXTimeLineSuite_New;
  PyOFXTimeLineSuiteType.tp_dealloc = PyOFXTimeLineSuite_Delete;
  PyOFXTimeLineSuiteType.tp_methods = PyOFXTimeLineSuite_Methods;
  if (PyType_Ready(&PyOFXTimeLineSuiteType) < 0)
  {
    return false;
  }
  Py_INCREF(&PyOFXTimeLineSuiteType);
  PyModule_AddObject(mod, "TimeLineSuite", (PyObject*)&PyOFXTimeLineSuiteType);
  return true;
}
