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

#include <ofx/parameter/rgb.h>
#include <ofx/host.h>

namespace ofx {

RGBParameterDescriptor::RGBParameterDescriptor()
  : ValueParameterDescriptor() {
}

RGBParameterDescriptor::RGBParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ValueParameterDescriptor(h, hdl) {
}

RGBParameterDescriptor::RGBParameterDescriptor(const RGBParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

RGBParameterDescriptor::~RGBParameterDescriptor() {
}

RGBParameterDescriptor& RGBParameterDescriptor::operator=(const RGBParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

RGBAColour<double> RGBParameterDescriptor::getDefault() {
  RGBAColour<double> rv;
  getDoubles(kOfxParamPropDefault, 3, &(rv.r));
  rv.a = 1.0;
  return rv;
}

void RGBParameterDescriptor::setDefault(const RGBAColour<double> &v) {
  setDoubles(kOfxParamPropDefault, 3, (double*)&(v.r));
}

// ---

RGBParameter::RGBParameter()
  : ValueParameter() {
}

RGBParameter::RGBParameter(Host *h, OfxParamHandle hdl)
  : ValueParameter(h, hdl) {
}

RGBParameter::RGBParameter(const RGBParameter &rhs)
  : ValueParameter(rhs) {
}

RGBParameter::~RGBParameter() {
}

RGBParameter& RGBParameter::operator=(const RGBParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

RGBAColour<double> RGBParameter::getDefault() {
  RGBAColour<double> rv;
  mProps.getDoubles(kOfxParamPropDefault, 3, &(rv.r));
  rv.a = 1.0;
  return rv;
}

RGBAColour<double> RGBParameter::getValue() throw(Exception) {
  RGBAColour<double> v;
  v.a = 1.0;
  OfxStatus stat = mSuite->paramGetValue(mHandle, &(v.r), &(v.g), &(v.b));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBParameter::getValue");
  }
  return v;
}

RGBAColour<double> RGBParameter::getValueAtTime(Time t) throw(Exception) {
  RGBAColour<double> v;
  v.a = 1.0;
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &(v.r), &(v.g), &(v.b));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBParameter::getValueAtTime");
  }
  return v;
}

RGBAColour<double> RGBParameter::getDerivative(Time t) throw(Exception) {
  RGBAColour<double> v;
  v.a = 1.0;
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, &(v.r), &(v.g), &(v.b));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBParameter::getDerivative");
  }
  return v;
}

RGBAColour<double> RGBParameter::getIntegral(Time t0, Time t1) throw(Exception) {
  RGBAColour<double> v;
  v.a = 1.0;
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, &(v.r), &(v.g), &(v.b));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBParameter::getIntegral");
  }
  return v;
}

void RGBParameter::setValue(const RGBAColour<double> &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v.r, v.g, v.b);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBParameter::setValue");
  }
}

void RGBParameter::setValueAtTime(Time t, const RGBAColour<double> &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v.r, v.g, v.b);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBParameter::setValueAtTime");
  }
}

}

