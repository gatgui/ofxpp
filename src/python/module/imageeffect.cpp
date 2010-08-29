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

#include "common.h"
#include "entrypoints.h"

PyTypeObject PyOFXImageEffectDescriptorType;
PyTypeObject PyOFXImageEffectType;
PyTypeObject PyOFXInputClipPreferencesType;
PyTypeObject PyOFXOutputClipPreferencesType;

// ---

PyImageEffectDescriptor::PyImageEffectDescriptor()
  : ofx::ImageEffectDescriptor(), mSelf(0)
{
  ofx::Log("Create empty PyImageEffectDescriptor");
}

PyImageEffectDescriptor::PyImageEffectDescriptor(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl) throw(ofx::Exception)
  : ofx::ImageEffectDescriptor(h, hdl), mSelf(0)
{
  ofx::Log("Create PyImageEffectDescriptor"); 
}

PyImageEffectDescriptor::PyImageEffectDescriptor(const PyImageEffectDescriptor &rhs)
  : ofx::ImageEffectDescriptor(rhs), mSelf(rhs.mSelf)
{
  ofx::Log("Create copy PyImageEffectDescriptor");
  if (mSelf != 0)
  {
    Py_INCREF(mSelf);
  }
}

PyImageEffectDescriptor::~PyImageEffectDescriptor()
{
  ofx::Log("Delete PyImageEffectDescriptor");
  self(0);
}

PyImageEffectDescriptor& PyImageEffectDescriptor::operator=(const PyImageEffectDescriptor &rhs)
{
  ofx::ImageEffectDescriptor::operator=(rhs);
  self(rhs.self());
  return *this;
}

