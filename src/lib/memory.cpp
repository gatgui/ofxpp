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

#include <ofx/memory.h>
#include <ofx/host.h>

namespace ofx {

Memory::Memory(Host *h) throw(Exception) {
  if (!h) {
    throw BadHandleError("Cannot initialize ofx::Memory: invalid host");
  }
  mSuite = h->fetchSuite<OfxMemorySuiteV1>(kOfxMemorySuite, 1);
  if (!mSuite) {
    throw MissingHostFeatureError("Memory suite");
  }
}

Memory::~Memory() {
}

void Memory::free(void *mem) throw(Exception) {
  OfxStatus stat = mSuite->memoryFree(mem);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Memory::free");
  }
}

}

