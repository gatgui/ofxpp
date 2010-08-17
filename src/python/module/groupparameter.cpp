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

PyTypeObject PyOFXGroupParameterDescriptorType;
PyTypeObject PyOFXGroupParameterType;

// ---

int PyOFXGroupParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::GroupParameterDescriptor();
  return 0;
}

#ifdef OFX_API_1_2

PyObject* PyOFXGroupParameterDescriptor_GetOpen(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::GroupParameterDescriptor *desc = (ofx::GroupParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = desc->open();}, failed);
  
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

int PyOFXGroupParameterDescriptor_SetOpen(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::GroupParameterDescriptor *desc = (ofx::GroupParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->open(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

#endif

static PyGetSetDef PyOFXGroupParameterDescriptor_GetSeters[] =
{
#ifdef OFX_API_1_2
  {(char*)"open", PyOFXGroupParameterDescriptor_GetOpen, PyOFXGroupParameterDescriptor_SetOpen, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXGroupParameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::GroupParameter();
  return 0;
}

#ifdef OFX_API_1_2

PyObject* PyOFXGroupParameter_GetOpen(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::GroupParameter *param = (ofx::GroupParameter*) pparam->param;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = param->open();}, failed);
  
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

#endif

static PyGetSetDef PyOFXGroupParameter_GetSeters[] =
{
#ifdef OFX_API_1_2
  {(char*)"open", PyOFXGroupParameter_GetOpen, NULL, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

bool PyOFX_InitParameter_Group(PyObject *mod)
{
  INIT_TYPE(PyOFXGroupParameterDescriptorType, "ofx.GroupParameterDescriptor", PyOFXGroupParameterDescriptor);
  PyOFXGroupParameterDescriptorType.tp_base = &PyOFXParameterDescriptorType;
  PyOFXGroupParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXGroupParameterDescriptorType.tp_init = PyOFXGroupParameterDescriptor_Init;
  PyOFXGroupParameterDescriptorType.tp_getset = PyOFXGroupParameterDescriptor_GetSeters;
  if (PyType_Ready(&PyOFXGroupParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXGroupParameterType, "ofx.GroupParameter", PyOFXGroupParameter);
  PyOFXGroupParameterType.tp_base = &PyOFXParameterType;
  PyOFXGroupParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXGroupParameterType.tp_init = PyOFXGroupParameter_Init;
  PyOFXGroupParameterType.tp_getset = PyOFXGroupParameter_GetSeters;
  if (PyType_Ready(&PyOFXGroupParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXGroupParameterDescriptorType);
  PyModule_AddObject(mod, "GroupParameterDescriptor", (PyObject*)&PyOFXGroupParameterDescriptorType);
  
  Py_INCREF(&PyOFXGroupParameterType);
  PyModule_AddObject(mod, "GroupParameter", (PyObject*)&PyOFXGroupParameterType);
  
  return true;
}
