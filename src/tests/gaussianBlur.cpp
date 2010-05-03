#include <ofxCore.h>
#include <ofxImageEffect.h>
#include <ofxParam.h>
#include <ofxProperty.h>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <ctime>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>

// ---- Globals

FILE *gLog = 0;
OfxHost *gHost = 0;
OfxPropertySuiteV1 *gPropSuite = 0;
OfxParameterSuiteV1 *gParamSuite = 0;
OfxImageEffectSuiteV1 *gEffectSuite = 0;

#define RETURN_IF_ERROR(s, msg)\
  if (s >= kOfxStatFailed && s <= kOfxStatErrValue) {\
    Log("*** Error in plugin \"gatgui.filter.gaussianBlur\"\n%s", msg);\
    return s;\
  }

struct PluginData {
  // cache parameters and clip
  OfxParamHandle pWidth;
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

static OfxStatus DescribeInContext(OfxImageEffectHandle effect, const char *ctx) {
  
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
  
  stat = gParamSuite->paramDefine(params, kOfxParamTypeInteger2D, "width", &props);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not define \"width\" parameter");
  stat = gPropSuite->propSetInt(props, kOfxParamPropDefault, 0, 2);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"width\" parameter default");
  stat = gPropSuite->propSetInt(props, kOfxParamPropDefault, 1, 2);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"width\" parameter default");
  stat = gPropSuite->propSetInt(props, kOfxParamPropMin, 0, 0);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"width\" parameter min");
  stat = gPropSuite->propSetInt(props, kOfxParamPropMin, 1, 0);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"width\" parameter min");
  stat = gPropSuite->propSetInt(props, kOfxParamPropMax, 0, 100);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"width\" parameter max");
  stat = gPropSuite->propSetInt(props, kOfxParamPropMax, 1, 100);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"width\" parameter max");
  stat = gPropSuite->propSetString(props, kOfxParamPropDimensionLabel, 0, "w");
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"width\" parameter dimension 0 label");
  stat = gPropSuite->propSetString(props, kOfxParamPropDimensionLabel, 1, "h");
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not set \"width\" parameter dimension 1 label");
  
  stat = gParamSuite->paramDefine(params, kOfxParamTypeBoolean, "link", &props);
  RETURN_IF_ERROR(stat, "in DescribeInContext: Could not define \"link\" parameter");
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
  
  stat = gParamSuite->paramGetHandle(params, "width", &(data->pWidth), NULL);
  RETURN_IF_ERROR(stat, "in CreateInstance: Could not retrieve effect \"width\" parameter");
  
  stat = gParamSuite->paramGetHandle(params, "link", &(data->pLinkWidth), NULL);
  RETURN_IF_ERROR(stat, "in CreateInstance: Could not retrieve effect \"link\" parameter");
  
  stat = gPropSuite->propSetPointer(props, kOfxPropInstanceData, 0, (void*)data);
  
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
                            const char *field,
                            const OfxRectI &renderWindow,
                            double renderScaleX,
                            double renderScaleY,
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
  
  int wsamples = 0, hsamples = 0;
  
  stat = gParamSuite->paramGetValueAtTime(data->pWidth, t, &wsamples, &hsamples);
  RETURN_IF_ERROR(stat, "in IsIdentity: Could not get \"width\" parameter values");
  
  if (wsamples == 0 && hsamples == 0) {
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
                        const char *field,
                        const OfxRectI &renderWindow,
                        double renderScaleX,
                        double renderScaleY) {
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
  
  int wsamples = 0, hsamples = 0;
  
  stat = gParamSuite->paramGetValueAtTime(data->pWidth, t, &wsamples, &hsamples);
  RETURN_IF_ERROR(stat, "in Render: Could not get \"width\" parameter values");
  
  float *wweights = new float[wsamples + 1];
  float *hweights = new float[hsamples + 1];
  
  float wtheta = std::max(float((wsamples + 1) / 3), 1.0f);
  float htheta = std::max(float((hsamples + 1) / 3), 1.0f);
  
  float wInv2ThetaSqr = 1.0f / (2.0f * wtheta * wtheta);
  float hInv2ThetaSqr = 1.0f / (2.0f * htheta * htheta);
  
  for (int i=0; i<=wsamples; ++i) {
    wweights[i] = (float) exp(- wInv2ThetaSqr * i * i);
  }
  
  for (int i=0; i<=hsamples; ++i) {
    hweights[i] = (float) exp(- hInv2ThetaSqr * i * i);
  }
  
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
  
  stat = gEffectSuite->clipGetImage(data->cSource, t, NULL, &iOutput);
  RETURN_IF_ERROR(stat, "in Render: Could not get \"Output\" clip image");
  stat = gPropSuite->propGetPointer(iOutput, kOfxImagePropData, 0, &dOutput);
  RETURN_IF_ERROR(stat, "in Render: Could not get \"Output\" image data");
  stat = gPropSuite->propGetIntN(iOutput, kOfxImagePropBounds, 4, &(bOutput.x1));
  RETURN_IF_ERROR(stat, "in Render: Could not get \"Output\" image bounds");
  stat = gPropSuite->propGetInt(iOutput, kOfxImagePropRowBytes, 0, &rowSizeOutput);
  RETURN_IF_ERROR(stat, "in Render: Could not get \"Output\" image row size");
  pixSizeOutput = 4 * sizeof(float);
  
  // create temp image
  
  int ww = renderWindow.x2 - renderWindow.x1;
  int wh = renderWindow.y2 - renderWindow.y1;
  int pixSize = 4 * sizeof(float);
  int rowSize = wh * pixSize;
  
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
      ++dstPix;
    }
  }
  
  // pass 2: vertical blur
  
  for (int x=renderWindow.x1; x<renderWindow.x2; ++x) {
    if (gEffectSuite->abort(effect)) {
      break;
    }
    for (int y=renderWindow.y1; y<renderWindow.y2; ++y) {
      dstPix = (OfxRGBAColourF*) PixelAddress(dOutput, bOutput, rowSizeOutput, pixSizeOutput, x, y);
      if (dstPix == 0) {
        continue;
      }
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
    return Load();
    
  } else if (!strcmp(action, kOfxActionUnload)) {
    return Unload();
    
  } else if (!strcmp(action, kOfxActionDescribe)) {
    return Describe(effect);
  
  } else if (!strcmp(action, kOfxImageEffectActionDescribeInContext)) {
    char *ctx = 0;
    
    stat = gPropSuite->propGetString(inArgs, kOfxImageEffectPropContext, 0, &ctx);
    RETURN_IF_ERROR(stat, "in PluginMain/DescribeInContext: Could not get context");
    
    return DescribeInContext(effect, ctx);
    
  } else if (!strcmp(action, kOfxActionCreateInstance)) {
    return CreateInstance(effect);
    
  } else if (!strcmp(action, kOfxActionDestroyInstance)) {
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
    
    stat = IsIdentity(effect, t, f, rw, rsx, rsy, idt, idc);
    if (stat == kOfxStatOK) {
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
    
    return Render(effect, t, f, rw, rsx, rsy);
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

