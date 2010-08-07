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

PyTypeObject PyOFXExceptionType;
PyTypeObject PyOFXFailedErrorType;
PyTypeObject PyOFXFatalErrorType;
PyTypeObject PyOFXUnknownErrorType;
PyTypeObject PyOFXMissingHostFeatureErrorType;
PyTypeObject PyOFXUnsupportedErrorType;
PyTypeObject PyOFXExistsErrorType;
PyTypeObject PyOFXFormatErrorType;
PyTypeObject PyOFXMemoryErrorType;
PyTypeObject PyOFXBadHandleErrorType;
PyTypeObject PyOFXBadIndexErrorType;
PyTypeObject PyOFXValueErrorType;

// ---

static void PyOFXException_Delete(PyObject *self)
{
  PyOFXException *pexc = (PyOFXException*)self;
  Py_XDECREF(pexc->status);
  ((PyTypeObject*)PyExc_BaseException)->tp_dealloc(self);
}

static PyObject* PyOFXException_New(PyTypeObject *type, PyObject *args, PyObject *kwargs)
{
  PyObject *self = ((PyTypeObject*)PyExc_BaseException)->tp_new(type, args, kwargs);
  if (self != 0)
  {
    PyOFXException *pexc = (PyOFXException*)self;
    pexc->status = PyInt_FromLong(0);
  }
  return self;
}

static int PyOFXException_Init(PyObject *self, PyObject *args, PyObject *kwargs)
{
  PyOFXException *pexc = (PyOFXException*)self;
  
  if (PyTuple_Size(args) < 1)
  {
    PyErr_SetString(PyExc_RuntimeError, "At least one argument");
    return -1;
  }
  
  PyObject *status = PyTuple_GetItem(args, 0);
  
  if (!PyInt_Check(status))
  {
    PyErr_SetString(PyExc_TypeError, "First argument must be an integer");
    return -1;
  }
  
  Py_INCREF(status);
  pexc->status = status;
  
  PyObject *remainingArgs = PyTuple_GetSlice(args, 1, PyTuple_Size(args));
  
  int rv = ((PyTypeObject*)PyExc_BaseException)->tp_init(self, remainingArgs, kwargs);
  
  Py_DECREF(remainingArgs);

  return rv;
}

static PyMemberDef PyOFXException_Members[] =
{
  {(char*)"status", T_OBJECT_EX, offsetof(PyOFXException, status), 0, NULL},
  {NULL, 0, 0, 0, NULL}
};

// ---

static int PyOFXFailedError_Init(PyObject *self, PyObject *args, PyObject *kwargs)
{
  PyObject *newArgs = PyTuple_New(PyTuple_Size(args)+1);
  PyTuple_SetItem(newArgs, 0, PyInt_FromLong(kOfxStatFailed));
  for (Py_ssize_t i=0; i<PyTuple_Size(args); ++i)
  {
    PyObject *item = PyTuple_GetItem(args, i);
    Py_INCREF(item);
    PyTuple_SetItem(newArgs, i+1, item);
  }
  int rv = PyOFXExceptionType.tp_init(self, newArgs, kwargs);
  Py_DECREF(newArgs);
  return rv;
}

// ---

static int PyOFXFatalError_Init(PyObject *self, PyObject *args, PyObject *kwargs)
{
  PyObject *newArgs = PyTuple_New(PyTuple_Size(args)+1);
  PyTuple_SetItem(newArgs, 0, PyInt_FromLong(kOfxStatErrFatal));
  for (Py_ssize_t i=0; i<PyTuple_Size(args); ++i)
  {
    PyObject *item = PyTuple_GetItem(args, i);
    Py_INCREF(item);
    PyTuple_SetItem(newArgs, i+1, item);
  }
  int rv = PyOFXExceptionType.tp_init(self, newArgs, kwargs);
  Py_DECREF(newArgs);
  return rv;
}

// ---

