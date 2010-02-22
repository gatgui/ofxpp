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

#ifndef __ofx_plugin_h__
#define __ofx_plugin_h__

#include <ofxCore.h>
#include <ofx/host.h>
#include <ofx/imageeffect.h>
#include <map>

namespace ofx {
  
  
  class Plugin {
    
    public:
      
      Plugin();
      virtual ~Plugin();
      
      inline OfxPlugin* description() {
        return &mPlugin;
      }
      
      inline void setMajorVersion(int v) {
        mPlugin.pluginVersionMajor = v;
      }
      
      inline void setMinorVersion(int v) {
        mPlugin.pluginVersionMinor = v;
      }
      
      inline void setID(const char *ID) {
        mPlugin.pluginIdentifier = ID;
      }
      
    protected:
      
      OfxPlugin mPlugin;
  };
  
  template <class Descriptor, class Effect> //, const char *ID, int Major, int Minor>
  class ImageEffectPlugin : public Plugin {
    public:
      
      //typedef ImageEffectPlugin<Descriptor, Effect, ID, Major, Minor> SelfType;
      typedef ImageEffectPlugin<Descriptor, Effect> SelfType;
      typedef Descriptor EffectDescriptor;
      typedef Effect EffectInstance;
      typedef std::map<OfxImageEffectHandle, Effect*> EffectMap;
      
      static void SetHost(OfxHost *h) {
        Instance()->setHost(h);
        // If have anything to check on host...
        //ImageEffectHost *host = Instance()->host();
      }
      
