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

PyTypeObject PyOFXImageEffectDescriptorType;

// ---

PyImageEffectDescriptor::PyImageEffectDescriptor(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl) throw(ofx::Exception);
PyImageEffectDescriptor::PyImageEffectDescriptor(const PyImageEffectDescriptor &rhs);
PyImageEffectDescriptor::~PyImageEffectDescriptor();

PyImageEffectDescriptor& PyImageEffectDescriptor::operator=(const PyImageEffectDescriptor &rhs);

OfxStatus PyImageEffectDescriptor::describe();
OfxStatus PyImageEffectDescriptor::describeInContext(ofx::ImageEffectContext ctx);

// ---

PyObject* PyOFXImageEffectDescriptor_New(PyTypeObject *t, PyObject *, PyObject *)
{
  PyObject *self = t->tp_alloc(t, 0);
  PyOFXImageEffectDescriptor *pdesc = (PyOFXImageEffectDescriptor*)self
  pdesc->desc = new PyImageEffectDescriptor();
  pdesc->desc->self(self);
  return self;
}


/*
inline ImageEffectHost* host() {
  return mHost;
}

inline OfxImageEffectHandle handle() {
  return mHandle;
}

inline PropertySet& properties() {
  return mProps;
}

inline ParameterSetDescriptor& parameters() {
  return mParams;
}

// suite

ClipDescriptor defineClip(const std::string &name) throw(Exception);

// properties

std::string label();
void label(const std::string &s);

std::string shortLabel();
void shortLabel(const std::string &s);

std::string longLabel();
void longLabel(const std::string &s);

int supportedContextsCount();
ImageEffectContext supportedContext(int i);
void supportedContext(int i, ImageEffectContext ctx);

std::string group();
void group(const std::string &g);

bool singleInstance();
void singleInstance(bool);

RenderThreadSafety renderThreadSafety();
void renderThreadSafety(RenderThreadSafety rts);

// indicates whether plugin relies on host for frame threading or not
bool hostFrameThreading();
void hostFrameThreading(bool);

// Use this way:
//   effectDesc->overlayInteract(InteractEntryPoint<MyPluginClass, MyInteractDescriptionClass, MyInteractClass>)
EntryPoint overlayInteract();
void overlayInteract(EntryPoint func);

bool supportsMultiResolution();
void supportsMultiResolution(bool);

bool supportsTiles();
void supportsTiles(bool);

bool temporalClipAccess();
void temporalClipAccess(bool);

int supportedPixelDepthsCount();
void supportedPixelDepth(int i, BitDepth bd);
BitDepth supportedPixelDepth(int i);

bool fieldRenderTwiceAlways();
void fieldRenderTwiceAlways(bool);

bool supportsMultipleClipDepths();
void supportsMultipleClipDepths(bool);

bool supportsMultipleClipPARs();
void supportsMultipleClipPARs(bool);  

int clipPreferencesSlaveParamCount();
std::string clipPreferencesSlaveParam(int i);
void clipPreferencesSlaveParam(int i, const std::string &n);

std::string pluginFilePath();

SequentialRender sequentialRender();
void sequentialRender(SequentialRender sr);

#ifdef OFX_API_1_2
int version(int level);
int majorVersion();
int minorVersion();
void version(int level, int v);

std::string versionLabel();
void versionLabel(const std::string &vl);

std::string description();
void description(const std::string &vl);
#endif
*/

// ---

// ---

bool PyOFX_InitImageEffect(PyObject *mod)
{
  return true;
}
