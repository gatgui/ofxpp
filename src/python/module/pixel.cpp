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
#include <ofx/ofx.h>

PyTypeObject PyOFXRGBAColourBType;
PyTypeObject PyOFXRGBAColourSType;
PyTypeObject PyOFXRGBAColourFType;
PyTypeObject PyOFXRGBAColourDType;
PyTypeObject PyOFXRGBColourBType;
PyTypeObject PyOFXRGBColourSType;
PyTypeObject PyOFXRGBColourFType;
PyTypeObject PyOFXRGBColourDType;
PyTypeObject PyOFXYUVAColourBType;
PyTypeObject PyOFXYUVAColourSType;
PyTypeObject PyOFXYUVAColourFType;
PyTypeObject PyOFXYUVAColourDType;

// ---

PyObject* PyOFXRGBAColourB_New(PyTypeObject *t, PyObject *, PyObject *)
{
  return t->tp_alloc(t, 0);
}

int PyOFXRGBAColourB_Init(PyObject *self, PyObject *args, PyObject *)
{
  PyOFXRGBAColourB *pcolour = (PyOFXRGBAColourB*) self;
  
  Py_ssize_t n = PyTuple_Size(args);
  if (n == 4)
  {
    int r, g, b, a;
    if (!PyArg_ParseTuple(args, "iiii", &r, &g, &b, &a))
    {
      return -1;
    }
    pcolour->colour.r = (unsigned char) r;
    pcolour->colour.g = (unsigned char) g;
    pcolour->colour.b = (unsigned char) b;
    pcolour->colour.a = (unsigned char) a;
  }
  else if (n != 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Invalid argument(s) count. Accepts 0 or 4 arguments.");
    return -1;
  }
  else
  {
    pcolour->colour.r = 0;
    pcolour->colour.g = 0;
    pcolour->colour.b = 0;
    pcolour->colour.a = 255;
  }
  
  return 0;
}

void PyOFXRGBAColourB_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXRGBAColourB_GetR(PyObject *self, void*)
{
  PyOFXRGBAColourB *pcolour = (PyOFXRGBAColourB*) self;
  return PyInt_FromLong(pcolour->colour.r);
}

PyObject* PyOFXRGBAColourB_GetG(PyObject *self, void*)
{
  PyOFXRGBAColourB *pcolour = (PyOFXRGBAColourB*) self;
  return PyInt_FromLong(pcolour->colour.g);
}

PyObject* PyOFXRGBAColourB_GetB(PyObject *self, void*)
{
  PyOFXRGBAColourB *pcolour = (PyOFXRGBAColourB*) self;
  return PyInt_FromLong(pcolour->colour.b);
}

PyObject* PyOFXRGBAColourB_GetA(PyObject *self, void*)
{
  PyOFXRGBAColourB *pcolour = (PyOFXRGBAColourB*) self;
  return PyInt_FromLong(pcolour->colour.a);
}

