// ---------------------------------------------------------------------------
inline float Spark::r(int iX)
{
	SeedRandom(iX);
	return RandomUnitFloat();
}
// ---------------------------------------------------------------------------
inline int Spark::p(int iX)
{
	SeedRandom(iX);
	return RandomUInt();
}
// ---------------------------------------------------------------------------
template<class Real> int Spark::Hash(int iX, int iY, int iZ)
{
	return p( p(iX + p(iY + p(iZ) ) ) );
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Lattice(int iX, int iY, int iZ)
{
	return r( Hash(iX, iY, iZ) );
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Gradient(
	int iX, int iY, int iZ,
	Real fX, Real fY, Real fZ)
{
	// center of cube to edges (tetrahedron)
	static Real g3[16][3] =
	{
		{ 1, 1, 0}, { -1, 1, 0}, { 1, -1, 0}, { -1, -1, 0},
		{ 1, 0, 1}, { -1, 0, 1}, { 1, 0, -1}, { -1, 0, -1},
		{ 0, 1, 1}, { 0, -1, 1}, { 0, 1, -1}, { 0, -1, -1},
		{ 1, 1, 0}, { -1, 1, 0}, { 0, -1, 1}, { 0, -1, -1}
	};

	// get lattice point
	int iH = Hash(iX, iY, iZ) & 0xf;

	// determine length of gradient
	return fX * g3[iH][0] + fY * g3[iH][1] + fZ * g3[iH][2];
}
//*****************************************************************************
template<class Real> Real Spark::Bias( Real fX, Real fA )
{
	Real fV = ((1 / fA - 2)*(1 - fX) + 1);
	if( fV == 0 )
		return 1;
	else
		return fX / fV;
}
//*****************************************************************************
template<class Real> Real Spark::Gain( Real fX, Real fA )
{
	if ( fX < 0.5 )
	{
		Real fV = ((1 / fA - 2)*(1 - 2*fX) + 1);
		if(fV == 0)
			return 1;
		else
			return fX / fV;
	}
	else
	{
		Real fV = ((1 / fA - 2)*(1 - 2*fX) - 1);

		if(fV == 0)
			return 1;
		else
			return ((1 / fA - 2)*(1 - 2*fX) - fX) / fV ;
	}
}
//*****************************************************************************
template<class Real> Real Spark::Cubic( Real fT )
{
	return (fT * fT * (3 - 2 * fT));   // 3t^2 - 2t^3
}
//*****************************************************************************
template<class Real> Real Spark::Quintic(Real fT)
{
	return fT * fT * fT * (fT * (fT * 6 - 15) + 10); // 6t^5 - 15t^4 + 10t^3
}
//*****************************************************************************
template<class Real> Real Spark::Lerp(Real fT, Real fA, Real fB)
{
	return ( fA + fT * (fB - fA) );
}
//*****************************************************************************
template<class Real> Real Spark::Step( Real fX, Real fA )
{
	return (Real)( fX >= fA );
}
//*****************************************************************************
template<class Real> Real Spark::BoxStep( Real fX, Real fA, Real fB )
{
	return (Real)Clamp((fX-fA)/(fB-fA), 0, 1);
}
//*****************************************************************************
template<class Real> Real Spark::SmoothStep( Real fA, Real fB, Real fX )
{
	if ( fX < fA )
		return (Real)0.0;
	else
	{
		if ( fX > fB )
			return (Real)1.0;
		else
		{
			fX = (fX - fA) / (fB - fA);          // normalize to [0,1]
			return Cubic( fX );
		}
	}
}
//*****************************************************************************
template<class Real> Real Spark::Pulse( Real fX, Real fA, Real fB )
{
	return Step(fX, fA) - Step(fX, fB);
}
//*****************************************************************************
template<class Real> Real Spark::BoxPulse( Real fX, Real fA, Real fB )
{
	return BoxStep(fX, 0, fA) - BoxStep(fX, 0, fB);
}
//*****************************************************************************
template<class Real> Real Spark::SmoothPulse( Real fX, Real fA, Real fB )
{
	return SmoothStep(fX, 0, fA) - SmoothStep(fX, 0, fB);
}
//******************************************************************************
template<class Real> Real Spark::CatmullRomNoise(Real fX, Real fY, Real fZ)
{
	return ValueNoise(fX,fY,fZ,CatmullRomBasis);
}
//******************************************************************************
template<class Real> Real Spark::HermiteNoise(Real fX, Real fY, Real fZ)
{
	return ValueNoise(fX,fY,fZ,HermiteBasis);
}
//******************************************************************************
template<class Real> Real Spark::CardinalNoise(Real fX, Real fY, Real fZ)
{
	return ValueNoise(fX,fY,fZ,CardinalBasis);
}
//******************************************************************************
template<class Real> Real Spark::BSplineNoise(Real fX, Real fY, Real fZ)
{
	return ValueNoise(fX,fY,fZ,BSplineBasis);
}
//******************************************************************************
template<class Real> Real Spark::FilteredAbs(Real fX, Real fDX)
{
	// Note: based on the idea that the indefinite integral of abs(x) is
	// 		 sign(x) * 1/2 x*x;

	Real fX0 = fX - 0.5f * fDX;
	Real fX1 = fX0 + fDX;

	// first compute the box filter of abs(t) from x-dx/2 to x+dx/2.
	Real fX0Integral = Sign(fX0) * 0.5f * fX0 * fX0;
	Real fX1Integral = Sign(fX1) * 0.5f * fX1 * fX1;

	return (fX1Integral - fX0Integral) / fDX;
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::FilteredGradientNoise(
	Real fX, Real fY, Real fZ, Real fFilterWidth)
{
	return GradientNoise(fX, fY, fZ) *
		   (1.0f - SmoothStep(0.2f, 0.75f, fFilterWidth));
}
// ---------------------------------------------------------------------------
template<class Real> Real DefaultTurbulence(Real fX, Real fY, Real fZ)
{
	// use the default parameters specified in function declaration
	return Turbulence( fX, fY, fZ );
}
// ---------------------------------------------------------------------------
template<class Real> Real DefaultFBM(Real fX, Real fY, Real fZ)
{
	// use the default parameters specified in function declaration
	return FractionalBrownianMotion( fX, fY, fZ );
}
// ---------------------------------------------------------------------------
template<class Real> Real DefaultMonoFractal(Real fX, Real fY, Real fZ)
{
	// use the default parameters specified in function declaration
	return MonoFractal( fX, fY, fZ );
}
// ---------------------------------------------------------------------------
template<class Real> Real DefaultMultiFractal(Real fX, Real fY, Real fZ)
{
	// use the default parameters specified in function declaration
	return MultiFractal( fX, fY, fZ );
}
// ---------------------------------------------------------------------------
template<class Real> Real DefaultRidgedMultiFractal(Real fX, Real fY, Real fZ)
{
	// use the default parameters specified in function declaration
	return RidgedMultiFractal( fX, fY, fZ );
}
// ---------------------------------------------------------------------------
template<class Real> Real fBm(
	Real fX, Real fY, Real fZ,
	Real fIncrement, Real fLacunarity, Real fOctaves)
{
	return FractionalBrownianMotion(fX, fY, fZ, fIncrement, fLacunarity, fOctaves);
}
// ---------------------------------------------------------------------------