OfxStatus PyImageEffectDescriptor::describe()
{
  ofx::Log("PyImageEffectDescriptor::describe");
  
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "describe");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *rv = PyObject_CallObject(meth, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
          // no threading in python
          hostFrameThreading(false);
          renderThreadSafety(ofx::RenderThreadUnsafe);
        }
        else
        {
          ofx::Log("PyImageEffectDescriptor::describe: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffectDescriptor::describe();
}

OfxStatus PyImageEffectDescriptor::describeInContext(ofx::ImageEffectContext ctx)
{
  ofx::Log("PyImageEffectDescriptor::describeInContext");
  
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "describeInContext");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *args = Py_BuildValue("(i)", int(ctx));
      PyObject *rv = PyObject_Call(meth, args, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
        }
        else
        {
          ofx::Log("PyImageEffectDescriptor::describeInContext: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(args);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffectDescriptor::describeInContext(ctx);
}

// ---

PyImageEffect::PyImageEffect()
  : ofx::ImageEffect(), mSelf(0)
{
}

PyImageEffect::PyImageEffect(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl)
  : ofx::ImageEffect(h, hdl), mSelf(0)
{
}

PyImageEffect::~PyImageEffect()
{
  self(0);
}

OfxStatus PyImageEffect::beginInstanceChanged(ofx::ChangeReason reason)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "beginInstanceChanged");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *args = Py_BuildValue("(i)", int(reason));
      PyObject *rv = PyObject_Call(meth, args, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
        }
        else
        {
          ofx::Log("PyImageEffect::beginInstanceChanged: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(args);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::beginInstanceChanged(reason);
}

OfxStatus PyImageEffect::endInstanceChanged(ofx::ChangeReason reason)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "endInstanceChanged");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *args = Py_BuildValue("(i)", int(reason));
      PyObject *rv = PyObject_Call(meth, args, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
        }
        else
        {
          ofx::Log("PyImageEffect::endInstanceChanged: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(args);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::endInstanceChanged(reason);
}

OfxStatus PyImageEffect::instanceChanged(ofx::ImageEffect::InstanceChangedArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "instanceChanged");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyOFXActionArgumentsType, NULL);
      PyObject *oarg;
      PyObject *aname;
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      aname = PyString_FromString("renderScaleX");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      aname = PyString_FromString("renderScaleY");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyFloat_FromDouble(args.time);
      aname = PyString_FromString("time");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyInt_FromLong(args.type);
      aname = PyString_FromString("type");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyString_FromString(args.name.c_str());
      aname = PyString_FromString("name");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyInt_FromLong(args.reason);
      aname = PyString_FromString("reason");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      PyObject *pyargs = Py_BuildValue("(O)", oargs);
      
      PyObject *rv = PyObject_Call(meth, pyargs, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
        }
        else
        {
          ofx::Log("PyImageEffect::instanceChanged: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(oargs);
      Py_DECREF(pyargs);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::instanceChanged(args);
}

OfxStatus PyImageEffect::purgeCaches()
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "purgeCaches");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *rv = PyObject_CallObject(meth, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
        }
        else
        {
          ofx::Log("PyImageEffect::purgeCaches: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::purgeCaches();
}

OfxStatus PyImageEffect::syncPrivateData()
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "syncPrivateData");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *rv = PyObject_CallObject(meth, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
        }
        else
        {
          ofx::Log("PyImageEffect::syncPrivateData: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::syncPrivateData();
}

OfxStatus PyImageEffect::beginInstanceEdit()
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "beginInstanceEdit");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *rv = PyObject_CallObject(meth, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
        }
        else
        {
          ofx::Log("PyImageEffect::beginInstanceEdit: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::beginInstanceEdit();
}

OfxStatus PyImageEffect::endInstanceEdit()
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "endInstanceEdit");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *rv = PyObject_CallObject(meth, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
        }
        else
        {
          ofx::Log("PyImageEffect::endInstanceEdit: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::endInstanceEdit();
}

OfxStatus PyImageEffect::getRegionOfDefinition(ofx::ImageEffect::GetRoDArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "getRegionOfDefinition");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyOFXActionArgumentsType, NULL);
      PyObject *oarg;
      PyObject *aname;
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      aname = PyString_FromString("renderScaleX");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      aname = PyString_FromString("renderScaleY");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyFloat_FromDouble(args.time);
      aname = PyString_FromString("time");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      aname = PyString_FromString("RoD");
      PyObject_GenericSetAttr(oargs, aname, Py_None);
      Py_DECREF(aname);
      
      PyObject *pyargs = Py_BuildValue("(O)", oargs);
      
      PyObject *rv = PyObject_Call(meth, pyargs, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
          
          if (stat == kOfxStatOK)
          {
            PyObject *rod = PyObject_GetAttrString(oargs, "RoD");
            
            if (rod && PyTuple_Check(rod) && PyTuple_Size(rod) == 4)
            {
              args.RoD.x1 = PyFloat_AsDouble(PyTuple_GetItem(rod, 0));
              args.RoD.y1 = PyFloat_AsDouble(PyTuple_GetItem(rod, 1));
              args.RoD.x2 = PyFloat_AsDouble(PyTuple_GetItem(rod, 2));
              args.RoD.y2 = PyFloat_AsDouble(PyTuple_GetItem(rod, 3));
            }
            else
            {
              stat = kOfxStatFailed;
            }
            
            Py_XDECREF(rod);
          }
        }
        else
        {
          ofx::Log("PyImageEffect::getRegionOfDefinition: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(oargs);
      Py_DECREF(pyargs);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::getRegionOfDefinition(args);
}

OfxStatus PyImageEffect::getRegionsOfInterest(ofx::ImageEffect::GetRoIArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "getRegionsOfInterest");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyOFXActionArgumentsType, NULL);
      PyObject *oarg;
      PyObject *aname;
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      aname = PyString_FromString("renderScaleX");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      aname = PyString_FromString("renderScaleY");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyFloat_FromDouble(args.time);
      aname = PyString_FromString("time");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      aname = PyString_FromString("outRoI");
      PyObject_GenericSetAttr(oargs, aname, Py_None);
      Py_DECREF(aname);
      
      PyObject *inRoIs = PyDict_New();
      aname = PyString_FromString("inRoIs");
      PyObject_GenericSetAttr(oargs, aname, inRoIs);
      Py_DECREF(inRoIs);
      Py_DECREF(aname);
      
      PyObject *pyargs = Py_BuildValue("(O)", oargs);
      
      PyObject *rv = PyObject_Call(meth, pyargs, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
          
          if (stat == kOfxStatOK)
          {
            PyObject *outRoI = PyObject_GetAttrString(oargs, "outRoI");
            inRoIs = PyObject_GetAttrString(oargs, "inRoIs");
            
            if (outRoI && PyTuple_Check(outRoI) && PyTuple_Size(outRoI) == 4)
            {
              args.outRoI.x1 = PyFloat_AsDouble(PyTuple_GetItem(outRoI, 0));
              args.outRoI.y1 = PyFloat_AsDouble(PyTuple_GetItem(outRoI, 1));
              args.outRoI.x2 = PyFloat_AsDouble(PyTuple_GetItem(outRoI, 2));
              args.outRoI.y2 = PyFloat_AsDouble(PyTuple_GetItem(outRoI, 3));
            }
            else
            {
              stat = kOfxStatFailed;
            }
            
            if (stat == kOfxStatOK && inRoIs && PyDict_Check(inRoIs))
            {
              Py_ssize_t idx = 0;
              PyObject *key = 0, *val = 0;
              ofx::Rect<double> RoI;
              char *name = 0;
              
              while (PyDict_Next(inRoIs, &idx, &key, &val))
              {
                if (!PyString_Check(key) || !PyTuple_Check(val) || PyTuple_Size(val) != 4)
                {
                  continue;
                }
                
                name = PyString_AsString(key);
                
                RoI.x1 = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
                RoI.y1 = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
                RoI.x2 = PyFloat_AsDouble(PyTuple_GetItem(val, 2));
                RoI.y2 = PyFloat_AsDouble(PyTuple_GetItem(val, 3));
                
                args.inRoIs[name] = RoI;
              }
            }
            else
            {
              stat = kOfxStatFailed;
            }
            
            Py_XDECREF(outRoI);
            Py_XDECREF(inRoIs);
          }
        }
        else
        {
          ofx::Log("PyImageEffect::getRegionsOfInterest: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(oargs);
      Py_DECREF(pyargs);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::getRegionsOfInterest(args);
}

OfxStatus PyImageEffect::getFramesNeeded(ofx::ImageEffect::GetFramesNeededArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "getFramesNeeded");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyOFXActionArgumentsType, NULL);
      PyObject *oarg;
      PyObject *aname;
      
      oarg = PyFloat_FromDouble(args.time);
      aname = PyString_FromString("time");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      PyObject *inRanges = PyDict_New();
      aname = PyString_FromString("inRanges");
      PyObject_GenericSetAttr(oargs, aname, inRanges);
      Py_DECREF(inRanges);
      Py_DECREF(aname);
      
      PyObject *pyargs = Py_BuildValue("(O)", oargs);
      
      PyObject *rv = PyObject_Call(meth, pyargs, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
          
          if (stat == kOfxStatOK)
          {
            inRanges = PyObject_GetAttrString(oargs, "inRanges");
            
            if (inRanges && PyDict_Check(inRanges))
            {
              Py_ssize_t idx = 0;
              PyObject *key = 0, *val = 0, *range = 0;
              char *name = 0;
              ofx::FrameRange frange;
              
              while (PyDict_Next(inRanges, &idx, &key, &val))
              {
                if (!PyString_Check(key) || !PyList_Check(val))
                {
                  continue;
                }
                
                name = PyString_AsString(key);
                
                Py_ssize_t n = PyList_Size(val);
                for (Py_ssize_t i=0; i<n; ++i)
                {
                  range = PyList_GetItem(val, i);
                  if (!PyTuple_Check(range) || PyTuple_Size(range) != 2)
                  {
                    continue;
                  }
                  frange.min = PyFloat_AsDouble(PyTuple_GetItem(range, 0));
                  frange.max = PyFloat_AsDouble(PyTuple_GetItem(range, 1));
                  args.inRanges[name].push_back(frange);
                }
              }
            }
            else
            {
              stat = kOfxStatFailed;
            }
            
            Py_XDECREF(inRanges);
          }
        }
        else
        {
          ofx::Log("PyImageEffect::getFramesNeeded: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(oargs);
      Py_DECREF(pyargs);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::getFramesNeeded(args);
}

OfxStatus PyImageEffect::isIdentity(ofx::ImageEffect::IsIdentityArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "isIdentity");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyOFXActionArgumentsType, NULL);
      PyObject *oarg;
      PyObject *aname;
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      aname = PyString_FromString("renderScaleX");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      aname = PyString_FromString("renderScaleY");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyFloat_FromDouble(args.time);
      aname = PyString_FromString("time");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyInt_FromLong(args.field);
      aname = PyString_FromString("field");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyTuple_New(4);
      PyTuple_SetItem(oarg, 0, PyInt_FromLong(args.renderWindow.x1));
      PyTuple_SetItem(oarg, 1, PyInt_FromLong(args.renderWindow.y1));
      PyTuple_SetItem(oarg, 2, PyInt_FromLong(args.renderWindow.x2));
      PyTuple_SetItem(oarg, 3, PyInt_FromLong(args.renderWindow.y2));
      aname = PyString_FromString("renderWindow");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
#ifdef OFX_API_1_2
      oarg = (args.sequentialRender ? Py_True : Py_False);
      aname = PyString_FromString("sequentialRender");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(aname);
      
      oarg = (args.interactiveRender ? Py_True : Py_False);
      aname = PyString_FromString("interactiveRender");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(aname);
#endif
      
      aname = PyString_FromString("idClip");
      PyObject_GenericSetAttr(oargs, aname, Py_None);
      Py_DECREF(aname);
      
      aname = PyString_FromString("idTime");
      PyObject_GenericSetAttr(oargs, aname, Py_None);
      Py_DECREF(aname);
      
      PyObject *pyargs = Py_BuildValue("(O)", oargs);
      
      PyObject *rv = PyObject_Call(meth, pyargs, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
          
          if (stat == kOfxStatOK)
          {
            ofx::Log("PyImageEffect::isIdentity: Set return arguments");
            
            PyObject *ic = PyObject_GetAttrString(oargs, "idClip");
            
            if (ic && PyString_Check(ic))
            {
              args.idClip = PyString_AsString(ic);
            }
            else
            {
              stat = kOfxStatFailed;
            }
            
            PyObject *it = PyObject_GetAttrString(oargs, "idTime");
            
            if (stat == kOfxStatOK && it && PyFloat_Check(it))
            {
              args.idTime = PyFloat_AsDouble(it);
            }
            else
            {
              stat = kOfxStatFailed;
            }
            
            Py_XDECREF(ic);
            Py_XDECREF(it);
          }
        }
        else
        {
          ofx::Log("PyImageEffect::isIdentity: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(oargs);
      Py_DECREF(pyargs);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::isIdentity(args);
}

OfxStatus PyImageEffect::render(ofx::ImageEffect::RenderArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "render");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyOFXActionArgumentsType, NULL);
      PyObject *oarg;
      PyObject *aname;
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      aname = PyString_FromString("renderScaleX");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      aname = PyString_FromString("renderScaleY");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyFloat_FromDouble(args.time);
      aname = PyString_FromString("time");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyInt_FromLong(args.field);
      aname = PyString_FromString("field");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyTuple_New(4);
      PyTuple_SetItem(oarg, 0, PyInt_FromLong(args.renderWindow.x1));
      PyTuple_SetItem(oarg, 1, PyInt_FromLong(args.renderWindow.y1));
      PyTuple_SetItem(oarg, 2, PyInt_FromLong(args.renderWindow.x2));
      PyTuple_SetItem(oarg, 3, PyInt_FromLong(args.renderWindow.y2));
      aname = PyString_FromString("renderWindow");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
#ifdef OFX_API_1_2
      oarg = (args.sequentialRender ? Py_True : Py_False);
      aname = PyString_FromString("sequentialRender");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(aname);
      
      oarg = (args.interactiveRender ? Py_True : Py_False);
      aname = PyString_FromString("interactiveRender");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(aname);
#endif
      
      PyObject *pyargs = Py_BuildValue("(O)", oargs);
      
      PyObject *rv = PyObject_Call(meth, pyargs, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
        }
        else
        {
          ofx::Log("PyImageEffect::render: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(oargs);
      Py_DECREF(pyargs);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::render(args);
}

OfxStatus PyImageEffect::beginSequenceRender(ofx::ImageEffect::BeginSequenceArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "beginSequenceRender");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyOFXActionArgumentsType, NULL);
      PyObject *oarg;
      PyObject *aname;
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      aname = PyString_FromString("renderScaleX");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      aname = PyString_FromString("renderScaleY");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = (args.interactive ? Py_True : Py_False);
      aname = PyString_FromString("interactive");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(aname);
      
#ifdef OFX_API_1_2
      oarg = (args.sequentialRender ? Py_True : Py_False);
      aname = PyString_FromString("sequentialRender");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(aname);
      
      oarg = (args.interactiveRender ? Py_True : Py_False);
      aname = PyString_FromString("interactiveRender");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(aname);
#endif
      
      oarg = PyTuple_New(2);
      PyTuple_SetItem(oarg, 0, PyFloat_FromDouble(args.range.min));
      PyTuple_SetItem(oarg, 1, PyFloat_FromDouble(args.range.max));
      aname = PyString_FromString("range");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyFloat_FromDouble(args.step);
      aname = PyString_FromString("step");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      PyObject *pyargs = Py_BuildValue("(O)", oargs);
      
      PyObject *rv = PyObject_Call(meth, pyargs, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
        }
        else
        {
          ofx::Log("PyImageEffect::beginSequenceRender: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(oargs);
      Py_DECREF(pyargs);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::beginSequenceRender(args);
}

OfxStatus PyImageEffect::endSequenceRender(ofx::ImageEffect::EndSequenceArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "endSequenceRender");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyOFXActionArgumentsType, NULL);
      PyObject *oarg;
      PyObject *aname;
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      aname = PyString_FromString("renderScaleX");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      aname = PyString_FromString("renderScaleY");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = (args.interactive ? Py_True : Py_False);
      aname = PyString_FromString("interactive");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(aname);
      
#ifdef OFX_API_1_2
      oarg = (args.sequentialRender ? Py_True : Py_False);
      aname = PyString_FromString("sequentialRender");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(aname);
      
      oarg = (args.interactiveRender ? Py_True : Py_False);
      aname = PyString_FromString("interactiveRender");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(aname);
#endif
      
      PyObject *pyargs = Py_BuildValue("(O)", oargs);
      
      PyObject *rv = PyObject_Call(meth, pyargs, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
        }
        else
        {
          ofx::Log("PyImageEffect::endSequenceRender: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(oargs);
      Py_DECREF(pyargs);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::endSequenceRender(args);
}

OfxStatus PyImageEffect::getClipPreferences(ofx::ImageEffect::GetClipPrefArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "getClipPreferences");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyOFXActionArgumentsType, NULL);
      PyObject *oarg;
      PyObject *aname;
      
      oarg = PyObject_CallObject((PyObject*)&PyOFXOutputClipPreferencesType, NULL);
      aname = PyString_FromString("outPref");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyDict_New();
      aname = PyString_FromString("outPref");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      PyObject *pyargs = Py_BuildValue("(O)", oargs);
      
      PyObject *rv = PyObject_Call(meth, pyargs, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
          
          if (stat == kOfxStatOK)
          {
            // fill results
            PyObject *opref = PyObject_GetAttrString(oargs, "outPref");
            
            if (opref && PyObject_TypeCheck(opref, &PyOFXOutputClipPreferencesType))
            {
              PyOFXOutputClipPreferences *ppref = (PyOFXOutputClipPreferences*)opref;
              
              args.outPref.frameRate = PyFloat_AsDouble(ppref->frameRate);
              args.outPref.fieldOrder = ofx::ImageFieldOrder(PyInt_AsLong(ppref->fieldOrder));
              args.outPref.preMult = ofx::ImagePreMult(PyInt_AsLong(ppref->preMult));
              args.outPref.continuousSamples = (ppref->continuousSamples == Py_True);
              args.outPref.frameVarying = (ppref->frameVarying == Py_True);
            }
            else
            {
              stat = kOfxStatFailed;
            }
            
            PyObject *iprefs = PyObject_GetAttrString(oargs, "inPrefs");
            
            if (stat == kOfxStatOK && iprefs && PyDict_Check(iprefs))
            {
              Py_ssize_t i = 0;
              PyObject *clipName, *ipref;
              char *name;
              ofx::InputClipPreferences pref;
              
              while (PyDict_Next(iprefs, &i, &clipName, &ipref))
              {
                if (!PyString_Check(clipName) || !PyObject_TypeCheck(ipref, &PyOFXInputClipPreferencesType))
                {
                  continue;
                }
                
                PyOFXInputClipPreferences *ppref = (PyOFXInputClipPreferences*)ipref;
                
                name = PyString_AsString(clipName);
                
                pref.components = ofx::ImageComponent(PyInt_AsLong(ppref->components));
                pref.bitDepth = ofx::BitDepth(PyInt_AsLong(ppref->bitDepth));
                pref.pixelAspectRatio = PyFloat_AsDouble(ppref->pixelAspectRatio);
                
                args.inPrefs[name] = pref;
              }
            }
            else
            {
              stat = kOfxStatFailed;
            }
            
            Py_XDECREF(opref);
            Py_XDECREF(iprefs);
          }
        }
        else
        {
          ofx::Log("PyImageEffect::getClipPreferences: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(pyargs);
      Py_DECREF(oargs);
      Py_DECREF(meth);
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::getClipPreferences(args);
}

OfxStatus PyImageEffect::getTimeDomain(ofx::ImageEffect::GetTimeDomainArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "getTimeDomain");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyOFXActionArgumentsType, NULL);
      PyObject *oarg;
      PyObject *aname;
      
      oarg = PyFloat_FromDouble(0.0);
      aname = PyString_FromString("first");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      oarg = PyFloat_FromDouble(0.0);
      aname = PyString_FromString("last");
      PyObject_GenericSetAttr(oargs, aname, oarg);
      Py_DECREF(oarg);
      Py_DECREF(aname);
      
      PyObject *pyargs = Py_BuildValue("(O)", oargs);
      
      PyObject *rv = PyObject_Call(meth, pyargs, NULL);
      
      PyObject *err = PyErr_Occurred();
      
      if (err)
      {
        if (PyErr_ExceptionMatches((PyObject*)&PyOFXExceptionType))
        {
          PyOFXException *pexc = (PyOFXException*) err;
          stat = (OfxStatus) PyInt_AsLong(pexc->status);
        }
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
          
          PyObject *of = PyObject_GetAttrString(oargs, "first");
          
          if (of && PyFloat_Check(of))
          {
            args.first = PyFloat_AsDouble(of);
          }
          else
          {
            stat = kOfxStatFailed;
          }
          
          PyObject *ol = PyObject_GetAttrString(oargs, "last");
          
          if (stat == kOfxStatOK && ol && PyFloat_Check(ol))
          {
            args.last = PyFloat_AsDouble(ol);
          }
          else
          {
            stat = kOfxStatFailed;
          }
          
          Py_XDECREF(of);
          Py_XDECREF(ol);
        }
        else
        {
          ofx::Log("PyImageEffect::getTimeDomain: Invalid return value type");
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(oargs);
      Py_DECREF(pyargs);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      PyErr_Clear();
    }
  }
  
  return ofx::ImageEffect::getTimeDomain(args);
}

