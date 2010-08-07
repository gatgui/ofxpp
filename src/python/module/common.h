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

#ifndef __pyofx_common_h__
#define __pyofx_common_h__

#include <Python.h>
#include <structmember.h>
#include <ofx/host.h>
#include <ofx/exception.h>
#include <ofx/message.h>
#include <ofx/memory.h>
#include <ofx/progress.h>
#include <ofx/timeline.h>
#include <ofx/property.h>
#include <ofx/parameter.h>
#include <ofx/parameterset.h>
#include <iostream>

typedef struct {
  PyBaseExceptionObject base;
  PyObject *status;
} PyOFXException;

typedef struct {
  PyObject_HEAD
  void *handle;
} PyOFXHandle;

typedef struct {
  PyObject_HEAD
  ofx::MessageSuite *suite;
} PyOFXMessageSuite;

typedef struct {
  PyObject_HEAD
  ofx::MemorySuite *suite;
} PyOFXMemorySuite;

// Do no expose MultiThreadSuite

typedef struct {
  PyObject_HEAD
  ofx::ProgressSuite *suite;
} PyOFXProgressSuite;

typedef struct {
  PyObject_HEAD
  ofx::TimeLineSuite *suite;
} PyOFXTimeLineSuite;

typedef struct {
  PyObject_HEAD
  ofx::PropertySet *pset;
} PyOFXPropertySet;

typedef struct {
  PyObject_HEAD
  ofx::ParameterDescriptor *desc;
} PyOFXParameterDescriptor;

typedef struct {
  PyOFXParameterDescriptor base;
} PyOFXValueParameterDescriptor;

typedef struct {
  PyObject_HEAD
  ofx::Parameter *param;
} PyOFXParameter;

typedef struct {
  PyOFXParameter base;
} PyOFXValueParameter;

typedef struct {
  PyObject_HEAD
  ofx::Host *host;
} PyOFXHost;

typedef struct {
  PyOFXHost host;
} PyOFXImageEffectHost;


extern PyTypeObject PyOFXExceptionType;
extern PyTypeObject PyOFXFailedErrorType;
extern PyTypeObject PyOFXFatalErrorType;
extern PyTypeObject PyOFXUnknownErrorType;
extern PyTypeObject PyOFXMissingHostFeatureErrorType;
extern PyTypeObject PyOFXUnsupportedErrorType;
extern PyTypeObject PyOFXExistsErrorType;
extern PyTypeObject PyOFXFormatErrorType;
extern PyTypeObject PyOFXMemoryErrorType;
extern PyTypeObject PyOFXBadHandleErrorType;
extern PyTypeObject PyOFXBadIndexErrorType;
extern PyTypeObject PyOFXValueErrorType;
extern PyTypeObject PyOFXHostType;
extern PyTypeObject PyOFXImageEffectHostType;
extern PyTypeObject PyOFXMessageSuiteType;
extern PyTypeObject PyOFXMemorySuiteType;
extern PyTypeObject PyOFXProgressSuiteType;
extern PyTypeObject PyOFXTimeLineSuiteType;
extern PyTypeObject PyOFXPropertySetType;
extern PyTypeObject PyOFXHandleType;
extern PyTypeObject PyOFXParameterDescriptorType;
extern PyTypeObject PyOFXValueParameterDescriptorType;
extern PyTypeObject PyOFXParameterType;
extern PyTypeObject PyOFXValueParameterType;


class Receiver
{
  public:
    
    inline Receiver(PyObject *prcv)
      : mRcv(prcv)
    {
      if (mRcv)
      {
        Py_INCREF(mRcv);
      }
    }
    
    inline ~Receiver()
    {
      if (mRcv)
      {
        Py_DECREF(mRcv);
      }
    }
    
    inline void* getHandle()
    {
      void *rv = 0;
      if (mRcv)
      {
        if (PyObject_HasAttrString(mRcv, "handle"))
        {
          PyObject *phdl = PyObject_GetAttrString(mRcv, "handle");
          if (phdl && PyObject_TypeCheck(phdl, &PyOFXHandleType))
          {
            rv = ((PyOFXHandle*)phdl)->handle;
          }
          Py_DECREF(phdl);
        }
      }
      return rv;
    }
  
  protected:
    
    PyObject *mRcv;
};

