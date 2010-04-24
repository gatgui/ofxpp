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
    throw Exception(kOfxStatErrFatal, "ofx::PropertySet::PropertySet: no host");
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

void PropertySet::setPointer(const char * prop, int index, void *val) throw(Exception) {
  checkStatus(mSuite->propSetPointer(mHandle, prop, index, val));
}

void PropertySet::setPointers(const char* prop, int n, void **val) throw(Exception) {
  checkStatus(mSuite->propSetPointerN(mHandle, prop, n, val));
}

void PropertySet::setString(const char* prop, int index, const std::string &val) throw(Exception) {
  checkStatus(mSuite->propSetString(mHandle, prop, index, val.c_str()));
}

void PropertySet::setStrings(const char* prop, int n, const std::string *val) throw(Exception) {
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

void PropertySet::setDouble(const char* prop, int index, double val) throw(Exception) {
  checkStatus(mSuite->propSetDouble(mHandle, prop, index, val));
}

void PropertySet::setDoubles(const char* prop, int n, double *val) throw(Exception) {
  checkStatus(mSuite->propSetDoubleN(mHandle, prop, n, val));
}

void PropertySet::setInt(const char* prop, int index, int val) throw(Exception) {
  checkStatus(mSuite->propSetInt(mHandle, prop, index, val));
}

void PropertySet::setInts(const char* prop, int n, int *val) throw(Exception) {
  checkStatus(mSuite->propSetIntN(mHandle, prop, n, val));
}

void* PropertySet::getPointer(const char* prop, int index) throw(Exception) {
  void *rv = 0;
  checkStatus(mSuite->propGetPointer(mHandle, prop, index, &rv));
  return rv;
}

void PropertySet::getPointers(const char* prop, int n, void **rv) throw(Exception) {
  checkStatus(mSuite->propGetPointerN(mHandle, prop, n, rv));
}

std::string PropertySet::getString(const char* prop, int index) throw(Exception) {
  char *rv = 0;
  checkStatus(mSuite->propGetString(mHandle, prop, index, &rv));
  return std::string(rv);
}

void PropertySet::getStrings(const char* prop, int n, std::string *rv) throw(Exception) {
  if (!rv) {
    throw Exception(kOfxStatFailed, "ofx::PropertySet::getStrings received a NULL pointer");
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

double PropertySet::getDouble(const char* prop, int index) throw(Exception) {
  double rv = 0;
  checkStatus(mSuite->propGetDouble(mHandle, prop, index, &rv));
  return rv;
}

void PropertySet::getDoubles(const char* prop, int n, double *rv) throw(Exception) {
  checkStatus(mSuite->propGetDoubleN(mHandle, prop, n, rv));
}

int PropertySet::getInt(const char* prop, int index) throw(Exception) {
  int rv = 0;
  checkStatus(mSuite->propGetInt(mHandle, prop, index, &rv));
  return rv;
}

void PropertySet::getInts(const char* prop, int n, int *rv) throw(Exception) {
  checkStatus(mSuite->propGetIntN(mHandle, prop, n, rv));
}

void PropertySet::reset(const char* prop) throw(Exception) {
  checkStatus(mSuite->propReset(mHandle, prop));
}

int PropertySet::size(const char* prop) throw(Exception) {
  int n;
  checkStatus(mSuite->propGetDimension(mHandle, prop, &n));
  return n;
}

}

