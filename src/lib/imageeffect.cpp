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

ImageEffectDescriptor::ImageEffectDescriptor()
  : mHandle(0), mHost(0) {
}

ImageEffectDescriptor::ImageEffectDescriptor(ImageEffectHost *h, OfxImageEffectHandle hdl) throw(Exception)
  : mHandle(hdl), mHost(h) {
  if (!h) {
    throw BadHandleError("ofx::ImageEffectDescriptor::ImageEffectDescriptor: invalid host");
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

std::string ImageEffectDescriptor::label() {
  return mProps.getString(kOfxPropLabel, 0);
}

void ImageEffectDescriptor::label(const std::string &s) {
  mProps.setString(kOfxPropLabel, 0, s);
}

std::string ImageEffectDescriptor::shortLabel() {
  return mProps.getString(kOfxPropShortLabel, 0);
}

void ImageEffectDescriptor::shortLabel(const std::string &s) {
  mProps.setString(kOfxPropShortLabel, 0, s);
}

std::string ImageEffectDescriptor::longLabel() {
  return mProps.getString(kOfxPropLongLabel, 0);
}

void ImageEffectDescriptor::longLabel(const std::string &s) {
  mProps.setString(kOfxPropLongLabel, 0, s);
}

int ImageEffectDescriptor::supportedContextsCount() {
  return mProps.size(kOfxImageEffectPropSupportedContexts);
}

ImageEffectContext ImageEffectDescriptor::supportedContext(int i) {
  return StringToImageEffectContext(mProps.getString(kOfxImageEffectPropSupportedContexts, i));
}

void ImageEffectDescriptor::supportedContext(int i, ImageEffectContext ctx) {
  mProps.setString(kOfxImageEffectPropSupportedContexts, i, ImageEffectContextToString(ctx));
}

std::string ImageEffectDescriptor::group() {
  return mProps.getString(kOfxImageEffectPluginPropGrouping, 0);
}

void ImageEffectDescriptor::group(const std::string &g) {
  mProps.setString(kOfxImageEffectPluginPropGrouping, 0, g);
}

bool ImageEffectDescriptor::singleInstance() {
  return (mProps.getInt(kOfxImageEffectPluginPropSingleInstance, 0) == 1);
}

void ImageEffectDescriptor::singleInstance(bool yes) {
  mProps.setInt(kOfxImageEffectPluginPropSingleInstance, 0, (yes ? 1 : 0));
}

RenderThreadSafety ImageEffectDescriptor::renderThreadSafety() {
  return StringToRenderThreadSafety(mProps.getString(kOfxImageEffectPluginRenderThreadSafety, 0));
}

void ImageEffectDescriptor::renderThreadSafety(RenderThreadSafety rts) {
  mProps.setString(kOfxImageEffectPluginRenderThreadSafety, 0, RenderThreadSafetyToString(rts));
}

bool ImageEffectDescriptor::hostFrameThreading() {
  return (mProps.getInt(kOfxImageEffectPluginPropHostFrameThreading, 0) == 1);
}
  
void ImageEffectDescriptor::hostFrameThreading(bool yes) {
  mProps.setInt(kOfxImageEffectPluginPropHostFrameThreading, 0, (yes ? 1 : 0));
}
 
bool ImageEffectDescriptor::supportsMultiResolution() {
  return (mProps.getInt(kOfxImageEffectPropSupportsMultiResolution, 0) == 1);
}

void ImageEffectDescriptor::supportsMultiResolution(bool yes) {
  mProps.setInt(kOfxImageEffectPropSupportsMultiResolution, 0, (yes ? 1 : 0));
}

bool ImageEffectDescriptor::supportsTiles() {
  return (mProps.getInt(kOfxImageEffectPropSupportsTiles, 0) == 1);
}

void ImageEffectDescriptor::supportsTiles(bool yes) {
  mProps.setInt(kOfxImageEffectPropSupportsTiles, 0, (yes ? 1 : 0));
}

bool ImageEffectDescriptor::temporalClipAccess() {
  return (mProps.getInt(kOfxImageEffectPropTemporalClipAccess, 0) == 1);
}

void ImageEffectDescriptor::temporalClipAccess(bool yes) {
  mProps.setInt(kOfxImageEffectPropTemporalClipAccess, 0, (yes ? 1 : 0));
}
 
int ImageEffectDescriptor::supportedPixelDepthsCount() {
  return mProps.size(kOfxImageEffectPropSupportedPixelDepths);
}

void ImageEffectDescriptor::supportedPixelDepth(int i, BitDepth bd) {
  mProps.setString(kOfxImageEffectPropSupportedPixelDepths, i, BitDepthToString(bd));
}

BitDepth ImageEffectDescriptor::supportedPixelDepth(int i) {
  return StringToBitDepth(mProps.getString(kOfxImageEffectPropSupportedPixelDepths, i));
}

bool ImageEffectDescriptor::fieldRenderTwiceAlways() {
  return (mProps.getInt(kOfxImageEffectPluginPropFieldRenderTwiceAlways, 0) == 1);
}

void ImageEffectDescriptor::fieldRenderTwiceAlways(bool yes) {
  mProps.setInt(kOfxImageEffectPluginPropFieldRenderTwiceAlways, 0, (yes ? 1 : 0));
}

bool ImageEffectDescriptor::supportsMultipleClipDepths() {
  return (mProps.getInt(kOfxImageEffectPropSupportsMultipleClipDepths, 0) == 1);
}

void ImageEffectDescriptor::supportsMultipleClipDepths(bool yes) {
  mProps.setInt(kOfxImageEffectPropSupportsMultipleClipDepths, 0, (yes ? 1 : 0));
}

bool ImageEffectDescriptor::supportsMultipleClipPARs() {
  return (mProps.getInt(kOfxImageEffectPropSupportsMultipleClipPARs, 0) == 1);
}

void ImageEffectDescriptor::supportsMultipleClipPARs(bool yes) {
  mProps.setInt(kOfxImageEffectPropSupportsMultipleClipPARs, 0, (yes ? 1 : 0));
}  

int ImageEffectDescriptor::clipPreferencesSlaveParamCount() {
  return mProps.size(kOfxImageEffectPropClipPreferencesSlaveParam);
}

std::string ImageEffectDescriptor::clipPreferencesSlaveParam(int i) {
  return mProps.getString(kOfxImageEffectPropClipPreferencesSlaveParam, i);
}

void ImageEffectDescriptor::clipPreferencesSlaveParam(int i, const std::string &n) {
  mProps.setString(kOfxImageEffectPropClipPreferencesSlaveParam, i, n);
}

std::string ImageEffectDescriptor::pluginFilePath() {
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

EntryPoint ImageEffectDescriptor::overlayInteract() {
  return ((EntryPoint) mProps.getPointer(kOfxImageEffectPluginPropOverlayInteractV1, 0));
}

void ImageEffectDescriptor::overlayInteract(EntryPoint func) {
  mProps.setPointer(kOfxImageEffectPluginPropOverlayInteractV1, 0, (void*)func);
}

SequentialRender ImageEffectDescriptor::sequentialRender() {
  return SequentialRender(mProps.getInt(kOfxImageEffectInstancePropSequentialRender, 0));
}

void ImageEffectDescriptor::sequentialRender(SequentialRender sr) {
  mProps.setInt(kOfxImageEffectInstancePropSequentialRender, 0, int(sr));
}

#ifdef OFX_API_1_2

int ImageEffectDescriptor::version(int level) {
  return (mProps.size(kOfxPropVersion) > level ? mProps.getInt(kOfxPropVersion, level) : 0);
}

int ImageEffectDescriptor::majorVersion() {
  return (mProps.size(kOfxPropVersion) > 0 ? mProps.getInt(kOfxPropVersion, 0) : 0);
}

int ImageEffectDescriptor::minorVersion() {
  return (mProps.size(kOfxPropVersion) > 1 ? mProps.getInt(kOfxPropVersion, 1) : 0);
}

void ImageEffectDescriptor::version(int level, int v) {
  mProps.setInt(kOfxPropVersion, level, v);
}

std::string ImageEffectDescriptor::versionLabel() {
  return mProps.getString(kOfxPropVersionLabel, 0);
}

void ImageEffectDescriptor::versionLabel(const std::string &vl) {
  mProps.setString(kOfxPropVersionLabel, 0, vl);
}

std::string ImageEffectDescriptor::description() {
  return mProps.getString(kOfxPropPluginDescription, 0);
}

void ImageEffectDescriptor::description(const std::string &d) {
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
      outArgs.setDouble(outName.c_str(), i, frl[j].min);
      outArgs.setDouble(outName.c_str(), i+1, frl[j].max);
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
  range.min = inArgs.getDouble(kOfxImageEffectPropFrameRange, 0);
  range.max = inArgs.getDouble(kOfxImageEffectPropFrameRange, 1);
  step = inArgs.getDouble(kOfxImageEffectPropFrameStep, 0);
}

// ---

ImageEffect::GetClipPrefArgs::GetClipPrefArgs(ImageEffectHost *) {
}

void ImageEffect::GetClipPrefArgs::setOutputs(PropertySet &outArgs) {
  static std::string compBase = "OfxImageClipPropComponents_";
  static std::string depthBase = "OfxImageClipPropDepth_";
  static std::string parBase = "OfxImageClipPropPAR_";
  
  std::map<std::string, InputClipPreferences>::iterator it = inPrefs.begin();
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

void ImageEffect::GetClipPrefArgs::setInputPref(const std::string &name, const InputClipPreferences &prefs) {
  inPrefs[name] = prefs;
}

// ---

ImageEffect::GetTimeDomainArgs::GetTimeDomainArgs(ImageEffectHost *) {
}

void ImageEffect::GetTimeDomainArgs::setOutputs(PropertySet &outArgs) {
  outArgs.setDouble(kOfxImageEffectPropFrameRange, 0, first);
  outArgs.setDouble(kOfxImageEffectPropFrameRange, 1, last);
}

// ---

std::map<OfxImageEffectHandle, ImageEffect*> ImageEffect::msEffects;
std::map<OfxParamSetHandle, ImageEffect*> ImageEffect::msParamSetEffects;

ImageEffect* ImageEffect::GetEffect(OfxImageEffectHandle handle) {
  std::map<OfxImageEffectHandle, ImageEffect*>::iterator it = msEffects.find(handle);
  if (it != msEffects.end()) {
    return it->second;
  } else {
    return 0;
  }
}

ImageEffect* ImageEffect::GetEffectForParams(OfxParamSetHandle handle) {
  std::map<OfxParamSetHandle, ImageEffect*>::iterator it = msParamSetEffects.find(handle);
  if (it != msParamSetEffects.end()) {
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
  handle(hdl);
}

ImageEffect::~ImageEffect() {
  handle(0);
}

void ImageEffect::handle(OfxImageEffectHandle handle) throw(Exception) {
  if (mHandle != 0) {
    msEffects.erase(msEffects.find(mHandle));
  }
  if (!mHost) {
    throw BadHandleError("ofx::ImageEffet::setHandle: invalid host");
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

ImageEffectContext ImageEffect::context() {
  return StringToImageEffectContext(mProps.getString(kOfxImageEffectPropContext, 0));
}

void* ImageEffect::instanceData() {
  return mProps.getPointer(kOfxPropInstanceData, 0);
}

void ImageEffect::instanceData(void *data) {
  mProps.setPointer(kOfxPropInstanceData, 0, data);
}

void ImageEffect::projectSize(double *w, double *h) {
  *w = mProps.getDouble(kOfxImageEffectPropProjectSize, 0);
  *h = mProps.getDouble(kOfxImageEffectPropProjectSize, 1);
}

void ImageEffect::projectOffset(double *x, double *y) {
  *x = mProps.getDouble(kOfxImageEffectPropProjectOffset, 0);
  *y = mProps.getDouble(kOfxImageEffectPropProjectOffset, 1);
}

void ImageEffect::projectExtent(double *w, double *h) {
  *w = mProps.getDouble(kOfxImageEffectPropProjectExtent, 0);
  *h = mProps.getDouble(kOfxImageEffectPropProjectExtent, 1);
}

double ImageEffect::projectPixelAspectRatio() {
  return mProps.getDouble(kOfxImageEffectPropProjectPixelAspectRatio, 0);
}

double ImageEffect::duration() {
  return mProps.getDouble(kOfxImageEffectInstancePropEffectDuration, 0);
}

SequentialRender ImageEffect::sequentialRender() {
  return SequentialRender(mProps.getInt(kOfxImageEffectInstancePropSequentialRender, 0));
}

void ImageEffect::sequentialRender(SequentialRender sr) {
  mProps.setInt(kOfxImageEffectInstancePropSequentialRender, 0, int(sr));
}

double ImageEffect::frameRate() {
  return mProps.getDouble(kOfxImageEffectPropFrameRate, 0);
}

bool ImageEffect::isInteractive() {
  return (mProps.getInt(kOfxPropIsInteractive, 0) == 1);
}

bool ImageEffect::inAnalysis() {
  return (mProps.getInt(kOfxImageEffectPropInAnalysis, 0) == 1);
}

void ImageEffect::inAnalysis(bool v) {
  mProps.setInt(kOfxImageEffectPropInAnalysis, 0, (v ? 1 : 0));
}

ImageEffectDescriptor ImageEffect::descriptor() {
  OfxImageEffectHandle hdl = (OfxImageEffectHandle) mProps.getPointer(kOfxImageEffectPropPluginHandle, 0);
  return ImageEffectDescriptor(host(), hdl);
}

#ifdef OFX_API_1_2

std::string ImageEffect::description() {
  return mProps.getString(kOfxPropPluginDescription, 0);
}

#endif

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

OfxImageMemoryHandle ImageEffect::alloc(int w, int h, ImageComponent comps, BitDepth depth) throw(Exception)
{
  if (depth <= BitDepthNone || depth >= MaxBitDepth)
  {
    throw FailedError("ofx::ImageEffect::alloc: Invalid depth");
  }
  
  if (comps <= ImageComponentNone || comps >= MaxImageComponent)
  {
    throw FailedError("ofx::ImageEffect::alloc: Invalid components");
  }
  
  static size_t cs[] = {1, 2, 4};
#ifdef OFX_API_1_2
  static size_t cc[] = {3, 4, 1, 4};
#else
  static size_t cc[] = {4, 1, 4};
#endif
  
  size_t sz = w * h * cc[comps] * cs[depth];
  
  return alloc(sz);
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

OfxStatus ImageEffect::getTimeDomain(ImageEffect::GetTimeDomainArgs &) {
  return kOfxStatReplyDefault;
}

}
