// #############################################################################
// # Operators.h - Basic procedural functions for pixel manipulation
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

#include "Procedural.h"
#include "DataTypes.h"
#include "RandTables.h"
#include "Messages.h"
#include "Maths.h"

//******************************************************************************

using namespace dg;

//*****************************************************************************
Real dg::Spline(Real fX, UInt uiKnots, Real *apkKnots, const Real afBasis[4][4])
{
	Int iSpan;
	UInt uiSpanCount = uiKnots - 3;

	if (uiSpanCount < 1)
		return 0;

	// Find the appropriate 4-point span of the Spline.
	fX = Clamp(fX, (Real)0.0, (Real)1.0) * uiSpanCount;
	iSpan = (Int) fX;

	if (iSpan >= (Int)uiKnots - 3)
		iSpan = (Int)uiKnots - 3;

	fX -= iSpan;
	apkKnots += iSpan;

	// evaluate with appropriate basis
	return CubicSpan(fX, apkKnots, afBasis);
}
//******************************************************************************
Real dg::CellNoise( Real fX, Real fY, Real fZ )
{
	UInt iX = (Int)Floor(fX);
	UInt iY = (Int)Floor(fY);
	UInt iZ = (Int)Floor(fZ);
	UInt iHash = Hash(iX, iY, iZ);
	return r(iHash);
}
//******************************************************************************
Real dg::GradientNoise(Real fX, Real fY, Real fZ)
{
	Int iX, iY, iZ;
	Real fX0, fX1, fY0, fY1, fZ0, fZ1;
	Real fWX, fWY, fWZ;
	Real fVX0, fVX1, fVY0, fVY1, fVZ0, fVZ1;

	iX = (Int)Floor(fX);
	fX0 = fX - iX;
	fX1 = fX0 - 1;
	fWX = Cubic(fX0);

	iY = (Int)Floor(fY);
	fY0 = fY - iY;
	fY1 = fY0 - 1;
	fWY = Cubic(fY0);

	iZ = (Int)Floor(fZ);
	fZ0 = fZ - iZ;
	fZ1 = fZ0 - 1;
	fWZ = Cubic(fZ0);

	fVX0 = Gradient(iX, iY, iZ, fX0, fY0, fZ0);
	fVX1 = Gradient(iX + 1, iY, iZ, fX1, fY0, fZ0);

	fVY0 = Lerp(fWX, fVX0, fVX1);

	fVX0 = Gradient(iX, iY + 1, iZ, fX0, fY1, fZ0);
	fVX1 = Gradient(iX + 1, iY + 1, iZ, fX1, fY1, fZ0);

	fVY1 = Lerp(fWX, fVX0, fVX1);
	fVZ0 = Lerp(fWY, fVY0, fVY1);

	fVX0 = Gradient(iX, iY, iZ + 1, fX0, fY0, fZ1);
	fVX1 = Gradient(iX + 1, iY, iZ + 1, fX1, fY0, fZ1);

	fVY0 = Lerp(fWX, fVX0, fVX1);

	fVX0 = Gradient(iX, iY + 1, iZ + 1, fX0, fY1, fZ1);
	fVX1 = Gradient(iX + 1, iY + 1, iZ + 1, fX1, fY1, fZ1);

	fVY1 = Lerp(fWX, fVX0, fVX1);
	fVZ1 = Lerp(fWY, fVY0, fVY1);

	return 1.0 - 2.0 * Lerp(fWZ, fVZ0, fVZ1);
	//return Lerp(fWZ, fVZ0, fVZ1);

}
//******************************************************************************
Real dg::ValueNoise(Real fX, Real fY, Real fZ, const Real afBasis[4][4])
{
	Int i, j, k;
	Int iX, iY, iZ;
	Real fRX, fRY, fRZ;
	Real afKnotsX[4], afKnotsY[4], afKnotsZ[4];

	iX = (Int)floor(fX);
	fRX = fX - iX;

	iY = (Int)floor(fY);
	fRY = fY - iY;

	iZ = (Int)floor(fZ);
	fRZ = fZ - iZ;

	for (k = -1; k <= 2; k++)
	{
		for (j = -1; j <= 2; j++)
		{
			for (i = -1; i <= 2; i++)
			{
				afKnotsX[i + 1] = Lattice(iX + i, iY + j, iZ + k);
			}
			afKnotsY[j + 1] = Spline(fRX, 4, afKnotsX, afBasis);
		}
		afKnotsZ[k + 1] = Spline(fRY, 4, afKnotsY, afBasis);
	}
	return Spline(fRZ, 4, afKnotsZ, afBasis);
}
//******************************************************************************
Real dg::FractionalBrownianMotion(
	Real fX, Real fY, Real fZ, Real fIncrement,
	Real fLacunarity, Real fOctaves)
{
	// static variables for caching spectral weights
	static const UInt uiMaxOctaves = 32;
	static bool bInitialized = false;
	static double afExponents[uiMaxOctaves];
	static Real fPrevLacunarity = 0;

	// precompute and store spectral weights
	if(!bInitialized || fPrevLacunarity != fLacunarity)
	{
		//  compute weight for each frequency
		for( UInt i = 0; i < uiMaxOctaves; i++ )
			afExponents[i] = pow( fLacunarity, (Real)i * -fIncrement );

		bInitialized = true;
		fPrevLacunarity = fLacunarity;
	}

	// create the fractional brownian motion
	Real fSum = 0;
	UInt i = 0;
	for(i = 0;  i < fOctaves;  i++)
	{
		fSum += afExponents[i] * GradientNoise(fX, fY, fZ);

		// multipy in the lacunarity to create the gaps between octaves
		fX *= fLacunarity;
		fY *= fLacunarity;
		fZ *= fLacunarity;
	}

	// take care of remainder in "octaves"
	Real fRemainder = fOctaves - (int)fOctaves;
	if ( fRemainder )
	{
		// "i" and spatial freq. are preset in loop above
		fSum += fRemainder * afExponents[i] * GradientNoise(fX, fY, fZ);
	}
	return fSum;
}
//******************************************************************************
Real dg::FilteredFBM(
	Real fX, Real fY, Real fZ,
	Real fFilterWidth,
	Real fIncrement,
	Real fLacunarity,
	Real fOctaves)
{
	// static variables for caching spectral weights
	static const UInt uiMaxOctaves = 32;
	static bool bInitialized = false;
	static double afExponents[uiMaxOctaves];
	static Real fPrevLacunarity = 0;

	// precompute and store spectral weights
	if(!bInitialized || fPrevLacunarity != fLacunarity)
	{
		//  compute weight for each frequency
		for( UInt i = 0; i < uiMaxOctaves; i++ )
			afExponents[i] = pow( fLacunarity, (Real)i * -fIncrement );

		bInitialized = true;
		fPrevLacunarity = fLacunarity;
	}

	// create the fractional brownian motion
	Real fSum = 0;
	UInt i = 0;
	for(i = 0;  i < fOctaves;  i++)
	{
		fSum += afExponents[i] * FilteredGradientNoise(fX, fY, fZ, fFilterWidth);

		// multipy in the lacunarity to create the gaps between octaves
		fX *= fLacunarity;
		fY *= fLacunarity;
		fZ *= fLacunarity;

		fFilterWidth *= fLacunarity;
	}

	// take care of remainder in "octaves"
	Real fRemainder = fOctaves - (int)fOctaves;
	if ( fRemainder )
	{
		// "i" and spatial freq. are preset in loop above
		fSum += fRemainder * afExponents[i] * FilteredGradientNoise(fX, fY, fZ, fFilterWidth);
	}
	return fSum;
}
//******************************************************************************
Real dg::Turbulence(
	Real fX, Real fY, Real fZ,
	Real fIncrement,
	Real fLacunarity,
	Real fOctaves)
{
	// static variables for caching spectral weights
	static const UInt uiMaxOctaves = 32;
	static bool bInitialized = false;
	static double afExponents[uiMaxOctaves];
	static Real fPrevLacunarity = 0;

	// precompute and store spectral weights
	if(!bInitialized || fPrevLacunarity != fLacunarity)
	{
		//  compute weight for each frequency
		for( UInt i = 0; i < uiMaxOctaves; i++ )
			afExponents[i] = pow( fLacunarity, (Real)i * -fIncrement );

		bInitialized = true;
		fPrevLacunarity = fLacunarity;
	}

	UInt i = 0;
	Real fTemp, fValue, fRemainder;

	fValue = 0.0;
	fTemp = 0.0;

	// inner loop of spectral construction, where the fractal is built
	for (i = 0; i < fOctaves; i++)
	{
		// calculate the signal contribution
		fTemp = GradientNoise(fX, fY, fZ) * afExponents[i];

		// accumulate the result
		fValue += Abs(fTemp);

		// multipy in the lacunarity to create the gaps between octaves
		fX *= fLacunarity;
		fY *= fLacunarity;
		fZ *= fLacunarity;
	}

	// take care of remainder in "octaves"
	fRemainder = fOctaves - (int)fOctaves;
	if ( fRemainder )
	{
		// "i" and spatial freq. are preset in loop above
		fTemp = fRemainder * GradientNoise(fX, fY, fZ) * afExponents[i];

		// accumulate the result
		fValue += Abs(fTemp);
	}
	return( fValue );
}
//******************************************************************************
Real dg::FilteredTurbulence(
	Real fX, Real fY, Real fZ,
	Real fFilterWidth,
	Real fIncrement,
	Real fLacunarity,
	Real fOctaves)
{
	// static variables for caching spectral weights
	static const UInt uiMaxOctaves = 32;
	static bool bInitialized = false;
	static double afExponents[uiMaxOctaves];
	static Real fPrevLacunarity = 0;

	// precompute and store spectral weights
	if(!bInitialized || fPrevLacunarity != fLacunarity)
	{
		//  compute weight for each frequency
		for( UInt i = 0; i < uiMaxOctaves; i++ )
			afExponents[i] = pow( fLacunarity, (Real)i * -fIncrement );

		bInitialized = true;
		fPrevLacunarity = fLacunarity;
	}

	UInt i = 0;
	Real fTemp, fValue, fRemainder;

	fValue = 0.0;
	fTemp = 0.0;

	// inner loop of spectral construction, where the fractal is built
	for (i = 0; i < fOctaves; i++)
	{
		// calculate the signal contribution
		fTemp = FilteredGradientNoise(fX, fY, fZ, fFilterWidth) * afExponents[i];

		// accumulate the result
		fValue += FilteredAbs(fTemp, fFilterWidth);

		// multipy in the lacunarity to create the gaps between octaves
		fX *= fLacunarity;
		fY *= fLacunarity;
		fZ *= fLacunarity;
		fFilterWidth *= fLacunarity;
	}

	// take care of remainder in "octaves"
	fRemainder = fOctaves - (int)fOctaves;
	if ( fRemainder )
	{
		// "i" and spatial freq. are preset in loop above
		fValue += fRemainder * FilteredGradientNoise(fX, fY, fZ, fFilterWidth) * afExponents[i];

		// accumulate the result
		fValue += FilteredAbs(fTemp, fFilterWidth);
	}
	return( fValue );
}
//******************************************************************************
Real dg::MonoFractal(
	Real fX, Real fY, Real fZ,
	Real fIncrement,
	Real fLacunarity,
	Real fOctaves)
{
	// static variables for caching spectral weights
	static const UInt uiMaxOctaves = 32;
	static bool bInitialized = false;
	static double afExponents[uiMaxOctaves];
	static Real fPrevLacunarity = 0;

	// precompute and store spectral weights
	if(!bInitialized || fPrevLacunarity != fLacunarity)
	{
		//  compute weight for each frequency
		for( UInt i = 0; i < uiMaxOctaves; i++ )
			afExponents[i] = pow( fLacunarity, (Real)i * -fIncrement );

		bInitialized = true;
		fPrevLacunarity = fLacunarity;
	}


	UInt i = 0;
	Real fValue, fRemainder;
	fValue = 0.0;

	// inner loop of spectral construction, where the fractal is built
	for ( i = 0; i < fOctaves; i++ )
	{
		// evaluate the basis function to create the spectrum
		fValue += GradientNoise(fX, fY, fZ) * afExponents[i];

		// multipy in the lacunarity to create the gaps between octaves
		fX *= fLacunarity;
		fY *= fLacunarity;
		fZ *= fLacunarity;
	}

	// take care of remainder in "octaves"
	fRemainder = fOctaves - (int)fOctaves;
	if ( fRemainder )
	{
		// "i" and spatial freq. are preset in loop above
		fValue += fRemainder * GradientNoise(fX, fY, fZ) * afExponents[i];
	}
	return( fValue );
}
//*****************************************************************************
Real dg::MultiFractal(
	Real fX, Real fY, Real fZ,
	Real fIncrement,
	Real fLacunarity,
	Real fOctaves)
{
	// static variables for caching spectral weights
	static const UInt uiMaxOctaves = 32;
	static bool bInitialized = false;
	static double afExponents[uiMaxOctaves];
	static Real fPrevLacunarity = 0;

	// precompute and store spectral weights
	if(!bInitialized || fPrevLacunarity != fLacunarity)
	{
		//  compute weight for each frequency
		for( UInt i = 0; i < uiMaxOctaves; i++ )
			afExponents[i] = pow( fLacunarity, (Real)i * -fIncrement );

		bInitialized = true;
		fPrevLacunarity = fLacunarity;
	}

	UInt i = 0;
	Real fValue, fRemainder;
	fValue = 1.0;

	// inner loop of spectral construction, where the fractal is built
	for ( i = 0; i < fOctaves; i++ )
	{
		// evaluate the basis function to create the spectrum
		fValue *= afExponents[i] * GradientNoise(fX, fY, fZ) + 1.0f;

		// multipy in the lacunarity to create the gaps between octaves
		fX *= fLacunarity;
		fY *= fLacunarity;
		fZ *= fLacunarity;
	}

	// take care of remainder in "octaves"
	fRemainder = fOctaves - (int)fOctaves;
	if ( fRemainder )
	{
		fValue *= fRemainder * afExponents[i] * GradientNoise(fX, fY, fZ) + 1.0f;
	}
	return( fValue );
}
//*****************************************************************************
Real dg::HybridMultiFractal(
	Real fX, Real fY, Real fZ,
	Real fIncrement,
	Real fLacunarity,
	Real fOffset,
	Real fGain,
	Real fOctaves)
{
	// static variables for caching spectral weights
	static const UInt uiMaxOctaves = 32;
	static bool bInitialized = false;
	static double afExponents[uiMaxOctaves];
	static Real fPrevLacunarity = 0;

	// precompute and store spectral weights
	if(!bInitialized || fPrevLacunarity != fLacunarity)
	{
		//  compute weight for each frequency
		for( UInt i = 0; i < uiMaxOctaves; i++ )
			afExponents[i] = pow( fLacunarity, (Real)i * -fIncrement );

		bInitialized = true;
		fPrevLacunarity = fLacunarity;
	}

	UInt i = 0;

	// get signal for first octave
	Real fSignal = GradientNoise(fX, fY, fZ);

	// assign initial values
	Real fResult = fSignal;
	Real fWeight = fGain * fSignal;

	// multipy in the lacunarity to create the gaps between octaves
	fX *= fLacunarity;
	fY *= fLacunarity;
	fZ *= fLacunarity;

	// inner loop of spectral construction, where the fractal is built
	for ( i = 0; i < fOctaves; i++ )
	{
		// weight successive contributions by previous signal, clamp [0.0,1.0]
		if(fWeight > 1.0f)
			fWeight = 1.0f;

		// invert and translate (note that "offset" should be ~= 1.0)
		fSignal = (GradientNoise(fX, fY, fZ) + fOffset) * afExponents[i];

		// weight the contribution
		fResult += fSignal * fWeight;

		// square the signal, to increase "sharpness" of ridges
		fWeight *= fGain * fSignal;

		// multipy in the lacunarity to create the gaps between octaves
		fX *= fLacunarity;
		fY *= fLacunarity;
		fZ *= fLacunarity;
	}

	// take care of remainder in "octaves"
	Real fRemainder = fOctaves - (int)fOctaves;
	if ( fRemainder )
	{
		fResult *= fRemainder * afExponents[i] * GradientNoise(fX, fY, fZ);
	}
	return fResult;
}
//*****************************************************************************
Real dg::RidgedMultiFractal(
	Real fX, Real fY, Real fZ,
	Real fIncrement,
	Real fLacunarity,
	Real fThreshold,
	Real fOffset,
	Real fOctaves)
{
	// static variables for caching spectral weights
	static const UInt uiMaxOctaves = 32;
	static bool bInitialized = false;
	static double afExponents[uiMaxOctaves];
	static Real fPrevLacunarity = 0;

	// precompute and store spectral weights
	if(!bInitialized || fPrevLacunarity != fLacunarity)
	{
		//  compute weight for each frequency
		for( UInt i = 0; i < uiMaxOctaves; i++ )
			afExponents[i] = pow( fLacunarity, (Real)i * -fIncrement );

		bInitialized = true;
		fPrevLacunarity = fLacunarity;
	}

	UInt i = 0;

	// get absolute value of signal for first octave (this creates the ridges)
	Real fSignal = Abs( GradientNoise(fX, fY, fZ) );

	// invert and translate (note that "offset" should be ~= 1.0)
	fSignal = fOffset - fSignal;

	// square the signal, to increase "sharpness" of ridges
	fSignal *= fSignal;

	// assign initial values
	Real fResult = fSignal;
	Real fWeight = 1.0;

	// inner loop of spectral construction, where the fractal is built
	for ( i = 0; i < fOctaves; i++ )
	{
		// multipy in the lacunarity to create the gaps between octaves
		fX *= fLacunarity;
		fY *= fLacunarity;
		fZ *= fLacunarity;

		// weight successive contributions by previous signal, clamp [0.0,1.0]
		fWeight = Clamp( fSignal * fThreshold, 0.0, 1.0 );

		// get absolute value of signal (this creates the ridges)
		fSignal = Abs( GradientNoise(fX, fY, fZ ));

		// invert and translate (note that "offset" should be ~= 1.0)
		fSignal = fOffset - fSignal;

		// square the signal, to increase "sharpness" of ridges
		fSignal *= fSignal;

		// weight the contribution
		fSignal *= fWeight;

		// accumulate the result
		fResult += fSignal * afExponents[i];

	}
	return fResult;
}
//******************************************************************************
Real dg::Quadric(Real fA, Real fB, Real fC)
{
	Real fT = 0.0;
	Real fDet = fB*fB - 4.0*fA*fC;
	fA *= 2.0;
	if (fDet > 0.0)
	{
		fDet = sqrt(fDet);
		fT = (fB - fDet)/fA;
		if (fT > 0.0)
		{
			return fT;
		}
		else
		{
			fT = (fB + fDet)/fA;
			return fT;
		}
	}
	else
	{
	   fT = -1.0;
	}
	return fT;
}
//******************************************************************************
Real dg::VoronoiNoise(
	Real fX, Real fY, Real fZ,
	Real fJitter,
	Real& rfOX, Real& rfOY, Real& rfOZ)
{
	Real fCX = Floor(fX) + 0.5;
	Real fCY = Floor(fY) + 0.5;
	Real fCZ = Floor(fZ) + 0.5;

	Real f1 = 1000;
	Real i, j, k;
	for (i = -1;  i <= 1;  i += 1)
	{
		for (j = -1;  j <= 1;  j += 1)
		{
			for (k = -1;  k <= 1;  k += 1)
			{
				Real fTX = fCX + i;
				Real fTY = fCY + j;
				Real fTZ = fCZ + k;

				Real fNoise = CellNoise(fTX, fTY, fTZ);

				Real fPX = fTX + fJitter * fNoise - 0.5;
				Real fPY = fTY + fJitter * fNoise - 0.5;
				Real fPZ = fTZ + fJitter * fNoise - 0.5;

				Real fDX = fPX - fX;
				Real fDY = fPY - fY;
				Real fDZ = fPZ - fZ;

				Real fDistSqr = fDX*fDX + fDY*fDY + fDZ*fDZ;

				if(fDistSqr < f1)
				{
					f1 = fDistSqr;
					rfOX = fPX;
					rfOY = fPY;
					rfOZ = fPZ;
				}
			}
		}
	}
	return sqrt(f1);
}
