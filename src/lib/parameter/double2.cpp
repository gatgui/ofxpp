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

#include <ofx/parameter/double2.h>
#include <ofx/host.h>

namespace ofx {

Double2ParameterDescriptor::Double2ParameterDescriptor()
  : ValueParameterDescriptor() {
}

Double2ParameterDescriptor::Double2ParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ValueParameterDescriptor(h, hdl) {
}

Double2ParameterDescriptor::Double2ParameterDescriptor(const Double2ParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

Double2ParameterDescriptor::~Double2ParameterDescriptor() {
}

Double2ParameterDescriptor& Double2ParameterDescriptor::operator=(const Double2ParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

void Double2ParameterDescriptor::getDefault(double &v0, double &v1) {
  v0 = getDouble(kOfxParamPropDefault, 0);
  v1 = getDouble(kOfxParamPropDefault, 1);
}

void Double2ParameterDescriptor::setDefault(double v0, double v1) {
  setDouble(kOfxParamPropDefault, 0, v0);
  setDouble(kOfxParamPropDefault, 1, v1);
}

void Double2ParameterDescriptor::getMin(double &v0, double &v1) {
  v0 = getDouble(kOfxParamPropMin, 0);
  v1 = getDouble(kOfxParamPropMin, 1);
}

void Double2ParameterDescriptor::setMin(double min0, double min1) {
  setDouble(kOfxParamPropMin, 0, min0);
  setDouble(kOfxParamPropMin, 1, min1);
}

void Double2ParameterDescriptor::getMax(double &v0, double &v1) {
  v0 = getDouble(kOfxParamPropMax, 0);
  v1 = getDouble(kOfxParamPropMax, 1);
}

void Double2ParameterDescriptor::setMax(double max0, double max1) {
  setDouble(kOfxParamPropMax, 0, max0);
  setDouble(kOfxParamPropMax, 1, max1);
}

void Double2ParameterDescriptor::getDisplayMin(double &v0, double &v1) {
  v0 = getDouble(kOfxParamPropDisplayMin, 0);
  v1 = getDouble(kOfxParamPropDisplayMin, 1);
}

void Double2ParameterDescriptor::setDisplayMin(double min0, double min1) {
  setDouble(kOfxParamPropDisplayMin, 0, min0);
  setDouble(kOfxParamPropDisplayMin, 1, min1);
}

void Double2ParameterDescriptor::getDisplayMax(double &v0, double &v1) {
  v0 = getDouble(kOfxParamPropDisplayMax, 0);
  v1 = getDouble(kOfxParamPropDisplayMax, 1);
}

void Double2ParameterDescriptor::setDisplayMax(double max0, double max1) {
  setDouble(kOfxParamPropDisplayMax, 0, max0);
  setDouble(kOfxParamPropDisplayMax, 1, max1);
}

double Double2ParameterDescriptor::increment() {
  return getDouble(kOfxParamPropIncrement, 0);
}

void Double2ParameterDescriptor::setIncrement(double i) {
  setDouble(kOfxParamPropIncrement, 0, i);
}

int Double2ParameterDescriptor::digits() {
  return getInt(kOfxParamPropDigits, 0);
}

void Double2ParameterDescriptor::setDigits(int d) {
  setInt(kOfxParamPropDigits, 0, d);
}

DoubleParamType Double2ParameterDescriptor::doubleType() {
  return StringToDoubleParamType(getString(kOfxParamPropDoubleType, 0));
}

void Double2ParameterDescriptor::setDoubleType(DoubleParamType t) {
  setString(kOfxParamPropDoubleType, 0, DoubleParamTypeToString(t));
}

void Double2ParameterDescriptor::setDimensionLabel(int i, const std::string &name) {
  setString(kOfxParamPropDimensionLabel, i, name);
}

std::string Double2ParameterDescriptor::dimensionLabel(int i) {
  return getString(kOfxParamPropDimensionLabel, i);
}

#ifdef OFX_API_1_2

Coordinates Double2ParameterDescriptor::defaultCoordinateSystem() {
  return StringToCoordinates(getString(kOfxParamPropDefaultCoordinateSystem, 0));
}

void Double2ParameterDescriptor::setDefaultCoordinateSystem(Coordinates cs) {
  setString(kOfxParamPropDefaultCoordinateSystem, 0, CoordinatesToString(cs));
}

#endif

// ---

Double2Parameter::Double2Parameter()
  : ValueParameter() {
}

Double2Parameter::Double2Parameter(Host *h, OfxParamHandle hdl)
  : ValueParameter(h, hdl) {
}

Double2Parameter::Double2Parameter(const Double2Parameter &rhs)
  : ValueParameter(rhs) {
}

Double2Parameter::~Double2Parameter() {
}

Double2Parameter& Double2Parameter::operator=(const Double2Parameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

void Double2Parameter::getDefault(double &v0, double &v1) {
  v0 = mProps.getDouble(kOfxParamPropDefault, 0);
  v1 = mProps.getDouble(kOfxParamPropDefault, 1);
}

void Double2Parameter::getMin(double &v0, double &v1) {
  v0 = mProps.getDouble(kOfxParamPropMin, 0);
  v1 = mProps.getDouble(kOfxParamPropMin, 1);
}

void Double2Parameter::setMin(double min0, double min1) {
  mProps.setDouble(kOfxParamPropMin, 0, min0);
  mProps.setDouble(kOfxParamPropMin, 1, min1);
}

void Double2Parameter::getMax(double &v0, double &v1) {
  v0 = mProps.getDouble(kOfxParamPropMax, 0);
  v1 = mProps.getDouble(kOfxParamPropMax, 1);
}

void Double2Parameter::setMax(double max0, double max1) {
  mProps.setDouble(kOfxParamPropMax, 0, max0);
  mProps.setDouble(kOfxParamPropMax, 1, max1);
}

void Double2Parameter::getDisplayMin(double &v0, double &v1) {
  v0 = mProps.getDouble(kOfxParamPropDisplayMin, 0);
  v1 = mProps.getDouble(kOfxParamPropDisplayMin, 1);
}

void Double2Parameter::setDisplayMin(double min0, double min1) {
  mProps.setDouble(kOfxParamPropDisplayMin, 0, min0);
  mProps.setDouble(kOfxParamPropDisplayMin, 1, min1);
}

void Double2Parameter::getDisplayMax(double &v0, double &v1) {
  v0 = mProps.getDouble(kOfxParamPropDisplayMax, 0);
  v1 = mProps.getDouble(kOfxParamPropDisplayMax, 1);
}

void Double2Parameter::setDisplayMax(double max0, double max1) {
  mProps.setDouble(kOfxParamPropDisplayMax, 0, max0);
  mProps.setDouble(kOfxParamPropDisplayMax, 1, max1);
}

double Double2Parameter::increment() {
  return mProps.getDouble(kOfxParamPropIncrement, 0);
}

void Double2Parameter::setIncrement(double i) {
  mProps.setDouble(kOfxParamPropIncrement, 0, i);
}

int Double2Parameter::digits() {
  return mProps.getInt(kOfxParamPropDigits, 0);
}

void Double2Parameter::setDigits(int d) {
  mProps.setInt(kOfxParamPropDigits, 0, d);
}

DoubleParamType Double2Parameter::doubleType() {
  return StringToDoubleParamType(mProps.getString(kOfxParamPropDoubleType, 0));
}

std::string Double2Parameter::dimensionLabel(int i) {
  return mProps.getString(kOfxParamPropDimensionLabel, i);
}

#ifdef OFX_API_1_2

Coordinates Double2Parameter::defaultCoordinateSystem() {
  return StringToCoordinates(mProps.getString(kOfxParamPropDefaultCoordinateSystem, 0));
}

#endif

void Double2Parameter::getValue(double &v0, double &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValue(mHandle, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double2Parameter::getValue");
  }
}

void Double2Parameter::getValueAtTime(Time t, double &v0, double &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double2Parameter::getValueAtTime");
  }
}

void Double2Parameter::getDerivative(Time t, double &v0, double &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double2Parameter::getDerivative");
  }
}

void Double2Parameter::getIntegral(Time t0, Time t1, double &v0, double &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double2Parameter::getIntegral");
  }
}

void Double2Parameter::setValue(double v0, double v1) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v0, v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double2Parameter::setValue");
  }
}

void Double2Parameter::setValueAtTime(Time t, double v0, double v1) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v0, v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double2Parameter::setValueAtTime");
  }
}

}

