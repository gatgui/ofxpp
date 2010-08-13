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

#ifndef __ofx_parameter_int_h__
#define __ofx_parameter_int_h__

#include <ofx/parameter.h>

namespace ofx {
  
  class IntParameterDescriptor : public ValueParameterDescriptor {
    public:
      IntParameterDescriptor();
      IntParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      IntParameterDescriptor(const IntParameterDescriptor &rhs);
      virtual ~IntParameterDescriptor();
      
      IntParameterDescriptor& operator=(const IntParameterDescriptor &rhs);
      
      // properties
      
      int getDefault();
      void setDefault(int v);
      
      int getMin();
      void setMin(int v);
      
      int getMax();
      void setMax(int v);
      
      int getDisplayMin();
      void setDisplayMin(int v);
      
      int getDisplayMax();
      void setDisplayMax(int v);
  };
  
  class IntParameter : public ValueParameter {
    public:
      IntParameter();
      IntParameter(Host *h, OfxParamHandle hdl);
      IntParameter(const IntParameter &rhs);
      virtual ~IntParameter();
      
      IntParameter& operator=(const IntParameter &rhs);
      
      // properties
      
      int getDefault();
      
      int getMin();
      void setMin(int v);
      
      int getMax();
      void setMax(int v);
      
      int getDisplayMin();
      void setDisplayMin(int v);
      
      int getDisplayMax();
      void setDisplayMax(int v);
      
      // suite
      
      int getValue() throw(Exception);
      int getValueAtTime(Time t) throw(Exception);
      int getDerivative(Time t) throw(Exception);
      int getIntegral(Time t0, Time t1) throw(Exception);
      
      void setValue(int v) throw(Exception);
      void setValueAtTime(Time t, int v) throw(Exception);
  };
  
}

#endif
