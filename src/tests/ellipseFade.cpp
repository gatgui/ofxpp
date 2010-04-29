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

#if 0
# define FORCE_OVERLAY_REDRAW
#endif

#define CLAMP(val, minVal, maxVal) (val < minVal ? minVal : (val > maxVal ? maxVal : val))

class EllipseFadeInteract : public ofx::Interact {
  public:
    
    EllipseFadeInteract(ofx::ImageEffectHost *host, OfxInteractHandle hdl) throw(ofx::Exception);
    virtual ~EllipseFadeInteract();
    
    virtual OfxStatus draw(ofx::Interact::DrawArgs &args);
    virtual OfxStatus penMotion(ofx::Interact::PenArgs &args);
    virtual OfxStatus penDown(ofx::Interact::PenArgs &args);
    virtual OfxStatus penUp(ofx::Interact::PenArgs &args);
    
  protected:
    
    enum DragOp {
      DO_NONE = 0,
      DO_CENTER,
      DO_WIDTH,
      DO_HEIGHT
    };

    DragOp mDragOp;
    bool mWidthSelected;
    bool mHeightSelected;
    bool mCenterSelected;
    double mLastX;
    double mLastY;
};

class EllipseFadeDescriptor : public ofx::ImageEffectDescriptor {
  public:
    
    EllipseFadeDescriptor(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl) throw(ofx::Exception);
    virtual ~EllipseFadeDescriptor();
    
    virtual OfxStatus describe();
    virtual OfxStatus describeInContext(ofx::ImageEffectContext ctx);
};

class EllipseFadeEffect : public ofx::ImageEffect {
  public:
    
    EllipseFadeEffect(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl) throw(ofx::Exception);
    virtual ~EllipseFadeEffect();
    
    double normalisedDistanceToEllipseCenter(double x, double y, double w, double h, double px, double py);
    
    virtual OfxStatus isIdentity(ofx::ImageEffect::IsIdentityArgs &args);
    //virtual OfxStatus getRegionOfDefinition(ofx::ImageEffect::GetRoDArgs &args);
    //virtual OfxStatus getRegionsOfInterest(ofx::ImageEffect::GetRoIsArgs &args);
    virtual OfxStatus render(ofx::ImageEffect::RenderArgs &args);
    
  public:
    
    ofx::Double2Parameter pCenter;
    ofx::DoubleParameter pWidth;
    ofx::DoubleParameter pHeight;
    ofx::BooleanParameter pInvert;
};

class EllipseFadePlugin : public ofx::ImageEffectPlugin<EllipseFadeDescriptor, EllipseFadeEffect> {
  public:
    EllipseFadePlugin();
    virtual ~EllipseFadePlugin();
};

// ---

EllipseFadeInteract::EllipseFadeInteract(ofx::ImageEffectHost *host, OfxInteractHandle hdl) throw(ofx::Exception)
  : ofx::Interact(host, hdl),
    mDragOp(EllipseFadeInteract::DO_NONE),
    mWidthSelected(false),
    mHeightSelected(false),
    mCenterSelected(false),
    mLastX(-1),
    mLastY(-1) {
  // do I need to call setSlaveToParam? This seems to already be the case in fusion
  setSlaveToParam(0, "center");
  setSlaveToParam(1, "width");
  setSlaveToParam(2, "height");
}

EllipseFadeInteract::~EllipseFadeInteract() {
}

