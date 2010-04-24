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

ParameterDescriptor::ParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
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

std::string ParameterDescriptor::name() throw(Exception) {
  return getString(kOfxPropName, 0);
}

void ParameterDescriptor::setName(const std::string &name) throw(Exception) {
  setString(kOfxPropName, 0, name);
}

std::string ParameterDescriptor::label() throw(Exception) {
  return getString(kOfxPropLabel, 0);
}

void ParameterDescriptor::setLabel(const std::string &lbl) throw(Exception) {
  setString(kOfxPropLabel, 0, lbl);
}

std::string ParameterDescriptor::shortLabel() throw(Exception) {
  return getString(kOfxPropShortLabel, 0);
}

void ParameterDescriptor::setShortLabel(const std::string &lbl) throw(Exception) {
  setString(kOfxPropShortLabel, 0, lbl);
}

std::string ParameterDescriptor::longLabel() throw(Exception) {
  return getString(kOfxPropLongLabel, 0);
}

void ParameterDescriptor::setLongLabel(const std::string &lbl) throw(Exception) {
  setString(kOfxPropLongLabel, 0, lbl);
}

ParamType ParameterDescriptor::type() throw(Exception) {
  return StringToParamType(getString(kOfxParamPropType, 0));
}

bool ParameterDescriptor::isSecret() throw(Exception) {
  return (getInt(kOfxParamPropSecret, 0) == 1);
}

void ParameterDescriptor::setSecret(bool yes) throw(Exception) {
  setInt(kOfxParamPropSecret, 0, (yes ? 1 : 0));
}

bool ParameterDescriptor::canUndo() throw(Exception) {
  return (getInt(kOfxParamPropCanUndo, 0) == 1);
}

void ParameterDescriptor::setCanUndo(bool yes) throw(Exception) {
  setInt(kOfxParamPropCanUndo, 0, (yes ? 1 : 0));
}

std::string ParameterDescriptor::hint() throw(Exception) {
  return getString(kOfxParamPropHint, 0);
}

void ParameterDescriptor::setHint(const std::string &h) throw(Exception) {
  setString(kOfxParamPropHint, 0, h);
}

std::string ParameterDescriptor::scriptName() throw(Exception) {
  return getString(kOfxParamPropScriptName, 0);
}

void ParameterDescriptor::setScriptName(const std::string &h) throw(Exception) {
  setString(kOfxParamPropScriptName, 0, h);
}

std::string ParameterDescriptor::parent() throw(Exception) {
  return getString(kOfxParamPropParent, 0);
}

void ParameterDescriptor::setParent(const std::string &n) throw(Exception) {
  setString(kOfxParamPropParent, 0, n);
}

bool ParameterDescriptor::isEnable() throw(Exception) {
  return (getInt(kOfxParamPropEnabled, 0) == 1);
}

void ParameterDescriptor::enable(bool yes) throw(Exception) {
  setInt(kOfxParamPropEnabled, 0, (yes ? 1 : 0));
}

void* ParameterDescriptor::data() throw(Exception) {
  return getPointer(kOfxParamPropDataPtr, 0);
}

void ParameterDescriptor::setData(void *d) throw(Exception) {
  setPointer(kOfxParamPropDataPtr, 0, d);
}

// ---

ValueParameterDescriptor::ValueParameterDescriptor()
  : ParameterDescriptor() {
}

ValueParameterDescriptor::ValueParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
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

EntryPoint ValueParameterDescriptor::interact() throw(Exception) {
  return ((EntryPoint) getPointer(kOfxParamPropInteractV1, 0));
}

void ValueParameterDescriptor::setInteract(EntryPoint func) throw(Exception) {
  setPointer(kOfxParamPropInteractV1, 0, (void*)func);
}

void ValueParameterDescriptor::interactSize(double &w, double &h) throw(Exception) {
  w = getDouble(kOfxParamPropInteractSize, 0);
  h = getDouble(kOfxParamPropInteractSize, 1);
}

void ValueParameterDescriptor::setInteractSize(double w, double h) throw(Exception) {
  setDouble(kOfxParamPropInteractSize, 0, w);
  setDouble(kOfxParamPropInteractSize, 1, h);
}

double ValueParameterDescriptor::interactSizeAspect() throw(Exception) {
  return getDouble(kOfxParamPropInteractSizeAspect, 0);
}

void ValueParameterDescriptor::setInteractSizeAspect(double a) throw(Exception) {
  setDouble(kOfxParamPropInteractSizeAspect, 0, a);
}

void ValueParameterDescriptor::interactMinimumSize(int &w, int &h) throw(Exception) {
  w = getInt(kOfxParamPropInteractMinimumSize, 0);
  h = getInt(kOfxParamPropInteractMinimumSize, 1);
}

void ValueParameterDescriptor::setMinimumInteractSize(int w, int h) throw(Exception) {
  setInt(kOfxParamPropInteractMinimumSize, 0, w);
  setInt(kOfxParamPropInteractMinimumSize, 1, h);
}

void ValueParameterDescriptor::interactPreferedSize(int &w, int &h) throw(Exception) {
  w = getInt(kOfxParamPropInteractPreferedSize, 0);
  h = getInt(kOfxParamPropInteractPreferedSize, 1);
}

void ValueParameterDescriptor::setInteractPreferedSize(int w, int h) throw(Exception) {
  setInt(kOfxParamPropInteractPreferedSize, 0, w);
  setInt(kOfxParamPropInteractPreferedSize, 1, h);
}

bool ValueParameterDescriptor::isAnimateable() throw(Exception) {
  return (getInt(kOfxParamPropAnimates, 0) == 1);
}

void ValueParameterDescriptor::setAnimateable(bool yes) throw(Exception) {
  setInt(kOfxParamPropAnimates, 0, (yes ? 1 : 0));
}

bool ValueParameterDescriptor::isAnimating() throw(Exception) {
  return (getInt(kOfxParamPropIsAnimating, 0) == 1);
}

void ValueParameterDescriptor::setAnimating(bool yes) throw(Exception) {
  setInt(kOfxParamPropIsAnimating, 0, (yes ? 1 : 0));
}

bool ValueParameterDescriptor::isAutoKeying() throw(Exception) {
  return (getInt(kOfxParamPropIsAutoKeying, 0) == 1);
}

void ValueParameterDescriptor::setAutoKeying(bool yes) throw(Exception) {
  setInt(kOfxParamPropIsAutoKeying, 0, (yes ? 1 : 0));
}

bool ValueParameterDescriptor::isPersistant() throw(Exception) {
  return (getInt(kOfxParamPropPersistant, 0) == 1);
}

void ValueParameterDescriptor::setPersistant(bool yes) throw(Exception) {
  setInt(kOfxParamPropPersistant, 0, (yes ? 1 : 0));
}

bool ValueParameterDescriptor::evaluateOnChange() throw(Exception) {
  return (getInt(kOfxParamPropEvaluateOnChange, 0) == 1);
}

void ValueParameterDescriptor::setEvaluateOnChange(bool yes) throw(Exception) {
  setInt(kOfxParamPropEvaluateOnChange, 0, (yes ? 1 : 0));
}

bool ValueParameterDescriptor::pluginMayWrite() throw(Exception) {
  return (getInt(kOfxParamPropPluginMayWrite, 0) == 1);
}
void ValueParameterDescriptor::setPluginMayWrite(bool yes) throw(Exception) {
  setInt(kOfxParamPropPluginMayWrite, 0, (yes ? 1 : 0));
}

ParamInvalidate ValueParameterDescriptor::cacheInvalidation() throw(Exception) {
  return StringToParamInvalidate(getString(kOfxParamPropCacheInvalidation, 0));
}

void ValueParameterDescriptor::setCacheInvalidation(ParamInvalidate i) throw(Exception) {
  setString(kOfxParamPropCacheInvalidation, 0, ParamInvalidateToString(i));
}

// --

IntParameterDescriptor::IntParameterDescriptor()
  : ValueParameterDescriptor() {
}

IntParameterDescriptor::IntParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
  : ValueParameterDescriptor(h, hdl) {
}

