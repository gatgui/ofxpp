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

/** \file stringparameter.h
 *  String parameter descriptor and instance classes.
 */

#ifndef __ofx_parameter_string_h__
#define __ofx_parameter_string_h__

#include <ofx/parameter.h>

namespace ofx {
  
  //! String parameter descriptor class.
  class StringParameterDescriptor : public ValueParameterDescriptor {
    public:
      StringParameterDescriptor();
      StringParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      StringParameterDescriptor(const StringParameterDescriptor &rhs);
      virtual ~StringParameterDescriptor();
      
      StringParameterDescriptor& operator=(const StringParameterDescriptor &rhs);
      
      // properties
      
      //! Get default value.
      std::string defaultValue();
      //! Set default value.
      void defaultValue(const std::string &v);
      
      //! Get value interpretation.
      StringParamMode mode();
      //! Set value interpretation.
      void mode(StringParamMode m);
      
      //! Check if value used as a file path must points to an existing file.
      bool filePathExists();
      //! Set if value used as a file path must points to an existing file.
      void filePathExists(bool);
  };
  
  //! String parameter instance class.
  class StringParameter : public ValueParameter {
    public:
      StringParameter();
      StringParameter(Host *h, OfxParamHandle hdl);
      StringParameter(const StringParameter &rhs);
      virtual ~StringParameter();
      
      StringParameter& operator=(const StringParameter &rhs);
      
      // properties
      
      //! Get default value.
      std::string defaultValue();
      
      //! Get value interpretation.
      StringParamMode mode();
      
      //! Check if value used as a file path must points to an existing file.
      bool filePathExists();
      
      // suite
      
      //! Get current value.
      std::string getValue() throw(Exception);
      //! Get value at given time.
      std::string getValueAtTime(Time t) throw(Exception);
      
      //! Set current value.
      void setValue(const std::string &v) throw(Exception);
      //! Set value at given time.
      void setValueAtTime(Time t, const std::string &v) throw(Exception);
  };
  
}

#endif
