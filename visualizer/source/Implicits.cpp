
#include "Implicits.h"
#include "DataTypes.h"
#include "Vector.h"
#include "Procedural.h"
#include <cstdio>

using namespace dg;

//******************************************************************************
Real dg::Torus(Real fX, Real fY, Real fZ)
{
	Real fX2 = fX*fX;
	Real fY2 = fY*fY;
	Real fZ2 = fZ*fZ;
	Real fA = fX2 + fY2 + fZ2 + (0.5 *0.5) - (0.1 * 0.1);
	Real fResult = fA * fA - 4.0 * (0.5 * 0.5) * ( fY2 + fZ2 );
	return Validate( fResult );
}
//******************************************************************************
Real dg::Sphere(Real fX, Real fY, Real fZ)
{
	Real fRadSqr = fX * fX + fY * fY + fZ * fZ;
	Real fResult = 1.0/(fRadSqr < 0.00001? 0.00001 : fRadSqr);
	return Validate( fResult );
}
//******************************************************************************
Real dg::Blob(Real fX, Real fY, Real fZ)
{
	static Real fDelta = 1.1f;
	Real fResult = Exp( 1.0f - Sqr(fX) - Sqr(fY + fDelta) - Sqr( fZ )) +
				   Exp( 1.0f - Sqr(fX) - Sqr(fY - fDelta) - Sqr( fZ )) - 1.0f;
   return fResult;
}
//******************************************************************************
Real dg::TriBlob(Real fX, Real fY, Real fZ)
{
	Real fResult =  4.0 - Sphere(fX + 1.0, fY, fZ) -
						  Sphere( fX, fY + 1.0, fZ) -
						  Sphere(fX, fY, fZ + 1.0);
	return Validate( fResult );
}
//******************************************************************************
Real dg::Heart(Real fX, Real fY, Real fZ)
{
	Real fResult = Cub(2.0f * Sqr(fX) + Sqr(fY) + Sqr(fZ) - 1.0f) -
				   (0.1f * Sqr(fX) + Sqr(fY) ) * Cub(fZ);
	return fResult;
}
//******************************************************************************
Real dg::KleinBottle( Real fX, Real fY, Real fZ)
{
	Real fResult = (Sqr(fX) + Sqr(fY) + Sqr(fZ) + 2.0f * fY - 1.0f) *
				   (Sqr( Sqr(fX) + Sqr(fY) + Sqr(fZ) - 2.0f * fY - 1.0f) -
				   8.0f * Sqr(fZ)) + 16.0f * fX * fZ *
				   (Sqr(fX) + Sqr(fY) + Sqr(fZ) - 2.0f * fY - 1.0f);

	return fResult;
}
//******************************************************************************
Real dg::TriConnect(Real fX, Real fY, Real fZ)
{
	Real fT = Clamp(fZ, 0, 1);

	Real fResult =  4.0 - Sphere(fT*fX, fY, fZ) -
						  Sphere(fX, fT*fY, fZ) -
						  Sphere(fX, fY, fT*fZ);
	return fResult;
}
//******************************************************************************
Real dg::QuadConnect(Real fX, Real fY, Real fZ)
{
	Real fT = 1.0f;

	// use the distance of from center to
	// define three moving lines
	Real fResult = 0.0;
	Real fDX, fDY, fDZ;
	fDX = fX - 0.5f * fT;
	fDY = fY - 0.0f * fT;
	fResult += 0.5/(fDX*fDX + fDY*fDY);

	fDX = fX - 0.0f * fT;
	fDZ = fZ - 0.0f * fT;
	fResult += 0.75/(fDX*fDX + fDZ*fDZ);

	fDY = fY - 0.0f * fT;
	fDZ = fZ - 0.5f * fT;
	fResult += 1.0/(fDY*fDY + fDZ*fDZ);

	return fResult/100.0f;
}
//******************************************************************************
Real dg::Ripples(Real fX, Real fY, Real fZ)
{
	Real fT = Sine(fZ);

	// define a height field by using the distance
	// from the center into the sin and cos functions
	Real fHeight = 20.0*(fT + Sqrt((0.5-fX)*(0.5-fX) + (0.5-fY)*(0.5-fY)));
	fHeight = 1.5 + 0.1*(Sine(fHeight) + Cosine(fHeight));
	Real fResult = (fHeight - fZ)*50.0;

	return fResult;
}
//******************************************************************************
Real dg::VoronoiBumps(Real fX, Real fY, Real fZ)
{
	// define a height field by using voronoi noise
	Real fRX, fRY, fRZ;
	Real fHeight = VoronoiNoise( fX, fY, fZ, 1, fRX, fRY, fRZ );
	Real fResult = (fHeight - fZ)*10;

	return fResult;
}
//******************************************************************************
Real dg::SphericalShell(Real fX, Real fY, Real fZ)
{
	static Real fOuterRadius = 1.0;
	static Real fInnerRadius = 0.9;
	static Real fOuter = fOuterRadius * fOuterRadius;
	static Real fInner = fInnerRadius * fInnerRadius;
	static Real fDelta = fInner - fOuter;
	static Real fInvDelta = 1.0/fDelta;

	Real fRadSqr = fX * fX + fY * fY + fZ * fZ;

	if(fRadSqr > fOuter)
		return 0.0;
	else if (fRadSqr < fInner)
		return 1.0;

	return (fRadSqr - fOuter) * fInvDelta;
}
//******************************************************************************
Real dg::SphericalFalloff(Real fX, Real fY, Real fZ)
{
	static Real fOuterRadius = 1.0;
	static Real fInnerRadius = 0.0;
	static Real fOuter = fOuterRadius * fOuterRadius;
	static Real fInner = fInnerRadius * fInnerRadius;
	static Real fDelta = fInner - fOuter;
	static Real fInvDelta = 1.0/fDelta;

	Real fRadSqr = fX * fX + fY * fY + fZ * fZ;

	if(fRadSqr > fOuter)
		return 0.0;
	else if (fRadSqr < fInner)
		return 1.0;

	return (fRadSqr - fOuter) * fInvDelta;
}
//******************************************************************************
Real dg::EggShell( Real fX, Real fY, Real fZ )
{
	static Real fOuterRadius = 1.0;
	static Real fInnerRadius = 0.9;
	static Real fOuter = fOuterRadius * fOuterRadius;
	static Real fInner = fInnerRadius * fInnerRadius;
	static Real fDelta = fInner - fOuter;
	static Real fInvDelta = 1.0/fDelta;

	Real fE = ( 5.0 - fY / fOuter ) / 6.0;
	fX = fX / fE;
	fZ = fZ / fE;
	Real fRadSqr = fX * fX + fY * fY + fZ * fZ;

	if(fRadSqr > fOuter)
		return 0.0;
	else if (fRadSqr < fInner)
		return 1.0;

	return (fRadSqr - fOuter) * fInvDelta;
}
//******************************************************************************
Real dg::EggFalloff( Real fX, Real fY, Real fZ )
{
	static Real fOuterRadius = 1.0;
	static Real fInnerRadius = 0.0;
	static Real fOuter = fOuterRadius * fOuterRadius;
	static Real fInner = fInnerRadius * fInnerRadius;
	static Real fDelta = fInner - fOuter;
	static Real fInvDelta = 1.0/fDelta;

	Real fE = ( 5.0 - fY / fOuter ) / 6.0;
	fX = fX / fE;
	fZ = fZ / fE;

	Real fRadSqr = fX * fX + fY * fY + fZ * fZ;

	if(fRadSqr > fOuter)
		return 0.0;
	else if (fRadSqr < fInner)
		return 1.0;

	return (fRadSqr - fOuter) * fInvDelta;
}
//******************************************************************************
Real dg::TurbulentSpace( Real fX, Real fY, Real fZ )
{
	static Real fAmplitude = 1.0;

	Real fValue = 0.5 + fAmplitude * DefaultTurbulence(fX, fY, fZ);

	return Max(0.0, Min( 1.0, fValue ) );
}
//******************************************************************************
Real dg::TurbulentSphere( Real fX, Real fY, Real fZ )
{
	Real fValue = SphericalFalloff( fX, fY, fZ );

	if(fValue > 0.0)
		fValue = fValue * TurbulentSpace( fX, fY, fZ );

	return fValue;
}
//******************************************************************************
Real dg::Threads( Real fX, Real fY, Real fZ )
{
	static Real fBias = 0.1;
	static Real fGain = 0.7;

	if(Abs(fY) > PI)
		return 0.0;

	fY = fY + HALF_PI * Cosine(fX) * Cosine(fZ);
	if(Abs(fY) > HALF_PI)
		return 0.0;

	Real fValue = Cosine(fY);
	fValue = fValue * Cosine(fZ);
	fValue = fValue * fValue;

	fValue = Bias( fValue, fBias );
	fValue = Gain( fValue, fGain );

	return fValue;
}
//******************************************************************************
Real dg::Cloth( Real fX, Real fY, Real fZ )
{
	return Threads( fX, fY, fZ ) + Threads(fZ, -fY, fX);
}
//******************************************************************************
Real dg::SuperEllipsoid( Real fX, Real fY, Real fZ, Real fN1, Real fN2 )
{
	static Real fRX = 1.0;
	static Real fRY = 1.0;
	static Real fRZ = 1.0;

	//static Real fN1 = 0.5;
	//static Real fN2 = 1;

	Real fN2N1 = fN2/fN1;
	Real f2N1 = 2.0/fN1;
	Real f2N2 = 2.0/fN2;

	Real fA = Pow( fX/ fRX, f2N2 );
	Real fB = Pow( fY/ fRY, f2N1 );
	Real fC = Pow( fA + fB, fN2N1 );
	Real fResult = fC + Pow( fZ / fRZ, f2N1 );
	return fResult;
}
//******************************************************************************