IntParameterDescriptor::IntParameterDescriptor(const IntParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

IntParameterDescriptor::~IntParameterDescriptor() {
}

IntParameterDescriptor& IntParameterDescriptor::operator=(const IntParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

int IntParameterDescriptor::getDefault() throw(Exception) {
  return getInt(kOfxParamPropDefault, 0);
}

void IntParameterDescriptor::setDefault(int v0) throw(Exception) {
  setInt(kOfxParamPropDefault, 0, v0);
}

int IntParameterDescriptor::getMin() throw(Exception) {
  return getInt(kOfxParamPropMin, 0);
}

void IntParameterDescriptor::setMin(int v) throw(Exception) {
  setInt(kOfxParamPropMin, 0, v);
}

int IntParameterDescriptor::getMax() throw(Exception) {
  return getInt(kOfxParamPropMax, 0);
}

void IntParameterDescriptor::setMax(int v) throw(Exception) {
  setInt(kOfxParamPropMax, 0, v);
}

int IntParameterDescriptor::getDisplayMin() throw(Exception) {
  return getInt(kOfxParamPropDisplayMin, 0);
}

void IntParameterDescriptor::setDisplayMin(int v) throw(Exception) {
  setInt(kOfxParamPropDisplayMin, 0, v);
}

int IntParameterDescriptor::getDisplayMax() throw(Exception) {
  return getInt(kOfxParamPropDisplayMax, 0);
}

void IntParameterDescriptor::setDisplayMax(int v) throw(Exception) {
  setInt(kOfxParamPropDisplayMax, 0, v);
}

// --

Int2ParameterDescriptor::Int2ParameterDescriptor()
  : ValueParameterDescriptor() {
}

Int2ParameterDescriptor::Int2ParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
  : ValueParameterDescriptor(h, hdl) {
}

Int2ParameterDescriptor::Int2ParameterDescriptor(const Int2ParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

Int2ParameterDescriptor::~Int2ParameterDescriptor() {
}

Int2ParameterDescriptor& Int2ParameterDescriptor::operator=(const Int2ParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

void Int2ParameterDescriptor::getDefault(int &v0, int &v1) throw(Exception) {
  v0 = getInt(kOfxParamPropDefault, 0);
  v1 = getInt(kOfxParamPropDefault, 1);
}

void Int2ParameterDescriptor::setDefault(int v0, int v1) throw(Exception) {
  setInt(kOfxParamPropDefault, 0, v0);
  setInt(kOfxParamPropDefault, 1, v1);
}

void Int2ParameterDescriptor::getMin(int &v0, int &v1) throw(Exception) {
  v0 = getInt(kOfxParamPropMin, 0);
  v1 = getInt(kOfxParamPropMin, 1);
}

void Int2ParameterDescriptor::setMin(int v0, int v1) throw(Exception) {
  setInt(kOfxParamPropMin, 0, v0);
  setInt(kOfxParamPropMin, 1, v1);
}

void Int2ParameterDescriptor::getMax(int &v0, int &v1) throw(Exception) {
  v0 = getInt(kOfxParamPropMax, 0);
  v1 = getInt(kOfxParamPropMax, 1);
}

void Int2ParameterDescriptor::setMax(int v0, int v1) throw(Exception) {
  setInt(kOfxParamPropMax, 0, v0);
  setInt(kOfxParamPropMax, 1, v1);
}

void Int2ParameterDescriptor::getDisplayMin(int &v0, int &v1) throw(Exception) {
  v0 = getInt(kOfxParamPropDisplayMin, 0);
  v1 = getInt(kOfxParamPropDisplayMin, 1);
}

void Int2ParameterDescriptor::setDisplayMin(int v0, int v1) throw(Exception) {
  setInt(kOfxParamPropDisplayMin, 0, v0);
  setInt(kOfxParamPropDisplayMin, 1, v1);
}

void Int2ParameterDescriptor::getDisplayMax(int &v0, int &v1) throw(Exception) {
  v0 = getInt(kOfxParamPropDisplayMax, 0);
  v1 = getInt(kOfxParamPropDisplayMax, 1);
}

void Int2ParameterDescriptor::setDisplayMax(int v0, int v1) throw(Exception) {
  setInt(kOfxParamPropDisplayMax, 0, v0);
  setInt(kOfxParamPropDisplayMax, 1, v1);
}

void Int2ParameterDescriptor::setDimensionLabel(int i, const std::string &l) throw(Exception) {
  setString(kOfxParamPropDimensionLabel, i, l);
}

std::string Int2ParameterDescriptor::getDimensionLabel(int i) throw(Exception) {
  return getString(kOfxParamPropDimensionLabel, i);
}

// ---

Int3ParameterDescriptor::Int3ParameterDescriptor()
  : ValueParameterDescriptor() {
}

Int3ParameterDescriptor::Int3ParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
  : ValueParameterDescriptor(h, hdl) {
}

Int3ParameterDescriptor::Int3ParameterDescriptor(const Int3ParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

Int3ParameterDescriptor::~Int3ParameterDescriptor() {
}

Int3ParameterDescriptor& Int3ParameterDescriptor::operator=(const Int3ParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

void Int3ParameterDescriptor::getDefault(int &v0, int &v1, int &v2) throw(Exception) {
  v0 = getInt(kOfxParamPropDefault, 0);
  v1 = getInt(kOfxParamPropDefault, 1);
  v2 = getInt(kOfxParamPropDefault, 2);
}

void Int3ParameterDescriptor::setDefault(int v0, int v1, int v2) throw(Exception) {
  setInt(kOfxParamPropDefault, 0, v0);
  setInt(kOfxParamPropDefault, 1, v1);
  setInt(kOfxParamPropDefault, 2, v2);
}

void Int3ParameterDescriptor::getMin(int &v0, int &v1, int &v2) throw(Exception) {
  v0 = getInt(kOfxParamPropMin, 0);
  v1 = getInt(kOfxParamPropMin, 1);
  v2 = getInt(kOfxParamPropMin, 2);
}

void Int3ParameterDescriptor::setMin(int v0, int v1, int v2) throw(Exception) {
  setInt(kOfxParamPropMin, 0, v0);
  setInt(kOfxParamPropMin, 1, v1);
  setInt(kOfxParamPropMin, 2, v2);
}

void Int3ParameterDescriptor::getMax(int &v0, int &v1, int &v2) throw(Exception) {
  v0 = getInt(kOfxParamPropMax, 0);
  v1 = getInt(kOfxParamPropMax, 1);
  v2 = getInt(kOfxParamPropMax, 2);
}

void Int3ParameterDescriptor::setMax(int v0, int v1, int v2) throw(Exception) {
  setInt(kOfxParamPropMax, 0, v0);
  setInt(kOfxParamPropMax, 1, v1);
  setInt(kOfxParamPropMax, 2, v2);
}

void Int3ParameterDescriptor::getDisplayMin(int &v0, int &v1, int &v2) throw(Exception) {
  v0 = getInt(kOfxParamPropDisplayMin, 0);
  v1 = getInt(kOfxParamPropDisplayMin, 1);
  v2 = getInt(kOfxParamPropDisplayMin, 2);
}

void Int3ParameterDescriptor::setDisplayMin(int v0, int v1, int v2) throw(Exception) {
  setInt(kOfxParamPropDisplayMin, 0, v0);
  setInt(kOfxParamPropDisplayMin, 1, v1);
  setInt(kOfxParamPropDisplayMin, 2, v2);
}

void Int3ParameterDescriptor::getDisplayMax(int &v0, int &v1, int &v2) throw(Exception) {
  v0 = getInt(kOfxParamPropDisplayMax, 0);
  v1 = getInt(kOfxParamPropDisplayMax, 1);
  v2 = getInt(kOfxParamPropDisplayMax, 2);
}

void Int3ParameterDescriptor::setDisplayMax(int v0, int v1, int v2) throw(Exception) {
  setInt(kOfxParamPropDisplayMax, 0, v0);
  setInt(kOfxParamPropDisplayMax, 1, v1);
  setInt(kOfxParamPropDisplayMax, 2, v2);
}

void Int3ParameterDescriptor::setDimensionLabel(int i, const std::string &l) throw(Exception) {
  setString(kOfxParamPropDimensionLabel, i, l);
}

std::string Int3ParameterDescriptor::getDimensionLabel(int i) throw(Exception) {
  return getString(kOfxParamPropDimensionLabel, i);
}

// ---

DoubleParameterDescriptor::DoubleParameterDescriptor()
  : ValueParameterDescriptor() {
}

DoubleParameterDescriptor::DoubleParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
  : ValueParameterDescriptor(h, hdl) {
}

DoubleParameterDescriptor::DoubleParameterDescriptor(const DoubleParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

DoubleParameterDescriptor::~DoubleParameterDescriptor() {
}

DoubleParameterDescriptor& DoubleParameterDescriptor::operator=(const DoubleParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

double DoubleParameterDescriptor::getDefault() throw(Exception) {
  return getDouble(kOfxParamPropDefault, 0);
}

void DoubleParameterDescriptor::setDefault(double v0) throw(Exception) {
  setDouble(kOfxParamPropDefault, 0, v0);
}

double DoubleParameterDescriptor::getMin() throw(Exception) {
  return getDouble(kOfxParamPropMin, 0);
}

void DoubleParameterDescriptor::setMin(double min0) throw(Exception) {
  setDouble(kOfxParamPropMin, 0, min0);
}

double DoubleParameterDescriptor::getMax() throw(Exception) {
  return getDouble(kOfxParamPropMax, 0);
}

void DoubleParameterDescriptor::setMax(double max0) throw(Exception) {
  setDouble(kOfxParamPropMax, 0, max0);
}

double DoubleParameterDescriptor::getDisplayMin() throw(Exception) {
  return getDouble(kOfxParamPropDisplayMin, 0);
}

void DoubleParameterDescriptor::setDisplayMin(double min0) throw(Exception) {
  setDouble(kOfxParamPropDisplayMin, 0, min0);
}

double DoubleParameterDescriptor::getDisplayMax() throw(Exception) {
  return getDouble(kOfxParamPropDisplayMax, 0);
}

void DoubleParameterDescriptor::setDisplayMax(double max0) throw(Exception) {
  setDouble(kOfxParamPropDisplayMax, 0, max0);
}

double DoubleParameterDescriptor::increment() throw(Exception) {
  return getDouble(kOfxParamPropIncrement, 0);
}

void DoubleParameterDescriptor::setIncrement(double i) throw(Exception) {
  setDouble(kOfxParamPropIncrement, 0, i);
}

int DoubleParameterDescriptor::digits() throw(Exception) {
  return getInt(kOfxParamPropDigits, 0);
}

void DoubleParameterDescriptor::setDigits(int d) throw(Exception) {
  setInt(kOfxParamPropDigits, 0, d);
}

bool DoubleParameterDescriptor::showTimeMarker() throw(Exception) {
  return (getInt(kOfxParamPropShowTimeMarker, 0) == 1);
}

void DoubleParameterDescriptor::setShowTimeMarker(bool yes) throw(Exception) {
  setInt(kOfxParamPropShowTimeMarker, 0, (yes ? 1 : 0));
}

DoubleParamType DoubleParameterDescriptor::doubleType() throw(Exception) {
  return StringToDoubleParamType(getString(kOfxParamPropDoubleType, 0));
}

void DoubleParameterDescriptor::setDoubleType(DoubleParamType t) throw(Exception) {
  setString(kOfxParamPropDoubleType, 0, DoubleParamTypeToString(t));
}

// ---

Double2ParameterDescriptor::Double2ParameterDescriptor()
  : ValueParameterDescriptor() {
}

Double2ParameterDescriptor::Double2ParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
  : ValueParameterDescriptor(h, hdl) {
}

Double2ParameterDescriptor::Double2ParameterDescriptor(const Double2ParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

Double2ParameterDescriptor::~Double2ParameterDescriptor() {
}

Double2ParameterDescriptor& Double2ParameterDescriptor::operator=(const Double2ParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

void Double2ParameterDescriptor::getDefault(double &v0, double &v1) throw(Exception) {
  v0 = getDouble(kOfxParamPropDefault, 0);
  v1 = getDouble(kOfxParamPropDefault, 1);
}

void Double2ParameterDescriptor::setDefault(double v0, double v1) throw(Exception) {
  setDouble(kOfxParamPropDefault, 0, v0);
  setDouble(kOfxParamPropDefault, 1, v1);
}

void Double2ParameterDescriptor::getMin(double &v0, double &v1) throw(Exception) {
  v0 = getDouble(kOfxParamPropMin, 0);
  v1 = getDouble(kOfxParamPropMin, 1);
}

void Double2ParameterDescriptor::setMin(double min0, double min1) throw(Exception) {
  setDouble(kOfxParamPropMin, 0, min0);
  setDouble(kOfxParamPropMin, 1, min1);
}

void Double2ParameterDescriptor::getMax(double &v0, double &v1) throw(Exception) {
  v0 = getDouble(kOfxParamPropMax, 0);
  v1 = getDouble(kOfxParamPropMax, 1);
}

void Double2ParameterDescriptor::setMax(double max0, double max1) throw(Exception) {
  setDouble(kOfxParamPropMax, 0, max0);
  setDouble(kOfxParamPropMax, 1, max1);
}

void Double2ParameterDescriptor::getDisplayMin(double &v0, double &v1) throw(Exception) {
  v0 = getDouble(kOfxParamPropDisplayMin, 0);
  v1 = getDouble(kOfxParamPropDisplayMin, 1);
}

void Double2ParameterDescriptor::setDisplayMin(double min0, double min1) throw(Exception) {
  setDouble(kOfxParamPropDisplayMin, 0, min0);
  setDouble(kOfxParamPropDisplayMin, 1, min1);
}

void Double2ParameterDescriptor::getDisplayMax(double &v0, double &v1) throw(Exception) {
  v0 = getDouble(kOfxParamPropDisplayMax, 0);
  v1 = getDouble(kOfxParamPropDisplayMax, 1);
}

void Double2ParameterDescriptor::setDisplayMax(double max0, double max1) throw(Exception) {
  setDouble(kOfxParamPropDisplayMax, 0, max0);
  setDouble(kOfxParamPropDisplayMax, 1, max1);
}

double Double2ParameterDescriptor::increment() throw(Exception) {
  return getDouble(kOfxParamPropIncrement, 0);
}

void Double2ParameterDescriptor::setIncrement(double i) throw(Exception) {
  setDouble(kOfxParamPropIncrement, 0, i);
}

int Double2ParameterDescriptor::digits() throw(Exception) {
  return getInt(kOfxParamPropDigits, 0);
}

void Double2ParameterDescriptor::setDigits(int d) throw(Exception) {
  setInt(kOfxParamPropDigits, 0, d);
}

DoubleParamType Double2ParameterDescriptor::doubleType() throw(Exception) {
  return StringToDoubleParamType(getString(kOfxParamPropDoubleType, 0));
}

void Double2ParameterDescriptor::setDoubleType(DoubleParamType t) throw(Exception) {
  setString(kOfxParamPropDoubleType, 0, DoubleParamTypeToString(t));
}

void Double2ParameterDescriptor::setDimensionLabel(int i, const std::string &name) throw(Exception) {
  setString(kOfxParamPropDimensionLabel, i, name);
}

std::string Double2ParameterDescriptor::getDimensionLabel(int i) throw(Exception) {
  return getString(kOfxParamPropDimensionLabel, i);
}

// ---

Double3ParameterDescriptor::Double3ParameterDescriptor()
  : ValueParameterDescriptor() {
}

Double3ParameterDescriptor::Double3ParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
  : ValueParameterDescriptor(h, hdl) {
}

Double3ParameterDescriptor::Double3ParameterDescriptor(const Double3ParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

Double3ParameterDescriptor::~Double3ParameterDescriptor() {
}

Double3ParameterDescriptor& Double3ParameterDescriptor::operator=(const Double3ParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

void Double3ParameterDescriptor::getDefault(double &v0, double &v1, double &v2) throw(Exception) {
  v0 = getDouble(kOfxParamPropDefault, 0);
  v1 = getDouble(kOfxParamPropDefault, 1);
  v2 = getDouble(kOfxParamPropDefault, 2);
}

void Double3ParameterDescriptor::setDefault(double v0, double v1, double v2) throw(Exception) {
  setDouble(kOfxParamPropDefault, 0, v0);
  setDouble(kOfxParamPropDefault, 1, v1);
  setDouble(kOfxParamPropDefault, 2, v2);
}

void Double3ParameterDescriptor::getMin(double &v0, double &v1, double &v2) throw(Exception) {
  v0 = getDouble(kOfxParamPropMin, 0);
  v1 = getDouble(kOfxParamPropMin, 1);
  v2 = getDouble(kOfxParamPropMin, 2);
}

void Double3ParameterDescriptor::setMin(double min0, double min1, double min2) throw(Exception) {
  setDouble(kOfxParamPropMin, 0, min0);
  setDouble(kOfxParamPropMin, 1, min1);
  setDouble(kOfxParamPropMin, 2, min2);
}

void Double3ParameterDescriptor::getMax(double &v0, double &v1, double &v2) throw(Exception) {
  v0 = getDouble(kOfxParamPropMax, 0);
  v1 = getDouble(kOfxParamPropMax, 1);
  v2 = getDouble(kOfxParamPropMax, 2);
}

void Double3ParameterDescriptor::setMax(double max0, double max1, double max2) throw(Exception) {
  setDouble(kOfxParamPropMax, 0, max0);
  setDouble(kOfxParamPropMax, 1, max1);
  setDouble(kOfxParamPropMax, 2, max2);
}

void Double3ParameterDescriptor::getDisplayMin(double &v0, double &v1, double &v2) throw(Exception) {
  v0 = getDouble(kOfxParamPropDisplayMin, 0);
  v1 = getDouble(kOfxParamPropDisplayMin, 1);
  v2 = getDouble(kOfxParamPropDisplayMin, 2);
}

void Double3ParameterDescriptor::setDisplayMin(double min0, double min1, double min2) throw(Exception) {
  setDouble(kOfxParamPropDisplayMin, 0, min0);
  setDouble(kOfxParamPropDisplayMin, 1, min1);
  setDouble(kOfxParamPropDisplayMin, 2, min2);
}

void Double3ParameterDescriptor::getDisplayMax(double &v0, double &v1, double &v2) throw(Exception) {
  v0 = getDouble(kOfxParamPropDisplayMax, 0);
  v1 = getDouble(kOfxParamPropDisplayMax, 1);
  v2 = getDouble(kOfxParamPropDisplayMax, 2);
}

void Double3ParameterDescriptor::setDisplayMax(double max0, double max1, double max2) throw(Exception) {
  setDouble(kOfxParamPropDisplayMax, 0, max0);
  setDouble(kOfxParamPropDisplayMax, 1, max1);
  setDouble(kOfxParamPropDisplayMax, 2, max2);
}

double Double3ParameterDescriptor::increment() throw(Exception) {
  return getDouble(kOfxParamPropIncrement, 0);
}

void Double3ParameterDescriptor::setIncrement(double i) throw(Exception) {
  setDouble(kOfxParamPropIncrement, 0, i);
}

int Double3ParameterDescriptor::digits() throw(Exception) {
  return getInt(kOfxParamPropDigits, 0);
}

void Double3ParameterDescriptor::setDigits(int d) throw(Exception) {
  setInt(kOfxParamPropDigits, 0, d);
}

DoubleParamType Double3ParameterDescriptor::doubleType() throw(Exception) {
  return StringToDoubleParamType(getString(kOfxParamPropDoubleType, 0));
}

void Double3ParameterDescriptor::setDoubleType(DoubleParamType t) throw(Exception) {
  setString(kOfxParamPropDoubleType, 0, DoubleParamTypeToString(t));
}

void Double3ParameterDescriptor::setDimensionLabel(int i, const std::string &name) throw(Exception) {
  setString(kOfxParamPropDimensionLabel, i, name);
}

std::string Double3ParameterDescriptor::getDimensionLabel(int i) throw(Exception) {
  return getString(kOfxParamPropDimensionLabel, i);
}

// ---

ChoiceParameterDescriptor::ChoiceParameterDescriptor()
  : ValueParameterDescriptor() {
}

ChoiceParameterDescriptor::ChoiceParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
  : ValueParameterDescriptor(h, hdl) {
}

ChoiceParameterDescriptor::ChoiceParameterDescriptor(const ChoiceParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

ChoiceParameterDescriptor::~ChoiceParameterDescriptor() {
}

ChoiceParameterDescriptor& ChoiceParameterDescriptor::operator=(const ChoiceParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

int ChoiceParameterDescriptor::getDefault() throw(Exception) {
  return getInt(kOfxParamPropDefault, 0);
}

void ChoiceParameterDescriptor::setDefault(int v) throw(Exception) {
  setInt(kOfxParamPropDefault, 0, v);
}

int ChoiceParameterDescriptor::getChoiceCount() throw(Exception) {
  return size(kOfxParamPropChoiceOption);
}

void ChoiceParameterDescriptor::setChoice(int i, const std::string &str) throw(Exception) {
  setString(kOfxParamPropChoiceOption, i, str);
}

std::string ChoiceParameterDescriptor::getChoice(int i) throw(Exception) {
  return getString(kOfxParamPropChoiceOption, i);
}

// ---

StringParameterDescriptor::StringParameterDescriptor()
  : ValueParameterDescriptor() {
}

StringParameterDescriptor::StringParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
  : ValueParameterDescriptor(h, hdl) {
  
}

StringParameterDescriptor::StringParameterDescriptor(const StringParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
  
}

StringParameterDescriptor::~StringParameterDescriptor() {
}

StringParameterDescriptor& StringParameterDescriptor::operator=(const StringParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

std::string StringParameterDescriptor::getDefault() throw(Exception) {
  return getString(kOfxParamPropDefault, 0);
}

void StringParameterDescriptor::setDefault(const std::string &v) throw(Exception) {
  setString(kOfxParamPropDefault, 0, v);
}

StringParamMode StringParameterDescriptor::mode() throw(Exception) {
  return StringToStringParamMode(getString(kOfxParamPropStringMode, 0));
}

void StringParameterDescriptor::setMode(StringParamMode m) throw(Exception) {
  setString(kOfxParamPropStringMode, 0, StringParamModeToString(m));
}

bool StringParameterDescriptor::filePathExists() throw(Exception) {
  return (getInt(kOfxParamPropStringFilePathExists, 0) == 1);
}

void StringParameterDescriptor::setFilePathExists(bool yes) throw(Exception) {
  setInt(kOfxParamPropStringFilePathExists, 0, (yes ? 1 : 0));
}

// ---

CustomParameterDescriptor::CustomParameterDescriptor()
  : ValueParameterDescriptor() {
}

CustomParameterDescriptor::CustomParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
  : ValueParameterDescriptor(h, hdl) {
}

CustomParameterDescriptor::CustomParameterDescriptor(const CustomParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

CustomParameterDescriptor::~CustomParameterDescriptor() {
}

CustomParameterDescriptor& CustomParameterDescriptor::operator=(const CustomParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

std::string CustomParameterDescriptor::getDefault() throw(Exception) {
  return getString(kOfxParamPropDefault, 0);
}

void CustomParameterDescriptor::setDefault(const std::string &v) throw(Exception) {
  setString(kOfxParamPropDefault, 0, v);
}

void* CustomParameterDescriptor::getInterpolator() throw(Exception) {
  return getPointer(kOfxParamPropCustomInterpCallbackV1, 0);
}

// ---

BooleanParameterDescriptor::BooleanParameterDescriptor()
  : ValueParameterDescriptor() {
}

BooleanParameterDescriptor::BooleanParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
  : ValueParameterDescriptor(h, hdl) {
}

BooleanParameterDescriptor::BooleanParameterDescriptor(const BooleanParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

BooleanParameterDescriptor::~BooleanParameterDescriptor() {
}

BooleanParameterDescriptor& BooleanParameterDescriptor::operator=(const BooleanParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

bool BooleanParameterDescriptor::getDefault() throw(Exception) {
  return (getInt(kOfxParamPropDefault, 0) == 1);
}

void BooleanParameterDescriptor::setDefault(bool v) throw(Exception) {
  setInt(kOfxParamPropDefault, 0, (v ? 1 : 0));
}

// ---

RGBParameterDescriptor::RGBParameterDescriptor()
  : ValueParameterDescriptor() {
}

RGBParameterDescriptor::RGBParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
  : ValueParameterDescriptor(h, hdl) {
}

RGBParameterDescriptor::RGBParameterDescriptor(const RGBParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

RGBParameterDescriptor::~RGBParameterDescriptor() {
}

RGBParameterDescriptor& RGBParameterDescriptor::operator=(const RGBParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

RGBAColour<double> RGBParameterDescriptor::getDefault() throw(Exception) {
  RGBAColour<double> rv;
  getDoubles(kOfxParamPropDefault, 3, &(rv.r));
  rv.a = 1.0;
  return rv;
}

void RGBParameterDescriptor::setDefault(const RGBAColour<double> &v) throw(Exception) {
  setDoubles(kOfxParamPropDefault, 3, (double*)&(v.r));
}

// ---

RGBAParameterDescriptor::RGBAParameterDescriptor()
  : ValueParameterDescriptor() {
}

RGBAParameterDescriptor::RGBAParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
  : ValueParameterDescriptor(h, hdl) {
}

RGBAParameterDescriptor::RGBAParameterDescriptor(const RGBAParameterDescriptor &rhs)
  : ValueParameterDescriptor(rhs) {
}

RGBAParameterDescriptor::~RGBAParameterDescriptor() {
}

RGBAParameterDescriptor& RGBAParameterDescriptor::operator=(const RGBAParameterDescriptor &rhs) {
  ValueParameterDescriptor::operator=(rhs);
  return *this;
}

RGBAColour<double> RGBAParameterDescriptor::getDefault() throw(Exception) {
  RGBAColour<double> rv;
  getDoubles(kOfxParamPropDefault, 4, &(rv.r));
  return rv;
}

void RGBAParameterDescriptor::setDefault(const RGBAColour<double> &v) throw(Exception) {
  setDoubles(kOfxParamPropDefault, 4, (double*)&(v.r));
}

// ---

PageParameterDescriptor::PageParameterDescriptor()
  : ParameterDescriptor() {
}

PageParameterDescriptor::PageParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
  : ParameterDescriptor(h, hdl) {
}

PageParameterDescriptor::PageParameterDescriptor(const PageParameterDescriptor &rhs)
  : ParameterDescriptor(rhs) {
}

PageParameterDescriptor::~PageParameterDescriptor() {
}

PageParameterDescriptor& PageParameterDescriptor::operator=(const PageParameterDescriptor &rhs) {
  ParameterDescriptor::operator=(rhs);
  return *this;
}

int PageParameterDescriptor::getChildCount() throw(Exception) {
  return size(kOfxParamPropPageChild);
}

void PageParameterDescriptor::setChild(int i, const std::string &name) throw(Exception) {
  setString(kOfxParamPropPageChild, i, name);
}

std::string PageParameterDescriptor::getChild(int i) throw(Exception) {
  return getString(kOfxParamPropPageChild, i);
}

// ---

PushButtonParameterDescriptor::PushButtonParameterDescriptor()
  : ParameterDescriptor() {
}

PushButtonParameterDescriptor::PushButtonParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception)
  : ParameterDescriptor(h, hdl) {
}

PushButtonParameterDescriptor::PushButtonParameterDescriptor(const PushButtonParameterDescriptor &rhs)
  : ParameterDescriptor(rhs) {
}

PushButtonParameterDescriptor::~PushButtonParameterDescriptor() {
}

PushButtonParameterDescriptor& PushButtonParameterDescriptor::operator=(const PushButtonParameterDescriptor &rhs) {
  ParameterDescriptor::operator=(rhs);
  return *this;
}

EntryPoint PushButtonParameterDescriptor::interact() throw(Exception) {
  return ((EntryPoint) getPointer(kOfxParamPropInteractV1, 0));
}

void PushButtonParameterDescriptor::setInteract(EntryPoint func) throw(Exception) {
  setPointer(kOfxParamPropInteractV1, 0, (void*)func);
}

void PushButtonParameterDescriptor::interactSize(double &w, double &h) throw(Exception) {
  w = getDouble(kOfxParamPropInteractSize, 0);
  h = getDouble(kOfxParamPropInteractSize, 1);
}

void PushButtonParameterDescriptor::setInteractSize(double w, double h) throw(Exception) {
  setDouble(kOfxParamPropInteractSize, 0, w);
  setDouble(kOfxParamPropInteractSize, 1, h);
}

double PushButtonParameterDescriptor::interactSizeAspect() throw(Exception) {
  return getDouble(kOfxParamPropInteractSizeAspect, 0);
}

void PushButtonParameterDescriptor::setInteractSizeAspect(double a) throw(Exception) {
  setDouble(kOfxParamPropInteractSizeAspect, 0, a);
}

void PushButtonParameterDescriptor::interactMinimumSize(int &w, int &h) throw(Exception) {
  w = getInt(kOfxParamPropInteractMinimumSize, 0);
  h = getInt(kOfxParamPropInteractMinimumSize, 1);
}

void PushButtonParameterDescriptor::setMinimumInteractSize(int w, int h) throw(Exception) {
  setInt(kOfxParamPropInteractMinimumSize, 0, w);
  setInt(kOfxParamPropInteractMinimumSize, 1, h);
}

void PushButtonParameterDescriptor::interactPreferedSize(int &w, int &h) throw(Exception) {
  w = getInt(kOfxParamPropInteractPreferedSize, 0);
  h = getInt(kOfxParamPropInteractPreferedSize, 1);
}

void PushButtonParameterDescriptor::setInteractPreferedSize(int w, int h) throw(Exception) {
  setInt(kOfxParamPropInteractPreferedSize, 0, w);
  setInt(kOfxParamPropInteractPreferedSize, 1, h);
}

// ---

Parameter::Parameter()
  : mHandle(0), mSuite(0) {
}

Parameter::Parameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : mHandle(hdl) {
  if (!h) {
    throw Exception(kOfxStatErrFatal, "ofx::Parameter::Parameter: no host");
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

std::string Parameter::name() throw(Exception) {
  return mProps.getString(kOfxPropName, 0);
}

std::string Parameter::label() throw(Exception) {
  return mProps.getString(kOfxPropLabel, 0);
}

void Parameter::setLabel(const std::string &lbl) throw(Exception) {
  mProps.setString(kOfxPropLabel, 0, lbl);
}

std::string Parameter::shortLabel() throw(Exception) {
  return mProps.getString(kOfxPropShortLabel, 0);
}

void Parameter::setShortLabel(const std::string &lbl) throw(Exception) {
  mProps.setString(kOfxPropShortLabel, 0, lbl);
}

std::string Parameter::longLabel() throw(Exception) {
  return mProps.getString(kOfxPropLongLabel, 0);
}

void Parameter::setLongLabel(const std::string &lbl) throw(Exception) {
  mProps.setString(kOfxPropLongLabel, 0, lbl);
}

ParamType Parameter::type() throw(Exception) {
  return StringToParamType(mProps.getString(kOfxParamPropType, 0));
}

bool Parameter::isSecret() throw(Exception) {
  return (mProps.getInt(kOfxParamPropSecret, 0) == 1);
}

void Parameter::setSecret(bool yes) throw(Exception) {
  mProps.setInt(kOfxParamPropSecret, 0, (yes ? 1 : 0));
}

bool Parameter::canUndo() throw(Exception) {
  return (mProps.getInt(kOfxParamPropCanUndo, 0) == 1);
}

std::string Parameter::hint() throw(Exception) {
  return mProps.getString(kOfxParamPropHint, 0);
}

void Parameter::setHint(const std::string &h) throw(Exception) {
  mProps.setString(kOfxParamPropHint, 0, h);
}

std::string Parameter::scriptName() throw(Exception) {
  return mProps.getString(kOfxParamPropScriptName, 0);
}

std::string Parameter::parent() throw(Exception) {
  return mProps.getString(kOfxParamPropParent, 0);
}

bool Parameter::isEnable() throw(Exception) {
  return (mProps.getInt(kOfxParamPropEnabled, 0) == 1);
}

void Parameter::enable(bool yes) throw(Exception) {
  mProps.setInt(kOfxParamPropEnabled, 0, (yes ? 1 : 0));
}

void* Parameter::data() throw(Exception) {
  return mProps.getPointer(kOfxParamPropDataPtr, 0);
}

void Parameter::setData(void *d) throw(Exception) {
  mProps.setPointer(kOfxParamPropDataPtr, 0, d);
}

// ---

ValueParameter::ValueParameter()
  : Parameter() {
}

ValueParameter::ValueParameter(Host *h, OfxParamHandle hdl) throw(Exception)
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

EntryPoint ValueParameter::interact() throw(Exception) {
  return ((EntryPoint) mProps.getPointer(kOfxParamPropInteractV1, 0));
}

void ValueParameter::interactSize(double &w, double &h) throw(Exception) {
  w = mProps.getDouble(kOfxParamPropInteractSize, 0);
  h = mProps.getDouble(kOfxParamPropInteractSize, 1);
}

double ValueParameter::interactSizeAspect() throw(Exception) {
  return mProps.getDouble(kOfxParamPropInteractSizeAspect, 0);
}

void ValueParameter::interactMinimumSize(int &w, int &h) throw(Exception) {
  w = mProps.getInt(kOfxParamPropInteractMinimumSize, 0);
  h = mProps.getInt(kOfxParamPropInteractMinimumSize, 1);
}

void ValueParameter::interactPreferedSize(int &w, int &h) throw(Exception) {
  w = mProps.getInt(kOfxParamPropInteractPreferedSize, 0);
  h = mProps.getInt(kOfxParamPropInteractPreferedSize, 1);
}

bool ValueParameter::isAnimateable() throw(Exception) {
  return (mProps.getInt(kOfxParamPropAnimates, 0) == 1);
}

bool ValueParameter::isAnimating() throw(Exception) {
  return (mProps.getInt(kOfxParamPropIsAnimating, 0) == 1);
}

bool ValueParameter::isAutoKeying() throw(Exception) {
  return (mProps.getInt(kOfxParamPropIsAutoKeying, 0) == 1);
}

bool ValueParameter::isPersistant() throw(Exception) {
  return (mProps.getInt(kOfxParamPropPersistant, 0) == 1);
}

bool ValueParameter::evaluateOnChange() throw(Exception) {
  return (mProps.getInt(kOfxParamPropEvaluateOnChange, 0) == 1);
}

bool ValueParameter::pluginMayWrite() throw(Exception) {
  return (mProps.getInt(kOfxParamPropPluginMayWrite, 0) == 1);
}

ParamInvalidate ValueParameter::cacheInvalidation() throw(Exception) {
  return StringToParamInvalidate(mProps.getString(kOfxParamPropCacheInvalidation, 0));
}

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
    stat = mSuite->paramCopy(handle(), from.handle(), offset, &frameRange);
  } else {
    stat = mSuite->paramCopy(handle(), from.handle(), offset, NULL);
  }
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ValueParameter::copy");
  }
}

// ---

IntParameter::IntParameter()
  : ValueParameter() {
}

IntParameter::IntParameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : ValueParameter(h, hdl) {
}

IntParameter::IntParameter(const IntParameter &rhs)
  : ValueParameter(rhs) {
}

IntParameter::~IntParameter() {
}

IntParameter& IntParameter::operator=(const IntParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

int IntParameter::getDefault() throw(Exception) {
  return mProps.getInt(kOfxParamPropDefault, 0);
}

int IntParameter::getMin() throw(Exception) {
  return mProps.getInt(kOfxParamPropMin, 0);
}

void IntParameter::setMin(int v) throw(Exception) {
  mProps.setInt(kOfxParamPropMin, 0, v);
}

int IntParameter::getMax() throw(Exception) {
  return mProps.getInt(kOfxParamPropMax, 0);
}

void IntParameter::setMax(int v) throw(Exception) {
  mProps.setInt(kOfxParamPropMax, 0, v);
}

int IntParameter::getDisplayMin() throw(Exception) {
  return mProps.getInt(kOfxParamPropDisplayMin, 0);
}

void IntParameter::setDisplayMin(int v) throw(Exception) {
  mProps.setInt(kOfxParamPropDisplayMin, 0, v);
}

int IntParameter::getDisplayMax() throw(Exception) {
  return mProps.getInt(kOfxParamPropDisplayMax, 0);
}

void IntParameter::setDisplayMax(int v) throw(Exception) {
  mProps.setInt(kOfxParamPropDisplayMax, 0, v);
}

int IntParameter::getValue() throw(Exception) {
  int val;
  OfxStatus stat = mSuite->paramGetValue(mHandle, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::IntParameter::getValue");
  }
  return val;
}

int IntParameter::getValueAtTime(Time t) throw(Exception) {
  int val;
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::IntParameter::getValueAtTime");
  }
  return val;
}

int IntParameter::getDerivative(Time t) throw(Exception) {
  int val;
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::IntParameter::getDerivative");
  }
  return val;
}

int IntParameter::getIntegral(Time t0, Time t1) throw(Exception) {
  int val;
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::IntParameter::getIntegral");
  }
  return val;
}

void IntParameter::setValue(int v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::IntParameter::setValue");
  }
}

void IntParameter::setValueAtTime(Time t, int v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::IntParameter::setValueAtTime");
  }
}

// ---

Int2Parameter::Int2Parameter()
  : ValueParameter() {
}

Int2Parameter::Int2Parameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : ValueParameter(h, hdl) {
}

Int2Parameter::Int2Parameter(const Int2Parameter &rhs)
  : ValueParameter(rhs) {
}

Int2Parameter::~Int2Parameter() {
}

Int2Parameter& Int2Parameter::operator=(const Int2Parameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

void Int2Parameter::getDefault(int &v0, int &v1) throw(Exception) {
  v0 = mProps.getInt(kOfxParamPropDefault, 0);
  v1 = mProps.getInt(kOfxParamPropDefault, 1);
}

void Int2Parameter::getMin(int &v0, int &v1) throw(Exception) {
  v0 = mProps.getInt(kOfxParamPropMin, 0);
  v1 = mProps.getInt(kOfxParamPropMin, 1);
}

void Int2Parameter::setMin(int v0, int v1) throw(Exception) {
  mProps.setInt(kOfxParamPropMin, 0, v0);
  mProps.setInt(kOfxParamPropMin, 1, v1);
}

void Int2Parameter::getMax(int &v0, int &v1) throw(Exception) {
  v0 = mProps.getInt(kOfxParamPropMax, 0);
  v1 = mProps.getInt(kOfxParamPropMax, 1);
}

void Int2Parameter::setMax(int v0, int v1) throw(Exception) {
  mProps.setInt(kOfxParamPropMax, 0, v0);
  mProps.setInt(kOfxParamPropMax, 1, v1);
}

void Int2Parameter::getDisplayMin(int &v0, int &v1) throw(Exception) {
  v0 = mProps.getInt(kOfxParamPropDisplayMin, 0);
  v1 = mProps.getInt(kOfxParamPropDisplayMin, 1);
}

void Int2Parameter::setDisplayMin(int v0, int v1) throw(Exception) {
  mProps.setInt(kOfxParamPropDisplayMin, 0, v0);
  mProps.setInt(kOfxParamPropDisplayMin, 1, v1);
}

void Int2Parameter::getDisplayMax(int &v0, int &v1) throw(Exception) {
  v0 = mProps.getInt(kOfxParamPropDisplayMax, 0);
  v1 = mProps.getInt(kOfxParamPropDisplayMax, 1);
}

void Int2Parameter::setDisplayMax(int v0, int v1) throw(Exception) {
  mProps.setInt(kOfxParamPropDisplayMax, 0, v0);
  mProps.setInt(kOfxParamPropDisplayMax, 1, v1);
}

std::string Int2Parameter::getDimensionLabel(int i) throw(Exception) {
  return mProps.getString(kOfxParamPropDimensionLabel, i);
}

void Int2Parameter::getValue(int &v0, int &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValue(mHandle, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int2Parameter::getValue");
  }
}

void Int2Parameter::getValueAtTime(Time t, int &v0, int &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int2Parameter::getValueAtTime");
  }
}

void Int2Parameter::getDerivative(Time t, int &v0, int &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int2Parameter::getDerivative");
  }
}

void Int2Parameter::getIntegral(Time t0, Time t1, int &v0, int &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int2Parameter::getIntegral");
  }
}

void Int2Parameter::setValue(int v0, int v1) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v0, v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int2Parameter::setValue");
  }
}

void Int2Parameter::setValueAtTime(Time t, int v0, int v1) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v0, v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int2Parameter::setValueAtTime");
  }
}

// ---

Int3Parameter::Int3Parameter()
  : ValueParameter() {
}

Int3Parameter::Int3Parameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : ValueParameter(h, hdl) {
}

Int3Parameter::Int3Parameter(const Int3Parameter &rhs)
  : ValueParameter(rhs) {
}

Int3Parameter::~Int3Parameter() {
}

Int3Parameter& Int3Parameter::operator=(const Int3Parameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

void Int3Parameter::getDefault(int &v0, int &v1, int &v2) throw(Exception) {
  v0 = mProps.getInt(kOfxParamPropDefault, 0);
  v1 = mProps.getInt(kOfxParamPropDefault, 1);
  v2 = mProps.getInt(kOfxParamPropDefault, 2);
}

void Int3Parameter::getMin(int &v0, int &v1, int &v2) throw(Exception) {
  v0 = mProps.getInt(kOfxParamPropMin, 0);
  v1 = mProps.getInt(kOfxParamPropMin, 1);
  v2 = mProps.getInt(kOfxParamPropMin, 2);
}

void Int3Parameter::setMin(int v0, int v1, int v2) throw(Exception) {
  mProps.setInt(kOfxParamPropMin, 0, v0);
  mProps.setInt(kOfxParamPropMin, 1, v1);
  mProps.setInt(kOfxParamPropMin, 2, v2);
}

void Int3Parameter::getMax(int &v0, int &v1, int &v2) throw(Exception) {
  v0 = mProps.getInt(kOfxParamPropMax, 0);
  v1 = mProps.getInt(kOfxParamPropMax, 1);
  v2 = mProps.getInt(kOfxParamPropMax, 2);
}

void Int3Parameter::setMax(int v0, int v1, int v2) throw(Exception) {
  mProps.setInt(kOfxParamPropMax, 0, v0);
  mProps.setInt(kOfxParamPropMax, 1, v1);
  mProps.setInt(kOfxParamPropMax, 2, v2);
}

void Int3Parameter::getDisplayMin(int &v0, int &v1, int &v2) throw(Exception) {
  v0 = mProps.getInt(kOfxParamPropDisplayMin, 0);
  v1 = mProps.getInt(kOfxParamPropDisplayMin, 1);
  v2 = mProps.getInt(kOfxParamPropDisplayMin, 2);
}

void Int3Parameter::setDisplayMin(int v0, int v1, int v2) throw(Exception) {
  mProps.setInt(kOfxParamPropDisplayMin, 0, v0);
  mProps.setInt(kOfxParamPropDisplayMin, 1, v1);
  mProps.setInt(kOfxParamPropDisplayMin, 2, v2);
}

void Int3Parameter::getDisplayMax(int &v0, int &v1, int &v2) throw(Exception) {
  v0 = mProps.getInt(kOfxParamPropDisplayMax, 0);
  v1 = mProps.getInt(kOfxParamPropDisplayMax, 1);
  v2 = mProps.getInt(kOfxParamPropDisplayMax, 2);
}

void Int3Parameter::setDisplayMax(int v0, int v1, int v2) throw(Exception) {
  mProps.setInt(kOfxParamPropDisplayMax, 0, v0);
  mProps.setInt(kOfxParamPropDisplayMax, 1, v1);
  mProps.setInt(kOfxParamPropDisplayMax, 2, v2);
}

std::string Int3Parameter::getDimensionLabel(int i) throw(Exception) {
  return mProps.getString(kOfxParamPropDimensionLabel, i);
}

void Int3Parameter::getValue(int &v0, int &v1, int &v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValue(mHandle, &v0, &v1, &v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int3Parameter::getValue");
  }
}

void Int3Parameter::getValueAtTime(Time t, int &v0, int &v1, int &v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &v0, &v1, &v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int3Parameter::getValueAtTime");
  }
}

void Int3Parameter::getDerivative(Time t, int &v0, int &v1, int &v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, &v0, &v1, &v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int3Parameter::getDerivative");
  }
}

void Int3Parameter::getIntegral(Time t0, Time t1, int &v0, int &v1, int &v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, &v0, &v1, &v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int3Parameter::getIntegral");
  }
}

void Int3Parameter::setValue(int v0, int v1, int v2) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v0, v1, v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int3Parameter::setValue");
  }
}

void Int3Parameter::setValueAtTime(Time t, int v0, int v1, int v2) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v0, v1, v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Int3Parameter::setValueAtTime");
  }
}

// ---

DoubleParameter::DoubleParameter()
  : ValueParameter() {
}

DoubleParameter::DoubleParameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : ValueParameter(h, hdl) {
}

DoubleParameter::DoubleParameter(const DoubleParameter &rhs)
  : ValueParameter(rhs) {
}

DoubleParameter::~DoubleParameter() {
}

DoubleParameter& DoubleParameter::operator=(const DoubleParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

double DoubleParameter::getDefault() throw(Exception) {
  return mProps.getDouble(kOfxParamPropDefault, 0);
}

double DoubleParameter::getMin() throw(Exception) {
  return mProps.getDouble(kOfxParamPropMin, 0);
}

void DoubleParameter::setMin(double min0) throw(Exception) {
  mProps.setDouble(kOfxParamPropMin, 0, min0);
}

double DoubleParameter::getMax() throw(Exception) {
  return mProps.getDouble(kOfxParamPropMax, 0);
}

void DoubleParameter::setMax(double max0) throw(Exception) {
  mProps.setDouble(kOfxParamPropMax, 0, max0);
}

double DoubleParameter::getDisplayMin() throw(Exception) {
  return mProps.getDouble(kOfxParamPropDisplayMin, 0);
}

void DoubleParameter::setDisplayMin(double min0) throw(Exception) {
  mProps.setDouble(kOfxParamPropDisplayMin, 0, min0);
}

double DoubleParameter::getDisplayMax() throw(Exception) {
  return mProps.getDouble(kOfxParamPropDisplayMax, 0);
}

void DoubleParameter::setDisplayMax(double max0) throw(Exception) {
  mProps.setDouble(kOfxParamPropDisplayMax, 0, max0);
}

double DoubleParameter::increment() throw(Exception) {
  return mProps.getDouble(kOfxParamPropIncrement, 0);
}

void DoubleParameter::setIncrement(double i) throw(Exception) {
  mProps.setDouble(kOfxParamPropIncrement, 0, i);
}

int DoubleParameter::digits() throw(Exception) {
  return mProps.getInt(kOfxParamPropDigits, 0);
}

void DoubleParameter::setDigits(int d) throw(Exception) {
  mProps.setInt(kOfxParamPropDigits, 0, d);
}

bool DoubleParameter::showTimeMarker() throw(Exception) {
  return (mProps.getInt(kOfxParamPropShowTimeMarker, 0) == 1);
}

void DoubleParameter::setShowTimeMarker(bool yes) throw(Exception) {
  mProps.setInt(kOfxParamPropShowTimeMarker, 0, (yes ? 1 : 0));
}

DoubleParamType DoubleParameter::doubleType() throw(Exception) {
  return StringToDoubleParamType(mProps.getString(kOfxParamPropDoubleType, 0));
}

double DoubleParameter::getValue() throw(Exception) {
  double val;
  OfxStatus stat = mSuite->paramGetValue(mHandle, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::DoubleParameter::getValue");
  }
  return val;
}

double DoubleParameter::getValueAtTime(Time t) throw(Exception) {
  double val;
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::DoubleParameter::getValueAtTime");
  }
  return val;
}

double DoubleParameter::getDerivative(Time t) throw(Exception) {
  double val;
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::DoubleParameter::getDerivative");
  }
  return val;
}

double DoubleParameter::getIntegral(Time t0, Time t1) throw(Exception) {
  double val;
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::DoubleParameter::getIntegral");
  }
  return val;
}

void DoubleParameter::setValue(double v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::DoubleParameter::setValue");
  }
}

