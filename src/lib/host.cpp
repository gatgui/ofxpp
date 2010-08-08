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

#include <ofx/host.h>
#include <ofx/memory.h>
#include <ofx/message.h>
#include <ofx/progress.h>
#include <ofx/multithread.h>
#include <ofx/timeline.h>
#include <ofx/parameter.h>
#include <ofx/imageeffect.h>
#include <ofx/interact.h>

namespace ofx {

// this disqualifies ofxpp to be used as a shared library
static Host *gsHost = 0;

Host* Host::Get()
{
  return gsHost;
}

Host::Host(OfxHost *host) throw(Exception)
  : PropertySet(), mHost(host), mTimeLine(0), mProgress(0), mMessage(0),
    mMemory(0), mMultiThread(0), mPropSuite(0), mParamSuite(0) {
  if (host == 0) {
    throw BadHandleError("Host");
  }
  // this member comes from PropertySet
  mHandle = mHost->host;
}

Host::~Host() {
  if (mTimeLine) {
    delete mTimeLine;
  }
  if (mProgress) {
    delete mProgress;
  }
  if (mMessage) {
    delete mMessage;
  }
  if (mMemory) {
    delete mMemory;
  }
  if (mMultiThread) {
    delete mMultiThread;
  }
}

void Host::init() throw(Exception) {
  mPropSuite = fetchSuite<OfxPropertySuiteV1>(kOfxPropertySuite, 1);
  if (!mPropSuite) {
    throw MissingHostFeatureError("Property suite");
  }
  
  mSuite = mPropSuite;
  
  mTimeLine = new TimeLineSuite(this);
  
  mMultiThread = new MultiThreadSuite(this);
  
  mMemory = new MemorySuite(this);
  
  mMessage = new MessageSuite(this);
  
  mProgress = new ProgressSuite(this);
  
  mParamSuite = fetchSuite<OfxParameterSuiteV1>(kOfxParameterSuite, 1);
  if (!mParamSuite) {
    throw MissingHostFeatureError("Parameter suite");
  }
  
#ifdef OFX_API_1_2
  mParametricParamSuite = fetchSuite<OfxParametricParameterSuiteV1>(kOfxParametricParameterSuite, 1);
  if (!mParametricParamSuite && checkAPIVersion(1, 2)) {
    // Host supporting OpenFX API 1.2 or above MUST provide this suite
    throw MissingHostFeatureError("Parametric parameter suite");
  }
#endif
  
  gsHost = this;
}

int Host::getAPIVersion(int level) {
#ifdef OFX_API_1_2
  try {
    return getInt(kOfxPropAPIVersion, level);
  } catch (...) {
    return (level < 2 ? 1 : 0);
  }
#else
  return (level == 0 ? 1 : (level == 1 ? 1 : 0));
#endif
}

int Host::getAPIMajorVersion() {
#ifdef OFX_API_1_2
  try {
    return getInt(kOfxPropAPIVersion, 0);
  } catch (...) {
    return 1;
  }
#else
  return 1;
#endif
}

int Host::getAPIMinorVersion() {
#ifdef OFX_API_1_2
  try {
    return getInt(kOfxPropAPIVersion, 1);
  } catch (...) {
    return 1;
  }
#else
  return 1;
#endif
}

bool Host::checkAPIVersion(int major, int minor) {
  int apiMaj = getAPIMajorVersion();
  int apiMin = getAPIMinorVersion();
  return (apiMaj > major || (apiMaj == major && apiMin >= minor));
}

#ifdef OFX_API_1_2

int Host::getVersion(int level) {
  return (size(kOfxPropVersion) > level ? getInt(kOfxPropVersion, level) : 0);
}

int Host::getMajorVersion() {
  return (size(kOfxPropVersion) > 0 ? getInt(kOfxPropVersion, 0) : 0);
}

int Host::getMinorVersion() {
  return (size(kOfxPropVersion) > 1 ? getInt(kOfxPropVersion, 1) : 0);
}

std::string Host::getVersionLabel() {
  return getString(kOfxPropVersionLabel, 0);
}

void* Host::getOSHandle() {
  return getPointer(kOfxPropHostOSHandle, 0);
}

#endif

// ---

// this disqualifies ofxpp to be used as a shared library
static ImageEffectHost *gsImageEffectHost = 0;

ImageEffectHost* ImageEffectHost::Get()
{
  return gsImageEffectHost;
}

ImageEffectHost::ImageEffectHost(OfxHost *h)
  : Host(h), mInteractSuite(0), mImageEffectSuite(0) {
}

ImageEffectHost::~ImageEffectHost() {
}

void ImageEffectHost::init() throw(Exception) {
  Host::init();
  mInteractSuite = fetchSuite<OfxInteractSuiteV1>(kOfxInteractSuite, 1);
  if (!mInteractSuite) {
    throw MissingHostFeatureError("Interact suite");
  }
  mImageEffectSuite = fetchSuite<OfxImageEffectSuiteV1>(kOfxImageEffectSuite, 1);
  if (!mImageEffectSuite) {
    throw MissingHostFeatureError("Image effect suite");
  }
  gsImageEffectHost = this;
}

std::string ImageEffectHost::getName() {
  return getString(kOfxPropName, 0);
}

std::string ImageEffectHost::getLabel() {
  return getString(kOfxPropLabel, 0);
}

bool ImageEffectHost::isBackground() {
  return (getInt(kOfxImageEffectHostPropIsBackground, 0) == 1);
}

bool ImageEffectHost::supportOverlays() {
  return (getInt(kOfxImageEffectPropSupportsOverlays, 0) == 1);
}

bool ImageEffectHost::supportMultiResolution() {
  return (getInt(kOfxImageEffectPropSupportsMultiResolution, 0) == 1);
}

bool ImageEffectHost::supportTiles() {
  return (getInt(kOfxImageEffectPropSupportsTiles, 0) == 1);
}

bool ImageEffectHost::supportTemporalClipAccess() {
  return (getInt(kOfxImageEffectPropTemporalClipAccess, 0) == 1);
}

int ImageEffectHost::getSupportedComponentsCount() {
  return size(kOfxImageEffectPropSupportedComponents);
}

ImageComponent ImageEffectHost::getSupportedComponent(int idx) {
  return StringToImageComponent(getString(kOfxImageEffectPropSupportedComponents, idx));
}

int ImageEffectHost::getSupportedPixelDepthsCount() {
  return size(kOfxImageEffectPropSupportedPixelDepths);
}

BitDepth ImageEffectHost::getSupportedPixelDepth(int idx) {
  return StringToBitDepth(getString(kOfxImageEffectPropSupportedPixelDepths, idx));
}

int ImageEffectHost::getSupportedContextsCount() {
  return size(kOfxImageEffectPropSupportedContexts);
}

ImageEffectContext ImageEffectHost::getSupportedContext(int idx) {
  return StringToImageEffectContext(getString(kOfxImageEffectPropSupportedContexts, idx));
}

bool ImageEffectHost::supportMultipleClipDepths() {
  return (getInt(kOfxImageEffectPropSupportsMultipleClipDepths, 0) == 1);
}

bool ImageEffectHost::supportMultipleClipPARs() {
  return (getInt(kOfxImageEffectPropSupportsMultipleClipPARs, 0) == 1);
}

bool ImageEffectHost::isFramerateSetable() {
  return (getInt(kOfxImageEffectPropSetableFrameRate, 0) == 1);
}

bool ImageEffectHost::isFieldingSetable() {
  return (getInt(kOfxImageEffectPropSetableFielding, 0) == 1);
}

bool ImageEffectHost::supportCustomParamAnimation() {
  return (getInt(kOfxParamHostPropSupportsCustomAnimation, 0) == 1);
}

bool ImageEffectHost::supportStringParamAnimation() {
  return (getInt(kOfxParamHostPropSupportsStringAnimation, 0) == 1);
}

bool ImageEffectHost::supportChoiceParamAnimation() {
  return (getInt(kOfxParamHostPropSupportsChoiceAnimation, 0) == 1);
}

bool ImageEffectHost::supportBooleanParamAnimation() {
  return (getInt(kOfxParamHostPropSupportsBooleanAnimation, 0) == 1);
}

bool ImageEffectHost::supportParamCustomInteract() {
  return (getInt(kOfxParamHostPropSupportsCustomInteract, 0) == 1);
}

int ImageEffectHost::getMaxParameters() {
  return (getInt(kOfxParamHostPropMaxParameters, 0));
}

int ImageEffectHost::getMaxParameterPages() {
  return (getInt(kOfxParamHostPropMaxPages, 0));
}

void ImageEffectHost::getParameterPageRowColumnCount(int &rowCount, int &columnCount) {
  columnCount = getInt(kOfxParamHostPropPageRowColumnCount, 0);
  rowCount = getInt(kOfxParamHostPropPageRowColumnCount, 1);
}

#ifdef OFX_API_1_2

SequentialRender ImageEffectHost::getSequentialRender() {
  return SequentialRender(getInt(kOfxImageEffectInstancePropSequentialRender, 0));
}

bool ImageEffectHost::supportParametricParamAnimation() {
  return (getInt(kOfxParamHostPropSupportsParametricAnimation, 0) == 1);
}

#endif

}

