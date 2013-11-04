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

#include <ofx/image.h>
#include <ofx/host.h>
#include <cmath>

namespace ofx {

ImageBase::ImageBase()
  : mSuite(0)
  , mBitDepth(BitDepthNone)
  , mComponents(ImageComponentNone)
  , mPreMult(ImageOpaque)
  , mRenderScaleX(1.0)
  , mRenderScaleY(1.0)
  , mPixelAspectRatio(1.0)
  , mField(ImageFieldNone)
  , mUID("")
  , mPixelBytes(0)
  , mRowBytes(0) {
}

ImageBase::ImageBase(ImageEffectHost *h, OfxPropertySetHandle hdl) throw(Exception)
  : mProps(h, hdl) {
  if (!h) {
    throw BadHandleError("ofx::ImageBase::ImageBase: invalid host");
  }

  mSuite = h->imageEffectSuite();

  static int byteSize[] = {0, 1, 2, 4};
#ifdef OFX_API_1_2
  static int compCount[] = {0, 3, 4, 1, 4};
#else
  static int compCount[] = {0, 4, 1, 4};
#endif

  mBitDepth = StringToBitDepth(mProps.getString(kOfxImageEffectPropPixelDepth, 0));
  mComponents = StringToImageComponent(mProps.getString(kOfxImageEffectPropComponents, 0));
  mPreMult = StringToImagePreMult(mProps.getString(kOfxImageEffectPropPreMultiplication, 0));
  mRenderScaleX = mProps.getDouble(kOfxImageEffectPropRenderScale, 0);
  mRenderScaleY = mProps.getDouble(kOfxImageEffectPropRenderScale, 1);
  mPixelAspectRatio = mProps.getDouble(kOfxImagePropPixelAspectRatio, 0);
  mProps.getInts(kOfxImagePropRegionOfDefinition, 4, &(mRoD.x1));
  mField = StringToImageField(mProps.getString(kOfxImagePropField, 0));
  mUID = mProps.getString(kOfxImagePropUniqueIdentifier, 0);
  mRowBytes = mProps.getInt(kOfxImagePropRowBytes, 0);
  mProps.getInts(kOfxImagePropBounds, 4, &(mBounds.x1));

  mCompBytes = byteSize[pixelDepth()];
  mNumComps = compCount[components()];
  mPixelBytes = mNumComps * mCompBytes;
}

ImageBase::ImageBase(const ImageBase &rhs)
  : mSuite(rhs.mSuite)
  , mProps(rhs.mProps)
  , mBitDepth(rhs.mBitDepth)
  , mComponents(rhs.mComponents)
  , mPreMult(rhs.mPreMult)
  , mRenderScaleX(rhs.mRenderScaleX)
  , mRenderScaleY(rhs.mRenderScaleY)
  , mPixelAspectRatio(rhs.mPixelAspectRatio)
  , mRoD(rhs.mRoD)
  , mField(rhs.mField)
  , mUID(rhs.mUID)
  , mCompBytes(rhs.mCompBytes)
  , mNumComps(rhs.mNumComps)
  , mPixelBytes(rhs.mPixelBytes)
  , mRowBytes(rhs.mRowBytes)
  , mBounds(rhs.mBounds) {
}

ImageBase::~ImageBase() {
}

ImageBase& ImageBase::operator=(const ImageBase &rhs) {
  if (this != &rhs) {
    mProps = rhs.mProps;
    mSuite = rhs.mSuite;
    mCompBytes = rhs.mCompBytes;
    mNumComps = rhs.mNumComps;
    mPixelBytes = rhs.mPixelBytes;
    mRowBytes = rhs.mRowBytes;
    mBounds = rhs.mBounds;
    mBitDepth = rhs.mBitDepth;
    mComponents = rhs.mComponents;
    mPreMult = rhs.mPreMult;
    mRenderScaleX = rhs.mRenderScaleX;
    mRenderScaleY = rhs.mRenderScaleY;
    mPixelAspectRatio = rhs.mPixelAspectRatio;
    mRoD = rhs.mRoD;
    mField = rhs.mField;
    mUID = rhs.mUID;
  }
  return *this;
}

// ---

Image::Image()
  : ImageBase(), mData(0) {
}

Image::Image(ImageEffectHost *h, OfxPropertySetHandle hdl) throw(Exception)
  : ImageBase(h, hdl), mData(0) {
  
  mData = mProps.getPointer(kOfxImagePropData, 0);
}

Image::Image(const Image &rhs)
  : ImageBase(rhs), mData(rhs.mData) {
}

Image::~Image() {
}

Image& Image::operator=(const Image &rhs) {
  if (this != &rhs) {
    ImageBase::operator=(rhs);
    mData = rhs.mData;
  }
  return *this;
}

void Image::release() throw(Exception) {
  OfxStatus stat = mSuite->clipReleaseImage(mProps.handle());
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Image::release");
  }
  mData = 0;
  mNumComps = 0;
  mCompBytes = 0;
  mPixelBytes = 0;
  mRowBytes = 0;
}

// ---

#ifdef OFX_API_1_3

Texture::Texture()
  : ImageBase(), mIndex(-1), mTarget(-1), mGLSuite(0) {
}

Texture::Texture(ImageEffectHost *h, OfxPropertySetHandle hdl) throw(Exception)
  : ImageBase(h, hdl), mGLSuite(0) {
  
  mIndex = mProps.getInt(kOfxImageEffectPropOpenGLTextureIndex, 0);
  mTarget = mProps.getInt(kOfxImageEffectPropOpenGLTextureTarget, 0);
  
  mGLSuite = h->openGLRenderSuite();
}

Texture::Texture(const Texture &rhs)
  : ImageBase(rhs), mIndex(rhs.mIndex), mTarget(rhs.mTarget), mGLSuite(rhs.mGLSuite) {
}

Texture::~Texture() {
}

Texture& Texture::operator=(const Texture &rhs) {
  if (this != &rhs) {
    ImageBase::operator=(rhs);
    mIndex = rhs.mIndex;
    mTarget = rhs.mTarget;
    mGLSuite = rhs.mGLSuite;
  }
  return *this;
}

void Texture::release() throw(Exception) {
  if (mGLSuite) {
    OfxStatus stat = mGLSuite->clipFreeTexture(mProps.handle());
    if (stat != kOfxStatOK) {
      throw Exception(stat, "ofx::Texture::release");
    }
    mIndex = -1;
    mTarget = -1;
  }
}

#endif

}
