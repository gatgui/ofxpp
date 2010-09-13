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

/** \file host.h
 *  Host classes.
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
  
  
  //! %Host base class.
  class Host : public PropertySet {
    public:
      
      Host(OfxHost *host) throw(Exception);
      virtual ~Host();
      
      //! Initialize host.
      virtual void init() throw(Exception);
      
      //! Fetch a function suite from host.
      template <typename T>
      inline T* fetchSuite(const char *name, int ver) {
        return (T*) mHost->fetchSuite(mHost->host, name, ver);
      }
      
      //! Get native host pointer.
      inline operator OfxHost* () {
        return mHost;
      }
      
      //! Get time line functions suite object.
      inline TimeLineSuite* timeLineSuite() {return mTimeLine;}
      
      //! Get progress functions suite object.
      inline ProgressSuite* progressSuite() {return mProgress;}
      
      //! Get message functions suite object.
      inline MessageSuite* messageSuite() {return mMessage;}
      
      //! Get memory functions suite object.
      inline MemorySuite* memorySuite() {return mMemory;}
      
      //! Get multi threading functions suite object.
      inline MultiThreadSuite* multiThreadSuite() {return mMultiThread;}
      
      //! Get property functions suite.
      inline OfxPropertySuiteV1 *propertySuite() {return mPropSuite;}
      
      //! Get parameter functions suite.
      inline OfxParameterSuiteV1 *parameterSuite() {return mParamSuite;}
      
      //! Get host API version.
      int APIVersion(int level=0);
      
      //! Get host API major version (level = 0).
      int APIMajorVersion();
      
      //! Get host API minor version (level = 1).
      int APIMinorVersion();
      
      //! Check if host supports a given (major, minor) API version.
      bool checkAPIVersion(int major, int minor);
      
#ifdef OFX_API_1_2
      
      /** Get host version.
       * \note OpenFX version >= 1.2.
       */
      int version(int level=0);
      
      /** Get host major version (level = 0).
       * \note OpenFX version >= 1.2.
       */
      int majorVersion();
      
      /** Get host minor version (level = 1).
       * \note OpenFX version >= 1.2.
       */
      int minorVersion();
      
      /** Get host version label.
       * \note OpenFX version >= 1.2.
       */
      std::string versionLabel();
      
      /** Get host OS specific handle.
       * \note OpenFX version >= 1.2.
       */
      void* OSHandle();
      
      /** Get parametric parameter suite.
       * \note OpenFX version >= 1.2.
       */
      OfxParametricParameterSuiteV1 *parametricParameterSuite() {return mParametricParamSuite;}
      
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
  
  
  //! %Image effect host class.
  class ImageEffectHost : public Host {
    public:
      
      ImageEffectHost(OfxHost *);
      virtual ~ImageEffectHost();
      
      //! Initialize image effect host.
      virtual void init() throw(Exception);
      
      //! Get interact functions suite.
      inline OfxInteractSuiteV1* interactSuite() {return mInteractSuite;}
      
      //! Get image effect functions suite.
      inline OfxImageEffectSuiteV1 *imageEffectSuite() {return mImageEffectSuite;}
      
      // general properties
      
      //! Get host name.
      std::string name();
      
      //! Get host label.
      std::string label();
      
      // image effect properties
      
      //! Check if host is running as a background task.
      bool isBackground();
      
      //! Check if host supports overlay interacts.
      bool supportsOverlays();
      
      //! Check if host supports multiple resolution images for the same effect.
      bool supportsMultiResolution();
      
      //! Check if host supports tiled images.
      bool supportsTiles();
      
      //! Check if host supports random temporal clip access.
      bool temporalClipAccess();
      
      //! Get the number of supported components.
      int supportedComponentsCount();
      //! Get the ith supported components.
      ImageComponent supportedComponent(int idx);
      
      //! Get the number of supported image effect contexts.
      int supportedContextsCount();
      //! Get the ith supported image effect context.
      ImageEffectContext supportedContext(int idx);
      
      //! Get the number of supported pixel depths.
      int supportedPixelDepthsCount();
      //! Get the ith supported pixel depth.
      BitDepth supportedPixelDepth(int idx);
      
      //! Check if host supports clips of differing component depths for the same effect.
      bool supportsMultipleClipDepths();
      
      //! Check if host supports clips if differing pixel aspect ratio for the same effect.
      bool supportsMultipleClipPARs();
      
      //! Check if host allows an effect to set its output clip framerate.
      bool setableFrameRate();
      
      //! Check if host allows an effect to set its output clip fielding.
      bool setableFielding();
      
#ifdef OFX_API_1_2
      
      /** Get host sequantial render support.
       *  \note OpenFX version >= 1.2
       */
      SequentialRender sequentialRender();
      
      /** Check if host supports parametric parameter animation.
       *  \note OpenFX version >= 1.2
       */
      bool supportsParametricAnimation();
      
#endif
      
      // parameter properties
      
      //! Check if host supports custom parameter animation.
      bool supportsCustomAnimation();
      
      //! Check if host supports string parameter animation.
      bool supportsStringAnimation();
      
      //! Check if host supports choice parameter animation.
      bool supportsChoiceAnimation();
      
      //! Check if host supports boolean parameter animation.
      bool supportsBooleanAnimation();
      
      //! Check if host supports parameter custom interacts.
      bool supportsCustomInteract();
      
      //! Get the maxumum number of parameters.
      int maxParameters();
      
      //! Get the maximum number of parameter pages.
      int maxPages();
      
      //! Get the number of rows and columns for parameter pages.
      void pageRowColumnCount(int *rowCount, int *columnCount);
      
    protected:
      
      OfxInteractSuiteV1 *mInteractSuite;
      OfxImageEffectSuiteV1 *mImageEffectSuite;
  };
}

#endif
