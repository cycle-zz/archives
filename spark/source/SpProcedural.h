// #############################################################################
// # Procedural.h - Basic procedural functions for pixel manipulation
// #
// # Created 	: May 2004
// # Copyright	: (C) 2004 by Derek Gerstmann
// # Email		: dgerstma@acm.org
// #
// #############################################################################

// =============================================================================
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
// =============================================================================

// -----------------------------------------------------------------------------
// The majority of these functions have been derived and adapted from
// examples given in the following excellent must-have procedural references:
//
//  "Texturing & Modeling: A Procedural Approach, 3rd Edition." by
//  David Ebert, F. Kenton Musgrave, Darwin Peachey, Ken Perlin, Steve Worley,
//	Morgan Kauffman, 2003.
//
//  "Advanced RenderMan: Creating CGI for Motion Picture",
//	by Anthony A. Apodaca and Larry Gritz, Morgan Kaufmann, 1999.
// -----------------------------------------------------------------------------

#ifndef SP_PROCEDURAL_H
#define SP_PROCEDURAL_H

#include "SpRandom.h"
#include "SpMaths.h"

// ---------------------------------------------------------------------------

namespace Spark
{

// ---------------------------------------------------------------------------

template<class Real>
Real Quadric(Real fA, Real fB, Real fC);

template<class Real>
Real Spline(Real fX, unsigned int uiKnots, Real *apkKnots, const Real afB[4][4]= CatmullRomBasis);

template<class Real>
Real CellNoise( Real fX, Real fY, Real fZ );

template<class Real>
Real GradientNoise(Real fX, Real fY, Real fZ);

template<class Real>
Real ValueNoise(Real fX, Real fY, Real fZ, const Real afB[4][4]= CatmullRomBasis);

template<class Real>
Real FractionalBrownianMotion(
	Real fX, Real fY, Real fZ,
	Real fIncrement = 0.5f,
	Real fLacunarity=2.0345f,
	Real fOctaves=4.0f);

template<class Real>
Real Turbulence(
	Real fX, Real fY, Real fZ,
	Real fIncrement = 0.5f,
	Real fLacunarity = 2.0345f,
	Real fOctaves = 4.0f);

template<class Real>
Real MonoFractal(
	Real fX, Real fY, Real fZ,
	Real fIncrement = 0.5f,
	Real fLacunarity = 2.0345f,
	Real fOctaves = 4.0f);

template<class Real>
Real MultiFractal(
	Real fX, Real fY, Real fZ,
	Real fIncrement = 0.5f,
	Real fLacunarity = 2.0345f,
	Real fOctaves = 4.0f);

template<class Real>
Real HybridMultiFractal(
	Real fX, Real fY, Real fZ,
	Real fIncrement = 0.25f,
	Real fLacunarity = 2.0345f,
	Real fOffset = 0.7f,
	Real fGain = 1.0f,
	Real fOctaves = 4.0f);

template<class Real>
Real RidgedMultiFractal(
	Real fX, Real fY, Real fZ,
	Real fIncrement = 0.9f,
	Real fLacunarity = 2.0345f,
	Real fThreshold = 0.5f,
	Real fOffset = 1.0f,
	Real fOctaves = 4.0f);

template<class Real>
Real FilteredTurbulence(
	Real fX, Real fY, Real fZ,
	Real fFilterWidth,
	Real fIncrement = 0.5f,
	Real fLacunarity = 2.0345f,
	Real fOctaves = 4.0f);

template<class Real>
Real FilteredFBM(
	Real fX, Real fY, Real fZ,
	Real fFilterWidth, Real fIncrement = 0.5f,
	Real fLacunarity=2.0345f, Real fOctaves=4.0f );

template<class Real>
Real VoronoiNoise(
	Real fX, Real fY, Real fZ,
	Real fJitter,
	Real& rfOX, Real& rfOY, Real& rfOZ);

// ---------------------------------------------------------------------------

template<class Real>
Real DefaultTurbulence(Real fX, Real fY, Real fZ);

template<class Real>
Real DefaultFBM(Real fX, Real fY, Real fZ);

template<class Real>
Real DefaultMonoFractal(Real fX, Real fY, Real fZ);

template<class Real>
Real DefaultMultiFractal(Real fX, Real fY, Real fZ);

template<class Real>
Real DefaultRidgedMultiFractal(Real fX, Real fY, Real fZ);

template<class Real> Real fBm(
	Real fX, Real fY, Real fZ,
	Real fIncrement = 0.5f,
	Real fLacunarity=2.0345f,
	Real fOctaves=4.0f);

// ---------------------------------------------------------------------------

inline int p(int iX);

inline float r(int iX);

// ---------------------------------------------------------------------------

template<class Real>
int Hash(int iX, int iY, int iZ);

template<class Real>
Real Lattice(int iX, int iY, int iZ);

template<class Real>
Real Gradient( int iX, int iY, int iZ, Real fX, Real fY, Real fZ);

template<class Real>
Real Bias( Real fX, Real fA );

template<class Real>
Real Gain( Real fX, Real fA );

template<class Real>
Real Cubic( Real fT );

template<class Real>
Real Quintic(Real fT);

template<class Real>
Real Lerp(Real fT, Real fA, Real fB);

template<class Real>
Real Step( Real fX, Real fA );

template<class Real>
Real BoxStep( Real fX, Real fA, Real fB );

template<class Real>
Real SmoothStep( Real fA, Real fB, Real fX );

template<class Real>
Real Pulse( Real fX, Real fA, Real fB );

template<class Real>
Real BoxPulse( Real fX, Real fA, Real fB );

template<class Real>
Real SmoothPulse( Real fX, Real fA, Real fB );

template<class Real>
Real FilteredAbs( Real fX, Real fDX );

template<class Real>
Real CatmullRomNoise(Real fX, Real fY, Real fZ);

template<class Real>
Real HermiteNoise(Real fX, Real fY, Real fZ);

template<class Real>
Real CardinalNoise(Real fX, Real fY, Real fZ);

template<class Real>
Real BSplineNoise(Real fX, Real fY, Real fZ);

template<class Real>
Real FilteredGradientNoise(Real fX, Real fY, Real fZ, Real fFilterWidth);

// ---------------------------------------------------------------------------

#include "SpProcedural.inc"

// ---------------------------------------------------------------------------

} // end namespace: Spark

#endif
