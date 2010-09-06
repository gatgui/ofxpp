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

/** \file double3parameter.h
 *  3 dimensional double parameter descriptor and instance classes.
 */

#ifndef __ofx_parameter_double3_h__
#define __ofx_parameter_double3_h__

#include <ofx/parameter.h>

namespace ofx {
  
  //! 3 dimensional double parameter descriptor class.
  class Double3ParameterDescriptor : public ValueParameterDescriptor {
    public:
      Double3ParameterDescriptor();
      Double3ParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      Double3ParameterDescriptor(const Double3ParameterDescriptor &rhs);
      virtual ~Double3ParameterDescriptor();
      
      Double3ParameterDescriptor& operator=(const Double3ParameterDescriptor &rhs);
      
      // properties
      
      //! Get default value.
      void defaultValue(double *v0, double *v1, double *v2);
      //! Set default value.
      void defaultValue(double v0, double v1, double v2);
      
      //! Get minimum value.
      void min(double *min0, double *min1, double *min2);
      //! Set minimum value.
      void min(double min0, double min1, double min2);
      
      //! Get maximum value.
      void max(double *max0, double *max1, double *max2);
      //! Set maximum value.
      void max(double max0, double max1, double max2);
      
      //! Get displayed minimum value.
      void displayMin(double *min0, double *min1, double *max2);
      //! Set displayed minimum value.
      void displayMin(double min0, double min1, double max2);
      
      //! Get displayed maximum value.
      void displayMax(double *max0, double *max1, double *max2);
      //! Set displayed maximum value.
      void displayMax(double max0, double max1, double max2);
      
      //! Get value increment step.
      double increment();
      //! Set value increment step.
      void increment(double i);
      
      //! Get number of displayed digits
      int digits();
      //! Set number of displayed digits
      void digits(int d);
      
      //! Get value type.
      DoubleParamType doubleType();
      //! Set value type.
      void doubleType(DoubleParamType t);
      
      //! Set ith dimension label.
      void dimensionLabel(int i, const std::string &name);
      //! Get ith dimension label.
      std::string dimensionLabel(int i);
      
      /*
#ifdef OFX_API_1_2
      Coordinates defaultCoordinateSystem();
      void defaultCoordinateSystem(Coordinates cs);
#endif
      */
  };
  
  //! 3 dimensional double parameter instance class.
  class Double3Parameter : public ValueParameter {
    public:
      Double3Parameter();
      Double3Parameter(Host *h, OfxParamHandle hdl);
      Double3Parameter(const Double3Parameter &rhs);
      virtual ~Double3Parameter();
      
      Double3Parameter& operator=(const Double3Parameter &rhs);
      
      // properties
      
      //! Get default value.
      void defaultValue(double *v0, double *v1, double *v2);
      
      //! Get minimum value.
      void min(double *min0, double *min1, double *min2);
      //! Set minimum value.
      void min(double min0, double min1, double min2);
      
      //! Get maximum value.
      void max(double *max0, double *max1, double *max2);
      //! Set maximum value.
      void max(double max0, double max1, double max2);
      
      //! Get displayed minimum value.
      void displayMin(double *min0, double *min1, double *max2);
      //! Set displayed minimum value.
      void displayMin(double min0, double min1, double max2);
      
      //! Get displayed maximum value.
      void displayMax(double *max0, double *max1, double *max2);
      //! Set displayed maximum value.
      void displayMax(double max0, double max1, double max2);
      
      //! Get value increment step.
      double increment();
      //! Set value increment step.
      void increment(double i);
      
      //! Get number of displayed digits
      int digits();
      //! Set number of displayed digits
      void digits(int d);
      
      //! Get value type.
      DoubleParamType doubleType();
      
      //! Get ith dimension label.
      std::string dimensionLabel(int i);
      
      /*
#ifdef OFX_API_1_2
      Coordinates defaultCoordinateSystem();
#endif
      */
      
      // suite
      
      //! Get current value.
      void getValue(double *v0, double *v1, double *v2) throw(Exception);
      //! Get value at given time.
      void getValueAtTime(Time t, double *v0, double *v1, double *v2) throw(Exception);
      //! Get value derivative at given time.
      void getDerivative(Time t, double *v0, double *v1, double *v2) throw(Exception);
      //! Get value integral for a given range.
      void getIntegral(Time t0, Time t1, double *v0, double *v1, double *v2) throw(Exception);
      
      //! Set current value.
      void setValue(double v0, double v1, double v2) throw(Exception);
      //! Set value at given time.
      void setValueAtTime(Time t, double v0, double v1, double v2) throw(Exception);
  };
  
}

#endif
