# Copyright (C) 2010  Gaetan Guidet
# 
# This file is part of ofxpp.
# 
# ofxpp is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 2.1 of the License, or (at
# your option) any later version.
# 
# ofxpp is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
# USA.

import PyOpenGL
import ofx

class Interact(ofx.Interact):
  
  # Host application
  HA_GENERIC = 0
  HA_NUKE = 1
  HA_RAMEN = 2
  HA_FUSION = 3
  HA_TOXIK = 4
  
  # Drag target
  DO_NONE = 0
  DO_CENTER = 1
  DO_WIDTH = 2
  DO_HEIGHT = 3
  
  def __init__(self, host):
    ofx.Interact.__init__(self, host)
    self.dragOp = DO_NONE
    self.widthSelected = False
    self.heightSelected = False
    self.centerSelected = False
    self.lastX = -1
    self.lastY = -1
    self.hostApp = HA_GENERIC
    if self.host.name == "uk.co.thefoundry.nuke":
      self.hostApp = HA_NUKE
    elif self.host.name == "Ramen":
      self.hostApp = HA_RAMEN
    elif self.host.name == "Autodesk Toxik":
      self.hostApp = HA_TOXIK
    elif self.host.name == "com.eyeonline.Fusion":
      self.hostApp = HA_FUSION
    self.setSlaveParam(0, "center")
    self.setSlaveParam(1, "width")
    self.setSlaveParam(2, "height")
  
  def draw(self, args):
    pass
  
  def penMotion(self, args):
    pC = None #((EllipseFadeEffect*) args.effect)->pCenter;
    pW = None #((EllipseFadeEffect*) args.effect)->pWidth;
    pH = None #((EllipseFadeEffect*) args.effect)->pHeight;
    # args.effect.parameters.getDouble2Param("center")... No
    # should be able to access python object members: args.effect.center
    
  def penDown(self, args):
    pass
  
  def penUp(self, args):
    pass
  


class Descriptor(ofx.ImageEffectDescriptor):
  
  def __init__(self, host, hdl):
    ofx.ImageEffectDescriptor.__init__(self, host, hdl)
    
  def describe(self):
    self.label = "ellipseFade"
    self.shortLabel = "ellipseFade"
    self.longLabel = "ellipseFade"
    self.group = "gatgui"
    self.singleInstance = False
    # Do not leave frame threading to hist
    self.hostFrameThreading = False
    # Python plugin are not even instance safe
    self.renderThreadSafety = ofx.RenderThreadUnsafe
    self.setSupportedPixelDepth(0, ofx.BitDepthFloat)
    self.setSupportedContext(0, ofx.ImageEffectContextFilter)
    self.temporalClipAccess = False
    self.tilesSupport = True
    self.alwaysRenderFieldTwice = True
    self.multipleClipDepthsSupport = False
    self.multipleClipPARsSupport = False
    self.multiResolutionSupport = False
    if self.host.supportOverlays:
      self.setOverlayInteract(Plugin, ofx.InteractDescriptor, Interact)
    return ofx.StatOK;
  
  def describeInContext(self, ctx):
    
    clip = self.defineClip("Output");
    clip.setSupportedComponent(0, ofx.ImageComponentRGBA)
    
    clip = self.defineClip("Source");
    clip.setSupportedComponent(0, ofx.ImageComponentRGBA)
    
    c = self.parameters.defineDouble2Param("center");
    c.default = (0.5, 0.5)
    c.min = (0, 0)
    c.max = (1, 1)
    c.digits = 3
    c.setDimensionLabel(0, "X")
    c.setDimensionLabel(1, "Y")
    c.persistant = True
    c.animateable = True
    c.doubleType = ofx.DoubleParamNormalisedXY
    
    w = self.parameters.defineDoubleParam("width");
    w.default = 0.5
    w.min = 0.0
    w.max = 1.0
    w.increment = 0.001
    w.digits = 3
    w.persistant = True
    w.animateable = True
    w.doubleType = ofx.DoubleParamNormalisedX
    
    h = self.parameters.defineDoubleParam("height");
    h.default = 0.5
    h.min = 0.0
    h.max = 1.0
    h.increment = 0.001
    h.digits = 3
    h.persistant = True
    h.animateable = True
    h.doubleType = ofx.DoubleParamNormalisedY
    
    i = self.parameters.defineBooleanParam("invert");
    i.default = False
    i.persistant = True
    i.animateable = False
    
    return ofx.StatOK
  


