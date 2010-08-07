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
/*
 =
{
  PyObject_HEAD_INIT(NULL)
  0,
  "ofx.ParameterDescriptor",
  sizeof(PyOFXParameterDescriptor),
  0
};
*/

PyTypeObject PyOFXValueParameterDescriptorType;
/*
 =
{
  PyObject_HEAD_INIT(NULL)
  0,
  "ofx.ValueParameterDescriptor",
  sizeof(PyOFXValueParameterDescriptor),
  0
};
*/

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
  
  return PyString_FromString(pdesc->desc->getName().c_str());
}

PyObject* PyOFXParameterDescriptor_GetLabel(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyString_FromString(pdesc->desc->getLabel().c_str());
}

PyObject* PyOFXParameterDescriptor_GetShortLabel(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyString_FromString(pdesc->desc->getShortLabel().c_str());
}

PyObject* PyOFXParameterDescriptor_GetLongLabel(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyString_FromString(pdesc->desc->getLongLabel().c_str());
}

PyObject* PyOFXParameterDescriptor_GetType(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(pdesc->desc->getType());
}

PyObject* PyOFXParameterDescriptor_GetSecret(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  if (pdesc->desc->isSecret())
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
  
  if (pdesc->desc->canUndo())
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
  
  return PyString_FromString(pdesc->desc->getHint().c_str());
}

PyObject* PyOFXParameterDescriptor_GetScriptName(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyString_FromString(pdesc->desc->getScriptName().c_str());
}

PyObject* PyOFXParameterDescriptor_GetParent(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyString_FromString(pdesc->desc->getParent().c_str());
}

