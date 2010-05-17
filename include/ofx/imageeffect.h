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
    
  class Image {
    public:
      
      Image();
      Image(ImageEffectHost *h, OfxPropertySetHandle hdl) throw(Exception);
      Image(const Image &rhs);
      ~Image();
      
      Image& operator=(const Image &rhs);
      
      inline OfxPropertySetHandle handle() {
        return mProps.handle();
      }
      
      inline void* data() {
        return mData;
      }
      
      inline BitDepth pixelDepth() const {
        return mBitDepth;
      }
      
      inline ImageComponent components() const {
        return mComponents;
      }
      
      inline ImagePreMult preMultiplication() const {
        return mPreMult;
      }
      
      inline void renderScale(double &sx, double &sy) const {
        sx = mRenderScaleX;
        sy = mRenderScaleY;
      }
      
      inline double pixelAspectRatio() const {
        return mPixelAspectRatio;
      }
      
      const Rect<int>& regionOfDefinition() const {
        return mRoD;
      }
      
      inline ImageField field() const {
        return mField;
      }
      
      inline const std::string& uniqueIdentifier() const {
        return mUID;
      }
      
      inline int componentBytes() const {
        return mCompBytes;
      }
      
      inline int numComponents() const {
        return mNumComps;
      }
      
      inline int pixelBytes() const {
        return mPixelBytes;
      }
      
      inline int rowBytes() {
        return mRowBytes;
      }
      
      inline const Rect<int>& bounds() {
        return mBounds;
      }
      
      inline void* pixelAddress(int x, int y) {
        if (x < mBounds.x1 || x >= mBounds.x2 || y < mBounds.y1 || y >= mBounds.y2) {
          return 0;
        }
        return (void*)((char*)mData + ((y - mBounds.y1) * mRowBytes) + ((x - mBounds.x1) * mPixelBytes));
      }
      
      template <typename ComponentType>
      inline bool pixelAddress(int x, int y, RGBAColour<ComponentType> *&adr) {
        adr = (RGBAColour<ComponentType>*) pixelAddress(x, y);
        return (adr != 0);
      }
      
      // suite
      
      void release() throw(Exception);
      
    protected:
      
      PropertySet mProps;
      OfxImageEffectSuiteV1 *mSuite;
      
      BitDepth mBitDepth;
      ImageComponent mComponents;
      ImagePreMult mPreMult;
      double mRenderScaleX;
      double mRenderScaleY;
      double mPixelAspectRatio;
      Rect<int> mRoD;
      ImageField mField;
      std::string mUID;
      
      int mCompBytes;
      int mNumComps;
      int mPixelBytes;
      int mRowBytes;
      Rect<int> mBounds;
      void *mData;
  };
  
  class ClipDescriptor {
    public:
      
      ClipDescriptor();
      ClipDescriptor(ImageEffectHost *h, OfxPropertySetHandle hdl);
      ClipDescriptor(const ClipDescriptor &rhs);
      ~ClipDescriptor();
      
      ClipDescriptor& operator=(const ClipDescriptor &rhs);
      
      inline OfxPropertySetHandle handle() {
        return mProps.handle();
      }
      
      // properties
      
      std::string name();
      
      std::string label();
      void setLabel(const std::string &l);
      
      std::string shortLabel();
      void setShortLabel(const std::string &l);
      
      std::string longLabel();
      void setLongLabel(const std::string &l);
      
      int supportedComponentsCount();
      ImageComponent getSupportedComponent(int i);
      void setSupportedComponent(int i, ImageComponent ic);
      
      bool needsTemporalClipAccess();
      void requireTemporalClipAccess(bool);
      
      bool isOptional();
      void setOptional(bool);
      
      ImageFieldExtract fieldExtraction();
      void setFieldExtraction(ImageFieldExtract f);
      
      bool isMask();
      void setMask(bool);
      
      bool supportsTiles();
      void setTilesSupport(bool);
    
    protected:
      
      PropertySet mProps;
  };
  
  class Clip {
    public:
      
      Clip();
      Clip(ImageEffectHost *h, OfxImageClipHandle hdl) throw(Exception);
      Clip(const Clip &rhs);
      ~Clip();
      
      Clip& operator=(const Clip &rhs);
      
      inline ImageEffectHost* host() {
        return mHost;
      }
      
      inline OfxImageClipHandle handle() {
        return mHandle;
      }
      
      // suite
      
      Image getImage(Time t) throw(Exception);
      
      Image getImage(Time t, const Rect<double> &region) throw(Exception);
      
      Rect<double> getRegionOfDefinition(Time t) throw(Exception);
      
      // properties
      
      std::string name();
      
      std::string label();
      
      std::string shortLabel();
      
      std::string longLabel();
      
      int supportedComponentsCount();
      ImageComponent getSupportedComponent(int i);
      
      bool needsTemporalClipAccess();
      
      bool isOptional();
      
      ImageFieldExtract fieldExtraction();
      
      bool isMask();
      
      bool supportsTiles();
      
      BitDepth pixelDepth();
      
      ImageComponent components();
      
      BitDepth unmappedPixelDepth();
      
      ImageComponent unmappedComponents();
      
      ImagePreMult preMultiplication();
      
      double pixelAspectRatio();
      
      double frameRate();
      
      void frameRange(double &from, double &to);
      
      ImageFieldOrder fieldOrder();
      
      bool isConnected();
      
      void unmappedFrameRange(double &from, double &to);
      
      double unmappedFrameRate();
      
      bool continuousSamples();
      
    protected:
      
      OfxImageClipHandle mHandle;
      PropertySet mProps;
      ImageEffectHost *mHost;
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
      void setLabel(const std::string &s);
      
      std::string shortLabel();
      void setShortLabel(const std::string &s);
      
      std::string longLabel();
      void setLongLabel(const std::string &s);
      
      int supportedContextsCount();
      ImageEffectContext getSupportedContext(int i);
      void setSupportedContext(int i, ImageEffectContext ctx);
      
      std::string grouping();
      void setGrouping(const std::string &g);
      
      bool singleInstance();
      void setSingleInstance(bool);
      
      RenderThreadSafety renderThreadSafety();
      void setRenderThreadSafety(RenderThreadSafety rts);
      
      bool hostFrameThreading();
      void setHostFrameThreading(bool);
      
      // Use this way:
      //   effectDesc->setOverlayInteract(InteractEntryPoint<MyPluginClass, MyInteractDescriptionClass, MyInteractClass>)
      EntryPoint overlayInteract();
      void setOverlayInteract(EntryPoint func);
      
      bool supportsMultiResolution();
      void setMultiResolutionSupport(bool);
      
      bool supportsTiles();
      void setTilesSupport(bool);
      
      bool needsTemporalClipAccess();
      void requireTemporalClipAccess(bool);
      
      int supportedPixelDepthsCount();
      void setSupportedPixelDepth(int i, BitDepth bd);
      BitDepth getSupportedPixelDepth(int i);
      
      bool fieldRenderTwiceAlways();
      void setFieldRenderTwiceAlways(bool);
      
      bool supportsMultipleClipDepths();
      void setMultipleClipDepthsSupport(bool);
      
      bool supportsMultipleClipPARs();
      void setMultipleClipPARsSupport(bool);  
      
      int clipPreferencesSlaveParamCount();
      std::string getClipPreferencesSlaveParam(int i);
      void setClipPreferencesSlaveParam(int i, const std::string &n);
      
      std::string pluginFilePath();
      
      SequentialRender sequentialRender();
      void setSequentialRender(SequentialRender sr);
      
#ifdef OFX_API_1_2
      int version(int level);
      int majorVersion();
      int minorVersion();
      void setVersion(int level, int v);
      
      std::string versionLabel();
      void setVersionLabel(const std::string &vl);
      
      std::string description();
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
      
      void setHandle(OfxImageEffectHandle handle) throw(Exception);
      
      // suite
      
      Clip getClip(const std::string &name) throw(Exception);
      bool abort() throw(Exception);
      
      OfxImageMemoryHandle alloc(size_t nBytes) throw(Exception);
      void* lock(OfxImageMemoryHandle hdl) throw(Exception);
      void unlock(OfxImageMemoryHandle hdl) throw(Exception);
      void free(OfxImageMemoryHandle hdl) throw(Exception);
      
      // properties
      
      ImageEffectContext context();
      
      void* instanceData();
      void setInstanceData(void *data);
      
      void projectSize(double &w, double &h);
      
      void projectOffset(double &x, double &y);
      
      void projectExtent(double &w, double &h);
      
      double projectPixelAspectRatio();
      
      double duration();
      
      SequentialRender sequentialRender();
      void setSequentialRender(SequentialRender sr);
      
      double frameRate();
      
      bool isInteractive();
      
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
