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

/** \file intparameter.h
 *  Integer parameter descriptor and instance classes.
 */

#ifndef __ofx_parameter_int_h__
#define __ofx_parameter_int_h__

#include <ofx/parameter.h>

namespace ofx {
  
  //! Integer parameter descriptor class.
  class IntParameterDescriptor : public ValueParameterDescriptor {
    public:
      IntParameterDescriptor();
      IntParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      IntParameterDescriptor(const IntParameterDescriptor &rhs);
      virtual ~IntParameterDescriptor();
      
      IntParameterDescriptor& operator=(const IntParameterDescriptor &rhs);
      
      // properties
      
      //! Get default value.
      int defaultValue();
      //! Set default value.
      void defaultValue(int v);
      
      //! Get minimum value.
      int min();
      //! Set minimum value.
      void min(int v);
      
      //! Get maximum value.
      int max();
      //! Get maximum value.
      void max(int v);
      
      //! Get displayed minimum value.
      int displayMin();
      //! Set displayed minimum value.
      void displayMin(int v);
      
      //! Get displayed maximum value.
      int displayMax();
      //! Set displayed maximum value.
      void displayMax(int v);
  };
  
  //! Integer parameter instance class.
  class IntParameter : public ValueParameter {
    public:
      IntParameter();
      IntParameter(Host *h, OfxParamHandle hdl);
      IntParameter(const IntParameter &rhs);
      virtual ~IntParameter();
      
      IntParameter& operator=(const IntParameter &rhs);
      
      // properties
      
      //! Get default value.
      int defaultValue();
      
      //! Get minimum value.
      int min();
      //! Set minimum value.
      void min(int v);
      
      //! Get maximum value.
      int max();
      //! Set maximum value.
      void max(int v);
      
      //! Get displayed minimum value.
      int displayMin();
      //! Set displayed minimum value.
      void displayMin(int v);
      
      //! Get displayed maximum value.
      int displayMax();
      //! Set displayed maximum value.
      void displayMax(int v);
      
      // suite
      
      //! Get current value.
      int getValue() throw(Exception);
      //! Get value at given time.
      int getValueAtTime(Time t) throw(Exception);
      //! Get value derivative at given time.
      int getDerivative(Time t) throw(Exception);
      //! Get value integral for given range.
      int getIntegral(Time t0, Time t1) throw(Exception);
      
      //! Set current value.
      void setValue(int v) throw(Exception);
      //! Set value at given time.
      void setValueAtTime(Time t, int v) throw(Exception);
  };
  
}

#endif
