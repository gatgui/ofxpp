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

#include <ofx/property.h>
#include <ofx/host.h>
#include <ofxParam.h>

namespace ofx {

PropertySet::PropertySet()
  : mHandle(0), mSuite(0) {
}

PropertySet::PropertySet(Host *h, OfxPropertySetHandle hdl) throw(Exception)
  : mHandle(hdl), mSuite(0) {
  if (!h) {
    throw BadHandleError("ofx::PropertySet::PropertySet: invalid host");
  }
  mSuite = h->propertySuite();
}

PropertySet::PropertySet(const PropertySet &rhs)
  : mHandle(rhs.mHandle), mSuite(rhs.mSuite) {
}

PropertySet::~PropertySet() {
}

PropertySet& PropertySet::operator=(const PropertySet &rhs) {
  mHandle = rhs.mHandle;
  mSuite = rhs.mSuite;
  return *this;
}

void PropertySet::checkStatus(OfxStatus s, const std::string &msg) throw(Exception) {
  if (s != kOfxStatOK) {
    if (msg.length() > 0) {
      throw Exception(s, msg);
    } else {
      throw Exception(s, "ofx::PropertySet error");
    }
  }
}

void PropertySet::setPointer(const char * prop, int index, void *val) {
  checkStatus(mSuite->propSetPointer(mHandle, prop, index, val));
}

void PropertySet::setPointers(const char* prop, int n, void **val) {
  checkStatus(mSuite->propSetPointerN(mHandle, prop, n, val));
}

void PropertySet::setString(const char* prop, int index, const std::string &val) {
  checkStatus(mSuite->propSetString(mHandle, prop, index, val.c_str()));
}

void PropertySet::setStrings(const char* prop, int n, const std::string *val) {
  if (!val) {
    throw Exception(kOfxStatFailed, "ofx::PropertySet::setStrings received a NULL pointer");
  }
  const char ** strs = new const char* [n];
  for (int i=0; i<n; ++i) {
    strs[i] = val[i].c_str();
  }
  OfxStatus stat = mSuite->propSetStringN(mHandle, prop, n, strs);
  delete[] strs;
  checkStatus(stat);
}

void PropertySet::setDouble(const char* prop, int index, double val) {
  checkStatus(mSuite->propSetDouble(mHandle, prop, index, val));
}

void PropertySet::setDoubles(const char* prop, int n, double *val) {
  checkStatus(mSuite->propSetDoubleN(mHandle, prop, n, val));
}

void PropertySet::setInt(const char* prop, int index, int val) {
  checkStatus(mSuite->propSetInt(mHandle, prop, index, val));
}

void PropertySet::setInts(const char* prop, int n, int *val) {
  checkStatus(mSuite->propSetIntN(mHandle, prop, n, val));
}

void* PropertySet::getPointer(const char* prop, int index) {
  void *rv = 0;
  checkStatus(mSuite->propGetPointer(mHandle, prop, index, &rv));
  return rv;
}

void PropertySet::getPointers(const char* prop, int n, void **rv) {
  checkStatus(mSuite->propGetPointerN(mHandle, prop, n, rv));
}

std::string PropertySet::getString(const char* prop, int index) {
  char *rv = 0;
  checkStatus(mSuite->propGetString(mHandle, prop, index, &rv));
  return std::string(rv);
}

void PropertySet::getStrings(const char* prop, int n, std::string *rv) throw(Exception) {
  if (!rv) {
    throw FailedError("ofx::PropertySet::getStrings received a NULL pointer");
  }
  char ** strs = new char* [n];
  OfxStatus stat = mSuite->propGetStringN(mHandle, prop, n, strs);
  if (stat == kOfxStatOK) {
    for (int i=0; i<n; ++i) {
      rv[i] = std::string(strs[i]);
    }
  }
  delete[] strs;
  checkStatus(stat);
}

double PropertySet::getDouble(const char* prop, int index) {
  double rv = 0;
  checkStatus(mSuite->propGetDouble(mHandle, prop, index, &rv));
  return rv;
}

void PropertySet::getDoubles(const char* prop, int n, double *rv) {
  checkStatus(mSuite->propGetDoubleN(mHandle, prop, n, rv));
}

int PropertySet::getInt(const char* prop, int index) {
  int rv = 0;
  checkStatus(mSuite->propGetInt(mHandle, prop, index, &rv));
  return rv;
}

void PropertySet::getInts(const char* prop, int n, int *rv) {
  checkStatus(mSuite->propGetIntN(mHandle, prop, n, rv));
}

void PropertySet::reset(const char* prop) {
  checkStatus(mSuite->propReset(mHandle, prop));
}

int PropertySet::size(const char* prop) {
  int n;
  checkStatus(mSuite->propGetDimension(mHandle, prop, &n));
  return n;
}

}

