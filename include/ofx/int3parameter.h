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

/** \file int3parameter.h
 *  3 dimensional integer parameter descriptor and instance classes.
 */

#ifndef __ofx_parameter_int3_h__
#define __ofx_parameter_int3_h__

#include <ofx/parameter.h>

namespace ofx {
  
  //! 3 dimensional integer parameter descriptor class.
  class Int3ParameterDescriptor : public ValueParameterDescriptor {
    public:
      Int3ParameterDescriptor();
      Int3ParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      Int3ParameterDescriptor(const Int3ParameterDescriptor &rhs);
      virtual ~Int3ParameterDescriptor();
      
      Int3ParameterDescriptor& operator=(const Int3ParameterDescriptor &rhs);
      
      // properties
      
      //! Get default value.
      void defaultValue(int *v0, int *v1, int *v2);
      //! Set default value.
      void defaultValue(int v0, int v1, int v2);
      
      //! Get minimum value.
      void min(int *min0, int *min1, int *min2);
      //! Set minimum value.
      void min(int min0, int min1, int min2);
      
      //! Get maximum value.
      void max(int *max0, int *max1, int *max2);
      //! Set maximum value.
      void max(int max0, int max1, int max2);
      
      //! Get displayed minimum value.
      void displayMin(int *min0, int *min1, int *max2);
      //! Set displayed minimum value.
      void displayMin(int min0, int min1, int max2);
      
      //! Get displayed maximum value.
      void displayMax(int *max0, int *max1, int *max2);
      //! Set displayed maximum value.
      void displayMax(int max0, int max1, int max2);
      
      //! Set ith dimension label.
      void dimensionLabel(int i, const std::string &name);
      //! Get ith dimension label.
      std::string dimensionLabel(int i);
  };
  
  //! 3 dimensional integer parameter instance class.
  class Int3Parameter : public ValueParameter {
    public:
      Int3Parameter();
      Int3Parameter(Host *h, OfxParamHandle hdl);
      Int3Parameter(const Int3Parameter &rhs);
      virtual ~Int3Parameter();
      
      Int3Parameter& operator=(const Int3Parameter &rhs);
      
      // properties
      
      //! Get default value.
      void defaultValue(int *v0, int *v1, int *v2);
      
      //! Get minimum value.
      void min(int *min0, int *min1, int *min2);
      //! Set minimum value.
      void min(int min0, int min1, int min2);
      
      //! Get maximum value.
      void max(int *max0, int *max1, int *max2);
      //! Set maximum value.
      void max(int max0, int max1, int max2);
      
      //! Get displayed minimum value.
      void displayMin(int *min0, int *min1, int *max2);
      //! Set displayed minimum value.
      void displayMin(int min0, int min1, int max2);
      
      //! Get displayed maximum value.
      void displayMax(int *max0, int *max1, int *max2);
      //! Set displayed maximum value.
      void displayMax(int max0, int max1, int max2);
      
      //! Get ith dimension label.
      std::string dimensionLabel(int i);
      
      // suite
      
      //! Get current value.
      void getValue(int *v0, int *v1, int *v2) throw(Exception);
      //! Get value at given time.
      void getValueAtTime(Time t, int *v0, int *v1, int *v2) throw(Exception);
      //! Get value derivative at given time.
      void getDerivative(Time t, int *v0, int *v1, int *v2) throw(Exception);
      //! Get value integral for given range.
      void getIntegral(Time t0, Time t1, int *v0, int *v1, int *v2) throw(Exception);
      
      //! Set current value.
      void setValue(int v0, int v1, int v2) throw(Exception);
      //! Set value at given time.
      void setValueAtTime(Time t, int v0, int v1, int v2) throw(Exception);
  };
}

#endif
