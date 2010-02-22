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

#include <ofx/imageeffect.h>
#include <ofx/host.h>

namespace ofx {

//OfxImageEffectSuiteV1 * Image::msSuiteV1 = 0;

Image::Image()
  : mSuite(0), mPixelBytes(0), mRowBytes(0), mData(0) {
}

Image::Image(ImageEffectHost *h, OfxPropertySetHandle hdl) throw(Exception)
  : mProps(h, hdl) {
  if (!h) {
    throw Exception(kOfxStatErrFatal, "ofx::Image::Image: no host");
  }
  
  mSuite = h->imageEffectSuite();
  
  static size_t byteSize[] = {0, 1, 2, 4};
  static size_t compCount[] = {0, 4, 1};
  
  mCompBytes = byteSize[pixelDepth()];
  mNumComps = compCount[components()];
  mData = mProps.getPointer(kOfxImagePropData, 0);
  mRowBytes = mProps.getInt(kOfxImagePropRowBytes, 0);
  mProps.getInts(kOfxImagePropBounds, 4, &(mBounds.x1));
  mPixelBytes = mNumComps * mCompBytes;
}

Image::Image(const Image &rhs)
  : mProps(rhs.mProps), mSuite(rhs.mSuite), mCompBytes(rhs.mCompBytes),
    mNumComps(rhs.mNumComps), mPixelBytes(rhs.mPixelBytes),
    mRowBytes(rhs.mRowBytes), mBounds(rhs.mBounds) {
}

Image::~Image() {
}

Image& Image::operator=(const Image &rhs) {
  mProps = rhs.mProps;
  mSuite = rhs.mSuite;
  mCompBytes = rhs.mCompBytes;
  mNumComps = rhs.mNumComps;
  mPixelBytes = rhs.mPixelBytes;
  mRowBytes = rhs.mRowBytes;
  mBounds = rhs.mBounds;
  mData = rhs.mData;
  return *this;
}

//Image& Image::operator=(OfxPropertySetHandle hdl) {
//  mProps = hdl;
//  return *this;
//}

void Image::release() throw(Exception) {
  mSuite->clipReleaseImage(mProps.handle());
  mData = 0;
  mNumComps = 0;
  mCompBytes = 0;
  mPixelBytes = 0;
  mRowBytes = 0;
}

BitDepth Image::pixelDepth() throw(Exception) {
  return StringToBitDepth(mProps.getString(kOfxImageEffectPropPixelDepth, 0));
}
      
ImageComponent Image::components() throw(Exception) {
  return StringToImageComponent(mProps.getString(kOfxImageEffectPropComponents, 0));
}

ImagePreMult Image::preMultiplication() throw(Exception) {
  return StringToImagePreMult(mProps.getString(kOfxImageEffectPropPreMultiplication, 0));
}

void Image::renderScale(double &sx, double &sy) throw(Exception) {
  sx = mProps.getDouble(kOfxImageEffectPropRenderScale, 0);
  sy = mProps.getDouble(kOfxImageEffectPropRenderScale, 1);
}

double Image::pixelAspectRatio() throw(Exception) {
  return mProps.getDouble(kOfxImagePropPixelAspectRatio, 0);
}

//void* Image::data() throw(Exception) {
//  return mProps.getPointer(kOfxImagePropData, 0);
//}

//Rect<int> Image::bounds() throw(Exception) {
//  Rect<int> bounds;
//  mProps.getInts(kOfxImagePropBounds, 4, &(bounds.x1));
//  return bounds;
//}

Rect<int> Image::regionOfDefinition() throw(Exception) {
  Rect<int> rod;
  mProps.getInts(kOfxImagePropRegionOfDefinition, 4, &(rod.x1));
  return rod;
}

//int Image::rowBytes() throw(Exception) {
//  return mProps.getInt(kOfxImagePropRowBytes, 0);
//}

ImageField Image::field() throw(Exception) {
  return StringToImageField(mProps.getString(kOfxImagePropField, 0));
}

std::string Image::uniqueIdentifier() throw(Exception) {
  return mProps.getString(kOfxImagePropUniqueIdentifier, 0);
}

// ---

//OfxImageEffectSuiteV1 * ClipDescriptor::msSuiteV1 = 0;

ClipDescriptor::ClipDescriptor() {
}

ClipDescriptor::ClipDescriptor(ImageEffectHost *h, OfxPropertySetHandle hdl) throw(Exception)
  : mProps(h, hdl) {
}

ClipDescriptor::ClipDescriptor(const ClipDescriptor &rhs)
  : mProps(rhs.mProps) {
}

ClipDescriptor::~ClipDescriptor() {
}

ClipDescriptor& ClipDescriptor::operator=(const ClipDescriptor &rhs) {
  mProps = rhs.mProps;
  return *this;
}

//ClipDescriptor& ClipDescriptor::operator=(OfxPropertySetHandle hdl) {
//  mProps = hdl;
//  return *this;
//}

std::string ClipDescriptor::name() throw(Exception) {
  return mProps.getString(kOfxPropName, 0);
}

std::string ClipDescriptor::label() throw(Exception) {
  return mProps.getString(kOfxPropLabel, 0);
}

void ClipDescriptor::setLabel(const std::string &l) throw(Exception) {
  mProps.setString(kOfxPropLabel, 0, l);
}

std::string ClipDescriptor::shortLabel() throw(Exception) {
  return mProps.getString(kOfxPropShortLabel, 0);
}

void ClipDescriptor::setShortLabel(const std::string &l) throw(Exception) {
  mProps.setString(kOfxPropShortLabel, 0, l);
}

std::string ClipDescriptor::longLabel() throw(Exception) {
  return mProps.getString(kOfxPropLongLabel, 0);
}

void ClipDescriptor::setLongLabel(const std::string &l) throw(Exception) {
  mProps.setString(kOfxPropLongLabel, 0, l);
}
 
int ClipDescriptor::supportedComponentsCount() throw(Exception) {
  return mProps.size(kOfxImageEffectPropSupportedComponents);
}

ImageComponent ClipDescriptor::getSupportedComponent(int i) throw(Exception) {
  return StringToImageComponent(mProps.getString(kOfxImageEffectPropSupportedComponents, i));
}

void ClipDescriptor::setSupportedComponent(int i, ImageComponent ic) throw(Exception) {
  mProps.setString(kOfxImageEffectPropSupportedComponents, i, ImageComponentToString(ic));
}

bool ClipDescriptor::needsTemporalClipAccess() throw(Exception) {
  return (mProps.getInt(kOfxImageEffectPropTemporalClipAccess, 0) == 1);
}

void ClipDescriptor::requireTemporalClipAccess(bool yes) throw(Exception) {
  mProps.setInt(kOfxImageEffectPropTemporalClipAccess, 0, (yes ? 1 : 0));
}
 
bool ClipDescriptor::isOptional() throw(Exception) {
  return (mProps.getInt(kOfxImageClipPropOptional, 0) == 1);
}

void ClipDescriptor::setOptional(bool yes) throw(Exception) {
  mProps.setInt(kOfxImageClipPropOptional, 0, (yes ? 1 : 0));
}
 
ImageFieldExtract ClipDescriptor::fieldExtraction() throw(Exception) {
  return StringToImageFieldExtract(mProps.getString(kOfxImageClipPropFieldExtraction, 0));
}

void ClipDescriptor::setFieldExtraction(ImageFieldExtract f) throw(Exception) {
  mProps.setString(kOfxImageClipPropFieldExtraction, 0, ImageFieldExtractToString(f));
}
 
bool ClipDescriptor::isMask() throw(Exception) {
  return (mProps.getInt(kOfxImageClipPropIsMask, 0) == 1);
}

void ClipDescriptor::setMask(bool yes) throw(Exception) {
  mProps.setInt(kOfxImageClipPropIsMask, 0, (yes ? 1 : 0));
}
 
bool ClipDescriptor::supportsTiles() throw(Exception) {
  return (mProps.getInt(kOfxImageEffectPropSupportsTiles, 0) == 1);
}

void ClipDescriptor::setTilesSupport(bool yes) throw(Exception) {
  mProps.setInt(kOfxImageEffectPropSupportsTiles, 0, (yes ? 1 : 0));
}

// ---

//OfxImageEffectSuiteV1 * Clip::msSuiteV1 = 0;

Clip::Clip()
  : mHandle(0), mHost(0) {
}

Clip::Clip(ImageEffectHost *h, OfxImageClipHandle hdl) throw(Exception)
  : mHandle(hdl), mHost(h) {
  if (!h) {
    throw Exception(kOfxStatErrFatal, "ofx::Clip::Clip: no host");
  }
  OfxPropertySetHandle hProps;
  mHost->imageEffectSuite()->clipGetPropertySet(mHandle, &hProps);
  mProps = PropertySet(h, hProps);
}

Clip::Clip(const Clip &rhs)
  : mHandle(rhs.mHandle), mProps(rhs.mProps), mHost(rhs.mHost) {
}

Clip::~Clip() {
}

Clip& Clip::operator=(const Clip &rhs) {
  mHandle = rhs.mHandle;
  mProps = rhs.mProps;
  mHost = rhs.mHost;
  return *this;
}

//Clip& Clip::operator=(OfxImageClipHandle hdl) {
//  mHandle = hdl;
//  if (mHandle != 0 && msSuiteV1 != 0) {
//    OfxPropertySetHandle hProps;
//    msSuiteV1->clipGetPropertySet(mHandle, &hProps);
//    mProps = hProps;
//  }
//  return *this;
//}

std::string Clip::name() throw(Exception) {
  return mProps.getString(kOfxPropName, 0);
}
      
std::string Clip::label() throw(Exception) {
  return mProps.getString(kOfxPropLabel, 0);
}

std::string Clip::shortLabel() throw(Exception) {
  return mProps.getString(kOfxPropShortLabel, 0);
}

std::string Clip::longLabel() throw(Exception) {
  return mProps.getString(kOfxPropLongLabel, 0);
}

int Clip::supportedComponentsCount() throw(Exception) {
  return mProps.size(kOfxImageEffectPropSupportedComponents);
}

ImageComponent Clip::getSupportedComponent(int i) throw(Exception) {
  return StringToImageComponent(mProps.getString(kOfxImageEffectPropSupportedComponents, i));
}

bool Clip::needsTemporalClipAccess() throw(Exception) {
  return (mProps.getInt(kOfxImageEffectPropTemporalClipAccess, 0) == 1);
}

bool Clip::isOptional() throw(Exception) {
  return (mProps.getInt(kOfxImageClipPropOptional, 0) == 1);
}

ImageFieldExtract Clip::fieldExtraction() throw(Exception) {
  return StringToImageFieldExtract(mProps.getString(kOfxImageClipPropFieldExtraction, 0));
}

bool Clip::isMask() throw(Exception) {
  return (mProps.getInt(kOfxImageClipPropIsMask, 0) == 1);
}

bool Clip::supportsTiles() throw(Exception) {
  return (mProps.getInt(kOfxImageEffectPropSupportsTiles, 0) == 1);
}

BitDepth Clip::pixelDepth() throw(Exception) {
  return StringToBitDepth(mProps.getString(kOfxImageEffectPropPixelDepth, 0));
}
      
ImageComponent Clip::components() throw(Exception) {
  return StringToImageComponent(mProps.getString(kOfxImageEffectPropComponents, 0));
}

BitDepth Clip::unmappedPixelDepth() throw(Exception) {
  return StringToBitDepth(mProps.getString(kOfxImageClipPropUnmappedPixelDepth, 0));
}

ImageComponent Clip::unmappedComponents() throw(Exception) {
  return StringToImageComponent(mProps.getString(kOfxImageClipPropUnmappedComponents, 0));
}

ImagePreMult Clip::preMultiplication() throw(Exception) {
  return StringToImagePreMult(mProps.getString(kOfxImageEffectPropPreMultiplication, 0));
}

double Clip::pixelAspectRatio() throw(Exception) {
  return mProps.getDouble(kOfxImagePropPixelAspectRatio, 0);
}

double Clip::frameRate() throw(Exception) {
  return mProps.getDouble(kOfxImageEffectPropFrameRate, 0);
}

void Clip::frameRange(double &from, double &to) throw(Exception) {
  from = mProps.getDouble(kOfxImageEffectPropFrameRange, 0);
  to = mProps.getDouble(kOfxImageEffectPropFrameRange, 1);
}

ImageFieldOrder Clip::fieldOrder() throw(Exception) {
  return StringToImageFieldOrder(mProps.getString(kOfxImageClipPropConnected, 0));
}

bool Clip::isConnected() throw(Exception) {
  return (mProps.getInt(kOfxImageClipPropConnected, 0) == 1);
}

void Clip::unmappedFrameRange(double &from, double &to) throw(Exception) {
  from = mProps.getDouble(kOfxImageEffectPropUnmappedFrameRange, 0);
  to = mProps.getDouble(kOfxImageEffectPropUnmappedFrameRange, 1);
}

double Clip::unmappedFrameRate() throw(Exception) {
  return mProps.getDouble(kOfxImageEffectPropUnmappedFrameRate, 0);
}

bool Clip::continuousSamples() throw(Exception) {
  return (mProps.getInt(kOfxImageClipPropContinuousSamples, 0) == 1);
}

Image Clip::getImage(Time t) throw(Exception) {
  OfxPropertySetHandle hImage;
  OfxStatus stat = mHost->imageEffectSuite()->clipGetImage(mHandle, t, NULL, &hImage);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Clip::getImage");
  }
  return Image(mHost, hImage);
}

