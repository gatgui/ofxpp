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

/** \file message.h
 *  Message suite wrapper.
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
  
  //! Message suite wrapper class.
  class MessageSuite {
    public:
      
      MessageSuite(Host *h) throw(Exception);
      ~MessageSuite();
      
      /** Send a transient message to the host.
       *  \param recv Object to associate with the message.\n
       *              Must be a class having a "handle" method.
       *  \param type The message type.
       *  \param id ID to associate with the message or NULL.
       *  \param format Format string.
       *  \return true or false for MessageTypeQuestion, true for any other type.
       */
      template <class Receiver>
      bool message(Receiver *recv,
                   MessageType type,
                   const char *id,
                   const char *format, ...) throw(Exception) {
        va_list args;
        char buffer[8192];
        
        va_start(args, format);
        vsnprintf(buffer, 8192, format, args);
        va_end(args);
        
        OfxStatus stat = mSuite->message(recv->handle(), MessageTypeToString(type), id, buffer);  
        
        if (stat == kOfxStatReplyYes) {
          return true;
        } else if (stat == kOfxStatReplyNo) {
          return false;
        } else if (stat != kOfxStatOK) {
          throw Exception(stat, "ofx::Message::message");
        }
        return true;
      }
      
#ifdef OFX_API_1_2
      /** Set a persistent message.
       *  \param recv Object to associate with the message.\n
       *              Must be a class having a "handle" method.
       *  \param type The message type.
       *  \param id ID to associate with the message or NULL.
       *  \param format Format string.
       *  \note OpenFX API version must be at least 1.2
       */
      template <class Receiver>
      void setPersistentMessage(Receiver *recv,
                                MessageType type,
                                const char *id,
                                const char *format, ...) throw(Exception) {
        
        if (!mSuite2) {
          // client built using OpenFX api 1.2 or above doesn't necessarily means
          // the host supports it
          throw MissingHostFeatureError("Message suite v2");
        }
        
        va_list args;
        char buffer[8192];
        
        va_start(args, format);
        vsnprintf(buffer, 8192, format, args);
        va_end(args);
        
        OfxStatus stat = mSuite2->setPersistentMessage(recv->handle(), MessageTypeToString(type), id, buffer);
        
        if (stat != kOfxStatOK) {
          throw Exception(stat, "ofx::Message::setPersistentMessage");
        }
      }
      
      /** Clear persistent message.
       *  \param recv Object to remove the persistent message for.\n
       *              Must be a class having a "handle" method.
       *  \note OpenFX API version must be at least 1.2
       */
      template <class Receiver>
      void clearPersistentMessage(Receiver *recv) {
        if (!mSuite2) {
          throw MissingHostFeatureError("Message suite v2");
        }
        
        OfxStatus stat = mSuite2->clearPersistentMessage(recv->handle());
        
        if (stat != kOfxStatOK) {
          throw Exception(stat, "ofx::Message::clearPersistentMessage");
        }
      }
#endif
      
    protected:
      
      OfxMessageSuiteV1 *mSuite;
      
#ifdef OFX_API_1_2
      OfxMessageSuiteV2 *mSuite2;
#endif
  };
  
}

#endif
