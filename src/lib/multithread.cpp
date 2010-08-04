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

#include <ofx/multithread.h>
#include <ofx/host.h>

namespace ofx {

Thread::Thread() {
}

Thread::~Thread() {
}

// ---


MultiThreadSuite::MultiThreadSuite(Host *h) throw(Exception) {
  if (!h) {
    throw BadHandleError("Cannot initialize ofx::Threads: invalid host");
  }
  mSuite = h->fetchSuite<OfxMultiThreadSuiteV1>(kOfxMultiThreadSuite, 1);
  if (!mSuite) {
    throw MissingHostFeatureError("Multithread suite");
    return;
  }
}

MultiThreadSuite::~MultiThreadSuite() {
}

unsigned int MultiThreadSuite::numCPUs() throw(Exception) {
  unsigned int n;
  OfxStatus stat = mSuite->multiThreadNumCPUs(&n);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Threads::numCPUs");
  }
  return n;
}

unsigned int MultiThreadSuite::index() throw(Exception) {
  unsigned int i;
  OfxStatus stat = mSuite->multiThreadIndex(&i);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Threads::index");
  }
  return i;
}

bool MultiThreadSuite::isSpawned() {
  return (mSuite->multiThreadIsSpawnedThread() == 1);
}

void MultiThreadSuite::run(ThreadFunction func, unsigned int nThreads, void *userData) throw(Exception) {
  OfxStatus stat = mSuite->multiThread(func, nThreads, userData);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Threads::run");
  }
}

void MultiThreadSuite::run(Thread **threads, unsigned int nThreads) throw(Exception) {
  run(Thread::Main, nThreads, (void*)threads);
}

Mutex MultiThreadSuite::createMutex(int lockCount) throw(Exception) {
  Mutex m = 0;
  OfxStatus stat = mSuite->mutexCreate(&m, lockCount);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::MultiThread::createMutex");
  }
  return m;
}

void MultiThreadSuite::lock(Mutex mutex) throw(Exception) {
  OfxStatus stat = mSuite->mutexLock(mutex);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::MultiThread::lock");
  }
}

void MultiThreadSuite::unlock(Mutex mutex) throw(Exception) {
  OfxStatus stat = mSuite->mutexUnLock(mutex);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::MultiThread::unLock");
  }
}

bool MultiThreadSuite::tryLock(Mutex mutex) throw(Exception) {
  OfxStatus stat = mSuite->mutexTryLock(mutex);
  if (stat == kOfxStatFailed) {
    return false;
  } else if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::MultiThread::tryLock");
  }
  return true;
}

void MultiThreadSuite::destroyMutex(Mutex mutex) {
  mSuite->mutexDestroy(mutex);
}


}
