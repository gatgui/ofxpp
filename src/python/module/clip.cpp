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

PyTypeObject PyOFXClipDescriptorType;
PyTypeObject PyOFXClipType;

// ---

PyObject* PyOFXClipDescriptor_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  ((PyOFXClipDescriptor*)self)->desc = new ofx::ClipDescriptor();
  return self;
}

int PyOFXClipDescriptor_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

void PyOFXClipDescriptor_Delete(PyObject *self)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  if (pdesc->desc)
  {
    delete pdesc->desc;
  }
  self->ob_type->tp_free(self);
}

PyObject* PyOFXClipDescriptor_GetHandle(PyObject *self, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  OfxPropertySetHandle hdl = pdesc->desc->handle();
  
  if (!hdl)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *phdl = PyObject_CallObject((PyObject*)&PyOFXHandleType, NULL);
    ((PyOFXHandle*)phdl)->handle = hdl;
    return phdl;
  }
}

PyObject* PyOFXClipDescriptor_GetName(PyObject *self, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
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

PyObject* PyOFXClipDescriptor_GetLabel(PyObject *self, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
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

int PyOFXClipDescriptor_SetLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
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
  
  char *v = PyString_AsString(val);
  
  CATCH({pdesc->desc->label(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXClipDescriptor_GetShortLabel(PyObject *self, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
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

int PyOFXClipDescriptor_SetShortLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
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
  
  char *v = PyString_AsString(val);
  
  CATCH({pdesc->desc->shortLabel(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXClipDescriptor_GetLongLabel(PyObject *self, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
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

int PyOFXClipDescriptor_SetLongLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
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
  
  char *v = PyString_AsString(val);
  
  CATCH({pdesc->desc->longLabel(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXClipDescriptor_GetTemporalClipAccess(PyObject *self, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->temporalClipAccess();}, failed);
  
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
    Py_RETURN_NONE;
  }
}

int PyOFXClipDescriptor_SetTemporalClipAccess(PyObject *self, PyObject *val, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->temporalClipAccess(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXClipDescriptor_GetOptional(PyObject *self, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->optional();}, failed);
  
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
    Py_RETURN_NONE;
  }
}

int PyOFXClipDescriptor_SetOptional(PyObject *self, PyObject *val, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->optional(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXClipDescriptor_GetIsMask(PyObject *self, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->isMask();}, failed);
  
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
    Py_RETURN_NONE;
  }
}

int PyOFXClipDescriptor_SetIsMask(PyObject *self, PyObject *val, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->isMask(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXClipDescriptor_GetSupportsTiles(PyObject *self, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->supportsTiles();}, failed);
  
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
    Py_RETURN_NONE;
  }
}

int PyOFXClipDescriptor_SetSupportsTiles(PyObject *self, PyObject *val, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->supportsTiles(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXClipDescriptor_GetFieldExtraction(PyObject *self, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(pdesc->desc->fieldExtraction());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXClipDescriptor_SetFieldExtraction(PyObject *self, PyObject *val, void*)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  
  bool failed = false;
  
  int v = PyInt_AsLong(val);
  
  CATCH({pdesc->desc->fieldExtraction(ofx::ImageFieldExtract(v));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXClipDescriptor_GetSeters[] =
{
  {(char*)"handle", PyOFXClipDescriptor_GetHandle, NULL, NULL, NULL},
  {(char*)"name", PyOFXClipDescriptor_GetName, NULL, NULL, NULL},
  {(char*)"label", PyOFXClipDescriptor_GetLabel, PyOFXClipDescriptor_SetLabel, NULL, NULL},
  {(char*)"shortLabel", PyOFXClipDescriptor_GetShortLabel, PyOFXClipDescriptor_SetShortLabel, NULL, NULL},
  {(char*)"longLabel", PyOFXClipDescriptor_GetLongLabel, PyOFXClipDescriptor_SetLongLabel, NULL, NULL},
  {(char*)"temporalClipAccess", PyOFXClipDescriptor_GetTemporalClipAccess, PyOFXClipDescriptor_SetTemporalClipAccess, NULL, NULL},
  {(char*)"optional", PyOFXClipDescriptor_GetOptional, PyOFXClipDescriptor_SetOptional, NULL, NULL},
  {(char*)"isMask", PyOFXClipDescriptor_GetIsMask, PyOFXClipDescriptor_SetIsMask, NULL, NULL},
  {(char*)"supportsTiles", PyOFXClipDescriptor_GetSupportsTiles, PyOFXClipDescriptor_SetSupportsTiles, NULL, NULL},
  {(char*)"fieldExtraction", PyOFXClipDescriptor_GetFieldExtraction, PyOFXClipDescriptor_SetFieldExtraction, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};


PyObject* PyOFXClipDescriptor_SupportedComponentsCount(PyObject *self, PyObject *)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = pdesc->desc->supportedComponentsCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXClipDescriptor_SupportedComponent(PyObject *self, PyObject *args)
{
  PyOFXClipDescriptor *pdesc = (PyOFXClipDescriptor*) self;
  
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
  PyObject *val = 0;
  
  if (nargs == 2)
  {
    val = PyTuple_GetItem(args, 1);
  }
  
  bool failed = false;
  
  if (val)
  {
    if (!PyInt_Check(val))
    {
      PyErr_SetString(PyExc_TypeError, "Expected an integer");
      return NULL;
    }
    
    int v = PyInt_AsLong(val);
    
    CATCH({pdesc->desc->supportedComponent(idx, ofx::ImageComponent(v));}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    Py_RETURN_NONE;
  }
  else
  {
    int rv = 0;
    
    CATCH({rv = int(pdesc->desc->supportedComponent(idx));}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    return PyInt_FromLong(rv);
  }
}

static PyMethodDef PyOFXClipDescriptor_Methods[] =
{
  {"supportedComponentsCount", PyOFXClipDescriptor_SupportedComponentsCount, METH_VARARGS, NULL},
  {"supportedComponent", PyOFXClipDescriptor_SupportedComponent, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

// ---

PyObject* PyOFXClip_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  ((PyOFXClip*)self)->clip = new ofx::Clip();
  return self;
}

int PyOFXClip_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

void PyOFXClip_Delete(PyObject *self)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  if (pclip->clip)
  {
    delete pclip->clip;
  }
  self->ob_type->tp_free(self);
}

PyObject* PyOFXClip_GetHost(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = pclip->clip->host();
  
  if (!host)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*) &PyOFXImageEffectHostType, NULL);
    ((PyOFXHost*)rv)->host = host;
    return rv;
  }
}

PyObject* PyOFXClip_GetHandle(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  OfxImageClipHandle hdl = pclip->clip->handle();
  
  if (!hdl)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*) &PyOFXHandleType, NULL);
    ((PyOFXHandle*)rv)->handle = hdl;
    return rv;
  }
}

PyObject* PyOFXClip_GetName(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pclip->clip->name();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXClip_GetLabel(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pclip->clip->label();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXClip_GetShortLabel(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pclip->clip->shortLabel();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXClip_GetLongLabel(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pclip->clip->longLabel();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXClip_GetPixelDepth(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(pclip->clip->pixelDepth());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXClip_GetComponents(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(pclip->clip->components());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXClip_GetPreMultiplication(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(pclip->clip->preMultiplication());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXClip_GetPixelAspectRatio(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double rv = 0;
  
  CATCH({rv = pclip->clip->pixelAspectRatio();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXClip_GetFrameRate(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double rv = 0.0;
  
  CATCH({rv = pclip->clip->frameRate();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXClip_GetFrameRange(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  ofx::FrameRange range = {0, 0};
  
  CATCH({range = pclip->clip->frameRange();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXRangeDType, NULL);
  PyOFXRangeD *prange = (PyOFXRangeD*) rv;
  prange->range = range;
  return rv;
}

PyObject* PyOFXClip_GetFieldOrder(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(pclip->clip->fieldOrder());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXClip_GetUnmappedPixelDepth(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(pclip->clip->unmappedPixelDepth());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXClip_GetUnmappedComponents(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(pclip->clip->unmappedComponents());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXClip_GetUnmappedFrameRate(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double rv = 0.0;
  
  CATCH({rv = pclip->clip->unmappedFrameRate();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXClip_GetUnmappedFrameRange(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  ofx::FrameRange range = {0, 0};
  
  CATCH({range = pclip->clip->unmappedFrameRange();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXRangeDType, NULL);
  PyOFXRangeD *prange = (PyOFXRangeD*) rv;
  prange->range = range;
  return rv;
}

PyObject* PyOFXClip_GetConnected(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pclip->clip->connected();}, failed);
  
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

PyObject* PyOFXClip_GetContinuousSamples(PyObject *self, void*)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pclip->clip->continuousSamples();}, failed);
  
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

static PyGetSetDef PyOFXClip_GetSeters[] =
{
  {(char*)"host", PyOFXClip_GetHost, NULL, NULL, NULL},
  {(char*)"handle", PyOFXClip_GetHandle, NULL, NULL, NULL},
  {(char*)"name", PyOFXClip_GetName, NULL, NULL, NULL},
  {(char*)"label", PyOFXClip_GetLabel, NULL, NULL, NULL},
  {(char*)"shortLabel", PyOFXClip_GetShortLabel, NULL, NULL, NULL},
  {(char*)"longLabel", PyOFXClip_GetLongLabel, NULL, NULL, NULL},
  {(char*)"pixelDepth", PyOFXClip_GetPixelDepth, NULL, NULL, NULL},
  {(char*)"components", PyOFXClip_GetComponents, NULL, NULL, NULL},
  {(char*)"preMultiplication", PyOFXClip_GetPreMultiplication, NULL, NULL, NULL},
  {(char*)"pixelAspectRatio", PyOFXClip_GetPixelAspectRatio, NULL, NULL, NULL},
  {(char*)"frameRate", PyOFXClip_GetFrameRate, NULL, NULL, NULL},
  {(char*)"frameRange", PyOFXClip_GetFrameRange, NULL, NULL, NULL},
  {(char*)"fieldOrder", PyOFXClip_GetFieldOrder, NULL, NULL, NULL},
  {(char*)"connected", PyOFXClip_GetConnected, NULL, NULL, NULL},
  {(char*)"continuousSamples", PyOFXClip_GetContinuousSamples, NULL, NULL, NULL},
  {(char*)"unmappedPixelDepth", PyOFXClip_GetUnmappedPixelDepth, NULL, NULL, NULL},
  {(char*)"unmappedComponents", PyOFXClip_GetUnmappedComponents, NULL, NULL, NULL},
  {(char*)"unmappedFrameRate", PyOFXClip_GetUnmappedFrameRate, NULL, NULL, NULL},
  {(char*)"unmappedFrameRange", PyOFXClip_GetUnmappedFrameRange, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXClip_GetImage(PyObject *self, PyObject *args)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
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
  
  if (!PyFloat_Check(PyTuple_GetItem(args, 0)))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float for first argument");
    return NULL;
  }
  
  double t = PyFloat_AsDouble(PyTuple_GetItem(args, 0));
  PyObject *pregion = 0;
  
  if (nargs == 2)
  {
    pregion = PyTuple_GetItem(args, 1);
  }
  
  bool failed = false;
  
  ofx::Image img;
  
  if (pregion)
  {
    if (!PyObject_TypeCheck(pregion, &PyOFXRectDType))
    {
      PyErr_SetString(PyExc_TypeError, "Expected a ofx.RectD object");
      return NULL;
    }
    
    CATCH({img = pclip->clip->getImage(t, ((PyOFXRectD*)pregion)->rect);}, failed);
  }
  else
  {
    CATCH({img = pclip->clip->getImage(t);}, failed);
  }
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *pimg = PyObject_CallObject((PyObject*) &PyOFXImageType, NULL);
  *(((PyOFXImage*)pimg)->img) = img;
  return pimg;
}

PyObject* PyOFXClip_GetRegionOfDefinition(PyObject *self, PyObject *args)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  double t;
  
  if (!PyArg_ParseTuple(args, "d", &t))
  {
    return NULL;
  }
  
  ofx::Rect<double> rv = {0, 0, 0, 0};
  
  bool failed = false;
  
  CATCH({rv = pclip->clip->getRegionOfDefinition(t);}, failed);
  
  if (failed)
  {
    return false;
  }
  
  PyObject *prv = PyObject_CallObject((PyObject*)&PyOFXRectDType, NULL);
  PyOFXRectD *prect = (PyOFXRectD*) prv;
  prect->rect = rv;
  return prv;
}

#ifdef OFX_API_1_3

PyObject* PyOFXClip_LoadTexture(PyObject *self, PyObject *args)
{
  PyOFXClip *pclip = (PyOFXClip*) self;
  
  if (!pclip->clip)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  Py_ssize_t nargs = PyTuple_Size(args);
  if (nargs < 1 || nargs > 3)
  {
    PyErr_SetString(PyExc_RuntimeError, "At least 1 argument, at most 3");
    return NULL;
  }
  
  if (!PyFloat_Check(PyTuple_GetItem(args, 0)))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float for first argument");
    return NULL;
  }
  
  double t = PyFloat_AsDouble(PyTuple_GetItem(args, 0));
  const char *fmt = 0;
  PyObject *pregion = 0;
  
  if (nargs >= 2)
  {
    PyObject *item = PyTuple_GetItem(args, 1);
    if (item != Py_None)
    {
      if (!PyString_Check(item))
      {
        PyErr_SetString(PyExc_TypeError, "Expected a string as second argument");
        return NULL;
      }
      fmt = PyString_AsString(item);
    }
  }
  
  if (nargs == 3)
  {
    pregion = PyTuple_GetItem(args, 2);
    if (!PyObject_TypeCheck(pregion, &PyOFXRectDType))
    {
      PyErr_SetString(PyExc_TypeError, "Expected a ofx.RectD object as third argument");
      return NULL;
    }
  }
  
  bool failed = false;
  
  ofx::Texture tex;
  
  if (pregion)
  {
    CATCH({tex = pclip->clip->loadTexture(t, fmt, &(((PyOFXRectD*)pregion)->rect));}, failed);
  }
  else
  {
    CATCH({tex = pclip->clip->loadTexture(t, fmt);}, failed);
  }
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *ptex = PyObject_CallObject((PyObject*) &PyOFXTextureType, NULL);
  *(((PyOFXTexture*)ptex)->tex) = tex;
  return ptex;
}

#endif

static PyMethodDef PyOFXClip_Methods[] =
{
  {"getImage", PyOFXClip_GetImage, METH_VARARGS, NULL},
  {"getRegionOfDefinition", PyOFXClip_GetRegionOfDefinition, METH_VARARGS, NULL},
#ifdef OFX_API_1_3
  {"loadTexture", PyOFXClip_LoadTexture, METH_VARARGS, NULL},
#endif
  {NULL, NULL, 0, NULL}
};

// ---

bool PyOFX_InitClip(PyObject *mod)
{
  INIT_TYPE(PyOFXClipDescriptorType, "ofx.ClipDescriptor", PyOFXClipDescriptor);
  PyOFXClipDescriptorType.tp_new = PyOFXClipDescriptor_New;
  PyOFXClipDescriptorType.tp_init = PyOFXClipDescriptor_Init;
  PyOFXClipDescriptorType.tp_dealloc = PyOFXClipDescriptor_Delete;
  PyOFXClipDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXClipDescriptorType.tp_getset = PyOFXClipDescriptor_GetSeters;
  PyOFXClipDescriptorType.tp_methods = PyOFXClipDescriptor_Methods;
  
  INIT_TYPE(PyOFXClipType, "ofx.Clip", PyOFXClip);
  PyOFXClipType.tp_new = PyOFXClip_New;
  PyOFXClipType.tp_init = PyOFXClip_Init;
  PyOFXClipType.tp_dealloc = PyOFXClip_Delete;
  PyOFXClipType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXClipType.tp_getset = PyOFXClip_GetSeters;
  PyOFXClipType.tp_methods = PyOFXClip_Methods;
  
  if (PyType_Ready(&PyOFXClipDescriptorType) < 0)
  {
    return false;
  }
  
  if (PyType_Ready(&PyOFXClipType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXClipDescriptorType);
  PyModule_AddObject(mod, "ClipDescriptor", (PyObject*)&PyOFXClipDescriptorType);
  
  Py_INCREF(&PyOFXClipType);
  PyModule_AddObject(mod, "Clip", (PyObject*)&PyOFXClipType);
  
  return true;
}

