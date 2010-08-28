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

PyTypeObject PyOFXInteractDescriptorType;
PyTypeObject PyOFXInteractType;

// ---

PyInteractDescriptor::PyInteractDescriptor()
  : ofx::InteractDescriptor(), mSelf(0)
{
}

PyInteractDescriptor::PyInteractDescriptor(ofx::ImageEffectHost *h, OfxInteractHandle hdl) throw(ofx::Exception)
  : ofx::InteractDescriptor(h, hdl), mSelf(0)
{
}

PyInteractDescriptor::PyInteractDescriptor(const PyInteractDescriptor &rhs)
  : ofx::InteractDescriptor(rhs), mSelf(rhs.mSelf)
{
  if (mSelf != 0)
  {
    Py_INCREF(mSelf);
  }
}

PyInteractDescriptor::~PyInteractDescriptor()
{
  self(0);
}

PyInteractDescriptor& PyInteractDescriptor::operator=(const PyInteractDescriptor &rhs)
{
  ofx::InteractDescriptor::operator=(rhs);
  self(rhs.self());
  return *this;
}

OfxStatus PyInteractDescriptor::describe()
{
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
        //PyErr_Clear();
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
        }
      }
      
      Py_XDECREF(rv);
      Py_DECREF(meth);
      
      return stat;
    }
    else
    {
      //PyErr_Clear();
      LogPythonError();
    }
  }
  
  return ofx::InteractDescriptor::describe();
}

// ---

PyInteract::PyInteract()
  : ofx::Interact(), mSelf(0)
{
}

PyInteract::PyInteract(ofx::ImageEffectHost *h, OfxInteractHandle hdl) throw(ofx::Exception)
  : ofx::Interact(h, hdl), mSelf(0)
{
}

PyInteract::~PyInteract()
{
  self(0);
}

OfxStatus PyInteract::draw(ofx::Interact::DrawArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "draw");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyObject_Type, NULL);
      PyObject *oarg;
      
      // base args
      oarg = PyObject_CallObject((PyObject*)&PyOFXImageEffectType, NULL);
      ((PyOFXImageEffect*)oarg)->effect = args.effect;
      PyObject_SetAttrString(oargs, "effect", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      PyObject_SetAttrString(oargs, "renderScaleX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      PyObject_SetAttrString(oargs, "renderScaleY", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.time);
      PyObject_SetAttrString(oargs, "time", oarg);
      Py_DECREF(oarg);
      
      // common args
      oarg = PyFloat_FromDouble(args.pixelScaleX);
      PyObject_SetAttrString(oargs, "pixelScaleX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.pixelScaleY);
      PyObject_SetAttrString(oargs, "pixelScaleY", oarg);
      Py_DECREF(oarg);
      
      oarg = Py_BuildValue("dddd", args.bgColour.r, args.bgColour.g, args.bgColour.b, args.bgColour.a);
      PyObject_SetAttrString(oargs, "bgColour", oarg);
      Py_DECREF(oarg);
      
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
        //PyErr_Clear();
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
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
      //PyErr_Clear();
      LogPythonError();
    }
  }
  
  return ofx::Interact::draw(args);
}

