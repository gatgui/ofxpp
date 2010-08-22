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

PyTypeObject PyOFXParameterDescriptorType;
PyTypeObject PyOFXValueParameterDescriptorType;
PyTypeObject PyOFXParameterType;
PyTypeObject PyOFXValueParameterType;

// ---

PyObject* PyOFXParameterDescriptor_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  ((PyOFXParameterDescriptor*)self)->desc = 0;
  return self;
}

int PyOFXParameterDescriptor_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

void PyOFXParameterDescriptor_Delete(PyObject *self)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  if (pdesc->desc)
  {
    delete pdesc->desc;
  }
  self->ob_type->tp_free(self);
}

PyObject* PyOFXParameterDescriptor_GetName(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->name();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameterDescriptor_GetLabel(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->label();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameterDescriptor_GetShortLabel(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->shortLabel();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameterDescriptor_GetLongLabel(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->longLabel();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameterDescriptor_GetType(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  ofx::ParamType rv = ofx::MaxParamType;
  
  CATCH({rv = pdesc->desc->type();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(long(rv));
}

PyObject* PyOFXParameterDescriptor_GetSecret(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->secret();}, failed);
  
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

PyObject* PyOFXParameterDescriptor_GetCanUndo(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->canUndo();}, failed);
  
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

PyObject* PyOFXParameterDescriptor_GetHint(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->hint();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameterDescriptor_GetScriptName(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->scriptName();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameterDescriptor_GetParent(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->parent();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameterDescriptor_GetEnabled(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->enabled();}, failed);
  
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

/*
PyObject* PyOFXParameterDescriptor_GetData(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  void *rv;
  
  CATCH({rv = pdesc->desc->data();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return ((PyObject*) rv);
}
*/

#ifdef OFX_API_1_2

PyObject* PyOFXParameterDescriptor_GetPNGIcon(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->PNGIcon();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameterDescriptor_GetSVGIcon(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->SVGIcon();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

#endif

int PyOFXParameterDescriptor_SetName(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->name(PyString_AsString(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXParameterDescriptor_SetLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->label(PyString_AsString(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXParameterDescriptor_SetShortLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->shortLabel(PyString_AsString(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXParameterDescriptor_SetLongLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->longLabel(PyString_AsString(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXParameterDescriptor_SetHint(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->hint(PyString_AsString(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXParameterDescriptor_SetScriptName(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->scriptName(PyString_AsString(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXParameterDescriptor_SetParent(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->parent(PyString_AsString(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

/*
int PyOFXParameterDescriptor_SetData(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->data((void*)val);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}
*/

int PyOFXParameterDescriptor_SetEnabled(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->enabled(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXParameterDescriptor_SetCanUndo(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->canUndo(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXParameterDescriptor_SetSecret(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->secret(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

#ifdef OFX_API_1_2

int PyOFXParameterDescriptor_SetPNGIcon(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->PNGIcon(PyString_AsString(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXParameterDescriptor_SetSVGIcon(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->SVGIcon(PyString_AsString(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

#endif

static PyGetSetDef PyOFXParameterDescriptor_GetSeters[] =
{
  {(char*)"name", PyOFXParameterDescriptor_GetName, PyOFXParameterDescriptor_SetName, NULL, NULL},
  {(char*)"label", PyOFXParameterDescriptor_GetLabel, PyOFXParameterDescriptor_SetLabel, NULL, NULL},
  {(char*)"shortLabel", PyOFXParameterDescriptor_GetShortLabel, PyOFXParameterDescriptor_SetShortLabel, NULL, NULL},
  {(char*)"longLabel", PyOFXParameterDescriptor_GetLongLabel, PyOFXParameterDescriptor_SetLongLabel, NULL, NULL},
  {(char*)"type", PyOFXParameterDescriptor_GetType, NULL, NULL, NULL},
  {(char*)"hint", PyOFXParameterDescriptor_GetHint, PyOFXParameterDescriptor_SetHint, NULL, NULL},
  {(char*)"parent", PyOFXParameterDescriptor_GetParent, PyOFXParameterDescriptor_SetParent, NULL, NULL},
  {(char*)"scriptName", PyOFXParameterDescriptor_GetScriptName, PyOFXParameterDescriptor_SetScriptName, NULL, NULL},
  //{(char*)"data", PyOFXParameterDescriptor_GetData, PyOFXParameterDescriptor_SetData, NULL, NULL},
  {(char*)"enabled", PyOFXParameterDescriptor_GetEnabled, PyOFXParameterDescriptor_SetEnabled, NULL, NULL},
  {(char*)"secret", PyOFXParameterDescriptor_GetSecret, PyOFXParameterDescriptor_SetSecret, NULL, NULL},
  {(char*)"canUndo", PyOFXParameterDescriptor_GetCanUndo, PyOFXParameterDescriptor_SetCanUndo, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"PNGIcon", PyOFXParameterDescriptor_GetPNGIcon, PyOFXParameterDescriptor_SetPNGIcon, NULL, NULL},
  {(char*)"SVGIcon", PyOFXParameterDescriptor_GetSVGIcon, PyOFXParameterDescriptor_SetSVGIcon, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

// ----

int PyOFXValueParameterDescriptor_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

/*
template <class PluginClass, class DescriptorClass, class InstanceClass>
OfxStatus InteractEntryPoint(const char *action,
                             const void *handle,
                             OfxPropertySetHandle hInArgs,
                             OfxPropertySetHandle);
*/

PyObject* PyOFXValueParameterDescriptor_GetInteract(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  //ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  // typedef OfxStatus (*EntryPoint)(const char*, const void*, OfxPropertySetHandle, OfxPropertySetHandle);
  //ofx::EntryPoint interact = desc->interact();
  
  // -> wrap as a python method?
  
  Py_INCREF(Py_None);
  return Py_None;
}

/*
PyObject* PyOFXValueParameterDescriptor_GetInteractSize(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  double w, h;
  
  bool failed = false;
  
  CATCH({desc->interactSize(&w, &h);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyTuple_New(2);
  PyTuple_SetItem(rv, 0, PyFloat_FromDouble(w));
  PyTuple_SetItem(rv, 1, PyFloat_FromDouble(h));
  return rv;
}
*/

PyObject* PyOFXValueParameterDescriptor_GetInteractSizeAspect(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double rv = 0.0;
  
  CATCH({rv = desc->interactSizeAspect();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXValueParameterDescriptor_GetInteractMinimumSize(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
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

PyObject* PyOFXValueParameterDescriptor_GetInteractPreferedSize(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
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

PyObject* PyOFXValueParameterDescriptor_GetAnimates(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = desc->animates();}, failed);
  
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

/*
PyObject* PyOFXValueParameterDescriptor_GetAnimating(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  bool rv;
  
  CATCH({rv = desc->animating();}, failed);
  
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

PyObject* PyOFXValueParameterDescriptor_GetAutoKeying(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  bool rv;
  
  CATCH({rv = desc->autoKeying();}, failed);
  
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
*/

PyObject* PyOFXValueParameterDescriptor_GetPersistant(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = desc->persistant();}, failed);
  
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

PyObject* PyOFXValueParameterDescriptor_GetEvaluateOnChange(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = desc->evaluateOnChange();}, failed);
  
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

PyObject* PyOFXValueParameterDescriptor_GetPluginMayWrite(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = desc->pluginMayWrite();}, failed);
  
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

PyObject* PyOFXValueParameterDescriptor_GetCacheInvalidation(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  ofx::ParamInvalidate rv = ofx::MaxParamInvalidate;
  
  CATCH({rv = desc->cacheInvalidation();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(long(rv));
}

#ifdef OFX_API_1_2

PyObject* PyOFXValueParameterDescriptor_GetHasHostOverlayHandle(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
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

PyObject* PyOFXValueParameterDescriptor_GetUseHostOverlayHandle(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
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

#endif

/*
int PyOFXValueParameterDescriptor_SetInteractSize(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
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
  
  double w = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double h = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  
  bool failed = false;
  
  CATCH({desc->interactSize(w, h);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}
*/

int PyOFXValueParameterDescriptor_SetInteractSizeAspect(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->interactSizeAspect(PyFloat_AsDouble(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXValueParameterDescriptor_SetInteractMinimumSize(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
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

int PyOFXValueParameterDescriptor_SetInteractPreferedSize(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
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

int PyOFXValueParameterDescriptor_SetAnimates(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->animates(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

/*
int PyOFXValueParameterDescriptor_SetAnimating(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->animating(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXValueParameterDescriptor_SetAutoKeying(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->autoKeying(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}
*/

int PyOFXValueParameterDescriptor_SetPersistant(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->persistant(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXValueParameterDescriptor_SetEvaluateOnChange(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->evaluateOnChange(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXValueParameterDescriptor_SetPluginMayWrite(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->pluginMayWrite(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXValueParameterDescriptor_SetCacheInvalidation(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->cacheInvalidation(ofx::ParamInvalidate(PyInt_AsLong(val)));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

#ifdef OFX_API_1_2

int PyOFXValueParameterDescriptor_SetUseHostOverlayHandle(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->useHostOverlayHandle(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

#endif

int PyOFXValueParameterDescriptor_SetInteract(PyObject *self, PyObject *, void*)
{
  // val is a callable
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  //ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->desc;
  
  return 0;
}

static PyGetSetDef PyOFXValueParameterDescriptor_GetSeters[] =
{
  {(char*)"interact", PyOFXValueParameterDescriptor_GetInteract, PyOFXValueParameterDescriptor_SetInteract, NULL, NULL},
  //{(char*)"interactSize", PyOFXValueParameterDescriptor_GetInteractSize, PyOFXValueParameterDescriptor_SetInteractSize, NULL, NULL},
  {(char*)"interactSizeAspect", PyOFXValueParameterDescriptor_GetInteractSizeAspect, PyOFXValueParameterDescriptor_SetInteractSizeAspect, NULL, NULL},
  {(char*)"interactMinimumSize", PyOFXValueParameterDescriptor_GetInteractMinimumSize, PyOFXValueParameterDescriptor_SetInteractMinimumSize, NULL, NULL},
  {(char*)"interactPreferedSize", PyOFXValueParameterDescriptor_GetInteractPreferedSize, PyOFXValueParameterDescriptor_SetInteractPreferedSize, NULL, NULL},
  {(char*)"animates", PyOFXValueParameterDescriptor_GetAnimates, PyOFXValueParameterDescriptor_SetAnimates, NULL, NULL},
  //{(char*)"animating", PyOFXValueParameterDescriptor_GetAnimating, PyOFXValueParameterDescriptor_SetAnimating, NULL, NULL},
  //{(char*)"autoKeying", PyOFXValueParameterDescriptor_GetAutoKeying, PyOFXValueParameterDescriptor_SetAutoKeying, NULL, NULL},
  {(char*)"persistant", PyOFXValueParameterDescriptor_GetPersistant, PyOFXValueParameterDescriptor_SetPersistant, NULL, NULL},
  {(char*)"evaluateOnChange", PyOFXValueParameterDescriptor_GetEvaluateOnChange, PyOFXValueParameterDescriptor_SetEvaluateOnChange, NULL, NULL},
  {(char*)"pluginMayWrite", PyOFXValueParameterDescriptor_GetPluginMayWrite, PyOFXValueParameterDescriptor_SetPluginMayWrite, NULL, NULL},
  {(char*)"cacheInvalidation", PyOFXValueParameterDescriptor_GetCacheInvalidation, PyOFXValueParameterDescriptor_SetCacheInvalidation, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"hasHostOverlayHandle", PyOFXValueParameterDescriptor_GetHasHostOverlayHandle, NULL, NULL, NULL},
  {(char*)"useHostOverlayHandle", PyOFXValueParameterDescriptor_GetUseHostOverlayHandle, PyOFXValueParameterDescriptor_SetUseHostOverlayHandle, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXParameter_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  ((PyOFXParameter*)self)->param = 0;
  return self;
}

int PyOFXParameter_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

void PyOFXParameter_Delete(PyObject *self)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  if (pparam->param)
  {
    delete pparam->param;
  }
  self->ob_type->tp_free(self);
}

PyObject* PyOFXParameter_GetHandle(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  OfxParamHandle hdl = pparam->param->handle();
  
  if (failed)
  {
    return NULL;
  }
  
  if (!hdl)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXHandleType, NULL);
    ((PyOFXHandle*)rv)->handle = (void*) hdl;
    return rv;
  }
}

PyObject* PyOFXParameter_GetName(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return 0;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pparam->param->name();}, failed);
  
  if (failed)
  {
    return 0;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameter_GetLabel(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return 0;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pparam->param->label();}, failed);
  
  if (failed)
  {
    return 0;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameter_GetShortLabel(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return 0;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pparam->param->shortLabel();}, failed);
  
  if (failed)
  {
    return 0;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameter_GetLongLabel(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return 0;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pparam->param->longLabel();}, failed);
  
  if (failed)
  {
    return 0;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameter_GetHint(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return 0;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pparam->param->hint();}, failed);
  
  if (failed)
  {
    return 0;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameter_GetScriptName(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return 0;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pparam->param->scriptName();}, failed);
  
  if (failed)
  {
    return 0;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameter_GetParent(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return 0;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pparam->param->parent();}, failed);
  
  if (failed)
  {
    return 0;
  }
  
  return PyString_FromString(rv.c_str());
}

#ifdef OFX_API_1_2

PyObject* PyOFXParameter_GetPNGIcon(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return 0;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pparam->param->PNGIcon();}, failed);
  
  if (failed)
  {
    return 0;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParameter_GetSVGIcon(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return 0;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pparam->param->SVGIcon();}, failed);
  
  if (failed)
  {
    return 0;
  }
  
  return PyString_FromString(rv.c_str());
}

#endif

PyObject* PyOFXParameter_GetData(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return 0;
  }
  
  bool failed = false;
  
  void *rv = 0;
  
  CATCH({rv = pparam->param->data();}, failed);
  
  if (failed)
  {
    return 0;
  }
  
  if (!rv)
  {
    Py_RETURN_NONE;
  }
  else
  {
    return (PyObject*)rv;
  }
}

PyObject* PyOFXParameter_GetType(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return 0;
  }
  
  bool failed = false;
  
  ofx::ParamType rv = ofx::MaxParamType;
  
  CATCH({rv = pparam->param->type();}, failed);
  
  if (failed)
  {
    return 0;
  }
  
  return PyInt_FromLong(long(rv));
}

PyObject* PyOFXParameter_GetSecret(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return 0;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pparam->param->secret();}, failed);
  
  if (failed)
  {
    return 0;
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

PyObject* PyOFXParameter_GetCanUndo(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return 0;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pparam->param->canUndo();}, failed);
  
  if (failed)
  {
    return 0;
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

PyObject* PyOFXParameter_GetEnabled(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return 0;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pparam->param->enabled();}, failed);
  
  if (failed)
  {
    return 0;
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

int PyOFXParameter_SetLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pparam->param->label(PyString_AsString(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXParameter_SetShortLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pparam->param->shortLabel(PyString_AsString(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXParameter_SetLongLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pparam->param->longLabel(PyString_AsString(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXParameter_SetHint(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pparam->param->hint(PyString_AsString(val));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXParameter_SetEnabled(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pparam->param->enabled(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXParameter_SetSecret(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pparam->param->secret(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

int PyOFXParameter_SetData(PyObject *self, PyObject *val, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pparam->param->data((void*)val);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXParameter_GetSeters[] = 
{
  {(char*)"name", PyOFXParameter_GetName, NULL, NULL, NULL},
  {(char*)"type", PyOFXParameter_GetType, NULL, NULL, NULL},
  {(char*)"parent", PyOFXParameter_GetParent, NULL, NULL, NULL},
  {(char*)"handle", PyOFXParameter_GetHandle, NULL, NULL, NULL},
  {(char*)"scriptName", PyOFXParameter_GetScriptName, NULL, NULL, NULL},
  {(char*)"canUndo", PyOFXParameter_GetCanUndo, NULL, NULL, NULL},
  {(char*)"label", PyOFXParameter_GetLabel, PyOFXParameter_SetLabel, NULL, NULL},
  {(char*)"shortLabel", PyOFXParameter_GetShortLabel, PyOFXParameter_SetShortLabel, NULL, NULL},
  {(char*)"longLabel", PyOFXParameter_GetLongLabel, PyOFXParameter_SetLongLabel, NULL, NULL},
  {(char*)"hint", PyOFXParameter_GetHint, PyOFXParameter_SetHint, NULL, NULL},
  {(char*)"data", PyOFXParameter_GetData, PyOFXParameter_SetData, NULL, NULL},
  {(char*)"enabled", PyOFXParameter_GetEnabled, PyOFXParameter_SetEnabled, NULL, NULL},
  {(char*)"secret", PyOFXParameter_GetSecret, PyOFXParameter_SetSecret, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"PNGIcon", PyOFXParameter_GetPNGIcon, NULL, NULL, NULL},
  {(char*)"SVGIcon", PyOFXParameter_GetSVGIcon, NULL, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXValueParameter_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

PyObject* PyOFXValueParameter_GetInteract(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  //ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* PyOFXValueParameter_GetInteractSize(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  bool failed = false;
  
  double w, h;
  
  CATCH({param->interactSize(&w, &h);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyTuple_New(2);
  PyTuple_SetItem(rv, 0, PyFloat_FromDouble(w));
  PyTuple_SetItem(rv, 1, PyFloat_FromDouble(h));
  return rv;
}

PyObject* PyOFXValueParameter_GetInteractSizeAspect(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  bool failed = false;
  
  double rv = 0.0;
  
  CATCH({rv = param->interactSizeAspect();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXValueParameter_GetInteractMinimumSize(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  bool failed = false;
  
  int w, h;
  
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

PyObject* PyOFXValueParameter_GetInteractPreferedSize(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  bool failed = false;
  
  int w, h;
  
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

PyObject* PyOFXValueParameter_GetAnimates(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = param->animates();}, failed);
  
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

PyObject* PyOFXValueParameter_GetAnimating(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = param->animating();}, failed);
  
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

PyObject* PyOFXValueParameter_GetAutoKeying(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = param->autoKeying();}, failed);
  
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

PyObject* PyOFXValueParameter_GetPersistant(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = param->persistant();}, failed);
  
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

PyObject* PyOFXValueParameter_GetEvaluateOnChange(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = param->evaluateOnChange();}, failed);
  
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

PyObject* PyOFXValueParameter_GetPluginMayWrite(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = param->pluginMayWrite();}, failed);
  
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

PyObject* PyOFXValueParameter_GetCacheInvalidation(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  bool failed = false;
  
  ofx::ParamInvalidate rv = ofx::MaxParamInvalidate;
  
  CATCH({rv = param->cacheInvalidation();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(long(rv));
}

#ifdef OFX_API_1_2

PyObject* PyOFXValueParameter_GetUseHostOverlayHandle(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
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

static PyGetSetDef PyOFXValueParameter_GetSeters[] =
{
  {(char*)"interact", PyOFXValueParameter_GetInteract, NULL, NULL, NULL},
  {(char*)"interactSize", PyOFXValueParameter_GetInteractSize, NULL, NULL, NULL},
  {(char*)"interactSizeAspect", PyOFXValueParameter_GetInteractSizeAspect, NULL, NULL, NULL},
  {(char*)"interactMinimumSize", PyOFXValueParameter_GetInteractMinimumSize, NULL, NULL, NULL},
  {(char*)"interactPreferedSize", PyOFXValueParameter_GetInteractPreferedSize, NULL, NULL, NULL},
  {(char*)"animates", PyOFXValueParameter_GetAnimates, NULL, NULL, NULL},
  {(char*)"animating", PyOFXValueParameter_GetAnimating, NULL, NULL, NULL},
  {(char*)"autoKeying", PyOFXValueParameter_GetAutoKeying, NULL, NULL, NULL},
  {(char*)"persistant", PyOFXValueParameter_GetPersistant, NULL, NULL, NULL},
  {(char*)"evaluateOnChange", PyOFXValueParameter_GetEvaluateOnChange, NULL, NULL, NULL},
  {(char*)"pluginMayWrite", PyOFXValueParameter_GetPluginMayWrite, NULL, NULL, NULL},
  {(char*)"cacheInvalidation", PyOFXValueParameter_GetCacheInvalidation, NULL, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"useHostOverlayHandle", PyOFXValueParameter_GetUseHostOverlayHandle, NULL, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXValueParameter_GetNumKeys(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  bool failed = false;
  
  unsigned int rv = 0;
  
  CATCH({rv = param->getNumKeys();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(long(rv));
}

PyObject* PyOFXValueParameter_GetKeyTime(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  unsigned int nth;
  
  if (!PyArg_ParseTuple(args, "I", &nth))
  {
    return NULL;
  }
  
  bool failed = false;
  
  ofx::Time rv = 0.0;
  
  CATCH({rv = param->getKeyTime(nth);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXValueParameter_GetKeyIndex(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  double t;
  int d = int(ofx::KeyDirectionExact);
  
  if (!PyArg_ParseTuple(args, "d|i", &t, &d))
  {
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->getKeyIndex(t, ofx::KeyDirection(d));}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXValueParameter_DeleteKey(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  double t;
  
  if (!PyArg_ParseTuple(args, "d", &t))
  {
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = param->deleteKey(t);}, failed);
  
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

PyObject* PyOFXValueParameter_DeleteAllKeys(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->deleteAllKeys();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* PyOFXValueParameter_Copy(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameter *param = (ofx::ValueParameter*) pparam->param;
  
  PyObject *pfrom = 0;
  double offset = 0.0;
  PyObject *prange = 0;
  
  if (!PyArg_ParseTuple(args, "Od|O", &pfrom, &offset, &prange))
  {
    
  }
  
  ofx::ValueParameter *from = 0;
  
  if (!PyObject_TypeCheck(pfrom, &PyOFXValueParameterType))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a ofx.ValueParameter object");
    return NULL;
  }
  
  from = (ofx::ValueParameter*) (((PyOFXValueParameter*) pfrom)->base.param);
  
  ofx::FrameRange *range = 0;
  ofx::FrameRange _range;
  
  if (prange)
  {
    if (!PyTuple_Check(prange))
    {
      PyErr_SetString(PyExc_TypeError, "Expected a tuple");
      return NULL;
    }
    if (PyTuple_Size(prange) != 2)
    {
      PyErr_SetString(PyExc_ValueError, "Expected a tuple of two values");
      return NULL;
    }
    range = &_range;
    range->min = PyFloat_AsDouble(PyTuple_GetItem(prange, 0));
    range->max = PyFloat_AsDouble(PyTuple_GetItem(prange, 1));
  }
  
  bool failed = false;
  
  CATCH({param->copy(*from, offset, range);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyMethodDef PyOFXValueParameter_Methods[] =
{
  {"getNumKeys", PyOFXValueParameter_GetNumKeys, METH_VARARGS, NULL},
  {"getKeyTime", PyOFXValueParameter_GetKeyTime, METH_VARARGS, NULL},
  {"getKeyIndex", PyOFXValueParameter_GetKeyIndex, METH_VARARGS, NULL},
  {"deleteKey", PyOFXValueParameter_DeleteKey, METH_VARARGS, NULL},
  {"deleteAllKeys", PyOFXValueParameter_DeleteAllKeys, METH_VARARGS, NULL},
  {"copy", PyOFXValueParameter_Copy, METH_VARARGS, NULL},
  {NULL, NULL, NULL, NULL}
};

// ---

extern bool PyOFX_InitParameter_Boolean(PyObject *mod);
extern bool PyOFX_InitParameter_Choice(PyObject *mod);
extern bool PyOFX_InitParameter_Custom(PyObject *mod);
extern bool PyOFX_InitParameter_Double(PyObject *mod);
extern bool PyOFX_InitParameter_Double2(PyObject *mod);
extern bool PyOFX_InitParameter_Double3(PyObject *mod);
extern bool PyOFX_InitParameter_Int(PyObject *mod);
extern bool PyOFX_InitParameter_Int2(PyObject *mod);
extern bool PyOFX_InitParameter_Int3(PyObject *mod);
extern bool PyOFX_InitParameter_String(PyObject *mod);
extern bool PyOFX_InitParameter_Page(PyObject *mod);
extern bool PyOFX_InitParameter_RGB(PyObject *mod);
extern bool PyOFX_InitParameter_RGBA(PyObject *mod);
extern bool PyOFX_InitParameter_Group(PyObject *mod);
extern bool PyOFX_InitParameter_PushButton(PyObject *mod);
extern bool PyOFX_InitParameter_Parametric(PyObject *mod);

bool PyOFX_InitParameter(PyObject *mod)
{
  INIT_TYPE(PyOFXParameterDescriptorType, "ofx.ParameterDescriptor", PyOFXParameterDescriptor);
  PyOFXParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXParameterDescriptorType.tp_new = PyOFXParameterDescriptor_New;
  PyOFXParameterDescriptorType.tp_init = PyOFXParameterDescriptor_Init;
  PyOFXParameterDescriptorType.tp_dealloc = PyOFXParameterDescriptor_Delete;
  PyOFXParameterDescriptorType.tp_getset = PyOFXParameterDescriptor_GetSeters;
  if (PyType_Ready(&PyOFXParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXValueParameterDescriptorType, "ofx.ValueParameterDescriptor", PyOFXValueParameterDescriptor);
  PyOFXValueParameterDescriptorType.tp_base = &PyOFXParameterDescriptorType;
  PyOFXValueParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXValueParameterDescriptorType.tp_init = PyOFXValueParameterDescriptor_Init;
  PyOFXValueParameterDescriptorType.tp_getset = PyOFXValueParameterDescriptor_GetSeters;
  if (PyType_Ready(&PyOFXValueParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXParameterType, "ofx.Parameter", PyOFXParameter);
  PyOFXParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXParameterType.tp_new = PyOFXParameter_New;
  PyOFXParameterType.tp_init = PyOFXParameter_Init;
  PyOFXParameterType.tp_dealloc = PyOFXParameter_Delete;
  PyOFXParameterType.tp_getset = PyOFXParameter_GetSeters;
  if (PyType_Ready(&PyOFXParameterType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXValueParameterType, "ofx.ValueParameter", PyOFXValueParameter);
  PyOFXValueParameterType.tp_base = &PyOFXParameterType;
  PyOFXValueParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXValueParameterType.tp_init = PyOFXValueParameter_Init;
  PyOFXValueParameterType.tp_getset = PyOFXValueParameter_GetSeters;
  PyOFXValueParameterType.tp_methods = PyOFXValueParameter_Methods;
  if (PyType_Ready(&PyOFXValueParameterType) < 0)
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_Boolean(mod))
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_Choice(mod))
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_Custom(mod))
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_Double(mod))
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_Double2(mod))
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_Double3(mod))
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_Int(mod))
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_Int2(mod))
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_Int3(mod))
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_String(mod))
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_Page(mod))
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_RGB(mod))
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_RGBA(mod))
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_Group(mod))
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_PushButton(mod))
  {
    return false;
  }
  
  if (!PyOFX_InitParameter_Parametric(mod))
  {
    return false;
  }
  
  Py_INCREF(&PyOFXParameterDescriptorType);
  PyModule_AddObject(mod, "ParameterDescriptor", (PyObject*)&PyOFXParameterDescriptorType);
  
  Py_INCREF(&PyOFXValueParameterDescriptorType);
  PyModule_AddObject(mod, "ValueParameterDescriptor", (PyObject*)&PyOFXValueParameterDescriptorType);
  
  Py_INCREF(&PyOFXParameterType);
  PyModule_AddObject(mod, "Parameter", (PyObject*)&PyOFXParameterType);
  
  Py_INCREF(&PyOFXValueParameterType);
  PyModule_AddObject(mod, "ValueParameter", (PyObject*)&PyOFXValueParameterType);
  
  
  
  return true;
}