void DoubleParameter::setValueAtTime(Time t, double v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::DoubleParameter::setValueAtTime");
  }
}

// ---

Double2Parameter::Double2Parameter()
  : ValueParameter() {
}

Double2Parameter::Double2Parameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : ValueParameter(h, hdl) {
}

Double2Parameter::Double2Parameter(const Double2Parameter &rhs)
  : ValueParameter(rhs) {
}

Double2Parameter::~Double2Parameter() {
}

Double2Parameter& Double2Parameter::operator=(const Double2Parameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

void Double2Parameter::getDefault(double &v0, double &v1) throw(Exception) {
  v0 = mProps.getDouble(kOfxParamPropDefault, 0);
  v1 = mProps.getDouble(kOfxParamPropDefault, 1);
}

void Double2Parameter::getMin(double &v0, double &v1) throw(Exception) {
  v0 = mProps.getDouble(kOfxParamPropMin, 0);
  v1 = mProps.getDouble(kOfxParamPropMin, 1);
}

void Double2Parameter::setMin(double min0, double min1) throw(Exception) {
  mProps.setDouble(kOfxParamPropMin, 0, min0);
  mProps.setDouble(kOfxParamPropMin, 1, min1);
}

void Double2Parameter::getMax(double &v0, double &v1) throw(Exception) {
  v0 = mProps.getDouble(kOfxParamPropMax, 0);
  v1 = mProps.getDouble(kOfxParamPropMax, 1);
}

void Double2Parameter::setMax(double max0, double max1) throw(Exception) {
  mProps.setDouble(kOfxParamPropMax, 0, max0);
  mProps.setDouble(kOfxParamPropMax, 1, max1);
}

void Double2Parameter::getDisplayMin(double &v0, double &v1) throw(Exception) {
  v0 = mProps.getDouble(kOfxParamPropDisplayMin, 0);
  v1 = mProps.getDouble(kOfxParamPropDisplayMin, 1);
}

void Double2Parameter::setDisplayMin(double min0, double min1) throw(Exception) {
  mProps.setDouble(kOfxParamPropDisplayMin, 0, min0);
  mProps.setDouble(kOfxParamPropDisplayMin, 1, min1);
}

void Double2Parameter::getDisplayMax(double &v0, double &v1) throw(Exception) {
  v0 = mProps.getDouble(kOfxParamPropDisplayMax, 0);
  v1 = mProps.getDouble(kOfxParamPropDisplayMax, 1);
}

void Double2Parameter::setDisplayMax(double max0, double max1) throw(Exception) {
  mProps.setDouble(kOfxParamPropDisplayMax, 0, max0);
  mProps.setDouble(kOfxParamPropDisplayMax, 1, max1);
}

double Double2Parameter::increment() throw(Exception) {
  return mProps.getDouble(kOfxParamPropIncrement, 0);
}

void Double2Parameter::setIncrement(double i) throw(Exception) {
  mProps.setDouble(kOfxParamPropIncrement, 0, i);
}

int Double2Parameter::digits() throw(Exception) {
  return mProps.getInt(kOfxParamPropDigits, 0);
}

void Double2Parameter::setDigits(int d) throw(Exception) {
  mProps.setInt(kOfxParamPropDigits, 0, d);
}

DoubleParamType Double2Parameter::doubleType() throw(Exception) {
  return StringToDoubleParamType(mProps.getString(kOfxParamPropDoubleType, 0));
}

std::string Double2Parameter::getDimensionLabel(int i) throw(Exception) {
  return mProps.getString(kOfxParamPropDimensionLabel, i);
}

void Double2Parameter::getValue(double &v0, double &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValue(mHandle, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double2Parameter::getValue");
  }
}

void Double2Parameter::getValueAtTime(Time t, double &v0, double &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double2Parameter::getValueAtTime");
  }
}