class Effect(ofx.ImageEffect):
  
  def __init__(self, host, hdl):
    ofx.ImageEffect.__init__(self, host, hdl)
    self.center = self.parameters.getDouble2Param("center")
    self.width = self.parameters.getDoubleParam("width")
    self.height = self.parameters.getDoubleParam("height")
    self.invert = self.parameters.getBooleanParam("invert")
  
  def normalisedDistanceToEllipseCenter(self, x, y, w, h, px, py):
    dx = (px - x) / w;
    dy = (py - y) / h;
    return (dx*dx + dy*dy);
    
  def isIdentity(self, args):
    if self.width.value <= 0.0 or self.height.value <= 0.0:
      args.idClip = "Source"
      args.idTime = args.time
      return ofx.StatOK
    else:
      return ofx.StatReplyDefault
  
  def render(self, args):
    # Note: args.renderWindow is in pixels, not canonical coords
    cSrc = self.getClip("Source")
    cOut = self.getClip("Output")
    
    iSrc = cSrc.getImage(args.time)
    iOut = cOut.getImage(args.time)
    
    srcPix = None
    dstPix = None
    
    nx, ny = self.center.getValueAtTime(args.time)
    w = self.width.getValueAtTime(args.time)
    h = self.height.getValueAtTime(args.time)
    
    xoff, yoff = self.projectOffset
    wext, hext = self.projectExtent
    par = self.projectPixelAspectRatio
    
    cx, cy = ofx.NormalisedToCanonicalCoords((nx, ny), (wext, hext), (xoff, yoff), True)
    cw, ch = ofx.NormalisedToCanonicalCoords((w*0.5, h*0.5), (wext, hext), (0, 0), False)
    
    if self.invert.value:
      for y in xrange(args.renderWindow.y1, args.renderWindow.y2):
        if self.abort():
          break
        dstPix = iOut.getPixelAddress(args.renderWindow.x1, y)
        if not dstPix:
          continue
        for x in xrange(args.renderWindow.x1, args.renderWindow.x2):
          pcx, pcy = ofx.PixelToCanonicalCoords(x, y, par, args.renderScaleX, args.renderScaleY, args.field)
          srcPix = iSrc.getPixelAddress(x, y)
          if not srcPix:
            dstPix.set(0, 0, 0, 1)
          else:
            d = self.normalisedDistanceToEllipseCenter(cx, cy, cw, ch, pcx, pcy)
            if d <= 1.0:
              falloff = d * d
              dstPix.set(falloff*srcPix.r, falloff*srcPix.g, falloff*srcPix.b, srcPix.a)
            else:
              dstPix = srcPix
          dstPix.next()
    else:
      for y in xrange(args.renderWindow.y1, args.renderWindow.y2):
        if self.abort():
          break
        dstPix = iOut.getPixelAddress(args.renderWindow.x1, y)
        if not dstPix:
          continue
        for x in xrange(args.renderWindow.x1, args.renderWindow.x2):
          pcx, pcy = ofx.PixelToCanonicalCoords(x, y, par, args.renderScaleX, args.renderScaleY, args.field)
          srcPix = iSrc.getPixelAddress(x, y)
          if not srcPix:
            dstPix.set(0, 0, 0, 1)
          else:
            d = self.normalisedDistanceToEllipseCenter(cx, cy, cw, ch, pcx, pcy)
            if d <= 1.0:
              falloff = 1.0 - d * d
              dstPix.set(falloff*srcPix.r, falloff*srcPix.g, falloff*srcPix.b, srcPix.a)
            else:
              dstPix.set(0, 0, 0, srcPix.a)
          dstPix.next()
    
    iSrc.release()
    iOut.release()
    
    return (ofx.StatFailed if self.abort() else ofx.StatOK)
  


# in C++
#class Plugin : public ofx::ImageEffectPlugin<Descriptor, Effect> {
#  public:
#    Plugin();
#    virtual ~Plugin();
#};
class Plugin(ofx.ImageEffectPlugin):
  def __init__(self):
    ofx.ImageEffectPlugin.__init__(Descriptor, Effect)
    self.majorVersion = 1
    self.minorVersion = 0
    self.id = "gatgui.filter.pyEllipseFade";


# The entry points PythonOfxLoader will look for

def GetNumberOfPlugins():
  return 1

def GetPlugin(i):
  if i == 0:
    return Plugin()
  else:
    return None

