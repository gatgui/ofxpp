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
#include <sstream>
#ifdef OFX_API_1_3
#include <ofxImageEffect.h>
#include <ofxOpenGLRender.h>
#endif

namespace ofx {

#define STAT_MAX 14
static const char* gStatString[] = {
  "OK",
  "Failed",
  "Fatal error",
  "Unknown error",
  "Missing host feature error",
  "Unsupported error",
  "Exists error",
  "Format error",
  "Memory error",
  "Bad handle error",
  "Bad index error",
  "Value error",
  "Reply yes",
  "Reply no",
  "Reply default"
};

static std::string InvalidStatusString(int i) {
  std::ostringstream oss;
  oss << "Invalid status (";
  oss << i;
  oss << ")";
  return oss.str();
}

Exception::Exception(OfxStatus s, const std::string &msg, const char *statusString)
  : std::runtime_error(std::string("OFX Exception [") +
                       ((s>=0 && s<=STAT_MAX) ? gStatString[s] : (statusString ? statusString : InvalidStatusString(s))) +
                       std::string("] ") +
                       msg),
    mStat(s) {
  
}

Exception::~Exception() throw() {
}

// ---

FailedError::FailedError(const std::string &msg)
  : Exception(kOfxStatFailed, msg) {
}

FailedError::~FailedError() throw() {
}

// ---

FatalError::FatalError(const std::string &msg)
  : Exception(kOfxStatErrFatal, msg) {
}

FatalError::~FatalError() throw() {
}

// ---

UnknownError::UnknownError(const std::string &msg)
  : Exception(kOfxStatErrUnknown, msg) {
}

UnknownError::~UnknownError() throw() {
}

// ---

MissingHostFeatureError::MissingHostFeatureError(const std::string &msg)
  : Exception(kOfxStatErrMissingHostFeature, msg) {
}

MissingHostFeatureError::~MissingHostFeatureError() throw() {
}

// ---

UnsupportedError::UnsupportedError(const std::string &msg)
  : Exception(kOfxStatErrUnsupported, msg) {
}

UnsupportedError::~UnsupportedError() throw() {
}

// ---

ExistsError::ExistsError(const std::string &msg)
  : Exception(kOfxStatErrExists, msg) {
}

ExistsError::~ExistsError() throw() {
}

// ---

FormatError::FormatError(const std::string &msg)
  : Exception(kOfxStatErrFormat, msg) {
}

FormatError::~FormatError() throw() {
}

// ---

MemoryError::MemoryError(const std::string &msg)
  : Exception(kOfxStatErrMemory, msg) {
}

MemoryError::~MemoryError() throw() {
}

// ---

BadHandleError::BadHandleError(const std::string &msg)
  : Exception(kOfxStatErrBadHandle, msg) {
}

BadHandleError::~BadHandleError() throw() {
}

// ---

BadIndexError::BadIndexError(const std::string &msg)
  : Exception(kOfxStatErrBadIndex, msg) {
}

BadIndexError::~BadIndexError() throw() {
}

// ---

ValueError::ValueError(const std::string &msg)
  : Exception(kOfxStatErrValue, msg) {
}

ValueError::~ValueError() throw() {
}

// ---

ImageFormatError::ImageFormatError(const std::string &msg)
  : Exception(kOfxStatErrImageFormat, msg, "ImageFormatError") {
}

ImageFormatError::~ImageFormatError() throw() {
}

// ---

#ifdef OFX_API_1_3

GLOutOfMemory::GLOutOfMemory(const std::string &msg)
  : Exception(kOfxStatGLOutOfMemory, msg, "GLOutOfMemory") {
}

GLOutOfMemory::~GLOutOfMemory() throw() {
}

// ---

GLRenderFailed::GLRenderFailed(const std::string &msg)
  : Exception(kOfxStatGLRenderFailed, msg, "GLRenderFailed") {
}

GLRenderFailed::~GLRenderFailed() throw() {
}

#endif

}
