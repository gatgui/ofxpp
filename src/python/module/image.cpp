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

PyTypeObject PyOFXImageType;

// ---

PyObject* PyOFXImage_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  ((PyOFXImage*)self)->img = new ofx::Image();
  return self;
}

int PyOFXImage_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

void PyOFXImage_Delete(PyObject *self)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  if (pimg->img)
  {
    delete pimg->img;
  }
  self->ob_type->tp_free(self);
}

PyObject* PyOFXImage_GetHandle(PyObject *self, void*)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  OfxPropertySetHandle hdl = pimg->img->handle();
  
  if (!hdl)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *phdl = PyObject_CallObject((PyObject*) &PyOFXHandleType, NULL);
    ((PyOFXHandle*)phdl)->handle = hdl;
    return phdl;
  }
}

PyObject* PyOFXImage_GetData(PyObject *self, void*)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  void *ptr = pimg->img->data();
  
  if (!ptr)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *pptr = PyObject_CallObject((PyObject*) &PyOFXHandleType, NULL);
    ((PyOFXHandle*)pptr)->handle = ptr;
    return pptr;
  }
}

PyObject* PyOFXImage_GetPixelDepth(PyObject *self, void*)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->img->pixelDepth()));
}

PyObject* PyOFXImage_GetComponents(PyObject *self, void*)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->img->components()));
}

PyObject* PyOFXImage_GetPreMultiplication(PyObject *self, void*)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->img->preMultiplication()));
}

PyObject* PyOFXImage_GetRenderScale(PyObject *self, void*)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  double sx, sy;
  
  pimg->img->renderScale(&sx, &sy);
  
  return Py_BuildValue("dd", sx, sy);
}

PyObject* PyOFXImage_GetPixelAspectRatio(PyObject *self, void*)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyFloat_FromDouble(pimg->img->pixelAspectRatio());
}

PyObject* PyOFXImage_GetRegionOfDefinition(PyObject *self, void*)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Rect<int> rod = pimg->img->regionOfDefinition();
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXRectIType, NULL);
  ((PyOFXRectI*)rv)->rect = rod;
  return rv;
}

PyObject* PyOFXImage_GetField(PyObject *self, void*)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->img->field()));
}

PyObject* PyOFXImage_GetUniqueIdentifier(PyObject *self, void*)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyString_FromString(pimg->img->uniqueIdentifier().c_str());
}

PyObject* PyOFXImage_GetComponentBytes(PyObject *self, void*)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->img->componentBytes()));
}

PyObject* PyOFXImage_GetComponentsCount(PyObject *self, void*)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->img->componentsCount()));
}

PyObject* PyOFXImage_GetPixelBytes(PyObject *self, void*)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->img->pixelBytes()));
}

PyObject* PyOFXImage_GetRowBytes(PyObject *self, void*)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->img->rowBytes()));
}

PyObject* PyOFXImage_GetBounds(PyObject *self, void*)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Rect<int> bounds = pimg->img->bounds();
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXRectIType, NULL);
  ((PyOFXRectI*)rv)->rect = bounds;
  return rv;
}

