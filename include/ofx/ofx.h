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

/** \file ofx.h
 *  Common ofxpp definitions.
 */

/** \mainpage OFXpp library documentation.
 *  \section intro Introduction
 *  \section build Build
 *  In order to build OFXpp library, you will need git command line tools and SCons above 1.3.\n
 *  First, get the source code:
 *  \code
 *  git clone git://github.com/gatgui/ofxpp.git
 *  cd ofxpp
 *  git submodule init
 *  git submodule update
 *  \endcode
 *  Build it using:
 *  \code
 *  scons [flags] [target]
 *  \endcode
 *  Here is the list of available targets:\n
 *  - ofxpp: C++ object oriented library that wraps the OpenFX API.
 *  - pyofx: Python bindings of the ofxpp library.
 *  - pyplugin: OpenFX plugin in charge of loading python written plugins.
 *  - ellipseFade: Sample plugin.
 *  - multiBlur: Sample plugin.
 *  - gaussianBlur: Sample plugin.
 *  
 *  and flags:\n
 *  - ofxVersion={ver} (1.1 by default)
 *  - with-python={path_to_python_directory} (windows and OSX only)
 *  - x64=0|1
 *  - x86=0|1
 *  - debug=0|1
 *  - debugInfo=0|1 (windows only)
 *  - ofxNewMacPackaging=0|1 (OSX only, tells to use the newly defined architecture in OpenFX 1.2 for 64bit plugins, defaults to "0")
 *  - forceOverlayRedraw=0|1 (for ellipseFade, multiBlur targets only, defaults to "1")
 *
 *  So to build pyplugin for 32bit architectures using 2 processes:
 *  \code
 *  scons -j 2 x86=1 pyplugin
 *  \endcode
 *  This should create new directories in the current one containing the binaries.\n
 *  With the example above:
 *  \code
 *  release/
 *   |_ x86/
 *       |_ include/
 *       |_ lib/
 *       |   |_ libofxpp.a : C++ library.
 *       |   |_ python/
 *       |       |_ ofx.so : Python bindings.
 *       |_ openfx/
 *           |_ pyplugin.ofx.bundle : OpenFX plugin.
 *  \endcode
 *  \note x64 and x86 are mutually exclusive.\n
 *        You can of course use other SCons builtin flags (-c: clean, -j {n}: compile using n processes, ...).\n
 *        SCons handles dependencies, so building pyplugin will automatically build ofxpp and pyofx.
 *  
 *  \section plugin How to write a plugin
 *  \subsection plugcpp In C++
 *  For each effect you need to create at least 3 new classes.\n
 *  <ul>
 *  <li>A subclass of the ofx::ImageEffectDescriptor class.\n\n
 *  Override the ofx::ImageEffectDescriptor::describe and ofx::ImageEffectDescriptor::describeInContext methods.\n
 *  Provide a constructor that takes a ofx::ImageEffectHost pointer and a OfxImageEffectHandle as parameters.\n
 *  \n
 *  \code
 *  class MyEffectDesc : public ofx::ImageEffectDescriptor {
 *    
 *    public:
 *      MyEffectDesc(ofx::ImageEffectHost *host, OfxImageEffectHandle handle)
 *        : ofx::ImageEffectDescriptor(host, handle) {
 *        ...
 *      }
 *      
 *      virtual ~MyEffectDesc() {
 *      }
 *      
 *      ...
 *      
 *      virtual OfxStatus describe() {
 *        ...
 *        return kOfxStatOK;
 *      }
 *      
 *      virtual OfxStatus describeInContext(ofx::ImageEffectContext context) {
 *        ...
 *        return kOfxStatOK;
 *      }
 *  };
 *  \endcode
 *  \n
 *  </li>
 *  <li>A subclass of the ofx::ImageEffect class.\n\n
 *  Override at least the ofx::ImageEffect::render method.\n
 *  Provide a constructor that takes a ofx::ImageEffectHost pointer and a OfxImageEffectHandle as parameters.\n
 *  \n
 *  \code
 *  class MyEffect : public ofx::ImageEffect {
 *    public:
 *      
 *      MyEffect(ofx::ImageEffectHost *host, OfxImageEffectHandle handle)
 *        : ofx::ImageEffect(host, handle) {
 *        ...
 *      }
 *      
 *      virtual ~MyEffect() {
 *      }
 *      
 *      ...
 *      
 *      virtual OfxStatus render(ofx::ImageEffect::RenderArgs &args) {
 *        ...
 *        return kOfxStatOK;
 *      }
 *  };
 *  \endcode
 *  \n
 *  </li>
 *  <li>A subclass of the ofx::ImageEffectPlugin template class.\n\n
 *  You should provide your newly defined descriptor and effect classes for the template parmeters.\n
 *  Fill in your plugin version and unique identifier in the plugin constructor.
 *  \n
*   \code
 *  class MyPlugin : public ofx::ImageEffectPlugin<MyEffectDesc, MyEffect> {
 *    public:
 *      
 *      MyPlugin()
 *        : ofx::ImageEffectPlugin<MyEffectDesc, MyEffect>(host, handle) {
 *        majorVersion(1);
 *        minorVersion(0);
 *        identifier("gatgui.filter.myeffect"):
 *      }
 *      
 *      virtual ~MyPlugin() {
 *      }
 *  };
 *  \endcode
 *  \n
 *  </li>
 *  </ul>
 *  \n
 *  If you also want to have an overlay interact for your effect, you will need:
 *  <ul>
 *  <li>A subclass of the ofx::InteractDescriptor class.\n\n
 *  Override the ofx::InteractDescriptor::describe method.\n
 *  Provide a constructor that taks a ofx::ImageEffectHost pointer and a OfxInteractHandle as parameters.\n
 *  \n
 *  \code
 *  class MyInteractDesc : public ofx::InteractDescriptor {
 *    public:
 *      
 *      MyInteractDesc(ofx::ImageEffectHost *host, OfxInteractHandle handle)
 *        : ofx::InteractDescriptor(host, handle) {
 *        ...
 *      }
 *  
 *      virtual ~MyInteractDesc() {
 *      }
 *      
 *      ...
 *      
 *      virtual OfxStatus describe() {
 *        ...
 *        return kOfxStatOK;
 *      }
 *  }
 *  \endcode
 *  \n
 *  \note This one is optional, and you probably don't need it most of the time.\n
 *        You can use the defaulf ofx::InteractDescriptor instead.\n
 *  \n
 *  </li>
 *  <li>A subclass of the ofx::Interact class.\n\n
 *  Override at least the ofx::Interact::draw method.\n
 *  Provide a constructor that takes a ofx::ImageEffectHost pointer and a OfxInteractHandle as parameters.\n
 *  \n
 *  \code
 *  class MyInteract : public ofx::Interact {
 *    public:
 *      
 *      MyInteract(ofx::ImageEffectHost *host, OfxInteractHandle handle)
 *        : ofx::Interact(host, handle) {
 *        ...
 *      }
 *  
 *      virtual ~MyInteract() {
 *      }
 *      
 *      ...
 *      
 *      virtual OfxStatus draw(ofx::Interact::DrawArgs &args) {
 *        ...
 *        return kOfxStatOK;
 *      }
 *  }
 *  \endcode
 *  \n
 *  Don't forget to tell the host to use your interact in the "describeInContext" method:
 *  \n
 *  \code
 *  // Check if host supports overlay interacts.
 *  if (host()->supportsOverlays()) {
 *    // If you have decided to use the default interact descriptor, pass ofx::InteractDescriptor instead of MyInteractDesc.
 *    overlayInteract(ofx::InteractEntryPoint<MyPlugin, MyInteractDesc, MyInteract>);
 *  }
 *  \endcode
 *  \n
 *  </li>
 *  </ul>
 *  \n
 *  Last thing to do (beside implementing all those methods), is to define the OpenFX entry points the host will look for:
 *  \n
 *  \code
 *  OfxExport int OfxGetNumberOfPlugins(void) {
 *    return 1;
 *  }
 *
 *  OfxExport OfxPlugin* OfxGetPlugin(int i) {
 *    if (i == 0) {
 *      MyPlugin *p = new MyPlugin();
 *      return p->description();
 *    }
 *    return NULL;
 *  }
 *  \endcode
 *  \n
 *  In the "Examples" section, you will find the complete source code of a simple plugin called ellipseFade.\n
 *  \n
 *  \subsection plugpy In Python
 *  The python API tries to stricly follow the C++ one whenever possible.\n
 *  Still, there are some language related concept that cannot be translated straight into python.\n
 *  Amongst them, class templates and pointers needed a bit of work-around.\n
 *  Class templates issues are handled case by case, and the best way to understand how those bits of API are translated into python is yet to see real code.\n
 *  As for pointers, most of them are wrapped in a Handle class, whose main purpose is just to pass the pointers around.\n
 *  The only exception is for pointers that are supposed to be used to access image data. As in\n
 *  <ul><li>ofx::Image::pixelAddress</li>
 *  <li>ofx::ImageEffect::alloc (only the variant which take pixel data informations is available in python)</li>
 *  <li>ofx::ImageEffect::lock</li></ul>
 *  As there's no pointers in python, thus no pointer arithmetic, those are wrapped in special classes that also holds pixel type informations.\n
 *  The returned objects have then r, g, b, a, y, u, v attributes (depending on the actual pixel type, some might not be defined) and 3 extra methods,\n
 *  <ul><li>goto(x, y)</li>
 *  <li>next()</li>
 *  <li>prev()</li></ul>
 *  to respectively move to pixel at position (x,y), next pixel and previous pixel.\n
 *  \n
 *  For the remaining of the API, using the following rules should be enough to apply the C++ documenation to python code:\n
 *  <ul>
 *  <li>The ofx namespace is mapped to the ofx module</li>
 *  <li>Simple property get/set pairs are directly mapped to python object attributes</li>
 *  <li>Multi-dimensional parameters values are represented as tuples</li>
 *  <li>All suites related methods are also methods</li>
 *  </ul>
 *  \n
 *  I will re-use the code samples from the C++ section\n
 *  \n
 *  Effect descriptor class:\n
 *  \code
 *  class MyEffectDesc(ofx.ImageEffectDescriptor):
 *    def __init__(self, host, handle):
 *      ofx.ImageEffectDescriptor.__init__(self, host, handle)
 *    
 *    def describe(self):
 *      ...
 *      return ofx.StatOK
 *    
 *    def describeInContext(self, context):
 *      ...
 *      return ofx.StatOK
 *
 *  \endcode
 *  \n
 *  Effect class:\n
 *  \code
 *  class MyEffect(ofx.ImageEffect):
 *    def __init__(self, host, handle):
 *      ofx.ImageEffect.__init__(self, host, handle)
 *    
 *    def render(self, args):
 *      ...
 *      return ofx.StatOK
 *
 *  \endcode
 *  \n
 *  Interact descriptor class:\n
 *  \code
 *  class MyInteractDesc(ofx.InteractDescriptor):
 *    def __init__(self, host, handle):
 *      ofx.InteractDescriptor.__init__(self, host, handle)
 *    
 *    def describe(self):
 *      ...
 *      return ofx.StatOK
 *
 *  \endcode
 *  \n
 *  Interact class:\n
 *  \code
 *  class MyInteract(ofx.Interact):
 *    def __init__(self, host, handle):
 *      ofx.Interact.__init__(self, host, handle)
 *    
 *    def draw(self, args):
 *      ...
 *      return ofx.StatOK
 *
 *  \endcode
 *  \n
 *  Plugin class:\n
 *  \code
 *  class MyPlugin(ofx.ImageEffectPlugin):
 *    # This class attribute needs to be defined as it will be looked up internaly in the interact entry point function.
 *    Instance = None
 *    def __init__(self):
 *      # There are no templates in python, instead, just pass you new classes as arguments.
 *      ofx.ImageEffectPlugin.__init__(self, MyEffectDesc, MyEffect)
 *      # Set the plugin instance object (don't forget it, or there will be no visible interact)
 *      MyPlugin.Instance = self
 *      self.majorVersion = 1
 *      self.minorVersion = 0
 *      self.identifier = "gatgui.filter.mypyeffect"
 *  
 *  \endcode
 *  \n
 *  Bind the interact to your effect:\n
 *  \code
 *  if self.host.supportsOverlays:
 *    # There are no templates in python, instead, pass a tuple containing the plugin, interact descriptor and instance classes.
 *    self.overlayInteract = (MyPlugin, MyInteractDesc, MyInteract)
 *  \endcode
 *  \n
 *  OpenFX entry points:\n
 *  \code
 *  def OfxNumberOfPlugins():
 *    return 1
 *  
 *  def OfxGetPlugin(i):
 *    if i == 0:
 *      # Note here that we return the plugin object itself.
 *      return MyPlugin()
 *    return None
 *  
 *  \endcode
 *  \n
 *  You will also find the python version of "ellipseFade" plugin in the "Examples" section.\n
 *  \n
 *  \section usage Usage
 *  \subsection env Environment setup
 *  Add the OpenFX plugin "pyplugin" to your OFX_PLUGIN_PATH.\n
 *  You will also need to add the directory the ofx python module lies in to your PYTHONPATH.\n
 *  \note For nuke users, the .nuke folder in your home directory is automatically added to both the OFX_PLUGIN_PATH and PYTHONPATH.\n
 *        Just copying the plugin and the python module in your .nuke folder doesn't seem to work though. Any ideas?\n
 *  \subsection install Install python plugins
 *  The python loader looks for ".py" files in all the directories specified by the standard OFX_PLUGIN_PATH environment variable.\n
 *  \subsection limitation Limitations
 *  Python being an interpreted language, plugin written in it tends to be dog slow. There's nothing I can do about that sorry.\n
 *  Python is not really threads friendly. All python plugins are automatically set to be thread unsafe, but there are still some issues with interacts.\n
 *  If you try to use the overlay interact of a python effect that is still rendering, nasty things will happen. To say, from my tests on windows, Nuke would just freeze.\n
 *
 *  \example ellipseFade.py
 *  Mask the input image with an ellipse, gardually fading its content to black towards the edges. Python version.
 *  \example ellipseFade.cpp
 *  Mask the input image with an ellipse, gardually fading its content to black towards the edges. C++ version.
 */

