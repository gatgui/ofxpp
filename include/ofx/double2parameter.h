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

#ifndef __ofx_parameter_double2_h__
#define __ofx_parameter_double2_h__

#include <ofx/parameter.h>

namespace ofx {
  
  class Double2ParameterDescriptor : public ValueParameterDescriptor {
    public:
      Double2ParameterDescriptor();
      Double2ParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      Double2ParameterDescriptor(const Double2ParameterDescriptor &rhs);
      virtual ~Double2ParameterDescriptor();
      
      Double2ParameterDescriptor& operator=(const Double2ParameterDescriptor &rhs);
      
      // properties
      
      void getDefault(double &v0, double &v1);
      void setDefault(double v0, double v1);
      
      void getMin(double &min0, double &min1);
      void setMin(double min0, double min1);
      
      void getMax(double &max0, double &max1);
      void setMax(double max0, double max1);
      
      void getDisplayMin(double &min0, double &min1);
      void setDisplayMin(double min0, double min1);
      
      void getDisplayMax(double &max0, double &max1);
      void setDisplayMax(double max0, double max1);
      
      double getIncrement();
      void setIncrement(double i);
      
      int getDigits();
      void setDigits(int d);
      
      DoubleParamType getDoubleType();
      void setDoubleType(DoubleParamType t);
      
      void setDimensionLabel(int i, const std::string &name);
      std::string getDimensionLabel(int i);
      
#ifdef OFX_API_1_2
      Coordinates getDefaultCoordinateSystem();
      void setDefaultCoordinateSystem(Coordinates cs);
#endif
  };
  
  class Double2Parameter : public ValueParameter {
    public:
      Double2Parameter();
      Double2Parameter(Host *h, OfxParamHandle hdl);
      Double2Parameter(const Double2Parameter &rhs);
      virtual ~Double2Parameter();
      
      Double2Parameter& operator=(const Double2Parameter &rhs);
      
      // properties
      
      void getDefault(double &v0, double &v1);
      
      void getMin(double &min0, double &min1);
      void setMin(double min0, double min1);
      
      void getMax(double &max0, double &max1);
      void setMax(double max0, double max1);
      
      void getDisplayMin(double &min0, double &min1);
      void setDisplayMin(double min0, double min1);
      
      void getDisplayMax(double &max0, double &max1);
      void setDisplayMax(double max0, double max1);
      
      double getIncrement();
      void setIncrement(double i);
      
      int getDigits();
      void setDigits(int d);
      
      DoubleParamType getDoubleType();
      
      std::string getDimensionLabel(int i);
      
#ifdef OFX_API_1_2
      Coordinates getDefaultCoordinateSystem();
#endif
      
      // suite
      
      void getValue(double &v0, double &v1) throw(Exception);
      void getValueAtTime(Time t, double &v0, double &v1) throw(Exception);
      void getDerivative(Time t, double &v0, double &v1) throw(Exception);
      void getIntegral(Time t0, Time t1, double &v0, double &v1) throw(Exception);
      
      void setValue(double v0, double v1) throw(Exception);
      void setValueAtTime(Time t, double v0, double v1) throw(Exception);
  };
  
}

#endif
