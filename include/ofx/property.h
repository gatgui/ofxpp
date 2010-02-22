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

#ifndef __ofx_property_h__
#define __ofx_property_h__

#include <ofxProperty.h>
#include <ofx/exception.h>
#include <cassert>
#include <string>

namespace ofx {
  
  class Host;
  
  class PropertySet {
    //protected:
    //  
    //  static OfxPropertySuiteV1 *msSuiteV1;
    //  
    //public:
    //  
    //  static void Init(Host *s) throw(Exception);
    
    public:
      
      PropertySet();
      PropertySet(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      PropertySet(const PropertySet &rhs);
      virtual ~PropertySet();
      
      PropertySet& operator=(const PropertySet &rhs);
      //PropertySet& operator=(OfxPropertySetHandle hdl);
      
      void setPointer(const char * prop, int index, void *val) throw(Exception);
      void setPointers(const char * prop, int n, void **val) throw(Exception);
      void setString(const char * prop, int index, const std::string &val) throw(Exception);
      void setStrings(const char * prop, int n, const std::string *val) throw(Exception);
      void setDouble(const char * prop, int index, double val) throw(Exception);
      void setDoubles(const char * prop, int n, double *val) throw(Exception);
      void setInt(const char * prop, int index, int val) throw(Exception);
      void setInts(const char * prop, int n, int *val) throw(Exception);
      
      void* getPointer(const char * prop, int index) throw(Exception);
      void getPointers(const char * prop, int n, void **rv) throw(Exception);
      std::string getString(const char * prop, int index) throw(Exception);
      void getStrings(const char * prop, int n, std::string *rv) throw(Exception);
      double getDouble(const char * prop, int index) throw(Exception);
      void getDoubles(const char * prop, int n, double *rv) throw(Exception);
      int getInt(const char * prop, int index) throw(Exception);
      void getInts(const char * prop, int n, int *rv) throw(Exception);
      
      void reset(const char * prop) throw(Exception);
      
      int size(const char * prop) throw(Exception);
      
      inline OfxPropertySetHandle handle() {
        return mHandle;
      }
    
    protected:
      
      void checkStatus(OfxStatus s, const std::string &msg="") throw(Exception);
      
    protected:
      
      OfxPropertySetHandle mHandle;
      OfxPropertySuiteV1 *mSuite;
      
  };
}

#endif
