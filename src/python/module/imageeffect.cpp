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

PyTypeObject PyOFXImageEffectDescriptorType;
PyTypeObject PyOFXImageEffectType;

// ---

PyImageEffectDescriptor::PyImageEffectDescriptor(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl) throw(ofx::Exception)
  : ofx::ImageEffectDescriptor(h, hdl), mSelf(0)
{  
}

PyImageEffectDescriptor::PyImageEffectDescriptor(const PyImageEffectDescriptor &rhs)
  : ofx::ImageEffectDescriptor(rhs)
{
}

PyImageEffectDescriptor::~PyImageEffectDescriptor()
{
  self(0);
}

PyImageEffectDescriptor& PyImageEffectDescriptor::operator=(const PyImageEffectDescriptor &rhs)
{
  ofx::ImageEffectDescriptor::operator=(rhs);
  return *this;
}

OfxStatus PyImageEffectDescriptor::describe()
{
  // Call python
  return ofx::ImageEffectDescriptor::describe();
}

OfxStatus PyImageEffectDescriptor::describeInContext(ofx::ImageEffectContext ctx)
{
  // Call python
  return ofx::ImageEffectDescriptor::describeInContext(ctx);
}

// ---

PyImageEffect::PyImageEffect(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl)
  : ofx::ImageEffect(h, hdl)
{
}

PyImageEffect::~PyImageEffect()
{
  self(0);
}

OfxStatus PyImageEffect::beginInstanceChanged(ofx::ChangeReason reason)
{
  return ofx::ImageEffect::beginInstanceChanged(reason);
}

OfxStatus PyImageEffect::endInstanceChanged(ofx::ChangeReason reason)
{
  return ofx::ImageEffect::endInstanceChanged(reason);
}

OfxStatus PyImageEffect::instanceChanged(ofx::ImageEffect::InstanceChangedArgs &args)
{
  return ofx::ImageEffect::instanceChanged(args);
}

OfxStatus PyImageEffect::purgeCaches()
{
  return ofx::ImageEffect::purgeCaches();
}

OfxStatus PyImageEffect::syncPrivateData()
{
  return ofx::ImageEffect::syncPrivateData();
}

OfxStatus PyImageEffect::beginInstanceEdit()
{
  return ofx::ImageEffect::beginInstanceEdit();
}

OfxStatus PyImageEffect::endInstanceEdit()
{
  return ofx::ImageEffect::endInstanceEdit();
}

OfxStatus PyImageEffect::getRegionOfDefinition(ofx::ImageEffect::GetRoDArgs &args)
{
  return ofx::ImageEffect::getRegionOfDefinition(args);
}

OfxStatus PyImageEffect::getRegionsOfInterest(ofx::ImageEffect::GetRoIArgs &args)
{
  return ofx::ImageEffect::getRegionsOfInterest(args);
}

OfxStatus PyImageEffect::getFramesNeeded(ofx::ImageEffect::GetFramesNeededArgs &args)
{
  return ofx::ImageEffect::getFramesNeeded(args);
}

OfxStatus PyImageEffect::isIdentity(ofx::ImageEffect::IsIdentityArgs &args)
{
  return ofx::ImageEffect::isIdentity(args);
}

OfxStatus PyImageEffect::render(ofx::ImageEffect::RenderArgs &args)
{
  return ofx::ImageEffect::render(args);
}

OfxStatus PyImageEffect::beginSequenceRender(ofx::ImageEffect::BeginSequenceArgs &args)
{
  return ofx::ImageEffect::beginSequenceRender(args);
}

OfxStatus PyImageEffect::endSequenceRender(ofx::ImageEffect::EndSequenceArgs &args)
{
  return ofx::ImageEffect::endSequenceRender(args);
}

OfxStatus PyImageEffect::getClipPreferences(ofx::ImageEffect::GetClipPrefArgs &args)
{
  return ofx::ImageEffect::getClipPreferences(args);
}

OfxStatus PyImageEffect::getTimeDomain(double *first, double *last)
{
  return ofx::ImageEffect::getTimeDomain(first, last);
}

// ---

