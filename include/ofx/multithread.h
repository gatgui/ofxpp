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

#ifndef __ofx_multithread_h__
#define __ofx_multithread_h__

#include <ofxCore.h>
#include <ofxMultiThread.h>
#include <ofx/exception.h>
#include <vector>

#ifdef _MSC_VER
# pragma warning(disable:4290)
#endif

namespace ofx {
  
  class Host;
  
  typedef const OfxMutexHandle Mutex;
  
  typedef OfxThreadFunctionV1 ThreadFunction;
  
  class Thread {
    public:
      
      static void Main(unsigned int i, unsigned int n, void *data) {
        Thread **threads = (Thread**) data;
        if (i < n) {
          threads[i]->run();
        }
      }
      
      Thread();
      virtual ~Thread();
      
      virtual void run() = 0;
  };
  
  class MultiThread {
    protected:
      
      OfxMultiThreadSuiteV1 *mSuite;
      
    public:
      
      MultiThread(Host *h) throw(Exception);
      ~MultiThread();
      
      unsigned int numCPUs() throw(Exception);
      unsigned int index() throw(Exception);
      bool isSpawned();
      
      Mutex createMutex(int lockCount=0) throw(Exception);
      void destroyMutex(Mutex mutex);
      void lock(Mutex mutex) throw(Exception);
      void unlock(Mutex mutex) throw(Exception);
      bool tryLock(Mutex mutex) throw(Exception);
      
      void run(ThreadFunction func, unsigned int nThreads, void *userData) throw(Exception);
      void run(Thread **threads, unsigned int nThreads) throw(Exception);
      
  };
  
}

#endif
