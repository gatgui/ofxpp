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

#from PyOpenGL import *
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
  
  def __init__(self, host, handle):
    ofx.Interact.__init__(self, host, handle)
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
    self.slaveToParam(0, "center")
    self.slaveToParam(1, "width")
    self.slaveToParam(2, "height")
  
  def draw(self, args):
    # TODO
    pass
  
  def penMotion(self, args):
    # TODO
    pass
  
  def penDown(self, args):
    # TODO
    pass
  
  def penUp(self, args):
    # TODO
    pass
  


class Descriptor(ofx.ImageEffectDescriptor):
  
  def __init__(self, host, handle):
    ofx.ImageEffectDescriptor.__init__(self, host, handle)
  
  def describe(self):
    ofx.Log("ellipseFade.Descriptor.describe")
    self.label = "pyEllipseFade"
    self.shortLabel = "pyEllipseFade"
    self.longLabel = "pyEllipseFade"
    self.group = "gatgui"
    self.singleInstance = False
    self.supportedPixelDepth(0, ofx.BitDepthFloat)
    self.supportedContext(0, ofx.ImageEffectContextFilter)
    self.temporalClipAccess = False
    self.supportsTiles = True
    self.fieldRenderTwiceAlways = True
    self.supportsMultipleClipDepths = False
    self.supportsMultipleClipPARs = False
    self.supportsMultiResolution = False
    #if self.host.supportsOverlays:
    #  self.overlayInteract = (ofx.InteractDescriptor, Interact)
    return ofx.StatOK;
  
  def describeInContext(self, ctx):
    ofx.Log("ellipseFade.Descriptor.describeInContext")
    clip = self.defineClip("Output");
    clip.supportedComponent(0, ofx.ImageComponentRGBA)
    
    clip = self.defineClip("Source");
    clip.supportedComponent(0, ofx.ImageComponentRGBA)
    
    c = self.parameters.defineDouble2Param("center");
    c.defaultValue = (0.5, 0.5)
    c.min = (0, 0)
    c.max = (1, 1)
    c.digits = 3
    c.dimensionLabel(0, "X")
    c.dimensionLabel(1, "Y")
    c.persistant = True
    c.animates = True
    c.doubleType = ofx.DoubleParamNormalisedXY
    
    w = self.parameters.defineDoubleParam("width");
    w.defaultValue = 0.5
    w.min = 0.0
    w.max = 1.0
    w.increment = 0.001
    w.digits = 3
    w.persistant = True
    w.animates = True
    w.doubleType = ofx.DoubleParamNormalisedX
    
    h = self.parameters.defineDoubleParam("height");
    h.defaultValue = 0.5
    h.min = 0.0
    h.max = 1.0
    h.increment = 0.001
    h.digits = 3
    h.persistant = True
    h.animates = True
    h.doubleType = ofx.DoubleParamNormalisedY
    
    i = self.parameters.defineBooleanParam("invert");
    i.defaultValue = False
    i.persistant = True
    i.animates = False
    
    return ofx.StatOK
  


class Effect(ofx.ImageEffect):
  
  def __init__(self, host, handle):
    ofx.ImageEffect.__init__(self, host, handle)
    self.center = self.parameters.getDouble2Param("center")
    self.width = self.parameters.getDoubleParam("width")
    self.height = self.parameters.getDoubleParam("height")
    self.invert = self.parameters.getBooleanParam("invert")
  
  def normalisedDistanceToEllipseCenter(self, x, y, w, h, px, py):
    dx = (px - x) / w;
    dy = (py - y) / h;
    return (dx*dx + dy*dy);
    
  def isIdentity(self, args):
    if self.width.getValue() <= 0.0 or self.height.getValue() <= 0.0:
      args.idClip = "Source"
      args.idTime = args.time
      return ofx.StatOK
    else:
      return ofx.StatReplyDefault
  
  def render(self, args):
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
    
    cx, cy = ofx.NormalisedToCanonicalCoords(nx, ny, wext, hext, xoff, yoff, True)
    cw, ch = ofx.NormalisedToCanonicalCoords(w*0.5, h*0.5, wext, hext, 0, 0, False)
    
    if self.invert.value:
      for y in xrange(args.renderWindow.y1, args.renderWindow.y2):
        if self.abort():
          break
        dstPix = iOut.pixelAddress(args.renderWindow.x1, y)
        if not dstPix:
          continue
        for x in xrange(args.renderWindow.x1, args.renderWindow.x2):
          pcx, pcy = ofx.PixelToCanonicalCoords(x, y, par, args.renderScaleX, args.renderScaleY, args.field)
          srcPix = iSrc.pixelAddress(x, y)
          if not srcPix:
            dstPix.r = 0
            dstPix.g = 0
            dstPix.b = 0
            dstPix.a = 1
          else:
            d = self.normalisedDistanceToEllipseCenter(cx, cy, cw, ch, pcx, pcy)
            if d <= 1.0:
              falloff = d * d
              dstPix.r = falloff * srcPix.r
              dstPix.g = falloff * srcPix.g
              dstPix.b = falloff * srcPix.b
              dstPix.a = srcPix.a
            else:
              dstPix.r = srcPix.r
              dstPix.g = srcPix.g
              dstPix.b = srcPix.b
              dstPix.a = srcPix.a
          dstPix.next()
    else:
      for y in xrange(args.renderWindow.y1, args.renderWindow.y2):
        if self.abort():
          break
        dstPix = iOut.pixelAddress(args.renderWindow.x1, y)
        if not dstPix:
          continue
        for x in xrange(args.renderWindow.x1, args.renderWindow.x2):
          pcx, pcy = ofx.PixelToCanonicalCoords(x, y, par, args.renderScaleX, args.renderScaleY, args.field)
          srcPix = iSrc.pixelAddress(x, y)
          if not srcPix:
            dstPix.r = 0
            dstPix.g = 0
            dstPix.b = 0
            dstPix.a = 1
          else:
            d = self.normalisedDistanceToEllipseCenter(cx, cy, cw, ch, pcx, pcy)
            if d <= 1.0:
              falloff = 1.0 - d * d
              dstPix.r = falloff * srcPix.r
              dstPix.g = falloff * srcPix.g
              dstPix.b = falloff * srcPix.b
              dstPix.a = srcPix.a
            else:
              dstPix.r = 0
              dstPix.g = 0
              dstPix.b = 0
              dstPix.a = srcPix.a
          dstPix.next()
    
    iSrc.release()
    iOut.release()
    
    return (ofx.StatFailed if self.abort() else ofx.StatOK)
  


class Plugin(ofx.ImageEffectPlugin):
  def __init__(self):
    ofx.ImageEffectPlugin.__init__(self, Descriptor, Effect)
    self.majorVersion = 1
    self.minorVersion = 0
    self.identifier = "gatgui.filter.pyEllipseFade";


# The entry points PythonOfxLoader will look for

def OfxGetNumberOfPlugins():
  return 1

def OfxGetPlugin(i):
  if i == 0:
    return Plugin()
  else:
    return None

