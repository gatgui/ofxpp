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

#ifndef __ofx_parameter_parametric_h__
#define __ofx_parameter_parametric_h__

#include <ofx/parameter.h>

#ifdef OFX_API_1_2

#include <ofxParametricParam.h>

namespace ofx {
  
  class ParametricParameterDescriptor : public ValueParameterDescriptor {
    public:
      
      ParametricParameterDescriptor();
      ParametricParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      ParametricParameterDescriptor(const ParametricParameterDescriptor &rhs);
      virtual ~ParametricParameterDescriptor();
      
      ParametricParameterDescriptor& operator=(const ParametricParameterDescriptor &rhs);
      
      // properties
      
      int dimension();
      void dimension(int n);
      
      RGBAColour<double> UIColour(int d);
      void UIColour(int d, const RGBAColour<double> &c);
      
      EntryPoint interactBackground();
      void interactBackground(EntryPoint ep);
      
      void range(double *pmin, double *pmax);
      void range(double pmin, double pmax);
      
      std::string dimensionLabel(int d);
      void dimensionLabel(int d, const std::string &l);
      
      /*
      // Parametric parameters are numeric
      kOfxParamPropMin
      kOfxParamPropMax
      kOfxParamPropDisplayMin
      kOfxParamPropDisplayMax
      
      // Parametric parameters are double
      kOfxParamPropIncrement
      kOfxParamPropDigits
      kOfxParamPropDoubleType
      kOfxParamPropDefaultCoordinateSystem (doubleType == non-normalised coordinate)
      
      // Parametric parameters can have 1 or more dimensions
      kOfxParamPropShowTimeMarker (if dim == 1 and doubleType == absoluteTime)
      x kOfxParamPropDimensionLabel (if dim >= 2)
      */
  };
  
  class ParametricParameter : public ValueParameter {
    protected:
      
      OfxParametricParameterSuiteV1 *mParametricSuite;
      
    public:
      
      ParametricParameter();
      ParametricParameter(Host *h, OfxParamHandle hdl);
      ParametricParameter(const ParametricParameter &rhs);
      virtual ~ParametricParameter();
      
      ParametricParameter& operator=(const ParametricParameter &rhs);
      
      // properties
      
      int dimension();
      
      RGBAColour<double> UIColour(int d);
      
      EntryPoint interactBackground();
      
      void range(double *pmin, double *pmax);
      
      std::string dimensionLabel(int d);
      
      // suite
      
      int getControlPointsCount(int curveIndex, Time t);
      
      void getControlPoint(int curveIndex, Time t, int ctrlIdx, double *pos, double *val);
      
      void setControlPoint(int curveIndex, Time t, int ctrlIdx, double pos, double val, bool addKey);
      
      void addControlPoint(int curveIndex, Time t, double pos, double val, bool addKey);
      
      void deleteControlPoint(int curveIndex, int ctrlIdx);
      
      void deleteAllControlPoints(int curveIndex);
      
      double eval(int curveIndex, Time t, double pos);
  };
  
}


#endif

#endif
