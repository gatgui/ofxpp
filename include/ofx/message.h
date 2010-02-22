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

#ifndef __ofx_message_h__
#define __ofx_message_h__

#include <ofxCore.h>
#include <ofxMessage.h>
#include <ofx/exception.h>
#include <ofx/ofx.h>
#include <cstdarg>

namespace ofx {
  
  class Host;
  
  class Message {
    public:
      
      Message(Host *h) throw(Exception);
      ~Message();
      
      template <class Receiver>
      void sendTo(Receiver *recv,
                  MessageType type,
                  const char *id,
                  const char *format, ...) throw(Exception) {
        va_list args;
        char dummy;
        char buffer[8192];
        
        va_start(args, format);
        vsnprintf(buffer, 8192, format, args);
        va_end(args);
        
        OfxStatus stat = mSuite->message(recv->handle(), MessageTypeToString(type), id, buffer);  
        
        if (stat != kOfxStatOK) {
          throw Exception(stat, "ofx::Message::sendTo");
        }
      }
      
    protected:
      
      OfxMessageSuiteV1 *mSuite;
  };
  
}

#endif
