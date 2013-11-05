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

PyTypeObject PyOFXImageBaseType;
PyTypeObject PyOFXImageType;
#ifdef OFX_API_1_3
PyTypeObject PyOFXTextureType;
#endif

// ---

PyObject* PyOFXImageBase_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  ((PyOFXImageBase*)self)->imgbase = 0;
  return self;
}

int PyOFXImageBase_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

void PyOFXImageBase_Delete(PyObject *self)
{
  PyOFXImageBase *pimg = (PyOFXImageBase*)self;
  if (pimg->imgbase)
  {
    delete pimg->imgbase;
  }
  self->ob_type->tp_free(self);
}

PyObject* PyOFXImageBase_GetHandle(PyObject *self, void*)
{
  PyOFXImageBase *pimg = (PyOFXImageBase*) self;
  
  if (!pimg->imgbase)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  OfxPropertySetHandle hdl = pimg->imgbase->handle();
  
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

PyObject* PyOFXImageBase_GetPixelDepth(PyObject *self, void*)
{
  PyOFXImageBase *pimg = (PyOFXImageBase*) self;
  
  if (!pimg->imgbase)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->imgbase->pixelDepth()));
}

PyObject* PyOFXImageBase_GetComponents(PyObject *self, void*)
{
  PyOFXImageBase *pimg = (PyOFXImageBase*) self;
  
  if (!pimg->imgbase)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->imgbase->components()));
}

PyObject* PyOFXImageBase_GetPreMultiplication(PyObject *self, void*)
{
  PyOFXImageBase *pimg = (PyOFXImageBase*) self;
  
  if (!pimg->imgbase)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->imgbase->preMultiplication()));
}

PyObject* PyOFXImageBase_GetRenderScale(PyObject *self, void*)
{
  PyOFXImageBase *pimg = (PyOFXImageBase*) self;
  
  if (!pimg->imgbase)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  double sx, sy;
  
  pimg->imgbase->renderScale(&sx, &sy);
  
  return Py_BuildValue("dd", sx, sy);
}

PyObject* PyOFXImageBase_GetPixelAspectRatio(PyObject *self, void*)
{
  PyOFXImageBase *pimg = (PyOFXImageBase*) self;
  
  if (!pimg->imgbase)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyFloat_FromDouble(pimg->imgbase->pixelAspectRatio());
}

PyObject* PyOFXImageBase_GetRegionOfDefinition(PyObject *self, void*)
{
  PyOFXImageBase *pimg = (PyOFXImageBase*) self;
  
  if (!pimg->imgbase)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Rect<int> rod = pimg->imgbase->regionOfDefinition();
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXRectIType, NULL);
  ((PyOFXRectI*)rv)->rect = rod;
  return rv;
}

PyObject* PyOFXImageBase_GetField(PyObject *self, void*)
{
  PyOFXImageBase *pimg = (PyOFXImageBase*) self;
  
  if (!pimg->imgbase)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->imgbase->field()));
}

PyObject* PyOFXImageBase_GetUniqueIdentifier(PyObject *self, void*)
{
  PyOFXImageBase *pimg = (PyOFXImageBase*) self;
  
  if (!pimg->imgbase)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyString_FromString(pimg->imgbase->uniqueIdentifier().c_str());
}

PyObject* PyOFXImageBase_GetComponentBytes(PyObject *self, void*)
{
  PyOFXImageBase *pimg = (PyOFXImageBase*) self;
  
  if (!pimg->imgbase)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->imgbase->componentBytes()));
}

PyObject* PyOFXImageBase_GetComponentsCount(PyObject *self, void*)
{
  PyOFXImageBase *pimg = (PyOFXImageBase*) self;
  
  if (!pimg->imgbase)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->imgbase->componentsCount()));
}

PyObject* PyOFXImageBase_GetPixelBytes(PyObject *self, void*)
{
  PyOFXImageBase *pimg = (PyOFXImageBase*) self;
  
  if (!pimg->imgbase)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->imgbase->pixelBytes()));
}

PyObject* PyOFXImageBase_GetRowBytes(PyObject *self, void*)
{
  PyOFXImageBase *pimg = (PyOFXImageBase*) self;
  
  if (!pimg->imgbase)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(long(pimg->imgbase->rowBytes()));
}

PyObject* PyOFXImageBase_GetBounds(PyObject *self, void*)
{
  PyOFXImageBase *pimg = (PyOFXImageBase*) self;
  
  if (!pimg->imgbase)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::Rect<int> bounds = pimg->imgbase->bounds();
  
  PyObject *rv = PyObject_CallObject((PyObject*)&PyOFXRectIType, NULL);
  ((PyOFXRectI*)rv)->rect = bounds;
  return rv;
}

