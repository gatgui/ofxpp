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

#include <ofx/imageeffect.h>
#include <ofx/interact.h>
#include <ofx/message.h>
#include <ofx/plugin.h>
#ifdef __APPLE__
# include <OpenGL/gl.h>
#else
# ifdef _WIN32
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
# endif
# include <GL/gl.h>
#endif
#include <cmath>

// Interact

// Descriptor

class BlurDescriptor : public ofx::ImageEffectDescriptor {
  public:
    
    BlurDescriptor(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl);
    virtual ~BlurDescriptor();
    
    virtual OfxStatus describe();
    virtual OfxStatus describeInContext(ofx::ImageEffectContext ctx);
};

// Effect

class BlurEffect : public ofx::ImageEffect {
  public:
    
    BlurEffect(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl);
    virtual ~BlurEffect();
    
    virtual OfxStatus isIdentity(ofx::ImageEffect::IsIdentityArgs &args);
    virtual OfxStatus render(ofx::ImageEffect::RenderArgs &args);
    // getRegionOfDefinition
    // getRegionsOfInterest
    // beginInstanceChanged
    // instanceChanged
    // endInstanceChanged
    
  protected:
    
    ofx::Clip cSource;
    ofx::Clip cOutput;
    ofx::Clip cMask;
    
    ofx::ChoiceParameter pType;
    ofx::ChoiceParameter pFilter;
    ofx::Int2Parameter pRadius;
    ofx::DoubleParameter pZoom;
    ofx::DoubleParameter pAngle;
    ofx::Double2Parameter pCenter;
};

// Plugin

class BlurPlugin : public ofx::ImageEffectPlugin<BlurDescriptor, BlurEffect> {
  public:
    BlurPlugin()
      : ofx::ImageEffectPlugin<BlurDescriptor, BlurEffect>() {
      setMajorVersion(1);
      setMinorVersion(0);
      setID("gatgui.filter.multiBlur");
    }
    virtual ~BlurPlugin() {
    }
};

// ---

BlurDescriptor::BlurDescriptor(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl)
  : ofx::ImageEffectDescriptor(h, hdl) {
}

BlurDescriptor::~BlurDescriptor() {
}

OfxStatus BlurDescriptor::describe() {
  setLabel("multiBlur");
  setShortLabel("multiBlur");
  setLongLabel("multiBlur");
  setGrouping("gatgui");
  setSupportedContext(0, ofx::ImageEffectContextFilter);
  setSingleInstance(false);
  setRenderThreadSafety(ofx::RenderThreadFullySafe);
  setHostFrameThreading(true);
  setMultiResolutionSupport(false);
  setTilesSupport(true);
  requireTemporalClipAccess(false);
  setMultipleClipDepthsSupport(false);
  setSupportedPixelDepth(0, ofx::BitDepthFloat);
  setFieldRenderTwiceAlways(true);
  return kOfxStatOK;
}

