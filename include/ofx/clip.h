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

#ifndef __ofx_clip_h__
#define __ofx_clip_h__

#include <ofxImageEffect.h>
#include <ofx/ofx.h>
#include <ofx/image.h>

namespace ofx {
  
  
  class ClipDescriptor {
    public:
      
      ClipDescriptor();
      ClipDescriptor(ImageEffectHost *h, OfxPropertySetHandle hdl);
      ClipDescriptor(const ClipDescriptor &rhs);
      ~ClipDescriptor();
      
      ClipDescriptor& operator=(const ClipDescriptor &rhs);
      
      inline OfxPropertySetHandle handle() {
        return mProps.handle();
      }
      
      // properties
      
      std::string name();
      
      std::string label();
      void label(const std::string &l);
      
      std::string shortLabel();
      void shortLabel(const std::string &l);
      
      std::string longLabel();
      void longLabel(const std::string &l);
      
      int supportedComponentsCount();
      ImageComponent supportedComponent(int i);
      void supportedComponent(int i, ImageComponent ic);
      
      bool temporalClipAccess();
      void temporalClipAccess(bool);
      
      bool optional();
      void optional(bool);
      
      ImageFieldExtract fieldExtraction();
      void fieldExtraction(ImageFieldExtract f);
      
      bool isMask();
      void isMask(bool);
      
      bool supportsTiles();
      void supportsTiles(bool);
    
    protected:
      
      PropertySet mProps;
  };
  
  
  class Clip {
    public:
      
      Clip();
      Clip(ImageEffectHost *h, OfxImageClipHandle hdl) throw(Exception);
      Clip(const Clip &rhs);
      ~Clip();
      
      Clip& operator=(const Clip &rhs);
      
      inline ImageEffectHost* host() {
        return mHost;
      }
      
      inline OfxImageClipHandle handle() {
        return mHandle;
      }
      
      // suite
      
      Image getImage(Time t) throw(Exception);
      
      Image getImage(Time t, const Rect<double> &region) throw(Exception);
      
      Rect<double> getRegionOfDefinition(Time t) throw(Exception);
      
      // properties
      
      std::string name();
      
      std::string label();
      
      std::string shortLabel();
      
      std::string longLabel();
      
      /*
      int supportedComponentsCount();
      ImageComponent supportedComponent(int i);
      
      bool temporalClipAccess();
      
      bool optional();
      
      ImageFieldExtract fieldExtraction();
      
      bool isMask();
      
      bool supportsTiles();
      */
      
      BitDepth pixelDepth();
      
      ImageComponent components();
      
      ImagePreMult preMultiplication();
      
      double pixelAspectRatio();
      
      double frameRate();
      
      ofx::FrameRange frameRange();
      
      ImageFieldOrder fieldOrder();
      
      bool connected();
      
      bool continuousSamples();
      
      BitDepth unmappedPixelDepth();
      
      ImageComponent unmappedComponents();
      
      ofx::FrameRange unmappedFrameRange();
      
      double unmappedFrameRate();
      
      
    protected:
      
      OfxImageClipHandle mHandle;
      PropertySet mProps;
      ImageEffectHost *mHost;
  };
  
  
}

#endif