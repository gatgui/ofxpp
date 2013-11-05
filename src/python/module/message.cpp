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

PyTypeObject PyOFXMessageSuiteType;

static PyObject* PyOFXMessageSuite_New(PyTypeObject *type, PyObject *, PyObject *)
{
  PyObject *self = type->tp_alloc(type, 0);
  ((PyOFXMessageSuite*)self)->suite = 0;
  return self;
}

static int PyOFXMessageSuite_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

static void PyOFXMessageSuite_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

static PyObject* PyOFXMessageSuite_Message(PyObject *self, PyObject *args)
{
  PyObject *prcv = 0;
  int mtype = 0;
  const char *id = 0;
  const char *msg = 0;
  
  if (!PyArg_ParseTuple(args, "Oiss", &prcv, &mtype, &id, &msg))
  {
    return NULL;
  }
  
  Receiver rcv(prcv);
  
  PyOFXMessageSuite *psuite = (PyOFXMessageSuite*)self;
  
  if (!psuite->suite)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = psuite->suite->message(&rcv, ofx::MessageType(mtype), id, msg);}, failed);
  
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

#ifdef OFX_API_1_2

static PyObject* PyOFXMessageSuite_SetPersistentMessage(PyObject *self, PyObject *args)
{
  PyObject *prcv = 0;
  int mtype = 0;
  const char *id = 0;
  const char *msg = 0;
  
  if (!PyArg_ParseTuple(args, "Oiss", &prcv, &mtype, &id, &msg))
  {
    return NULL;
  }
  
  Receiver rcv(prcv);
  
  PyOFXMessageSuite *psuite = (PyOFXMessageSuite*)self;
  
  if (!psuite->suite)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({psuite->suite->setPersistentMessage(&rcv, ofx::MessageType(mtype), id, msg);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* PyOFXMessageSuite_ClearPersistentMessage(PyObject *self, PyObject *args)
{
  PyObject *prcv = 0;
  
  if (!PyArg_ParseTuple(args, "O", &prcv))
  {
    return NULL;
  }
  
  Receiver rcv(prcv);
  
  PyOFXMessageSuite *psuite = (PyOFXMessageSuite*)self;
  
  if (!psuite->suite)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({psuite->suite->clearPersistentMessage(&rcv);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

#endif

static PyMethodDef PyOFXMessageSuite_Methods[] =
{
  {"message", PyOFXMessageSuite_Message, METH_VARARGS, 0},
#ifdef OFX_API_1_2
  {"setPersistentMessage", PyOFXMessageSuite_SetPersistentMessage, METH_VARARGS, 0},
  {"clearPersistentMessage", PyOFXMessageSuite_ClearPersistentMessage, METH_VARARGS, 0},
#endif
  {NULL, NULL, 0, NULL}
};

bool PyOFX_InitMessage(PyObject *mod)
{
  INIT_TYPE(PyOFXMessageSuiteType, "ofx.MessageSuite", PyOFXMessageSuite);
  PyOFXMessageSuiteType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXMessageSuiteType.tp_init = PyOFXMessageSuite_Init;
  PyOFXMessageSuiteType.tp_new = PyOFXMessageSuite_New;
  PyOFXMessageSuiteType.tp_dealloc = PyOFXMessageSuite_Delete;
  PyOFXMessageSuiteType.tp_methods = PyOFXMessageSuite_Methods;
  if (PyType_Ready(&PyOFXMessageSuiteType) < 0)
  {
    return false;
  }
  Py_INCREF(&PyOFXMessageSuiteType);
  PyModule_AddObject(mod, "MessageSuite", (PyObject*)&PyOFXMessageSuiteType);
  return true;
}