static PyGetSetDef PyOFXImage_GetSeters[] =
{
  {(char*)"handle", PyOFXImage_GetHandle, NULL, NULL, NULL},
  {(char*)"data", PyOFXImage_GetData, NULL, NULL, NULL},
  {(char*)"pixelDepth", PyOFXImage_GetPixelDepth, NULL, NULL, NULL},
  {(char*)"components", PyOFXImage_GetComponents, NULL, NULL, NULL},
  {(char*)"preMultiplication", PyOFXImage_GetPreMultiplication, NULL, NULL, NULL},
  {(char*)"renderScale", PyOFXImage_GetRenderScale, NULL, NULL, NULL},
  {(char*)"pixelAspectRatio", PyOFXImage_GetPixelAspectRatio, NULL, NULL, NULL},
  {(char*)"regionOfDefinition", PyOFXImage_GetRegionOfDefinition, NULL, NULL, NULL},
  {(char*)"field", PyOFXImage_GetField, NULL, NULL, NULL},
  {(char*)"uniqueIdentifier", PyOFXImage_GetUniqueIdentifier, NULL, NULL, NULL},
  {(char*)"componentBytes", PyOFXImage_GetComponentBytes, NULL, NULL, NULL},
  {(char*)"componentsCount", PyOFXImage_GetComponentsCount, NULL, NULL, NULL},
  {(char*)"pixelBytes", PyOFXImage_GetPixelBytes, NULL, NULL, NULL},
  {(char*)"rowBytes", PyOFXImage_GetRowBytes, NULL, NULL, NULL},
  {(char*)"bounds", PyOFXImage_GetBounds, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXImage_Release(PyObject *self, PyObject *)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({pimg->img->release();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXImage_PixelAddress(PyObject *self, PyObject *args)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  
  if (!pimg->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int x, y;
  
  if (!PyArg_ParseTuple(args, "ii", &x, &y))
  {
    return NULL;
  }
  
  void *ptr = pimg->img->pixelAddress(x, y);
  
  if (ptr == 0)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = Py_None;
    
    switch (pimg->img->components())
    {
    case ofx::ImageComponentAlpha:
      switch (pimg->img->pixelDepth())
      {
      case ofx::BitDepthByte:
        rv = PyObject_CallObject((PyObject*)&PyOFXAColourBAddressType, NULL);
        break;
      case ofx::BitDepthShort:
        rv = PyObject_CallObject((PyObject*)&PyOFXAColourSAddressType, NULL);
        break;
      case ofx::BitDepthFloat:
        rv = PyObject_CallObject((PyObject*)&PyOFXAColourFAddressType, NULL);
        break;
      default:
        break;
      }
      break;
    case ofx::ImageComponentRGBA:
      switch (pimg->img->pixelDepth())
      {
      case ofx::BitDepthByte:
        rv = PyObject_CallObject((PyObject*)&PyOFXRGBAColourBAddressType, NULL);
        break;
      case ofx::BitDepthShort:
        rv = PyObject_CallObject((PyObject*)&PyOFXRGBAColourSAddressType, NULL);
        break;
      case ofx::BitDepthFloat:
        rv = PyObject_CallObject((PyObject*)&PyOFXRGBAColourFAddressType, NULL);
        break;
      default:
        break;
      }
      break;
    case ofx::ImageComponentYUVA:
      switch (pimg->img->pixelDepth())
      {
      case ofx::BitDepthByte:
        rv = PyObject_CallObject((PyObject*)&PyOFXYUVAColourBAddressType, NULL);
        break;
      case ofx::BitDepthShort:
        rv = PyObject_CallObject((PyObject*)&PyOFXYUVAColourSAddressType, NULL);
        break;
      case ofx::BitDepthFloat:
        rv = PyObject_CallObject((PyObject*)&PyOFXYUVAColourFAddressType, NULL);
        break;
      default:
        break;
      }
      break;
#ifdef OFX_API_1_2
    case ofx::ImageComponentRGB:
      switch (pimg->img->pixelDepth())
      {
      case ofx::BitDepthByte:
        rv = PyObject_CallObject((PyObject*)&PyOFXRGBColourBAddressType, NULL);
        break;
      case ofx::BitDepthShort:
        rv = PyObject_CallObject((PyObject*)&PyOFXRGBColourSAddressType, NULL);
        break;
      case ofx::BitDepthFloat:
        rv = PyObject_CallObject((PyObject*)&PyOFXRGBColourFAddressType, NULL);
        break;
      default:
        break;
      }
      break;
#endif
    default:
      break;
    }
    
    if (rv != Py_None)
    {
      PyOFXColourAddress *caddr = (PyOFXColourAddress*) rv;
      caddr->ptr = ptr;
      caddr->base = pimg->img->data();
      caddr->bounds = pimg->img->bounds();
      caddr->pixelBytes = pimg->img->pixelBytes();
      caddr->rowBytes = pimg->img->rowBytes();
    }
    else
    {
      Py_INCREF(rv);
    }
    
    return rv;
  }
}

static PyMethodDef PyOFXImage_Methods[] =
{
  {"release", PyOFXImage_Release, METH_VARARGS, NULL},
  {"pixelAddress", PyOFXImage_PixelAddress, METH_VARARGS, NULL},
  {NULL, NULL, NULL, NULL}
};

// ---

bool PyOFX_InitImage(PyObject *mod)
{
  INIT_TYPE(PyOFXImageType, "ofx.Image", PyOFXImage);
  PyOFXImageType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXImageType.tp_new = PyOFXImage_New;
  PyOFXImageType.tp_init = PyOFXImage_Init;
  PyOFXImageType.tp_dealloc = PyOFXImage_Delete;
  PyOFXImageType.tp_getset = PyOFXImage_GetSeters;
  PyOFXImageType.tp_methods = PyOFXImage_Methods;
  
  if (PyType_Ready(&PyOFXImageType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXImageType);
  PyModule_AddObject(mod, "Image", (PyObject*)&PyOFXImageType);
  
  return true;
}