void Double2Parameter::getDerivative(Time t, double &v0, double &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double2Parameter::getDerivative");
  }
}

void Double2Parameter::getIntegral(Time t0, Time t1, double &v0, double &v1) throw(Exception) {
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, &v0, &v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double2Parameter::getIntegral");
  }
}

void Double2Parameter::setValue(double v0, double v1) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v0, v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double2Parameter::setValue");
  }
}

void Double2Parameter::setValueAtTime(Time t, double v0, double v1) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v0, v1);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double2Parameter::setValueAtTime");
  }
}

// ---

Double3Parameter::Double3Parameter()
  : ValueParameter() {
}

Double3Parameter::Double3Parameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : ValueParameter(h, hdl) {
}

Double3Parameter::Double3Parameter(const Double3Parameter &rhs)
  : ValueParameter(rhs) {
}

Double3Parameter::~Double3Parameter() {
}

Double3Parameter& Double3Parameter::operator=(const Double3Parameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

void Double3Parameter::getDefault(double &v0, double &v1, double &v2) throw(Exception) {
  v0 = mProps.getDouble(kOfxParamPropDefault, 0);
  v1 = mProps.getDouble(kOfxParamPropDefault, 1);
  v2 = mProps.getDouble(kOfxParamPropDefault, 2);
}

void Double3Parameter::getMin(double &v0, double &v1, double &v2) throw(Exception) {
  v0 = mProps.getDouble(kOfxParamPropMin, 0);
  v1 = mProps.getDouble(kOfxParamPropMin, 1);
  v2 = mProps.getDouble(kOfxParamPropMin, 2);
}

void Double3Parameter::setMin(double min0, double min1, double min2) throw(Exception) {
  mProps.setDouble(kOfxParamPropMin, 0, min0);
  mProps.setDouble(kOfxParamPropMin, 1, min1);
  mProps.setDouble(kOfxParamPropMin, 2, min2);
}

void Double3Parameter::getMax(double &v0, double &v1, double &v2) throw(Exception) {
  v0 = mProps.getDouble(kOfxParamPropMax, 0);
  v1 = mProps.getDouble(kOfxParamPropMax, 1);
  v2 = mProps.getDouble(kOfxParamPropMax, 2);
}

void Double3Parameter::setMax(double max0, double max1, double max2) throw(Exception) {
  mProps.setDouble(kOfxParamPropMax, 0, max0);
  mProps.setDouble(kOfxParamPropMax, 1, max1);
  mProps.setDouble(kOfxParamPropMax, 2, max2);
}

void Double3Parameter::getDisplayMin(double &v0, double &v1, double &v2) throw(Exception) {
  v0 = mProps.getDouble(kOfxParamPropDisplayMin, 0);
  v1 = mProps.getDouble(kOfxParamPropDisplayMin, 1);
  v2 = mProps.getDouble(kOfxParamPropDisplayMin, 2);
}

void Double3Parameter::setDisplayMin(double min0, double min1, double min2) throw(Exception) {
  mProps.setDouble(kOfxParamPropDisplayMin, 0, min0);
  mProps.setDouble(kOfxParamPropDisplayMin, 1, min1);
  mProps.setDouble(kOfxParamPropDisplayMin, 2, min2);
}

void Double3Parameter::getDisplayMax(double &v0, double &v1, double &v2) throw(Exception) {
  v0 = mProps.getDouble(kOfxParamPropDisplayMax, 0);
  v1 = mProps.getDouble(kOfxParamPropDisplayMax, 1);
  v2 = mProps.getDouble(kOfxParamPropDisplayMax, 2);
}

void Double3Parameter::setDisplayMax(double max0, double max1, double max2) throw(Exception) {
  mProps.setDouble(kOfxParamPropDisplayMax, 0, max0);
  mProps.setDouble(kOfxParamPropDisplayMax, 1, max1);
  mProps.setDouble(kOfxParamPropDisplayMax, 2, max2);
}

double Double3Parameter::increment() throw(Exception) {
  return mProps.getDouble(kOfxParamPropIncrement, 0);
}

void Double3Parameter::setIncrement(double i) throw(Exception) {
  mProps.setDouble(kOfxParamPropIncrement, 0, i);
}

int Double3Parameter::digits() throw(Exception) {
  return mProps.getInt(kOfxParamPropDigits, 0);
}

void Double3Parameter::setDigits(int d) throw(Exception) {
  mProps.setInt(kOfxParamPropDigits, 0, d);
}

DoubleParamType Double3Parameter::doubleType() throw(Exception) {
  return StringToDoubleParamType(mProps.getString(kOfxParamPropDoubleType, 0));
}

std::string Double3Parameter::getDimensionLabel(int i) throw(Exception) {
  return mProps.getString(kOfxParamPropDimensionLabel, i);
}

void Double3Parameter::getValue(double &v0, double &v1, double &v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValue(mHandle, &v0, &v1, &v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double3Parameter::getValue");
  }
}

void Double3Parameter::getValueAtTime(Time t, double &v0, double &v1, double &v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &v0, &v1, &v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double3Parameter::getValueAtTime");
  }
}

