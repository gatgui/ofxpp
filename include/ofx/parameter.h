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

#ifndef __ofx_parameter_h__
#define __ofx_parameter_h__

#include <ofx/ofx.h>
#include <ofx/exception.h>
#include <ofx/property.h>
#include <ofxParam.h>

namespace ofx {
  
  class Host;
  class ParameterSet;
  
  typedef std::string (*InterpFunc)(ParameterSet &params,
                                    const std::string &paramName,
                                    Time t,
                                    Time t0,
                                    const std::string &v0,
                                    Time t1,
                                    const std::string &v1,
                                    double amount);
  
  template <InterpFunc F>
  static OfxStatus Interpolator(OfxParamSetHandle instance, OfxPropertySetHandle inArgs, OfxPropertySetHandle outArgs) {
    ParameterSet params(instance);
    PropertySet ia(inArgs);
    PropertySet oa(outArgs);
    try {
      std::string name = ia.getString(kOfxPropName, 0);
      Time ct = ia.getDouble(kOfxPropTime, 0);
      Time t0 = ia.getDouble(kOfxParamPropInterpolationTime, 0);
      Time t1 = ia.getDouble(kOfxParamPropInterpolationTime, 1);
      std::string v0 = ia.getString(kOfxParamPropCustomValue, 0);
      std::string v1 = ia.getString(kOfxParamPropCustomValue, 1);
      double amount = ia.getDouble(kOfxParamPropInterpolationAmount, 0);
      std::string rv = F(params, name, ct, t0, v0, t1, v1, amount);
      oa.setString(kOfxParamPropCustomValue, 0, rv);
      return kOfxStatOK;
    } catch (Exception &e) {
      return e.getStatus();
    }
  }
  
  
  class ParameterDescriptor : public PropertySet {
    public:
      
      ParameterDescriptor();
      ParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      ParameterDescriptor(const ParameterDescriptor &rhs);
      virtual ~ParameterDescriptor();
      
      ParameterDescriptor& operator=(const ParameterDescriptor &rhs);
      
      // properties
      
      std::string name();
      void setName(const std::string &name);
      
      std::string label();
      void setLabel(const std::string &lbl);
      
      std::string shortLabel();
      void setShortLabel(const std::string &lbl);
      
      std::string longLabel();
      void setLongLabel(const std::string &lbl);
      
      ParamType type();
      
      bool isSecret();
      void setSecret(bool);
      
      bool canUndo();
      void setCanUndo(bool);
      
      std::string hint();
      void setHint(const std::string &h);
      
      std::string scriptName();
      void setScriptName(const std::string &h);
      
      std::string parent();
      void setParent(const std::string &n);
      
      bool isEnable();
      void enable(bool);
      
      void* data();
      void setData(void *);
      
#ifdef OFX_API_1_2
      std::string PNGIcon();
      std::string SVGIcon();
      void setPNGIcon(const std::string &resPath);
      void setSVGIcon(const std::string &resPath);
#endif
  };
  
  class ValueParameterDescriptor : public ParameterDescriptor {
    public:
      
      ValueParameterDescriptor();
      ValueParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      ValueParameterDescriptor(const ValueParameterDescriptor &rhs);
      virtual ~ValueParameterDescriptor();
      
      ValueParameterDescriptor& operator=(const ValueParameterDescriptor &rhs);
      
      // properties
      
      EntryPoint interact();
      void setInteract(EntryPoint func);
      
      void interactSize(double &w, double &h);
      void setInteractSize(double w, double h);
      
      double interactSizeAspect();
      void setInteractSizeAspect(double a);
      
      void interactMinimumSize(int &w, int &h);
      void setMinimumInteractSize(int w, int h);
      
      void interactPreferedSize(int &w, int &h);
      void setInteractPreferedSize(int w, int h);
      
      bool isAnimateable();
      void setAnimateable(bool);
      
      bool isAnimating();
      void setAnimating(bool);
      
      bool isAutoKeying();
      void setAutoKeying(bool);
      
      bool isPersistant();
      void setPersistant(bool);
      
      bool evaluateOnChange();
      void setEvaluateOnChange(bool);
      
      bool pluginMayWrite();
      void setPluginMayWrite(bool);
      
      ParamInvalidate cacheInvalidation();
      void setCacheInvalidation(ParamInvalidate i);
      
#ifdef OFX_API_1_2
      bool hasHostOverlayHandle();
      
      bool useHostOverlayHandle();
      void setUseHostOverlayHandle(bool b);
#endif
  };
  
  class Parameter {
    protected:
      
      OfxParamHandle mHandle;
      PropertySet mProps;
      OfxParameterSuiteV1 *mSuite;
      
    public:
      
      Parameter();
      Parameter(Host *h, OfxParamHandle hdl) throw(Exception);
      Parameter(const Parameter &rhs);
      virtual ~Parameter();
      
      Parameter& operator=(const Parameter &rhs);
      
      inline OfxParamHandle handle() {
        return mHandle;
      }
      
      // properties
      
      std::string name();
      
      std::string label();
      void setLabel(const std::string &lbl);
      
      std::string shortLabel();
      void setShortLabel(const std::string &lbl);
      
      std::string longLabel();
      void setLongLabel(const std::string &lbl);
      
      ParamType type();
      
      bool isSecret();
      void setSecret(bool);
      
      bool canUndo();
      
      std::string hint();
      void setHint(const std::string &h);
      
      std::string scriptName();
      
      std::string parent();
      
      bool isEnable();
      void enable(bool);
      
      void* data();
      void setData(void *);
      
#ifdef OFX_API_1_2
      std::string PNGIcon();
      std::string SVGIcon();
#endif
      
      // suite
  };
  
  class ValueParameter : public Parameter {
    public:
      
      ValueParameter();
      ValueParameter(Host *h, OfxParamHandle hdl);
      ValueParameter(const ValueParameter &rhs);
      virtual ~ValueParameter();
      
      ValueParameter& operator=(const ValueParameter &rhs);
      
      // properties
      
      EntryPoint interact();
      
      void interactSize(double &w, double &h);
      
      double interactSizeAspect();
      
      void interactMinimumSize(int &w, int &h);
      
      void interactPreferedSize(int &w, int &h);
      
      bool isAnimateable();
      
      bool isAnimating();
      
      bool isAutoKeying();
      
      bool isPersistant();
      
      bool evaluateOnChange();
      
      bool pluginMayWrite();
      
      ParamInvalidate cacheInvalidation();
      
#ifdef OFX_API_1_2
      bool useHostOverlayHandle();
#endif
      
      // suite
      
      unsigned int getNumKeys() throw(Exception);
      
      Time getKeyTime(unsigned int nth) throw(Exception);
      
      int getKeyIndex(Time t, KeyDirection kd=KeyDirectionExact) throw(Exception);
      
      bool deleteKey(Time t) throw(Exception);
      
      void deleteAllKeys() throw(Exception);
      
      void copy(ValueParameter &from, Time offset, FrameRange *range=0) throw(Exception);
  };
  
}

#endif
