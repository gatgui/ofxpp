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

#include <ofx/double3parameter.h>
#include <ofx/host.h>

namespace ofx {

Double3ParameterDescriptor::Double3ParameterDescriptor()
  : ValueParameterDescriptor() {
}

Double3ParameterDescriptor::Double3ParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ValueParameterDescriptor(h, hdl) {
}

Double3ParameterDescriptor::Double3ParameterDescriptor(const Double3ParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

Double3ParameterDescriptor::~Double3ParameterDescriptor() {
}

Double3ParameterDescriptor& Double3ParameterDescriptor::operator=(const Double3ParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

void Double3ParameterDescriptor::defaultValue(double *v0, double *v1, double *v2) {
  *v0 = getDouble(kOfxParamPropDefault, 0);
  *v1 = getDouble(kOfxParamPropDefault, 1);
  *v2 = getDouble(kOfxParamPropDefault, 2);
}

void Double3ParameterDescriptor::defaultValue(double v0, double v1, double v2) {
  setDouble(kOfxParamPropDefault, 0, v0);
  setDouble(kOfxParamPropDefault, 1, v1);
  setDouble(kOfxParamPropDefault, 2, v2);
}

void Double3ParameterDescriptor::min(double *v0, double *v1, double *v2) {
  *v0 = getDouble(kOfxParamPropMin, 0);
  *v1 = getDouble(kOfxParamPropMin, 1);
  *v2 = getDouble(kOfxParamPropMin, 2);
}

void Double3ParameterDescriptor::min(double min0, double min1, double min2) {
  setDouble(kOfxParamPropMin, 0, min0);
  setDouble(kOfxParamPropMin, 1, min1);
  setDouble(kOfxParamPropMin, 2, min2);
}

void Double3ParameterDescriptor::max(double *v0, double *v1, double *v2) {
  *v0 = getDouble(kOfxParamPropMax, 0);
  *v1 = getDouble(kOfxParamPropMax, 1);
  *v2 = getDouble(kOfxParamPropMax, 2);
}

void Double3ParameterDescriptor::max(double max0, double max1, double max2) {
  setDouble(kOfxParamPropMax, 0, max0);
  setDouble(kOfxParamPropMax, 1, max1);
  setDouble(kOfxParamPropMax, 2, max2);
}

void Double3ParameterDescriptor::displayMin(double *v0, double *v1, double *v2) {
  *v0 = getDouble(kOfxParamPropDisplayMin, 0);
  *v1 = getDouble(kOfxParamPropDisplayMin, 1);
  *v2 = getDouble(kOfxParamPropDisplayMin, 2);
}

void Double3ParameterDescriptor::displayMin(double min0, double min1, double min2) {
  setDouble(kOfxParamPropDisplayMin, 0, min0);
  setDouble(kOfxParamPropDisplayMin, 1, min1);
  setDouble(kOfxParamPropDisplayMin, 2, min2);
}

void Double3ParameterDescriptor::displayMax(double *v0, double *v1, double *v2) {
  *v0 = getDouble(kOfxParamPropDisplayMax, 0);
  *v1 = getDouble(kOfxParamPropDisplayMax, 1);
  *v2 = getDouble(kOfxParamPropDisplayMax, 2);
}

void Double3ParameterDescriptor::displayMax(double max0, double max1, double max2) {
  setDouble(kOfxParamPropDisplayMax, 0, max0);
  setDouble(kOfxParamPropDisplayMax, 1, max1);
  setDouble(kOfxParamPropDisplayMax, 2, max2);
}

double Double3ParameterDescriptor::increment() {
  return getDouble(kOfxParamPropIncrement, 0);
}

void Double3ParameterDescriptor::increment(double i) {
  setDouble(kOfxParamPropIncrement, 0, i);
}

int Double3ParameterDescriptor::digits() {
  return getInt(kOfxParamPropDigits, 0);
}

void Double3ParameterDescriptor::digits(int d) {
  setInt(kOfxParamPropDigits, 0, d);
}

DoubleParamType Double3ParameterDescriptor::doubleType() {
  return StringToDoubleParamType(getString(kOfxParamPropDoubleType, 0));
}

void Double3ParameterDescriptor::doubleType(DoubleParamType t) {
  setString(kOfxParamPropDoubleType, 0, DoubleParamTypeToString(t));
}

void Double3ParameterDescriptor::dimensionLabel(int i, const std::string &name) {
  setString(kOfxParamPropDimensionLabel, i, name);
}

std::string Double3ParameterDescriptor::dimensionLabel(int i) {
  return getString(kOfxParamPropDimensionLabel, i);
}

/*
#ifdef OFX_API_1_2

Coordinates Double3ParameterDescriptor::defaultCoordinateSystem() {
  return StringToCoordinates(getString(kOfxParamPropDefaultCoordinateSystem, 0));
}

void Double3ParameterDescriptor::defaultCoordinateSystem(Coordinates cs) {
  setString(kOfxParamPropDefaultCoordinateSystem, 0, CoordinatesToString(cs));
}

#endif
*/

// ---

Double3Parameter::Double3Parameter()
  : ValueParameter() {
}

Double3Parameter::Double3Parameter(Host *h, OfxParamHandle hdl)
  : ValueParameter(h, hdl) {
}

Double3Parameter::Double3Parameter(const Double3Parameter &rhs)
  : ValueParameter(rhs) {
}

Double3Parameter::~Double3Parameter() {
}

Double3Parameter& Double3Parameter::operator=(const Double3Parameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

void Double3Parameter::defaultValue(double *v0, double *v1, double *v2) {
  *v0 = mProps.getDouble(kOfxParamPropDefault, 0);
  *v1 = mProps.getDouble(kOfxParamPropDefault, 1);
  *v2 = mProps.getDouble(kOfxParamPropDefault, 2);
}

void Double3Parameter::min(double *v0, double *v1, double *v2) {
  *v0 = mProps.getDouble(kOfxParamPropMin, 0);
  *v1 = mProps.getDouble(kOfxParamPropMin, 1);
  *v2 = mProps.getDouble(kOfxParamPropMin, 2);
}

void Double3Parameter::min(double min0, double min1, double min2) {
  mProps.setDouble(kOfxParamPropMin, 0, min0);
  mProps.setDouble(kOfxParamPropMin, 1, min1);
  mProps.setDouble(kOfxParamPropMin, 2, min2);
}

void Double3Parameter::max(double *v0, double *v1, double *v2) {
  *v0 = mProps.getDouble(kOfxParamPropMax, 0);
  *v1 = mProps.getDouble(kOfxParamPropMax, 1);
  *v2 = mProps.getDouble(kOfxParamPropMax, 2);
}

void Double3Parameter::max(double max0, double max1, double max2) {
  mProps.setDouble(kOfxParamPropMax, 0, max0);
  mProps.setDouble(kOfxParamPropMax, 1, max1);
  mProps.setDouble(kOfxParamPropMax, 2, max2);
}

void Double3Parameter::displayMin(double *v0, double *v1, double *v2) {
  *v0 = mProps.getDouble(kOfxParamPropDisplayMin, 0);
  *v1 = mProps.getDouble(kOfxParamPropDisplayMin, 1);
  *v2 = mProps.getDouble(kOfxParamPropDisplayMin, 2);
}

void Double3Parameter::displayMin(double min0, double min1, double min2) {
  mProps.setDouble(kOfxParamPropDisplayMin, 0, min0);
  mProps.setDouble(kOfxParamPropDisplayMin, 1, min1);
  mProps.setDouble(kOfxParamPropDisplayMin, 2, min2);
}

void Double3Parameter::displayMax(double *v0, double *v1, double *v2) {
  *v0 = mProps.getDouble(kOfxParamPropDisplayMax, 0);
  *v1 = mProps.getDouble(kOfxParamPropDisplayMax, 1);
  *v2 = mProps.getDouble(kOfxParamPropDisplayMax, 2);
}

void Double3Parameter::displayMax(double max0, double max1, double max2) {
  mProps.setDouble(kOfxParamPropDisplayMax, 0, max0);
  mProps.setDouble(kOfxParamPropDisplayMax, 1, max1);
  mProps.setDouble(kOfxParamPropDisplayMax, 2, max2);
}

double Double3Parameter::increment() {
  return mProps.getDouble(kOfxParamPropIncrement, 0);
}

void Double3Parameter::increment(double i) {
  mProps.setDouble(kOfxParamPropIncrement, 0, i);
}

int Double3Parameter::digits() {
  return mProps.getInt(kOfxParamPropDigits, 0);
}

void Double3Parameter::digits(int d) {
  mProps.setInt(kOfxParamPropDigits, 0, d);
}

DoubleParamType Double3Parameter::doubleType() {
  return StringToDoubleParamType(mProps.getString(kOfxParamPropDoubleType, 0));
}

std::string Double3Parameter::dimensionLabel(int i) {
  return mProps.getString(kOfxParamPropDimensionLabel, i);
}

/*
#ifdef OFX_API_1_2

Coordinates Double3Parameter::defaultCoordinateSystem() {
  return StringToCoordinates(mProps.getString(kOfxParamPropDefaultCoordinateSystem, 0));
}

#endif
*/

void Double3Parameter::getValue(double *v0, double *v1, double *v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValue(mHandle, v0, v1, v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double3Parameter::getValue");
  }
}

void Double3Parameter::getValueAtTime(Time t, double *v0, double *v1, double *v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, v0, v1, v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double3Parameter::getValueAtTime");
  }
}

void Double3Parameter::getDerivative(Time t, double *v0, double *v1, double *v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, v0, v1, v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double3Parameter::getDerivative");
  }
}

void Double3Parameter::getIntegral(Time t0, Time t1, double *v0, double *v1, double *v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, v0, v1, v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double3Parameter::getIntegral");
  }
}

void Double3Parameter::setValue(double v0, double v1, double v2) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v0, v1, v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double3Parameter::setValue");
  }
}

void Double3Parameter::setValueAtTime(Time t, double v0, double v1, double v2) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v0, v1, v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double3Parameter::setValueAtTime");
  }
}

}

