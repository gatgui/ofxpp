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

#ifndef __ofx_parameter_int2_h__
#define __ofx_parameter_int2_h__

#include <ofx/parameter.h>

namespace ofx {
  
  class Int2ParameterDescriptor : public ValueParameterDescriptor {
    public:
      Int2ParameterDescriptor();
      Int2ParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      Int2ParameterDescriptor(const Int2ParameterDescriptor &rhs);
      virtual ~Int2ParameterDescriptor();
      
      Int2ParameterDescriptor& operator=(const Int2ParameterDescriptor &rhs);
      
      // properties
      
      void defaultValue(int *v0, int *v1);
      void defaultValue(int v0, int v1);
      
      void min(int *min0, int *min1);
      void min(int min0, int min1);
      
      void max(int *max0, int *max1);
      void max(int max0, int max1);
      
      void displayMin(int *min0, int *min1);
      void displayMin(int min0, int min1);
      
      void displayMax(int *max0, int *max1);
      void displayMax(int max0, int max1);
      
      void dimensionLabel(int i, const std::string &name);
      std::string dimensionLabel(int i);
  };
  
  class Int2Parameter : public ValueParameter {
    public:
      Int2Parameter();
      Int2Parameter(Host *h, OfxParamHandle hdl);
      Int2Parameter(const Int2Parameter &rhs);
      virtual ~Int2Parameter();
      
      Int2Parameter& operator=(const Int2Parameter &rhs);
      
      // properties
      
      void defaultValue(int *v0, int *v1);
      
      void min(int *min0, int *min1);
      void min(int min0, int min1);
      
      void max(int *max0, int *max1);
      void max(int max0, int max1);
      
      void displayMin(int *min0, int *min1);
      void displayMin(int min0, int min1);
      
      void displayMax(int *max0, int *max1);
      void displayMax(int max0, int max1);
      
      std::string dimensionLabel(int i);
      
      // suite
      
      void getValue(int *v0, int *v1) throw(Exception);
      void getValueAtTime(Time t, int *v0, int *v1) throw(Exception);
      void getDerivative(Time t, int *v0, int *v1) throw(Exception);
      void getIntegral(Time t0, Time t1, int *v0, int *v1) throw(Exception);
      
      void setValue(int v0, int v1) throw(Exception);
      void setValueAtTime(Time t, int v0, int v1) throw(Exception);
  };
  
}

#endif