OfxStatus EllipseFadeInteract::penMotion(ofx::Interact::PenArgs &args) {
  if (mDragOp == DO_NONE) {
    return kOfxStatReplyDefault;
  }

  ofx::Double2Parameter pC = ((EllipseFadeEffect*) args.effect)->pCenter; //args.effect->parameters().getDouble2Param("center");
  ofx::DoubleParameter pW = ((EllipseFadeEffect*) args.effect)->pWidth; //args.effect->parameters().getDoubleParam("width");
  ofx::DoubleParameter pH = ((EllipseFadeEffect*) args.effect)->pHeight; //args.effect->parameters().getDoubleParam("height");
  
  double ecx, ecy;
  pC.getValueAtTime(args.time, ecx, ecy);
  double ew = 0.5 * pW.getValueAtTime(args.time);
  double eh = 0.5 * pH.getValueAtTime(args.time);
  
  double wext, hext;
  args.effect->projectExtent(wext, hext);
  
  double xoff, yoff;
  args.effect->projectOffset(xoff, yoff);
  
  // canonical values for eclipse
  double cecx, cecy, cew, ceh;
  ofx::NormalisedToCanonicalCoords(ecx, ecy, wext, hext, xoff, yoff, true, cecx, cecy);
  ofx::NormalisedToCanonicalCoords(ew, eh, wext, hext, 0, 0, false, cew, ceh);
  
  if (mDragOp == DO_CENTER) {
    double dx = args.x - mLastX;
    double dy = args.y - mLastY;
    cecx += dx;
    cecy += dy;
    ofx::CanonicalToNormalisedCoords(cecx, cecy, wext, hext, xoff, yoff, true, ecx, ecy);
    if (pC.isAutoKeying()) {
      pC.setValueAtTime(args.time, ecx, ecy);
    } else {
      pC.setValue(ecx, ecy);
    }
#ifdef FORCE_OVERLAY_REDRAW
    redraw();
#endif

  } else if (mDragOp == DO_WIDTH) {
    double dx = args.x - mLastX;
    cew += dx;
    ofx::CanonicalToNormalisedCoords(cew, ceh, wext, hext, 0, 0, false, ew, eh);
    ew *= 2.0;
    if (pW.isAutoKeying()) {
      pW.setValueAtTime(args.time, ew);
    } else {
      pW.setValue(ew);
    }
#ifdef FORCE_OVERLAY_REDRAW
    redraw();
#endif

  } else if (mDragOp == DO_HEIGHT) {
    double dy = args.y - mLastY;
    ceh += dy;
    ofx::CanonicalToNormalisedCoords(cew, ceh, wext, hext, 0, 0, false, ew, eh);
    eh *= 2.0;
    if (pH.isAutoKeying()) {
      pH.setValueAtTime(args.time, eh);
    } else {
      pH.setValue(eh);
    }
#ifdef FORCE_OVERLAY_REDRAW
    redraw();
#endif

  }

  mLastX = args.x;
  mLastY = args.y;
  
  return kOfxStatOK;
}
    
OfxStatus EllipseFadeInteract::penDown(ofx::Interact::PenArgs &args) {
  
  ofx::Double2Parameter pC = ((EllipseFadeEffect*) args.effect)->pCenter; //args.effect->parameters().getDouble2Param("center");
  ofx::DoubleParameter pW = ((EllipseFadeEffect*) args.effect)->pWidth; //args.effect->parameters().getDoubleParam("width");
  ofx::DoubleParameter pH = ((EllipseFadeEffect*) args.effect)->pHeight; //args.effect->parameters().getDoubleParam("height");
  
  double ecx, ecy;
  pC.getValueAtTime(args.time, ecx, ecy);
  double ew = 0.5 * pW.getValueAtTime(args.time);
  double eh = 0.5 * pH.getValueAtTime(args.time);
  
  double wext, hext;
  args.effect->projectExtent(wext, hext);
  
  double xoff, yoff;
  args.effect->projectOffset(xoff, yoff);
  
  // canonical values for eclipse
  double cecx, cecy, cew, ceh;
  ofx::NormalisedToCanonicalCoords(ecx, ecy, wext, hext, xoff, yoff, true, cecx, cecy);
  ofx::NormalisedToCanonicalCoords(ew, eh, wext, hext, 0, 0, false, cew, ceh);

  double bw = 4.0 * args.pixelScaleX;
  double bh = 4.0 * args.pixelScaleY;
  
  if (args.x >= cecx-bw && args.x <= cecx+bw) {
    if (args.y >= cecy-bh && args.y <= cecy+bh) {
      mDragOp = DO_CENTER;
    } else if (args.y >= cecy+ceh-bh && args.y <= cecy+ceh+bh) {
      mDragOp = DO_HEIGHT;
    }
  } else if (args.x >= cecx+cew-bw && args.x <= cecx+cew+bw && args.y >= cecy-bh && args.y <= cecy+bh) {
    mDragOp = DO_WIDTH;
  }
  
  mLastX = args.x;
  mLastY = args.y;
  
  mCenterSelected = (mDragOp == DO_CENTER);
  mWidthSelected = (mDragOp == DO_WIDTH);
  mHeightSelected = (mDragOp == DO_HEIGHT);
  
#ifdef FORCE_OVERLAY_REDRAW
  if (mDragOp != DO_NONE) {
    redraw();
  }
#endif
  
  return kOfxStatOK;
}

OfxStatus EllipseFadeInteract::penUp(ofx::Interact::PenArgs &) {
  mCenterSelected = false;
  mWidthSelected = false;
  mHeightSelected = false;
#ifdef FORCE_OVERLAY_REDRAW
  if (mDragOp != DO_NONE) {
    redraw();
  }
#endif
  mDragOp = DO_NONE;
  return kOfxStatOK;
}