static PyGetSetDef PyOFXImageBase_GetSeters[] =
{
  {(char*)"handle", PyOFXImageBase_GetHandle, NULL, NULL, NULL},
  {(char*)"pixelDepth", PyOFXImageBase_GetPixelDepth, NULL, NULL, NULL},
  {(char*)"components", PyOFXImageBase_GetComponents, NULL, NULL, NULL},
  {(char*)"preMultiplication", PyOFXImageBase_GetPreMultiplication, NULL, NULL, NULL},
  {(char*)"renderScale", PyOFXImageBase_GetRenderScale, NULL, NULL, NULL},
  {(char*)"pixelAspectRatio", PyOFXImageBase_GetPixelAspectRatio, NULL, NULL, NULL},
  {(char*)"regionOfDefinition", PyOFXImageBase_GetRegionOfDefinition, NULL, NULL, NULL},
  {(char*)"field", PyOFXImageBase_GetField, NULL, NULL, NULL},
  {(char*)"uniqueIdentifier", PyOFXImageBase_GetUniqueIdentifier, NULL, NULL, NULL},
  {(char*)"componentBytes", PyOFXImageBase_GetComponentBytes, NULL, NULL, NULL},
  {(char*)"componentsCount", PyOFXImageBase_GetComponentsCount, NULL, NULL, NULL},
  {(char*)"pixelBytes", PyOFXImageBase_GetPixelBytes, NULL, NULL, NULL},
  {(char*)"rowBytes", PyOFXImageBase_GetRowBytes, NULL, NULL, NULL},
  {(char*)"bounds", PyOFXImageBase_GetBounds, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

/*
PyObject* PyOFXImage_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  PyOFXImage *pimg = ((PyOFXImage*)self);
  pimg->img = new ofx::Image();
  pimg->base.imgbase = pimg->img;
  return self;
}
*/

int PyOFXImage_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

/*
void PyOFXImage_Delete(PyObject *self)
{
  PyOFXImage *pimg = (PyOFXImage*) self;
  if (pimg->img)
  {
    delete pimg->img;
  }
  self->ob_type->tp_free(self);
}
*/

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

static PyGetSetDef PyOFXImage_GetSeters[] =
{
  {(char*)"data", PyOFXImage_GetData, NULL, NULL, NULL},
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
  {NULL, NULL, 0, NULL}
};

// ---

#ifdef OFX_API_1_3

/*
PyObject* PyOFXTexture_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  PyOFXTexture *ptex = ((PyOFXTexture*)self);
  ptex->tex = new ofx::Texture();
  ptex->base.imgbase = ptex->tex;
  return self;
}
*/

int PyOFXTexture_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

/*
void PyOFXTexture_Delete(PyObject *self)
{
  PyOFXTexture *ptex = (PyOFXTexture*) self;
  if (ptex->tex)
  {
    delete ptex->tex;
  }
  self->ob_type->tp_free(self);
}
*/

PyObject* PyOFXTexture_GetIndex(PyObject *self, void*)
{
  PyOFXTexture *ptex = (PyOFXTexture*) self;
  
  if (!ptex->tex)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(ptex->tex->index());
}

PyObject* PyOFXTexture_GetTarget(PyObject *self, void*)
{
  PyOFXTexture *ptex = (PyOFXTexture*) self;
  
  if (!ptex->tex)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  return PyInt_FromLong(ptex->tex->target());
}

static PyGetSetDef PyOFXTexture_GetSeters[] =
{
  {(char*)"index", PyOFXTexture_GetIndex, NULL, NULL, NULL},
  {(char*)"target", PyOFXTexture_GetTarget, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXTexture_Release(PyObject *self, PyObject *)
{
  PyOFXTexture *ptex = (PyOFXTexture*) self;
  
  if (!ptex->tex)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({ptex->tex->release();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

static PyMethodDef PyOFXTexture_Methods[] =
{
  {"release", PyOFXTexture_Release, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

#endif

// ---

bool PyOFX_InitImage(PyObject *mod)
{
  INIT_TYPE(PyOFXImageBaseType, "ofx.ImageBase", PyOFXImageBase);
  PyOFXImageBaseType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXImageBaseType.tp_new = PyOFXImageBase_New;
  PyOFXImageBaseType.tp_init = PyOFXImageBase_Init;
  PyOFXImageBaseType.tp_dealloc = PyOFXImageBase_Delete;
  PyOFXImageBaseType.tp_getset = PyOFXImageBase_GetSeters;
  
  if (PyType_Ready(&PyOFXImageBaseType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXImageBaseType);
  PyModule_AddObject(mod, "ImageBase", (PyObject*)&PyOFXImageBaseType);
  
  
  INIT_TYPE(PyOFXImageType, "ofx.Image", PyOFXImage);
  PyOFXImageType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXImageType.tp_base = &PyOFXImageBaseType;
  //PyOFXImageType.tp_new = PyOFXImage_New;
  PyOFXImageType.tp_init = PyOFXImage_Init;
  //PyOFXImageType.tp_dealloc = PyOFXImage_Delete;
  PyOFXImageType.tp_getset = PyOFXImage_GetSeters;
  PyOFXImageType.tp_methods = PyOFXImage_Methods;
  
  if (PyType_Ready(&PyOFXImageBaseType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXImageType);
  PyModule_AddObject(mod, "Image", (PyObject*)&PyOFXImageType);
  
#ifdef OFX_API_1_3

  INIT_TYPE(PyOFXTextureType, "ofx.Texture", PyOFXTexture);
  PyOFXTextureType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXTextureType.tp_base = &PyOFXImageBaseType;
  //PyOFXTextureType.tp_new = PyOFXTexture_New;
  PyOFXTextureType.tp_init = PyOFXTexture_Init;
  //PyOFXTextureType.tp_dealloc = PyOFXTexture_Delete;
  PyOFXTextureType.tp_getset = PyOFXTexture_GetSeters;
  PyOFXTextureType.tp_methods = PyOFXTexture_Methods;
  
  if (PyType_Ready(&PyOFXTextureType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXTextureType);
  PyModule_AddObject(mod, "Texture", (PyObject*)&PyOFXTextureType);

#endif
  
  return true;
}

