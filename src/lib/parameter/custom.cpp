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

#include <ofx/parameter/custom.h>
#include <ofx/host.h>

namespace ofx {

CustomParameterDescriptor::CustomParameterDescriptor()
  : ValueParameterDescriptor() {
}

CustomParameterDescriptor::CustomParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ValueParameterDescriptor(h, hdl) {
}

CustomParameterDescriptor::CustomParameterDescriptor(const CustomParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

CustomParameterDescriptor::~CustomParameterDescriptor() {
}

CustomParameterDescriptor& CustomParameterDescriptor::operator=(const CustomParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

std::string CustomParameterDescriptor::getDefault() {
  return getString(kOfxParamPropDefault, 0);
}

void CustomParameterDescriptor::setDefault(const std::string &v) {
  setString(kOfxParamPropDefault, 0, v);
}

void CustomParameterDescriptor::setInterpolator(OfxInterpFunc func) {
  setPointer(kOfxParamPropCustomInterpCallbackV1, 0, (void*)func);
}

OfxInterpFunc CustomParameterDescriptor::getInterpolator() {
  return (OfxInterpFunc) getPointer(kOfxParamPropCustomInterpCallbackV1, 0);
}

// ---

CustomParameter::CustomParameter()
  : ValueParameter() {
}

CustomParameter::CustomParameter(Host *h, OfxParamHandle hdl)
  : ValueParameter(h, hdl) {
}

CustomParameter::CustomParameter(const CustomParameter &rhs)
  : ValueParameter(rhs) {
}

CustomParameter::~CustomParameter() {
}

CustomParameter& CustomParameter::operator=(const CustomParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

std::string CustomParameter::getDefault() {
  return mProps.getString(kOfxParamPropDefault, 0);
}

OfxInterpFunc CustomParameter::getInterpolator() {
  return (OfxInterpFunc) mProps.getPointer(kOfxParamPropCustomInterpCallbackV1, 0);
}

std::string CustomParameter::getValue() throw(Exception) {
  char *val = 0;
  // no quite sure about this one
  OfxStatus stat = mSuite->paramGetValue(mHandle, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::CustomParameter::getValue");
  }
  return val;
}

std::string CustomParameter::getValueAtTime(Time t) throw(Exception) {
  char *val = 0;
  // no quite sure about this one
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::CustomParameter::getValueAtTime");
  }
  return val;
}

void CustomParameter::setValue(const std::string &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v.c_str());
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::CustomParameter::setValue");
  }
}

void CustomParameter::setValueAtTime(Time t, const std::string &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v.c_str());
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::CustomParameter::setValueAtTime");
  }
}

}

