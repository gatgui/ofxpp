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
      
      inline ImageEffectHost* host() {
        return mHost;
      }
      
      inline OfxImageEffectHandle handle() {
        return mHandle;
      }
      
      inline PropertySet& properties() {
        return mProps;
      }
      
      inline ParameterSetDescriptor& parameters() {
        return mParams;
      }
      
      // suite
      
      ClipDescriptor defineClip(const std::string &name) throw(Exception);
      
      // properties
      
      std::string label();
      void label(const std::string &s);
      
      std::string shortLabel();
      void shortLabel(const std::string &s);
      
      std::string longLabel();
      void longLabel(const std::string &s);
      
      int supportedContextsCount();
      ImageEffectContext supportedContext(int i);
      void supportedContext(int i, ImageEffectContext ctx);
      
      std::string group();
      void group(const std::string &g);
      
      bool singleInstance();
      void singleInstance(bool);
      
      RenderThreadSafety renderThreadSafety();
      void renderThreadSafety(RenderThreadSafety rts);
      
      // indicates whether plugin relies on host for frame threading or not
      bool hostFrameThreading();
      void hostFrameThreading(bool);
      
      // Use this way:
      //   effectDesc->overlayInteract(InteractEntryPoint<MyPluginClass, MyInteractDescriptionClass, MyInteractClass>)
      EntryPoint overlayInteract();
      void overlayInteract(EntryPoint func);
      
      bool supportsMultiResolution();
      void supportsMultiResolution(bool);
      
      bool supportsTiles();
      void supportsTiles(bool);
      
      bool temporalClipAccess();
      void temporalClipAccess(bool);
      
      int supportedPixelDepthsCount();
      void supportedPixelDepth(int i, BitDepth bd);
      BitDepth supportedPixelDepth(int i);
      
      bool fieldRenderTwiceAlways();
      void fieldRenderTwiceAlways(bool);
      
      bool supportsMultipleClipDepths();
      void supportsMultipleClipDepths(bool);
      
      bool supportsMultipleClipPARs();
      void supportsMultipleClipPARs(bool);  
      
      int clipPreferencesSlaveParamCount();
      std::string clipPreferencesSlaveParam(int i);
      void clipPreferencesSlaveParam(int i, const std::string &n);
      
      std::string pluginFilePath();
      
      SequentialRender sequentialRender();
      void sequentialRender(SequentialRender sr);
      
#ifdef OFX_API_1_2
      int version(int level);
      int majorVersion();
      int minorVersion();
      void version(int level, int v);
      
      std::string versionLabel();
      void versionLabel(const std::string &vl);
      
      std::string description();
      void description(const std::string &vl);
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
      
      inline ImageEffectHost* host() {
        return mHost;
      }
      
      inline PropertySet& properties() {
        return mProps;
      }
      
      inline ParameterSet& parameters() {
        return mParams;
      }
      
      inline OfxImageEffectHandle handle() {
        return mHandle;
      }
      
      void handle(OfxImageEffectHandle handle) throw(Exception);
      
      // suite
      
      Clip getClip(const std::string &name) throw(Exception);
      bool abort() throw(Exception);
      
      OfxImageMemoryHandle alloc(size_t nBytes) throw(Exception);
      OfxImageMemoryHandle alloc(int w, int h, ImageComponent comps, BitDepth depth) throw(Exception);
      void* lock(OfxImageMemoryHandle hdl) throw(Exception);
      void unlock(OfxImageMemoryHandle hdl) throw(Exception);
      void free(OfxImageMemoryHandle hdl) throw(Exception);
      
      // properties
      
      ImageEffectContext context();
      
      void* instanceData();
      void instanceData(void *data);
      
      void projectSize(double *w, double *h);
      
      void projectOffset(double *x, double *y);
      
      void projectExtent(double *w, double *h);
      
      double projectPixelAspectRatio();
      
      double duration();
      
      SequentialRender sequentialRender();
      void sequentialRender(SequentialRender sr);
      
      double frameRate();
      
      bool isInteractive();
      
      bool inAnalysis();
      void inAnalysis(bool v);
      
      ImageEffectDescriptor descriptor();
      
#ifdef OFX_API_1_2
      std::string description();
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
      virtual OfxStatus getTimeDomain(double *first, double *last);
    
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
