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

#ifndef __pyofx_common_h__
#define __pyofx_common_h__

#include <Python.h>
#include <structmember.h>
#include <ofx/host.h>
#include <ofx/exception.h>
#include <ofx/message.h>
#include <ofx/memory.h>
#include <ofx/progress.h>
#include <ofx/timeline.h>
#include <ofx/property.h>
#include <ofx/parameter.h>
#include <ofx/parameterset.h>
#include <ofx/image.h>
#include <ofx/clip.h>
#include <ofx/imageeffect.h>
#include <ofx/interact.h>
#include <ofx/plugin.h>
#include <iostream>
#include <map>

typedef struct
{
  PyBaseExceptionObject base;
  PyObject *status;
} PyOFXException;

typedef struct
{
  PyObject_HEAD
  void *handle;
} PyOFXHandle;

typedef struct
{
  PyOFXHandle base;
  int w;
  int h;
  ofx::ImageComponent components;
  ofx::BitDepth pixelDepth;
} PyOFXImageMemoryHandle;

typedef struct
{
  PyObject_HEAD
  ofx::MessageSuite *suite;
} PyOFXMessageSuite;

typedef struct
{
  PyObject_HEAD
  ofx::MemorySuite *suite;
} PyOFXMemorySuite;

// Do no expose MultiThreadSuite

typedef struct
{
  PyObject_HEAD
  ofx::ProgressSuite *suite;
} PyOFXProgressSuite;

typedef struct
{
  PyObject_HEAD
  ofx::TimeLineSuite *suite;
} PyOFXTimeLineSuite;

typedef struct
{
  PyObject_HEAD
  ofx::PropertySet *pset;
} PyOFXPropertySet;

typedef struct
{
  PyObject_HEAD
  ofx::ParameterDescriptor *desc;
} PyOFXParameterDescriptor;

typedef struct
{
  PyOFXParameterDescriptor base;
} PyOFXValueParameterDescriptor;

typedef struct
{
  PyOFXValueParameterDescriptor base;
} PyOFXBooleanParameterDescriptor;

typedef struct
{
  PyOFXValueParameterDescriptor base;
} PyOFXChoiceParameterDescriptor;

typedef struct
{
  PyOFXValueParameterDescriptor base;
} PyOFXCustomParameterDescriptor;

typedef struct
{
  PyOFXValueParameterDescriptor base;
} PyOFXDoubleParameterDescriptor;

typedef struct
{
  PyOFXValueParameterDescriptor base;
} PyOFXDouble2ParameterDescriptor;

typedef struct
{
  PyOFXValueParameterDescriptor base;
} PyOFXDouble3ParameterDescriptor;

typedef struct
{
  PyOFXValueParameterDescriptor base;
} PyOFXIntParameterDescriptor;

typedef struct
{
  PyOFXValueParameterDescriptor base;
} PyOFXInt2ParameterDescriptor;

typedef struct
{
  PyOFXValueParameterDescriptor base;
} PyOFXInt3ParameterDescriptor;

typedef struct
{
  PyOFXValueParameterDescriptor base;
} PyOFXStringParameterDescriptor;

typedef struct
{
  PyOFXValueParameterDescriptor base;
} PyOFXRGBParameterDescriptor;

typedef struct
{
  PyOFXValueParameterDescriptor base;
} PyOFXRGBAParameterDescriptor;

#ifdef OFX_API_1_2
typedef struct
{
  PyOFXValueParameterDescriptor base;
} PyOFXParametricParameterDescriptor;
#endif

typedef struct
{
  PyOFXParameterDescriptor base;
} PyOFXPageParameterDescriptor;

typedef struct
{
  PyOFXParameterDescriptor base;
} PyOFXGroupParameterDescriptor;

typedef struct
{
  PyOFXParameterDescriptor base;
} PyOFXPushButtonParameterDescriptor;

typedef struct
{
  PyObject_HEAD
  ofx::Parameter *param;
} PyOFXParameter;

typedef struct
{
  PyOFXParameter base;
} PyOFXValueParameter;

typedef struct
{
  PyOFXValueParameter base;
} PyOFXBooleanParameter;

typedef struct
{
  PyOFXValueParameter base;
} PyOFXChoiceParameter;

typedef struct
{
  PyOFXValueParameter base;
} PyOFXCustomParameter;

