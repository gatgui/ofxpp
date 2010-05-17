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

#ifndef __ofx_ofx_h__
#define __ofx_ofx_h__

#include <ofxCore.h>
#include <map>
#include <vector>
#include <string>
#include <limits>

#ifdef _MSC_VER
# pragma warning(disable:4290)
#endif

#define DECLARE_ENUM_MAP(Enum)\
  extern const char* Enum##ToString(Enum e);\
  extern Enum StringTo##Enum(const char *s);\
  inline Enum StringTo##Enum(const std::string &s) {\
    return StringTo##Enum(s.c_str());\
  }

#define BEGIN_ENUM_MAP(Enum)\
  static std::map<std::string, Enum> gsStringTo##Enum;\
  static const char *gs##Enum##ToString[Max##Enum];\
  static void Init##Enum##Mapping() {

#define ADD_ENUM_MAPPING(Enum, ID)\
  gsStringTo##Enum[kOfx##Enum##ID] = Enum##ID;\
    gs##Enum##ToString[int(Enum##ID)] = kOfx##Enum##ID;

#define ADD_ENUM_MAPPING_CUSTOM(Enum, EnumVal, StringVal)\
  gsStringTo##Enum[StringVal] = EnumVal;\
    gs##Enum##ToString[int(EnumVal)] = StringVal;

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

namespace ofx {
  
  enum Type {
    TypeImageEffectHost = 0,
    TypeImageEffect,
    TypeImageEffectInstance,
    TypeParameter,
    TypeParameterInstance,
    TypeClip,
    TypeImage,
    MaxType
  };
  
  enum BitDepth {
    BitDepthNone = 0,
    BitDepthByte,
    BitDepthShort,
    BitDepthFloat,
    MaxBitDepth
  };
  
  enum ImageComponent {
    ImageComponentNone = 0,
    ImageComponentRGBA,
    ImageComponentAlpha,
    MaxImageComponent
  };
  
  enum ImageField {
    ImageFieldNone,
    ImageFieldBoth,
    ImageFieldLower,
    ImageFieldUpper,
    MaxImageField
  };
  
  enum ImageFieldExtract {
    ImageFieldExtractBoth = 0,
    ImageFieldExtractSingle,
    ImageFieldExtractDoubled,
    MaxImageFieldExtract
  };
  
  enum ImageFieldOrder {
    ImageFieldOrderNone = 0,
    ImageFieldOrderLower,
    ImageFieldOrderUpper,
    MaxImageFieldOrder
  };
  
  enum ImagePreMult {
    ImageOpaque = 0,
    ImagePreMultiplied,
    ImageUnPreMultiplied,
    MaxImagePreMult
  };
  
  enum ImageEffectContext {
    ImageEffectContextGenerator = 0,
    ImageEffectContextFilter,
    ImageEffectContextTransition,
    ImageEffectContextPaint,
    ImageEffectContextGeneral,
    ImageEffectContextRetimer,
    MaxImageEffectContext
  };
  
  enum RenderThreadSafety {
    RenderThreadUnsafe = 0,
    RenderThreadInstanceSafe,
    RenderThreadFullySafe,
    MaxRenderThreadSafety
  };
  
  enum ParamType {
    ParamTypeInteger = 0,
    ParamTypeDouble,
    ParamTypeBoolean,
    ParamTypeChoice,
    ParamTypeRGBA,
    ParamTypeRGB,
    ParamTypeDouble2D,
    ParamTypeInteger2D,
    ParamTypeDouble3D,
    ParamTypeInteger3D,
    ParamTypeString,
    ParamTypeCustom,
    ParamTypeGroup,
    ParamTypePage,
    ParamTypePushButton,
#ifdef OFX_API_1_2
    ParamTypeParametric,
#endif
    MaxParamType
  };
  
  enum ParamInvalidate {
    ParamInvalidateValueChange = 0,
    ParamInvalidateValueChangeToEnd,
    ParamInvalidateAll,
    MaxParamInvalidate
  };
  