OfxStatus EllipseFadeInteract::draw(ofx::Interact::DrawArgs &args) {  
  ofx::Double2Parameter pC = ((EllipseFadeEffect*) args.effect)->pCenter; //args.effect->parameters().getDouble2Param("center");
  ofx::DoubleParameter pW = ((EllipseFadeEffect*) args.effect)->pWidth; //args.effect->parameters().getDoubleParam("width");
  ofx::DoubleParameter pH = ((EllipseFadeEffect*) args.effect)->pHeight; //args.effect->parameters().getDoubleParam("height");
  
  double ecx, ecy;
  pC.getValueAtTime(args.time, ecx, ecy);
  double ew = 0.5 * pW.getValueAtTime(args.time);
  double eh = 0.5 * pH.getValueAtTime(args.time);
  
  double wext, hext;
  args.effect->projectExtent(wext, hext);
  
  double xoff, yoff;
  args.effect->projectOffset(xoff, yoff);
  
  //double par = effect->projectPixelAspectRatio();
  
  double cecx, cecy, cew, ceh;
  ofx::NormalisedToCanonicalCoords(ecx, ecy, wext, hext, xoff, yoff, true, cecx, cecy);
  ofx::NormalisedToCanonicalCoords(ew, eh, wext, hext, 0, 0, false, cew, ceh);

  double bw = 2.0 * args.pixelScaleX;
  double bh = 2.0 * args.pixelScaleY;
  
  // center manipulator
  if (mCenterSelected) {
    glColor3d(1.0, 0.0, 0.0);
  } else {
    glColor3d(0.0, 1.0, 0.0);
  }
  glBegin(GL_LINE_LOOP);
  glVertex2d(cecx-bw, cecy-bh);
  glVertex2d(cecx+bw, cecy-bh);
  glVertex2d(cecx+bw, cecy+bh);
  glVertex2d(cecx-bw, cecy+bh);
  glEnd();

  // width manipulator
  if (mWidthSelected) {
    glColor3d(1.0, 0.0, 0.0);
  } else {
    glColor3d(0.0, 1.0, 0.0);
  }
  glBegin(GL_LINE_LOOP);
  glVertex2d(cecx+cew-bw, cecy-bh);
  glVertex2d(cecx+cew+bw, cecy-bh);
  glVertex2d(cecx+cew+bw, cecy+bh);
  glVertex2d(cecx+cew-bw, cecy+bh);
  glEnd();
  glBegin(GL_LINES);
  glVertex2d(cecx+bw, cecy);
  glVertex2d(cecx+cew-bw, cecy);
  glEnd();

  // height manipulator
  if (mHeightSelected) {
    glColor3d(1.0, 0.0, 0.0);
  } else {
    glColor3d(0.0, 1.0, 0.0);
  }
  glBegin(GL_LINE_LOOP);
  glVertex2d(cecx-bw, cecy+ceh-bh);
  glVertex2d(cecx+bw, cecy+ceh-bh);
  glVertex2d(cecx+bw, cecy+ceh+bh);
  glVertex2d(cecx-bw, cecy+ceh+bh);
  glEnd();
  glBegin(GL_LINES);
  glVertex2d(cecx, cecy+bh);
  glVertex2d(cecx, cecy+ceh-bh);
  glEnd();
  
  return kOfxStatOK;
}

// ---

EllipseFadeDescriptor::EllipseFadeDescriptor(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl) throw(ofx::Exception)
  : ofx::ImageEffectDescriptor(h, hdl) {
}

EllipseFadeDescriptor::~EllipseFadeDescriptor() {
}

OfxStatus EllipseFadeDescriptor::describe() {
  setLabel("ellipseFade");
  setShortLabel("ellipseFade");
  setLongLabel("ellipseFade");
  setGrouping("gatgui");
  setSingleInstance(false);
  setHostFrameThreading(true);
  setRenderThreadSafety(ofx::RenderThreadFullySafe);
  setSupportedPixelDepth(0, ofx::BitDepthFloat);
  setSupportedContext(0, ofx::ImageEffectContextFilter);
  requireTemporalClipAccess(false);
  setTilesSupport(true);
  setFieldRenderTwiceAlways(true);
  setMultipleClipDepthsSupport(false);
  setMultipleClipPARsSupport(false);
  setMultiResolutionSupport(false);
  if (host()->supportsOverlays()) {
    setOverlayInteract(ofx::InteractEntryPoint<EllipseFadePlugin, ofx::InteractDescriptor, EllipseFadeInteract>);
  }
  return kOfxStatOK;
}