typedef struct
{
  PyOFXValueParameter base;
} PyOFXDoubleParameter;

typedef struct
{
  PyOFXValueParameter base;
} PyOFXDouble2Parameter;

typedef struct
{
  PyOFXValueParameter base;
} PyOFXDouble3Parameter;

typedef struct
{
  PyOFXValueParameter base;
} PyOFXIntParameter;

typedef struct
{
  PyOFXValueParameter base;
} PyOFXInt2Parameter;

typedef struct
{
  PyOFXValueParameter base;
} PyOFXInt3Parameter;

typedef struct
{
  PyOFXValueParameter base;
} PyOFXStringParameter;

typedef struct
{
  PyOFXValueParameter base;
} PyOFXRGBParameter;

typedef struct
{
  PyOFXValueParameter base;
} PyOFXRGBAParameter;

#ifdef OFX_API_1_2
typedef struct
{
  PyOFXValueParameter base;
} PyOFXParametricParameter;
#endif

typedef struct
{
  PyOFXParameter base;
} PyOFXPageParameter;

typedef struct
{
  PyOFXParameter base;
} PyOFXGroupParameter;

typedef struct
{
  PyOFXParameter base;
} PyOFXPushButtonParameter;

typedef struct
{
  PyObject_HEAD
  ofx::ParameterSetDescriptor *desc;
} PyOFXParameterSetDescriptor;

typedef struct
{
  PyObject_HEAD
  ofx::ParameterSet *pset;
} PyOFXParameterSet;

typedef struct
{
  PyObject_HEAD
  ofx::Host *host;
} PyOFXHost;

typedef struct
{
  PyOFXHost host;
} PyOFXImageEffectHost;

typedef struct
{
  PyObject_HEAD
  ofx::ImageBase *imgbase;
} PyOFXImageBase;

typedef struct
{
  PyOFXImageBase base;
  ofx::Image *img;
} PyOFXImage;

#ifdef OFX_API_1_3

typedef struct
{
  PyOFXImageBase base;
  ofx::Texture *tex;
} PyOFXTexture;

#endif

typedef struct
{
  PyObject_HEAD
  ofx::ClipDescriptor *desc;
} PyOFXClipDescriptor;

typedef struct
{
  PyObject_HEAD
  ofx::Clip *clip;
} PyOFXClip;

typedef struct
{
  PyObject_HEAD
  ofx::ImageEffectDescriptor *desc;
} PyOFXImageEffectDescriptor;

typedef struct
{
  PyObject_HEAD
  PyObject *components;
  PyObject *bitDepth;
  PyObject *pixelAspectRatio;
} PyOFXClipPreferences;

typedef struct
{
  PyObject_HEAD
  PyObject *frameRate;
  PyObject *fieldOrder;
  PyObject *preMult;
  PyObject *continuousSamples;
  PyObject *frameVarying;
} PyOFXOutputClipPreferences;

typedef struct
{
  PyObject_HEAD
  ofx::ImageEffect *effect;
} PyOFXImageEffect;

typedef struct
{
  PyObject_HEAD
  ofx::InteractDescriptor *desc;
} PyOFXInteractDescriptor;

typedef struct
{
  PyObject_HEAD
  ofx::Interact *interact;
} PyOFXInteract;

typedef struct
{
  PyObject_HEAD
  ofx::Plugin *plugin;
} PyOFXPlugin;

typedef struct
{
  PyOFXPlugin base;
} PyOFXImageEffectPlugin;

typedef struct
{
  PyObject_HEAD
  std::map<std::string, PyObject*> args;
} PyOFXActionArguments;

typedef struct
{
  PyObject_HEAD
  ofx::RectI rect;
} PyOFXRectI;

typedef struct
{
  PyObject_HEAD
  ofx::RectD rect;
} PyOFXRectD;

typedef struct
{
  PyObject_HEAD
  ofx::RangeI range;
} PyOFXRangeI;

typedef struct
{
  PyObject_HEAD
  ofx::RangeD range;
} PyOFXRangeD;

typedef struct
{
  PyObject_HEAD
  ofx::RGBAColourB colour;
} PyOFXRGBAColourB;

typedef struct
{
  PyObject_HEAD
  ofx::RGBAColourS colour;
} PyOFXRGBAColourS;

