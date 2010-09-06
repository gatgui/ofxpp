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

/** \file timeline.h
 *  Time line suite functions wrapper.
 */

#ifndef __ofx_timeline_h__
#define __ofx_timeline_h__

#include <ofxCore.h>
#include <ofxTimeLine.h>
#include <ofx/exception.h>
#include <ofx/ofx.h>

#ifdef _MSC_VER
# pragma warning(disable:4290)
#endif

namespace ofx {
  
  class Host;
  class ImageEffect;
  
  //! Time line suite functions wrapper class.
  class TimeLineSuite {
    protected:
      
      OfxTimeLineSuiteV1 *mSuite;
      
    public:
      
      TimeLineSuite(Host *h) throw(Exception);
      ~TimeLineSuite();
      
      /** Get current time
       *  \param[in] recv Object to retrive time for.\n
       *                  Must be an object having a "handle" method.
       */
      template <class Receiver>
      double getTime(Receiver *recv) throw(Exception) {
        double val;
        OfxStatus stat = mSuite->getTime(recv->handle(), &val);
        if (stat != kOfxStatOK) {
          throw Exception(stat, "ofx::TimeLine::getTime");
        }
        return val;
      }
      
      /** Set current time
       *  \param[in] recv Object to set time for.\n
       *              Must be an object having a "handle" method.
       *  \param[in] t The time.
       */
      template <class Receiver>
      void gotoTime(Receiver *recv, double t) throw(Exception) {
        OfxStatus stat = mSuite->gotoTime(recv->handle(), t);
        if (stat != kOfxStatOK) {
          throw Exception(stat, "ofx::TimeLine::gotoTime");
        }
      }
      
      /** Get time line range.
       *  \param[in] recv Object to get range for.\n
       *                  Must be an object having a "handle" method.
       *  \return Time line range
       */
      template <class Receiver>
      FrameRange getTimeBounds(Receiver *recv) throw(Exception) {
        FrameRange r = {0, 0};
        OfxStatus stat = mSuite->getTimeBounds(recv->handle(), &(r.min), &(r.max));
        if (stat != kOfxStatOK) {
          throw Exception(stat, "ofx::TimeLine::getTimeBounds");
        }
        return r;
      }
      
  };
}

#endif
