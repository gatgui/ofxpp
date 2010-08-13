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

#ifndef __ofx_imageeffect_h__
#define __ofx_imageeffect_h__

#include <ofxImageEffect.h>
#include <ofx/ofx.h>
#include <ofx/exception.h>
#include <ofx/property.h>
#include <ofx/parameterset.h>
#include <ofx/clip.h>
#include <map>

namespace ofx {
  
  class Host;
  class ImageEffectHost;
  class Interaction;
  
  
  struct PixelPreferences {
    ImageComponent components;
    BitDepth bitDepth;
    double pixelAspectRatio;
  };
  
  
  struct ClipPreferences { // derive from PixelPreferences?
    double frameRate;
    ImageFieldOrder fieldOrder;
    ImagePreMult preMult;
    bool continuousSamples;
    bool frameVarying;
  };
  
  
  class ImageEffectDescriptor {
    protected:
      
      OfxImageEffectHandle mHandle;
      PropertySet mProps;
      ParameterSetDescriptor mParams;
      ImageEffectHost *mHost;
      
      ImageEffectDescriptor();
      
    public:
      
      ImageEffectDescriptor(ImageEffectHost *h, OfxImageEffectHandle hdl) throw(Exception);
      ImageEffectDescriptor(const ImageEffectDescriptor &rhs);
      virtual ~ImageEffectDescriptor();
      
      ImageEffectDescriptor& operator=(const ImageEffectDescriptor &rhs);
      
      inline ImageEffectHost* getHost() {
        return mHost;
      }
      
      inline OfxImageEffectHandle getHandle() {
        return mHandle;
      }
      
      inline PropertySet& getProperties() {
        return mProps;
      }
      
      inline ParameterSetDescriptor& getParameters() {
        return mParams;
      }
      
      // suite
      
      ClipDescriptor defineClip(const std::string &name) throw(Exception);
      
      // properties
      
      std::string getLabel();
      void setLabel(const std::string &s);
      
      std::string getShortLabel();
      void setShortLabel(const std::string &s);
      
      std::string getLongLabel();
      void setLongLabel(const std::string &s);
      
      int getSupportedContextsCount();
      ImageEffectContext getSupportedContext(int i);
      void setSupportedContext(int i, ImageEffectContext ctx);
      
      std::string getGroup();
      void setGroup(const std::string &g);
      
      bool isSingleInstance();
      void setSingleInstance(bool);
      
      RenderThreadSafety getRenderThreadSafety();
      void setRenderThreadSafety(RenderThreadSafety rts);
      
      // indicates whether plugin relies on host for frame threading or not
      bool requireHostFrameThreading();
      void setHostFrameThreading(bool);
      
      // Use this way:
      //   effectDesc->setOverlayInteract(InteractEntryPoint<MyPluginClass, MyInteractDescriptionClass, MyInteractClass>)
      EntryPoint getOverlayInteract();
      void setOverlayInteract(EntryPoint func);
      
      bool supportMultiResolution();
      void setMultiResolutionSupport(bool);
      
      bool supportTiles();
      void setTilesSupport(bool);
      
      bool requireTemporalClipAccess();
      void setTemporalClipAccess(bool);
      
      int getSupportedPixelDepthsCount();
      void setSupportedPixelDepth(int i, BitDepth bd);
      BitDepth getSupportedPixelDepth(int i);
      
      bool alwaysRenderFieldTwice();
      void setAlwaysRenderFieldTwice(bool);
      
      bool supportMultipleClipDepths();
      void setMultipleClipDepthsSupport(bool);
      
      bool supportMultipleClipPARs();
      void setMultipleClipPARsSupport(bool);  
      
      int getClipPreferencesSlaveParamCount();
      std::string getClipPreferencesSlaveParam(int i);
      void setClipPreferencesSlaveParam(int i, const std::string &n);
      
      std::string getPluginFilePath();
      
      SequentialRender getSequentialRender();
      void setSequentialRender(SequentialRender sr);
      
#ifdef OFX_API_1_2
      int getVersion(int level);
      int getMajorVersion();
      int getMinorVersion();
      void setVersion(int level, int v);
      
      std::string getVersionLabel();
      void setVersionLabel(const std::string &vl);
      
      std::string getDescription();
      void setDescription(const std::string &vl);
#endif
      
      // Image effect actions
      
      virtual OfxStatus describe();
      virtual OfxStatus describeInContext(ImageEffectContext ctx);
  };
  
  
  class ImageEffect {
    public:
      
      static ImageEffect* GetEffect(OfxImageEffectHandle hdl);
    
    public:
      
      struct RenderScaleArgs {
        double renderScaleX;
        double renderScaleY;
        
        RenderScaleArgs(ImageEffectHost *host, PropertySet &props);
      };
      
      struct TimeArgs {
        Time time;
        
        TimeArgs(ImageEffectHost *host, PropertySet &props);
      };
      
      struct InstanceChangedArgs : public RenderScaleArgs, public TimeArgs {
        Type type;
        std::string name;
        ChangeReason reason;
        
        InstanceChangedArgs(ImageEffectHost *host, PropertySet &props);
      };
      
      struct GetRoDArgs : public RenderScaleArgs, public TimeArgs {
        Rect<double> RoD;
        
