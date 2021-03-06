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

/** \file exception.h
 *  Exception classes.
 */

#ifndef __ofx_exception_h__
#define __ofx_exception_h__

#include <ofxCore.h>
#include <exception>
#include <stdexcept>
#include <string>

namespace ofx {
  
  //! Base exception class.
  class Exception : public std::runtime_error {
    public:
      
      explicit Exception(OfxStatus s, const std::string &msg="", const char *statusString=0);
      
      virtual ~Exception() throw();
      
      //! Get associated OpenFX status.
      inline OfxStatus status() const {
        return mStat;
      }
      
    protected:
      
      OfxStatus mStat;
  };
  
  //! Failed exception.
  class FailedError : public Exception {
    public:
      explicit FailedError(const std::string &msg="");
      virtual ~FailedError() throw();
  };
  
  //! Fatal exception.
  class FatalError : public Exception {
    public:
      explicit FatalError(const std::string &msg="");
      virtual ~FatalError() throw();
  };
  
  //! Unknown exception.
  class UnknownError : public Exception {
    public:
      explicit UnknownError(const std::string &msg="");
      virtual ~UnknownError() throw();
  };
  
  //! Missing host feature exception.
  class MissingHostFeatureError : public Exception {
    public:
      explicit MissingHostFeatureError(const std::string &msg="");
      virtual ~MissingHostFeatureError() throw();
  };
  
  //! Unsupported exception.
  class UnsupportedError : public Exception {
    public:
      explicit UnsupportedError(const std::string &msg="");
      virtual ~UnsupportedError() throw();
  };
  
  //! Exists exception.
  class ExistsError : public Exception {
    public:
      explicit ExistsError(const std::string &msg="");
      virtual ~ExistsError() throw();
  };
  
  //! Format exception.
  class FormatError : public Exception {
    public:
      explicit FormatError(const std::string &msg="");
      virtual ~FormatError() throw();
  };
  
  //! Memory exception.
  class MemoryError : public Exception {
    public:
      explicit MemoryError(const std::string &msg="");
      virtual ~MemoryError() throw();
  };
  
  //! Bad handle exception.
  class BadHandleError : public Exception {
    public:
      explicit BadHandleError(const std::string &msg="");
      virtual ~BadHandleError() throw();
  };
  
  //! Bad index exception.
  class BadIndexError : public Exception {
    public:
      explicit BadIndexError(const std::string &msg="");
      virtual ~BadIndexError() throw();
  };
  
  //! Value exception.
  class ValueError : public Exception {
    public:
      explicit ValueError(const std::string &msg="");
      virtual ~ValueError() throw();
  };

  //! Image format exception
  class ImageFormatError : public Exception {
    public:
      explicit ImageFormatError(const std::string &msg="");
      virtual ~ImageFormatError() throw();
  };
  
#ifdef OFX_API_1_3
  
  class GLOutOfMemory : public Exception {
    public:
      explicit GLOutOfMemory(const std::string &msg="");
      virtual ~GLOutOfMemory() throw();
  };
  
  class GLRenderFailed : public Exception {
    public:
      explicit GLRenderFailed(const std::string &msg="");
      virtual ~GLRenderFailed() throw();
  };

#endif
  
}

#endif
