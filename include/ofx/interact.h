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

#ifndef __ofx_interact_h__
#define __ofx_interact_h__

#include <ofxInteract.h>
#include <ofxKeySyms.h>
#include <ofx/ofx.h>
#include <ofx/property.h>
#include <ofx/imageeffect.h>
#include <map>

namespace ofx {
  
  class Host;
  
  class InteractDescriptor {
    protected:
      
      //static OfxInteractSuiteV1 * msSuiteV1;
      
      OfxInteractHandle mHandle;
      PropertySet mProps;
      
    public:
      
      friend class Interact;
      
      InteractDescriptor();
      InteractDescriptor(ImageEffectHost *h, OfxInteractHandle hdl) throw(Exception);
      InteractDescriptor(const InteractDescriptor &rhs);
      ~InteractDescriptor();
      
      InteractDescriptor& operator=(const InteractDescriptor &rhs);
      //InteractDescriptor& operator=(OfxInteractHandle hdl);
      
      // properties
      
      bool hasAlpha() throw(Exception);
      
      int bitDepth() throw(Exception);
      
      // for sub-classing
      
      virtual void describe() throw(Exception);
  };
  
  class Interact {
    protected:
      
      //static OfxInteractSuiteV1 * msSuiteV1;
      
      OfxInteractHandle mHandle;
      PropertySet mProps;
      OfxInteractSuiteV1 *mSuite;
      
    //public:
    //  
    //  static void Init(Host *h) throw(Exception);
      
      static std::map<OfxInteractHandle, Interact*> msInteracts;
    
    public:
      
      static Interact* GetInteract(OfxInteractHandle hdl);
      
    public:
      
      Interact();
      Interact(ImageEffectHost *h, OfxInteractHandle hdl) throw(Exception);
      //Interact(const Interact &rhs);
      ~Interact();
      
      //Interact& operator=(const Interact &rhs);
      //Interact& operator=(OfxInteractHandle hdl);
      
      // suite
      
      void swapBuffers() throw(Exception);
      void redraw() throw(Exception);
      
      // properties
      
      // Review this one
      ImageEffect* effectInstance() throw(Exception);
      
      void* instanceData() throw(Exception);
      void setInstanceData(void *d) throw(Exception);
      
      void pixelScale(double &sx, double &sy) throw(Exception);
      
      RGBAColour<double> backgroundColor() throw(Exception);
      
      void viewportSize(int &w, int &h) throw(Exception);
      
      bool hasAlpha() throw(Exception);
      
      int bitDepth() throw(Exception);
      
      int slaveToParamCount() throw(Exception);
      std::string getSlaveToParam(int i) throw(Exception);
      void setSlaveToParam(int i, const std::string &pn) throw(Exception);
      
      // for sub-classing
      
      virtual void draw(ImageEffect *effect, //int w, int h,
                        double pixelScaleX, double pixelScaleY,
                        const RGBAColour<double> &bgColor, Time t,
                        double renderScaleX, double renderScaleY) throw(Exception);
      
      virtual void penMotion(ImageEffect *effect, //int w, int h,
                             double pixelScaleX, double pixelScaleY,
                             const RGBAColour<double> &bgColor, Time t,
                             double renderScaleX, double renderScaleY,
                             double penX, double penY, double pressure) throw(Exception);
      
      virtual void penDown(ImageEffect *effectt, //int w, int h,
                           double pixelScaleX, double pixelScaleY,
                           const RGBAColour<double> &bgColor, Time t,
                           double renderScaleX, double renderScaleY,
                           double penX, double penY, double pressure) throw(Exception);
      
      virtual void penUp(ImageEffect *effect, //int w, int h,
                         double pixelScaleX, double pixelScaleY,
                         const RGBAColour<double> &bgColor, Time t,
                         double renderScaleX, double renderScaleY,
                         double penX, double penY, double pressure) throw(Exception);
      
