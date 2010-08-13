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

#ifndef __ofx_parameter_double_h__
#define __ofx_parameter_double_h__

#include <ofx/parameter.h>

namespace ofx {
  
  class DoubleParameterDescriptor : public ValueParameterDescriptor {
    public:
      DoubleParameterDescriptor();
      DoubleParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      DoubleParameterDescriptor(const DoubleParameterDescriptor &rhs);
      virtual ~DoubleParameterDescriptor();
      
      DoubleParameterDescriptor& operator=(const DoubleParameterDescriptor &rhs);
      
      // properties
      
      double getDefault();
      void setDefault(double v);
      
      double getMin();
      void setMin(double min0);
      
      double getMax();
      void setMax(double max0);
      
      double getDisplayMin();
      void setDisplayMin(double min0);
      
      double getDisplayMax();
      void setDisplayMax(double max0);
      
      double getIncrement();
      void setIncrement(double i);
      
      int getDigits();
      void setDigits(int d);
      
      bool showTimeMarker();
      void setShowTimeMarker(bool);
      
      DoubleParamType getDoubleType();
      void setDoubleType(DoubleParamType t);
      
#ifdef OFX_API_1_2
      Coordinates getDefaultCoordinateSystem();
      void setDefaultCoordinateSystem(Coordinates cs);
#endif
  };
  
  class DoubleParameter : public ValueParameter {
    public:
      DoubleParameter();
      DoubleParameter(Host *h, OfxParamHandle hdl);
      DoubleParameter(const DoubleParameter &rhs);
      virtual ~DoubleParameter();
      
      DoubleParameter& operator=(const DoubleParameter &rhs);
      
      // properties
      
      double getDefault();
      
      double getMin();
      void setMin(double min0);
      
      double getMax();
      void setMax(double max0);
      
      double getDisplayMin();
      void setDisplayMin(double min0);
      
      double getDisplayMax();
      void setDisplayMax(double max0);
      
      double getIncrement();
      void setIncrement(double i);
      
      int getDigits();
      void setDigits(int d);
      
      bool showTimeMarker();
      void setShowTimeMarker(bool);
      
      DoubleParamType getDoubleType();
      
#ifdef OFX_API_1_2
      Coordinates getDefaultCoordinateSystem();
#endif
      // suite
      
      double getValue() throw(Exception);
      double getValueAtTime(Time t) throw(Exception);
      double getDerivative(Time t) throw(Exception);
      double getIntegral(Time t0, Time t1) throw(Exception);
      
      void setValue(double v0) throw(Exception);
      void setValueAtTime(Time t, double v0) throw(Exception);
  };
}

#endif
