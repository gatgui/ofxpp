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
#include <sstream>

void LogPythonError()
{
  if (PyErr_Occurred() == 0)
  {
    return;
  }
  
  std::ostringstream oss;
    
  PyObject *et=0, *ev=0, *etb=0, *s=0;
  
  PyErr_Fetch(&et, &ev, &etb);
  
  //s = PyObject_Str(et);
  //oss << std::endl << "--- Python --- " << PyString_AsString(s);
  //Py_DECREF(s);
  
  if (ev)
  {
    s = PyObject_Str(ev);
    oss << PyString_AsString(s);
    Py_DECREF(s);
  }
  
  if (etb)
  {
    PyObject *tbmn = PyString_FromString("traceback");
    PyObject *tbm = PyImport_Import(tbmn);
    Py_DECREF(tbmn);
    if (tbm)
    {
      PyObject *mdict = PyModule_GetDict(tbm);
      PyObject *func = PyDict_GetItemString(mdict, "format_tb"); // borrowed reference
      if (func && PyCallable_Check(func))
      {
        PyObject *tbargs = PyTuple_New(1);
        PyTuple_SetItem(tbargs, 0, etb);
        PyObject *tbl = PyObject_CallObject(func, tbargs);
        if (tbl)
        {
          Py_ssize_t nf = PyList_Size(tbl);
          for (Py_ssize_t f=0; f<nf; ++f)
          {
            PyObject *fs = PyList_GetItem(tbl, f);
            std::string lines = PyString_AsString(fs);
            size_t p0 = 0, p1 = lines.find('\n', p0);
            while (p1 != std::string::npos)
            {
              std::string line = lines.substr(p0, p1-p0);
              oss << std::endl << line;
              p0 = p1 + 1;
              p1 = lines.find('\n', p0);
            }
            oss << std::endl << lines.substr(p0);
          }
          Py_DECREF(tbl);
        }
        Py_DECREF(tbargs);
      }
      Py_DECREF(tbm);
    }
  }
  
  Py_XDECREF(et);
  Py_XDECREF(ev);
  Py_XDECREF(etb);
  
  oss << std::endl;
  
  ofx::Log("pyofx:\n*** Python Error ***\n%s", oss.str().c_str());
}

// ---

PyTypeObject PyOFXActionArgumentsType;

static PyObject* PyOFXActionArguments_New(PyTypeObject *t, PyObject *, PyObject *)
{
  return t->tp_alloc(t, 0);
}

static int PyOFXActionArguments_Init(PyObject *, PyObject *, PyObject *)
{
  return 0;
}

static void PyOFXActionArguments_Delete(PyObject *self)
{
  self->ob_type->tp_free(self);
}



// ---

static PyObject* PyOFX_CanonicalToPixelCoords(PyObject *, PyObject *args)
{
  double x = 0, y = 0;
  double par = 1;
  double rsx = 1, rsy = 1;
  int field = 0;
  
  if (!PyArg_ParseTuple(args, "dddddi", &x, &y, &par, &rsx, &rsy, &field))
  {
    return NULL;
  }
  
  int outX, outY;
  
  ofx::CanonicalToPixelCoords(x, y, par, rsx, rsy, ofx::ImageField(field), &outX, &outY);
  
  return Py_BuildValue("ii", outX, outY);
}

static PyObject* PyOFX_PixelToCanonicalCoords(PyObject *, PyObject *args)
{
  int x = 0, y = 0;
  double par = 1;
  double rsx = 1, rsy = 1;
  int field = 0;
  
  if (!PyArg_ParseTuple(args, "iidddi", &x, &y, &par, &rsx, &rsy, &field))
  {
    return NULL;
  }
  
  double outX, outY;
  
  ofx::PixelToCanonicalCoords(x, y, par, rsx, rsy, ofx::ImageField(field), &outX, &outY);
  
  return Py_BuildValue("dd", outX, outY);
}

static PyObject* PyOFX_NormalisedToCanonicalCoords(PyObject *, PyObject *args)
{
  double inX, inY, extW, extH, offX, offY;
  bool absolute = false;
  
  if (!PyArg_ParseTuple(args, "ddddddB", &inX, &inY, &extW, &extH, &offX, &offY, &absolute))
  {
    return NULL;
  }
  
  double outX, outY;
  
  ofx::NormalisedToCanonicalCoords(inX, inY, extW, extH, offX, offY, absolute, &outX, &outY);
  
  return Py_BuildValue("dd", outX, outY);
}

