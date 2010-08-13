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

#include <ofx/clip.h>
#include <ofx/host.h>
#include <cmath>

namespace ofx {

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

}

