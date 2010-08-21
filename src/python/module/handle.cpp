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

PyTypeObject PyOFXHandleType;
PyTypeObject PyOFXImageMemoryHandleType;

static PyObject* PyOFXHandle_New(PyTypeObject *type, PyObject *, PyObject *)
{
  PyObject *self = type->tp_alloc(type, 0);
  ((PyOFXHandle*)self)->handle = 0;
  return self;
}

static int PyOFXHandle_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

static void PyOFXHandle_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

// ---

static int PyOFXImageMemoryHandle_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXImageMemoryHandle *phdl = (PyOFXImageMemoryHandle*) self;
  phdl->w = 0;
  phdl->h = 0;
  phdl->components = ofx::ImageComponentNone;
  phdl->pixelDepth = ofx::BitDepthNone;
  return 0;
}

// ---

bool PyOFX_InitHandle(PyObject *mod)
{
  INIT_TYPE(PyOFXHandleType, "ofx.Handle", PyOFXHandle);
  PyOFXHandleType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXHandleType.tp_init = PyOFXHandle_Init;
  PyOFXHandleType.tp_new = PyOFXHandle_New;
  PyOFXHandleType.tp_dealloc = PyOFXHandle_Delete;
  
  INIT_TYPE(PyOFXImageMemoryHandleType, "ofx.ImageMemoryHandle", PyOFXImageMemoryHandle);
  PyOFXImageMemoryHandleType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXImageMemoryHandleType.tp_init = PyOFXImageMemoryHandle_Init;
  
  if (PyType_Ready(&PyOFXHandleType) < 0)
  {
    return false;
  }
  
  if (PyType_Ready(&PyOFXImageMemoryHandleType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXHandleType);
  PyModule_AddObject(mod, "Handle", (PyObject*)&PyOFXHandleType);
  
  Py_INCREF(&PyOFXImageMemoryHandleType);
  PyModule_AddObject(mod, "ImageMemoryHandle", (PyObject*)&PyOFXImageMemoryHandleType);
  
  return true;
}
