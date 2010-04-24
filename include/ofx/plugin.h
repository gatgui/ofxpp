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
  
  template <class Descriptor, class Effect>
  class ImageEffectPlugin : public Plugin {
    public:
      
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
            ImageEffect::InstanceChangedArgs args(inArgs);
            effect->instanceChanged(args);
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
            ImageEffect::GetRoDArgs args(inArgs);
            effect->getRegionOfDefinition(args);
            args.setOutputs(outArgs);
            break;
          }
          case ActionImageEffectGetRoI: {
            Effect *effect = plugin->getEffect(hEffect);
            ImageEffect::GetRoIArgs args(inArgs);
            effect->getRegionsOfInterest(args);
            args.setOutputs(outArgs);
            break;
          }
          case ActionImageEffectGetFramesNeeded: {
            Effect *effect = plugin->getEffect(hEffect);
            ImageEffect::GetFramesNeededArgs args(inArgs);
            effect->getFramesNeeded(args);
            args.setOutputs(outArgs);
            break;
          }
          case ActionImageEffectIsIdentity: {
            Effect *effect = plugin->getEffect(hEffect);
            ImageEffect::IsIdentityArgs args(inArgs);
            if (effect->isIdentity(args)) {
              args.setOutputs(outArgs);
            }
            break;
          }
          case ActionImageEffectRender: {
            Effect *effect = plugin->getEffect(hEffect);
            ImageEffect::RenderArgs args(inArgs);
            effect->render(args);
            break;
          }
          case ActionImageEffectBeginSequenceRender: {
            Effect *effect = plugin->getEffect(hEffect);
            ImageEffect::SequenceArgs args(inArgs);
            effect->beginSequenceRender(args);
            break;
          }
          case ActionImageEffectEndSequenceRender: {
            Effect *effect = plugin->getEffect(hEffect);
            ImageEffect::SequenceArgs args(inArgs);
            effect->endSequenceRender(args);
            break;
          }
          case ActionImageEffectGetClipPreferences: {
            Effect *effect = plugin->getEffect(hEffect);
            ImageEffect::GetClipPrefArgs args;
            effect->getClipPreferences(args);
            args.setOutputs(outArgs);
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
