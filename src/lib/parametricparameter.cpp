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

#include <ofx/parametricparameter.h>
#include <ofx/host.h>

namespace ofx {

#ifdef OFX_API_1_2

ParametricParameterDescriptor::ParametricParameterDescriptor()
  : ValueParameterDescriptor() {
}

ParametricParameterDescriptor::ParametricParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ValueParameterDescriptor(h, hdl) {
}

ParametricParameterDescriptor::ParametricParameterDescriptor(const ParametricParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

ParametricParameterDescriptor::~ParametricParameterDescriptor() {
}

ParametricParameterDescriptor& ParametricParameterDescriptor::operator=(const ParametricParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

int ParametricParameterDescriptor::dimension() {
  return getInt(kOfxParamPropParametricDimension, 0);
}

void ParametricParameterDescriptor::dimension(int n) {
  setInt(kOfxParamPropParametricDimension, 0, n);
}

RGBAColour<double> ParametricParameterDescriptor::UIColour(int d) {
  int offset = 3 * d;
  RGBAColour<double> rv;
  rv.r = getDouble(kOfxParamPropParametricUIColour, offset+0);
  rv.g = getDouble(kOfxParamPropParametricUIColour, offset+1);
  rv.b = getDouble(kOfxParamPropParametricUIColour, offset+2);
  rv.a = 1.0;
  return rv;
}

void ParametricParameterDescriptor::UIColour(int d, const RGBAColour<double> &c) {
  int offset = 3 * d;
  setDouble(kOfxParamPropParametricUIColour, offset+0, c.r);
  setDouble(kOfxParamPropParametricUIColour, offset+1, c.g);
  setDouble(kOfxParamPropParametricUIColour, offset+2, c.b);
}

EntryPoint ParametricParameterDescriptor::interactBackground() {
  return (EntryPoint) getPointer(kOfxParamPropParametricInteractBackground, 0);
}

void ParametricParameterDescriptor::interactBackground(EntryPoint ep) {
  setPointer(kOfxParamPropParametricInteractBackground, 0, (void*)ep);
}

void ParametricParameterDescriptor::range(double *pmin, double *pmax) {
  *pmin = getDouble(kOfxParamPropParametricRange, 0);
  *pmax = getDouble(kOfxParamPropParametricRange, 1);
}

void ParametricParameterDescriptor::range(double pmin, double pmax) {
  setDouble(kOfxParamPropParametricRange, 0, pmin);
  setDouble(kOfxParamPropParametricRange, 1, pmax);
}

std::string ParametricParameterDescriptor::dimensionLabel(int d) {
  return getString(kOfxParamPropDimensionLabel, d);
}

void ParametricParameterDescriptor::dimensionLabel(int d, const std::string &l) {
  setString(kOfxParamPropDimensionLabel, d, l);
}

// ---

ParametricParameter::ParametricParameter()
  : ValueParameter() {
}

ParametricParameter::ParametricParameter(Host *h, OfxParamHandle hdl)
  : ValueParameter(h, hdl) {
  mParametricSuite = h->parametricParameterSuite();
  if (!mParametricSuite) {
    throw MissingHostFeatureError("Parametric parameter suite");
  }
}

ParametricParameter::ParametricParameter(const ParametricParameter &rhs)
  : ValueParameter(rhs), mParametricSuite(rhs.mParametricSuite) {
}

ParametricParameter::~ParametricParameter() {
}

ParametricParameter& ParametricParameter::operator=(const ParametricParameter &rhs) {
  ValueParameter::operator=(rhs);
  mParametricSuite = rhs.mParametricSuite;
  return *this;
}

int ParametricParameter::dimension() {
  return mProps.getInt(kOfxParamPropParametricDimension, 0);
}

RGBAColour<double> ParametricParameter::UIColour(int d) {
  int offset = 3 * d;
  RGBAColour<double> rv;
  rv.r = mProps.getDouble(kOfxParamPropParametricUIColour, offset+0);
  rv.g = mProps.getDouble(kOfxParamPropParametricUIColour, offset+1);
  rv.b = mProps.getDouble(kOfxParamPropParametricUIColour, offset+2);
  rv.a = 1.0;
  return rv;
}

EntryPoint ParametricParameter::interactBackground() {
  return (EntryPoint) mProps.getPointer(kOfxParamPropParametricInteractBackground, 0);
}

void ParametricParameter::range(double *pmin, double *pmax) {
  *pmin = mProps.getDouble(kOfxParamPropParametricRange, 0);
  *pmax = mProps.getDouble(kOfxParamPropParametricRange, 1);
}

std::string ParametricParameter::dimensionLabel(int d) {
  return mProps.getString(kOfxParamPropDimensionLabel, d);
}

int ParametricParameter::getControlPointsCount(int curveIndex, Time t) {
  int rv = 0;
  OfxStatus stat = mParametricSuite->parametricParamGetNControlPoints(mHandle, curveIndex, t, &rv);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParametricParameter::controlPointsCount");
  }
  return rv;
}

void ParametricParameter::getControlPoint(int curveIndex, Time t, int ctrlIdx, double *pos, double *val) {
  OfxStatus stat = mParametricSuite->parametricParamGetNthControlPoint(mHandle, curveIndex, t, ctrlIdx, pos, val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParametricParameter::getControlPoint");
  }
}

void ParametricParameter::setControlPoint(int curveIndex, Time t, int ctrlIdx, double pos, double val, bool addKey) {
  OfxStatus stat = mParametricSuite->parametricParamSetNthControlPoint(mHandle, curveIndex, t, ctrlIdx, pos, val, addKey);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParametricParameter::setControlPoint");
  }
}

void ParametricParameter::addControlPoint(int curveIndex, Time t, double pos, double val, bool addKey) {
  OfxStatus stat = mParametricSuite->parametricParamAddControlPoint(mHandle, curveIndex, t, pos, val, addKey);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParametricParameter::addControlPoint");
  }
}

void ParametricParameter::deleteControlPoint(int curveIndex, int ctrlIdx) {
  OfxStatus stat = mParametricSuite->parametricParamDeleteControlPoint(mHandle, curveIndex, ctrlIdx);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParametricParameter::deleteControlPoint");
  }
}

void ParametricParameter::deleteAllControlPoints(int curveIndex) {
  OfxStatus stat = mParametricSuite->parametricParamDeleteAllControlPoints(mHandle, curveIndex);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParametricParameter::deleteAllControlPoints");
  }
}

double ParametricParameter::eval(int curveIndex, Time t, double pos) {
  double rv = 0.0;
  OfxStatus stat = mParametricSuite->parametricParamGetValue(mHandle, curveIndex, t, pos, &rv);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParametricParameter::eval");
  }
  return rv;
}

#endif

}

