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

/** \file imageeffect.h
 *  %Image effect descriptor and instance classes.
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
  
  //! %Image effect input/output clip preferences.
  struct ClipPreferences {
    ImageComponent components; //!< %Image pixel components.
    BitDepth bitDepth; //!< Pixel component depth.
    double pixelAspectRatio; //!< Pixel aspect ratio.
  };
  
  //! %Image effect output clip preferences.
  struct OutputClipPreferences {
    double frameRate; //!< Frame rate.
    ImageFieldOrder fieldOrder; //!< Field ordering.
    ImagePreMult preMult; //!< Pre multiplication state.
    bool continuousSamples; //!< true if effect can sample its output continuously.
    bool frameVarying; //!< true if, for the same parameter set, output may vary depending on time.
  };
  
  
  //! %Image effect descriptor class.
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
      
      //! Get image effect host pointer.
      inline ImageEffectHost* host() {
        return mHost;
      }
      
      //! Get descriptor native handle.
      inline OfxImageEffectHandle handle() {
        return mHandle;
      }
      
      //! Get associated properties.
      inline PropertySet& properties() {
        return mProps;
      }
      
      //! Get associated parameter set descriptor.
      inline ParameterSetDescriptor& parameters() {
        return mParams;
      }
      
      // suite
      
      //! Add a new clip to effect description.
      ClipDescriptor defineClip(const std::string &name) throw(Exception);
      
      // properties
      
      //! Get effect label.
      std::string label();
      //! Set effect label.
      void label(const std::string &s);
      
      //! Get effect short label.
      std::string shortLabel();
      //! Set effect short label.
      void shortLabel(const std::string &s);
      
      //! Get effect long label.
      std::string longLabel();
      //! Set effect long label.
      void longLabel(const std::string &s);
      
      //! Get number of supported image effect contexts.
      int supportedContextsCount();
      //! Get ith supported image effect context.
      ImageEffectContext supportedContext(int i);
      //! Add/Set ith supported image effect context.
      void supportedContext(int i, ImageEffectContext ctx);
      
      //! Get effect's group.
      std::string group();
      //! Set effect's group
      void group(const std::string &g);
      
      //! Check if effect should have no more than one instance.
      bool singleInstance();
      //! Set if effect should have no more than one instance.
      void singleInstance(bool);
      
      //! Get effect thread safety state.
      RenderThreadSafety renderThreadSafety();
      //! Set effect thread safety state.
      void renderThreadSafety(RenderThreadSafety rts);
      
      //! Check if effect relies on host for frame threading.
      bool hostFrameThreading();
      //! Set if effect relies on host for frame threading.
      void hostFrameThreading(bool);
      
      //! Get overlay interact entry point function.
      EntryPoint overlayInteract();
      /** Set overlay interact entry point function.
       *  \note One should use the InteractEntryPoint function wrapper.\n
       *        effectDesc->overlayInteract(InteractEntryPoint<MyPluginClass, MyInteractDescClass, MyInteractClass>)
       */
      void overlayInteract(EntryPoint func);
      
      //! Check if effect supports clips of differing resolutions.
      bool supportsMultiResolution();
      //! Set if effect supports clips of differing resolutions.
      void supportsMultiResolution(bool);
      
      //! Check if effect supports tiled images.
      bool supportsTiles();
      //! Set if effect supports tiled images.
      void supportsTiles(bool);
      
      //! Check if effect requires random temporal clip access.
      bool temporalClipAccess();
      //! Set if effect requires random temporal clip access.
      void temporalClipAccess(bool);
      
      //! Get the number of supported pixel depths.
      int supportedPixelDepthsCount();
      //! Add/Set the ith supported pixel depth.
      void supportedPixelDepth(int i, BitDepth bd);
      //! Get the ith supported pixel depth.
      BitDepth supportedPixelDepth(int i);
      
      //! Check if effect always needs its render function called twice for fielded images.
      bool fieldRenderTwiceAlways();
      /** Set if effect always needs its render function called twice for fielded images.
       *  \note if false, the render function will be called twice only if parameters are animated.
       */
      void fieldRenderTwiceAlways(bool);
      
      //! Check if effects supports clips of differing pixel depths.
      bool supportsMultipleClipDepths();
      //! Set if effects supports clips of differing pixel depths.
      void supportsMultipleClipDepths(bool);
      
      //! Check if effects supports clips of differing pixel aspect ratios.
      bool supportsMultipleClipPARs();
      //! Set if effects supports clips of differing pixel aspect ratios.
      void supportsMultipleClipPARs(bool);  
      
      //! Get the number of parameters clip preferences depend on.
      int clipPreferencesSlaveParamCount();
      //! Get the ith parameter name the clip preferences depend on.
      std::string clipPreferencesSlaveParam(int i);
      //! Set the ith parameter name the clip preferences depend on.
      void clipPreferencesSlaveParam(int i, const std::string &n);
      
      //! Get plugin binary file path.
      std::string pluginFilePath();
      
      //! Get effect sequential render state.
      SequentialRender sequentialRender();
      //! Set effect sequential render state.
      void sequentialRender(SequentialRender sr);
      
