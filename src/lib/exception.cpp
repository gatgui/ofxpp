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

#include <ofx/exception.h>

namespace ofx {

Exception::Exception(OfxStatus s, const std::string &msg)
  : std::runtime_error((msg.length() == 0 ? "OFX Exception" : "OFX Exception: "+msg)),
    mStat(s) {
  
}

Exception::~Exception() throw() {
}

// ---

FailedError::FailedError(const std::string &msg)
  : Exception(kOfxStatFailed, "[Failed] "+msg) {
}

FailedError::~FailedError() throw() {
}

// ---

FatalError::FatalError(const std::string &msg)
  : Exception(kOfxStatErrFatal, "[Fatal] "+msg) {
}

FatalError::~FatalError() throw() {
}

// ---

UnknownError::UnknownError(const std::string &msg)
  : Exception(kOfxStatErrUnknown, "[Unknown] "+msg) {
}

UnknownError::~UnknownError() throw() {
}

// ---

MissingHostFeatureError::MissingHostFeatureError(const std::string &msg)
  : Exception(kOfxStatErrMissingHostFeature, "[Missing host feature] "+msg) {
}

MissingHostFeatureError::~MissingHostFeatureError() throw() {
}

// ---

UnsupportedError::UnsupportedError(const std::string &msg)
  : Exception(kOfxStatErrUnsupported, "[Unsupported] "+msg) {
}

UnsupportedError::~UnsupportedError() throw() {
}

// ---

ExistsError::ExistsError(const std::string &msg)
  : Exception(kOfxStatErrExists, "[Already exists] "+msg) {
}

ExistsError::~ExistsError() throw() {
}

// ---

FormatError::FormatError(const std::string &msg)
  : Exception(kOfxStatErrFormat, "[Invalid format] "+msg) {
}

FormatError::~FormatError() throw() {
}

// ---

MemoryError::MemoryError(const std::string &msg)
  : Exception(kOfxStatErrMemory, "[Memory] "+msg) {
}

MemoryError::~MemoryError() throw() {
}

// ---

BadHandleError::BadHandleError(const std::string &msg)
  : Exception(kOfxStatErrBadHandle, "[Bad handle] "+msg) {
}

BadHandleError::~BadHandleError() throw() {
}

// ---

BadIndexError::BadIndexError(const std::string &msg)
  : Exception(kOfxStatErrBadIndex, "[Bad index] "+msg) {
}

BadIndexError::~BadIndexError() throw() {
}

// ---

ValueError::ValueError(const std::string &msg)
  : Exception(kOfxStatErrValue, "[Invalid value] "+msg) {
}

ValueError::~ValueError() throw() {
}

}