#ifndef __ofx_ofx_h__
#define __ofx_ofx_h__

#include <ofxCore.h>
#include <ofxImageEffect.h>
#include <ofxParam.h>
#include <map>
#include <vector>
#include <string>
#include <limits>

#ifdef _MSC_VER
# pragma warning(disable:4290)
#endif

//! \internal
#define DECLARE_ENUM_MAP(Enum)\
  extern const char* Enum##ToString(Enum e);\
  extern Enum StringTo##Enum(const char *s);\
  inline Enum StringTo##Enum(const std::string &s) {\
    return StringTo##Enum(s.c_str());\
  }

//! \internal
#define BEGIN_ENUM_MAP(Enum)\
  static std::map<std::string, Enum> gsStringTo##Enum;\
  static const char *gs##Enum##ToString[Max##Enum];\
  static void Init##Enum##Mapping() {

//! \internal
#define ADD_ENUM_MAPPING(Enum, ID)\
  gsStringTo##Enum[kOfx##Enum##ID] = Enum##ID;\
    gs##Enum##ToString[int(Enum##ID)] = kOfx##Enum##ID;

//! \internal
#define ADD_ENUM_MAPPING_CUSTOM(Enum, EnumVal, StringVal)\
  gsStringTo##Enum[StringVal] = EnumVal;\
    gs##Enum##ToString[int(EnumVal)] = StringVal;

