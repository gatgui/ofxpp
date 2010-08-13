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

#include <ofx/stringparameter.h>
#include <ofx/host.h>

namespace ofx {

StringParameterDescriptor::StringParameterDescriptor()
  : ValueParameterDescriptor() {
}

StringParameterDescriptor::StringParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ValueParameterDescriptor(h, hdl) {
  
}

StringParameterDescriptor::StringParameterDescriptor(const StringParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
  
}

StringParameterDescriptor::~StringParameterDescriptor() {
}

StringParameterDescriptor& StringParameterDescriptor::operator=(const StringParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

std::string StringParameterDescriptor::getDefault() {
  return getString(kOfxParamPropDefault, 0);
}

void StringParameterDescriptor::setDefault(const std::string &v) {
  setString(kOfxParamPropDefault, 0, v);
}

StringParamMode StringParameterDescriptor::getMode() {
  return StringToStringParamMode(getString(kOfxParamPropStringMode, 0));
}

void StringParameterDescriptor::setMode(StringParamMode m) {
  setString(kOfxParamPropStringMode, 0, StringParamModeToString(m));
}

bool StringParameterDescriptor::requireExistingFilePath() {
  return (getInt(kOfxParamPropStringFilePathExists, 0) == 1);
}

void StringParameterDescriptor::setRequireExistingFilePath(bool yes) {
  setInt(kOfxParamPropStringFilePathExists, 0, (yes ? 1 : 0));
}

// ---

StringParameter::StringParameter()
  : ValueParameter() {
}

StringParameter::StringParameter(Host *h, OfxParamHandle hdl)
  : ValueParameter(h, hdl) {
  
}

StringParameter::StringParameter(const StringParameter &rhs)
  : ValueParameter(rhs) {
  
}

StringParameter::~StringParameter() {
}

StringParameter& StringParameter::operator=(const StringParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

std::string StringParameter::getDefault() {
  return mProps.getString(kOfxParamPropDefault, 0);
}

StringParamMode StringParameter::getMode() {
  return StringToStringParamMode(mProps.getString(kOfxParamPropStringMode, 0));
}

bool StringParameter::requireExistingFilePath() {
  return (mProps.getInt(kOfxParamPropStringFilePathExists, 0) == 1);
}

std::string StringParameter::getValue() throw(Exception) {
  char *val = 0;
  // no quite sure about this one
  OfxStatus stat = mSuite->paramGetValue(mHandle, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::StringParameter::getValue");
  }
  return val;
}

std::string StringParameter::getValueAtTime(Time t) throw(Exception) {
  char *val = 0;
  // no quite sure about this one
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::StringParameter::getValueAtTime");
  }
  return val;
}

void StringParameter::setValue(const std::string &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v.c_str());
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::StringParameter::setValue");
  }
}

void StringParameter::setValueAtTime(Time t, const std::string &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v.c_str());
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::StringParameter::setValueAtTime");
  }
}

}

