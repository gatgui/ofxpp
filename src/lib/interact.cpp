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

#include <ofx/interact.h>
#include <ofx/host.h>

namespace ofx {

//OfxInteractSuiteV1 * InteractDescriptor::msSuiteV1 = 0;

InteractDescriptor::InteractDescriptor()
  : mHandle(0) {
}

InteractDescriptor::InteractDescriptor(ImageEffectHost *h, OfxInteractHandle hdl) throw(Exception)
  : mHandle(hdl) {
  if (!h) {
    throw Exception(kOfxStatErrFatal, "ofx::InteractDescriptor::InteractDescriptor: no host");
  }
  if (!h->interactSuite()) {
    throw Exception(kOfxStatErrMissingHostFeature, "ofx::InteractDescriptor::InteractDescriptor: no interact suite");
  }
  OfxPropertySetHandle hProps;
  h->interactSuite()->interactGetPropertySet(mHandle, &hProps);
  mProps = PropertySet(h, hProps);
}

InteractDescriptor::InteractDescriptor(const InteractDescriptor &rhs)
  : mHandle(rhs.mHandle), mProps(rhs.mProps) {
}

InteractDescriptor::~InteractDescriptor() {
}

InteractDescriptor& InteractDescriptor::operator=(const InteractDescriptor &rhs) {
  mHandle = rhs.mHandle;
  mProps = rhs.mProps;
  return *this;
}

//InteractDescriptor& InteractDescriptor::operator=(OfxInteractHandle hdl) {
//  mHandle = hdl;
//  if (mHandle != 0 && msSuiteV1 != 0) {
//    OfxPropertySetHandle hProps;
//    msSuiteV1->interactGetPropertySet(mHandle, &hProps);
//    mProps = hProps;
//  }
//  return *this;
//}

bool InteractDescriptor::hasAlpha() throw(Exception) {
  return (mProps.getInt(kOfxInteractPropHasAlpha, 0) == 1);
}

int InteractDescriptor::bitDepth() throw(Exception) {
  return mProps.getInt(kOfxInteractPropBitDepth, 0);
}

void InteractDescriptor::describe() throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}
  
// ---

//OfxInteractSuiteV1 * Interact::msSuiteV1 = 0;

//void Interact::Init(Host *h) throw(Exception) {
//  if (h) {
//    msSuiteV1 = h->fetchSuite<OfxInteractSuiteV1>(kOfxInteractSuite, 1);
//    if (msSuiteV1) {
//      InteractDescriptor::msSuiteV1 = msSuiteV1;
//      return;
//    }
//  }
//  throw Exception(kOfxStatErrMissingHostFeature, "Cannot initialize ofx::Interact");
//}

std::map<OfxInteractHandle, Interact*> Interact::msInteracts;
    
Interact* Interact::GetInteract(OfxInteractHandle hdl) {
  std::map<OfxInteractHandle, Interact*>::iterator it = msInteracts.find(hdl);
  if (it != msInteracts.end()) {
    return it->second;
  } else {
    return 0;
  }
}

Interact::Interact()
  : mHandle(0), mSuite(0) {
}

Interact::Interact(ImageEffectHost *h, OfxInteractHandle hdl) throw(Exception)
  : mHandle(hdl) {
  if (!h) {
    throw Exception(kOfxStatErrFatal, "ofx::Interact::Interact: no host");
  }
  if (!h->interactSuite()) {
    throw Exception(kOfxStatErrMissingHostFeature, "ofx::Interact::Interact: no interact suite");
  }
  mSuite = h->interactSuite();
  OfxPropertySetHandle hProps;
  mSuite->interactGetPropertySet(mHandle, &hProps);
  mProps = PropertySet(h, hProps);
  msInteracts[hdl] = this;
}

//Interact::Interact(const Interact &rhs)
//  : mHandle(rhs.mHandle), mProps(rhs.mProps), mSuite(rhs.mSuite) {
//}

Interact::~Interact() {
  if (mHandle != 0) {
    msInteracts.erase(msInteracts.find(mHandle));
  }
}

