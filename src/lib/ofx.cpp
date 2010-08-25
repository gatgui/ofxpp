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

#include <ofx/ofx.h>
#include <ofxImageEffect.h>
#include <ofxInteract.h>
#include <ofxMemory.h>
#include <ofxMessage.h>
#include <ofxMultiThread.h>
#include <ofxParam.h>
#include <ofxProgress.h>
#include <ofxProperty.h>
#include <ofxTimeLine.h>
#ifdef OFX_API_1_2
#include <ofxParametricParam.h>
#endif
#include <ctime>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

namespace ofx {


BEGIN_ENUM_MAP(BitDepth)
  ADD_ENUM_MAPPING(BitDepth, None)
  ADD_ENUM_MAPPING(BitDepth, Byte)
  ADD_ENUM_MAPPING(BitDepth, Short)
  ADD_ENUM_MAPPING(BitDepth, Float)
END_ENUM_MAP(BitDepth)

BEGIN_ENUM_MAP(Type)
  ADD_ENUM_MAPPING(Type, ImageEffectHost)
  ADD_ENUM_MAPPING(Type, ImageEffect)
  ADD_ENUM_MAPPING(Type, ImageEffectInstance)
  ADD_ENUM_MAPPING(Type, Parameter)
  ADD_ENUM_MAPPING(Type, ParameterInstance)
  ADD_ENUM_MAPPING(Type, Clip)
  ADD_ENUM_MAPPING(Type, Image)
END_ENUM_MAP(Type)

BEGIN_ENUM_MAP(ImageComponent)
  ADD_ENUM_MAPPING(ImageComponent, None)
#ifdef OFX_API_1_2
  ADD_ENUM_MAPPING(ImageComponent, RGB)
#endif
  ADD_ENUM_MAPPING(ImageComponent, RGBA)
  ADD_ENUM_MAPPING(ImageComponent, Alpha)
  ADD_ENUM_MAPPING(ImageComponent, YUVA)
END_ENUM_MAP(ImageComponent)

BEGIN_ENUM_MAP(ImageField)
  ADD_ENUM_MAPPING(ImageField, None)
  ADD_ENUM_MAPPING(ImageField, Both)
  ADD_ENUM_MAPPING(ImageField, Lower)
  ADD_ENUM_MAPPING(ImageField, Upper)
END_ENUM_MAP(ImageField)

BEGIN_ENUM_MAP(ImageFieldExtract)
  ADD_ENUM_MAPPING_CUSTOM(ImageFieldExtract, ImageFieldExtractBoth, kOfxImageFieldBoth)
  ADD_ENUM_MAPPING_CUSTOM(ImageFieldExtract, ImageFieldExtractSingle, kOfxImageFieldSingle)
  ADD_ENUM_MAPPING_CUSTOM(ImageFieldExtract, ImageFieldExtractDoubled, kOfxImageFieldDoubled)
END_ENUM_MAP(ImageFieldExtract)

BEGIN_ENUM_MAP(ImageFieldOrder)
  ADD_ENUM_MAPPING_CUSTOM(ImageFieldOrder, ImageFieldOrderNone, kOfxImageFieldNone)
  ADD_ENUM_MAPPING_CUSTOM(ImageFieldOrder, ImageFieldOrderLower, kOfxImageFieldLower)
  ADD_ENUM_MAPPING_CUSTOM(ImageFieldOrder, ImageFieldOrderUpper, kOfxImageFieldUpper)
END_ENUM_MAP(ImageFieldOrder)

BEGIN_ENUM_MAP(ImagePreMult)
  ADD_ENUM_MAPPING_CUSTOM(ImagePreMult, ImageOpaque, kOfxImageOpaque)
  ADD_ENUM_MAPPING_CUSTOM(ImagePreMult, ImagePreMultiplied, kOfxImagePreMultiplied)
  ADD_ENUM_MAPPING_CUSTOM(ImagePreMult, ImageUnPreMultiplied, kOfxImageUnPreMultiplied)
END_ENUM_MAP(ImagePreMult)

BEGIN_ENUM_MAP(ImageEffectContext)
  ADD_ENUM_MAPPING(ImageEffectContext, Generator)
  ADD_ENUM_MAPPING(ImageEffectContext, Filter)
  ADD_ENUM_MAPPING(ImageEffectContext, Transition)
  ADD_ENUM_MAPPING(ImageEffectContext, Paint)
  ADD_ENUM_MAPPING(ImageEffectContext, General)
  ADD_ENUM_MAPPING(ImageEffectContext, Retimer)
END_ENUM_MAP(ImageEffectContext)

BEGIN_ENUM_MAP(RenderThreadSafety)
  ADD_ENUM_MAPPING_CUSTOM(RenderThreadSafety, RenderThreadUnsafe, kOfxImageEffectRenderUnsafe)
  ADD_ENUM_MAPPING_CUSTOM(RenderThreadSafety, RenderThreadInstanceSafe, kOfxImageEffectRenderInstanceSafe)
  ADD_ENUM_MAPPING_CUSTOM(RenderThreadSafety, RenderThreadFullySafe, kOfxImageEffectRenderFullySafe)
END_ENUM_MAP(RenderThreadSafety)

BEGIN_ENUM_MAP(ParamType)
  ADD_ENUM_MAPPING(ParamType, Integer)
  ADD_ENUM_MAPPING(ParamType, Double)
  ADD_ENUM_MAPPING(ParamType, Boolean)
  ADD_ENUM_MAPPING(ParamType, Choice)
  ADD_ENUM_MAPPING(ParamType, RGBA)
  ADD_ENUM_MAPPING(ParamType, RGB)
  ADD_ENUM_MAPPING(ParamType, Double2D)
  ADD_ENUM_MAPPING(ParamType, Integer2D)
  ADD_ENUM_MAPPING(ParamType, Double3D)
  ADD_ENUM_MAPPING(ParamType, Integer3D)
  ADD_ENUM_MAPPING(ParamType, String)
  ADD_ENUM_MAPPING(ParamType, Custom)
  ADD_ENUM_MAPPING(ParamType, Group)
  ADD_ENUM_MAPPING(ParamType, Page)
  ADD_ENUM_MAPPING(ParamType, PushButton)
#ifdef OFX_API_1_2
  ADD_ENUM_MAPPING(ParamType, Parametric)
#endif
END_ENUM_MAP(ParamType)

BEGIN_ENUM_MAP(ParamInvalidate)
  ADD_ENUM_MAPPING(ParamInvalidate, ValueChange)
  ADD_ENUM_MAPPING(ParamInvalidate, ValueChangeToEnd)
  ADD_ENUM_MAPPING(ParamInvalidate, All)
END_ENUM_MAP(ParamInvalidate)

BEGIN_ENUM_MAP(StringParamMode)
  ADD_ENUM_MAPPING_CUSTOM(StringParamMode, StringParamSingleLine, kOfxParamStringIsSingleLine)
  ADD_ENUM_MAPPING_CUSTOM(StringParamMode, StringParamMultiLine, kOfxParamStringIsMultiLine)
  ADD_ENUM_MAPPING_CUSTOM(StringParamMode, StringParamFilePath, kOfxParamStringIsFilePath)
  ADD_ENUM_MAPPING_CUSTOM(StringParamMode, StringParamDirectoryPath, kOfxParamStringIsDirectoryPath)
  ADD_ENUM_MAPPING_CUSTOM(StringParamMode, StringParamLabel, kOfxParamStringIsLabel)
END_ENUM_MAP(StringParamMode)

BEGIN_ENUM_MAP(DoubleParamType)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamPlain, kOfxParamDoubleTypePlain)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamAngle, kOfxParamDoubleTypeAngle)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamScale, kOfxParamDoubleTypeScale)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamTime, kOfxParamDoubleTypeTime)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamAbsoluteTime, kOfxParamDoubleTypeAbsoluteTime)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamNormalisedX, kOfxParamDoubleTypeNormalisedX)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamNormalisedXAbsolute, kOfxParamDoubleTypeNormalisedXAbsolute)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamNormalisedY, kOfxParamDoubleTypeNormalisedY)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamNormalisedYAbsolute, kOfxParamDoubleTypeNormalisedYAbsolute)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamNormalisedXY, kOfxParamDoubleTypeNormalisedXY)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamNormalisedXYAbsolute, kOfxParamDoubleTypeNormalisedXYAbsolute)
#ifdef OFX_API_1_2
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamX, kOfxParamDoubleTypeX)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamXAbsolute, kOfxParamDoubleTypeXAbsolute)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamY, kOfxParamDoubleTypeY)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamYAbsolute, kOfxParamDoubleTypeYAbsolute)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamXY, kOfxParamDoubleTypeXY)
  ADD_ENUM_MAPPING_CUSTOM(DoubleParamType, DoubleParamXYAbsolute, kOfxParamDoubleTypeXYAbsolute)
