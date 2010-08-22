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

#include <ofx/parameter.h>
#include <ofx/host.h>

namespace ofx {

ParameterDescriptor::ParameterDescriptor() {
}

ParameterDescriptor::ParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : PropertySet(h, hdl) {
}

ParameterDescriptor::ParameterDescriptor(const ParameterDescriptor &rhs)
  : PropertySet(rhs) {
  
}

ParameterDescriptor::~ParameterDescriptor() {
}

ParameterDescriptor& ParameterDescriptor::operator=(const ParameterDescriptor &rhs) {
  PropertySet::operator=(rhs);
  return *this;
}

std::string ParameterDescriptor::name() {
  return getString(kOfxPropName, 0);
}

void ParameterDescriptor::name(const std::string &name) {
  setString(kOfxPropName, 0, name);
}

std::string ParameterDescriptor::label() {
  return getString(kOfxPropLabel, 0);
}

void ParameterDescriptor::label(const std::string &lbl) {
  setString(kOfxPropLabel, 0, lbl);
}

std::string ParameterDescriptor::shortLabel() {
  return getString(kOfxPropShortLabel, 0);
}

void ParameterDescriptor::shortLabel(const std::string &lbl) {
  setString(kOfxPropShortLabel, 0, lbl);
}

std::string ParameterDescriptor::longLabel() {
  return getString(kOfxPropLongLabel, 0);
}

void ParameterDescriptor::longLabel(const std::string &lbl) {
  setString(kOfxPropLongLabel, 0, lbl);
}

ParamType ParameterDescriptor::type() {
  return StringToParamType(getString(kOfxParamPropType, 0));
}

bool ParameterDescriptor::secret() {
  return (getInt(kOfxParamPropSecret, 0) == 1);
}

void ParameterDescriptor::secret(bool yes) {
  setInt(kOfxParamPropSecret, 0, (yes ? 1 : 0));
}

bool ParameterDescriptor::canUndo() {
  return (getInt(kOfxParamPropCanUndo, 0) == 1);
}

void ParameterDescriptor::canUndo(bool yes) {
  setInt(kOfxParamPropCanUndo, 0, (yes ? 1 : 0));
}

std::string ParameterDescriptor::hint() {
  return getString(kOfxParamPropHint, 0);
}

void ParameterDescriptor::hint(const std::string &h) {
  setString(kOfxParamPropHint, 0, h);
}

std::string ParameterDescriptor::scriptName() {
  return getString(kOfxParamPropScriptName, 0);
}

void ParameterDescriptor::scriptName(const std::string &h) {
  setString(kOfxParamPropScriptName, 0, h);
}

std::string ParameterDescriptor::parent() {
  return getString(kOfxParamPropParent, 0);
}

void ParameterDescriptor::parent(const std::string &n) {
  setString(kOfxParamPropParent, 0, n);
}

bool ParameterDescriptor::enabled() {
  return (getInt(kOfxParamPropEnabled, 0) == 1);
}

void ParameterDescriptor::enabled(bool yes) {
  setInt(kOfxParamPropEnabled, 0, (yes ? 1 : 0));
}

/*
void* ParameterDescriptor::data() {
  return getPointer(kOfxParamPropDataPtr, 0);
}

void ParameterDescriptor::data(void *d) {
  setPointer(kOfxParamPropDataPtr, 0, d);
}
*/

#ifdef OFX_API_1_2
      
std::string ParameterDescriptor::PNGIcon() {
  return getString(kOfxPropIcon, 1);
}

std::string ParameterDescriptor::SVGIcon() {
  return getString(kOfxPropIcon, 0);
}

void ParameterDescriptor::PNGIcon(const std::string &resPath) {
  setString(kOfxPropIcon, 1, resPath);
}

void ParameterDescriptor::SVGIcon(const std::string &resPath) {
  setString(kOfxPropIcon, 0, resPath);
}

#endif


// ---

ValueParameterDescriptor::ValueParameterDescriptor()
  : ParameterDescriptor() {
}

ValueParameterDescriptor::ValueParameterDescriptor(Host *h, OfxPropertySetHandle hdl)
  : ParameterDescriptor(h, hdl) {
}

ValueParameterDescriptor::ValueParameterDescriptor(const ValueParameterDescriptor &rhs)
  : ParameterDescriptor(rhs) {
}

ValueParameterDescriptor::~ValueParameterDescriptor() {
}

ValueParameterDescriptor& ValueParameterDescriptor::operator=(const ValueParameterDescriptor &rhs) {
  ParameterDescriptor::operator=(rhs);
  return *this;
}

EntryPoint ValueParameterDescriptor::interact() {
  return ((EntryPoint) getPointer(kOfxParamPropInteractV1, 0));
}

void ValueParameterDescriptor::interact(EntryPoint func) {
  setPointer(kOfxParamPropInteractV1, 0, (void*)func);
}

/*
void ValueParameterDescriptor::interactSize(double &w, double &h) {
  w = getDouble(kOfxParamPropInteractSize, 0);
  h = getDouble(kOfxParamPropInteractSize, 1);
}

void ValueParameterDescriptor::interactSize(double w, double h) {
  setDouble(kOfxParamPropInteractSize, 0, w);
  setDouble(kOfxParamPropInteractSize, 1, h);
}
*/

double ValueParameterDescriptor::interactSizeAspect() {
  return getDouble(kOfxParamPropInteractSizeAspect, 0);
}

void ValueParameterDescriptor::interactSizeAspect(double a) {
  setDouble(kOfxParamPropInteractSizeAspect, 0, a);
}

void ValueParameterDescriptor::interactMinimumSize(int *w, int *h) {
  *w = getInt(kOfxParamPropInteractMinimumSize, 0);
  *h = getInt(kOfxParamPropInteractMinimumSize, 1);
}

void ValueParameterDescriptor::interactMinimumSize(int w, int h) {
  setInt(kOfxParamPropInteractMinimumSize, 0, w);
  setInt(kOfxParamPropInteractMinimumSize, 1, h);
}

void ValueParameterDescriptor::interactPreferedSize(int *w, int *h) {
  *w = getInt(kOfxParamPropInteractPreferedSize, 0);
  *h = getInt(kOfxParamPropInteractPreferedSize, 1);
}

void ValueParameterDescriptor::interactPreferedSize(int w, int h) {
  setInt(kOfxParamPropInteractPreferedSize, 0, w);
  setInt(kOfxParamPropInteractPreferedSize, 1, h);
}

bool ValueParameterDescriptor::animates() {
  return (getInt(kOfxParamPropAnimates, 0) == 1);
}

void ValueParameterDescriptor::animates(bool yes) {
  setInt(kOfxParamPropAnimates, 0, (yes ? 1 : 0));
}

/*
bool ValueParameterDescriptor::animating() {
  return (getInt(kOfxParamPropIsAnimating, 0) == 1);
}

void ValueParameterDescriptor::animating(bool yes) {
  setInt(kOfxParamPropIsAnimating, 0, (yes ? 1 : 0));
}

bool ValueParameterDescriptor::autoKeying() {
  return (getInt(kOfxParamPropIsAutoKeying, 0) == 1);
}

void ValueParameterDescriptor::autoKeying(bool yes) {
  setInt(kOfxParamPropIsAutoKeying, 0, (yes ? 1 : 0));
}
*/

bool ValueParameterDescriptor::persistant() {
  return (getInt(kOfxParamPropPersistant, 0) == 1);
}

void ValueParameterDescriptor::persistant(bool yes) {
  setInt(kOfxParamPropPersistant, 0, (yes ? 1 : 0));
}

bool ValueParameterDescriptor::evaluateOnChange() {
  return (getInt(kOfxParamPropEvaluateOnChange, 0) == 1);
}

void ValueParameterDescriptor::evaluateOnChange(bool yes) {
  setInt(kOfxParamPropEvaluateOnChange, 0, (yes ? 1 : 0));
}

bool ValueParameterDescriptor::pluginMayWrite() {
  return (getInt(kOfxParamPropPluginMayWrite, 0) == 1);
}
void ValueParameterDescriptor::pluginMayWrite(bool yes) {
  setInt(kOfxParamPropPluginMayWrite, 0, (yes ? 1 : 0));
}

ParamInvalidate ValueParameterDescriptor::cacheInvalidation() {
  return StringToParamInvalidate(getString(kOfxParamPropCacheInvalidation, 0));
}

void ValueParameterDescriptor::cacheInvalidation(ParamInvalidate i) {
  setString(kOfxParamPropCacheInvalidation, 0, ParamInvalidateToString(i));
}

#ifdef OFX_API_1_2

bool ValueParameterDescriptor::hasHostOverlayHandle() {
  return (getInt(kOfxParamPropHasHostOverlayHandle, 0) != 0);
}

bool ValueParameterDescriptor::useHostOverlayHandle() {
  return (getInt(kOfxParamPropUseHostOverlayHandle, 0) != 0);
}

void ValueParameterDescriptor::useHostOverlayHandle(bool v) {
  setInt(kOfxParamPropUseHostOverlayHandle, 0, (v ? 1 : 0));
}

#endif

// ---

Parameter::Parameter()
  : mHandle(0), mSuite(0) {
}

Parameter::Parameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : mHandle(hdl) {
  if (!h) {
    throw BadHandleError("ofx::Parameter::Parameter: invalid host");
  }
  mSuite = h->parameterSuite();
  OfxPropertySetHandle hProps;
  mSuite->paramGetPropertySet(mHandle, &hProps);
  mProps = PropertySet(h, hProps);
}

Parameter::Parameter(const Parameter &rhs)
  : mHandle(rhs.mHandle), mProps(rhs.mProps), mSuite(rhs.mSuite) {
  
}

Parameter::~Parameter() {
}

Parameter& Parameter::operator=(const Parameter &rhs) {
  mHandle = rhs.mHandle;
  mProps = rhs.mProps;
  mSuite = rhs.mSuite;
  return *this;
}

std::string Parameter::name() {
  return mProps.getString(kOfxPropName, 0);
}

std::string Parameter::label() {
  return mProps.getString(kOfxPropLabel, 0);
}

void Parameter::label(const std::string &lbl) {
  mProps.setString(kOfxPropLabel, 0, lbl);
}

std::string Parameter::shortLabel() {
  return mProps.getString(kOfxPropShortLabel, 0);
}

void Parameter::shortLabel(const std::string &lbl) {
  mProps.setString(kOfxPropShortLabel, 0, lbl);
}

std::string Parameter::longLabel() {
  return mProps.getString(kOfxPropLongLabel, 0);
}

void Parameter::longLabel(const std::string &lbl) {
  mProps.setString(kOfxPropLongLabel, 0, lbl);
}

ParamType Parameter::type() {
  return StringToParamType(mProps.getString(kOfxParamPropType, 0));
}

bool Parameter::secret() {
  return (mProps.getInt(kOfxParamPropSecret, 0) == 1);
}

void Parameter::secret(bool yes) {
  mProps.setInt(kOfxParamPropSecret, 0, (yes ? 1 : 0));
}

bool Parameter::canUndo() {
  return (mProps.getInt(kOfxParamPropCanUndo, 0) == 1);
}

std::string Parameter::hint() {
  return mProps.getString(kOfxParamPropHint, 0);
}

void Parameter::hint(const std::string &h) {
  mProps.setString(kOfxParamPropHint, 0, h);
}

std::string Parameter::scriptName() {
  return mProps.getString(kOfxParamPropScriptName, 0);
}

std::string Parameter::parent() {
  return mProps.getString(kOfxParamPropParent, 0);
}

bool Parameter::enabled() {
  return (mProps.getInt(kOfxParamPropEnabled, 0) == 1);
}

void Parameter::enabled(bool yes) {
  mProps.setInt(kOfxParamPropEnabled, 0, (yes ? 1 : 0));
}

void* Parameter::data() {
  return mProps.getPointer(kOfxParamPropDataPtr, 0);
}

void Parameter::data(void *d) {
  mProps.setPointer(kOfxParamPropDataPtr, 0, d);
}

#ifdef OFX_API_1_2
      
std::string Parameter::PNGIcon() {
  return mProps.getString(kOfxPropIcon, 1);
}

std::string Parameter::SVGIcon() {
  return mProps.getString(kOfxPropIcon, 0);
}

#endif

// ---

ValueParameter::ValueParameter()
  : Parameter() {
}

ValueParameter::ValueParameter(Host *h, OfxParamHandle hdl)
  : Parameter(h, hdl) {
}

ValueParameter::ValueParameter(const ValueParameter &rhs)
  : Parameter(rhs) {
}

ValueParameter::~ValueParameter() {
}

ValueParameter& ValueParameter::operator=(const ValueParameter &rhs) {
  Parameter::operator=(rhs);
  return *this;
}

EntryPoint ValueParameter::interact() {
  return ((EntryPoint) mProps.getPointer(kOfxParamPropInteractV1, 0));
}

void ValueParameter::interactSize(double *w, double *h) {
  *w = mProps.getDouble(kOfxParamPropInteractSize, 0);
  *h = mProps.getDouble(kOfxParamPropInteractSize, 1);
}

double ValueParameter::interactSizeAspect() {
  return mProps.getDouble(kOfxParamPropInteractSizeAspect, 0);
}

void ValueParameter::interactMinimumSize(int *w, int *h) {
  *w = mProps.getInt(kOfxParamPropInteractMinimumSize, 0);
  *h = mProps.getInt(kOfxParamPropInteractMinimumSize, 1);
}

void ValueParameter::interactPreferedSize(int *w, int *h) {
  *w = mProps.getInt(kOfxParamPropInteractPreferedSize, 0);
  *h = mProps.getInt(kOfxParamPropInteractPreferedSize, 1);
}

bool ValueParameter::animates() {
  return (mProps.getInt(kOfxParamPropAnimates, 0) == 1);
}

bool ValueParameter::animating() {
  return (mProps.getInt(kOfxParamPropIsAnimating, 0) == 1);
}

bool ValueParameter::autoKeying() {
  return (mProps.getInt(kOfxParamPropIsAutoKeying, 0) == 1);
}

bool ValueParameter::persistant() {
  return (mProps.getInt(kOfxParamPropPersistant, 0) == 1);
}

bool ValueParameter::evaluateOnChange() {
  return (mProps.getInt(kOfxParamPropEvaluateOnChange, 0) == 1);
}

bool ValueParameter::pluginMayWrite() {
  return (mProps.getInt(kOfxParamPropPluginMayWrite, 0) == 1);
}

ParamInvalidate ValueParameter::cacheInvalidation() {
  return StringToParamInvalidate(mProps.getString(kOfxParamPropCacheInvalidation, 0));
}

#ifdef OFX_API_1_2

bool ValueParameter::useHostOverlayHandle() {
  return (mProps.getInt(kOfxParamPropUseHostOverlayHandle, 0) != 0);
}

#endif

unsigned int ValueParameter::getNumKeys() throw(Exception) {
  unsigned int nkeys = 0;
  OfxStatus stat = mSuite->paramGetNumKeys(mHandle, &nkeys);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ValueParameter::getNumKeys");
  }
  return nkeys;
}

