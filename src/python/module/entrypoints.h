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

#ifndef __pyofx_entrypoints_h__
#define __pyofx_entrypoints_h__

#include "common.h"

#if 1
# define PYOFX_USE_MACROS
#endif

#ifdef PYOFX_USE_MACROS
// visual c++ limit to nested macros...
# define PYOFX_MAX_ENTRY 122
#else
// up to 499 entries [default limit to 500 on template recursion depth fof g++ on OSX]
// compile time explodes
# define PYOFX_MAX_ENTRY 499
#endif

typedef void (*OfxSetHostFunc)(OfxHost*);

extern PyImageEffectPlugin* gEffectPlugins[PYOFX_MAX_ENTRY];
extern PyObject*            gInteractPluginClasses[PYOFX_MAX_ENTRY];
extern PyObject*            gInteractDescClasses[PYOFX_MAX_ENTRY];
extern PyObject*            gInteractClasses[PYOFX_MAX_ENTRY];
extern PyObject*            gInterpFuncObjs[PYOFX_MAX_ENTRY];


extern ofx::EntryPoint PyOFX_GetInteractFunc(PyObject *pluginClass, PyObject *descClass, PyObject *instClass);
extern OfxSetHostFunc  PyOFX_GetSetHostFunc(PyImageEffectPlugin *plugin);
extern ofx::EntryPoint PyOFX_GetMainFunc(PyImageEffectPlugin *plugin);
extern OfxInterpFunc   PyOFX_GetInterpFunc(PyObject *funcObj);

extern int PyOFX_GetInteractFuncIndex(ofx::EntryPoint func);
extern int PyOFX_GetSetHostFuncIndex(OfxSetHostFunc func);
extern int PyOFX_GetMainFuncIndex(ofx::EntryPoint func);
extern int PyOFX_GetInterpFuncIndex(OfxInterpFunc func);


# define PyOFX_AcquireGIL \
PyGILState_STATE gstate = PyGILState_UNLOCKED;\
if (PyOFX_UseGIL()) {\
  gstate = PyGILState_Ensure();\
}

# define PyOFX_ReleaseGIL \
if (PyOFX_UseGIL()) {\
  PyGILState_Release(gstate);\
}

template <int IDX>
std::string PyOFX_InterpFunc(ofx::ParameterSet &params,
                             const std::string &paramName,
                             ofx::Time t,
                             ofx::Time t0, const std::string &v0,
                             ofx::Time t1, const std::string &v1,
                             double amount)
{
  PyOFX_AcquireGIL
  
  if (gInterpFuncObjs[IDX] == 0)
  {
    PyOFX_ReleaseGIL
    
    throw ofx::FailedError("No associated python interpolation function");
  }
  
  PyObject *ppset = PyObject_CallObject((PyObject*)&PyOFXParameterSetType, NULL);
  ofx::ParameterSet *pset = ((PyOFXParameterSet*)ppset)->pset;
  *pset = params;
  
  PyObject *args = Py_BuildValue("Osddsdsd", ppset, paramName.c_str(), t, t0, v0.c_str(), t1, v1.c_str(), amount);
  
  PyObject *iv = PyObject_CallObject(gInterpFuncObjs[IDX], args);
  
  Py_DECREF(args);
  Py_DECREF(ppset);
  
  if (!PyString_Check(iv))
  {
    Py_DECREF(iv);
    
    PyOFX_ReleaseGIL
    
    throw ofx::ValueError("Python interpolation function should return a string");
  }
  
  std::string rv = PyString_AsString(iv);
  Py_DECREF(iv);
  
  PyOFX_ReleaseGIL
  
  return rv;
}

template <int IDX>
void PyOFX_SetHost(OfxHost *host)
{
  PyOFX_AcquireGIL
  
  PyImageEffectPlugin *plugin = gEffectPlugins[IDX];
  
  if (plugin != 0)
  {
    plugin->setHost(host);
  }
  
  PyOFX_ReleaseGIL
}

