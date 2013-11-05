# Example translator for official OpenFX 1.3 OpenGL sample

import ofx
import sys

try:
  import pygl
  from pygl import gl

  class Descriptor(ofx.ImageEffectDescriptor):
  
    def __init__(self, host, handle):
      ofx.ImageEffectDescriptor.__init__(self, host, handle)
    
    def describe(self):
      if not self.host.supportsOpenGLRender:
        return ofx.StatErrMissingHostFeature

      self.label = "pyOpenGL"
      self.shortLabel = "pyOpenGL"
      self.longLabel = "pyOpenGL"
      self.group = "gatgui"
      self.singleInstance = False
      self.fieldRenderTwiceAlways = False
      self.supportsMultipleClipDepths = True
      self.supportedPixelDepth(0, ofx.BitDepthByte)
      self.supportedPixelDepth(1, ofx.BitDepthShort)
      self.supportedPixelDepth(2, ofx.BitDepthFloat)
      self.supportedContext(0, ofx.ImageEffectContextFilter)
      self.supportedContext(1, ofx.ImageEffectContextGeneral)

      self.needsOpenGLRender = True
      self.openGLPixelDepth(0, ofx.BitDepthByte)
      self.openGLPixelDepth(1, ofx.BitDepthShort)
      self.openGLPixelDepth(2, ofx.BitDepthFloat)
      
      return ofx.StatOK;
    
    def describeInContext(self, ctx):
      #isGeneralContext = (ctx == ofx.ImageEffectContextGeneral)

      clip = self.defineClip("Output");
      clip.supportedComponent(0, ofx.ImageComponentRGBA)
      clip.supportedComponent(1, ofx.ImageComponentAlpha)
      
      clip = self.defineClip("Source");
      clip.supportedComponent(0, ofx.ImageComponentRGBA)
      clip.supportedComponent(1, ofx.ImageComponentAlpha)

      scale = self.parameters.defineDoubleParam("scale")
      scale.label = "scale"
      scale.defaultValue = 1.0
      scale.min = 0.0
      scale.displayMin = 0.0
      scale.increment = 0.01
      scale.scriptName = "scale"
      scale.hint = "Scales the red rect"

      source_scale = self.parameters.defineDoubleParam("source_scale")
      source_scale.label = "source_scale"
      source_scale.defaultValue = 1.0
      source_scale.min = 0.0
      source_scale.displayMin = 0.0
      source_scale.increment = 0.01
      source_scale.scriptName = "source_scale"
      source_scale.hint = "Scales the source image"

      page = self.parameters.definePageParam("Main")
      page.child(0, "scale")
      page.child(1, "source_scale")
      
      return ofx.StatOK

  class Effect(ofx.ImageEffect):
  
    def __init__(self, host, handle):
      ofx.ImageEffect.__init__(self, host, handle)
      self.isGeneral = (self.context() == ofx.ImageEffectContextGeneral)
      self.scale = self.parameters.getDoubleParam("scale")
      self.sourceScale = self.parameter.getDoubleParam("source_scale")
      self.sourceClip = self.getClip("Source")
      self.outputClip = self.getClip("Output")

    def getRegionOfDefinition(self, args):
      args.outRoD = self.sourceClip.getRegionOfDefinition(args.time)
      return ofx.StatOK

    def getRegionsOfInterest(self, args):
      args.outRoI = args.inRoIs["Source"]
      return ofx.StatOK

    def getTimeDomain(self, args):
      sourceRange = self.sourceClip.frameRange
      args.first = sourceRange.min
      args.last = sourceRange.max
      return ofx.StatOK

    def getClipPreferences(self, args):
      outpref = ofx.ClipPreferences()
      
      incomps = self.sourceClip.components
      if incomps == ofx.BitDepthByte or \
         incomps == ofx.BitDepthShort:
        outpref.components = incomps
      else:
        outpref.components = ofx.BitDepthFloat
      
      indepth = self.sourceClip.pixelDepth
      if indepth == ofx.ImageComponentAlpha:
        outpref.bitDepth = indepth
      else:
        outpref.bitDepth = ofx.ImageComponentRGBA

      args.prefs["Output"] = outpref

      return ofx.StatOK

    def isIdentity(self, args):
      return ofx.StatReplyDefault
    
    def render(self, args):
      if not args.glEnabled:
        return ofx.StatErrImageFormat

      #outImg = self.outputClip.loadTexture(args.time)
      srcImg = self.sourceClip.loadTexture(args.time)

      scale = self.scale.getValueAtTime(args.time)
      sourceScale = self.sourceScale.getValueAtTime(args.time)

      w = args.renderWindow.x2 - args.renderWindow.x1
      h = args.renderWindow.y2 - args.renderWindow.y1

      gl.PushAttrib(gl.ALL_ATTRIB_BITS)
      gl.Disable(gl.BLEND)

      # Draw a black quad first
      gl.Begin(gl.QUADS)
      gl.Color4f(0, 0, 0, 1)
      gl.Vertex2f(0, 0)
      gl.Vertex2f(0, h)
      gl.Vertex2f(w, h)
      gl.Vertex2f(w, 0)
      gl.End()

      gl.Enable(srcImg.target)
      gl.BindTexture(srcImg.target, srcImg.index)
      gl.TexParameteri(srcImg.target, gl.TEXTURE_WRAP_S, gl.REPEAT)
      gl.TexParameteri(srcImg.target, gl.TEXTURE_WRAP_T, gl.REPEAT)
      gl.TexParameteri(srcImg.target, gl.TEXTURE_MAG_FILTER, gl.LINEAR)
      gl.TexParameteri(srcImg.target, gl.TEXTURE_MIN_FILTER, gl.LINEAR)
      gl.TexEnvf(gl.TEXTURE_ENV, gl.TEXTURE_ENV_MODE, gl.MODULATE)

      tymin = 0
      tymax = 0

      # Draw the textured quad containing the source
      gl.Begin(gl.QUADS)
      gl.Color4f(1, 1, 1, 1)
      gl.TexCoord2f(0, tymin)
      gl.Vertex2f(0, 0)
      gl.TexCoord2f(1, tymin)
      gl.Vertex2f(w * sourceScale, 0)
      gl.TexCoord2f(1, tymax)
      gl.Vertex2f(w * sourceScale, h * sourceScale)
      gl.TexCoord2f(0, tymax)
      gl.Vertex2f(0, h * sourceScale)
      gl.End()

      gl.Disable(srcImg.target)

      # Draw some stuff on top of it to show we really did something
      width = 200
      height = 100

      gl.Begin(gl.QUADS)
      gl.Color3f(1, 0, 0)
      gl.Vertex2f(10, 10)
      gl.Vertex2f(10, height * scale)
      gl.Vertex2f(width * scale, height * scale)
      gl.Vertex2f(width * scale, 10)
      gl.End()

      gl.PopAttrib()

      #outImg.release()
      srcImg.release()

      return ofx.StatOK

  class Plugin(ofx.ImageEffectPlugin):
  
    Instance = None
  
    def __init__(self):
      ofx.ImageEffectPlugin.__init__(self, Descriptor, Effect)
      Plugin.Instance = self
      self.majorVersion = 1
      self.minorVersion = 0
      self.identifier = "gatgui.test.pyOpenGL";


  # The entry points pyplugin will look for

  def OfxGetNumberOfPlugins():
    return 1

  def OfxGetPlugin(i):
    if i == 0:
      return Plugin()
    else:
      return None

except Exception, e:
   ofx.Log("pyOpenGL: Could not load pygl module.")
   ofx.Log("%s" % e)
