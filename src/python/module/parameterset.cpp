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

PyTypeObject PyOFXParameterSetType;
PyTypeObject PyOFXParameterSetDescriptorType;

// ---

std::map<PyInterpolatorKey, PyObject*> gPyInterpolators;

std::string PyInterpolator(ofx::ParameterSet &params,
                           const std::string &paramName,
                           ofx::Time t,
                           ofx::Time t0, const std::string &v0,
                           ofx::Time t1, const std::string &v1,
                           double amount)
{
  PyInterpolatorKey key = {params.handle(), paramName};
  
  std::map<PyInterpolatorKey, PyObject*>::iterator it = gPyInterpolators.find(key);
  
  if (it == gPyInterpolators.end())
  {
    throw ofx::FailedError("No associated python interpolation function");
  }
  
  PyObject *ppset = PyObject_CallObject((PyObject*)&PyOFXParameterSetType, NULL);
  ofx::ParameterSet *pset = ((PyOFXParameterSet*)ppset)->pset;
  *pset = params;
  
  PyObject *args = Py_BuildValue("Osddsdsd", ppset, paramName.c_str(), t, t0, v0.c_str(), t1, v1.c_str(), amount);
  
  PyObject *iv = PyObject_CallObject(it->second, args);
  
  Py_DECREF(args);
  Py_DECREF(ppset);
  
  if (!PyString_Check(iv))
  {
    Py_DECREF(iv);
    throw ofx::ValueError("Python interpolation function should return a string");
  }
  
  std::string rv = PyString_AsString(iv);
  Py_DECREF(iv);
  
  return rv;
}

// ---

