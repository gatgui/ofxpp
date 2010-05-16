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
  mTimeLine = new TimeLine(this);
  mMultiThread = new MultiThread(this);
  mMemory = new Memory(this);
  mMessage = new Message(this);
  mProgress = new Progress(this);
  mPropSuite = fetchSuite<OfxPropertySuiteV1>(kOfxPropertySuite, 1);
  if (!mPropSuite) {
    throw MissingHostFeatureError("Property suite");
  }
  mParamSuite = fetchSuite<OfxParameterSuiteV1>(kOfxParameterSuite, 1);
  if (!mParamSuite) {
    throw MissingHostFeatureError("Parameter suite");
  }
  // this member comes from PropertySet
  mSuite = mPropSuite;
}

int Host::APIVersion(int level) {
#if OFX_VERSION_MAJOR > 1 || OFX_VERSION_MINOR >= 2
  return (size(kOfxPropAPIVersion) > level ? getInt(kOfxPropAPIVersion, level) : (level < 2 ? 1 : 0));
#else
  return (level == 0 ? 1 : (level == 1 ? 1 : 0));
#endif
}

int Host::APIMajorVersion() {
#if OFX_VERSION_MAJOR > 1 || OFX_VERSION_MINOR >= 2
  return (size(kOfxPropAPIVersion) > 0 ? getInt(kOfxPropAPIVersion, 0) : 1);
#else
  return 1;
#endif
}

int Host::APIMinorVersion() {
#if OFX_VERSION_MAJOR > 1 || OFX_VERSION_MINOR >= 2
  return (size(kOfxPropAPIVersion) > 1 ? getInt(kOfxPropAPIVersion, 1) : 1);
#else
  return 1;
#endif
}

#if OFX_VERSION_MAJOR > 1 || OFX_VERSION_MINOR >= 2

int Host::version(int level) {
  return (size(kOfxPropVersion) > level ? getInt(kOfxPropVersion, level) : 0);
}

int Host::majorVersion() {
  return (size(kOfxPropVersion) > 0 ? getInt(kOfxPropVersion, 0) : 0);
}

int Host::minorVersion() {
  return (size(kOfxPropVersion) > 1 ? getInt(kOfxPropVersion, 1) : 0);
}

std::string Host::versionLabel() {
  return getString(kOfxPropVersionLabel, 0);
}

void* Host::OSHandle() {
  return getPointer(kOfxPropHostOSHandle, 0);
}

#endif

// ---

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
}

std::string ImageEffectHost::name() {
  return getString(kOfxPropName, 0);
}

std::string ImageEffectHost::label() {
  return getString(kOfxPropLabel, 0);
}

bool ImageEffectHost::isBackground() {
  return (getInt(kOfxImageEffectHostPropIsBackground, 0) == 1);
}

bool ImageEffectHost::supportsOverlays() {
  return (getInt(kOfxImageEffectPropSupportsOverlays, 0) == 1);
}

bool ImageEffectHost::supportsMultiResolution() {
  return (getInt(kOfxImageEffectPropSupportsMultiResolution, 0) == 1);
}

bool ImageEffectHost::supportsTiles() {
  return (getInt(kOfxImageEffectPropSupportsTiles, 0) == 1);
}

bool ImageEffectHost::supportsTemporalClipAccess() {
  return (getInt(kOfxImageEffectPropTemporalClipAccess, 0) == 1);
}

int ImageEffectHost::supportedComponentsCount() {
  return size(kOfxImageEffectPropSupportedComponents);
}

ImageComponent ImageEffectHost::getSupportedComponent(int idx) {
  return StringToImageComponent(getString(kOfxImageEffectPropSupportedComponents, idx));
}

int ImageEffectHost::supportedPixelDepthsCount() {
  return size(kOfxImageEffectPropSupportedPixelDepths);
}

BitDepth ImageEffectHost::getSupportedPixelDepth(int idx) {
  return StringToBitDepth(getString(kOfxImageEffectPropSupportedPixelDepths, idx));
}

int ImageEffectHost::supportedContextsCount() {
  return size(kOfxImageEffectPropSupportedContexts);
}

ImageEffectContext ImageEffectHost::getSupportedContext(int idx) {
  return StringToImageEffectContext(getString(kOfxImageEffectPropSupportedContexts, idx));
}

bool ImageEffectHost::supportsMultipleClipDepths() {
  return (getInt(kOfxImageEffectPropSupportsMultipleClipDepths, 0) == 1);
}

bool ImageEffectHost::supportsMultipleClipPARs() {
  return (getInt(kOfxImageEffectPropSupportsMultipleClipPARs, 0) == 1);
}

bool ImageEffectHost::setableFramerate() {
  return (getInt(kOfxImageEffectPropSetableFrameRate, 0) == 1);
}

bool ImageEffectHost::setableFielding() {
  return (getInt(kOfxImageEffectPropSetableFielding, 0) == 1);
}

bool ImageEffectHost::supportsCustomParamAnimation() {
  return (getInt(kOfxParamHostPropSupportsCustomAnimation, 0) == 1);
}

bool ImageEffectHost::supportsStringParamAnimation() {
  return (getInt(kOfxParamHostPropSupportsStringAnimation, 0) == 1);
}

bool ImageEffectHost::supportsChoiceParamAnimation() {
  return (getInt(kOfxParamHostPropSupportsChoiceAnimation, 0) == 1);
}

bool ImageEffectHost::supportsBooleanParamAnimation() {
  return (getInt(kOfxParamHostPropSupportsBooleanAnimation, 0) == 1);
}

bool ImageEffectHost::supportsParamCustomInteract() {
  return (getInt(kOfxParamHostPropSupportsCustomInteract, 0) == 1);
}

int ImageEffectHost::maxParameters() {
  return (getInt(kOfxParamHostPropMaxParameters, 0));
}

int ImageEffectHost::maxParameterPages() {
  return (getInt(kOfxParamHostPropMaxPages, 0));
}

void ImageEffectHost::parameterPageRowColumnCount(int &rowCount, int &columnCount) {
  columnCount = getInt(kOfxParamHostPropPageRowColumnCount, 0);
  rowCount = getInt(kOfxParamHostPropPageRowColumnCount, 1);
}

#if OFX_VERSION_MAJOR > 1 || OFX_VERSION_MINOR >= 2

SequentialRender ImageEffectHost::sequentialRender() {
  return SequentialRender(getInt(kOfxImageEffectInstancePropSequentialRender, 0));
}

#endif

}

