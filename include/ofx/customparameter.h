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

namespace ofx {
  
  template <class ParameterClass>
  class Interpolator
  {
    public:
      static OfxStatus Interpolate(OfxParamSetHandle instance,
                                   OfxPropertySetHandle inArgs,
                                   OfxPropertySetHandle outArgs)
      {
        Host *host = Host::Get();
        
        if (!host)
        {
          return kOfxStatFailed;
        }
        
        PropertySet ia(host, inArgs);
        PropertySet oa(host, outArgs);
        
        try
        {
          // get input arguments
          std::string name = ia.getString(kOfxPropName, 0);
          Time t = ia.getDouble(kOfxPropTime, 0);
          Time t0 = ia.getDouble(kOfxParamPropInterpolationTime, 0);
          Time t1 = ia.getDouble(kOfxParamPropInterpolationTime, 1);
          std::string v0 = ia.getString(kOfxParamPropCustomValue, 0);
          std::string v1 = ia.getString(kOfxParamPropCustomValue, 1);
          double amount = ia.getDouble(kOfxParamPropInterpolationAmount, 0);
          
          // get custom param class (without using the ParameterSet class)
          OfxParamHandle hParam;
          OfxStatus stat = host->getParameterSuite()->paramGetHandle(instance, name.c_str(), &hParam, NULL);
          if (stat != kOfxStatOK)
          {
            return stat;
          }
          
          ParameterClass param(host, hParam);
          
          if (param.getType() != ParamTypeCustom)
          {
            return kOfxStatFailed;
          }
          
          std::string rv = param.interpolate(t0, v0, t1, v1, t, amount);
          
          oa.setString(kOfxParamPropCustomValue, 0, rv);
          
          return kOfxStatOK;
        }
        catch (Exception &e)
        {
          return e.getStatus();
        }
      }
  };
  
  class CustomParameterDescriptor : public ValueParameterDescriptor {
    public:
      CustomParameterDescriptor();
      CustomParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      CustomParameterDescriptor(const CustomParameterDescriptor &rhs);
      virtual ~CustomParameterDescriptor();
      
      CustomParameterDescriptor& operator=(const CustomParameterDescriptor &rhs);
      
      // properties
      
      std::string getDefault();
      void setDefault(const std::string &v);
      
      void setInterpolator(OfxInterpFunc func);
      OfxInterpFunc getInterpolator();
      
      template <class ParameterClass>
      void setInterpolator() {
        setInterpolator(&Interpolator<ParameterClass>::Interpolate);
      }
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
      
      std::string getDefault();
      OfxInterpFunc getInterpolator();
      
      // suite
      
      std::string getValue() throw(Exception);
      std::string getValueAtTime(Time t) throw(Exception);
      
      void setValue(const std::string &v) throw(Exception);
      void setValueAtTime(Time t, const std::string &v) throw(Exception);
  };
  
}

#endif
