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

#include "entrypoints.h"

PyImageEffectPlugin *gEffectPlugins[PYOFX_MAX_ENTRY] = {0};
PyObject* gInteractDescClasses[PYOFX_MAX_ENTRY] = {0};
PyObject* gInteractClasses[PYOFX_MAX_ENTRY] = {0};
PyObject* gInterpFuncObjs[PYOFX_MAX_ENTRY] = {0};

// also keep those to get an index back
OfxSetHostFunc gSetHostFuncs[PYOFX_MAX_ENTRY] = {0};
ofx::EntryPoint gMainFuncs[PYOFX_MAX_ENTRY] = {0};
ofx::EntryPoint gInteractFuncs[PYOFX_MAX_ENTRY] = {0};
OfxInterpFunc gInterpFuncs[PYOFX_MAX_ENTRY] = {0};

#ifdef PYOFX_USE_MACROS

#include "macros.h"

#define FIND_INTERACT(N, RV, DESC, INST)\
  if ((gInteractDescClasses[N] == 0 && gInteractClasses[N] == 0) ||\
      (gInteractDescClasses[N] == DESC && gInteractClasses[N] == INST))\
  {\
    gInteractDescClasses[N] = DESC;\
    gInteractClasses[N] = INST;\
    rv = PyOFX_InteractMain<N>;\
    gInteractFuncs[N] = rv;\
  }\
  else

#define FIND_INTERACT_LAST(N, RV, DESC, INST)\
  {\
    rv = 0;\
  }

ofx::EntryPoint PyOFX_GetInteractFunc(PyObject *descClass, PyObject *instClass)
{
  ofx::EntryPoint rv = 0;
  
  MCR_REP(PYOFX_MAX_ENTRY, FIND_INTERACT, FIND_INTERACT_LAST, rv, descClass, instClass);
  return rv;
}

#define FIND_HOST(N, RV, PLUGIN, DUMMY)\
  if (gEffectPlugins[N] == 0 || gEffectPlugins[N] == PLUGIN)\
  {\
    gEffectPlugins[N] = PLUGIN;\
    rv = PyOFX_SetHost<N>;\
    gSetHostFuncs[N] = rv;\
  }\
  else

#define FIND_HOST_LAST(N, RV, PLUGIN, DUMMY)\
  {\
    rv = 0;\
  }

OfxSetHostFunc PyOFX_GetSetHostFunc(PyImageEffectPlugin *plugin)
{
  OfxSetHostFunc rv = 0;
  
  MCR_REP(PYOFX_MAX_ENTRY, FIND_HOST, FIND_HOST_LAST, rv, plugin, 0);
  return rv;
}

#define FIND_EFFECT(N, RV, PLUGIN, DUMMY)\
  if (gEffectPlugins[N] == 0 || gEffectPlugins[N] == PLUGIN)\
  {\
    gEffectPlugins[N] = PLUGIN;\
    rv = PyOFX_Main<N>;\
    gMainFuncs[N] = rv;\
  }\
  else

#define FIND_EFFECT_LAST(N, RV, PLUGIN, DUMMY)\
  {\
    rv = 0;\
  }

ofx::EntryPoint PyOFX_GetMainFunc(PyImageEffectPlugin *plugin)
{
  ofx::EntryPoint rv = 0;
  
  MCR_REP(PYOFX_MAX_ENTRY, FIND_EFFECT, FIND_EFFECT_LAST, rv, plugin, 0);
  return rv;
}

#define FIND_INTERPFUNC(N, RV, FUNCOBJ, DUMMY)\
  if (gInterpFuncObjs[N] == 0 || gInterpFuncObjs[N] == FUNCOBJ)\
  {\
    gInterpFuncObjs[N] = FUNCOBJ;\
    rv = ofx::InterpFuncWrap<PyOFX_InterpFunc<N> >;\
    gInterpFuncs[N] = rv;\
  }\
  else

#define FIND_INTERPFUNC_LAST(N, RV, FUNCOBJ, DUMMY)\
  {\
    rv = 0;\
  }

OfxInterpFunc PyOFX_GetInterpFunc(PyObject *funcObj)
{
  OfxInterpFunc rv = 0;
  
  MCR_REP(PYOFX_MAX_ENTRY, FIND_INTERPFUNC, FIND_INTERPFUNC_LAST, rv, funcObj, 0);
  return rv;
}

#else