// ---

int PyOFXInputClipPreferences_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXInputClipPreferences *ppref = (PyOFXInputClipPreferences*) self;
  
  ppref->components = PyInt_FromLong(ofx::ImageComponentRGBA);
  ppref->bitDepth = PyInt_FromLong(ofx::BitDepthFloat);
  ppref->pixelAspectRatio = PyFloat_FromDouble(1.0);
  
  return 0;
}

static PyMemberDef PyOFXInputClipPreferences_Members[] =
{
  {(char*)"components", T_OBJECT_EX, offsetof(PyOFXInputClipPreferences, components), 0, NULL},
  {(char*)"bitDepth", T_OBJECT_EX, offsetof(PyOFXInputClipPreferences, bitDepth), 0, NULL},
  {(char*)"pixelAspectRatio", T_OBJECT_EX, offsetof(PyOFXInputClipPreferences, pixelAspectRatio), 0, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXOutputClipPreferences_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXOutputClipPreferences *ppref = (PyOFXOutputClipPreferences*) self;
  
  ppref->frameRate = PyFloat_FromDouble(0.0);
  ppref->fieldOrder = PyInt_FromLong(ofx::ImageFieldOrderNone);
  ppref->preMult = PyInt_FromLong(ofx::ImageOpaque);
  ppref->continuousSamples = Py_False;
  ppref->frameVarying = Py_False;
  
  Py_INCREF(Py_False);
  Py_INCREF(Py_False);
  
  return 0;
}

static PyMemberDef PyOFXOutputClipPreferences_Members[] =
{
  {(char*)"frameRate", T_OBJECT_EX, offsetof(PyOFXOutputClipPreferences, frameRate), 0, NULL},
  {(char*)"fieldOrder", T_OBJECT_EX, offsetof(PyOFXOutputClipPreferences, fieldOrder), 0, NULL},
  {(char*)"preMult", T_OBJECT_EX, offsetof(PyOFXOutputClipPreferences, preMult), 0, NULL},
  {(char*)"continuousSamples", T_OBJECT_EX, offsetof(PyOFXOutputClipPreferences, continuousSamples), 0, NULL},
  {(char*)"frameVarying", T_OBJECT_EX, offsetof(PyOFXOutputClipPreferences, frameVarying), 0, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXImageEffectDescriptor_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  pdesc->desc = 0;
  return self;
}

int PyOFXImageEffectDescriptor_Init(PyObject *self, PyObject *args, PyObject *)
{
  if (PyTuple_Size(args) == 2)
  {
    PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*) self;
    
    PyObject *phost = PyTuple_GetItem(args, 0);
    PyObject *phandle = PyTuple_GetItem(args, 1);
    
    if (!PyObject_TypeCheck(phost, &PyOFXImageEffectHostType))
    {
      PyErr_SetString(PyExc_TypeError, "First argument must be a object of class ofx.ImageEffectHost");
      return -1;
    }
    
    if (!PyObject_TypeCheck(phandle, &PyOFXHandleType))
    {
      PyErr_SetString(PyExc_TypeError, "Second argument must be a object of class ofx.Handle");
      return -1;
    }
    
    ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) ((PyOFXHost*)phost)->host;
    OfxImageEffectHandle handle = (OfxImageEffectHandle) ((PyOFXHandle*)phandle)->handle;
    
    PyImageEffectDescriptor *desc = new PyImageEffectDescriptor(host, handle);
    desc->self(self);
    
    pdesc->desc = desc;
  }
  return 0;
}

