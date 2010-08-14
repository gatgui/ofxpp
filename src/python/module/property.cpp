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

PyTypeObject PyOFXPropertySetType;

static PyObject* PyOFXPropertySet_New(PyTypeObject *type, PyObject *, PyObject *)
{
  PyObject *self = type->tp_alloc(type, 0);
  ((PyOFXPropertySet*)self)->pset = 0;
  return self;
}

static int PyOFXPropertySet_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

static void PyOFXPropertySet_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

static PyObject* PyOFXPropertySet_SetPointer(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  int index = 0;
  PyObject *val;
  
  if (!PyArg_ParseTuple(args, "siO", &prop, &index, &val))
  {
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({ppset->pset->setPointer(prop, index, val);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* PyOFXPropertySet_SetPointers(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  PyObject *val;
  
  if (!PyArg_ParseTuple(args, "sO", &prop, &val))
  {
    return NULL;
  }
  
  if (!PyList_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a list");
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  Py_ssize_t n = PyList_Size(val);
  void ** vals = new void* [n];
  
  for (Py_ssize_t i=0; i<n; ++i)
  {
    vals[i] = (void*) PyList_GetItem(val, i);
  }
  
  bool failed = false;
  
  CATCH({ppset->pset->setPointers(prop, int(n), vals);}, failed);
  
  delete[] vals;
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* PyOFXPropertySet_SetString(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  int index = 0;
  const char *val = 0;
  
  if (!PyArg_ParseTuple(args, "sis", &prop, &index, &val))
  {
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({ppset->pset->setString(prop, index, val);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* PyOFXPropertySet_SetStrings(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  PyObject *val;
  
  if (!PyArg_ParseTuple(args, "sO", &prop, &val))
  {
    return NULL;
  }
  
  if (!PyList_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a list");
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  Py_ssize_t n = PyList_Size(val);
  std::string *vals = new std::string[n];
  
  for (Py_ssize_t i=0; i<n; ++i)
  {
    PyObject *item = PyList_GetItem(val, i);
    if (!PyString_Check(item))
    {
      PyErr_SetString(PyExc_TypeError, "Expected a list of strings");
      delete[] vals;
      return NULL;
    }
    vals[i] = PyString_AsString(item);
  }
  
  bool failed = false;
  
  CATCH({ppset->pset->setStrings(prop, int(n), vals);}, failed);
  
  delete[] vals;
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* PyOFXPropertySet_SetDouble(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  int index = 0;
  double val = 0;
  
  if (!PyArg_ParseTuple(args, "sid", &prop, &index, &val))
  {
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({ppset->pset->setDouble(prop, index, val);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* PyOFXPropertySet_SetDoubles(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  PyObject *val;
  
  if (!PyArg_ParseTuple(args, "sO", &prop, &val))
  {
    return NULL;
  }
  
  if (!PyList_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a list");
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  Py_ssize_t n = PyList_Size(val);
  double *vals = new double[n];
  
  for (Py_ssize_t i=0; i<n; ++i)
  {
    PyObject *item = PyList_GetItem(val, i);
    if (!PyFloat_Check(item))
    {
      PyErr_SetString(PyExc_TypeError, "Expected a list of floats");
      delete[] vals;
      return NULL;
    }
    vals[i] = PyFloat_AsDouble(item);
  }
  
  bool failed = false;
  
  CATCH({ppset->pset->setDoubles(prop, int(n), vals);}, failed);
  
  delete[] vals;
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* PyOFXPropertySet_SetInt(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  int index = 0;
  int val = 0;
  
  if (!PyArg_ParseTuple(args, "sii", &prop, &index, &val))
  {
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({ppset->pset->setInt(prop, index, val);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* PyOFXPropertySet_SetInts(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  PyObject *val;
  
  if (!PyArg_ParseTuple(args, "sO", &prop, &val))
  {
    return NULL;
  }
  
  if (!PyList_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a list");
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  Py_ssize_t n = PyList_Size(val);
  int *vals = new int[n];
  
  for (Py_ssize_t i=0; i<n; ++i)
  {
    PyObject *item = PyList_GetItem(val, i);
    if (!PyInt_Check(item))
    {
      PyErr_SetString(PyExc_TypeError, "Expected a list of ints");
      delete[] vals;
      return NULL;
    }
    vals[i] = PyInt_AsLong(item);
  }
  
  bool failed = false;
  
  CATCH({ppset->pset->setInts(prop, int(n), vals);}, failed);
  
  delete[] vals;
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* PyOFXPropertySet_GetPointer(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  int index = 0;
  
  if (!PyArg_ParseTuple(args, "si", &prop, &index))
  {
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  void *ptr = 0;
  
  CATCH({ptr = ppset->pset->getPointer(prop, index);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (ptr == 0)
  {
    Py_INCREF(Py_None);
    return Py_None;
  }
  else
  {
    return ((PyObject*)ptr);
  }
}

static PyObject* PyOFXPropertySet_GetPointers(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  int n = 0;
  
  if (!PyArg_ParseTuple(args, "si", &prop, &n))
  {
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  void **vals = new void* [n];
  
  CATCH({ppset->pset->getPointers(prop, n, vals);}, failed);
  
  if (failed)
  {
    delete[] vals;
    return NULL;
  }
  
  PyObject *rv = PyList_New(n);
  for (int i=0; i<n; ++i)
  {
    if (vals[i])
    {
      PyList_SetItem(rv, i, (PyObject*)vals[i]);
    }
    else
    {
      Py_INCREF(Py_None);
      PyList_SetItem(rv, i, Py_None);
    }
  }
  
  delete[] vals;
  
  return rv;
}

static PyObject* PyOFXPropertySet_GetString(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  int index = 0;
  
  if (!PyArg_ParseTuple(args, "si", &prop, &index))
  {
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string val;
  
  CATCH({val = ppset->pset->getString(prop, index);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(val.c_str());
}

static PyObject* PyOFXPropertySet_GetStrings(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  int n = 0;
  
  if (!PyArg_ParseTuple(args, "si", &prop, &n))
  {
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string *vals = new std::string[n];
  
  CATCH({ppset->pset->getStrings(prop, n, vals);}, failed);
  
  if (failed)
  {
    delete[] vals;
    return NULL;
  }
  
  PyObject *rv = PyList_New(n);
  for (int i=0; i<n; ++i)
  {
    PyList_SetItem(rv, i, PyString_FromString(vals[i].c_str()));
  }
  
  delete[] vals;
  
  return rv;
}

static PyObject* PyOFXPropertySet_GetDouble(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  int index = 0;
  
  if (!PyArg_ParseTuple(args, "si", &prop, &index))
  {
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double val = 0.0;
  
  CATCH({val = ppset->pset->getDouble(prop, index);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(val);
}

static PyObject* PyOFXPropertySet_GetDoubles(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  int n = 0;
  
  if (!PyArg_ParseTuple(args, "si", &prop, &n))
  {
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double *vals = new double[n];
  
  CATCH({ppset->pset->getDoubles(prop, n, vals);}, failed);
  
  if (failed)
  {
    delete[] vals;
    return NULL;
  }
  
  PyObject *rv = PyList_New(n);
  for (int i=0; i<n; ++i)
  {
    PyList_SetItem(rv, i, PyFloat_FromDouble(vals[i]));
  }
  
  delete[] vals;
  
  return rv;
}

static PyObject* PyOFXPropertySet_GetInt(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  int index = 0;
  
  if (!PyArg_ParseTuple(args, "si", &prop, &index))
  {
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int val = 0;
  
  CATCH({val = ppset->pset->getInt(prop, index);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(val);
}

static PyObject* PyOFXPropertySet_GetInts(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  int n = 0;
  
  if (!PyArg_ParseTuple(args, "si", &prop, &n))
  {
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int *vals = new int[n];
  
  CATCH({ppset->pset->getInts(prop, n, vals);}, failed);
  
  if (failed)
  {
    delete[] vals;
    return NULL;
  }
  
  PyObject *rv = PyList_New(n);
  for (int i=0; i<n; ++i)
  {
    PyList_SetItem(rv, i, PyInt_FromLong(vals[i]));
  }
  
  delete[] vals;
  
  return rv;
}

static PyObject* PyOFXPropertySet_Reset(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  
  if (!PyArg_ParseTuple(args, "s", &prop))
  {
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({ppset->pset->reset(prop);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* PyOFXPropertySet_Size(PyObject *self, PyObject *args)
{
  const char *prop = 0;
  
  if (!PyArg_ParseTuple(args, "s", &prop))
  {
    return NULL;
  }
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int sz = 0;
  
  CATCH({sz = ppset->pset->size(prop);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(sz);
}

static PyObject* PyOFXPropertySet_GetHandle(PyObject *self, void*)
{
  PyOFXPropertySet *ppset = (PyOFXPropertySet*) self;
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  OfxPropertySetHandle handle = 0;
  
  CATCH({handle = ppset->pset->handle();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *phdl = PyObject_CallObject((PyObject*)&PyOFXHandleType, NULL);
  ((PyOFXHandle*)phdl)->handle = (void*) handle;
  return phdl;
}

static PyGetSetDef PyOFXPropertySet_GetSeters[] =
{
  {(char*)"handle", PyOFXPropertySet_GetHandle, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

static PyMethodDef PyOFXPropertySet_Methods[] =
{
  {"setPointer", PyOFXPropertySet_SetPointer, METH_VARARGS, 0},
  {"setPointers", PyOFXPropertySet_SetPointers, METH_VARARGS, 0},
  {"setString", PyOFXPropertySet_SetString, METH_VARARGS, 0},
  {"setStrings", PyOFXPropertySet_SetStrings, METH_VARARGS, 0},
  {"setDouble", PyOFXPropertySet_SetDouble, METH_VARARGS, 0},
  {"setDoubles", PyOFXPropertySet_SetDoubles, METH_VARARGS, 0},
  {"setInt", PyOFXPropertySet_SetInt, METH_VARARGS, 0},
  {"setInts", PyOFXPropertySet_SetInts, METH_VARARGS, 0},
  {"getPointer", PyOFXPropertySet_GetPointer, METH_VARARGS, 0},
  {"getPointers", PyOFXPropertySet_GetPointers, METH_VARARGS, 0},
  {"getString", PyOFXPropertySet_GetString, METH_VARARGS, 0},
  {"getStrings", PyOFXPropertySet_GetStrings, METH_VARARGS, 0},
  {"getDouble", PyOFXPropertySet_GetDouble, METH_VARARGS, 0},
  {"getDoubles", PyOFXPropertySet_GetDoubles, METH_VARARGS, 0},
  {"getInt", PyOFXPropertySet_GetInt, METH_VARARGS, 0},
  {"getInts", PyOFXPropertySet_GetInts, METH_VARARGS, 0},
  {"reset", PyOFXPropertySet_Reset, METH_VARARGS, 0},
  {"size", PyOFXPropertySet_Size, METH_VARARGS, 0},
  {NULL, NULL, NULL, NULL}
};

bool PyOFX_InitProperty(PyObject *mod)
{
  INIT_TYPE(PyOFXPropertySetType, "PropertySet", PyOFXPropertySet);
  PyOFXPropertySetType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXPropertySetType.tp_init = PyOFXPropertySet_Init;
  PyOFXPropertySetType.tp_new = PyOFXPropertySet_New;
  PyOFXPropertySetType.tp_dealloc = PyOFXPropertySet_Delete;
  PyOFXPropertySetType.tp_methods = PyOFXPropertySet_Methods;
  PyOFXPropertySetType.tp_getset = PyOFXPropertySet_GetSeters;
  if (PyType_Ready(&PyOFXPropertySetType) < 0)
  {
    return false;
  }
  Py_INCREF(&PyOFXPropertySetType);
  PyModule_AddObject(mod, "PropertySet", (PyObject*)&PyOFXPropertySetType);
  return true;
}