template <int IDX, int MAXIDX>
struct Functions
{
  static OfxSetHostFunc GetSetHostFunc(PyImageEffectPlugin *plugin)
  {
    if (gEffectPlugins[IDX] == 0 || gEffectPlugins[IDX] == plugin)
    {
      gEffectPlugins[IDX] = plugin;
      OfxSetHostFunc rv = PyOFX_SetHost<IDX>;
      gSetHostFuncs[IDX] = rv;
      return rv;
    }
    return Functions<IDX+1, MAXIDX>::GetSetHostFunc(plugin);
  }
  
  static ofx::EntryPoint GetMainFunc(PyImageEffectPlugin *plugin)
  {
    if (gEffectPlugins[IDX] == 0 || gEffectPlugins[IDX] == plugin)
    {
      gEffectPlugins[IDX] = plugin;
      ofx::EntryPoint rv = PyOFX_Main<IDX>;
      gMainFuncs[IDX] = rv;
      return rv;
    }
    return Functions<IDX+1, MAXIDX>::GetMainFunc(plugin);
  }
  
  static ofx::EntryPoint GetInteractFunc(PyObject *descClass, PyObject *instClass)
  {
    if ((gInteractDescClasses[IDX] == 0 && gInteractClasses[IDX] == 0) ||
        (gInteractDescClasses[IDX] == descClass && gInteractClasses[IDX] == instClass))
    {
      gInteractDescClasses[IDX] = descClass;
      gInteractClasses[IDX] = instClass;
      ofx::EntryPoint rv = PyOFX_InteractMain<IDX>;
      gInteractFuncs[IDX] = rv;
      return rv;
    }
    return Functions<IDX+1, MAXIDX>::GetInteractFunc(descClass, instClass);
  }
  
  static OfxInterpFunc GetInterpFunc(PyObject *funcObj)
  {
    if (gInterpFuncObjs[IDX] == 0 || gInterpFuncObjs[IDX] == funcObj)
    {
      gInterpFuncObjs[IDX] = funcObj;
      OfxInterpFunc rv = ofx::InterpFuncWrap<PyOFX_InterpFunc<IDX> >;
      gInterpFuncs[IDX] = rv;
      return rv;
    }
    return Functions<IDX+1, MAXIDX>::GetInterpFunc(funcObj);
  }
};

template <int IDX>
struct Functions<IDX, IDX>
{
  static OfxSetHostFunc GetSetHostFunc(PyImageEffectPlugin *)
  {
    return 0;
  }
  
  static ofx::EntryPoint GetMainFunc(PyImageEffectPlugin *)
  {
    return 0;
  }
  
  static ofx::EntryPoint GetInteractFunc(PyObject *, PyObject *)
  {
    return 0;
  }
  
  static OfxInterpFunc GetInterpFunc(PyObject *)
  {
    return 0;
  }
};

ofx::EntryPoint PyOFX_GetInteractFunc(PyObject *descClass, PyObject *instClass)
{
  return Functions<0, PYOFX_MAX_ENTRY>::GetInteractFunc(descClass, instClass);
}

OfxSetHostFunc PyOFX_GetSetHostFunc(PyImageEffectPlugin *plugin)
{
  return Functions<0, PYOFX_MAX_ENTRY>::GetSetHostFunc(plugin);
}

ofx::EntryPoint PyOFX_GetMainFunc(PyImageEffectPlugin *plugin)
{
  return Functions<0, PYOFX_MAX_ENTRY>::GetMainFunc(plugin);
}

OfxInterpFunc PyOFX_GetInterpFunc(PyObject *funcObj)
{
  return Functions<0, PYOFX_MAX_ENTRY>::GetInterpFunc(funcObj);
}

#endif

int PyOFX_GetInteractFuncIndex(ofx::EntryPoint func)
{
  for (int i=0; i<PYOFX_MAX_ENTRY; ++i)
  {
    if (gInteractFuncs[i] == func)
    {
      return i;
    }
  }
  return -1;
}

int PyOFX_GetSetHostFuncIndex(OfxSetHostFunc func)
{
  for (int i=0; i<PYOFX_MAX_ENTRY; ++i)
  {
    if (gSetHostFuncs[i] == func)
    {
      return i;
    }
  }
  return -1;
}

int PyOFX_GetMainFuncIndex(ofx::EntryPoint func)
{
  for (int i=0; i<PYOFX_MAX_ENTRY; ++i)
  {
    if (gMainFuncs[i] == func)
    {
      return i;
    }
  }
  return -1;
}

int PyOFX_GetInterpFuncIndex(OfxInterpFunc func)
{
  for (int i=0; i<PYOFX_MAX_ENTRY; ++i)
  {
    if (gInterpFuncs[i] == func)
    {
      return i;
    }
  }
  return -1;
}