void Double3Parameter::getDerivative(Time t, double &v0, double &v1, double &v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, &v0, &v1, &v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double3Parameter::getDerivative");
  }
}

void Double3Parameter::getIntegral(Time t0, Time t1, double &v0, double &v1, double &v2) throw(Exception) {
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, &v0, &v1, &v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double3Parameter::getIntegral");
  }
}

void Double3Parameter::setValue(double v0, double v1, double v2) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v0, v1, v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double3Parameter::setValue");
  }
}

void Double3Parameter::setValueAtTime(Time t, double v0, double v1, double v2) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v0, v1, v2);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::Double3Parameter::setValueAtTime");
  }
}

// ---

ChoiceParameter::ChoiceParameter()
  : ValueParameter() {
}

ChoiceParameter::ChoiceParameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : ValueParameter(h, hdl) {
}

ChoiceParameter::ChoiceParameter(const ChoiceParameter &rhs)
  : ValueParameter(rhs) {
}

ChoiceParameter::~ChoiceParameter() {
}

ChoiceParameter& ChoiceParameter::operator=(const ChoiceParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

int ChoiceParameter::getDefault() throw(Exception) {
  return mProps.getInt(kOfxParamPropDefault, 0);
}

int ChoiceParameter::getChoiceCount() throw(Exception) {
  return mProps.size(kOfxParamPropChoiceOption);
}

void ChoiceParameter::setChoice(int i, const std::string &str) throw(Exception) {
  mProps.setString(kOfxParamPropChoiceOption, i, str);
}

std::string ChoiceParameter::getChoice(int i) throw(Exception) {
  return mProps.getString(kOfxParamPropChoiceOption, i);
}

int ChoiceParameter::getValue() throw(Exception) {
  int val;
  OfxStatus stat = mSuite->paramGetValue(mHandle, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ChoiceParameter::getValue");
  }
  return val;
}

int ChoiceParameter::getValueAtTime(Time t) throw(Exception) {
  int val;
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ChoiceParameter::getValueAtTime");
  }
  return val;
}

