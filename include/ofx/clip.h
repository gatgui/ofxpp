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

/** \file clip.h
 *  Clip descriptor and instance classes.
 */

#ifndef __ofx_clip_h__
#define __ofx_clip_h__

#include <ofxImageEffect.h>
#include <ofx/ofx.h>
#include <ofx/image.h>

namespace ofx {
  
  //! Clip descriptor class.
  class ClipDescriptor {
    public:
      
      ClipDescriptor();
      ClipDescriptor(ImageEffectHost *h, OfxPropertySetHandle hdl);
      ClipDescriptor(const ClipDescriptor &rhs);
      ~ClipDescriptor();
      
      ClipDescriptor& operator=(const ClipDescriptor &rhs);
      
      //! Get associated property handle.
      inline OfxPropertySetHandle handle() {
        return mProps.handle();
      }
      
      // properties
      
      //! Get clip name.
      std::string name();
      
      //! Get clip label.
      std::string label();
      //! Set clip label.
      void label(const std::string &l);
      
      //! Get clip short label.
      std::string shortLabel();
      //! Set clip label.
      void shortLabel(const std::string &l);
      
      //! Get clip long label.
      std::string longLabel();
      //! Set clip label.
      void longLabel(const std::string &l);
      
      //! Get the number of supported image pixel components.
      int supportedComponentsCount();
      //! Get the ith supported image pixel components.
      ImageComponent supportedComponent(int i);
      //! Add/Set a supported image pixel components.
      void supportedComponent(int i, ImageComponent ic);
      
      //! Check if clip needs random temporal access to images.
      bool temporalClipAccess();
      //! Set if clip needs random temporal access to images.
      void temporalClipAccess(bool);
      
      //! Check if clip is optional.
      bool optional();
      //! Set if clip is optional.
      void optional(bool);
      
      ImageFieldExtract fieldExtraction();
      void fieldExtraction(ImageFieldExtract f);
      
      //! Check if clip is used as a mask.
      bool isMask();
      //! Set if clip should be used as a mask.
      void isMask(bool);
      
      //! Check if clip supports tiled images.
      bool supportsTiles();
      //! Set if clip supports tiled images.
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
      
      //! Get associated image effect host.
      inline ImageEffectHost* host() {
        return mHost;
      }
      
      //! Get clip handle.
      inline OfxImageClipHandle handle() {
        return mHandle;
      }
      
      // suite
      
      //! Get clip image at given time.
      Image getImage(Time t) throw(Exception);
      
      //! Get clip image tile at given time.
      Image getImage(Time t, const Rect<double> &region) throw(Exception);
      
      //! Get clip region of definition at given time.
      Rect<double> getRegionOfDefinition(Time t) throw(Exception);
      
      // properties
      
      //! Get clip name.
      std::string name();
      
      //! Get clip label
      std::string label();
      
      //! Get clip short label.
      std::string shortLabel();
      
      //! Get clip long label.
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
      
      //! Get clip images pixel component depth.
      BitDepth pixelDepth();
      
      //! Get clip images pixel components.
      ImageComponent components();
      
      //! Get clip images premultiplcation state.
      ImagePreMult preMultiplication();
      
      //! Get clip pixel aspect ratio.
      double pixelAspectRatio();
      
      //! Get clip frame rate.
      double frameRate();
      
      //! Get clip frame range.
      ofx::FrameRange frameRange();
      
      //! Get clip images field ordering.
      ImageFieldOrder fieldOrder();
      
      //! Check if clip is actually connected.
      bool connected();
      
      //! Check if clip can be sampled continuously.
      bool continuousSamples();
      
      //! Get clip images pixel component depth before any mapping by clip preferences.
      BitDepth unmappedPixelDepth();
      
      //! Get clip images pixel components before any mapping by clip preferences.
      ImageComponent unmappedComponents();
      
      //! Get clip frame range before any mapping by clip preferences.
      ofx::FrameRange unmappedFrameRange();
      
      //! Get clip frame rate before any mapping by clip preferences.
      double unmappedFrameRate();
      
      
    protected:
      
      OfxImageClipHandle mHandle;
      PropertySet mProps;
      ImageEffectHost *mHost;
  };
  
  
}

#endif