#endif
END_ENUM_MAP(DoubleParamType)

#ifdef OFX_API_1_2
BEGIN_ENUM_MAP(Coordinates)
  ADD_ENUM_MAPPING_CUSTOM(Coordinates, CoordinatesCanonical, kOfxParamCoordinatesCanonical)
  ADD_ENUM_MAPPING_CUSTOM(Coordinates, CoordinatesNormalised, kOfxParamCoordinatesNormalised)
END_ENUM_MAP(Coordinates)
#endif

BEGIN_ENUM_MAP(Action)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionLoad, kOfxActionLoad)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionUnload, kOfxActionUnload)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionDescribe, kOfxActionDescribe)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionCreateInstance, kOfxActionCreateInstance)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionDestroyInstance, kOfxActionDestroyInstance)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionInstanceChanged, kOfxActionInstanceChanged)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionBeginInstanceChanged, kOfxActionBeginInstanceChanged)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionEndInstanceChanged, kOfxActionEndInstanceChanged)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionPurgeCaches, kOfxActionPurgeCaches)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionSyncPrivateData, kOfxActionSyncPrivateData)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionBeginInstanceEdit, kOfxActionBeginInstanceEdit)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionEndInstanceEdit, kOfxActionEndInstanceEdit)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionImageEffectDescribeInContext, kOfxImageEffectActionDescribeInContext)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionImageEffectGetRoD, kOfxImageEffectActionGetRegionOfDefinition)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionImageEffectGetRoI, kOfxImageEffectActionGetRegionsOfInterest)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionImageEffectGetFramesNeeded, kOfxImageEffectActionGetFramesNeeded)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionImageEffectIsIdentity, kOfxImageEffectActionIsIdentity)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionImageEffectRender, kOfxImageEffectActionRender)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionImageEffectBeginSequenceRender, kOfxImageEffectActionBeginSequenceRender)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionImageEffectEndSequenceRender, kOfxImageEffectActionEndSequenceRender)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionImageEffectGetClipPreferences, kOfxImageEffectActionGetClipPreferences)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionImageEffectGetTimeDomain, kOfxImageEffectActionGetTimeDomain)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionInteractDraw, kOfxInteractActionDraw)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionInteractPenMotion, kOfxInteractActionPenMotion)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionInteractPenDown, kOfxInteractActionPenDown)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionInteractPenUp, kOfxInteractActionPenUp)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionInteractKeyDown, kOfxInteractActionKeyDown)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionInteractKeyUp, kOfxInteractActionKeyUp)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionInteractKeyRepeat, kOfxInteractActionKeyRepeat)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionInteractGainFocus, kOfxInteractActionGainFocus)
  ADD_ENUM_MAPPING_CUSTOM(Action, ActionInteractLoseFocus, kOfxInteractActionLoseFocus)
