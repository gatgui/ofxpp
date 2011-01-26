#include <ofxCore.h>
#include <ofxImageEffect.h>
#include <ofxParam.h>
#include <ofxProperty.h>
#ifdef OFX_API_1_2
#include <ofxPixels.h>
#endif
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <ctime>
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>

// ---- Globals

FILE *gLog = 0;
OfxHost *gHost = 0;
OfxPropertySuiteV1 *gPropSuite = 0;
OfxParameterSuiteV1 *gParamSuite = 0;
OfxImageEffectSuiteV1 *gEffectSuite = 0;

static const char *ErrorHeader = "Error\n\tin plugin \"gatgui.filter.gaussianBlur\"\n\t";
static const char *InfoHeader  = "Info\n\tin plugin \"gatgui.filter.gaussianBlur\"\n\t";

#define RETURN_IF_ERROR(s, msg)\
  if (s != kOfxStatOK) {\
    Log("%s%s", ErrorHeader, msg);\
    return s;\
  }

struct PluginData {
  // cache parameters and clip
  OfxParamHandle pSamples;
  OfxParamHandle pLinkWidth;
  OfxImageClipHandle cSource;
  OfxImageClipHandle cOutput;
};

// --- Log

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
  // TODO
#endif
  
  if (!gLog) {
    std::string path;
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
    atexit(CloseLog);
  }
  
#ifndef _WIN32
  fprintf(gLog, "%s > ", timestamp);
#else
  // TODO
#endif
  
  va_list args;
  va_start(args, msg);
  vfprintf(gLog, msg, args);
  va_end(args);
  
  fprintf(gLog, "\n");
  
  fflush(gLog);
}

// --- Plugin functions

static OfxStatus Load() {
  if (!gHost) {
    return kOfxStatErrFatal;
  }
  gPropSuite = (OfxPropertySuiteV1*) gHost->fetchSuite(gHost->host, kOfxPropertySuite, 1);
  if (!gPropSuite) {
    RETURN_IF_ERROR(kOfxStatErrMissingHostFeature, "in Load: Could not fetch property suite");
  }
  gParamSuite = (OfxParameterSuiteV1*) gHost->fetchSuite(gHost->host, kOfxParameterSuite, 1);
  if (!gParamSuite) {
    RETURN_IF_ERROR(kOfxStatErrMissingHostFeature, "in Load: Could not fetch parameter suite");
  }
  gEffectSuite = (OfxImageEffectSuiteV1*) gHost->fetchSuite(gHost->host, kOfxImageEffectSuite, 1);
  if (!gEffectSuite) {
    RETURN_IF_ERROR(kOfxStatErrMissingHostFeature, "in Load: Could not fetch image effect suite");
  }
  return kOfxStatOK;
}

static OfxStatus Unload() {
  return kOfxStatOK;
}

static OfxStatus Describe(OfxImageEffectHandle effect) {
  OfxStatus stat;
  OfxPropertySetHandle props;
  
  stat = gEffectSuite->getPropertySet(effect, &props);
  RETURN_IF_ERROR(stat, "in Describe: Could not get effect descriptor properties");
  
  stat = gPropSuite->propSetString(props, kOfxPropLabel, 0, "gaussianBlur");
  RETURN_IF_ERROR(stat, "in Describe: Could not set label property");
  
  stat = gPropSuite->propSetString(props, kOfxPropShortLabel, 0, "gaussianBlur");
  RETURN_IF_ERROR(stat, "in Describe: Could not set short label property");
  
  stat = gPropSuite->propSetString(props, kOfxPropLongLabel, 0, "gaussianBlur");
  RETURN_IF_ERROR(stat, "in Describe: Could not set long label property");
  
  stat = gPropSuite->propSetString(props, kOfxImageEffectPluginPropGrouping, 0, "gatgui");
  RETURN_IF_ERROR(stat, "in Describe: Could not set grouping property");
  
  stat = gPropSuite->propSetString(props, kOfxImageEffectPropSupportedContexts, 0, kOfxImageEffectContextFilter);
  RETURN_IF_ERROR(stat, "in Describe: Could not set supported contexts property");
  
  stat = gPropSuite->propSetString(props, kOfxImageEffectPluginRenderThreadSafety, 0, kOfxImageEffectRenderFullySafe);
  RETURN_IF_ERROR(stat, "in Describe: Could not set render thread safety property");
  
  stat = gPropSuite->propSetInt(props, kOfxImageEffectPluginPropHostFrameThreading, 0, 1);
  RETURN_IF_ERROR(stat, "in Describe: Could not set frame threading property");
  
  stat = gPropSuite->propSetString(props, kOfxImageEffectPropSupportedPixelDepths, 0, kOfxBitDepthFloat);
  RETURN_IF_ERROR(stat, "in Describe: Could not set pixel depth property");
  
  return kOfxStatReplyDefault;
}