Image Clip::getImage(Time t, const Rect<double> &region) throw(Exception) {
  OfxRectD r;
  r.x1 = region.x1;
  r.x2 = region.x2;
  r.y1 = region.y1;
  r.y2 = region.y2;
  OfxPropertySetHandle hImage;
  OfxStatus stat = mHost->imageEffectSuite()->clipGetImage(mHandle, t, &r, &hImage);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Clip::getImage");
  }
  return Image(mHost, hImage);
}

Rect<double> Clip::getRegionOfDefinition(Time t) throw(Exception) {
  OfxRectD bounds;
  OfxStatus stat = mHost->imageEffectSuite()->clipGetRegionOfDefinition(mHandle, t, &bounds);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Clip::getRegionOfDefinition");
  }
  Rect<double> rv;
  rv.x1 = bounds.x1;
  rv.x2 = bounds.x2;
  rv.y1 = bounds.y1;
  rv.y2 = bounds.y2;
  return rv;
}

// ---

//OfxImageEffectSuiteV1 * ImageEffectDescriptor::msSuiteV1 = 0;

ImageEffectDescriptor::ImageEffectDescriptor()
  : mHandle(0), mHost(0) {
}

ImageEffectDescriptor::ImageEffectDescriptor(ImageEffectHost *h, OfxImageEffectHandle hdl) throw(Exception)
  : mHandle(hdl), mHost(h) {
  if (!h) {
    throw Exception(kOfxStatErrFatal, "ofx::ImageEffectDescriptor::ImageEffectDescriptor: no host");
  }
  
  OfxPropertySetHandle hProps;
  mHost->imageEffectSuite()->getPropertySet(mHandle, &hProps);
  mProps = PropertySet(mHost, hProps);
  
  OfxParamSetHandle hParams;
  mHost->imageEffectSuite()->getParamSet(mHandle, &hParams);
  mParams = ParameterSetDescriptor(mHost, hParams);
}

