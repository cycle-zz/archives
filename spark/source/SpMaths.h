// #############################################################################
//! SpMaths.h : Wrappers for common mathematical functions and constants
//
// Created 		: Aug 2004
// Copyright	: (C) 2004 by Derek Gerstmann
// Email		: dgerstma@acm.org
//
// #############################################################################

// =============================================================================
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
// =============================================================================

#ifndef SP_MATHS_H
#define SP_MATHS_H

#include <cmath>

// ---------------------------------------------------------------------------

namespace Spark
{

#ifndef INFINITY
#define INFINITY FLT_MAX
#endif

// ---------------------------------------------------------------------------
//! Static utility class for mathematical constants
// ---------------------------------------------------------------------------
template< class Real >
class SpMaths
{

//! Static Constants:
public:

	static const Real PI;
	static const Real TWO_PI;
	static const Real HALF_PI;
	static const Real INV_PI;
	static const Real INV_TWO_PI;
	static const Real DEG_TO_RAD;
	static const Real RAD_TO_DEG;
	static const Real EPSILON;
	static const Real MAXIMUM;

};

// ---------------------------------------------------------------------------

template< class Real >
Real Erfc(Real fX);

template< class Real >
Real LogGamma(Real fX);

// ---------------------------------------------------------------------------

template< class Real >
Real Radians(Real fDeg){ return fDeg*DEG_TO_RAD; }

template< class Real >
Real Degrees(Real fRad){ return fRad*RAD_TO_DEG; }

// ---------------------------------------------------------------------------

template< class Real >
Real Abs(Real fValue);

template< class Real >
Real Ceil(Real fValue);

template< class Real >
Real Clamp(Real fV, Real fMin, Real fMax);

template< class Real >
Real Exp(Real fValue);

template< class Real >
Real Floor(Real fValue);

template< class Real >
Real InvSqrt(Real fValue);

template< class Real >
Real Log(Real fValue);

template< class Real >
Real Pow(Real fBase, Real fExponent);

template< class Real >
Real Cub(Real fValue);

template< class Real >
Real Square(Real fValue);

template< class Real >
Real Sqr(Real fValue);

template< class Real >
Real Sqrt(Real fValue);

template< class Real >
Real Sign(Real fValue);

template< class Real >
Real Gamma(Real fX);

template< class Real >
Real Gaussian( Real fX, Real fStdDev );

template< class Real >
Real Min( Real fX, Real fA );

template< class Real >
Real Max( Real fX, Real fA );

template< class Real >
Real Mod( Real fX, Real fA );

template< class Real >
Real Frac( const Real fX );

template< class Real >
Real Step( Real fX, Real fA );

template< class Real >
Real Erf(Real fX);

template< class Real >
Real ArcCosine( Real fValue );

template< class Real >
Real ArcSine( Real fValue );

template< class Real >
Real ArcTangent( Real fValue );

template< class Real >
Real ArcTangent( Real fY, Real fX );

template< class Real >
Real Cosine( Real fValue );

template< class Real >
Real Sine( Real fValue );

template< class Real >
Real Tangent( Real fValue );

// ---------------------------------------------------------------------------

inline bool IsPowerOfTwo( int iWidth, int iHeight );

// ---------------------------------------------------------------------------

#include "SpMaths.inc"

// ---------------------------------------------------------------------------

} // end namespace: Spark

#endif