        GetRoDArgs(ImageEffectHost *host, PropertySet &in);
        void setOutputs(PropertySet &out);
      };
      
      struct RenderArgs : public RenderScaleArgs, public TimeArgs {
        ImageField field;
        Rect<int> renderWindow;
#ifdef OFX_API_1_2
        bool sequentialRender;
        bool interactiveRender;
#endif
        
        RenderArgs(ImageEffectHost *host, PropertySet &props);
      };
      
      struct IsIdentityArgs : public RenderArgs {
        std::string idClip;
        Time idTime;
        
        IsIdentityArgs(ImageEffectHost *host, PropertySet &in);
        void setOutputs(PropertySet &out);
      };
      
      struct GetRoIArgs : public RenderScaleArgs, public TimeArgs {
        Rect<double> outRoI;
        std::map<std::string, Rect<double> > inRoIs;
        
        GetRoIArgs(ImageEffectHost *host, PropertySet &in);
        void setOutputs(PropertySet &out);
        void setInputRoI(const std::string &name, const Rect<double> &RoI);
      };
      
      struct GetFramesNeededArgs : public TimeArgs {
        std::map<std::string, FrameRangeList> inRanges;
        
        GetFramesNeededArgs(ImageEffectHost *host, PropertySet &in);
        void setOutputs(PropertySet &out);
        void addInputRange(const std::string &name, const FrameRange &range);
      };
      
      struct SequenceArgs : public RenderScaleArgs {
        bool interactive;
#ifdef OFX_API_1_2
        bool sequentialRender;
        bool interactiveRender;
#endif
        
        SequenceArgs(ImageEffectHost *host, PropertySet &props);
      };
      
      struct BeginSequenceArgs : public SequenceArgs {
        FrameRange range;
        double step;
        // supposed to be the same in the specs for EndSequence action
        
        BeginSequenceArgs(ImageEffectHost *host, PropertySet &props);
      };
      
      typedef SequenceArgs EndSequenceArgs;
      
      struct GetClipPrefArgs {
        ClipPreferences outPref;
        std::map<std::string, PixelPreferences> inPrefs;
        
        GetClipPrefArgs(ImageEffectHost *host);
        void setOutputs(PropertySet &out);
        void setInputPref(const std::string &name, const PixelPreferences &prefs);
      };
      
    public:
      
      ImageEffect(ImageEffectHost *h, OfxImageEffectHandle hdl);
      virtual ~ImageEffect();
      
      inline ImageEffectHost* getHost() {
        return mHost;
      }
      
      inline PropertySet& getProperties() {
        return mProps;
      }
      
      inline ParameterSet& getParameters() {
        return mParams;
      }
      
      inline OfxImageEffectHandle getHandle() {
        return mHandle;
      }
      
      void setHandle(OfxImageEffectHandle handle) throw(Exception);
      
      // suite
      
      Clip getClip(const std::string &name) throw(Exception);
      bool abort() throw(Exception);
      
      OfxImageMemoryHandle alloc(size_t nBytes) throw(Exception);
      void* lock(OfxImageMemoryHandle hdl) throw(Exception);
      void unlock(OfxImageMemoryHandle hdl) throw(Exception);
      void free(OfxImageMemoryHandle hdl) throw(Exception);
      
      // properties
      
      ImageEffectContext getContext();
      
      void* getInstanceData();
      void setInstanceData(void *data);
      
      void getProjectSize(double &w, double &h);
      
      void getProjectOffset(double &x, double &y);
      
      void getProjectExtent(double &w, double &h);
      
      double getProjectPixelAspectRatio();
      
      double getDuration();
      
      SequentialRender getSequentialRender();
      void setSequentialRender(SequentialRender sr);
      
      double getFrameRate();
      
      bool isInteractive();
      
#ifdef OFX_API_1_2
      std::string getDescription();
#endif
      
      // Image effect actions
      
      virtual OfxStatus beginInstanceChanged(ChangeReason reason);
      virtual OfxStatus endInstanceChanged(ChangeReason reason);
      virtual OfxStatus instanceChanged(InstanceChangedArgs &args);
      virtual OfxStatus purgeCaches();
      virtual OfxStatus syncPrivateData();
      virtual OfxStatus beginInstanceEdit();
      virtual OfxStatus endInstanceEdit();
      virtual OfxStatus getRegionOfDefinition(GetRoDArgs &args);
      virtual OfxStatus getRegionsOfInterest(GetRoIArgs &args);
      virtual OfxStatus getFramesNeeded(GetFramesNeededArgs &args);
      virtual OfxStatus isIdentity(IsIdentityArgs &args);
      virtual OfxStatus render(RenderArgs &args);
      virtual OfxStatus beginSequenceRender(BeginSequenceArgs &args);
      virtual OfxStatus endSequenceRender(EndSequenceArgs &args);
      virtual OfxStatus getClipPreferences(GetClipPrefArgs &args);
      virtual OfxStatus getTimeDomain(double &first, double &last);
    
    protected:
      
      OfxImageEffectHandle mHandle;
      PropertySet mProps;
      ParameterSet mParams;
      ImageEffectHost *mHost;
      
      static std::map<OfxImageEffectHandle, ImageEffect*> msEffects;
      
      ImageEffect();
  };
  
  
}

#endif
