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
      
      OfxInteractHandle mHandle;
      PropertySet mProps;
      OfxInteractSuiteV1 *mSuite;
      
      static std::map<OfxInteractHandle, Interact*> msInteracts;
    
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
      
      virtual void draw(DrawArgs &args) throw(Exception);
      
      virtual void penMotion(PenArgs &args) throw(Exception);
      
      virtual void penDown(PenArgs &args) throw(Exception);
      
      virtual void penUp(PenArgs &args) throw(Exception);
      
      virtual void keyDown(KeyArgs &args) throw(Exception);
      
      virtual void keyUp(KeyArgs &args) throw(Exception);
      
      virtual void keyRepeat(KeyArgs &args) throw(Exception);
      
      virtual void gainFocus(FocusArgs &args) throw(Exception);
      
      virtual void loseFocus(FocusArgs &args) throw(Exception);
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
        Interact::DrawArgs args(inArgs);
        ic->draw(args);
        break;
      }
      case ActionInteractPenMotion: {
        Interact::PenArgs args(inArgs);
        ic->penMotion(args);
        break;
      }
      case ActionInteractPenUp: {
        Interact::PenArgs args(inArgs);
        ic->penUp(args);
        break;
      }
      case ActionInteractPenDown: {
        Interact::PenArgs args(inArgs);
        ic->penDown(args);
        break;
      }
      case ActionInteractKeyDown: {
        Interact::KeyArgs args(inArgs);
        ic->keyDown(args);
        break;
      }
      case ActionInteractKeyUp: {
        Interact::KeyArgs args(inArgs);
        ic->keyUp(args);
        break;
      }
      case ActionInteractKeyRepeat: {
        Interact::KeyArgs args(inArgs);
        ic->keyRepeat(args);
        break;
      }
      case ActionInteractGainFocus: {
        Interact::FocusArgs args(inArgs);
        ic->gainFocus(args);
        break;
      }
      case ActionInteractLoseFocus: {
        Interact::FocusArgs args(inArgs);
        ic->loseFocus(args);
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
