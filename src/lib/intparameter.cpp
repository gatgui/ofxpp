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

#include <ofx/intparameter.h>
#include <ofx/host.h>

namespace ofx {

IntParameterDescriptor::IntParameterDescriptor()
  : ValueParameterDescriptor() {
}

IntParameterDescriptor::IntParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ValueParameterDescriptor(h, hdl) {
}

IntParameterDescriptor::IntParameterDescriptor(const IntParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

IntParameterDescriptor::~IntParameterDescriptor() {
}

IntParameterDescriptor& IntParameterDescriptor::operator=(const IntParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

int IntParameterDescriptor::defaultValue() {
  return getInt(kOfxParamPropDefault, 0);
}

void IntParameterDescriptor::defaultValue(int v0) {
  setInt(kOfxParamPropDefault, 0, v0);
}

int IntParameterDescriptor::min() {
  return getInt(kOfxParamPropMin, 0);
}

void IntParameterDescriptor::min(int v) {
  setInt(kOfxParamPropMin, 0, v);
}

int IntParameterDescriptor::max() {
  return getInt(kOfxParamPropMax, 0);
}

void IntParameterDescriptor::max(int v) {
  setInt(kOfxParamPropMax, 0, v);
}

int IntParameterDescriptor::displayMin() {
  return getInt(kOfxParamPropDisplayMin, 0);
}

void IntParameterDescriptor::displayMin(int v) {
  setInt(kOfxParamPropDisplayMin, 0, v);
}

int IntParameterDescriptor::displayMax() {
  return getInt(kOfxParamPropDisplayMax, 0);
}

void IntParameterDescriptor::displayMax(int v) {
  setInt(kOfxParamPropDisplayMax, 0, v);
}

// ---

IntParameter::IntParameter()
  : ValueParameter() {
}

IntParameter::IntParameter(Host *h, OfxParamHandle hdl)
  : ValueParameter(h, hdl) {
}

IntParameter::IntParameter(const IntParameter &rhs)
  : ValueParameter(rhs) {
}

IntParameter::~IntParameter() {
}

IntParameter& IntParameter::operator=(const IntParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

int IntParameter::defaultValue() {
  return mProps.getInt(kOfxParamPropDefault, 0);
}

int IntParameter::min() {
  return mProps.getInt(kOfxParamPropMin, 0);
}

void IntParameter::min(int v) {
  mProps.setInt(kOfxParamPropMin, 0, v);
}

int IntParameter::max() {
  return mProps.getInt(kOfxParamPropMax, 0);
}

void IntParameter::max(int v) {
  mProps.setInt(kOfxParamPropMax, 0, v);
}

int IntParameter::displayMin() {
  return mProps.getInt(kOfxParamPropDisplayMin, 0);
}

void IntParameter::displayMin(int v) {
  mProps.setInt(kOfxParamPropDisplayMin, 0, v);
}

int IntParameter::displayMax() {
  return mProps.getInt(kOfxParamPropDisplayMax, 0);
}

void IntParameter::displayMax(int v) {
  mProps.setInt(kOfxParamPropDisplayMax, 0, v);
}

int IntParameter::getValue() throw(Exception) {
  int val;
  OfxStatus stat = mSuite->paramGetValue(mHandle, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::IntParameter::getValue");
  }
  return val;
}

int IntParameter::getValueAtTime(Time t) throw(Exception) {
  int val;
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::IntParameter::getValueAtTime");
  }
  return val;
}

int IntParameter::getDerivative(Time t) throw(Exception) {
  int val;
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::IntParameter::getDerivative");
  }
  return val;
}

int IntParameter::getIntegral(Time t0, Time t1) throw(Exception) {
  int val;
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::IntParameter::getIntegral");
  }
  return val;
}

void IntParameter::setValue(int v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::IntParameter::setValue");
  }
}

void IntParameter::setValueAtTime(Time t, int v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::IntParameter::setValueAtTime");
  }
}

}

