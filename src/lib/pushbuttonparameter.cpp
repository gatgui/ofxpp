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

#include <ofx/pushbuttonparameter.h>
#include <ofx/host.h>

namespace ofx {

PushButtonParameterDescriptor::PushButtonParameterDescriptor()
  : ParameterDescriptor() {
}

PushButtonParameterDescriptor::PushButtonParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ParameterDescriptor(h, hdl) {
}

PushButtonParameterDescriptor::PushButtonParameterDescriptor(const PushButtonParameterDescriptor &rhs)
  : ParameterDescriptor(rhs) {
}

PushButtonParameterDescriptor::~PushButtonParameterDescriptor() {
}

PushButtonParameterDescriptor& PushButtonParameterDescriptor::operator=(const PushButtonParameterDescriptor &rhs) {
  ParameterDescriptor::operator=(rhs);
  return *this;
}

EntryPoint PushButtonParameterDescriptor::interact() {
  return ((EntryPoint) getPointer(kOfxParamPropInteractV1, 0));
}

void PushButtonParameterDescriptor::interact(EntryPoint func) {
  setPointer(kOfxParamPropInteractV1, 0, (void*)func);
}

/*
void PushButtonParameterDescriptor::interactSize(double *w, double *h) {
  *w = getDouble(kOfxParamPropInteractSize, 0);
  *h = getDouble(kOfxParamPropInteractSize, 1);
}

void PushButtonParameterDescriptor::interactSize(double w, double h) {
  setDouble(kOfxParamPropInteractSize, 0, w);
  setDouble(kOfxParamPropInteractSize, 1, h);
}
*/

double PushButtonParameterDescriptor::interactSizeAspect() {
  return getDouble(kOfxParamPropInteractSizeAspect, 0);
}

void PushButtonParameterDescriptor::interactSizeAspect(double a) {
  setDouble(kOfxParamPropInteractSizeAspect, 0, a);
}

void PushButtonParameterDescriptor::interactMinimumSize(int *w, int *h) {
  *w = getInt(kOfxParamPropInteractMinimumSize, 0);
  *h = getInt(kOfxParamPropInteractMinimumSize, 1);
}

void PushButtonParameterDescriptor::interactMinimumSize(int w, int h) {
  setInt(kOfxParamPropInteractMinimumSize, 0, w);
  setInt(kOfxParamPropInteractMinimumSize, 1, h);
}

void PushButtonParameterDescriptor::interactPreferedSize(int *w, int *h) {
  *w = getInt(kOfxParamPropInteractPreferedSize, 0);
  *h = getInt(kOfxParamPropInteractPreferedSize, 1);
}

void PushButtonParameterDescriptor::interactPreferedSize(int w, int h) {
  setInt(kOfxParamPropInteractPreferedSize, 0, w);
  setInt(kOfxParamPropInteractPreferedSize, 1, h);
}

#ifdef OFX_API_1_2

bool PushButtonParameterDescriptor::hasHostOverlayHandle() {
  return (getInt(kOfxParamPropHasHostOverlayHandle, 0) != 0);
}

bool PushButtonParameterDescriptor::useHostOverlayHandle() {
  return (getInt(kOfxParamPropUseHostOverlayHandle, 0) != 0);
}

void PushButtonParameterDescriptor::useHostOverlayHandle(bool v) {
  setInt(kOfxParamPropUseHostOverlayHandle, 0, (v ? 1 : 0));
}

#endif

// ---

PushButtonParameter::PushButtonParameter()
  : Parameter() {
}

PushButtonParameter::PushButtonParameter(Host *h, OfxParamHandle hdl)
  : Parameter(h, hdl) {
}

PushButtonParameter::PushButtonParameter(const PushButtonParameter &rhs)
  : Parameter(rhs) {
}

PushButtonParameter::~PushButtonParameter() {
}

PushButtonParameter& PushButtonParameter::operator=(const PushButtonParameter &rhs) {
  Parameter::operator=(rhs);
  return *this;
}

EntryPoint PushButtonParameter::interact() {
  return ((EntryPoint) mProps.getPointer(kOfxParamPropInteractV1, 0));
}

void PushButtonParameter::interactSize(double *w, double *h) {
  *w = mProps.getDouble(kOfxParamPropInteractSize, 0);
  *h = mProps.getDouble(kOfxParamPropInteractSize, 1);
}

double PushButtonParameter::interactSizeAspect() {
  return mProps.getDouble(kOfxParamPropInteractSizeAspect, 0);
}

void PushButtonParameter::interactMinimumSize(int *w, int *h) {
  *w = mProps.getInt(kOfxParamPropInteractMinimumSize, 0);
  *h = mProps.getInt(kOfxParamPropInteractMinimumSize, 1);
}

void PushButtonParameter::interactPreferedSize(int *w, int *h) {
  *w = mProps.getInt(kOfxParamPropInteractPreferedSize, 0);
  *h = mProps.getInt(kOfxParamPropInteractPreferedSize, 1);
}

#ifdef OFX_API_1_2

bool PushButtonParameter::useHostOverlayHandle() {
  return (mProps.getInt(kOfxParamPropUseHostOverlayHandle, 0) != 0);
}

#endif

}

