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

#include <ofx/doubleparameter.h>
#include <ofx/host.h>

namespace ofx {

DoubleParameterDescriptor::DoubleParameterDescriptor()
  : ValueParameterDescriptor() {
}

DoubleParameterDescriptor::DoubleParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ValueParameterDescriptor(h, hdl) {
}

DoubleParameterDescriptor::DoubleParameterDescriptor(const DoubleParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

DoubleParameterDescriptor::~DoubleParameterDescriptor() {
}

DoubleParameterDescriptor& DoubleParameterDescriptor::operator=(const DoubleParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

double DoubleParameterDescriptor::getDefault() {
  return getDouble(kOfxParamPropDefault, 0);
}

void DoubleParameterDescriptor::setDefault(double v0) {
  setDouble(kOfxParamPropDefault, 0, v0);
}

double DoubleParameterDescriptor::getMin() {
  return getDouble(kOfxParamPropMin, 0);
}

void DoubleParameterDescriptor::setMin(double min0) {
  setDouble(kOfxParamPropMin, 0, min0);
}

double DoubleParameterDescriptor::getMax() {
  return getDouble(kOfxParamPropMax, 0);
}

void DoubleParameterDescriptor::setMax(double max0) {
  setDouble(kOfxParamPropMax, 0, max0);
}

double DoubleParameterDescriptor::getDisplayMin() {
  return getDouble(kOfxParamPropDisplayMin, 0);
}

void DoubleParameterDescriptor::setDisplayMin(double min0) {
  setDouble(kOfxParamPropDisplayMin, 0, min0);
}

double DoubleParameterDescriptor::getDisplayMax() {
  return getDouble(kOfxParamPropDisplayMax, 0);
}

void DoubleParameterDescriptor::setDisplayMax(double max0) {
  setDouble(kOfxParamPropDisplayMax, 0, max0);
}

double DoubleParameterDescriptor::getIncrement() {
  return getDouble(kOfxParamPropIncrement, 0);
}

void DoubleParameterDescriptor::setIncrement(double i) {
  setDouble(kOfxParamPropIncrement, 0, i);
}

int DoubleParameterDescriptor::getDigits() {
  return getInt(kOfxParamPropDigits, 0);
}

void DoubleParameterDescriptor::setDigits(int d) {
  setInt(kOfxParamPropDigits, 0, d);
}

bool DoubleParameterDescriptor::showTimeMarker() {
  return (getInt(kOfxParamPropShowTimeMarker, 0) == 1);
}

void DoubleParameterDescriptor::setShowTimeMarker(bool yes) {
  setInt(kOfxParamPropShowTimeMarker, 0, (yes ? 1 : 0));
}

DoubleParamType DoubleParameterDescriptor::getDoubleType() {
  return StringToDoubleParamType(getString(kOfxParamPropDoubleType, 0));
}

void DoubleParameterDescriptor::setDoubleType(DoubleParamType t) {
  setString(kOfxParamPropDoubleType, 0, DoubleParamTypeToString(t));
}

#ifdef OFX_API_1_2

Coordinates DoubleParameterDescriptor::getDefaultCoordinateSystem() {
  return StringToCoordinates(getString(kOfxParamPropDefaultCoordinateSystem, 0));
}

void DoubleParameterDescriptor::setDefaultCoordinateSystem(Coordinates cs) {
  setString(kOfxParamPropDefaultCoordinateSystem, 0, CoordinatesToString(cs));
}

#endif

// ---

DoubleParameter::DoubleParameter()
  : ValueParameter() {
}

DoubleParameter::DoubleParameter(Host *h, OfxParamHandle hdl)
  : ValueParameter(h, hdl) {
}

DoubleParameter::DoubleParameter(const DoubleParameter &rhs)
  : ValueParameter(rhs) {
}

DoubleParameter::~DoubleParameter() {
}

DoubleParameter& DoubleParameter::operator=(const DoubleParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

double DoubleParameter::getDefault() {
  return mProps.getDouble(kOfxParamPropDefault, 0);
}

double DoubleParameter::getMin() {
  return mProps.getDouble(kOfxParamPropMin, 0);
}

void DoubleParameter::setMin(double min0) {
  mProps.setDouble(kOfxParamPropMin, 0, min0);
}

double DoubleParameter::getMax() {
  return mProps.getDouble(kOfxParamPropMax, 0);
}

void DoubleParameter::setMax(double max0) {
  mProps.setDouble(kOfxParamPropMax, 0, max0);
}

double DoubleParameter::getDisplayMin() {
  return mProps.getDouble(kOfxParamPropDisplayMin, 0);
}

void DoubleParameter::setDisplayMin(double min0) {
  mProps.setDouble(kOfxParamPropDisplayMin, 0, min0);
}

double DoubleParameter::getDisplayMax() {
  return mProps.getDouble(kOfxParamPropDisplayMax, 0);
}

void DoubleParameter::setDisplayMax(double max0) {
  mProps.setDouble(kOfxParamPropDisplayMax, 0, max0);
}

double DoubleParameter::getIncrement() {
  return mProps.getDouble(kOfxParamPropIncrement, 0);
}

void DoubleParameter::setIncrement(double i) {
  mProps.setDouble(kOfxParamPropIncrement, 0, i);
}

int DoubleParameter::getDigits() {
  return mProps.getInt(kOfxParamPropDigits, 0);
}

void DoubleParameter::setDigits(int d) {
  mProps.setInt(kOfxParamPropDigits, 0, d);
}

bool DoubleParameter::showTimeMarker() {
  return (mProps.getInt(kOfxParamPropShowTimeMarker, 0) == 1);
}

void DoubleParameter::setShowTimeMarker(bool yes) {
  mProps.setInt(kOfxParamPropShowTimeMarker, 0, (yes ? 1 : 0));
}

DoubleParamType DoubleParameter::getDoubleType() {
  return StringToDoubleParamType(mProps.getString(kOfxParamPropDoubleType, 0));
}

#ifdef OFX_API_1_2

Coordinates DoubleParameter::getDefaultCoordinateSystem() {
  return StringToCoordinates(mProps.getString(kOfxParamPropDefaultCoordinateSystem, 0));
}

#endif

double DoubleParameter::getValue() throw(Exception) {
  double val;
  OfxStatus stat = mSuite->paramGetValue(mHandle, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::DoubleParameter::getValue");
  }
  return val;
}

double DoubleParameter::getValueAtTime(Time t) throw(Exception) {
  double val;
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::DoubleParameter::getValueAtTime");
  }
  return val;
}

double DoubleParameter::getDerivative(Time t) throw(Exception) {
  double val;
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::DoubleParameter::getDerivative");
  }
  return val;
}

double DoubleParameter::getIntegral(Time t0, Time t1) throw(Exception) {
  double val;
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::DoubleParameter::getIntegral");
  }
  return val;
}

void DoubleParameter::setValue(double v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::DoubleParameter::setValue");
  }
}

void DoubleParameter::setValueAtTime(Time t, double v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::DoubleParameter::setValueAtTime");
  }
}

}

