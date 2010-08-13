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

#include <ofx/booleanparameter.h>
#include <ofx/host.h>

namespace ofx {

BooleanParameterDescriptor::BooleanParameterDescriptor()
  : ValueParameterDescriptor() {
}

BooleanParameterDescriptor::BooleanParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ValueParameterDescriptor(h, hdl) {
}

BooleanParameterDescriptor::BooleanParameterDescriptor(const BooleanParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

BooleanParameterDescriptor::~BooleanParameterDescriptor() {
}

BooleanParameterDescriptor& BooleanParameterDescriptor::operator=(const BooleanParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

bool BooleanParameterDescriptor::getDefault() {
  return (getInt(kOfxParamPropDefault, 0) == 1);
}

void BooleanParameterDescriptor::setDefault(bool v) {
  setInt(kOfxParamPropDefault, 0, (v ? 1 : 0));
}

// ---

BooleanParameter::BooleanParameter()
  : ValueParameter() {
}

BooleanParameter::BooleanParameter(Host *h, OfxParamHandle hdl)
  : ValueParameter(h, hdl) {
}

BooleanParameter::BooleanParameter(const BooleanParameter &rhs)
  : ValueParameter(rhs) {
}

BooleanParameter::~BooleanParameter() {
}

BooleanParameter& BooleanParameter::operator=(const BooleanParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

bool BooleanParameter::getDefault() {
  return (mProps.getInt(kOfxParamPropDefault, 0) == 1);
}

bool BooleanParameter::getValue() throw(Exception) {
  int val;
  // no quite sure about this one
  OfxStatus stat = mSuite->paramGetValue(mHandle, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::BooleanParameter::getValue");
  }
  return (val == 1);
}

bool BooleanParameter::getValueAtTime(Time t) throw(Exception) {
  int val;
  // no quite sure about this one
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::BooleanParameter::getValueAtTime");
  }
  return (val == 1);
}

void BooleanParameter::setValue(bool v) throw(Exception) {
  int val = (v ? 1 : 0);
  OfxStatus stat = mSuite->paramSetValue(mHandle, val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::BooleanParameter::setValue");
  }
}

void BooleanParameter::setValueAtTime(Time t, bool v) throw(Exception) {
  int val = (v ? 1 : 0);
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::BooleanParameter::setValueAtTime");
  }
}

}

