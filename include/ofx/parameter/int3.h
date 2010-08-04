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

#ifndef __ofx_parameter_int3_h__
#define __ofx_parameter_int3_h__

#include <ofx/parameter.h>

namespace ofx {
  
  class Int3ParameterDescriptor : public ValueParameterDescriptor {
    public:
      Int3ParameterDescriptor();
      Int3ParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      Int3ParameterDescriptor(const Int3ParameterDescriptor &rhs);
      virtual ~Int3ParameterDescriptor();
      
      Int3ParameterDescriptor& operator=(const Int3ParameterDescriptor &rhs);
      
      // properties
      
      void getDefault(int &v0, int &v1, int &v2);
      void setDefault(int v0, int v1, int v2);
      
      void getMin(int &min0, int &min1, int &min2);
      void setMin(int min0, int min1, int min2);
      
      void getMax(int &max0, int &max1, int &max2);
      void setMax(int max0, int max1, int max2);
      
      void getDisplayMin(int &min0, int &min1, int &max2);
      void setDisplayMin(int min0, int min1, int max2);
      
      void getDisplayMax(int &max0, int &max1, int &max2);
      void setDisplayMax(int max0, int max1, int max2);
      
      void setDimensionLabel(int i, const std::string &name);
      std::string getDimensionLabel(int i);
  };
  
  class Int3Parameter : public ValueParameter {
    public:
      Int3Parameter();
      Int3Parameter(Host *h, OfxParamHandle hdl);
      Int3Parameter(const Int3Parameter &rhs);
      virtual ~Int3Parameter();
      
      Int3Parameter& operator=(const Int3Parameter &rhs);
      
      // properties
      
      void getDefault(int &v0, int &v1, int &v2);
      
      void getMin(int &min0, int &min1, int &min2);
      void setMin(int min0, int min1, int min2);
      
      void getMax(int &max0, int &max1, int &max2);
      void setMax(int max0, int max1, int max2);
      
      void getDisplayMin(int &min0, int &min1, int &max2);
      void setDisplayMin(int min0, int min1, int max2);
      
      void getDisplayMax(int &max0, int &max1, int &max2);
      void setDisplayMax(int max0, int max1, int max2);
      
      std::string getDimensionLabel(int i);
      
      // suite
      
      void getValue(int &v0, int &v1, int &v2) throw(Exception);
      void getValueAtTime(Time t, int &v0, int &v1, int &v2) throw(Exception);
      void getDerivative(Time t, int &v0, int &v1, int &v2) throw(Exception);
      void getIntegral(Time t0, Time t1, int &v0, int &v1, int &v2) throw(Exception);
      
      void setValue(int v0, int v1, int v2) throw(Exception);
      void setValueAtTime(Time t, int v0, int v1, int v2) throw(Exception);
  };
}

#endif