void ChoiceParameter::setValue(int v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ChoiceParameter::setValue");
  }
}

void ChoiceParameter::setValueAtTime(Time t, int v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ChoiceParameter::setValueAtTime");
  }
}

// ---

StringParameter::StringParameter()
  : ValueParameter() {
}

StringParameter::StringParameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : ValueParameter(h, hdl) {
  
}

StringParameter::StringParameter(const StringParameter &rhs)
  : ValueParameter(rhs) {
  
}

StringParameter::~StringParameter() {
}

StringParameter& StringParameter::operator=(const StringParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

std::string StringParameter::getDefault() throw(Exception) {
  return mProps.getString(kOfxParamPropDefault, 0);
}

StringParamMode StringParameter::mode() throw(Exception) {
  return StringToStringParamMode(mProps.getString(kOfxParamPropStringMode, 0));
}

bool StringParameter::filePathExists() throw(Exception) {
  return (mProps.getInt(kOfxParamPropStringFilePathExists, 0) == 1);
}

std::string StringParameter::getValue() throw(Exception) {
  char *val = 0;
  // no quite sure about this one
  OfxStatus stat = mSuite->paramGetValue(mHandle, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::StringParameter::getValue");
  }
  return val;
}

std::string StringParameter::getValueAtTime(Time t) throw(Exception) {
  char *val = 0;
  // no quite sure about this one
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::StringParameter::getValueAtTime");
  }
  return val;
}

