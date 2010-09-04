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

/** \file booleanparameter.h
 *  Boolean parameter descriptor and instance classes.
 */

#ifndef __ofx_parameter_boolean_h__
#define __ofx_parameter_boolean_h__

#include <ofx/parameter.h>

namespace ofx {
  
  //! Boolean parameter descriptor class.
  class BooleanParameterDescriptor : public ValueParameterDescriptor {
    public:
      BooleanParameterDescriptor();
      BooleanParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      BooleanParameterDescriptor(const BooleanParameterDescriptor &rhs);
      virtual ~BooleanParameterDescriptor();
      
      BooleanParameterDescriptor& operator=(const BooleanParameterDescriptor &rhs);
      
      // properties
      
      //! Get default value.
      bool defaultValue();
      
      //! Set default value.
      void defaultValue(bool v);
  };
  
  //! Boolean parameter instance class.
  class BooleanParameter : public ValueParameter {
    public:
      BooleanParameter();
      BooleanParameter(Host *h, OfxParamHandle hdl);
      BooleanParameter(const BooleanParameter &rhs);
      virtual ~BooleanParameter();
      
      BooleanParameter& operator=(const BooleanParameter &rhs);
      
      // properties
      
      //! Get default value.
      bool defaultValue();
      
      // suite
      
      //! Get current value.
      bool getValue() throw(Exception);
      
      //! Get value at given time.
      bool getValueAtTime(Time t) throw(Exception);
      
      //! Set current value.
      void setValue(bool v) throw(Exception);
      
      //! Set value at given time.
      void setValueAtTime(Time t, bool v) throw(Exception);
  };
  
}

#endif