int PyOFXRGBAColourB_SetR(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXRGBAColourB *pcolour = (PyOFXRGBAColourB*) self;
  pcolour->colour.r = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBAColourB_SetG(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXRGBAColourB *pcolour = (PyOFXRGBAColourB*) self;
  pcolour->colour.g = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBAColourB_SetB(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXRGBAColourB *pcolour = (PyOFXRGBAColourB*) self;
  pcolour->colour.b = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBAColourB_SetA(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXRGBAColourB *pcolour = (PyOFXRGBAColourB*) self;
  pcolour->colour.a = (unsigned char) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef PyOFXRGBAColourB_GetSeters[] =
{
  {(char*)"r", PyOFXRGBAColourB_GetR, PyOFXRGBAColourB_SetR, NULL, NULL},
  {(char*)"g", PyOFXRGBAColourB_GetG, PyOFXRGBAColourB_SetG, NULL, NULL},
  {(char*)"b", PyOFXRGBAColourB_GetB, PyOFXRGBAColourB_SetB, NULL, NULL},
  {(char*)"a", PyOFXRGBAColourB_GetA, PyOFXRGBAColourB_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXRGBAColourS_New(PyTypeObject *t, PyObject *, PyObject *)
{
  return t->tp_alloc(t, 0);
}

int PyOFXRGBAColourS_Init(PyObject *self, PyObject *args, PyObject *)
{
  PyOFXRGBAColourS *pcolour = (PyOFXRGBAColourS*) self;
  
  Py_ssize_t n = PyTuple_Size(args);
  if (n == 4)
  {
    int r, g, b, a;
    if (!PyArg_ParseTuple(args, "iiii", &r, &g, &b, &a))
    {
      return -1;
    }
    pcolour->colour.r = (unsigned short) r;
    pcolour->colour.g = (unsigned short) g;
    pcolour->colour.b = (unsigned short) b;
    pcolour->colour.a = (unsigned short) a;
  }
  else if (n != 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Invalid argument(s) count. Accepts 0 or 4 arguments.");
    return -1;
  }
  else
  {
    pcolour->colour.r = 0;
    pcolour->colour.g = 0;
    pcolour->colour.b = 0;
    pcolour->colour.a = std::numeric_limits<unsigned short>::max();
  }
  
  return 0;
}

void PyOFXRGBAColourS_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXRGBAColourS_GetR(PyObject *self, void*)
{
  PyOFXRGBAColourS *pcolour = (PyOFXRGBAColourS*) self;
  return PyInt_FromLong(pcolour->colour.r);
}

PyObject* PyOFXRGBAColourS_GetG(PyObject *self, void*)
{
  PyOFXRGBAColourS *pcolour = (PyOFXRGBAColourS*) self;
  return PyInt_FromLong(pcolour->colour.g);
}

PyObject* PyOFXRGBAColourS_GetB(PyObject *self, void*)
{
  PyOFXRGBAColourS *pcolour = (PyOFXRGBAColourS*) self;
  return PyInt_FromLong(pcolour->colour.b);
}

PyObject* PyOFXRGBAColourS_GetA(PyObject *self, void*)
{
  PyOFXRGBAColourS *pcolour = (PyOFXRGBAColourS*) self;
  return PyInt_FromLong(pcolour->colour.a);
}

int PyOFXRGBAColourS_SetR(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXRGBAColourS *pcolour = (PyOFXRGBAColourS*) self;
  pcolour->colour.r = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBAColourS_SetG(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXRGBAColourS *pcolour = (PyOFXRGBAColourS*) self;
  pcolour->colour.g = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBAColourS_SetB(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXRGBAColourS *pcolour = (PyOFXRGBAColourS*) self;
  pcolour->colour.b = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBAColourS_SetA(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXRGBAColourS *pcolour = (PyOFXRGBAColourS*) self;
  pcolour->colour.a = (unsigned short) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef PyOFXRGBAColourS_GetSeters[] =
{
  {(char*)"r", PyOFXRGBAColourS_GetR, PyOFXRGBAColourS_SetR, NULL, NULL},
  {(char*)"g", PyOFXRGBAColourS_GetG, PyOFXRGBAColourS_SetG, NULL, NULL},
  {(char*)"b", PyOFXRGBAColourS_GetB, PyOFXRGBAColourS_SetB, NULL, NULL},
  {(char*)"a", PyOFXRGBAColourS_GetA, PyOFXRGBAColourS_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXRGBAColourF_New(PyTypeObject *t, PyObject *, PyObject *)
{
  return t->tp_alloc(t, 0);
}

int PyOFXRGBAColourF_Init(PyObject *self, PyObject *args, PyObject *)
{
  PyOFXRGBAColourF *pcolour = (PyOFXRGBAColourF*) self;
  
  Py_ssize_t n = PyTuple_Size(args);
  if (n == 4)
  {
    if (!PyArg_ParseTuple(args, "ffff", &(pcolour->colour.r), &(pcolour->colour.g), &(pcolour->colour.b), &(pcolour->colour.a)))
    {
      return -1;
    }
  }
  else if (n != 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Invalid argument(s) count. Accepts 0 or 4 arguments.");
    return -1;
  }
  else
  {
    pcolour->colour.r = 0.0f;
    pcolour->colour.g = 0.0f;
    pcolour->colour.b = 0.0f;
    pcolour->colour.a = 1.0f;
  }
  
  return 0;
}

void PyOFXRGBAColourF_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXRGBAColourF_GetR(PyObject *self, void*)
{
  PyOFXRGBAColourF *pcolour = (PyOFXRGBAColourF*) self;
  return PyFloat_FromDouble(pcolour->colour.r);
}

PyObject* PyOFXRGBAColourF_GetG(PyObject *self, void*)
{
  PyOFXRGBAColourF *pcolour = (PyOFXRGBAColourF*) self;
  return PyFloat_FromDouble(pcolour->colour.g);
}

PyObject* PyOFXRGBAColourF_GetB(PyObject *self, void*)
{
  PyOFXRGBAColourF *pcolour = (PyOFXRGBAColourF*) self;
  return PyFloat_FromDouble(pcolour->colour.b);
}

PyObject* PyOFXRGBAColourF_GetA(PyObject *self, void*)
{
  PyOFXRGBAColourF *pcolour = (PyOFXRGBAColourF*) self;
  return PyFloat_FromDouble(pcolour->colour.a);
}

int PyOFXRGBAColourF_SetR(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXRGBAColourF *pcolour = (PyOFXRGBAColourF*) self;
  pcolour->colour.r = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXRGBAColourF_SetG(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXRGBAColourF *pcolour = (PyOFXRGBAColourF*) self;
  pcolour->colour.g = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXRGBAColourF_SetB(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXRGBAColourF *pcolour = (PyOFXRGBAColourF*) self;
  pcolour->colour.b = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXRGBAColourF_SetA(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXRGBAColourF *pcolour = (PyOFXRGBAColourF*) self;
  pcolour->colour.a = (float) PyFloat_AsDouble(val);
  return 0;
}

static PyGetSetDef PyOFXRGBAColourF_GetSeters[] =
{
  {(char*)"r", PyOFXRGBAColourF_GetR, PyOFXRGBAColourF_SetR, NULL, NULL},
  {(char*)"g", PyOFXRGBAColourF_GetG, PyOFXRGBAColourF_SetG, NULL, NULL},
  {(char*)"b", PyOFXRGBAColourF_GetB, PyOFXRGBAColourF_SetB, NULL, NULL},
  {(char*)"a", PyOFXRGBAColourF_GetA, PyOFXRGBAColourF_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXRGBAColourD_New(PyTypeObject *t, PyObject *, PyObject *)
{
  return t->tp_alloc(t, 0);
}

int PyOFXRGBAColourD_Init(PyObject *self, PyObject *args, PyObject *)
{
  PyOFXRGBAColourD *pcolour = (PyOFXRGBAColourD*) self;
  
  Py_ssize_t n = PyTuple_Size(args);
  if (n == 4)
  {
    if (!PyArg_ParseTuple(args, "dddd", &(pcolour->colour.r), &(pcolour->colour.g), &(pcolour->colour.b), &(pcolour->colour.a)))
    {
      return -1;
    }
  }
  else if (n != 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Invalid argument(s) count. Accepts 0 or 4 arguments.");
    return -1;
  }
  else
  {
    pcolour->colour.r = 0.0;
    pcolour->colour.g = 0.0;
    pcolour->colour.b = 0.0;
    pcolour->colour.a = 1.0;
  }
  
  return 0;
}

void PyOFXRGBAColourD_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXRGBAColourD_GetR(PyObject *self, void*)
{
  PyOFXRGBAColourD *pcolour = (PyOFXRGBAColourD*) self;
  return PyFloat_FromDouble(pcolour->colour.r);
}

PyObject* PyOFXRGBAColourD_GetG(PyObject *self, void*)
{
  PyOFXRGBAColourD *pcolour = (PyOFXRGBAColourD*) self;
  return PyFloat_FromDouble(pcolour->colour.g);
}

PyObject* PyOFXRGBAColourD_GetB(PyObject *self, void*)
{
  PyOFXRGBAColourD *pcolour = (PyOFXRGBAColourD*) self;
  return PyFloat_FromDouble(pcolour->colour.b);
}

PyObject* PyOFXRGBAColourD_GetA(PyObject *self, void*)
{
  PyOFXRGBAColourD *pcolour = (PyOFXRGBAColourD*) self;
  return PyFloat_FromDouble(pcolour->colour.a);
}

int PyOFXRGBAColourD_SetR(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXRGBAColourD *pcolour = (PyOFXRGBAColourD*) self;
  pcolour->colour.r = PyFloat_AsDouble(val);
  return 0;
}

int PyOFXRGBAColourD_SetG(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXRGBAColourD *pcolour = (PyOFXRGBAColourD*) self;
  pcolour->colour.g = PyFloat_AsDouble(val);
  return 0;
}

int PyOFXRGBAColourD_SetB(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXRGBAColourD *pcolour = (PyOFXRGBAColourD*) self;
  pcolour->colour.b = PyFloat_AsDouble(val);
  return 0;
}

int PyOFXRGBAColourD_SetA(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXRGBAColourD *pcolour = (PyOFXRGBAColourD*) self;
  pcolour->colour.a = PyFloat_AsDouble(val);
  return 0;
}

static PyGetSetDef PyOFXRGBAColourD_GetSeters[] =
{
  {(char*)"r", PyOFXRGBAColourD_GetR, PyOFXRGBAColourD_SetR, NULL, NULL},
  {(char*)"g", PyOFXRGBAColourD_GetG, PyOFXRGBAColourD_SetG, NULL, NULL},
  {(char*)"b", PyOFXRGBAColourD_GetB, PyOFXRGBAColourD_SetB, NULL, NULL},
  {(char*)"a", PyOFXRGBAColourD_GetA, PyOFXRGBAColourD_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXYUVAColourB_New(PyTypeObject *t, PyObject *, PyObject *)
{
  return t->tp_alloc(t, 0);
}

int PyOFXYUVAColourB_Init(PyObject *self, PyObject *args, PyObject *)
{
  PyOFXYUVAColourB *pcolour = (PyOFXYUVAColourB*) self;
  
  Py_ssize_t n = PyTuple_Size(args);
  if (n == 4)
  {
    int y, u, v, a;
    if (!PyArg_ParseTuple(args, "iiii", &y, &u, &v, &a))
    {
      return -1;
    }
    pcolour->colour.y = (unsigned char) y;
    pcolour->colour.u = (unsigned char) u;
    pcolour->colour.v = (unsigned char) v;
    pcolour->colour.a = (unsigned char) a;
  }
  else if (n != 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Invalid argument(s) count. Accepts 0 or 4 arguments.");
    return -1;
  }
  else
  {
    pcolour->colour.y = 0;
    pcolour->colour.u = 0;
    pcolour->colour.v = 0;
    pcolour->colour.a = 255;
  }
  
  return 0;
}

void PyOFXYUVAColourB_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXYUVAColourB_GetY(PyObject *self, void*)
{
  PyOFXYUVAColourB *pcolour = (PyOFXYUVAColourB*) self;
  return PyInt_FromLong(pcolour->colour.y);
}

PyObject* PyOFXYUVAColourB_GetU(PyObject *self, void*)
{
  PyOFXYUVAColourB *pcolour = (PyOFXYUVAColourB*) self;
  return PyInt_FromLong(pcolour->colour.u);
}

PyObject* PyOFXYUVAColourB_GetV(PyObject *self, void*)
{
  PyOFXYUVAColourB *pcolour = (PyOFXYUVAColourB*) self;
  return PyInt_FromLong(pcolour->colour.v);
}

PyObject* PyOFXYUVAColourB_GetA(PyObject *self, void*)
{
  PyOFXYUVAColourB *pcolour = (PyOFXYUVAColourB*) self;
  return PyInt_FromLong(pcolour->colour.a);
}

int PyOFXYUVAColourB_SetY(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXYUVAColourB *pcolour = (PyOFXYUVAColourB*) self;
  pcolour->colour.y = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXYUVAColourB_SetU(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXYUVAColourB *pcolour = (PyOFXYUVAColourB*) self;
  pcolour->colour.u = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXYUVAColourB_SetV(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXYUVAColourB *pcolour = (PyOFXYUVAColourB*) self;
  pcolour->colour.v = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXYUVAColourB_SetA(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXYUVAColourB *pcolour = (PyOFXYUVAColourB*) self;
  pcolour->colour.a = (unsigned char) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef PyOFXYUVAColourB_GetSeters[] =
{
  {(char*)"y", PyOFXYUVAColourB_GetY, PyOFXYUVAColourB_SetY, NULL, NULL},
  {(char*)"u", PyOFXYUVAColourB_GetU, PyOFXYUVAColourB_SetU, NULL, NULL},
  {(char*)"v", PyOFXYUVAColourB_GetV, PyOFXYUVAColourB_SetV, NULL, NULL},
  {(char*)"a", PyOFXYUVAColourB_GetA, PyOFXYUVAColourB_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXYUVAColourS_New(PyTypeObject *t, PyObject *, PyObject *)
{
  return t->tp_alloc(t, 0);
}

int PyOFXYUVAColourS_Init(PyObject *self, PyObject *args, PyObject *)
{
  PyOFXYUVAColourS *pcolour = (PyOFXYUVAColourS*) self;
  
  Py_ssize_t n = PyTuple_Size(args);
  if (n == 4)
  {
    int y, u, v, a;
    if (!PyArg_ParseTuple(args, "iiii", &y, &u, &v, &a))
    {
      return -1;
    }
    pcolour->colour.y = (unsigned short) y;
    pcolour->colour.u = (unsigned short) u;
    pcolour->colour.v = (unsigned short) v;
    pcolour->colour.a = (unsigned short) a;
  }
  else if (n != 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Invalid argument(s) count. Accepts 0 or 4 arguments.");
    return -1;
  }
  else
  {
    pcolour->colour.y = 0;
    pcolour->colour.u = 0;
    pcolour->colour.v = 0;
    pcolour->colour.a = std::numeric_limits<unsigned short>::max();
  }
  
  return 0;
}

void PyOFXYUVAColourS_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXYUVAColourS_GetY(PyObject *self, void*)
{
  PyOFXYUVAColourS *pcolour = (PyOFXYUVAColourS*) self;
  return PyInt_FromLong(pcolour->colour.y);
}

PyObject* PyOFXYUVAColourS_GetU(PyObject *self, void*)
{
  PyOFXYUVAColourS *pcolour = (PyOFXYUVAColourS*) self;
  return PyInt_FromLong(pcolour->colour.u);
}

PyObject* PyOFXYUVAColourS_GetV(PyObject *self, void*)
{
  PyOFXYUVAColourS *pcolour = (PyOFXYUVAColourS*) self;
  return PyInt_FromLong(pcolour->colour.v);
}

PyObject* PyOFXYUVAColourS_GetA(PyObject *self, void*)
{
  PyOFXYUVAColourS *pcolour = (PyOFXYUVAColourS*) self;
  return PyInt_FromLong(pcolour->colour.a);
}

int PyOFXYUVAColourS_SetY(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXYUVAColourS *pcolour = (PyOFXYUVAColourS*) self;
  pcolour->colour.y = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXYUVAColourS_SetU(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXYUVAColourS *pcolour = (PyOFXYUVAColourS*) self;
  pcolour->colour.u = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXYUVAColourS_SetV(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXYUVAColourS *pcolour = (PyOFXYUVAColourS*) self;
  pcolour->colour.v = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXYUVAColourS_SetA(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXYUVAColourS *pcolour = (PyOFXYUVAColourS*) self;
  pcolour->colour.a = (unsigned short) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef PyOFXYUVAColourS_GetSeters[] =
{
  {(char*)"y", PyOFXYUVAColourS_GetY, PyOFXYUVAColourS_SetY, NULL, NULL},
  {(char*)"u", PyOFXYUVAColourS_GetU, PyOFXYUVAColourS_SetU, NULL, NULL},
  {(char*)"v", PyOFXYUVAColourS_GetV, PyOFXYUVAColourS_SetV, NULL, NULL},
  {(char*)"a", PyOFXYUVAColourS_GetA, PyOFXYUVAColourS_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXYUVAColourF_New(PyTypeObject *t, PyObject *, PyObject *)
{
  return t->tp_alloc(t, 0);
}

int PyOFXYUVAColourF_Init(PyObject *self, PyObject *args, PyObject *)
{
  PyOFXYUVAColourF *pcolour = (PyOFXYUVAColourF*) self;
  
  Py_ssize_t n = PyTuple_Size(args);
  if (n == 4)
  {
    if (!PyArg_ParseTuple(args, "ffff", &(pcolour->colour.y), &(pcolour->colour.u), &(pcolour->colour.v), &(pcolour->colour.a)))
    {
      return -1;
    }
  }
  else if (n != 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Invalid argument(s) count. Accepts 0 or 4 arguments.");
    return -1;
  }
  else
  {
    pcolour->colour.y = 0.0f;
    pcolour->colour.u = 0.0f;
    pcolour->colour.v = 0.0f;
    pcolour->colour.a = 1.0f;
  }
  
  return 0;
}

void PyOFXYUVAColourF_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXYUVAColourF_GetY(PyObject *self, void*)
{
  PyOFXYUVAColourF *pcolour = (PyOFXYUVAColourF*) self;
  return PyFloat_FromDouble(pcolour->colour.y);
}

PyObject* PyOFXYUVAColourF_GetU(PyObject *self, void*)
{
  PyOFXYUVAColourF *pcolour = (PyOFXYUVAColourF*) self;
  return PyFloat_FromDouble(pcolour->colour.u);
}

PyObject* PyOFXYUVAColourF_GetV(PyObject *self, void*)
{
  PyOFXYUVAColourF *pcolour = (PyOFXYUVAColourF*) self;
  return PyFloat_FromDouble(pcolour->colour.v);
}

PyObject* PyOFXYUVAColourF_GetA(PyObject *self, void*)
{
  PyOFXYUVAColourF *pcolour = (PyOFXYUVAColourF*) self;
  return PyFloat_FromDouble(pcolour->colour.a);
}

int PyOFXYUVAColourF_SetY(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXYUVAColourF *pcolour = (PyOFXYUVAColourF*) self;
  pcolour->colour.y = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXYUVAColourF_SetU(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXYUVAColourF *pcolour = (PyOFXYUVAColourF*) self;
  pcolour->colour.u = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXYUVAColourF_SetV(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXYUVAColourF *pcolour = (PyOFXYUVAColourF*) self;
  pcolour->colour.v = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXYUVAColourF_SetA(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXYUVAColourF *pcolour = (PyOFXYUVAColourF*) self;
  pcolour->colour.a = (float) PyFloat_AsDouble(val);
  return 0;
}

static PyGetSetDef PyOFXYUVAColourF_GetSeters[] =
{
  {(char*)"y", PyOFXYUVAColourF_GetY, PyOFXYUVAColourF_SetY, NULL, NULL},
  {(char*)"u", PyOFXYUVAColourF_GetU, PyOFXYUVAColourF_SetU, NULL, NULL},
  {(char*)"v", PyOFXYUVAColourF_GetV, PyOFXYUVAColourF_SetV, NULL, NULL},
  {(char*)"a", PyOFXYUVAColourF_GetA, PyOFXYUVAColourF_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXYUVAColourD_New(PyTypeObject *t, PyObject *, PyObject *)
{
  return t->tp_alloc(t, 0);
}

int PyOFXYUVAColourD_Init(PyObject *self, PyObject *args, PyObject *)
{
  PyOFXYUVAColourD *pcolour = (PyOFXYUVAColourD*) self;
  
  Py_ssize_t n = PyTuple_Size(args);
  if (n == 4)
  {
    if (!PyArg_ParseTuple(args, "dddd", &(pcolour->colour.y), &(pcolour->colour.u), &(pcolour->colour.v), &(pcolour->colour.a)))
    {
      return -1;
    }
  }
  else if (n != 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Invalid argument(s) count. Accepts 0 or 4 arguments.");
    return -1;
  }
  else
  {
    pcolour->colour.y = 0.0;
    pcolour->colour.u = 0.0;
    pcolour->colour.v = 0.0;
    pcolour->colour.a = 1.0;
  }
  
  return 0;
}

void PyOFXYUVAColourD_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXYUVAColourD_GetY(PyObject *self, void*)
{
  PyOFXYUVAColourD *pcolour = (PyOFXYUVAColourD*) self;
  return PyFloat_FromDouble(pcolour->colour.y);
}

PyObject* PyOFXYUVAColourD_GetU(PyObject *self, void*)
{
  PyOFXYUVAColourD *pcolour = (PyOFXYUVAColourD*) self;
  return PyFloat_FromDouble(pcolour->colour.u);
}

PyObject* PyOFXYUVAColourD_GetV(PyObject *self, void*)
{
  PyOFXYUVAColourD *pcolour = (PyOFXYUVAColourD*) self;
  return PyFloat_FromDouble(pcolour->colour.v);
}

PyObject* PyOFXYUVAColourD_GetA(PyObject *self, void*)
{
  PyOFXYUVAColourD *pcolour = (PyOFXYUVAColourD*) self;
  return PyFloat_FromDouble(pcolour->colour.a);
}

int PyOFXYUVAColourD_SetY(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXYUVAColourD *pcolour = (PyOFXYUVAColourD*) self;
  pcolour->colour.y = PyFloat_AsDouble(val);
  return 0;
}

int PyOFXYUVAColourD_SetU(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXYUVAColourD *pcolour = (PyOFXYUVAColourD*) self;
  pcolour->colour.u = PyFloat_AsDouble(val);
  return 0;
}

int PyOFXYUVAColourD_SetV(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXYUVAColourD *pcolour = (PyOFXYUVAColourD*) self;
  pcolour->colour.v = PyFloat_AsDouble(val);
  return 0;
}

int PyOFXYUVAColourD_SetA(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXYUVAColourD *pcolour = (PyOFXYUVAColourD*) self;
  pcolour->colour.a = PyFloat_AsDouble(val);
  return 0;
}

static PyGetSetDef PyOFXYUVAColourD_GetSeters[] =
{
  {(char*)"y", PyOFXYUVAColourD_GetY, PyOFXYUVAColourD_SetY, NULL, NULL},
  {(char*)"u", PyOFXYUVAColourD_GetU, PyOFXYUVAColourD_SetU, NULL, NULL},
  {(char*)"v", PyOFXYUVAColourD_GetV, PyOFXYUVAColourD_SetV, NULL, NULL},
  {(char*)"a", PyOFXYUVAColourD_GetA, PyOFXYUVAColourD_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXRGBColourB_New(PyTypeObject *t, PyObject *, PyObject *)
{
  return t->tp_alloc(t, 0);
}

int PyOFXRGBColourB_Init(PyObject *self, PyObject *args, PyObject *)
{
  PyOFXRGBColourB *pcolour = (PyOFXRGBColourB*) self;
  
  Py_ssize_t n = PyTuple_Size(args);
  if (n == 3)
  {
    int r, g, b;
    if (!PyArg_ParseTuple(args, "iii", &r, &g, &b))
    {
      return -1;
    }
    pcolour->colour.r = (unsigned char) r;
    pcolour->colour.g = (unsigned char) g;
    pcolour->colour.b = (unsigned char) b;
  }
  else if (n != 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Invalid argument(s) count. Accepts 0 or 3 arguments.");
    return -1;
  }
  else
  {
    pcolour->colour.r = 0;
    pcolour->colour.g = 0;
    pcolour->colour.b = 0;
  }
  
  return 0;
}

void PyOFXRGBColourB_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXRGBColourB_GetR(PyObject *self, void*)
{
  PyOFXRGBColourB *pcolour = (PyOFXRGBColourB*) self;
  return PyInt_FromLong(pcolour->colour.r);
}

PyObject* PyOFXRGBColourB_GetG(PyObject *self, void*)
{
  PyOFXRGBColourB *pcolour = (PyOFXRGBColourB*) self;
  return PyInt_FromLong(pcolour->colour.g);
}

PyObject* PyOFXRGBColourB_GetB(PyObject *self, void*)
{
  PyOFXRGBColourB *pcolour = (PyOFXRGBColourB*) self;
  return PyInt_FromLong(pcolour->colour.b);
}

int PyOFXRGBColourB_SetR(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXRGBColourB *pcolour = (PyOFXRGBColourB*) self;
  pcolour->colour.r = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBColourB_SetG(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXRGBColourB *pcolour = (PyOFXRGBColourB*) self;
  pcolour->colour.g = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBColourB_SetB(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXRGBColourB *pcolour = (PyOFXRGBColourB*) self;
  pcolour->colour.b = (unsigned char) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef PyOFXRGBColourB_GetSeters[] =
{
  {(char*)"r", PyOFXRGBColourB_GetR, PyOFXRGBColourB_SetR, NULL, NULL},
  {(char*)"g", PyOFXRGBColourB_GetG, PyOFXRGBColourB_SetG, NULL, NULL},
  {(char*)"b", PyOFXRGBColourB_GetB, PyOFXRGBColourB_SetB, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXRGBColourS_New(PyTypeObject *t, PyObject *, PyObject *)
{
  return t->tp_alloc(t, 0);
}

int PyOFXRGBColourS_Init(PyObject *self, PyObject *args, PyObject *)
{
  PyOFXRGBColourS *pcolour = (PyOFXRGBColourS*) self;
  
  Py_ssize_t n = PyTuple_Size(args);
  if (n == 3)
  {
    int r, g, b;
    if (!PyArg_ParseTuple(args, "iii", &r, &g, &b))
    {
      return -1;
    }
    pcolour->colour.r = (unsigned short) r;
    pcolour->colour.g = (unsigned short) g;
    pcolour->colour.b = (unsigned short) b;
  }
  else if (n != 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Invalid argument(s) count. Accepts 0 or 3 arguments.");
    return -1;
  }
  else
  {
    pcolour->colour.r = 0;
    pcolour->colour.g = 0;
    pcolour->colour.b = 0;
  }
  
  return 0;
}

void PyOFXRGBColourS_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXRGBColourS_GetR(PyObject *self, void*)
{
  PyOFXRGBColourS *pcolour = (PyOFXRGBColourS*) self;
  return PyInt_FromLong(pcolour->colour.r);
}

PyObject* PyOFXRGBColourS_GetG(PyObject *self, void*)
{
  PyOFXRGBColourS *pcolour = (PyOFXRGBColourS*) self;
  return PyInt_FromLong(pcolour->colour.g);
}

PyObject* PyOFXRGBColourS_GetB(PyObject *self, void*)
{
  PyOFXRGBColourS *pcolour = (PyOFXRGBColourS*) self;
  return PyInt_FromLong(pcolour->colour.b);
}

int PyOFXRGBColourS_SetR(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXRGBColourS *pcolour = (PyOFXRGBColourS*) self;
  pcolour->colour.r = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBColourS_SetG(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXRGBColourS *pcolour = (PyOFXRGBColourS*) self;
  pcolour->colour.g = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBColourS_SetB(PyObject *self, PyObject *val, void*)
{
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  PyOFXRGBColourS *pcolour = (PyOFXRGBColourS*) self;
  pcolour->colour.b = (unsigned short) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef PyOFXRGBColourS_GetSeters[] =
{
  {(char*)"r", PyOFXRGBColourS_GetR, PyOFXRGBColourS_SetR, NULL, NULL},
  {(char*)"g", PyOFXRGBColourS_GetG, PyOFXRGBColourS_SetG, NULL, NULL},
  {(char*)"b", PyOFXRGBColourS_GetB, PyOFXRGBColourS_SetB, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXRGBColourF_New(PyTypeObject *t, PyObject *, PyObject *)
{
  return t->tp_alloc(t, 0);
}

int PyOFXRGBColourF_Init(PyObject *self, PyObject *args, PyObject *)
{
  PyOFXRGBColourF *pcolour = (PyOFXRGBColourF*) self;
  
  Py_ssize_t n = PyTuple_Size(args);
  if (n == 3)
  {
    if (!PyArg_ParseTuple(args, "fff", &(pcolour->colour.r), &(pcolour->colour.g), &(pcolour->colour.b)))
    {
      return -1;
    }
  }
  else if (n != 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Invalid argument(s) count. Accepts 0 or 3 arguments.");
    return -1;
  }
  else
  {
    pcolour->colour.r = 0.0f;
    pcolour->colour.g = 0.0f;
    pcolour->colour.b = 0.0f;
  }
  
  return 0;
}

void PyOFXRGBColourF_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXRGBColourF_GetR(PyObject *self, void*)
{
  PyOFXRGBColourF *pcolour = (PyOFXRGBColourF*) self;
  return PyFloat_FromDouble(pcolour->colour.r);
}

PyObject* PyOFXRGBColourF_GetG(PyObject *self, void*)
{
  PyOFXRGBColourF *pcolour = (PyOFXRGBColourF*) self;
  return PyFloat_FromDouble(pcolour->colour.g);
}

PyObject* PyOFXRGBColourF_GetB(PyObject *self, void*)
{
  PyOFXRGBColourF *pcolour = (PyOFXRGBColourF*) self;
  return PyFloat_FromDouble(pcolour->colour.b);
}

int PyOFXRGBColourF_SetR(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXRGBColourF *pcolour = (PyOFXRGBColourF*) self;
  pcolour->colour.r = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXRGBColourF_SetG(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXRGBColourF *pcolour = (PyOFXRGBColourF*) self;
  pcolour->colour.g = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXRGBColourF_SetB(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXRGBColourF *pcolour = (PyOFXRGBColourF*) self;
  pcolour->colour.b = (float) PyFloat_AsDouble(val);
  return 0;
}

static PyGetSetDef PyOFXRGBColourF_GetSeters[] =
{
  {(char*)"r", PyOFXRGBColourF_GetR, PyOFXRGBColourF_SetR, NULL, NULL},
  {(char*)"g", PyOFXRGBColourF_GetG, PyOFXRGBColourF_SetG, NULL, NULL},
  {(char*)"b", PyOFXRGBColourF_GetB, PyOFXRGBColourF_SetB, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

PyObject* PyOFXRGBColourD_New(PyTypeObject *t, PyObject *, PyObject *)
{
  return t->tp_alloc(t, 0);
}

int PyOFXRGBColourD_Init(PyObject *self, PyObject *args, PyObject *)
{
  PyOFXRGBColourD *pcolour = (PyOFXRGBColourD*) self;
  
  Py_ssize_t n = PyTuple_Size(args);
  if (n == 3)
  {
    if (!PyArg_ParseTuple(args, "ddd", &(pcolour->colour.r), &(pcolour->colour.g), &(pcolour->colour.b)))
    {
      return -1;
    }
  }
  else if (n != 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Invalid argument(s) count. Accepts 0 or 3 arguments.");
    return -1;
  }
  else
  {
    pcolour->colour.r = 0.0;
    pcolour->colour.g = 0.0;
    pcolour->colour.b = 0.0;
  }
  
  return 0;
}

void PyOFXRGBColourD_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXRGBColourD_GetR(PyObject *self, void*)
{
  PyOFXRGBColourD *pcolour = (PyOFXRGBColourD*) self;
  return PyFloat_FromDouble(pcolour->colour.r);
}

PyObject* PyOFXRGBColourD_GetG(PyObject *self, void*)
{
  PyOFXRGBColourD *pcolour = (PyOFXRGBColourD*) self;
  return PyFloat_FromDouble(pcolour->colour.g);
}

PyObject* PyOFXRGBColourD_GetB(PyObject *self, void*)
{
  PyOFXRGBColourD *pcolour = (PyOFXRGBColourD*) self;
  return PyFloat_FromDouble(pcolour->colour.b);
}

int PyOFXRGBColourD_SetR(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXRGBColourD *pcolour = (PyOFXRGBColourD*) self;
  pcolour->colour.r = PyFloat_AsDouble(val);
  return 0;
}

int PyOFXRGBColourD_SetG(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXRGBColourD *pcolour = (PyOFXRGBColourD*) self;
  pcolour->colour.g = PyFloat_AsDouble(val);
  return 0;
}

int PyOFXRGBColourD_SetB(PyObject *self, PyObject *val, void*)
{
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  PyOFXRGBColourD *pcolour = (PyOFXRGBColourD*) self;
  pcolour->colour.b = PyFloat_AsDouble(val);
  return 0;
}

static PyGetSetDef PyOFXRGBColourD_GetSeters[] =
{
  {(char*)"r", PyOFXRGBColourD_GetR, PyOFXRGBColourD_SetR, NULL, NULL},
  {(char*)"g", PyOFXRGBColourD_GetG, PyOFXRGBColourD_SetG, NULL, NULL},
  {(char*)"b", PyOFXRGBColourD_GetB, PyOFXRGBColourD_SetB, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

PyTypeObject PyOFXColourAddressType;
PyTypeObject PyOFXAColourBAddressType;
PyTypeObject PyOFXAColourSAddressType;
PyTypeObject PyOFXAColourFAddressType;
PyTypeObject PyOFXRGBAColourBAddressType;
PyTypeObject PyOFXRGBAColourSAddressType;
PyTypeObject PyOFXRGBAColourFAddressType;
PyTypeObject PyOFXYUVAColourBAddressType;
PyTypeObject PyOFXYUVAColourSAddressType;
PyTypeObject PyOFXYUVAColourFAddressType;
PyTypeObject PyOFXRGBColourBAddressType;
PyTypeObject PyOFXRGBColourSAddressType;
PyTypeObject PyOFXRGBColourFAddressType;

// ---

PyObject* PyOFXColourAddress_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  
  PyOFXColourAddress *padd = (PyOFXColourAddress*)self;
  padd->base = 0;
  padd->ptr = 0;
  padd->pixelBytes = 0;
  padd->rowBytes = 0;
  
  return self;
}

int PyOFXColourAddress_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

void PyOFXColourAddress_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}

PyObject* PyOFXColourAddress_Goto(PyObject *self, PyObject *args)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  
  if (!paddr->base)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  int x, y;
  
  if (!PyArg_ParseTuple(args, "ii", &x, &y))
  {
    return NULL;
  }
  
  if (x <  paddr->bounds.x1 ||
      x >= paddr->bounds.x2 ||
      y <  paddr->bounds.y1 ||
      y >= paddr->bounds.y2)
  {
    Py_RETURN_FALSE;
  }
  
  char *bytesPtr = (char*) paddr->base;
  bytesPtr += (y - paddr->bounds.y1) * paddr->rowBytes;
  bytesPtr += (x - paddr->bounds.x1) * paddr->pixelBytes;
  
  paddr->ptr = (void*) bytesPtr;
  
  Py_RETURN_TRUE;
}

PyObject* PyOFXColourAddress_Next(PyObject *self, PyObject *)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  
  if (!paddr->ptr)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  unsigned char *bytePtr = (unsigned char*) paddr->ptr;
  
  // check boundaries?
  
  bytePtr += paddr->pixelBytes;
  
  paddr->ptr = (void*) bytePtr;
  
  Py_RETURN_NONE;
}

PyObject* PyOFXColourAddress_Prev(PyObject *self, PyObject *)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  
  if (!paddr->ptr)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  unsigned char *bytePtr = (unsigned char*) paddr->ptr;
  
  // check boundaries?
  
  bytePtr -= paddr->pixelBytes;
  
  paddr->ptr = (void*) bytePtr;
  
  Py_RETURN_NONE;
}

static PyMethodDef PyOFXColourAddress_Methods[] =
{
  {"next", PyOFXColourAddress_Next, METH_VARARGS, NULL},
  {"prev", PyOFXColourAddress_Prev, METH_VARARGS, NULL},
  {"goto", PyOFXColourAddress_Goto, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

// ---

int PyOFXAColourBAddress_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

PyObject* PyOFXAColourBAddress_GetA(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(*((unsigned char*) paddr->ptr));
}

int PyOFXAColourBAddress_SetA(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  *((unsigned char*) paddr->ptr) = (unsigned char) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef PyOFXAColourBAddress_GetSeters[] =
{
  {(char*)"a", PyOFXAColourBAddress_GetA, PyOFXAColourBAddress_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXAColourSAddress_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

PyObject* PyOFXAColourSAddress_GetA(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(*((unsigned short*) paddr->ptr));
}

int PyOFXAColourSAddress_SetA(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  *((unsigned short*) paddr->ptr) = (unsigned short) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef PyOFXAColourSAddress_GetSeters[] =
{
  {(char*)"a", PyOFXAColourSAddress_GetA, PyOFXAColourSAddress_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXAColourFAddress_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

PyObject* PyOFXAColourFAddress_GetA(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyFloat_FromDouble(*((float*) paddr->ptr));
}

int PyOFXAColourFAddress_SetA(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  *((float*) paddr->ptr) = (float) PyFloat_AsDouble(val);
  return 0;
}

static PyGetSetDef PyOFXAColourFAddress_GetSeters[] =
{
  {(char*)"a", PyOFXAColourFAddress_GetA, PyOFXAColourFAddress_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXRGBAColourBAddress_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

PyObject* PyOFXRGBAColourBAddress_GetR(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::RGBAColourB*) paddr->ptr)->r);
}

PyObject* PyOFXRGBAColourBAddress_GetG(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::RGBAColourB*) paddr->ptr)->g);
}

PyObject* PyOFXRGBAColourBAddress_GetB(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::RGBAColourB*) paddr->ptr)->b);
}

PyObject* PyOFXRGBAColourBAddress_GetA(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::RGBAColourB*) paddr->ptr)->a);
}

int PyOFXRGBAColourBAddress_SetR(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::RGBAColourB*) paddr->ptr)->r = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBAColourBAddress_SetG(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::RGBAColourB*) paddr->ptr)->g = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBAColourBAddress_SetB(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::RGBAColourB*) paddr->ptr)->b = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBAColourBAddress_SetA(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::RGBAColourB*) paddr->ptr)->a = (unsigned char) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef PyOFXRGBAColourBAddress_GetSeters[] =
{
  {(char*)"r", PyOFXRGBAColourBAddress_GetR, PyOFXRGBAColourBAddress_SetR, NULL, NULL},
  {(char*)"g", PyOFXRGBAColourBAddress_GetG, PyOFXRGBAColourBAddress_SetG, NULL, NULL},
  {(char*)"b", PyOFXRGBAColourBAddress_GetB, PyOFXRGBAColourBAddress_SetB, NULL, NULL},
  {(char*)"a", PyOFXRGBAColourBAddress_GetA, PyOFXRGBAColourBAddress_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXRGBAColourSAddress_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

PyObject* PyOFXRGBAColourSAddress_GetR(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::RGBAColourS*) paddr->ptr)->r);
}

PyObject* PyOFXRGBAColourSAddress_GetG(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::RGBAColourS*) paddr->ptr)->g);
}

PyObject* PyOFXRGBAColourSAddress_GetB(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::RGBAColourS*) paddr->ptr)->b);
}

PyObject* PyOFXRGBAColourSAddress_GetA(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::RGBAColourS*) paddr->ptr)->a);
}

int PyOFXRGBAColourSAddress_SetR(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::RGBAColourS*) paddr->ptr)->r = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBAColourSAddress_SetG(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::RGBAColourS*) paddr->ptr)->g = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBAColourSAddress_SetB(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::RGBAColourS*) paddr->ptr)->b = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBAColourSAddress_SetA(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::RGBAColourS*) paddr->ptr)->a = (unsigned short) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef PyOFXRGBAColourSAddress_GetSeters[] =
{
  {(char*)"r", PyOFXRGBAColourSAddress_GetR, PyOFXRGBAColourSAddress_SetR, NULL, NULL},
  {(char*)"g", PyOFXRGBAColourSAddress_GetG, PyOFXRGBAColourSAddress_SetG, NULL, NULL},
  {(char*)"b", PyOFXRGBAColourSAddress_GetB, PyOFXRGBAColourSAddress_SetB, NULL, NULL},
  {(char*)"a", PyOFXRGBAColourSAddress_GetA, PyOFXRGBAColourSAddress_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXRGBAColourFAddress_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

PyObject* PyOFXRGBAColourFAddress_GetR(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyFloat_FromDouble(((ofx::RGBAColourF*) paddr->ptr)->r);
}

PyObject* PyOFXRGBAColourFAddress_GetG(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyFloat_FromDouble(((ofx::RGBAColourF*) paddr->ptr)->g);
}

PyObject* PyOFXRGBAColourFAddress_GetB(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyFloat_FromDouble(((ofx::RGBAColourF*) paddr->ptr)->b);
}

PyObject* PyOFXRGBAColourFAddress_GetA(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyFloat_FromDouble(((ofx::RGBAColourF*) paddr->ptr)->a);
}

int PyOFXRGBAColourFAddress_SetR(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  ((ofx::RGBAColourF*) paddr->ptr)->r = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXRGBAColourFAddress_SetG(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  ((ofx::RGBAColourF*) paddr->ptr)->g = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXRGBAColourFAddress_SetB(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  ((ofx::RGBAColourF*) paddr->ptr)->b = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXRGBAColourFAddress_SetA(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  ((ofx::RGBAColourF*) paddr->ptr)->a = (float) PyFloat_AsDouble(val);
  return 0;
}

static PyGetSetDef PyOFXRGBAColourFAddress_GetSeters[] =
{
  {(char*)"r", PyOFXRGBAColourFAddress_GetR, PyOFXRGBAColourFAddress_SetR, NULL, NULL},
  {(char*)"g", PyOFXRGBAColourFAddress_GetG, PyOFXRGBAColourFAddress_SetG, NULL, NULL},
  {(char*)"b", PyOFXRGBAColourFAddress_GetB, PyOFXRGBAColourFAddress_SetB, NULL, NULL},
  {(char*)"a", PyOFXRGBAColourFAddress_GetA, PyOFXRGBAColourFAddress_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXYUVAColourBAddress_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

PyObject* PyOFXYUVAColourBAddress_GetY(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::YUVAColourB*) paddr->ptr)->y);
}

PyObject* PyOFXYUVAColourBAddress_GetU(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::YUVAColourB*) paddr->ptr)->u);
}

PyObject* PyOFXYUVAColourBAddress_GetV(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::YUVAColourB*) paddr->ptr)->v);
}

PyObject* PyOFXYUVAColourBAddress_GetA(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::YUVAColourB*) paddr->ptr)->a);
}

int PyOFXYUVAColourBAddress_SetY(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::YUVAColourB*) paddr->ptr)->y = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXYUVAColourBAddress_SetU(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::YUVAColourB*) paddr->ptr)->u = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXYUVAColourBAddress_SetV(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::YUVAColourB*) paddr->ptr)->v = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXYUVAColourBAddress_SetA(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::YUVAColourB*) paddr->ptr)->a = (unsigned char) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef PyOFXYUVAColourBAddress_GetSeters[] =
{
  {(char*)"y", PyOFXYUVAColourBAddress_GetY, PyOFXYUVAColourBAddress_SetY, NULL, NULL},
  {(char*)"u", PyOFXYUVAColourBAddress_GetU, PyOFXYUVAColourBAddress_SetU, NULL, NULL},
  {(char*)"v", PyOFXYUVAColourBAddress_GetV, PyOFXYUVAColourBAddress_SetV, NULL, NULL},
  {(char*)"a", PyOFXYUVAColourBAddress_GetA, PyOFXYUVAColourBAddress_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXYUVAColourSAddress_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

PyObject* PyOFXYUVAColourSAddress_GetY(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::YUVAColourS*) paddr->ptr)->y);
}

PyObject* PyOFXYUVAColourSAddress_GetU(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::YUVAColourS*) paddr->ptr)->u);
}

PyObject* PyOFXYUVAColourSAddress_GetV(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::YUVAColourS*) paddr->ptr)->v);
}

PyObject* PyOFXYUVAColourSAddress_GetA(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::YUVAColourS*) paddr->ptr)->a);
}

int PyOFXYUVAColourSAddress_SetY(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::YUVAColourS*) paddr->ptr)->y = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXYUVAColourSAddress_SetU(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::YUVAColourS*) paddr->ptr)->u = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXYUVAColourSAddress_SetV(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::YUVAColourS*) paddr->ptr)->v = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXYUVAColourSAddress_SetA(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::YUVAColourS*) paddr->ptr)->a = (unsigned short) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef PyOFXYUVAColourSAddress_GetSeters[] =
{
  {(char*)"y", PyOFXYUVAColourSAddress_GetY, PyOFXYUVAColourSAddress_SetY, NULL, NULL},
  {(char*)"u", PyOFXYUVAColourSAddress_GetU, PyOFXYUVAColourSAddress_SetU, NULL, NULL},
  {(char*)"v", PyOFXYUVAColourSAddress_GetV, PyOFXYUVAColourSAddress_SetV, NULL, NULL},
  {(char*)"a", PyOFXYUVAColourSAddress_GetA, PyOFXYUVAColourSAddress_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXYUVAColourFAddress_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

PyObject* PyOFXYUVAColourFAddress_GetY(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyFloat_FromDouble(((ofx::YUVAColourF*) paddr->ptr)->y);
}

PyObject* PyOFXYUVAColourFAddress_GetU(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyFloat_FromDouble(((ofx::YUVAColourF*) paddr->ptr)->u);
}

PyObject* PyOFXYUVAColourFAddress_GetV(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyFloat_FromDouble(((ofx::YUVAColourF*) paddr->ptr)->v);
}

PyObject* PyOFXYUVAColourFAddress_GetA(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyFloat_FromDouble(((ofx::YUVAColourF*) paddr->ptr)->a);
}

int PyOFXYUVAColourFAddress_SetY(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  ((ofx::YUVAColourF*) paddr->ptr)->y = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXYUVAColourFAddress_SetU(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  ((ofx::YUVAColourF*) paddr->ptr)->u = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXYUVAColourFAddress_SetV(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  ((ofx::YUVAColourF*) paddr->ptr)->v = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXYUVAColourFAddress_SetA(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  ((ofx::YUVAColourF*) paddr->ptr)->a = (float) PyFloat_AsDouble(val);
  return 0;
}

static PyGetSetDef PyOFXYUVAColourFAddress_GetSeters[] =
{
  {(char*)"y", PyOFXYUVAColourFAddress_GetY, PyOFXYUVAColourFAddress_SetY, NULL, NULL},
  {(char*)"u", PyOFXYUVAColourFAddress_GetU, PyOFXYUVAColourFAddress_SetU, NULL, NULL},
  {(char*)"v", PyOFXYUVAColourFAddress_GetV, PyOFXYUVAColourFAddress_SetV, NULL, NULL},
  {(char*)"a", PyOFXYUVAColourFAddress_GetA, PyOFXYUVAColourFAddress_SetA, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXRGBColourBAddress_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

PyObject* PyOFXRGBColourBAddress_GetR(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::RGBColourB*) paddr->ptr)->r);
}

PyObject* PyOFXRGBColourBAddress_GetG(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::RGBColourB*) paddr->ptr)->g);
}

PyObject* PyOFXRGBColourBAddress_GetB(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::RGBColourB*) paddr->ptr)->b);
}

int PyOFXRGBColourBAddress_SetR(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::RGBColourB*) paddr->ptr)->r = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBColourBAddress_SetG(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::RGBColourB*) paddr->ptr)->g = (unsigned char) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBColourBAddress_SetB(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::RGBColourB*) paddr->ptr)->b = (unsigned char) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef PyOFXRGBColourBAddress_GetSeters[] =
{
  {(char*)"r", PyOFXRGBColourBAddress_GetR, PyOFXRGBColourBAddress_SetR, NULL, NULL},
  {(char*)"g", PyOFXRGBColourBAddress_GetG, PyOFXRGBColourBAddress_SetG, NULL, NULL},
  {(char*)"b", PyOFXRGBColourBAddress_GetB, PyOFXRGBColourBAddress_SetB, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXRGBColourSAddress_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

PyObject* PyOFXRGBColourSAddress_GetR(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::RGBColourS*) paddr->ptr)->r);
}

