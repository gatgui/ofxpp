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

/*

#include "macros.h"

#define FIND_INTERACT_SLOT(N, MAX, descClass, instClass)\
  if (N >= MAX) {\
    return 0;\
  } else if (gInteractDescClasses[N] == 0 && gInteractClasses[N] == 0) {\
    gInteractDescClasses[N] = descClass;\
    gInteractClasses[N] = instClass;\
    return PyInteractEntry<N>;\
  } else {\
    FIND_INTERACT_SLOT(TPL_INCR(N), MAX, descClass, instClass);\
  }

#define FIND_EFFECT_SLOT(N, MAX, plugin) \
  if (N >= MAX) {\
    return 0;\
  } else if (gEffectPlugins[N] == 0) {\
    gEffectPlugins[N] = plugin;\
    return PyEffectEntry<N>;\
  } else {\
    FIND_EFFECT_SLOT(TPL_INCR(N), MAX, plugin);\
  }

#define FIND_INTERPFUNC_SLOT(N, MAX, funcObj)\
  if (N >= MAX) {\
    return 0;\
  } else if (gInterpolators[N] == 0) {\
    gInterpolators[N] = funcObj;\
    return ofx::InterpFuncWrap<PyInterpFunc<N> >;\
  } else {\
    FIND_INTERPOLATOR_SLOT(TPL_INCR(N), MAX, funcObj);\
  }

*/

PyImageEffectPlugin *gEffectPlugins[OFXPY_MAX_ENTRY] = {0};
PyObject* gInteractDescClasses[OFXPY_MAX_ENTRY] = {0};
PyObject* gInteractClasses[OFXPY_MAX_ENTRY] = {0};
PyObject* gInterpolators[OFXPY_MAX_ENTRY] = {0};
OfxHost* gHost;

template <int IDX, int MAXIDX>
struct Adder
{
  static ofx::EntryPoint AddEffect(PyImageEffectPlugin *plugin)
  {
    if (gEffectPlugins[IDX] == 0 || gEffectPlugins[IDX] == plugin)
    {
      return PyEffectEntry<IDX>;
    }
    else
    {
      return Adder<IDX+1, MAXIDX>::AddEffect(plugin);
    }
  }
  
  static ofx::EntryPoint AddInteract(PyObject *descClass, PyObject *instClass)
  {
    if ((gInteractDescClasses[IDX] == 0 && gInteractClasses[IDX] == 0) ||
        (gInteractDescClasses[IDX] == descClass && gInteractClasses[IDX] == instClass))
    {
      gInteractDescClasses[IDX] = descClass;
      gInteractClasses[IDX] = instClass;
      return PyInteractEntry<IDX>;
    }
    else
    {
      return Adder<IDX+1, MAXIDX>::AddInteract(descClass, instClass);
    }
  }
  
  static OfxInterpFunc AddInterpFunc(PyObject *funcObj)
  {
    if (gInterpolators[IDX] == 0 || gInterpolators[IDX] == funcObj)
    {
      return ofx::InterpFuncWrap<PyInterpFunc<IDX> >;
    }
    else
    {
      return Adder<IDX+1, MAXIDX>::AddInterpFunc(funcObj);
    }
  }
};

template <int IDX>
struct Adder<IDX, IDX>
{
  static ofx::EntryPoint AddEffect(PyImageEffectPlugin *)
  {
    return 0;
  }
  
  static ofx::EntryPoint AddInteract(PyObject *, PyObject *)
  {
    return 0;
  }
  
  static OfxInterpFunc AddInterpFunc(PyObject *)
  {
    return 0;
  }
};

// ---

void PySetHost(OfxHost *h)
{
  if (gHost != 0 && gHost != h)
  {
    throw std::runtime_error("PyOFX cannot be run on different host at the same time.");
  }
  gHost = h;
}

ofx::EntryPoint PyAddInteract(PyObject *descClass, PyObject *instClass)
{
  return Adder<0, OFXPY_MAX_ENTRY>::AddInteract(descClass, instClass);
}

ofx::EntryPoint PyAddEffectPlugin(PyImageEffectPlugin *plugin)
{
  return Adder<0, OFXPY_MAX_ENTRY>::AddEffect(plugin);
}

OfxInterpFunc PyAddInterpFunc(PyObject *funcObj)
{
  return Adder<0, OFXPY_MAX_ENTRY>::AddInterpFunc(funcObj);
}

int PyEffectPluginIndex(PyImageEffectPlugin *plugin)
{
  for (int i=0; i<OFXPY_MAX_ENTRY; ++i)
  {
    if (gEffectPlugins[i] == plugin)
    {
      return i;
    }
  }
  return -1;
}

int PyInterpFuncIndex(ofx::InterpFunc)
{
  return -1;
}

int PyInteractIndex(ofx::EntryPoint)
{
  return -1;
}
