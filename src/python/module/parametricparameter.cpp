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
#include "entrypoints.h"

#ifdef OFX_API_1_2

PyTypeObject PyOFXParametricParameterDescriptorType;
PyTypeObject PyOFXParametricParameterType;

// ---

int PyOFXParametricParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::ParametricParameterDescriptor();
  return 0;
}

PyObject* PyOFXParametricParameterDescriptor_GetDimension(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ParametricParameterDescriptor *desc = (ofx::ParametricParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = desc->dimension();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

int PyOFXParametricParameterDescriptor_SetDimension(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::ParametricParameterDescriptor *desc = (ofx::ParametricParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  int d = PyInt_AsLong(val);
  
  CATCH({desc->dimension(d);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXParametricParameterDescriptor_GetRange(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ParametricParameterDescriptor *desc = (ofx::ParametricParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  double rmin, rmax;
  
  CATCH({desc->range(&rmin, &rmax);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", rmin, rmax);
}

int PyOFXParametricParameterDescriptor_SetRange(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyTuple_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple");
    return -1;
  }
  
  if (PyTuple_Size(val) != 2)
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple of 2 values");
    return -1;
  }
  
  double rmin = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
  double rmax = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
  
  ofx::ParametricParameterDescriptor *desc = (ofx::ParametricParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->range(rmin, rmax);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

PyObject* PyOFXParametricParameterDescriptor_GetInteractBackground(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ParametricParameterDescriptor *desc = (ofx::ParametricParameterDescriptor*) pdesc->desc;
  
  ofx::EntryPoint func = 0;
  
  bool failed = false;
  
  CATCH({func = desc->interactBackground();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyTuple_New(2);
  
  int idx = PyOFX_GetInteractFuncIndex(func);
  
  if (idx < 0 || idx >= PYOFX_MAX_ENTRY)
  {
    Py_INCREF(Py_None);
    PyTuple_SetItem(rv, 0, Py_None);
    
    Py_INCREF(Py_None);
    PyTuple_SetItem(rv, 1, Py_None);
  }
  else
  {
    Py_INCREF(gInteractDescClasses[idx]);
    PyTuple_SetItem(rv, 0, gInteractDescClasses[idx]);
    
    Py_INCREF(gInteractClasses[idx]);
    PyTuple_SetItem(rv, 1, gInteractClasses[idx]);
  }
  
  return rv;
}

int PyOFXParametricParameterDescriptor_SetInteractBackground(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  if (!PyTuple_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a tuple");
    return -1;
  }
  
  if (PyTuple_Size(val) != 2)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a tuple of 2 elements");
    return -1;
  }
  
  PyObject *descClass = PyTuple_GetItem(val, 0);
  if (!PyObject_IsSubclass(descClass, (PyObject*)&PyOFXInteractDescriptorType))
  {
    PyErr_SetString(PyExc_TypeError, "Tuple first element must be a sub class of ofx.InteractDescriptor");
    return -1;
  }
  
  PyObject *instClass = PyTuple_GetItem(val, 1);
  if (!PyObject_IsSubclass(instClass, (PyObject*)&PyOFXInteractType))
  {
    PyErr_SetString(PyExc_TypeError, "Tuple second element must be a sub class of ofx.Interact");
    return -1;
  }
  
  ofx::ParametricParameterDescriptor *desc = (ofx::ParametricParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->interactBackground(PyOFX_GetInteractFunc(descClass, instClass));}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXParametricParameterDescriptor_GetSeters[] =
{
  {(char*)"dimension", PyOFXParametricParameterDescriptor_GetDimension, PyOFXParametricParameterDescriptor_SetDimension, NULL, NULL},
  {(char*)"range", PyOFXParametricParameterDescriptor_GetRange, PyOFXParametricParameterDescriptor_SetRange, NULL, NULL},
  {(char*)"interactBackground", PyOFXParametricParameterDescriptor_GetInteractBackground, PyOFXParametricParameterDescriptor_SetInteractBackground, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXParametricParameterDescriptor_UIColour(PyObject *self, PyObject *args)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx;
  PyObject *val = 0;
  
  if (!PyArg_ParseTuple(args, "i|O", &idx, &val))
  {
    return NULL;
  }
  
  ofx::ParametricParameterDescriptor *desc = (ofx::ParametricParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  if (val)
  {
    if (!PyTuple_Check(val))
    {
      PyErr_SetString(PyExc_TypeError, "Expected a tuple");
      return NULL;
    }
    
    if (PyTuple_Size(val) != 3)
    {
      PyErr_SetString(PyExc_ValueError, "Expected a tuple of 3 values");
      return NULL;
    }
    
    ofx::RGBAColour<double> v;
    
    v.r = PyFloat_AsDouble(PyTuple_GetItem(val, 0));
    v.g = PyFloat_AsDouble(PyTuple_GetItem(val, 1));
    v.b = PyFloat_AsDouble(PyTuple_GetItem(val, 2));
    v.a = 1.0;
    
    CATCH({desc->UIColour(idx, v);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    Py_RETURN_NONE;
  }
  else
  {
    ofx::RGBAColour<double> rv = {0,0,0,1};
  
    CATCH({rv = desc->UIColour(idx);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    return Py_BuildValue("ddd", rv.r, rv.g, rv.b);
  }
}

PyObject* PyOFXParametricParameterDescriptor_DimensionLabel(PyObject *self, PyObject *args)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx;
  PyObject *val = 0;
  
  if (!PyArg_ParseTuple(args, "i|O", &idx, &val))
  {
    return NULL;
  }
  
  ofx::ParametricParameterDescriptor *desc = (ofx::ParametricParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  if (val)
  {
    if (!PyString_Check(val))
    {
      PyErr_SetString(PyExc_TypeError, "Expected a string");
      return NULL;
    }
    
    char *v = PyString_AsString(val);
    
    CATCH({desc->dimensionLabel(idx, v);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    Py_RETURN_NONE;
  }
  else
  {
    std::string rv;
  
    CATCH({rv = desc->dimensionLabel(idx);}, failed);
    
    if (failed)
    {
      return NULL;
    }
    
    return PyString_FromString(rv.c_str());
  }
}

static PyMethodDef PyOFXParametricParameterDescriptor_Methods[] =
{
  {"UIColour", PyOFXParametricParameterDescriptor_UIColour, METH_VARARGS, NULL},
  {"dimensionLabel", PyOFXParametricParameterDescriptor_DimensionLabel, METH_VARARGS, NULL},
  {NULL, NULL, NULL, NULL}
};

// ---

int PyOFXParametricParameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::ParametricParameter();
  return 0;
}

PyObject* PyOFXParametricParameter_GetDimension(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ParametricParameter *param = (ofx::ParametricParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->dimension();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXParametricParameter_GetRange(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ParametricParameter *param = (ofx::ParametricParameter*) pparam->param;
  
  bool failed = false;
  
  double rmin, rmax;
  
  CATCH({param->range(&rmin, &rmax);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", rmin, rmax);
}

PyObject* PyOFXParametricParameter_GetInteractBackground(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::ParametricParameter *param = (ofx::ParametricParameter*) pparam->param;
  
  ofx::EntryPoint func = 0;
  
  bool failed = false;
  
  CATCH({func = param->interactBackground();}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  PyObject *rv = PyTuple_New(2);
  
  int idx = PyOFX_GetInteractFuncIndex(func);
  
  if (idx < 0 || idx >= PYOFX_MAX_ENTRY)
  {
    Py_INCREF(Py_None);
    PyTuple_SetItem(rv, 0, Py_None);
    
    Py_INCREF(Py_None);
    PyTuple_SetItem(rv, 1, Py_None);
  }
  else
  {
    Py_INCREF(gInteractDescClasses[idx]);
    PyTuple_SetItem(rv, 0, gInteractDescClasses[idx]);
    
    Py_INCREF(gInteractClasses[idx]);
    PyTuple_SetItem(rv, 1, gInteractClasses[idx]);
  }
  
  return rv;
}

static PyGetSetDef PyOFXParametricParameter_GetSeters[] =
{
  {(char*)"dimension", PyOFXParametricParameter_GetDimension, NULL, NULL, NULL},
  {(char*)"range", PyOFXParametricParameter_GetRange, NULL, NULL, NULL},
  {(char*)"interactBackground", PyOFXParametricParameter_GetInteractBackground, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};


PyObject* PyOFXParametricParameter_UIColour(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx;
  
  if (!PyArg_ParseTuple(args, "i", &idx))
  {
    return NULL;
  }
  
  ofx::ParametricParameter *param = (ofx::ParametricParameter*) pparam->param;
  
  bool failed = false;
  
  ofx::RGBAColour<double> rv = {0,0,0,1};

  CATCH({rv = param->UIColour(idx);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("ddd", rv.r, rv.g, rv.b);
}

PyObject* PyOFXParametricParameter_DimensionLabel(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx;
  
  if (!PyArg_ParseTuple(args, "i", &idx))
  {
    return NULL;
  }
  
  ofx::ParametricParameter *param = (ofx::ParametricParameter*) pparam->param;
  
  bool failed = false;
  
  std::string rv;

  CATCH({rv = param->dimensionLabel(idx);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyString_FromString(rv.c_str());
}

PyObject* PyOFXParametricParameter_GetControlPointsCount(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx;
  double t;
  
  if (!PyArg_ParseTuple(args, "id", &idx, &t))
  {
    return NULL;
  }
  
  ofx::ParametricParameter *param = (ofx::ParametricParameter*) pparam->param;
  
  bool failed = false;
  
  int rv = 0;
  
  CATCH({rv = param->getControlPointsCount(idx, t);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyInt_FromLong(rv);
}

PyObject* PyOFXParametricParameter_GetControlPoint(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int cidx;
  double t;
  int pidx;
  
  if (!PyArg_ParseTuple(args, "idi", &cidx, &t, &pidx))
  {
    return NULL;
  }
  
  ofx::ParametricParameter *param = (ofx::ParametricParameter*) pparam->param;
  
  bool failed = false;
  
  double pos, val;
  
  CATCH({param->getControlPoint(cidx, t, pidx, &pos, &val);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return Py_BuildValue("dd", pos, val);
}

PyObject* PyOFXParametricParameter_SetControlPoint(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int cidx;
  double t;
  int pidx;
  double pos;
  double val;
  PyObject *addKey;
  
  if (!PyArg_ParseTuple(args, "ididdO", &cidx, &t, &pidx, &pos, &val, &addKey))
  {
    return NULL;
  }
  
  ofx::ParametricParameter *param = (ofx::ParametricParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->setControlPoint(cidx, t, pidx, pos, val, (addKey == Py_True));}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXParametricParameter_AddControlPoint(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int cidx;
  double t;
  double pos;
  double val;
  PyObject *addKey;
  
  if (!PyArg_ParseTuple(args, "idddO", &cidx, &t, &pos, &val, &addKey))
  {
    return NULL;
  }
  
  ofx::ParametricParameter *param = (ofx::ParametricParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->addControlPoint(cidx, t, pos, val, (addKey == Py_True));}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXParametricParameter_DeleteControlPoint(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int cidx;
  int pidx;
  
  if (!PyArg_ParseTuple(args, "ii", &cidx, &pidx))
  {
    return NULL;
  }
  
  ofx::ParametricParameter *param = (ofx::ParametricParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->deleteControlPoint(cidx, pidx);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXParametricParameter_DeleteAllControlPoints(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx;
  
  if (!PyArg_ParseTuple(args, "i", &idx))
  {
    return NULL;
  }
  
  ofx::ParametricParameter *param = (ofx::ParametricParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->deleteAllControlPoints(idx);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXParametricParameter_Eval(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int idx;
  double t;
  double p;
  
  if (!PyArg_ParseTuple(args, "idd", &idx, &t, &p))
  {
    return NULL;
  }
  
  ofx::ParametricParameter *param = (ofx::ParametricParameter*) pparam->param;
  
  bool failed = false;
  
  double rv = 0.0;
  
  CATCH({rv = param->eval(idx, t, p);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  return PyFloat_FromDouble(rv);
}

static PyMethodDef PyOFXParametricParameter_Methods[] =
{
  {"UIColour", PyOFXParametricParameter_UIColour, METH_VARARGS, NULL},
  {"dimensionLabel", PyOFXParametricParameter_DimensionLabel, METH_VARARGS, NULL},
  {"getControlPointsCount", PyOFXParametricParameter_GetControlPointsCount, METH_VARARGS, NULL},
  {"getControlPoint", PyOFXParametricParameter_GetControlPoint, METH_VARARGS, NULL},
  {"setControlPoint", PyOFXParametricParameter_SetControlPoint, METH_VARARGS, NULL},
  {"addControlPoint", PyOFXParametricParameter_AddControlPoint, METH_VARARGS, NULL},
  {"deleteControlPoint", PyOFXParametricParameter_DeleteControlPoint, METH_VARARGS, NULL},
  {"deleteAllControlPoints", PyOFXParametricParameter_DeleteAllControlPoints, METH_VARARGS, NULL},
  {"eval", PyOFXParametricParameter_Eval, METH_VARARGS, NULL},
  {NULL, NULL, NULL, NULL}
};

// ---

bool PyOFX_InitParameter_Parametric(PyObject *mod)
{
  INIT_TYPE(PyOFXParametricParameterDescriptorType, "ofx.ParametricParameterDescriptor", PyOFXParametricParameterDescriptor);
  PyOFXParametricParameterDescriptorType.tp_base = &PyOFXValueParameterDescriptorType;
  PyOFXParametricParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXParametricParameterDescriptorType.tp_init = PyOFXParametricParameterDescriptor_Init;
  PyOFXParametricParameterDescriptorType.tp_getset = PyOFXParametricParameterDescriptor_GetSeters;
  PyOFXParametricParameterDescriptorType.tp_methods = PyOFXParametricParameterDescriptor_Methods;
  if (PyType_Ready(&PyOFXParametricParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXParametricParameterType, "ofx.ParametricParameter", PyOFXParametricParameter);
  PyOFXParametricParameterType.tp_base = &PyOFXValueParameterType;
  PyOFXParametricParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXParametricParameterType.tp_init = PyOFXParametricParameter_Init;
  PyOFXParametricParameterType.tp_getset = PyOFXParametricParameter_GetSeters;
  PyOFXParametricParameterType.tp_methods = PyOFXParametricParameter_Methods;
  if (PyType_Ready(&PyOFXParametricParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXParametricParameterDescriptorType);
  PyModule_AddObject(mod, "ParametricParameterDescriptor", (PyObject*)&PyOFXParametricParameterDescriptorType);
  
  Py_INCREF(&PyOFXParametricParameterType);
  PyModule_AddObject(mod, "ParametricParameter", (PyObject*)&PyOFXParametricParameterType);
  
  return true;
}

#endif
