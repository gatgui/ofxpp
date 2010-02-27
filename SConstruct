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

prjs = [
  { "name"    : "ofxpp",
    "type"    : "staticlib",
    "srcs"    : glob.glob("src/lib/*.cpp"),
    "install" : {"include/ofx": glob.glob("include/ofx/*.h"),
                 "include"    : glob.glob("include/*.h")}
  },
  { "name"    : "sample",
    "type"    : "dynamicmodule",
    "ext"     : ".ofx",
    "srcs"    : glob.glob("src/tests/sample.cpp"),
    "libs"    : ["ofxpp"],
    "custom"  : [gl.Require],
    "post"    : openfx.MakeBundle
  }
]

env = excons.MakeBaseEnv()
excons.DeclareTargets(env, prjs)
