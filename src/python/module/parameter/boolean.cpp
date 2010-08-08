#include "common.h"

PyTypeObject PyOFXBooleanParameterDescriptorType;
PyTypeObject PyOFXBooleanParameterType;

// ---

int PyOFXBooleanParameterDescriptor_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  pdesc->desc = new ofx::BooleanParameterDescriptor();
  return 0;
}

PyObject* PyOFXBooleanParameterDescriptor_GetDefault(PyObject *self, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::BooleanParameterDescriptor *desc = (ofx::BooleanParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  bool rv;
  
  CATCH({rv = desc->getDefault();}, failed);
  
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

int PyOFXBooleanParameterDescriptor_SetDefault(PyObject *self, PyObject *val, void*)
{
  PyOFXParameterDescriptor *pdesc = (PyOFXParameterDescriptor*) self;
  
  if (!pdesc->desc)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return -1;
  }
  
  ofx::BooleanParameterDescriptor *desc = (ofx::BooleanParameterDescriptor*) pdesc->desc;
  
  bool failed = false;
  
  CATCH({desc->setDefault(val == Py_True);}, failed);
  
  if (failed)
  {
    return -1;
  }
  
  return 0;
}

static PyGetSetDef PyOFXBooleanParameterDescriptor_GetSeters[] =
{
  {(char*)"default", PyOFXBooleanParameterDescriptor_GetDefault, PyOFXBooleanParameterDescriptor_SetDefault, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

// ---

int PyOFXBooleanParameter_Init(PyObject *self, PyObject *, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  pparam->param = new ofx::BooleanParameter();
  return 0;
}

PyObject* PyOFXBooleanParameter_GetDefault(PyObject *self, void*)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::BooleanParameter *param = (ofx::BooleanParameter*) pparam->param;
  
  bool failed = false;
  
  bool rv;
  
  CATCH({rv = param->getDefault();}, failed);
  
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

static PyGetSetDef PyOFXBooleanParameter_GetSeters[] =
{
  {(char*)"default", PyOFXBooleanParameter_GetDefault, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL}
};

PyObject* PyOFXBooleanParameter_GetValue(PyObject *self, PyObject *)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  ofx::BooleanParameter *param = (ofx::BooleanParameter*) pparam->param;
  
  bool failed = false;
  
  bool rv;
  
  CATCH({rv = param->getValue();}, failed);
  
  if (failed)
  {
    return false;
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

PyObject* PyOFXBooleanParameter_GetValueAtTime(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  double t;
  
  if (!PyArg_ParseTuple(args, "d", &t))
  {
    return NULL;
  }
  
  ofx::BooleanParameter *param = (ofx::BooleanParameter*) pparam->param;
  
  bool failed = false;
  
  bool rv;
  
  CATCH({rv = param->getValueAtTime(t);}, failed);
  
  if (failed)
  {
    return false;
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

PyObject* PyOFXBooleanParameter_SetValue(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyObject *val = 0;
  
  if (!PyArg_ParseTuple(args, "O", &val))
  {
    return NULL;
  }
  
  ofx::BooleanParameter *param = (ofx::BooleanParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->setValue(val == Py_True);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

PyObject* PyOFXBooleanParameter_SetValueAtTime(PyObject *self, PyObject *args)
{
  PyOFXParameter *pparam = (PyOFXParameter*) self;
  
  if (!pparam->param)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unbound object");
    return NULL;
  }
  
  PyObject *val = 0;
  double t = 0.0;
  
  if (!PyArg_ParseTuple(args, "dO", &t, &val))
  {
    return NULL;
  }
  
  ofx::BooleanParameter *param = (ofx::BooleanParameter*) pparam->param;
  
  bool failed = false;
  
  CATCH({param->setValueAtTime(t, val == Py_True);}, failed);
  
  if (failed)
  {
    return NULL;
  }
  
  Py_RETURN_NONE;
}

static PyMethodDef PyOFXBooleanParameter_Methods[] =
{
  {"setValue", PyOFXBooleanParameter_SetValue, METH_VARARGS, NULL},
  {"getValue", PyOFXBooleanParameter_GetValue, METH_VARARGS, NULL},
  {"setValueAtTime", PyOFXBooleanParameter_SetValueAtTime, METH_VARARGS, NULL},
  {"getValueAtTime", PyOFXBooleanParameter_GetValueAtTime, METH_VARARGS, NULL},
  {NULL, NULL, NULL, NULL}
};

// ---

bool PyOFX_InitParameter_Boolean(PyObject *mod)
{
  INIT_TYPE(PyOFXBooleanParameterDescriptorType, "ofx.BooleanParameterDescriptor", PyOFXBooleanParameterDescriptor);
  PyOFXBooleanParameterDescriptorType.tp_base = &PyOFXValueParameterDescriptorType;
  PyOFXBooleanParameterDescriptorType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXBooleanParameterDescriptorType.tp_init = PyOFXBooleanParameterDescriptor_Init;
  PyOFXBooleanParameterDescriptorType.tp_getset = PyOFXBooleanParameterDescriptor_GetSeters;
  if (PyType_Ready(&PyOFXBooleanParameterDescriptorType) < 0)
  {
    return false;
  }
  
  INIT_TYPE(PyOFXBooleanParameterType, "ofx.BooleanParameter", PyOFXBooleanParameter);
  PyOFXBooleanParameterType.tp_base = &PyOFXValueParameterType;
  PyOFXBooleanParameterType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXBooleanParameterType.tp_init = PyOFXBooleanParameter_Init;
  PyOFXBooleanParameterType.tp_getset = PyOFXBooleanParameter_GetSeters;
  PyOFXBooleanParameterType.tp_methods = PyOFXBooleanParameter_Methods;
  if (PyType_Ready(&PyOFXBooleanParameterType) < 0)
  {
    return false;
  }
  
  Py_INCREF(&PyOFXBooleanParameterDescriptorType);
  PyModule_AddObject(mod, "BooleanParameterDescriptor", (PyObject*)&PyOFXBooleanParameterDescriptorType);
  
  Py_INCREF(&PyOFXBooleanParameterType);
  PyModule_AddObject(mod, "BooleanParameter", (PyObject*)&PyOFXBooleanParameterType);
  
  return true;
}