typedef struct
{
  PyObject_HEAD
  ofx::RGBAColourF colour;
} PyOFXRGBAColourF;

typedef struct
{
  PyObject_HEAD
  ofx::RGBAColourD colour;
} PyOFXRGBAColourD;

typedef struct
{
  PyObject_HEAD
  ofx::RGBColourB colour;
} PyOFXRGBColourB;

typedef struct
{
  PyObject_HEAD
  ofx::RGBColourS colour;
} PyOFXRGBColourS;

typedef struct
{
  PyObject_HEAD
  ofx::RGBColourF colour;
} PyOFXRGBColourF;

typedef struct
{
  PyObject_HEAD
  ofx::RGBColourD colour;
} PyOFXRGBColourD;

typedef struct
{
  PyObject_HEAD
  ofx::YUVAColourB colour;
} PyOFXYUVAColourB;

typedef struct
{
  PyObject_HEAD
  ofx::YUVAColourS colour;
} PyOFXYUVAColourS;

typedef struct
{
  PyObject_HEAD
  ofx::YUVAColourF colour;
} PyOFXYUVAColourF;

typedef struct
{
  PyObject_HEAD
  ofx::YUVAColourD colour;
} PyOFXYUVAColourD;

typedef struct
{
  PyObject_HEAD
  void *ptr;
  void *base;
  ofx::Rect<int> bounds;
  int pixelBytes;
  int rowBytes;
} PyOFXColourAddress;

typedef struct
{
  PyOFXColourAddress addr;
} PyOFXRGBAColourBAddress;

typedef struct
{
  PyOFXColourAddress addr;
} PyOFXRGBAColourSAddress;

typedef struct
{
  PyOFXColourAddress addr;
} PyOFXRGBAColourFAddress;

typedef struct
{
  PyOFXColourAddress addr;
} PyOFXAColourBAddress;

typedef struct
{
  PyOFXColourAddress addr;
} PyOFXAColourSAddress;

typedef struct
{
  PyOFXColourAddress addr;
} PyOFXAColourFAddress;

typedef struct
{
  PyOFXColourAddress addr;
} PyOFXYUVAColourBAddress;

typedef struct
{
  PyOFXColourAddress addr;
} PyOFXYUVAColourSAddress;

typedef struct
{
  PyOFXColourAddress addr;
} PyOFXYUVAColourFAddress;

#ifdef OFX_API_1_2

typedef struct
{
  PyOFXColourAddress addr;
} PyOFXRGBColourBAddress;

typedef struct
{
  PyOFXColourAddress addr;
} PyOFXRGBColourSAddress;

typedef struct
{
  PyOFXColourAddress addr;
} PyOFXRGBColourFAddress;

#endif
// all the pixels type


