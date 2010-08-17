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

#ifndef __ofx_host_h__
#define __ofx_host_h__

#include <ofxCore.h>
#include <ofxKeySyms.h>
#include <ofxParam.h>
#ifdef OFX_API_1_2
#include <ofxParametricParam.h>
#endif
#include <ofxInteract.h>
#include <ofxImageEffect.h>
#include <ofx/ofx.h>
#include <ofx/exception.h>
#include <ofx/property.h>

namespace ofx {
  
  
  class TimeLineSuite;
  class ProgressSuite;
  class MessageSuite;
  class MemorySuite;
  class MultiThreadSuite;
  
  
  
  class Host : public PropertySet {
    public:
      
      Host(OfxHost *host) throw(Exception);
      virtual ~Host();
      
      virtual void init() throw(Exception);
      
      template <typename T>
      inline T* fetchSuite(const char *name, int ver) {
        return (T*) mHost->fetchSuite(mHost->host, name, ver);
      }
      
      inline operator OfxHost* () {
        return mHost;
      }
      
      inline TimeLineSuite* timeLineSuite() {return mTimeLine;}
      
      inline ProgressSuite* progressSuite() {return mProgress;}
      
      inline MessageSuite* messageSuite() {return mMessage;}
      
      inline MemorySuite* memorySuite() {return mMemory;}
      
      inline MultiThreadSuite* multiThreadSuite() {return mMultiThread;}
      
      inline OfxPropertySuiteV1 *propertySuite() {return mPropSuite;}
      
      inline OfxParameterSuiteV1 *parameterSuite() {return mParamSuite;}
      
      // host OpenFX version
      int APIVersion(int level=0);
      
      int APIMajorVersion();
      
      int APIMinorVersion();
      
      bool checkAPIVersion(int major, int minor);
      
#ifdef OFX_API_1_2
      
      int version(int level=0);
      
      int majorVersion();
      
      int minorVersion();
      
      std::string versionLabel();
      
      void* OSHandle();
      
      OfxParametricParameterSuiteV1 *parametricParameterSuite() {return mParametricParamSuite;}
      
#endif
      
    public:
      
      static Host* Get();
      
    protected:
      
      OfxHost *mHost;
      TimeLineSuite *mTimeLine;
      ProgressSuite *mProgress;
      MessageSuite *mMessage;
      MemorySuite *mMemory;
      MultiThreadSuite *mMultiThread;
      OfxPropertySuiteV1 *mPropSuite;
      OfxParameterSuiteV1 *mParamSuite;
#ifdef OFX_API_1_2
      OfxParametricParameterSuiteV1 *mParametricParamSuite;
#endif
  };
  
  
  
  class ImageEffectHost : public Host {
    public:
      
      ImageEffectHost(OfxHost *);
      virtual ~ImageEffectHost();
      
      virtual void init() throw(Exception);
      
      inline OfxInteractSuiteV1* interactSuite() {return mInteractSuite;}
      
      inline OfxImageEffectSuiteV1 *imageEffectSuite() {return mImageEffectSuite;}
      
      // general properties
      std::string name();
      
      std::string label();
      
      // image effect properties
      bool isBackground();
      
      bool supportsOverlays();
      
      bool supportsMultiResolution();
      
      bool supportsTiles();
      
      bool temporalClipAccess();
      
      int supportedComponentsCount();
      ImageComponent supportedComponent(int idx);
      
      int supportedContextsCount();
      ImageEffectContext supportedContext(int idx);
      
      int supportedPixelDepthsCount();
      BitDepth supportedPixelDepth(int idx);
      
      bool supportsMultipleClipDepths();
      
      bool supportsMultipleClipPARs();
      
      bool setableFrameRate();
      
      bool setableFielding();
      
#ifdef OFX_API_1_2
      
      SequentialRender sequentialRender();
      
      bool supportsParametricAnimation();
      
#endif
      
      // parameter properties
      bool supportsCustomAnimation();
      
      bool supportsStringAnimation();
      
      bool supportsChoiceAnimation();
      
      bool supportsBooleanAnimation();
      
      bool supportsCustomInteract();
      
      int maxParameters();
      
      int maxPages();
      
      void pageRowColumnCount(int *rowCount, int *columnCount);
    
    public:
      
      static ImageEffectHost* Get();
      
    protected:
      
      OfxInteractSuiteV1 *mInteractSuite;
      OfxImageEffectSuiteV1 *mImageEffectSuite;
  };
}

#endif