void StringParameter::setValue(const std::string &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v.c_str());
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::StringParameter::setValue");
  }
}

void StringParameter::setValueAtTime(Time t, const std::string &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v.c_str());
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::StringParameter::setValueAtTime");
  }
}

// ---

CustomParameter::CustomParameter()
  : ValueParameter() {
}

CustomParameter::CustomParameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : ValueParameter(h, hdl) {
}

CustomParameter::CustomParameter(const CustomParameter &rhs)
  : ValueParameter(rhs) {
}

CustomParameter::~CustomParameter() {
}

CustomParameter& CustomParameter::operator=(const CustomParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

std::string CustomParameter::getDefault() throw(Exception) {
  return mProps.getString(kOfxParamPropDefault, 0);
}

void* CustomParameter::getInterpolator() throw(Exception) {
  return mProps.getPointer(kOfxParamPropCustomInterpCallbackV1, 0);
}

std::string CustomParameter::getValue() throw(Exception) {
  char *val = 0;
  // no quite sure about this one
  OfxStatus stat = mSuite->paramGetValue(mHandle, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::CustomParameter::getValue");
  }
  return val;
}

std::string CustomParameter::getValueAtTime(Time t) throw(Exception) {
  char *val = 0;
  // no quite sure about this one
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::CustomParameter::getValueAtTime");
  }
  return val;
}

void CustomParameter::setValue(const std::string &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v.c_str());
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::CustomParameter::setValue");
  }
}

void CustomParameter::setValueAtTime(Time t, const std::string &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v.c_str());
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::CustomParameter::setValueAtTime");
  }
}

// ---

BooleanParameter::BooleanParameter()
  : ValueParameter() {
}

BooleanParameter::BooleanParameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : ValueParameter(h, hdl) {
}

BooleanParameter::BooleanParameter(const BooleanParameter &rhs)
  : ValueParameter(rhs) {
}

BooleanParameter::~BooleanParameter() {
}

BooleanParameter& BooleanParameter::operator=(const BooleanParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

bool BooleanParameter::getDefault() throw(Exception) {
  return (mProps.getInt(kOfxParamPropDefault, 0) == 1);
}

bool BooleanParameter::getValue() throw(Exception) {
  int val;
  // no quite sure about this one
  OfxStatus stat = mSuite->paramGetValue(mHandle, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::BooleanParameter::getValue");
  }
  return (val == 1);
}

bool BooleanParameter::getValueAtTime(Time t) throw(Exception) {
  int val;
  // no quite sure about this one
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::BooleanParameter::getValueAtTime");
  }
  return (val == 1);
}

void BooleanParameter::setValue(bool v) throw(Exception) {
  int val = (v ? 1 : 0);
  OfxStatus stat = mSuite->paramSetValue(mHandle, val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::BooleanParameter::setValue");
  }
}

void BooleanParameter::setValueAtTime(Time t, bool v) throw(Exception) {
  int val = (v ? 1 : 0);
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, val);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::BooleanParameter::setValueAtTime");
  }
}

// ---

RGBParameter::RGBParameter()
  : ValueParameter() {
}

RGBParameter::RGBParameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : ValueParameter(h, hdl) {
}

RGBParameter::RGBParameter(const RGBParameter &rhs)
  : ValueParameter(rhs) {
}

RGBParameter::~RGBParameter() {
}

RGBParameter& RGBParameter::operator=(const RGBParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

RGBAColour<double> RGBParameter::getDefault() throw(Exception) {
  RGBAColour<double> rv;
  mProps.getDoubles(kOfxParamPropDefault, 3, &(rv.r));
  rv.a = 1.0;
  return rv;
}

RGBAColour<double> RGBParameter::getValue() throw(Exception) {
  RGBAColour<double> v;
  v.a = 1.0;
  OfxStatus stat = mSuite->paramGetValue(mHandle, &(v.r), &(v.g), &(v.b));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBParameter::getValue");
  }
  return v;
}

RGBAColour<double> RGBParameter::getValueAtTime(Time t) throw(Exception) {
  RGBAColour<double> v;
  v.a = 1.0;
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &(v.r), &(v.g), &(v.b));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBParameter::getValueAtTime");
  }
  return v;
}

RGBAColour<double> RGBParameter::getDerivative(Time t) throw(Exception) {
  RGBAColour<double> v;
  v.a = 1.0;
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, &(v.r), &(v.g), &(v.b));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBParameter::getDerivative");
  }
  return v;
}

RGBAColour<double> RGBParameter::getIntegral(Time t0, Time t1) throw(Exception) {
  RGBAColour<double> v;
  v.a = 1.0;
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, &(v.r), &(v.g), &(v.b));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBParameter::getIntegral");
  }
  return v;
}

void RGBParameter::setValue(const RGBAColour<double> &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v.r, v.g, v.b);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBParameter::setValue");
  }
}

void RGBParameter::setValueAtTime(Time t, const RGBAColour<double> &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v.r, v.g, v.b);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBParameter::setValueAtTime");
  }
}

// ---

RGBAParameter::RGBAParameter()
  : ValueParameter() {
}

RGBAParameter::RGBAParameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : ValueParameter(h, hdl) {
}

RGBAParameter::RGBAParameter(const RGBAParameter &rhs)
  : ValueParameter(rhs) {
}

RGBAParameter::~RGBAParameter() {
}

RGBAParameter& RGBAParameter::operator=(const RGBAParameter &rhs) {
  ValueParameter::operator=(rhs);
  return *this;
}

RGBAColour<double> RGBAParameter::getDefault() throw(Exception) {
  RGBAColour<double> rv;
  mProps.getDoubles(kOfxParamPropDefault, 4, &(rv.r));
  return rv;
}

RGBAColour<double> RGBAParameter::getValue() throw(Exception) {
  RGBAColour<double> v;
  OfxStatus stat = mSuite->paramGetValue(mHandle, &(v.r), &(v.g), &(v.b), &(v.a));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBAParameter::getValue");
  }
  return v;
}

RGBAColour<double> RGBAParameter::getValueAtTime(Time t) throw(Exception) {
  RGBAColour<double> v;
  OfxStatus stat = mSuite->paramGetValueAtTime(mHandle, t, &(v.r), &(v.g), &(v.b), &(v.a));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBAParameter::getValueAtTime");
  }
  return v;
}

RGBAColour<double> RGBAParameter::getDerivative(Time t) throw(Exception) {
  RGBAColour<double> v;
  OfxStatus stat = mSuite->paramGetDerivative(mHandle, t, &(v.r), &(v.g), &(v.b), &(v.a));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBAParameter::getDerivative");
  }
  return v;
}

RGBAColour<double> RGBAParameter::getIntegral(Time t0, Time t1) throw(Exception) {
  RGBAColour<double> v;
  OfxStatus stat = mSuite->paramGetIntegral(mHandle, t0, t1, &(v.r), &(v.g), &(v.b), &(v.a));
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBAParameter::getIntegral");
  }
  return v;
}

void RGBAParameter::setValue(const RGBAColour<double> &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValue(mHandle, v.r, v.g, v.b, v.a);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBAParameter::setValue");
  }
}

void RGBAParameter::setValueAtTime(Time t, const RGBAColour<double> &v) throw(Exception) {
  OfxStatus stat = mSuite->paramSetValueAtTime(mHandle, t, v.r, v.g, v.b, v.a);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::RGBAParameter::setValueAtTime");
  }
}


// ---

PageParameter::PageParameter()
  : Parameter() {
}

PageParameter::PageParameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : Parameter(h, hdl) {
}

PageParameter::PageParameter(const PageParameter &rhs)
  : Parameter(rhs) {
}

PageParameter::~PageParameter() {
}