PyObject* PyOFXImageEffectDescriptor_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  pdesc->desc = 0;
  return self;
}

int PyOFXImageEffectDescriptor_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

void PyOFXImageEffectDescriptor_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXImageEffectDescriptor_GetProperties(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXPropertySetType, NULL);
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*)rv;
  ppset->pset = &(pdesc->desc->properties());
  
  return rv;
}

PyObject* PyOFXImageEffectDescriptor_GetParameters(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXParameterSetDescriptorType, NULL);
  
  PyOFXParameterSetDescriptor *ppset = (PyOFXParameterSetDescriptor*)rv;
  ppset->desc = &(pdesc->desc->parameters());
  
  return rv;
}

PyObject* PyOFXImageEffectDescriptor_GetHost(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = pdesc->desc->host();
  
  if (!host)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXImageEffectHostType, NULL);
    
    PyOFXHost *phost = (PyOFXHost*)rv;
    phost->host = host;
    
    return rv;
  }
}

PyObject* PyOFXImageEffectDescriptor_GetHandle(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  OfxImageEffectHandle hdl = pdesc->desc->handle();
  
  if (!hdl)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXHandleType, NULL);
    
    PyOFXHandle *phandle = (PyOFXHandle*)rv;
    phandle->handle = hdl;
    
    return rv;
  }
}

