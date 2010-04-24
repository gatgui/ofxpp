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

Interact::BaseArgs::BaseArgs(PropertySet &args) {
  OfxImageEffectHandle hEffect = (OfxImageEffectHandle) args.getPointer(kOfxPropEffectInstance, 0);
  effect = ImageEffect::GetEffect(hEffect);
  time = args.getDouble(kOfxPropTime, 0);
  renderScaleX = args.getDouble(kOfxImageEffectPropRenderScale, 0);
  renderScaleY = args.getDouble(kOfxImageEffectPropRenderScale, 1);
}

// ---

Interact::CommonArgs::CommonArgs(PropertySet &args)
  : Interact::BaseArgs(args) {
  viewportWidth = args.getInt(kOfxInteractPropViewportSize, 0);
  viewportHeight = args.getInt(kOfxInteractPropViewportSize, 1);
  pixelScaleX = args.getDouble(kOfxInteractPropPixelScale, 0);
  pixelScaleY = args.getDouble(kOfxInteractPropPixelScale, 1);
  bgColour.r = args.getDouble(kOfxInteractPropBackgroundColour, 0);
  bgColour.g = args.getDouble(kOfxInteractPropBackgroundColour, 1);
  bgColour.b = args.getDouble(kOfxInteractPropBackgroundColour, 2);
  bgColour.a = 1.0;
}

// ---

Interact::PenArgs::PenArgs(PropertySet &args)
  : Interact::CommonArgs(args) {
  x = args.getDouble(kOfxInteractPropPenPosition, 0);
  y = args.getDouble(kOfxInteractPropPenPosition, 1);
  pressure = args.getDouble(kOfxInteractPropPenPressure, 0);  
}

// ---

Interact::KeyArgs::KeyArgs(PropertySet &args)
  : Interact::BaseArgs(args) {
  sym = args.getInt(kOfxPropKeySym, 0);
  string = args.getString(kOfxPropKeyString, 0);
}

// ---

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

Interact::~Interact() {
  if (mHandle != 0) {
    msInteracts.erase(msInteracts.find(mHandle));
  }
}

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

void Interact::draw(Interact::DrawArgs &) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::penMotion(Interact::PenArgs &) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::penDown(Interact::PenArgs &) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::penUp(Interact::PenArgs &) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::keyDown(Interact::KeyArgs &) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::keyUp(Interact::KeyArgs &) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::keyRepeat(Interact::KeyArgs &) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::gainFocus(Interact::FocusArgs &) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

void Interact::loseFocus(Interact::FocusArgs &) throw(Exception) {
  throw Exception(kOfxStatReplyDefault, "Not implemented");
}

}