  enum StringParamMode {
    StringParamSingleLine = 0,
    StringParamMultiLine,
    StringParamFilePath,
    StringParamDirectoryPath,
    StringParamLabel,
    MaxStringParamMode
  };
  
  enum DoubleParamType {
    DoubleParamPlain = 0,
    DoubleParamAngle,
    DoubleParamScale,
    DoubleParamTime,
    DoubleParamAbsoluteTime,
    DoubleParamNormalisedX,
    DoubleParamNormalisedXAbsolute,
    DoubleParamNormalisedY,
    DoubleParamNormalisedYAbsolute,
    DoubleParamNormalisedXY,
    DoubleParamNormalisedXYAbsolute,
#ifdef OFX_API_1_2
    DoubleParamX,
    DoubleParamXAbsolute,
    DoubleParamY,
    DoubleParamYAbsolute,
    DoubleParamXY,
    DoubleParamXYAbsolute,
#endif
    MaxDoubleParamType
  };

#ifdef OFX_API_1_2
  enum Coordinates {
    CoordinatesCanonical = 0,
    CoordinatesNormalised,
    MaxCoordinates
  };
#endif

  enum Action {
    ActionLoad = 0,
    ActionUnload,
    ActionDescribe,
    ActionCreateInstance,
    ActionDestroyInstance,
    ActionInstanceChanged,
    ActionBeginInstanceChanged,
    ActionEndInstanceChanged,
    ActionPurgeCaches,
    ActionSyncPrivateData,
    ActionBeginInstanceEdit,
    ActionEndInstanceEdit,
    ActionImageEffectDescribeInContext,
    ActionImageEffectGetRoD,
    ActionImageEffectGetRoI,
    ActionImageEffectGetFramesNeeded,
    ActionImageEffectIsIdentity,
    ActionImageEffectRender,
    ActionImageEffectBeginSequenceRender,
    ActionImageEffectEndSequenceRender,
    ActionImageEffectGetClipPreferences,
    ActionImageEffectGetTimeDomain,
    ActionInteractDraw,
    ActionInteractPenMotion,
    ActionInteractPenDown,
    ActionInteractPenUp,
    ActionInteractKeyDown,
    ActionInteractKeyUp,
    ActionInteractKeyRepeat,
    ActionInteractGainFocus,
    ActionInteractLoseFocus,
    MaxAction
  };
  
  enum ChangeReason {
    ChangeUserEdited = 0,
    ChangePluginEdited,
    ChangeTime,
    MaxChangeReason
  };
  
  enum MessageType {
    MessageTypeFatal = 0,
    MessageTypeError,
    MessageTypeMessage,
    MessageTypeLog,
    MessageTypeQuestion,
    MaxMessageType
  };
  
  enum KeyDirection {
    KeyDirectionPrev = -1,
    KeyDirectionExact,
    KeyDirectionNext
  };
  
  DECLARE_ENUM_MAP(BitDepth);
  DECLARE_ENUM_MAP(Type);
  DECLARE_ENUM_MAP(ImageComponent);
  DECLARE_ENUM_MAP(ImageField);
  DECLARE_ENUM_MAP(ImageFieldExtract);
  DECLARE_ENUM_MAP(ImageFieldOrder);
  DECLARE_ENUM_MAP(ImagePreMult);
  DECLARE_ENUM_MAP(ImageEffectContext);
  DECLARE_ENUM_MAP(RenderThreadSafety);
  DECLARE_ENUM_MAP(ParamType);
  DECLARE_ENUM_MAP(ParamInvalidate);
  DECLARE_ENUM_MAP(StringParamMode);
  DECLARE_ENUM_MAP(DoubleParamType);
  DECLARE_ENUM_MAP(Action);
  DECLARE_ENUM_MAP(ChangeReason);
  DECLARE_ENUM_MAP(MessageType);
#ifdef OFX_API_1_2
  DECLARE_ENUM_MAP(Coordinates);
#endif
  
