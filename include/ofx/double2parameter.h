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

/** \file double2parameter.h
 *  2 dimensional double parameter descriptor and instance classes.
 */

#ifndef __ofx_parameter_double2_h__
#define __ofx_parameter_double2_h__

#include <ofx/parameter.h>

namespace ofx {
  
  //! 2 dimensional double parameter descriptor class.
  class Double2ParameterDescriptor : public ValueParameterDescriptor {
    public:
      Double2ParameterDescriptor();
      Double2ParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      Double2ParameterDescriptor(const Double2ParameterDescriptor &rhs);
      virtual ~Double2ParameterDescriptor();
      
      Double2ParameterDescriptor& operator=(const Double2ParameterDescriptor &rhs);
      
      // properties
      
      //! Get default value.
      void defaultValue(double *v0, double *v1);
      //! Set default value.
      void defaultValue(double v0, double v1);
      
      //! Get minimum value.
      void min(double *min0, double *min1);
      //! Set minimum value.
      void min(double min0, double min1);
      
      //! Get maximum value.
      void max(double *max0, double *max1);
      //! Set maximum value.
      void max(double max0, double max1);
      
      //! Get displayed minimum value.
      void displayMin(double *min0, double *min1);
      //! Set displayed minimum value.
      void displayMin(double min0, double min1);
      
      //! Get displayed maximum value.
      void displayMax(double *max0, double *max1);
      //! Set displayed maximum value.
      void displayMax(double max0, double max1);
      
      //! Get value increment step.
      double increment();
      //! Set value increment step.
      void increment(double i);
      
      //! Get number of displayed digits.
      int digits();
      //! Set number of displayed digits.
      void digits(int d);
      
      //! Get value type.
      DoubleParamType doubleType();
      //! Set value type.
      void doubleType(DoubleParamType t);
      
      //! Set ith dimension label.
      void dimensionLabel(int i, const std::string &name);
      //! Get ith dimension label.
      std::string dimensionLabel(int i);
      
#ifdef OFX_API_1_2
      /** Get default coordinate system for spacial types.
       * \note OpenFX version >= 1.2.
       */
      Coordinates defaultCoordinateSystem();
      /** Set default coordinate system for spacial types.
       * \note OpenFX version >= 1.2.
       */
      void defaultCoordinateSystem(Coordinates cs);
#endif
  };
  
  //! 2 dimensional double parameter instance class.
  class Double2Parameter : public ValueParameter {
    public:
      Double2Parameter();
      Double2Parameter(Host *h, OfxParamHandle hdl);
      Double2Parameter(const Double2Parameter &rhs);
      virtual ~Double2Parameter();
      
      Double2Parameter& operator=(const Double2Parameter &rhs);
      
      // properties
      
      //! Get default value.
      void defaultValue(double *v0, double *v1);
      
      //! Get minimum value.
      void min(double *min0, double *min1);
      //! Set minimum value.
      void min(double min0, double min1);
      
      //! Get maximum value.
      void max(double *max0, double *max1);
      //! Set maximum value.
      void max(double max0, double max1);
      
      //! Get displayed minimum value.
      void displayMin(double *min0, double *min1);
      //! Set displayed minimum value.
      void displayMin(double min0, double min1);
      
      //! Get displayed maximum value.
      void displayMax(double *max0, double *max1);
      //! Set displayed maximum value.
      void displayMax(double max0, double max1);
      
      //! Get value increment step.
      double increment();
      //! Set value increment step.
      void increment(double i);
      
      //! Get number of displayed digits.
      int digits();
      //! Set number of displayed digits.
      void digits(int d);
      
      //! Get value tyoe.
      DoubleParamType doubleType();
      
      //! Get ith dimension label.
      std::string dimensionLabel(int i);
      
#ifdef OFX_API_1_2
      /** Get default coordinate system for spacial types.
       * \note OpenFX version >= 1.2.
       */
      Coordinates defaultCoordinateSystem();
#endif
      
      // suite
      
      //! Get current value.
      void getValue(double *v0, double *v1) throw(Exception);
      //! Get value at given time.
      void getValueAtTime(Time t, double *v0, double *v1) throw(Exception);
      //! Get value derivative at given time.
      void getDerivative(Time t, double *v0, double *v1) throw(Exception);
      //! Get value integral for a given range.
      void getIntegral(Time t0, Time t1, double *v0, double *v1) throw(Exception);
      
      //! Set current value.
      void setValue(double v0, double v1) throw(Exception);
      //! Set value at given time.
      void setValueAtTime(Time t, double v0, double v1) throw(Exception);
  };
  
}

#endif
