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
      
      inline TimeLineSuite* getTimeLineSuite() {return mTimeLine;}
      
      inline ProgressSuite* getProgressSuite() {return mProgress;}
      
      inline MessageSuite* getMessageSuite() {return mMessage;}
      
      inline MemorySuite* getMemorySuite() {return mMemory;}
      
      inline MultiThreadSuite* getMultiThreadSuite() {return mMultiThread;}
      
      OfxPropertySuiteV1 *getPropertySuite() {return mPropSuite;}
      
      OfxParameterSuiteV1 *getParameterSuite() {return mParamSuite;}
      
      // host OpenFX version
      int getAPIVersion(int level=0);
      
      int getAPIMajorVersion();
      
      int getAPIMinorVersion();
      
      bool checkAPIVersion(int major, int minor);
      
#ifdef OFX_API_1_2
      
      int getVersion(int level=0);
      
      int getMajorVersion();
      
      int getMinorVersion();
      
      std::string getVersionLabel();
      
      void* getOSHandle();
      
      OfxParametricParameterSuiteV1 *getParametricParameterSuite() {return mParametricParamSuite;}
      
#endif
      
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
      
      inline OfxInteractSuiteV1* getInteractSuite() {return mInteractSuite;}
      
      inline OfxImageEffectSuiteV1 *getImageEffectSuite() {return mImageEffectSuite;}
      
      // general properties
      std::string getName();
      
      std::string getLabel();
      
      // image effect properties
      bool isBackground();
      
      bool supportOverlays();
      
      bool supportMultiResolution();
      
      bool supportTiles();
      
      bool supportTemporalClipAccess();
      
      int getSupportedComponentsCount();
      
      ImageComponent getSupportedComponent(int idx);
      
      int getSupportedContextsCount();
      
      ImageEffectContext getSupportedContext(int idx);
      
      int getSupportedPixelDepthsCount();
      
      BitDepth getSupportedPixelDepth(int idx);
      
      bool supportMultipleClipDepths();
      
      bool supportMultipleClipPARs();
      
      bool isFramerateSetable();
      
      bool isFieldingSetable();
      
#ifdef OFX_API_1_2
      
      SequentialRender getSequentialRender();
      
      bool supportParametricParamAnimation();
      
#endif
      
      // parameter properties
      bool supportCustomParamAnimation();
      
      bool supportStringParamAnimation();
      
      bool supportChoiceParamAnimation();
      
      bool supportBooleanParamAnimation();
      
      bool supportParamCustomInteract();
      
      int getMaxParameters();
      
      int getMaxParameterPages();
      
      void getParameterPageRowColumnCount(int &rowCount, int &columnCount);
    
    protected:
      
      OfxInteractSuiteV1 *mInteractSuite;
      OfxImageEffectSuiteV1 *mImageEffectSuite;
  };
}

#endif