static OfxStatus DescribeInContext(OfxImageEffectHandle effect, const char *) {
  
  OfxStatus stat;
  OfxPropertySetHandle props;
  OfxParamSetHandle params;
  
  stat = gEffectSuite->getParamSet(effect, &params);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not get effect descriptor parameter set")
  
  // define clips
  
  stat = gEffectSuite->clipDefine(effect, "Source", &props);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not define \"Source\" clip");
  stat = gPropSuite->propSetString(props, kOfxImageEffectPropSupportedComponents, 0, kOfxImageComponentRGBA);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"Source\" clip supported components");
  
  stat = gEffectSuite->clipDefine(effect, "Output", &props);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not define \"Output\" clip");
  stat = gPropSuite->propSetString(props, kOfxImageEffectPropSupportedComponents, 0, kOfxImageComponentRGBA);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"Output\" clip supported components");
  
  // define parameters
  
  //stat = gParamSuite->paramDefine(params, kOfxParamTypeInteger2D, "samples", &props);
  stat = gParamSuite->paramDefine(params, kOfxParamTypeDouble2D, "samples", &props);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not define \"samples\" parameter");
  stat = gPropSuite->propSetString(props, kOfxParamPropDoubleType, 0, kOfxParamDoubleTypePlain);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"samples\" parameter double type");
  stat = gPropSuite->propSetDouble(props, kOfxParamPropIncrement, 0, 1);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"samples\" parameter increment");
  stat = gPropSuite->propSetInt(props, kOfxParamPropDigits, 0, 0);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"samples\" parameter digits");
  stat = gPropSuite->propSetString(props, kOfxParamPropDimensionLabel, 0, "w");
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"samples\" parameter dimension 0 label");
  stat = gPropSuite->propSetString(props, kOfxParamPropDimensionLabel, 1, "h");
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"samples\" parameter dimension 1 label");
  stat = gPropSuite->propSetInt(props, kOfxParamPropAnimates, 0, 1);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"samples\" parameter animates");
  stat = gPropSuite->propSetDouble(props, kOfxParamPropMin, 0, 0);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"samples\" parameter min");
  stat = gPropSuite->propSetDouble(props, kOfxParamPropMin, 1, 0);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"samples\" parameter min");
  stat = gPropSuite->propSetDouble(props, kOfxParamPropMax, 0, 100);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"samples\" parameter max");
  stat = gPropSuite->propSetDouble(props, kOfxParamPropMax, 1, 100);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"samples\" parameter max");
  stat = gPropSuite->propSetDouble(props, kOfxParamPropDefault, 0, 2);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"samples\" parameter default");
  stat = gPropSuite->propSetDouble(props, kOfxParamPropDefault, 1, 2);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"samples\" parameter default");
  
  stat = gParamSuite->paramDefine(params, kOfxParamTypeBoolean, "link", &props);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not define \"link\" parameter");
  stat = gPropSuite->propSetInt(props, kOfxParamPropAnimates, 0, 0);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"link\" parameter animates");
  stat = gPropSuite->propSetInt(props, kOfxParamPropDefault, 0, 1);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"link\" parameter default");
  
  return kOfxStatReplyDefault;
}

