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
      
      double defaultValue();
      void defaultValue(double v);
      
      double min();
      void min(double min0);
      
      double max();
      void max(double max0);
      
      double displayMin();
      void displayMin(double min0);
      
      double displayMax();
      void displayMax(double max0);
      
      double increment();
      void increment(double i);
      
      int digits();
      void digits(int d);
      
      bool showTimeMarker();
      void showTimeMarker(bool);
      
      DoubleParamType doubleType();
      void doubleType(DoubleParamType t);
      
#ifdef OFX_API_1_2
      Coordinates defaultCoordinateSystem();
      void defaultCoordinateSystem(Coordinates cs);
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
      
      double defaultValue();
      
      double min();
      void min(double min0);
      
      double max();
      void max(double max0);
      
      double displayMin();
      void displayMin(double min0);
      
      double displayMax();
      void displayMax(double max0);
      
      double increment();
      void increment(double i);
      
      int digits();
      void digits(int d);
      
      bool showTimeMarker();
      void showTimeMarker(bool);
      
      DoubleParamType doubleType();
      
#ifdef OFX_API_1_2
      Coordinates defaultCoordinateSystem();
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
