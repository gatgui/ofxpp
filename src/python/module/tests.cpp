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

static PyObject* PyOFXTest_Exception(PyObject *, PyObject *)
{
  bool failed = false;
  
  CATCH({throw ofx::ExistsError("File doesn't exist");}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

static PyMethodDef PyOFX_TestMethods[] =
{
  {"exception", PyOFXTest_Exception, METH_VARARGS, 0},
  {NULL, NULL, NULL, NULL}
};

bool PyOFX_InitTest(PyObject *mod)
{
  PyObject *tmod = Py_InitModule("ofx.tests", PyOFX_TestMethods);
  PyModule_AddObject(mod, "tests", tmod);
  return true;
}
