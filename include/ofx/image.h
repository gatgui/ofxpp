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

/** \file image.h
 *  %Image class.
 */

#ifndef __ofx_image_h__
#define __ofx_image_h__

#include <ofxImageEffect.h>
#include <ofx/ofx.h>
#include <ofx/exception.h>
#include <ofx/property.h>

namespace ofx {
  
  class ImageEffectHost;
  
  //! %Image class.
  class Image {
    public:
      
      Image();
      Image(ImageEffectHost *h, OfxPropertySetHandle hdl) throw(Exception);
      Image(const Image &rhs);
      ~Image();
      
      Image& operator=(const Image &rhs);
      
      //! Get property handle.
      inline OfxPropertySetHandle handle() {
        return mProps.handle();
      }
      
      //! Get image data raw pointer.
      inline void* data() {
        return mData;
      }
      
      //! Get pixel depth.
      inline BitDepth pixelDepth() const {
        return mBitDepth;
      }
      
      //! Get pixel components.
      inline ImageComponent components() const {
        return mComponents;
      }
      
      //! Get pre multiplication state.
      inline ImagePreMult preMultiplication() const {
        return mPreMult;
      }
      
      //! Get render scale.
      inline void renderScale(double *sx, double *sy) const {
        *sx = mRenderScaleX;
        *sy = mRenderScaleY;
      }
      
      //! Get pixel aspect ratio.
      inline double pixelAspectRatio() const {
        return mPixelAspectRatio;
      }
      
      //! Get region of definition.
      const Rect<int>& regionOfDefinition() const {
        return mRoD;
      }
      
      //! Get field.
      inline ImageField field() const {
        return mField;
      }
      
      //! Get unique identifier.
      inline const std::string& uniqueIdentifier() const {
        return mUID;
      }
      
      //! Get number of bytes per component.
      inline int componentBytes() const {
        return mCompBytes;
      }
      
      //! Get number of components per pixel.
      inline int componentsCount() const {
        return mNumComps;
      }
      
      //! Get number of bytes per pixel.
      inline int pixelBytes() const {
        return mPixelBytes;
      }
      
      //! Get number of bytes per row.
      inline int rowBytes() {
        return mRowBytes;
      }
      
      //! Get bounds.
      inline const Rect<int>& bounds() {
        return mBounds;
      }
      
      //! Get pixel raw address.
      inline void* pixelAddress(int x, int y) {
        if (x < mBounds.x1 || x >= mBounds.x2 || y < mBounds.y1 || y >= mBounds.y2) {
          return 0;
        }
        return (void*)((char*)mData + ((y - mBounds.y1) * mRowBytes) + ((x - mBounds.x1) * mPixelBytes));
      }
      
      //! Get pixel typed address.
      template <typename T>
      inline bool pixelAddress(int x, int y, T *&adr) {
        adr = (T*) pixelAddress(x, y);
        return (adr != 0);
      }
      
      // suite
      
      //! Release image resources.
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
