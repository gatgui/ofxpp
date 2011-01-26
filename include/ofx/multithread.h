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

/** \file multithread.h
 *  Multithread suite functions wrapper.
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
  
  //! Mutex type.
  typedef OfxMutexHandle Mutex;
  
  //! %Thread function prototype.
  typedef OfxThreadFunctionV1 ThreadFunction;
  
  //! Helper thread class.
  class Thread {
    public:
      
      //! %Thread entry point function.
      static void Main(unsigned int i, unsigned int n, void *data) {
        Thread **threads = (Thread**) data;
        if (i < n) {
          threads[i]->run();
        }
      }
      
      Thread();
      virtual ~Thread();
      
      //! %Thread run function to override.
      virtual void run() = 0;
  };
  
  //! Multithread suite wrapper class.
  class MultiThreadSuite {
    protected:
      
      OfxMultiThreadSuiteV1 *mSuite;
      
    public:
      
      MultiThreadSuite(Host *h) throw(Exception);
      ~MultiThreadSuite();
      
      //! Get the number of physical CPUs.
      unsigned int numCPUs() throw(Exception);
      //! Get the index of current thread.
      unsigned int index() throw(Exception);
      //! Check if current thread has been spawned by the multithead suite "run" function.
      bool isSpawned();
      
      /** Create a new mutex
       *  \param[in] lockCount Initial lock count.
       */
      Mutex createMutex(int lockCount=0) throw(Exception);
      //! Destroy mutex.
      void destroyMutex(Mutex mutex);
      //! Lock given mutex.
      void lock(Mutex mutex) throw(Exception);
      //! Unlock given mutex.
      void unlock(Mutex mutex) throw(Exception);
      /** Try lock given mutex.
       *  \return true if mutex could be locked, false otherwise.
       */
      bool tryLock(Mutex mutex) throw(Exception);
      
      /** Spawn a new set of threads 
       *  \param[in] func Function to run in threads.
       *  \param[in] nThreads Number of threads to spawn.
       *  \param[in] userData Opaque user data to be passed down to the thread function.
       */
      void run(ThreadFunction func, unsigned int nThreads, void *userData) throw(Exception);
      /** Spawn a new set of threads 
       *  \param[in] threads Array of Thread objects.
       *  \param[in] nThreads Number of threads to spawn.
       */
      void run(Thread **threads, unsigned int nThreads) throw(Exception);
      
  };
  
}

#endif