//! \internal
#define END_ENUM_MAP(Enum)\
  }\
  const char* Enum##ToString(Enum i) {\
    if (gsStringTo##Enum.size() == 0) {\
      Init##Enum##Mapping();\
    }\
    int idx = int(i);\
    if (idx < 0 || idx >= Max##Enum) {\
      return 0;\
    } else {\
      return gs##Enum##ToString[idx];\
    }\
  }\
  Enum StringTo##Enum(const char *s) {\
    if (gsStringTo##Enum.size() == 0) {\
      Init##Enum##Mapping();\
    }\
    std::map<std::string, Enum>::iterator it = gsStringTo##Enum.find(s);\
    if (it == gsStringTo##Enum.end()) {\
      return Enum(-1);\
    } else {\
      return it->second;\
    }\
  }


//! ofx namespace.
namespace ofx {
  
  //! ofxpp library version as a string {major}.{minor}.{patch}
  extern const char *Version;
  
  //! ofxpp library major version. (same as wrapped OpenFX API)
  extern int MajorVersion;
  
  //! ofxpp library minor version. (same as wrapped OpenFX API)
  extern int MinorVersion;
  
  //! ofxpp patch level.
  extern int PatchVersion;
  
  
  //! Handle type enumeration.
  enum Type {
    TypeImageEffectHost = 0, //!< %Image effect host handle.
    TypeImageEffect, //!< %Image effect descriptor handle.
    TypeImageEffectInstance, //!< %Image effect instance handle.
    TypeParameter, //!< %Parameter descriptor handle.
    TypeParameterInstance, //!< %Parameter instance handle.
    TypeClip, //!< %Clip handle.
    TypeImage, //!< %Image handle.
    MaxType
  };
  