//Interact& Interact::operator=(const Interact &rhs) {
//  mHandle = rhs.mHandle;
//  mProps = rhs.mProps;
//  mSuite = rhs.mSuite;
//  return *this;
//}

//Interact& Interact::operator=(OfxInteractHandle hdl) {
//  mHandle = hdl;
//  if (mHandle != 0 && msSuiteV1 != 0) {
//    OfxPropertySetHandle hProps;
//    msSuiteV1->interactGetPropertySet(mHandle, &hProps);
//    mProps = hProps;
//  }
//  return *this;
//}

void Interact::swapBuffers() throw(Exception) {
  OfxStatus stat = mSuite->interactSwapBuffers(mHandle);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Interact::swapBuffers");
  }
}

void Interact::redraw() throw(Exception) {
  OfxStatus stat = mSuite->interactRedraw(mHandle);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Interact::redraw");
  }
}

ImageEffect* Interact::effectInstance() throw(Exception) {
  OfxImageEffectHandle hdl = (OfxImageEffectHandle) mProps.getPointer(kOfxPropEffectInstance, 0);
  return ImageEffect::GetEffect(hdl);
}

void* Interact::instanceData() throw(Exception) {
  return mProps.getPointer(kOfxPropInstanceData, 0);
}

void Interact::setInstanceData(void *d) throw(Exception) {
  mProps.setPointer(kOfxPropInstanceData, 0, d);
}

void Interact::pixelScale(double &sx, double &sy) throw(Exception) {
  sx = mProps.getDouble(kOfxInteractPropPixelScale, 0);
  sy = mProps.getDouble(kOfxInteractPropPixelScale, 1);
}

RGBAColour<double> Interact::backgroundColor() throw(Exception) {
  RGBAColour<double> color;
  color.r = mProps.getDouble(kOfxInteractPropBackgroundColour, 0);
  color.g = mProps.getDouble(kOfxInteractPropBackgroundColour, 1);
  color.b = mProps.getDouble(kOfxInteractPropBackgroundColour, 2);
  color.a = 1.0;
  return color;
}

void Interact::viewportSize(int &w, int &h) throw(Exception) {
  w = mProps.getInt(kOfxInteractPropViewportSize, 0);
  h = mProps.getInt(kOfxInteractPropViewportSize, 1);
}

bool Interact::hasAlpha() throw(Exception) {
  return (mProps.getInt(kOfxInteractPropHasAlpha, 0) == 1);
}

int Interact::bitDepth() throw(Exception) {
  return mProps.getInt(kOfxInteractPropBitDepth, 0);
}

int Interact::slaveToParamCount() throw(Exception) {
  return mProps.size(kOfxInteractPropSlaveToParam);
}

std::string Interact::getSlaveToParam(int i) throw(Exception) {
  return mProps.getString(kOfxInteractPropSlaveToParam, i);
}

void Interact::setSlaveToParam(int i, const std::string &pn) throw(Exception) {
  mProps.setString(kOfxInteractPropSlaveToParam, i, pn);
}

void Interact::draw(ImageEffect *, //int w, int h,
                    double, double,
                    const RGBAColour<double> &, Time,
                    double, double) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::penMotion(ImageEffect *, //int w, int h,
                         double, double,
                         const RGBAColour<double> &, Time,
                         double, double,
                         double, double, double) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::penDown(ImageEffect *, //int w, int h,
                       double, double,
                       const RGBAColour<double> &, Time,
                       double, double,
                       double, double, double) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::penUp(ImageEffect *, //int w, int h,
                     double, double,
                     const RGBAColour<double> &, Time,
                     double, double,
                     double, double, double) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::keyDown(ImageEffect *,
                       int, const std::string &,
                       Time, double, double) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::keyUp(ImageEffect *,
                     int, const std::string &,
                     Time, double, double) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::keyRepeat(ImageEffect *,
                         int, const std::string &,
                         Time, double, double) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::gainFocus(ImageEffect *, //int w, int h,
                         double, double,
                         const RGBAColour<double> &, Time,
                         double, double) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::loseFocus(ImageEffect *, //int w, int h,
                         double, double,
                         const RGBAColour<double> &, Time,
                         double, double) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

}
