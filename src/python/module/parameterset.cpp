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

PyTypeObject PyOFXParameterSetType;
PyTypeObject PyOFXParameterSetDescriptorType;

// ---

PyObject* PyOFXParameterSetDescriptor_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  //((PyOFXParameterSetDescriptor*)self)->desc = new ofx::ParameterSetDescriptor();
  ((PyOFXParameterSetDescriptor*)self)->desc = 0;
  return self;
}

int PyOFXParameterSetDescriptor_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

void PyOFXParameterSetDescriptor_Delete(PyObject *self)
{
  //PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  //if (pdesc->desc)
  //{
  //  delete pdesc->desc;
  //}
  self->ob_type->tp_free(self);
}

PyObject* PyOFXParameterSetDescriptor_GetHost(PyObject *self, void*)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  if (pdesc->desc->host() == 0)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*) &PyOFXHostType, NULL);
    ((PyOFXHost*)rv)->host = pdesc->desc->host();
    return rv;
  }
}

PyObject* PyOFXParameterSetDescriptor_GetHandle(PyObject *self, void*)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  if (pdesc->desc->handle() == 0)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*) &PyOFXHandleType, NULL);
    ((PyOFXHandle*)rv)->handle = (void*) pdesc->desc->handle();
    return rv;
  }
}

PyObject* PyOFXParameterSetDescriptor_GetProperties(PyObject *self, void*)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*) &PyOFXPropertySetType, NULL);
  ((PyOFXPropertySet*)rv)->pset = &(pdesc->desc->properties());
  return rv;
}

