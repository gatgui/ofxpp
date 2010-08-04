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

std::string ParameterDescriptor::getName() {
  return getString(kOfxPropName, 0);
}

void ParameterDescriptor::setName(const std::string &name) {
  setString(kOfxPropName, 0, name);
}

std::string ParameterDescriptor::getLabel() {
  return getString(kOfxPropLabel, 0);
}

void ParameterDescriptor::setLabel(const std::string &lbl) {
  setString(kOfxPropLabel, 0, lbl);
}

std::string ParameterDescriptor::getShortLabel() {
  return getString(kOfxPropShortLabel, 0);
}

void ParameterDescriptor::setShortLabel(const std::string &lbl) {
  setString(kOfxPropShortLabel, 0, lbl);
}

std::string ParameterDescriptor::getLongLabel() {
  return getString(kOfxPropLongLabel, 0);
}

void ParameterDescriptor::setLongLabel(const std::string &lbl) {
  setString(kOfxPropLongLabel, 0, lbl);
}

ParamType ParameterDescriptor::getType() {
  return StringToParamType(getString(kOfxParamPropType, 0));
}

bool ParameterDescriptor::isSecret() {
  return (getInt(kOfxParamPropSecret, 0) == 1);
}

void ParameterDescriptor::setSecret(bool yes) {
  setInt(kOfxParamPropSecret, 0, (yes ? 1 : 0));
}

bool ParameterDescriptor::canUndo() {
  return (getInt(kOfxParamPropCanUndo, 0) == 1);
}

void ParameterDescriptor::setCanUndo(bool yes) {
  setInt(kOfxParamPropCanUndo, 0, (yes ? 1 : 0));
}

std::string ParameterDescriptor::getHint() {
  return getString(kOfxParamPropHint, 0);
}

void ParameterDescriptor::setHint(const std::string &h) {
  setString(kOfxParamPropHint, 0, h);
}

std::string ParameterDescriptor::getScriptName() {
  return getString(kOfxParamPropScriptName, 0);
}

void ParameterDescriptor::setScriptName(const std::string &h) {
  setString(kOfxParamPropScriptName, 0, h);
}

std::string ParameterDescriptor::getParent() {
  return getString(kOfxParamPropParent, 0);
}

void ParameterDescriptor::setParent(const std::string &n) {
  setString(kOfxParamPropParent, 0, n);
}

bool ParameterDescriptor::isEnable() {
  return (getInt(kOfxParamPropEnabled, 0) == 1);
}

void ParameterDescriptor::enable(bool yes) {
  setInt(kOfxParamPropEnabled, 0, (yes ? 1 : 0));
}

void* ParameterDescriptor::getData() {
  return getPointer(kOfxParamPropDataPtr, 0);
}

void ParameterDescriptor::setData(void *d) {
  setPointer(kOfxParamPropDataPtr, 0, d);
}

#ifdef OFX_API_1_2
      
std::string ParameterDescriptor::getPNGIcon() {
  return getString(kOfxPropIcon, 1);
}

std::string ParameterDescriptor::getSVGIcon() {
  return getString(kOfxPropIcon, 0);
}

void ParameterDescriptor::setPNGIcon(const std::string &resPath) {
  setString(kOfxPropIcon, 1, resPath);
}

