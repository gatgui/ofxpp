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

/*
PyTypeObject PyOFXPlugin;
PyTypeObject PyOFXImageEffectPlugin;

// ---

PyObject* PyOFXPlugin_new(PyTypeObject *type, PyObject *args, PyObject *kwargs)
{
  PyObject *self = type->tp_alloc(type, 1);
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  pplugin->plugin = new ofx::Plugin();
  return self;
}

int PyOFXPlugin_init(PyObject *self, PyObject *args, PyObject *kwargs)
{
  return 0;
}

void PyOFXPlugin_delete(PyObject *self)
{
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  if (pplugin->plugin && pplugin->owns)
  {
    delete pplugin->plugin;
  }
  self->ob_type->tp_free(self);
}

PyObject* PyOFXPlugin_getMajorVersion(PyObject *self, void*)
{
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  return PyInt_FromLong(pplugin->plugin->getMajorVersion());
}

int PyOFXPlugin_setMajorVersion(PyObject *self, PyObject *value, void*)
{
  if (!PyInt_Check(value))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  
  int v = PyInt_AsLong(value);
  
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  pplugin->plugin->setMajorVersion(v);
  
  return 0;
}

PyObject* PyOFXPlugin_getMinorVersion(PyObject *self, void*)
{
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  return PyInt_FromLong(pplugin->plugin->getMinorVersion());
}

int PyOFXPlugin_setMinorVersion(PyObject *self, PyObject *value, void*)
{
  if (!PyInt_Check(value))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  
  int v = PyInt_AsLong(value);
  
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  pplugin->plugin->setMinorVersion(v);
  
  return 0;
}

PyObject* PyOFXPlugin_getID(PyObject *self, void*)
{
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  return PyString_FromString(pplugin->plugin->getID());
}

int PyOFXPlugin_setID(PyObject *self, PyObject *value, void*)
{
  if (!PyString_Check(value))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a string");
    return -1;
  }
  
  const char *id = PyString_AsString(value);
  
  PyOFXPlugin *pplugin = (PyOFXPlugin*) self;
  pplugin->plugin->setID(id);
  
  return 0;
}

static PyGetSetDef PyOFXPlugin_getsetters[] =
{
  {"majorVersion", PyOFXPlugin_getMajorVersion, PyOFXPlugin_setMajorVersion, 0},
  {"minorVersion", PyOFXPlugin_getMinorVersion, PyOFXPlugin_setMinorVersion, 0},
  {"majorVersion", PyOFXPlugin_getID, PyOFXPlugin_setID, 0},
  {NULL}
};

PyObject* PyOFXImageEffectPlugin_load(PyObject *self, PyObject *)
{
}

PyObject* PyOFXImageEffectPlugin_unload(PyObject *self, PyObject *)
{
}

PyObject* PyOFXImageEffectPlugin_getHost(PyObject *self, PyObject *)
{
}
*/
// ---

bool PyOFX_InitPlugin(PyObject *)
{
  return true;
}

