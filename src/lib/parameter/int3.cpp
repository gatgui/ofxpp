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

#include <ofx/parameter/int3.h>
#include <ofx/host.h>

namespace ofx {

Int3ParameterDescriptor::Int3ParameterDescriptor()
  : ValueParameterDescriptor() {
}

Int3ParameterDescriptor::Int3ParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ValueParameterDescriptor(h, hdl) {
}

Int3ParameterDescriptor::Int3ParameterDescriptor(const Int3ParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

Int3ParameterDescriptor::~Int3ParameterDescriptor() {
}

Int3ParameterDescriptor& Int3ParameterDescriptor::operator=(const Int3ParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

void Int3ParameterDescriptor::getDefault(int &v0, int &v1, int &v2) {
  v0 = getInt(kOfxParamPropDefault, 0);
  v1 = getInt(kOfxParamPropDefault, 1);
  v2 = getInt(kOfxParamPropDefault, 2);
}

void Int3ParameterDescriptor::setDefault(int v0, int v1, int v2) {
  setInt(kOfxParamPropDefault, 0, v0);
  setInt(kOfxParamPropDefault, 1, v1);
  setInt(kOfxParamPropDefault, 2, v2);
}

void Int3ParameterDescriptor::getMin(int &v0, int &v1, int &v2) {
  v0 = getInt(kOfxParamPropMin, 0);
  v1 = getInt(kOfxParamPropMin, 1);
  v2 = getInt(kOfxParamPropMin, 2);
}

void Int3ParameterDescriptor::setMin(int v0, int v1, int v2) {
  setInt(kOfxParamPropMin, 0, v0);
  setInt(kOfxParamPropMin, 1, v1);
  setInt(kOfxParamPropMin, 2, v2);
}

void Int3ParameterDescriptor::getMax(int &v0, int &v1, int &v2) {
  v0 = getInt(kOfxParamPropMax, 0);
  v1 = getInt(kOfxParamPropMax, 1);
  v2 = getInt(kOfxParamPropMax, 2);
}

void Int3ParameterDescriptor::setMax(int v0, int v1, int v2) {
  setInt(kOfxParamPropMax, 0, v0);
  setInt(kOfxParamPropMax, 1, v1);
  setInt(kOfxParamPropMax, 2, v2);
}

void Int3ParameterDescriptor::getDisplayMin(int &v0, int &v1, int &v2) {
  v0 = getInt(kOfxParamPropDisplayMin, 0);
  v1 = getInt(kOfxParamPropDisplayMin, 1);
  v2 = getInt(kOfxParamPropDisplayMin, 2);
}

void Int3ParameterDescriptor::setDisplayMin(int v0, int v1, int v2) {
  setInt(kOfxParamPropDisplayMin, 0, v0);
  setInt(kOfxParamPropDisplayMin, 1, v1);
  setInt(kOfxParamPropDisplayMin, 2, v2);
}

void Int3ParameterDescriptor::getDisplayMax(int &v0, int &v1, int &v2) {
  v0 = getInt(kOfxParamPropDisplayMax, 0);
  v1 = getInt(kOfxParamPropDisplayMax, 1);
  v2 = getInt(kOfxParamPropDisplayMax, 2);
}

void Int3ParameterDescriptor::setDisplayMax(int v0, int v1, int v2) {
  setInt(kOfxParamPropDisplayMax, 0, v0);
  setInt(kOfxParamPropDisplayMax, 1, v1);
  setInt(kOfxParamPropDisplayMax, 2, v2);
}

void Int3ParameterDescriptor::setDimensionLabel(int i, const std::string &l) {
  setString(kOfxParamPropDimensionLabel, i, l);
}

std::string Int3ParameterDescriptor::getDimensionLabel(int i) {
  return getString(kOfxParamPropDimensionLabel, i);
}

// ---

Int3Parameter::Int3Parameter()
  : ValueParameter() {
}

Int3Parameter::Int3Parameter(Host *h, OfxParamHandle hdl)
  : ValueParameter(h, hdl) {
}

Int3Parameter::Int3Parameter(const Int3Parameter &rhs)
  : ValueParameter(rhs) {
}

Int3Parameter::~Int3Parameter() {
}

Int3Parameter& Int3Parameter::operator=(const Int3Parameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

void Int3Parameter::getDefault(int &v0, int &v1, int &v2) {
  v0 = mProps.getInt(kOfxParamPropDefault, 0);
  v1 = mProps.getInt(kOfxParamPropDefault, 1);
  v2 = mProps.getInt(kOfxParamPropDefault, 2);
}

void Int3Parameter::getMin(int &v0, int &v1, int &v2) {
  v0 = mProps.getInt(kOfxParamPropMin, 0);
  v1 = mProps.getInt(kOfxParamPropMin, 1);
  v2 = mProps.getInt(kOfxParamPropMin, 2);
}

void Int3Parameter::setMin(int v0, int v1, int v2) {
  mProps.setInt(kOfxParamPropMin, 0, v0);
  mProps.setInt(kOfxParamPropMin, 1, v1);
  mProps.setInt(kOfxParamPropMin, 2, v2);
}

void Int3Parameter::getMax(int &v0, int &v1, int &v2) {
  v0 = mProps.getInt(kOfxParamPropMax, 0);
  v1 = mProps.getInt(kOfxParamPropMax, 1);
  v2 = mProps.getInt(kOfxParamPropMax, 2);
}

void Int3Parameter::setMax(int v0, int v1, int v2) {
  mProps.setInt(kOfxParamPropMax, 0, v0);
  mProps.setInt(kOfxParamPropMax, 1, v1);
  mProps.setInt(kOfxParamPropMax, 2, v2);
}

void Int3Parameter::getDisplayMin(int &v0, int &v1, int &v2) {
  v0 = mProps.getInt(kOfxParamPropDisplayMin, 0);
  v1 = mProps.getInt(kOfxParamPropDisplayMin, 1);
  v2 = mProps.getInt(kOfxParamPropDisplayMin, 2);
}

void Int3Parameter::setDisplayMin(int v0, int v1, int v2) {
  mProps.setInt(kOfxParamPropDisplayMin, 0, v0);
  mProps.setInt(kOfxParamPropDisplayMin, 1, v1);
  mProps.setInt(kOfxParamPropDisplayMin, 2, v2);
}

void Int3Parameter::getDisplayMax(int &v0, int &v1, int &v2) {
  v0 = mProps.getInt(kOfxParamPropDisplayMax, 0);
  v1 = mProps.getInt(kOfxParamPropDisplayMax, 1);
  v2 = mProps.getInt(kOfxParamPropDisplayMax, 2);
}

void Int3Parameter::setDisplayMax(int v0, int v1, int v2) {
  mProps.setInt(kOfxParamPropDisplayMax, 0, v0);
  mProps.setInt(kOfxParamPropDisplayMax, 1, v1);
  mProps.setInt(kOfxParamPropDisplayMax, 2, v2);
}

std::string Int3Parameter::getDimensionLabel(int i) {
  return mProps.getString(kOfxParamPropDimensionLabel, i);
}

void Int3Parameter::getValue(int &v0, int &v1, int &v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValue(mHandle, &v0, &v1, &v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int3Parameter::getValue");
  }
}

void Int3Parameter::getValueAtTime(Time t, int &v0, int &v1, int &v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &v0, &v1, &v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int3Parameter::getValueAtTime");
  }
}

void Int3Parameter::getDerivative(Time t, int &v0, int &v1, int &v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, &v0, &v1, &v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int3Parameter::getDerivative");
  }
}

void Int3Parameter::getIntegral(Time t0, Time t1, int &v0, int &v1, int &v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, &v0, &v1, &v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int3Parameter::getIntegral");
  }
}

void Int3Parameter::setValue(int v0, int v1, int v2) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v0, v1, v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int3Parameter::setValue");
  }
}

void Int3Parameter::setValueAtTime(Time t, int v0, int v1, int v2) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v0, v1, v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int3Parameter::setValueAtTime");
  }
}

}