ImageEffectDescriptor::ImageEffectDescriptor(const ImageEffectDescriptor &rhs)
  : mHandle(rhs.mHandle), mProps(rhs.mProps), mParams(rhs.mParams) {
  
}

ImageEffectDescriptor::~ImageEffectDescriptor() {
  
}

ImageEffectDescriptor& ImageEffectDescriptor::operator=(const ImageEffectDescriptor &rhs) {
  mHandle = rhs.mHandle;
  mProps = rhs.mProps;
  mParams = rhs.mParams;
  mHost = rhs.mHost;
  return *this;
}

//ImageEffectDescriptor& ImageEffectDescriptor::operator=(OfxImageEffectHandle hdl) {
//  mHandle = hdl;
//  if (mHandle != 0 && msSuiteV1 != 0) {
//    OfxPropertySetHandle hProps;
//    msSuiteV1->getPropertySet(mHandle, &hProps);
//    mProps = hProps;
//    OfxParamSetHandle hParams;
//    msSuiteV1->getParamSet(mHandle, &hParams);
//    mParams = hParams;
//  }
//  return *this;
//}

std::string ImageEffectDescriptor::label() throw(Exception) {
  return mProps.getString(kOfxPropLabel, 0);
}

void ImageEffectDescriptor::setLabel(const std::string &s) throw(Exception) {
  mProps.setString(kOfxPropLabel, 0, s);
}

