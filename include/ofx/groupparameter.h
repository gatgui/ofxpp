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

/** \file groupparameter.h
 *  Group parameter descriptor and instance classes.
 */

#ifndef __ofx_parameter_group_h__
#define __ofx_parameter_group_h__

#include <ofx/parameter.h>

namespace ofx {
  
#ifdef OFX_API_1_2
  
  //! Group parameter descriptor class.
  class GroupParameterDescriptor : public ParameterDescriptor {
    public:
      
      GroupParameterDescriptor();
      GroupParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      GroupParameterDescriptor(const GroupParameterDescriptor &rhs);
      virtual ~GroupParameterDescriptor();
      
      GroupParameterDescriptor& operator=(const GroupParameterDescriptor &rhs);
      
      // properties
      
      /** Check if group is opened.
       *  \note OpenFX version >= 1.2
       */
      bool open();
      /** Set group opened or not.
       *  \note OpenFX version >= 1.2
       */
      void open(bool o);
  };
  
  //! Group parameter instance classe.
  class GroupParameter : public Parameter {
    public:
      
      GroupParameter();
      GroupParameter(Host *h, OfxParamHandle hdl);
      GroupParameter(const GroupParameter &rhs);
      virtual ~GroupParameter();
      
      GroupParameter& operator=(const GroupParameter &rhs);
      
      // properties
      
      /** Check if group is opened.
       *  \note OpenFX version >= 1.2
       */
      bool open();
  };
  
#else
  
  //! Group parameter descriptor classe.
  typedef ParameterDescriptor GroupParameterDescriptor;
  
  //! Group parameter instance classe.
  typedef Parameter GroupParameter;
  
#endif
}

#endif