static PyObject* PyOFX_CanonicalToNormalisedCoords(PyObject *, PyObject *args)
{
  double inX, inY, extW, extH, offX, offY;
  bool absolute = false;
  
  if (!PyArg_ParseTuple(args, "ddddddB", &inX, &inY, &extW, &extH, &offX, &offY, &absolute))
  {
    return NULL;
  }
  
  double outX, outY;
  
  ofx::CanonicalToNormalisedCoords(inX, inY, extW, extH, offX, offY, absolute, &outX, &outY);
  
  return Py_BuildValue("dd", outX, outY);
}

PyObject* PyOFX_Log(PyObject *, PyObject *args)
{
  char *msg = 0;
  
  if (!PyArg_ParseTuple(args, "s", &msg))
  {
    return NULL;
  }
  
  ofx::Log(msg);
  
  Py_RETURN_NONE;
}

PyObject* PyOFX_DebugLog(PyObject *, PyObject *args)
{
  char *msg = 0;
  
  if (!PyArg_ParseTuple(args, "s", &msg))
  {
    return NULL;
  }
  
  ofx::DebugLog(msg);
  
  Py_RETURN_NONE;
}

static PyMethodDef PyOFX_Methods[] =
{
  {"CanonicalToPixelCoords", PyOFX_CanonicalToPixelCoords, METH_VARARGS, 0},
  {"PixelToCanonicalCoords", PyOFX_PixelToCanonicalCoords, METH_VARARGS, 0},
  {"NormalisedToCanonicalCoords", PyOFX_NormalisedToCanonicalCoords, METH_VARARGS, 0},
  {"CanonicalToNormalisedCoords", PyOFX_CanonicalToNormalisedCoords, METH_VARARGS, 0},
  {"Log", PyOFX_Log, METH_VARARGS, 0},
  {"DebugLog", PyOFX_DebugLog, METH_VARARGS, 0},
  {NULL, NULL, NULL, NULL}
};


