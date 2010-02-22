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

#define CLAMP(val, minVal, maxVal) (val < minVal ? minVal : (val > maxVal ? maxVal : val))

class SampleInteractDescriptor : public ofx::InteractDescriptor {
  public:
    SampleInteractDescriptor(ofx::ImageEffectHost *host, OfxInteractHandle hdl) throw(ofx::Exception);
    virtual ~SampleInteractDescriptor();

    virtual void describe() throw(ofx::Exception);
};

class SampleInteract : public ofx::Interact {
  public:
    
    SampleInteract(ofx::ImageEffectHost *host, OfxInteractHandle hdl) throw(ofx::Exception);
    virtual ~SampleInteract();
    
    virtual void draw(ofx::ImageEffect *effect,
                      double pixelScaleX,
                      double pixelScaleY,
                      const ofx::RGBAColourD &bgColor,
                      ofx::Time t,
                      double renderScaleX,
                      double renderScaleY) throw(ofx::Exception);
    
    virtual void penMotion(ofx::ImageEffect *effect,
                           double pixelScaleX, double pixelScaleY,
                           const ofx::RGBAColour<double> &bgColor, ofx::Time t,
                           double renderScaleX, double renderScaleY,
                           double penX, double penY, double pressure) throw(ofx::Exception);
    
    virtual void penDown(ofx::ImageEffect *effectt,
                         double pixelScaleX, double pixelScaleY,
                         const ofx::RGBAColour<double> &bgColor, ofx::Time t,
                         double renderScaleX, double renderScaleY,
                         double penX, double penY, double pressure) throw(ofx::Exception);
    
    virtual void penUp(ofx::ImageEffect *effect,
                       double pixelScaleX, double pixelScaleY,
                       const ofx::RGBAColour<double> &bgColor, ofx::Time t,
                       double renderScaleX, double renderScaleY,
                       double penX, double penY, double pressure) throw(ofx::Exception);
    
    /*
    virtual void gainFocus(ofx::ImageEffect *effect, //int w, int h,
                           double pixelScaleX, double pixelScaleY,
                           const ofx::RGBAColour<double> &bgColor, ofx::Time t,
                           double renderScaleX, double renderScaleY) throw(ofx::Exception);
    
    virtual void loseFocus(ofx::ImageEffect *effect, //int w, int h,
                           double pixelScaleX, double pixelScaleY,
                           const ofx::RGBAColour<double> &bgColor, ofx::Time t,
                           double renderScaleX, double renderScaleY) throw(ofx::Exception);
    */
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

class SampleDescriptor : public ofx::ImageEffectDescriptor {
  public:
    
    SampleDescriptor(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl) throw(ofx::Exception);
    virtual ~SampleDescriptor();
    
    virtual void describe() throw(ofx::Exception);
    virtual void describeInContext(ofx::ImageEffectContext ctx) throw(ofx::Exception);
};

class SampleEffect : public ofx::ImageEffect {
  public:
    
    SampleEffect(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl) throw(ofx::Exception);
    virtual ~SampleEffect();
    
    double normalisedDistanceToEllipseCenter(double x, double y, double w, double h, double px, double py);
    
    virtual bool isIdentity(ofx::Time t,
                            ofx::ImageField field,
                            const ofx::Rect<int> &renderWindow,
                            double renderScaleX,
                            double renderScaleY,
                            std::string &idClip,
                            ofx::Time &idTime) throw(ofx::Exception);
    
    /*
    virtual ofx::Rect<double> getRegionOfDefinition(ofx::Time t,
                                                    double renderScaleX,
                                                    double renderScaleY) throw(ofx::Exception);
    
    virtual void getRegionsOfInterest(ofx::Time t,
                                      double renderScaleX,
                                      double renderScaleY,
                                      const ofx::Rect<double> &outRoI,
                                      std::map<std::string, ofx::Rect<double> > &inClipsRoI) throw(Exception);
    */
    
