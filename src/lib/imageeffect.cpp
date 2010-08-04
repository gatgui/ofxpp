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
#include <cmath>

namespace ofx {

Image::Image()
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
  , mRowBytes(0)
  , mData(0) {
}

Image::Image(ImageEffectHost *h, OfxPropertySetHandle hdl) throw(Exception)
  : mProps(h, hdl) {
  if (!h) {
    throw BadHandleError("ofx::Image::Image: invalid host");
  }
  
  mSuite = h->getImageEffectSuite();
  
  static int byteSize[] = {0, 1, 2, 4};
  static int compCount[] = {0, 4, 1};

  mBitDepth = StringToBitDepth(mProps.getString(kOfxImageEffectPropPixelDepth, 0));
  mComponents = StringToImageComponent(mProps.getString(kOfxImageEffectPropComponents, 0));
  mPreMult = StringToImagePreMult(mProps.getString(kOfxImageEffectPropPreMultiplication, 0));
  mRenderScaleX = mProps.getDouble(kOfxImageEffectPropRenderScale, 0);
  mRenderScaleY = mProps.getDouble(kOfxImageEffectPropRenderScale, 1);
  mPixelAspectRatio = mProps.getDouble(kOfxImagePropPixelAspectRatio, 0);
  mProps.getInts(kOfxImagePropRegionOfDefinition, 4, &(mRoD.x1));
  mField = StringToImageField(mProps.getString(kOfxImagePropField, 0));
  mUID = mProps.getString(kOfxImagePropUniqueIdentifier, 0);
  mData = mProps.getPointer(kOfxImagePropData, 0);
  mRowBytes = mProps.getInt(kOfxImagePropRowBytes, 0);
  mProps.getInts(kOfxImagePropBounds, 4, &(mBounds.x1));
  
  mCompBytes = byteSize[getPixelDepth()];
  mNumComps = compCount[getComponents()];
  mPixelBytes = mNumComps * mCompBytes;
}

Image::Image(const Image &rhs)
  : mProps(rhs.mProps)
  , mSuite(rhs.mSuite)
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
  mBitDepth = rhs.mBitDepth;
  mComponents = rhs.mComponents;
  mPreMult = rhs.mPreMult;
  mRenderScaleX = rhs.mRenderScaleX;
  mRenderScaleY = rhs.mRenderScaleY;
  mPixelAspectRatio = rhs.mPixelAspectRatio;
  mRoD = rhs.mRoD;
  mField = rhs.mField;
  mUID = rhs.mUID;
  return *this;
}