OfxStatus BlurDescriptor::describeInContext(ofx::ImageEffectContext ctx) {
  ofx::ClipDescriptor iClip = defineClip("Source");
  iClip.setSupportedComponent(0, ofx::ImageComponentRGBA);
  
  ofx::ClipDescriptor oClip = defineClip("Output");
  oClip.setSupportedComponent(0, ofx::ImageComponentRGBA);
  
  ofx::ClipDescriptor mClip = defineClip("Mask");
  mClip.setSupportedComponent(0, ofx::ImageComponentRGBA);
  mClip.setSupportedComponent(0, ofx::ImageComponentAlpha);
  mClip.setOptional(true);
  
  ofx::ChoiceParameterDescriptor type = parameters().defineChoiceParam("type");
  type.setAnimating(false);
  type.setPersistant(true);
  type.setChoice(0, "standard");
  type.setChoice(1, "directional");
  type.setChoice(2, "radial");
  type.setDefault(0);
  
  ofx::ChoiceParameterDescriptor filter = parameters().defineChoiceParam("filter");
  filter.setAnimating(false);
  filter.setPersistant(true);
  filter.setChoice(0, "box");
  filter.setChoice(1, "triangle");
  filter.setChoice(2, "gaussian");
  filter.setDefault(2);
  
  ofx::Int2ParameterDescriptor radius = parameters().defineInt2Param("radius");
  radius.setAnimating(false);
  radius.setPersistant(true);
  radius.setMin(0, 0);
  radius.setMax(100, 100);
  radius.setDefault(2, 2);
  // this seems to fail
  //radius.setDimensionLabel(0, "dir1");
  //radius.setDimensionLabel(1, "dir2");
  
  // use for directional and radial blur
  ofx::DoubleParameterDescriptor angle = parameters().defineDoubleParam("angle");
  angle.setPersistant(true);
  angle.setAnimating(true);
  angle.setDefault(0);
  angle.setMin(0);
  angle.setMax(360);
  angle.setIncrement(0.001);
  angle.setDigits(3);
  angle.enable(false);
  
  // used for radial blur only
  ofx::Double2ParameterDescriptor center = parameters().defineDouble2Param("center");
  center.setMin(0, 0);
  center.setMax(1, 1);
  center.setDefault(0.5, 0.5);
  center.setPersistant(true);
  center.setAnimating(true);
  center.setDimensionLabel(0, "X");
  center.setDimensionLabel(1, "X");
  center.setDigits(3);
  center.setIncrement(0.001);
  center.setDoubleType(ofx::DoubleParamNormalisedXY);
  center.enable(false);
  
  // used for radial blur only
  ofx::DoubleParameterDescriptor zoom = parameters().defineDoubleParam("zoom");
  zoom.setPersistant(true);
  zoom.setAnimating(true);
  zoom.setMin(0);
  zoom.setMax(1);
  zoom.setDefault(0.001);
  zoom.setDigits(3);
  zoom.setIncrement(0.001);
  zoom.enable(false);
  
  return kOfxStatOK;
}

// ---

BlurEffect::BlurEffect(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl)
  : ofx::ImageEffect(h, hdl) {
  cSource = getClip("Source");
  cOutput = getClip("Output");
  cMask = getClip("Mask");
  pType = parameters().getChoiceParam("type");
  pFilter = parameters().getChoiceParam("filter");
  pRadius = parameters().getInt2Param("radius");
  pAngle = parameters().getDoubleParam("angle");
  pZoom = parameters().getDoubleParam("zoom");
  pCenter = parameters().getDouble2Param("center");
}

BlurEffect::~BlurEffect() {
}

OfxStatus BlurEffect::isIdentity(ofx::ImageEffect::IsIdentityArgs &args) {
  int wsamples=0, hsamples=0;
  // this seems to fail... wsamples seems to be always 0
  pRadius.getValue(wsamples, hsamples);
  if (wsamples == 0 && hsamples == 0) {
    args.idClip = "Source";
    args.idTime = args.time;
    return kOfxStatOK;
  } else {
    return kOfxStatReplyDefault;
  }
}

