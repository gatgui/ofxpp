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
      
      inline void majorVersion(int v) {
        mPlugin.pluginVersionMajor = v;
      }
      
      inline void minorVersion(int v) {
        mPlugin.pluginVersionMinor = v;
      }
      
      inline void identifier(const char *ID) {
        mPlugin.pluginIdentifier = ID;
      }
      
      inline int majorVersion() const {
        return mPlugin.pluginVersionMajor;
      }
      
      inline int minorVersion() const {
        return mPlugin.pluginVersionMinor;
      }
      
      inline const char* identifier() const {
        return mPlugin.pluginIdentifier;
      }
      
    protected:
      
      OfxPlugin mPlugin;
  };
  
  template <class Descriptor, class Effect, class BaseClass=Plugin>
  class ImageEffectPlugin : public BaseClass {
    public:
      
      typedef ImageEffectPlugin<Descriptor, Effect, BaseClass> SelfType;
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
        if (!plugin) {
          Log("*** Invalid plugin");
          return kOfxStatErrBadHandle;
        }
        ImageEffectHost *host = plugin->host();
        if (!host) {
          Log("*** Invalid host");
          return kOfxStatErrBadHandle;
        }
        
        PropertySet inArgs(host, hInArgs);
        PropertySet outArgs(host, hOutArgs);
        
        OfxImageEffectHandle hEffect = (OfxImageEffectHandle) handle;
        
        Action a = StringToAction(action);
        
        try {
          switch (a) {
          case ActionLoad: {
            Log("OFX Image Effect Plugin: Load");
            host->init();
            return plugin->load();
          }
          case ActionUnload: {
            Log("OFX Image Effect Plugin: Unload");
            OfxStatus stat = plugin->unload();
            delete plugin;
            return stat;
          }
          case ActionDescribe: {
            Log("OFX Image Effect Plugin: Describe");
            Descriptor desc(host, hEffect);
            return desc.describe();
          }
          case ActionImageEffectDescribeInContext: {
            Log("OFX Image Effect Plugin: Describe in context");
            // might not be the same handle as in ActionDescribe
            Descriptor desc(host, hEffect);
            ImageEffectContext ctx = StringToImageEffectContext(inArgs.getString(kOfxImageEffectPropContext, 0));
            return desc.describeInContext(ctx);
          }
          case ActionCreateInstance: {
            Log("OFX Image Effect Plugin: Create instance");
            plugin->addEffect(hEffect);
            return kOfxStatOK;
          }
          case ActionDestroyInstance: {
            Log("OFX Image Effect Plugin: Destroy instance");
            plugin->removeEffect(hEffect);
            return kOfxStatOK;
          }
          case ActionBeginInstanceChanged: {
            Log("OFX Image Effect Plugin: Begin instance changed");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ChangeReason reason = StringToChangeReason(inArgs.getString(kOfxPropChangeReason, 0));
            return effect->beginInstanceChanged(reason);
          }
          case ActionEndInstanceChanged: {
            Log("OFX Image Effect Plugin: End instance changed");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ChangeReason reason = StringToChangeReason(inArgs.getString(kOfxPropChangeReason, 0));
            return effect->endInstanceChanged(reason);
          }
          case ActionInstanceChanged: {
            Log("OFX Image Effect Plugin: Instance changed");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ImageEffect::InstanceChangedArgs args(host, inArgs);
            return effect->instanceChanged(args);
          }
          case ActionPurgeCaches: {
            Log("OFX Image Effect Plugin: Purge caches");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            return effect->purgeCaches();
          }
          case ActionSyncPrivateData: {
            Log("OFX Image Effect Plugin: Sync private data");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            return effect->syncPrivateData();
          }
          case ActionBeginInstanceEdit: {
            Log("OFX Image Effect Plugin: Begin instance edit");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            return effect->beginInstanceEdit();
          }
          case ActionEndInstanceEdit: {
            Log("OFX Image Effect Plugin: End instance edit");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            return effect->endInstanceEdit();
          }
          case ActionImageEffectGetRoD: {
            Log("OFX Image Effect Plugin: Get region of definition");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ImageEffect::GetRoDArgs args(host, inArgs);
            OfxStatus stat = effect->getRegionOfDefinition(args);
            if (stat == kOfxStatOK) {
              args.setOutputs(outArgs);
            }
            return stat;
          }
          case ActionImageEffectGetRoI: {
            Log("OFX Image Effect Plugin: Get regions of interest");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ImageEffect::GetRoIArgs args(host, inArgs);
            OfxStatus stat = effect->getRegionsOfInterest(args);
            if (stat == kOfxStatOK) {
              args.setOutputs(outArgs);
            }
            return stat;
          }
          case ActionImageEffectGetFramesNeeded: {
            Log("OFX Image Effect Plugin: Get frames needed");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ImageEffect::GetFramesNeededArgs args(host, inArgs);
            OfxStatus stat = effect->getFramesNeeded(args);
            if (stat == kOfxStatOK) {
              args.setOutputs(outArgs);
            }
            return stat;
          }
          case ActionImageEffectIsIdentity: {
            Log("OFX Image Effect Plugin: Is identity");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ImageEffect::IsIdentityArgs args(host, inArgs);
            OfxStatus stat =  effect->isIdentity(args);
            if (stat == kOfxStatOK) {
              args.setOutputs(outArgs);
            }
            return stat;
          }
          case ActionImageEffectRender: {
            Log("OFX Image Effect Plugin: Render");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ImageEffect::RenderArgs args(host, inArgs);
            return effect->render(args);
          }
          case ActionImageEffectBeginSequenceRender: {
            Log("OFX Image Effect Plugin: Begin sequence render");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ImageEffect::BeginSequenceArgs args(host, inArgs);
            return effect->beginSequenceRender(args);
          }
          case ActionImageEffectEndSequenceRender: {
            Log("OFX Image Effect Plugin: End sequence render");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ImageEffect::EndSequenceArgs args(host, inArgs);
            return effect->endSequenceRender(args);
          }
          case ActionImageEffectGetClipPreferences: {
            Log("OFX Image Effect Plugin: Get clip preferences");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ImageEffect::GetClipPrefArgs args(host);
            OfxStatus stat = effect->getClipPreferences(args);
            if (stat == kOfxStatOK) {
              args.setOutputs(outArgs);
            }
            return stat;
          }
          case ActionImageEffectGetTimeDomain: {
            Log("OFX Image Effect Plugin: Get time domain");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ImageEffect::GetTimeDomainArgs args(host);
            OfxStatus stat = effect->getTimeDomain(args);
            if (stat == kOfxStatOK) {
              args.setOutputs(outArgs);
            }
            return stat;
          }
          default:
            return kOfxStatReplyDefault;
          }
          
        } catch (Exception &e) {
          Log("*** Caught exception");
          Log("***   %s", e.what());
          return e.status();
          
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
      
      virtual OfxStatus load() {
        return kOfxStatReplyDefault;
      }
      
      virtual OfxStatus unload() {
        return kOfxStatReplyDefault;
      }
      
      inline ImageEffectHost* host() {
        return mHost;
      }
      
      inline Effect* addEffect(OfxImageEffectHandle handle) {
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
      
      inline void removeEffect(OfxImageEffectHandle handle) {
        typename EffectMap::iterator it = mEffects.find(handle);
        if (it != mEffects.end()) {
          delete it->second;
          mEffects.erase(it);
        }
      }
      
    protected:
      
      ImageEffectPlugin()
        : BaseClass(), mHost(0) {
        OfxPlugin *plugin = BaseClass::description();
        plugin->pluginApi = kOfxImageEffectPluginApi;
        plugin->apiVersion = kOfxImageEffectPluginApiVersion;
        plugin->setHost = SelfType::SetHost;
        plugin->mainEntry = SelfType::Main;
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
  
  template <class Descriptor, class Effect, class BaseClass>
  typename ImageEffectPlugin<Descriptor, Effect, BaseClass>::SelfType * ImageEffectPlugin<Descriptor, Effect, BaseClass>::msInstance = 0;
}

#endif