  //! Pixel component bit depth enumeration.
  enum BitDepth {
    BitDepthNone = 0, //!< Undefined.
    BitDepthByte, //!< 8 bits integer.
    BitDepthShort, //!< 16 bits integer.
    BitDepthFloat, //!< 32 bits float.
#ifdef OFX_API_1_3
    BitDepthHalf, //!< 16 bits float.
#endif
    MaxBitDepth
  };
  
  //! Pixel components enumeration.
  enum ImageComponent {
    ImageComponentNone = 0, //!< Undefined.
#ifdef OFX_API_1_2
    ImageComponentRGB, //!< R, G and B components. (OFX >= 1.2)
#endif
    ImageComponentRGBA, //!< R, G, B and A components.
    ImageComponentAlpha, //!< Alpha component.
    ImageComponentYUVA, //!< Y, U, V and A components.
    MaxImageComponent
  };
  
  //! %Image field enumeration.
  enum ImageField {
    ImageFieldNone, //!< Non-fielded image.
    ImageFieldBoth, //!< Fielded image containing both fileds.
    ImageFieldLower, //!< Fielded image only containing lower field (rows 0, 2, 4...)
    ImageFieldUpper, //!< Fielded image only containing upper field (rows 1, 3, 5...)
    MaxImageField
  };
  
  //! %Image field extraction enumeration.
  enum ImageFieldExtract {
    ImageFieldExtractBoth = 0, //!< Extract both field.
    ImageFieldExtractSingle, //!< Extract a single field. (half height image)
    ImageFieldExtractDoubled, //!< Extract a single field but double each line. (full height image)
    MaxImageFieldExtract
  };
  
  //! Field temporal order enumeration.
  enum ImageFieldOrder {
    ImageFieldOrderNone = 0, //!< Unfielded.
    ImageFieldOrderLower, //!< Lower field occuring first in a frame.
    ImageFieldOrderUpper, //!< Upper field occuring first in a frame.
    MaxImageFieldOrder
  };
  
  //! Premultiplcation state enumation.
  enum ImagePreMult {
    ImageOpaque = 0, //!< No premultiplication state.
    ImagePreMultiplied, //!< %Image premultipled by its alpha channel.
    ImageUnPreMultiplied,
    MaxImagePreMult
  };
  
  //! %Image effect instance context enumeration.
  enum ImageEffectContext {
    ImageEffectContextGenerator = 0, //!< %Image generating effetcs.
    ImageEffectContextFilter, //!< Filtering effetcs.
    ImageEffectContextTransition, //!< Transition effects.
    ImageEffectContextPaint, //!< Paint/Brush effects.
    ImageEffectContextGeneral, //!< Generic effects.
    ImageEffectContextRetimer, //!< Retiming effects.
    MaxImageEffectContext
  };
  
  //! Render thread safety enumeration.
  enum RenderThreadSafety {
    RenderThreadUnsafe = 0, //!< Only a single instance of the effect can be render at any time.
    RenderThreadInstanceSafe, //!< Different instances of the effect can be rendered at the same time.
    RenderThreadFullySafe, //!< Same instance of an effect can have multiple renders at the same time.
    MaxRenderThreadSafety
  };
  
  //! Parameter type enumeration.
  enum ParamType {
    ParamTypeInteger = 0, //!< Integer parameter.
    ParamTypeDouble, //!< Double parameter.
    ParamTypeBoolean, //!< Boolean parameter.
    ParamTypeChoice, //!< Choice parameter.
    ParamTypeRGBA, //!< RGBA colour parameter.
    ParamTypeRGB, //!< RGB colour parameter.
    ParamTypeDouble2D, //!< 2D double parameter.
    ParamTypeInteger2D, //!< 2D integer parameter.
    ParamTypeDouble3D, //!< 3D double parameter.
    ParamTypeInteger3D, //!< 3D integer parameter.
    ParamTypeString, //!< String parameter.
    ParamTypeCustom, //!< Custom parameter.
    ParamTypeGroup, //!< Group parameter.
    ParamTypePage, //!< Page parameter.
    ParamTypePushButton, //!< Push button parameter.
#ifdef OFX_API_1_2
    ParamTypeParametric, //!< Parametric parameter (OFX >= 1.2)
#endif
    MaxParamType
  };
  
  //! %Parameter cache invalidation state enumeration.
  enum ParamInvalidate {
    ParamInvalidateValueChange = 0, //!< %Parameter value change invalidates cache only locally (up to previous and/or next keyframe)
    ParamInvalidateValueChangeToEnd, //!< %Parameter value change invalidates cache up to the end.
    ParamInvalidateAll, //!< %Parameter value change invalidates the whole cache.
    MaxParamInvalidate
  };
  
  //! String parameter mode enumeration.
  enum StringParamMode {
    StringParamSingleLine = 0, //!< %Parameter value can only contain a single line.
    StringParamMultiLine, //!<  %Parameter value can contain multiple lines.
    StringParamFilePath, //!< %Parameter value should be interpreted as a file path.
    StringParamDirectoryPath, //!< %Parameter value should be interpreted as a directory path.
    StringParamLabel, //!< %Parameter value should be interpreted as a label.
#ifdef OFX_API_1_3
    StringParamRichText, //!< %Parameter value should be interpreted as rich text.
#endif
    MaxStringParamMode
  };
  
