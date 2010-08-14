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
#include <ofx/host.h>
#include <ofxParam.h>

typedef OfxStatus (*OfxInterpFunc)(OfxParamSetHandle instance,
                                   OfxPropertySetHandle inArgs,
                                   OfxPropertySetHandle outArgs);

namespace ofx {
  
  //class Host;
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
  OfxStatus InterpFuncWrap(OfxParamSetHandle instance, OfxPropertySetHandle inArgs, OfxPropertySetHandle outArgs) {
    
    Host *host = Host::Get();
    
    if (!host) {
      return kOfxStatFailed;
    }
    
    ParameterSet params(host, instance);
    PropertySet ia(host, inArgs);
    PropertySet oa(host, outArgs);
    
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
      return e.status();
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
      void name(const std::string &name);
      
      std::string label();
      void label(const std::string &lbl);
      
      std::string shortLabel();
      void shortLabel(const std::string &lbl);
      
      std::string longLabel();
      void longLabel(const std::string &lbl);
      
      ParamType type();
      
      bool secret();
      void secret(bool);
      
      bool canUndo();
      void canUndo(bool);
      
      std::string hint();
      void hint(const std::string &h);
      
      std::string scriptName();
      void scriptName(const std::string &h);
      
      std::string parent();
      void parent(const std::string &n);
      
      bool enabled();
      void enabled(bool);
      
      //void* data();
      //void data(void *);
      
#ifdef OFX_API_1_2
      
      std::string PNGIcon();
      std::string SVGIcon();
      void PNGIcon(const std::string &resPath);
      void SVGIcon(const std::string &resPath);
      
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
      void interact(EntryPoint func);
      
      //void interactSize(double &w, double &h);
      //void interactSize(double w, double h);
      
      double interactSizeAspect();
      void interactSizeAspect(double a);
      
      void interactMinimumSize(int *w, int *h);
      void interactMinimumSize(int w, int h);
      
      void interactPreferedSize(int *w, int *h);
      void interactPreferedSize(int w, int h);
      
      bool animates();
      void animates(bool);
      
      //bool animating();
      //void animating(bool);
      
      //bool autoKeying();
      //void autoKeying(bool);
      
      bool persistant();
      void persistant(bool);
      
      bool evaluateOnChange();
      void evaluateOnChange(bool);
      
      bool pluginMayWrite();
      void pluginMayWrite(bool);
      
      ParamInvalidate cacheInvalidation();
      void cacheInvalidation(ParamInvalidate i);
      
#ifdef OFX_API_1_2
      
      bool hasHostOverlayHandle();
      
      bool useHostOverlayHandle();
      void useHostOverlayHandle(bool b);
      
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
      
      inline PropertySet& properties() {
        return mProps;
      }
      
      // properties
      
      std::string name();
      
      std::string label();
      void label(const std::string &lbl);
      
      std::string shortLabel();
      void shortLabel(const std::string &lbl);
      
      std::string longLabel();
      void longLabel(const std::string &lbl);
      
      ParamType type();
      
      bool secret();
      void secret(bool);
      
      bool canUndo();
      
      std::string hint();
      void hint(const std::string &h);
      
      std::string scriptName();
      
      std::string parent();
      
      bool enabled();
      void enabled(bool);
      
      void* data();
      void data(void *);
      
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
      
      void interactSize(double *w, double *h);
      
      double interactSizeAspect();
      
      void interactMinimumSize(int *w, int *h);
      
      void interactPreferedSize(int *w, int *h);
      
      bool animates();
      
      bool animating();
      
      bool autoKeying();
      
      bool persistant();
      
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
