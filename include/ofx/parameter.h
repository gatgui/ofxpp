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

/** \file parameter.h
 *  Parameters descriptor and instance base classes.
 */

#ifndef __ofx_parameter_h__
#define __ofx_parameter_h__

#include <ofx/ofx.h>
#include <ofx/exception.h>
#include <ofx/property.h>
#include <ofx/host.h>
#include <ofxParam.h>

namespace ofx {
  
  //class Host;
  class ParameterSet;
  
  //! %Parameter descriptor base class.
  class ParameterDescriptor : public PropertySet {
    public:
      
      ParameterDescriptor();
      ParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      ParameterDescriptor(const ParameterDescriptor &rhs);
      virtual ~ParameterDescriptor();
      
      ParameterDescriptor& operator=(const ParameterDescriptor &rhs);
      
      // properties
      
      //! Get name.
      std::string name();
      //! Set name.
      void name(const std::string &name);
      
      //! Get label.
      std::string label();
      //! Set label.
      void label(const std::string &lbl);
      
      //! Get short label.
      std::string shortLabel();
      //! Set short label.
      void shortLabel(const std::string &lbl);
      
      //! Get long label.
      std::string longLabel();
      //! Set long label.
      void longLabel(const std::string &lbl);
      
      //! Get type.
      ParamType type();
      
      //! Check if parameter should be hidden.
      bool secret();
      //! Set if parameter should be hidden.
      void secret(bool);
      
      //! Check if value changes are undoable
      bool canUndo();
      //! Set if value changes are undoable
      void canUndo(bool);
      
      //! Get hint.
      std::string hint();
      //! Set hint.
      void hint(const std::string &h);
      
      //! Get script name.
      std::string scriptName();
      //! Set script name.
      void scriptName(const std::string &h);
      
      //! Get group name.
      std::string parent();
      //! Set group name.
      void parent(const std::string &n);
      
      //! Check if parameter is enabled.
      bool enabled();
      //! Set if parameter is enabled.
      void enabled(bool);
      
      //void* data();
      //void data(void *);
      
#ifdef OFX_API_1_2
      
      /** Get PNG icon resource path.
       *  \note OpenFX version >= 1.2
       */
      std::string PNGIcon();
      /** Get SVG icon resource path.
       *  \note OpenFX version >= 1.2
       */
      std::string SVGIcon();
      /** Set PNG icon resource path.
       *  \note OpenFX version >= 1.2
       */
      void PNGIcon(const std::string &resPath);
      /** Set SVG icon resource path.
       *  \note OpenFX version >= 1.2
       */
      void SVGIcon(const std::string &resPath);
      
#endif
  };
  
  //! Value parameter descriptor base class.
  class ValueParameterDescriptor : public ParameterDescriptor {
    public:
      
      ValueParameterDescriptor();
      ValueParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      ValueParameterDescriptor(const ValueParameterDescriptor &rhs);
      virtual ~ValueParameterDescriptor();
      
      ValueParameterDescriptor& operator=(const ValueParameterDescriptor &rhs);
      
      // properties
      
      //! Get interact entry point function.
      EntryPoint interact();
      //! Set interact entry point function.
      void interact(EntryPoint func);
      
      //void interactSize(double &w, double &h);
      //void interactSize(double w, double h);
      
      //! Get interact size aspect.
      double interactSizeAspect();
      //! Set interact size aspect.
      void interactSizeAspect(double a);
      
      //! Get interact minimum size.
      void interactMinimumSize(int *w, int *h);
      //! Set interact minimum size.
      void interactMinimumSize(int w, int h);
      
      //! Get interact prefered size.
      void interactPreferedSize(int *w, int *h);
      //! Set interact prefered size.
      void interactPreferedSize(int w, int h);
      
      //! Check if parameter can be animated.
      bool animates();
      //! Set if parameter can be animated.
      void animates(bool);
      
      //bool animating();
      //void animating(bool);
      
      //bool autoKeying();
      //void autoKeying(bool);
      
      //! Check if value is persisant.
      bool persistant();
      //! Set if value is persisant.
      void persistant(bool);
      
      //! Check if a value change forces a render.
      bool evaluateOnChange();
      //! Set if a value change forces a render.
      void evaluateOnChange(bool);
      
      //! Check if plugin may change the value internally.
      bool pluginMayWrite();
      //! Set if plugin may change the value internally.
      void pluginMayWrite(bool);
      
