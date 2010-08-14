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
  PyErr_SetString(PyExc_RuntimeError, "ofx.Host cannot be instanciated on client side");
  return -1;
}

void PyOFXHost_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

/*
inline TimeLineSuite* getTimeLineSuite() {return mTimeLine;}
inline ProgressSuite* getProgressSuite() {return mProgress;}
inline MessageSuite* getMessageSuite() {return mMessage;}
inline MemorySuite* getMemorySuite() {return mMemory;}
*/
PyObject* PyOFXHost_GetAPIVersion(PyObject *self, PyObject *args)
{
  int level, v;
  
  if (!PyArg_ParseTuple(args, "i", &level))
  {
    return NULL;
  }
  
  PyOFXHost *phost = (PyOFXHost*)self;
  
  if (!phost->host)
  {
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
/*
int getAPIMajorVersion();
int getAPIMinorVersion();
bool checkAPIVersion(int major, int minor);
#ifdef OFX_API_1_2
  int getVersion(int level=0);
  int getMajorVersion();
  int getMinorVersion();
  std::string getVersionLabel();
#endif
*/

/*
// general properties
std::string getName();
std::string getLabel();

// image effect properties
bool isBackground();
bool supportOverlays();
bool supportMultiResolution();
bool supportTiles();
bool supportTemporalClipAccess();
int getSupportedComponentsCount();
ImageComponent getSupportedComponent(int idx);
int getSupportedContextsCount();
ImageEffectContext getSupportedContext(int idx);
int getSupportedPixelDepthsCount();
BitDepth getSupportedPixelDepth(int idx);
bool supportMultipleClipDepths();
bool supportMultipleClipPARs();
bool isFramerateSetable();
bool isFieldingSetable();

#ifdef OFX_API_1_2
SequentialRender getSequentialRender();
bool supportParametricParamAnimation();
#endif

// parameter properties
bool supportCustomParamAnimation();
bool supportStringParamAnimation();
bool supportChoiceParamAnimation();
bool supportBooleanParamAnimation();
bool supportParamCustomInteract();
int getMaxParameters();
int getMaxParameterPages();
void getParameterPageRowColumnCount(int &rowCount, int &columnCount);
*/

// ---

bool PyOFX_InitHost(PyObject *)
{
  /*
  PyOFXHostType.tp_new = PyOFXHost_New;
  PyOFXHostType.tp_init = PyOFXHost_Init;
  PyOFXHostType.tp_dealloc = PyOFXHost_Delete;
  PyOFXHostType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXHostType.tp_doc = "OFX Host base class";
  
  if (PyType_Ready(&PyOFXHostType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXHostType);
  PyModule_AddObject(mod, "Host", (PyObject *)&PyOFXHostType);
  */
  
  return true;
}