#ifdef OFX_API_1_2
      /** Get effect version.
       *  \note OpenFX version >= 1.2
       */
      int version(int level);
      /** Get effect major version (level = 0).
       *  \note OpenFX version >= 1.2
       */
      int majorVersion();
      /** Get effect minor version (level = 1).
       *  \note OpenFX version >= 1.2
       */
      int minorVersion();
      /** Set effect version.
       *  \note OpenFX version >= 1.2
       */
      void version(int level, int v);
      
      /** Get effect version label.
       *  \note OpenFX version >= 1.2
       */
      std::string versionLabel();
      /** Set effect version label.
       *  \note OpenFX version >= 1.2
       */
      void versionLabel(const std::string &vl);
      
      /** Get effect description.
       *  \note OpenFX version >= 1.2
       */
      std::string description();
      /** Set effect description.
       *  \note OpenFX version >= 1.2
       */
      void description(const std::string &vl);
#endif
      
#ifdef OFX_API_1_3
      
      bool supportsOpenGLRender(); 
      void supportsOpenGLRender(bool v);
      
      bool needsOpenGLRender();
      void needsOpenGLRender(bool v);
      
      int openGLPixelDepthsCount();
      void openGLPixelDepth(int i, BitDepth bd);
      BitDepth openGLPixelDepth(int i);
      
