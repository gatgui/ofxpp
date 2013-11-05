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

PyTypeObject PyOFXHostType;
PyTypeObject PyOFXImageEffectHostType;

// ---

PyObject* PyOFXHost_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  if (self != 0)
  {
    ((PyOFXHost*)self)->host = 0;
  }
  return self;
}

int PyOFXHost_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

void PyOFXHost_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXHost_GetTimeLineSuite(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  if (!phost->host->timeLineSuite())
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*) &PyOFXTimeLineSuiteType, NULL);
    ((PyOFXTimeLineSuite*)rv)->suite = phost->host->timeLineSuite();
    return rv;
  }
}

PyObject* PyOFXHost_GetProgressSuite(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  if (!phost->host->progressSuite())
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*) &PyOFXProgressSuiteType, NULL);
    ((PyOFXProgressSuite*)rv)->suite = phost->host->progressSuite();
    return rv;
  }
}

PyObject* PyOFXHost_GetMessageSuite(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  if (!phost->host->messageSuite())
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*) &PyOFXMessageSuiteType, NULL);
    ((PyOFXMessageSuite*)rv)->suite = phost->host->messageSuite();
    return rv;
  }
}

PyObject* PyOFXHost_GetMemorySuite(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  if (!phost->host->memorySuite())
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*) &PyOFXMemorySuiteType, NULL);
    ((PyOFXMemorySuite*)rv)->suite = phost->host->memorySuite();
    return rv;
  }
}

