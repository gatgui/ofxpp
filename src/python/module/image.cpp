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
PyTypeObject PyOFXPixelAddressType;

// ---

PyObject* PyOFXPixelAddress_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  ((PyOFXPixelAddress*)self)->img = 0;
  ((PyOFXPixelAddress*)self)->ptr = 0;
  return self;
}

int PyOFXPixelAddress_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

void PyOFXPixelAddress_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXPixelAddress_GetR(PyObject *self, void*)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  switch (paddr->img->components())
  {
#ifdef OFX_API_1_2
  case ofx::ImageComponentRGB:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      return PyInt_FromLong(((ofx::RGBColour<unsigned char>*) paddr->ptr)->r);
    case ofx::BitDepthShort:
      return PyInt_FromLong(((ofx::RGBColour<unsigned short>*) paddr->ptr)->r);
    case ofx::BitDepthFloat:
      return PyFloat_FromDouble(((ofx::RGBColour<float>*) paddr->ptr)->r);
    default:
      Py_RETURN_NONE;
    }
#endif
  case ofx::ImageComponentRGBA:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      return PyInt_FromLong(((ofx::RGBAColour<unsigned char>*) paddr->ptr)->r);
    case ofx::BitDepthShort:
      return PyInt_FromLong(((ofx::RGBAColour<unsigned short>*) paddr->ptr)->r);
    case ofx::BitDepthFloat:
      return PyFloat_FromDouble(((ofx::RGBAColour<float>*) paddr->ptr)->r);
    default:
      Py_RETURN_NONE;
    }
  default:
    Py_RETURN_NONE;
  }
}

PyObject* PyOFXPixelAddress_GetG(PyObject *self, void*)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  switch (paddr->img->components())
  {
#ifdef OFX_API_1_2
  case ofx::ImageComponentRGB:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      return PyInt_FromLong(((ofx::RGBColour<unsigned char>*) paddr->ptr)->g);
    case ofx::BitDepthShort:
      return PyInt_FromLong(((ofx::RGBColour<unsigned short>*) paddr->ptr)->g);
    case ofx::BitDepthFloat:
      return PyFloat_FromDouble(((ofx::RGBColour<float>*) paddr->ptr)->g);
    default:
      Py_RETURN_NONE;
    }
#endif
  case ofx::ImageComponentRGBA:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      return PyInt_FromLong(((ofx::RGBAColour<unsigned char>*) paddr->ptr)->g);
    case ofx::BitDepthShort:
      return PyInt_FromLong(((ofx::RGBAColour<unsigned short>*) paddr->ptr)->g);
    case ofx::BitDepthFloat:
      return PyFloat_FromDouble(((ofx::RGBAColour<float>*) paddr->ptr)->g);
    default:
      Py_RETURN_NONE;
    }
  default:
    Py_RETURN_NONE;
  }
}

PyObject* PyOFXPixelAddress_GetB(PyObject *self, void*)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  switch (paddr->img->components())
  {
#ifdef OFX_API_1_2
  case ofx::ImageComponentRGB:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      return PyInt_FromLong(((ofx::RGBColour<unsigned char>*) paddr->ptr)->b);
    case ofx::BitDepthShort:
      return PyInt_FromLong(((ofx::RGBColour<unsigned short>*) paddr->ptr)->b);
    case ofx::BitDepthFloat:
      return PyFloat_FromDouble(((ofx::RGBColour<float>*) paddr->ptr)->b);
    default:
      Py_RETURN_NONE;
    }
#endif
  case ofx::ImageComponentRGBA:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      return PyInt_FromLong(((ofx::RGBAColour<unsigned char>*) paddr->ptr)->b);
    case ofx::BitDepthShort:
      return PyInt_FromLong(((ofx::RGBAColour<unsigned short>*) paddr->ptr)->b);
    case ofx::BitDepthFloat:
      return PyFloat_FromDouble(((ofx::RGBAColour<float>*) paddr->ptr)->b);
    default:
      Py_RETURN_NONE;
    }
  default:
    Py_RETURN_NONE;
  }
}