std::string ImageEffectDescriptor::shortLabel() throw(Exception) {
  return mProps.getString(kOfxPropShortLabel, 0);
}

void ImageEffectDescriptor::setShortLabel(const std::string &s) throw(Exception) {
  mProps.setString(kOfxPropShortLabel, 0, s);
}

std::string ImageEffectDescriptor::longLabel() throw(Exception) {
  return mProps.getString(kOfxPropLongLabel, 0);
}

void ImageEffectDescriptor::setLongLabel(const std::string &s) throw(Exception) {
  mProps.setString(kOfxPropLongLabel, 0, s);
}

int ImageEffectDescriptor::supportedContextsCount() throw(Exception) {
  return mProps.size(kOfxImageEffectPropSupportedContexts);
}

ImageEffectContext ImageEffectDescriptor::getSupportedContext(int i) throw(Exception) {
  return StringToImageEffectContext(mProps.getString(kOfxImageEffectPropSupportedContexts, i));
}

void ImageEffectDescriptor::setSupportedContext(int i, ImageEffectContext ctx) throw(Exception) {
  mProps.setString(kOfxImageEffectPropSupportedContexts, i, ImageEffectContextToString(ctx));
}

std::string ImageEffectDescriptor::grouping() throw(Exception) {
  return mProps.getString(kOfxImageEffectPluginPropGrouping, 0);
}

