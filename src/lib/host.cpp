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
    throw Exception(kOfxStatErrMissingHostFeature, "Invalid Host handle");
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
    throw Exception(kOfxStatErrMissingHostFeature, "Missing property suite");
  }
  mParamSuite = fetchSuite<OfxParameterSuiteV1>(kOfxParameterSuite, 1);
  if (!mParamSuite) {
    throw Exception(kOfxStatErrMissingHostFeature, "Missing parameter suite");
  }
  // this member comes from PropertySet
  mSuite = mPropSuite;
}

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
    throw Exception(kOfxStatErrMissingHostFeature, "Missing interact suite");
  }
  mImageEffectSuite = fetchSuite<OfxImageEffectSuiteV1>(kOfxImageEffectSuite, 1);
  if (!mImageEffectSuite) {
    throw Exception(kOfxStatErrMissingHostFeature, "Missing image effect suite");
  }
}

std::string ImageEffectHost::name() throw(Exception) {
  return getString(kOfxPropName, 0);
}

std::string ImageEffectHost::label() throw(Exception) {
  return getString(kOfxPropLabel, 0);
}

bool ImageEffectHost::isBackground() throw(Exception) {
  return (getInt(kOfxImageEffectHostPropIsBackground, 0) == 1);
}

bool ImageEffectHost::supportsOverlays() throw(Exception) {
  return (getInt(kOfxImageEffectPropSupportsOverlays, 0) == 1);
}

bool ImageEffectHost::supportsMultiResolution() throw(Exception) {
  return (getInt(kOfxImageEffectPropSupportsMultiResolution, 0) == 1);
}

bool ImageEffectHost::supportsTiles() throw(Exception) {
  return (getInt(kOfxImageEffectPropSupportsTiles, 0) == 1);
}

bool ImageEffectHost::supportsTemporalClipAccess() throw(Exception) {
  return (getInt(kOfxImageEffectPropTemporalClipAccess, 0) == 1);
}

int ImageEffectHost::supportedComponentsCount() throw(Exception) {
  return size(kOfxImageEffectPropSupportedComponents);
}

ImageComponent ImageEffectHost::getSupportedComponent(int idx) throw(Exception) {
  return StringToImageComponent(getString(kOfxImageEffectPropSupportedComponents, idx));
}

int ImageEffectHost::supportedContextsCount() throw(Exception) {
  return size(kOfxImageEffectPropSupportedContexts);
}

ImageEffectContext ImageEffectHost::getSupportedContext(int idx) throw(Exception) {
  return StringToImageEffectContext(getString(kOfxImageEffectPropSupportedContexts, idx));
}

bool ImageEffectHost::supportsMultipleClipDepths() throw(Exception) {
  return (getInt(kOfxImageEffectPropSupportsMultipleClipDepths, 0) == 1);
}

bool ImageEffectHost::supportsMultipleClipPARs() throw(Exception) {
  return (getInt(kOfxImageEffectPropSupportsMultipleClipPARs, 0) == 1);
}

bool ImageEffectHost::setableFramerate() throw(Exception) {
  return (getInt(kOfxImageEffectPropSetableFrameRate, 0) == 1);
}

bool ImageEffectHost::setableFielding() throw(Exception) {
  return (getInt(kOfxImageEffectPropSetableFielding, 0) == 1);
}

bool ImageEffectHost::supportsCustomParamAnimation() throw(Exception) {
  return (getInt(kOfxParamHostPropSupportsCustomAnimation, 0) == 1);
}

bool ImageEffectHost::supportsStringParamAnimation() throw(Exception) {
  return (getInt(kOfxParamHostPropSupportsStringAnimation, 0) == 1);
}

bool ImageEffectHost::supportsChoiceParamAnimation() throw(Exception) {
  return (getInt(kOfxParamHostPropSupportsChoiceAnimation, 0) == 1);
}

bool ImageEffectHost::supportsBooleanParamAnimation() throw(Exception) {
  return (getInt(kOfxParamHostPropSupportsBooleanAnimation, 0) == 1);
}

bool ImageEffectHost::supportsParamCustomInteract() throw(Exception) {
  return (getInt(kOfxParamHostPropSupportsCustomInteract, 0) == 1);
}

int ImageEffectHost::maxParameters() throw(Exception) {
  return (getInt(kOfxParamHostPropMaxParameters, 0));
}

int ImageEffectHost::maxParameterPages() throw(Exception) {
  return (getInt(kOfxParamHostPropMaxPages, 0));
}

void ImageEffectHost::parameterPageRowColumnCount(int &rowCount, int &columnCount) throw(Exception) {
  columnCount = getInt(kOfxParamHostPropPageRowColumnCount, 0);
  rowCount = getInt(kOfxParamHostPropPageRowColumnCount, 1);
}

}

