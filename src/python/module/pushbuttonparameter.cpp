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
#include "entrypoints.h"

PyTypeObject PyOFXPushButtonParameterDescriptorType;
PyTypeObject PyOFXPushButtonParameterType;

// ---

int PyOFXPushButtonParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::PushButtonParameterDescriptor();
  return 0;
}

PyObject* PyOFXPushButtonParameterDescriptor_GetInteract(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::PushButtonParameterDescriptor *desc = (ofx::PushButtonParameterDescriptor*) pdesc->desc;
  
  ofx::EntryPoint func = 0;
  
  bool failed = false;
  
  CATCH({func = desc->interact();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyTuple_New(2);
  
  int idx = PyOFX_GetInteractFuncIndex(func);
  
  if (idx < 0 || idx >= PYOFX_MAX_ENTRY)
  {
    Py_INCREF(Py_None);
    PyTuple_SetItem(rv, 0, Py_None);
    
    Py_INCREF(Py_None);
    PyTuple_SetItem(rv, 1, Py_None);
  }
  else
  {
    Py_INCREF(gInteractDescClasses[idx]);
    PyTuple_SetItem(rv, 0, gInteractDescClasses[idx]);
    
    Py_INCREF(gInteractClasses[idx]);
    PyTuple_SetItem(rv, 1, gInteractClasses[idx]);
  }
  
  return rv;
}

int PyOFXPushButtonParameterDescriptor_SetInteract(PyObject *self, PyObject *val, void*)
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
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 2 elements");
    return -1;
  }
  
  PyObject *descClass = PyTuple_GetItem(val, 0);
  if (!PyObject_IsSubclass(descClass, (PyObject*)&PyOFXInteractDescriptorType))
  {
    PyErr_SetString(PyExc_TypeError, "Tuple first element must be a sub class of ofx.InteractDescriptor");
    return -1;
  }
  
  PyObject *instClass = PyTuple_GetItem(val, 1);
  if (!PyObject_IsSubclass(instClass, (PyObject*)&PyOFXInteractType))
  {
    PyErr_SetString(PyExc_TypeError, "Tuple second element must be a sub class of ofx.Interact");
    return -1;
  }
  
  ofx::PushButtonParameterDescriptor *desc = (ofx::PushButtonParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->interact(PyOFX_GetInteractFunc(descClass, instClass));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXPushButtonParameterDescriptor_GetInteractSizeAspect(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::PushButtonParameterDescriptor *desc = (ofx::PushButtonParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double rv = 0.0;
  
  CATCH({rv = desc->interactSizeAspect();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

int PyOFXPushButtonParameterDescriptor_SetInteractSizeAspect(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::PushButtonParameterDescriptor *desc = (ofx::PushButtonParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->interactSizeAspect(PyFloat_AsDouble(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXPushButtonParameterDescriptor_GetInteractMinimumSize(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::PushButtonParameterDescriptor *desc = (ofx::PushButtonParameterDescriptor*) pdesc->desc;
  
  int w, h;
  
  bool failed = false;
  
  CATCH({desc->interactMinimumSize(&w, &h);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyTuple_New(2);
  PyTuple_SetItem(rv, 0, PyInt_FromLong(w));
  PyTuple_SetItem(rv, 1, PyInt_FromLong(h));
  return rv;
}

int PyOFXPushButtonParameterDescriptor_SetInteractMinimumSize(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::PushButtonParameterDescriptor *desc = (ofx::PushButtonParameterDescriptor*) pdesc->desc;
  
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
  
  int w = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int h = PyInt_AsLong(PyTuple_GetItem(val, 1));
  
  bool failed = false;
  
  CATCH({desc->interactMinimumSize(w, h);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXPushButtonParameterDescriptor_GetInteractPreferedSize(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::PushButtonParameterDescriptor *desc = (ofx::PushButtonParameterDescriptor*) pdesc->desc;
  
  int w, h;
  
  bool failed = false;
  
  CATCH({desc->interactPreferedSize(&w, &h);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyTuple_New(2);
  PyTuple_SetItem(rv, 0, PyInt_FromLong(w));
  PyTuple_SetItem(rv, 1, PyInt_FromLong(h));
  return rv;
}

int PyOFXPushButtonParameterDescriptor_SetInteractPreferedSize(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::PushButtonParameterDescriptor *desc = (ofx::PushButtonParameterDescriptor*) pdesc->desc;
  
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
  
  int w = PyInt_AsLong(PyTuple_GetItem(val, 0));
  int h = PyInt_AsLong(PyTuple_GetItem(val, 1));
  
  bool failed = false;
  
  CATCH({desc->interactPreferedSize(w, h);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

#ifdef OFX_API_1_2

PyObject* PyOFXPushButtonParameterDescriptor_GetHasHostOverlayHandle(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::PushButtonParameterDescriptor *desc = (ofx::PushButtonParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = desc->hasHostOverlayHandle();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_INCREF(Py_True);
    return Py_True;
  }
  else
  {
    Py_INCREF(Py_False);
    return Py_False;
  }
}

PyObject* PyOFXPushButtonParameterDescriptor_GetUseHostOverlayHandle(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::PushButtonParameterDescriptor *desc = (ofx::PushButtonParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = desc->useHostOverlayHandle();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_INCREF(Py_True);
    return Py_True;
  }
  else
  {
    Py_INCREF(Py_False);
    return Py_False;
  }
}

int PyOFXPushButtonParameterDescriptor_SetUseHostOverlayHandle(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::PushButtonParameterDescriptor *desc = (ofx::PushButtonParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->useHostOverlayHandle(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

#endif

static PyGetSetDef PyOFXPushButtonParameterDescriptor_GetSeters[] =
{
  {(char*)"interact", PyOFXPushButtonParameterDescriptor_GetInteract, PyOFXPushButtonParameterDescriptor_SetInteract, NULL, NULL},
  {(char*)"interactSizeAspect", PyOFXPushButtonParameterDescriptor_GetInteractSizeAspect, PyOFXPushButtonParameterDescriptor_SetInteractSizeAspect, NULL, NULL},
  {(char*)"interactMinimumSize", PyOFXPushButtonParameterDescriptor_GetInteractMinimumSize, PyOFXPushButtonParameterDescriptor_SetInteractMinimumSize, NULL, NULL},
  {(char*)"interactPreferedSize", PyOFXPushButtonParameterDescriptor_GetInteractPreferedSize, PyOFXPushButtonParameterDescriptor_SetInteractPreferedSize, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"hasHostOverlayHandle", PyOFXPushButtonParameterDescriptor_GetHasHostOverlayHandle, NULL, NULL, NULL},
  {(char*)"useHostOverlayHandle", PyOFXPushButtonParameterDescriptor_GetUseHostOverlayHandle, PyOFXPushButtonParameterDescriptor_SetUseHostOverlayHandle, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXPushButtonParameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::PushButtonParameter();
  return 0;
}

PyObject* PyOFXPushButtonParameter_GetInteract(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::PushButtonParameter *param = (ofx::PushButtonParameter*) pparam->param;
  
  ofx::EntryPoint func = 0;
  
  bool failed = false;
  
  CATCH({func = param->interact();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyTuple_New(2);
  
  int idx = PyOFX_GetInteractFuncIndex(func);
  
  if (idx < 0 || idx >= PYOFX_MAX_ENTRY)
  {
    Py_INCREF(Py_None);
    PyTuple_SetItem(rv, 0, Py_None);
    
    Py_INCREF(Py_None);
    PyTuple_SetItem(rv, 1, Py_None);
  }
  else
  {
    Py_INCREF(gInteractDescClasses[idx]);
    PyTuple_SetItem(rv, 0, gInteractDescClasses[idx]);
    
    Py_INCREF(gInteractClasses[idx]);
    PyTuple_SetItem(rv, 1, gInteractClasses[idx]);
  }
  
  return rv;
}

PyObject* PyOFXPushButtonParameter_GetInteractSizeAspect(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::PushButtonParameter *param = (ofx::PushButtonParameter*) pparam->param;
  
  bool failed = false;
  
  double rv = 0.0;
  
  CATCH({rv = param->interactSizeAspect();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXPushButtonParameter_GetInteractSize(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::PushButtonParameter *param = (ofx::PushButtonParameter*) pparam->param;
  
  int w, h;
  
  bool failed = false;
  
  CATCH({param->interactMinimumSize(&w, &h);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyTuple_New(2);
  PyTuple_SetItem(rv, 0, PyInt_FromLong(w));
  PyTuple_SetItem(rv, 1, PyInt_FromLong(h));
  return rv;
}

PyObject* PyOFXPushButtonParameter_GetInteractMinimumSize(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::PushButtonParameter *param = (ofx::PushButtonParameter*) pparam->param;
  
  int w, h;
  
  bool failed = false;
  
  CATCH({param->interactMinimumSize(&w, &h);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyTuple_New(2);
  PyTuple_SetItem(rv, 0, PyInt_FromLong(w));
  PyTuple_SetItem(rv, 1, PyInt_FromLong(h));
  return rv;
}

PyObject* PyOFXPushButtonParameter_GetInteractPreferedSize(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::PushButtonParameter *param = (ofx::PushButtonParameter*) pparam->param;
  
  int w, h;
  
  bool failed = false;
  
  CATCH({param->interactPreferedSize(&w, &h);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyTuple_New(2);
  PyTuple_SetItem(rv, 0, PyInt_FromLong(w));
  PyTuple_SetItem(rv, 1, PyInt_FromLong(h));
  return rv;
}

#ifdef OFX_API_1_2

PyObject* PyOFXPushButtonParameter_GetUseHostOverlayHandle(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::PushButtonParameter *param = (ofx::PushButtonParameter*) pparam->param;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = param->useHostOverlayHandle();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_INCREF(Py_True);
    return Py_True;
  }
  else
  {
    Py_INCREF(Py_False);
    return Py_False;
  }
}

#endif

static PyGetSetDef PyOFXPushButtonParameter_GetSeters[] =
{
  {(char*)"interact", PyOFXPushButtonParameter_GetInteract, NULL, NULL, NULL},
  {(char*)"interactSizeAspect", PyOFXPushButtonParameter_GetInteractSizeAspect, NULL, NULL, NULL},
  {(char*)"interactSize", PyOFXPushButtonParameter_GetInteractSize, NULL, NULL, NULL},
  {(char*)"interactMinimumSize", PyOFXPushButtonParameter_GetInteractMinimumSize, NULL, NULL, NULL},
  {(char*)"interactPreferedSize", PyOFXPushButtonParameter_GetInteractPreferedSize, NULL, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"useHostOverlayHandle", PyOFXPushButtonParameter_GetUseHostOverlayHandle, NULL, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

bool PyOFX_InitParameter_PushButton(PyObject *mod)
{
  INIT_TYPE(PyOFXPushButtonParameterDescriptorType, "ofx.PushButtonParameterDescriptor", PyOFXPushButtonParameterDescriptor);
  PyOFXPushButtonParameterDescriptorType.tp_base = &PyOFXParameterDescriptorType;
  PyOFXPushButtonParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXPushButtonParameterDescriptorType.tp_init = PyOFXPushButtonParameterDescriptor_Init;
  PyOFXPushButtonParameterDescriptorType.tp_getset = PyOFXPushButtonParameterDescriptor_GetSeters;
  if (PyType_Ready(&PyOFXPushButtonParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXPushButtonParameterType, "ofx.PushButtonParameter", PyOFXPushButtonParameter);
  PyOFXPushButtonParameterType.tp_base = &PyOFXParameterType;
  PyOFXPushButtonParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXPushButtonParameterType.tp_init = PyOFXPushButtonParameter_Init;
  PyOFXPushButtonParameterType.tp_getset = PyOFXPushButtonParameter_GetSeters;
  if (PyType_Ready(&PyOFXPushButtonParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXPushButtonParameterDescriptorType);
  PyModule_AddObject(mod, "PushButtonParameterDescriptor", (PyObject*)&PyOFXPushButtonParameterDescriptorType);
  
  Py_INCREF(&PyOFXPushButtonParameterType);
  PyModule_AddObject(mod, "PushButtonParameter", (PyObject*)&PyOFXPushButtonParameterType);
  
  return true;
}