extern PyTypeObject PyOFXExceptionType;
extern PyTypeObject PyOFXFailedErrorType;
extern PyTypeObject PyOFXFatalErrorType;
extern PyTypeObject PyOFXUnknownErrorType;
extern PyTypeObject PyOFXMissingHostFeatureErrorType;
extern PyTypeObject PyOFXUnsupportedErrorType;
extern PyTypeObject PyOFXExistsErrorType;
extern PyTypeObject PyOFXFormatErrorType;
extern PyTypeObject PyOFXMemoryErrorType;
extern PyTypeObject PyOFXBadHandleErrorType;
extern PyTypeObject PyOFXBadIndexErrorType;
extern PyTypeObject PyOFXValueErrorType;
extern PyTypeObject PyOFXImageFormatErrorType;
#ifdef OFX_API_1_3
extern PyTypeObject PyOFXGLOutOfMemoryType;
extern PyTypeObject PyOFXGLRenderFailedType;
#endif
extern PyTypeObject PyOFXHostType;
extern PyTypeObject PyOFXImageEffectHostType;
extern PyTypeObject PyOFXMessageSuiteType;
extern PyTypeObject PyOFXMemorySuiteType;
extern PyTypeObject PyOFXProgressSuiteType;
extern PyTypeObject PyOFXTimeLineSuiteType;
extern PyTypeObject PyOFXPropertySetType;
extern PyTypeObject PyOFXHandleType;
extern PyTypeObject PyOFXImageMemoryHandleType;
extern PyTypeObject PyOFXParameterDescriptorType;
extern PyTypeObject PyOFXValueParameterDescriptorType;
extern PyTypeObject PyOFXBooleanParameterDescriptorType;
extern PyTypeObject PyOFXChoiceParameterDescriptorType;
extern PyTypeObject PyOFXCustomParameterDescriptorType;
extern PyTypeObject PyOFXDoubleParameterDescriptorType;
extern PyTypeObject PyOFXDouble2ParameterDescriptorType;
extern PyTypeObject PyOFXDouble3ParameterDescriptorType;
extern PyTypeObject PyOFXIntParameterDescriptorType;
extern PyTypeObject PyOFXInt2ParameterDescriptorType;
extern PyTypeObject PyOFXInt3ParameterDescriptorType;
extern PyTypeObject PyOFXStringParameterDescriptorType;
extern PyTypeObject PyOFXRGBParameterDescriptorType;
extern PyTypeObject PyOFXRGBAParameterDescriptorType;
#ifdef OFX_API_1_2
extern PyTypeObject PyOFXParametricParameterDescriptorType;
#endif
extern PyTypeObject PyOFXPageParameterDescriptorType;
extern PyTypeObject PyOFXGroupParameterDescriptorType;
extern PyTypeObject PyOFXPushButtonParameterDescriptorType;
extern PyTypeObject PyOFXParameterType;
extern PyTypeObject PyOFXValueParameterType;
extern PyTypeObject PyOFXBooleanParameterType;
extern PyTypeObject PyOFXChoiceParameterType;
extern PyTypeObject PyOFXCustomParameterType;
extern PyTypeObject PyOFXDoubleParameterType;
extern PyTypeObject PyOFXDouble2ParameterType;
extern PyTypeObject PyOFXDouble3ParameterType;
extern PyTypeObject PyOFXIntParameterType;
extern PyTypeObject PyOFXInt2ParameterType;
extern PyTypeObject PyOFXInt3ParameterType;
extern PyTypeObject PyOFXStringParameterType;
extern PyTypeObject PyOFXRGBParameterType;
extern PyTypeObject PyOFXRGBAParameterType;
#ifdef OFX_API_1_2
extern PyTypeObject PyOFXParametricParameterType;
#endif
extern PyTypeObject PyOFXPageParameterType;
extern PyTypeObject PyOFXGroupParameterType;
extern PyTypeObject PyOFXPushButtonParameterType;
extern PyTypeObject PyOFXParameterSetType;
extern PyTypeObject PyOFXParameterSetDescriptorType;
extern PyTypeObject PyOFXImageBaseType;
extern PyTypeObject PyOFXImageType;
#ifdef OFX_API_1_3
extern PyTypeObject PyOFXTextureType;
#endif
extern PyTypeObject PyOFXClipDescriptorType;
extern PyTypeObject PyOFXClipType;
extern PyTypeObject PyOFXImageEffectDescriptorType;
extern PyTypeObject PyOFXImageEffectType;
extern PyTypeObject PyOFXClipPreferencesType;
extern PyTypeObject PyOFXOutputClipPreferencesType;
extern PyTypeObject PyOFXInteractDescriptorType;
extern PyTypeObject PyOFXInteractType;
extern PyTypeObject PyOFXPluginType;
extern PyTypeObject PyOFXImageEffectPluginType;
extern PyTypeObject PyOFXActionArgumentsType;
extern PyTypeObject PyOFXRangeIType;
extern PyTypeObject PyOFXRangeDType;
extern PyTypeObject PyOFXRectIType;
extern PyTypeObject PyOFXRectDType;
extern PyTypeObject PyOFXRGBAColourBType;
extern PyTypeObject PyOFXRGBAColourSType;
extern PyTypeObject PyOFXRGBAColourFType;
extern PyTypeObject PyOFXRGBAColourDType;
extern PyTypeObject PyOFXYUVAColourBType;
extern PyTypeObject PyOFXYUVAColourSType;
extern PyTypeObject PyOFXYUVAColourFType;
extern PyTypeObject PyOFXYUVAColourDType;
extern PyTypeObject PyOFXColourAddressType;
extern PyTypeObject PyOFXAColourBAddressType;
extern PyTypeObject PyOFXAColourSAddressType;
extern PyTypeObject PyOFXAColourFAddressType;
extern PyTypeObject PyOFXRGBAColourBAddressType;
extern PyTypeObject PyOFXRGBAColourSAddressType;
extern PyTypeObject PyOFXRGBAColourFAddressType;
extern PyTypeObject PyOFXYUVAColourBAddressType;
extern PyTypeObject PyOFXYUVAColourSAddressType;
extern PyTypeObject PyOFXYUVAColourFAddressType;
#ifdef OFX_API_1_2
extern PyTypeObject PyOFXRGBColourBType;
extern PyTypeObject PyOFXRGBColourSType;
extern PyTypeObject PyOFXRGBColourFType;
extern PyTypeObject PyOFXRGBColourDType;
extern PyTypeObject PyOFXRGBColourBAddressType;
extern PyTypeObject PyOFXRGBColourSAddressType;
extern PyTypeObject PyOFXRGBColourFAddressType;
#endif