      virtual void keyDown(ImageEffect *effect,
                           int keySym, const std::string &keyStr,
                           Time t, double renderScaleX, double renderScaleY) throw(Exception);
      
      virtual void keyUp(ImageEffect *effect,
                         int keySym, const std::string &keyStr,
                         Time t, double renderScaleX, double renderScaleY) throw(Exception);
      
      virtual void keyRepeat(ImageEffect *effect,
                             int keySym, const std::string &keyStr,
                             Time t, double renderScaleX, double renderScaleY) throw(Exception);
      
      virtual void gainFocus(ImageEffect *effect, //int w, int h,
                             double pixelScaleX, double pixelScaleY,
                             const RGBAColour<double> &bgColor, Time t,
                             double renderScaleX, double renderScaleY) throw(Exception);
      
      virtual void loseFocus(ImageEffect *effect, //int w, int h,
                             double pixelScaleX, double pixelScaleY,
                             const RGBAColour<double> &bgColor, Time t,
                             double renderScaleX, double renderScaleY) throw(Exception);
  };
  
  
  // when you want to set an interact somewhere
  // obj->setOverlayInteract(InteractEntryPoint<MyPlugin, MyInteractDesc, MyInteract>)
  
  template <class PluginClass, class DescriptorClass, class InstanceClass>    
  OfxStatus InteractEntryPoint(const char *action,
                               const void *handle,
                               OfxPropertySetHandle hInArgs,
                               OfxPropertySetHandle hOutArgs) {
    
    ImageEffectHost *host = PluginClass::Instance()->host();
    
    OfxInteractHandle hInteract = (OfxInteractHandle) handle;
    
    PropertySet inArgs(host, hInArgs);
    PropertySet outArgs(host, hOutArgs);
    
    Action a = StringToAction(action);
    
    InstanceClass *ic = (InstanceClass*) Interact::GetInteract(hInteract);
    
    try {
      switch (a) {
      case ActionDescribe: {
        DescriptorClass desc(host, hInteract);
        desc.describe();
        break;
      }
      case ActionCreateInstance: {
        new InstanceClass(host, hInteract);
        break;
      }
      case ActionDestroyInstance: {
        if (ic) {
          delete ic;
        }
        break;
      }
      case ActionInteractDraw: {
        OfxImageEffectHandle hEffect = (OfxImageEffectHandle) inArgs.getPointer(kOfxPropEffectInstance, 0);
        //int w = inArgs.getInt(kOfxInteractPropViewportSize, 0);
        //int h = inArgs.getInt(kOfxInteractPropViewportSize, 1);
        double psx = inArgs.getDouble(kOfxInteractPropPixelScale, 0);
        double psy = inArgs.getDouble(kOfxInteractPropPixelScale, 1);
        RGBAColour<double> bg;
        bg.r = inArgs.getDouble(kOfxInteractPropBackgroundColour, 0);
        bg.g = inArgs.getDouble(kOfxInteractPropBackgroundColour, 1);
        bg.b = inArgs.getDouble(kOfxInteractPropBackgroundColour, 2);
        bg.a = 1.0;
        Time t = inArgs.getDouble(kOfxPropTime, 0);
        double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
        double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
        ic->draw(ImageEffect::GetEffect(hEffect), /*w, h,*/ psx, psy, bg, t, rsx, rsy);
        break;
      }
      case ActionInteractPenMotion: {
        OfxImageEffectHandle hEffect = (OfxImageEffectHandle) inArgs.getPointer(kOfxPropEffectInstance, 0);
        //int w = inArgs.getInt(kOfxInteractPropViewportSize, 0);
        //int h = inArgs.getInt(kOfxInteractPropViewportSize, 1);
        double psx = inArgs.getDouble(kOfxInteractPropPixelScale, 0);
        double psy = inArgs.getDouble(kOfxInteractPropPixelScale, 1);
        RGBAColour<double> bg;
        bg.r = inArgs.getDouble(kOfxInteractPropBackgroundColour, 0);
        bg.g = inArgs.getDouble(kOfxInteractPropBackgroundColour, 1);
        bg.b = inArgs.getDouble(kOfxInteractPropBackgroundColour, 2);
        bg.a = 1.0;
        Time t = inArgs.getDouble(kOfxPropTime, 0);
        double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
        double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
        double px = inArgs.getDouble(kOfxInteractPropPenPosition, 0);
        double py = inArgs.getDouble(kOfxInteractPropPenPosition, 1);
        double pp = inArgs.getDouble(kOfxInteractPropPenPressure, 0);
        ic->penMotion(ImageEffect::GetEffect(hEffect), /*w, h,*/ psx, psy, bg, t, rsx, rsy, px, py, pp);
        break;
      }
      case ActionInteractPenUp: {
        OfxImageEffectHandle hEffect = (OfxImageEffectHandle) inArgs.getPointer(kOfxPropEffectInstance, 0);
        //int w = inArgs.getInt(kOfxInteractPropViewportSize, 0);
        //int h = inArgs.getInt(kOfxInteractPropViewportSize, 1);
        double psx = inArgs.getDouble(kOfxInteractPropPixelScale, 0);
        double psy = inArgs.getDouble(kOfxInteractPropPixelScale, 1);
        RGBAColour<double> bg;
        bg.r = inArgs.getDouble(kOfxInteractPropBackgroundColour, 0);
        bg.g = inArgs.getDouble(kOfxInteractPropBackgroundColour, 1);
        bg.b = inArgs.getDouble(kOfxInteractPropBackgroundColour, 2);
        bg.a = 1.0;
        Time t = inArgs.getDouble(kOfxPropTime, 0);
        double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
        double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
        double px = inArgs.getDouble(kOfxInteractPropPenPosition, 0);
        double py = inArgs.getDouble(kOfxInteractPropPenPosition, 1);
        double pp = inArgs.getDouble(kOfxInteractPropPenPressure, 0);
        ic->penUp(ImageEffect::GetEffect(hEffect), /*w, h,*/ psx, psy, bg, t, rsx, rsy, px, py, pp);
        break;
      }
      case ActionInteractPenDown: {
        OfxImageEffectHandle hEffect = (OfxImageEffectHandle) inArgs.getPointer(kOfxPropEffectInstance, 0);
        //int w = inArgs.getInt(kOfxInteractPropViewportSize, 0);
        //int h = inArgs.getInt(kOfxInteractPropViewportSize, 1);
        double psx = inArgs.getDouble(kOfxInteractPropPixelScale, 0);
        double psy = inArgs.getDouble(kOfxInteractPropPixelScale, 1);
        RGBAColour<double> bg;
        bg.r = inArgs.getDouble(kOfxInteractPropBackgroundColour, 0);
        bg.g = inArgs.getDouble(kOfxInteractPropBackgroundColour, 1);
        bg.b = inArgs.getDouble(kOfxInteractPropBackgroundColour, 2);
        bg.a = 1.0;
        Time t = inArgs.getDouble(kOfxPropTime, 0);
        double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
        double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
        double px = inArgs.getDouble(kOfxInteractPropPenPosition, 0);
        double py = inArgs.getDouble(kOfxInteractPropPenPosition, 1);
        double pp = inArgs.getDouble(kOfxInteractPropPenPressure, 0);
        ic->penDown(ImageEffect::GetEffect(hEffect), /*w, h,*/ psx, psy, bg, t, rsx, rsy, px, py, pp);
        break;
      }
      case ActionInteractKeyDown: {
        OfxImageEffectHandle hEffect = (OfxImageEffectHandle) inArgs.getPointer(kOfxPropEffectInstance, 0);
        int key = inArgs.getInt(kOfxPropKeySym, 0);
        std::string keyStr = inArgs.getString(kOfxPropKeyString, 0);
        Time t = inArgs.getDouble(kOfxPropTime, 0);
        double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
        double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
        ic->keyDown(ImageEffect::GetEffect(hEffect), key, keyStr, t, rsx, rsy);
        break;
      }
      case ActionInteractKeyUp: {
        OfxImageEffectHandle hEffect = (OfxImageEffectHandle) inArgs.getPointer(kOfxPropEffectInstance, 0);
        int key = inArgs.getInt(kOfxPropKeySym, 0);
        std::string keyStr = inArgs.getString(kOfxPropKeyString, 0);
        Time t = inArgs.getDouble(kOfxPropTime, 0);
        double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
        double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
        ic->keyUp(ImageEffect::GetEffect(hEffect), key, keyStr, t, rsx, rsy);
        break;
      }
      case ActionInteractKeyRepeat: {
        OfxImageEffectHandle hEffect = (OfxImageEffectHandle) inArgs.getPointer(kOfxPropEffectInstance, 0);
        int key = inArgs.getInt(kOfxPropKeySym, 0);
        std::string keyStr = inArgs.getString(kOfxPropKeyString, 0);
        Time t = inArgs.getDouble(kOfxPropTime, 0);
        double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
        double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
        ic->keyRepeat(ImageEffect::GetEffect(hEffect), key, keyStr, t, rsx, rsy);
        break;
      }
      case ActionInteractGainFocus: {
        OfxImageEffectHandle hEffect = (OfxImageEffectHandle) inArgs.getPointer(kOfxPropEffectInstance, 0);
        //int w = inArgs.getInt(kOfxInteractPropViewportSize, 0);
        //int h = inArgs.getInt(kOfxInteractPropViewportSize, 1);
        double psx = inArgs.getDouble(kOfxInteractPropPixelScale, 0);
        double psy = inArgs.getDouble(kOfxInteractPropPixelScale, 1);
        RGBAColour<double> bg;
        bg.r = inArgs.getDouble(kOfxInteractPropBackgroundColour, 0);
        bg.g = inArgs.getDouble(kOfxInteractPropBackgroundColour, 1);
        bg.b = inArgs.getDouble(kOfxInteractPropBackgroundColour, 2);
        bg.a = 1.0;
        Time t = inArgs.getDouble(kOfxPropTime, 0);
        double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
        double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
        ic->gainFocus(ImageEffect::GetEffect(hEffect), /*w, h,*/ psx, psy, bg, t, rsx, rsy);
        break;
      }
      case ActionInteractLoseFocus: {
        OfxImageEffectHandle hEffect = (OfxImageEffectHandle) inArgs.getPointer(kOfxPropEffectInstance, 0);
        //int w = inArgs.getInt(kOfxInteractPropViewportSize, 0);
        //int h = inArgs.getInt(kOfxInteractPropViewportSize, 1);
        double psx = inArgs.getDouble(kOfxInteractPropPixelScale, 0);
        double psy = inArgs.getDouble(kOfxInteractPropPixelScale, 1);
        RGBAColour<double> bg;
        bg.r = inArgs.getDouble(kOfxInteractPropBackgroundColour, 0);
        bg.g = inArgs.getDouble(kOfxInteractPropBackgroundColour, 1);
        bg.b = inArgs.getDouble(kOfxInteractPropBackgroundColour, 2);
        bg.a = 1.0;
        Time t = inArgs.getDouble(kOfxPropTime, 0);
        double rsx = inArgs.getDouble(kOfxImageEffectPropRenderScale, 0);
        double rsy = inArgs.getDouble(kOfxImageEffectPropRenderScale, 1);
        ic->loseFocus(ImageEffect::GetEffect(hEffect), /*w, h,*/ psx, psy, bg, t, rsx, rsy);
        break;
      }
      default:
        return kOfxStatReplyDefault; // there's another value here
      }
      return kOfxStatOK;
      
    } catch (Exception &e) {
      return e.getStatus();
    }
  }
}

#endif
