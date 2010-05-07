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
    virtual OfxStatus instanceChanged(ofx::ImageEffect::InstanceChangedArgs &args);
    
  protected:
    
    ofx::Clip cSource;
    ofx::Clip cOutput;
    ofx::Clip cMask;
    
    ofx::ChoiceParameter pType;
    ofx::ChoiceParameter pFilter;
    //ofx::IntParameter pRadius1;
    //ofx::IntParameter pRadius2;
    ofx::Double2Parameter pWidth;
    ofx::DoubleParameter pZoom;
    ofx::DoubleParameter pLength;
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
  setSupportedPixelDepth(0, ofx::BitDepthFloat);
  setTilesSupport(true);
  requireTemporalClipAccess(false);
  setMultipleClipDepthsSupport(false);
  setMultipleClipPARsSupport(false);
  setMultiResolutionSupport(false);
  setFieldRenderTwiceAlways(true);
  return kOfxStatOK;
}

OfxStatus BlurDescriptor::describeInContext(ofx::ImageEffectContext /*ctx*/) {
  ofx::ClipDescriptor iClip = defineClip("Source");
  iClip.setSupportedComponent(0, ofx::ImageComponentRGBA);
  
  ofx::ClipDescriptor oClip = defineClip("Output");
  oClip.setSupportedComponent(0, ofx::ImageComponentRGBA);
  
  ofx::ClipDescriptor mClip = defineClip("Mask");
  mClip.setLabel("Mask");
  mClip.setShortLabel("Mask");
  mClip.setLongLabel("Mask");
  //mClip.setSupportedComponent(0, ofx::ImageComponentRGBA);
  mClip.setSupportedComponent(1, ofx::ImageComponentAlpha);
  mClip.setOptional(true);
  mClip.setMask(true);
  
  ofx::ChoiceParameterDescriptor type = parameters().defineChoiceParam("type");
  type.setAnimateable(false);
  type.setPersistant(true);
  type.setChoice(0, "standard");
  type.setChoice(1, "directional");
  type.setChoice(2, "radial");
  type.setDefault(0);
  
  ofx::ChoiceParameterDescriptor filter = parameters().defineChoiceParam("filter");
  filter.setAnimateable(false);
  filter.setPersistant(true);
  filter.setChoice(0, "box");
  filter.setChoice(1, "triangle");
  filter.setChoice(2, "gaussian");
  filter.setDefault(2);
  
  /*
  ofx::IntParameterDescriptor radius1 = parameters().defineIntParam("radius1");
  radius1.setAnimating(true);
  radius1.setPersistant(true);
  radius1.setMin(0);
  radius1.setMax(100);
  radius1.setDefault(2);
  
  ofx::IntParameterDescriptor radius2 = parameters().defineIntParam("radius2");
  radius2.setAnimating(true);
  radius2.setPersistant(true);
  radius2.setMin(0);
  radius2.setMax(100);
  radius2.setDefault(2);
  */
  ofx::Double2ParameterDescriptor width = parameters().defineDouble2Param("width");
  width.setPersistant(true);
  width.setAnimateable(true);
  width.setDefault(2, 2);
  width.setMin(0, 0);
  width.setMax(100, 100);
  width.setIncrement(1);
  width.setDigits(0);
  width.setDoubleType(ofx::DoubleParamPlain);
  width.setDimensionLabel(0, "w");
  width.setDimensionLabel(1, "h");
  width.setHint("Blur samples");
  
  // use for directional and radial blur
  ofx::DoubleParameterDescriptor angle = parameters().defineDoubleParam("angle");
  angle.setPersistant(true);
  angle.setAnimateable(true);
  angle.setDefault(0);
  angle.setMin(-180);
  angle.setMax(180);
  angle.setIncrement(0.001);
  angle.setDigits(3);
  //angle.enable(false);
  angle.setDoubleType(ofx::DoubleParamAngle);
  angle.setHint("Direction or blur angle");
  
  /*
  // used for directional blur only
  ofx::DoubleParameterDescriptor length = parameters().defineDoubleParam("length");
  length.setPersistant(true);
  length.setAnimateable(true);
  //length.setMin(0);
  //length.setMax(100);
  length.setDefault(0.001);
  length.setDigits(3);
  length.setIncrement(0.001);
  length.enable(false);
  length.setDoubleType(ofx::DoubleParamScale);
  */
  
  // used for radial blur only
  ofx::Double2ParameterDescriptor center = parameters().defineDouble2Param("center");
  center.setMin(0, 0);
  center.setMax(1, 1);
  center.setDefault(0.5, 0.5);
  center.setPersistant(true);
  center.setAnimateable(true);
  center.setDimensionLabel(0, "X");
  center.setDimensionLabel(1, "X");
  center.setDigits(3);
  center.setIncrement(0.001);
  center.setDoubleType(ofx::DoubleParamNormalisedXY);
  center.setHint("Radial blur center");
  //center.enable(false);
  
  ofx::DoubleParameterDescriptor zoom = parameters().defineDoubleParam("zoom");
  zoom.setPersistant(true);
  zoom.setAnimateable(true);
  zoom.setMin(0);
  zoom.setMax(10);
  zoom.setDefault(0);
  zoom.setDigits(3);
  zoom.setIncrement(0.001);
  zoom.setDoubleType(ofx::DoubleParamScale);
  zoom.setHint("Zoom scale");
  //zoom.enable(false);
  
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
  pWidth = parameters().getDouble2Param("width");
  pAngle = parameters().getDoubleParam("angle");
  //pLength = parameters().getDoubleParam("length");
  pZoom = parameters().getDoubleParam("zoom");
  pCenter = parameters().getDouble2Param("center");
}