PageParameter& PageParameter::operator=(const PageParameter &rhs) {
  Parameter::operator=(rhs);
  return *this;
}

int PageParameter::getChildCount() throw(Exception) {
  return mProps.size(kOfxParamPropPageChild);
}

std::string PageParameter::getChild(int i) throw(Exception) {
  return mProps.getString(kOfxParamPropPageChild, i);
}

// ---

PushButtonParameter::PushButtonParameter()
  : Parameter() {
}

PushButtonParameter::PushButtonParameter(Host *h, OfxParamHandle hdl) throw(Exception)
  : Parameter(h, hdl) {
}

PushButtonParameter::PushButtonParameter(const PushButtonParameter &rhs)
  : Parameter(rhs) {
}

PushButtonParameter::~PushButtonParameter() {
}

PushButtonParameter& PushButtonParameter::operator=(const PushButtonParameter &rhs) {
  Parameter::operator=(rhs);
  return *this;
}

EntryPoint PushButtonParameter::interact() throw(Exception) {
  return ((EntryPoint) mProps.getPointer(kOfxParamPropInteractV1, 0));
}

void PushButtonParameter::interactSize(double &w, double &h) throw(Exception) {
  w = mProps.getDouble(kOfxParamPropInteractSize, 0);
  h = mProps.getDouble(kOfxParamPropInteractSize, 1);
}

double PushButtonParameter::interactSizeAspect() throw(Exception) {
  return mProps.getDouble(kOfxParamPropInteractSizeAspect, 0);
}

void PushButtonParameter::interactMinimumSize(int &w, int &h) throw(Exception) {
  w = mProps.getInt(kOfxParamPropInteractMinimumSize, 0);
  h = mProps.getInt(kOfxParamPropInteractMinimumSize, 1);
}

void PushButtonParameter::interactPreferedSize(int &w, int &h) throw(Exception) {
  w = mProps.getInt(kOfxParamPropInteractPreferedSize, 0);
  h = mProps.getInt(kOfxParamPropInteractPreferedSize, 1);
}

// ---

ParameterSetDescriptor::ParameterSetDescriptor()
  : mHandle(0) {
}

ParameterSetDescriptor::ParameterSetDescriptor(Host *h, OfxParamSetHandle hdl) throw(Exception)
  : mHandle(hdl), mHost(h) {
  if (!mHost) {
    throw Exception(kOfxStatErrFatal, "ofx::ParameterSetDescriptor::ParameterSetDescriptor: no host");
  }
  OfxPropertySetHandle hProps;
  mHost->parameterSuite()->paramSetGetPropertySet(mHandle, &hProps);
  mProps = PropertySet(mHost, hProps);
}

ParameterSetDescriptor::ParameterSetDescriptor(const ParameterSetDescriptor &rhs)
  : mHandle(rhs.mHandle), mProps(rhs.mProps), mHost(rhs.mHost) {
  
}

ParameterSetDescriptor::~ParameterSetDescriptor() {
}

ParameterSetDescriptor& ParameterSetDescriptor::operator=(const ParameterSetDescriptor &rhs) {
  mHandle = rhs.mHandle;
  mProps = rhs.mProps;
  mHost = rhs.mHost;
  return *this;
}

IntParameterDescriptor ParameterSetDescriptor::defineIntParam(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypeInteger), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::defineIntParam");
  }
  return IntParameterDescriptor(mHost, hParam);
}

Int2ParameterDescriptor ParameterSetDescriptor::defineInt2Param(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypeInteger2D), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::defineInt2Param");
  }
  return Int2ParameterDescriptor(mHost, hParam);
}

Int3ParameterDescriptor ParameterSetDescriptor::defineInt3Param(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypeInteger3D), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::defineInt3Param");
  }
  return Int3ParameterDescriptor(mHost, hParam);
}

DoubleParameterDescriptor ParameterSetDescriptor::defineDoubleParam(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypeDouble), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::defineDoubleParam");
  }
  return DoubleParameterDescriptor(mHost, hParam);
}

Double2ParameterDescriptor ParameterSetDescriptor::defineDouble2Param(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypeDouble2D), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::defineDouble2Param");
  }
  return Double2ParameterDescriptor(mHost, hParam);
}

Double3ParameterDescriptor ParameterSetDescriptor::defineDouble3Param(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypeDouble3D), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::defineDouble3Param");
  }
  return Double3ParameterDescriptor(mHost, hParam);
}

RGBParameterDescriptor ParameterSetDescriptor::defineRGBParam(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypeRGB), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::defineRGBParam");
  }
  return RGBParameterDescriptor(mHost, hParam);
}

RGBAParameterDescriptor ParameterSetDescriptor::defineRGBAParam(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypeRGBA), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::defineRGBAParam");
  }
  return RGBAParameterDescriptor(mHost, hParam);
}

BooleanParameterDescriptor ParameterSetDescriptor::defineBooleanParam(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypeBoolean), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::defineBooleanParam");
  }
  return BooleanParameterDescriptor(mHost, hParam);
}

ChoiceParameterDescriptor ParameterSetDescriptor::defineChoiceParam(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypeChoice), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::defineChoiceParam");
  }
  return ChoiceParameterDescriptor(mHost, hParam);
}

StringParameterDescriptor ParameterSetDescriptor::defineStringParam(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypeString), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::defineStringParam");
  }
  return StringParameterDescriptor(mHost, hParam);
}

CustomParameterDescriptor ParameterSetDescriptor::defineCustomParam(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypeCustom), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::defineCustomParam");
  }
  return CustomParameterDescriptor(mHost, hParam);
}

GroupParameterDescriptor ParameterSetDescriptor::defineGroupParam(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypeGroup), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::defineGroupParam");
  }
  return GroupParameterDescriptor(mHost, hParam);
}

PageParameterDescriptor ParameterSetDescriptor::definePageParam(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypePage), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::definePageParam");
  }
  return PageParameterDescriptor(mHost, hParam);
}

PushButtonParameterDescriptor ParameterSetDescriptor::definePushButtonParam(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypePushButton), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::definePushButtonParam");
  }
  return PushButtonParameterDescriptor(mHost, hParam);
}

// ---

ParameterSet::ParameterSet()
  : mHandle(0), mHost(0) {
}

ParameterSet::ParameterSet(Host *h, OfxParamSetHandle hdl) throw(Exception)
  : mHandle(hdl), mHost(h) {
  if (!mHost) {
    throw Exception(kOfxStatErrFatal, "ofx::ParameterSet::ParameterSet: no host");
  }
  OfxPropertySetHandle hProps;
  mHost->parameterSuite()->paramSetGetPropertySet(mHandle, &hProps);
  mProps = PropertySet(h, hProps);
}

ParameterSet::ParameterSet(const ParameterSet &rhs)
  : mHandle(rhs.mHandle), mProps(rhs.mProps), mHost(rhs.mHost) {
}

ParameterSet::~ParameterSet() {
}

ParameterSet& ParameterSet::operator=(const ParameterSet &rhs) {
  mHandle = rhs.mHandle;
  mProps = rhs.mProps;
  mHost = rhs.mHost;
  return *this;
}

IntParameter ParameterSet::getIntParam(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSet::getIntParam");
  }
  IntParameter param(mHost, hParam);
  if (param.type() != ParamTypeInteger) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getIntParam: type mismatch");
  }
  return param;
}

Int2Parameter ParameterSet::getInt2Param(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::getInt2Param");
  }
  Int2Parameter param(mHost, hParam);
  if (param.type() != ParamTypeInteger2D) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getInt2Param: type mismatch");
  }
  return param;
}

Int3Parameter ParameterSet::getInt3Param(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::getInt3Param");
  }
  Int3Parameter param(mHost, hParam);
  if (param.type() != ParamTypeInteger3D) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getInt3Param: type mismatch");
  }
  return param;
}

DoubleParameter ParameterSet::getDoubleParam(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::getDoubleParam");
  }
  DoubleParameter param(mHost, hParam);
  if (param.type() != ParamTypeDouble) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getDoubleParam: type mismatch");
  }
  return param;
}

Double2Parameter ParameterSet::getDouble2Param(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::getDouble2Param");
  }
  Double2Parameter param(mHost, hParam);
  if (param.type() != ParamTypeDouble2D) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getDouble2Param: type mismatch");
  }
  return param;
}

Double3Parameter ParameterSet::getDouble3Param(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::getDouble3Param");
  }
  Double3Parameter param(mHost, hParam);
  if (param.type() != ParamTypeDouble3D) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getDouble3Param: type mismatch");
  }
  return param;
}

RGBParameter ParameterSet::getRGBParam(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::getRGBParam");
  }
  RGBParameter param(mHost, hParam);
  if (param.type() != ParamTypeRGB) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getRGBParam: type mismatch");
  }
  return param;
}

RGBAParameter ParameterSet::getRGBAParam(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::getRGBAParam");
  }
  RGBAParameter param(mHost, hParam);
  if (param.type() != ParamTypeRGBA) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getRGBAParam: type mismatch");
  }
  return param;
}

BooleanParameter ParameterSet::getBooleanParam(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::getBooleanParam");
  }
  BooleanParameter param(mHost, hParam);
  if (param.type() != ParamTypeBoolean) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getBooleanParam: type mismatch");
  }
  return param;
}

ChoiceParameter ParameterSet::getChoiceParam(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::getChoiceParam");
  }
  ChoiceParameter param(mHost, hParam);
  if (param.type() != ParamTypeChoice) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getChoiceParam: type mismatch");
  }
  return param;
}

StringParameter ParameterSet::getStringParam(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::getStringParam");
  }
  StringParameter param(mHost, hParam);
  if (param.type() != ParamTypeString) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getStringParam: type mismatch");
  }
  return param;
}

CustomParameter ParameterSet::getCustomParam(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::getCustomParam");
  }
  CustomParameter param(mHost, hParam);
  if (param.type() != ParamTypeCustom) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getCustomParam: type mismatch");
  }
  return param;
}

GroupParameter ParameterSet::getGroupParam(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::getGroupParam");
  }
  GroupParameter param(mHost, hParam);
  if (param.type() != ParamTypeGroup) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getGroupParam: type mismatch");
  }
  return param;
}

PageParameter ParameterSet::getPageParam(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::getPageParam");
  }
  PageParameter param(mHost, hParam);
  if (param.type() != ParamTypePage) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getPageParam: type mismatch");
  }
  return param;
}

PushButtonParameter ParameterSet::getPushButtonParam(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::getPushButtonParam");
  }
  PushButtonParameter param(mHost, hParam);
  if (param.type() != ParamTypePushButton) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getPushButtonParam: type mismatch");
  }
  return param;
}

void ParameterSet::beginEdit(const std::string &label) throw(Exception) {
  mHost->parameterSuite()->paramEditBegin(mHandle, label.c_str());
}

void ParameterSet::endEdit() throw(Exception) {
  mHost->parameterSuite()->paramEditEnd(mHandle);
}

}