class Receiver
{
  public:
    
    inline Receiver(PyObject *prcv)
      : mRcv(prcv)
    {
      if (mRcv)
      {
        Py_INCREF(mRcv);
      }
    }
    
    inline ~Receiver()
    {
      if (mRcv)
      {
        Py_DECREF(mRcv);
      }
    }
    
    inline void* handle()
    {
      void *rv = 0;
      if (mRcv)
      {
        if (PyObject_HasAttrString(mRcv, "handle"))
        {
          PyObject *phdl = PyObject_GetAttrString(mRcv, "handle");
          if (phdl && PyObject_TypeCheck(phdl, &PyOFXHandleType))
          {
            rv = ((PyOFXHandle*)phdl)->handle;
          }
          Py_DECREF(phdl);
        }
      }
      return rv;
    }
  
  protected:
    
    PyObject *mRcv;
};

class PyImageEffectDescriptor : public ofx::ImageEffectDescriptor
{
  public:
    
    PyImageEffectDescriptor();
    PyImageEffectDescriptor(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl) throw(ofx::Exception);
    PyImageEffectDescriptor(const PyImageEffectDescriptor &rhs);
    virtual ~PyImageEffectDescriptor();
    
    PyImageEffectDescriptor& operator=(const PyImageEffectDescriptor &rhs);
    
    virtual OfxStatus describe();
    virtual OfxStatus describeInContext(ofx::ImageEffectContext ctx);
    
    inline void self(PyObject *self)
    {
      if (mSelf)
      {
        Py_DECREF(mSelf);
      }
      mSelf = self;
      if (mSelf)
      {
        Py_INCREF(mSelf);
      }
    }
    
    inline PyObject* self() const
    {
      return mSelf;
    }
    
  protected:
    
    PyObject *mSelf;
};

class PyImageEffect : public ofx::ImageEffect
{
  public:
    
    PyImageEffect();
    PyImageEffect(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl);
    virtual ~PyImageEffect();
    
    virtual OfxStatus beginInstanceChanged(ofx::ChangeReason reason);
    virtual OfxStatus endInstanceChanged(ofx::ChangeReason reason);
    virtual OfxStatus instanceChanged(ofx::ImageEffect::InstanceChangedArgs &args);
    virtual OfxStatus purgeCaches();
    virtual OfxStatus syncPrivateData();
    virtual OfxStatus beginInstanceEdit();
    virtual OfxStatus endInstanceEdit();
    virtual OfxStatus getRegionOfDefinition(ofx::ImageEffect::GetRoDArgs &args);
    virtual OfxStatus getRegionsOfInterest(ofx::ImageEffect::GetRoIArgs &args);
    virtual OfxStatus getFramesNeeded(ofx::ImageEffect::GetFramesNeededArgs &args);
    virtual OfxStatus isIdentity(ofx::ImageEffect::IsIdentityArgs &args);
    virtual OfxStatus render(ofx::ImageEffect::RenderArgs &args);
    virtual OfxStatus beginSequenceRender(ofx::ImageEffect::BeginSequenceArgs &args);
    virtual OfxStatus endSequenceRender(ofx::ImageEffect::EndSequenceArgs &args);
    virtual OfxStatus getClipPreferences(ofx::ImageEffect::GetClipPrefArgs &args);
    virtual OfxStatus getTimeDomain(ofx::ImageEffect::GetTimeDomainArgs &args);
#ifdef OFX_API_1_3
    virtual OfxStatus openGLContextAttached();
    virtual OfxStatus openGLContextDetached();
#endif
    