OfxStatus PyInteract::penMotion(ofx::Interact::PenArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "penMotion");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyObject_Type, NULL);
      PyObject *oarg;
      
      // base args
      oarg = PyObject_CallObject((PyObject*)&PyOFXImageEffectType, NULL);
      ((PyOFXImageEffect*)oarg)->effect = args.effect;
      PyObject_SetAttrString(oargs, "effect", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      PyObject_SetAttrString(oargs, "renderScaleX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      PyObject_SetAttrString(oargs, "renderScaleY", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.time);
      PyObject_SetAttrString(oargs, "time", oarg);
      Py_DECREF(oarg);
      
      // common args
      oarg = PyFloat_FromDouble(args.pixelScaleX);
      PyObject_SetAttrString(oargs, "pixelScaleX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.pixelScaleY);
      PyObject_SetAttrString(oargs, "pixelScaleY", oarg);
      Py_DECREF(oarg);
      
      oarg = Py_BuildValue("dddd", args.bgColour.r, args.bgColour.g, args.bgColour.b, args.bgColour.a);
      PyObject_SetAttrString(oargs, "bgColour", oarg);
      Py_DECREF(oarg);
      
      // pen args
      oarg = PyFloat_FromDouble(args.x);
      PyObject_SetAttrString(oargs, "x", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.y);
      PyObject_SetAttrString(oargs, "y", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.pressure);
      PyObject_SetAttrString(oargs, "pressure", oarg);
      Py_DECREF(oarg);
      
#ifdef OFX_API_1_2
      oarg = PyInt_FromLong(args.viewportX);
      PyObject_SetAttrString(oargs, "viewportX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyInt_FromLong(args.viewportY);
      PyObject_SetAttrString(oargs, "viewportY", oarg);
      Py_DECREF(oarg);
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
        //PyErr_Clear();
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
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
      //PyErr_Clear();
      LogPythonError();
    }
  }
  
  return ofx::Interact::penMotion(args);
}

OfxStatus PyInteract::penDown(ofx::Interact::PenArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "penDown");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyObject_Type, NULL);
      PyObject *oarg;
      
      // base args
      oarg = PyObject_CallObject((PyObject*)&PyOFXImageEffectType, NULL);
      ((PyOFXImageEffect*)oarg)->effect = args.effect;
      PyObject_SetAttrString(oargs, "effect", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      PyObject_SetAttrString(oargs, "renderScaleX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      PyObject_SetAttrString(oargs, "renderScaleY", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.time);
      PyObject_SetAttrString(oargs, "time", oarg);
      Py_DECREF(oarg);
      
      // common args
      oarg = PyFloat_FromDouble(args.pixelScaleX);
      PyObject_SetAttrString(oargs, "pixelScaleX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.pixelScaleY);
      PyObject_SetAttrString(oargs, "pixelScaleY", oarg);
      Py_DECREF(oarg);
      
      oarg = Py_BuildValue("dddd", args.bgColour.r, args.bgColour.g, args.bgColour.b, args.bgColour.a);
      PyObject_SetAttrString(oargs, "bgColour", oarg);
      Py_DECREF(oarg);
      
      // pen args
      oarg = PyFloat_FromDouble(args.x);
      PyObject_SetAttrString(oargs, "x", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.y);
      PyObject_SetAttrString(oargs, "y", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.pressure);
      PyObject_SetAttrString(oargs, "pressure", oarg);
      Py_DECREF(oarg);
      
#ifdef OFX_API_1_2
      oarg = PyInt_FromLong(args.viewportX);
      PyObject_SetAttrString(oargs, "viewportX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyInt_FromLong(args.viewportY);
      PyObject_SetAttrString(oargs, "viewportY", oarg);
      Py_DECREF(oarg);
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
        //PyErr_Clear();
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
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
      //PyErr_Clear();
      LogPythonError();
    }
  }
  
  return ofx::Interact::penDown(args);
}

OfxStatus PyInteract::penUp(ofx::Interact::PenArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "penUp");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyObject_Type, NULL);
      PyObject *oarg;
      
      // base args
      oarg = PyObject_CallObject((PyObject*)&PyOFXImageEffectType, NULL);
      ((PyOFXImageEffect*)oarg)->effect = args.effect;
      PyObject_SetAttrString(oargs, "effect", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      PyObject_SetAttrString(oargs, "renderScaleX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      PyObject_SetAttrString(oargs, "renderScaleY", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.time);
      PyObject_SetAttrString(oargs, "time", oarg);
      Py_DECREF(oarg);
      
      // common args
      oarg = PyFloat_FromDouble(args.pixelScaleX);
      PyObject_SetAttrString(oargs, "pixelScaleX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.pixelScaleY);
      PyObject_SetAttrString(oargs, "pixelScaleY", oarg);
      Py_DECREF(oarg);
      
      oarg = Py_BuildValue("dddd", args.bgColour.r, args.bgColour.g, args.bgColour.b, args.bgColour.a);
      PyObject_SetAttrString(oargs, "bgColour", oarg);
      Py_DECREF(oarg);
      
      // pen args
      oarg = PyFloat_FromDouble(args.x);
      PyObject_SetAttrString(oargs, "x", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.y);
      PyObject_SetAttrString(oargs, "y", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.pressure);
      PyObject_SetAttrString(oargs, "pressure", oarg);
      Py_DECREF(oarg);
      
#ifdef OFX_API_1_2
      oarg = PyInt_FromLong(args.viewportX);
      PyObject_SetAttrString(oargs, "viewportX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyInt_FromLong(args.viewportY);
      PyObject_SetAttrString(oargs, "viewportY", oarg);
      Py_DECREF(oarg);
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
        //PyErr_Clear();
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
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
      //PyErr_Clear();
      LogPythonError();
    }
  }
  
  return ofx::Interact::penUp(args);
}

OfxStatus PyInteract::keyDown(ofx::Interact::KeyArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "keyDown");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyObject_Type, NULL);
      PyObject *oarg;
      
      // base args
      oarg = PyObject_CallObject((PyObject*)&PyOFXImageEffectType, NULL);
      ((PyOFXImageEffect*)oarg)->effect = args.effect;
      PyObject_SetAttrString(oargs, "effect", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      PyObject_SetAttrString(oargs, "renderScaleX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      PyObject_SetAttrString(oargs, "renderScaleY", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.time);
      PyObject_SetAttrString(oargs, "time", oarg);
      Py_DECREF(oarg);
      
      // key args
      oarg = PyInt_FromLong(args.sym);
      PyObject_SetAttrString(oargs, "time", oarg);
      Py_DECREF(oarg);
      
      oarg = PyString_FromString(args.string.c_str());
      PyObject_SetAttrString(oargs, "string", oarg);
      Py_DECREF(oarg);
      
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
        //PyErr_Clear();
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
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
      //PyErr_Clear();
      LogPythonError();
    }
  }
  
  return ofx::Interact::keyDown(args);
}