PyObject* PyOFXHost_GetAPIMajorVersion(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = phost->host->APIMajorVersion();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXHost_GetAPIMinorVersion(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = phost->host->APIMinorVersion();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

#ifdef OFX_API_1_2

PyObject* PyOFXHost_GetMajorVersion(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = phost->host->majorVersion();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXHost_GetMinorVersion(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = phost->host->minorVersion();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXHost_GetVersionLabel(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = phost->host->versionLabel();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXHost_GetOSHandle(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  void *handle = 0;
  
  CATCH({handle = phost->host->OSHandle();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  if (handle)
  {
    Py_RETURN_NONE;
  }
  else
  {
    PyObject *rv = PyObject_CallObject((PyObject*) &PyOFXHandleType, NULL);
    ((PyOFXHandle*)rv)->handle = handle;
    return rv;
  }
}

#endif

static PyGetSetDef PyOFXHost_GetSeters[] =
{
  {(char*)"APIMajorVersion", PyOFXHost_GetAPIMajorVersion, NULL, NULL, NULL},
  {(char*)"APIMinorVersion", PyOFXHost_GetAPIMinorVersion, NULL, NULL, NULL},
  {(char*)"messageSuite", PyOFXHost_GetMessageSuite, NULL, NULL, NULL},
  {(char*)"progressSuite", PyOFXHost_GetProgressSuite, NULL, NULL, NULL},
  {(char*)"memorySuite", PyOFXHost_GetMemorySuite, NULL, NULL, NULL},
  {(char*)"timeLineSuite", PyOFXHost_GetTimeLineSuite, NULL, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"majorVersion", PyOFXHost_GetMajorVersion, NULL, NULL, NULL},
  {(char*)"minorVersion", PyOFXHost_GetMinorVersion, NULL, NULL, NULL},
  {(char*)"versionLabel", PyOFXHost_GetVersionLabel, NULL, NULL, NULL},
  {(char*)"OSHandle", PyOFXHost_GetOSHandle, NULL, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXHost_APIVersion(PyObject *self, PyObject *args)
{
  int level, v = 0;
  
  if (!PyArg_ParseTuple(args, "i", &level))
  {
    return NULL;
  }
  
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({v = phost->host->APIVersion(level);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(v);
}

PyObject* PyOFXHost_CheckAPIVersion(PyObject *self, PyObject *args)
{
  int maj, min;
  
  if (!PyArg_ParseTuple(args, "ii", &maj, &min))
  {
    return NULL;
  }
  
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = phost->host->checkAPIVersion(maj, min);}, failed);
  
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

#ifdef OFX_API_1_2

PyObject* PyOFXHost_Version(PyObject *self, PyObject *args)
{
  int level, v = 0;
  
  if (!PyArg_ParseTuple(args, "i", &level))
  {
    return NULL;
  }
  
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  bool failed = false;
  
  CATCH({v = phost->host->version(level);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(v);
}

#endif

static PyMethodDef PyOFXHost_Methods[] =
{
  {"APIVersion", PyOFXHost_APIVersion, METH_VARARGS, NULL},
  {"checkAPIVersion", PyOFXHost_CheckAPIVersion, METH_VARARGS, NULL},
#ifdef OFX_API_1_2
  {"version", PyOFXHost_Version, METH_VARARGS, NULL},
#endif
  {NULL, NULL, 0, NULL}
};

// ---

int PyOFXImageEffectHost_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

PyObject* PyOFXImageEffectHost_GetName(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = host->name();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXImageEffectHost_GetLabel(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  std::string rv;
  
  CATCH({rv = host->label();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXImageEffectHost_GetIsBackground(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->isBackground();}, failed);
  
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

PyObject* PyOFXImageEffectHost_GetSupportsOverlays(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->supportsOverlays();}, failed);
  
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

PyObject* PyOFXImageEffectHost_GetSupportsMultiResolution(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->supportsMultiResolution();}, failed);
  
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

PyObject* PyOFXImageEffectHost_GetSupportsTiles(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->supportsTiles();}, failed);
  
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

PyObject* PyOFXImageEffectHost_GetTemporalClipAccess(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->temporalClipAccess();}, failed);
  
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

PyObject* PyOFXImageEffectHost_GetSupportsMultipleClipDepths(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->supportsMultipleClipDepths();}, failed);
  
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

PyObject* PyOFXImageEffectHost_GetSupportsMultipleClipPARs(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->supportsMultipleClipPARs();}, failed);
  
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

PyObject* PyOFXImageEffectHost_GetSetableFrameRate(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->setableFrameRate();}, failed);
  
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

PyObject* PyOFXImageEffectHost_GetSetableFielding(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->setableFielding();}, failed);
  
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

PyObject* PyOFXImageEffectHost_GetSupportsCustomAnimation(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->supportsCustomAnimation();}, failed);
  
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

PyObject* PyOFXImageEffectHost_GetSupportsStringAnimation(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->supportsStringAnimation();}, failed);
  
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

PyObject* PyOFXImageEffectHost_GetSupportsBooleanAnimation(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->supportsBooleanAnimation();}, failed);
  
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

PyObject* PyOFXImageEffectHost_GetSupportsChoiceAnimation(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->supportsChoiceAnimation();}, failed);
  
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

PyObject* PyOFXImageEffectHost_GetSupportsCustomInteract(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->supportsCustomInteract();}, failed);
  
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

PyObject* PyOFXImageEffectHost_GetMaxParameters(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = host->maxParameters();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectHost_GetMaxPages(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = host->maxPages();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectHost_GetPageRowColumnCount(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  int r, c;
  
  CATCH({host->pageRowColumnCount(&r, &c);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ii", r, c);
}

#ifdef OFX_API_1_2

PyObject* PyOFXImageEffectHost_GetSequentialRender(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(host->sequentialRender());}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectHost_GetSupportsParametricAnimation(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->supportsParametricAnimation();}, failed);
  
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

#ifdef OFX_API_1_3

PyObject* PyOFXImageEffectHost_GetSupportsOpenGLRender(PyObject *self, void*)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = false;
  
  CATCH({rv = host->supportsOpenGLRender();}, failed);
  
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

static PyGetSetDef PyOFXImageEffectHost_GetSeters[] =
{
  {(char*)"name", PyOFXImageEffectHost_GetName, NULL, NULL, NULL},
  {(char*)"label", PyOFXImageEffectHost_GetLabel, NULL, NULL, NULL},
  {(char*)"isBackground", PyOFXImageEffectHost_GetIsBackground, NULL, NULL, NULL},
  {(char*)"supportsOverlays", PyOFXImageEffectHost_GetSupportsOverlays, NULL, NULL, NULL},
  {(char*)"supportsMultiResolution", PyOFXImageEffectHost_GetSupportsMultiResolution, NULL, NULL, NULL},
  {(char*)"supportsTiles", PyOFXImageEffectHost_GetSupportsTiles, NULL, NULL, NULL},
  {(char*)"temporalClipAccess", PyOFXImageEffectHost_GetTemporalClipAccess, NULL, NULL, NULL},
  {(char*)"supportsMultipleClipDepths", PyOFXImageEffectHost_GetSupportsMultipleClipDepths, NULL, NULL, NULL},
  {(char*)"supportsMultipleClipPARs", PyOFXImageEffectHost_GetSupportsMultipleClipPARs, NULL, NULL, NULL},
  {(char*)"setableFrameRate", PyOFXImageEffectHost_GetSetableFrameRate, NULL, NULL, NULL},
  {(char*)"setableFielding", PyOFXImageEffectHost_GetSetableFielding, NULL, NULL, NULL},
  {(char*)"supportsCustomAnimation", PyOFXImageEffectHost_GetSupportsCustomAnimation, NULL, NULL, NULL},
  {(char*)"supportsStringAnimation", PyOFXImageEffectHost_GetSupportsStringAnimation, NULL, NULL, NULL},
  {(char*)"supportsChoiceAnimation", PyOFXImageEffectHost_GetSupportsChoiceAnimation, NULL, NULL, NULL},
  {(char*)"supportsBooleanAnimation", PyOFXImageEffectHost_GetSupportsBooleanAnimation, NULL, NULL, NULL},
  {(char*)"supportsCustomInteract", PyOFXImageEffectHost_GetSupportsCustomInteract, NULL, NULL, NULL},
  {(char*)"maxParameters", PyOFXImageEffectHost_GetMaxParameters, NULL, NULL, NULL},
  {(char*)"maxPages", PyOFXImageEffectHost_GetMaxPages, NULL, NULL, NULL},
  {(char*)"pageRowColumnCount", PyOFXImageEffectHost_GetPageRowColumnCount, NULL, NULL, NULL},
#ifdef OFX_API_1_2
  {(char*)"sequentialRender", PyOFXImageEffectHost_GetSequentialRender, NULL, NULL, NULL},
  {(char*)"supportsParametricAnimation", PyOFXImageEffectHost_GetSupportsParametricAnimation, NULL, NULL, NULL},
#endif
#ifdef OFX_API_1_3
  {(char*)"supportsOpenGLRender", PyOFXImageEffectHost_GetSupportsOpenGLRender, NULL, NULL, NULL},
#endif
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXImageEffectHost_SupportedComponentsCount(PyObject *self, PyObject *)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = host->supportedComponentsCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectHost_SupportedComponent(PyObject *self, PyObject *args)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx = 0;
  
  if (!PyArg_ParseTuple(args, "i", &idx))
  {
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(host->supportedComponent(idx));}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectHost_SupportedContextsCount(PyObject *self, PyObject *)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = host->supportedContextsCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectHost_SupportedContext(PyObject *self, PyObject *args)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx = 0;
  
  if (!PyArg_ParseTuple(args, "i", &idx))
  {
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(host->supportedContext(idx));}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectHost_SupportedPixelDepthsCount(PyObject *self, PyObject *)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = host->supportedPixelDepthsCount();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXImageEffectHost_SupportedPixelDepth(PyObject *self, PyObject *args)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx = 0;
  
  if (!PyArg_ParseTuple(args, "i", &idx))
  {
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = int(host->supportedPixelDepth(idx));}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

#ifdef OFX_API_1_3

PyObject* PyOFXImageEffectHost_FlushOpenGLResources(PyObject *self, PyObject *)
{
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ImageEffectHost *host = (ofx::ImageEffectHost*) phost->host;
  
  bool failed = false;
  
  bool rv = 0;
  
  CATCH({rv = host->flushOpenGLResources();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *prv = (rv ? Py_True : Py_False);
  Py_INCREF(prv);
  return prv;
}

#endif

static PyMethodDef PyOFXImageEffectHost_Methods[] =
{
  {"supportedComponentsCount", PyOFXImageEffectHost_SupportedComponentsCount, METH_VARARGS, NULL},
  {"supportedComponent", PyOFXImageEffectHost_SupportedComponent, METH_VARARGS, NULL},
  {"supportedContextsCount", PyOFXImageEffectHost_SupportedContextsCount, METH_VARARGS, NULL},
  {"supportedContext", PyOFXImageEffectHost_SupportedContext, METH_VARARGS, NULL},
  {"supportedPixelDepthsCount", PyOFXImageEffectHost_SupportedPixelDepthsCount, METH_VARARGS, NULL},
  {"supportedPixelDepth", PyOFXImageEffectHost_SupportedPixelDepth, METH_VARARGS, NULL},
#ifdef OFX_API_1_3
  {"flushOpenGLResources", PyOFXImageEffectHost_FlushOpenGLResources, METH_VARARGS, NULL},
#endif
  {NULL, NULL, 0, NULL}
};

// ---

bool PyOFX_InitHost(PyObject *mod)
{
  INIT_TYPE(PyOFXHostType, "ofx.Host", PyOFXHost);
  PyOFXHostType.tp_new = PyOFXHost_New;
  PyOFXHostType.tp_init = PyOFXHost_Init;
  PyOFXHostType.tp_dealloc = PyOFXHost_Delete;
  PyOFXHostType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXHostType.tp_getset = PyOFXHost_GetSeters;
  PyOFXHostType.tp_methods = PyOFXHost_Methods;
  
  INIT_TYPE(PyOFXImageEffectHostType, "ofx.ImageEffectHost", PyOFXImageEffectHost);
  PyOFXImageEffectHostType.tp_init = PyOFXImageEffectHost_Init;
  PyOFXImageEffectHostType.tp_base = &PyOFXHostType;
  PyOFXImageEffectHostType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXImageEffectHostType.tp_getset = PyOFXImageEffectHost_GetSeters;
  PyOFXImageEffectHostType.tp_methods = PyOFXImageEffectHost_Methods;
  
  if (PyType_Ready(&PyOFXHostType) < 0)
  {
    return false;
  }
  
  if (PyType_Ready(&PyOFXImageEffectHostType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXHostType);
  PyModule_AddObject(mod, "Host", (PyObject *)&PyOFXHostType);
  
  Py_INCREF(&PyOFXImageEffectHostType);
  PyModule_AddObject(mod, "ImageEffectHost", (PyObject *)&PyOFXImageEffectHostType);
  
  return true;
}
