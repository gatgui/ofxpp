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
    throw BadHandleError("ofx::InteractDescriptor::InteractDescriptor: invalid host");
  }
  if (!h->interactSuite()) {
    throw MissingHostFeatureError("Interact suite");
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

bool InteractDescriptor::hasAlpha() {
  return (mProps.getInt(kOfxInteractPropHasAlpha, 0) == 1);
}

int InteractDescriptor::bitDepth() {
  return mProps.getInt(kOfxInteractPropBitDepth, 0);
}

OfxStatus InteractDescriptor::describe() {
  //return kOfxStatReplyDefault;
  return kOfxStatOK;
}
  
// ---

Interact::BaseArgs::BaseArgs(ImageEffectHost *, PropertySet &args) {
  OfxImageEffectHandle hEffect = (OfxImageEffectHandle) args.getPointer(kOfxPropEffectInstance, 0);
  effect = ImageEffect::GetEffect(hEffect);
  time = args.getDouble(kOfxPropTime, 0);
  renderScaleX = args.getDouble(kOfxImageEffectPropRenderScale, 0);
  renderScaleY = args.getDouble(kOfxImageEffectPropRenderScale, 1);
}

// ---

Interact::CommonArgs::CommonArgs(ImageEffectHost *host, PropertySet &args)
  : Interact::BaseArgs(host, args) {
  //viewportWidth = args.getInt(kOfxInteractPropViewportSize, 0);
  //viewportHeight = args.getInt(kOfxInteractPropViewportSize, 1);
  pixelScaleX = args.getDouble(kOfxInteractPropPixelScale, 0);
  pixelScaleY = args.getDouble(kOfxInteractPropPixelScale, 1);
  bgColour.r = args.getDouble(kOfxInteractPropBackgroundColour, 0);
  bgColour.g = args.getDouble(kOfxInteractPropBackgroundColour, 1);
  bgColour.b = args.getDouble(kOfxInteractPropBackgroundColour, 2);
  bgColour.a = 1.0;
}

// ---

Interact::PenArgs::PenArgs(ImageEffectHost *host, PropertySet &args)
  : Interact::CommonArgs(host, args) {
  x = args.getDouble(kOfxInteractPropPenPosition, 0);
  y = args.getDouble(kOfxInteractPropPenPosition, 1);
  pressure = args.getDouble(kOfxInteractPropPenPressure, 0);
#ifdef OFX_API_1_2
  if (host->checkAPIVersion(1, 2)) {
    viewportX = args.getInt(kOfxInteractPropPenViewportPosition, 0);
    viewportY = args.getInt(kOfxInteractPropPenViewportPosition, 1);
  } else {
    viewportX = -1;
    viewportY = -1;
  }
#endif
}

// ---

Interact::KeyArgs::KeyArgs(ImageEffectHost *host, PropertySet &args)
  : Interact::BaseArgs(host, args) {
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
    throw BadHandleError("ofx::Interact::Interact: invalid host");
  }
  if (!h->interactSuite()) {
    throw MissingHostFeatureError("Interact suite");
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

ImageEffect* Interact::effectInstance() {
  OfxImageEffectHandle hdl = (OfxImageEffectHandle) mProps.getPointer(kOfxPropEffectInstance, 0);
  return ImageEffect::GetEffect(hdl);
}

void* Interact::instanceData() {
  return mProps.getPointer(kOfxPropInstanceData, 0);
}

void Interact::instanceData(void *d) {
  mProps.setPointer(kOfxPropInstanceData, 0, d);
}

void Interact::pixelScale(double *sx, double *sy) {
  *sx = mProps.getDouble(kOfxInteractPropPixelScale, 0);
  *sy = mProps.getDouble(kOfxInteractPropPixelScale, 1);
}

RGBAColour<double> Interact::backgroundColour() {
  RGBAColour<double> colour;
  colour.r = mProps.getDouble(kOfxInteractPropBackgroundColour, 0);
  colour.g = mProps.getDouble(kOfxInteractPropBackgroundColour, 1);
  colour.b = mProps.getDouble(kOfxInteractPropBackgroundColour, 2);
  colour.a = 1.0;
  return colour;
}

void Interact::viewportSize(int *w, int *h) {
  *w = mProps.getInt(kOfxInteractPropViewportSize, 0);
  *h = mProps.getInt(kOfxInteractPropViewportSize, 1);
}

bool Interact::hasAlpha() {
  return (mProps.getInt(kOfxInteractPropHasAlpha, 0) == 1);
}

int Interact::bitDepth() {
  return mProps.getInt(kOfxInteractPropBitDepth, 0);
}

int Interact::slaveToParamCount() {
  return mProps.size(kOfxInteractPropSlaveToParam);
}

std::string Interact::slaveToParam(int i) {
  return mProps.getString(kOfxInteractPropSlaveToParam, i);
}

void Interact::slaveToParam(int i, const std::string &pn) {
  mProps.setString(kOfxInteractPropSlaveToParam, i, pn);
}

#ifdef OFX_API_1_2
RGBAColour<double> Interact::suggestedColour() {
  RGBAColour<double> sc;
  sc.a = 1.0;
  sc.r = mProps.getDouble(kOfxInteractPropSuggestedColour, 0);
  sc.g = mProps.getDouble(kOfxInteractPropSuggestedColour, 1);
  sc.b = mProps.getDouble(kOfxInteractPropSuggestedColour, 2);
  return sc;
}
#endif

OfxStatus Interact::draw(Interact::DrawArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus Interact::penMotion(Interact::PenArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus Interact::penDown(Interact::PenArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus Interact::penUp(Interact::PenArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus Interact::keyDown(Interact::KeyArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus Interact::keyUp(Interact::KeyArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus Interact::keyRepeat(Interact::KeyArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus Interact::gainFocus(Interact::FocusArgs &) {
  return kOfxStatReplyDefault;
}

OfxStatus Interact::loseFocus(Interact::FocusArgs &) {
  return kOfxStatReplyDefault;
}

}