static int PyOFXUnknownError_Init(PyObject *self, PyObject *args, PyObject *kwargs)
{
  PyObject *newArgs = PyTuple_New(PyTuple_Size(args)+1);
  PyTuple_SetItem(newArgs, 0, PyInt_FromLong(kOfxStatErrUnknown));
  for (Py_ssize_t i=0; i<PyTuple_Size(args); ++i)
  {
    PyObject *item = PyTuple_GetItem(args, i);
    Py_INCREF(item);
    PyTuple_SetItem(newArgs, i+1, item);
  }
  int rv = PyOFXExceptionType.tp_init(self, newArgs, kwargs);
  Py_DECREF(newArgs);
  return rv;
}

// ---

static int PyOFXMissingHostFeatureError_Init(PyObject *self, PyObject *args, PyObject *kwargs)
{
  PyObject *newArgs = PyTuple_New(PyTuple_Size(args)+1);
  PyTuple_SetItem(newArgs, 0, PyInt_FromLong(kOfxStatErrMissingHostFeature));
  for (Py_ssize_t i=0; i<PyTuple_Size(args); ++i)
  {
    PyObject *item = PyTuple_GetItem(args, i);
    Py_INCREF(item);
    PyTuple_SetItem(newArgs, i+1, item);
  }
  int rv = PyOFXExceptionType.tp_init(self, newArgs, kwargs);
  Py_DECREF(newArgs);
  return rv;
}

// ---

static int PyOFXUnsupportedError_Init(PyObject *self, PyObject *args, PyObject *kwargs)
{
  PyObject *newArgs = PyTuple_New(PyTuple_Size(args)+1);
  PyTuple_SetItem(newArgs, 0, PyInt_FromLong(kOfxStatErrUnsupported));
  for (Py_ssize_t i=0; i<PyTuple_Size(args); ++i)
  {
    PyObject *item = PyTuple_GetItem(args, i);
    Py_INCREF(item);
    PyTuple_SetItem(newArgs, i+1, item);
  }
  int rv = PyOFXExceptionType.tp_init(self, newArgs, kwargs);
  Py_DECREF(newArgs);
  return rv;
}

// ---

static int PyOFXExistsError_Init(PyObject *self, PyObject *args, PyObject *kwargs)
{
  PyObject *newArgs = PyTuple_New(PyTuple_Size(args)+1);
  PyTuple_SetItem(newArgs, 0, PyInt_FromLong(kOfxStatErrExists));
  for (Py_ssize_t i=0; i<PyTuple_Size(args); ++i)
  {
    PyObject *item = PyTuple_GetItem(args, i);
    Py_INCREF(item);
    PyTuple_SetItem(newArgs, i+1, item);
  }
  int rv = PyOFXExceptionType.tp_init(self, newArgs, kwargs);
  Py_DECREF(newArgs);
  return rv;
}

// ---

static int PyOFXFormatError_Init(PyObject *self, PyObject *args, PyObject *kwargs)
{
  PyObject *newArgs = PyTuple_New(PyTuple_Size(args)+1);
  PyTuple_SetItem(newArgs, 0, PyInt_FromLong(kOfxStatErrFormat));
  for (Py_ssize_t i=0; i<PyTuple_Size(args); ++i)
  {
    PyObject *item = PyTuple_GetItem(args, i);
    Py_INCREF(item);
    PyTuple_SetItem(newArgs, i+1, item);
  }
  int rv = PyOFXExceptionType.tp_init(self, newArgs, kwargs);
  Py_DECREF(newArgs);
  return rv;
}

// ---

static int PyOFXMemoryError_Init(PyObject *self, PyObject *args, PyObject *kwargs)
{
  PyObject *newArgs = PyTuple_New(PyTuple_Size(args)+1);
  PyTuple_SetItem(newArgs, 0, PyInt_FromLong(kOfxStatErrMemory));
  for (Py_ssize_t i=0; i<PyTuple_Size(args); ++i)
  {
    PyObject *item = PyTuple_GetItem(args, i);
    Py_INCREF(item);
    PyTuple_SetItem(newArgs, i+1, item);
  }
  int rv = PyOFXExceptionType.tp_init(self, newArgs, kwargs);
  Py_DECREF(newArgs);
  return rv;
}

// ---

