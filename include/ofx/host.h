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
      
    protected:
      
      OfxHost *mHost;
      
      TimeLine *mTimeLine;
      Progress *mProgress;
      Message *mMessage;
      Memory *mMemory;
      MultiThread *mMultiThread;
      
      OfxPropertySuiteV1 *mPropSuite;
      OfxParameterSuiteV1 *mParamSuite;
  };
  
  class ImageEffectHost : public Host {
    public:
      
      ImageEffectHost(OfxHost *);
      virtual ~ImageEffectHost();
      
      virtual void init() throw(Exception);
      
      inline OfxInteractSuiteV1* interactSuite() {return mInteractSuite;}
      inline OfxImageEffectSuiteV1 *imageEffectSuite() {return mImageEffectSuite;}
      
      // general properties
      std::string name() throw(Exception);
      std::string label() throw(Exception);
      
      // image effect properties
      bool isBackground() throw(Exception);
      bool supportsOverlays() throw(Exception);
      bool supportsMultiResolution() throw(Exception);
      bool supportsTiles() throw(Exception);
      bool supportsTemporalClipAccess() throw(Exception);
      int supportedComponentsCount() throw(Exception);
      ImageComponent getSupportedComponent(int idx) throw(Exception);
      int supportedContextsCount() throw(Exception);
      ImageEffectContext getSupportedContext(int idx) throw(Exception);
      int supportedPixelDepthsCount() throw(Exception);
      BitDepth getSupportedPixelDepth(int idx) throw(Exception);
      bool supportsMultipleClipDepths() throw(Exception);
      bool supportsMultipleClipPARs() throw(Exception);
      bool setableFramerate() throw(Exception);
      bool setableFielding() throw(Exception);
      
      // parameter properties
      bool supportsCustomParamAnimation() throw(Exception);
      bool supportsStringParamAnimation() throw(Exception);
      bool supportsChoiceParamAnimation() throw(Exception);
      bool supportsBooleanParamAnimation() throw(Exception);
      bool supportsParamCustomInteract() throw(Exception);
      int maxParameters() throw(Exception);
      int maxParameterPages() throw(Exception);
      void parameterPageRowColumnCount(int &rowCount, int &columnCount) throw(Exception);
    
    protected:
      
      OfxInteractSuiteV1 *mInteractSuite;
      OfxImageEffectSuiteV1 *mImageEffectSuite;
  };
}

#endif
