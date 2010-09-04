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

/** \file choiceparameter.h
 *  Choice parameter descriptor and instance classes.
 */

#ifndef __ofx_parameter_choice_h__
#define __ofx_parameter_choice_h__

#include <ofx/parameter.h>

namespace ofx {
  
  //! Choice parameter descriptor class.
  class ChoiceParameterDescriptor : public ValueParameterDescriptor {
    public:
      ChoiceParameterDescriptor();
      ChoiceParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      ChoiceParameterDescriptor(const ChoiceParameterDescriptor &rhs);
      virtual ~ChoiceParameterDescriptor();
      
      ChoiceParameterDescriptor& operator=(const ChoiceParameterDescriptor &rhs);
      
      // properties
      
      /** Get default value.
       *  \return Default value.
       */
      int defaultValue();
      
      /** Set default value.
       *  \param[in] v Default value.
       */
      void defaultValue(int v);
      
      /** Get number of available choice options.
       *  \return Number of options.
       */
      int choiceOptionCount();
      
      /** Add/Set choice option string.
       *  \param[in] i Choice index.
       *  \param[in] str String to associate.
       */
      void choiceOption(int i, const std::string &str);
      
      /** Get choice option string.
       *  \param[in] i Choice index.
       *  \return Associated string.
       */
      std::string choiceOption(int i);
  };
  
  //! Choice parameter instance class.
  class ChoiceParameter : public ValueParameter {
    public:
      ChoiceParameter();
      ChoiceParameter(Host *h, OfxParamHandle hdl);
      ChoiceParameter(const ChoiceParameter &rhs);
      virtual ~ChoiceParameter();
      
      ChoiceParameter& operator=(const ChoiceParameter &rhs);
      
      // properties
      
      /** Get default value.
       *  \return Default value.
       */
      int defaultValue();
      
      /** Get number of available choice options.
       *  \return Number of options.
       */
      int choiceOptionCount();
      
      /** Add/Set choice option string.
       *  \param[in] i Choice index.
       *  \param[in] str String to associate.
       */
      void choiceOption(int i, const std::string &str);
      
      /** Get choice option string.
       *  \param[in] i Choice index.
       *  \return Associated string.
       */
      std::string choiceOption(int i);
      
      // suite
      
      /** Get current value.
       *  \return Current value.
       */
      int getValue() throw(Exception);
      
      /** Get value at time.
       *  \param[in] t Time to get value at.
       *  \return Value at time.
       */
      int getValueAtTime(Time t) throw(Exception);
      
      /** Set current value.
       *  \param[in] v Value.
       */
      void setValue(int v) throw(Exception);
      
      /** Set value at time.
       *  \param[in] t Time to set value at.
       *  \param[in] v Value.
       */
      void setValueAtTime(Time t, int v) throw(Exception);
  };
  
}

#endif