OfxStatus EllipseFadeDescriptor::describeInContext(ofx::ImageEffectContext) {
  
  ofx::ClipDescriptor clip;
  
  clip = defineClip("Output");
  clip.setSupportedComponent(0, ofx::ImageComponentRGBA);
  
  clip = defineClip("Source");
  clip.setSupportedComponent(0, ofx::ImageComponentRGBA);
  
  ofx::Double2ParameterDescriptor c = parameters().defineDouble2Param("center");
  c.setDefault(0.5, 0.5);
  c.setMin(0, 0);
  c.setMax(1, 1);
  c.setDigits(3);
  c.setDimensionLabel(0, "X");
  c.setDimensionLabel(1, "Y");
  c.setPersistant(true);
  c.setAnimateable(true);
  
  ofx::DoubleParameterDescriptor w = parameters().defineDoubleParam("width");
  w.setDefault(0.5);
  w.setMin(0.0);
  w.setMax(1.0);
  w.setIncrement(0.001);
  w.setDigits(3);
  w.setPersistant(true);
  w.setAnimateable(true);
  w.setDoubleType(ofx::DoubleParamNormalisedX);
  
  ofx::DoubleParameterDescriptor h = parameters().defineDoubleParam("height");
  h.setDefault(0.5);
  h.setMin(0.0);
  h.setMax(1.0);
  h.setIncrement(0.001);
  h.setDigits(3);
  h.setPersistant(true);
  h.setAnimateable(true);
  h.setDoubleType(ofx::DoubleParamNormalisedY);
  
  ofx::BooleanParameterDescriptor i = parameters().defineBooleanParam("invert");
  i.setDefault(false);
  i.setPersistant(true);
  i.setAnimateable(false);
  
  return kOfxStatOK;
}

// ---

EllipseFadeEffect::EllipseFadeEffect(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl) throw(ofx::Exception)
  : ofx::ImageEffect(h, hdl) {
  pCenter = parameters().getDouble2Param("center");
  pWidth = parameters().getDoubleParam("width");
  pHeight = parameters().getDoubleParam("height");
  pInvert = parameters().getBooleanParam("invert");
}

EllipseFadeEffect::~EllipseFadeEffect() {
}

double EllipseFadeEffect::normalisedDistanceToEllipseCenter(double x, double y, double w, double h, double px, double py) {
  double dx = (px - x) / w;
  double dy = (py - y) / h;
  return (dx*dx + dy*dy);
}

OfxStatus EllipseFadeEffect::isIdentity(ofx::ImageEffect::IsIdentityArgs &args) {
  //ofx::DoubleParameter w = parameters().getDoubleParam("width");
  //ofx::DoubleParameter h = parameters().getDoubleParam("height");
  if (pWidth.getValue() <= 0.0 || pHeight.getValue() <= 0.0) {
    args.idClip = "Source";
    args.idTime = args.time;
    return kOfxStatOK;
  } else {
    return kOfxStatReplyDefault;
  }
}

/*
OfxStatus EllipseFadeEffect::getRegionOfDefinition(ofx::ImageEffect::GetRoDArgs &args) {
  ofx::Rect<double> RoD;
  // -> check center, width, and height
  // -> also apply renderScaleX and renderScaleY
  // -> return in Canonical Coords
  
  //void projectSize(double &w, double &h) throw(Exception);
  //void projectOffset(double &x, double &y) throw(Exception);
  //void projectExtent(double &w, double &h) throw(Exception);
  //double projectPixelAspectRatio() throw(Exception);
}

OfxStatus EllipseFadeEffect::getRegionsOfInterest(ofx::ImageEffect::GetRoIArgs &args) {
}
*/