    inline void self(PyObject *self)
    {
      if (mSelf)
      {
        Py_DECREF(mSelf);
      }
      mSelf = self;
      if (mSelf)
      {
        Py_INCREF(mSelf);
      }
    }
    
    inline PyObject* self() const
    {
      return mSelf;
    }
    
  protected:
    
    PyObject *mSelf;
};

class PyInteractDescriptor : public ofx::InteractDescriptor
{
  public:
    
    PyInteractDescriptor();
    PyInteractDescriptor(ofx::ImageEffectHost *h, OfxInteractHandle hdl) throw(ofx::Exception);
    PyInteractDescriptor(const PyInteractDescriptor &rhs);
    virtual ~PyInteractDescriptor();
    
    PyInteractDescriptor& operator=(const PyInteractDescriptor &rhs);
    
    virtual OfxStatus describe();
    
    inline void self(PyObject *self)
    {
      if (mSelf)
      {
        Py_DECREF(mSelf);
      }
      mSelf = self;
      if (mSelf)
      {
        Py_INCREF(mSelf);
      }
    }
    
    inline PyObject* self() const
    {
      return mSelf;
    }
    
  protected:
    
    PyObject *mSelf;
};

class PyInteract : public ofx::Interact
{
  public:
    
    PyInteract();
    PyInteract(ofx::ImageEffectHost *h, OfxInteractHandle hdl) throw(ofx::Exception);
    virtual ~PyInteract();
    
    virtual OfxStatus draw(ofx::Interact::DrawArgs &args);
    virtual OfxStatus penMotion(ofx::Interact::PenArgs &args);
    virtual OfxStatus penDown(ofx::Interact::PenArgs &args);
    virtual OfxStatus penUp(ofx::Interact::PenArgs &args);
    virtual OfxStatus keyDown(ofx::Interact::KeyArgs &args);
    virtual OfxStatus keyUp(ofx::Interact::KeyArgs &args);
    virtual OfxStatus keyRepeat(ofx::Interact::KeyArgs &args);
    virtual OfxStatus gainFocus(ofx::Interact::FocusArgs &args);
    virtual OfxStatus loseFocus(ofx::Interact::FocusArgs &args);
    
    inline void self(PyObject *self)
    {
      if (mSelf)
      {
        Py_DECREF(mSelf);
      }
      mSelf = self;
      if (mSelf)
      {
        Py_INCREF(mSelf);
      }
    }
    
    inline PyObject* self() const
    {
      return mSelf;
    }
    
  protected:
    
    PyObject *mSelf;
};

class PyPlugin : public ofx::Plugin
{
  public:
    
    PyPlugin();
    virtual ~PyPlugin();
    
    inline void self(PyObject *self)
    {
      if (mSelf != 0)
      {
        Py_DECREF(mSelf);
        mSelf = 0;
      }
      mSelf = self;
      if (mSelf != 0)
      {
        Py_INCREF(mSelf);
      }
    }
    
    inline PyObject* self() const
    {
      return mSelf;
    }
    
  protected:
    
    PyObject *mSelf;
};

class PyImageEffectPlugin : public PyPlugin
{
  public:
    
    typedef std::map<OfxImageEffectHandle, PyImageEffect*> EffectMap;
  
  public:
    
    PyImageEffectPlugin(PyTypeObject *descClass, PyTypeObject *instClass);
    virtual ~PyImageEffectPlugin();
    
    virtual OfxStatus load();
    virtual OfxStatus unload();
    
    void setHost(OfxHost *h);
    ofx::ImageEffectHost* host();
    
    PyImageEffectDescriptor descriptor(OfxImageEffectHandle hdl);
    
    PyImageEffect* addEffect(OfxImageEffectHandle hdl);
    void removeEffect(OfxImageEffectHandle hdl);
    PyImageEffect* getEffect(OfxImageEffectHandle hdl);
    
  protected:
    
    PyTypeObject *mDescClass;
    PyTypeObject *mInstClass;
    
    ofx::ImageEffectHost *mHost;
    EffectMap mEffects;
};


