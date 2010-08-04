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

#include <ofx/timeline.h>
#include <ofx/host.h>
#include <ofx/imageeffect.h>

namespace ofx {

TimeLineSuite::TimeLineSuite(Host *h) throw(Exception) {
  if (!h) {
    throw BadHandleError("ofx::TimeLine: invalid host");
  }
  mSuite = h->fetchSuite<OfxTimeLineSuiteV1>(kOfxTimeLineSuite, 1);
  if (!mSuite) {
    throw MissingHostFeatureError("Timeline suite");
  }
}

TimeLineSuite::~TimeLineSuite() {
}

}

