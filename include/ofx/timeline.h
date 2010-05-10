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

#ifndef __ofx_timeline_h__
#define __ofx_timeline_h__

#include <ofxCore.h>
#include <ofxTimeLine.h>
#include <ofx/exception.h>

#ifdef _MSC_VER
# pragma warning(disable:4290)
#endif

namespace ofx {
  
  class Host;
  class ImageEffect;
  
  class TimeLine {
    protected:
      
      OfxTimeLineSuiteV1 *mSuite;
      
    public:
      
      TimeLine(Host *h) throw(Exception);
      ~TimeLine();
      
      template <class Receiver>
      double getTime(Receiver *recv) throw(Exception) {
        double val;
        OfxStatus stat = mSuite->getTime(recv->handle(), &val);
        if (stat != kOfxStatOK) {
          throw Exception(stat, "ofx::TimeLine::getTime");
        }
        return val;
      }
      
      template <class Receiver>
      void gotoTime(Receiver *recv, double t) throw(Exception) {
        OfxStatus stat = mSuite->gotoTime(recv->handle(), t);
        if (stat != kOfxStatOK) {
          throw Exception(stat, "ofx::TimeLine::gotoTime");
        }
      }
      
      template <class Receiver>
      void getTimeBounds(Receiver *recv, double &first, double &last) throw(Exception) {
        OfxStatus stat = mSuite->getTimeBounds(recv->handle(), &first, &last);
        if (stat != kOfxStatOK) {
          throw Exception(stat, "ofx::TimeLine::getTimeBounds");
        }
      }
      
  };
}

#endif
