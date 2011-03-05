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

/** \file interact.h
 *  Interact descriptor and instance classes.
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
  
  //! %Interact descriptor classe.
  class InteractDescriptor {
    public:
      
      InteractDescriptor();
      InteractDescriptor(ImageEffectHost *h, OfxInteractHandle hdl) throw(Exception);
      InteractDescriptor(const InteractDescriptor &rhs);
      virtual ~InteractDescriptor();
      
      InteractDescriptor& operator=(const InteractDescriptor &rhs);
      
      // properties
      
      //! Check if interact's frame buffer has an alpha component.
      bool hasAlpha();
      
      //! Get component bit depth if the interact's frame buffer.
      int bitDepth();
      
      // Interact actions
      
      //! Describe action.
      virtual OfxStatus describe();
    
    protected:
      
      OfxInteractHandle mHandle;
      PropertySet mProps;
  };
  
  
  //! %Interact instance classe.
  class Interact {
    public:
      
      static Interact* GetInteract(OfxInteractHandle hdl);
      
    public:
      
      //! Arguments shared for all actions.
      struct BaseArgs {
        ImageEffect *effect; //!< Effect object.
        Time time; //!< Time the action is called at.
        double renderScaleX; //!< Render scale along X axis.
        double renderScaleY; //!< Render scale along Y axis.
        
        BaseArgs(ImageEffectHost *h, PropertySet &args);
      };
      
      //! Arguments common to all by key actions.
      struct CommonArgs : public BaseArgs {
        //int viewportWidth;
        //int viewportHeight;
        double pixelScaleX; //!< Scale factor to convert from canonical to screen coordinates along X axis.
        double pixelScaleY; //!< Scale factor to convert from canonical to screen coordinates along Y axis.
        RGBAColour<double> bgColour; //!< Background colour.
        
        CommonArgs(ImageEffectHost *h, PropertySet &args);
      };
      
      //! Draw action arguments.
      typedef CommonArgs DrawArgs;
      
      //! Focus actions arguments.
      typedef CommonArgs FocusArgs;
      
      //! Pen actions arguments.
      struct PenArgs : public CommonArgs {
        double x; //!< Pen X position in canonical coordinates.
        double y; //!< Pen Y position in canonical coordinates.
        double pressure; //!< pressure of the pen.
#ifdef OFX_API_1_2
        int viewportX; //!< Pen X position in viewport coordinates.
        int viewportY; //!< Pen Y position in viewport coordinates.
#endif
        
        PenArgs(ImageEffectHost *h, PropertySet &args);
      };
      
      //! Key actions arguments.
      struct KeyArgs : public BaseArgs {
        int sym; //!< Key sym
        std::string string; //!< Key as a string.
        
        KeyArgs(ImageEffectHost *h, PropertySet &args);
      };
      
    public:
      
      Interact();
      Interact(ImageEffectHost *h, OfxInteractHandle hdl) throw(Exception);
      virtual ~Interact();
      
      // suite
      
      //! Swap framebuffer.
      void swapBuffers() throw(Exception);
      //! Redraw interact.
      void redraw() throw(Exception);
      
      // properties
      
      //! Get associated image effect instance object.
      ImageEffect* effectInstance();
      
      //! Get user data pointer.
      void* instanceData();
      //! Set user data pointer.
      void instanceData(void *d);
      
      //! Get size of a real screen pixel.
      void pixelScale(double *sx, double *sy);
      
      //! Get background colour.
      RGBAColour<double> backgroundColour();
      
      //! Get viewport size.
      void viewportSize(int *w, int *h);
      
      //! Check if interact's frame buffer has an alpha component.
      bool hasAlpha();
      
      //! Get component bit depth if the interact's frame buffer.
      int bitDepth();
      
      //! Get number of parameters the interact depends on.
      int slaveToParamCount();
      //! Get ith parameter name the interact depends on.
      std::string slaveToParam(int i);
      //! Add/Set ith parameter name the interact depends on.
      void slaveToParam(int i, const std::string &pn);
      
#ifdef OFX_API_1_2
      /** Get suggested colour.
       *  \note OpenFX version >= 1.2.
       */
      RGBAColour<double> suggestedColour();