PyObject* PyOFXPixelAddress_GetA(PyObject *self, void*)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  switch (paddr->img->components())
  {
  case ofx::ImageComponentAlpha:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      return PyInt_FromLong(*((unsigned char*) paddr->ptr));
    case ofx::BitDepthShort:
      return PyInt_FromLong(*((unsigned short*) paddr->ptr));
    case ofx::BitDepthFloat:
      return PyFloat_FromDouble(*((float*) paddr->ptr));
    default:
      Py_RETURN_NONE;
    }
  case ofx::ImageComponentRGBA:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      return PyInt_FromLong(((ofx::RGBAColour<unsigned char>*) paddr->ptr)->a);
    case ofx::BitDepthShort:
      return PyInt_FromLong(((ofx::RGBAColour<unsigned short>*) paddr->ptr)->a);
    case ofx::BitDepthFloat:
      return PyFloat_FromDouble(((ofx::RGBAColour<float>*) paddr->ptr)->a);
    default:
      Py_RETURN_NONE;
    }
  case ofx::ImageComponentYUVA:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      return PyInt_FromLong(((ofx::YUVAColour<unsigned char>*) paddr->ptr)->a);
    case ofx::BitDepthShort:
      return PyInt_FromLong(((ofx::YUVAColour<unsigned short>*) paddr->ptr)->a);
    case ofx::BitDepthFloat:
      return PyFloat_FromDouble(((ofx::YUVAColour<float>*) paddr->ptr)->a);
    default:
      Py_RETURN_NONE;
    }
  default:
    Py_RETURN_NONE;
  }
}

PyObject* PyOFXPixelAddress_GetY(PyObject *self, void*)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  if (paddr->img->components() != ofx::ImageComponentYUVA)
  {
    Py_RETURN_NONE;
  }
  else
  {
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      return PyInt_FromLong(((ofx::YUVAColour<unsigned char>*) paddr->ptr)->y);
    case ofx::BitDepthShort:
      return PyInt_FromLong(((ofx::YUVAColour<unsigned short>*) paddr->ptr)->y);
    case ofx::BitDepthFloat:
      return PyFloat_FromDouble(((ofx::YUVAColour<float>*) paddr->ptr)->y);
    default:
      Py_RETURN_NONE;
    }
  }
}

PyObject* PyOFXPixelAddress_GetU(PyObject *self, void*)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  if (paddr->img->components() != ofx::ImageComponentYUVA)
  {
    Py_RETURN_NONE;
  }
  else
  {
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      return PyInt_FromLong(((ofx::YUVAColour<unsigned char>*) paddr->ptr)->u);
    case ofx::BitDepthShort:
      return PyInt_FromLong(((ofx::YUVAColour<unsigned short>*) paddr->ptr)->u);
    case ofx::BitDepthFloat:
      return PyFloat_FromDouble(((ofx::YUVAColour<float>*) paddr->ptr)->u);
    default:
      Py_RETURN_NONE;
    }
  }
}

PyObject* PyOFXPixelAddress_GetV(PyObject *self, void*)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  if (paddr->img->components() != ofx::ImageComponentYUVA)
  {
    Py_RETURN_NONE;
  }
  else
  {
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      return PyInt_FromLong(((ofx::YUVAColour<unsigned char>*) paddr->ptr)->v);
    case ofx::BitDepthShort:
      return PyInt_FromLong(((ofx::YUVAColour<unsigned short>*) paddr->ptr)->v);
    case ofx::BitDepthFloat:
      return PyFloat_FromDouble(((ofx::YUVAColour<float>*) paddr->ptr)->v);
    default:
      Py_RETURN_NONE;
    }
  }
}

int PyOFXPixelAddress_SetR(PyObject *self, PyObject *val, void*)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  switch (paddr->img->components())
  {
#ifdef OFX_API_1_2
  case ofx::ImageComponentRGB:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      ((ofx::RGBColour<unsigned char>*) paddr->ptr)->r = (unsigned char) PyInt_AsLong(val);
      break;
    case ofx::BitDepthShort:
      ((ofx::RGBColour<unsigned short>*) paddr->ptr)->r = (unsigned short) PyInt_AsLong(val);
      break;
    case ofx::BitDepthFloat:
      ((ofx::RGBColour<float>*) paddr->ptr)->r = (float) PyFloat_AsDouble(val);
      break;
    default:
      break;
    }
    break;
#endif
  case ofx::ImageComponentRGBA:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      ((ofx::RGBAColour<unsigned char>*) paddr->ptr)->r = (unsigned char) PyInt_AsLong(val);
      break;
    case ofx::BitDepthShort:
      ((ofx::RGBAColour<unsigned short>*) paddr->ptr)->r = (unsigned short) PyInt_AsLong(val);
      break;
    case ofx::BitDepthFloat:
      ((ofx::RGBAColour<float>*) paddr->ptr)->r = (float) PyFloat_AsDouble(val);
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
  
  return 0;
}

int PyOFXPixelAddress_SetG(PyObject *self, PyObject *val, void*)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  switch (paddr->img->components())
  {
#ifdef OFX_API_1_2
  case ofx::ImageComponentRGB:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      ((ofx::RGBColour<unsigned char>*) paddr->ptr)->g = (unsigned char) PyInt_AsLong(val);
      break;
    case ofx::BitDepthShort:
      ((ofx::RGBColour<unsigned short>*) paddr->ptr)->g = (unsigned short) PyInt_AsLong(val);
      break;
    case ofx::BitDepthFloat:
      ((ofx::RGBColour<float>*) paddr->ptr)->g = (float) PyFloat_AsDouble(val);
      break;
    default:
      break;
    }
    break;
