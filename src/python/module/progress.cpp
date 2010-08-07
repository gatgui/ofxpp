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

PyTypeObject PyOFXProgressSuiteType;

static PyObject* PyOFXProgressSuite_New(PyTypeObject *type, PyObject *, PyObject *)
{
  PyObject *self = type->tp_alloc(type, 0);
  ((PyOFXProgressSuite*)self)->suite = 0;
  return self;
}

static int PyOFXProgressSuite_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

static void PyOFXProgressSuite_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

static PyObject* PyOFXProgressSuite_Start(PyObject *self, PyObject *args)
{
  PyObject *prcv = 0;
  const char *label = 0;
  
  if (!PyArg_ParseTuple(args, "Os", &prcv, &label))
  {
    return NULL;
  }
  
  Receiver rcv(prcv);
  
  PyOFXProgressSuite *psuite = (PyOFXProgressSuite*)self;
  
  if (!psuite->suite)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({psuite->suite->start(&rcv, label);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* PyOFXProgressSuite_Update(PyObject *self, PyObject *args)
{
  PyObject *prcv = 0;
  double val = 0.0;
  
  if (!PyArg_ParseTuple(args, "Od", &prcv, &val))
  {
    return NULL;
  }
  
  Receiver rcv(prcv);
  
  PyOFXProgressSuite *psuite = (PyOFXProgressSuite*)self;
  
  if (!psuite->suite)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({psuite->suite->update(&rcv, val);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* PyOFXProgressSuite_End(PyObject *self, PyObject *args)
{
  PyObject *prcv = 0;
  
  if (!PyArg_ParseTuple(args, "O", &prcv))
  {
    return NULL;
  }
  
  Receiver rcv(prcv);
  
  PyOFXProgressSuite *psuite = (PyOFXProgressSuite*)self;
  
  if (!psuite->suite)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({psuite->suite->end(&rcv);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyMethodDef PyOFXProgressSuite_Methods[] =
{
  {"start", PyOFXProgressSuite_Start, METH_VARARGS, 0},
  {"update", PyOFXProgressSuite_Update, METH_VARARGS, 0},
  {"end", PyOFXProgressSuite_End, METH_VARARGS, 0},
  {NULL, NULL, NULL, NULL}
};

bool PyOFX_InitProgress(PyObject *mod)
{
  INIT_TYPE(PyOFXProgressSuiteType, "ofx.ProgressSuite", PyOFXProgressSuite);
  PyOFXProgressSuiteType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXProgressSuiteType.tp_init = PyOFXProgressSuite_Init;
  PyOFXProgressSuiteType.tp_new = PyOFXProgressSuite_New;
  PyOFXProgressSuiteType.tp_dealloc = PyOFXProgressSuite_Delete;
  PyOFXProgressSuiteType.tp_methods = PyOFXProgressSuite_Methods;
  if (PyType_Ready(&PyOFXProgressSuiteType) < 0)
  {
    return false;
  }
  Py_INCREF(&PyOFXProgressSuiteType);
  PyModule_AddObject(mod, "ProgressSuite", (PyObject*)&PyOFXProgressSuiteType);
  return true;
}
