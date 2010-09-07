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
    protected:
      
      // Those 2 are required to set the default control points
      OfxParametricParameterSuiteV1 *mParametricSuite;
      OfxParamHandle mDescHandle;
    
    public:
      
      ParametricParameterDescriptor();
      ParametricParameterDescriptor(Host *h, OfxPropertySetHandle hdl, OfxParamHandle desc=NULL);
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
      
      //! Get position value range.
      void range(double *pmin, double *pmax);
      //! Set position value range.
      void range(double pmin, double pmax);
      
      //! Get dimension label.
      std::string dimensionLabel(int d);
      //! Set dimension label.
      void dimensionLabel(int d, const std::string &l);
      
      // suite
      
      //! Get number of default control points for a given dimension and time.
      int getControlPointsCount(int dim, Time t);
      
      //! Get default control point for a given dimension and time.
      void getControlPoint(int dim, Time t, int ctrlIdx, double *pos, double *val);
      
      //! Set default control point for a given dimension and time.
      void setControlPoint(int dim, Time t, int ctrlIdx, double pos, double val, bool addKey);
      
      //! Add a new default control point for a given dimension and time.
      void addControlPoint(int dim, Time t, double pos, double val, bool addKey);
      
      //! Delete default control point for a given dimension.
      void deleteControlPoint(int dim, int ctrlIdx);
      
      //! Delete all default control points for a given dimension.
      void deleteAllControlPoints(int dim);
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
      
      //! Get position value range.
      void range(double *pmin, double *pmax);
      
      //! Get dimension label.
      std::string dimensionLabel(int d);
      
      // suite
      
      //! Get number of control points for a given dimension and time.
      int getControlPointsCount(int dim, Time t);
      
      //! Get control point for a given dimension and time.
      void getControlPoint(int dim, Time t, int ctrlIdx, double *pos, double *val);
      
      //! Set control point for a given dimension and time.
      void setControlPoint(int dim, Time t, int ctrlIdx, double pos, double val, bool addKey);
      
      //! Add a new control point for a given dimension and time.
      void addControlPoint(int dim, Time t, double pos, double val, bool addKey);
      
      //! Delete control point for a given dimension.
      void deleteControlPoint(int dim, int ctrlIdx);
      
      //! Delete all control points for a given dimension.
      void deleteAllControlPoints(int dim);
      
      //! Eval parameter value for a given dimension, time and position.
      double eval(int dim, Time t, double pos);
  };
  
}


#endif

#endif