    virtual void render(ofx::Time t,
                        ofx::ImageField field,
                        const ofx::Rect<int> &renderWindow,
                        double &renderScaleX,
                        double renderScaleY) throw(ofx::Exception);
};

class SamplePlugin : public ofx::ImageEffectPlugin<SampleDescriptor, SampleEffect> {
  public:
    SamplePlugin();
    virtual ~SamplePlugin();
};

// ---

SampleInteractDescriptor::SampleInteractDescriptor(ofx::ImageEffectHost *host, OfxInteractHandle hdl) throw(ofx::Exception)
  : ofx::InteractDescriptor(host, hdl) {
}

SampleInteractDescriptor::~SampleInteractDescriptor() {
}

void SampleInteractDescriptor::describe() throw(ofx::Exception) {
  // NOOP
}

// ---

SampleInteract::SampleInteract(ofx::ImageEffectHost *host, OfxInteractHandle hdl) throw(ofx::Exception)
  : ofx::Interact(host, hdl),
    mDragOp(SampleInteract::DO_NONE),
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

SampleInteract::~SampleInteract() {
}

void SampleInteract::penMotion(ofx::ImageEffect *effect,
                               double, double,
                               const ofx::RGBAColourD &, ofx::Time t,
                               double, double,
                               double penX, double penY, double) throw(ofx::Exception) {
  
  if (mDragOp == DO_NONE) {
    return;
  }

  ofx::Double2Parameter pC = effect->parameters().getDouble2Param("center");
  ofx::DoubleParameter pW = effect->parameters().getDoubleParam("width");
  ofx::DoubleParameter pH = effect->parameters().getDoubleParam("height");
  
  double ecx, ecy;
  pC.getValueAtTime(t, ecx, ecy);
  double ew = 0.5 * pW.getValueAtTime(t);
  double eh = 0.5 * pH.getValueAtTime(t);
  
  double wext, hext;
  effect->projectExtent(wext, hext);
  
  double xoff, yoff;
  effect->projectOffset(xoff, yoff);
  
  // canonical values for eclipse
  double cecx, cecy, cew, ceh;
  ofx::NormalisedToCanonicalCoords(ecx, ecy, wext, hext, xoff, yoff, true, cecx, cecy);
  ofx::NormalisedToCanonicalCoords(ew, eh, wext, hext, 0, 0, false, cew, ceh);
  
  if (mDragOp == DO_CENTER) {
    double dx = penX - mLastX;
    double dy = penY - mLastY;
    cecx += dx;
    cecy += dy;
    ofx::CanonicalToNormalisedCoords(cecx, cecy, wext, hext, xoff, yoff, true, ecx, ecy);
    pC.setValueAtTime(t, ecx, ecy);
    redraw();

  } else if (mDragOp == DO_WIDTH) {
    double dx = penX - mLastX;
    cew += dx;
    ofx::CanonicalToNormalisedCoords(cew, ceh, wext, hext, 0, 0, false, ew, eh);
    ew *= 2.0;
    pW.setValueAtTime(t, ew);
    redraw();

  } else if (mDragOp == DO_HEIGHT) {
    double dy = penY - mLastY;
    ceh += dy;
    ofx::CanonicalToNormalisedCoords(cew, ceh, wext, hext, 0, 0, false, ew, eh);
    eh *= 2.0;
    pH.setValueAtTime(t, eh);
    redraw();

  }

  mLastX = penX;
  mLastY = penY;
}
    
void SampleInteract::penDown(ofx::ImageEffect *effect,
                             double pixelScaleX, double pixelScaleY,
                             const ofx::RGBAColourD &, ofx::Time t,
                             double, double,
                             double penX, double penY, double) throw(ofx::Exception) {
  
  ofx::Double2Parameter pC = effect->parameters().getDouble2Param("center");
  ofx::DoubleParameter pW = effect->parameters().getDoubleParam("width");
  ofx::DoubleParameter pH = effect->parameters().getDoubleParam("height");
  
  double ecx, ecy;
  pC.getValueAtTime(t, ecx, ecy);
  double ew = 0.5 * pW.getValueAtTime(t);
  double eh = 0.5 * pH.getValueAtTime(t);
  
  double wext, hext;
  effect->projectExtent(wext, hext);
  
  double xoff, yoff;
  effect->projectOffset(xoff, yoff);
  
  // canonical values for eclipse
  double cecx, cecy, cew, ceh;
  ofx::NormalisedToCanonicalCoords(ecx, ecy, wext, hext, xoff, yoff, true, cecx, cecy);
  ofx::NormalisedToCanonicalCoords(ew, eh, wext, hext, 0, 0, false, cew, ceh);

  double bw = 4.0 * pixelScaleX;
  double bh = 4.0 * pixelScaleY;
  
  if (penX >= cecx-bw && penX <= cecx+bw) {
    if (penY >= cecy-bh && penY <= cecy+bh) {
      mDragOp = DO_CENTER;
    } else if (penY >= cecy+ceh-bh && penY <= cecy+ceh+bh) {
      mDragOp = DO_HEIGHT;
    }
  } else if (penX >= cecx+cew-bw && penX <= cecx+cew+bw && penY >= cecy-bh && penY <= cecy+bh) {
    mDragOp = DO_WIDTH;
  }
  
  mLastX = penX;
  mLastY = penY;
  
  mCenterSelected = (mDragOp == DO_CENTER);
  mWidthSelected = (mDragOp == DO_WIDTH);
  mHeightSelected = (mDragOp == DO_HEIGHT);
  
  if (mDragOp != DO_NONE) {
    redraw();
  }
}

void SampleInteract::penUp(ofx::ImageEffect *,
                           double, double,
                           const ofx::RGBAColourD &, ofx::Time,
                           double, double,
                           double, double, double) throw(ofx::Exception) {
  mCenterSelected = false;
  mWidthSelected = false;
  mHeightSelected = false;
  if (mDragOp != DO_NONE) {
    redraw();
  }
  mDragOp = DO_NONE;
}

void SampleInteract::draw(ofx::ImageEffect *effect,
                          //int w,
                          //int h,
                          double pixelScaleX,
                          double pixelScaleY,
                          const ofx::RGBAColourD &,
                          ofx::Time t,
                          double,
                          double) throw(ofx::Exception)
{
  ofx::Double2Parameter pC = effect->parameters().getDouble2Param("center");
  ofx::DoubleParameter pW = effect->parameters().getDoubleParam("width");
  ofx::DoubleParameter pH = effect->parameters().getDoubleParam("height");
  
  double ecx, ecy;
  pC.getValueAtTime(t, ecx, ecy);
  double ew = 0.5 * pW.getValueAtTime(t);
  double eh = 0.5 * pH.getValueAtTime(t);
  
  double wext, hext;
  effect->projectExtent(wext, hext);
  
  double xoff, yoff;
  effect->projectOffset(xoff, yoff);
  
  //double par = effect->projectPixelAspectRatio();
  
  double cecx, cecy, cew, ceh;
  ofx::NormalisedToCanonicalCoords(ecx, ecy, wext, hext, xoff, yoff, true, cecx, cecy);
  ofx::NormalisedToCanonicalCoords(ew, eh, wext, hext, 0, 0, false, cew, ceh);

  double bw = 2.0 * pixelScaleX;
  double bh = 2.0 * pixelScaleY;
  
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
  
}

// ---

SampleDescriptor::SampleDescriptor(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl) throw(ofx::Exception)
  : ofx::ImageEffectDescriptor(h, hdl) {
}

SampleDescriptor::~SampleDescriptor() {
}

void SampleDescriptor::describe() throw(ofx::Exception) {
  setMultipleClipDepthsSupport(false);
  setSupportedPixelDepth(0, ofx::BitDepthByte);
  setSupportedContext(0, ofx::ImageEffectContextFilter);
  setGrouping("gatgui");
  setLabel("sample");
  if (host()->supportsOverlays()) {
    setOverlayInteract(ofx::InteractEntryPoint<SamplePlugin, SampleInteractDescriptor, SampleInteract>);
  }
}

void SampleDescriptor::describeInContext(ofx::ImageEffectContext) throw(ofx::Exception) {
  
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
}

// ---

SampleEffect::SampleEffect(ofx::ImageEffectHost *h, OfxImageEffectHandle hdl) throw(ofx::Exception)
  : ofx::ImageEffect(h, hdl) {
}

SampleEffect::~SampleEffect() {
}

double SampleEffect::normalisedDistanceToEllipseCenter(double x, double y, double w, double h, double px, double py) {
  double dx = (px - x) / w;
  double dy = (py - y) / h;
  return (dx*dx + dy*dy);
}

bool SampleEffect::isIdentity(ofx::Time t,
                              ofx::ImageField,
                              const ofx::Rect<int> &,
                              double,
                              double,
                              std::string &idClip,
                              ofx::Time &idTime) throw(ofx::Exception)
{
  ofx::DoubleParameter w = parameters().getDoubleParam("width");
  ofx::DoubleParameter h = parameters().getDoubleParam("height");
  if (w.getValue() <= 0.0 || h.getValue() <= 0.0) {
    idClip = "Source";
    idTime = t;
    return true;
  } else {
    return false;
  }
}

/*
ofx::RectD SampleEffect::getRegionOfDefinition(ofx::Time t,
                                               double renderScaleX,
                                               double renderScaleY) throw(ofx::Exception)
{
  ofx::Rect<double> RoD;
  // -> check center, width, and height
  // -> also apply renderScaleX and renderScaleY
  // -> return in Canonical Coords
  
  //void projectSize(double &w, double &h) throw(Exception);
  //void projectOffset(double &x, double &y) throw(Exception);
  //void projectExtent(double &w, double &h) throw(Exception);
  //double projectPixelAspectRatio() throw(Exception);
  
  return RoD;
}

void SampleEffect::getRegionsOfInterest(ofx::Time t,
                                        double renderScaleX,
                                        double renderScaleY,
                                        const ofx::Rect<double> &outRoI,
                                        std::map<std::string, ofx::Rect<double> > &inClipsRoI) throw(Exception)
{
}
*/

void SampleEffect::render(ofx::Time t,
                          ofx::ImageField field,
                          const ofx::Rect<int> &renderWindow,
                          double &renderScaleX,
                          double renderScaleY) throw(ofx::Exception)
{
  // renderWindow is in pixels, not canonical coords
  
  ofx::Clip cSrc = getClip("Source");
  ofx::Clip cOut = getClip("Output");
  
  ofx::Image iSrc = cSrc.getImage(t);
  ofx::Image iOut = cOut.getImage(t);
  
  ofx::RGBAColourB *srcPix, *dstPix;
  
  ofx::Double2Parameter pCenter = parameters().getDouble2Param("center");
  ofx::DoubleParameter pWidth = parameters().getDoubleParam("width");
  ofx::DoubleParameter pHeight = parameters().getDoubleParam("height");
  ofx::BooleanParameter pInvert = parameters().getBooleanParam("invert");
  
  double nx, ny;
  pCenter.getValueAtTime(t, nx, ny);
  
  double w = pWidth.getValueAtTime(t);
  double h = pHeight.getValueAtTime(t);
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
    for (int y=renderWindow.y1; y<renderWindow.y2; ++y) {
      if (abort()) {
        break;
      }
      if (!iOut.pixelAddress(renderWindow.x1, y, dstPix)) {
        continue;
      }
      for (int x=renderWindow.x1; x<renderWindow.x2; ++x) {
        PixelToCanonicalCoords(x, y, par, renderScaleX, renderScaleY, field, pcx, pcy);
        double d = normalisedDistanceToEllipseCenter(cx, cy, cw, ch, pcx, pcy);
        if (d <= 1.0) {
          if (!iSrc.pixelAddress(x, y, srcPix)) {
            dstPix->r = 0;
            dstPix->g = 0;
            dstPix->b = 0;
            dstPix->a = 255;
          } else {
            double tmp;
            double falloff = d * d;
            tmp = double(srcPix->r) / 255.0;
            tmp *= falloff;
            dstPix->r = (unsigned char) (255 * CLAMP(tmp, 0, 1));
            tmp = double(srcPix->g) / 255.0;
            tmp *= falloff;
            dstPix->g = (unsigned char) (255 * CLAMP(tmp, 0, 1));
            tmp = double(srcPix->b) / 255.0;
            tmp *= falloff;
            dstPix->b = (unsigned char) (255 * CLAMP(tmp, 0, 1));
            dstPix->a = srcPix->a;
          }
        } else {
          if (!iSrc.pixelAddress(x, y, srcPix)) {
            dstPix->r = 0;
            dstPix->g = 0;
            dstPix->b = 0;
            dstPix->a = 255;
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
    for (int y=renderWindow.y1; y<renderWindow.y2; ++y) {
      if (abort()) {
        break;
      }
      if (!iOut.pixelAddress(renderWindow.x1, y, dstPix)) {
        continue;
      }
      for (int x=renderWindow.x1; x<renderWindow.x2; ++x) {
        PixelToCanonicalCoords(x, y, par, renderScaleX, renderScaleY, field, pcx, pcy);
        double d = normalisedDistanceToEllipseCenter(cx, cy, cw, ch, pcx, pcy);
        if (d <= 1.0) {
          if (!iSrc.pixelAddress(x, y, srcPix)) {
            dstPix->r = 0;
            dstPix->g = 0;
            dstPix->b = 0;
            dstPix->a = 255;
          } else {
            double tmp;
            double falloff = (1.0 - d * d);
            tmp = double(srcPix->r) / 255.0;
            tmp *= falloff;
            dstPix->r = (unsigned char) (255 * CLAMP(tmp, 0, 1));
            tmp = double(srcPix->g) / 255.0;
            tmp *= falloff;
            dstPix->g = (unsigned char) (255 * CLAMP(tmp, 0, 1));
            tmp = double(srcPix->b) / 255.0;
            tmp *= falloff;
            dstPix->b = (unsigned char) (255 * CLAMP(tmp, 0, 1));
            dstPix->a = srcPix->a;
          }
        } else {
          dstPix->r = 0;
          dstPix->g = 0;
          dstPix->b = 0;
          if (!iSrc.pixelAddress(x, y, srcPix)) {
            dstPix->a = 255;
          } else {
            dstPix->a = srcPix->a;
          }
        }
        dstPix++;
      }
    }
  }
  
  if (abort()) {
    throw ofx::Exception(kOfxStatFailed, "InverEffect::render aborted");
  }
}

// ---

SamplePlugin::SamplePlugin()
  : ofx::ImageEffectPlugin<SampleDescriptor, SampleEffect>() {
  setMajorVersion(0);
  setMinorVersion(0);
  setID("gatgui.filter.sample");
}

SamplePlugin::~SamplePlugin() {
}

// ---

OfxExport int OfxGetNumberOfPlugins(void) {
  return 1;
}

OfxExport OfxPlugin* OfxGetPlugin(int i) {
  if (i == 0) {
    SamplePlugin *p = new SamplePlugin();
    return p->description();
  }
  return NULL;
}