OfxStatus EllipseFadeEffect::render(ofx::ImageEffect::RenderArgs &args) { 
  // renderWindow is in pixels, not canonical coords
  
  ofx::Clip cSrc = getClip("Source");
  ofx::Clip cOut = getClip("Output");
  
  ofx::Image iSrc = cSrc.getImage(args.time);
  ofx::Image iOut = cOut.getImage(args.time);
  
  ofx::RGBAColourF *srcPix, *dstPix;
  
  //ofx::Double2Parameter pCenter = parameters().getDouble2Param("center");
  //ofx::DoubleParameter pWidth = parameters().getDoubleParam("width");
  //ofx::DoubleParameter pHeight = parameters().getDoubleParam("height");
  //ofx::BooleanParameter pInvert = parameters().getBooleanParam("invert");
  
  double nx, ny;
  pCenter.getValueAtTime(args.time, nx, ny);
  
  double w = pWidth.getValueAtTime(args.time);
  double h = pHeight.getValueAtTime(args.time);
  bool invert = pInvert.getValue();
  
  double xoff, yoff;
  projectOffset(xoff, yoff);
  
  double wext, hext;
  projectExtent(wext, hext);
  
  double par = projectPixelAspectRatio();
  
  double cx, cy;
  ofx::NormalisedToCanonicalCoords(nx, ny, wext, hext, xoff, yoff, true, cx, cy);
  
  double cw, ch;
  ofx::NormalisedToCanonicalCoords(w*0.5, h*0.5, wext, hext, 0, 0, false, cw, ch);
  
  //host()->message()->sendTo(this, ofx::MessageTypeMessage, NULL, "ellipse center: %f, %f", cx, cy);
  //host()->message()->sendTo(this, ofx::MessageTypeMessage, NULL, "ellipse dimension: %f, %f", cw, ch);
  
  double pcx, pcy;
  
  if (invert) {
    for (int y=args.renderWindow.y1; y<args.renderWindow.y2; ++y) {
      if (abort()) {
        break;
      }
      if (!iOut.pixelAddress(args.renderWindow.x1, y, dstPix)) {
        continue;
      }
      for (int x=args.renderWindow.x1; x<args.renderWindow.x2; ++x) {
        PixelToCanonicalCoords(x, y, par, args.renderScaleX, args.renderScaleY, args.field, pcx, pcy);
        double d = normalisedDistanceToEllipseCenter(cx, cy, cw, ch, pcx, pcy);
        if (d <= 1.0) {
          if (!iSrc.pixelAddress(x, y, srcPix)) {
            dstPix->r = 0.0f;
            dstPix->g = 0.0f;
            dstPix->b = 0.0f;
            dstPix->a = 1.0f;
          } else {
            double falloff = (1.0f - float(d * d));
            dstPix->r = falloff * srcPix->r;
            dstPix->g = falloff * srcPix->g;
            dstPix->b = falloff * srcPix->b;
            dstPix->a = srcPix->a;
          }
        } else {
          if (!iSrc.pixelAddress(x, y, srcPix)) {
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
        }
        dstPix++;
      }
    }
  } else {
    for (int y=args.renderWindow.y1; y<args.renderWindow.y2; ++y) {
      if (abort()) {
        break;
      }
      if (!iOut.pixelAddress(args.renderWindow.x1, y, dstPix)) {
        continue;
      }
      for (int x=args.renderWindow.x1; x<args.renderWindow.x2; ++x) {
        PixelToCanonicalCoords(x, y, par, args.renderScaleX, args.renderScaleY, args.field, pcx, pcy);
        double d = normalisedDistanceToEllipseCenter(cx, cy, cw, ch, pcx, pcy);
        if (d <= 1.0) {
          if (!iSrc.pixelAddress(x, y, srcPix)) {
            dstPix->r = 0.0f;
            dstPix->g = 0.0f;
            dstPix->b = 0.0f;
            dstPix->a = 1.0f;
          } else {
            float falloff = (1.0f - float(d * d));
            dstPix->r = falloff * srcPix->r;
            dstPix->g = falloff * srcPix->g;
            dstPix->b = falloff * srcPix->b;
            dstPix->a = srcPix->a;
          }
        } else {
          dstPix->r = 0.0f;
          dstPix->g = 0.0f;
          dstPix->b = 0.0f;
          if (!iSrc.pixelAddress(x, y, srcPix)) {
            dstPix->a = 1.0f;
          } else {
            dstPix->a = srcPix->a;
          }
        }
        dstPix++;
      }
    }
  }
  
  iSrc.release();
  iOut.release();
  
  if (abort()) {
    return kOfxStatFailed;
  } else {
    return kOfxStatOK;
  }
  
}

// ---

EllipseFadePlugin::EllipseFadePlugin()
  : ofx::ImageEffectPlugin<EllipseFadeDescriptor, EllipseFadeEffect>() {
  setMajorVersion(1);
  setMinorVersion(0);
  setID("gatgui.filter.ellipseFade");
}

EllipseFadePlugin::~EllipseFadePlugin() {
}

// ---

OfxExport int OfxGetNumberOfPlugins(void) {
  return 1;
}

OfxExport OfxPlugin* OfxGetPlugin(int i) {
  if (i == 0) {
    EllipseFadePlugin *p = new EllipseFadePlugin();
    return p->description();
  }
  return NULL;
}

