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

#ifndef __ofx_parameter_rgb_h__
#define __ofx_parameter_rgb_h__

#include <ofx/parameter.h>

namespace ofx {
  
  class RGBParameterDescriptor : public ValueParameterDescriptor {
    public:
      RGBParameterDescriptor();
      RGBParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      RGBParameterDescriptor(const RGBParameterDescriptor &rhs);
      virtual ~RGBParameterDescriptor();
      
      RGBParameterDescriptor& operator=(const RGBParameterDescriptor &rhs);
      
      // properties
      
      RGBAColour<double> defaultValue();
      void defaultValue(const RGBAColour<double> &v);
  };
  
  class RGBParameter : public ValueParameter {
    public:
      RGBParameter();
      RGBParameter(Host *h, OfxParamHandle hdl);
      RGBParameter(const RGBParameter &rhs);
      virtual ~RGBParameter();
      
      RGBParameter& operator=(const RGBParameter &rhs);
      
      // properties
      
      RGBAColour<double> defaultValue();
      
      // suite
      
      RGBAColour<double> getValue() throw(Exception);
      RGBAColour<double> getValueAtTime(Time t) throw(Exception);
      RGBAColour<double> getDerivative(Time t) throw(Exception);
      RGBAColour<double> getIntegral(Time t0, Time t1) throw(Exception);
      
      void setValue(const RGBAColour<double> &v) throw(Exception);
      void setValueAtTime(Time t, const RGBAColour<double> &v) throw(Exception);
  };
  
}

#endif
