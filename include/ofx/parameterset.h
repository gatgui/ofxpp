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

#ifndef __ofx_parameterset_h__
#define __ofx_parameterset_h__


#include <ofx/booleanparameter.h>
#include <ofx/intparameter.h>
#include <ofx/int2parameter.h>
#include <ofx/int3parameter.h>
#include <ofx/doubleparameter.h>
#include <ofx/double2parameter.h>
#include <ofx/double3parameter.h>
#include <ofx/stringparameter.h>
#include <ofx/choiceparameter.h>
#include <ofx/rgbparameter.h>
#include <ofx/rgbaparameter.h>
#include <ofx/customparameter.h>
#include <ofx/pageparameter.h>
#include <ofx/groupparameter.h>
#include <ofx/pushbuttonparameter.h>
#ifdef OFX_API_1_2
#include <ofx/parametricparameter.h>
#endif

namespace ofx {
  
  
  class ParameterSetDescriptor {
    protected:
      
      OfxParamSetHandle mHandle;
      PropertySet mProps;
      Host *mHost;
    
    public:
      
      ParameterSetDescriptor();
      ParameterSetDescriptor(Host *h, OfxParamSetHandle hdl) throw(Exception);
      ParameterSetDescriptor(const ParameterSetDescriptor &rhs);
      ~ParameterSetDescriptor();
      
      ParameterSetDescriptor& operator=(const ParameterSetDescriptor &rhs);
      
      inline Host* getHost() {
        return mHost;
      }
      
      inline OfxParamSetHandle getHandle() {
        return mHandle;
      }
      
      inline PropertySet& getProperties() {
        return mProps;
      }
      
      // properties
      
      // kOfxPluginPropParamPageOrder -> multi string
      
      // suite
      
      IntParameterDescriptor defineIntParam(const std::string &name) throw(Exception);
      Int2ParameterDescriptor defineInt2Param(const std::string &name) throw(Exception);
      Int3ParameterDescriptor defineInt3Param(const std::string &name) throw(Exception);
      DoubleParameterDescriptor defineDoubleParam(const std::string &name) throw(Exception);
      Double2ParameterDescriptor defineDouble2Param(const std::string &name) throw(Exception);
      Double3ParameterDescriptor defineDouble3Param(const std::string &name) throw(Exception);
      RGBParameterDescriptor defineRGBParam(const std::string &name) throw(Exception);
      RGBAParameterDescriptor defineRGBAParam(const std::string &name) throw(Exception);
      BooleanParameterDescriptor defineBooleanParam(const std::string &name) throw(Exception);
      ChoiceParameterDescriptor defineChoiceParam(const std::string &name) throw(Exception);
      StringParameterDescriptor defineStringParam(const std::string &name) throw(Exception);
      CustomParameterDescriptor defineCustomParam(const std::string &name) throw(Exception);
      GroupParameterDescriptor defineGroupParam(const std::string &name) throw(Exception);
      PageParameterDescriptor definePageParam(const std::string &name) throw(Exception);
      PushButtonParameterDescriptor definePushButtonParam(const std::string &name) throw(Exception);
#ifdef OFX_API_1_2
      ParametricParameterDescriptor defineParametricParam(const std::string &name) throw(Exception);
#endif
  };
  
  class ParameterSet {
    protected:
      
      OfxParamSetHandle mHandle;
      PropertySet mProps;
      Host *mHost;
    
    public:
      
      ParameterSet();
      ParameterSet(Host *h, OfxParamSetHandle hdl) throw(Exception);
      ParameterSet(const ParameterSet &rhs);
      ~ParameterSet();
      
      ParameterSet& operator=(const ParameterSet &rhs);
      
      inline Host* getHost() {
        return mHost;
      }
      
      inline OfxParamSetHandle getHandle() {
        return mHandle;
      }
      
      inline PropertySet& getProperties() {
        return mProps;
      }
      
      // properties
      
      // read/write: kOfxPropParamSetNeedsSyncing
      
      // suite
      
      IntParameter getIntParam(const std::string &name) throw(Exception);
      Int2Parameter getInt2Param(const std::string &name) throw(Exception);
      Int3Parameter getInt3Param(const std::string &name) throw(Exception);
      DoubleParameter getDoubleParam(const std::string &name) throw(Exception);
      Double2Parameter getDouble2Param(const std::string &name) throw(Exception);
      Double3Parameter getDouble3Param(const std::string &name) throw(Exception);
      RGBParameter getRGBParam(const std::string &name) throw(Exception);
      RGBAParameter getRGBAParam(const std::string &name) throw(Exception);
      BooleanParameter getBooleanParam(const std::string &name) throw(Exception);
      ChoiceParameter getChoiceParam(const std::string &name) throw(Exception);
      StringParameter getStringParam(const std::string &name) throw(Exception);
      CustomParameter getCustomParam(const std::string &name) throw(Exception);
      GroupParameter getGroupParam(const std::string &name) throw(Exception);
      PageParameter getPageParam(const std::string &name) throw(Exception);
      PushButtonParameter getPushButtonParam(const std::string &name) throw(Exception);
#ifdef OFX_API_1_2
      ParametricParameter getParametricParam(const std::string &name) throw(Exception);
#endif
      
      void beginEdit(const std::string &label);
      void endEdit();
  };
  
}

#endif