extern bool PyOFX_InitException(PyObject *mod);
extern bool PyOFX_InitTest(PyObject *mod);
extern bool PyOFX_InitHost(PyObject *mod);
extern bool PyOFX_InitMessage(PyObject *mod);
extern bool PyOFX_InitMemory(PyObject *mod);
extern bool PyOFX_InitProgress(PyObject *mod);
extern bool PyOFX_InitTimeLine(PyObject *mod);
extern bool PyOFX_InitHandle(PyObject *mod);
extern bool PyOFX_InitProperty(PyObject *mod);
extern bool PyOFX_InitParameter(PyObject *mod);
extern bool PyOFX_InitParameterSet(PyObject *mod);
extern bool PyOFX_InitImage(PyObject *mod);
extern bool PyOFX_InitClip(PyObject *mod);
extern bool PyOFX_InitImageEffect(PyObject *mod);
extern bool PyOFX_InitInteract(PyObject *mod);
extern bool PyOFX_InitPlugin(PyObject *mod);
extern bool PyOFX_InitPixel(PyObject *mod);

extern void LogPythonError();

extern "C"
{

#ifdef _WIN32
__declspec(dllexport)
#else
__attribute__ ((visibility ("default")))
#endif
bool PyOFX_UseGIL();

#ifdef _WIN32
__declspec(dllexport)
#else
__attribute__ ((visibility ("default")))
#endif
void PyOFX_SetUseGIL(bool yes);

#ifdef _WIN32
__declspec(dllexport)
#else
__attribute__ ((visibility ("default")))
#endif
void PyOFX_Lock();

#ifdef _WIN32
__declspec(dllexport)
#else
__attribute__ ((visibility ("default")))
#endif
void PyOFX_UnLock();

}

#ifdef OFX_API_1_3
#define CATCH_EXTRAS(failed)\
  } catch (ofx::GLOutOfMemory &e) {\
    PyErr_SetString((PyObject*)&PyOFXGLOutOfMemoryType, e.what());\
  } catch (ofx::GLRenderFailed &e) {\
    PyErr_SetString((PyObject*)&PyOFXGLRenderFailedType, e.what());
#else
#define CATCH_EXTRAS(failed)
#endif

#define CATCH(code, failed)\
  failed = true;\
  try {\
    code;\
    failed = false;\
  } catch (ofx::FailedError &e) {\
    PyErr_SetString((PyObject*)&PyOFXFailedErrorType, e.what());\
  } catch (ofx::FatalError &e) {\
    PyErr_SetString((PyObject*)&PyOFXFatalErrorType, e.what());\
  } catch (ofx::UnknownError &e) {\
    PyErr_SetString((PyObject*)&PyOFXUnknownErrorType, e.what());\
  } catch (ofx::MissingHostFeatureError &e) {\
    PyErr_SetString((PyObject*)&PyOFXMissingHostFeatureErrorType, e.what());\
  } catch (ofx::UnsupportedError &e) {\
    PyErr_SetString((PyObject*)&PyOFXUnsupportedErrorType, e.what());\
  } catch (ofx::FormatError &e) {\
    PyErr_SetString((PyObject*)&PyOFXFormatErrorType, e.what());\
  } catch (ofx::MemoryError &e) {\
    PyErr_SetString((PyObject*)&PyOFXMemoryErrorType, e.what());\
  } catch (ofx::ExistsError &e) {\
    PyErr_SetString((PyObject*)&PyOFXExistsErrorType, e.what());\
  } catch (ofx::ValueError &e) {\
    PyErr_SetString((PyObject*)&PyOFXValueErrorType, e.what());\
  } catch (ofx::BadIndexError &e) {\
    PyErr_SetString((PyObject*)&PyOFXBadIndexErrorType, e.what());\
  } catch (ofx::BadHandleError &e) {\
    PyErr_SetString((PyObject*)&PyOFXBadHandleErrorType, e.what());\
  } catch (ofx::ImageFormatError &e) {\
    PyErr_SetString((PyObject*)&PyOFXImageFormatErrorType, e.what());\
  CATCH_EXTRAS(failed)\
  } catch (std::exception &e) {\
    PyErr_SetString(PyExc_RuntimeError, e.what());\
  } catch (...) {\
    PyErr_SetString(PyExc_RuntimeError, "Unknown error");\
  }


#define INIT_TYPE(ptype, name, ctype)\
  memset(&ptype, 0, sizeof(PyTypeObject));\
  ptype.ob_refcnt = 1;\
  ptype.ob_size = 0;\
  ptype.tp_name = name;\
  ptype.tp_basicsize = sizeof(ctype)


#endif