void ParameterDescriptor::setSVGIcon(const std::string &resPath) {
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

EntryPoint ValueParameterDescriptor::getInteract() {
  return ((EntryPoint) getPointer(kOfxParamPropInteractV1, 0));
}

void ValueParameterDescriptor::setInteract(EntryPoint func) {
  setPointer(kOfxParamPropInteractV1, 0, (void*)func);
}

void ValueParameterDescriptor::getInteractSize(double &w, double &h) {
  w = getDouble(kOfxParamPropInteractSize, 0);
  h = getDouble(kOfxParamPropInteractSize, 1);
}

void ValueParameterDescriptor::setInteractSize(double w, double h) {
  setDouble(kOfxParamPropInteractSize, 0, w);
  setDouble(kOfxParamPropInteractSize, 1, h);
}

double ValueParameterDescriptor::getInteractSizeAspect() {
  return getDouble(kOfxParamPropInteractSizeAspect, 0);
}

void ValueParameterDescriptor::setInteractSizeAspect(double a) {
  setDouble(kOfxParamPropInteractSizeAspect, 0, a);
}

void ValueParameterDescriptor::getInteractMinSize(int &w, int &h) {
  w = getInt(kOfxParamPropInteractMinimumSize, 0);
  h = getInt(kOfxParamPropInteractMinimumSize, 1);
}

void ValueParameterDescriptor::setInteractMinSize(int w, int h) {
  setInt(kOfxParamPropInteractMinimumSize, 0, w);
  setInt(kOfxParamPropInteractMinimumSize, 1, h);
}

void ValueParameterDescriptor::getInteractPreferedSize(int &w, int &h) {
  w = getInt(kOfxParamPropInteractPreferedSize, 0);
  h = getInt(kOfxParamPropInteractPreferedSize, 1);
}

void ValueParameterDescriptor::setInteractPreferedSize(int w, int h) {
  setInt(kOfxParamPropInteractPreferedSize, 0, w);
  setInt(kOfxParamPropInteractPreferedSize, 1, h);
}

bool ValueParameterDescriptor::isAnimateable() {
  return (getInt(kOfxParamPropAnimates, 0) == 1);
}

void ValueParameterDescriptor::setAnimateable(bool yes) {
  setInt(kOfxParamPropAnimates, 0, (yes ? 1 : 0));
}

bool ValueParameterDescriptor::isAnimating() {
  return (getInt(kOfxParamPropIsAnimating, 0) == 1);
}

void ValueParameterDescriptor::setAnimating(bool yes) {
  setInt(kOfxParamPropIsAnimating, 0, (yes ? 1 : 0));
}

bool ValueParameterDescriptor::isAutoKeying() {
  return (getInt(kOfxParamPropIsAutoKeying, 0) == 1);
}

void ValueParameterDescriptor::setAutoKeying(bool yes) {
  setInt(kOfxParamPropIsAutoKeying, 0, (yes ? 1 : 0));
}

bool ValueParameterDescriptor::isPersistant() {
  return (getInt(kOfxParamPropPersistant, 0) == 1);
}

void ValueParameterDescriptor::setPersistant(bool yes) {
  setInt(kOfxParamPropPersistant, 0, (yes ? 1 : 0));
}

bool ValueParameterDescriptor::evaluateOnChange() {
  return (getInt(kOfxParamPropEvaluateOnChange, 0) == 1);
}

void ValueParameterDescriptor::setEvaluateOnChange(bool yes) {
  setInt(kOfxParamPropEvaluateOnChange, 0, (yes ? 1 : 0));
}

bool ValueParameterDescriptor::mayPluginWrite() {
  return (getInt(kOfxParamPropPluginMayWrite, 0) == 1);
}
void ValueParameterDescriptor::setPluginMayWrite(bool yes) {
  setInt(kOfxParamPropPluginMayWrite, 0, (yes ? 1 : 0));
}

ParamInvalidate ValueParameterDescriptor::getCacheInvalidation() {
  return StringToParamInvalidate(getString(kOfxParamPropCacheInvalidation, 0));
}

void ValueParameterDescriptor::setCacheInvalidation(ParamInvalidate i) {
  setString(kOfxParamPropCacheInvalidation, 0, ParamInvalidateToString(i));
}

#ifdef OFX_API_1_2

bool ValueParameterDescriptor::hasHostOverlayHandle() {
  return (getInt(kOfxParamPropHasHostOverlayHandle, 0) != 0);
}

bool ValueParameterDescriptor::useHostOverlayHandle() {
  return (getInt(kOfxParamPropUseHostOverlayHandle, 0) != 0);
}

void ValueParameterDescriptor::setUseHostOverlayHandle(bool v) {
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
  mSuite = h->getParameterSuite();
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

std::string Parameter::getName() {
  return mProps.getString(kOfxPropName, 0);
}

std::string Parameter::getLabel() {
  return mProps.getString(kOfxPropLabel, 0);
}

void Parameter::setLabel(const std::string &lbl) {
  mProps.setString(kOfxPropLabel, 0, lbl);
}

std::string Parameter::getShortLabel() {
  return mProps.getString(kOfxPropShortLabel, 0);
}

void Parameter::setShortLabel(const std::string &lbl) {
  mProps.setString(kOfxPropShortLabel, 0, lbl);
}

std::string Parameter::getLongLabel() {
  return mProps.getString(kOfxPropLongLabel, 0);
}

void Parameter::setLongLabel(const std::string &lbl) {
  mProps.setString(kOfxPropLongLabel, 0, lbl);
}

ParamType Parameter::getType() {
  return StringToParamType(mProps.getString(kOfxParamPropType, 0));
}

bool Parameter::isSecret() {
  return (mProps.getInt(kOfxParamPropSecret, 0) == 1);
}

void Parameter::setSecret(bool yes) {
  mProps.setInt(kOfxParamPropSecret, 0, (yes ? 1 : 0));
}

bool Parameter::canUndo() {
  return (mProps.getInt(kOfxParamPropCanUndo, 0) == 1);
}

std::string Parameter::getHint() {
  return mProps.getString(kOfxParamPropHint, 0);
}

void Parameter::setHint(const std::string &h) {
  mProps.setString(kOfxParamPropHint, 0, h);
}

std::string Parameter::getScriptName() {
  return mProps.getString(kOfxParamPropScriptName, 0);
}

std::string Parameter::getParent() {
  return mProps.getString(kOfxParamPropParent, 0);
}

bool Parameter::isEnable() {
  return (mProps.getInt(kOfxParamPropEnabled, 0) == 1);
}

void Parameter::enable(bool yes) {
  mProps.setInt(kOfxParamPropEnabled, 0, (yes ? 1 : 0));
}

void* Parameter::getData() {
  return mProps.getPointer(kOfxParamPropDataPtr, 0);
}

void Parameter::setData(void *d) {
  mProps.setPointer(kOfxParamPropDataPtr, 0, d);
}

#ifdef OFX_API_1_2
      
std::string Parameter::getPNGIcon() {
  return mProps.getString(kOfxPropIcon, 1);
}

std::string Parameter::getSVGIcon() {
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

EntryPoint ValueParameter::getInteract() {
  return ((EntryPoint) mProps.getPointer(kOfxParamPropInteractV1, 0));
}

void ValueParameter::getInteractSize(double &w, double &h) {
  w = mProps.getDouble(kOfxParamPropInteractSize, 0);
  h = mProps.getDouble(kOfxParamPropInteractSize, 1);
}

double ValueParameter::getInteractSizeAspect() {
  return mProps.getDouble(kOfxParamPropInteractSizeAspect, 0);
}

void ValueParameter::getInteractMinSize(int &w, int &h) {
  w = mProps.getInt(kOfxParamPropInteractMinimumSize, 0);
  h = mProps.getInt(kOfxParamPropInteractMinimumSize, 1);
}

void ValueParameter::getInteractPreferedSize(int &w, int &h) {
  w = mProps.getInt(kOfxParamPropInteractPreferedSize, 0);
  h = mProps.getInt(kOfxParamPropInteractPreferedSize, 1);
}

bool ValueParameter::isAnimateable() {
  return (mProps.getInt(kOfxParamPropAnimates, 0) == 1);
}

bool ValueParameter::isAnimating() {
  return (mProps.getInt(kOfxParamPropIsAnimating, 0) == 1);
}

bool ValueParameter::isAutoKeying() {
  return (mProps.getInt(kOfxParamPropIsAutoKeying, 0) == 1);
}

bool ValueParameter::isPersistant() {
  return (mProps.getInt(kOfxParamPropPersistant, 0) == 1);
}

bool ValueParameter::evaluateOnChange() {
  return (mProps.getInt(kOfxParamPropEvaluateOnChange, 0) == 1);
}

bool ValueParameter::mayPluginWrite() {
  return (mProps.getInt(kOfxParamPropPluginMayWrite, 0) == 1);
}

ParamInvalidate ValueParameter::getCacheInvalidation() {
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
    frameRange.min = range->first;
    frameRange.max = range->second;
    stat = mSuite->paramCopy(getHandle(), from.getHandle(), offset, &frameRange);
  } else {
    stat = mSuite->paramCopy(getHandle(), from.getHandle(), offset, NULL);
  }
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ValueParameter::copy");
  }
}

}
