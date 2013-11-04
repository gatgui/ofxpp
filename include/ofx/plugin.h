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

/** \file plugin.h
 *  %Plugin classes.
 */

#ifndef __ofx_plugin_h__
#define __ofx_plugin_h__

#include <ofxCore.h>
#include <ofx/host.h>
#include <ofx/imageeffect.h>
#include <map>

namespace ofx {
  
  //! Base plugin class.
  class Plugin {
    
    public:
      
      Plugin();
      virtual ~Plugin();
      
      //! Get native ofx plugin description.
      inline OfxPlugin* description() {
        return &mPlugin;
      }
      
      //! Set major version.
      inline void majorVersion(int v) {
        mPlugin.pluginVersionMajor = v;
      }
      
      //! Set minor version.
      inline void minorVersion(int v) {
        mPlugin.pluginVersionMinor = v;
      }
      
      //! Set unique identifier.
      inline void identifier(const char *ID) {
        mIdentifier = ID;
        mPlugin.pluginIdentifier = mIdentifier.c_str();
      }
      
      //! Get major version.
      inline int majorVersion() const {
        return mPlugin.pluginVersionMajor;
      }
      
      //! Get minor version.
      inline int minorVersion() const {
        return mPlugin.pluginVersionMinor;
      }
      
      //! Get unique identifier.
      inline const char* identifier() const {
        return mPlugin.pluginIdentifier;
      }
      
    protected:
      
      OfxPlugin mPlugin;
      std::string mIdentifier;
  };
  
  /** %Image effect plugin class.
   *  A template class which given a Descriptor and Effect class will generate unique entry points and wrap handle provided by the host to appropriate classes.
   */
  template <class Descriptor, class Effect, class BaseClass=Plugin>
  class ImageEffectPlugin : public BaseClass {
    public:
      
      typedef ImageEffectPlugin<Descriptor, Effect, BaseClass> SelfType;
      typedef Descriptor EffectDescriptor;
      typedef Effect EffectInstance;
      typedef std::map<OfxImageEffectHandle, Effect*> EffectMap;
      
      //! %Image effect plugin set host entry point.
      static void SetHost(OfxHost *h) {
        Instance()->setHost(h);
        // If have anything to check on host...
        //ImageEffectHost *host = Instance()->host();
      }
      
