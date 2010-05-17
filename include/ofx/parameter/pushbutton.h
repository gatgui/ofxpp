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

#ifndef __ofx_parameter_pushbutton_h__
#define __ofx_parameter_pushbutton_h__

#include <ofx/parameter.h>

namespace ofx {
  
  class PushButtonParameterDescriptor : public ParameterDescriptor {
    public:
      PushButtonParameterDescriptor();
      PushButtonParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      PushButtonParameterDescriptor(const PushButtonParameterDescriptor &rhs);
      virtual ~PushButtonParameterDescriptor();
      
      PushButtonParameterDescriptor& operator=(const PushButtonParameterDescriptor &rhs);
      
      // properties
      
      EntryPoint interact();
      void setInteract(EntryPoint func);
      
      void interactSize(double &w, double &h);
      void setInteractSize(double w, double h);
      
      double interactSizeAspect();
      void setInteractSizeAspect(double a);
      
      void interactMinimumSize(int &w, int &h);
      void setMinimumInteractSize(int w, int h);
      
      void interactPreferedSize(int &w, int &h);
      void setInteractPreferedSize(int w, int h);
      
#ifdef OFX_API_1_2
      bool hasHostOverlayHandle();
      
      bool useHostOverlayHandle();
      void setUseHostOverlayHandle(bool b);
#endif
  };
  
  class PushButtonParameter : public Parameter {
    public:
      
      PushButtonParameter();
      PushButtonParameter(Host *h, OfxParamHandle hdl);
      PushButtonParameter(const PushButtonParameter &rhs);
      virtual ~PushButtonParameter();
      
      PushButtonParameter& operator=(const PushButtonParameter &rhs);
      
      // properties
      
      EntryPoint interact();
      
      void interactSize(double &w, double &h);
      
      double interactSizeAspect();
      
      void interactMinimumSize(int &w, int &h);
      
      void interactPreferedSize(int &w, int &h);
      
#ifdef OFX_API_1_2
      bool useHostOverlayHandle();
#endif
  };
  
}

#endif