void Image::release() throw(Exception) {
  OfxStatus stat = mSuite->clipReleaseImage(mProps.getHandle());
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

ClipDescriptor::ClipDescriptor() {
}

ClipDescriptor::ClipDescriptor(ImageEffectHost *h, OfxPropertySetHandle hdl)
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

std::string ClipDescriptor::getName() {
  return mProps.getString(kOfxPropName, 0);
}

std::string ClipDescriptor::getLabel() {
  return mProps.getString(kOfxPropLabel, 0);
}

void ClipDescriptor::setLabel(const std::string &l) {
  mProps.setString(kOfxPropLabel, 0, l);
}

std::string ClipDescriptor::getShortLabel() {
  return mProps.getString(kOfxPropShortLabel, 0);
}

void ClipDescriptor::setShortLabel(const std::string &l) {
  mProps.setString(kOfxPropShortLabel, 0, l);
}

std::string ClipDescriptor::getLongLabel() {
  return mProps.getString(kOfxPropLongLabel, 0);
}

void ClipDescriptor::setLongLabel(const std::string &l) {
  mProps.setString(kOfxPropLongLabel, 0, l);
}
 
int ClipDescriptor::getSupportedComponentsCount() {
  return mProps.size(kOfxImageEffectPropSupportedComponents);
}

ImageComponent ClipDescriptor::getSupportedComponent(int i) {
  return StringToImageComponent(mProps.getString(kOfxImageEffectPropSupportedComponents, i));
}

void ClipDescriptor::setSupportedComponent(int i, ImageComponent ic) {
  mProps.setString(kOfxImageEffectPropSupportedComponents, i, ImageComponentToString(ic));
}

bool ClipDescriptor::requireTemporalClipAccess() {
  return (mProps.getInt(kOfxImageEffectPropTemporalClipAccess, 0) == 1);
}

void ClipDescriptor::setTemporalClipAccess(bool yes) {
  mProps.setInt(kOfxImageEffectPropTemporalClipAccess, 0, (yes ? 1 : 0));
}
 
bool ClipDescriptor::isOptional() {
  return (mProps.getInt(kOfxImageClipPropOptional, 0) == 1);
}

void ClipDescriptor::setOptional(bool yes) {
  mProps.setInt(kOfxImageClipPropOptional, 0, (yes ? 1 : 0));
}
 
ImageFieldExtract ClipDescriptor::getFieldExtraction() {
  return StringToImageFieldExtract(mProps.getString(kOfxImageClipPropFieldExtraction, 0));
}

void ClipDescriptor::setFieldExtraction(ImageFieldExtract f) {
  mProps.setString(kOfxImageClipPropFieldExtraction, 0, ImageFieldExtractToString(f));
}
 
bool ClipDescriptor::isMask() {
  return (mProps.getInt(kOfxImageClipPropIsMask, 0) == 1);
}

void ClipDescriptor::setMask(bool yes) {
  mProps.setInt(kOfxImageClipPropIsMask, 0, (yes ? 1 : 0));
}
 
bool ClipDescriptor::supportTiles() {
  return (mProps.getInt(kOfxImageEffectPropSupportsTiles, 0) == 1);
}

void ClipDescriptor::setTilesSupport(bool yes) {
  mProps.setInt(kOfxImageEffectPropSupportsTiles, 0, (yes ? 1 : 0));
}

// ---

Clip::Clip()
  : mHandle(0), mHost(0) {
}

Clip::Clip(ImageEffectHost *h, OfxImageClipHandle hdl) throw(Exception)
  : mHandle(hdl), mHost(h) {
  if (!h) {
    throw BadHandleError("ofx::Clip::Clip: invalid host");
  }
  OfxPropertySetHandle hProps;
  mHost->getImageEffectSuite()->clipGetPropertySet(mHandle, &hProps);
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

std::string Clip::getName() {
  return mProps.getString(kOfxPropName, 0);
}
      
std::string Clip::getLabel() {
  return mProps.getString(kOfxPropLabel, 0);
}

std::string Clip::getShortLabel() {
  return mProps.getString(kOfxPropShortLabel, 0);
}

std::string Clip::getLongLabel() {
  return mProps.getString(kOfxPropLongLabel, 0);
}

int Clip::getSupportedComponentsCount() {
  return mProps.size(kOfxImageEffectPropSupportedComponents);
}

ImageComponent Clip::getSupportedComponent(int i) {
  return StringToImageComponent(mProps.getString(kOfxImageEffectPropSupportedComponents, i));
}

bool Clip::requireTemporalClipAccess() {
  return (mProps.getInt(kOfxImageEffectPropTemporalClipAccess, 0) == 1);
}

bool Clip::isOptional() {
  return (mProps.getInt(kOfxImageClipPropOptional, 0) == 1);
}

ImageFieldExtract Clip::getFieldExtraction() {
  return StringToImageFieldExtract(mProps.getString(kOfxImageClipPropFieldExtraction, 0));
}

bool Clip::isMask() {
  return (mProps.getInt(kOfxImageClipPropIsMask, 0) == 1);
}

bool Clip::supportTiles() {
  return (mProps.getInt(kOfxImageEffectPropSupportsTiles, 0) == 1);
}

BitDepth Clip::getPixelDepth() {
  return StringToBitDepth(mProps.getString(kOfxImageEffectPropPixelDepth, 0));
}
      
ImageComponent Clip::getComponents() {
  return StringToImageComponent(mProps.getString(kOfxImageEffectPropComponents, 0));
}

BitDepth Clip::getUnmappedPixelDepth() {
  return StringToBitDepth(mProps.getString(kOfxImageClipPropUnmappedPixelDepth, 0));
}

ImageComponent Clip::getUnmappedComponents() {
  return StringToImageComponent(mProps.getString(kOfxImageClipPropUnmappedComponents, 0));
}

ImagePreMult Clip::getPreMultiplication() {
  return StringToImagePreMult(mProps.getString(kOfxImageEffectPropPreMultiplication, 0));
}

double Clip::getPixelAspectRatio() {
  return mProps.getDouble(kOfxImagePropPixelAspectRatio, 0);
}

double Clip::getFrameRate() {
  return mProps.getDouble(kOfxImageEffectPropFrameRate, 0);
}

void Clip::getFrameRange(double &from, double &to) {
  from = mProps.getDouble(kOfxImageEffectPropFrameRange, 0);
  to = mProps.getDouble(kOfxImageEffectPropFrameRange, 1);
}

ImageFieldOrder Clip::getFieldOrder() {
  return StringToImageFieldOrder(mProps.getString(kOfxImageClipPropConnected, 0));
}

bool Clip::isConnected() {
  return (mProps.getInt(kOfxImageClipPropConnected, 0) == 1);
}

void Clip::getUnmappedFrameRange(double &from, double &to) {
  from = mProps.getDouble(kOfxImageEffectPropUnmappedFrameRange, 0);
  to = mProps.getDouble(kOfxImageEffectPropUnmappedFrameRange, 1);
}

double Clip::getUnmappedFrameRate() {
  return mProps.getDouble(kOfxImageEffectPropUnmappedFrameRate, 0);
}

bool Clip::supportContinuousSampling() {
  return (mProps.getInt(kOfxImageClipPropContinuousSamples, 0) == 1);
}

Image Clip::getImage(Time t) throw(Exception) {
  OfxPropertySetHandle hImage;
  OfxStatus stat = mHost->getImageEffectSuite()->clipGetImage(mHandle, t, NULL, &hImage);
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
  OfxStatus stat = mHost->getImageEffectSuite()->clipGetImage(mHandle, t, &r, &hImage);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Clip::getImage");
  }
  return Image(mHost, hImage);
}

Rect<double> Clip::getRegionOfDefinition(Time t) throw(Exception) {
  OfxRectD bounds;
  OfxStatus stat = mHost->getImageEffectSuite()->clipGetRegionOfDefinition(mHandle, t, &bounds);
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

ImageEffectDescriptor::ImageEffectDescriptor()
  : mHandle(0), mHost(0) {
}

ImageEffectDescriptor::ImageEffectDescriptor(ImageEffectHost *h, OfxImageEffectHandle hdl) throw(Exception)
  : mHandle(hdl), mHost(h) {
  if (!h) {
    throw BadHandleError("ofx::ImageEffectDescriptor::ImageEffectDescriptor: invalid host");
  }
  
  OfxPropertySetHandle hProps;
  mHost->getImageEffectSuite()->getPropertySet(mHandle, &hProps);
  mProps = PropertySet(mHost, hProps);
  
  OfxParamSetHandle hParams;
  mHost->getImageEffectSuite()->getParamSet(mHandle, &hParams);
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

std::string ImageEffectDescriptor::getLabel() {
  return mProps.getString(kOfxPropLabel, 0);
}

void ImageEffectDescriptor::setLabel(const std::string &s) {
  mProps.setString(kOfxPropLabel, 0, s);
}

std::string ImageEffectDescriptor::getShortLabel() {
  return mProps.getString(kOfxPropShortLabel, 0);
}

void ImageEffectDescriptor::setShortLabel(const std::string &s) {
  mProps.setString(kOfxPropShortLabel, 0, s);
}

std::string ImageEffectDescriptor::getLongLabel() {
  return mProps.getString(kOfxPropLongLabel, 0);
}

void ImageEffectDescriptor::setLongLabel(const std::string &s) {
  mProps.setString(kOfxPropLongLabel, 0, s);
}

int ImageEffectDescriptor::getSupportedContextsCount() {
  return mProps.size(kOfxImageEffectPropSupportedContexts);
}

ImageEffectContext ImageEffectDescriptor::getSupportedContext(int i) {
  return StringToImageEffectContext(mProps.getString(kOfxImageEffectPropSupportedContexts, i));
}

void ImageEffectDescriptor::setSupportedContext(int i, ImageEffectContext ctx) {
  mProps.setString(kOfxImageEffectPropSupportedContexts, i, ImageEffectContextToString(ctx));
}

std::string ImageEffectDescriptor::getGroup() {
  return mProps.getString(kOfxImageEffectPluginPropGrouping, 0);
}

void ImageEffectDescriptor::setGroup(const std::string &g) {
  mProps.setString(kOfxImageEffectPluginPropGrouping, 0, g);
}

bool ImageEffectDescriptor::isSingleInstance() {
  return (mProps.getInt(kOfxImageEffectPluginPropSingleInstance, 0) == 1);
}

void ImageEffectDescriptor::setSingleInstance(bool yes) {
  mProps.setInt(kOfxImageEffectPluginPropSingleInstance, 0, (yes ? 1 : 0));
}

RenderThreadSafety ImageEffectDescriptor::getRenderThreadSafety() {
  return StringToRenderThreadSafety(mProps.getString(kOfxImageEffectPluginRenderThreadSafety, 0));
}

void ImageEffectDescriptor::setRenderThreadSafety(RenderThreadSafety rts) {
  mProps.setString(kOfxImageEffectPluginRenderThreadSafety, 0, RenderThreadSafetyToString(rts));
}

bool ImageEffectDescriptor::requireHostFrameThreading() {
  return (mProps.getInt(kOfxImageEffectPluginPropHostFrameThreading, 0) == 1);
}
  
void ImageEffectDescriptor::setHostFrameThreading(bool yes) {
  mProps.setInt(kOfxImageEffectPluginPropHostFrameThreading, 0, (yes ? 1 : 0));
}
 
bool ImageEffectDescriptor::supportMultiResolution() {
  return (mProps.getInt(kOfxImageEffectPropSupportsMultiResolution, 0) == 1);
}

void ImageEffectDescriptor::setMultiResolutionSupport(bool yes) {
  mProps.setInt(kOfxImageEffectPropSupportsMultiResolution, 0, (yes ? 1 : 0));
}

bool ImageEffectDescriptor::supportTiles() {
  return (mProps.getInt(kOfxImageEffectPropSupportsTiles, 0) == 1);
}

void ImageEffectDescriptor::setTilesSupport(bool yes) {
  mProps.setInt(kOfxImageEffectPropSupportsTiles, 0, (yes ? 1 : 0));
}

bool ImageEffectDescriptor::requireTemporalClipAccess() {
  return (mProps.getInt(kOfxImageEffectPropTemporalClipAccess, 0) == 1);
}

void ImageEffectDescriptor::setTemporalClipAccess(bool yes) {
  mProps.setInt(kOfxImageEffectPropTemporalClipAccess, 0, (yes ? 1 : 0));
}
 
int ImageEffectDescriptor::getSupportedPixelDepthsCount() {
  return mProps.size(kOfxImageEffectPropSupportedPixelDepths);
}

void ImageEffectDescriptor::setSupportedPixelDepth(int i, BitDepth bd) {
  mProps.setString(kOfxImageEffectPropSupportedPixelDepths, i, BitDepthToString(bd));
}

BitDepth ImageEffectDescriptor::getSupportedPixelDepth(int i) {
  return StringToBitDepth(mProps.getString(kOfxImageEffectPropSupportedPixelDepths, i));
}

bool ImageEffectDescriptor::alwaysRenderFieldTwice() {
  return (mProps.getInt(kOfxImageEffectPluginPropFieldRenderTwiceAlways, 0) == 1);
}

void ImageEffectDescriptor::setAlwaysRenderFieldTwice(bool yes) {
  mProps.setInt(kOfxImageEffectPluginPropFieldRenderTwiceAlways, 0, (yes ? 1 : 0));
}

bool ImageEffectDescriptor::supportMultipleClipDepths() {
  return (mProps.getInt(kOfxImageEffectPropSupportsMultipleClipDepths, 0) == 1);
}

void ImageEffectDescriptor::setMultipleClipDepthsSupport(bool yes) {
  mProps.setInt(kOfxImageEffectPropSupportsMultipleClipDepths, 0, (yes ? 1 : 0));
}

bool ImageEffectDescriptor::supportMultipleClipPARs() {
  return (mProps.getInt(kOfxImageEffectPropSupportsMultipleClipPARs, 0) == 1);
}

void ImageEffectDescriptor::setMultipleClipPARsSupport(bool yes) {
  mProps.setInt(kOfxImageEffectPropSupportsMultipleClipPARs, 0, (yes ? 1 : 0));
}  

int ImageEffectDescriptor::getClipPreferencesSlaveParamCount() {
  return mProps.size(kOfxImageEffectPropClipPreferencesSlaveParam);
}

std::string ImageEffectDescriptor::getClipPreferencesSlaveParam(int i) {
  return mProps.getString(kOfxImageEffectPropClipPreferencesSlaveParam, i);
}

void ImageEffectDescriptor::setClipPreferencesSlaveParam(int i, const std::string &n) {
  mProps.setString(kOfxImageEffectPropClipPreferencesSlaveParam, i, n);
}

std::string ImageEffectDescriptor::getPluginFilePath() {
  return mProps.getString(kOfxPluginPropFilePath, 0);
}

ClipDescriptor ImageEffectDescriptor::defineClip(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hProps;
  OfxStatus stat = mHost->getImageEffectSuite()->clipDefine(mHandle, name.c_str(), &hProps);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ImageEffectDescriptor::defineClip");
  }
  return ClipDescriptor(mHost, hProps);
}

EntryPoint ImageEffectDescriptor::getOverlayInteract() {
  return ((EntryPoint) mProps.getPointer(kOfxImageEffectPluginPropOverlayInteractV1, 0));
}

void ImageEffectDescriptor::setOverlayInteract(EntryPoint func) {
  mProps.setPointer(kOfxImageEffectPluginPropOverlayInteractV1, 0, (void*)func);
}

SequentialRender ImageEffectDescriptor::getSequentialRender() {
  return SequentialRender(mProps.getInt(kOfxImageEffectInstancePropSequentialRender, 0));
}

void ImageEffectDescriptor::setSequentialRender(SequentialRender sr) {
  mProps.setInt(kOfxImageEffectInstancePropSequentialRender, 0, int(sr));
}

#ifdef OFX_API_1_2

int ImageEffectDescriptor::getVersion(int level) {
  return (mProps.size(kOfxPropVersion) > level ? mProps.getInt(kOfxPropVersion, level) : 0);
}

int ImageEffectDescriptor::getMajorVersion() {
  return (mProps.size(kOfxPropVersion) > 0 ? mProps.getInt(kOfxPropVersion, 0) : 0);
}

int ImageEffectDescriptor::getMinorVersion() {
  return (mProps.size(kOfxPropVersion) > 1 ? mProps.getInt(kOfxPropVersion, 1) : 0);
}

void ImageEffectDescriptor::setVersion(int level, int v) {
  mProps.setInt(kOfxPropVersion, level, v);
}

std::string ImageEffectDescriptor::getVersionLabel() {
  return mProps.getString(kOfxPropVersionLabel, 0);
}

void ImageEffectDescriptor::setVersionLabel(const std::string &vl) {
  mProps.setString(kOfxPropVersionLabel, 0, vl);
}

std::string ImageEffectDescriptor::getDescription() {
  return mProps.getString(kOfxPropPluginDescription, 0);
}

void ImageEffectDescriptor::setDescription(const std::string &d) {
  mProps.setString(kOfxPropPluginDescription, 0, d);
}

#endif

OfxStatus ImageEffectDescriptor::describe() {
  return kOfxStatFailed;
}

OfxStatus ImageEffectDescriptor::describeInContext(ImageEffectContext) {
  return kOfxStatFailed;
}

// ---

ImageEffect::RenderScaleArgs::RenderScaleArgs(ImageEffectHost *, PropertySet &inArgs) {
  renderScaleX = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
  renderScaleY = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
}

// ---

ImageEffect::TimeArgs::TimeArgs(ImageEffectHost *, PropertySet &inArgs) {
  time = inArgs.getDouble(kOfxPropTime, 0);
}

// ---

ImageEffect::InstanceChangedArgs::InstanceChangedArgs(ImageEffectHost *host, PropertySet &inArgs)
  : ImageEffect::RenderScaleArgs(host, inArgs), ImageEffect::TimeArgs(host, inArgs) {
  type = StringToType(inArgs.getString(kOfxPropType, 0));
  name = inArgs.getString(kOfxPropName, 0);
  reason = StringToChangeReason(inArgs.getString(kOfxPropChangeReason, 0));
}

// ---

ImageEffect::GetRoDArgs::GetRoDArgs(ImageEffectHost *host, PropertySet &inArgs)
  : ImageEffect::RenderScaleArgs(host, inArgs), ImageEffect::TimeArgs(host, inArgs) {
}

void ImageEffect::GetRoDArgs::setOutputs(PropertySet &outArgs) {
  outArgs.setDoubles(kOfxImageEffectPropRegionOfDefinition, 4, &(RoD.x1));
}

// ---

ImageEffect::RenderArgs::RenderArgs(ImageEffectHost *host, PropertySet &inArgs)
  : ImageEffect::RenderScaleArgs(host, inArgs), ImageEffect::TimeArgs(host, inArgs) {
  field = StringToImageField(inArgs.getString(kOfxImageEffectPropFieldToRender, 0));
  inArgs.getInts(kOfxImageEffectPropRenderWindow, 4, &(renderWindow.x1));
#ifdef OFX_API_1_2
  if (host->checkAPIVersion(1, 2)) {
    sequentialRender = (inArgs.getInt(kOfxImageEffectPropSequentialRenderStatus, 0) != 0);
    interactiveRender = (inArgs.getInt(kOfxImageEffectPropInteractiveRenderStatus, 0) != 0);
  } else {
    sequentialRender = false;
    interactiveRender = false;
  }
#endif
}

// ---

ImageEffect::IsIdentityArgs::IsIdentityArgs(ImageEffectHost *host, PropertySet &inArgs)
  : ImageEffect::RenderArgs(host, inArgs) {
}

void ImageEffect::IsIdentityArgs::setOutputs(PropertySet &outArgs) {
  outArgs.setString(kOfxPropName, 0, idClip);
  outArgs.setDouble(kOfxPropTime, 0, idTime);
}

// ---

ImageEffect::GetRoIArgs::GetRoIArgs(ImageEffectHost *host, PropertySet &inArgs)
  : ImageEffect::RenderScaleArgs(host, inArgs), ImageEffect::TimeArgs(host, inArgs) {
  inArgs.getDoubles(kOfxImageEffectPropRegionOfInterest, 4, &(outRoI.x1));
}

void ImageEffect::GetRoIArgs::setOutputs(PropertySet &outArgs) {
  static std::string outBaseName = "OfxImageClipPropRoI_";
  
  std::map<std::string, Rect<double> >::iterator it = inRoIs.begin();
  while (it != inRoIs.end()) {
    std::string name = outBaseName + it->first;
    outArgs.setDoubles(name.c_str(), 4, &(it->second.x1));
    ++it;
  }
}

void ImageEffect::GetRoIArgs::setInputRoI(const std::string &name, const Rect<double> &RoI) {
  inRoIs[name] = RoI;
}

// ---

ImageEffect::GetFramesNeededArgs::GetFramesNeededArgs(ImageEffectHost *host, PropertySet &inArgs)
  : ImageEffect::TimeArgs(host, inArgs) {
}

void ImageEffect::GetFramesNeededArgs::setOutputs(PropertySet &outArgs) {
  static std::string outBaseName = "OfxImageClipPropFrameRange_";
  
  std::map<std::string, FrameRangeList>::iterator it = inRanges.begin();
  while (it != inRanges.end()) {
    std::string outName = outBaseName + it->first;
    FrameRangeList &frl = it->second;
    int i = 0;
    for (size_t j=0; j<frl.size(); ++j, i+=2) {
      outArgs.setDouble(outName.c_str(), i, frl[j].first);
      outArgs.setDouble(outName.c_str(), i+1, frl[j].second);
    }
    ++it;
  }
}

void ImageEffect::GetFramesNeededArgs::addInputRange(const std::string &name, const FrameRange &range) {
  inRanges[name].push_back(range);
}

// ---

ImageEffect::SequenceArgs::SequenceArgs(ImageEffectHost *host, PropertySet &inArgs)
  : ImageEffect::RenderScaleArgs(host, inArgs) {
  interactive = (inArgs.getInt(kOfxPropIsInteractive, 0) == 1);
#ifdef OFX_API_1_2
  if (host->checkAPIVersion(1, 2)) {
    sequentialRender = (inArgs.getInt(kOfxImageEffectPropSequentialRenderStatus, 0) != 0);
    interactiveRender = (inArgs.getInt(kOfxImageEffectPropInteractiveRenderStatus, 0) != 0);
  } else {
    sequentialRender = false;
    interactiveRender = false;
  }
#endif
}

// ---

ImageEffect::BeginSequenceArgs::BeginSequenceArgs(ImageEffectHost *host, PropertySet &inArgs)
  : ImageEffect::SequenceArgs(host, inArgs) {
  range.first = inArgs.getDouble(kOfxImageEffectPropFrameRange, 0);
  range.second = inArgs.getDouble(kOfxImageEffectPropFrameRange, 1);
  step = inArgs.getDouble(kOfxImageEffectPropFrameStep, 0);
}

// ---

ImageEffect::GetClipPrefArgs::GetClipPrefArgs(ImageEffectHost *) {
}

void ImageEffect::GetClipPrefArgs::setOutputs(PropertySet &outArgs) {
  static std::string compBase = "OfxImageClipPropComponents_";
  static std::string depthBase = "OfxImageClipPropDepth_";
  static std::string parBase = "OfxImageClipPropPAR_";
  
  std::map<std::string, PixelPreferences>::iterator it = inPrefs.begin();
  while (it != inPrefs.end()) {
    std::string name;
    name = compBase + it->first;
    outArgs.setString(name.c_str(), 0, ImageComponentToString(it->second.components));
    name = depthBase + it->first;
    outArgs.setString(name.c_str(), 0, BitDepthToString(it->second.bitDepth));
    name = parBase + it->first;
    outArgs.setDouble(name.c_str(), 0, it->second.pixelAspectRatio);
    ++it;
  }
  outArgs.setDouble(kOfxImageEffectPropFrameRate, 0, outPref.frameRate);
  outArgs.setString(kOfxImageClipPropFieldOrder, 0, ImageFieldOrderToString(outPref.fieldOrder));
  outArgs.setString(kOfxImageEffectPropPreMultiplication, 0, ImagePreMultToString(outPref.preMult));
  outArgs.setInt(kOfxImageClipPropContinuousSamples, 0, (outPref.continuousSamples ? 1 : 0));
  outArgs.setInt(kOfxImageEffectFrameVarying, 0, (outPref.frameVarying ? 1 : 0));
}

void ImageEffect::GetClipPrefArgs::setInputPref(const std::string &name, const PixelPreferences &prefs) {
  inPrefs[name] = prefs;
}

// ---

std::map<OfxImageEffectHandle, ImageEffect*> ImageEffect::msEffects;

ImageEffect* ImageEffect::GetEffect(OfxImageEffectHandle handle) {
  std::map<OfxImageEffectHandle, ImageEffect*>::iterator it = msEffects.find(handle);
  if (it != msEffects.end()) {
    return it->second;
  } else {
    return 0;
  }
}

ImageEffect::ImageEffect()
  : mHandle(0), mHost(0) {
}

ImageEffect::ImageEffect(ImageEffectHost *h, OfxImageEffectHandle hdl)
  : mHandle(0), mHost(h) {
  setHandle(hdl);
}

ImageEffect::~ImageEffect() {
  setHandle(0);
}

void ImageEffect::setHandle(OfxImageEffectHandle handle) throw(Exception) {
  if (mHandle != 0) {
    msEffects.erase(msEffects.find(mHandle));
  }
  if (!mHost) {
    throw BadHandleError("ofx::ImageEffet::setHandle: invalid host");
  }
  mHandle = handle;
  if (mHandle != 0) {
    OfxPropertySetHandle hProps;
    mHost->getImageEffectSuite()->getPropertySet(mHandle, &hProps);
    mProps = PropertySet(mHost, hProps);
    
    OfxParamSetHandle hParams;
    mHost->getImageEffectSuite()->getParamSet(mHandle, &hParams);
    mParams = ParameterSet(mHost, hParams);
    
    msEffects[mHandle] = this;
  }
}

ImageEffectContext ImageEffect::getContext() {
  return StringToImageEffectContext(mProps.getString(kOfxImageEffectPropContext, 0));
}

void* ImageEffect::getInstanceData() {
  return mProps.getPointer(kOfxPropInstanceData, 0);
}

void ImageEffect::setInstanceData(void *data) {
  mProps.setPointer(kOfxPropInstanceData, 0, data);
}

void ImageEffect::getProjectSize(double &w, double &h) {
  w = mProps.getDouble(kOfxImageEffectPropProjectSize, 0);
  h = mProps.getDouble(kOfxImageEffectPropProjectSize, 1);
}

void ImageEffect::getProjectOffset(double &x, double &y) {
  x = mProps.getDouble(kOfxImageEffectPropProjectOffset, 0);
  y = mProps.getDouble(kOfxImageEffectPropProjectOffset, 1);
}

void ImageEffect::getProjectExtent(double &w, double &h) {
  w = mProps.getDouble(kOfxImageEffectPropProjectExtent, 0);
  h = mProps.getDouble(kOfxImageEffectPropProjectExtent, 1);
}

double ImageEffect::getProjectPixelAspectRatio() {
  return mProps.getDouble(kOfxImageEffectPropProjectPixelAspectRatio, 0);
}

double ImageEffect::getDuration() {
  return mProps.getDouble(kOfxImageEffectInstancePropEffectDuration, 0);
}

SequentialRender ImageEffect::getSequentialRender() {
  return SequentialRender(mProps.getInt(kOfxImageEffectInstancePropSequentialRender, 0));
}

void ImageEffect::setSequentialRender(SequentialRender sr) {
  mProps.setInt(kOfxImageEffectInstancePropSequentialRender, 0, int(sr));
}

double ImageEffect::getFrameRate() {
  return mProps.getDouble(kOfxImageEffectPropFrameRate, 0);
}

bool ImageEffect::isInteractive() {
  return (mProps.getInt(kOfxPropIsInteractive, 0) == 1);
}

#ifdef OFX_API_1_2

std::string ImageEffect::getDescription() {
  return mProps.getString(kOfxPropPluginDescription, 0);
}

#endif

Clip ImageEffect::getClip(const std::string &name) throw(Exception) {
  OfxImageClipHandle hClip;
  OfxStatus stat = mHost->getImageEffectSuite()->clipGetHandle(mHandle, name.c_str(), &hClip, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ImageEffect::getClip");
  }
  return Clip(mHost, hClip);
}

bool ImageEffect::abort() throw(Exception) {
  return (mHost->getImageEffectSuite()->abort(mHandle) == 1);
}

OfxImageMemoryHandle ImageEffect::alloc(size_t nBytes) throw(Exception) {
  OfxImageMemoryHandle hdl;
  OfxStatus stat = mHost->getImageEffectSuite()->imageMemoryAlloc(mHandle, nBytes, &hdl);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ImageEffect::alloc");
  }
  return hdl;
}

void* ImageEffect::lock(OfxImageMemoryHandle hdl) throw(Exception) {
  void *ptr = 0;
  OfxStatus stat = mHost->getImageEffectSuite()->imageMemoryLock(hdl, &ptr);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ImageEffect::lock");
  }
  return ptr;
}