  //! Double parameter type enumeration.
  enum DoubleParamType {
    DoubleParamPlain = 0, //!< %Parameter doesn't represent anything special.
    DoubleParamAngle, //!< %Parameter represents an angular value.
    DoubleParamScale, //!< %Parameter represents a scale value.
    DoubleParamTime, //!< %Parameter represents a time value.
    DoubleParamAbsoluteTime, //!< %Parameter represents an absolute time value.
    DoubleParamNormalisedX, //!< %Parameter represents a normalised position in x.
    DoubleParamNormalisedXAbsolute, //!< %Parameter represents a normalised  absolute position in x.
    DoubleParamNormalisedY, //!< %Parameter represents a normalised position in y.
    DoubleParamNormalisedYAbsolute, //!< %Parameter represents a normalised  absolute position in y.
    DoubleParamNormalisedXY, //!< %Parameter represents a normalised position in x and y.
    DoubleParamNormalisedXYAbsolute, //!< %Parameter represents a normalised  absolute position in x and y.
#ifdef OFX_API_1_2
    DoubleParamX, //!< %Parameter represents a position in x. (OFX >= 1.2)
    DoubleParamXAbsolute, //!< %Parameter represents an absolute position in x. (OFX >= 1.2)
    DoubleParamY, //!< %Parameter represents a position in y. (OFX >= 1.2)
    DoubleParamYAbsolute, //!< %Parameter represents an absolute position in y. (OFX >= 1.2)
    DoubleParamXY, //!< %Parameter represents a position in x and y. (OFX >= 1.2)
    DoubleParamXYAbsolute, //!< %Parameter represents an absolute position in x and t. (OFX >= 1.2)
#endif
    MaxDoubleParamType
  };
  
#ifdef OFX_API_1_2
  //! Coorindates space enumeration. (OFX >= 1.2)
  enum Coordinates {
    CoordinatesCanonical = 0, //!< Canonical coordinates.
    CoordinatesNormalised, //!< Normalised coordinates.
    MaxCoordinates
  };
#endif
  
  //! Entry point action enumeration.
  enum Action {
    ActionLoad = 0, //!< Load action.
    ActionUnload, //!< Unload action.
    ActionDescribe, //!< Describe action.
    ActionCreateInstance, //!< Create instance action.
    ActionDestroyInstance, //!< Destroy instance action.
    ActionInstanceChanged, //!< Instance changed action.
    ActionBeginInstanceChanged, //!< Begin instance changed action.
    ActionEndInstanceChanged, //!< End instance changed action.
    ActionPurgeCaches, //!< Purge caches action.
    ActionSyncPrivateData, //!< Synchronize private data action.
    ActionBeginInstanceEdit, //!< Begin instance edit action.
    ActionEndInstanceEdit, //!< End instance edit action.
    ActionImageEffectDescribeInContext, //!< Describe in context action.
    ActionImageEffectGetRoD, //!< Get region of definition action.
    ActionImageEffectGetRoI, //!< Get regions of interest action.
    ActionImageEffectGetFramesNeeded, //!< Get required frames action.
    ActionImageEffectIsIdentity, //!< Is identity action.
    ActionImageEffectRender, //!< Render action.
    ActionImageEffectBeginSequenceRender, //!< Begin sequence render action.
    ActionImageEffectEndSequenceRender, //!< End sequence render action.
    ActionImageEffectGetClipPreferences, //!< Get clip preferences action.
    ActionImageEffectGetTimeDomain, //!< Get time domain action.
    ActionInteractDraw, //!< Draw action.
    ActionInteractPenMotion, //!< Pen/Mouse move action.
    ActionInteractPenDown, //!< Pen/Mouse down action.
    ActionInteractPenUp, //!< Pen/Mouse up action.
    ActionInteractKeyDown, //!< Key down action.
    ActionInteractKeyUp, //!< Key up action.
    ActionInteractKeyRepeat, //!< Key repeat action.
    ActionInteractGainFocus, //!< Gain focus action.
    ActionInteractLoseFocus, //!< Lose focus action.
#ifdef OFX_API_1_3
    ActionOpenGLContextAttached, //!< OpenGL context attached action.
    ActionOpenGLContextDetached, //!< OpenGL context detach action.
#endif
    MaxAction
  };
  
  //! Change reason enumeration.
  enum ChangeReason {
    ChangeUserEdited = 0, //!< User interaction.
    ChangePluginEdited, //!< %Plugin interaction.
    ChangeTime, //!< %Time has changed.
    MaxChangeReason
  };
  
  //! Message type enumeration.
  enum MessageType {
    MessageTypeFatal = 0, //!< Fatal error message.
    MessageTypeError, //!< Error message.
    MessageTypeMessage, //!< Standard message.
    MessageTypeLog, //!< Log message.
    MessageTypeQuestion, //!< Question message.
#ifdef OFX_API_1_2
    MessageTypeWarning, //!< Warning message. (OFX >= 1.2)
#endif
    MaxMessageType
  };
  
  //! Key direction enumeration.
  enum KeyDirection {
    KeyDirectionPrev = -1, //!< Search key backward.
    KeyDirectionExact, //!< Search key for exact match.
    KeyDirectionNext //!< Search key forward.
  };
  
  //! Sequential render state enumeration.
  enum SequentialRender {
    SequentialRenderNotNeeded = 0, //!< %Plugin doesn't require to be rendererd sequentialy.
    SequentialRenderRequired = 1, //!< %Plugin requires to be rendererd sequentialy.
#ifdef OFX_API_1_2
    SequentialRenderIfPossible = 2, //!< %Plugin is better rendererd sequentialy. (OFX >= 1.2)
#endif
    MaxSequentialRender,
    SequentialRenderUnknown = 0, //!< %Host can not guaranty an effect will be rendered sequentialy.
    SequentialRenderAlways = 1, //!< %Host will render an effect sequentialy if it requires so.
#ifdef OFX_API_1_2
    SequentialRenderSometimes = 2 //!< %Host might render effect sequentialy. (OFX >= 1.2)
#endif
  };
  
