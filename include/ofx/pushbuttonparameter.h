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

/** \file pushbuttonparameter.h
 *  Button parameter descriptor and instance classes.
 */

#ifndef __ofx_parameter_pushbutton_h__
#define __ofx_parameter_pushbutton_h__

#include <ofx/parameter.h>

namespace ofx {
  
  //! Button parameter descriptor class.
  class PushButtonParameterDescriptor : public ParameterDescriptor {
    public:
      PushButtonParameterDescriptor();
      PushButtonParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      PushButtonParameterDescriptor(const PushButtonParameterDescriptor &rhs);
      virtual ~PushButtonParameterDescriptor();
      
      PushButtonParameterDescriptor& operator=(const PushButtonParameterDescriptor &rhs);
      
      // properties
      
      //! Get interact entry point function.
      EntryPoint interact();
      //! Set interact entry point function.
      void interact(EntryPoint func);
      
      //void interactSize(double &w, double &h);
      //void interactSize(double w, double h);
      
      //! Get interact size aspect.
      double interactSizeAspect();
      //! Set interact size aspect.
      void interactSizeAspect(double a);
      
      //! Get interact minimum size.
      void interactMinimumSize(int *w, int *h);
      //! Set interact minimum size.
      void interactMinimumSize(int w, int h);
      
      //! Get interact prefered size.
      void interactPreferedSize(int *w, int *h);
      //! Set interact prefered size.
      void interactPreferedSize(int w, int h);
      
#ifdef OFX_API_1_2
      /** Check if host provides generic overlay handle.
       *  \note OpenFX version >= 1.2.
       */
      bool hasHostOverlayHandle();
      
      /** Check if parameter is using host provided overlay handle.
       *  \note OpenFX version >= 1.2.
       */
      bool useHostOverlayHandle();
      /** Set if parameter is using host provided overlay handle.
       *  \note OpenFX version >= 1.2.
       */
      void useHostOverlayHandle(bool b);
#endif
  };
  
  //! Button parameter instance class.
  class PushButtonParameter : public Parameter {
    public:
      
      PushButtonParameter();
      PushButtonParameter(Host *h, OfxParamHandle hdl);
      PushButtonParameter(const PushButtonParameter &rhs);
      virtual ~PushButtonParameter();
      
      PushButtonParameter& operator=(const PushButtonParameter &rhs);
      
      // properties
      
      //! Get interact entry point function.
      EntryPoint interact();
      
      //! Get interact size.
      void interactSize(double *w, double *h);
      
      //! Get interact size aspect.
      double interactSizeAspect();
      
      //! Get interact minimum size.
      void interactMinimumSize(int *w, int *h);
      
      //! Get interact prefered size.
      void interactPreferedSize(int *w, int *h);
      
#ifdef OFX_API_1_2
      /** Check if parameter is using host provided overlay handle.
       *  \note OpenFX version >= 1.2.
       */
      bool useHostOverlayHandle();
#endif
  };
  
}

#endif
