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

#include <ofx/choiceparameter.h>
#include <ofx/host.h>

namespace ofx {

ChoiceParameterDescriptor::ChoiceParameterDescriptor()
  : ValueParameterDescriptor() {
}

ChoiceParameterDescriptor::ChoiceParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ValueParameterDescriptor(h, hdl) {
}

ChoiceParameterDescriptor::ChoiceParameterDescriptor(const ChoiceParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

ChoiceParameterDescriptor::~ChoiceParameterDescriptor() {
}

ChoiceParameterDescriptor& ChoiceParameterDescriptor::operator=(const ChoiceParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

int ChoiceParameterDescriptor::getDefault() {
  return getInt(kOfxParamPropDefault, 0);
}

void ChoiceParameterDescriptor::setDefault(int v) {
  setInt(kOfxParamPropDefault, 0, v);
}

int ChoiceParameterDescriptor::getChoiceCount() {
  return size(kOfxParamPropChoiceOption);
}

void ChoiceParameterDescriptor::setChoice(int i, const std::string &str) {
  setString(kOfxParamPropChoiceOption, i, str);
}

std::string ChoiceParameterDescriptor::getChoice(int i) {
  return getString(kOfxParamPropChoiceOption, i);
}

// ---

ChoiceParameter::ChoiceParameter()
  : ValueParameter() {
}

ChoiceParameter::ChoiceParameter(Host *h, OfxParamHandle hdl)
  : ValueParameter(h, hdl) {
}

ChoiceParameter::ChoiceParameter(const ChoiceParameter &rhs)
  : ValueParameter(rhs) {
}

ChoiceParameter::~ChoiceParameter() {
}

ChoiceParameter& ChoiceParameter::operator=(const ChoiceParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

int ChoiceParameter::getDefault() {
  return mProps.getInt(kOfxParamPropDefault, 0);
}

int ChoiceParameter::getChoiceCount() {
  return mProps.size(kOfxParamPropChoiceOption);
}

void ChoiceParameter::setChoice(int i, const std::string &str) {
  mProps.setString(kOfxParamPropChoiceOption, i, str);
}

std::string ChoiceParameter::getChoice(int i) {
  return mProps.getString(kOfxParamPropChoiceOption, i);
}

int ChoiceParameter::getValue() throw(Exception) {
  int val;
  OfxStatus stat = mSuite->paramGetValue(mHandle, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ChoiceParameter::getValue");
  }
  return val;
}

int ChoiceParameter::getValueAtTime(Time t) throw(Exception) {
  int val;
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ChoiceParameter::getValueAtTime");
  }
  return val;
}

void ChoiceParameter::setValue(int v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ChoiceParameter::setValue");
  }
}

void ChoiceParameter::setValueAtTime(Time t, int v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ChoiceParameter::setValueAtTime");
  }
}

}