PyObject* PyOFXImageEffectDescriptor_GetLabel(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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

int PyOFXImageEffectDescriptor_SetLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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
  
  std::string v = PyString_AsString(val);
  
  CATCH({pdesc->desc->label(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetShortLabel(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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

int PyOFXImageEffectDescriptor_SetShortLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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
  
  std::string v = PyString_AsString(val);
  
  CATCH({pdesc->desc->shortLabel(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetLongLabel(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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

int PyOFXImageEffectDescriptor_SetLongLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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
  
  std::string v = PyString_AsString(val);
  
  CATCH({pdesc->desc->longLabel(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetGroup(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->group();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

int PyOFXImageEffectDescriptor_SetGroup(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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
  
  std::string v = PyString_AsString(val);
  
  CATCH({pdesc->desc->group(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetPluginFilePath(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->pluginFilePath();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

#ifdef OFX_API_1_2

PyObject* PyOFXImageEffectDescriptor_GetVersionLabel(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->versionLabel();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

int PyOFXImageEffectDescriptor_SetVersionLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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
  
  std::string v = PyString_AsString(val);
  
  CATCH({pdesc->desc->versionLabel(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetDescription(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->description();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

int PyOFXImageEffectDescriptor_SetDescription(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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
  
  std::string v = PyString_AsString(val);
  
  CATCH({pdesc->desc->description(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetMajorVersion(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = pdesc->desc->majorVersion();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectDescriptor_GetMinorVersion(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = pdesc->desc->minorVersion();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

#endif

PyObject* PyOFXImageEffectDescriptor_GetSingleInstance(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->singleInstance();}, failed);
  
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

int PyOFXImageEffectDescriptor_SetSingleInstance(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->singleInstance(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetHostFrameThreading(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->hostFrameThreading();}, failed);
  
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

int PyOFXImageEffectDescriptor_SetHostFrameThreading(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->hostFrameThreading(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetSupportsMultiResolution(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->supportsMultiResolution();}, failed);
  
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

int PyOFXImageEffectDescriptor_SetSupportsMultiResolution(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->supportsMultiResolution(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetSupportsTiles(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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
    Py_RETURN_FALSE;
  }
}

int PyOFXImageEffectDescriptor_SetSupportsTiles(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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

PyObject* PyOFXImageEffectDescriptor_GetSupportsMultipleClipDepths(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->supportsMultipleClipDepths();}, failed);
  
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

int PyOFXImageEffectDescriptor_SetSupportsMultipleClipDepths(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->supportsMultipleClipDepths(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetSupportsMultipleClipPARs(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->supportsMultipleClipPARs();}, failed);
  
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

int PyOFXImageEffectDescriptor_SetSupportsMultipleClipPARs(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->supportsMultipleClipPARs(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetTemporalClipAccess(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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
    Py_RETURN_FALSE;
  }
}

int PyOFXImageEffectDescriptor_SetTemporalClipAccess(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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

PyObject* PyOFXImageEffectDescriptor_GetFieldRenderTwiceAlways(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->fieldRenderTwiceAlways();}, failed);
  
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

int PyOFXImageEffectDescriptor_SetFieldRenderTwiceAlways(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->fieldRenderTwiceAlways(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetRenderThreadSafety(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(pdesc->desc->renderThreadSafety());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXImageEffectDescriptor_SetRenderThreadSafety(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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
  
  CATCH({pdesc->desc->renderThreadSafety(ofx::RenderThreadSafety(v));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetSequentialRender(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(pdesc->desc->sequentialRender());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXImageEffectDescriptor_SetSequentialRender(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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
  
  CATCH({pdesc->desc->sequentialRender(ofx::SequentialRender(v));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetOverlayInteract(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  // TODO
  
  Py_RETURN_NONE;
}

int PyOFXImageEffectDescriptor_SetOverlayInteract(PyObject *self, PyObject *, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  // TODO
  // NOTE: effectDesc->overlayInteract(InteractEntryPoint<MyPluginClass, MyInteractDescriptionClass, MyInteractClass>)
  
  return 0;
}

static PyGetSetDef PyOFXImageEffectDescriptor_GetSeters[] =
{
  {(char*)"handle", PyOFXImageEffectDescriptor_GetHandle, NULL, NULL, NULL},
  {(char*)"host", PyOFXImageEffectDescriptor_GetHost, NULL, NULL, NULL},
  {(char*)"parameters", PyOFXImageEffectDescriptor_GetParameters, NULL, NULL, NULL},
  {(char*)"properties", PyOFXImageEffectDescriptor_GetProperties, NULL, NULL, NULL},
  {(char*)"label", PyOFXImageEffectDescriptor_GetLabel, PyOFXImageEffectDescriptor_SetLabel, NULL, NULL},
  {(char*)"shortLabel", PyOFXImageEffectDescriptor_GetShortLabel, PyOFXImageEffectDescriptor_SetShortLabel, NULL, NULL},
  {(char*)"longLabel", PyOFXImageEffectDescriptor_GetLongLabel, PyOFXImageEffectDescriptor_SetLongLabel, NULL, NULL},
  {(char*)"group", PyOFXImageEffectDescriptor_GetGroup, PyOFXImageEffectDescriptor_SetGroup, NULL, NULL},
  {(char*)"pluginFilePath", PyOFXImageEffectDescriptor_GetPluginFilePath, NULL, NULL, NULL},
  {(char*)"singleInstance", PyOFXImageEffectDescriptor_GetSingleInstance, PyOFXImageEffectDescriptor_SetSingleInstance, NULL, NULL},
  {(char*)"hostFrameThreading", PyOFXImageEffectDescriptor_GetHostFrameThreading, PyOFXImageEffectDescriptor_SetHostFrameThreading, NULL, NULL},
  {(char*)"supportsMultiResolution", PyOFXImageEffectDescriptor_GetSupportsMultiResolution, PyOFXImageEffectDescriptor_SetSupportsMultiResolution, NULL, NULL},
  {(char*)"supportsTiles", PyOFXImageEffectDescriptor_GetSupportsTiles, PyOFXImageEffectDescriptor_SetSupportsTiles, NULL, NULL},
  {(char*)"supportsMultipleClipDepths", PyOFXImageEffectDescriptor_GetSupportsMultipleClipDepths, PyOFXImageEffectDescriptor_SetSupportsMultipleClipDepths, NULL, NULL},
  {(char*)"supportsMultipleClipPARs", PyOFXImageEffectDescriptor_GetSupportsMultipleClipPARs, PyOFXImageEffectDescriptor_SetSupportsMultipleClipPARs, NULL, NULL},
  {(char*)"temporalClipAccess", PyOFXImageEffectDescriptor_GetTemporalClipAccess, PyOFXImageEffectDescriptor_SetTemporalClipAccess, NULL, NULL},
  {(char*)"fieldRenderTwiceAlways", PyOFXImageEffectDescriptor_GetFieldRenderTwiceAlways, PyOFXImageEffectDescriptor_SetFieldRenderTwiceAlways, NULL, NULL},
  {(char*)"renderThreadSafety", PyOFXImageEffectDescriptor_GetRenderThreadSafety, PyOFXImageEffectDescriptor_SetRenderThreadSafety, NULL, NULL},
  {(char*)"sequentialRender", PyOFXImageEffectDescriptor_GetSequentialRender, PyOFXImageEffectDescriptor_SetSequentialRender, NULL, NULL},
  {(char*)"overlayInteract", PyOFXImageEffectDescriptor_GetOverlayInteract, PyOFXImageEffectDescriptor_SetOverlayInteract, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"description", PyOFXImageEffectDescriptor_GetDescription, PyOFXImageEffectDescriptor_SetDescription, NULL, NULL},
  {(char*)"versionLabel", PyOFXImageEffectDescriptor_GetVersionLabel, PyOFXImageEffectDescriptor_SetVersionLabel, NULL, NULL},
  {(char*)"majorVersion", PyOFXImageEffectDescriptor_GetMajorVersion, NULL, NULL, NULL},
  {(char*)"minorVersion", PyOFXImageEffectDescriptor_GetMinorVersion, NULL, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXImageEffectDescriptor_DefineClip(PyObject *self, PyObject *args)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
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
  
  bool failed = false;
  
  ofx::ClipDescriptor cd;
  
  CATCH({cd = pdesc->desc->defineClip(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXClipDescriptorType, NULL);
  
  PyOFXClipDescriptor *pcd = (PyOFXClipDescriptor*)rv;
  *(pcd->desc) = cd;
  
  return rv;
}

PyObject* PyOFXImageEffectDescriptor_SupportedContextsCount(PyObject *self, PyObject *)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = pdesc->desc->supportedContextsCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectDescriptor_SupportedPixelDepthsCount(PyObject *self, PyObject *)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = pdesc->desc->supportedPixelDepthsCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectDescriptor_ClipPreferencesSlaveParamCount(PyObject *self, PyObject *)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = pdesc->desc->clipPreferencesSlaveParamCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectDescriptor_SupportedContext(PyObject *self, PyObject *args)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx = 0;
  PyObject *pctx = 0;
  
  if (PyArg_ParseTuple(args, "i|O", &idx, &pctx))
  {
    return NULL;
  }
  
  bool failed = false;
  
  if (pctx != 0)
  {
    if (!PyInt_Check(pctx))
    {
      PyErr_SetString(PyExc_TypeError, "Expected an integer");
      return NULL;
    }
    
    int ctx = PyInt_AsLong(pctx);
    
    CATCH({pdesc->desc->supportedContext(idx, ofx::ImageEffectContext(ctx));}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    Py_RETURN_NONE;
  }
  else
  {
    int rv = 0;
    
    CATCH({rv = int(pdesc->desc->supportedContext(idx));}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    return PyInt_FromLong(rv);
  }
}

PyObject* PyOFXImageEffectDescriptor_SupportedPixelDepth(PyObject *self, PyObject *args)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx = 0;
  PyObject *ppd = 0;
  
  if (PyArg_ParseTuple(args, "i|O", &idx, &ppd))
  {
    return NULL;
  }
  
  bool failed = false;
  
  if (ppd != 0)
  {
    if (!PyInt_Check(ppd))
    {
      PyErr_SetString(PyExc_TypeError, "Expected an integer");
      return NULL;
    }
    
    int pd = PyInt_AsLong(ppd);
    
    CATCH({pdesc->desc->supportedPixelDepth(idx, ofx::BitDepth(pd));}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    Py_RETURN_NONE;
  }
  else
  {
    int rv = 0;
    
    CATCH({rv = int(pdesc->desc->supportedPixelDepth(idx));}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    return PyInt_FromLong(rv);
  }
}

PyObject* PyOFXImageEffectDescriptor_ClipPreferencesSlaveParam(PyObject *self, PyObject *args)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx = 0;
  PyObject *pparam = 0;
  
  if (PyArg_ParseTuple(args, "i|O", &idx, &pparam))
  {
    return NULL;
  }
  
  bool failed = false;
  
  if (pparam != 0)
  {
    if (!PyString_Check(pparam))
    {
      PyErr_SetString(PyExc_TypeError, "Expected a string");
      return NULL;
    }
    
    char *param = PyString_AsString(pparam);
    
    CATCH({pdesc->desc->clipPreferencesSlaveParam(idx, param);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    Py_RETURN_NONE;
  }
  else
  {
    std::string rv;
    
    CATCH({rv = pdesc->desc->clipPreferencesSlaveParam(idx);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    return PyString_FromString(rv.c_str());
  }
}

#ifdef OFX_API_1_2

PyObject* PyOFXImageEffectDescriptor_Version(PyObject *self, PyObject *args)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int level = 0;
  PyObject *pver = 0;
  
  if (PyArg_ParseTuple(args, "i|O", &level, &pver))
  {
    return NULL;
  }
  
  bool failed = false;
  
  if (pver != 0)
  {
    if (!PyInt_Check(pver))
    {
      PyErr_SetString(PyExc_TypeError, "Expected an integer");
      return NULL;
    }
    
    int ver = PyInt_AsLong(pver);
    
    CATCH({pdesc->desc->version(level, ver);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    Py_RETURN_NONE;
  }
  else
  {
    int rv = 0;
    
    CATCH({rv = pdesc->desc->version(level);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    return PyInt_FromLong(rv);
  }
}

#endif

static PyMethodDef PyOFXImageEffectDescriptor_Methods[] =
{
  {"defineClip", PyOFXImageEffectDescriptor_DefineClip, METH_VARARGS, NULL},
  {"supportedContextsCount", PyOFXImageEffectDescriptor_SupportedContextsCount, METH_VARARGS, NULL},
  {"supportedContext", PyOFXImageEffectDescriptor_SupportedContext, METH_VARARGS, NULL},
  {"supportedPixelDepthsCount", PyOFXImageEffectDescriptor_SupportedPixelDepthsCount, METH_VARARGS, NULL},
  {"supportedPixelDepth", PyOFXImageEffectDescriptor_SupportedPixelDepth, METH_VARARGS, NULL},
  {"clipPreferencesSlaveParamCount", PyOFXImageEffectDescriptor_ClipPreferencesSlaveParamCount, METH_VARARGS, NULL},
  {"clipPreferencesSlaveParam", PyOFXImageEffectDescriptor_ClipPreferencesSlaveParam, METH_VARARGS, NULL},
#ifdef OFX_API_1_2
  {"version", PyOFXImageEffectDescriptor_Version, METH_VARARGS, NULL},
#endif
  {NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXImageEffect_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  ((PyOFXImageEffect*)self)->effect = 0;
  return self;
}

int PyOFXImageEffect_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

void PyOFXImageEffect_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXImageEffect_GetProperties(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXPropertySetType, NULL);
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*)rv;
  ppset->pset = &(peffect->effect->properties());
  
  return rv;
}

PyObject* PyOFXImageEffect_GetParameters(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXParameterSetType, NULL);
  
  PyOFXParameterSet *ppset = (PyOFXParameterSet*)rv;
  ppset->pset = &(peffect->effect->parameters());
  
  return rv;
}

PyObject* PyOFXImageEffect_GetHost(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = peffect->effect->host();
  
  if (!host)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXImageEffectHostType, NULL);
    
    PyOFXHost *phost = (PyOFXHost*)rv;
    phost->host = host;
    
    return rv;
  }
}

PyObject* PyOFXImageEffect_GetHandle(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  OfxImageEffectHandle hdl = peffect->effect->handle();
  
  if (!hdl)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXHandleType, NULL);
    
    PyOFXHandle *phandle = (PyOFXHandle*)rv;
    phandle->handle = hdl;
    
    return rv;
  }
}

PyObject* PyOFXImageEffect_GetContext(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(peffect->effect->context());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffect_GetProjectSize(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double w, h;
  
  CATCH({peffect->effect->projectSize(&w, &h);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", w, h);
}

PyObject* PyOFXImageEffect_GetProjectOffset(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double x, y;
  
  CATCH({peffect->effect->projectOffset(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", x, y);
}

PyObject* PyOFXImageEffect_GetProjectExtent(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double w, h;
  
  CATCH({peffect->effect->projectExtent(&w, &h);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", w, h);
}

PyObject* PyOFXImageEffect_GetProjectPixelAspectRatio(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double par = 1.0;
  
  CATCH({par = peffect->effect->projectPixelAspectRatio();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(par);
}

PyObject* PyOFXImageEffect_GetDuration(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double rv = 0.0;
  
  CATCH({rv = peffect->effect->duration();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXImageEffect_GetFrameRate(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double rv = 0.0;
  
  CATCH({rv = peffect->effect->frameRate();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXImageEffect_GetIsInteractive(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = peffect->effect->isInteractive();}, failed);
  
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

PyObject* PyOFXImageEffect_GetInAnalysis(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = peffect->effect->inAnalysis();}, failed);
  
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

int PyOFXImageEffect_SetInAnalysis(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({peffect->effect->inAnalysis(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffect_GetSequentialRender(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(peffect->effect->sequentialRender());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXImageEffect_SetSequentialRender(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
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
  
  CATCH({peffect->effect->sequentialRender(ofx::SequentialRender(v));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

#ifdef OFX_API_1_2

PyObject* PyOFXImageEffect_GetDescription(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = peffect->effect->description();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

#endif

static PyGetSetDef PyOFXImageEffect_GetSeters[] =
{
  {(char*)"properties", PyOFXImageEffect_GetProperties, NULL, NULL, NULL},
  {(char*)"parameters", PyOFXImageEffect_GetParameters, NULL, NULL, NULL},
  {(char*)"host", PyOFXImageEffect_GetHost, NULL, NULL, NULL},
  {(char*)"handle", PyOFXImageEffect_GetHandle, NULL, NULL, NULL},
  {(char*)"context", PyOFXImageEffect_GetContext, NULL, NULL, NULL},
  {(char*)"projectSize", PyOFXImageEffect_GetProjectSize, NULL, NULL, NULL},
  {(char*)"projectOffset", PyOFXImageEffect_GetProjectOffset, NULL, NULL, NULL},
  {(char*)"projectExtent", PyOFXImageEffect_GetProjectExtent, NULL, NULL, NULL},
  {(char*)"projectPixelAspectRatio", PyOFXImageEffect_GetProjectPixelAspectRatio, NULL, NULL, NULL},
  {(char*)"duration", PyOFXImageEffect_GetDuration, NULL, NULL, NULL},
  {(char*)"frameRate", PyOFXImageEffect_GetFrameRate, NULL, NULL, NULL},
  {(char*)"isInteractive", PyOFXImageEffect_GetIsInteractive, NULL, NULL, NULL},
  {(char*)"inAnalysis", PyOFXImageEffect_GetInAnalysis, PyOFXImageEffect_SetInAnalysis, NULL, NULL},
  {(char*)"sequentialRender", PyOFXImageEffect_GetSequentialRender, PyOFXImageEffect_SetSequentialRender, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"description", PyOFXImageEffect_GetDescription, NULL, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

/*
// properties
void* instanceData();
void instanceData(void *data);

ImageEffectDescriptor descriptor();

// suite
Clip getClip(const std::string &name) throw(Exception);
bool abort() throw(Exception);

OfxImageMemoryHandle alloc(size_t nBytes) throw(Exception);
void* lock(OfxImageMemoryHandle hdl) throw(Exception);
void unlock(OfxImageMemoryHandle hdl) throw(Exception);
void free(OfxImageMemoryHandle hdl) throw(Exception);
*/

PyObject* PyOFXImageEffect_GetClip(PyObject *self, PyObject *args)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::Clip clip;
  
  bool failed = false;
  
  CATCH({clip = peffect->effect->getClip(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXClipType, NULL);
  
  PyOFXClip *pclip = (PyOFXClip*)rv;
  *(pclip->clip) = clip;
  
  return rv;
}

PyObject* PyOFXImageEffect_Abort(PyObject *self, PyObject *)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = peffect->effect->abort();}, failed);
  
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

PyObject* PyOFXImageEffect_Alloc(PyObject *self, PyObject *args)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int w, h, comps, depth;
  
  if (!PyArg_ParseTuple(args, "iiii", &w, &h, &comps, &depth))
  {
    return NULL;
  }
  
  bool failed = false;
  
  OfxImageMemoryHandle hdl = 0;
  
  CATCH({hdl = peffect->effect->alloc(w, h, ofx::ImageComponent(comps), ofx::BitDepth(depth));}, failed);
  
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
    PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXImageMemoryHandleType, NULL);
    
    PyOFXImageMemoryHandle *phdl = (PyOFXImageMemoryHandle*)rv;
    phdl->base.handle = hdl;
    phdl->w = w;
    phdl->h = h;
    phdl->components = (ofx::ImageComponent) comps;
    phdl->pixelDepth = (ofx::BitDepth) depth;
    
    return rv;
  }
}

PyObject* PyOFXImageEffect_Lock(PyObject *self, PyObject *args)
{
  // -> Components? BitDepth? Width? Height?
  // -> use as arguments to alloc
  // -> review this API in base library
  // -> review the PixelIterator not to reference image directly
  // we actually want a pixel iterator
  Py_RETURN_NONE;
}

PyObject* PyOFXImageEffect_Unlock(PyObject *self, PyObject *args)
{
  Py_RETURN_NONE;
}

PyObject* PyOFXImageEffect_Free(PyObject *self, PyObject *args)
{
  Py_RETURN_NONE;
}

static PyMethodDef PyOFXImageEffect_Methods[] =
{
  {"getClip", PyOFXImageEffect_GetClip, METH_VARARGS, NULL},
  {"abort", PyOFXImageEffect_Abort, METH_VARARGS, NULL},
  {"alloc", PyOFXImageEffect_Alloc, METH_VARARGS, NULL},
  {"lock", PyOFXImageEffect_Lock, METH_VARARGS, NULL},
  {"unlock", PyOFXImageEffect_Unlock, METH_VARARGS, NULL},
  {"free", PyOFXImageEffect_Free, METH_VARARGS, NULL},
  {NULL, NULL, NULL, NULL}
};

// ---

bool PyOFX_InitImageEffect(PyObject *mod)
{
  INIT_TYPE(PyOFXImageEffectDescriptorType, "ofx.ImageEffectDescriptor", PyOFXImageEffectDescriptor);
  PyOFXImageEffectDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXImageEffectDescriptorType.tp_new = PyOFXImageEffectDescriptor_New;
  PyOFXImageEffectDescriptorType.tp_dealloc = PyOFXImageEffectDescriptor_Delete;
  PyOFXImageEffectDescriptorType.tp_init = PyOFXImageEffectDescriptor_Init;
  PyOFXImageEffectDescriptorType.tp_getset = PyOFXImageEffectDescriptor_GetSeters;
  PyOFXImageEffectDescriptorType.tp_methods = PyOFXImageEffectDescriptor_Methods;
  
  INIT_TYPE(PyOFXImageEffectType, "ofx.ImageEffect", PyOFXImageEffect);
  PyOFXImageEffectType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXImageEffectType.tp_new = PyOFXImageEffect_New;
  PyOFXImageEffectType.tp_dealloc = PyOFXImageEffect_Delete;
  PyOFXImageEffectType.tp_init = PyOFXImageEffect_Init;
  PyOFXImageEffectType.tp_getset = PyOFXImageEffect_GetSeters;
  PyOFXImageEffectType.tp_methods = PyOFXImageEffect_Methods;
  
  if (PyType_Ready(&PyOFXImageEffectDescriptorType) < 0)
  {
    return false;
  }
  
  if (PyType_Ready(&PyOFXImageEffectType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXImageEffectDescriptorType);
  PyModule_AddObject(mod, "ImageEffectDescriptor", (PyObject*)&PyOFXImageEffectDescriptorType);
  
  Py_INCREF(&PyOFXImageEffectType);
  PyModule_AddObject(mod, "ImageEffect", (PyObject*)&PyOFXImageEffectType);
  
  return true;
}
