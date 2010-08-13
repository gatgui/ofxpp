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

#include <ofx/groupparameter.h>
#include <ofx/host.h>

namespace ofx {

#ifdef OFX_API_1_2

GroupParameterDescriptor::GroupParameterDescriptor()
  : ParameterDescriptor() {
}

GroupParameterDescriptor::GroupParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ParameterDescriptor(h, hdl) {
}

GroupParameterDescriptor::GroupParameterDescriptor(const GroupParameterDescriptor &rhs)
  : ParameterDescriptor(rhs) {
}

GroupParameterDescriptor::~GroupParameterDescriptor() {
}

GroupParameterDescriptor& GroupParameterDescriptor::operator=(const GroupParameterDescriptor &rhs) {
  ParameterDescriptor::operator=(rhs);
  return *this;
}

bool GroupParameterDescriptor::isInitiallyOpened() {
  return (getInt(kOfxParamPropGroupOpen, 0) == 1);
}

void GroupParameterDescriptor::setInitiallyOpened(bool o) {
  setInt(kOfxParamPropGroupOpen, 0, (o ? 1 : 0));
}

// ---

GroupParameter::GroupParameter()
  : Parameter() {
}

GroupParameter::GroupParameter(Host *h, OfxParamHandle hdl)
  : Parameter(h, hdl) {
}

GroupParameter::GroupParameter(const GroupParameter &rhs)
  : Parameter(rhs) {
}

GroupParameter::~GroupParameter() {
}

GroupParameter& GroupParameter::operator=(const GroupParameter &rhs) {
  Parameter::operator=(rhs);
  return *this;
}

bool GroupParameter::isInitiallyOpened() {
  return (mProps.getInt(kOfxParamPropGroupOpen, 0) == 1);
}

#endif

}

