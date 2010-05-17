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

#ifndef __ofx_parameter_string_h__
#define __ofx_parameter_string_h__

#include <ofx/parameter.h>

namespace ofx {
  
  class StringParameterDescriptor : public ValueParameterDescriptor {
    public:
      StringParameterDescriptor();
      StringParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      StringParameterDescriptor(const StringParameterDescriptor &rhs);
      virtual ~StringParameterDescriptor();
      
      StringParameterDescriptor& operator=(const StringParameterDescriptor &rhs);
      
      // properties
      
      std::string getDefault();
      void setDefault(const std::string &v);
      
      StringParamMode mode();
      void setMode(StringParamMode m);
      
      bool filePathExists();
      void setFilePathExists(bool);
  };
  
  class StringParameter : public ValueParameter {
    public:
      StringParameter();
      StringParameter(Host *h, OfxParamHandle hdl);
      StringParameter(const StringParameter &rhs);
      virtual ~StringParameter();
      
      StringParameter& operator=(const StringParameter &rhs);
      
      // properties
      
      std::string getDefault();
      
      StringParamMode mode();
      
      bool filePathExists();
      
      // suite
      
      std::string getValue() throw(Exception);
      std::string getValueAtTime(Time t) throw(Exception);
      
      void setValue(const std::string &v) throw(Exception);
      void setValueAtTime(Time t, const std::string &v) throw(Exception);
  };
  
}

#endif
