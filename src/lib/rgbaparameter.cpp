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

#include <ofx/rgbaparameter.h>
#include <ofx/host.h>

namespace ofx {

RGBAParameterDescriptor::RGBAParameterDescriptor()
  : ValueParameterDescriptor() {
}

RGBAParameterDescriptor::RGBAParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ValueParameterDescriptor(h, hdl) {
}

RGBAParameterDescriptor::RGBAParameterDescriptor(const RGBAParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

RGBAParameterDescriptor::~RGBAParameterDescriptor() {
}

RGBAParameterDescriptor& RGBAParameterDescriptor::operator=(const RGBAParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

RGBAColour<double> RGBAParameterDescriptor::defaultValue() {
  RGBAColour<double> rv;
  getDoubles(kOfxParamPropDefault, 4, &(rv.r));
  return rv;
}

void RGBAParameterDescriptor::defaultValue(const RGBAColour<double> &v) {
  setDoubles(kOfxParamPropDefault, 4, (double*)&(v.r));
}

// ---

RGBAParameter::RGBAParameter()
  : ValueParameter() {
}

RGBAParameter::RGBAParameter(Host *h, OfxParamHandle hdl)
  : ValueParameter(h, hdl) {
}

RGBAParameter::RGBAParameter(const RGBAParameter &rhs)
  : ValueParameter(rhs) {
}

RGBAParameter::~RGBAParameter() {
}

RGBAParameter& RGBAParameter::operator=(const RGBAParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

RGBAColour<double> RGBAParameter::defaultValue() {
  RGBAColour<double> rv;
  mProps.getDoubles(kOfxParamPropDefault, 4, &(rv.r));
  return rv;
}

RGBAColour<double> RGBAParameter::getValue() throw(Exception) {
  RGBAColour<double> v;
  OfxStatus stat = mSuite->paramGetValue(mHandle, &(v.r), &(v.g), &(v.b), &(v.a));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBAParameter::getValue");
  }
  return v;
}

RGBAColour<double> RGBAParameter::getValueAtTime(Time t) throw(Exception) {
  RGBAColour<double> v;
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &(v.r), &(v.g), &(v.b), &(v.a));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBAParameter::getValueAtTime");
  }
  return v;
}

RGBAColour<double> RGBAParameter::getDerivative(Time t) throw(Exception) {
  RGBAColour<double> v;
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, &(v.r), &(v.g), &(v.b), &(v.a));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBAParameter::getDerivative");
  }
  return v;
}

RGBAColour<double> RGBAParameter::getIntegral(Time t0, Time t1) throw(Exception) {
  RGBAColour<double> v;
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, &(v.r), &(v.g), &(v.b), &(v.a));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBAParameter::getIntegral");
  }
  return v;
}

void RGBAParameter::setValue(const RGBAColour<double> &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v.r, v.g, v.b, v.a);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBAParameter::setValue");
  }
}

void RGBAParameter::setValueAtTime(Time t, const RGBAColour<double> &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v.r, v.g, v.b, v.a);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBAParameter::setValueAtTime");
  }
}

}