Time ValueParameter::getKeyTime(unsigned int nth) throw(Exception) {
  Time t;
  OfxStatus stat = mSuite->paramGetKeyTime(mHandle, nth, &t);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ValueParameter::getKeyTime");
  }
  return t;
}

int ValueParameter::getKeyIndex(Time t, KeyDirection kd) throw(Exception) {
  int idx;
  OfxStatus stat = mSuite->paramGetKeyIndex(mHandle, t, (int)kd, &idx);
  if (stat == kOfxStatFailed) {
    return -1;
  } else if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ValueParameter::getKeyTime");
  }
  return idx;
}

bool ValueParameter::deleteKey(Time t) throw(Exception) {
  OfxStatus stat = mSuite->paramDeleteKey(mHandle, t);
  if (stat == kOfxStatErrBadIndex) {
    return false;
  } else if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ValueParameter::deleteKey");
  }
  return true;
}

void ValueParameter::deleteAllKeys() throw(Exception) {
  OfxStatus stat = mSuite->paramDeleteAllKeys(mHandle);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ValueParameter::deleteAllKeys");
  }
}

void ValueParameter::copy(ValueParameter &from, Time offset, FrameRange *range) throw(Exception) {
  OfxStatus stat;
  if (range != 0) {
    OfxRangeD frameRange;
    frameRange.min = range->min;
    frameRange.max = range->max;
    stat = mSuite->paramCopy(handle(), from.handle(), offset, &frameRange);
  } else {
    stat = mSuite->paramCopy(handle(), from.handle(), offset, NULL);
  }
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ValueParameter::copy");
  }
}

}