static PyGetSetDef PyOFXParameterSetDescriptor_GetSeters[] =
{
  {(char*)"host", PyOFXParameterSetDescriptor_GetHost, NULL, NULL, NULL},
  {(char*)"handle", PyOFXParameterSetDescriptor_GetHandle, NULL, NULL, NULL},
  {(char*)"properties", PyOFXParameterSetDescriptor_GetProperties, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXParameterSetDescriptor_PageOrderCount(PyObject *self, PyObject *)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = desc->pageOrderCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXParameterSetDescriptor_PageOrder(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
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
  char *name = 0;
  
  if (nargs == 2)
  {
    if (!PyString_Check(PyTuple_GetItem(args, 1)))
    {
      PyErr_SetString(PyExc_TypeError, "Expected a string for second argument");
    }
    name = PyString_AsString(PyTuple_GetItem(args, 1));
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  if (name)
  {
    CATCH({desc->pageOrder(idx, name);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    Py_RETURN_NONE;
  }
  else
  {
    std::string rv;
    
    CATCH({rv = desc->pageOrder(idx);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    return PyString_FromString(rv.c_str());
  }
}

PyObject* PyOFXParameterSetDescriptor_DefineIntParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::IntParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->defineIntParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXIntParameterDescriptorType, NULL);
  
  ofx::IntParameterDescriptor *tparam = (ofx::IntParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSetDescriptor_DefineInt2Param(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::Int2ParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->defineInt2Param(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXInt2ParameterDescriptorType, NULL);
  
  ofx::Int2ParameterDescriptor *tparam = (ofx::Int2ParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSetDescriptor_DefineInt3Param(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::Int3ParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->defineInt3Param(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXInt3ParameterDescriptorType, NULL);
  
  ofx::Int3ParameterDescriptor *tparam = (ofx::Int3ParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSetDescriptor_DefineDoubleParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::DoubleParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->defineDoubleParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXDoubleParameterDescriptorType, NULL);
  
  ofx::DoubleParameterDescriptor *tparam = (ofx::DoubleParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSetDescriptor_DefineDouble2Param(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::Double2ParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->defineDouble2Param(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXDouble2ParameterDescriptorType, NULL);
  
  ofx::Double2ParameterDescriptor *tparam = (ofx::Double2ParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSetDescriptor_DefineDouble3Param(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::Double3ParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->defineDouble3Param(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXDouble3ParameterDescriptorType, NULL);
  
  ofx::Double3ParameterDescriptor *tparam = (ofx::Double3ParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSetDescriptor_DefineBooleanParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::BooleanParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->defineBooleanParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXBooleanParameterDescriptorType, NULL);
  
  ofx::BooleanParameterDescriptor *tparam = (ofx::BooleanParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSetDescriptor_DefineRGBParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::RGBParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->defineRGBParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXRGBParameterDescriptorType, NULL);
  
  ofx::RGBParameterDescriptor *tparam = (ofx::RGBParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSetDescriptor_DefineRGBAParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::RGBAParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->defineRGBAParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXRGBAParameterDescriptorType, NULL);
  
  ofx::RGBAParameterDescriptor *tparam = (ofx::RGBAParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSetDescriptor_DefineChoiceParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::ChoiceParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->defineChoiceParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXChoiceParameterDescriptorType, NULL);
  
  ofx::ChoiceParameterDescriptor *tparam = (ofx::ChoiceParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSetDescriptor_DefineStringParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::StringParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->defineStringParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXStringParameterDescriptorType, NULL);
  
  ofx::StringParameterDescriptor *tparam = (ofx::StringParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSetDescriptor_DefineCustomParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::CustomParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->defineCustomParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXCustomParameterDescriptorType, NULL);
  
  ofx::CustomParameterDescriptor *tparam = (ofx::CustomParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSetDescriptor_DefineGroupParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::GroupParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->defineGroupParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXGroupParameterDescriptorType, NULL);
  
  ofx::GroupParameterDescriptor *tparam = (ofx::GroupParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSetDescriptor_DefinePageParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::PageParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->definePageParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXPageParameterDescriptorType, NULL);
  
  ofx::PageParameterDescriptor *tparam = (ofx::PageParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSetDescriptor_DefinePushButtonParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::PushButtonParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->definePushButtonParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXPushButtonParameterDescriptorType, NULL);
  
  ofx::PushButtonParameterDescriptor *tparam = (ofx::PushButtonParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

#ifdef OFX_API_1_2

PyObject* PyOFXParameterSetDescriptor_DefineParametricParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSetDescriptor *pdesc = (PyOFXParameterSetDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSetDescriptor *desc = (ofx::ParameterSetDescriptor*) pdesc->desc;
  
  ofx::ParametricParameterDescriptor param;
  
  bool failed = false;
  
  CATCH({param = desc->defineParametricParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXParametricParameterDescriptorType, NULL);
  
  ofx::ParametricParameterDescriptor *tparam = (ofx::ParametricParameterDescriptor*) ((PyOFXParameterDescriptor*)pparam)->desc;
  
  *tparam = param;
  
  return pparam;
}

#endif

static PyMethodDef PyOFXParameterSetDescriptor_Methods[] =
{
  {"pageOrderCount", PyOFXParameterSetDescriptor_PageOrderCount, METH_VARARGS, NULL},
  {"pageOrder", PyOFXParameterSetDescriptor_PageOrder, METH_VARARGS, NULL},
  {"defineIntParam", PyOFXParameterSetDescriptor_DefineIntParam, METH_VARARGS, NULL},
  {"defineInt2Param", PyOFXParameterSetDescriptor_DefineInt2Param, METH_VARARGS, NULL},
  {"defineInt3Param", PyOFXParameterSetDescriptor_DefineInt3Param, METH_VARARGS, NULL},
  {"defineDoubleParam", PyOFXParameterSetDescriptor_DefineDoubleParam, METH_VARARGS, NULL},
  {"defineDouble2Param", PyOFXParameterSetDescriptor_DefineDouble2Param, METH_VARARGS, NULL},
  {"defineDouble3Param", PyOFXParameterSetDescriptor_DefineDouble3Param, METH_VARARGS, NULL},
  {"defineChoiceParam", PyOFXParameterSetDescriptor_DefineChoiceParam, METH_VARARGS, NULL},
  {"defineStringParam", PyOFXParameterSetDescriptor_DefineStringParam, METH_VARARGS, NULL},
  {"defineCustomParam", PyOFXParameterSetDescriptor_DefineCustomParam, METH_VARARGS, NULL},
  {"defineBooleanParam", PyOFXParameterSetDescriptor_DefineBooleanParam, METH_VARARGS, NULL},
  {"defineRGBParam", PyOFXParameterSetDescriptor_DefineRGBParam, METH_VARARGS, NULL},
  {"defineRGBAParam", PyOFXParameterSetDescriptor_DefineRGBAParam, METH_VARARGS, NULL},
  {"defineGroupParam", PyOFXParameterSetDescriptor_DefineGroupParam, METH_VARARGS, NULL},
  {"definePageParam", PyOFXParameterSetDescriptor_DefinePageParam, METH_VARARGS, NULL},
  {"definePushButtonParam", PyOFXParameterSetDescriptor_DefinePushButtonParam, METH_VARARGS, NULL},
#ifdef OFX_API_1_2
  {"defineParametricParam", PyOFXParameterSetDescriptor_DefineParametricParam, METH_VARARGS, NULL},
#endif
  {NULL, NULL, 0, NULL}
};

// ---

PyObject* PyOFXParameterSet_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  //((PyOFXParameterSet*)self)->pset = new ofx::ParameterSet();
  ((PyOFXParameterSet*)self)->pset = 0;
  return self;
}

int PyOFXParameterSet_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

void PyOFXParameterSet_Delete(PyObject *self)
{
  //PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  //if (ppset->pset)
  //{
  //  delete ppset->pset;
  //}
  self->ob_type->tp_free(self);
}

PyObject* PyOFXParameterSet_GetHost(PyObject *self, void*)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  if (ppset->pset->host() == 0)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*) &PyOFXHostType, NULL);
    ((PyOFXHost*)rv)->host = ppset->pset->host();
    return rv;
  }
}

PyObject* PyOFXParameterSet_GetHandle(PyObject *self, void*)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  if (ppset->pset->handle() == 0)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*) &PyOFXHandleType, NULL);
    ((PyOFXHandle*)rv)->handle = (void*) ppset->pset->handle();
    return rv;
  }
}

PyObject* PyOFXParameterSet_GetProperties(PyObject *self, void*)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*) &PyOFXPropertySetType, NULL);
  ((PyOFXPropertySet*)rv)->pset = &(ppset->pset->properties());
  return rv;
}

#ifdef OFX_API_1_2

PyObject* PyOFXParameterSet_GetNeedsSyncing(PyObject *self, void*)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = ppset->pset->needsSyncing();}, failed);
  
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

int PyOFXParameterSet_SetNeedsSyncing(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({ppset->pset->needsSyncing(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

#endif

static PyGetSetDef PyOFXParameterSet_GetSeters[] =
{
  {(char*)"host", PyOFXParameterSet_GetHost, NULL, NULL, NULL},
  {(char*)"handle", PyOFXParameterSet_GetHandle, NULL, NULL, NULL},
  {(char*)"properties", PyOFXParameterSet_GetProperties, NULL, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"needsSyncing", PyOFXParameterSet_GetNeedsSyncing, PyOFXParameterSet_SetNeedsSyncing, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXParameterSet_PageOrderCount(PyObject *self, PyObject *)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = pset->pageOrderCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXParameterSet_PageOrder(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx;
  
  if (!PyArg_ParseTuple(args, "i", &idx))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  bool failed = false;
  
  std::string rv;
    
  CATCH({rv = pset->pageOrder(idx);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameterSet_BeginEdit(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  bool failed = false;
  
  CATCH({pset->beginEdit(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXParameterSet_EndEdit(PyObject *self, PyObject *)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  bool failed = false;
  
  CATCH({pset->endEdit();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXParameterSet_GetIntParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::IntParameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getIntParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXIntParameterType, NULL);
  
  ofx::IntParameter *tparam = (ofx::IntParameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSet_GetInt2Param(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::Int2Parameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getInt2Param(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXInt2ParameterType, NULL);
  
  ofx::Int2Parameter *tparam = (ofx::Int2Parameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSet_GetInt3Param(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::Int3Parameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getInt3Param(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXInt3ParameterType, NULL);
  
  ofx::Int3Parameter *tparam = (ofx::Int3Parameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSet_GetDoubleParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::DoubleParameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getDoubleParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXDoubleParameterType, NULL);
  
  ofx::DoubleParameter *tparam = (ofx::DoubleParameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSet_GetDouble2Param(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::Double2Parameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getDouble2Param(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXDouble2ParameterType, NULL);
  
  ofx::Double2Parameter *tparam = (ofx::Double2Parameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSet_GetDouble3Param(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::Double3Parameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getDouble3Param(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXDouble3ParameterType, NULL);
  
  ofx::Double3Parameter *tparam = (ofx::Double3Parameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSet_GetBooleanParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::BooleanParameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getBooleanParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXBooleanParameterType, NULL);
  
  ofx::BooleanParameter *tparam = (ofx::BooleanParameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSet_GetRGBParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::RGBParameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getRGBParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXRGBParameterType, NULL);
  
  ofx::RGBParameter *tparam = (ofx::RGBParameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSet_GetRGBAParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::RGBAParameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getRGBAParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXRGBAParameterType, NULL);
  
  ofx::RGBAParameter *tparam = (ofx::RGBAParameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSet_GetChoiceParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::ChoiceParameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getChoiceParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXChoiceParameterType, NULL);
  
  ofx::ChoiceParameter *tparam = (ofx::ChoiceParameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSet_GetStringParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::StringParameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getStringParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXStringParameterType, NULL);
  
  ofx::StringParameter *tparam = (ofx::StringParameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSet_GetCustomParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::CustomParameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getCustomParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXCustomParameterType, NULL);
  
  ofx::CustomParameter *tparam = (ofx::CustomParameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSet_GetGroupParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::GroupParameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getGroupParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXGroupParameterType, NULL);
  
  ofx::GroupParameter *tparam = (ofx::GroupParameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSet_GetPageParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::PageParameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getPageParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXPageParameterType, NULL);
  
  ofx::PageParameter *tparam = (ofx::PageParameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

PyObject* PyOFXParameterSet_GetPushButtonParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::PushButtonParameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getPushButtonParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXPushButtonParameterType, NULL);
  
  ofx::PushButtonParameter *tparam = (ofx::PushButtonParameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

#ifdef OFX_API_1_2

PyObject* PyOFXParameterSet_GetParametricParam(PyObject *self, PyObject *args)
{
  PyOFXParameterSet *ppset = (PyOFXParameterSet*) self;
  
  if (!ppset->pset)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::ParameterSet *pset = (ofx::ParameterSet*) ppset->pset;
  
  ofx::ParametricParameter param;
  
  bool failed = false;
  
  CATCH({param = pset->getParametricParam(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pparam = PyObject_CallObject((PyObject*) &PyOFXParametricParameterType, NULL);
  
  ofx::ParametricParameter *tparam = (ofx::ParametricParameter*) ((PyOFXParameterSet*)pparam)->pset;
  
  *tparam = param;
  
  return pparam;
}

#endif

static PyMethodDef PyOFXParameterSet_Methods[] =
{
  {"pageOrderCount", PyOFXParameterSet_PageOrderCount, METH_VARARGS, NULL},
  {"pageOrder", PyOFXParameterSet_PageOrder, METH_VARARGS, NULL},
  {"beginEdit", PyOFXParameterSet_BeginEdit, METH_VARARGS, NULL},
  {"endEdit", PyOFXParameterSet_EndEdit, METH_VARARGS, NULL},
  {"getIntParam", PyOFXParameterSet_GetIntParam, METH_VARARGS, NULL},
  {"getInt2Param", PyOFXParameterSet_GetInt2Param, METH_VARARGS, NULL},
  {"getInt3Param", PyOFXParameterSet_GetInt3Param, METH_VARARGS, NULL},
  {"getDoubleParam", PyOFXParameterSet_GetDoubleParam, METH_VARARGS, NULL},
  {"getDouble2Param", PyOFXParameterSet_GetDouble2Param, METH_VARARGS, NULL},
  {"getDouble3Param", PyOFXParameterSet_GetDouble3Param, METH_VARARGS, NULL},
  {"getChoiceParam", PyOFXParameterSet_GetChoiceParam, METH_VARARGS, NULL},
  {"getStringParam", PyOFXParameterSet_GetStringParam, METH_VARARGS, NULL},
  {"getCustomParam", PyOFXParameterSet_GetCustomParam, METH_VARARGS, NULL},
  {"getBooleanParam", PyOFXParameterSet_GetBooleanParam, METH_VARARGS, NULL},
  {"getRGBParam", PyOFXParameterSet_GetRGBParam, METH_VARARGS, NULL},
  {"getRGBAParam", PyOFXParameterSet_GetRGBAParam, METH_VARARGS, NULL},
  {"getGroupParam", PyOFXParameterSet_GetGroupParam, METH_VARARGS, NULL},
  {"getPageParam", PyOFXParameterSet_GetPageParam, METH_VARARGS, NULL},
  {"getPushButtonParam", PyOFXParameterSet_GetPushButtonParam, METH_VARARGS, NULL},
#ifdef OFX_API_1_2
  {"getParametricParam", PyOFXParameterSet_GetParametricParam, METH_VARARGS, NULL},
#endif
  {NULL, NULL, 0, NULL}
};

// ---

bool PyOFX_InitParameterSet(PyObject *mod)
{
  INIT_TYPE(PyOFXParameterSetDescriptorType, "ofx.ParameterSetDescriptor", PyOFXParameterSetDescriptor);
  PyOFXParameterSetDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXParameterSetDescriptorType.tp_new = PyOFXParameterSetDescriptor_New;
  PyOFXParameterSetDescriptorType.tp_init = PyOFXParameterSetDescriptor_Init;
  PyOFXParameterSetDescriptorType.tp_dealloc = PyOFXParameterSetDescriptor_Delete;
  PyOFXParameterSetDescriptorType.tp_getset = PyOFXParameterSetDescriptor_GetSeters;
  PyOFXParameterSetDescriptorType.tp_methods = PyOFXParameterSetDescriptor_Methods;
  if (PyType_Ready(&PyOFXParameterSetDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXParameterSetType, "ofx.ParameterSet", PyOFXParameterSet);
  PyOFXParameterSetType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXParameterSetType.tp_new = PyOFXParameterSet_New;
  PyOFXParameterSetType.tp_init = PyOFXParameterSet_Init;
  PyOFXParameterSetType.tp_dealloc = PyOFXParameterSet_Delete;
  PyOFXParameterSetType.tp_getset = PyOFXParameterSet_GetSeters;
  PyOFXParameterSetType.tp_methods = PyOFXParameterSet_Methods;
  if (PyType_Ready(&PyOFXParameterSetType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXParameterSetDescriptorType);
  PyModule_AddObject(mod, "ParameterSetDescriptor", (PyObject*)&PyOFXParameterSetDescriptorType);
  
  Py_INCREF(&PyOFXParameterSetType);
  PyModule_AddObject(mod, "ParameterSet", (PyObject*)&PyOFXParameterSetType);
  
  return true;
}