      static OfxStatus Main(const char *action, const void *handle,
                            OfxPropertySetHandle hInArgs,
                            OfxPropertySetHandle hOutArgs) {
        
        SelfType *plugin = Instance();
        ImageEffectHost *host = plugin->host();
        
        PropertySet inArgs(host, hInArgs);
        PropertySet outArgs(host, hOutArgs);
        
        OfxImageEffectHandle hEffect = (OfxImageEffectHandle) handle;
        
        Action a = StringToAction(action);
        
        try {
          switch (a) {
          case ActionLoad: {
            host->init();
            plugin->load();
            break;
          }
          case ActionUnload: {
            plugin->unload();
            delete plugin;
            break;
          }
          case ActionDescribe: {
            Descriptor desc(host, hEffect);
            desc.describe();
            break;
          }
          case ActionImageEffectDescribeInContext: {
            // might not be the same handle as in ActionDescribe
            Descriptor desc(host, hEffect);
            ImageEffectContext ctx = StringToImageEffectContext(inArgs.getString(kOfxImageEffectPropContext, 0));
            desc.describeInContext(ctx);
            break;
          }
          case ActionCreateInstance: {
            plugin->addEffect(hEffect);
            break;
          }
          case ActionDestroyInstance: {
            plugin->remEffect(hEffect);
            break;
          }
          case ActionBeginInstanceChanged: {
            Effect *effect = plugin->getEffect(hEffect);
            ChangeReason reason = StringToChangeReason(inArgs.getString(kOfxPropChangeReason, 0));
            effect->beginInstanceChanged(reason);
            break;
          }
          case ActionEndInstanceChanged: {
            Effect *effect = plugin->getEffect(hEffect);
            ChangeReason reason = StringToChangeReason(inArgs.getString(kOfxPropChangeReason, 0));
            effect->endInstanceChanged(reason);
            break;
          }
          case ActionInstanceChanged: {
            Effect *effect = plugin->getEffect(hEffect);
            Type type = StringToType(inArgs.getString(kOfxPropType, 0));
            std::string name = inArgs.getString(kOfxPropName, 0);
            ChangeReason reason = StringToChangeReason(inArgs.getString(kOfxPropChangeReason, 0));
            Time t = inArgs.getDouble(kOfxPropTime, 0);
            double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
            double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
            effect->instanceChanged(type, name, reason, t, rsx, rsy);
            break;
          }
          case ActionPurgeCaches: {
            Effect *effect = plugin->getEffect(hEffect);
            effect->purgeCaches();
            break;
          }
          case ActionSyncPrivateData: {
            Effect *effect = plugin->getEffect(hEffect);
            effect->syncPrivateData();
            break;
          }
          case ActionBeginInstanceEdit: {
            Effect *effect = plugin->getEffect(hEffect);
            effect->beginInstanceEdit();
            break;
          }
          case ActionEndInstanceEdit: {
            Effect *effect = plugin->getEffect(hEffect);
            effect->endInstanceEdit();
            break;
          }
          case ActionImageEffectGetRoD: {
            Effect *effect = plugin->getEffect(hEffect);
            Time t = inArgs.getDouble(kOfxPropTime, 0);
            double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
            double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
            Rect<double> rod = effect->getRegionOfDefinition(t, rsx, rsy);
            outArgs.setDoubles(kOfxImageEffectPropRegionOfDefinition, 4, &(rod.x1));
            break;
          }
          case ActionImageEffectGetRoI: {
            static std::string outBaseName = "OfxImageClipPropRoI_";
            
            Effect *effect = plugin->getEffect(hEffect);
            Time t = inArgs.getDouble(kOfxPropTime, 0);
            double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
            double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
            Rect<double> outRoI;
            inArgs.getDoubles(kOfxImageEffectPropRegionOfInterest, 4, &(outRoI.x1));
            std::map<std::string, Rect<double> > clipsRoI;
            effect->getRegionsOfInterest(t, rsx, rsy, outRoI, clipsRoI);
            std::map<std::string, Rect<double> >::iterator it = clipsRoI.begin();
            while (it != clipsRoI.end()) {
              std::string name = outBaseName + it->first;
              outArgs.setDoubles(name.c_str(), 4, &(it->second.x1));
              ++it;
            }
            break;
          }
          case ActionImageEffectGetFramesNeeded: {
            static std::string outBaseName = "OfxImageClipPropFrameRange_";
            
            Effect *effect = plugin->getEffect(hEffect);
            Time t = inArgs.getDouble(kOfxPropTime, 0);
            std::map<std::string, FrameRangeList> clipsFrameRange;
            effect->getFramesNeeded(t, clipsFrameRange);
            std::map<std::string, FrameRangeList>::iterator it = clipsFrameRange.begin();
            while (it != clipsFrameRange.end()) {
              std::string outName = outBaseName + it->first;
              FrameRangeList &frl = it->second;
              int i = 0;
              for (size_t j=0; j<frl.size(); ++j, i+=2) {
                outArgs.setDouble(outName.c_str(), i, frl[j].first);
                outArgs.setDouble(outName.c_str(), i+1, frl[j].second);
              }
              ++it;
            }
            break;
          }
          case ActionImageEffectIsIdentity: {
            Effect *effect = plugin->getEffect(hEffect);
            Time t = inArgs.getDouble(kOfxPropTime, 0);
            ImageField field = StringToImageField(inArgs.getString(kOfxImageEffectPropFieldToRender, 0));
            Rect<int> renderWindow;
            inArgs.getInts(kOfxImageEffectPropRenderWindow, 4, &(renderWindow.x1));
            double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
            double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
            std::string idClip;
            Time idTime;
            if (effect->isIdentity(t, field, renderWindow, rsx, rsy, idClip, idTime)) {
              outArgs.setString(kOfxPropName, 0, idClip);
              outArgs.setDouble(kOfxPropTime, 0, idTime);
            }
            break;
          }
          case ActionImageEffectRender: {
            Effect *effect = plugin->getEffect(hEffect);
            Time t = inArgs.getDouble(kOfxPropTime, 0);
            ImageField field = StringToImageField(inArgs.getString(kOfxImageEffectPropFieldToRender, 0));
            Rect<int> renderWindow;
            inArgs.getInts(kOfxImageEffectPropRenderWindow, 4, &(renderWindow.x1));
            double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
            double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
            effect->render(t, field, renderWindow, rsx, rsy);
            break;
          }
          case ActionImageEffectBeginSequenceRender: {
            Effect *effect = plugin->getEffect(hEffect);
            FrameRange range;
            range.first = inArgs.getDouble(kOfxImageEffectPropFrameRange, 0);
            range.second = inArgs.getDouble(kOfxImageEffectPropFrameRange, 1);
            double step = inArgs.getDouble(kOfxImageEffectPropFrameStep, 0);
            bool interactive = (inArgs.getInt(kOfxPropIsInteractive, 0) == 1);
            double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
            double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
            effect->beginSequenceRender(range, step, interactive, rsx, rsy);
            break;
          }
          case ActionImageEffectEndSequenceRender: {
            Effect *effect = plugin->getEffect(hEffect);
            FrameRange range;
            range.first = inArgs.getDouble(kOfxImageEffectPropFrameRange, 0);
            range.second = inArgs.getDouble(kOfxImageEffectPropFrameRange, 1);
            double step = inArgs.getDouble(kOfxImageEffectPropFrameStep, 0);
            bool interactive = (inArgs.getInt(kOfxPropIsInteractive, 0) == 1);
            double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
            double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
            effect->endSequenceRender(range, step, interactive, rsx, rsy);
            break;
          }
          case ActionImageEffectGetClipPreferences: {
            static std::string compBase = "OfxImageClipPropComponents_";
            static std::string depthBase = "OfxImageClipPropDepth_";
            static std::string parBase = "OfxImageClipPropPAR_";
            
            Effect *effect = plugin->getEffect(hEffect);
            std::map<std::string, PixelPreferences> inClipsPrefs;
            ClipPreferences outClipPrefs;
            effect->getClipPreferences(outClipPrefs, inClipsPrefs);
            std::map<std::string, PixelPreferences>::iterator it = inClipsPrefs.begin();
            while (it != inClipsPrefs.end()) {
              std::string name;
              name = compBase + it->first;
              outArgs.setString(name.c_str(), 0, ImageComponentToString(it->second.components));
              name = depthBase + it->first;
              outArgs.setString(name.c_str(), 0, BitDepthToString(it->second.bitDepth));
              name = parBase + it->first;
              outArgs.setDouble(name.c_str(), 0, it->second.pixelAspectRatio);
              ++it;
            }
            outArgs.setDouble(kOfxImageEffectPropFrameRate, 0, outClipPrefs.frameRate);
            outArgs.setString(kOfxImageClipPropFieldOrder, 0, ImageFieldOrderToString(outClipPrefs.fieldOrder));
            outArgs.setString(kOfxImageEffectPropPreMultiplication, 0, ImagePreMultToString(outClipPrefs.preMult));
            outArgs.setInt(kOfxImageClipPropContinuousSamples, 0, (outClipPrefs.continuousSamples ? 1 : 0));
            outArgs.setInt(kOfxImageEffectFrameVarying, 0, (outClipPrefs.frameVarying ? 1 : 0));
            break;
          }
          case ActionImageEffectGetTimeDomain: {
            Effect *effect = plugin->getEffect(hEffect);
            double first, last;
            effect->getTimeDomain(first, last);
            outArgs.setDouble(kOfxImageEffectPropFrameRange, 0, first);
            outArgs.setDouble(kOfxImageEffectPropFrameRange, 1, last);
            break;
          }
          default:
            return kOfxStatReplyDefault;
          }
          return kOfxStatOK;
          
        } catch (Exception &e) {
          return e.getStatus();
          
        }
      }
      
