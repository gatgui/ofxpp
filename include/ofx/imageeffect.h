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
#include <ofx/parameter.h>
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
  
  struct ClipPreferences {
    double frameRate;
    ImageFieldOrder fieldOrder;
    ImagePreMult preMult;
    bool continuousSamples;
    bool frameVarying;
  };
    
  class Image {
    public:
      
      //friend class ImageEffect;
      
      Image();
      Image(ImageEffectHost *h, OfxPropertySetHandle hdl) throw(Exception);
      Image(const Image &rhs);
      ~Image();
      
      Image& operator=(const Image &rhs);
      //Image& operator=(OfxPropertySetHandle hdl);
      
      inline OfxPropertySetHandle handle() {
        return mProps.handle();
      }
      
      inline void* data() {
        return mData;
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
      
      inline Rect<int> bounds() {
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
        if (x < mBounds.x1 || x >= mBounds.x2 || y < mBounds.y1 || y >= mBounds.y2) {
          adr = 0;
          return false;
        }
        adr = (RGBAColour<ComponentType>*)((char*)mData + ((y - mBounds.y1) * mRowBytes) + ((x - mBounds.x1) * mPixelBytes));
        return true;
      }
      
      template <typename ComponentType>
      inline bool getPixelAt(int x, int y, RGBAColour<ComponentType> &dst) {
        if (sizeof(ComponentType) != mCompBytes) {
          return false;
        }
        void *src = pixelAddress(x, y);
        if (!src) {
          return false;
        }
        memcpy(&(dst.r), src, mPixelBytes);
        return true;
      }
      
      template <typename ComponentType>
      inline bool setPixelAt(int x, int y, const RGBAColour<ComponentType> &src) {
        if (sizeof(ComponentType) != mCompBytes) {
          return false;
        }
        void *dst = pixelAddress(x, y);
        if (!dst) {
          return false;
        }
        memcpy(dst, &(src.r), mPixelBytes);
        return true;
      }
      
      // suite
      
      void release() throw(Exception);
      
      // properties
      
      BitDepth pixelDepth() throw(Exception);
      
      ImageComponent components() throw(Exception);
      
      ImagePreMult preMultiplication() throw(Exception);
      
      void renderScale(double &sx, double &sy) throw(Exception);
      
      double pixelAspectRatio() throw(Exception);
      
      //void* data() throw(Exception);
      
      //Rect<int> bounds() throw(Exception);
      
      Rect<int> regionOfDefinition() throw(Exception);
      
      //int rowBytes() throw(Exception);
      
      ImageField field() throw(Exception);
      
      std::string uniqueIdentifier() throw(Exception);
      
    protected:
      
      PropertySet mProps;
      OfxImageEffectSuiteV1 *mSuite;
      
      int mCompBytes;
      int mNumComps;
      int mPixelBytes;
      int mRowBytes;
      Rect<int> mBounds;
      void *mData;
      //static OfxImageEffectSuiteV1 * msSuiteV1;
  };
  
  class ClipDescriptor {
    public:
      
      //friend class ImageEffect;
      
      ClipDescriptor();
      ClipDescriptor(ImageEffectHost *h, OfxPropertySetHandle hdl) throw(Exception);
      ClipDescriptor(const ClipDescriptor &rhs);
      ~ClipDescriptor();
      
      ClipDescriptor& operator=(const ClipDescriptor &rhs);
      //ClipDescriptor& operator=(OfxPropertySetHandle hdl);
      
      inline OfxPropertySetHandle handle() {
        return mProps.handle();
      }
      
      // properties
      
      std::string name() throw(Exception);
      
      std::string label() throw(Exception);
      void setLabel(const std::string &l) throw(Exception);
      
      std::string shortLabel() throw(Exception);
      void setShortLabel(const std::string &l) throw(Exception);
      
      std::string longLabel() throw(Exception);
      void setLongLabel(const std::string &l) throw(Exception);
      
      int supportedComponentsCount() throw(Exception);
      ImageComponent getSupportedComponent(int i) throw(Exception);
      void setSupportedComponent(int i, ImageComponent ic) throw(Exception);
      
      bool needsTemporalClipAccess() throw(Exception);
      void requireTemporalClipAccess(bool) throw(Exception);
      
      bool isOptional() throw(Exception);
      void setOptional(bool) throw(Exception);
      
      ImageFieldExtract fieldExtraction() throw(Exception);
      void setFieldExtraction(ImageFieldExtract f) throw(Exception);
      
      bool isMask() throw(Exception);
      void setMask(bool) throw(Exception);
      
      bool supportsTiles() throw(Exception);
      void setTilesSupport(bool) throw(Exception);
    
    protected:
      
      PropertySet mProps;
      
      //static OfxImageEffectSuiteV1 *msSuiteV1;
  };
  
  class Clip {
    public:
      
      //friend class ImageEffect;
      
      Clip();
      Clip(ImageEffectHost *h, OfxImageClipHandle hdl) throw(Exception);
      Clip(const Clip &rhs);
      ~Clip();
      
      Clip& operator=(const Clip &rhs);
      //Clip& operator=(OfxImageClipHandle hdl);
      
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
      
      std::string name() throw(Exception);
      
      std::string label() throw(Exception);
      
      std::string shortLabel() throw(Exception);
      
      std::string longLabel() throw(Exception);
      
      int supportedComponentsCount() throw(Exception);
      ImageComponent getSupportedComponent(int i) throw(Exception);
      
      bool needsTemporalClipAccess() throw(Exception);
      
      bool isOptional() throw(Exception);
      
      ImageFieldExtract fieldExtraction() throw(Exception);
      
      bool isMask() throw(Exception);
      
      bool supportsTiles() throw(Exception);
      
      BitDepth pixelDepth() throw(Exception);
      
      ImageComponent components() throw(Exception);
      
      BitDepth unmappedPixelDepth() throw(Exception);
      
      ImageComponent unmappedComponents() throw(Exception);
      
      ImagePreMult preMultiplication() throw(Exception);
      
      double pixelAspectRatio() throw(Exception);
      
      double frameRate() throw(Exception);
      
      void frameRange(double &from, double &to) throw(Exception);
      
      ImageFieldOrder fieldOrder() throw(Exception);
      
      bool isConnected() throw(Exception);
      
      void unmappedFrameRange(double &from, double &to) throw(Exception);
      
      double unmappedFrameRate() throw(Exception);
      
      bool continuousSamples() throw(Exception);
      
    protected:
      
      OfxImageClipHandle mHandle;
      PropertySet mProps;
      ImageEffectHost *mHost;
      
      //static OfxImageEffectSuiteV1 *msSuiteV1;
  };
  
  class ImageEffectDescriptor {
    protected:
      
      OfxImageEffectHandle mHandle;
      PropertySet mProps;
      ParameterSetDescriptor mParams;
      ImageEffectHost *mHost;
      
      //static OfxImageEffectSuiteV1 *msSuiteV1;
      
      ImageEffectDescriptor();
      
    public:
      
      //friend class ImageEffect;
      
      //ImageEffectDescriptor();
      ImageEffectDescriptor(ImageEffectHost *h, OfxImageEffectHandle hdl) throw(Exception);
      ImageEffectDescriptor(const ImageEffectDescriptor &rhs);
      virtual ~ImageEffectDescriptor();
      
      ImageEffectDescriptor& operator=(const ImageEffectDescriptor &rhs);
      //ImageEffectDescriptor& operator=(OfxImageEffectHandle hdl);
      
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
      
      std::string label() throw(Exception);
      void setLabel(const std::string &s) throw(Exception);
      
      std::string shortLabel() throw(Exception);
      void setShortLabel(const std::string &s) throw(Exception);
      
      std::string longLabel() throw(Exception);
      void setLongLabel(const std::string &s) throw(Exception);
      
      int supportedContextsCount() throw(Exception);
      ImageEffectContext getSupportedContext(int i) throw(Exception);
      void setSupportedContext(int i, ImageEffectContext ctx) throw(Exception);
      
      std::string grouping() throw(Exception);
      void setGrouping(const std::string &g) throw(Exception);
      
      bool singleInstance() throw(Exception);
      void setSingleInstance(bool) throw(Exception);
      
      RenderThreadSafety renderThreadSafety() throw(Exception);
      void setRenderThreadSafety(RenderThreadSafety rts) throw(Exception);
      
      bool hostFrameThreading() throw(Exception);
      void setHostFrameThreading(bool) throw(Exception);
      
      // Use this way:
      //   effectDesc->setOverlayInteract(InteractEntryPoint<MyPluginClass, MyInteractDescriptionClass, MyInteractClass>)
      EntryPoint overlayInteract() throw(Exception);
      void setOverlayInteract(EntryPoint func) throw(Exception);
      
      bool supportsMultiResolution() throw(Exception);
      void setMultiResolutionSupport(bool) throw(Exception);
      
      bool supportsTiles() throw(Exception);
      void setTilesSupport(bool) throw(Exception);
      
      bool needsTemporalClipAccess() throw(Exception);
      void requireTemporalClipAccess(bool) throw(Exception);
      
      int supportedPixelDepthsCount() throw(Exception);
      void setSupportedPixelDepth(int i, BitDepth bd) throw(Exception);
      BitDepth getSupportedPixelDepth(int i) throw(Exception);
      
      bool fieldRenderTwiceAlways() throw(Exception);
      void setFieldRenderTwiceAlways(bool) throw(Exception);
      
      bool supportsMultipleClipDepths() throw(Exception);
      void setMultipleClipDepthsSupport(bool) throw(Exception);
      
      bool supportsMultipleClipPARs() throw(Exception);
      void setMultipleClipPARsSupport(bool) throw(Exception);  
      
      int clipPreferencesSlaveParamCount() throw(Exception);
      std::string getClipPreferencesSlaveParam(int i) throw(Exception);
      void setClipPreferencesSlaveParam(int i, const std::string &n) throw(Exception);
      
      std::string pluginFilePath() throw(Exception);
      
      // for sub-classing
      virtual void describe() throw(Exception);
      virtual void describeInContext(ImageEffectContext ctx) throw(Exception);
  };
  
  class ImageEffect {
    protected:
      
      OfxImageEffectHandle mHandle;
      PropertySet mProps;
      ParameterSet mParams;
      ImageEffectHost *mHost;
      
      //static OfxImageEffectSuiteV1 * msSuiteV1;
      static std::map<OfxImageEffectHandle, ImageEffect*> msEffects;
      
      ImageEffect();
      
    public:
      
      //static void Init(Host *h) throw(Exception);
      
      static ImageEffect* GetEffect(OfxImageEffectHandle hdl);
      
    public:
      
      //ImageEffect();
      ImageEffect(ImageEffectHost *h, OfxImageEffectHandle hdl) throw(Exception);
      //ImageEffect(const ImageEffect &rhs);
      virtual ~ImageEffect();
      
      //ImageEffect& operator=(const ImageEffect &rhs);
      //ImageEffect& operator=(OfxImageEffectHandle hdl);
      
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
      
      ImageEffectContext context() throw(Exception);
      
      void* instanceData() throw(Exception);
      void setInstanceData(void *data) throw(Exception);
      
      void projectSize(double &w, double &h) throw(Exception);
      
      void projectOffset(double &x, double &y) throw(Exception);
      
      void projectExtent(double &w, double &h) throw(Exception);
      
      double projectPixelAspectRatio() throw(Exception);
      
      double duration() throw(Exception);
      
      bool needsSequentialRender() throw(Exception);
      void requireSequentialRender(bool) throw(Exception);
      
      double frameRate() throw(Exception);
      
      bool isInteractive() throw(Exception);
      
      // for sub-classing
      
      virtual void beginInstanceChanged(ChangeReason reason) throw(Exception);
      
      virtual void endInstanceChanged(ChangeReason reason) throw(Exception);
      
      virtual void instanceChanged(Type typ, const std::string &name, ChangeReason reason,
                                   Time t, double renderScaleX, double renderScaleY) throw(Exception);
      
      virtual void purgeCaches() throw(Exception);
      
      virtual void syncPrivateData() throw(Exception);
      
      virtual void beginInstanceEdit() throw(Exception);
      
      virtual void endInstanceEdit() throw(Exception);
      
      virtual Rect<double> getRegionOfDefinition(Time t, double renderScaleX, double renderScaleY) throw(Exception);
      
      virtual void getRegionsOfInterest(Time t, double renderScaleX, double renderScaleY,
                                        const Rect<double> &outRoI,
                                        std::map<std::string, Rect<double> > &inClipsRoI) throw(Exception);
      
      virtual void getFramesNeeded(Time t, std::map<std::string, FrameRangeList> &clipsFrameRange) throw(Exception);
      
      virtual bool isIdentity(Time t, ImageField field, const Rect<int> &renderWindow,
                              double renderScaleX, double renderScaleY,
                              std::string &idClip, Time &idTime) throw(Exception);
      
      virtual void render(Time t, ImageField field, const Rect<int> &renderWindow,
                          double renderScaleX, double renderScaleY) throw(Exception);
      
      virtual void beginSequenceRender(const FrameRange &range, int step, bool interactive,
                                       double renderScaleX, double renderScaleY) throw(Exception);
      
      virtual void endSequenceRender(const FrameRange &range, int step, bool interactive,
                                     double renderScaleX, double renderScaleY) throw(Exception);
      
      virtual void getClipPreferences(ClipPreferences &outPrefs,
                                      std::map<std::string, PixelPreferences> &inClipsPrefs) throw(Exception);
      
      virtual void getTimeDomain(double &first, double &last) throw(Exception);
  };
}

#endif
