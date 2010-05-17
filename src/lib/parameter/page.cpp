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

#include <ofx/parameter/page.h>
#include <ofx/host.h>

namespace ofx {

PageParameterDescriptor::PageParameterDescriptor()
  : ParameterDescriptor() {
}

PageParameterDescriptor::PageParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ParameterDescriptor(h, hdl) {
}

PageParameterDescriptor::PageParameterDescriptor(const PageParameterDescriptor &rhs)
  : ParameterDescriptor(rhs) {
}

PageParameterDescriptor::~PageParameterDescriptor() {
}

PageParameterDescriptor& PageParameterDescriptor::operator=(const PageParameterDescriptor &rhs) {
  ParameterDescriptor::operator=(rhs);
  return *this;
}

int PageParameterDescriptor::getChildCount() {
  return size(kOfxParamPropPageChild);
}

void PageParameterDescriptor::setChild(int i, const std::string &name) {
  setString(kOfxParamPropPageChild, i, name);
}

std::string PageParameterDescriptor::getChild(int i) {
  return getString(kOfxParamPropPageChild, i);
}

// ---

PageParameter::PageParameter()
  : Parameter() {
}

PageParameter::PageParameter(Host *h, OfxParamHandle hdl)
  : Parameter(h, hdl) {
}

PageParameter::PageParameter(const PageParameter &rhs)
  : Parameter(rhs) {
}

PageParameter::~PageParameter() {
}

PageParameter& PageParameter::operator=(const PageParameter &rhs) {
  Parameter::operator=(rhs);
  return *this;
}

int PageParameter::getChildCount() {
  return mProps.size(kOfxParamPropPageChild);
}

std::string PageParameter::getChild(int i) {
  return mProps.getString(kOfxParamPropPageChild, i);
}

}