      //! Get how value changes affect the cache.
      ParamInvalidate cacheInvalidation();
      //! Set how value changes affect the cache.
      void cacheInvalidation(ParamInvalidate i);
      
#ifdef OFX_API_1_2
      
      /** Check if host provides generic overlay handle.
       *  \note OpenFX version >= 1.2.
       */
      bool hasHostOverlayHandle();
      
      /** Check if parameter is using host provided overlay handle.
       *  \note OpenFX version >= 1.2.
       */
      bool useHostOverlayHandle();
      /** Set if parameter is using host provided overlay handle.
       *  \note OpenFX version >= 1.2.
       */
      void useHostOverlayHandle(bool b);
      
#endif
  };
  
  //! %Parameter instance base class.
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
      
      //! Get native handle.
      inline OfxParamHandle handle() {
        return mHandle;
      }
      
      //! Get associated properties.
      inline PropertySet& properties() {
        return mProps;
      }
      
      // properties
      
      //! Get name.
      std::string name();
      
      //! Get label.
      std::string label();
      //! Set label.
      void label(const std::string &lbl);
      
      //! Get short label.
      std::string shortLabel();
      //! Set short label.
      void shortLabel(const std::string &lbl);
      
      //! Get long label.
      std::string longLabel();
      //! Set long label.
      void longLabel(const std::string &lbl);
      
      //! Get type.
      ParamType type();
      
      //! Check if parameter is hidden.
      bool secret();
      //! Set if parameter is hidden.
      void secret(bool);
      
      //! Check if value changes are undoable
      bool canUndo();
      
      //! Get hint.
      std::string hint();
      //! Set hint.
      void hint(const std::string &h);
      
      //! Get script name.
      std::string scriptName();
      
      //! Get group name.
      std::string parent();
      
      //! Check if parameter is enabled.
      bool enabled();
      //! Set if parameter is enabled.
      void enabled(bool);
      
      //! Get associated user data.
      void* data();
      //! Set associated user data.
      void data(void *);
      
#ifdef OFX_API_1_2
      
      /** Get PNG icon resource path.
       *  \note OpenFX version >= 1.2
       */
      std::string PNGIcon();
      
      /** Get SVG icon resource path.
       *  \note OpenFX version >= 1.2
       */
      std::string SVGIcon();
#endif
      
      // suite
  };
  
  //! Value parameter instance base class.
  class ValueParameter : public Parameter {
    public:
      
      ValueParameter();
      ValueParameter(Host *h, OfxParamHandle hdl);
      ValueParameter(const ValueParameter &rhs);
      virtual ~ValueParameter();
      
      ValueParameter& operator=(const ValueParameter &rhs);
      
      // properties
      
      //! Get interact entry point function.
      EntryPoint interact();
      
      //! Get interact size.
      void interactSize(double *w, double *h);
      
      //! Get interact size aspect.
      double interactSizeAspect();
      
      //! Get interact minimum size.
      void interactMinimumSize(int *w, int *h);
      
      //! Get interact prefered size.
      void interactPreferedSize(int *w, int *h);
      
      //! Check if parameter can be animated.
      bool animates();
      
      //! Check if parameter is currently animating.
      bool animating();
      
      //! Check if parameter is auto keying.
      bool autoKeying();
      
      //! Check if parameter value is persistant.
      bool persistant();
      
      //! Check if a value change forces a render.
      bool evaluateOnChange();
      
      //! Check if plugin may change the value internally.
      bool pluginMayWrite();
      
      //! Get how value changes affect the cache.
      ParamInvalidate cacheInvalidation();
      
#ifdef OFX_API_1_2
      
      /** Check if parameter is using host provided overlay handle.
       *  \note OpenFX version >= 1.2.
       */
      bool useHostOverlayHandle();
      
#endif
      
      // suite
      
      //! Get number of key frames.
      unsigned int getNumKeys() throw(Exception);
      
      //! Get key frame time.
      Time getKeyTime(unsigned int nth) throw(Exception);
      
      //! Get key frame index.
      int getKeyIndex(Time t, KeyDirection kd=KeyDirectionExact) throw(Exception);
      
      //! Delete key frame at time.
      bool deleteKey(Time t) throw(Exception);
      
      //! Delete all key frames.
      void deleteAllKeys() throw(Exception);
      
      //! Copy key frame data.
      void copy(ValueParameter &from, Time offset, FrameRange *range=0) throw(Exception);
  };
  
}

#endif
