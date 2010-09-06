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

/** \file rgbaparameter.h
 *  RGBA colour parameter descriptor and instance classes.
 */

#ifndef __ofx_parameter_rgba_h__
#define __ofx_parameter_rgba_h__

#include <ofx/parameter.h>

namespace ofx {
  
  //! RGBA colour parameter descriptor class.
  class RGBAParameterDescriptor : public ValueParameterDescriptor {
    public:
      RGBAParameterDescriptor();
      RGBAParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      RGBAParameterDescriptor(const RGBAParameterDescriptor &rhs);
      virtual ~RGBAParameterDescriptor();
      
      RGBAParameterDescriptor& operator=(const RGBAParameterDescriptor &rhs);
      
      // properties
      
      //! Get default value.
      RGBAColour<double> defaultValue();
      //! Set default value.
      void defaultValue(const RGBAColour<double> &v);
  };
  
  //! RGBA colour parameter instance class.
  class RGBAParameter : public ValueParameter {
    public:
      RGBAParameter();
      RGBAParameter(Host *h, OfxParamHandle hdl);
      RGBAParameter(const RGBAParameter &rhs);
      virtual ~RGBAParameter();
      
      RGBAParameter& operator=(const RGBAParameter &rhs);
      
      // properties
      
      //! Get default value.
      RGBAColour<double> defaultValue();
      
      // suite
      
      //! Get current value.
      RGBAColour<double> getValue() throw(Exception);
      //! Get value at given time.
      RGBAColour<double> getValueAtTime(Time t) throw(Exception);
      //! Get value derivative at given time.
      RGBAColour<double> getDerivative(Time t) throw(Exception);
      //! Get value integral for given range.
      RGBAColour<double> getIntegral(Time t0, Time t1) throw(Exception);
      
      //! Set current value.
      void setValue(const RGBAColour<double> &v) throw(Exception);
      //! Set value at given time.
      void setValueAtTime(Time t, const RGBAColour<double> &v) throw(Exception);
  };
  
}

#endif