void ImageEffectDescriptor::setGrouping(const std::string &g) throw(Exception) {
  mProps.setString(kOfxImageEffectPluginPropGrouping, 0, g);
}

bool ImageEffectDescriptor::singleInstance() throw(Exception) {
  return (mProps.getInt(kOfxImageEffectPluginPropSingleInstance, 0) == 1);
}

void ImageEffectDescriptor::setSingleInstance(bool yes) throw(Exception) {
  mProps.setInt(kOfxImageEffectPluginPropSingleInstance, 0, (yes ? 1 : 0));
}

RenderThreadSafety ImageEffectDescriptor::renderThreadSafety() throw(Exception) {
  return StringToRenderThreadSafety(mProps.getString(kOfxImageEffectPluginRenderThreadSafety, 0));
}

void ImageEffectDescriptor::setRenderThreadSafety(RenderThreadSafety rts) throw(Exception) {
  mProps.setString(kOfxImageEffectPluginRenderThreadSafety, 0, RenderThreadSafetyToString(rts));
}

bool ImageEffectDescriptor::hostFrameThreading() throw(Exception) {
  return (mProps.getInt(kOfxImageEffectPluginPropHostFrameThreading, 0) == 1);
}
  
void ImageEffectDescriptor::setHostFrameThreading(bool yes) throw(Exception) {
  mProps.setInt(kOfxImageEffectPluginPropHostFrameThreading, 0, (yes ? 1 : 0));
}
 
bool ImageEffectDescriptor::supportsMultiResolution() throw(Exception) {
  return (mProps.getInt(kOfxImageEffectPropSupportsMultiResolution, 0) == 1);
}

void ImageEffectDescriptor::setMultiResolutionSupport(bool yes) throw(Exception) {
  mProps.setInt(kOfxImageEffectPropSupportsMultiResolution, 0, (yes ? 1 : 0));
}

bool ImageEffectDescriptor::supportsTiles() throw(Exception) {
  return (mProps.getInt(kOfxImageEffectPropSupportsTiles, 0) == 1);
}

void ImageEffectDescriptor::setTilesSupport(bool yes) throw(Exception) {
  mProps.setInt(kOfxImageEffectPropSupportsTiles, 0, (yes ? 1 : 0));
}

