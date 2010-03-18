#ifndef DG_MATHS_H
#define DG_MATHS_H

#include "DataTypes.h"

namespace dg
{

//******************************************************************************
static const Real PI = 4.0*atan( 1.0 );
static const Real TWO_PI = 2.0 * PI;
static const Real HALF_PI = 0.5 * PI;
static const Real INV_PI = 1.0 / PI;
static const Real INV_TWO_PI = 1.0 / TWO_PI;
static const Real DEG_TO_RAD = PI / 180.0;
static const Real RAD_TO_DEG = 180.0 / PI;
static const Real QUARTER_PI = ( Real ) ( PI / 4.0 );
static const Real EIGHTH_PI = ( Real ) ( PI / 8.0 );
static const Real PI_SQUARED = ( Real ) ( PI * PI );
static const Real PI_INVERSE = ( Real ) ( 1.0 / PI );
static const Real PI_OVER_180 = ( Real ) ( PI / 180 );
static const Real PI_DIV_180 = ( Real ) ( 180 / PI );
//******************************************************************************
Real Erfc(Real fX);
Real LogGamma(Real fX);
//******************************************************************************
inline Real Radians(Real fDeg){ return fDeg*DEG_TO_RAD; }
inline Real Degrees(Real fRad){ return fRad*RAD_TO_DEG; }
//******************************************************************************
inline Real Abs(Real fValue);
inline Real Ceil(Real fValue);
inline Real Clamp(Real fV, Real fMin, Real fMax);
inline Real Exp(Real fValue);
inline Real Floor(Real fValue);
inline Real InvSqrt(Real fValue);
inline Real Log(Real fValue);
inline Real Pow(Real fBase, Real fExponent);
inline Real Cub(Real fValue);
inline Real Square(Real fValue);
inline Real Sqr(Real fValue);
inline Real Sqrt(Real fValue);
inline Real Sign(Real fValue);
inline Real Gamma(Real fX);
inline Real Gaussian( Real fX, Real fStdDev );
inline Real Min( Real fX, Real fA );
inline Real Max( Real fX, Real fA );
inline Real Mod( Real fX, Real fA );
inline Real Frac( const Real fX );
inline Real Step( Real fX, Real fA );
inline Real Erf(Real fX);
inline Real ArcCosine( Real fValue );
inline Real ArcSine( Real fValue );
inline Real ArcTangent( Real fValue );
inline Real ArcTangent( Real fY, Real fX );
inline Real Cosine( Real fValue );
inline Real Sine( Real fValue );
inline Real Tangent( Real fValue );
//******************************************************************************
//
// Evaluates a 1-dimensional cubic span via Horners rule
//
Real CubicSpan(Real fX, const Real afC[4], const Real afM[4][4]);
//******************************************************************************
//
// bicubic evaluation
//
// X(u,v) = [v^3 v^2 v^1] * Cx * [u^3 u^2 u^1]^T
//
Real BicubicSpan(Real fU, Real fV, Real afBasis[4][4]);
//******************************************************************************
//
// constructs a bicubic coefficients matrix
//
// C = M � Gx � M^(t) (C gets M times Gx times transpose of M)
//
void MakeBicubicMatrix(
	Real afG[4][4],
	Real afM[4][4],
	Real afC[4][4]);
//******************************************************************************
//
// B-Spline basis matrix
//
static const Real BSplineBasis[4][4] =
{
	{-1/6., 1/2.,-1/2., 1/6.},
	{ 1/2.,-1.  , 1/2., 0   },
	{-1/2., 0   , 1/2., 0   },
	{ 1/6., 2/3., 1/6., 0   }
};
//******************************************************************************
//
// Cardinal basis matrix
//
static const Real CardinalBasis[4][4] =
{
	{ -0.5,  1.5, -1.5,  0.5 },
	{  1.0, -2.5,  2.0, -0.5 },
	{ -0.5,  0.0,  0.5,  0.0 },
	{  0.0,  1.0,  0.0,  0.0 }
};
//******************************************************************************
//
// Catmull-Rom basis matrix
//
static const Real CatmullRomBasis[4][4] =
{
	{ -0.5,  1.5, -1.5,  0.5 },
	{  1.0, -2.5,  2.0, -0.5 },
	{ -0.5,  0.0,  0.5,  0.0 },
	{  0.0,  1.0,  0.0,  0.0 },
};
//******************************************************************************
//
// Hermite basis matrix
//
static const Real HermiteBasis[4][4] =
{
	{ 2, -2,  1,  1 },
	{-3,  3, -2, -1 },
	{ 0,  0,  1,  0 },
	{ 1,  0,  0,  0 }
};
//******************************************************************************

#include "Maths.inc"

//******************************************************************************

} // end namespace: dg

#endif