template <int IDX>
OfxStatus PyOFX_Main(const char *action,
                     const void *handle,
                     OfxPropertySetHandle hInArgs,
                     OfxPropertySetHandle hOutArgs)
{
  PyOFX_AcquireGIL
  
  PyImageEffectPlugin *plugin = gEffectPlugins[IDX];
  
  if (!plugin)
  {
    PyOFX_ReleaseGIL
    return kOfxStatErrBadHandle;
  }
  
  ofx::ImageEffectHost *host = plugin->host();
  
  if (!host)
  {
    PyOFX_ReleaseGIL
    ofx::Log("*** Invalid host");
    return kOfxStatErrFatal;
  }
  
  ofx::PropertySet inArgs(host, hInArgs);
  ofx::PropertySet outArgs(host, hOutArgs);
  
  OfxImageEffectHandle hEffect = (OfxImageEffectHandle) handle;
  
  ofx::Action a = ofx::StringToAction(action);
  
  OfxStatus rv = kOfxStatReplyDefault;
  
  try
  {
    switch (a)
    {
    case ofx::ActionLoad:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Load");
      host->init();
      rv = plugin->load();
      // this means binary has been loaded... as we proxy python plugins,
      // is this aimed at the pyplugin or the proxied python one?
      break;
    }
    case ofx::ActionUnload:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Unload");
      rv = plugin->unload();
      // this means binary has been unload... as we proxy python plugins,
      // is this aimed at the pyplugin or the proxied python one?
      // this could be problematic...
      break;
    }
    case ofx::ActionDescribe:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Describe");
      PyImageEffectDescriptor desc = plugin->descriptor(hEffect);
      rv = desc.describe();
      break;
    }
    case ofx::ActionImageEffectDescribeInContext:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Describe in context");
      // might not be the same handle as in ActionDescribe
      PyImageEffectDescriptor desc = plugin->descriptor(hEffect);
      ofx::ImageEffectContext ctx = ofx::StringToImageEffectContext(inArgs.getString(kOfxImageEffectPropContext, 0));
      rv = desc.describeInContext(ctx);
      break;
    }
    case ofx::ActionCreateInstance:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Create instance");
      plugin->addEffect(hEffect);
      rv = kOfxStatOK;
      break;
    }
    case ofx::ActionDestroyInstance:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Destroy instance");
      plugin->removeEffect(hEffect);
      rv = kOfxStatOK;
      break;
    }
    case ofx::ActionBeginInstanceChanged:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Begin instance changed");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        ofx::ChangeReason reason = ofx::StringToChangeReason(inArgs.getString(kOfxPropChangeReason, 0));
        rv = effect->beginInstanceChanged(reason);
      }
      break;
    }
    case ofx::ActionEndInstanceChanged:
    {
      ofx::DebugLog("OFX Image Effect Plugin: End instance changed");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        ofx::ChangeReason reason = ofx::StringToChangeReason(inArgs.getString(kOfxPropChangeReason, 0));
        rv = effect->endInstanceChanged(reason);
      }
      break;
    }
    case ofx::ActionInstanceChanged:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Instance changed");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        ofx::ImageEffect::InstanceChangedArgs args(host, inArgs);
        rv = effect->instanceChanged(args);
      }
      break;
    }
    case ofx::ActionPurgeCaches:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Purge caches");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        rv = effect->purgeCaches();
      }
      break;
    }
    case ofx::ActionSyncPrivateData:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Sync private data");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        rv = effect->syncPrivateData();
      }
      break;
    }
    case ofx::ActionBeginInstanceEdit:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Begin instance edit");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        rv = effect->beginInstanceEdit();
      }
      break;
    }
    case ofx::ActionEndInstanceEdit:
    {
      ofx::DebugLog("OFX Image Effect Plugin: End instance edit");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        rv = effect->endInstanceEdit();
      }
      break;
    }
    case ofx::ActionImageEffectGetRoD:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Get region of definition");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        ofx::ImageEffect::GetRoDArgs args(host, inArgs);
        rv = effect->getRegionOfDefinition(args);
        if (rv == kOfxStatOK)
        {
          args.setOutputs(outArgs);
        }
      }
      break;
    }
    case ofx::ActionImageEffectGetRoI:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Get regions of interest");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        ofx::ImageEffect::GetRoIArgs args(host, inArgs);
        rv = effect->getRegionsOfInterest(args);
        if (rv == kOfxStatOK)
        {
          args.setOutputs(outArgs);
        }
      }
      break;
    }
    case ofx::ActionImageEffectGetFramesNeeded:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Get frames needed");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        ofx::ImageEffect::GetFramesNeededArgs args(host, inArgs);
        rv = effect->getFramesNeeded(args);
        if (rv == kOfxStatOK)
        {
          args.setOutputs(outArgs);
        }
      }
      break;
    }
    case ofx::ActionImageEffectIsIdentity:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Is identity");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        ofx::ImageEffect::IsIdentityArgs args(host, inArgs);
        rv =  effect->isIdentity(args);
        if (rv == kOfxStatOK)
        {
          args.setOutputs(outArgs);
        }
      }
      break;
    }
    case ofx::ActionImageEffectRender:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Render");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        ofx::ImageEffect::RenderArgs args(host, inArgs);
        rv = effect->render(args);
      }
      break;
    }
    case ofx::ActionImageEffectBeginSequenceRender:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Begin sequence render");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        ofx::ImageEffect::BeginSequenceArgs args(host, inArgs);
        rv = effect->beginSequenceRender(args);
      }
      break;
    }
    case ofx::ActionImageEffectEndSequenceRender:
    {
      ofx::DebugLog("OFX Image Effect Plugin: End sequence render");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        ofx::ImageEffect::EndSequenceArgs args(host, inArgs);
        rv = effect->endSequenceRender(args);
      }
      break;
    }
    case ofx::ActionImageEffectGetClipPreferences:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Get clip preferences");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        ofx::ImageEffect::GetClipPrefArgs args(host);
        rv = effect->getClipPreferences(args);
        if (rv == kOfxStatOK)
        {
          args.setOutputs(outArgs);
        }
      }
      break;
    }
    case ofx::ActionImageEffectGetTimeDomain:
    {
      ofx::DebugLog("OFX Image Effect Plugin: Get time domain");
      PyImageEffect *effect = plugin->getEffect(hEffect);
      if (!effect)
      {
        ofx::Log("*** Invalid effect");
        rv = kOfxStatErrUnknown;
      }
      else
      {
        ofx::ImageEffect::GetTimeDomainArgs args(host);
        rv = effect->getTimeDomain(args);
        if (rv == kOfxStatOK)
        {
          args.setOutputs(outArgs);
        }
      }
      break;
    }
    default:
      break;
    }
    
  }
  catch (ofx::Exception &e)
  {
    ofx::Log("*** Caught exception");
    ofx::Log("***   %s", e.what());
    rv = e.status();
  }
  
  PyOFX_ReleaseGIL
  
  return rv;
}