OfxStatus PyInteract::keyUp(ofx::Interact::KeyArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "keyUp");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyObject_Type, NULL);
      PyObject *oarg;
      
      // base args
      oarg = PyObject_CallObject((PyObject*)&PyOFXImageEffectType, NULL);
      ((PyOFXImageEffect*)oarg)->effect = args.effect;
      PyObject_SetAttrString(oargs, "effect", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      PyObject_SetAttrString(oargs, "renderScaleX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      PyObject_SetAttrString(oargs, "renderScaleY", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.time);
      PyObject_SetAttrString(oargs, "time", oarg);
      Py_DECREF(oarg);
      
      // key args
      oarg = PyInt_FromLong(args.sym);
      PyObject_SetAttrString(oargs, "time", oarg);
      Py_DECREF(oarg);
      
      oarg = PyString_FromString(args.string.c_str());
      PyObject_SetAttrString(oargs, "string", oarg);
      Py_DECREF(oarg);
      
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
        //PyErr_Clear();
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
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
      //PyErr_Clear();
      LogPythonError();
    }
  }
  
  return ofx::Interact::keyUp(args);
}

OfxStatus PyInteract::keyRepeat(ofx::Interact::KeyArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "keyRepeat");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyObject_Type, NULL);
      PyObject *oarg;
      
      // base args
      oarg = PyObject_CallObject((PyObject*)&PyOFXImageEffectType, NULL);
      ((PyOFXImageEffect*)oarg)->effect = args.effect;
      PyObject_SetAttrString(oargs, "effect", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      PyObject_SetAttrString(oargs, "renderScaleX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      PyObject_SetAttrString(oargs, "renderScaleY", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.time);
      PyObject_SetAttrString(oargs, "time", oarg);
      Py_DECREF(oarg);
      
      // key args
      oarg = PyInt_FromLong(args.sym);
      PyObject_SetAttrString(oargs, "time", oarg);
      Py_DECREF(oarg);
      
      oarg = PyString_FromString(args.string.c_str());
      PyObject_SetAttrString(oargs, "string", oarg);
      Py_DECREF(oarg);
      
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
        //PyErr_Clear();
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
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
      //PyErr_Clear();
      LogPythonError();
    }
  }
  
  return ofx::Interact::keyRepeat(args);
}

