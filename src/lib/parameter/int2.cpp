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

#include <ofx/parameter/int2.h>
#include <ofx/host.h>

namespace ofx {

Int2ParameterDescriptor::Int2ParameterDescriptor()
  : ValueParameterDescriptor() {
}

Int2ParameterDescriptor::Int2ParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ValueParameterDescriptor(h, hdl) {
}

Int2ParameterDescriptor::Int2ParameterDescriptor(const Int2ParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

Int2ParameterDescriptor::~Int2ParameterDescriptor() {
}

Int2ParameterDescriptor& Int2ParameterDescriptor::operator=(const Int2ParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

void Int2ParameterDescriptor::getDefault(int &v0, int &v1) {
  v0 = getInt(kOfxParamPropDefault, 0);
  v1 = getInt(kOfxParamPropDefault, 1);
}

void Int2ParameterDescriptor::setDefault(int v0, int v1) {
  setInt(kOfxParamPropDefault, 0, v0);
  setInt(kOfxParamPropDefault, 1, v1);
}

void Int2ParameterDescriptor::getMin(int &v0, int &v1) {
  v0 = getInt(kOfxParamPropMin, 0);
  v1 = getInt(kOfxParamPropMin, 1);
}

void Int2ParameterDescriptor::setMin(int v0, int v1) {
  setInt(kOfxParamPropMin, 0, v0);
  setInt(kOfxParamPropMin, 1, v1);
}

void Int2ParameterDescriptor::getMax(int &v0, int &v1) {
  v0 = getInt(kOfxParamPropMax, 0);
  v1 = getInt(kOfxParamPropMax, 1);
}

void Int2ParameterDescriptor::setMax(int v0, int v1) {
  setInt(kOfxParamPropMax, 0, v0);
  setInt(kOfxParamPropMax, 1, v1);
}

void Int2ParameterDescriptor::getDisplayMin(int &v0, int &v1) {
  v0 = getInt(kOfxParamPropDisplayMin, 0);
  v1 = getInt(kOfxParamPropDisplayMin, 1);
}

void Int2ParameterDescriptor::setDisplayMin(int v0, int v1) {
  setInt(kOfxParamPropDisplayMin, 0, v0);
  setInt(kOfxParamPropDisplayMin, 1, v1);
}

void Int2ParameterDescriptor::getDisplayMax(int &v0, int &v1) {
  v0 = getInt(kOfxParamPropDisplayMax, 0);
  v1 = getInt(kOfxParamPropDisplayMax, 1);
}

void Int2ParameterDescriptor::setDisplayMax(int v0, int v1) {
  setInt(kOfxParamPropDisplayMax, 0, v0);
  setInt(kOfxParamPropDisplayMax, 1, v1);
}

void Int2ParameterDescriptor::setDimensionLabel(int i, const std::string &l) {
  setString(kOfxParamPropDimensionLabel, i, l);
}

std::string Int2ParameterDescriptor::dimensionLabel(int i) {
  return getString(kOfxParamPropDimensionLabel, i);
}

// ---

Int2Parameter::Int2Parameter()
  : ValueParameter() {
}

Int2Parameter::Int2Parameter(Host *h, OfxParamHandle hdl)
  : ValueParameter(h, hdl) {
}

Int2Parameter::Int2Parameter(const Int2Parameter &rhs)
  : ValueParameter(rhs) {
}

Int2Parameter::~Int2Parameter() {
}

Int2Parameter& Int2Parameter::operator=(const Int2Parameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

void Int2Parameter::getDefault(int &v0, int &v1) {
  v0 = mProps.getInt(kOfxParamPropDefault, 0);
  v1 = mProps.getInt(kOfxParamPropDefault, 1);
}

void Int2Parameter::getMin(int &v0, int &v1) {
  v0 = mProps.getInt(kOfxParamPropMin, 0);
  v1 = mProps.getInt(kOfxParamPropMin, 1);
}

void Int2Parameter::setMin(int v0, int v1) {
  mProps.setInt(kOfxParamPropMin, 0, v0);
  mProps.setInt(kOfxParamPropMin, 1, v1);
}

void Int2Parameter::getMax(int &v0, int &v1) {
  v0 = mProps.getInt(kOfxParamPropMax, 0);
  v1 = mProps.getInt(kOfxParamPropMax, 1);
}

void Int2Parameter::setMax(int v0, int v1) {
  mProps.setInt(kOfxParamPropMax, 0, v0);
  mProps.setInt(kOfxParamPropMax, 1, v1);
}

void Int2Parameter::getDisplayMin(int &v0, int &v1) {
  v0 = mProps.getInt(kOfxParamPropDisplayMin, 0);
  v1 = mProps.getInt(kOfxParamPropDisplayMin, 1);
}

void Int2Parameter::setDisplayMin(int v0, int v1) {
  mProps.setInt(kOfxParamPropDisplayMin, 0, v0);
  mProps.setInt(kOfxParamPropDisplayMin, 1, v1);
}

void Int2Parameter::getDisplayMax(int &v0, int &v1) {
  v0 = mProps.getInt(kOfxParamPropDisplayMax, 0);
  v1 = mProps.getInt(kOfxParamPropDisplayMax, 1);
}

void Int2Parameter::setDisplayMax(int v0, int v1) {
  mProps.setInt(kOfxParamPropDisplayMax, 0, v0);
  mProps.setInt(kOfxParamPropDisplayMax, 1, v1);
}

std::string Int2Parameter::dimensionLabel(int i) {
  return mProps.getString(kOfxParamPropDimensionLabel, i);
}

void Int2Parameter::getValue(int &v0, int &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValue(mHandle, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int2Parameter::getValue");
  }
}

void Int2Parameter::getValueAtTime(Time t, int &v0, int &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int2Parameter::getValueAtTime");
  }
}

void Int2Parameter::getDerivative(Time t, int &v0, int &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int2Parameter::getDerivative");
  }
}

void Int2Parameter::getIntegral(Time t0, Time t1, int &v0, int &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int2Parameter::getIntegral");
  }
}

void Int2Parameter::setValue(int v0, int v1) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v0, v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int2Parameter::setValue");
  }
}

void Int2Parameter::setValueAtTime(Time t, int v0, int v1) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v0, v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int2Parameter::setValueAtTime");
  }
}

}