static int PyOFXBadHandleError_Init(PyObject *self, PyObject *args, PyObject *kwargs)
{
  PyObject *newArgs = PyTuple_New(PyTuple_Size(args)+1);
  PyTuple_SetItem(newArgs, 0, PyInt_FromLong(kOfxStatErrBadHandle));
  for (Py_ssize_t i=0; i<PyTuple_Size(args); ++i)
  {
    PyObject *item = PyTuple_GetItem(args, i);
    Py_INCREF(item);
    PyTuple_SetItem(newArgs, i+1, item);
  }
  int rv = PyOFXExceptionType.tp_init(self, newArgs, kwargs);
  Py_DECREF(newArgs);
  return rv;
}

// ---

static int PyOFXBadIndexError_Init(PyObject *self, PyObject *args, PyObject *kwargs)
{
  PyObject *newArgs = PyTuple_New(PyTuple_Size(args)+1);
  PyTuple_SetItem(newArgs, 0, PyInt_FromLong(kOfxStatErrBadIndex));
  for (Py_ssize_t i=0; i<PyTuple_Size(args); ++i)
  {
    PyObject *item = PyTuple_GetItem(args, i);
    Py_INCREF(item);
    PyTuple_SetItem(newArgs, i+1, item);
  }
  int rv = PyOFXExceptionType.tp_init(self, newArgs, kwargs);
  Py_DECREF(newArgs);
  return rv;
}

// ---

static int PyOFXValueError_Init(PyObject *self, PyObject *args, PyObject *kwargs)
{
  PyObject *newArgs = PyTuple_New(PyTuple_Size(args)+1);
  PyTuple_SetItem(newArgs, 0, PyInt_FromLong(kOfxStatErrValue));
  for (Py_ssize_t i=0; i<PyTuple_Size(args); ++i)
  {
    PyObject *item = PyTuple_GetItem(args, i);
    Py_INCREF(item);
    PyTuple_SetItem(newArgs, i+1, item);
  }
  int rv = PyOFXExceptionType.tp_init(self, newArgs, kwargs);
  Py_DECREF(newArgs);
  return rv;
}

// ---

