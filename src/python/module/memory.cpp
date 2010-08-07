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

PyTypeObject PyOFXMemorySuiteType;
/* =
{
  PyObject_HEAD_INIT(NULL)
  0,
  "ofx.MemorySuite",
  sizeof(PyOFXMemorySuite),
  0
};*/

static PyObject* PyOFXMemorySuite_New(PyTypeObject *type, PyObject *, PyObject *)
{
  PyObject *self = type->tp_alloc(type, 0);
  ((PyOFXMemorySuite*)self)->suite = 0;
  return self;
}

static int PyOFXMemorySuite_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

static void PyOFXMemorySuite_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

static PyObject* PyOFXMemorySuite_Alloc(PyObject *self, PyObject *args)
{
  PyObject *prcv = 0;
  unsigned long size = 0;
  
  if (!PyArg_ParseTuple(args, "Ok", &prcv, &size))
  {
    return NULL;
  }
  
  Receiver rcv(prcv);
  
  PyOFXMemorySuite *psuite = (PyOFXMemorySuite*)self;
  
  if (!psuite->suite)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  void *mem = 0;
  
  CATCH({mem = psuite->suite->alloc(&rcv, size);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (mem == 0)
  {
    Py_INCREF(Py_None);
    return Py_None;
  }
  else
  {
    PyObject *phdl = PyObject_CallObject((PyObject*)&PyOFXHandleType, NULL);
    ((PyOFXHandle*)phdl)->handle = mem;
    return phdl;  
  }
}

static PyObject* PyOFXMemorySuite_Free(PyObject *self, PyObject *args)
{
  PyObject *phdl = 0;
  
  if (!PyArg_ParseTuple(args, "O", &phdl))
  {
    return NULL;
  }
  
  if (!PyObject_TypeCheck(phdl, &PyOFXHandleType))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a ofx.Handle object");
    return NULL;
  }
  
  PyOFXMemorySuite *psuite = (PyOFXMemorySuite*)self;
  
  if (!psuite->suite)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({psuite->suite->free(((PyOFXHandle*)phdl)->handle);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyMethodDef PyOFXMemorySuite_Methods[] =
{
  {"alloc", PyOFXMemorySuite_Alloc, METH_VARARGS, 0},
  {"free", PyOFXMemorySuite_Free, METH_VARARGS, 0},
  {NULL, NULL, NULL, NULL}
};

bool PyOFX_InitMemory(PyObject *mod)
{
  INIT_TYPE(PyOFXMemorySuiteType, "ofx.MemorySuite", PyOFXMemorySuite);
  PyOFXMemorySuiteType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXMemorySuiteType.tp_init = PyOFXMemorySuite_Init;
  PyOFXMemorySuiteType.tp_new = PyOFXMemorySuite_New;
  PyOFXMemorySuiteType.tp_dealloc = PyOFXMemorySuite_Delete;
  PyOFXMemorySuiteType.tp_methods = PyOFXMemorySuite_Methods;
  if (PyType_Ready(&PyOFXMemorySuiteType) < 0)
  {
    return false;
  }
  Py_INCREF(&PyOFXMemorySuiteType);
  PyModule_AddObject(mod, "MemorySuite", (PyObject*)&PyOFXMemorySuiteType);
  return true;
}
