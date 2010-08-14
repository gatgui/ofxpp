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

#ifndef __ofx_parameter_page_h__
#define __ofx_parameter_page_h__

#include <ofx/parameter.h>

namespace ofx {
  
  class PageParameterDescriptor : ParameterDescriptor {
    public:
      PageParameterDescriptor();
      PageParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      PageParameterDescriptor(const PageParameterDescriptor &rhs);
      virtual ~PageParameterDescriptor();
      
      PageParameterDescriptor& operator=(const PageParameterDescriptor &rhs);
      
      // properties
      
      // special string values:
      //   kOfxParamPageSkipRow
      //   kOfxParamPageSkipColumn
      int childCount();
      void child(int i, const std::string &name);
      std::string child(int i);
  };
  
  class PageParameter : public Parameter {
    public:
      PageParameter();
      PageParameter(Host *h, OfxParamHandle hdl);
      PageParameter(const PageParameter &rhs);
      virtual ~PageParameter();
      
      PageParameter& operator=(const PageParameter &rhs);
      
      // properties
      
      int childCount();
      std::string child(int i);
  };
  
}

#endif
