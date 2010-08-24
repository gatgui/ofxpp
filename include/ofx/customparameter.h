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

#ifndef __ofx_parameter_custom_h__
#define __ofx_parameter_custom_h__

#include <ofx/parameter.h>

typedef OfxStatus (*OfxInterpFunc)(OfxParamSetHandle instance,
                                   OfxPropertySetHandle inArgs,
                                   OfxPropertySetHandle outArgs);

namespace ofx {
  
  typedef std::string (*InterpFunc)(ParameterSet &params,
                                    const std::string &paramName,
                                    Time t,
                                    Time t0,
                                    const std::string &v0,
                                    Time t1,
                                    const std::string &v1,
                                    double amount);
  
  template <InterpFunc F>
  OfxStatus InterpFuncWrap(OfxParamSetHandle instance, OfxPropertySetHandle inArgs, OfxPropertySetHandle outArgs) {
    
    Host *host = Host::Get();
    
    if (!host) {
      return kOfxStatFailed;
    }
    
    ParameterSet params(host, instance);
    PropertySet ia(host, inArgs);
    PropertySet oa(host, outArgs);
    
    try {
      std::string name = ia.getString(kOfxPropName, 0);
      Time ct = ia.getDouble(kOfxPropTime, 0);
      Time t0 = ia.getDouble(kOfxParamPropInterpolationTime, 0);
      Time t1 = ia.getDouble(kOfxParamPropInterpolationTime, 1);
      std::string v0 = ia.getString(kOfxParamPropCustomValue, 0);
      std::string v1 = ia.getString(kOfxParamPropCustomValue, 1);
      double amount = ia.getDouble(kOfxParamPropInterpolationAmount, 0);
      
      std::string rv = F(params, name, ct, t0, v0, t1, v1, amount);
      
      oa.setString(kOfxParamPropCustomValue, 0, rv);
      
      return kOfxStatOK;
      
    } catch (Exception &e) {
      return e.status();
    }
  }
  
  class CustomParameterDescriptor : public ValueParameterDescriptor {
    public:
      CustomParameterDescriptor();
      CustomParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      CustomParameterDescriptor(const CustomParameterDescriptor &rhs);
      virtual ~CustomParameterDescriptor();
      
      CustomParameterDescriptor& operator=(const CustomParameterDescriptor &rhs);
      
      // properties
      
      std::string defaultValue();
      void defaultValue(const std::string &v);
      
      void interpCallback(OfxInterpFunc func);
      OfxInterpFunc interpCallback();
  };
  
  class CustomParameter : public ValueParameter {
    public:
      CustomParameter();
      CustomParameter(Host *h, OfxParamHandle hdl);
      CustomParameter(const CustomParameter &rhs);
      virtual ~CustomParameter();
      
      CustomParameter& operator=(const CustomParameter &rhs);
      
      virtual std::string interpolate(Time t0, const std::string &v0,
                                      Time t1, const std::string &v1,
                                      Time t, double amount);
      
      // properties
      
      std::string defaultValue();
      OfxInterpFunc interpCallback();
      
      // suite
      
      std::string getValue() throw(Exception);
      std::string getValueAtTime(Time t) throw(Exception);
      
      void setValue(const std::string &v) throw(Exception);
      void setValueAtTime(Time t, const std::string &v) throw(Exception);
  };
  
}

#endif