BlurEffect::~BlurEffect() {
}

OfxStatus BlurEffect::instanceChanged(ofx::ImageEffect::InstanceChangedArgs &/*args*/) {
  /*
  if (args.name == "type") {
    if (pType.getValue() == 1) {
      // directional blur
      pAngle.enable(true);
      pZoom.enable(false);
      pCenter.enable(false);
      
    } else if (pType.getValue() == 2) {
      // radial blur
      pAngle.enable(true);
      pZoom.enable(true);
      pCenter.enable(true);
      
    } else {
      // standard blur
      pAngle.enable(false);
      pZoom.enable(false);
      pCenter.enable(false);
    }
    
    return kOfxStatOK;
  }
  */
  return kOfxStatReplyDefault;
}

OfxStatus BlurEffect::isIdentity(ofx::ImageEffect::IsIdentityArgs &args) {
  // review that
  double wsamples = 0, hsamples = 0;
  pWidth.getValueAtTime(args.time, wsamples, hsamples);
  if (wsamples <= 0 && hsamples <= 0) {
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
  
  double ws = 0, hs = 0;
  pWidth.getValueAtTime(args.time, ws, hs);
  
  // Project format
  
  double xoff, yoff, wext, hext, PAR;
  
  projectOffset(xoff, yoff);
  projectExtent(wext, hext);
  PAR = projectPixelAspectRatio();
  
  // note: clip must be pre-multipled
  
  int wsamples = int(ceil(ws * args.renderScaleX));
  int hsamples = int(ceil(hs * args.renderScaleY));
  
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
    
    //float wtheta = std::max(float((wsamples + 1) / 3), 1.0f);
    //float htheta = std::max(float((hsamples + 1) / 3), 1.0f);
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
  }
  
  if (pType.getValue() == 0) {
    // standard blur
    ofx::Log("gatgui.filter.multiBlur: standard, %dx%d samples", wsamples, hsamples);
    
    int ww = args.renderWindow.x2 - args.renderWindow.x1;
    int wh = args.renderWindow.y2 - args.renderWindow.y1;
    float wsum = 0.0f;
    
    OfxImageMemoryHandle htmp = alloc(ww * wh * sizeof(ofx::RGBAColourF));
    ofx::RGBAColourF *tmpImg = (ofx::RGBAColourF*) lock(htmp);
    
    for (int y0=args.renderWindow.y1, y1=0; y0<args.renderWindow.y2; ++y0, ++y1) {
      if (abort()) {
        break;
      }
      dstPix = tmpImg + y1 * ww;
      for (int x0=args.renderWindow.x1; x0<args.renderWindow.x2; ++x0) {
        dstPix->r = 0.0f;
        dstPix->g = 0.0f;
        dstPix->b = 0.0f;
        dstPix->a = 0.0f;
        wsum = 0.0f;
        for (int x1=0; x1<=wsamples; ++x1) {
          if (iSource.pixelAddress(x0-x1, y0, srcPix)) {
            wsum += wweights[x1];
            dstPix->r += wweights[x1] * srcPix->r;
            dstPix->g += wweights[x1] * srcPix->g;
            dstPix->b += wweights[x1] * srcPix->b;
            dstPix->a += wweights[x1] * srcPix->a;
          }
        }
        for (int x1=1; x1<=wsamples; ++x1) {
          if (iSource.pixelAddress(x0+x1, y0, srcPix)) {
            wsum += wweights[x1];
            dstPix->r += wweights[x1] * srcPix->r;
            dstPix->g += wweights[x1] * srcPix->g;
            dstPix->b += wweights[x1] * srcPix->b;
            dstPix->a += wweights[x1] * srcPix->a;
          }
        }
        if (wsum > 0) {
          wsum = 1.0f / wsum;
          dstPix->r *= wsum;
          dstPix->g *= wsum;
          dstPix->b *= wsum;
          dstPix->a *= wsum;
        }
        dstPix++;
      }
    }
    
    if (!abort()) {
      
      for (int y0=args.renderWindow.y1, y1=0; y0<args.renderWindow.y2; ++y0, ++y1) {
        if (abort()) {
          break;
        }
        if (!iOutput.pixelAddress(args.renderWindow.x1, y0, dstPix)) {
          continue;
        }
        for (int x0=args.renderWindow.x1, x1=0; x0<args.renderWindow.x2; ++x0, ++x1) {
          dstPix->r = 0.0f;
          dstPix->g = 0.0f;
          dstPix->b = 0.0f;
          dstPix->a = 0.0f;
          wsum = 0.0f;
          //for (int y2=-hsamples; y2<=0; ++y2) {
          for (int y2=0; y2<=hsamples; ++y2) {
            int srcY = y1 - y2;
            if (srcY >= 0 && srcY < wh) {
              srcPix = tmpImg + (srcY * ww) + x1;
              wsum += hweights[y2];
              dstPix->r += hweights[y2] * srcPix->r;
              dstPix->g += hweights[y2] * srcPix->g;
              dstPix->b += hweights[y2] * srcPix->b;
              dstPix->a += hweights[y2] * srcPix->a;
            }
          }
          for (int y2=1; y2<=hsamples; ++y2) {
            int srcY = y1 + y2;
            if (srcY >= 0 && srcY < wh) {
              srcPix = tmpImg + (srcY * ww) + x1;
              wsum += hweights[y2];
              dstPix->r += hweights[y2] * srcPix->r;
              dstPix->g += hweights[y2] * srcPix->g;
              dstPix->b += hweights[y2] * srcPix->b;
              dstPix->a += hweights[y2] * srcPix->a;
            }
          }
          if (wsum > 0) {
            wsum = 1.0f / wsum;
            dstPix->r *= wsum;
            dstPix->g *= wsum;
            dstPix->b *= wsum;
            dstPix->a *= wsum;
          }
          dstPix++;
        }
      }
      
    }
    
    unlock(htmp);
    free(htmp);
    
  } else if (pType.getValue() == 1) {
    // directional blur
    ofx::Log("gatgui.filter.multiBlur: directional, %dx%d samples", wsamples, hsamples);
    
    int ww = args.renderWindow.x2 - args.renderWindow.x1;
    int wh = args.renderWindow.y2 - args.renderWindow.y1;
    float wsum = 0.0f;
    
    OfxImageMemoryHandle htmp = alloc(ww * wh * sizeof(ofx::RGBAColourF));
    ofx::RGBAColourF *tmpImg = (ofx::RGBAColourF*) lock(htmp);
    
    double cx, cy, scx, scy;
    int sx, sy;
    
    double angle = pAngle.getValueAtTime(args.time) * M_PI / 180.0f;
    double wstepx = cos(angle) / (args.renderScaleX > 0.0f ? args.renderScaleX : 1.0f);
    double wstepy = sin(angle) / (args.renderScaleY > 0.0f ? args.renderScaleY : 1.0f);
    
    ofx::Log("  wstepx = %f", wstepx);
    ofx::Log("  wstepy = %f", wstepy);
    
    // first pass, along direction
    for (int y0=args.renderWindow.y1, y1=0; y0<args.renderWindow.y2; ++y0, ++y1) {
      if (abort()) {
        break;
      }
      dstPix = tmpImg + y1 * ww;
      for (int x0=args.renderWindow.x1; x0<args.renderWindow.x2; ++x0) {
        dstPix->r = 0.0f;
        dstPix->g = 0.0f;
        dstPix->b = 0.0f;
        dstPix->a = 0.0f;
        wsum = 0.0f;
        ofx::PixelToCanonicalCoords(x0, y0, PAR, args.renderScaleX, args.renderScaleY, args.field, cx, cy);
        for (int x1=0; x1<=wsamples; ++x1) {
          scx = cx - x1 * wstepx;
          scy = cy - x1 * wstepy;
          ofx::CanonicalToPixelCoords(scx, scy, PAR, args.renderScaleX, args.renderScaleY, args.field, sx, sy);
          if (iSource.pixelAddress(sx, sy, srcPix)) {
            wsum += wweights[x1];
            dstPix->r += wweights[x1] * srcPix->r;
            dstPix->g += wweights[x1] * srcPix->g;
            dstPix->b += wweights[x1] * srcPix->b;
            dstPix->a += wweights[x1] * srcPix->a;
          }
        }
        for (int x1=1; x1<wsamples; ++x1) {
          scx = cx + x1 * wstepx;
          scy = cy + x1 * wstepy;
          ofx::CanonicalToPixelCoords(scx, scy, PAR, args.renderScaleX, args.renderScaleY, args.field, sx, sy);
          if (iSource.pixelAddress(sx, sy, srcPix)) {
            wsum += wweights[x1];
            dstPix->r += wweights[x1] * srcPix->r;
            dstPix->g += wweights[x1] * srcPix->g;
            dstPix->b += wweights[x1] * srcPix->b;
            dstPix->a += wweights[x1] * srcPix->a;
          }
        }
        if (wsum > 0.0f) {
          wsum = 1.0f / wsum;
          dstPix->r *= wsum;
          dstPix->g *= wsum;
          dstPix->b *= wsum;
          dstPix->a *= wsum;
        }
        dstPix++;
      }
    }
    
    // second pass, along orthogonal direction
    if (!abort()) {
      
      for (int y0=args.renderWindow.y1; y0<args.renderWindow.y2; ++y0) {
        if (abort()) {
          break;
        }
        if (!iOutput.pixelAddress(args.renderWindow.x1, y0, dstPix)) {
          continue;
        }
        for (int x0=args.renderWindow.x1; x0<args.renderWindow.x2; ++x0) {
          dstPix->r = 0.0f;
          dstPix->g = 0.0f;
          dstPix->b = 0.0f;
          dstPix->a = 0.0f;
          wsum = 0.0f;
          ofx::PixelToCanonicalCoords(x0, y0, PAR, args.renderScaleX, args.renderScaleY, args.field, cx, cy);
          for (int y1=0; y1<=hsamples; ++y1) {
            scx = cx - y1 * wstepy;
            scy = cy - y1 * wstepx;
            ofx::CanonicalToPixelCoords(scx, scy, PAR, args.renderScaleX, args.renderScaleY, args.field, sx, sy);
            sx -= args.renderWindow.x1;
            sy -= args.renderWindow.y1;
            if (sx >= 0 && sx < ww && sy >= 0 && sy < wh) {
              srcPix = tmpImg + (sy * ww) + sx;
              wsum += hweights[y1];
              dstPix->r += hweights[y1] * srcPix->r;
              dstPix->g += hweights[y1] * srcPix->g;
              dstPix->b += hweights[y1] * srcPix->b;
              dstPix->a += hweights[y1] * srcPix->a;
            }
          }
          for (int y1=1; y1<=hsamples; ++y1) {
            scx = cx + y1 * wstepy;
            scy = cy + y1 * wstepx;
            ofx::CanonicalToPixelCoords(scx, scy, PAR, args.renderScaleX, args.renderScaleY, args.field, sx, sy);
            sx -= args.renderWindow.x1;
            sy -= args.renderWindow.y1;
            if (sx >= 0 && sx < ww && sy >= 0 && sy < wh) {
              srcPix = tmpImg + (sy * ww) + sx;
              wsum += hweights[y1];
              dstPix->r += hweights[y1] * srcPix->r;
              dstPix->g += hweights[y1] * srcPix->g;
              dstPix->b += hweights[y1] * srcPix->b;
              dstPix->a += hweights[y1] * srcPix->a;
            }
          }
          if (wsum > 0.0f) {
            wsum = 1.0f / wsum;
            dstPix->r *= wsum;
            dstPix->g *= wsum;
            dstPix->b *= wsum;
            dstPix->a *= wsum;
          }
          dstPix++;
        }
      }
      
    }
    
    unlock(htmp);
    free(htmp);
  
  } else if (pType.getValue() == 2) {
    // radial blur
    ofx::Log("gatgui.filter.multiBlur: radial, %dx%d samples", wsamples, hsamples);
    
    // still use wsamples and hsamples
    double ncx, ncy, ccx, ccy, pcx, pcy, vcx, vcy, scx, scy, ca, sa;
    int sx, sy;
    
    pCenter.getValueAtTime(args.time, ncx, ncy);
    
    double angle = pAngle.getValueAtTime(args.time) * M_PI / 180.0f;
    double astep = (wsamples > 0 ? angle / (2.0f * wsamples) : 0.0f);
    double cangle = 0.0f;
    
    ofx::NormalisedToCanonicalCoords(ncx, ncy, wext, hext, xoff, yoff, true, ccx, ccy);
    
    ofx::Log("Angle: %f", angle);
    ofx::Log("Angular step: %f", astep);
    ofx::Log("Center: (%f, %f) [normalised]", ncx, ncy);
    ofx::Log("Center: (%f, %f) [canonical]", ccx, ccy);
    
    int ww = args.renderWindow.x2 - args.renderWindow.x1;
    int wh = args.renderWindow.y2 - args.renderWindow.y1;
    float wsum = 0.0f;
    
    OfxImageMemoryHandle htmp = alloc(ww * wh * sizeof(ofx::RGBAColourF));
    ofx::RGBAColourF *tmpImg = (ofx::RGBAColourF*) lock(htmp);
    
    for (int y0=args.renderWindow.y1, y1=0; y0<args.renderWindow.y2; ++y0, ++y1) {
      if (abort()) {
        break;
      }
      dstPix = tmpImg + y1 * ww;
      for (int x0=args.renderWindow.x1; x0<args.renderWindow.x2; ++x0) {
        dstPix->r = 0.0f;
        dstPix->g = 0.0f;
        dstPix->b = 0.0f;
        dstPix->a = 0.0f;
        wsum = 0.0f;
        ofx::PixelToCanonicalCoords(x0, y0, PAR, args.renderScaleX, args.renderScaleY, args.field, pcx, pcy);
        vcx = pcx - ccx;
        vcy = pcy - ccy;
        for (int x1=0; x1<=wsamples; ++x1) {
          cangle = -x1 * astep;
          ca = cos(cangle);
          sa = sin(cangle);
          scx = ccx + vcx * ca - vcy * sa;
          scy = ccy + vcy * ca + vcx * sa;
          ofx::CanonicalToPixelCoords(scx, scy, PAR, args.renderScaleX, args.renderScaleY, args.field, sx, sy);
          if (iSource.pixelAddress(sx, sy, srcPix)) {
            wsum += wweights[x1];
            dstPix->r += wweights[x1] * srcPix->r;
            dstPix->g += wweights[x1] * srcPix->g;
            dstPix->b += wweights[x1] * srcPix->b;
            dstPix->a += wweights[x1] * srcPix->a;
          }
        }
        for (int x1=1; x1<=wsamples; ++x1) {
          cangle = x1 * astep;
          ca = cos(cangle);
          sa = sin(cangle);
          scx = ccx + vcx * ca - vcy * sa;
          scy = ccy + vcy * ca + vcx * sa;
          ofx::CanonicalToPixelCoords(scx, scy, PAR, args.renderScaleX, args.renderScaleY, args.field, sx, sy);
          if (iSource.pixelAddress(sx, sy, srcPix)) {
            wsum += wweights[x1];
            dstPix->r += wweights[x1] * srcPix->r;
            dstPix->g += wweights[x1] * srcPix->g;
            dstPix->b += wweights[x1] * srcPix->b;
            dstPix->a += wweights[x1] * srcPix->a;
          }
        }
        if (wsum > 0.0f) {
          wsum = 1.0f / wsum;
          dstPix->r *= wsum;
          dstPix->g *= wsum;
          dstPix->b *= wsum;
          dstPix->a *= wsum;
        }
        dstPix++;
      }
    }
    
    if (!abort()) {
      
      // second pass [zoom]
      double zoom = pZoom.getValueAtTime(args.time);
      double fromx, fromy, tox, toy, stepx, stepy;
      
      for (int y0=args.renderWindow.y1; y0<args.renderWindow.y2; ++y0) {
        if (abort()) {
          break;
        }
        if (!iOutput.pixelAddress(args.renderWindow.x1, y0, dstPix)) {
          continue;
        }
        for (int x0=args.renderWindow.x1; x0<args.renderWindow.x2; ++x0) {
          dstPix->r = 0.0f;
          dstPix->g = 0.0f;
          dstPix->b = 0.0f;
          dstPix->a = 0.0f;
          wsum = 0.0f;
          ofx::PixelToCanonicalCoords(x0, y0, PAR, args.renderScaleX, args.renderScaleY, args.field, pcx, pcy);
          vcx = pcx - ccx;
          vcy = pcy - ccy;
          fromx = ccx - vcx * 0.5 * zoom;
          fromy = ccy - vcy * 0.5 * zoom;
          tox = ccx + vcx * 0.5 * zoom;
          toy = ccy + vcy * 0.5 * zoom;
          stepx = (hsamples > 0 ? (tox - fromx) / (hsamples * 2.0f) : 0.0f);
          stepy = (hsamples > 0 ? (toy - fromy) / (hsamples * 2.0f) : 0.0f);
          for (int y1=0; y1<=hsamples; ++y1) {
            scx = pcx - y1 * stepx;
            scy = pcy - y1 * stepy;
            ofx::CanonicalToPixelCoords(scx, scy, PAR, args.renderScaleX, args.renderScaleY, args.field, sx, sy);
            sx -= args.renderWindow.x1;
            sy -= args.renderWindow.y1;
            if (sx >= 0 && sx < ww && sy >= 0 && sy < wh) {
              srcPix = tmpImg + sy * ww + sx;
              wsum += hweights[y1];
              dstPix->r += hweights[y1] * srcPix->r;
              dstPix->g += hweights[y1] * srcPix->g;
              dstPix->b += hweights[y1] * srcPix->b;
              dstPix->a += hweights[y1] * srcPix->a;
            }
          }
          for (int y1=1; y1<=hsamples; ++y1) {
            scx = pcx + y1 * stepx;
            scy = pcy + y1 * stepy;
            ofx::CanonicalToPixelCoords(scx, scy, PAR, args.renderScaleX, args.renderScaleY, args.field, sx, sy);
            sx -= args.renderWindow.x1;
            sy -= args.renderWindow.y1;
            if (sx >= 0 && sx < ww && sy >= 0 && sy < wh) {
              srcPix = tmpImg + sy * ww + sx;
              wsum += hweights[y1];
              dstPix->r += hweights[y1] * srcPix->r;
              dstPix->g += hweights[y1] * srcPix->g;
              dstPix->b += hweights[y1] * srcPix->b;
              dstPix->a += hweights[y1] * srcPix->a;
            }
          }
          if (wsum > 0.0f) {
            wsum = 1.0f / wsum;
            dstPix->r *= wsum;
            dstPix->g *= wsum;
            dstPix->b *= wsum;
            dstPix->a *= wsum;
          }
          dstPix++;
        }
      }
    }
    
    unlock(htmp);
    free(htmp);
    
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

