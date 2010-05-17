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

#include <ofx/parameter/int.h>
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

int IntParameterDescriptor::getDefault() {
  return getInt(kOfxParamPropDefault, 0);
}

void IntParameterDescriptor::setDefault(int v0) {
  setInt(kOfxParamPropDefault, 0, v0);
}

int IntParameterDescriptor::getMin() {
  return getInt(kOfxParamPropMin, 0);
}

void IntParameterDescriptor::setMin(int v) {
  setInt(kOfxParamPropMin, 0, v);
}

int IntParameterDescriptor::getMax() {
  return getInt(kOfxParamPropMax, 0);
}

void IntParameterDescriptor::setMax(int v) {
  setInt(kOfxParamPropMax, 0, v);
}

int IntParameterDescriptor::getDisplayMin() {
  return getInt(kOfxParamPropDisplayMin, 0);
}

void IntParameterDescriptor::setDisplayMin(int v) {
  setInt(kOfxParamPropDisplayMin, 0, v);
}

int IntParameterDescriptor::getDisplayMax() {
  return getInt(kOfxParamPropDisplayMax, 0);
}

void IntParameterDescriptor::setDisplayMax(int v) {
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

int IntParameter::getDefault() {
  return mProps.getInt(kOfxParamPropDefault, 0);
}

int IntParameter::getMin() {
  return mProps.getInt(kOfxParamPropMin, 0);
}

void IntParameter::setMin(int v) {
  mProps.setInt(kOfxParamPropMin, 0, v);
}

int IntParameter::getMax() {
  return mProps.getInt(kOfxParamPropMax, 0);
}

void IntParameter::setMax(int v) {
  mProps.setInt(kOfxParamPropMax, 0, v);
}

int IntParameter::getDisplayMin() {
  return mProps.getInt(kOfxParamPropDisplayMin, 0);
}

void IntParameter::setDisplayMin(int v) {
  mProps.setInt(kOfxParamPropDisplayMin, 0, v);
}

int IntParameter::getDisplayMax() {
  return mProps.getInt(kOfxParamPropDisplayMax, 0);
}

void IntParameter::setDisplayMax(int v) {
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