bool ImageEffectDescriptor::needsTemporalClipAccess() throw(Exception) {
  return (mProps.getInt(kOfxImageEffectPropTemporalClipAccess, 0) == 1);
}

void ImageEffectDescriptor::requireTemporalClipAccess(bool yes) throw(Exception) {
  mProps.setInt(kOfxImageEffectPropTemporalClipAccess, 0, (yes ? 1 : 0));
}
 
int ImageEffectDescriptor::supportedPixelDepthsCount() throw(Exception) {
  return mProps.size(kOfxImageEffectPropSupportedPixelDepths);
}

void ImageEffectDescriptor::setSupportedPixelDepth(int i, BitDepth bd) throw(Exception) {
  mProps.setString(kOfxImageEffectPropSupportedPixelDepths, i, BitDepthToString(bd));
}

BitDepth ImageEffectDescriptor::getSupportedPixelDepth(int i) throw(Exception) {
  return StringToBitDepth(mProps.getString(kOfxImageEffectPropSupportedPixelDepths, i));
}

bool ImageEffectDescriptor::fieldRenderTwiceAlways() throw(Exception) {
  return (mProps.getInt(kOfxImageEffectPluginPropFieldRenderTwiceAlways, 0) == 1);
}

void ImageEffectDescriptor::setFieldRenderTwiceAlways(bool yes) throw(Exception) {
  mProps.setInt(kOfxImageEffectPluginPropFieldRenderTwiceAlways, 0, (yes ? 1 : 0));
}

bool ImageEffectDescriptor::supportsMultipleClipDepths() throw(Exception) {
  return (mProps.getInt(kOfxImageEffectPropSupportsMultipleClipDepths, 0) == 1);
}

void ImageEffectDescriptor::setMultipleClipDepthsSupport(bool yes) throw(Exception) {
  mProps.setInt(kOfxImageEffectPropSupportsMultipleClipDepths, 0, (yes ? 1 : 0));
}

bool ImageEffectDescriptor::supportsMultipleClipPARs() throw(Exception) {
  return (mProps.getInt(kOfxImageEffectPropSupportsMultipleClipPARs, 0) == 1);
}

void ImageEffectDescriptor::setMultipleClipPARsSupport(bool yes) throw(Exception) {
  mProps.setInt(kOfxImageEffectPropSupportsMultipleClipPARs, 0, (yes ? 1 : 0));
}  

int ImageEffectDescriptor::clipPreferencesSlaveParamCount() throw(Exception) {
  return mProps.size(kOfxImageEffectPropClipPreferencesSlaveParam);
}

std::string ImageEffectDescriptor::getClipPreferencesSlaveParam(int i) throw(Exception) {
  return mProps.getString(kOfxImageEffectPropClipPreferencesSlaveParam, i);
}

void ImageEffectDescriptor::setClipPreferencesSlaveParam(int i, const std::string &n) throw(Exception) {
  mProps.setString(kOfxImageEffectPropClipPreferencesSlaveParam, i, n);
}

std::string ImageEffectDescriptor::pluginFilePath() throw(Exception) {
  return mProps.getString(kOfxPluginPropFilePath, 0);
}

ClipDescriptor ImageEffectDescriptor::defineClip(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hProps;
  OfxStatus stat = mHost->imageEffectSuite()->clipDefine(mHandle, name.c_str(), &hProps);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ImageEffectDescriptor::defineClip");
  }
  return ClipDescriptor(mHost, hProps);
}

EntryPoint ImageEffectDescriptor::overlayInteract() throw(Exception) {
  return ((EntryPoint) mProps.getPointer(kOfxImageEffectPluginPropOverlayInteractV1, 0));
}

void ImageEffectDescriptor::setOverlayInteract(EntryPoint func) throw(Exception) {
  mProps.setPointer(kOfxImageEffectPluginPropOverlayInteractV1, 0, (void*)func);
}

void ImageEffectDescriptor::describe() throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void ImageEffectDescriptor::describeInContext(ImageEffectContext) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

// ---

