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

/** \file parameterset.h
 *  %Parameter set descriptor and instance classes.
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
  
  //! %Parameter set descriptor classe.
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
      
      //! Get host object.
      inline Host* host() {
        return mHost;
      }
      
      //! Get native handle.
      inline OfxParamSetHandle handle() {
        return mHandle;
      }
      
      //! Get associated properties.
      inline PropertySet& properties() {
        return mProps;
      }
      
      // properties
      
      //! Get number of ordered pages.
      int pageOrderCount();
      //! Get the ith page name.
      std::string pageOrder(int idx);
      //! Set the ith page name.
      void pageOrder(int idx, const std::string &page);
      
      // suite
      
      //! Add an integer parameter.
      IntParameterDescriptor defineIntParam(const std::string &name) throw(Exception);
      //! Add an 2 dimensional integer parameter.
      Int2ParameterDescriptor defineInt2Param(const std::string &name) throw(Exception);
      //! Add an 3 dimensional integer parameter.
      Int3ParameterDescriptor defineInt3Param(const std::string &name) throw(Exception);
      //! Add a double parameter.
      DoubleParameterDescriptor defineDoubleParam(const std::string &name) throw(Exception);
      //! Add an 2 dimensional double parameter.
      Double2ParameterDescriptor defineDouble2Param(const std::string &name) throw(Exception);
      //! Add an 3 dimensional double parameter.
      Double3ParameterDescriptor defineDouble3Param(const std::string &name) throw(Exception);
      //! Add a RGB colour parameter.
      RGBParameterDescriptor defineRGBParam(const std::string &name) throw(Exception);
      //! Add a RGBA colour parameter.
      RGBAParameterDescriptor defineRGBAParam(const std::string &name) throw(Exception);
      //! Add a boolean parameter.
      BooleanParameterDescriptor defineBooleanParam(const std::string &name) throw(Exception);
      //! Add a choice parameter.
      ChoiceParameterDescriptor defineChoiceParam(const std::string &name) throw(Exception);
      //! Add a string parameter.
      StringParameterDescriptor defineStringParam(const std::string &name) throw(Exception);
      //! Add a custom parameter.
      CustomParameterDescriptor defineCustomParam(const std::string &name) throw(Exception);
      //! Add a group parameter.
      GroupParameterDescriptor defineGroupParam(const std::string &name) throw(Exception);
      //! Add a page parameter.
      PageParameterDescriptor definePageParam(const std::string &name) throw(Exception);
      //! Add a button parameter.
      PushButtonParameterDescriptor definePushButtonParam(const std::string &name) throw(Exception);
#ifdef OFX_API_1_2
      /** Add a parametric parameter.
       *  \note OpenFX version >= 1.2
       */
      ParametricParameterDescriptor defineParametricParam(const std::string &name) throw(Exception);
#endif
  };
  
  //! %Parameter set instance classe.
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
      
      //! Get host object.
      inline Host* host() {
        return mHost;
      }
      
      //! Get native handle.
      inline OfxParamSetHandle handle() {
        return mHandle;
      }
      
      //! Get associated properties.
      inline PropertySet& properties() {
        return mProps;
      }
      
      // properties
      
      //! Get number of ordered pages.
      int pageOrderCount();
      //! Get the ith page name.
      std::string pageOrder(int idx);
      
#ifdef OFX_API_1_2
      
      /** Check if plugin needs to resync its private data.
       *  \note OpenFX version >= 1.2.
       */
      bool needsSyncing();
      
      /** Set if plugin needs to resync its private data.
       *  \note OpenFX version >= 1.2.
       */
      void needsSyncing(bool v);
      
#endif
      
      // suite
      
      //! Get named integer parameter.
      IntParameter getIntParam(const std::string &name) throw(Exception);
      //! Get named 2 dimensional integer parameter.
      Int2Parameter getInt2Param(const std::string &name) throw(Exception);
      //! Get named 3 dimensional integer parameter.
      Int3Parameter getInt3Param(const std::string &name) throw(Exception);
      //! Get named double parameter.
      DoubleParameter getDoubleParam(const std::string &name) throw(Exception);
      //! Get named 2 dimensional double parameter.
      Double2Parameter getDouble2Param(const std::string &name) throw(Exception);
      //! Get named 3 dimensional double parameter.
      Double3Parameter getDouble3Param(const std::string &name) throw(Exception);
      //! Get named RGB colour parameter.
      RGBParameter getRGBParam(const std::string &name) throw(Exception);
      //! Get named RGBA colour parameter.
      RGBAParameter getRGBAParam(const std::string &name) throw(Exception);
      //! Get named boolean parameter.
      BooleanParameter getBooleanParam(const std::string &name) throw(Exception);
      //! Get named choice parameter.
      ChoiceParameter getChoiceParam(const std::string &name) throw(Exception);
      //! Get named string parameter.
      StringParameter getStringParam(const std::string &name) throw(Exception);
      //! Get named custom parameter.
      CustomParameter getCustomParam(const std::string &name) throw(Exception);
      //! Get named group parameter.
      GroupParameter getGroupParam(const std::string &name) throw(Exception);
      //! Get named page parameter.
      PageParameter getPageParam(const std::string &name) throw(Exception);
      //! Get named button parameter.
      PushButtonParameter getPushButtonParam(const std::string &name) throw(Exception);
#ifdef OFX_API_1_2
      /** Get named parametric parameter.
       *  \note OpenFX version >= 1.2
       */
      ParametricParameter getParametricParam(const std::string &name) throw(Exception);
#endif
      
      //! Start a named group of parameter edits.
      void beginEdit(const std::string &label);
      //! End current parameter edits group.
      void endEdit();
  };
  
}

#endif