      static SelfType* Instance() {
        //static SelfType instance;
        //return &instance;
        return msInstance;
      }
      
    public:
      
      virtual ~ImageEffectPlugin() {
        if (mHost) {
          delete mHost;
        }
        typename EffectMap::iterator it = mEffects.begin();
        while (it != mEffects.end()) {
          delete it->second;
          ++it;
        }
        msInstance = 0;
      }
      
      virtual void load() throw(Exception) {
        throw Exception(kOfxStatReplyDefault, "Not implemented");
      }
      
      virtual void unload() throw(Exception) {
        throw Exception(kOfxStatReplyDefault, "Not implemented");
      }
      
      inline ImageEffectHost* host() {
        return mHost;
      }
      
      inline Effect* addEffect(OfxImageEffectHandle handle) throw(Exception) {
        Effect *effect = new Effect(mHost, handle);
        mEffects[handle] = effect;
        return effect;
      }
      
      inline Effect* getEffect(OfxImageEffectHandle handle) {
        typename EffectMap::iterator it = mEffects.find(handle);
        if (it != mEffects.end()) {
          return it->second;
        } else {
          return 0;
        }
      }
      
      inline void remEffect(OfxImageEffectHandle handle) {
        typename EffectMap::iterator it = mEffects.find(handle);
        if (it != mEffects.end()) {
          delete it->second;
          mEffects.erase(it);
        }
      }
      
    protected:
      
      ImageEffectPlugin()
        : Plugin(), mHost(0) {
        mPlugin.pluginApi = kOfxImageEffectPluginApi;
        mPlugin.apiVersion = kOfxImageEffectPluginApiVersion;
        mPlugin.setHost = SelfType::SetHost;
        mPlugin.mainEntry = SelfType::Main;
        //mPlugin.pluginIdentifier = ID;
        //mPlugin.pluginVersionMajor = Major;
        //mPlugin.pluginVersionMinor = Minor;
        msInstance = this;
      }
      
      void setHost(OfxHost *h) {
        if (!mHost) {
          mHost = new ImageEffectHost(h);
        }
      }
      
    protected:
      
      ImageEffectHost *mHost;
      EffectMap mEffects;
      
      static SelfType *msInstance;
  };
  
  template <class Descriptor, class Effect>
  typename ImageEffectPlugin<Descriptor, Effect>::SelfType * ImageEffectPlugin<Descriptor, Effect>::msInstance = 0;
}

#endif