  //! Time type.
  typedef OfxTime Time;
  
  //! %Image effect and interact entry point prototype.
  typedef OfxStatus (*EntryPoint)(const char*, const void*, OfxPropertySetHandle, OfxPropertySetHandle);
  
  //! Generic range type.
  template <typename T>
  struct Range {
    T min; //!< Min value.
    T max; //!< Max value.
  };

  typedef Range<int> RangeI; //!< Integer range type.
  typedef Range<double> RangeD; //!< Double range type.
  
  //! Generic 2D point type.
  template <typename T>
  struct Point {
    T x; //!< X coordinate.
    T y; //!< Y coordinate.
  };

  typedef Point<int> PointI; //!< Integer point type.
  typedef Point<double> PointD; //!< Double point type.
  
  //! Generic rectangle type.
  template <typename T>
  struct Rect {
    T x1; //!< Lower left corner X coordinate.
    T y1; //!< Lower left corner Y coordinate.
    T x2; //!< Upper right corner X coordinate.
    T y2; //!< Upper right corner Y coordinate.
  };

  typedef Rect<int> RectI; //!< Integer rectangle type.
  typedef Rect<double> RectD; //!< Double rectangle type.
  
  //! Generic RGBA colour type.
  template <typename T>
  struct RGBAColour {
    T r; //!< R channel value.
    T g; //!< G channel value.
    T b; //!< B channel value.
    T a; //!< A channel value.
  };

  typedef RGBAColour<unsigned char> RGBAColourB; //!< Byte depth RGBA colour.
  typedef RGBAColour<unsigned short> RGBAColourS; //!< Short depth RGBA colour.
  typedef RGBAColour<float> RGBAColourF; //!< Float depth RGBA colour.
  typedef RGBAColour<double> RGBAColourD; //!< Double depth RGBA colour.
  
  //! Generic RGB colour type. (OFX >= 1.2)
  template <typename T>
  struct RGBColour {
    T r; //!< R channel value.
    T g; //!< G channel value.
    T b; //!< B channel value.
  };
  
  typedef RGBColour<unsigned char> RGBColourB; //!< Byte depth RGB colour. (OFX >= 1.2)
  typedef RGBColour<unsigned short> RGBColourS; //!< Short depth RGB colour. (OFX >= 1.2)
  typedef RGBColour<float> RGBColourF; //!< Float depth RGB colour. (OFX >= 1.2)
  typedef RGBColour<double> RGBColourD; //!< Double depth RGB colour. (OFX >= 1.2)
  
  //! Generic YUVA colour type.
  template <typename T>
  struct YUVAColour {
    T y; //!< Y channel value.
    T u; //!< U channel value.
    T v; //!< V channel value.
    T a; //!< A channel value.
  };

  typedef YUVAColour<unsigned char> YUVAColourB; //!< Byte depth YUVA colour.
  typedef YUVAColour<unsigned short> YUVAColourS; //!< Short depth YUVA colour.
  typedef YUVAColour<float> YUVAColourF; //!< Float depth YUVA colour.
  typedef YUVAColour<double> YUVAColourD; //!< Double depth YUVA colour.
  
  typedef RangeD FrameRange; //!< Frame range type.
  typedef std::vector<FrameRange> FrameRangeList; //!< Frame range list type.
  
  
  const int IntMax = std::numeric_limits<int>::max(); //!< Integer maximum value.
  const int IntMin = std::numeric_limits<int>::min(); //!< Integer minimum value.
  
  
  /** Convert canonical to pixel coordinates.
   *  \param[in] cx Canonical X coordinate.
   *  \param[in] cy Canonical Y coordinate.
   *  \param[in] pixelAspectRatio Project pixel aspect ratio.
   *  \param[in] renderScaleX Current render scale along x axis.
   *  \param[in] renderScaleY Current render scale along y axis.
   *  \param[in] field Image fielding.
   *  \param[out] px Pixel X coordinate.
   *  \param[out] py Pixel Y coordinate.
   */
  inline void CanonicalToPixelCoords(double cx, double cy,
                                     double pixelAspectRatio,
                                     double renderScaleX,
                                     double renderScaleY,
                                     ImageField field,
                                     int *px, int *py)
  {
    double fieldScale = ((field == ImageFieldUpper || field == ImageFieldLower) ? 0.5 : 1.0);
    double invPAR = 1.0 / pixelAspectRatio;
    *px = int(cx * renderScaleX * invPAR);
    *py = int(cy * renderScaleY * fieldScale);
  }
  
  /** Convert pixel to canonical coordinates.
   *  \param[in] px Pixel X coordinate.
   *  \param[in] py Pixel Y coordinate.
   *  \param[in] pixelAspectRatio Project pixel aspect ratio.
   *  \param[in] renderScaleX Current render scale along x axis.
   *  \param[in] renderScaleY Current render scale along y axis.
   *  \param[in] field Image fielding.
   *  \param[out] cx Canonical X coordinate.
   *  \param[out] cy Canonical Y coordinate.
   */
  inline void PixelToCanonicalCoords(int px, int py,
                                     double pixelAspectRatio,
                                     double renderScaleX,
                                     double renderScaleY,
                                     ImageField field,
                                     double *cx, double *cy)
  {
    double fieldScale = ((field == ImageFieldUpper || field == ImageFieldLower) ? 0.5 : 1.0);
    *cx = double(px) * pixelAspectRatio / renderScaleX;
    *cy = double(py) / (renderScaleY * fieldScale);
  }
  
