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

PyTypeObject PyOFXPluginType;
PyTypeObject PyOFXImageEffectPluginType;

// ---

PyPlugin::PyPlugin()
  : ofx::Plugin(), mSelf(0)
{
}
  
PyPlugin::~PyPlugin()
{
  self(0);
}

// ---

PyImageEffectPlugin::PyImageEffectPlugin(PyTypeObject *descClass, PyTypeObject *instClass)
  : PyPlugin(), mDescClass(descClass), mInstClass(instClass), mHost(0)
{
  Py_INCREF(descClass);
  Py_INCREF(instClass);
  
  OfxPlugin *plugin = description();
  plugin->pluginApi = kOfxImageEffectPluginApi;
  plugin->apiVersion = kOfxImageEffectPluginApiVersion;
  plugin->setHost = PyOFX_GetSetHostFunc(this);
  plugin->mainEntry = PyOFX_GetMainFunc(this);
}

PyImageEffectPlugin::~PyImageEffectPlugin()
{
  if (mHost)
  {
    delete mHost;
  }
  
  EffectMap::iterator it = mEffects.begin();
  while (it != mEffects.end())
  {
    delete it->second;
    ++it;
  }
  mEffects.clear();
  
  Py_DECREF(mDescClass);
  Py_DECREF(mInstClass);
}

void PyImageEffectPlugin::setHost(OfxHost *h)
{
  if (!mHost)
  {
    mHost = new ofx::ImageEffectHost(h);
  }
}

ofx::ImageEffectHost* PyImageEffectPlugin::host()
{
  return mHost;
}

PyImageEffectDescriptor PyImageEffectPlugin::descriptor(OfxImageEffectHandle hdl)
{
  if (!mHost)
  {
    return PyImageEffectDescriptor();
  }
  
  PyObject *args = PyTuple_New(2);
    
  PyObject *phost = PyObject_CallObject((PyObject*)&PyOFXImageEffectHostType, NULL);
  ((PyOFXHost*)phost)->host = mHost;
  PyTuple_SetItem(args, 0, phost);
  
  PyObject *phandle = PyObject_CallObject((PyObject*)&PyOFXHandleType, NULL);
  ((PyOFXHandle*)phandle)->handle = hdl;
  PyTuple_SetItem(args, 1, phandle);
  
  PyObject *pdesc = PyObject_CallObject((PyObject*)mDescClass, args);
  
  Py_DECREF(args);
  
  PyImageEffectDescriptor desc = *( (PyImageEffectDescriptor*) ((PyOFXImageEffectDescriptor*)pdesc)->desc );
  
  Py_DECREF(pdesc);
  
  return desc;
}

PyImageEffect* PyImageEffectPlugin::addEffect(OfxImageEffectHandle hdl)
{
  if (!mHost)
  {
    return NULL;
  }
  
  EffectMap::iterator it = mEffects.find(hdl);
  
  if (it == mEffects.end())
  {
    PyObject *args = PyTuple_New(2);
    
    PyObject *phost = PyObject_CallObject((PyObject*)&PyOFXImageEffectHostType, NULL);
    ((PyOFXHost*)phost)->host = mHost;
    PyTuple_SetItem(args, 0, phost);
    
    PyObject *phandle = PyObject_CallObject((PyObject*)&PyOFXHandleType, NULL);
    ((PyOFXHandle*)phandle)->handle = hdl;
    PyTuple_SetItem(args, 1, phandle);
    
    PyObject *peffect = PyObject_CallObject((PyObject*)mInstClass, args);
    
    Py_DECREF(args);
    
    PyImageEffect *effect = (PyImageEffect*) ((PyOFXImageEffect*)peffect)->effect;
    
    Py_DECREF(peffect);
    
    mEffects[hdl] = effect;
    
    return effect;
  }
  else
  {
    return it->second;
  }
}

void PyImageEffectPlugin::removeEffect(OfxImageEffectHandle hdl)
{
  EffectMap::iterator it = mEffects.find(hdl);
  if (it != mEffects.end())
  {
    delete it->second;
    mEffects.erase(it);
  }
}

PyImageEffect* PyImageEffectPlugin::getEffect(OfxImageEffectHandle hdl)
{
  EffectMap::iterator it = mEffects.find(hdl);
  if (it != mEffects.end())
  {
    return it->second;
  }
  return NULL;
}

