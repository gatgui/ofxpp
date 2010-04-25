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
  };
  
  class IntParameterDescriptor : public ValueParameterDescriptor {
    public:
      IntParameterDescriptor();
      IntParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      IntParameterDescriptor(const IntParameterDescriptor &rhs);
      virtual ~IntParameterDescriptor();
      
      IntParameterDescriptor& operator=(const IntParameterDescriptor &rhs);
      
      // properties
      
      int getDefault();
      void setDefault(int v);
      
      int getMin();
      void setMin(int v);
      
      int getMax();
      void setMax(int v);
      
      int getDisplayMin();
      void setDisplayMin(int v);
      
      int getDisplayMax();
      void setDisplayMax(int v);
  };
  
  class Int2ParameterDescriptor : public ValueParameterDescriptor {
    public:
      Int2ParameterDescriptor();
      Int2ParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      Int2ParameterDescriptor(const Int2ParameterDescriptor &rhs);
      virtual ~Int2ParameterDescriptor();
      
      Int2ParameterDescriptor& operator=(const Int2ParameterDescriptor &rhs);
      
      // properties
      
      void getDefault(int &v0, int &v1);
      void setDefault(int v0, int v1);
      
      void getMin(int &min0, int &min1);
      void setMin(int min0, int min1);
      
      void getMax(int &max0, int &max1);
      void setMax(int max0, int max1);
      
      void getDisplayMin(int &min0, int &min1);
      void setDisplayMin(int min0, int min1);
      
      void getDisplayMax(int &max0, int &max1);
      void setDisplayMax(int max0, int max1);
      
      void setDimensionLabel(int i, const std::string &name);
      std::string getDimensionLabel(int i);
  };
  
  class Int3ParameterDescriptor : public ValueParameterDescriptor {
    public:
      Int3ParameterDescriptor();
      Int3ParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      Int3ParameterDescriptor(const Int3ParameterDescriptor &rhs);
      virtual ~Int3ParameterDescriptor();
      
      Int3ParameterDescriptor& operator=(const Int3ParameterDescriptor &rhs);
      
      // properties
      
      void getDefault(int &v0, int &v1, int &v2);
      void setDefault(int v0, int v1, int v2);
      
      void getMin(int &min0, int &min1, int &min2);
      void setMin(int min0, int min1, int min2);
      
      void getMax(int &max0, int &max1, int &max2);
      void setMax(int max0, int max1, int max2);
      
      void getDisplayMin(int &min0, int &min1, int &max2);
      void setDisplayMin(int min0, int min1, int max2);
      
      void getDisplayMax(int &max0, int &max1, int &max2);
      void setDisplayMax(int max0, int max1, int max2);
      
      void setDimensionLabel(int i, const std::string &name);
      std::string getDimensionLabel(int i);
  };
  
  class DoubleParameterDescriptor : public ValueParameterDescriptor {
    public:
      DoubleParameterDescriptor();
      DoubleParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      DoubleParameterDescriptor(const DoubleParameterDescriptor &rhs);
      virtual ~DoubleParameterDescriptor();
      
      DoubleParameterDescriptor& operator=(const DoubleParameterDescriptor &rhs);
      
      // properties
      
      double getDefault();
      void setDefault(double v);
      
      double getMin();
      void setMin(double min0);
      
      double getMax();
      void setMax(double max0);
      
      double getDisplayMin();
      void setDisplayMin(double min0);
      
      double getDisplayMax();
      void setDisplayMax(double max0);
      
      double increment();
      void setIncrement(double i);
      
      int digits();
      void setDigits(int d);
      
      bool showTimeMarker();
      void setShowTimeMarker(bool);
      
      DoubleParamType doubleType();
      void setDoubleType(DoubleParamType t);
  };
  
  class Double2ParameterDescriptor : public ValueParameterDescriptor {
    public:
      Double2ParameterDescriptor();
      Double2ParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      Double2ParameterDescriptor(const Double2ParameterDescriptor &rhs);
      virtual ~Double2ParameterDescriptor();
      
      Double2ParameterDescriptor& operator=(const Double2ParameterDescriptor &rhs);
      
      // properties
      
      void getDefault(double &v0, double &v1);
      void setDefault(double v0, double v1);
      
      void getMin(double &min0, double &min1);
      void setMin(double min0, double min1);
      
      void getMax(double &max0, double &max1);
      void setMax(double max0, double max1);
      
      void getDisplayMin(double &min0, double &min1);
      void setDisplayMin(double min0, double min1);
      
      void getDisplayMax(double &max0, double &max1);
      void setDisplayMax(double max0, double max1);
      
      double increment();
      void setIncrement(double i);
      
      int digits();
      void setDigits(int d);
      
      DoubleParamType doubleType();
      void setDoubleType(DoubleParamType t);
      
      void setDimensionLabel(int i, const std::string &name);
      std::string getDimensionLabel(int i);
  };
  
  class Double3ParameterDescriptor : public ValueParameterDescriptor {
    public:
      Double3ParameterDescriptor();
      Double3ParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      Double3ParameterDescriptor(const Double3ParameterDescriptor &rhs);
      virtual ~Double3ParameterDescriptor();
      
      Double3ParameterDescriptor& operator=(const Double3ParameterDescriptor &rhs);
      
      // properties
      
      void getDefault(double &v0, double &v1, double &v2);
      void setDefault(double v0, double v1, double v2);
      
      void getMin(double &min0, double &min1, double &min2);
      void setMin(double min0, double min1, double min2);
      
      void getMax(double &max0, double &max1, double &max2);
      void setMax(double max0, double max1, double max2);
      
      void getDisplayMin(double &min0, double &min1, double &max2);
      void setDisplayMin(double min0, double min1, double max2);
      
      void getDisplayMax(double &max0, double &max1, double &max2);
      void setDisplayMax(double max0, double max1, double max2);
      
      double increment();
      void setIncrement(double i);
      
      int digits();
      void setDigits(int d);
      
      DoubleParamType doubleType();
      void setDoubleType(DoubleParamType t);
      
      void setDimensionLabel(int i, const std::string &name);
      std::string getDimensionLabel(int i);
  };
  
  class ChoiceParameterDescriptor : public ValueParameterDescriptor {
    public:
      ChoiceParameterDescriptor();
      ChoiceParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      ChoiceParameterDescriptor(const ChoiceParameterDescriptor &rhs);
      virtual ~ChoiceParameterDescriptor();
      
      ChoiceParameterDescriptor& operator=(const ChoiceParameterDescriptor &rhs);
      
      // properties
      
      int getDefault();
      void setDefault(int);
      
      int getChoiceCount();
      void setChoice(int i, const std::string &str);
      std::string getChoice(int i);
  };
  
  class StringParameterDescriptor : public ValueParameterDescriptor {
    public:
      StringParameterDescriptor();
      StringParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      StringParameterDescriptor(const StringParameterDescriptor &rhs);
      virtual ~StringParameterDescriptor();
      
      StringParameterDescriptor& operator=(const StringParameterDescriptor &rhs);
      
      // properties
      
      std::string getDefault();
      void setDefault(const std::string &v);
      
      StringParamMode mode();
      void setMode(StringParamMode m);
      
      bool filePathExists();
      void setFilePathExists(bool);
  };
  
  class CustomParameterDescriptor : public ValueParameterDescriptor {
    public:
      CustomParameterDescriptor();
      CustomParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      CustomParameterDescriptor(const CustomParameterDescriptor &rhs);
      virtual ~CustomParameterDescriptor();
      
      CustomParameterDescriptor& operator=(const CustomParameterDescriptor &rhs);
      
      // properties
      
      std::string getDefault();
      void setDefault(const std::string &v);
      
      template <InterpFunc F>
      void setInterpolator(InterpFunc func) {
        setPointer(kOfxParamPropCustomInterpCallbackV1, 0, (void*) &Interpolator<InterpFunc>);
      }
      // no proper getter. cannot cast back from void* to Interpolator<func>
      void* getInterpolator();
  };
  
  class PageParameterDescriptor : ParameterDescriptor {
    public:
      PageParameterDescriptor();
      PageParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      PageParameterDescriptor(const PageParameterDescriptor &rhs);
      virtual ~PageParameterDescriptor();
      
      PageParameterDescriptor& operator=(const PageParameterDescriptor &rhs);
      
      // properties
      
      // special string values:
      //   kOfxParamPageSkipRow
      //   kOfxParamPageSkipColumn
      int getChildCount();
      void setChild(int i, const std::string &name);
      std::string getChild(int i);
  };
  
  class BooleanParameterDescriptor : public ValueParameterDescriptor {
    public:
      BooleanParameterDescriptor();
      BooleanParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      BooleanParameterDescriptor(const BooleanParameterDescriptor &rhs);
      virtual ~BooleanParameterDescriptor();
      
      BooleanParameterDescriptor& operator=(const BooleanParameterDescriptor &rhs);
      
      // properties
      
      bool getDefault();
      void setDefault(bool v);
  };
  
  class RGBParameterDescriptor : public ValueParameterDescriptor {
    public:
      RGBParameterDescriptor();
      RGBParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      RGBParameterDescriptor(const RGBParameterDescriptor &rhs);
      virtual ~RGBParameterDescriptor();
      
      RGBParameterDescriptor& operator=(const RGBParameterDescriptor &rhs);
      
      // properties
      
      RGBAColour<double> getDefault();
      void setDefault(const RGBAColour<double> &v);
  };
  
  class RGBAParameterDescriptor : public ValueParameterDescriptor {
    public:
      RGBAParameterDescriptor();
      RGBAParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      RGBAParameterDescriptor(const RGBAParameterDescriptor &rhs);
      virtual ~RGBAParameterDescriptor();
      
      RGBAParameterDescriptor& operator=(const RGBAParameterDescriptor &rhs);
      
      // properties
      
      RGBAColour<double> getDefault();
      void setDefault(const RGBAColour<double> &v);
  };
  
  class PushButtonParameterDescriptor : public ParameterDescriptor {
    public:
      PushButtonParameterDescriptor();
      PushButtonParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      PushButtonParameterDescriptor(const PushButtonParameterDescriptor &rhs);
      virtual ~PushButtonParameterDescriptor();
      
      PushButtonParameterDescriptor& operator=(const PushButtonParameterDescriptor &rhs);
      
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
      IntParameter(Host *h, OfxParamHandle hdl);
      IntParameter(const IntParameter &rhs);
      virtual ~IntParameter();
      
      IntParameter& operator=(const IntParameter &rhs);
      
      // properties
      
      int getDefault();
      
      int getMin();
      void setMin(int v);
      
      int getMax();
      void setMax(int v);
      
      int getDisplayMin();
      void setDisplayMin(int v);
      
      int getDisplayMax();
      void setDisplayMax(int v);
      
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
      Int2Parameter(Host *h, OfxParamHandle hdl);
      Int2Parameter(const Int2Parameter &rhs);
      virtual ~Int2Parameter();
      
      Int2Parameter& operator=(const Int2Parameter &rhs);
      
      // properties
      
      void getDefault(int &v0, int &v1);
      
      void getMin(int &min0, int &min1);
      void setMin(int min0, int min1);
      
      void getMax(int &max0, int &max1);
      void setMax(int max0, int max1);
      
      void getDisplayMin(int &min0, int &min1);
      void setDisplayMin(int min0, int min1);
      
      void getDisplayMax(int &max0, int &max1);
      void setDisplayMax(int max0, int max1);
      
      std::string getDimensionLabel(int i);
      
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
      Int3Parameter(Host *h, OfxParamHandle hdl);
      Int3Parameter(const Int3Parameter &rhs);
      virtual ~Int3Parameter();
      
      Int3Parameter& operator=(const Int3Parameter &rhs);
      
      // properties
      
      void getDefault(int &v0, int &v1, int &v2);
      
      void getMin(int &min0, int &min1, int &min2);
      void setMin(int min0, int min1, int min2);
      
      void getMax(int &max0, int &max1, int &max2);
      void setMax(int max0, int max1, int max2);
      
      void getDisplayMin(int &min0, int &min1, int &max2);
      void setDisplayMin(int min0, int min1, int max2);
      
      void getDisplayMax(int &max0, int &max1, int &max2);
      void setDisplayMax(int max0, int max1, int max2);
      
      std::string getDimensionLabel(int i);
      
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
      DoubleParameter(Host *h, OfxParamHandle hdl);
      DoubleParameter(const DoubleParameter &rhs);
      virtual ~DoubleParameter();
      
      DoubleParameter& operator=(const DoubleParameter &rhs);
      
      // properties
      
      double getDefault();
      
      double getMin();
      void setMin(double min0);
      
      double getMax();
      void setMax(double max0);
      
      double getDisplayMin();
      void setDisplayMin(double min0);
      
      double getDisplayMax();
      void setDisplayMax(double max0);
      
      double increment();
      void setIncrement(double i);
      
      int digits();
      void setDigits(int d);
      
      bool showTimeMarker();
      void setShowTimeMarker(bool);
      
      DoubleParamType doubleType();
      
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
      Double2Parameter(Host *h, OfxParamHandle hdl);
      Double2Parameter(const Double2Parameter &rhs);
      virtual ~Double2Parameter();
      
      Double2Parameter& operator=(const Double2Parameter &rhs);
      
      // properties
      
      void getDefault(double &v0, double &v1);
      
      void getMin(double &min0, double &min1);
      void setMin(double min0, double min1);
      
      void getMax(double &max0, double &max1);
      void setMax(double max0, double max1);
      
      void getDisplayMin(double &min0, double &min1);
      void setDisplayMin(double min0, double min1);
      
      void getDisplayMax(double &max0, double &max1);
      void setDisplayMax(double max0, double max1);
      
      double increment();
      void setIncrement(double i);
      
      int digits();
      void setDigits(int d);
      
      DoubleParamType doubleType();
      
      std::string getDimensionLabel(int i);
      
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
      Double3Parameter(Host *h, OfxParamHandle hdl);
      Double3Parameter(const Double3Parameter &rhs);
      virtual ~Double3Parameter();
      
      Double3Parameter& operator=(const Double3Parameter &rhs);
      
      // properties
      
      void getDefault(double &v0, double &v1, double &v2);
      
      void getMin(double &min0, double &min1, double &min2);
      void setMin(double min0, double min1, double min2);
      
      void getMax(double &max0, double &max1, double &max2);
      void setMax(double max0, double max1, double max2);
      
      void getDisplayMin(double &min0, double &min1, double &max2);
      void setDisplayMin(double min0, double min1, double max2);
      
      void getDisplayMax(double &max0, double &max1, double &max2);
      void setDisplayMax(double max0, double max1, double max2);
      
      double increment();
      void setIncrement(double i);
      
      int digits();
      void setDigits(int d);
      
      DoubleParamType doubleType();
      
      std::string getDimensionLabel(int i);
      
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
      StringParameter(Host *h, OfxParamHandle hdl);
      StringParameter(const StringParameter &rhs);
      virtual ~StringParameter();
      
      StringParameter& operator=(const StringParameter &rhs);
      
      // properties
      
      std::string getDefault();
      
      StringParamMode mode();
      
      bool filePathExists();
      
      // suite
      
      std::string getValue() throw(Exception);
      std::string getValueAtTime(Time t) throw(Exception);
      
      void setValue(const std::string &v) throw(Exception);
      void setValueAtTime(Time t, const std::string &v) throw(Exception);
  };
  
  class CustomParameter : public ValueParameter {
    public:
      CustomParameter();
      CustomParameter(Host *h, OfxParamHandle hdl);
      CustomParameter(const CustomParameter &rhs);
      virtual ~CustomParameter();
      
      CustomParameter& operator=(const CustomParameter &rhs);
      
      // properties
      
      std::string getDefault();
      
      void* getInterpolator();
      
      // suite
      
      std::string getValue() throw(Exception);
      std::string getValueAtTime(Time t) throw(Exception);
      
      void setValue(const std::string &v) throw(Exception);
      void setValueAtTime(Time t, const std::string &v) throw(Exception);
  };
  
  class BooleanParameter : public ValueParameter {
    public:
      BooleanParameter();
      BooleanParameter(Host *h, OfxParamHandle hdl);
      BooleanParameter(const BooleanParameter &rhs);
      virtual ~BooleanParameter();
      
      BooleanParameter& operator=(const BooleanParameter &rhs);
      
      // properties
      
      bool getDefault();
      
      // suite
      
      bool getValue() throw(Exception);
      bool getValueAtTime(Time t) throw(Exception);
      
      void setValue(bool v) throw(Exception);
      void setValueAtTime(Time t, bool v) throw(Exception);
  };
  
  class RGBParameter : public ValueParameter {
    public:
      RGBParameter();
      RGBParameter(Host *h, OfxParamHandle hdl);
      RGBParameter(const RGBParameter &rhs);
      virtual ~RGBParameter();
      
      RGBParameter& operator=(const RGBParameter &rhs);
      
      // properties
      
      RGBAColour<double> getDefault();
      
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
      RGBAParameter(Host *h, OfxParamHandle hdl);
      RGBAParameter(const RGBAParameter &rhs);
      virtual ~RGBAParameter();
      
      RGBAParameter& operator=(const RGBAParameter &rhs);
      
      // properties
      
      RGBAColour<double> getDefault();
      
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
      ChoiceParameter(Host *h, OfxParamHandle hdl);
      ChoiceParameter(const ChoiceParameter &rhs);
      virtual ~ChoiceParameter();
      
      ChoiceParameter& operator=(const ChoiceParameter &rhs);
      
      // properties
      
      int getDefault();
      
      int getChoiceCount();
      void setChoice(int i, const std::string &str);
      std::string getChoice(int i);
      
      // suite
      
      int getValue() throw(Exception);
      int getValueAtTime(Time t) throw(Exception);
      
      void setValue(int v) throw(Exception);
      void setValueAtTime(Time t, int v) throw(Exception);
  };
  
  class PageParameter : public Parameter {
    public:
      PageParameter();
      PageParameter(Host *h, OfxParamHandle hdl);
      PageParameter(const PageParameter &rhs);
      virtual ~PageParameter();
      
      PageParameter& operator=(const PageParameter &rhs);
      
      // properties
      
      int getChildCount();
      std::string getChild(int i);
  };
  
  class PushButtonParameter : public Parameter {
    public:
      
      PushButtonParameter();
      PushButtonParameter(Host *h, OfxParamHandle hdl);
      PushButtonParameter(const PushButtonParameter &rhs);
      virtual ~PushButtonParameter();
      
      PushButtonParameter& operator=(const PushButtonParameter &rhs);
      
      // properties
      
      EntryPoint interact();
      
      void interactSize(double &w, double &h);
      
      double interactSizeAspect();
      
      void interactMinimumSize(int &w, int &h);
      
      void interactPreferedSize(int &w, int &h);
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
      
      void beginEdit(const std::string &label);
      void endEdit();
  };
  
}

#endif