OfxStatus PyInteract::gainFocus(ofx::Interact::FocusArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "gainFocus");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyObject_Type, NULL);
      PyObject *oarg;
      
      // base args
      oarg = PyObject_CallObject((PyObject*)&PyOFXImageEffectType, NULL);
      ((PyOFXImageEffect*)oarg)->effect = args.effect;
      PyObject_SetAttrString(oargs, "effect", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      PyObject_SetAttrString(oargs, "renderScaleX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      PyObject_SetAttrString(oargs, "renderScaleY", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.time);
      PyObject_SetAttrString(oargs, "time", oarg);
      Py_DECREF(oarg);
      
      // common args
      oarg = PyFloat_FromDouble(args.pixelScaleX);
      PyObject_SetAttrString(oargs, "pixelScaleX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.pixelScaleY);
      PyObject_SetAttrString(oargs, "pixelScaleY", oarg);
      Py_DECREF(oarg);
      
      oarg = Py_BuildValue("dddd", args.bgColour.r, args.bgColour.g, args.bgColour.b, args.bgColour.a);
      PyObject_SetAttrString(oargs, "bgColour", oarg);
      Py_DECREF(oarg);
      
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
        //PyErr_Clear();
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
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
      //PyErr_Clear();
      LogPythonError();
    }
  }
  
  return ofx::Interact::gainFocus(args);
}

