#include <ofxCore.h>
#include <ofxImageEffect.h>
#include <ofxParam.h>
#include <ofxProperty.h>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <ctime>
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
  /*
  */
  return kOfxStatReplyDefault;
}

static OfxStatus DescribeInContext(OfxImageEffectHandle effect, const char *ctx) {
  // width -> int x2
  // link -> bool
  // in & out clips
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
  RETURN_IF_ERROR(stat, "in IsIdentity: Could not get \"width\" parameter value");
  
  if (wsamples == 0 && hsamples == 0) {
    idt = t;
    idc = "Source";
    return kOfxStatOK;
  }
  
  return kOfxStatReplyDefault;
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

  stat = gEffectSuite->getPropertySet(effect, &props);
  RETURN_IF_ERROR(stat, "in Render: Could not retrieve effect properties");
  
  stat = gPropSuite->propGetPointer(props, kOfxPropInstanceData, 0, &ptr);
  RETURN_IF_ERROR(stat, "in Render: Could not retrieve effect instance data");
  
  data = (PluginData*)ptr;
  if (!data) {
    RETURN_IF_ERROR(kOfxStatFailed, "in Render: Invalid effect instance data");
  }
  
  // apply gaussian blur
  
  return kOfxStatOK;
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