static OfxStatus CreateInstance(OfxImageEffectHandle effect) {
  OfxStatus stat;
  OfxPropertySetHandle props;
  OfxParamSetHandle params;
  PluginData *data = 0;
  
  stat = gEffectSuite->getPropertySet(effect, &props);
  RETURN_IF_ERROR(stat, "in CreateInstance: Could not retrieve effect properties");
  
  stat = gEffectSuite->getParamSet(effect, &params);
  RETURN_IF_ERROR(stat, "in CreateInstance: Could not retrieve effect parameters");
  
  data = new PluginData();
  
  stat = gEffectSuite->clipGetHandle(effect, "Source", &(data->cSource), NULL);
  RETURN_IF_ERROR(stat, "in CreateInstance: Could not retrieve effect \"Source\" clip");
  
  stat = gEffectSuite->clipGetHandle(effect, "Output", &(data->cOutput), NULL);
  RETURN_IF_ERROR(stat, "in CreateInstance: Could not retrieve effect \"Output\" clip");
  
  stat = gParamSuite->paramGetHandle(params, "samples", &(data->pSamples), NULL);
  RETURN_IF_ERROR(stat, "in CreateInstance: Could not retrieve effect \"samples\" parameter");
  
  stat = gParamSuite->paramGetHandle(params, "link", &(data->pLinkWidth), NULL);
  RETURN_IF_ERROR(stat, "in CreateInstance: Could not retrieve effect \"link\" parameter");
  
  stat = gPropSuite->propSetPointer(props, kOfxPropInstanceData, 0, (void*)data);
  RETURN_IF_ERROR(stat, "in CreateInstance: Could not set effect instance data");
  
  return stat;
}

static OfxStatus DestroyInstance(OfxImageEffectHandle effect) {
  OfxStatus stat;
  OfxPropertySetHandle props;
  void *ptr = 0;
  PluginData *data = 0;
  
  stat = gEffectSuite->getPropertySet(effect, &props);
  RETURN_IF_ERROR(stat, "in DestroyInstance: Could not retrieve effect properties");
  
  stat = gPropSuite->propGetPointer(props, kOfxPropInstanceData, 0, &ptr);
  RETURN_IF_ERROR(stat, "in DestroyInstance: Could not retrieve effect instance data");
  
  if (ptr != 0) {
    data = (PluginData*) ptr;
    delete data;
  }
  
  return kOfxStatOK;
}

static OfxStatus IsIdentity(OfxImageEffectHandle effect,
                            OfxTime t,
                            const char * /*field*/,
                            const OfxRectI & /*renderWindow*/,
                            double /*renderScaleX*/,
                            double /*renderScaleY*/,
                            OfxTime &idt,
                            std::string &idc) {
  OfxStatus stat;
  OfxPropertySetHandle props;
  void *ptr = 0;
  PluginData *data = 0;
  
  stat = gEffectSuite->getPropertySet(effect, &props);
  RETURN_IF_ERROR(stat, "in IsIdentity: Could not retrieve effect properties");
  
  stat = gPropSuite->propGetPointer(props, kOfxPropInstanceData, 0, &ptr);
  RETURN_IF_ERROR(stat, "in IsIdentity: Could not retrieve effect instance data");
  
  data = (PluginData*)ptr;
  if (!data) {
    return kOfxStatFailed;
  }
  
  double wsamples = 0, hsamples = 0;
  
  stat = gParamSuite->paramGetValueAtTime(data->pSamples, t, &wsamples, &hsamples);
  RETURN_IF_ERROR(stat, "in IsIdentity: Could not get \"samples\" parameter values");
  
  if (wsamples <= 0 && hsamples <= 0) {
    idt = t;
    idc = "Source";
    return kOfxStatOK;
  }
  
  return kOfxStatReplyDefault;
}