OfxStatus PyInteract::loseFocus(ofx::Interact::FocusArgs &args)
{
  if (mSelf != 0)
  {
    PyObject *meth = PyObject_GetAttrString(mSelf, "loseFocus");
    
    if (meth)
    {
      OfxStatus stat = kOfxStatFailed;
      
      PyObject *oargs = PyObject_CallObject((PyObject*)&PyObject_Type, NULL);
      PyObject *oarg;
      
      // base args
      oarg = PyObject_CallObject((PyObject*)&PyOFXImageEffectType, NULL);
      ((PyOFXImageEffect*)oarg)->effect = args.effect;
      PyObject_SetAttrString(oargs, "effect", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleX);
      PyObject_SetAttrString(oargs, "renderScaleX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.renderScaleY);
      PyObject_SetAttrString(oargs, "renderScaleY", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.time);
      PyObject_SetAttrString(oargs, "time", oarg);
      Py_DECREF(oarg);
      
      // common args
      oarg = PyFloat_FromDouble(args.pixelScaleX);
      PyObject_SetAttrString(oargs, "pixelScaleX", oarg);
      Py_DECREF(oarg);
      
      oarg = PyFloat_FromDouble(args.pixelScaleY);
      PyObject_SetAttrString(oargs, "pixelScaleY", oarg);
      Py_DECREF(oarg);
      
      oarg = Py_BuildValue("dddd", args.bgColour.r, args.bgColour.g, args.bgColour.b, args.bgColour.a);
      PyObject_SetAttrString(oargs, "bgColour", oarg);
      Py_DECREF(oarg);
      
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
        //PyErr_Clear();
        LogPythonError();
      }
      else
      {
        if (PyInt_Check(rv))
        {
          stat = (OfxStatus) PyInt_AsLong(rv);
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
      //PyErr_Clear();
      LogPythonError();
    }
  }
  
  return ofx::Interact::loseFocus(args);
}

// ---

PyObject* PyOFXInteractDescriptor_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  ((PyOFXInteractDescriptor*)self)->desc = 0;
  return self;
}

int PyOFXInteractDescriptor_Init(PyObject *self, PyObject *args, PyObject *)
{
  if (PyTuple_Size(args) == 2)
  {
    PyOFXInteractDescriptor *pdesc = (PyOFXInteractDescriptor*) self;
    
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
    OfxInteractHandle handle = (OfxInteractHandle) ((PyOFXHandle*)phandle)->handle;
    
    PyInteractDescriptor *desc = new PyInteractDescriptor(host, handle);
    desc->self(self);
    
    pdesc->desc = desc;
  }
  return 0;
}

void PyOFXInteractDescriptor_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXInteractDescriptor_GetHasAlpha(PyObject *self, void*)
{
  PyOFXInteractDescriptor *pdesc = (PyOFXInteractDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pdesc->desc->hasAlpha();}, failed);
  
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

PyObject* PyOFXInteractDescriptor_GetBitDepth(PyObject *self, void*)
{
  PyOFXInteractDescriptor *pdesc = (PyOFXInteractDescriptor*)self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = pdesc->desc->bitDepth();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

static PyGetSetDef PyOFXInteractDescriptor_GetSeters[] =
{
  {(char*)"hasAlpha", PyOFXInteractDescriptor_GetHasAlpha, NULL, NULL, NULL},
  {(char*)"bitDepth", PyOFXInteractDescriptor_GetBitDepth, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXInteract_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  ((PyOFXInteract*)self)->interact = 0;
  return self;
}

int PyOFXInteract_Init(PyObject *self, PyObject *args, PyObject *)
{
  if (PyTuple_Size(args) == 2)
  {
    PyOFXInteract *pinteract = (PyOFXInteract*) self;
    
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
    OfxInteractHandle handle = (OfxInteractHandle) ((PyOFXHandle*)phandle)->handle;
    
    PyInteract *interact = new PyInteract(host, handle);
    interact->self(self);
    
    pinteract->interact = interact;
  }
  return 0;
}

void PyOFXInteract_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXInteract_GetHasAlpha(PyObject *self, void*)
{
  PyOFXInteract *pinteract = (PyOFXInteract*)self;
  
  if (!pinteract->interact)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = pinteract->interact->hasAlpha();}, failed);
  
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

PyObject* PyOFXInteract_GetBitDepth(PyObject *self, void*)
{
  PyOFXInteract *pinteract = (PyOFXInteract*)self;
  
  if (!pinteract->interact)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = pinteract->interact->bitDepth();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXInteract_GetEffectInstance(PyObject *self, void*)
{
  PyOFXInteract *pinteract = (PyOFXInteract*)self;
  
  if (!pinteract->interact)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  ofx::ImageEffect *effect = 0;
  
  CATCH({effect = pinteract->interact->effectInstance();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (!effect)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXImageEffectType, NULL);
    ((PyOFXImageEffect*)rv)->effect = effect;
    return rv;
  }
}

PyObject* PyOFXInteract_GetInstanceData(PyObject *self, void*)
{
  PyOFXInteract *pinteract = (PyOFXInteract*)self;
  
  if (!pinteract->interact)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  void *data = 0;
  
  CATCH({data = pinteract->interact->instanceData();}, failed);
  
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

int PyOFXInteract_SetInstanceData(PyObject *self, PyObject *val, void*)
{
  PyOFXInteract *pinteract = (PyOFXInteract*)self;
  
  if (!pinteract->interact)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  bool failed = false;
  
  CATCH({pinteract->interact->instanceData((void*)val);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXInteract_GetPixelScale(PyObject *self, void*)
{
  PyOFXInteract *pinteract = (PyOFXInteract*)self;
  
  if (!pinteract->interact)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  double sx, sy;
  
  CATCH({pinteract->interact->pixelScale(&sx, &sy);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", sx, sy);
}

PyObject* PyOFXInteract_GetViewportSize(PyObject *self, void*)
{
  PyOFXInteract *pinteract = (PyOFXInteract*)self;
  
  if (!pinteract->interact)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int w, h;
  
  CATCH({pinteract->interact->viewportSize(&w, &h);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ii", w, h);
}

PyObject* PyOFXInteract_GetBackgroundColour(PyObject *self, void*)
{
  PyOFXInteract *pinteract = (PyOFXInteract*)self;
  
  if (!pinteract->interact)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  ofx::RGBAColour<double> colour = {0,0,0,1};
  
  CATCH({colour = pinteract->interact->backgroundColour();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dddd", colour.r, colour.g, colour.b, colour.a);
}

#ifdef OFX_API_1_2

PyObject* PyOFXInteract_GetSuggestedColour(PyObject *self, void*)
{
  PyOFXInteract *pinteract = (PyOFXInteract*)self;
  
  if (!pinteract->interact)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  ofx::RGBAColour<double> colour = {0,0,0,1};
  
  CATCH({colour = pinteract->interact->suggestedColour();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dddd", colour.r, colour.g, colour.b, colour.a);
}

#endif

static PyGetSetDef PyOFXInteract_GetSeters[] =
{
  {(char*)"hasAlpha", PyOFXInteract_GetHasAlpha, NULL, NULL, NULL},
  {(char*)"bitDepth", PyOFXInteract_GetBitDepth, NULL, NULL, NULL},
  {(char*)"effectInstance", PyOFXInteract_GetEffectInstance, NULL, NULL, NULL},
  {(char*)"instanceData", PyOFXInteract_GetInstanceData, PyOFXInteract_SetInstanceData, NULL, NULL},
  {(char*)"pixelScale", PyOFXInteract_GetPixelScale, NULL, NULL, NULL},
  {(char*)"viewportSize", PyOFXInteract_GetViewportSize, NULL, NULL, NULL},
  {(char*)"backgroundColour", PyOFXInteract_GetBackgroundColour, NULL, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"suggestedColour", PyOFXInteract_GetSuggestedColour, NULL, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXInteract_SwapBuffers(PyObject *self, PyObject *)
{
  PyOFXInteract *pinteract = (PyOFXInteract*)self;
  
  if (!pinteract->interact)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({pinteract->interact->swapBuffers();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXInteract_Redraw(PyObject *self, PyObject *)
{
  PyOFXInteract *pinteract = (PyOFXInteract*)self;
  
  if (!pinteract->interact)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({pinteract->interact->redraw();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXInteract_SlaveToParamCount(PyObject *self, PyObject *)
{
  PyOFXInteract *pinteract = (PyOFXInteract*)self;
  
  if (!pinteract->interact)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = pinteract->interact->slaveToParamCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXInteract_SlaveToParam(PyObject *self, PyObject *args)
{
  PyOFXInteract *pinteract = (PyOFXInteract*)self;
  
  if (!pinteract->interact)
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
  PyObject *val = 0;
  
  if (nargs == 2)
  {
    val = PyTuple_GetItem(args, 1);
  }
  
  bool failed = false;
  
  if (val != 0)
  {
    if (!PyString_Check(val))
    {
      PyErr_SetString(PyExc_TypeError, "Expected a string");
      return NULL;
    }
    
    char *v = PyString_AsString(val);
    
    CATCH({pinteract->interact->slaveToParam(idx, v);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    Py_RETURN_NONE;
  }
  else
  {
    std::string rv;
    
    CATCH({rv = pinteract->interact->slaveToParam(idx);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    return PyString_FromString(rv.c_str());
  }
}

static PyMethodDef PyOFXInteract_Methods[] =
{
  {"swapBuffers", PyOFXInteract_SwapBuffers, METH_VARARGS, NULL},
  {"redraw", PyOFXInteract_Redraw, METH_VARARGS, NULL},
  {"slaveToParamCount", PyOFXInteract_SlaveToParamCount, METH_VARARGS, NULL},
  {"slaveToParam", PyOFXInteract_SlaveToParam, METH_VARARGS, NULL},
  {NULL, NULL, NULL, NULL}
};

// ---

bool PyOFX_InitInteract(PyObject *mod)
{
  INIT_TYPE(PyOFXInteractDescriptorType, "ofx.InteractDescriptor", PyOFXInteractDescriptor);
  PyOFXInteractDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXInteractDescriptorType.tp_new = PyOFXInteractDescriptor_New;
  PyOFXInteractDescriptorType.tp_dealloc = PyOFXInteractDescriptor_Delete;
  PyOFXInteractDescriptorType.tp_init = PyOFXInteractDescriptor_Init;
  PyOFXInteractDescriptorType.tp_getset = PyOFXInteractDescriptor_GetSeters;
  
  INIT_TYPE(PyOFXInteractType, "ofx.Interact", PyOFXInteract);
  PyOFXInteractType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXInteractType.tp_new = PyOFXInteract_New;
  PyOFXInteractType.tp_dealloc = PyOFXInteract_Delete;
  PyOFXInteractType.tp_init = PyOFXInteract_Init;
  PyOFXInteractType.tp_getset = PyOFXInteract_GetSeters;
  PyOFXInteractType.tp_methods = PyOFXInteract_Methods;
  
  if (PyType_Ready(&PyOFXInteractDescriptorType) < 0)
  {
    return false;
  }
  
  if (PyType_Ready(&PyOFXInteractType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXInteractDescriptorType);
  PyModule_AddObject(mod, "InteractDescriptor", (PyObject*)&PyOFXInteractDescriptorType);
  
  Py_INCREF(&PyOFXInteractType);
  PyModule_AddObject(mod, "Interact", (PyObject*)&PyOFXInteractType);
  
  return true;
}
