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


//! ofx namespace.
namespace ofx {
  
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
    ImageFieldExtractBoth = 0, //<! Extract both field.
    ImageFieldExtractSingle, //<! Extract a single field. (half height image)
    ImageFieldExtractDoubled, //<! Extract a single field but double each line. (full height image)
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
  
#ifdef OFX_API_1_2
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
#endif
  
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
   *  \param[in] msg Format stirng.
   *  \note The log file is the one pointed by the OFX_LOG environment variable.\n
   *        If it is not set, it will default to $HOME/ofx.log
   */
  inline void DebugLog(const char *, ...) {}
#endif
  
  
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
}

#endif