  enum SequentialRender {
    SequentialRenderNotNeeded = 0,
    SequentialRenderRequired = 1,
#ifdef OFX_API_1_2
    SequentialRenderIfPossible = 2,
#endif
    MaxSequentialRender
  };
  
  typedef OfxTime Time;
  
  typedef OfxStatus (*EntryPoint)(const char*, const void*, OfxPropertySetHandle, OfxPropertySetHandle);
  
  template <typename T>
  struct Range {
    T min, max;
  };

  typedef Range<int> RangeI;
  typedef Range<double> RangeD;
  
  template <typename T>
  struct Point {
    T x, y;
  };

  typedef Point<int> PointI;
  typedef Point<double> PointD;
  
  template <typename T>
  struct Rect {
    T x1, y1, x2, y2;
  };

  typedef Rect<int> RectI;
  typedef Rect<double> RectD;
  
  template <typename T>
  struct RGBAColour {
    T r, g, b, a;
  };

  typedef RGBAColour<unsigned char> RGBAColourB; 
  typedef RGBAColour<unsigned short> RGBAColourS;
  typedef RGBAColour<float> RGBAColourF;
  typedef RGBAColour<double> RGBAColourD;
  
  template <typename T>
  struct YUVAColour {
    T y, u, v, a;
  };

  typedef YUVAColour<unsigned char> YUVAColourB;
  typedef YUVAColour<unsigned short> YUVAColourS;
  typedef YUVAColour<float> YUVAColourF;
  typedef YUVAColour<double> YUVAColourD;
  
  typedef std::pair<double, double> FrameRange;
  typedef std::vector<FrameRange> FrameRangeList;
  
  //const int IntMax = kOfxFlagInfiniteMax;
  //const int IntMin = kOfxFlagInfiniteMin;
  const int IntMax = std::numeric_limits<int>::max();
  const int IntMin = std::numeric_limits<int>::min();
  
  inline void CanonicalToPixelCoords(double cx, double cy,
                                     double pixelAspectRatio,
                                     double renderScaleX,
                                     double renderScaleY,
                                     ImageField field,
                                     int &px, int &py)
  {
    double fieldScale = ((field == ImageFieldUpper || field == ImageFieldLower) ? 0.5 : 1.0);
    double invPAR = 1.0 / pixelAspectRatio;
    px = int(cx * renderScaleX * invPAR);
    py = int(cy * renderScaleY * fieldScale);
  }
  
  inline void PixelToCanonicalCoords(int px, int py,
                                     double pixelAspectRatio,
                                     double renderScaleX,
                                     double renderScaleY,
                                     ImageField field,
                                     double &cx, double &cy)
  {
    double fieldScale = ((field == ImageFieldUpper || field == ImageFieldLower) ? 0.5 : 1.0);
    cx = double(px) * pixelAspectRatio / renderScaleX;
    cy = double(py) / (renderScaleY * fieldScale);
  }
  
  inline void NormalisedToCanonicalCoords(double nx, double ny,
                                          double wsize, double hsize,
                                          double xoff, double yoff,
                                          bool absolute,
                                          double &cx, double &cy)
  {
    cx = (nx * wsize) + (absolute ? xoff : 0.0);
    cy = (ny * hsize) + (absolute ? yoff : 0.0);
  }
  
  inline void CanonicalToNormalisedCoords(double cx, double cy,
                                          double wsize, double hsize,
                                          double xoff, double yoff,
                                          bool absolute,
                                          double &nx, double &ny)
  {
    nx = (cx - (absolute ? xoff : 0.0)) / wsize;
    ny = (cy - (absolute ? yoff : 0.0)) / hsize;
  }
  
#ifdef _DEBUG
  void Log(const char *msg, ...);
#else
  inline void Log(const char *, ...) {}
#endif
}

#endif
