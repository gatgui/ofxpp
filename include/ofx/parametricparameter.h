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

/** \file parametricparameter.h
 *  Parametric parameter descriptor and instance classes.
 */

#ifndef __ofx_parameter_parametric_h__
#define __ofx_parameter_parametric_h__

#include <ofx/parameter.h>

#ifdef OFX_API_1_2

#include <ofxParametricParam.h>

namespace ofx {
  
  /** Parametric parameter descriptor class.
   *  \note OpenFX version >= 1.2.
   */
  class ParametricParameterDescriptor : public ValueParameterDescriptor {
    public:
      
      ParametricParameterDescriptor();
      ParametricParameterDescriptor(Host *h, OfxPropertySetHandle hdl);
      ParametricParameterDescriptor(const ParametricParameterDescriptor &rhs);
      virtual ~ParametricParameterDescriptor();
      
      ParametricParameterDescriptor& operator=(const ParametricParameterDescriptor &rhs);
      
      // properties
      
      //! Get dimension count.
      int dimension();
      //! Set dimension count.
      void dimension(int n);
      
      //! Get dimension colour.
      RGBAColour<double> UIColour(int d);
      //! Set dimension colour.
      void UIColour(int d, const RGBAColour<double> &c);
      
      //! Get background interact entry point function.
      EntryPoint interactBackground();
      //! Set background interact entry point function.
      void interactBackground(EntryPoint ep);
      
      //! Get input value range.
      void range(double *pmin, double *pmax);
      //! Set input value range.
      void range(double pmin, double pmax);
      
      //! Get dimension label.
      std::string dimensionLabel(int d);
      //! Set dimension label.
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
  
  /** Parametric parameter instance class.
   *  \note OpenFX version >= 1.2.
   */
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
      
      //! Get dimensions count.
      int dimension();
      
      //! Get dimension colour.
      RGBAColour<double> UIColour(int d);
      
      //! Get background interact entry point function.
      EntryPoint interactBackground();
      
      //! Get input value range.
      void range(double *pmin, double *pmax);
      
      //! Get dimension label.
      std::string dimensionLabel(int d);
      
      // suite
      
      //! Get number of control points of a dimension.
      int getControlPointsCount(int curveIndex, Time t);
      
      //! Get control point value of a dimension..
      void getControlPoint(int curveIndex, Time t, int ctrlIdx, double *pos, double *val);
      
      //! Set control point value of a dimension.
      void setControlPoint(int curveIndex, Time t, int ctrlIdx, double pos, double val, bool addKey);
      
      //! Add a new control point value to a dimension.
      void addControlPoint(int curveIndex, Time t, double pos, double val, bool addKey);
      
      //! Delete control point of a dimension.
      void deleteControlPoint(int curveIndex, int ctrlIdx);
      
      //! Delete all control points of a dimension.
      void deleteAllControlPoints(int curveIndex);
      
      //! Eval a dimension.
      double eval(int curveIndex, Time t, double pos);
  };
  
}


#endif

#endif
