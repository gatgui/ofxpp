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


import os
import glob
import excons
import excons.tools
from excons.tools import gl
from excons.tools import openfx

ofxVersion = ARGUMENTS.get("ofxVersion", "1.1")
ofxNewMacPackaging = (int(ARGUMENTS.get("ofxNewMacPackaging", "0")) != 0)

defines = []
if int(ARGUMENTS.get("forceOverlayRedraw", "1")) == 1:
  defines.append("FORCE_OVERLAY_REDRAW")

# Add openfx version define

prjs = [
  { "name"    : "ofxpp",
    "type"    : "staticlib",
    "srcs"    : glob.glob("src/lib/*.cpp") + glob.glob("src/lib/parameter/*.cpp"),
    "install" : {"include"               : glob.glob("include/%s/*.h" % ofxVersion),
                 "include/ofx"           : glob.glob("include/ofx/*.h"),
                 "include/ofx/parameter" : glob.glob("include/ofx/parameter/*.h")}
  },
  { "name"    : "ellipseFade",
    "type"    : "dynamicmodule",
    "ext"     : ".ofx",
    "defs"    : defines,
    "srcs"    : glob.glob("src/tests/ellipseFade.cpp"),
    "libs"    : ["ofxpp"],
    "custom"  : [gl.Require],
    "post"    : openfx.MakeBundle
  },
  { "name"    : "multiBlur",
    "type"    : "dynamicmodule",
    "ext"     : ".ofx",
    "defs"    : defines,
    "srcs"    : glob.glob("src/tests/blur.cpp"),
    "libs"    : ["ofxpp"],
    "custom"  : [gl.Require],
    "post"    : openfx.MakeBundle
  },
  { "name"    : "gaussianBlur",
    "type"    : "dynamicmodule",
    "ext"     : ".ofx",
    "defs"    : defines,
    "srcs"    : glob.glob("src/tests/gaussianBlur.cpp"),
    "post"    : openfx.MakeBundle
  }
]

env = excons.MakeBaseEnv()
if float(ofxVersion) >= 1.2 and ofxNewMacPackaging:
  env["OFX_VERSION"] = float(ofxVersion)
excons.DeclareTargets(env, prjs)