void ImageEffect::unlock(OfxImageMemoryHandle hdl) throw(Exception) {
  OfxStatus stat = mHost->getImageEffectSuite()->imageMemoryUnlock(hdl);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ImageEffect::unlock");
  }
}

void ImageEffect::free(OfxImageMemoryHandle hdl) throw(Exception) {
  OfxStatus stat = mHost->getImageEffectSuite()->imageMemoryFree(hdl);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ImageEffect::free");
  }
}

OfxStatus ImageEffect::beginInstanceChanged(ChangeReason) {
  return kOfxStatReplyDefault;
}
      
OfxStatus ImageEffect::endInstanceChanged(ChangeReason) {
  return kOfxStatReplyDefault;
}

OfxStatus ImageEffect::instanceChanged(ImageEffect::InstanceChangedArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus ImageEffect::purgeCaches() {
  return kOfxStatReplyDefault;
}

OfxStatus ImageEffect::syncPrivateData() {
  return kOfxStatReplyDefault;
}

OfxStatus ImageEffect::beginInstanceEdit() {
  return kOfxStatReplyDefault;
}

OfxStatus ImageEffect::endInstanceEdit() {
  return kOfxStatReplyDefault;
}

OfxStatus ImageEffect::getRegionOfDefinition(ImageEffect::GetRoDArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus ImageEffect::getRegionsOfInterest(ImageEffect::GetRoIArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus ImageEffect::getFramesNeeded(ImageEffect::GetFramesNeededArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus ImageEffect::isIdentity(ImageEffect::IsIdentityArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus ImageEffect::render(ImageEffect::RenderArgs &) {
  return kOfxStatFailed;
}

OfxStatus ImageEffect::beginSequenceRender(ImageEffect::BeginSequenceArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus ImageEffect::endSequenceRender(ImageEffect::EndSequenceArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus ImageEffect::getClipPreferences(ImageEffect::GetClipPrefArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus ImageEffect::getTimeDomain(double &, double &) {
  return kOfxStatReplyDefault;
}

}