PyMODINIT_FUNC initofx(void)
{
  PyObject *mod = Py_InitModule("ofx", PyOFX_Methods);
  
  PyModule_AddIntConstant(mod, "TypeImageEffectHost", ofx::TypeImageEffectHost);
  PyModule_AddIntConstant(mod, "TypeImageEffect", ofx::TypeImageEffect);
  PyModule_AddIntConstant(mod, "TypeImageEffectInstance", ofx::TypeImageEffectInstance);
  PyModule_AddIntConstant(mod, "TypeParameter", ofx::TypeParameter);
  PyModule_AddIntConstant(mod, "TypeParameterInstance", ofx::TypeParameterInstance);
  PyModule_AddIntConstant(mod, "TypeClip", ofx::TypeClip);
  PyModule_AddIntConstant(mod, "TypeImage", ofx::TypeImage);
  
  PyModule_AddIntConstant(mod, "BitDepthNone", ofx::BitDepthNone);
  PyModule_AddIntConstant(mod, "BitDepthByte", ofx::BitDepthByte);
  PyModule_AddIntConstant(mod, "BitDepthShort", ofx::BitDepthShort);
  PyModule_AddIntConstant(mod, "BitDepthFloat", ofx::BitDepthFloat);
  
  PyModule_AddIntConstant(mod, "ImageComponentNone", ofx::ImageComponentNone);
#ifdef OFX_API_1_2
  PyModule_AddIntConstant(mod, "ImageComponentRGB", ofx::ImageComponentRGB);
#endif
  PyModule_AddIntConstant(mod, "ImageComponentRGBA", ofx::ImageComponentRGBA);
  PyModule_AddIntConstant(mod, "ImageComponentAlpha", ofx::ImageComponentAlpha);
  PyModule_AddIntConstant(mod, "ImageComponentYUVA", ofx::ImageComponentYUVA);
  
  PyModule_AddIntConstant(mod, "ImageFieldNone", ofx::ImageFieldNone);
  PyModule_AddIntConstant(mod, "ImageFieldBoth", ofx::ImageFieldBoth);
  PyModule_AddIntConstant(mod, "ImageFieldLower", ofx::ImageFieldLower);
  PyModule_AddIntConstant(mod, "ImageFieldUpper", ofx::ImageFieldUpper);
  
  PyModule_AddIntConstant(mod, "ImageFieldExtractBoth", ofx::ImageFieldExtractBoth);
  PyModule_AddIntConstant(mod, "ImageFieldExtractSingle", ofx::ImageFieldExtractSingle);
  PyModule_AddIntConstant(mod, "ImageFieldExtractDoubled", ofx::ImageFieldExtractDoubled);
  
  PyModule_AddIntConstant(mod, "ImageFieldOrderNone", ofx::ImageFieldOrderNone);
  PyModule_AddIntConstant(mod, "ImageFieldOrderLower", ofx::ImageFieldOrderLower);
  PyModule_AddIntConstant(mod, "ImageFieldOrderUpper", ofx::ImageFieldOrderUpper);
  
  PyModule_AddIntConstant(mod, "ImageOpaque", ofx::ImageOpaque);
  PyModule_AddIntConstant(mod, "ImagePreMultiplied", ofx::ImagePreMultiplied);
  PyModule_AddIntConstant(mod, "ImageUnPreMultiplied", ofx::ImageUnPreMultiplied);
  
  PyModule_AddIntConstant(mod, "ImageEffectContextGenerator", ofx::ImageEffectContextGenerator);
  PyModule_AddIntConstant(mod, "ImageEffectContextFilter", ofx::ImageEffectContextFilter);
  PyModule_AddIntConstant(mod, "ImageEffectContextTransition", ofx::ImageEffectContextTransition);
  PyModule_AddIntConstant(mod, "ImageEffectContextPaint", ofx::ImageEffectContextPaint);
  PyModule_AddIntConstant(mod, "ImageEffectContextGeneral", ofx::ImageEffectContextGeneral);
  PyModule_AddIntConstant(mod, "ImageEffectContextRetimer", ofx::ImageEffectContextRetimer);
  
  PyModule_AddIntConstant(mod, "RenderThreadUnsafe", ofx::RenderThreadUnsafe);
  PyModule_AddIntConstant(mod, "RenderThreadInstanceSafe", ofx::RenderThreadInstanceSafe);
  PyModule_AddIntConstant(mod, "RenderThreadFullySafe", ofx::RenderThreadFullySafe);
  
  PyModule_AddIntConstant(mod, "ParamTypeInteger", ofx::ParamTypeInteger);
  PyModule_AddIntConstant(mod, "ParamTypeDouble", ofx::ParamTypeDouble);
  PyModule_AddIntConstant(mod, "ParamTypeBoolean", ofx::ParamTypeBoolean);
  PyModule_AddIntConstant(mod, "ParamTypeChoice", ofx::ParamTypeChoice);
  PyModule_AddIntConstant(mod, "ParamTypeRGBA", ofx::ParamTypeRGBA);
  PyModule_AddIntConstant(mod, "ParamTypeRGB", ofx::ParamTypeRGB);
  PyModule_AddIntConstant(mod, "ParamTypeDouble2D", ofx::ParamTypeDouble2D);
  PyModule_AddIntConstant(mod, "ParamTypeInteger2D", ofx::ParamTypeInteger2D);
  PyModule_AddIntConstant(mod, "ParamTypeDouble3D", ofx::ParamTypeDouble3D);
  PyModule_AddIntConstant(mod, "ParamTypeInteger3D", ofx::ParamTypeInteger3D);
  PyModule_AddIntConstant(mod, "ParamTypeString", ofx::ParamTypeString);
  PyModule_AddIntConstant(mod, "ParamTypeCustom", ofx::ParamTypeCustom);
  PyModule_AddIntConstant(mod, "ParamTypeGroup", ofx::ParamTypeGroup);
  PyModule_AddIntConstant(mod, "ParamTypePage", ofx::ParamTypePage);
  PyModule_AddIntConstant(mod, "ParamTypePushButton", ofx::ParamTypePushButton);
#ifdef OFX_API_1_2
  PyModule_AddIntConstant(mod, "ParamTypeParametric", ofx::ParamTypeParametric);
#endif
  
  PyModule_AddIntConstant(mod, "ParamInvalidateValueChange", ofx::ParamInvalidateValueChange);
  PyModule_AddIntConstant(mod, "ParamInvalidateValueChangeToEnd", ofx::ParamInvalidateValueChangeToEnd);
  PyModule_AddIntConstant(mod, "ParamInvalidateAll", ofx::ParamInvalidateAll);
  
  PyModule_AddIntConstant(mod, "StringParamSingleLine", ofx::StringParamSingleLine);
  PyModule_AddIntConstant(mod, "StringParamMultiLine", ofx::StringParamMultiLine);
  PyModule_AddIntConstant(mod, "StringParamFilePath", ofx::StringParamFilePath);
  PyModule_AddIntConstant(mod, "StringParamDirectoryPath", ofx::StringParamDirectoryPath);
  PyModule_AddIntConstant(mod, "StringParamLabel", ofx::StringParamLabel);
  
  PyModule_AddIntConstant(mod, "DoubleParamPlain", ofx::DoubleParamPlain);
  PyModule_AddIntConstant(mod, "DoubleParamAngle", ofx::DoubleParamAngle);
  PyModule_AddIntConstant(mod, "DoubleParamScale", ofx::DoubleParamScale);
  PyModule_AddIntConstant(mod, "DoubleParamTime", ofx::DoubleParamTime);
  PyModule_AddIntConstant(mod, "DoubleParamAbsoluteTime", ofx::DoubleParamAbsoluteTime);
  PyModule_AddIntConstant(mod, "DoubleParamNormalisedX", ofx::DoubleParamNormalisedX);
  PyModule_AddIntConstant(mod, "DoubleParamNormalisedXAbsolute", ofx::DoubleParamNormalisedXAbsolute);
  PyModule_AddIntConstant(mod, "DoubleParamNormalisedY", ofx::DoubleParamNormalisedY);
  PyModule_AddIntConstant(mod, "DoubleParamNormalisedYAbsolute", ofx::DoubleParamNormalisedYAbsolute);
  PyModule_AddIntConstant(mod, "DoubleParamNormalisedXY", ofx::DoubleParamNormalisedXY);
  PyModule_AddIntConstant(mod, "DoubleParamNormalisedXYAbsolute", ofx::DoubleParamNormalisedXYAbsolute);
#ifdef OFX_API_1_2
  PyModule_AddIntConstant(mod, "DoubleParamX", ofx::DoubleParamX);
  PyModule_AddIntConstant(mod, "DoubleParamXAbsolute", ofx::DoubleParamXAbsolute);
  PyModule_AddIntConstant(mod, "DoubleParamY", ofx::DoubleParamY);
  PyModule_AddIntConstant(mod, "DoubleParamYAbsolute", ofx::DoubleParamYAbsolute);
  PyModule_AddIntConstant(mod, "DoubleParamXY", ofx::DoubleParamXY);
  PyModule_AddIntConstant(mod, "DoubleParamXYAbsolute", ofx::DoubleParamXYAbsolute);
#endif
  
#ifdef OFX_API_1_2
  PyModule_AddIntConstant(mod, "CoordinatesCanonical", ofx::CoordinatesCanonical);
  PyModule_AddIntConstant(mod, "CoordinatesNormalised", ofx::CoordinatesNormalised);
#endif
  
  PyModule_AddIntConstant(mod, "KeyDirectionPrev", ofx::KeyDirectionPrev);
  PyModule_AddIntConstant(mod, "KeyDirectionExact", ofx::KeyDirectionExact);
  PyModule_AddIntConstant(mod, "KeyDirectionNext", ofx::KeyDirectionNext);
  
  PyModule_AddIntConstant(mod, "MessageTypeFatal", ofx::MessageTypeFatal);
  PyModule_AddIntConstant(mod, "MessageTypeError", ofx::MessageTypeError);
  PyModule_AddIntConstant(mod, "MessageTypeMessage", ofx::MessageTypeMessage);
  PyModule_AddIntConstant(mod, "MessageTypeLog", ofx::MessageTypeLog);
  PyModule_AddIntConstant(mod, "MessageTypeQuestion", ofx::MessageTypeQuestion);
  
  PyModule_AddIntConstant(mod, "ChangeUserEdited", ofx::ChangeUserEdited);
  PyModule_AddIntConstant(mod, "ChangePluginEdited", ofx::ChangePluginEdited);
  PyModule_AddIntConstant(mod, "ChangeTime", ofx::ChangeTime);
  
  PyModule_AddIntConstant(mod, "ActionLoad", ofx::ActionLoad);
  PyModule_AddIntConstant(mod, "ActionInteractLoseFocus", ofx::ActionInteractLoseFocus);
  PyModule_AddIntConstant(mod, "ActionInteractGainFocus", ofx::ActionInteractGainFocus);
  PyModule_AddIntConstant(mod, "ActionInteractKeyRepeat", ofx::ActionInteractKeyRepeat);
  PyModule_AddIntConstant(mod, "ActionInteractKeyUp", ofx::ActionInteractKeyUp);
  PyModule_AddIntConstant(mod, "ActionInteractKeyDown", ofx::ActionInteractKeyDown);
  PyModule_AddIntConstant(mod, "ActionInteractPenUp", ofx::ActionInteractPenUp);
  PyModule_AddIntConstant(mod, "ActionInteractPenDown", ofx::ActionInteractPenDown);
  PyModule_AddIntConstant(mod, "ActionInteractPenMotion", ofx::ActionInteractPenMotion);
  PyModule_AddIntConstant(mod, "ActionInteractDraw", ofx::ActionInteractDraw);
  PyModule_AddIntConstant(mod, "ActionImageEffectGetTimeDomain", ofx::ActionImageEffectGetTimeDomain);
  PyModule_AddIntConstant(mod, "ActionImageEffectGetClipPreferences", ofx::ActionImageEffectGetClipPreferences);
  PyModule_AddIntConstant(mod, "ActionImageEffectEndSequenceRender", ofx::ActionImageEffectEndSequenceRender);
  PyModule_AddIntConstant(mod, "ActionImageEffectBeginSequenceRender", ofx::ActionImageEffectBeginSequenceRender);
  PyModule_AddIntConstant(mod, "ActionImageEffectRender", ofx::ActionImageEffectRender);
  PyModule_AddIntConstant(mod, "ActionImageEffectIsIdentity", ofx::ActionImageEffectIsIdentity);
  PyModule_AddIntConstant(mod, "ActionImageEffectGetFramesNeeded", ofx::ActionImageEffectGetFramesNeeded);
  PyModule_AddIntConstant(mod, "ActionImageEffectGetRoI", ofx::ActionImageEffectGetRoI);
  PyModule_AddIntConstant(mod, "ActionImageEffectGetRoD", ofx::ActionImageEffectGetRoD);
  PyModule_AddIntConstant(mod, "ActionImageEffectDescribeInContext", ofx::ActionImageEffectDescribeInContext);
  PyModule_AddIntConstant(mod, "ActionEndInstanceEdit", ofx::ActionEndInstanceEdit);
  PyModule_AddIntConstant(mod, "ActionBeginInstanceEdit", ofx::ActionBeginInstanceEdit);
  PyModule_AddIntConstant(mod, "ActionUnload", ofx::ActionUnload);
  PyModule_AddIntConstant(mod, "ActionDescribe", ofx::ActionDescribe);
  PyModule_AddIntConstant(mod, "ActionCreateInstance", ofx::ActionCreateInstance);
  PyModule_AddIntConstant(mod, "ActionDestroyInstance", ofx::ActionDestroyInstance);
  PyModule_AddIntConstant(mod, "ActionInstanceChanged", ofx::ActionInstanceChanged);
  PyModule_AddIntConstant(mod, "ActionBeginInstanceChanged", ofx::ActionBeginInstanceChanged);
  PyModule_AddIntConstant(mod, "ActionEndInstanceChanged", ofx::ActionEndInstanceChanged);
  PyModule_AddIntConstant(mod, "ActionPurgeCaches", ofx::ActionPurgeCaches);
  PyModule_AddIntConstant(mod, "ActionSyncPrivateData", ofx::ActionSyncPrivateData);
  
  PyModule_AddIntConstant(mod, "SequentialRenderNotNeeded", ofx::SequentialRenderNotNeeded);
  PyModule_AddIntConstant(mod, "SequentialRenderRequired", ofx::SequentialRenderRequired);
  PyModule_AddIntConstant(mod, "SequentialRenderUnknown", ofx::SequentialRenderUnknown);
  PyModule_AddIntConstant(mod, "SequentialRenderAlways", ofx::SequentialRenderAlways);
#ifdef OFX_API_1_2
  PyModule_AddIntConstant(mod, "SequentialRenderIfPossible", ofx::SequentialRenderIfPossible);
  PyModule_AddIntConstant(mod, "SequentialRenderSometimes", ofx::SequentialRenderSometimes);
#endif

  PyModule_AddIntConstant(mod, "StatOK", kOfxStatOK);
  PyModule_AddIntConstant(mod, "StatFailed", kOfxStatFailed);
  PyModule_AddIntConstant(mod, "StatErrFatal", kOfxStatErrFatal);
  PyModule_AddIntConstant(mod, "StatErrUnknown", kOfxStatErrUnknown);
  PyModule_AddIntConstant(mod, "StatErrMissingHostFeature", kOfxStatErrMissingHostFeature);
  PyModule_AddIntConstant(mod, "StatErrUnsupported", kOfxStatErrUnsupported);
  PyModule_AddIntConstant(mod, "StatErrExists", kOfxStatErrExists);
  PyModule_AddIntConstant(mod, "StatErrFormat", kOfxStatErrFormat);
  PyModule_AddIntConstant(mod, "StatErrMemory", kOfxStatErrMemory);
  PyModule_AddIntConstant(mod, "StatErrBadHandle", kOfxStatErrBadHandle);
  PyModule_AddIntConstant(mod, "StatErrBadIndex", kOfxStatErrBadIndex);
  PyModule_AddIntConstant(mod, "StatErrValue", kOfxStatErrValue);
  PyModule_AddIntConstant(mod, "StatReplyYes", kOfxStatReplyYes);
  PyModule_AddIntConstant(mod, "StatReplyNo", kOfxStatReplyNo);
  PyModule_AddIntConstant(mod, "StatReplyDefault", kOfxStatReplyDefault);
  
  PyModule_AddStringConstant(mod, "PageSkipRow", kOfxParamPageSkipRow);
  PyModule_AddStringConstant(mod, "PageSkipColumn", kOfxParamPageSkipColumn);
  
  INIT_TYPE(PyOFXActionArgumentsType, "ofx.ActionArguments", PyOFXActionArguments);
  PyOFXActionArgumentsType.tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE;
  PyOFXActionArgumentsType.tp_new = PyOFXActionArguments_New;
  PyOFXActionArgumentsType.tp_init = PyOFXActionArguments_Init;
  PyOFXActionArgumentsType.tp_dealloc = PyOFXActionArguments_Delete;
  PyOFXActionArgumentsType.tp_setattro = PyObject_GenericSetAttr;
  PyOFXActionArgumentsType.tp_getattro = PyObject_GenericGetAttr;
  if (PyType_Ready(&PyOFXActionArgumentsType) < 0)
  {
    Py_DECREF(mod);
    return;
  }
  
  Py_INCREF(&PyOFXActionArgumentsType);
  PyModule_AddObject(mod, "ActionArguments", (PyObject*)&PyOFXActionArgumentsType);
  
  if (!PyOFX_InitException(mod))
  {
    Py_DECREF(mod);
    return;
  }
  
  if (!PyOFX_InitHandle(mod))
  {
    Py_DECREF(mod);
    return;
  }
  
  if (!PyOFX_InitMessage(mod))
  {
    Py_DECREF(mod);
    return;
  }
  
  if (!PyOFX_InitMemory(mod))
  {
    Py_DECREF(mod);
    return;
  }
  
  if (!PyOFX_InitProgress(mod))
  {
    Py_DECREF(mod);
    return;
  }
  
  if (!PyOFX_InitTimeLine(mod))
  {
    Py_DECREF(mod);
    return;
  }
  
  if (!PyOFX_InitProperty(mod))
  {
    Py_DECREF(mod);
    return;
  }
  
  if (!PyOFX_InitParameter(mod))
  {
    Py_DECREF(mod);
    return;
  }
  
  if (!PyOFX_InitParameterSet(mod))
  {
    Py_DECREF(mod);
    return;
  }
  
  if (!PyOFX_InitHost(mod))
  {
    Py_DECREF(mod);
    return;
  }
  
  if (!PyOFX_InitImage(mod))
  {
    Py_DECREF(mod);
    return;
  }
  
  if (!PyOFX_InitClip(mod))
  {
    Py_DECREF(mod);
    return;
  }
  
  if (!PyOFX_InitInteract(mod))
  {
    Py_DECREF(mod);
    return;
  }
  
  if (!PyOFX_InitImageEffect(mod))
  {
    Py_DECREF(mod);
    return;
  }
  
  if (!PyOFX_InitPlugin(mod))
  {
    Py_DECREF(mod);
    return;
  }
  
  if (!PyOFX_InitTest(mod))
  {
    Py_DECREF(mod);
    return;
  }
}
