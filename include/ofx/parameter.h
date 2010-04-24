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

#include <ofxCore.h>
#include <ofxParam.h>
#include <ofx/ofx.h>
#include <ofx/exception.h>
#include <ofx/property.h>

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
      ParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      ParameterDescriptor(const ParameterDescriptor &rhs);
      virtual ~ParameterDescriptor();
      
      ParameterDescriptor& operator=(const ParameterDescriptor &rhs);
      
      // properties
      
      std::string name() throw(Exception);
      void setName(const std::string &name) throw(Exception);
      
      std::string label() throw(Exception);
      void setLabel(const std::string &lbl) throw(Exception);
      
      std::string shortLabel() throw(Exception);
      void setShortLabel(const std::string &lbl) throw(Exception);
      
      std::string longLabel() throw(Exception);
      void setLongLabel(const std::string &lbl) throw(Exception);
      
      ParamType type() throw(Exception);
      
      bool isSecret() throw(Exception);
      void setSecret(bool) throw(Exception);
      
      bool canUndo() throw(Exception);
      void setCanUndo(bool) throw(Exception);
      
      std::string hint() throw(Exception);
      void setHint(const std::string &h) throw(Exception);
      
      std::string scriptName() throw(Exception);
      void setScriptName(const std::string &h) throw(Exception);
      
      std::string parent() throw(Exception);
      void setParent(const std::string &n) throw(Exception);
      
      bool isEnable() throw(Exception);
      void enable(bool) throw(Exception);
      
      void* data() throw(Exception);
      void setData(void *) throw(Exception);
  };
  
  class ValueParameterDescriptor : public ParameterDescriptor {
    public:
      
      ValueParameterDescriptor();
      ValueParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      ValueParameterDescriptor(const ValueParameterDescriptor &rhs);
      virtual ~ValueParameterDescriptor();
      
      ValueParameterDescriptor& operator=(const ValueParameterDescriptor &rhs);
      
      // properties
      
      EntryPoint interact() throw(Exception);
      void setInteract(EntryPoint func) throw(Exception);
      
      void interactSize(double &w, double &h) throw(Exception);
      void setInteractSize(double w, double h) throw(Exception);
      
      double interactSizeAspect() throw(Exception);
      void setInteractSizeAspect(double a) throw(Exception);
      
      void interactMinimumSize(int &w, int &h) throw(Exception);
      void setMinimumInteractSize(int w, int h) throw(Exception);
      
      void interactPreferedSize(int &w, int &h) throw(Exception);
      void setInteractPreferedSize(int w, int h) throw(Exception);
      
      bool isAnimateable() throw(Exception);
      void setAnimateable(bool) throw(Exception);
      
      bool isAnimating() throw(Exception);
      void setAnimating(bool) throw(Exception);
      
      bool isAutoKeying() throw(Exception);
      void setAutoKeying(bool) throw(Exception);
      
      bool isPersistant() throw(Exception);
      void setPersistant(bool) throw(Exception);
      
      bool evaluateOnChange() throw(Exception);
      void setEvaluateOnChange(bool) throw(Exception);
      
      bool pluginMayWrite() throw(Exception);
      void setPluginMayWrite(bool) throw(Exception);
      
      ParamInvalidate cacheInvalidation() throw(Exception);
      void setCacheInvalidation(ParamInvalidate i) throw(Exception);
  };
  
  class IntParameterDescriptor : public ValueParameterDescriptor {
    public:
      IntParameterDescriptor();
      IntParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      IntParameterDescriptor(const IntParameterDescriptor &rhs);
      virtual ~IntParameterDescriptor();
      
      IntParameterDescriptor& operator=(const IntParameterDescriptor &rhs);
      
      // properties
      
      int getDefault() throw(Exception);
      void setDefault(int v) throw(Exception);
      
      int getMin() throw(Exception);
      void setMin(int v) throw(Exception);
      
      int getMax() throw(Exception);
      void setMax(int v) throw(Exception);
      
      int getDisplayMin() throw(Exception);
      void setDisplayMin(int v) throw(Exception);
      
      int getDisplayMax() throw(Exception);
      void setDisplayMax(int v) throw(Exception);
  };
  
  class Int2ParameterDescriptor : public ValueParameterDescriptor {
    public:
      Int2ParameterDescriptor();
      Int2ParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      Int2ParameterDescriptor(const Int2ParameterDescriptor &rhs);
      virtual ~Int2ParameterDescriptor();
      
      Int2ParameterDescriptor& operator=(const Int2ParameterDescriptor &rhs);
      
      // properties
      
      void getDefault(int &v0, int &v1) throw(Exception);
      void setDefault(int v0, int v1) throw(Exception);
      
      void getMin(int &min0, int &min1) throw(Exception);
      void setMin(int min0, int min1) throw(Exception);
      
      void getMax(int &max0, int &max1) throw(Exception);
      void setMax(int max0, int max1) throw(Exception);
      
      void getDisplayMin(int &min0, int &min1) throw(Exception);
      void setDisplayMin(int min0, int min1) throw(Exception);
      
      void getDisplayMax(int &max0, int &max1) throw(Exception);
      void setDisplayMax(int max0, int max1) throw(Exception);
      
      void setDimensionLabel(int i, const std::string &name) throw(Exception);
      std::string getDimensionLabel(int i) throw(Exception);
  };
  
  class Int3ParameterDescriptor : public ValueParameterDescriptor {
    public:
      Int3ParameterDescriptor();
      Int3ParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      Int3ParameterDescriptor(const Int3ParameterDescriptor &rhs);
      virtual ~Int3ParameterDescriptor();
      
      Int3ParameterDescriptor& operator=(const Int3ParameterDescriptor &rhs);
      
      // properties
      
      void getDefault(int &v0, int &v1, int &v2) throw(Exception);
      void setDefault(int v0, int v1, int v2) throw(Exception);
      
      void getMin(int &min0, int &min1, int &min2) throw(Exception);
      void setMin(int min0, int min1, int min2) throw(Exception);
      
      void getMax(int &max0, int &max1, int &max2) throw(Exception);
      void setMax(int max0, int max1, int max2) throw(Exception);
      
      void getDisplayMin(int &min0, int &min1, int &max2) throw(Exception);
      void setDisplayMin(int min0, int min1, int max2) throw(Exception);
      
      void getDisplayMax(int &max0, int &max1, int &max2) throw(Exception);
      void setDisplayMax(int max0, int max1, int max2) throw(Exception);
      
      void setDimensionLabel(int i, const std::string &name) throw(Exception);
      std::string getDimensionLabel(int i) throw(Exception);
  };
  
  class DoubleParameterDescriptor : public ValueParameterDescriptor {
    public:
      DoubleParameterDescriptor();
      DoubleParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      DoubleParameterDescriptor(const DoubleParameterDescriptor &rhs);
      virtual ~DoubleParameterDescriptor();
      
      DoubleParameterDescriptor& operator=(const DoubleParameterDescriptor &rhs);
      
      // properties
      
      double getDefault() throw(Exception);
      void setDefault(double v) throw(Exception);
      
      double getMin() throw(Exception);
      void setMin(double min0) throw(Exception);
      
      double getMax() throw(Exception);
      void setMax(double max0) throw(Exception);
      
      double getDisplayMin() throw(Exception);
      void setDisplayMin(double min0) throw(Exception);
      
      double getDisplayMax() throw(Exception);
      void setDisplayMax(double max0) throw(Exception);
      
      double increment() throw(Exception);
      void setIncrement(double i) throw(Exception);
      
      int digits() throw(Exception);
      void setDigits(int d) throw(Exception);
      
      bool showTimeMarker() throw(Exception);
      void setShowTimeMarker(bool) throw(Exception);
      
      DoubleParamType doubleType() throw(Exception);
      void setDoubleType(DoubleParamType t) throw(Exception);
  };
  
  class Double2ParameterDescriptor : public ValueParameterDescriptor {
    public:
      Double2ParameterDescriptor();
      Double2ParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      Double2ParameterDescriptor(const Double2ParameterDescriptor &rhs);
      virtual ~Double2ParameterDescriptor();
      
      Double2ParameterDescriptor& operator=(const Double2ParameterDescriptor &rhs);
      
      // properties
      
      void getDefault(double &v0, double &v1) throw(Exception);
      void setDefault(double v0, double v1) throw(Exception);
      
      void getMin(double &min0, double &min1) throw(Exception);
      void setMin(double min0, double min1) throw(Exception);
      
      void getMax(double &max0, double &max1) throw(Exception);
      void setMax(double max0, double max1) throw(Exception);
      
      void getDisplayMin(double &min0, double &min1) throw(Exception);
      void setDisplayMin(double min0, double min1) throw(Exception);
      
      void getDisplayMax(double &max0, double &max1) throw(Exception);
      void setDisplayMax(double max0, double max1) throw(Exception);
      
      double increment() throw(Exception);
      void setIncrement(double i) throw(Exception);
      
      int digits() throw(Exception);
      void setDigits(int d) throw(Exception);
      
      DoubleParamType doubleType() throw(Exception);
      void setDoubleType(DoubleParamType t) throw(Exception);
      
      void setDimensionLabel(int i, const std::string &name) throw(Exception);
      std::string getDimensionLabel(int i) throw(Exception);
  };
  
  class Double3ParameterDescriptor : public ValueParameterDescriptor {
    public:
      Double3ParameterDescriptor();
      Double3ParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      Double3ParameterDescriptor(const Double3ParameterDescriptor &rhs);
      virtual ~Double3ParameterDescriptor();
      
      Double3ParameterDescriptor& operator=(const Double3ParameterDescriptor &rhs);
      
      // properties
      
      void getDefault(double &v0, double &v1, double &v2) throw(Exception);
      void setDefault(double v0, double v1, double v2) throw(Exception);
      
      void getMin(double &min0, double &min1, double &min2) throw(Exception);
      void setMin(double min0, double min1, double min2) throw(Exception);
      
      void getMax(double &max0, double &max1, double &max2) throw(Exception);
      void setMax(double max0, double max1, double max2) throw(Exception);
      
      void getDisplayMin(double &min0, double &min1, double &max2) throw(Exception);
      void setDisplayMin(double min0, double min1, double max2) throw(Exception);
      
      void getDisplayMax(double &max0, double &max1, double &max2) throw(Exception);
      void setDisplayMax(double max0, double max1, double max2) throw(Exception);
      
      double increment() throw(Exception);
      void setIncrement(double i) throw(Exception);
      
      int digits() throw(Exception);
      void setDigits(int d) throw(Exception);
      
      DoubleParamType doubleType() throw(Exception);
      void setDoubleType(DoubleParamType t) throw(Exception);
      
      void setDimensionLabel(int i, const std::string &name) throw(Exception);
      std::string getDimensionLabel(int i) throw(Exception);
  };
  
  class ChoiceParameterDescriptor : public ValueParameterDescriptor {
    public:
      ChoiceParameterDescriptor();
      ChoiceParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      ChoiceParameterDescriptor(const ChoiceParameterDescriptor &rhs);
      virtual ~ChoiceParameterDescriptor();
      
      ChoiceParameterDescriptor& operator=(const ChoiceParameterDescriptor &rhs);
      
      // properties
      
      int getDefault() throw(Exception);
      void setDefault(int) throw(Exception);
      
      int getChoiceCount() throw(Exception);
      void setChoice(int i, const std::string &str) throw(Exception);
      std::string getChoice(int i) throw(Exception);
  };
  
  class StringParameterDescriptor : public ValueParameterDescriptor {
    public:
      StringParameterDescriptor();
      StringParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      StringParameterDescriptor(const StringParameterDescriptor &rhs);
      virtual ~StringParameterDescriptor();
      
      StringParameterDescriptor& operator=(const StringParameterDescriptor &rhs);
      
      // properties
      
      std::string getDefault() throw(Exception);
      void setDefault(const std::string &v) throw(Exception);
      
      StringParamMode mode() throw(Exception);
      void setMode(StringParamMode m) throw(Exception);
      
      bool filePathExists() throw(Exception);
      void setFilePathExists(bool) throw(Exception);
  };
  
  class CustomParameterDescriptor : public ValueParameterDescriptor {
    public:
      CustomParameterDescriptor();
      CustomParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      CustomParameterDescriptor(const CustomParameterDescriptor &rhs);
      virtual ~CustomParameterDescriptor();
      
      CustomParameterDescriptor& operator=(const CustomParameterDescriptor &rhs);
      
      // properties
      
      std::string getDefault() throw(Exception);
      void setDefault(const std::string &v) throw(Exception);
      
      template <InterpFunc F>
      void setInterpolator(InterpFunc func) throw(Exception) {
        setPointer(kOfxParamPropCustomInterpCallbackV1, 0, (void*) &Interpolator<InterpFunc>);
      }
      // no proper getter. cannot cast back from void* to Interpolator<func>
      void* getInterpolator() throw(Exception);
  };
  
  class PageParameterDescriptor : ParameterDescriptor {
    public:
      PageParameterDescriptor();
      PageParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      PageParameterDescriptor(const PageParameterDescriptor &rhs);
      virtual ~PageParameterDescriptor();
      
      PageParameterDescriptor& operator=(const PageParameterDescriptor &rhs);
      
      // properties
      
      // special string values:
      //   kOfxParamPageSkipRow
      //   kOfxParamPageSkipColumn
      int getChildCount() throw(Exception);
      void setChild(int i, const std::string &name) throw(Exception);
      std::string getChild(int i) throw(Exception);
  };
  
  class BooleanParameterDescriptor : public ValueParameterDescriptor {
    public:
      BooleanParameterDescriptor();
      BooleanParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      BooleanParameterDescriptor(const BooleanParameterDescriptor &rhs);
      virtual ~BooleanParameterDescriptor();
      
      BooleanParameterDescriptor& operator=(const BooleanParameterDescriptor &rhs);
      
      // properties
      
      bool getDefault() throw(Exception);
      void setDefault(bool v) throw(Exception);
  };
  
  class RGBParameterDescriptor : public ValueParameterDescriptor {
    public:
      RGBParameterDescriptor();
      RGBParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      RGBParameterDescriptor(const RGBParameterDescriptor &rhs);
      virtual ~RGBParameterDescriptor();
      
      RGBParameterDescriptor& operator=(const RGBParameterDescriptor &rhs);
      
      // properties
      
      RGBAColour<double> getDefault() throw(Exception);
      void setDefault(const RGBAColour<double> &v) throw(Exception);
  };
  
  class RGBAParameterDescriptor : public ValueParameterDescriptor {
    public:
      RGBAParameterDescriptor();
      RGBAParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      RGBAParameterDescriptor(const RGBAParameterDescriptor &rhs);
      virtual ~RGBAParameterDescriptor();
      
      RGBAParameterDescriptor& operator=(const RGBAParameterDescriptor &rhs);
      
      // properties
      
      RGBAColour<double> getDefault() throw(Exception);
      void setDefault(const RGBAColour<double> &v) throw(Exception);
  };
  
  class PushButtonParameterDescriptor : public ParameterDescriptor {
    public:
      PushButtonParameterDescriptor();
      PushButtonParameterDescriptor(Host *h, OfxPropertySetHandle hdl) throw(Exception);
      PushButtonParameterDescriptor(const PushButtonParameterDescriptor &rhs);
      virtual ~PushButtonParameterDescriptor();
      
      PushButtonParameterDescriptor& operator=(const PushButtonParameterDescriptor &rhs);
      
      // properties
      
      EntryPoint interact() throw(Exception);
      void setInteract(EntryPoint func) throw(Exception);
      
      void interactSize(double &w, double &h) throw(Exception);
      void setInteractSize(double w, double h) throw(Exception);
      
      double interactSizeAspect() throw(Exception);
      void setInteractSizeAspect(double a) throw(Exception);
      
      void interactMinimumSize(int &w, int &h) throw(Exception);
      void setMinimumInteractSize(int w, int h) throw(Exception);
      
      void interactPreferedSize(int &w, int &h) throw(Exception);
      void setInteractPreferedSize(int w, int h) throw(Exception);
  };
  
  typedef ParameterDescriptor GroupParameterDescriptor;
  
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
      
      std::string name() throw(Exception);
      
      std::string label() throw(Exception);
      void setLabel(const std::string &lbl) throw(Exception);
      
      std::string shortLabel() throw(Exception);
      void setShortLabel(const std::string &lbl) throw(Exception);
      
      std::string longLabel() throw(Exception);
      void setLongLabel(const std::string &lbl) throw(Exception);
      
      ParamType type() throw(Exception);
      
      bool isSecret() throw(Exception);
      void setSecret(bool) throw(Exception);
      
      bool canUndo() throw(Exception);
      
      std::string hint() throw(Exception);
      void setHint(const std::string &h) throw(Exception);
      
      std::string scriptName() throw(Exception);
      
      std::string parent() throw(Exception);
      
      bool isEnable() throw(Exception);
      void enable(bool) throw(Exception);
      
      void* data() throw(Exception);
      void setData(void *) throw(Exception);
      
      // suite
  };
  
  class ValueParameter : public Parameter {
    public:
      
      ValueParameter();
      ValueParameter(Host *h, OfxParamHandle hdl) throw(Exception);
      ValueParameter(const ValueParameter &rhs);
      virtual ~ValueParameter();
      
      ValueParameter& operator=(const ValueParameter &rhs);
      
      // properties
      
      EntryPoint interact() throw(Exception);
      
      void interactSize(double &w, double &h) throw(Exception);
      
      double interactSizeAspect() throw(Exception);
      
      void interactMinimumSize(int &w, int &h) throw(Exception);
      
      void interactPreferedSize(int &w, int &h) throw(Exception);
      
      bool isAnimateable() throw(Exception);
      
      bool isAnimating() throw(Exception);
      
      bool isAutoKeying() throw(Exception);
      
      bool isPersistant() throw(Exception);
      
      bool evaluateOnChange() throw(Exception);
      
      bool pluginMayWrite() throw(Exception);
      
      ParamInvalidate cacheInvalidation() throw(Exception);
      
      // suite
      
      unsigned int getNumKeys() throw(Exception);
      
      Time getKeyTime(unsigned int nth) throw(Exception);
      
      int getKeyIndex(Time t, KeyDirection kd=KeyDirectionExact) throw(Exception);
      
      bool deleteKey(Time t) throw(Exception);
      
      void deleteAllKeys() throw(Exception);
      
      void copy(ValueParameter &from, Time offset, FrameRange *range=0) throw(Exception);
  };
  
  class IntParameter : public ValueParameter {
    public:
      IntParameter();
      IntParameter(Host *h, OfxParamHandle hdl) throw(Exception);
      IntParameter(const IntParameter &rhs);
      virtual ~IntParameter();
      
      IntParameter& operator=(const IntParameter &rhs);
      
      // properties
      
      int getDefault() throw(Exception);
      
      int getMin() throw(Exception);
      void setMin(int v) throw(Exception);
      
      int getMax() throw(Exception);
      void setMax(int v) throw(Exception);
      
      int getDisplayMin() throw(Exception);
      void setDisplayMin(int v) throw(Exception);
      
      int getDisplayMax() throw(Exception);
      void setDisplayMax(int v) throw(Exception);
      
      // suite
      
      int getValue() throw(Exception);
      int getValueAtTime(Time t) throw(Exception);
      int getDerivative(Time t) throw(Exception);
      int getIntegral(Time t0, Time t1) throw(Exception);
      
      void setValue(int v) throw(Exception);
      void setValueAtTime(Time t, int v) throw(Exception);
  };
  
  class Int2Parameter : public ValueParameter {
    public:
      Int2Parameter();
      Int2Parameter(Host *h, OfxParamHandle hdl) throw(Exception);
      Int2Parameter(const Int2Parameter &rhs);
      virtual ~Int2Parameter();
      
      Int2Parameter& operator=(const Int2Parameter &rhs);
      
      // properties
      
      void getDefault(int &v0, int &v1) throw(Exception);
      
      void getMin(int &min0, int &min1) throw(Exception);
      void setMin(int min0, int min1) throw(Exception);
      
      void getMax(int &max0, int &max1) throw(Exception);
      void setMax(int max0, int max1) throw(Exception);
      
      void getDisplayMin(int &min0, int &min1) throw(Exception);
      void setDisplayMin(int min0, int min1) throw(Exception);
      
      void getDisplayMax(int &max0, int &max1) throw(Exception);
      void setDisplayMax(int max0, int max1) throw(Exception);
      
      std::string getDimensionLabel(int i) throw(Exception);
      
      // suite
      
      void getValue(int &v0, int &v1) throw(Exception);
      void getValueAtTime(Time t, int &v0, int &v1) throw(Exception);
      void getDerivative(Time t, int &v0, int &v1) throw(Exception);
      void getIntegral(Time t0, Time t1, int &v0, int &v1) throw(Exception);
      
      void setValue(int v0, int v1) throw(Exception);
      void setValueAtTime(Time t, int v0, int v1) throw(Exception);
  };
  
  class Int3Parameter : public ValueParameter {
    public:
      Int3Parameter();
      Int3Parameter(Host *h, OfxParamHandle hdl) throw(Exception);
      Int3Parameter(const Int3Parameter &rhs);
      virtual ~Int3Parameter();
      
      Int3Parameter& operator=(const Int3Parameter &rhs);
      
      // properties
      
      void getDefault(int &v0, int &v1, int &v2) throw(Exception);
      
      void getMin(int &min0, int &min1, int &min2) throw(Exception);
      void setMin(int min0, int min1, int min2) throw(Exception);
      
      void getMax(int &max0, int &max1, int &max2) throw(Exception);
      void setMax(int max0, int max1, int max2) throw(Exception);
      
      void getDisplayMin(int &min0, int &min1, int &max2) throw(Exception);
      void setDisplayMin(int min0, int min1, int max2) throw(Exception);
      
      void getDisplayMax(int &max0, int &max1, int &max2) throw(Exception);
      void setDisplayMax(int max0, int max1, int max2) throw(Exception);
      
      std::string getDimensionLabel(int i) throw(Exception);
      
      // suite
      
      void getValue(int &v0, int &v1, int &v2) throw(Exception);
      void getValueAtTime(Time t, int &v0, int &v1, int &v2) throw(Exception);
      void getDerivative(Time t, int &v0, int &v1, int &v2) throw(Exception);
      void getIntegral(Time t0, Time t1, int &v0, int &v1, int &v2) throw(Exception);
      
      void setValue(int v0, int v1, int v2) throw(Exception);
      void setValueAtTime(Time t, int v0, int v1, int v2) throw(Exception);
  };
  
  class DoubleParameter : public ValueParameter {
    public:
      DoubleParameter();
      DoubleParameter(Host *h, OfxParamHandle hdl) throw(Exception);
      DoubleParameter(const DoubleParameter &rhs);
      virtual ~DoubleParameter();
      
      DoubleParameter& operator=(const DoubleParameter &rhs);
      
      // properties
      
      double getDefault() throw(Exception);
      
      double getMin() throw(Exception);
      void setMin(double min0) throw(Exception);
      
      double getMax() throw(Exception);
      void setMax(double max0) throw(Exception);
      
      double getDisplayMin() throw(Exception);
      void setDisplayMin(double min0) throw(Exception);
      
      double getDisplayMax() throw(Exception);
      void setDisplayMax(double max0) throw(Exception);
      
      double increment() throw(Exception);
      void setIncrement(double i) throw(Exception);
      
      int digits() throw(Exception);
      void setDigits(int d) throw(Exception);
      
      bool showTimeMarker() throw(Exception);
      void setShowTimeMarker(bool) throw(Exception);
      
      DoubleParamType doubleType() throw(Exception);
      
      // suite
      
      double getValue() throw(Exception);
      double getValueAtTime(Time t) throw(Exception);
      double getDerivative(Time t) throw(Exception);
      double getIntegral(Time t0, Time t1) throw(Exception);
      
      void setValue(double v0) throw(Exception);
      void setValueAtTime(Time t, double v0) throw(Exception);
  };
  
  class Double2Parameter : public ValueParameter {
    public:
      Double2Parameter();
      Double2Parameter(Host *h, OfxParamHandle hdl) throw(Exception);
      Double2Parameter(const Double2Parameter &rhs);
      virtual ~Double2Parameter();
      
      Double2Parameter& operator=(const Double2Parameter &rhs);
      
      // properties
      
      void getDefault(double &v0, double &v1) throw(Exception);
      
      void getMin(double &min0, double &min1) throw(Exception);
      void setMin(double min0, double min1) throw(Exception);
      
      void getMax(double &max0, double &max1) throw(Exception);
      void setMax(double max0, double max1) throw(Exception);
      
      void getDisplayMin(double &min0, double &min1) throw(Exception);
      void setDisplayMin(double min0, double min1) throw(Exception);
      
      void getDisplayMax(double &max0, double &max1) throw(Exception);
      void setDisplayMax(double max0, double max1) throw(Exception);
      
      double increment() throw(Exception);
      void setIncrement(double i) throw(Exception);
      
      int digits() throw(Exception);
      void setDigits(int d) throw(Exception);
      
      DoubleParamType doubleType() throw(Exception);
      
      std::string getDimensionLabel(int i) throw(Exception);
      
      // suite
      
      void getValue(double &v0, double &v1) throw(Exception);
      void getValueAtTime(Time t, double &v0, double &v1) throw(Exception);
      void getDerivative(Time t, double &v0, double &v1) throw(Exception);
      void getIntegral(Time t0, Time t1, double &v0, double &v1) throw(Exception);
      
      void setValue(double v0, double v1) throw(Exception);
      void setValueAtTime(Time t, double v0, double v1) throw(Exception);
  };
  
  class Double3Parameter : public ValueParameter {
    public:
      Double3Parameter();
      Double3Parameter(Host *h, OfxParamHandle hdl) throw(Exception);
      Double3Parameter(const Double3Parameter &rhs);
      virtual ~Double3Parameter();
      
      Double3Parameter& operator=(const Double3Parameter &rhs);
      
      // properties
      
      void getDefault(double &v0, double &v1, double &v2) throw(Exception);
      
      void getMin(double &min0, double &min1, double &min2) throw(Exception);
      void setMin(double min0, double min1, double min2) throw(Exception);
      
      void getMax(double &max0, double &max1, double &max2) throw(Exception);
      void setMax(double max0, double max1, double max2) throw(Exception);
      
      void getDisplayMin(double &min0, double &min1, double &max2) throw(Exception);
      void setDisplayMin(double min0, double min1, double max2) throw(Exception);
      
      void getDisplayMax(double &max0, double &max1, double &max2) throw(Exception);
      void setDisplayMax(double max0, double max1, double max2) throw(Exception);
      
      double increment() throw(Exception);
      void setIncrement(double i) throw(Exception);
      
      int digits() throw(Exception);
      void setDigits(int d) throw(Exception);
      
      DoubleParamType doubleType() throw(Exception);
      
      std::string getDimensionLabel(int i) throw(Exception);
      
      // suite
      
      void getValue(double &v0, double &v1, double &v2) throw(Exception);
      void getValueAtTime(Time t, double &v0, double &v1, double &v2) throw(Exception);
      void getDerivative(Time t, double &v0, double &v1, double &v2) throw(Exception);
      void getIntegral(Time t0, Time t1, double &v0, double &v1, double &v2) throw(Exception);
      
      void setValue(double v0, double v1, double v2) throw(Exception);
      void setValueAtTime(Time t, double v0, double v1, double v2) throw(Exception);
  };
  
  class StringParameter : public ValueParameter {
    public:
      StringParameter();
      StringParameter(Host *h, OfxParamHandle hdl) throw(Exception);
      StringParameter(const StringParameter &rhs);
      virtual ~StringParameter();
      
      StringParameter& operator=(const StringParameter &rhs);
      
      // properties
      
      std::string getDefault() throw(Exception);
      
      StringParamMode mode() throw(Exception);
      
      bool filePathExists() throw(Exception);
      
      // suite
      
      std::string getValue() throw(Exception);
      std::string getValueAtTime(Time t) throw(Exception);
      
      void setValue(const std::string &v) throw(Exception);
      void setValueAtTime(Time t, const std::string &v) throw(Exception);
  };
  
  class CustomParameter : public ValueParameter {
    public:
      CustomParameter();
      CustomParameter(Host *h, OfxParamHandle hdl) throw(Exception);
      CustomParameter(const CustomParameter &rhs);
      virtual ~CustomParameter();
      
      CustomParameter& operator=(const CustomParameter &rhs);
      
      // properties
      
      std::string getDefault() throw(Exception);
      
      void* getInterpolator() throw(Exception);
      
      // suite
      
      std::string getValue() throw(Exception);
      std::string getValueAtTime(Time t) throw(Exception);
      
      void setValue(const std::string &v) throw(Exception);
      void setValueAtTime(Time t, const std::string &v) throw(Exception);
  };
  
  class BooleanParameter : public ValueParameter {
    public:
      BooleanParameter();
      BooleanParameter(Host *h, OfxParamHandle hdl) throw(Exception);
      BooleanParameter(const BooleanParameter &rhs);
      virtual ~BooleanParameter();
      
      BooleanParameter& operator=(const BooleanParameter &rhs);
      
      // properties
      
      bool getDefault() throw(Exception);
      
      // suite
      
      bool getValue() throw(Exception);
      bool getValueAtTime(Time t) throw(Exception);
      
      void setValue(bool v) throw(Exception);
      void setValueAtTime(Time t, bool v) throw(Exception);
  };
  
  class RGBParameter : public ValueParameter {
    public:
      RGBParameter();
      RGBParameter(Host *h, OfxParamHandle hdl) throw(Exception);
      RGBParameter(const RGBParameter &rhs);
      virtual ~RGBParameter();
      
      RGBParameter& operator=(const RGBParameter &rhs);
      
      // properties
      
      RGBAColour<double> getDefault() throw(Exception);
      
      // suite
      
      RGBAColour<double> getValue() throw(Exception);
      RGBAColour<double> getValueAtTime(Time t) throw(Exception);
      RGBAColour<double> getDerivative(Time t) throw(Exception);
      RGBAColour<double> getIntegral(Time t0, Time t1) throw(Exception);
      
      void setValue(const RGBAColour<double> &v) throw(Exception);
      void setValueAtTime(Time t, const RGBAColour<double> &v) throw(Exception);
  };
  
  class RGBAParameter : public ValueParameter {
    public:
      RGBAParameter();
      RGBAParameter(Host *h, OfxParamHandle hdl) throw(Exception);
      RGBAParameter(const RGBAParameter &rhs);
      virtual ~RGBAParameter();
      
      RGBAParameter& operator=(const RGBAParameter &rhs);
      
      // properties
      
      RGBAColour<double> getDefault() throw(Exception);
      
      // suite
      
      RGBAColour<double> getValue() throw(Exception);
      RGBAColour<double> getValueAtTime(Time t) throw(Exception);
      RGBAColour<double> getDerivative(Time t) throw(Exception);
      RGBAColour<double> getIntegral(Time t0, Time t1) throw(Exception);
      
      void setValue(const RGBAColour<double> &v) throw(Exception);
      void setValueAtTime(Time t, const RGBAColour<double> &v) throw(Exception);
  };
  
  class ChoiceParameter : public ValueParameter {
    public:
      ChoiceParameter();
      ChoiceParameter(Host *h, OfxParamHandle hdl) throw(Exception);
      ChoiceParameter(const ChoiceParameter &rhs);
      virtual ~ChoiceParameter();
      
      ChoiceParameter& operator=(const ChoiceParameter &rhs);
      
      // properties
      
      int getDefault() throw(Exception);
      
      int getChoiceCount() throw(Exception);
      void setChoice(int i, const std::string &str) throw(Exception);
      std::string getChoice(int i) throw(Exception);
      
      // suite
      
      int getValue() throw(Exception);
      int getValueAtTime(Time t) throw(Exception);
      
      void setValue(int v) throw(Exception);
      void setValueAtTime(Time t, int v) throw(Exception);
  };
  
  class PageParameter : public Parameter {
    public:
      PageParameter();
      PageParameter(Host *h, OfxParamHandle hdl) throw(Exception);
      PageParameter(const PageParameter &rhs);
      virtual ~PageParameter();
      
      PageParameter& operator=(const PageParameter &rhs);
      
      // properties
      
      int getChildCount() throw(Exception);
      std::string getChild(int i) throw(Exception);
  };
  
  class PushButtonParameter : public Parameter {
    public:
      
      PushButtonParameter();
      PushButtonParameter(Host *h, OfxParamHandle hdl) throw(Exception);
      PushButtonParameter(const PushButtonParameter &rhs);
      virtual ~PushButtonParameter();
      
      PushButtonParameter& operator=(const PushButtonParameter &rhs);
      
      // properties
      
      EntryPoint interact() throw(Exception);
      
      void interactSize(double &w, double &h) throw(Exception);
      
      double interactSizeAspect() throw(Exception);
      
      void interactMinimumSize(int &w, int &h) throw(Exception);
      
      void interactPreferedSize(int &w, int &h) throw(Exception);
  };
  
  typedef Parameter GroupParameter;
  
  // ---
  
  class ParameterSetDescriptor {
    protected:
      
      OfxParamSetHandle mHandle;
      PropertySet mProps;
      Host *mHost;
    
    public:
      
      ParameterSetDescriptor();
      ParameterSetDescriptor(Host *h, OfxParamSetHandle hdl) throw(Exception);
      ParameterSetDescriptor(const ParameterSetDescriptor &rhs);
      ~ParameterSetDescriptor();
      
      ParameterSetDescriptor& operator=(const ParameterSetDescriptor &rhs);
      
      inline Host* host() {
        return mHost;
      }
      
      // properties
      
      // suite
      
      IntParameterDescriptor defineIntParam(const std::string &name) throw(Exception);
      Int2ParameterDescriptor defineInt2Param(const std::string &name) throw(Exception);
      Int3ParameterDescriptor defineInt3Param(const std::string &name) throw(Exception);
      DoubleParameterDescriptor defineDoubleParam(const std::string &name) throw(Exception);
      Double2ParameterDescriptor defineDouble2Param(const std::string &name) throw(Exception);
      Double3ParameterDescriptor defineDouble3Param(const std::string &name) throw(Exception);
      RGBParameterDescriptor defineRGBParam(const std::string &name) throw(Exception);
      RGBAParameterDescriptor defineRGBAParam(const std::string &name) throw(Exception);
      BooleanParameterDescriptor defineBooleanParam(const std::string &name) throw(Exception);
      ChoiceParameterDescriptor defineChoiceParam(const std::string &name) throw(Exception);
      StringParameterDescriptor defineStringParam(const std::string &name) throw(Exception);
      CustomParameterDescriptor defineCustomParam(const std::string &name) throw(Exception);
      GroupParameterDescriptor defineGroupParam(const std::string &name) throw(Exception);
      PageParameterDescriptor definePageParam(const std::string &name) throw(Exception);
      PushButtonParameterDescriptor definePushButtonParam(const std::string &name) throw(Exception);
  };
  
  class ParameterSet {
    protected:
      
      OfxParamSetHandle mHandle;
      PropertySet mProps;
      Host *mHost;
    
    public:
      
      ParameterSet();
      ParameterSet(Host *h, OfxParamSetHandle hdl) throw(Exception);
      ParameterSet(const ParameterSet &rhs);
      ~ParameterSet();
      
      ParameterSet& operator=(const ParameterSet &rhs);
      
      inline Host* host() {
        return mHost;
      }
      
      // properties
      
      // suite
      
      IntParameter getIntParam(const std::string &name) throw(Exception);
      Int2Parameter getInt2Param(const std::string &name) throw(Exception);
      Int3Parameter getInt3Param(const std::string &name) throw(Exception);
      DoubleParameter getDoubleParam(const std::string &name) throw(Exception);
      Double2Parameter getDouble2Param(const std::string &name) throw(Exception);
      Double3Parameter getDouble3Param(const std::string &name) throw(Exception);
      RGBParameter getRGBParam(const std::string &name) throw(Exception);
      RGBAParameter getRGBAParam(const std::string &name) throw(Exception);
      BooleanParameter getBooleanParam(const std::string &name) throw(Exception);
      ChoiceParameter getChoiceParam(const std::string &name) throw(Exception);
      StringParameter getStringParam(const std::string &name) throw(Exception);
      CustomParameter getCustomParam(const std::string &name) throw(Exception);
      GroupParameter getGroupParam(const std::string &name) throw(Exception);
      PageParameter getPageParam(const std::string &name) throw(Exception);
      PushButtonParameter getPushButtonParam(const std::string &name) throw(Exception);
      
      void beginEdit(const std::string &label) throw(Exception);
      void endEdit() throw(Exception);
  };
  
}

#endif