OfxStatus PyImageEffectPlugin::load()
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "load");
    
    if (meth != 0)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *rv = PyObject_CallObject(meth, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
        }
        else
        {
          ofx::Log("PyImageEffectPlugin::load: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
    
  return kOfxStatReplyDefault;
}
  
OfxStatus PyImageEffectPlugin::unload()
{
  // it seems that sometimes, unload is called after python interpreter has been killed...
  if (Py_IsInitialized() && mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "unload");
    
    if (meth != 0)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *rv = PyObject_CallObject(meth, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
        }
        else
        {
          ofx::Log("PyImageEffectPlugin::unload: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return kOfxStatReplyDefault;
}

// ---

PyObject* PyOFXPlugin_New(PyTypeObject *type, PyObject *, PyObject *)
{
  PyObject *self = type->tp_alloc(type, 1);
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  pplugin->plugin = 0;
  return self;
}

int PyOFXPlugin_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

void PyOFXPlugin_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXPlugin_GetMajorVersion(PyObject *self, void*)
{
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  
  if (!pplugin->plugin)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(pplugin->plugin->majorVersion());
}

int PyOFXPlugin_SetMajorVersion(PyObject *self, PyObject *value, void*)
{
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  
  if (!pplugin->plugin)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyInt_Check(value))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  
  int v = PyInt_AsLong(value);
  
  pplugin->plugin->majorVersion(v);
  
  return 0;
}

PyObject* PyOFXPlugin_GetMinorVersion(PyObject *self, void*)
{
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  
  if (!pplugin->plugin)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(pplugin->plugin->minorVersion());
}

int PyOFXPlugin_SetMinorVersion(PyObject *self, PyObject *value, void*)
{
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  
  if (!pplugin->plugin)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyInt_Check(value))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  
  int v = PyInt_AsLong(value);
  
  pplugin->plugin->minorVersion(v);
  
  return 0;
}

PyObject* PyOFXPlugin_GetIdentifier(PyObject *self, void*)
{
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  
  if (!pplugin->plugin)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyString_FromString(pplugin->plugin->identifier());
}

int PyOFXPlugin_SetIdentifier(PyObject *self, PyObject *value, void*)
{
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  
  if (!pplugin->plugin)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(value))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  const char *id = PyString_AsString(value);
  
  pplugin->plugin->identifier(id);
  
  return 0;
}

static PyGetSetDef PyOFXPlugin_GetSeters[] =
{
  {(char*)"majorVersion", PyOFXPlugin_GetMajorVersion, PyOFXPlugin_SetMajorVersion, NULL, NULL},
  {(char*)"minorVersion", PyOFXPlugin_GetMinorVersion, PyOFXPlugin_SetMinorVersion, NULL, NULL},
  {(char*)"identifier", PyOFXPlugin_GetIdentifier, PyOFXPlugin_SetIdentifier, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXImageEffectPlugin_Init(PyObject *self, PyObject *args, PyObject *)
{
  PyOFXPlugin *pplugin = (PyOFXPlugin*)self;
  
  PyObject *desc = 0, *inst = 0;
  
  if (!PyArg_ParseTuple(args, "OO", &desc, &inst))
  {
    return -1;
  }
  
  if (!PyObject_IsSubclass(desc, (PyObject*)&PyOFXImageEffectDescriptorType))
  {
    PyErr_SetString(PyExc_TypeError, "First argument must be a subclass of ofx.ImageEffectDescriptor");
    return -1;
  }
  
  if (!PyObject_IsSubclass(inst, (PyObject*)&PyOFXImageEffectType))
  {
    PyErr_SetString(PyExc_TypeError, "Second argument must be a subclass of ofx.ImageEffect");
    return -1;
  }
  
  PyImageEffectPlugin *plugin = new PyImageEffectPlugin((PyTypeObject*)desc, (PyTypeObject*)inst);
  plugin->self(self);
  
  pplugin->plugin = plugin;
  
  return 0;
}

PyObject* PyOFXImageEffectPlugin_GetHost(PyObject *self, void *)
{
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  
  if (!pplugin->plugin)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyImageEffectPlugin *plugin = (PyImageEffectPlugin*) pplugin->plugin;
  
  ofx::ImageEffectHost *host = plugin->host();
  
  if (!host)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXImageEffectHostType, NULL);
    ((PyOFXHost*)rv)->host = host;
    return rv;
  }
}

static PyGetSetDef PyOFXImageEffectPlugin_GetSeters[] = 
{
  {(char*)"host", PyOFXImageEffectPlugin_GetHost, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

bool PyOFX_InitPlugin(PyObject *mod)
{
  INIT_TYPE(PyOFXPluginType, "ofx.Plugin", PyOFXPlugin);
  PyOFXPluginType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXPluginType.tp_new = PyOFXPlugin_New;
  PyOFXPluginType.tp_dealloc = PyOFXPlugin_Delete;
  PyOFXPluginType.tp_init = PyOFXPlugin_Init;
  PyOFXPluginType.tp_getset = PyOFXPlugin_GetSeters;
  
  INIT_TYPE(PyOFXImageEffectPluginType, "ofx.ImageEffectPlugin", PyOFXImageEffectPlugin);
  PyOFXImageEffectPluginType.tp_base = &PyOFXPluginType;
  PyOFXImageEffectPluginType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXImageEffectPluginType.tp_init = PyOFXImageEffectPlugin_Init;
  PyOFXImageEffectPluginType.tp_getset = PyOFXImageEffectPlugin_GetSeters;
  
  if (PyType_Ready(&PyOFXPluginType) < 0)
  {
    return false;
  }
  
  if (PyType_Ready(&PyOFXImageEffectPluginType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXPluginType);
  PyModule_AddObject(mod, "Plugin", (PyObject*)&PyOFXPluginType);
  
  Py_INCREF(&PyOFXImageEffectPluginType);
  PyModule_AddObject(mod, "ImageEffectPlugin", (PyObject*)&PyOFXImageEffectPluginType);
  
  return true;
}