#endif
  case ofx::ImageComponentRGBA:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      ((ofx::RGBAColour<unsigned char>*) paddr->ptr)->g = (unsigned char) PyInt_AsLong(val);
      break;
    case ofx::BitDepthShort:
      ((ofx::RGBAColour<unsigned short>*) paddr->ptr)->g = (unsigned short) PyInt_AsLong(val);
      break;
    case ofx::BitDepthFloat:
      ((ofx::RGBAColour<float>*) paddr->ptr)->g = (float) PyFloat_AsDouble(val);
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
  
  return 0;
}

int PyOFXPixelAddress_SetB(PyObject *self, PyObject *val, void*)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  switch (paddr->img->components())
  {
#ifdef OFX_API_1_2
  case ofx::ImageComponentRGB:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      ((ofx::RGBColour<unsigned char>*) paddr->ptr)->b = (unsigned char) PyInt_AsLong(val);
      break;
    case ofx::BitDepthShort:
      ((ofx::RGBColour<unsigned short>*) paddr->ptr)->b = (unsigned short) PyInt_AsLong(val);
      break;
    case ofx::BitDepthFloat:
      ((ofx::RGBColour<float>*) paddr->ptr)->b = (float) PyFloat_AsDouble(val);
      break;
    default:
      break;
    }
    break;
#endif
  case ofx::ImageComponentRGBA:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      ((ofx::RGBAColour<unsigned char>*) paddr->ptr)->b = (unsigned char) PyInt_AsLong(val);
      break;
    case ofx::BitDepthShort:
      ((ofx::RGBAColour<unsigned short>*) paddr->ptr)->b = (unsigned short) PyInt_AsLong(val);
      break;
    case ofx::BitDepthFloat:
      ((ofx::RGBAColour<float>*) paddr->ptr)->b = (float) PyFloat_AsDouble(val);
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
  
  return 0;
}

int PyOFXPixelAddress_SetA(PyObject *self, PyObject *val, void*)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  switch (paddr->img->components())
  {
  case ofx::ImageComponentAlpha:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      *((unsigned char*) paddr->ptr) = (unsigned char) PyInt_AsLong(val);
      break;
    case ofx::BitDepthShort:
      *((unsigned short*) paddr->ptr) = (unsigned short) PyInt_AsLong(val);
      break;
    case ofx::BitDepthFloat:
      *((float*) paddr->ptr) = (float) PyFloat_AsDouble(val);
      break;
    default:
      break;
    }
    break;
  case ofx::ImageComponentRGBA:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      ((ofx::RGBAColour<unsigned char>*) paddr->ptr)->a = (unsigned char) PyInt_AsLong(val);
      break;
    case ofx::BitDepthShort:
      ((ofx::RGBAColour<unsigned short>*) paddr->ptr)->a = (unsigned short) PyInt_AsLong(val);
      break;
    case ofx::BitDepthFloat:
      ((ofx::RGBAColour<float>*) paddr->ptr)->a = (float) PyFloat_AsDouble(val);
      break;
    default:
      break;
    }
    break;
  case ofx::ImageComponentYUVA:
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      ((ofx::YUVAColour<unsigned char>*) paddr->ptr)->a = (unsigned char) PyInt_AsLong(val);
      break;
    case ofx::BitDepthShort:
      ((ofx::YUVAColour<unsigned short>*) paddr->ptr)->a = (unsigned short) PyInt_AsLong(val);
      break;
    case ofx::BitDepthFloat:
      ((ofx::YUVAColour<float>*) paddr->ptr)->a = (float) PyFloat_AsDouble(val);
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
  
  return 0;
}

int PyOFXPixelAddress_SetY(PyObject *self, PyObject *val, void*)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (paddr->img->components() == ofx::ImageComponentYUVA)
  {
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      ((ofx::YUVAColour<unsigned char>*) paddr->ptr)->y = (unsigned char) PyInt_AsLong(val);
      break;
    case ofx::BitDepthShort:
      ((ofx::YUVAColour<unsigned short>*) paddr->ptr)->y = (unsigned short) PyInt_AsLong(val);
      break;
    case ofx::BitDepthFloat:
      ((ofx::YUVAColour<float>*) paddr->ptr)->y = (float) PyFloat_AsDouble(val);
      break;
    default:
      break;
    }
  }
  
  return 0;
}

int PyOFXPixelAddress_SetU(PyObject *self, PyObject *val, void*)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (paddr->img->components() == ofx::ImageComponentYUVA)
  {
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      ((ofx::YUVAColour<unsigned char>*) paddr->ptr)->u = (unsigned char) PyInt_AsLong(val);
      break;
    case ofx::BitDepthShort:
      ((ofx::YUVAColour<unsigned short>*) paddr->ptr)->u = (unsigned short) PyInt_AsLong(val);
      break;
    case ofx::BitDepthFloat:
      ((ofx::YUVAColour<float>*) paddr->ptr)->u = (float) PyFloat_AsDouble(val);
      break;
    default:
      break;
    }
  }
  
  return 0;
}

