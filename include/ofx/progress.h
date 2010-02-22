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

#ifndef __ofx_progress_h__
#define __ofx_progress_h__

#include <ofxCore.h>
#include <ofxProgress.h>
#include <ofx/exception.h>

namespace ofx {
  
  class Host;
  
  class Progress {
    protected:
      
      OfxProgressSuiteV1 *mSuite;
      
    public:
      
      Progress(Host *h) throw(Exception);
      ~Progress();
      
      template <class Receiver>
      void start(Receiver *recv, const std::string &label) throw(Exception) {
        OfxStatus stat = mSuite->progressStart(recv->handle(), label.c_str());
        if (stat != kOfxStatOK) {
          throw Exception(stat, "ofx::Progress::start");
        }
      }
      
      template <class Receiver>
      void update(Receiver *recv, double progress) throw(Exception) {
        OfxStatus stat = mSuite->progressUpdate(recv->handle(), progress);
        if (stat != kOfxStatOK) {
          throw Exception(stat, "ofx::Progress::Update");
        }
      }
      
      template <class Receiver>
      void end(Receiver *recv) throw(Exception) {
        OfxStatus stat = mSuite->progressEnd(recv->handle());
        if (stat != kOfxStatOK) {
          throw Exception(stat, "ofx::Progress::End");
        }
      }
      
  };
  
}

#endif