PyObject* PyOFXRGBColourSAddress_GetG(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::RGBColourS*) paddr->ptr)->g);
}

PyObject* PyOFXRGBColourSAddress_GetB(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyInt_FromLong(((ofx::RGBColourS*) paddr->ptr)->b);
}

int PyOFXRGBColourSAddress_SetR(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::RGBColourS*) paddr->ptr)->r = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBColourSAddress_SetG(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::RGBColourS*) paddr->ptr)->g = (unsigned short) PyInt_AsLong(val);
  return 0;
}

int PyOFXRGBColourSAddress_SetB(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected an integer");
    return -1;
  }
  ((ofx::RGBColourS*) paddr->ptr)->b = (unsigned short) PyInt_AsLong(val);
  return 0;
}

static PyGetSetDef PyOFXRGBColourSAddress_GetSeters[] =
{
  {(char*)"r", PyOFXRGBColourSAddress_GetR, PyOFXRGBColourSAddress_SetR, NULL, NULL},
  {(char*)"g", PyOFXRGBColourSAddress_GetG, PyOFXRGBColourSAddress_SetG, NULL, NULL},
  {(char*)"b", PyOFXRGBColourSAddress_GetB, PyOFXRGBColourSAddress_SetB, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXRGBColourFAddress_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

PyObject* PyOFXRGBColourFAddress_GetR(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyFloat_FromDouble(((ofx::RGBColourF*) paddr->ptr)->r);
}

PyObject* PyOFXRGBColourFAddress_GetG(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyFloat_FromDouble(((ofx::RGBColourF*) paddr->ptr)->g);
}

PyObject* PyOFXRGBColourFAddress_GetB(PyObject *self, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  return PyFloat_FromDouble(((ofx::RGBColourF*) paddr->ptr)->b);
}

int PyOFXRGBColourFAddress_SetR(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  ((ofx::RGBColourF*) paddr->ptr)->r = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXRGBColourFAddress_SetG(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  ((ofx::RGBColourF*) paddr->ptr)->g = (float) PyFloat_AsDouble(val);
  return 0;
}

int PyOFXRGBColourFAddress_SetB(PyObject *self, PyObject *val, void*)
{
  PyOFXColourAddress *paddr = (PyOFXColourAddress*) self;
  if (paddr->ptr == 0)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  if (!PyFloat_Check(val) && !PyInt_Check(val))
  {
    PyErr_SetString(PyExc_TypeError, "Expected a float");
    return -1;
  }
  ((ofx::RGBColourF*) paddr->ptr)->b = (float) PyFloat_AsDouble(val);
  return 0;
}

static PyGetSetDef PyOFXRGBColourFAddress_GetSeters[] =
{
  {(char*)"r", PyOFXRGBColourFAddress_GetR, PyOFXRGBColourFAddress_SetR, NULL, NULL},
  {(char*)"g", PyOFXRGBColourFAddress_GetG, PyOFXRGBColourFAddress_SetG, NULL, NULL},
  {(char*)"b", PyOFXRGBColourFAddress_GetB, PyOFXRGBColourFAddress_SetB, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

bool PyOFX_InitPixel(PyObject *mod)
{
  INIT_TYPE(PyOFXRGBAColourBType, "ofx.RGBAColourB", PyOFXRGBAColourB);
  PyOFXRGBAColourBType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXRGBAColourBType.tp_new = PyOFXRGBAColourB_New;
  PyOFXRGBAColourBType.tp_init = PyOFXRGBAColourB_Init;
  PyOFXRGBAColourBType.tp_dealloc = PyOFXRGBAColourB_Delete;
  PyOFXRGBAColourBType.tp_getset = PyOFXRGBAColourB_GetSeters;
  if (PyType_Ready(&PyOFXRGBAColourBType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXRGBAColourSType, "ofx.RGBAColourS", PyOFXRGBAColourS);
  PyOFXRGBAColourSType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXRGBAColourSType.tp_new = PyOFXRGBAColourS_New;
  PyOFXRGBAColourSType.tp_init = PyOFXRGBAColourS_Init;
  PyOFXRGBAColourSType.tp_dealloc = PyOFXRGBAColourS_Delete;
  PyOFXRGBAColourSType.tp_getset = PyOFXRGBAColourS_GetSeters;
  if (PyType_Ready(&PyOFXRGBAColourSType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXRGBAColourFType, "ofx.RGBAColourF", PyOFXRGBAColourF);
  PyOFXRGBAColourFType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXRGBAColourFType.tp_new = PyOFXRGBAColourF_New;
  PyOFXRGBAColourFType.tp_init = PyOFXRGBAColourF_Init;
  PyOFXRGBAColourFType.tp_dealloc = PyOFXRGBAColourF_Delete;
  PyOFXRGBAColourFType.tp_getset = PyOFXRGBAColourF_GetSeters;
  if (PyType_Ready(&PyOFXRGBAColourFType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXRGBAColourDType, "ofx.RGBAColourD", PyOFXRGBAColourD);
  PyOFXRGBAColourDType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXRGBAColourDType.tp_new = PyOFXRGBAColourD_New;
  PyOFXRGBAColourDType.tp_init = PyOFXRGBAColourD_Init;
  PyOFXRGBAColourDType.tp_dealloc = PyOFXRGBAColourD_Delete;
  PyOFXRGBAColourDType.tp_getset = PyOFXRGBAColourD_GetSeters;
  if (PyType_Ready(&PyOFXRGBAColourDType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXYUVAColourBType, "ofx.YUVAColourB", PyOFXYUVAColourB);
  PyOFXYUVAColourBType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXYUVAColourBType.tp_new = PyOFXYUVAColourB_New;
  PyOFXYUVAColourBType.tp_init = PyOFXYUVAColourB_Init;
  PyOFXYUVAColourBType.tp_dealloc = PyOFXYUVAColourB_Delete;
  PyOFXYUVAColourBType.tp_getset = PyOFXYUVAColourB_GetSeters;
  if (PyType_Ready(&PyOFXYUVAColourBType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXYUVAColourSType, "ofx.YUVAColourS", PyOFXYUVAColourS);
  PyOFXYUVAColourSType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXYUVAColourSType.tp_new = PyOFXYUVAColourS_New;
  PyOFXYUVAColourSType.tp_init = PyOFXYUVAColourS_Init;
  PyOFXYUVAColourSType.tp_dealloc = PyOFXYUVAColourS_Delete;
  PyOFXYUVAColourSType.tp_getset = PyOFXYUVAColourS_GetSeters;
  if (PyType_Ready(&PyOFXYUVAColourSType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXYUVAColourFType, "ofx.YUVAColourF", PyOFXYUVAColourF);
  PyOFXYUVAColourFType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXYUVAColourFType.tp_new = PyOFXYUVAColourF_New;
  PyOFXYUVAColourFType.tp_init = PyOFXYUVAColourF_Init;
  PyOFXYUVAColourFType.tp_dealloc = PyOFXYUVAColourF_Delete;
  PyOFXYUVAColourFType.tp_getset = PyOFXYUVAColourF_GetSeters;
  if (PyType_Ready(&PyOFXYUVAColourFType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXYUVAColourDType, "ofx.YUVAColourD", PyOFXYUVAColourD);
  PyOFXYUVAColourDType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXYUVAColourDType.tp_new = PyOFXYUVAColourD_New;
  PyOFXYUVAColourDType.tp_init = PyOFXYUVAColourD_Init;
  PyOFXYUVAColourDType.tp_dealloc = PyOFXYUVAColourD_Delete;
  PyOFXYUVAColourDType.tp_getset = PyOFXYUVAColourD_GetSeters;
  if (PyType_Ready(&PyOFXYUVAColourDType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXColourAddressType, "ofx.ColourAddress", PyOFXColourAddress);
  PyOFXColourAddressType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXColourAddressType.tp_new = PyOFXColourAddress_New;
  PyOFXColourAddressType.tp_init = PyOFXColourAddress_Init;
  PyOFXColourAddressType.tp_dealloc = PyOFXColourAddress_Delete;
  PyOFXColourAddressType.tp_methods = PyOFXColourAddress_Methods;
  if (PyType_Ready(&PyOFXColourAddressType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXAColourBAddressType, "ofx.AColourBAddress", PyOFXAColourBAddress);
  PyOFXAColourBAddressType.tp_base = &PyOFXColourAddressType;
  PyOFXAColourBAddressType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXAColourBAddressType.tp_init = PyOFXAColourBAddress_Init;
  PyOFXAColourBAddressType.tp_getset = PyOFXAColourBAddress_GetSeters;
  if (PyType_Ready(&PyOFXAColourBAddressType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXAColourSAddressType, "ofx.AColourSAddress", PyOFXAColourSAddress);
  PyOFXAColourSAddressType.tp_base = &PyOFXColourAddressType;
  PyOFXAColourSAddressType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXAColourSAddressType.tp_init = PyOFXAColourSAddress_Init;
  PyOFXAColourSAddressType.tp_getset = PyOFXAColourSAddress_GetSeters;
  if (PyType_Ready(&PyOFXAColourSAddressType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXAColourFAddressType, "ofx.AColourFAddress", PyOFXAColourFAddress);
  PyOFXAColourFAddressType.tp_base = &PyOFXColourAddressType;
  PyOFXAColourFAddressType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXAColourFAddressType.tp_init = PyOFXAColourFAddress_Init;
  PyOFXAColourFAddressType.tp_getset = PyOFXAColourFAddress_GetSeters;
  if (PyType_Ready(&PyOFXAColourFAddressType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXRGBAColourBAddressType, "ofx.RGBAColourBAddress", PyOFXRGBAColourBAddress);
  PyOFXRGBAColourBAddressType.tp_base = &PyOFXColourAddressType;
  PyOFXRGBAColourBAddressType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXRGBAColourBAddressType.tp_init = PyOFXRGBAColourBAddress_Init;
  PyOFXRGBAColourBAddressType.tp_getset = PyOFXRGBAColourBAddress_GetSeters;
  if (PyType_Ready(&PyOFXRGBAColourBAddressType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXRGBAColourSAddressType, "ofx.RGBAColourSAddress", PyOFXRGBAColourSAddress);
  PyOFXRGBAColourSAddressType.tp_base = &PyOFXColourAddressType;
  PyOFXRGBAColourSAddressType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXRGBAColourSAddressType.tp_init = PyOFXRGBAColourSAddress_Init;
  PyOFXRGBAColourSAddressType.tp_getset = PyOFXRGBAColourSAddress_GetSeters;
  if (PyType_Ready(&PyOFXRGBAColourSAddressType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXRGBAColourFAddressType, "ofx.RGBAColourFAddress", PyOFXRGBAColourFAddress);
  PyOFXRGBAColourFAddressType.tp_base = &PyOFXColourAddressType;
  PyOFXRGBAColourFAddressType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXRGBAColourFAddressType.tp_init = PyOFXRGBAColourFAddress_Init;
  PyOFXRGBAColourFAddressType.tp_getset = PyOFXRGBAColourFAddress_GetSeters;
  if (PyType_Ready(&PyOFXRGBAColourFAddressType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXYUVAColourBAddressType, "ofx.YUVAColourBAddress", PyOFXYUVAColourBAddress);
  PyOFXYUVAColourBAddressType.tp_base = &PyOFXColourAddressType;
  PyOFXYUVAColourBAddressType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXYUVAColourBAddressType.tp_init = PyOFXYUVAColourBAddress_Init;
  PyOFXYUVAColourBAddressType.tp_getset = PyOFXYUVAColourBAddress_GetSeters;
  if (PyType_Ready(&PyOFXYUVAColourBAddressType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXYUVAColourSAddressType, "ofx.YUVAColourSAddress", PyOFXYUVAColourSAddress);
  PyOFXYUVAColourSAddressType.tp_base = &PyOFXColourAddressType;
  PyOFXYUVAColourSAddressType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXYUVAColourSAddressType.tp_init = PyOFXYUVAColourSAddress_Init;
  PyOFXYUVAColourSAddressType.tp_getset = PyOFXYUVAColourSAddress_GetSeters;
  if (PyType_Ready(&PyOFXYUVAColourSAddressType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXYUVAColourFAddressType, "ofx.YUVAColourFAddress", PyOFXYUVAColourFAddress);
  PyOFXYUVAColourFAddressType.tp_base = &PyOFXColourAddressType;
  PyOFXYUVAColourFAddressType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXYUVAColourFAddressType.tp_init = PyOFXYUVAColourFAddress_Init;
  PyOFXYUVAColourFAddressType.tp_getset = PyOFXYUVAColourFAddress_GetSeters;
  if (PyType_Ready(&PyOFXYUVAColourFAddressType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXRGBColourBType, "ofx.RGBColourB", PyOFXRGBColourB);
  PyOFXRGBColourBType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXRGBColourBType.tp_new = PyOFXRGBColourB_New;
  PyOFXRGBColourBType.tp_init = PyOFXRGBColourB_Init;
  PyOFXRGBColourBType.tp_dealloc = PyOFXRGBColourB_Delete;
  PyOFXRGBColourBType.tp_getset = PyOFXRGBColourB_GetSeters;
  if (PyType_Ready(&PyOFXRGBColourBType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXRGBColourSType, "ofx.RGBColourS", PyOFXRGBColourS);
  PyOFXRGBColourSType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXRGBColourSType.tp_new = PyOFXRGBColourS_New;
  PyOFXRGBColourSType.tp_init = PyOFXRGBColourS_Init;
  PyOFXRGBColourSType.tp_dealloc = PyOFXRGBColourS_Delete;
  PyOFXRGBColourSType.tp_getset = PyOFXRGBColourS_GetSeters;
  if (PyType_Ready(&PyOFXRGBColourSType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXRGBColourFType, "ofx.RGBColourF", PyOFXRGBColourF);
  PyOFXRGBColourFType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXRGBColourFType.tp_new = PyOFXRGBColourF_New;
  PyOFXRGBColourFType.tp_init = PyOFXRGBColourF_Init;
  PyOFXRGBColourFType.tp_dealloc = PyOFXRGBColourF_Delete;
  PyOFXRGBColourFType.tp_getset = PyOFXRGBColourF_GetSeters;
  if (PyType_Ready(&PyOFXRGBColourFType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXRGBColourDType, "ofx.RGBColourD", PyOFXRGBColourD);
  PyOFXRGBColourDType.tp_flags = Py_TPFLAGS_DEFAULT;
  PyOFXRGBColourDType.tp_new = PyOFXRGBColourD_New;
  PyOFXRGBColourDType.tp_init = PyOFXRGBColourD_Init;
  PyOFXRGBColourDType.tp_dealloc = PyOFXRGBColourD_Delete;
  PyOFXRGBColourDType.tp_getset = PyOFXRGBColourD_GetSeters;
  if (PyType_Ready(&PyOFXRGBColourDType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXRGBColourBAddressType, "ofx.RGBColourBAddress", PyOFXRGBColourBAddress);
  PyOFXRGBColourBAddressType.tp_base = &PyOFXColourAddressType;
  PyOFXRGBColourBAddressType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXRGBColourBAddressType.tp_init = PyOFXRGBColourBAddress_Init;
  PyOFXRGBColourBAddressType.tp_getset = PyOFXRGBColourBAddress_GetSeters;
  if (PyType_Ready(&PyOFXRGBColourBAddressType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXRGBColourSAddressType, "ofx.RGBColourSAddress", PyOFXRGBColourSAddress);
  PyOFXRGBColourSAddressType.tp_base = &PyOFXColourAddressType;
  PyOFXRGBColourSAddressType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXRGBColourSAddressType.tp_init = PyOFXRGBColourSAddress_Init;
  PyOFXRGBColourSAddressType.tp_getset = PyOFXRGBColourSAddress_GetSeters;
  if (PyType_Ready(&PyOFXRGBColourSAddressType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXRGBColourFAddressType, "ofx.RGBColourFAddress", PyOFXRGBColourFAddress);
  PyOFXRGBColourFAddressType.tp_base = &PyOFXColourAddressType;
  PyOFXRGBColourFAddressType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXRGBColourFAddressType.tp_init = PyOFXRGBColourFAddress_Init;
  PyOFXRGBColourFAddressType.tp_getset = PyOFXRGBColourFAddress_GetSeters;
  if (PyType_Ready(&PyOFXRGBColourFAddressType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXRGBColourBType);
  PyModule_AddObject(mod, "RGBColourB", (PyObject*)&PyOFXRGBColourBType);
  
  Py_INCREF(&PyOFXRGBColourSType);
  PyModule_AddObject(mod, "RGBColourS", (PyObject*)&PyOFXRGBColourSType);
  
  Py_INCREF(&PyOFXRGBColourFType);
  PyModule_AddObject(mod, "RGBColourF", (PyObject*)&PyOFXRGBColourFType);
  
  Py_INCREF(&PyOFXRGBColourDType);
  PyModule_AddObject(mod, "RGBColourD", (PyObject*)&PyOFXRGBColourDType);
  
  Py_INCREF(&PyOFXRGBColourBAddressType);
  PyModule_AddObject(mod, "RGBColourBAddress", (PyObject*)&PyOFXRGBColourBAddressType);
  
  Py_INCREF(&PyOFXRGBColourSAddressType);
  PyModule_AddObject(mod, "RGBColourSAddress", (PyObject*)&PyOFXRGBColourSAddressType);
  
  Py_INCREF(&PyOFXRGBColourFAddressType);
  PyModule_AddObject(mod, "RGBColourFAddress", (PyObject*)&PyOFXRGBColourFAddressType);
  
  Py_INCREF(&PyOFXColourAddressType);
  PyModule_AddObject(mod, "ColourAddress", (PyObject*)&PyOFXColourAddressType);
  
  Py_INCREF(&PyOFXRGBAColourBType);
  PyModule_AddObject(mod, "RGBAColourB", (PyObject*)&PyOFXRGBAColourBType);
  
  Py_INCREF(&PyOFXRGBAColourSType);
  PyModule_AddObject(mod, "RGBAColourS", (PyObject*)&PyOFXRGBAColourSType);
  
  Py_INCREF(&PyOFXRGBAColourFType);
  PyModule_AddObject(mod, "RGBAColourF", (PyObject*)&PyOFXRGBAColourFType);
  
  Py_INCREF(&PyOFXRGBAColourDType);
  PyModule_AddObject(mod, "RGBAColourD", (PyObject*)&PyOFXRGBAColourDType);
  
  Py_INCREF(&PyOFXYUVAColourBType);
  PyModule_AddObject(mod, "YUVAColourB", (PyObject*)&PyOFXYUVAColourBType);
  
  Py_INCREF(&PyOFXYUVAColourSType);
  PyModule_AddObject(mod, "YUVAColourS", (PyObject*)&PyOFXYUVAColourSType);
  
  Py_INCREF(&PyOFXYUVAColourFType);
  PyModule_AddObject(mod, "YUVAColourF", (PyObject*)&PyOFXYUVAColourFType);
  
  Py_INCREF(&PyOFXYUVAColourDType);
  PyModule_AddObject(mod, "YUVAColourD", (PyObject*)&PyOFXYUVAColourDType);
  
  Py_INCREF(&PyOFXRGBAColourBAddressType);
  PyModule_AddObject(mod, "RGBAColourBAddress", (PyObject*)&PyOFXRGBAColourBAddressType);
  
  Py_INCREF(&PyOFXRGBAColourSAddressType);
  PyModule_AddObject(mod, "RGBAColourSAddress", (PyObject*)&PyOFXRGBAColourSAddressType);
  
  Py_INCREF(&PyOFXRGBAColourFAddressType);
  PyModule_AddObject(mod, "RGBAColourFAddress", (PyObject*)&PyOFXRGBAColourFAddressType);
  
  Py_INCREF(&PyOFXYUVAColourBAddressType);
  PyModule_AddObject(mod, "YUVAColourBAddress", (PyObject*)&PyOFXYUVAColourBAddressType);
  
  Py_INCREF(&PyOFXYUVAColourSAddressType);
  PyModule_AddObject(mod, "YUVAColourSAddress", (PyObject*)&PyOFXYUVAColourSAddressType);
  
  Py_INCREF(&PyOFXYUVAColourFAddressType);
  PyModule_AddObject(mod, "YUVAColourFAddress", (PyObject*)&PyOFXYUVAColourFAddressType);
  
  return true;
}

