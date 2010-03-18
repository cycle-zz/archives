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

#ifndef DG_PROCEDURAL_H
#define DG_PROCEDURAL_H

#include "DataTypes.h"
#include "RandTables.h"
#include "Random.h"
#include "Maths.h"


//******************************************************************************

namespace dg
{

//******************************************************************************
Real Quadric(Real fA, Real fB, Real fC);

Real Spline(Real fX, UInt uiKnots, Real *apkKnots, const Real afB[4][4]= CatmullRomBasis);
Real CellNoise( Real fX, Real fY, Real fZ );
Real GradientNoise(Real fX, Real fY, Real fZ);
Real ValueNoise(Real fX, Real fY, Real fZ, const Real afB[4][4]= CatmullRomBasis);

Real FractionalBrownianMotion(
	Real fX, Real fY, Real fZ,
	Real fIncrement = 0.5f,
	Real fLacunarity=2.0345f,
	Real fOctaves=4.0f);

Real Turbulence(
	Real fX, Real fY, Real fZ,
	Real fIncrement = 0.5f,
	Real fLacunarity = 2.0345f,
	Real fOctaves = 4.0f);

Real MonoFractal(
	Real fX, Real fY, Real fZ,
	Real fIncrement = 0.5f,
	Real fLacunarity = 2.0345f,
	Real fOctaves = 4.0f);

Real MultiFractal(
	Real fX, Real fY, Real fZ,
	Real fIncrement = 0.5f,
	Real fLacunarity = 2.0345f,
	Real fOctaves = 4.0f);

Real HybridMultiFractal(
	Real fX, Real fY, Real fZ,
	Real fIncrement = 0.25f,
	Real fLacunarity = 2.0345f,
	Real fOffset = 0.7f,
	Real fGain = 1.0f,
	Real fOctaves = 4.0f);

Real RidgedMultiFractal(
	Real fX, Real fY, Real fZ,
	Real fIncrement = 0.9f,
	Real fLacunarity = 2.0345f,
	Real fThreshold = 0.5f,
	Real fOffset = 1.0f,
	Real fOctaves = 4.0f);

Real FilteredTurbulence(
	Real fX, Real fY, Real fZ,
	Real fFilterWidth,
	Real fIncrement = 0.5f,
	Real fLacunarity = 2.0345f,
	Real fOctaves = 4.0f);

Real FilteredFBM(
	Real fX, Real fY, Real fZ,
	Real fFilterWidth, Real fIncrement = 0.5f,
	Real fLacunarity=2.0345f, Real fOctaves=4.0f );

Real VoronoiNoise(
	Real fX, Real fY, Real fZ,
	Real fJitter,
	Real& rfOX, Real& rfOY, Real& rfOZ);

//******************************************************************************

inline Real DefaultTurbulence(Real fX, Real fY, Real fZ);
inline Real DefaultFBM(Real fX, Real fY, Real fZ);
inline Real DefaultMonoFractal(Real fX, Real fY, Real fZ);
inline Real DefaultMultiFractal(Real fX, Real fY, Real fZ);
inline Real DefaultRidgedMultiFractal(Real fX, Real fY, Real fZ);

inline Real fBm(
	Real fX, Real fY, Real fZ,
	Real fIncrement = 0.5f,
	Real fLacunarity=2.0345f,
	Real fOctaves=4.0f);

//******************************************************************************

inline Real r(Int iX);
inline Int p(Int iX);
inline Int Hash(Int iX, Int iY, Int iZ);
inline Real Lattice(Int iX, Int iY, Int iZ);
inline Real Gradient( Int iX, Int iY, Int iZ, Real fX, Real fY, Real fZ);
inline Real Bias( Real fX, Real fA );
inline Real Gain( Real fX, Real fA );
inline Real Cubic( Real fT );
inline Real Quintic(Real fT);
inline Real Lerp(Real fT, Real fA, Real fB);
inline Real Step( Real fX, Real fA );
inline Real BoxStep( Real fX, Real fA, Real fB );
inline Real SmoothStep( Real fA, Real fB, Real fX );
inline Real Pulse( Real fX, Real fA, Real fB );
inline Real BoxPulse( Real fX, Real fA, Real fB );
inline Real SmoothPulse( Real fX, Real fA, Real fB );
inline Real FilteredAbs( Real fX, Real fDX );

inline Real CatmullRomNoise(Real fX, Real fY, Real fZ);
inline Real HermiteNoise(Real fX, Real fY, Real fZ);
inline Real CardinalNoise(Real fX, Real fY, Real fZ);
inline Real BSplineNoise(Real fX, Real fY, Real fZ);
inline Real FilteredGradientNoise(Real fX, Real fY, Real fZ, Real fFilterWidth);

//******************************************************************************

#include "Procedural.inc"

//******************************************************************************

} // end namespace: dg

//******************************************************************************
#endif