void PyOFXImageEffectDescriptor_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXImageEffectDescriptor_GetProperties(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXPropertySetType, NULL);
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*)rv;
  ppset->pset = &(pdesc->desc->properties());
  
  return rv;
}

PyObject* PyOFXImageEffectDescriptor_GetParameters(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXParameterSetDescriptorType, NULL);
  
  PyOFXParameterSetDescriptor *ppset = (PyOFXParameterSetDescriptor*)rv;
  ppset->desc = &(pdesc->desc->parameters());
  
  return rv;
}

PyObject* PyOFXImageEffectDescriptor_GetHost(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = pdesc->desc->host();
  
  if (!host)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXImageEffectHostType, NULL);
    
    PyOFXHost *phost = (PyOFXHost*)rv;
    phost->host = host;
    
    return rv;
  }
}

PyObject* PyOFXImageEffectDescriptor_GetHandle(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  OfxImageEffectHandle hdl = pdesc->desc->handle();
  
  if (!hdl)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXHandleType, NULL);
    
    PyOFXHandle *phandle = (PyOFXHandle*)rv;
    phandle->handle = hdl;
    
    return rv;
  }
}

PyObject* PyOFXImageEffectDescriptor_GetLabel(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->label();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

int PyOFXImageEffectDescriptor_SetLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  std::string v = PyString_AsString(val);
  
  CATCH({pdesc->desc->label(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetShortLabel(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->shortLabel();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

int PyOFXImageEffectDescriptor_SetShortLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  std::string v = PyString_AsString(val);
  
  CATCH({pdesc->desc->shortLabel(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetLongLabel(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->longLabel();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

int PyOFXImageEffectDescriptor_SetLongLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  std::string v = PyString_AsString(val);
  
  CATCH({pdesc->desc->longLabel(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetGroup(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->group();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

int PyOFXImageEffectDescriptor_SetGroup(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  std::string v = PyString_AsString(val);
  
  CATCH({pdesc->desc->group(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetPluginFilePath(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->pluginFilePath();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

#ifdef OFX_API_1_2

PyObject* PyOFXImageEffectDescriptor_GetVersionLabel(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->versionLabel();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

int PyOFXImageEffectDescriptor_SetVersionLabel(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  std::string v = PyString_AsString(val);
  
  CATCH({pdesc->desc->versionLabel(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetDescription(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = pdesc->desc->description();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

int PyOFXImageEffectDescriptor_SetDescription(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyString_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  bool failed = false;
  
  std::string v = PyString_AsString(val);
  
  CATCH({pdesc->desc->description(v);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetMajorVersion(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = pdesc->desc->majorVersion();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectDescriptor_GetMinorVersion(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = pdesc->desc->minorVersion();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

#endif

PyObject* PyOFXImageEffectDescriptor_GetSingleInstance(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->singleInstance();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_RETURN_TRUE;
  }
  else
  {
    Py_RETURN_FALSE;
  }
}

int PyOFXImageEffectDescriptor_SetSingleInstance(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->singleInstance(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetHostFrameThreading(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->hostFrameThreading();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_RETURN_TRUE;
  }
  else
  {
    Py_RETURN_FALSE;
  }
}

int PyOFXImageEffectDescriptor_SetHostFrameThreading(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->hostFrameThreading(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetSupportsMultiResolution(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->supportsMultiResolution();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_RETURN_TRUE;
  }
  else
  {
    Py_RETURN_FALSE;
  }
}

int PyOFXImageEffectDescriptor_SetSupportsMultiResolution(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->supportsMultiResolution(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetSupportsTiles(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->supportsTiles();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_RETURN_TRUE;
  }
  else
  {
    Py_RETURN_FALSE;
  }
}

int PyOFXImageEffectDescriptor_SetSupportsTiles(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->supportsTiles(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetSupportsMultipleClipDepths(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->supportsMultipleClipDepths();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_RETURN_TRUE;
  }
  else
  {
    Py_RETURN_FALSE;
  }
}

int PyOFXImageEffectDescriptor_SetSupportsMultipleClipDepths(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->supportsMultipleClipDepths(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetSupportsMultipleClipPARs(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->supportsMultipleClipPARs();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_RETURN_TRUE;
  }
  else
  {
    Py_RETURN_FALSE;
  }
}

int PyOFXImageEffectDescriptor_SetSupportsMultipleClipPARs(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->supportsMultipleClipPARs(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetTemporalClipAccess(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->temporalClipAccess();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_RETURN_TRUE;
  }
  else
  {
    Py_RETURN_FALSE;
  }
}

int PyOFXImageEffectDescriptor_SetTemporalClipAccess(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->temporalClipAccess(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetFieldRenderTwiceAlways(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->fieldRenderTwiceAlways();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_RETURN_TRUE;
  }
  else
  {
    Py_RETURN_FALSE;
  }
}

int PyOFXImageEffectDescriptor_SetFieldRenderTwiceAlways(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->fieldRenderTwiceAlways(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetRenderThreadSafety(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(pdesc->desc->renderThreadSafety());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXImageEffectDescriptor_SetRenderThreadSafety(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  
  bool failed = false;
  
  int v = PyInt_AsLong(val);
  
  CATCH({pdesc->desc->renderThreadSafety(ofx::RenderThreadSafety(v));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetSequentialRender(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(pdesc->desc->sequentialRender());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXImageEffectDescriptor_SetSequentialRender(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  
  bool failed = false;
  
  int v = PyInt_AsLong(val);
  
  CATCH({pdesc->desc->sequentialRender(ofx::SequentialRender(v));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffectDescriptor_GetOverlayInteract(PyObject *self, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::EntryPoint func = 0;
  
  bool failed = false;
  
  CATCH({func = pdesc->desc->overlayInteract();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyTuple_New(2);
  
  int idx = PyOFX_GetInteractFuncIndex(func);
  
  if (idx < 0 || idx >= PYOFX_MAX_ENTRY)
  {
    Py_INCREF(Py_None);
    PyTuple_SetItem(rv, 0, Py_None);
    
    Py_INCREF(Py_None);
    PyTuple_SetItem(rv, 1, Py_None);
  }
  else
  {
    Py_INCREF(gInteractDescClasses[idx]);
    PyTuple_SetItem(rv, 0, gInteractDescClasses[idx]);
    
    Py_INCREF(gInteractClasses[idx]);
    PyTuple_SetItem(rv, 1, gInteractClasses[idx]);
  }
  
  return rv;
}

int PyOFXImageEffectDescriptor_SetOverlayInteract(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyTuple_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple");
    return -1;
  }
  
  if (PyTuple_Size(val) != 2)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 2 elements");
    return -1;
  }
  
  PyObject *descClass = PyTuple_GetItem(val, 0);
  if (!PyObject_IsSubclass(descClass, (PyObject*)&PyOFXInteractDescriptorType))
  {
    PyErr_SetString(PyExc_TypeError, "Tuple first element must be a sub class of ofx.InteractDescriptor");
    return -1;
  }
  
  PyObject *instClass = PyTuple_GetItem(val, 1);
  if (!PyObject_IsSubclass(instClass, (PyObject*)&PyOFXInteractType))
  {
    PyErr_SetString(PyExc_TypeError, "Tuple second element must be a sub class of ofx.Interact");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pdesc->desc->overlayInteract(PyOFX_GetInteractFunc(descClass, instClass));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXImageEffectDescriptor_GetSeters[] =
{
  {(char*)"handle", PyOFXImageEffectDescriptor_GetHandle, NULL, NULL, NULL},
  {(char*)"host", PyOFXImageEffectDescriptor_GetHost, NULL, NULL, NULL},
  {(char*)"parameters", PyOFXImageEffectDescriptor_GetParameters, NULL, NULL, NULL},
  {(char*)"properties", PyOFXImageEffectDescriptor_GetProperties, NULL, NULL, NULL},
  {(char*)"label", PyOFXImageEffectDescriptor_GetLabel, PyOFXImageEffectDescriptor_SetLabel, NULL, NULL},
  {(char*)"shortLabel", PyOFXImageEffectDescriptor_GetShortLabel, PyOFXImageEffectDescriptor_SetShortLabel, NULL, NULL},
  {(char*)"longLabel", PyOFXImageEffectDescriptor_GetLongLabel, PyOFXImageEffectDescriptor_SetLongLabel, NULL, NULL},
  {(char*)"group", PyOFXImageEffectDescriptor_GetGroup, PyOFXImageEffectDescriptor_SetGroup, NULL, NULL},
  {(char*)"pluginFilePath", PyOFXImageEffectDescriptor_GetPluginFilePath, NULL, NULL, NULL},
  {(char*)"singleInstance", PyOFXImageEffectDescriptor_GetSingleInstance, PyOFXImageEffectDescriptor_SetSingleInstance, NULL, NULL},
//  {(char*)"hostFrameThreading", PyOFXImageEffectDescriptor_GetHostFrameThreading, PyOFXImageEffectDescriptor_SetHostFrameThreading, NULL, NULL},
  {(char*)"supportsMultiResolution", PyOFXImageEffectDescriptor_GetSupportsMultiResolution, PyOFXImageEffectDescriptor_SetSupportsMultiResolution, NULL, NULL},
  {(char*)"supportsTiles", PyOFXImageEffectDescriptor_GetSupportsTiles, PyOFXImageEffectDescriptor_SetSupportsTiles, NULL, NULL},
  {(char*)"supportsMultipleClipDepths", PyOFXImageEffectDescriptor_GetSupportsMultipleClipDepths, PyOFXImageEffectDescriptor_SetSupportsMultipleClipDepths, NULL, NULL},
  {(char*)"supportsMultipleClipPARs", PyOFXImageEffectDescriptor_GetSupportsMultipleClipPARs, PyOFXImageEffectDescriptor_SetSupportsMultipleClipPARs, NULL, NULL},
  {(char*)"temporalClipAccess", PyOFXImageEffectDescriptor_GetTemporalClipAccess, PyOFXImageEffectDescriptor_SetTemporalClipAccess, NULL, NULL},
  {(char*)"fieldRenderTwiceAlways", PyOFXImageEffectDescriptor_GetFieldRenderTwiceAlways, PyOFXImageEffectDescriptor_SetFieldRenderTwiceAlways, NULL, NULL},
//  {(char*)"renderThreadSafety", PyOFXImageEffectDescriptor_GetRenderThreadSafety, PyOFXImageEffectDescriptor_SetRenderThreadSafety, NULL, NULL},
  {(char*)"sequentialRender", PyOFXImageEffectDescriptor_GetSequentialRender, PyOFXImageEffectDescriptor_SetSequentialRender, NULL, NULL},
  {(char*)"overlayInteract", PyOFXImageEffectDescriptor_GetOverlayInteract, PyOFXImageEffectDescriptor_SetOverlayInteract, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"description", PyOFXImageEffectDescriptor_GetDescription, PyOFXImageEffectDescriptor_SetDescription, NULL, NULL},
  {(char*)"versionLabel", PyOFXImageEffectDescriptor_GetVersionLabel, PyOFXImageEffectDescriptor_SetVersionLabel, NULL, NULL},
  {(char*)"majorVersion", PyOFXImageEffectDescriptor_GetMajorVersion, NULL, NULL, NULL},
  {(char*)"minorVersion", PyOFXImageEffectDescriptor_GetMinorVersion, NULL, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXImageEffectDescriptor_DefineClip(PyObject *self, PyObject *args)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  bool failed = false;
  
  ofx::ClipDescriptor cd;
  
  CATCH({cd = pdesc->desc->defineClip(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXClipDescriptorType, NULL);
  
  PyOFXClipDescriptor *pcd = (PyOFXClipDescriptor*)rv;
  *(pcd->desc) = cd;
  
  return rv;
}

PyObject* PyOFXImageEffectDescriptor_SupportedContextsCount(PyObject *self, PyObject *)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = pdesc->desc->supportedContextsCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectDescriptor_SupportedPixelDepthsCount(PyObject *self, PyObject *)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = pdesc->desc->supportedPixelDepthsCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectDescriptor_ClipPreferencesSlaveParamCount(PyObject *self, PyObject *)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = pdesc->desc->clipPreferencesSlaveParamCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectDescriptor_SupportedContext(PyObject *self, PyObject *args)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  Py_ssize_t nargs = PyTuple_Size(args);
  
  if (nargs < 1 || nargs > 2)
  {
    PyErr_SetString(PyExc_RuntimeError, "At least 1 argument, at most 2");
    return NULL;
  }
  
  if (!PyInt_Check(PyTuple_GetItem(args, 0)))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer for first argument");
    return NULL;
  }
  
  int idx = PyInt_AsLong(PyTuple_GetItem(args, 0));
  
  PyObject *pctx = 0;
  
  if (nargs == 2)
  {
    pctx = PyTuple_GetItem(args, 1);
  }
  
  bool failed = false;
  
  if (pctx != 0)
  {
    if (!PyInt_Check(pctx))
    {
      PyErr_SetString(PyExc_TypeError, "Expected an integer");
      return NULL;
    }
    
    int ctx = PyInt_AsLong(pctx);
    
    CATCH({pdesc->desc->supportedContext(idx, ofx::ImageEffectContext(ctx));}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    Py_RETURN_NONE;
  }
  else
  {
    int rv = 0;
    
    CATCH({rv = int(pdesc->desc->supportedContext(idx));}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    return PyInt_FromLong(rv);
  }
}

PyObject* PyOFXImageEffectDescriptor_SupportedPixelDepth(PyObject *self, PyObject *args)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  Py_ssize_t nargs = PyTuple_Size(args);
  
  if (nargs < 1 || nargs > 2)
  {
    PyErr_SetString(PyExc_RuntimeError, "At least 1 argument, at most 2");
    return NULL;
  }
  
  if (!PyInt_Check(PyTuple_GetItem(args, 0)))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer for first argument");
    return NULL;
  }
  
  int idx = PyInt_AsLong(PyTuple_GetItem(args, 0));
  
  PyObject *ppd = 0;
  
  if (nargs == 2)
  {
    ppd = PyTuple_GetItem(args, 1);
  }
  
  bool failed = false;
  
  if (ppd != 0)
  {
    if (!PyInt_Check(ppd))
    {
      PyErr_SetString(PyExc_TypeError, "Expected an integer");
      return NULL;
    }
    
    int pd = PyInt_AsLong(ppd);
    
    CATCH({pdesc->desc->supportedPixelDepth(idx, ofx::BitDepth(pd));}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    Py_RETURN_NONE;
  }
  else
  {
    int rv = 0;
    
    CATCH({rv = int(pdesc->desc->supportedPixelDepth(idx));}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    return PyInt_FromLong(rv);
  }
}

PyObject* PyOFXImageEffectDescriptor_ClipPreferencesSlaveParam(PyObject *self, PyObject *args)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  Py_ssize_t nargs = PyTuple_Size(args);
  
  if (nargs < 1 || nargs > 2)
  {
    PyErr_SetString(PyExc_RuntimeError, "At least 1 argument, at most 2");
    return NULL;
  }
  
  if (!PyInt_Check(PyTuple_GetItem(args, 0)))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer for first argument");
    return NULL;
  }
  
  int idx = PyInt_AsLong(PyTuple_GetItem(args, 0));
  
  PyObject *pparam = 0;
  
  if (nargs == 2)
  {
    pparam = PyTuple_GetItem(args, 1);
  }
  
  bool failed = false;
  
  if (pparam != 0)
  {
    if (!PyString_Check(pparam))
    {
      PyErr_SetString(PyExc_TypeError, "Expected a string");
      return NULL;
    }
    
    char *param = PyString_AsString(pparam);
    
    CATCH({pdesc->desc->clipPreferencesSlaveParam(idx, param);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    Py_RETURN_NONE;
  }
  else
  {
    std::string rv;
    
    CATCH({rv = pdesc->desc->clipPreferencesSlaveParam(idx);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    return PyString_FromString(rv.c_str());
  }
}

#ifdef OFX_API_1_2

PyObject* PyOFXImageEffectDescriptor_Version(PyObject *self, PyObject *args)
{
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  Py_ssize_t nargs = PyTuple_Size(args);
  
  if (nargs < 1 || nargs > 2)
  {
    PyErr_SetString(PyExc_RuntimeError, "At least 1 argument, at most 2");
    return NULL;
  }
  
  if (!PyInt_Check(PyTuple_GetItem(args, 0)))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer for first argument");
    return NULL;
  }
  
  int level = PyInt_AsLong(PyTuple_GetItem(args, 0));
  
  PyObject *pver = 0;
  
  if (nargs == 2)
  {
    pver = PyTuple_GetItem(args, 1);
  }
  
  bool failed = false;
  
  if (pver != 0)
  {
    if (!PyInt_Check(pver))
    {
      PyErr_SetString(PyExc_TypeError, "Expected an integer");
      return NULL;
    }
    
    int ver = PyInt_AsLong(pver);
    
    CATCH({pdesc->desc->version(level, ver);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    Py_RETURN_NONE;
  }
  else
  {
    int rv = 0;
    
    CATCH({rv = pdesc->desc->version(level);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    return PyInt_FromLong(rv);
  }
}

#endif

static PyMethodDef PyOFXImageEffectDescriptor_Methods[] =
{
  {"defineClip", PyOFXImageEffectDescriptor_DefineClip, METH_VARARGS, NULL},
  {"supportedContextsCount", PyOFXImageEffectDescriptor_SupportedContextsCount, METH_VARARGS, NULL},
  {"supportedContext", PyOFXImageEffectDescriptor_SupportedContext, METH_VARARGS, NULL},
  {"supportedPixelDepthsCount", PyOFXImageEffectDescriptor_SupportedPixelDepthsCount, METH_VARARGS, NULL},
  {"supportedPixelDepth", PyOFXImageEffectDescriptor_SupportedPixelDepth, METH_VARARGS, NULL},
  {"clipPreferencesSlaveParamCount", PyOFXImageEffectDescriptor_ClipPreferencesSlaveParamCount, METH_VARARGS, NULL},
  {"clipPreferencesSlaveParam", PyOFXImageEffectDescriptor_ClipPreferencesSlaveParam, METH_VARARGS, NULL},
#ifdef OFX_API_1_2
  {"version", PyOFXImageEffectDescriptor_Version, METH_VARARGS, NULL},
#endif
  {NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXImageEffect_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  ((PyOFXImageEffect*)self)->effect = 0;
  return self;
}

int PyOFXImageEffect_Init(PyObject *self, PyObject *args, PyObject *)
{
  if (PyTuple_Size(args) == 2)
  {
    PyOFXImageEffect *peffect = (PyOFXImageEffect*) self;
    
    PyObject *phost = PyTuple_GetItem(args, 0);
    PyObject *phandle = PyTuple_GetItem(args, 1);
    
    if (!PyObject_TypeCheck(phost, &PyOFXImageEffectHostType))
    {
      PyErr_SetString(PyExc_TypeError, "First argument must be a object of class ofx.ImageEffectHost");
      return -1;
    }
    
    if (!PyObject_TypeCheck(phandle, &PyOFXHandleType))
    {
      PyErr_SetString(PyExc_TypeError, "Second argument must be a object of class ofx.Handle");
      return -1;
    }
    
    ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) ((PyOFXHost*)phost)->host;
    OfxImageEffectHandle handle = (OfxImageEffectHandle) ((PyOFXHandle*)phandle)->handle;
    
    PyImageEffect *effect = new PyImageEffect(host, handle);
    effect->self(self);
    
    peffect->effect = effect;
  }
  return 0;
}

void PyOFXImageEffect_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXImageEffect_GetProperties(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXPropertySetType, NULL);
  
  PyOFXPropertySet *ppset = (PyOFXPropertySet*)rv;
  ppset->pset = &(peffect->effect->properties());
  
  return rv;
}

PyObject* PyOFXImageEffect_GetParameters(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXParameterSetType, NULL);
  
  PyOFXParameterSet *ppset = (PyOFXParameterSet*)rv;
  ppset->pset = &(peffect->effect->parameters());
  
  return rv;
}

PyObject* PyOFXImageEffect_GetHost(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = peffect->effect->host();
  
  if (!host)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXImageEffectHostType, NULL);
    
    PyOFXHost *phost = (PyOFXHost*)rv;
    phost->host = host;
    
    return rv;
  }
}

PyObject* PyOFXImageEffect_GetHandle(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  OfxImageEffectHandle hdl = peffect->effect->handle();
  
  if (!hdl)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXHandleType, NULL);
    
    PyOFXHandle *phandle = (PyOFXHandle*)rv;
    phandle->handle = hdl;
    
    return rv;
  }
}

PyObject* PyOFXImageEffect_GetContext(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(peffect->effect->context());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffect_GetProjectSize(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double w, h;
  
  CATCH({peffect->effect->projectSize(&w, &h);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", w, h);
}

PyObject* PyOFXImageEffect_GetProjectOffset(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double x, y;
  
  CATCH({peffect->effect->projectOffset(&x, &y);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", x, y);
}

PyObject* PyOFXImageEffect_GetProjectExtent(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double w, h;
  
  CATCH({peffect->effect->projectExtent(&w, &h);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", w, h);
}

PyObject* PyOFXImageEffect_GetProjectPixelAspectRatio(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double par = 1.0;
  
  CATCH({par = peffect->effect->projectPixelAspectRatio();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(par);
}

PyObject* PyOFXImageEffect_GetDuration(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double rv = 0.0;
  
  CATCH({rv = peffect->effect->duration();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXImageEffect_GetFrameRate(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double rv = 0.0;
  
  CATCH({rv = peffect->effect->frameRate();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

PyObject* PyOFXImageEffect_GetIsInteractive(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = peffect->effect->isInteractive();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_RETURN_TRUE;
  }
  else
  {
    Py_RETURN_FALSE;
  }
}

PyObject* PyOFXImageEffect_GetInAnalysis(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = peffect->effect->inAnalysis();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_RETURN_TRUE;
  }
  else
  {
    Py_RETURN_FALSE;
  }
}

int PyOFXImageEffect_SetInAnalysis(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({peffect->effect->inAnalysis(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffect_GetSequentialRender(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(peffect->effect->sequentialRender());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXImageEffect_SetSequentialRender(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  
  bool failed = false;
  
  int v = PyInt_AsLong(val);
  
  CATCH({peffect->effect->sequentialRender(ofx::SequentialRender(v));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXImageEffect_GetInstanceData(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  void *data = 0;
  
  CATCH({data = peffect->effect->instanceData();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (!data)
  {
    Py_RETURN_NONE;
  }
  else
  {
    return (PyObject*)data;
  }
}

int PyOFXImageEffect_SetInstanceData(PyObject *self, PyObject *val, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({peffect->effect->instanceData((void*)val);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

#ifdef OFX_API_1_2

PyObject* PyOFXImageEffect_GetDescription(PyObject *self, void*)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = peffect->effect->description();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

#endif

static PyGetSetDef PyOFXImageEffect_GetSeters[] =
{
  {(char*)"properties", PyOFXImageEffect_GetProperties, NULL, NULL, NULL},
  {(char*)"parameters", PyOFXImageEffect_GetParameters, NULL, NULL, NULL},
  {(char*)"host", PyOFXImageEffect_GetHost, NULL, NULL, NULL},
  {(char*)"handle", PyOFXImageEffect_GetHandle, NULL, NULL, NULL},
  {(char*)"context", PyOFXImageEffect_GetContext, NULL, NULL, NULL},
  {(char*)"projectSize", PyOFXImageEffect_GetProjectSize, NULL, NULL, NULL},
  {(char*)"projectOffset", PyOFXImageEffect_GetProjectOffset, NULL, NULL, NULL},
  {(char*)"projectExtent", PyOFXImageEffect_GetProjectExtent, NULL, NULL, NULL},
  {(char*)"projectPixelAspectRatio", PyOFXImageEffect_GetProjectPixelAspectRatio, NULL, NULL, NULL},
  {(char*)"duration", PyOFXImageEffect_GetDuration, NULL, NULL, NULL},
  {(char*)"frameRate", PyOFXImageEffect_GetFrameRate, NULL, NULL, NULL},
  {(char*)"isInteractive", PyOFXImageEffect_GetIsInteractive, NULL, NULL, NULL},
  {(char*)"inAnalysis", PyOFXImageEffect_GetInAnalysis, PyOFXImageEffect_SetInAnalysis, NULL, NULL},
  {(char*)"sequentialRender", PyOFXImageEffect_GetSequentialRender, PyOFXImageEffect_SetSequentialRender, NULL, NULL},
  {(char*)"instanceData", PyOFXImageEffect_GetInstanceData, PyOFXImageEffect_SetInstanceData, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"description", PyOFXImageEffect_GetDescription, NULL, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

//ImageEffectDescriptor descriptor();

PyObject* PyOFXImageEffect_GetClip(PyObject *self, PyObject *args)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  char *name = 0;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    return NULL;
  }
  
  ofx::Clip clip;
  
  bool failed = false;
  
  CATCH({clip = peffect->effect->getClip(name);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXClipType, NULL);
  
  PyOFXClip *pclip = (PyOFXClip*)rv;
  *(pclip->clip) = clip;
  
  return rv;
}

PyObject* PyOFXImageEffect_Abort(PyObject *self, PyObject *)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = peffect->effect->abort();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (rv)
  {
    Py_RETURN_TRUE;
  }
  else
  {
    Py_RETURN_FALSE;
  }
}

PyObject* PyOFXImageEffect_Alloc(PyObject *self, PyObject *args)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int w, h, comps, depth;
  
  if (!PyArg_ParseTuple(args, "iiii", &w, &h, &comps, &depth))
  {
    return NULL;
  }
  
  bool failed = false;
  
  OfxImageMemoryHandle hdl = 0;
  
  CATCH({hdl = peffect->effect->alloc(w, h, ofx::ImageComponent(comps), ofx::BitDepth(depth));}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (!hdl)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXImageMemoryHandleType, NULL);
    
    PyOFXImageMemoryHandle *phdl = (PyOFXImageMemoryHandle*)rv;
    phdl->base.handle = hdl;
    phdl->w = w;
    phdl->h = h;
    phdl->components = (ofx::ImageComponent) comps;
    phdl->pixelDepth = (ofx::BitDepth) depth;
    
    return rv;
  }
}

PyObject* PyOFXImageEffect_Lock(PyObject *self, PyObject *args)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;
  
  if (!peffect->effect)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyObject *phdl = 0;
  
  if (!PyArg_ParseTuple(args, "O", &phdl))
  {
    return NULL;
  }
  
  if (PyObject_TypeCheck(phdl, &PyOFXImageMemoryHandleType))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a ofx.ImageMemoryHandle");
    return NULL;
  }
  
  PyOFXImageMemoryHandle *hdl = (PyOFXImageMemoryHandle*) phdl;
  
  bool failed = false;
  
  void *ptr = 0;
  
  CATCH({ptr = peffect->effect->lock((OfxImageMemoryHandle)hdl->base.handle);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXPixelAddressType, NULL);
  
  static int compSize[] = {1, 2, 4};
#ifdef OFX_API_1_2
  static int compCount[] = {3, 4, 1, 4};
#else
  static int compCount[] = {4, 1, 4};
#endif
  
  PyOFXPixelAddress *padd = (PyOFXPixelAddress*)rv;
  padd->ptr = ptr;
  padd->base = ptr;
  padd->bounds.x1 = 0;
  padd->bounds.y1 = 0;
  padd->bounds.x2 = hdl->w;
  padd->bounds.y2 = hdl->h;
  padd->components = hdl->components;
  padd->pixelDepth = hdl->pixelDepth;
  padd->pixelBytes = compSize[padd->pixelDepth] * compCount[padd->components];
  padd->rowBytes = hdl->w * padd->pixelBytes;
  
  return rv;
}

PyObject* PyOFXImageEffect_Unlock(PyObject *self, PyObject *args)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;

  if (!peffect->effect)
  {
   PyErr_SetString(PyExc_RuntimeError, "Unbound object");
   return NULL;
  }

  PyObject *phdl = 0;

  if (!PyArg_ParseTuple(args, "O", &phdl))
  {
   return NULL;
  }

  if (PyObject_TypeCheck(phdl, &PyOFXImageMemoryHandleType))
  {
   PyErr_SetString(PyExc_TypeError, "Expected a ofx.ImageMemoryHandle");
   return NULL;
  }

  PyOFXHandle *hdl = (PyOFXHandle*) phdl;

  bool failed = false;

  CATCH({peffect->effect->unlock((OfxImageMemoryHandle)hdl->handle);}, failed);
   
  Py_RETURN_NONE;
}

PyObject* PyOFXImageEffect_Free(PyObject *self, PyObject *args)
{
  PyOFXImageEffect *peffect = (PyOFXImageEffect*)self;

  if (!peffect->effect)
  {
   PyErr_SetString(PyExc_RuntimeError, "Unbound object");
   return NULL;
  }

  PyObject *phdl = 0;

  if (!PyArg_ParseTuple(args, "O", &phdl))
  {
   return NULL;
  }

  if (PyObject_TypeCheck(phdl, &PyOFXImageMemoryHandleType))
  {
   PyErr_SetString(PyExc_TypeError, "Expected a ofx.ImageMemoryHandle");
   return NULL;
  }

  PyOFXHandle *hdl = (PyOFXHandle*) phdl;

  bool failed = false;

  CATCH({peffect->effect->free((OfxImageMemoryHandle)hdl->handle);}, failed);
   
  Py_RETURN_NONE;
}

static PyMethodDef PyOFXImageEffect_Methods[] =
{
  {"getClip", PyOFXImageEffect_GetClip, METH_VARARGS, NULL},
  {"abort", PyOFXImageEffect_Abort, METH_VARARGS, NULL},
  {"alloc", PyOFXImageEffect_Alloc, METH_VARARGS, NULL},
  {"lock", PyOFXImageEffect_Lock, METH_VARARGS, NULL},
  {"unlock", PyOFXImageEffect_Unlock, METH_VARARGS, NULL},
  {"free", PyOFXImageEffect_Free, METH_VARARGS, NULL},
  {NULL, NULL, NULL, NULL}
};

// ---

bool PyOFX_InitImageEffect(PyObject *mod)
{
  INIT_TYPE(PyOFXImageEffectDescriptorType, "ofx.ImageEffectDescriptor", PyOFXImageEffectDescriptor);
  PyOFXImageEffectDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXImageEffectDescriptorType.tp_new = PyOFXImageEffectDescriptor_New;
  PyOFXImageEffectDescriptorType.tp_dealloc = PyOFXImageEffectDescriptor_Delete;
  PyOFXImageEffectDescriptorType.tp_init = PyOFXImageEffectDescriptor_Init;
  PyOFXImageEffectDescriptorType.tp_getset = PyOFXImageEffectDescriptor_GetSeters;
  PyOFXImageEffectDescriptorType.tp_methods = PyOFXImageEffectDescriptor_Methods;
  
  INIT_TYPE(PyOFXImageEffectType, "ofx.ImageEffect", PyOFXImageEffect);
  PyOFXImageEffectType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXImageEffectType.tp_new = PyOFXImageEffect_New;
  PyOFXImageEffectType.tp_dealloc = PyOFXImageEffect_Delete;
  PyOFXImageEffectType.tp_init = PyOFXImageEffect_Init;
  PyOFXImageEffectType.tp_getset = PyOFXImageEffect_GetSeters;
  PyOFXImageEffectType.tp_methods = PyOFXImageEffect_Methods;
  
  INIT_TYPE(PyOFXInputClipPreferencesType, "ofx.InputClipPreferences", PyOFXInputClipPreferences);
  PyOFXInputClipPreferencesType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXInputClipPreferencesType.tp_members = PyOFXInputClipPreferences_Members;
  PyOFXInputClipPreferencesType.tp_init = PyOFXInputClipPreferences_Init;
  
  INIT_TYPE(PyOFXOutputClipPreferencesType, "ofx.OutputClipPreferences", PyOFXOutputClipPreferences);
  PyOFXOutputClipPreferencesType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXOutputClipPreferencesType.tp_members = PyOFXOutputClipPreferences_Members;
  PyOFXOutputClipPreferencesType.tp_init = PyOFXOutputClipPreferences_Init;
  
  if (PyType_Ready(&PyOFXImageEffectDescriptorType) < 0)
  {
    return false;
  }
  
  if (PyType_Ready(&PyOFXImageEffectType) < 0)
  {
    return false;
  }
  
  if (PyType_Ready(&PyOFXInputClipPreferencesType) < 0)
  {
    return false;
  }
  
  if (PyType_Ready(&PyOFXOutputClipPreferencesType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXImageEffectDescriptorType);
  PyModule_AddObject(mod, "ImageEffectDescriptor", (PyObject*)&PyOFXImageEffectDescriptorType);
  
  Py_INCREF(&PyOFXImageEffectType);
  PyModule_AddObject(mod, "ImageEffect", (PyObject*)&PyOFXImageEffectType);
  
  Py_INCREF(&PyOFXInputClipPreferencesType);
  PyModule_AddObject(mod, "InputClipPreferences", (PyObject*)&PyOFXInputClipPreferencesType);
  
  Py_INCREF(&PyOFXOutputClipPreferencesType);
  PyModule_AddObject(mod, "OutputClipPreferences", (PyObject*)&PyOFXOutputClipPreferencesType);
  
  return true;
}
