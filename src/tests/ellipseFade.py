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

import ofx


try:
  from OpenGL.GL import *
  
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
      self.dragOp = Interact.DO_NONE
      self.widthSelected = False
      self.heightSelected = False
      self.centerSelected = False
      self.lastX = -1
      self.lastY = -1
      self.hostApp = Interact.HA_GENERIC
      if host.name == "uk.co.thefoundry.nuke":
        self.hostApp = Interact.HA_NUKE
      elif host.name == "Ramen":
        self.hostApp = Interact.HA_RAMEN
      elif host.name == "Autodesk Toxik":
        self.hostApp = Interact.HA_TOXIK
      elif host.name == "com.eyeonline.Fusion":
        self.hostApp = Interact.HA_FUSION
      self.slaveToParam(0, "center")
      self.slaveToParam(1, "width")
      self.slaveToParam(2, "height")
    
    def draw(self, args):
      ecx, ecy = args.effect.center.getValueAtTime(args.time)
      ew = 0.5 * args.effect.width.getValueAtTime(args.time)
      eh = 0.5 * args.effect.height.getValueAtTime(args.time)
      
      xoff, yoff = args.effect.projectOffset
      wext, hext = args.effect.projectExtent
      
      cecx, cecy = ofx.NormalisedToCanonicalCoords(ecx, ecy, wext, hext, xoff, yoff, True)
      cew, ceh = ofx.NormalisedToCanonicalCoords(ew, eh, wext, hext, 0, 0, False)
      
      pw = args.pixelScaleX
      ph = args.pixelScaleY
      
      if self.hostApp == Interact.HA_NUKE:
        pw /= args.renderScaleX
        ph /= args.renderScaleY
      
      bw = 2.0 * pw
      bh = 2.0 * ph
      
      # Center manipulator
      if self.centerSelected:
        glColor3d(1.0, 0.0, 0.0)
      else:
        glColor3d(0.0, 1.0, 0.0)
      glBegin(GL_QUADS)
      glVertex2d(cecx-bw, cecy-bh)
      glVertex2d(cecx+bw, cecy-bh)
      glVertex2d(cecx+bw, cecy+bh)
      glVertex2d(cecx-bw, cecy+bh)
      glEnd()
      
      # Width manipulator
      if self.widthSelected:
        glColor3d(1.0, 0.0, 0.0)
      else:
        glColor3d(0.0, 1.0, 0.0)
      glBegin(GL_QUADS)
      glVertex2d(cecx+cew-bw, cecy-bh)
      glVertex2d(cecx+cew+bw, cecy-bh)
      glVertex2d(cecx+cew+bw, cecy+bh)
      glVertex2d(cecx+cew-bw, cecy+bh)
      glEnd()
      glBegin(GL_LINES)
      glVertex2d(cecx+bw, cecy)
      glVertex2d(cecx+cew-bw, cecy)
      glEnd()
      
      # Height manipulator
      if self.heightSelected:
        glColor3d(1.0, 0.0, 0.0)
      else:
        glColor3d(0.0, 1.0, 0.0)
      glBegin(GL_QUADS)
      glVertex2d(cecx-bw, cecy+ceh-bh)
      glVertex2d(cecx+bw, cecy+ceh-bh)
      glVertex2d(cecx+bw, cecy+ceh+bh)
      glVertex2d(cecx-bw, cecy+ceh+bh)
      glEnd()
      glBegin(GL_LINES)
      glVertex2d(cecx, cecy+bh)
      glVertex2d(cecx, cecy+ceh-bh)
      glEnd()
      
      return ofx.StatOK
    
    def penMotion(self, args):
      if self.dragOp == Interact.DO_NONE:
        return ofx.StatReplyDefault
      
      ecx, ecy = args.effect.center.getValueAtTime(args.time)
      ew = 0.5 * args.effect.width.getValueAtTime(args.time)
      eh = 0.5 * args.effect.height.getValueAtTime(args.time)
      
      xoff, yoff = args.effect.projectOffset
      wext, hext = args.effect.projectExtent
      
      cecx, cecy = ofx.NormalisedToCanonicalCoords(ecx, ecy, wext, hext, xoff, yoff, True)
      cew, ceh = ofx.NormalisedToCanonicalCoords(ew, eh, wext, hext, 0, 0, False)
      
      if self.dragOp == Interact.DO_CENTER:
        dx = args.x - self.lastX
        dy = args.y - self.lastY
        cecx += dx
        cecy += dy
        ecx, ecy = ofx.CanonicalToNormalisedCoords(cecx, cecy, wext, hext, xoff, yoff, True)
        if args.effect.center.autoKeying:
          args.effect.center.setValueAtTime(args.time, (ecx, ecy))
        else:
          args.effect.center.setValue((ecx, ecy))
      
      elif self.dragOp == Interact.DO_WIDTH:
        dx = args.x - self.lastX
        cew += dx
        ew, eh = ofx.CanonicalToNormalisedCoords(cew, ceh, wext, hext, 0, 0, False)
        ew *= 2.0
        if args.effect.width.autoKeying:
          args.effect.width.setValueAtTime(args.time, ew)
        else:
          args.effect.width.setValue(ew)
        
      elif self.dragOp == Interact.DO_HEIGHT:
        dy = args.y - self.lastY
        ceh += dy
        ew, eh = ofx.CanonicalToNormalisedCoords(cew, ceh, wext, hext, 0, 0, False)
        eh *= 2.0
        if args.effect.height.autoKeying:
          args.effect.height.setValueAtTime(args.time, eh)
        else:
          args.effect.height.setValue(eh)
        
      self.lastX = args.x
      self.lastY = args.y
      
      self.redraw()
      
      return ofx.StatOK
    
    def penDown(self, args):
      ecx, ecy = args.effect.center.getValueAtTime(args.time)
      ew = 0.5 * args.effect.width.getValueAtTime(args.time)
      eh = 0.5 * args.effect.height.getValueAtTime(args.time)
      
      xoff, yoff = args.effect.projectOffset
      wext, hext = args.effect.projectExtent
      
      cecx, cecy = ofx.NormalisedToCanonicalCoords(ecx, ecy, wext, hext, xoff, yoff, True)
      cew, ceh = ofx.NormalisedToCanonicalCoords(ew, eh, wext, hext, 0, 0, False)
      
      bw = 4.0 * args.pixelScaleX
      bh = 4.0 * args.pixelScaleY
      
      if self.hostApp == Interact.HA_NUKE:
        bw /= args.renderScaleX
        bh /= args.renderScaleY
      
      if args.x >= cecx-bw and args.x <= cecx+bw:
        if args.y >= cecy-bh and args.y <= cecy+bh:
          self.dragOp = Interact.DO_CENTER
        elif args.y >= cecy+ceh-bh and args.y <= cecy+ceh+bh:
          self.dragOp = Interact.DO_HEIGHT
      elif args.x >= cecx+cew-bw and args.x <= cecx+cew+bw and args.y >= cecy-bh and args.y <= cecy+bh:
        self.dragOp = Interact.DO_WIDTH
      
      self.lastX = args.x
      self.lastY = args.y
      
      self.centerSelected = (self.dragOp == Interact.DO_CENTER)
      self.widthSelected = (self.dragOp == Interact.DO_WIDTH)
      self.heightSelected = (self.dragOp == Interact.DO_HEIGHT)
      
      if self.dragOp != Interact.DO_NONE:
        self.redraw()
      
      return ofx.StatOK
    
    def penUp(self, args):
      self.centerSelected = False
      self.widthSelected = False
      self.heightSelected = False
      
      doRedraw = (self.dragOp != Interact.DO_NONE)
      self.dragOp = Interact.DO_NONE
      if doRedraw:
        self.redraw()
      
      return ofx.StatOK
    
  
except Exception, e:
  # Could no import OpenGL module
  ofx.Log("pyEllipseFade: Could not load PyOpenGL module. There will be no overlay interact.")
  ofx.Log("%s" % e)
  Interact = None




class Descriptor(ofx.ImageEffectDescriptor):
  
  def __init__(self, host, handle):
    ofx.ImageEffectDescriptor.__init__(self, host, handle)
  
  def describe(self):
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
    if Interact != None and self.host.supportsOverlays:
      self.overlayInteract = (ofx.InteractDescriptor, Interact)
    return ofx.StatOK;
  
  def describeInContext(self, ctx):
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
    if self.width.getValueAtTime(args.time) <= 0.0 or \
       self.height.getValueAtTime(args.time) <= 0.0:
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
    
    if self.invert.getValue():
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

