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
    ofx::IntParameter pSamples;
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
  filter.setChoice(1, "triangular");
  filter.setChoice(2, "gaussian");
  filter.setDefault(2);
  
  ofx::IntParameterDescriptor samples = parameters().defineIntParam("samples");
  samples.setAnimating(true);
  samples.setPersistant(true);
  samples.setMin(0);
  samples.setMax(1024);
  
  // use for directional and radial blur
  ofx::DoubleParameterDescriptor angle = parameters().defineDoubleParam("angle");
  angle.setPersistant(true);
  angle.setAnimating(true);
  angle.setDefault(0);
  angle.setMin(0);
  angle.setMax(360);
  angle.setIncrement(0.001);
  angle.setDigits(3);
  
  // used for radial blur only
  ofx::Double2ParameterDescriptor center = parameters().defineDouble2Param("center");
  center.setMin(0, 0);
  center.setMin(1, 0);
  center.setMax(0, 1);
  center.setMax(1, 1);
  center.setDefault(0.5, 0.5);
  center.setPersistant(true);
  center.setAnimating(true);
  center.setDimensionLabel(0, "X");
  center.setDimensionLabel(1, "X");
  center.setDigits(3);
  center.setIncrement(0.001);
  center.setDoubleType(ofx::DoubleParamNormalisedXY);
  
  // used for radial blur only
  ofx::DoubleParameterDescriptor zoom = parameters().defineDoubleParam("zoom");
  zoom.setPersistant(true);
  zoom.setAnimating(true);
  zoom.setMin(0);
  zoom.setMax(1);
  zoom.setDefault(0.001);
  zoom.setDigits(3);
  zoom.setIncrement(0.001);
  
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
  pSamples = parameters().getIntParam("samples");
  pAngle = parameters().getDoubleParam("angle");
  pZoom = parameters().getDoubleParam("zoom");
  pCenter = parameters().getDouble2Param("center");
}

BlurEffect::~BlurEffect() {
}

OfxStatus BlurEffect::isIdentity(ofx::ImageEffect::IsIdentityArgs &args) {
  ofx::IntParameter samples = parameters().getIntParam("samples");
  if (samples.getValue() == 0) {
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
  
  // filter width = nsamples*2 + 1 [center pix]
  int nsamples = pSamples.getValueAtTime(args.time);
  float *weights = new float[nsamples + 1];
  
  if (pFilter.getValue() == 0) {
    
    float sw = 1.0f / float(2 * nsamples + 1);
    
    for (int i=0; i<=nsamples; ++i) {
      weights[i] = sw;
    }
    
  } else if (pFilter.getValue() == 1) {
    
    float isum = 0.0f;
    float sw, fw = float(nsamples) + 1.0f;
    
    weights[0] = fw;
    
    for (int i=1; i<=nsamples; ++i) {
      sw = fw - float(i);
      weights[i] = sw;
      isum += sw;
    }
    
    isum = 1.0f / (2.0f * isum + fw);
    
    for (int i=0; i<=nsamples; ++i) {
      weights[i] *= isum;
    }
    
  } else {
    
    float isum = 0.0f;
    float sw;
    float i2ss = 1.0f / (2.0f * nsamples); // inverse 2 sigma square
    
    weights[0] = 1.0f;
    for (int i=1; i<=nsamples; ++i) {
      sw = exp(- float(i) * float(i) * i2ss);
      weights[i] = sw;
      isum += sw;
    }
    
    isum = 1.0f / (2.0f * isum + 1.0f);
    
    for (int i=0; i<=nsamples; ++i) {
      weights[i] *= isum;
    }
    
  }
  
  if (pType.getValue() == 0) {
    // standard blur
    ofx::Log("gatgui.filter.multiBlur: standard %d samples", nsamples);
    
    int tmpw = args.renderWindow.x2 - args.renderWindow.x1;
    int tmph = args.renderWindow.y2 - args.renderWindow.y1;
    int pixSize = 4 * sizeof(float);
    int rowSize = tmpw * pixSize;
    
    OfxImageMemoryHandle hTmp = alloc(tmph * rowSize);
    
    unsigned char *tmpPix = (unsigned char*) lock(hTmp);
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
        for (int x2=x-nsamples; x2<=x+nsamples; ++x2) {
          int widx = x2 - x;
          widx = (widx < 0 ? -widx : widx);
          if (!iSource.pixelAddress(x2, y, srcPix)) {
            //assume black opaque pixel
            dstPix->a += weights[widx];
          } else {
            dstPix->r += weights[widx] * srcPix->r;
            dstPix->g += weights[widx] * srcPix->g;
            dstPix->b += weights[widx] * srcPix->b;
            dstPix->a += weights[widx] * srcPix->a;
          }
        }
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
                                     ((y - nsamples) - args.renderWindow.y1) * rowSize +
                                     (x - args.renderWindow.x1) * pixSize);
        for (int y2=y-nsamples; y2<=y+nsamples; ++y2) {
          int widx = y2 - y;
          widx = (widx < 0 ? -widx : widx);
          if (y2 < args.renderWindow.y1 || y2 >= args.renderWindow.y2) {
            dstPix->a += weights[widx];
          } else {
            dstPix->r += weights[widx] * srcPix->r;
            dstPix->g += weights[widx] * srcPix->g;
            dstPix->b += weights[widx] * srcPix->b;
            dstPix->a += weights[widx] * srcPix->a;
          }
          srcPix += tmpw;
        }
      }
    }
    
    unlock(hTmp);
    free(hTmp);
    
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
  
  delete[] weights;
  
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