inline void* PixelAddress(void *data, const OfxRectI &bounds, int rowSize, int pixSize, int x, int y) {
  if (x < bounds.x1 || x >= bounds.x2 || y < bounds.y1 || y >= bounds.y2) {
    return 0;
  }
  return (void*)((char*)data + ((y - bounds.y1) * rowSize) + ((x - bounds.x1) * pixSize));
}

static OfxStatus Render(OfxImageEffectHandle effect,
                        OfxTime t,
                        const char * /*field*/,
                        const OfxRectI &renderWindow,
                        double /*renderScaleX*/,
                        double /*renderScaleY*/) {
  OfxStatus stat;
  OfxPropertySetHandle props;
  void *ptr = 0;
  PluginData *data = 0;
  OfxRGBAColourF *srcPix, *dstPix;

  stat = gEffectSuite->getPropertySet(effect, &props);
  RETURN_IF_ERROR(stat, "in Render: Could not retrieve effect properties");
  
  stat = gPropSuite->propGetPointer(props, kOfxPropInstanceData, 0, &ptr);
  RETURN_IF_ERROR(stat, "in Render: Could not retrieve effect instance data");
  
  data = (PluginData*)ptr;
  if (!data) {
    RETURN_IF_ERROR(kOfxStatFailed, "in Render: Invalid effect instance data");
  }
  
  // build gaussian weights
  
  double ws = -1, hs = -1;
  int wsamples = 0, hsamples = 0;
  
  stat = gParamSuite->paramGetValueAtTime(data->pSamples, t, &ws, &hs);
  RETURN_IF_ERROR(stat, "in Render: Could not get \"samples\" parameter values");
  
  wsamples = int(ceil(ws));
  hsamples = int(ceil(hs));
  
  float *wweights = new float[wsamples + 1];
  float *hweights = new float[hsamples + 1];
  
  float wtheta = (float(wsamples) + 1.0f) / 3.0f;
  float htheta = (float(hsamples) + 1.0f) / 3.0f;
  
  float wInv2ThetaSqr = 1.0f / (2.0f * wtheta * wtheta);
  float hInv2ThetaSqr = 1.0f / (2.0f * htheta * htheta);
  
  for (int i=0; i<=wsamples; ++i) {
    wweights[i] = (float) exp(- wInv2ThetaSqr * i * i);
  }
  
  for (int i=0; i<=hsamples; ++i) {
    hweights[i] = (float) exp(- hInv2ThetaSqr * i * i);
  }
  
  Log("%sin Render: samples = %dx%d", InfoHeader, wsamples, hsamples);
  
  // get source and output image buffers
  
  OfxPropertySetHandle iSource, iOutput;
  void *dSource, *dOutput;
  OfxRectI bSource, bOutput;
  int rowSizeSource, rowSizeOutput;
  int pixSizeSource, pixSizeOutput;
  
  stat = gEffectSuite->clipGetImage(data->cSource, t, NULL, &iSource);
  RETURN_IF_ERROR(stat, "in Render: Could not get \"Source\" clip image");
  stat = gPropSuite->propGetPointer(iSource, kOfxImagePropData, 0, &dSource);
  RETURN_IF_ERROR(stat, "in Render: Could not get \"Source\" image data");
  stat = gPropSuite->propGetIntN(iSource, kOfxImagePropBounds, 4, &(bSource.x1));
  RETURN_IF_ERROR(stat, "in Render: Could not get \"Source\" image bounds");
  stat = gPropSuite->propGetInt(iSource, kOfxImagePropRowBytes, 0, &rowSizeSource);
  RETURN_IF_ERROR(stat, "in Render: Could not get \"Source\" image row size");
  pixSizeSource = 4 * sizeof(float);
  //kOfxImageEffectPropPixelDepth, string x1
  //kOfxImageEffectPropComponents, string x1
  
  stat = gEffectSuite->clipGetImage(data->cOutput, t, NULL, &iOutput);
  RETURN_IF_ERROR(stat, "in Render: Could not get \"Output\" clip image");
  stat = gPropSuite->propGetPointer(iOutput, kOfxImagePropData, 0, &dOutput);
  RETURN_IF_ERROR(stat, "in Render: Could not get \"Output\" image data");
  stat = gPropSuite->propGetIntN(iOutput, kOfxImagePropBounds, 4, &(bOutput.x1));
  RETURN_IF_ERROR(stat, "in Render: Could not get \"Output\" image bounds");
  stat = gPropSuite->propGetInt(iOutput, kOfxImagePropRowBytes, 0, &rowSizeOutput);
  RETURN_IF_ERROR(stat, "in Render: Could not get \"Output\" image row size");
  pixSizeOutput = 4 * sizeof(float);
  
  /*
  for (int y=renderWindow.y1; y<renderWindow.y2; ++y) {
    if (gEffectSuite->abort(effect)) {
      break;
    }
    dstPix = (OfxRGBAColourF*) PixelAddress(dOutput, bOutput, rowSizeOutput, pixSizeOutput, renderWindow.x1, y);
    if (dstPix == 0) {
      continue;
    }
    for (int x=renderWindow.x1; x<renderWindow.x2; ++x) {
      srcPix = (OfxRGBAColourF*) PixelAddress(dSource, bSource, rowSizeSource, pixSizeSource, x, y);
      if (srcPix) {
        dstPix->r = srcPix->r;
        dstPix->g = srcPix->g;
        dstPix->b = srcPix->b;
        dstPix->a = srcPix->a;
      } else {
        dstPix->r = 0.0f;
        dstPix->g = 0.0f;
        dstPix->b = 0.0f;
        dstPix->a = 1.0f;
      }
      dstPix++;
    }
  }
  */
  
  // create temp image
  
  int ww = renderWindow.x2 - renderWindow.x1;
  int wh = renderWindow.y2 - renderWindow.y1;
  int pixSize = 4 * sizeof(float);
  int rowSize = ww * pixSize;
  
  unsigned char *dTemp = new unsigned char[ww * wh * pixSize];
  
  // pass 1: horizontal blur
  
  dstPix = (OfxRGBAColourF*) dTemp;
  
  for (int y=renderWindow.y1; y<renderWindow.y2; ++y) {
    if (gEffectSuite->abort(effect)) {
      break;
    }
    for (int x=renderWindow.x1; x<renderWindow.x2; ++x) {
      dstPix->r = 0.0f;
      dstPix->g = 0.0f;
      dstPix->b = 0.0f;
      dstPix->a = 0.0f;
      float w = 0.0f;
      int widx = 0;
      for (int x2=x-wsamples; x2<=x+wsamples; ++x2) {
        widx = x2 - x;
        widx = (widx < 0 ? -widx : widx);
        srcPix = (OfxRGBAColourF*) PixelAddress(dSource, bSource, rowSizeSource, pixSizeSource, x2, y);
        if (srcPix != 0) {
          w += wweights[widx];
          dstPix->r += wweights[widx] * srcPix->r;
          dstPix->g += wweights[widx] * srcPix->g;
          dstPix->b += wweights[widx] * srcPix->b;
          dstPix->a += wweights[widx] * srcPix->a;
        }
      }
      w = 1.0f / w;
      dstPix->r *= w;
      dstPix->g *= w;
      dstPix->b *= w;
      dstPix->a *= w;
      dstPix++;
    }
  }
  
  // pass 2: vertical blur
  
  for (int y=renderWindow.y1; y<renderWindow.y2; ++y) {
    if (gEffectSuite->abort(effect)) {
      break;
    }
    dstPix = (OfxRGBAColourF*) PixelAddress(dOutput, bOutput, rowSizeOutput, pixSizeOutput, renderWindow.x1, y);
    if (dstPix == 0) {
      continue;
    }
    for (int x=renderWindow.x1; x<renderWindow.x2; ++x) {
      srcPix = (OfxRGBAColourF*)(dTemp +
                                 ((y - hsamples) - renderWindow.y1) * rowSize +
                                 (x - renderWindow.x1) * pixSize);
      float w = 0.0f;
      int widx = 0;
      for (int y2=y-hsamples; y2<=y+hsamples; ++y2) {
        widx = y2 - y;
        widx = (widx < 0 ? -widx : widx);
        if (y2 >= renderWindow.y1 && y2 < renderWindow.y2) {
          w += hweights[widx];
          dstPix->r += hweights[widx] * srcPix->r;
          dstPix->g += hweights[widx] * srcPix->g;
          dstPix->b += hweights[widx] * srcPix->b;
          dstPix->a += hweights[widx] * srcPix->a;
        }
        srcPix += ww;
      }
      w = 1.0f / w;
      dstPix->r *= w;
      dstPix->g *= w;
      dstPix->b *= w;
      dstPix->a *= w;
      dstPix++;
    }
  }
  
  // cleanup
  
  gEffectSuite->clipReleaseImage(iSource);
  gEffectSuite->clipReleaseImage(iOutput);
  
  delete[] dTemp;
  delete[] wweights;
  delete[] hweights;
  
  return (gEffectSuite->abort(effect) == 0 ? kOfxStatOK : kOfxStatFailed);
}