      //! %Image effect plugin main entry point.
      static OfxStatus Main(const char *action, const void *handle,
                            OfxPropertySetHandle hInArgs,
                            OfxPropertySetHandle hOutArgs)
      {
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
            DebugLog("OFX Image Effect Plugin: Load");
            host->init();
            return plugin->load();
          }
          case ActionUnload: {
            DebugLog("OFX Image Effect Plugin: Unload");
            OfxStatus stat = plugin->unload();
            delete plugin;
            return stat;
          }
          case ActionDescribe: {
            DebugLog("OFX Image Effect Plugin: Describe");
            Descriptor desc(host, hEffect);
            return desc.describe();
          }
          case ActionImageEffectDescribeInContext: {
            DebugLog("OFX Image Effect Plugin: Describe in context");
            // might not be the same handle as in ActionDescribe
            Descriptor desc(host, hEffect);
            ImageEffectContext ctx = StringToImageEffectContext(inArgs.getString(kOfxImageEffectPropContext, 0));
            return desc.describeInContext(ctx);
          }
          case ActionCreateInstance: {
            DebugLog("OFX Image Effect Plugin: Create instance");
            plugin->addEffect(hEffect);
            return kOfxStatOK;
          }
          case ActionDestroyInstance: {
            DebugLog("OFX Image Effect Plugin: Destroy instance");
            plugin->removeEffect(hEffect);
            return kOfxStatOK;
          }
          case ActionBeginInstanceChanged: {
            DebugLog("OFX Image Effect Plugin: Begin instance changed");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ChangeReason reason = StringToChangeReason(inArgs.getString(kOfxPropChangeReason, 0));
            return effect->beginInstanceChanged(reason);
          }
          case ActionEndInstanceChanged: {
            DebugLog("OFX Image Effect Plugin: End instance changed");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ChangeReason reason = StringToChangeReason(inArgs.getString(kOfxPropChangeReason, 0));
            return effect->endInstanceChanged(reason);
          }
          case ActionInstanceChanged: {
            DebugLog("OFX Image Effect Plugin: Instance changed");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ImageEffect::InstanceChangedArgs args(host, inArgs);
            return effect->instanceChanged(args);
          }
          case ActionPurgeCaches: {
            DebugLog("OFX Image Effect Plugin: Purge caches");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            return effect->purgeCaches();
          }
          case ActionSyncPrivateData: {
            DebugLog("OFX Image Effect Plugin: Sync private data");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            return effect->syncPrivateData();
          }
          case ActionBeginInstanceEdit: {
            DebugLog("OFX Image Effect Plugin: Begin instance edit");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            return effect->beginInstanceEdit();
          }
          case ActionEndInstanceEdit: {
            DebugLog("OFX Image Effect Plugin: End instance edit");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            return effect->endInstanceEdit();
          }
          case ActionImageEffectGetRoD: {
            DebugLog("OFX Image Effect Plugin: Get region of definition");
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
            DebugLog("OFX Image Effect Plugin: Get regions of interest");
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
            DebugLog("OFX Image Effect Plugin: Get frames needed");
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
            DebugLog("OFX Image Effect Plugin: Is identity");
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
            DebugLog("OFX Image Effect Plugin: Render");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ImageEffect::RenderArgs args(host, inArgs);
            return effect->render(args);
          }
          case ActionImageEffectBeginSequenceRender: {
            DebugLog("OFX Image Effect Plugin: Begin sequence render");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ImageEffect::BeginSequenceArgs args(host, inArgs);
            return effect->beginSequenceRender(args);
          }
          case ActionImageEffectEndSequenceRender: {
            DebugLog("OFX Image Effect Plugin: End sequence render");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            ImageEffect::EndSequenceArgs args(host, inArgs);
            return effect->endSequenceRender(args);
          }
          case ActionImageEffectGetClipPreferences: {
            DebugLog("OFX Image Effect Plugin: Get clip preferences");
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
            DebugLog("OFX Image Effect Plugin: Get time domain");
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
#ifdef OFX_API_1_3
          case ActionOpenGLContextAttached: {
            DebugLog("OFX Image Effect Plugin: OpenGL Context Attached");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            return effect->openGLContextAttached();
          }
          case ActionOpenGLContextDetached: {
            DebugLog("OFX Image Effect Plugin: OpenGL Context Detached");
            Effect *effect = plugin->getEffect(hEffect);
            if (!effect) {
              Log("*** Invalid effect");
              return kOfxStatErrUnknown;
            }
            return effect->openGLContextDetached();
          }
#endif
          default:
            return kOfxStatReplyDefault;
          }
          
        } catch (Exception &e) {
          Log("*** Caught exception");
          Log("***   %s", e.what());
          return e.status();
          
        }
      }
      
      //! Get instance object.
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
      
      //! Load action.
      virtual OfxStatus load() {
        return kOfxStatReplyDefault;
      }
      
      //! Unload action.
      virtual OfxStatus unload() {
        return kOfxStatReplyDefault;
      }
      
      //! Get image effect host object.
      inline ImageEffectHost* host() {
        return mHost;
      }
      
      //! Add new effect instance for a native handle.
      inline Effect* addEffect(OfxImageEffectHandle handle) {
        Effect *effect = new Effect(mHost, handle);
        mEffects[handle] = effect;
        return effect;
      }
      
      //! Get effect instance object from its native handle.
      inline Effect* getEffect(OfxImageEffectHandle handle) {
        typename EffectMap::iterator it = mEffects.find(handle);
        if (it != mEffects.end()) {
          return it->second;
        } else {
          return 0;
        }
      }
      
      //! Remove effect instance associated with given native handle.
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
      
      //! \internal
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
