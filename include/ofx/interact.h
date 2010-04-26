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
    public:
      
      //friend class Interact;
      
      InteractDescriptor();
      InteractDescriptor(ImageEffectHost *h, OfxInteractHandle hdl) throw(Exception);
      InteractDescriptor(const InteractDescriptor &rhs);
      ~InteractDescriptor();
      
      InteractDescriptor& operator=(const InteractDescriptor &rhs);
      
      // properties
      
      bool hasAlpha();
      
      int bitDepth();
      
      // Interact actions
      
      virtual OfxStatus describe();
    
    protected:
      
      OfxInteractHandle mHandle;
      PropertySet mProps;
  };
  
  class Interact {
    public:
      
      static Interact* GetInteract(OfxInteractHandle hdl);
      
    public:
      
      struct BaseArgs {
        ImageEffect *effect;
        Time time;
        double renderScaleX;
        double renderScaleY;
        
        BaseArgs(PropertySet &args);
      };
      
      struct CommonArgs : public BaseArgs {
        int viewportWidth;
        int viewportHeight;
        double pixelScaleX;
        double pixelScaleY;
        RGBAColour<double> bgColour;
        
        CommonArgs(PropertySet &args);
      };
      
      typedef CommonArgs DrawArgs;
      
      typedef CommonArgs FocusArgs;
      
      struct PenArgs : public CommonArgs {
        double x;
        double y;
        double pressure;
        
        PenArgs(PropertySet &args);
      };
      
      struct KeyArgs : public BaseArgs {
        int sym;
        std::string string;
        
        KeyArgs(PropertySet &args);
      };
      
    public:
      
      Interact();
      Interact(ImageEffectHost *h, OfxInteractHandle hdl) throw(Exception);
      ~Interact();
      
      // suite
      
      void swapBuffers() throw(Exception);
      void redraw() throw(Exception);
      
      // properties
      
      ImageEffect* effectInstance();
      
      void* instanceData();
      void setInstanceData(void *d);
      
      void pixelScale(double &sx, double &sy);
      
      RGBAColour<double> backgroundColor();
      
      void viewportSize(int &w, int &h);
      
      bool hasAlpha();
      
      int bitDepth();
      
      int slaveToParamCount();
      std::string getSlaveToParam(int i);
      void setSlaveToParam(int i, const std::string &pn);
      
      
      // Interact actions
      
      virtual OfxStatus draw(DrawArgs &args);
      virtual OfxStatus penMotion(PenArgs &args);
      virtual OfxStatus penDown(PenArgs &args);
      virtual OfxStatus penUp(PenArgs &args);
      virtual OfxStatus keyDown(KeyArgs &args);
      virtual OfxStatus keyUp(KeyArgs &args);
      virtual OfxStatus keyRepeat(KeyArgs &args);
      virtual OfxStatus gainFocus(FocusArgs &args);
      virtual OfxStatus loseFocus(FocusArgs &args);
      
    protected:
      
      OfxInteractHandle mHandle;
      PropertySet mProps;
      OfxInteractSuiteV1 *mSuite;
      
      static std::map<OfxInteractHandle, Interact*> msInteracts;
  };
  
  
  // when you want to set an interact somewhere
  // obj->setOverlayInteract(InteractEntryPoint<MyPlugin, MyInteractDesc, MyInteract>)
  
  template <class PluginClass, class DescriptorClass, class InstanceClass>
  OfxStatus InteractEntryPoint(const char *action,
                               const void *handle,
                               OfxPropertySetHandle hInArgs,
                               OfxPropertySetHandle) {
    
    ImageEffectHost *host = PluginClass::Instance()->host();
    
    OfxInteractHandle hInteract = (OfxInteractHandle) handle;
    
    PropertySet inArgs(host, hInArgs);
    
    Action a = StringToAction(action);
    
    InstanceClass *ic = (InstanceClass*) Interact::GetInteract(hInteract);
    
    try {
      switch (a) {
      case ActionDescribe: {
        Log("OFX Overlay Interact: Describe");
        DescriptorClass desc(host, hInteract);
        return desc.describe();
      }
      case ActionCreateInstance: {
        Log("OFX Overlay Interact: Create instance");
        new InstanceClass(host, hInteract);
        return kOfxStatOK;
      }
      case ActionDestroyInstance: {
        Log("OFX Overlay Interact: Destroy instance");
        if (ic) {
          delete ic;
        }
        return kOfxStatOK;
      }
      case ActionInteractDraw: {
        Log("OFX Overlay Interact: Draw");
        Interact::DrawArgs args(inArgs);
        return ic->draw(args);
      }
      case ActionInteractPenMotion: {
        Log("OFX Overlay Interact: Pen motion");
        Interact::PenArgs args(inArgs);
        return ic->penMotion(args);
      }
      case ActionInteractPenUp: {
        Log("OFX Overlay Interact: Pen up");
        Interact::PenArgs args(inArgs);
        return ic->penUp(args);
      }
      case ActionInteractPenDown: {
        Log("OFX Overlay Interact: Pen down");
        Interact::PenArgs args(inArgs);
        return ic->penDown(args);
      }
      case ActionInteractKeyDown: {
        Log("OFX Overlay Interact: Key down");
        Interact::KeyArgs args(inArgs);
        return ic->keyDown(args);
      }
      case ActionInteractKeyUp: {
        Log("OFX Overlay Interact: Key up");
        Interact::KeyArgs args(inArgs);
        return ic->keyUp(args);
      }
      case ActionInteractKeyRepeat: {
        Log("OFX Overlay Interact: Key repeat");
        Interact::KeyArgs args(inArgs);
        return ic->keyRepeat(args);
      }
      case ActionInteractGainFocus: {
        Log("OFX Overlay Interact: Gain focus");
        Interact::FocusArgs args(inArgs);
        return ic->gainFocus(args);
      }
      case ActionInteractLoseFocus: {
        Log("OFX Overlay Interact: Lose focus");
        Interact::FocusArgs args(inArgs);
        return ic->loseFocus(args);
      }
      default:
        return kOfxStatReplyDefault; // there's another value here
      }
      
    } catch (Exception &e) {
      Log("*** Caught exception");
      Log("***   %s", e.what());
      return e.getStatus();
    }
  }
}

#endif