//OfxImageEffectSuiteV1 * ImageEffect::msSuiteV1 = 0;

std::map<OfxImageEffectHandle, ImageEffect*> ImageEffect::msEffects;

ImageEffect* ImageEffect::GetEffect(OfxImageEffectHandle handle) {
  std::map<OfxImageEffectHandle, ImageEffect*>::iterator it = msEffects.find(handle);
  if (it != msEffects.end()) {
    return it->second;
  } else {
    return 0;
  }
}

//void ImageEffect::Init(Host *h) throw(Exception) {
//  if (h) {
//    msSuiteV1 = h->fetchSuite<OfxImageEffectSuiteV1>(kOfxImageEffectSuite, 1);
//    if (msSuiteV1) {
//      Image::msSuiteV1 = msSuiteV1;
//      ClipDescriptor::msSuiteV1 = msSuiteV1;
//      Clip::msSuiteV1 = msSuiteV1;
//      ImageEffectDescriptor::msSuiteV1 = msSuiteV1;
//      return;
//    }
//  }
//  throw Exception(kOfxStatErrMissingHostFeature, "Cannot initialize ofx::ImageEffect");
//}

ImageEffect::ImageEffect()
  : mHandle(0), mHost(0) {
}

ImageEffect::ImageEffect(ImageEffectHost *h, OfxImageEffectHandle hdl) throw(Exception)
  : mHandle(0), mHost(h) {
  setHandle(hdl);
}

//ImageEffect::ImageEffect(const ImageEffect &rhs)
//  : mHandle(rhs.mHandle), mProps(rhs.mProps), mParams(rhs.mParams) {
//}

ImageEffect::~ImageEffect() {
  setHandle(0);
}

void ImageEffect::setHandle(OfxImageEffectHandle handle) throw(Exception) {
  if (mHandle != 0) {
    msEffects.erase(msEffects.find(mHandle));
  }
  if (!mHost) {
    throw Exception(kOfxStatErrFatal, "ofx::ImageEffet::setHandle: no host");
  }
  mHandle = handle;
  if (mHandle != 0) {
    OfxPropertySetHandle hProps;
    mHost->imageEffectSuite()->getPropertySet(mHandle, &hProps);
    mProps = PropertySet(mHost, hProps);
    
    OfxParamSetHandle hParams;
    mHost->imageEffectSuite()->getParamSet(mHandle, &hParams);
    mParams = ParameterSet(mHost, hParams);
    
    msEffects[mHandle] = this;
  }
}

//ImageEffect& ImageEffect::operator=(const ImageEffect &rhs) {
//  mHandle = rhs.mHandle;
//  mProps = rhs.mProps;
//  mParams = rhs.mParams;
//  return *this;
//}

//ImageEffect& ImageEffect::operator=(OfxImageEffectHandle hdl) {
//  mHandle = hdl;
//  if (mHandle != 0 && msSuiteV1 != 0) {
//    OfxPropertySetHandle hProps;
//    msSuiteV1->getPropertySet(mHandle, &hProps);
//    mProps = hProps;
//    OfxParamSetHandle hParams;
//    msSuiteV1->getParamSet(mHandle, &hParams);
//    mParams = hParams;
//  }
//  return *this;
//}

ImageEffectContext ImageEffect::context() throw(Exception) {
  return StringToImageEffectContext(mProps.getString(kOfxImageEffectPropContext, 0));
}

void* ImageEffect::instanceData() throw(Exception) {
  return mProps.getPointer(kOfxPropInstanceData, 0);
}

void ImageEffect::setInstanceData(void *data) throw(Exception) {
  mProps.setPointer(kOfxPropInstanceData, 0, data);
}

void ImageEffect::projectSize(double &w, double &h) throw(Exception) {
  w = mProps.getDouble(kOfxImageEffectPropProjectSize, 0);
  h = mProps.getDouble(kOfxImageEffectPropProjectSize, 1);
}

void ImageEffect::projectOffset(double &x, double &y) throw(Exception) {
  x = mProps.getDouble(kOfxImageEffectPropProjectOffset, 0);
  y = mProps.getDouble(kOfxImageEffectPropProjectOffset, 1);
}

