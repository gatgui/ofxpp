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

#ifndef __ofx_image_h__
#define __ofx_image_h__

#include <ofxImageEffect.h>
#include <ofx/ofx.h>
#include <ofx/exception.h>
#include <ofx/property.h>

namespace ofx {
  
  class ImageEffectHost;
  
  class Image {
    public:
      
      Image();
      Image(ImageEffectHost *h, OfxPropertySetHandle hdl) throw(Exception);
      Image(const Image &rhs);
      ~Image();
      
      Image& operator=(const Image &rhs);
      
      inline OfxPropertySetHandle handle() {
        return mProps.handle();
      }
      
      inline void* data() {
        return mData;
      }
      
      inline BitDepth pixelDepth() const {
        return mBitDepth;
      }
      
      inline ImageComponent components() const {
        return mComponents;
      }
      
      inline ImagePreMult preMultiplication() const {
        return mPreMult;
      }
      
      inline void renderScale(double *sx, double *sy) const {
        *sx = mRenderScaleX;
        *sy = mRenderScaleY;
      }
      
      inline double pixelAspectRatio() const {
        return mPixelAspectRatio;
      }
      
      const Rect<int>& regionOfDefinition() const {
        return mRoD;
      }
      
      inline ImageField field() const {
        return mField;
      }
      
      inline const std::string& uniqueIdentifier() const {
        return mUID;
      }
      
      inline int componentBytes() const {
        return mCompBytes;
      }
      
      inline int componentsCount() const {
        return mNumComps;
      }
      
      inline int pixelBytes() const {
        return mPixelBytes;
      }
      
      inline int rowBytes() {
        return mRowBytes;
      }
      
      inline const Rect<int>& bounds() {
        return mBounds;
      }
      
      inline void* pixelAddress(int x, int y) {
        if (x < mBounds.x1 || x >= mBounds.x2 || y < mBounds.y1 || y >= mBounds.y2) {
          return 0;
        }
        return (void*)((char*)mData + ((y - mBounds.y1) * mRowBytes) + ((x - mBounds.x1) * mPixelBytes));
      }
      
      template <typename ComponentType>
      inline bool pixelAddress(int x, int y, RGBAColour<ComponentType> *&adr) {
        adr = (RGBAColour<ComponentType>*) pixelAddress(x, y);
        return (adr != 0);
      }
      
      // suite
      
      void release() throw(Exception);
      
    protected:
      
      PropertySet mProps;
      OfxImageEffectSuiteV1 *mSuite;
      BitDepth mBitDepth;
      ImageComponent mComponents;
      ImagePreMult mPreMult;
      double mRenderScaleX;
      double mRenderScaleY;
      double mPixelAspectRatio;
      Rect<int> mRoD;
      ImageField mField;
      std::string mUID;
      int mCompBytes;
      int mNumComps;
      int mPixelBytes;
      int mRowBytes;
      Rect<int> mBounds;
      void *mData;
  };
}

#endif