PyObject* PyOFXParameterDescriptor_GetEnable(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  if (pdesc->desc->isEnable())
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

PyObject* PyOFXParameterDescriptor_GetData(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return ((PyObject*) pdesc->desc->getData());
}

#ifdef OFX_API_1_2

PyObject* PyOFXParameterDescriptor_GetPNGIcon(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyString_FromString(pdesc->desc->getPNGIcon().c_str());
}

PyObject* PyOFXParameterDescriptor_GetSVGIcon(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyString_FromString(pdesc->desc->getSVGIcon().c_str());
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
  
  pdesc->desc->setName(PyString_AsString(val));
  
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
  
  pdesc->desc->setLabel(PyString_AsString(val));
  
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
  
  pdesc->desc->setShortLabel(PyString_AsString(val));
  
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
  
  pdesc->desc->setLongLabel(PyString_AsString(val));
  
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
  
  pdesc->desc->setHint(PyString_AsString(val));
  
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
  
  pdesc->desc->setScriptName(PyString_AsString(val));
  
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
  
  pdesc->desc->setParent(PyString_AsString(val));
  
  return 0;
}

int PyOFXParameterDescriptor_SetData(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  pdesc->desc->setData((void*)val);
  
  return 0;
}

int PyOFXParameterDescriptor_SetEnable(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  pdesc->desc->enable(val == Py_True);
  
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
  
  pdesc->desc->setCanUndo(val == Py_True);
  
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
  
  pdesc->desc->setSecret(val == Py_True);
  
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
  
  pdesc->desc->setPNGIcon(PyString_AsString(val));
  
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
  
  pdesc->desc->setSVGIcon(PyString_AsString(val));
  
  return 0;
}

#endif

static PyGetSetDef PyOFXParameterDescriptor_GetSeters[] =
{
  {(char*)"name", PyOFXParameterDescriptor_GetName, PyOFXParameterDescriptor_SetName, NULL, NULL},
  {(char*)"label", PyOFXParameterDescriptor_GetLabel, PyOFXParameterDescriptor_SetLabel, NULL, NULL},
  {(char*)"shortLabel", PyOFXParameterDescriptor_GetShortLabel, PyOFXParameterDescriptor_SetShortLabel, NULL, NULL},
  {(char*)"longLabel", PyOFXParameterDescriptor_GetLongLabel, PyOFXParameterDescriptor_SetLongLabel, NULL, NULL},
  {(char*)"hint", PyOFXParameterDescriptor_GetHint, PyOFXParameterDescriptor_SetHint, NULL, NULL},
  {(char*)"parent", PyOFXParameterDescriptor_GetParent, PyOFXParameterDescriptor_SetParent, NULL, NULL},
  {(char*)"scriptName", PyOFXParameterDescriptor_GetScriptName, PyOFXParameterDescriptor_SetScriptName, NULL, NULL},
  {(char*)"data", PyOFXParameterDescriptor_GetData, PyOFXParameterDescriptor_SetData, NULL, NULL},
  {(char*)"enable", PyOFXParameterDescriptor_GetEnable, PyOFXParameterDescriptor_SetEnable, NULL, NULL},
  {(char*)"secret", PyOFXParameterDescriptor_GetSecret, PyOFXParameterDescriptor_SetSecret, NULL, NULL},
  {(char*)"canUndo", PyOFXParameterDescriptor_GetCanUndo, PyOFXParameterDescriptor_SetCanUndo, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"pngIcon", PyOFXParameterDescriptor_GetPNGIcon, PyOFXParameterDescriptor_SetPNGIcon, NULL, NULL},
  {(char*)"svgIcon", PyOFXParameterDescriptor_GetSVGIcon, PyOFXParameterDescriptor_SetSVGIcon, NULL, NULL},
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
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  //ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  // typedef OfxStatus (*EntryPoint)(const char*, const void*, OfxPropertySetHandle, OfxPropertySetHandle);
  //ofx::EntryPoint interact = desc->getInteract();
  
  // -> wrap as a python method?
  
  Py_INCREF(Py_None);
  return Py_None;
}


PyObject* PyOFXValueParameterDescriptor_GetInteractSize(PyObject *self, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  double w, h;
  desc->getInteractSize(w, h);
  
  PyObject *rv = PyTuple_New(2);
  PyTuple_SetItem(rv, 0, PyFloat_FromDouble(w));
  PyTuple_SetItem(rv, 1, PyFloat_FromDouble(h));
  return rv;
}

PyObject* PyOFXValueParameterDescriptor_GetInteractSizeAspect(PyObject *self, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  return PyFloat_FromDouble(desc->getInteractSizeAspect());
}

PyObject* PyOFXValueParameterDescriptor_GetInteractMinSize(PyObject *self, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  int w, h;
  desc->getInteractMinSize(w, h);
  
  PyObject *rv = PyTuple_New(2);
  PyTuple_SetItem(rv, 0, PyInt_FromLong(w));
  PyTuple_SetItem(rv, 1, PyInt_FromLong(h));
  return rv;
}

PyObject* PyOFXValueParameterDescriptor_GetInteractPreferedSize(PyObject *self, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  int w, h;
  desc->getInteractPreferedSize(w, h);
  
  PyObject *rv = PyTuple_New(2);
  PyTuple_SetItem(rv, 0, PyInt_FromLong(w));
  PyTuple_SetItem(rv, 1, PyInt_FromLong(h));
  return rv;
}

PyObject* PyOFXValueParameterDescriptor_GetAnimateable(PyObject *self, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  PyObject *rv = (desc->isAnimateable() ? Py_True : Py_False);
  Py_INCREF(rv);
  return rv;
}

PyObject* PyOFXValueParameterDescriptor_GetAnimating(PyObject *self, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  PyObject *rv = (desc->isAnimating() ? Py_True : Py_False);
  Py_INCREF(rv);
  return rv;
}

PyObject* PyOFXValueParameterDescriptor_GetAutoKeying(PyObject *self, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  PyObject *rv = (desc->isAutoKeying() ? Py_True : Py_False);
  Py_INCREF(rv);
  return rv;
}

PyObject* PyOFXValueParameterDescriptor_GetPersistant(PyObject *self, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  PyObject *rv = (desc->isPersistant() ? Py_True : Py_False);
  Py_INCREF(rv);
  return rv;
}

PyObject* PyOFXValueParameterDescriptor_GetEvaluateOnChange(PyObject *self, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  PyObject *rv = (desc->evaluateOnChange() ? Py_True : Py_False);
  Py_INCREF(rv);
  return rv;
}

PyObject* PyOFXValueParameterDescriptor_GetPluginMayWrite(PyObject *self, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  PyObject *rv = (desc->mayPluginWrite() ? Py_True : Py_False);
  Py_INCREF(rv);
  return rv;
}

PyObject* PyOFXValueParameterDescriptor_GetCacheInvalidation(PyObject *self, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  return PyInt_FromLong(desc->getCacheInvalidation());
}

#ifdef OFX_API_1_2

PyObject* PyOFXValueParameterDescriptor_GetHasHostOverlayHandle(PyObject *self, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  PyObject *rv = (desc->hasHostOverlayHandle() ? Py_True : Py_False);
  Py_INCREF(rv);
  return rv;
}

PyObject* PyOFXValueParameterDescriptor_GetUseHostOverlayHandle(PyObject *self, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  PyObject *rv = (desc->useHostOverlayHandle() ? Py_True : Py_False);
  Py_INCREF(rv);
  return rv;
}

#endif

int PyOFXValueParameterDescriptor_SetInteractSize(PyObject *self, PyObject *val, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
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
  
  desc->setInteractSize(w, h);
  
  return 0;
}

int PyOFXValueParameterDescriptor_SetInteractSizeAspect(PyObject *self, PyObject *val, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  desc->setInteractSizeAspect(PyFloat_AsDouble(val));
  
  return 0;
}

int PyOFXValueParameterDescriptor_SetInteractMinSize(PyObject *self, PyObject *val, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
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
  
  desc->setInteractMinSize(w, h);
  
  return 0;
}

int PyOFXValueParameterDescriptor_SetInteractPreferedSize(PyObject *self, PyObject *val, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
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
  
  desc->setInteractPreferedSize(w, h);
  
  return 0;
}

int PyOFXValueParameterDescriptor_SetAnimateable(PyObject *self, PyObject *val, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  desc->setAnimateable(val == Py_True);
  
  return 0;
}

int PyOFXValueParameterDescriptor_SetAnimating(PyObject *self, PyObject *val, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  desc->setAnimating(val == Py_True);
  
  return 0;
}

int PyOFXValueParameterDescriptor_SetAutoKeying(PyObject *self, PyObject *val, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  desc->setAutoKeying(val == Py_True);
  
  return 0;
}

int PyOFXValueParameterDescriptor_SetPersistant(PyObject *self, PyObject *val, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  desc->setPersistant(val == Py_True);
  
  return 0;
}

int PyOFXValueParameterDescriptor_SetEvaluateOnChange(PyObject *self, PyObject *val, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  desc->setEvaluateOnChange(val == Py_True);
  
  return 0;
}

int PyOFXValueParameterDescriptor_SetPluginMayWrite(PyObject *self, PyObject *val, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  desc->setPluginMayWrite(val == Py_True);
  
  return 0;
}

int PyOFXValueParameterDescriptor_SetCacheInvalidation(PyObject *self, PyObject *val, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  desc->setCacheInvalidation(ofx::ParamInvalidate(PyInt_AsLong(val)));
  
  return 0;
}

#ifdef OFX_API_1_2

int PyOFXValueParameterDescriptor_SetUseHostOverlayHandle(PyObject *self, PyObject *val, void*)
{
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  desc->setUseHostOverlayHandle(val == Py_True);
  
  return 0;
}

#endif

int PyOFXValueParameterDescriptor_SetInteract(PyObject *self, PyObject *, void*)
{
  // val is a callable
  PyOFXValueParameterDescriptor *pdesc = (PyOFXValueParameterDescriptor*) self;
  
  if (!pdesc->base.desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  //ofx::ValueParameterDescriptor *desc = (ofx::ValueParameterDescriptor*) pdesc->base.desc;
  
  return 0;
}

static PyGetSetDef PyOFXValueParameterDescriptor_GetSeters[] =
{
  {(char*)"interact", PyOFXValueParameterDescriptor_GetInteract, PyOFXValueParameterDescriptor_SetInteract, NULL, NULL},
  {(char*)"interactSize", PyOFXValueParameterDescriptor_GetInteractSize, PyOFXValueParameterDescriptor_SetInteractSize, NULL, NULL},
  {(char*)"interactSizeAspect", PyOFXValueParameterDescriptor_GetInteractSizeAspect, PyOFXValueParameterDescriptor_SetInteractSizeAspect, NULL, NULL},
  {(char*)"interactMinSize", PyOFXValueParameterDescriptor_GetInteractMinSize, PyOFXValueParameterDescriptor_SetInteractMinSize, NULL, NULL},
  {(char*)"interactPreferedSize", PyOFXValueParameterDescriptor_GetInteractPreferedSize, PyOFXValueParameterDescriptor_SetInteractPreferedSize, NULL, NULL},
  {(char*)"animateable", PyOFXValueParameterDescriptor_GetAnimateable, PyOFXValueParameterDescriptor_SetAnimateable, NULL, NULL},
  {(char*)"animating", PyOFXValueParameterDescriptor_GetAnimating, PyOFXValueParameterDescriptor_SetAnimating, NULL, NULL},
  {(char*)"autoKeying", PyOFXValueParameterDescriptor_GetAutoKeying, PyOFXValueParameterDescriptor_SetAutoKeying, NULL, NULL},
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
  
  // add new types to module
  
  Py_INCREF(&PyOFXParameterDescriptorType);
  PyModule_AddObject(mod, "ParameterDescriptor", (PyObject*)&PyOFXParameterDescriptorType);
  
  Py_INCREF(&PyOFXValueParameterDescriptorType);
  PyModule_AddObject(mod, "ValueParameterDescriptor", (PyObject*)&PyOFXValueParameterDescriptorType);
  
  return true;
}
