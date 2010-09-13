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

/** \file customparameter.h
 *  Custom parameter descriptor and instance classes.
 */

#ifndef __ofx_parameter_custom_h__
#define __ofx_parameter_custom_h__

#include <ofx/parameter.h>

//! Native custom parameter interpolation callback prototype.
typedef OfxStatus (*OfxInterpFunc)(OfxParamSetHandle instance,
                                   OfxPropertySetHandle inArgs,
                                   OfxPropertySetHandle outArgs);

namespace ofx {
  
  /** Custom parameter interpolation callback prototype.
   *  \param[in] params %Parameter set the interpolated custom parameter originates from.
   *  \param[in] paramName Name of the custom parameter being interpolated.
   *  \param[in] t %Time to compute the interpolated value at.
   *  \param[in] t0 %Time of the previous key frame.
   *  \param[in] v0 Value of the previous key frame.
   *  \param[in] t1 %Time of the next key frame.
   *  \param[in] v1 Value of the next key frame.
   *  \param[in] amount Interpolation amount in the range [0, 1].
   *  \return Interpolated value.
   */
  typedef std::string (*InterpFunc)(ParameterSet &params,
                                    const std::string &paramName,
                                    Time t,
                                    Time t0,
                                    const std::string &v0,
                                    Time t1,
                                    const std::string &v1,
                                    double amount);
  
  /** Custom parameter interpolation callback wrapper.
   *  Wherever an OfxInterpFunc is expected, you can use ofx::InterpFuncWrap<MyCustomInterpolator> instead.\n
   *  MyCustomInterpolator must match the ofx::InterpFunc prototype.
   */
  template <InterpFunc F>
  OfxStatus InterpFuncWrap(OfxParamSetHandle instance, OfxPropertySetHandle inArgs, OfxPropertySetHandle outArgs) {
    
    ImageEffect *effect = ImageEffect::GetEffectForParams(instance);
    
    if (!effect) {
      return kOfxStatFailed;
    }
    
    Host *host = effect->host();
    
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
  
  //! Custom parameter descriptor class.
  class CustomParameterDescriptor : public ValueParameterDescriptor {
    public:
      CustomParameterDescriptor();
      CustomParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      CustomParameterDescriptor(const CustomParameterDescriptor &rhs);
      virtual ~CustomParameterDescriptor();
      
      CustomParameterDescriptor& operator=(const CustomParameterDescriptor &rhs);
      
      // properties
      
      //! Get default value.
      std::string defaultValue();
      //! Set default value.
      void defaultValue(const std::string &v);
      
      //! Set interpolation callback.
      void interpCallback(OfxInterpFunc func);
      //! Get interpolation callback.
      OfxInterpFunc interpCallback();
  };
  
  //! Custom parameter instance class.
  class CustomParameter : public ValueParameter {
    public:
      CustomParameter();
      CustomParameter(Host *h, OfxParamHandle hdl);
      CustomParameter(const CustomParameter &rhs);
      virtual ~CustomParameter();
      
      CustomParameter& operator=(const CustomParameter &rhs);
      
      // properties
      
      //! Get default value.
      std::string defaultValue();
      //! Set default value.
      OfxInterpFunc interpCallback();
      
      // suite
      
      //! Get current value.
      std::string getValue() throw(Exception);
      //! Get value at given time.
      std::string getValueAtTime(Time t) throw(Exception);
      
      //! Set current value.
      void setValue(const std::string &v) throw(Exception);
      //! Set value at given time.
      void setValueAtTime(Time t, const std::string &v) throw(Exception);
  };
  
}

#endif
