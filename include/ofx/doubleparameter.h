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

/** \file doubleparameter.h
 *  Double parameter descriptor and instance classes.
 */

#ifndef __ofx_parameter_double_h__
#define __ofx_parameter_double_h__

#include <ofx/parameter.h>

namespace ofx {
  
  //! Double parameter descriptor class.
  class DoubleParameterDescriptor : public ValueParameterDescriptor {
    public:
      DoubleParameterDescriptor();
      DoubleParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      DoubleParameterDescriptor(const DoubleParameterDescriptor &rhs);
      virtual ~DoubleParameterDescriptor();
      
      DoubleParameterDescriptor& operator=(const DoubleParameterDescriptor &rhs);
      
      // properties
      
      //! Get default value.
      double defaultValue();
      //! Set default value.
      void defaultValue(double v);
      
      //! Get minimum value.
      double min();
      //! Set minimum value.
      void min(double min0);
      
      //! Get maximum value.
      double max();
      //! Set maximum value.
      void max(double max0);
      
      //! Get displayed minimum value.
      double displayMin();
      //! Set displayed minimum value.
      void displayMin(double min0);
      
      //! Get displayed maximum value.
      double displayMax();
      //! Set displayed maximum value.
      void displayMax(double max0);
      
      //! Get value increment step.
      double increment();
      //! Set value increment step.
      void increment(double i);
      
      //! Get number of displayed digits.
      int digits();
      //! Set number of displayed digits.
      void digits(int d);
      
      //! Check if time marker should be shown for time types.
      bool showTimeMarker();
      //! Set if time marker should be shown for time types.
      void showTimeMarker(bool);
      
      //! Get value type.
      DoubleParamType doubleType();
      //! Set value type.
      void doubleType(DoubleParamType t);
      
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
  
  //! Double parameter instance class. 
  class DoubleParameter : public ValueParameter {
    public:
      DoubleParameter();
      DoubleParameter(Host *h, OfxParamHandle hdl);
      DoubleParameter(const DoubleParameter &rhs);
      virtual ~DoubleParameter();
      
      DoubleParameter& operator=(const DoubleParameter &rhs);
      
      // properties
      
      //! Get default value.
      double defaultValue();
      
      //! Get minimum value.
      double min();
      //! Set minimum value.
      void min(double min0);
      
      //! Get maximum value.
      double max();
      //! Set maximum value.
      void max(double max0);
      
      //! Get displayed minimum value.
      double displayMin();
      //! Set displayed minimum value.
      void displayMin(double min0);
      
      //! Get displayed maximum value.
      double displayMax();
      //! Set displayed maximum value.
      void displayMax(double max0);
      
      //! Get value increment step.
      double increment();
      //! Set value increment step.
      void increment(double i);
      
      //! Get number of displayed digits.
      int digits();
      //! Set number of displayed digits.
      void digits(int d);
      
      //! Check if time marker should be shown for time types.
      bool showTimeMarker();
      //! Set if time marker should be shown for time types.
      void showTimeMarker(bool);
      
      //! Get value type.
      DoubleParamType doubleType();
      
#ifdef OFX_API_1_2
      /** Get default coordinate system for spacial types.
       * \note OpenFX version >= 1.2.
       */
      Coordinates defaultCoordinateSystem();
#endif
      // suite
      
      //! Get current value.
      double getValue() throw(Exception);
      //! Get value at given time.
      double getValueAtTime(Time t) throw(Exception);
      //! Get value derivative at given time.
      double getDerivative(Time t) throw(Exception);
      //! Get value integral for a given range.
      double getIntegral(Time t0, Time t1) throw(Exception);
      
      //! Set current value.
      void setValue(double v0) throw(Exception);
      //! Set value at given time.
      void setValueAtTime(Time t, double v0) throw(Exception);
  };
}

#endif