END_ENUM_MAP(Action)

BEGIN_ENUM_MAP(ChangeReason)
  ADD_ENUM_MAPPING_CUSTOM(ChangeReason, ChangeUserEdited, kOfxChangeUserEdited)
  ADD_ENUM_MAPPING_CUSTOM(ChangeReason, ChangePluginEdited, kOfxChangePluginEdited)
  ADD_ENUM_MAPPING_CUSTOM(ChangeReason, ChangeTime, kOfxChangeTime)
END_ENUM_MAP(ChangeReason)

BEGIN_ENUM_MAP(MessageType)
  ADD_ENUM_MAPPING_CUSTOM(MessageType, MessageTypeFatal, kOfxMessageFatal)
  ADD_ENUM_MAPPING_CUSTOM(MessageType, MessageTypeError, kOfxMessageError)
  ADD_ENUM_MAPPING_CUSTOM(MessageType, MessageTypeMessage, kOfxMessageMessage)
  ADD_ENUM_MAPPING_CUSTOM(MessageType, MessageTypeLog, kOfxMessageLog)
  ADD_ENUM_MAPPING_CUSTOM(MessageType, MessageTypeQuestion, kOfxMessageQuestion)
END_ENUM_MAP(MessageType)


static FILE *gLog = 0;

void CloseLog(void) {
  if (gLog != 0) {
    fclose(gLog);
    gLog = 0;
  }
}

void Log(const char *msg, ...) {
  
#ifndef _WIN32
  char timestamp[24];
  time_t curtime = time(NULL);
  struct tm *curdate = localtime(&curtime);
  strftime(timestamp, 24, "%Y/%m/%d %H:%M:%S", curdate);
#else
#endif
  
  if (!gLog) {
    ::std::string path;
    char *ofxlog = getenv("OFX_LOG");
    if (ofxlog) {
      path = ofxlog;
    } else {
      char *home = getenv("HOME");
      if (home) {
        path = home;
        path += "/ofx.log";
      } else {
        path = "./ofx.log";
      }
    }
    gLog = fopen(path.c_str(), "a+");
    fprintf(gLog, "============\n");
    fflush(gLog);
    atexit(CloseLog);
  }
  //fprintf(gLog, "%s\n", msg);
#ifndef _WIN32
  fprintf(gLog, "%s > ", timestamp);
#else
#endif
  va_list args;
  va_start(args, msg);
  vfprintf(gLog, msg, args);
  va_end(args);
  fprintf(gLog, "\n");
  fflush(gLog);
}


}