  /** Convert normalised to canonical coordinates.
   *  \param[in] nx Normalised X coordinate.
   *  \param[in] ny Normalised Y coordinate.
   *  \param[in] wsize Project extent along x axis.
   *  \param[in] hsize Project extent along y axis.
   *  \param[in] xoff Project offset along x axis.
   *  \param[in] yoff Project offset along y axis.
   *  \param[in] absolute Is the input an absolute position?.
   *  \param[out] cx Canonical X coordinate.
   *  \param[out] cy Canonical Y coordinate.
   */
  inline void NormalisedToCanonicalCoords(double nx, double ny,
                                          double wsize, double hsize,
                                          double xoff, double yoff,
                                          bool absolute,
                                          double *cx, double *cy)
  {
    *cx = (nx * wsize) + (absolute ? xoff : 0.0);
    *cy = (ny * hsize) + (absolute ? yoff : 0.0);
  }
  
  /** Convert canonical to normalised coordinates.
   *  \param[in] cx Canonical X coordinate.
   *  \param[in] cy Canonical Y coordinate.
   *  \param[in] wsize Project extent along x axis.
   *  \param[in] hsize Project extent along y axis.
   *  \param[in] xoff Project offset along x axis.
   *  \param[in] yoff Project offset along y axis.
   *  \param[in] absolute Is the input an absolute position?.
   *  \param[out] nx Normalised X coordinate.
   *  \param[out] ny Normalised Y coordinate.
   */
  inline void CanonicalToNormalisedCoords(double cx, double cy,
                                          double wsize, double hsize,
                                          double xoff, double yoff,
                                          bool absolute,
                                          double *nx, double *ny)
  {
    *nx = (cx - (absolute ? xoff : 0.0)) / wsize;
    *ny = (cy - (absolute ? yoff : 0.0)) / hsize;
  }
  
  //! Get host object from an effect instance handle
  class ImageEffectHost* GetHost(OfxImageEffectHandle hdl);
  
  //! Get host object from an parameter set instance handle
  class Host* GetHostForParams(OfxParamSetHandle hdl);
  
  //! Get image effect object from its instance handle.
  class ImageEffect* GetEffect(OfxImageEffectHandle hdl);
  
  //! Get image effect object from its parameter set instance handle.
  class ImageEffect* GetEffectForParams(OfxParamSetHandle handle);
  
  /** Write a message to the log file.
   *  \param[in] msg Format stirng.
   *  \note The log file is the one pointed by the OFX_LOG environment variable.\n
   *        If it is not set, it will default to $HOME/ofx.log
   */
  void Log(const char *msg, ...);
  
#ifdef _DEBUG
  #define DebugLog Log
#else
  /** Write a message to the log file but only if library was compiled in debug mode.
   *  Same parameter as for the Log function.
   *  \note The log file is the one pointed by the OFX_LOG environment variable.\n
   *        If it is not set, it will default to $HOME/ofx.log
   */
  inline void DebugLog(const char *, ...) {}
#endif
  
  /** \fn const char* BitDepthToString(BitDepth e)
   *  \brief Convert BitDepth enum value to string.
   */
  
  /** \fn BitDepth StringToBitDepth(const char *s)
   *  \brief Convert string to BitDepth enum value.
   */
  
  /** \fn BitDepth StringToBitDepth(const std::string &s)
   *  \brief Convert string to BitDepth enum value.
   */
  
  DECLARE_ENUM_MAP(BitDepth);
  
  /** \fn const char* TypeToString(Type e)
   *  \brief Convert Type enum value to string.
   */
  
  /** \fn Type StringToType(const char *s)
   *  \brief Convert string to Type enum value.
   */
  
  /** \fn Type StringToType(const std::string &s)
   *  \brief Convert string to Type enum value.
   */
    
  DECLARE_ENUM_MAP(Type);
  
  /** \fn const char* ImageComponentToString(ImageComponent e)
   *  \brief Convert ImageComponent enum value to string.
   */
  
  /** \fn ImageComponent StringToImageComponent(const char *s)
   *  \brief Convert string to ImageComponent enum value.
   */
  
  /** \fn ImageComponent StringToImageComponent(const std::string &s)
   *  \brief Convert string to ImageComponent enum value.
   */
  
  DECLARE_ENUM_MAP(ImageComponent);
  
  /** \fn const char* ImageFieldToString(ImageField e)
   *  \brief Convert ImageField enum value to string.
   */
  
  /** \fn ImageField StringToImageField(const char *s)
   *  \brief Convert string to ImageField enum value.
   */
  
  /** \fn ImageField StringToImageField(const std::string &s)
   *  \brief Convert string to ImageField enum value.
   */
  
  DECLARE_ENUM_MAP(ImageField);
  
  /** \fn const char* ImageFieldExtractToString(ImageFieldExtract e)
   *  \brief Convert ImageFieldExtract enum value to string.
   */
  
  /** \fn ImageFieldExtract StringToImageFieldExtract(const char *s)
   *  \brief Convert string to ImageFieldExtract enum value.
   */
  
  /** \fn ImageFieldExtract StringToImageFieldExtract(const std::string &s)
   *  \brief Convert string to ImageFieldExtract enum value.
   */
  
  DECLARE_ENUM_MAP(ImageFieldExtract);
  
  /** \fn const char* ImageFieldOrderToString(ImageFieldOrder e)
   *  \brief Convert ImageFieldOrder enum value to string.
   */
  
  /** \fn ImageFieldOrder StringToImageFieldOrder(const char *s)
   *  \brief Convert string to ImageFieldOrder enum value.
   */
  
