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

class EllipseFadeInteract : public ofx::Interact {
  public:
    
    enum HostApp {
      HA_GENERIC = 0,
      HA_NUKE,
      HA_RAMEN,
      HA_FUSION,
      HA_TOXIK
    };
    
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
    HostApp mApp;
};

class EllipseFadeDescriptor : public ofx::ImageEffectDescriptor {
  public:
    
    EllipseFadeDescriptor(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl);
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
    mLastY(-1),
    mApp(EllipseFadeInteract::HA_GENERIC) {
  if (host->name() == "uk.co.thefoundry.nuke") {
    mApp = HA_NUKE;
  } else if (host->name() == "Ramen") {
    mApp = HA_RAMEN;
  } else if (host->name() == "Autodesk Toxik") {
    mApp = HA_TOXIK;
  } else if (host->name() == "com.eyeonline.Fusion") {
    mApp = HA_FUSION;
  }
  // Is this really needed?
  slaveToParam(0, "center");
  slaveToParam(1, "width");
  slaveToParam(2, "height");
}

EllipseFadeInteract::~EllipseFadeInteract() {
}

OfxStatus EllipseFadeInteract::penMotion(ofx::Interact::PenArgs &args) {
  if (mDragOp == DO_NONE) {
    return kOfxStatReplyDefault;
  }

  ofx::Double2Parameter pC = ((EllipseFadeEffect*) args.effect)->pCenter;
  ofx::DoubleParameter pW = ((EllipseFadeEffect*) args.effect)->pWidth;
  ofx::DoubleParameter pH = ((EllipseFadeEffect*) args.effect)->pHeight;
  
  double ecx, ecy;
  pC.getValueAtTime(args.time, &ecx, &ecy);
  double ew = 0.5 * pW.getValueAtTime(args.time);
  double eh = 0.5 * pH.getValueAtTime(args.time);
  
  double wext, hext;
  args.effect->projectExtent(&wext, &hext);
  
  double xoff, yoff;
  args.effect->projectOffset(&xoff, &yoff);
  
  // canonical values for eclipse
  double cecx, cecy, cew, ceh;
  ofx::NormalisedToCanonicalCoords(ecx, ecy, wext, hext, xoff, yoff, true, &cecx, &cecy);
  ofx::NormalisedToCanonicalCoords(ew, eh, wext, hext, 0, 0, false, &cew, &ceh);
  
  if (mDragOp == DO_CENTER) {
    double dx = args.x - mLastX;
    double dy = args.y - mLastY;
    cecx += dx;
    cecy += dy;
    ofx::CanonicalToNormalisedCoords(cecx, cecy, wext, hext, xoff, yoff, true, &ecx, &ecy);
    if (pC.autoKeying()) {
      pC.setValueAtTime(args.time, ecx, ecy);
    } else {
      pC.setValue(ecx, ecy);
    }

  } else if (mDragOp == DO_WIDTH) {
    double dx = args.x - mLastX;
    cew += dx;
    ofx::CanonicalToNormalisedCoords(cew, ceh, wext, hext, 0, 0, false, &ew, &eh);
    ew *= 2.0;
    if (pW.autoKeying()) {
      pW.setValueAtTime(args.time, ew);
    } else {
      pW.setValue(ew);
    }

  } else if (mDragOp == DO_HEIGHT) {
    double dy = args.y - mLastY;
    ceh += dy;
    ofx::CanonicalToNormalisedCoords(cew, ceh, wext, hext, 0, 0, false, &ew, &eh);
    eh *= 2.0;
    if (pH.autoKeying()) {
      pH.setValueAtTime(args.time, eh);
    } else {
      pH.setValue(eh);
    }
    
  }

  mLastX = args.x;
  mLastY = args.y;

#ifdef FORCE_OVERLAY_REDRAW
  redraw();
#endif
  
  return kOfxStatOK;
}
    
OfxStatus EllipseFadeInteract::penDown(ofx::Interact::PenArgs &args) {
  
  ofx::Double2Parameter pC = ((EllipseFadeEffect*) args.effect)->pCenter;
  ofx::DoubleParameter pW = ((EllipseFadeEffect*) args.effect)->pWidth;
  ofx::DoubleParameter pH = ((EllipseFadeEffect*) args.effect)->pHeight;
  
  double ecx, ecy;
  pC.getValueAtTime(args.time, &ecx, &ecy);
  double ew = 0.5 * pW.getValueAtTime(args.time);
  double eh = 0.5 * pH.getValueAtTime(args.time);
  
  double wext, hext;
  args.effect->projectExtent(&wext, &hext);
  
  double xoff, yoff;
  args.effect->projectOffset(&xoff, &yoff);
  
  // canonical values for eclipse
  double cecx, cecy, cew, ceh;
  ofx::NormalisedToCanonicalCoords(ecx, ecy, wext, hext, xoff, yoff, true, &cecx, &cecy);
  ofx::NormalisedToCanonicalCoords(ew, eh, wext, hext, 0, 0, false, &cew, &ceh);
  
  double bw, bh;
  
  bw = 4.0 * args.pixelScaleX;
  bh = 4.0 * args.pixelScaleY;
  
  if (mApp == HA_NUKE) {
    bw /= args.renderScaleX;
    bh /= args.renderScaleY;
  }
  
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
  bool doRedraw = mDragOp != DO_NONE;
  mDragOp = DO_NONE;
#ifdef FORCE_OVERLAY_REDRAW
  if (doRedraw) {
    redraw();
  }
#endif
  return kOfxStatOK;
}

OfxStatus EllipseFadeInteract::draw(ofx::Interact::DrawArgs &args) {  
  ofx::Double2Parameter pC = ((EllipseFadeEffect*) args.effect)->pCenter;
  ofx::DoubleParameter pW = ((EllipseFadeEffect*) args.effect)->pWidth;
  ofx::DoubleParameter pH = ((EllipseFadeEffect*) args.effect)->pHeight;
  
  double ecx, ecy;
  pC.getValueAtTime(args.time, &ecx, &ecy);
  double ew = 0.5 * pW.getValueAtTime(args.time);
  double eh = 0.5 * pH.getValueAtTime(args.time);
  
  double wext, hext;
  args.effect->projectExtent(&wext, &hext);
  
  double xoff, yoff;
  args.effect->projectOffset(&xoff, &yoff);
  
  double cecx, cecy, cew, ceh;
  ofx::NormalisedToCanonicalCoords(ecx, ecy, wext, hext, xoff, yoff, true, &cecx, &cecy);
  ofx::NormalisedToCanonicalCoords(ew, eh, wext, hext, 0, 0, false, &cew, &ceh);
  
  double pw, ph;
  
  pw = args.pixelScaleX;
  ph = args.pixelScaleY;
  
  if (mApp == HA_NUKE) {
    pw /= args.renderScaleX;
    ph /= args.renderScaleY;
  }
  
  double bw = 2.0 * pw;
  double bh = 2.0 * ph;
  
  // center manipulator
  if (mCenterSelected) {
    glColor3d(1.0, 0.0, 0.0);
  } else {
    glColor3d(0.0, 1.0, 0.0);
  }
  glBegin(GL_QUADS);
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
  glBegin(GL_QUADS);
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
  glBegin(GL_QUADS);
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

EllipseFadeDescriptor::EllipseFadeDescriptor(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl)
  : ofx::ImageEffectDescriptor(h, hdl) {
}

EllipseFadeDescriptor::~EllipseFadeDescriptor() {
}

OfxStatus EllipseFadeDescriptor::describe() {
  label("ellipseFade");
  shortLabel("ellipseFade");
  longLabel("ellipseFade");
  group("gatgui");
  singleInstance(false);
  hostFrameThreading(true);
  renderThreadSafety(ofx::RenderThreadFullySafe);
  supportedPixelDepth(0, ofx::BitDepthFloat);
  supportedContext(0, ofx::ImageEffectContextFilter);
  temporalClipAccess(false);
  supportsTiles(true);
  fieldRenderTwiceAlways(true);
  supportsMultipleClipDepths(false);
  supportsMultipleClipPARs(false);
  supportsMultiResolution(false);
  if (host()->supportsOverlays()) {
    overlayInteract(ofx::InteractEntryPoint<EllipseFadePlugin, ofx::InteractDescriptor, EllipseFadeInteract>);
  }
  return kOfxStatOK;
}

OfxStatus EllipseFadeDescriptor::describeInContext(ofx::ImageEffectContext) {
  
  ofx::ClipDescriptor clip;
  
  clip = defineClip("Output");
  clip.supportedComponent(0, ofx::ImageComponentRGBA);
  
  clip = defineClip("Source");
  clip.supportedComponent(0, ofx::ImageComponentRGBA);
  
  ofx::Double2ParameterDescriptor c = parameters().defineDouble2Param("center");
  c.defaultValue(0.5, 0.5);
  c.min(0.0, 0.0);
  c.max(1, 1);
  c.digits(3);
  c.dimensionLabel(0, "X");
  c.dimensionLabel(1, "Y");
  c.persistant(true);
  c.animates(true);
  c.doubleType(ofx::DoubleParamNormalisedXY);
  
  ofx::DoubleParameterDescriptor w = parameters().defineDoubleParam("width");
  w.defaultValue(0.5);
  w.min(0.0);
  w.max(1.0);
  w.increment(0.001);
  w.digits(3);
  w.persistant(true);
  w.animates(true);
  w.doubleType(ofx::DoubleParamNormalisedX);
  
  ofx::DoubleParameterDescriptor h = parameters().defineDoubleParam("height");
  h.defaultValue(0.5);
  h.min(0.0);
  h.max(1.0);
  h.increment(0.001);
  h.digits(3);
  h.persistant(true);
  h.animates(true);
  h.doubleType(ofx::DoubleParamNormalisedY);
  
  ofx::BooleanParameterDescriptor i = parameters().defineBooleanParam("invert");
  i.defaultValue(false);
  i.persistant(true);
  i.animates(false);
  
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
  if (pWidth.getValue() <= 0.0 || pHeight.getValue() <= 0.0) {
    args.idClip = "Source";
    args.idTime = args.time;
    return kOfxStatOK;
  } else {
    return kOfxStatReplyDefault;
  }
}

OfxStatus EllipseFadeEffect::render(ofx::ImageEffect::RenderArgs &args) { 
  
  ofx::Clip cSrc = getClip("Source");
  ofx::Clip cOut = getClip("Output");
  
  ofx::Image iSrc = cSrc.getImage(args.time);
  ofx::Image iOut = cOut.getImage(args.time);
  
  ofx::RGBAColourF *srcPix, *dstPix;
  
  double nx, ny;
  pCenter.getValueAtTime(args.time, &nx, &ny);
  
  double w = pWidth.getValueAtTime(args.time);
  double h = pHeight.getValueAtTime(args.time);
  bool invert = pInvert.getValue();
  
  double xoff, yoff;
  projectOffset(&xoff, &yoff);
  
  double wext, hext;
  projectExtent(&wext, &hext);
  
  double par = projectPixelAspectRatio();
  
  double cx, cy;
  ofx::NormalisedToCanonicalCoords(nx, ny, wext, hext, xoff, yoff, true, &cx, &cy);
  
  double cw, ch;
  ofx::NormalisedToCanonicalCoords(w*0.5, h*0.5, wext, hext, 0, 0, false, &cw, &ch);
  
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
        ofx::PixelToCanonicalCoords(x, y, par, args.renderScaleX, args.renderScaleY, args.field, &pcx, &pcy);
        double d = normalisedDistanceToEllipseCenter(cx, cy, cw, ch, pcx, pcy);
        if (d <= 1.0) {
          if (!iSrc.pixelAddress(x, y, srcPix)) {
            dstPix->r = 0.0f;
            dstPix->g = 0.0f;
            dstPix->b = 0.0f;
            dstPix->a = 1.0f;
          } else {
            float falloff = float(d * d);
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
        ofx::PixelToCanonicalCoords(x, y, par, args.renderScaleX, args.renderScaleY, args.field, &pcx, &pcy);
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
  majorVersion(1);
  minorVersion(0);
  identifier("gatgui.filter.ellipseFade");
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