// --- OFX entry points

static void SetHost(OfxHost *host) {
  gHost = host;
}

static OfxStatus PluginMain(const char *action,
                            const void *handle,
                            OfxPropertySetHandle inArgs,
                            OfxPropertySetHandle outArgs) {
  
  OfxStatus stat = kOfxStatReplyDefault;
  OfxImageEffectHandle effect = (OfxImageEffectHandle) handle;
  
  if (!strcmp(action, kOfxActionLoad)) {
    Log("%sin PluginMain/Load", InfoHeader);
    return Load();
    
  } else if (!strcmp(action, kOfxActionUnload)) {
    Log("%sin PluginMain/Unload", InfoHeader);
    return Unload();
    
  } else if (!strcmp(action, kOfxActionDescribe)) {
    Log("%sin PluginMain/Describe", InfoHeader);
    return Describe(effect);
  
  } else if (!strcmp(action, kOfxImageEffectActionDescribeInContext)) {
    char *ctx = 0;
    
    stat = gPropSuite->propGetString(inArgs, kOfxImageEffectPropContext, 0, &ctx);
    RETURN_IF_ERROR(stat, "in PluginMain/DescribeInContext: Could not get context");
    
    Log("%sin PluginMain/DescribeInContext\n\t\tcontext = %s", InfoHeader, ctx);
    
    return DescribeInContext(effect, ctx);
    
  } else if (!strcmp(action, kOfxActionCreateInstance)) {
    Log("%sin PluginMain/CreateInstance", InfoHeader);
    return CreateInstance(effect);
    
  } else if (!strcmp(action, kOfxActionDestroyInstance)) {
    Log("%sin PluginMain/DestroyInstance", InfoHeader);
    return DestroyInstance(effect);
    
  } else if (!strcmp(action, kOfxImageEffectActionIsIdentity)) {
    char *f = 0;
    OfxTime t, idt;
    OfxRectI rw;
    double rsx, rsy;
    std::string idc;
    
    stat = gPropSuite->propGetString(inArgs, kOfxImageEffectPropFieldToRender, 0, &f);
    RETURN_IF_ERROR(stat, "in PluginMain/IsIdentity: Could not get field to render");
    
    stat = gPropSuite->propGetIntN(inArgs, kOfxImageEffectPropRenderWindow, 4, &(rw.x1));
    RETURN_IF_ERROR(stat, "in PluginMain/IsIdentity: Could not get render window");
    
    stat = gPropSuite->propGetDouble(inArgs, kOfxImageEffectPropRenderScale, 0, &rsx);
    RETURN_IF_ERROR(stat, "in PluginMain/IsIdentity: Could not get render scale x");
    
    stat = gPropSuite->propGetDouble(inArgs, kOfxImageEffectPropRenderScale, 1, &rsy);
    RETURN_IF_ERROR(stat, "in PluginMain/IsIdentity: Could not get render scale y");
    
    stat = gPropSuite->propGetDouble(inArgs, kOfxPropTime, 0, &t);
    RETURN_IF_ERROR(stat, "in PluginMain/IsIdentity: Could not get time");
    
    Log("%sin PluginMain/IsIdentity\n\t\ttime = %f\n\t\tfield = %s\n\t\trender scale = %f x %f\n\t\trender window = [(%d, %d), (%d, %d)]",
        InfoHeader, t, f, rsx, rsy, rw.x1, rw.y1, rw.x2, rw.y2);
    
    stat = IsIdentity(effect, t, f, rw, rsx, rsy, idt, idc);
    if (stat == kOfxStatOK) {
      Log("%s\tyes: \"%s\" @ %f", InfoHeader, idc.c_str(), idt);
      gPropSuite->propSetDouble(outArgs, kOfxPropTime, 0, idt);
      gPropSuite->propSetString(outArgs, kOfxPropName, 0, idc.c_str());
    }
    
    return stat;
    
  } else if (!strcmp(action, kOfxImageEffectActionRender)) {
    char *f = 0;
    OfxTime t;
    OfxRectI rw;
    double rsx, rsy;
    
    stat = gPropSuite->propGetString(inArgs, kOfxImageEffectPropFieldToRender, 0, &f);
    RETURN_IF_ERROR(stat, "in PluginMain/Render: Could not get field to render");
    
    stat = gPropSuite->propGetIntN(inArgs, kOfxImageEffectPropRenderWindow, 4, &(rw.x1));
    RETURN_IF_ERROR(stat, "in PluginMain/Render: Could not get render window");
    
    stat = gPropSuite->propGetDouble(inArgs, kOfxImageEffectPropRenderScale, 0, &rsx);
    RETURN_IF_ERROR(stat, "in PluginMain/Render: Could not get render scale x");
    
    stat = gPropSuite->propGetDouble(inArgs, kOfxImageEffectPropRenderScale, 1, &rsy);
    RETURN_IF_ERROR(stat, "in PluginMain/Render: Could not get render scale y");
    
    stat = gPropSuite->propGetDouble(inArgs, kOfxPropTime, 0, &t);
    RETURN_IF_ERROR(stat, "in PluginMain/Render: Could not get time");
    
    Log("%sin PluginMain/Render\n\t\ttime = %f\n\t\tfield = %s\n\t\trender scale = %f x %f\n\t\trender window = [(%d, %d), (%d, %d)]",
        InfoHeader, t, f, rsx, rsy, rw.x1, rw.y1, rw.x2, rw.y2);
    
    return Render(effect, t, f, rw, rsx, rsy);
  
  } else {
    Log("%sin PluginMain\n\t\tUn-handled action \"%s\"", InfoHeader, action);
  }
  
  return kOfxStatReplyDefault;
}

// ---

static struct OfxPlugin BlurPlugin = {
  kOfxImageEffectPluginApi,
  kOfxImageEffectPluginApiVersion,
  "gatgui.filter.gaussianBlur",
  1,
  0,
  SetHost,
  PluginMain
};

OfxExport int OfxGetNumberOfPlugins(void) {
  return 1;
}

OfxExport OfxPlugin* OfxGetPlugin(int i) {
  if (i == 0) {
    return &BlurPlugin;
  }
  return NULL;
}

