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

#include <ofx/parameterset.h>
#include <ofx/host.h>

namespace ofx {

ParameterSetDescriptor::ParameterSetDescriptor()
  : mHandle(0) {
}

ParameterSetDescriptor::ParameterSetDescriptor(Host *h, OfxParamSetHandle hdl) throw(Exception)
  : mHandle(hdl), mHost(h) {
  if (!mHost) {
    throw BadHandleError("ofx::ParameterSetDescriptor::ParameterSetDescriptor: invalid host");
  }
  OfxPropertySetHandle hProps;
  // unchecked?
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

int ParameterSetDescriptor::pageOrderCount() {
  return mProps.size(kOfxPluginPropParamPageOrder);
}

std::string ParameterSetDescriptor::pageOrder(int idx) {
  return mProps.getString(kOfxPluginPropParamPageOrder, idx);
}

void ParameterSetDescriptor::pageOrder(int idx, const std::string &page) {
  mProps.setString(kOfxPluginPropParamPageOrder, idx, page);
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

#ifdef OFX_API_1_2

ParametricParameterDescriptor ParameterSetDescriptor::defineParametricParam(const std::string &name) throw(Exception) {
  OfxPropertySetHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramDefine(mHandle, ParamTypeToString(ParamTypeParametric), name.c_str(), &hParam);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSetDescriptor::defineParametricParam");
  }
  return ParametricParameterDescriptor(mHost, hParam);
}

#endif

// ---

ParameterSet::ParameterSet()
  : mHandle(0), mHost(0) {
}

ParameterSet::ParameterSet(Host *h, OfxParamSetHandle hdl) throw(Exception)
  : mHandle(hdl), mHost(h) {
  if (!mHost) {
    throw BadHandleError("ofx::ParameterSet::ParameterSet: invalid host");
  }
  OfxPropertySetHandle hProps;
  // unchecked?
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

int ParameterSet::pageOrderCount() {
  return mProps.size(kOfxPluginPropParamPageOrder);
}

std::string ParameterSet::pageOrder(int idx) {
  return mProps.getString(kOfxPluginPropParamPageOrder, idx);
}

bool ParameterSet::needsSyncing() {
  return (mProps.getInt(kOfxPropParamSetNeedsSyncing, 0) == 1);
}

void ParameterSet::needsSyncing(bool v) {
  mProps.setInt(kOfxPropParamSetNeedsSyncing, 0, (v ? 1 : 0));
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
    throw Exception(stat, "ofx::ParameterSet::getInt2Param");
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
    throw Exception(stat, "ofx::ParameterSet::getInt3Param");
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
    throw Exception(stat, "ofx::ParameterSet::getDoubleParam");
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
    throw Exception(stat, "ofx::ParameterSet::getDouble2Param");
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
    throw Exception(stat, "ofx::ParameterSet::getDouble3Param");
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
    throw Exception(stat, "ofx::ParameterSet::getRGBParam");
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
    throw Exception(stat, "ofx::ParameterSet::getRGBAParam");
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
    throw Exception(stat, "ofx::ParameterSet::getBooleanParam");
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
    throw Exception(stat, "ofx::ParameterSet::getChoiceParam");
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
    throw Exception(stat, "ofx::ParameterSet::getStringParam");
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
    throw Exception(stat, "ofx::ParameterSet::getCustomParam");
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
    throw Exception(stat, "ofx::ParameterSet::getGroupParam");
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
    throw Exception(stat, "ofx::ParameterSet::getPageParam");
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
    throw Exception(stat, "ofx::ParameterSet::getPushButtonParam");
  }
  PushButtonParameter param(mHost, hParam);
  if (param.type() != ParamTypePushButton) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getPushButtonParam: type mismatch");
  }
  return param;
}

#ifdef OFX_API_1_2

ParametricParameter ParameterSet::getParametricParam(const std::string &name) throw(Exception) {
  OfxParamHandle hParam;
  OfxStatus stat = mHost->parameterSuite()->paramGetHandle(mHandle, name.c_str(), &hParam, NULL);
  if (stat != kOfxStatOK) {
    throw Exception(stat, "ofx::ParameterSet::getParametricParam");
  }
  ParametricParameter param(mHost, hParam);
  if (param.type() != ParamTypeParametric) {
    throw Exception(kOfxStatFailed, "ofx::ParameterSet::getParametricParam: type mismatch");
  }
  return param;
}

#endif

void ParameterSet::beginEdit(const std::string &label) {
  mHost->parameterSuite()->paramEditBegin(mHandle, label.c_str());
}

void ParameterSet::endEdit() {
  mHost->parameterSuite()->paramEditEnd(mHandle);
}

}