  /** \fn ImageFieldOrder StringToImageFieldOrder(const std::string &s)
   *  \brief Convert string to ImageFieldOrder enum value.
   */
  
  DECLARE_ENUM_MAP(ImageFieldOrder);
  
  /** \fn const char* ImagePreMultToString(ImagePreMult e)
   *  \brief Convert ImagePreMult enum value to string.
   */
  
  /** \fn ImagePreMult StringToImagePreMult(const char *s)
   *  \brief Convert string to ImagePreMult enum value.
   */
  
  /** \fn ImagePreMult StringToImagePreMult(const std::string &s)
   *  \brief Convert string to ImagePreMult enum value.
   */
  
  DECLARE_ENUM_MAP(ImagePreMult);
  
  /** \fn const char* ImageEffectContextToString(ImageEffectContext e)
   *  \brief Convert ImageEffectContext enum value to string.
   */
  
  /** \fn ImageEffectContext StringToImageEffectContext(const char *s)
   *  \brief Convert string to ImageEffectContext enum value.
   */
  
  /** \fn ImageEffectContext StringToImageEffectContext(const std::string &s)
   *  \brief Convert string to ImageEffectContext enum value.
   */
  
  DECLARE_ENUM_MAP(ImageEffectContext);
  
  /** \fn const char* RenderThreadSafetyToString(RenderThreadSafety e)
   *  \brief Convert RenderThreadSafety enum value to string.
   */
  
  /** \fn RenderThreadSafety StringToRenderThreadSafety(const char *s)
   *  \brief Convert string to RenderThreadSafety enum value.
   */
  
  /** \fn RenderThreadSafety StringToRenderThreadSafety(const std::string &s)
   *  \brief Convert string to RenderThreadSafety enum value.
   */
  
  DECLARE_ENUM_MAP(RenderThreadSafety);
  
  /** \fn const char* ParamTypeToString(ParamType e)
   *  \brief Convert ParamType enum value to string.
   */
  
  /** \fn ParamType StringToParamType(const char *s)
   *  \brief Convert string to ParamType enum value.
   */
  
  /** \fn ParamType StringToParamType(const std::string &s)
   *  \brief Convert string to ParamType enum value.
   */
  
  DECLARE_ENUM_MAP(ParamType);
  
  /** \fn const char* ParamInvalidateToString(ParamInvalidate e)
   *  \brief Convert ParamInvalidate enum value to string.
   */
  
  /** \fn ParamInvalidate StringToParamInvalidate(const char *s)
   *  \brief Convert string to ParamInvalidate enum value.
   */
  
  /** \fn ParamInvalidate StringToParamInvalidate(const std::string &s)
   *  \brief Convert string to ParamInvalidate enum value.
   */
  
  DECLARE_ENUM_MAP(ParamInvalidate);
  
  /** \fn const char* StringParamModeToString(StringParamMode e)
   *  \brief Convert StringParamMode enum value to string.
   */
  
  /** \fn StringParamMode StringToStringParamMode(const char *s)
   *  \brief Convert string to StringParamMode enum value.
   */
  
  /** \fn StringParamMode StringToStringParamMode(const std::string &s)
   *  \brief Convert string to StringParamMode enum value.
   */
  
  DECLARE_ENUM_MAP(StringParamMode);
  
  /** \fn const char* DoubleParamTypeToString(DoubleParamType e)
   *  \brief Convert DoubleParamType enum value to string.
   */
  
  /** \fn DoubleParamType StringToDoubleParamType(const char *s)
   *  \brief Convert string to DoubleParamType enum value.
   */
  
  /** \fn DoubleParamType StringToDoubleParamType(const std::string &s)
   *  \brief Convert string to DoubleParamType enum value.
   */
  
  DECLARE_ENUM_MAP(DoubleParamType);
  
  /** \fn const char* ActionToString(Action e)
   *  \brief Convert Action enum value to string.
   */
  
  /** \fn Action StringToAction(const char *s)
   *  \brief Convert string to Action enum value.
   */
  
  /** \fn Action StringToAction(const std::string &s)
   *  \brief Convert string to Action enum value.
   */
  
  DECLARE_ENUM_MAP(Action);
  
  /** \fn const char* ChangeReasonToString(ChangeReason e)
   *  \brief Convert ChangeReason enum value to string.
   */
  
  /** \fn ChangeReason StringToChangeReason(const char *s)
   *  \brief Convert string to ChangeReason enum value.
   */
  
  /** \fn ChangeReason StringToChangeReason(const std::string &s)
   *  \brief Convert string to ChangeReason enum value.
   */
  
  DECLARE_ENUM_MAP(ChangeReason);
  
  /** \fn const char* MessageTypeToString(MessageType e)
   *  \brief Convert MessageType enum value to string.
   */
  
  /** \fn MessageType StringToMessageType(const char *s)
   *  \brief Convert string to MessageType enum value.
   */
  
  /** \fn MessageType StringToMessageType(const std::string &s)
   *  \brief Convert string to MessageType enum value.
   */
  
  DECLARE_ENUM_MAP(MessageType);
  
#ifdef OFX_API_1_2
  
  /** \fn const char* CoordinatesToString(Coordinates e)
   *  \brief Convert Coordinates enum value to string.
   *  \note OpenFX version >= 1.2.
   */
  
  /** \fn Coordinates StringToCoordinates(const char *s)
   *  \brief Convert string to Coordinates enum value.
   *  \note OpenFX version >= 1.2.
   */
  
  /** \fn Coordinates StringToCoordinates(const std::string &s)
   *  \brief Convert string to Coordinates enum value.
   *  \note OpenFX version >= 1.2.
   */
  
  DECLARE_ENUM_MAP(Coordinates);
  
#endif
}

#endif
