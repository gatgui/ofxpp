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
      
      inline OfxPropertySetHandle getHandle() {
        return mProps.getHandle();
      }
      
      // properties
      
      std::string getName();
      
      std::string getLabel();
      void setLabel(const std::string &l);
      
      std::string getShortLabel();
      void setShortLabel(const std::string &l);
      
      std::string getLongLabel();
      void setLongLabel(const std::string &l);
      
      int getSupportedComponentsCount();
      ImageComponent getSupportedComponent(int i);
      void setSupportedComponent(int i, ImageComponent ic);
      
      bool requireTemporalClipAccess();
      void setTemporalClipAccess(bool);
      
      bool isOptional();
      void setOptional(bool);
      
      ImageFieldExtract getFieldExtraction();
      void setFieldExtraction(ImageFieldExtract f);
      
      bool isMask();
      void setMask(bool);
      
      bool supportTiles();
      void setTilesSupport(bool);
    
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
      
      inline ImageEffectHost* getHost() {
        return mHost;
      }
      
      inline OfxImageClipHandle getHandle() {
        return mHandle;
      }
      
      // suite
      
      Image getImage(Time t) throw(Exception);
      
      Image getImage(Time t, const Rect<double> &region) throw(Exception);
      
      Rect<double> getRegionOfDefinition(Time t) throw(Exception);
      
      // properties
      
      std::string getName();
      
      std::string getLabel();
      
      std::string getShortLabel();
      
      std::string getLongLabel();
      
      int getSupportedComponentsCount();
      ImageComponent getSupportedComponent(int i);
      
      bool requireTemporalClipAccess();
      
      bool isOptional();
      
      ImageFieldExtract getFieldExtraction();
      
      bool isMask();
      
      bool supportTiles();
      
      BitDepth getPixelDepth();
      
      ImageComponent getComponents();
      
      ImagePreMult getPreMultiplication();
      
      double getPixelAspectRatio();
      
      double getFrameRate();
      
      void getFrameRange(double &from, double &to);
      
      ImageFieldOrder getFieldOrder();
      
      bool isConnected();
      
      bool supportContinuousSampling();
      
      BitDepth getUnmappedPixelDepth();
      
      ImageComponent getUnmappedComponents();
      
      void getUnmappedFrameRange(double &from, double &to);
      
      double getUnmappedFrameRate();
      
      
    protected:
      
      OfxImageClipHandle mHandle;
      PropertySet mProps;
      ImageEffectHost *mHost;
  };
  
  
}

#endif