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

#ifndef __ofx_exception_h__
#define __ofx_exception_h__

#include <ofxCore.h>
#include <exception>
#include <stdexcept>
#include <string>

namespace ofx {
  
  class Exception : public std::runtime_error {
    public:
      
      explicit Exception(OfxStatus s, const std::string &msg="");
      
      virtual ~Exception() throw();
      
      inline OfxStatus getStatus() const {
        return mStat;
      }
      
    protected:
      
      OfxStatus mStat;
  };
  
}

#endif