void ImageEffect::projectExtent(double &w, double &h) throw(Exception) {
  w = mProps.getDouble(kOfxImageEffectPropProjectExtent, 0);
  h = mProps.getDouble(kOfxImageEffectPropProjectExtent, 1);
}

double ImageEffect::projectPixelAspectRatio() throw(Exception) {
  return mProps.getDouble(kOfxImageEffectPropProjectPixelAspectRatio, 0);
}

double ImageEffect::duration() throw(Exception) {
  return mProps.getDouble(kOfxImageEffectInstancePropEffectDuration, 0);
}

bool ImageEffect::needsSequentialRender() throw(Exception) {
  return (mProps.getInt(kOfxImageEffectInstancePropSequentialRender, 0) == 1);
}

void ImageEffect::requireSequentialRender(bool yes) throw(Exception) {
  mProps.setInt(kOfxImageEffectInstancePropSequentialRender, 0, (yes ? 1 : 0));
}

double ImageEffect::frameRate() throw(Exception) {
  return mProps.getDouble(kOfxImageEffectPropFrameRate, 0);
}

bool ImageEffect::isInteractive() throw(Exception) {
  return (mProps.getInt(kOfxPropIsInteractive, 0) == 1);
}

Clip ImageEffect::getClip(const std::string &name) throw(Exception) {
  OfxImageClipHandle hClip;
  OfxStatus stat = mHost->imageEffectSuite()->clipGetHandle(mHandle, name.c_str(), &hClip, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ImageEffect::getClip");
  }
  return Clip(mHost, hClip);
}

bool ImageEffect::abort() throw(Exception) {
  return (mHost->imageEffectSuite()->abort(mHandle) == 1);
}

OfxImageMemoryHandle ImageEffect::alloc(size_t nBytes) throw(Exception) {
  OfxImageMemoryHandle hdl;
  OfxStatus stat = mHost->imageEffectSuite()->imageMemoryAlloc(mHandle, nBytes, &hdl);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ImageEffect::alloc");
  }
  return hdl;
}

void* ImageEffect::lock(OfxImageMemoryHandle hdl) throw(Exception) {
  void *ptr = 0;
  OfxStatus stat = mHost->imageEffectSuite()->imageMemoryLock(hdl, &ptr);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ImageEffect::lock");
  }
  return ptr;
}

void ImageEffect::unlock(OfxImageMemoryHandle hdl) throw(Exception) {
  OfxStatus stat = mHost->imageEffectSuite()->imageMemoryUnlock(hdl);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ImageEffect::unlock");
  }
}

void ImageEffect::free(OfxImageMemoryHandle hdl) throw(Exception) {
  OfxStatus stat = mHost->imageEffectSuite()->imageMemoryFree(hdl);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ImageEffect::free");
  }
}

void ImageEffect::beginInstanceChanged(ChangeReason) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}
      
void ImageEffect::endInstanceChanged(ChangeReason) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void ImageEffect::instanceChanged(Type, const std::string &, ChangeReason,
                                  Time, double, double) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void ImageEffect::purgeCaches() throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void ImageEffect::syncPrivateData() throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void ImageEffect::beginInstanceEdit() throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void ImageEffect::endInstanceEdit() throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

Rect<double> ImageEffect::getRegionOfDefinition(Time, double, double) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void ImageEffect::getRegionsOfInterest(Time, double, double,
                                       const Rect<double> &,
                                       std::map<std::string, Rect<double> > &) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void ImageEffect::getFramesNeeded(Time, std::map<std::string, FrameRangeList> &) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

bool ImageEffect::isIdentity(Time, ImageField, const Rect<int> &,
                             double, double,
                             std::string &, Time &) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void ImageEffect::render(Time, ImageField, const Rect<int> &,
                         double, double) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void ImageEffect::beginSequenceRender(const FrameRange &, int, bool,
                                      double, double) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void ImageEffect::endSequenceRender(const FrameRange &, int, bool,
                                    double, double) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void ImageEffect::getClipPreferences(ClipPreferences &,
                                     std::map<std::string, PixelPreferences> &) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void ImageEffect::getTimeDomain(double &, double &) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

}
