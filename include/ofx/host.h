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
  
  class TimeLine;
  class Progress;
  class Message;
  class Memory;
  class MultiThread;
  
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
      
      inline TimeLine* timeLine() {return mTimeLine;}
      inline Progress* progress() {return mProgress;}
      inline Message* message() {return mMessage;}
      inline Memory* memory() {return mMemory;}
      inline MultiThread* multiThread() {return mMultiThread;}
      
      OfxPropertySuiteV1 *propertySuite() {return mPropSuite;}
      OfxParameterSuiteV1 *parameterSuite() {return mParamSuite;}
      
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
      
    protected:
      
      OfxHost *mHost;
      
      TimeLine *mTimeLine;
      Progress *mProgress;
      Message *mMessage;
      Memory *mMemory;
      MultiThread *mMultiThread;
      
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
      bool supportsTemporalClipAccess();
      int supportedComponentsCount();
      ImageComponent getSupportedComponent(int idx);
      int supportedContextsCount();
      ImageEffectContext getSupportedContext(int idx);
      int supportedPixelDepthsCount();
      BitDepth getSupportedPixelDepth(int idx);
      bool supportsMultipleClipDepths();
      bool supportsMultipleClipPARs();
      bool setableFramerate();
      bool setableFielding();
      
#ifdef OFX_API_1_2
      SequentialRender sequentialRender();
      bool supportsParametricParamAnimation();
#endif
      
      // parameter properties
      bool supportsCustomParamAnimation();
      bool supportsStringParamAnimation();
      bool supportsChoiceParamAnimation();
      bool supportsBooleanParamAnimation();
      bool supportsParamCustomInteract();
      int maxParameters();
      int maxParameterPages();
      void parameterPageRowColumnCount(int &rowCount, int &columnCount);
    
    protected:
      
      OfxInteractSuiteV1 *mInteractSuite;
      OfxImageEffectSuiteV1 *mImageEffectSuite;
  };
}

#endif
