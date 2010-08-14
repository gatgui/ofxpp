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

#ifndef __ofx_parameter_choice_h__
#define __ofx_parameter_choice_h__

#include <ofx/parameter.h>

namespace ofx {
  
  class ChoiceParameterDescriptor : public ValueParameterDescriptor {
    public:
      ChoiceParameterDescriptor();
      ChoiceParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      ChoiceParameterDescriptor(const ChoiceParameterDescriptor &rhs);
      virtual ~ChoiceParameterDescriptor();
      
      ChoiceParameterDescriptor& operator=(const ChoiceParameterDescriptor &rhs);
      
      // properties
      
      int defaultValue();
      void defaultValue(int);
      
      int choiceOptionCount();
      void choiceOption(int i, const std::string &str);
      std::string choiceOption(int i);
  };
  
  class ChoiceParameter : public ValueParameter {
    public:
      ChoiceParameter();
      ChoiceParameter(Host *h, OfxParamHandle hdl);
      ChoiceParameter(const ChoiceParameter &rhs);
      virtual ~ChoiceParameter();
      
      ChoiceParameter& operator=(const ChoiceParameter &rhs);
      
      // properties
      
      int defaultValue();
      
      int choiceOptionCount();
      void choiceOption(int i, const std::string &str);
      std::string choiceOption(int i);
      
      // suite
      
      int getValue() throw(Exception);
      int getValueAtTime(Time t) throw(Exception);
      
      void setValue(int v) throw(Exception);
      void setValueAtTime(Time t, int v) throw(Exception);
  };
  
}

#endif