OfxStatus BlurEffect::render(ofx::ImageEffect::RenderArgs &args) {
  
  ofx::Image iSource = cSource.getImage(args.time);
  ofx::Image iOutput = cOutput.getImage(args.time);
  
  ofx::RGBAColourF *srcPix, *dstPix;
  
  // filter width = wsamples*2 + 1
  int wsamples=0, hsamples=0;
  
  pRadius.getValue(wsamples, hsamples);
  
  float *wweights = new float[wsamples + 1];
  float *hweights = new float[hsamples + 1];
  
  if (pFilter.getValue() == 0) {
    
    for (int i=0; i<=wsamples; ++i) {
      wweights[i] = 1.0f;
    }
    for (int i=0; i<=hsamples; ++i) {
      hweights[i] = 1.0f;
    }
    
  } else if (pFilter.getValue() == 1) {
    
    for (int i=0; i<=wsamples; ++i) {
      wweights[i] = float(wsamples + 1 - i);
    }
    for (int i=0; i<=hsamples; ++i) {
      hweights[i] = float(hsamples + 1 - i);
    }
    
  } else {
    
    float wtheta = float((wsamples + 1) / 3);
    float htheta = float((hsamples + 1) / 3);
    
    float wInv2ThetaSqr = 1.0f / (2.0f * wtheta * wtheta);
    float hInv2ThetaSqr = 1.0f / (2.0f * htheta * htheta);
    
    for (int i=0; i<=wsamples; ++i) {
      wweights[i] = (float) exp(- wInv2ThetaSqr * i * i);
    }
    for (int i=0; i<=hsamples; ++i) {
      hweights[i] = (float) exp(- hInv2ThetaSqr * i * i);
    }
  }
  
  if (pType.getValue() == 0) {
    // standard blur
    ofx::Log("gatgui.filter.multiBlur: standard, %dx%d samples", wsamples, hsamples);
    
    // renderScale ?
    
    int tmpw = args.renderWindow.x2 - args.renderWindow.x1;
    int tmph = args.renderWindow.y2 - args.renderWindow.y1;
    int pixSize = 4 * sizeof(float);
    int rowSize = tmpw * pixSize;
    
    unsigned char *tmpPix = new unsigned char[tmpw * tmph * pixSize];
    dstPix = (ofx::RGBAColourF*) tmpPix;
    
    // first pass (horizontal)
    for (int y=args.renderWindow.y1; y<args.renderWindow.y2; ++y) {
      if (abort()) {
        break;
      }
      for (int x=args.renderWindow.x1; x<args.renderWindow.x2; ++x) {
        dstPix->r = 0.0f;
        dstPix->g = 0.0f;
        dstPix->b = 0.0f;
        dstPix->a = 0.0f;
        float w = 0.0f;
        int widx = 0;
        for (int x2=x-wsamples; x2<=x+wsamples; ++x2) {
          widx = x2 - x;
          widx = (widx < 0 ? -widx : widx);
          if (iSource.pixelAddress(x2, y, srcPix)) {
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
    
    // second pass (vertical)
    for (int x=args.renderWindow.x1; x<args.renderWindow.x2; ++x) {
      if (abort()) {
        break;
      }
      for (int y=args.renderWindow.y1; y<args.renderWindow.y2; ++y) {
        if (!iOutput.pixelAddress(x, y, dstPix)) {
          continue;
        }
        srcPix = (ofx::RGBAColourF*)(tmpPix +
                                     ((y - hsamples) - args.renderWindow.y1) * rowSize +
                                     (x - args.renderWindow.x1) * pixSize);
        float w = 0.0f;
        int widx = 0;
        for (int y2=y-hsamples; y2<=y+hsamples; ++y2) {
          widx = y2 - y;
          widx = (widx < 0 ? -widx : widx);
          if (y2 >= args.renderWindow.y1 && y2 < args.renderWindow.y2) {
            w += hweights[widx];
            dstPix->r += hweights[widx] * srcPix->r;
            dstPix->g += hweights[widx] * srcPix->g;
            dstPix->b += hweights[widx] * srcPix->b;
            dstPix->a += hweights[widx] * srcPix->a;
          }
          srcPix += tmpw;
        }
        w = 1.0f / w;
        dstPix->r *= w;
        dstPix->g *= w;
        dstPix->b *= w;
        dstPix->a *= w;
      }
    }
    
    delete[] tmpPix;
    
  } else {
    
    for (int y=args.renderWindow.y1; y<args.renderWindow.y2; ++y) {
      if (abort()) {
        break;
      }
      if (!iOutput.pixelAddress(args.renderWindow.x1, y, dstPix)) {
        continue;
      }
      for (int x=args.renderWindow.x1; x<args.renderWindow.x2; ++x) {
        if (!iSource.pixelAddress(x, y, srcPix)) {
          dstPix->r = 0.0f;
          dstPix->g = 0.0f;
          dstPix->b = 0.0f;
          dstPix->a = 1.0f;
        } else {
          dstPix->r = srcPix->r;
          dstPix->g = srcPix->g;
          dstPix->b = srcPix->b;
          dstPix->a = srcPix->a;
        }
        ++dstPix;
      }
    }
  }
  
  delete[] wweights;
  delete[] hweights;
  
  // mask?
  
  iSource.release();
  iOutput.release();
  
  return (abort() ? kOfxStatFailed : kOfxStatOK);
}

// ---

OfxExport int OfxGetNumberOfPlugins(void) {
  return 1;
}

OfxExport OfxPlugin* OfxGetPlugin(int i) {
  if (i == 0) {
    BlurPlugin *p = new BlurPlugin();
    return p->description();
  }
  return NULL;
}

