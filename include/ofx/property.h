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

/** \file property.h
 *  Property suite functions wrapper.
 */

#ifndef __ofx_property_h__
#define __ofx_property_h__

#include <ofxProperty.h>
#include <ofx/exception.h>
#include <cassert>
#include <string>

#ifdef _MSC_VER
# pragma warning(disable:4290)
#endif

namespace ofx {
  
  class Host;
  
  //! Property set class.
  class PropertySet {
    public:
      
      PropertySet();
      PropertySet(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      PropertySet(const PropertySet &rhs);
      virtual ~PropertySet();
      
      PropertySet& operator=(const PropertySet &rhs);
      
      //! Set indexed pointer property.
      void setPointer(const char * prop, int index, void *val);
      //! Set multiple pointer property.
      void setPointers(const char * prop, int n, void **val);
      //! Set indexed string property.
      void setString(const char * prop, int index, const std::string &val);
      //! Set multiple string property.
      void setStrings(const char * prop, int n, const std::string *val);
      //! Set indexed double property.
      void setDouble(const char * prop, int index, double val);
      //! Set multiple double property.
      void setDoubles(const char * prop, int n, double *val);
      //! Set indexed integer property.
      void setInt(const char * prop, int index, int val);
      //! Set multiple integer property.
      void setInts(const char * prop, int n, int *val);
      
      //! Get indexed pointer property.
      void* getPointer(const char * prop, int index);
      //! Get multiple pointer property.
      void getPointers(const char * prop, int n, void **rv);
      //! Get indexed string property.
      std::string getString(const char * prop, int index);
      //! Get multiple string property.
      void getStrings(const char * prop, int n, std::string *rv) throw(Exception);
      //! Get indexed double property.
      double getDouble(const char * prop, int index);
      //! Get multiple double property.
      void getDoubles(const char * prop, int n, double *rv);
      //! Get indexed integer property.
      int getInt(const char * prop, int index);
      //! Get multiple integer property.
      void getInts(const char * prop, int n, int *rv);
      
      //! Reset property value.
      void reset(const char * prop);
      
      //! Get property value size.
      int size(const char * prop);
      
      //! Get native handle.
      inline OfxPropertySetHandle handle() {
        return mHandle;
      }
    
    protected:
      
      //! \internal
      void checkStatus(OfxStatus s, const char *prop, const char *msg=0) throw(Exception);
      
    protected:
      
      OfxPropertySetHandle mHandle;
      OfxPropertySuiteV1 *mSuite;
      
  };
}

#endif