bool PyOFX_InitException(PyObject *mod)
{
  INIT_TYPE(PyOFXExceptionType, "ofx.Exception", PyOFXException);
  PyOFXExceptionType.tp_base = (PyTypeObject*)PyExc_BaseException;
  PyOFXExceptionType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXExceptionType.tp_new = PyOFXException_New;
  PyOFXExceptionType.tp_init = PyOFXException_Init;
  PyOFXExceptionType.tp_dealloc = PyOFXException_Delete;
  PyOFXExceptionType.tp_members = PyOFXException_Members;
  if (PyType_Ready(&PyOFXExceptionType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXFailedErrorType, "ofx.FailedError", PyOFXException);
  PyOFXFailedErrorType.tp_base = &PyOFXExceptionType;
  PyOFXFailedErrorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXFailedErrorType.tp_init = PyOFXFailedError_Init;
  if (PyType_Ready(&PyOFXFailedErrorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXFatalErrorType, "ofx.FatalError", PyOFXException);
  PyOFXFatalErrorType.tp_base = &PyOFXExceptionType;
  PyOFXFatalErrorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXFatalErrorType.tp_init = PyOFXFatalError_Init;
  if (PyType_Ready(&PyOFXFatalErrorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXUnknownErrorType, "ofx.UnknownError", PyOFXException);
  PyOFXUnknownErrorType.tp_base = &PyOFXExceptionType;
  PyOFXUnknownErrorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXUnknownErrorType.tp_init = PyOFXUnknownError_Init;
  if (PyType_Ready(&PyOFXUnknownErrorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXMissingHostFeatureErrorType, "ofx.MissingHostFeatureError", PyOFXException);
  PyOFXMissingHostFeatureErrorType.tp_base = &PyOFXExceptionType;
  PyOFXMissingHostFeatureErrorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXMissingHostFeatureErrorType.tp_init = PyOFXMissingHostFeatureError_Init;
  if (PyType_Ready(&PyOFXMissingHostFeatureErrorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXUnsupportedErrorType, "ofx.UnsupportedError", PyOFXException);
  PyOFXUnsupportedErrorType.tp_base = &PyOFXExceptionType;
  PyOFXUnsupportedErrorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXUnsupportedErrorType.tp_init = PyOFXUnsupportedError_Init;
  if (PyType_Ready(&PyOFXUnsupportedErrorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXExistsErrorType, "ofx.ExistsError", PyOFXException);
  PyOFXExistsErrorType.tp_base = &PyOFXExceptionType;
  PyOFXExistsErrorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXExistsErrorType.tp_init = PyOFXExistsError_Init;
  if (PyType_Ready(&PyOFXExistsErrorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXFormatErrorType, "ofx.FormatError", PyOFXException);
  PyOFXFormatErrorType.tp_base = &PyOFXExceptionType;
  PyOFXFormatErrorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXFormatErrorType.tp_init = PyOFXFormatError_Init;
  if (PyType_Ready(&PyOFXFormatErrorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXMemoryErrorType, "ofx.MemoryError", PyOFXException);
  PyOFXMemoryErrorType.tp_base = &PyOFXExceptionType;
  PyOFXMemoryErrorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXMemoryErrorType.tp_init = PyOFXMemoryError_Init;
  if (PyType_Ready(&PyOFXMemoryErrorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXBadHandleErrorType, "ofx.BadHandleError", PyOFXException);
  PyOFXBadHandleErrorType.tp_base = &PyOFXExceptionType;
  PyOFXBadHandleErrorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXBadHandleErrorType.tp_init = PyOFXBadHandleError_Init;
  if (PyType_Ready(&PyOFXBadHandleErrorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXBadIndexErrorType, "ofx.BadIndexError", PyOFXException);
  PyOFXBadIndexErrorType.tp_base = &PyOFXExceptionType;
  PyOFXBadIndexErrorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXBadIndexErrorType.tp_init = PyOFXBadIndexError_Init;
  if (PyType_Ready(&PyOFXBadIndexErrorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXValueErrorType, "ofx.ValueError", PyOFXException);
  PyOFXValueErrorType.tp_base = &PyOFXExceptionType;
  PyOFXValueErrorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXValueErrorType.tp_init = PyOFXValueError_Init;
  if (PyType_Ready(&PyOFXValueErrorType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXExceptionType);
  Py_INCREF(&PyOFXFailedErrorType);
  Py_INCREF(&PyOFXFatalErrorType);
  Py_INCREF(&PyOFXUnknownErrorType);
  Py_INCREF(&PyOFXMissingHostFeatureErrorType);
  Py_INCREF(&PyOFXUnsupportedErrorType);
  Py_INCREF(&PyOFXExistsErrorType);
  Py_INCREF(&PyOFXFormatErrorType);
  Py_INCREF(&PyOFXMemoryErrorType);
  Py_INCREF(&PyOFXBadHandleErrorType);
  Py_INCREF(&PyOFXBadIndexErrorType);
  Py_INCREF(&PyOFXValueErrorType);
  
  PyModule_AddObject(mod, "Exception", (PyObject*)&PyOFXExceptionType);
  PyModule_AddObject(mod, "FailedError", (PyObject*)&PyOFXFailedErrorType);
  PyModule_AddObject(mod, "FatalError", (PyObject*)&PyOFXFatalErrorType);
  PyModule_AddObject(mod, "UnknownError", (PyObject*)&PyOFXUnknownErrorType);
  PyModule_AddObject(mod, "MissingHostFeatureError", (PyObject*)&PyOFXMissingHostFeatureErrorType);
  PyModule_AddObject(mod, "UnsupportedError", (PyObject*)&PyOFXUnsupportedErrorType);
  PyModule_AddObject(mod, "ExistsError", (PyObject*)&PyOFXExistsErrorType);
  PyModule_AddObject(mod, "FormatError", (PyObject*)&PyOFXFormatErrorType);
  PyModule_AddObject(mod, "MemoryError", (PyObject*)&PyOFXMemoryErrorType);
  PyModule_AddObject(mod, "BadHandleError", (PyObject*)&PyOFXBadHandleErrorType);
  PyModule_AddObject(mod, "BadIndexError", (PyObject*)&PyOFXBadIndexErrorType);
  PyModule_AddObject(mod, "ValueError", (PyObject*)&PyOFXValueErrorType);
  
  return true;
}