int PyOFXPixelAddress_SetV(PyObject *self, PyObject *val, void*)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (paddr->img->components() == ofx::ImageComponentYUVA)
  {
    switch (paddr->img->pixelDepth())
    {
    case ofx::BitDepthByte:
      ((ofx::YUVAColour<unsigned char>*) paddr->ptr)->v = (unsigned char) PyInt_AsLong(val);
      break;
    case ofx::BitDepthShort:
      ((ofx::YUVAColour<unsigned short>*) paddr->ptr)->v = (unsigned short) PyInt_AsLong(val);
      break;
    case ofx::BitDepthFloat:
      ((ofx::YUVAColour<float>*) paddr->ptr)->v = (float) PyFloat_AsDouble(val);
      break;
    default:
      break;
    }
  }
  
  return 0;
}

static PyGetSetDef PyOFXPixelAddress_GetSeters[] =
{
  {(char*)"r", PyOFXPixelAddress_GetR, PyOFXPixelAddress_SetR, NULL, NULL},
  {(char*)"g", PyOFXPixelAddress_GetG, PyOFXPixelAddress_SetG, NULL, NULL},
  {(char*)"b", PyOFXPixelAddress_GetB, PyOFXPixelAddress_SetB, NULL, NULL},
  {(char*)"a", PyOFXPixelAddress_GetA, PyOFXPixelAddress_SetA, NULL, NULL},
  {(char*)"y", PyOFXPixelAddress_GetY, PyOFXPixelAddress_SetY, NULL, NULL},
  {(char*)"u", PyOFXPixelAddress_GetU, PyOFXPixelAddress_SetU, NULL, NULL},
  {(char*)"v", PyOFXPixelAddress_GetV, PyOFXPixelAddress_SetV, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXPixelAddress_Next(PyObject *self, PyObject *)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  unsigned char *bytePtr = (unsigned char*) paddr->ptr;
  
  // check boundaries?
  
  bytePtr += paddr->img->pixelBytes();
  
  paddr->ptr = (void*) bytePtr;
  
  Py_RETURN_NONE;
}

PyObject* PyOFXPixelAddress_Prev(PyObject *self, PyObject *)
{
  PyOFXPixelAddress *paddr = (PyOFXPixelAddress*) self;
  
  if (!paddr->ptr || !paddr->img)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  unsigned char *bytePtr = (unsigned char*) paddr->ptr;
  
  // check boundaries?
  
  bytePtr -= paddr->img->pixelBytes();
  
  paddr->ptr = (void*) bytePtr;
  
  Py_RETURN_NONE;
}

static PyMethodDef PyOFXPixelAddress_Methods[] =
{
  {"next", PyOFXPixelAddress_Next, METH_VARARGS, NULL},
  {"prev", PyOFXPixelAddress_Prev, METH_VARARGS, NULL},
  {NULL, NULL, NULL, NULL}
};

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
  
  return Py_BuildValue("iiii", rod.x1, rod.y1, rod.x2, rod.y2);
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
  
  ofx::Rect<int> rod = pimg->img->bounds();
  
  return Py_BuildValue("iiii", rod.x1, rod.y1, rod.x2, rod.y2);
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
    PyObject *pptr = PyObject_CallObject((PyObject*)&PyOFXPixelAddressType, NULL);
    ((PyOFXPixelAddress*)pptr)->ptr = ptr;
    ((PyOFXPixelAddress*)pptr)->img = pimg->img;
    return pptr;
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
  
  INIT_TYPE(PyOFXPixelAddressType, "ofx.PixelAddress", PyOFXPixelAddress);
  PyOFXPixelAddressType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXPixelAddressType.tp_new = PyOFXPixelAddress_New;
  PyOFXPixelAddressType.tp_init = PyOFXPixelAddress_Init;
  PyOFXPixelAddressType.tp_dealloc = PyOFXPixelAddress_Delete;
  PyOFXPixelAddressType.tp_getset = PyOFXPixelAddress_GetSeters;
  PyOFXPixelAddressType.tp_methods = PyOFXPixelAddress_Methods;
  
  if (PyType_Ready(&PyOFXImageType) < 0)
  {
    return false;
  }
  
  if (PyType_Ready(&PyOFXPixelAddressType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXImageType);
  PyModule_AddObject(mod, "Image", (PyObject*)&PyOFXImageType);
  
  Py_INCREF(&PyOFXPixelAddressType);
  PyModule_AddObject(mod, "PixelAddress", (PyObject*)&PyOFXPixelAddressType);
  
  return true;
}

