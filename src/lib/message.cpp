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

#include <ofx/message.h>
#include <ofx/host.h>

namespace ofx {

MessageSuite::MessageSuite(Host *h) throw(Exception) {
  if (!h) {
    throw BadHandleError("Cannot initialize ofx::Message: invalid host");
  }
  mSuite = h->fetchSuite<OfxMessageSuiteV1>(kOfxMessageSuite, 1);
  if (!mSuite) {
    throw MissingHostFeatureError("Message suite");
  }
#ifdef OFX_API_1_2
  if (h->checkAPIVersion(1, 2)) {
    mSuite2 = h->fetchSuite<OfxMessageSuiteV2>(kOfxMessageSuite, 2);
    if (!mSuite2) {
      throw MissingHostFeatureError("Message suite v2");
    }
  }
#endif
}

MessageSuite::~MessageSuite() {
}

}