#endif
      
      // Interact actions
      
      /** Draw action
       *  \param[in] args The action arguments.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus draw(DrawArgs &args);
      
      /** Pen motion action
       *  \param[in] args The action arguments.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus penMotion(PenArgs &args);
      
      /** Pen down action
       *  \param[in] args The action arguments.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus penDown(PenArgs &args);
      
      /** Pen up action
       *  \param[in] args The action arguments.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus penUp(PenArgs &args);
      
      /** Key down action
       *  \param[in] args The action arguments.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus keyDown(KeyArgs &args);
      
      /** Key up action
       *  \param[in] args The action arguments.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus keyUp(KeyArgs &args);
      
      /** Key repeat action
       *  \param[in] args The action arguments.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus keyRepeat(KeyArgs &args);
      
      /** Gain focus action
       *  \param[in] args The action arguments.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus gainFocus(FocusArgs &args);
      
      /** Lose focus action
       *  \param[in] args The action arguments.
       *  \return kOfxStatOK if action was overriden, kOfxStatReplyDefault otherwise.
       */
      virtual OfxStatus loseFocus(FocusArgs &args);
      
    protected:
      
      OfxInteractHandle mHandle;
      PropertySet mProps;
      OfxInteractSuiteV1 *mSuite;
      
      static std::map<OfxInteractHandle, Interact*> msInteracts;
  };
  
  
  //! %Interact entry point function wrapper.
  template <class PluginClass, class DescriptorClass, class InstanceClass>
  OfxStatus InteractEntryPoint(const char *action,
                               const void *handle,
                               OfxPropertySetHandle hInArgs,
                               OfxPropertySetHandle)
  {
    ImageEffectHost *host = PluginClass::Instance()->host();
    
    OfxInteractHandle hInteract = (OfxInteractHandle) handle;
    
    PropertySet inArgs(host, hInArgs);
    
    Action a = StringToAction(action);
    
    InstanceClass *ic = (InstanceClass*) Interact::GetInteract(hInteract);
    
    try {
      switch (a) {
      case ActionDescribe: {
        DebugLog("OFX Overlay Interact: Describe");
        DescriptorClass desc(host, hInteract);
        return desc.describe();
      }
      case ActionCreateInstance: {
        DebugLog("OFX Overlay Interact: Create instance");
        new InstanceClass(host, hInteract);
        return kOfxStatOK;
      }
      case ActionDestroyInstance: {
        DebugLog("OFX Overlay Interact: Destroy instance");
        if (ic) {
          delete ic;
        }
        return kOfxStatOK;
      }
      case ActionInteractDraw: {
        DebugLog("OFX Overlay Interact: Draw");
        Interact::DrawArgs args(host, inArgs);
        return ic->draw(args);
      }
      case ActionInteractPenMotion: {
        DebugLog("OFX Overlay Interact: Pen motion");
        Interact::PenArgs args(host, inArgs);
        return ic->penMotion(args);
      }
      case ActionInteractPenUp: {
        DebugLog("OFX Overlay Interact: Pen up");
        Interact::PenArgs args(host, inArgs);
        return ic->penUp(args);
      }
      case ActionInteractPenDown: {
        DebugLog("OFX Overlay Interact: Pen down");
        Interact::PenArgs args(host, inArgs);
        return ic->penDown(args);
      }
      case ActionInteractKeyDown: {
        DebugLog("OFX Overlay Interact: Key down");
        Interact::KeyArgs args(host, inArgs);
        return ic->keyDown(args);
      }
      case ActionInteractKeyUp: {
        DebugLog("OFX Overlay Interact: Key up");
        Interact::KeyArgs args(host, inArgs);
        return ic->keyUp(args);
      }
      case ActionInteractKeyRepeat: {
        DebugLog("OFX Overlay Interact: Key repeat");
        Interact::KeyArgs args(host, inArgs);
        return ic->keyRepeat(args);
      }
      case ActionInteractGainFocus: {
        DebugLog("OFX Overlay Interact: Gain focus");
        Interact::FocusArgs args(host, inArgs);
        return ic->gainFocus(args);
      }
      case ActionInteractLoseFocus: {
        DebugLog("OFX Overlay Interact: Lose focus");
        Interact::FocusArgs args(host, inArgs);
        return ic->loseFocus(args);
      }
      default:
        return kOfxStatReplyDefault; // there's another value here
      }
      
    } catch (Exception &e) {
      Log("*** Caught exception");
      Log("***   %s", e.what());
      return e.status();
    }
  }
}

#endif