/*
class PyPlugin : public Plugin
{
  public:
    
    PyPlugin()
      : mSelf(0)
    {
    }
    
    virtual ~PyPlugin()
    {
      if (mSelf != 0)
      {
        Py_DECREF(mSelf);
      }
    }
  
    void setSelf(PyObject *self)
    {
      if (mSelf != 0)
      {
        Py_DECREF(mSelf);
        mSelf = 0;
      }
      mSelf = self;
      if (mSelf != 0)
      {
        Py_INCREF(mSelf);
      }
    }
  
  protected:
    
    PyObject *mSelf;
};

class PyImageEffectPlugin : public PyPlugin
{
  // -> roughly copy/paste ImageEffectPlugin template class content
  //    with a little adaptation
  public:
    
    PyImageEffectPlugin()
    {
    }
    
    virtual ~PyImageEffectPlugin()
    {
    }
    
    virtual OfxStatus load()
    {
      if (!mSelf)
      {
        return kOfxStatFailed;
      }
      PyObject *rv = PyObject_CallMethod(mSelf, "load", NULL);
      return OfxStatus(PyInt_AsLong(rv));
    }
    
    virtual OfxStatus unload()
    {
      if (!mSelf)
      {
        return kOfxStatFailed;
      }
      PyObject *rv = PyObject_CallMethod(mSelf, "load", NULL);
      return OfxStatus(PyInt_AsLong(rv));
    }
    
  protected:
    
    // this will hold a second OfxPlugin
    // also this is the one that will get deleted by the main function
    // that sucks a little
    ImageEffectPlugin<PyImageEffectDescriptor, PyImageEffect> *mCorePlugin;
};
*/

extern bool PyOFX_InitException(PyObject *mod);
extern bool PyOFX_InitTest(PyObject *mod);
extern bool PyOFX_InitHost(PyObject *mod);
extern bool PyOFX_InitMessage(PyObject *mod);
extern bool PyOFX_InitMemory(PyObject *mod);
extern bool PyOFX_InitProgress(PyObject *mod);
extern bool PyOFX_InitTimeLine(PyObject *mod);
extern bool PyOFX_InitHandle(PyObject *mod);
extern bool PyOFX_InitProperty(PyObject *mod);
extern bool PyOFX_InitParameter(PyObject *mod);


#define CATCH(code, failed)\
  failed = true;\
  try {\
    code;\
    failed = false;\
  } catch (ofx::FailedError &e) {\
    PyErr_SetString((PyObject*)&PyOFXFailedErrorType, e.what());\
  } catch (ofx::FatalError &e) {\
    PyErr_SetString((PyObject*)&PyOFXFatalErrorType, e.what());\
  } catch (ofx::UnknownError &e) {\
    PyErr_SetString((PyObject*)&PyOFXUnknownErrorType, e.what());\
  } catch (ofx::MissingHostFeatureError &e) {\
    PyErr_SetString((PyObject*)&PyOFXMissingHostFeatureErrorType, e.what());\
  } catch (ofx::UnsupportedError &e) {\
    PyErr_SetString((PyObject*)&PyOFXUnsupportedErrorType, e.what());\
  } catch (ofx::FormatError &e) {\
    PyErr_SetString((PyObject*)&PyOFXFormatErrorType, e.what());\
  } catch (ofx::MemoryError &e) {\
    PyErr_SetString((PyObject*)&PyOFXMemoryErrorType, e.what());\
  } catch (ofx::ExistsError &e) {\
    PyErr_SetString((PyObject*)&PyOFXExistsErrorType, e.what());\
  } catch (ofx::ValueError &e) {\
    PyErr_SetString((PyObject*)&PyOFXValueErrorType, e.what());\
  } catch (ofx::BadIndexError &e) {\
    PyErr_SetString((PyObject*)&PyOFXBadIndexErrorType, e.what());\
  } catch (ofx::BadHandleError &e) {\
    PyErr_SetString((PyObject*)&PyOFXBadHandleErrorType, e.what());\
  } catch (std::exception &e) {\
    PyErr_SetString(PyExc_RuntimeError, e.what());\
  }


#define INIT_TYPE(ptype, name, ctype)\
  memset(&ptype, 0, sizeof(PyTypeObject));\
  ptype.ob_refcnt = 1;\
  ptype.ob_size = 0;\
  ptype.tp_name = name;\
  ptype.tp_basicsize = sizeof(ctype)

#endif