template <int IDX>
OfxStatus PyOFX_InteractMain(const char *action,
                             const void *handle,
                             OfxPropertySetHandle hInArgs,
                             OfxPropertySetHandle)
{
  PyOFX_AcquireGIL
  
  OfxStatus rv = kOfxStatReplyDefault;
  
  OfxInteractHandle hInteract = (OfxInteractHandle) handle;
  
  PyObject *pluginClass = gInteractPluginClasses[IDX];
  if (pluginClass == 0)
  {
    PyOFX_ReleaseGIL
    
    return kOfxStatErrBadHandle;
  }
  
  PyObject *pplugin = PyObject_GetAttrString(pluginClass, "Instance");
  if (pplugin == 0)
  {
    PyOFX_ReleaseGIL
    
    return kOfxStatErrBadHandle;
  }
  
  PyImageEffectPlugin *plugin = (PyImageEffectPlugin*) ((PyOFXPlugin*)pplugin)->plugin;
  if (plugin == 0)
  {
    PyOFX_ReleaseGIL
    
    return kOfxStatErrBadHandle;
  }
  
  ofx::ImageEffectHost *host = plugin->host();
  if (!host)
  {
    PyOFX_ReleaseGIL
    
    return kOfxStatErrBadHandle;
  }
  
  ofx::PropertySet inArgs(host, hInArgs);
  
  ofx::Action a = ofx::StringToAction(action);
  
  ofx::Interact *ic = (ofx::Interact*) ofx::Interact::GetInteract(hInteract);
  
  try
  {
    switch (a)
    {
    case ofx::ActionDescribe:
    {
      ofx::DebugLog("OFX Overlay Interact: Describe");
      
      PyObject *phost = PyObject_CallObject((PyObject*)&PyOFXImageEffectHostType, NULL);
      ((PyOFXHost*)phost)->host = host;
      
      PyObject *phandle = PyObject_CallObject((PyObject*)&PyOFXHandleType, NULL);
      ((PyOFXHandle*)phandle)->handle = hInteract;
      
      PyObject *args = PyTuple_New(2);
      PyTuple_SetItem(args, 0, phost);
      PyTuple_SetItem(args, 1, phandle);
      
      PyObject *interactDesc = PyObject_CallObject(gInteractDescClasses[IDX], args);
      
      Py_DECREF(args);
      
      PyObject *err = PyErr_Occurred();
      
      if (err != 0)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          rv = (OfxStatus) PyInt_AsLong(pexc->status);
          PyErr_Clear();
        }
        else
        {
          rv = kOfxStatErrFatal;
          LogPythonError();
        }
      }
      else
      {
        ofx::InteractDescriptor *desc = ((PyOFXInteractDescriptor*)interactDesc)->desc;
        
        rv = desc->describe();
        
        // this object does not need stay alive
        // [as a matter of fact, in the C version, it is allocated on the stack]
        delete desc;
      }
      
      Py_XDECREF(interactDesc);
      
      break;
    }
    case ofx::ActionCreateInstance:
    {
      ofx::DebugLog("OFX Overlay Interact: Create instance");
      
      PyObject *phost = PyObject_CallObject((PyObject*)&PyOFXImageEffectHostType, NULL);
      ((PyOFXHost*)phost)->host = host;
      
      PyObject *phandle = PyObject_CallObject((PyObject*)&PyOFXHandleType, NULL);
      ((PyOFXHandle*)phandle)->handle = hInteract;
      
      PyObject *args = PyTuple_New(2);
      PyTuple_SetItem(args, 0, phost);
      PyTuple_SetItem(args, 1, phandle);
      
      PyObject *interact = PyObject_CallObject(gInteractClasses[IDX], args);
      
      Py_DECREF(args);
      
      PyObject *err = PyErr_Occurred();
      
      if (err != 0)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          rv = (OfxStatus) PyInt_AsLong(pexc->status);
          PyErr_Clear();
        }
        else
        {
          rv = kOfxStatErrFatal;
          LogPythonError();
        }
      }
      else
      {
        rv = kOfxStatOK;
      }
      
      // this one we keep
      // [-> ofx::Interact::GetInteract(hInstance)]
      Py_XDECREF(interact);
      
      break;
    }
    case ofx::ActionDestroyInstance:
    {
      ofx::DebugLog("OFX Overlay Interact: Destroy instance");
      if (ic)
      {
        delete ic;
      }
      rv = kOfxStatOK;
      break;
    }
    case ofx::ActionInteractDraw:
    {
      ofx::DebugLog("OFX Overlay Interact: Draw");
      ofx::Interact::DrawArgs args(host, inArgs);
      rv = ic->draw(args);
      break;
    }
    case ofx::ActionInteractPenMotion:
    {
      ofx::DebugLog("OFX Overlay Interact: Pen motion");
      ofx::Interact::PenArgs args(host, inArgs);
      rv = ic->penMotion(args);
      break;
    }
    case ofx::ActionInteractPenUp:
    {
      ofx::DebugLog("OFX Overlay Interact: Pen up");
      ofx::Interact::PenArgs args(host, inArgs);
      rv = ic->penUp(args);
      break;
    }
    case ofx::ActionInteractPenDown:
    {
      ofx::DebugLog("OFX Overlay Interact: Pen down");
      ofx::Interact::PenArgs args(host, inArgs);
      rv = ic->penDown(args);
      break;
    }
    case ofx::ActionInteractKeyDown:
    {
      ofx::DebugLog("OFX Overlay Interact: Key down");
      ofx::Interact::KeyArgs args(host, inArgs);
      rv = ic->keyDown(args);
      break;
    }
    case ofx::ActionInteractKeyUp:
    {
      ofx::DebugLog("OFX Overlay Interact: Key up");
      ofx::Interact::KeyArgs args(host, inArgs);
      rv = ic->keyUp(args);
      break;
    }
    case ofx::ActionInteractKeyRepeat:
    {
      ofx::DebugLog("OFX Overlay Interact: Key repeat");
      ofx::Interact::KeyArgs args(host, inArgs);
      rv = ic->keyRepeat(args);
      break;
    }
    case ofx::ActionInteractGainFocus:
    {
      ofx::DebugLog("OFX Overlay Interact: Gain focus");
      ofx::Interact::FocusArgs args(host, inArgs);
      rv = ic->gainFocus(args);
      break;
    }
    case ofx::ActionInteractLoseFocus:
    {
      ofx::DebugLog("OFX Overlay Interact: Lose focus");
      ofx::Interact::FocusArgs args(host, inArgs);
      rv = ic->loseFocus(args);
      break;
    }
    default:
      break;
    }
    
  }
  catch (ofx::Exception &e)
  {
    ofx::Log("*** Caught exception");
    ofx::Log("***   %s", e.what());
    rv = e.status();
  }
  
  PyOFX_ReleaseGIL
  
  return rv;
}

#endif