#endif
      
      // Image effect actions
      
      /** Descrbe the effect.
       *  \note This method must be overriden by sub-classes.\n
       *        It will be called when the effect entry point receive the ActionDescribe action.
       */
      virtual OfxStatus describe();
      /** Descrbe the effect in a given context.
       *  \note This method must be overriden by sub-classes.\n
       *        It will be called when the effect entry point receive the ActionDescribe action.
       */
      virtual OfxStatus describeInContext(ImageEffectContext ctx);
  };
  
  //! %Image effect instance class.
  class ImageEffect {
    public:
      
      //! Actions' render scale arguments.
      struct RenderScaleArgs {
        double renderScaleX; //!< Scale along X axis.
        double renderScaleY; //!< Scale along Y axis.
        
        RenderScaleArgs(ImageEffectHost *host, PropertySet &props);
      };
      
      //! Actions' time arguments.
      struct TimeArgs {
        Time time; //!< Time the action has been called at.
        
        TimeArgs(ImageEffectHost *host, PropertySet &props);
      };
      
      //! ActionInstanceChange action arguments.
      struct InstanceChangedArgs : public RenderScaleArgs, public TimeArgs {
        Type type; //!< %Type of the thing that was changed.
        std::string name; //!< Name of the thing that was changed.
        ChangeReason reason; //!< What triggered the change.
        
        InstanceChangedArgs(ImageEffectHost *host, PropertySet &props);
      };
      
      //! ActionImageEffectGetRoD action arguments.
      struct GetRoDArgs : public RenderScaleArgs, public TimeArgs {
        Rect<double> RoD; //!< [out] Effect's region of definition in canonical coordinates.
        
        GetRoDArgs(ImageEffectHost *host, PropertySet &in);
        void setOutputs(PropertySet &out);
      };
      
      //! Render actions arguments.
      struct RenderArgs : public RenderScaleArgs, public TimeArgs {
        ImageField field; //!< Current field.
        Rect<int> renderWindow; //!< Render window in pixel coordinates.
#ifdef OFX_API_1_2
        bool sequentialRender; //!< Whether the effect is currently being rendered in strict frame order on a single instance (OFX >= 1.2).
        bool interactiveRender; //!< If the render is in response to a user modifying the effect in an interactive session (OFX >= 1.2).
#endif
#ifdef OFX_API_1_3
        bool glEnabled;
        int glTextureIndex;
        int glTextureTarget;
#endif
        
        RenderArgs(ImageEffectHost *host, PropertySet &props);
      };
      
      //! ActionIsIdentity action arguments.
      struct IsIdentityArgs : public RenderArgs {
        std::string idClip; //!< [out] Name of the clip to copy to the output when effect is identity.
        Time idTime; //!< [out] Time to extract image of the idClip at when effect is identity.
        
        IsIdentityArgs(ImageEffectHost *host, PropertySet &in);
        void setOutputs(PropertySet &out);
      };
      
      //! ActionImageEffectGetRoI action arguments.
      struct GetRoIArgs : public RenderScaleArgs, public TimeArgs {
        Rect<double> outRoI; //!< Region of interest of the output clip in canonical coordinates.
        std::map<std::string, Rect<double> > inRoIs; //<! Region of interest in canonical coordinates for each input clip.
        
        GetRoIArgs(ImageEffectHost *host, PropertySet &in);
        void setOutputs(PropertySet &out);
        //! Set the RoI of an input clip.
        void setInputRoI(const std::string &name, const Rect<double> &RoI);
      };
      
      //! ActionImageEffectGetFramesNeeded action arguments.
      struct GetFramesNeededArgs : public TimeArgs {
        std::map<std::string, FrameRangeList> inRanges; //!< [out] List of required frame ranges for each input clips.
        
        GetFramesNeededArgs(ImageEffectHost *host, PropertySet &in);
        void setOutputs(PropertySet &out);
        //! Add a required frame range for an input clip.
        void addInputRange(const std::string &name, const FrameRange &range);
      };
      
      //! Sequence actions arguments.
      struct SequenceArgs : public RenderScaleArgs {
        bool interactive; //!< Is this a single frame render due to user interaction in a GUI, or a proper full sequence render.
#ifdef OFX_API_1_2
        bool sequentialRender; //!< Whether the effect is currently being rendered in strict frame order on a single instance (OFX >= 1.2).
        bool interactiveRender; //!< If the render is in response to a user modifying the effect in an interactive session (OFX >= 1.2).
#endif
#ifdef OFX_API_1_3
        bool glEnabled;
        int glTextureIndex;
        int glTextureTarget;
#endif
        
        SequenceArgs(ImageEffectHost *host, PropertySet &props);
      };
      
      //! ActionImageEffectBeginSequenceRender action arguments.
      struct BeginSequenceArgs : public SequenceArgs {
        FrameRange range; //!< Frame range to be rendered (inclusive).
        double step; //!< Frame step (typically 1 for full frame renders, 0.5 for fielded renders).
        
        // supposed to be the same in the specs for EndSequence action
        
        BeginSequenceArgs(ImageEffectHost *host, PropertySet &props);
      };
      
      //! ActionImageEffectEndSequenceRender action arguments.
      typedef SequenceArgs EndSequenceArgs;
      
      //! ActionImageEffectGetClipPreferences action arguments.
      struct GetClipPrefArgs {
        ImageEffectHost *host;
        OutputClipPreferences outPref; //!< [out] Output clip preferences.
        std::map<std::string, ClipPreferences> prefs; //!< [out] Preferences for each of the input/output clips.
        
        GetClipPrefArgs(ImageEffectHost *host);
        void setOutputs(PropertySet &out);
        //! Set named clip preferences.
        void setPref(const std::string &name, const ClipPreferences &pref);
      };
      
      //! ActionImageEffectGetTimeDomain action arguments.
      struct GetTimeDomainArgs {
        double first; //!< [out] Start frame.
        double last; //<! [out] End frame.
        
        GetTimeDomainArgs(ImageEffectHost *host);
        void setOutputs(PropertySet &out);
      };
      
    public:
      
      ImageEffect(ImageEffectHost *h, OfxImageEffectHandle hdl);
      virtual ~ImageEffect();
      
      //! Get image effect host pointer.
      inline ImageEffectHost* host() {
        return mHost;
      }
      
      //! Get associated properties.
      inline PropertySet& properties() {
        return mProps;
      }
      
      //! Get associated parameters.
      inline ParameterSet& parameters() {
        return mParams;
      }
      
      //! Get instance native handle.
      inline OfxImageEffectHandle handle() {
        return mHandle;
      }
      
      //! Set instance native handle.
      void handle(OfxImageEffectHandle handle) throw(Exception);
      
      // suite
      
      //! Get named clip.
      Clip getClip(const std::string &name) throw(Exception);
      //! Check if render should be aborted.
      bool abort() throw(Exception);
      
      //! Allocate arbitrary chunk of memory.
      OfxImageMemoryHandle alloc(size_t nBytes) throw(Exception);
      //! Allocate enough memory.to fit an image of given specification..
      OfxImageMemoryHandle alloc(int w, int h, ImageComponent comps, BitDepth depth) throw(Exception);
      //! Lock allocated memory
      void* lock(OfxImageMemoryHandle hdl) throw(Exception);
      //! Unlock allocated memory
      void unlock(OfxImageMemoryHandle hdl) throw(Exception);
      //! Free allocated memory
      void free(OfxImageMemoryHandle hdl) throw(Exception);
      
      // properties
      
      //! Get context.
      ImageEffectContext context();
      
      //! Get user data pointer.
      void* instanceData();
      //! Set user data pointer.
      void instanceData(void *data);
      
      //! Get project size.
      void projectSize(double *w, double *h);
      
      //! Get project offset.
      void projectOffset(double *x, double *y);
      
      //! Get project extent.
      void projectExtent(double *w, double *h);
      
      //! Get project pixel aspect ratio.
      double projectPixelAspectRatio();
      
      //! Get duration.
      double duration();
      
      //! Get sequential render state.
      SequentialRender sequentialRender();
      //! Set sequential render state.
      void sequentialRender(SequentialRender sr);
      
      //! Get frame rate.
      double frameRate();
      
      //! Check if the effect is being edited interactively.
      bool isInteractive();
      
      //! Check if effect is performing an analysis pass
      bool inAnalysis();
      //! Set if effect is performing an analysis pass
      void inAnalysis(bool v);
      
      //! Get descriptor.
      ImageEffectDescriptor descriptor();
      
#ifdef OFX_API_1_2
      /** Get description.
       *  \note OpenFX version >= 1.2
       */
      std::string description();
#endif
      
      // Image effect actions
      
      /** Begin instance changed action.
       *  \param[in] reason What triggered the change.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus beginInstanceChanged(ChangeReason reason);
      
      /** End instance changed action.
       *  \param[in] reason What triggered the change.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus endInstanceChanged(ChangeReason reason);
      
      /** Instance changed action.
       *  \param[in] args The action arguments.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus instanceChanged(InstanceChangedArgs &args);
      
      /** Purge caches action.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus purgeCaches();
      
      /** Synchronize private data action.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus syncPrivateData();
      
      /** Begin instance edit action.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus beginInstanceEdit();
      
      /** End instance edit action.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus endInstanceEdit();
      
      /** Get region of definition action.
       *  \param[in] args The action arguments..
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus getRegionOfDefinition(GetRoDArgs &args);
      
      /** Get regions of interest action.
       *  \param[in] args The action arguments..
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus getRegionsOfInterest(GetRoIArgs &args);
      
      /** Get frames needed action.
       *  \param[in] args The action arguments..
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus getFramesNeeded(GetFramesNeededArgs &args);
      
      /** Is identity action.
       *  \param[in] args The action arguments..
       *  \return kOfxStatOK if action was overriden and effect is identity, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus isIdentity(IsIdentityArgs &args);
      
      /** Render action.
       *  \param[in] args The action arguments..
       *  \return kOfxStatOK if effect was render properly.
       *  \note Sub classes must override this method.
       */
      virtual OfxStatus render(RenderArgs &args);
      
      /** Begin sequence render action.
       *  \param[in] args The action arguments..
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus beginSequenceRender(BeginSequenceArgs &args);
      
      /** End sequence render action.
       *  \param[in] args The action arguments..
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus endSequenceRender(EndSequenceArgs &args);
      
      /** Get clip preferences action.
       *  \param[in] args The action arguments..
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus getClipPreferences(GetClipPrefArgs &args);
      
      /** Get time domain action.
       *  \param[in] args The action arguments..
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus getTimeDomain(GetTimeDomainArgs &args);
      
#ifdef OFX_API_1_3
      
      /** OpenGL context attached action.
       *
       */
      virtual OfxStatus openGLContextAttached();
      
      /** OpenGL context to be detached action.
       *
       */
      virtual OfxStatus openGLContextDetached();
      
#endif
    
    protected:
      
      OfxImageEffectHandle mHandle;
      PropertySet mProps;
      ParameterSet mParams;
      ImageEffectHost *mHost;
      
      ImageEffect();
  };
  
  
}

#endif
