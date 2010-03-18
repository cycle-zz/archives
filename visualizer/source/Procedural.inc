//******************************************************************************
inline Real dg::r(Int iX)
{
	return R[iX & R_TABLE_MASK];
}
//*******************************************************************************
inline Int dg::p(Int iX)
{
	return P[iX & P_TABLE_MASK];
}
//*******************************************************************************
inline Int dg::Hash(Int iX, Int iY, Int iZ)
{
	return p( p(iX + p(iY + p(iZ) ) ) );
}
//*******************************************************************************
inline Real dg::Lattice(Int iX, Int iY, Int iZ)
{
	return r( Hash(iX, iY, iZ) );
}
//*****************************************************************************
inline Real dg::Gradient(
	Int iX, Int iY, Int iZ,
	Real fX, Real fY, Real fZ)
{
	/* center of cube to edges (tetrahedron) */
	static Real g3[16][3] =
	{
		{ 1, 1, 0}, { -1, 1, 0}, { 1, -1, 0}, { -1, -1, 0},
		{ 1, 0, 1}, { -1, 0, 1}, { 1, 0, -1}, { -1, 0, -1},
		{ 0, 1, 1}, { 0, -1, 1}, { 0, 1, -1}, { 0, -1, -1},
		{ 1, 1, 0}, { -1, 1, 0}, { 0, -1, 1}, { 0, -1, -1}
	};

	// get lattice point
	Int iH = Hash(iX, iY, iZ) & 0xf;

	// determine length of gradient
	return fX * g3[iH][0] + fY * g3[iH][1] + fZ * g3[iH][2];
}
//*****************************************************************************
inline Real dg::Bias( Real fX, Real fA )
{
	Real fV = ((1 / fA - 2)*(1 - fX) + 1);
	if( fV == 0 )
		return 1;
	else
		return fX / fV;
}
//*****************************************************************************
inline Real dg::Gain( Real fX, Real fA )
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
inline Real dg::Cubic( Real fT )
{
	return (fT * fT * (3 - 2 * fT));   // 3t^2 - 2t^3
}
//*****************************************************************************
inline Real dg::Quintic(Real fT)
{
	return fT * fT * fT * (fT * (fT * 6 - 15) + 10); // 6t^5 - 15t^4 + 10t^3
}
//*****************************************************************************
inline Real dg::Lerp(Real fT, Real fA, Real fB)
{
	return ( fA + fT * (fB - fA) );
}
//*****************************************************************************
inline Real dg::Step( Real fX, Real fA )
{
	return (Real)( fX >= fA );
}
//*****************************************************************************
inline Real dg::BoxStep( Real fX, Real fA, Real fB )
{
	return (Real)Clamp((fX-fA)/(fB-fA), 0, 1);
}
//*****************************************************************************
inline Real dg::SmoothStep( Real fA, Real fB, Real fX )
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
inline Real dg::Pulse( Real fX, Real fA, Real fB )
{
	return Step(fX, fA) - Step(fX, fB);
}
//*****************************************************************************
inline Real dg::BoxPulse( Real fX, Real fA, Real fB )
{
	return BoxStep(fX, 0, fA) - BoxStep(fX, 0, fB);
}
//*****************************************************************************
inline Real dg::SmoothPulse( Real fX, Real fA, Real fB )
{
	return SmoothStep(fX, 0, fA) - SmoothStep(fX, 0, fB);
}
//******************************************************************************
inline Real dg::CatmullRomNoise(Real fX, Real fY, Real fZ)
{
	return ValueNoise(fX,fY,fZ,CatmullRomBasis);
}
//******************************************************************************
inline Real dg::HermiteNoise(Real fX, Real fY, Real fZ)
{
	return ValueNoise(fX,fY,fZ,HermiteBasis);
}
//******************************************************************************
inline Real dg::CardinalNoise(Real fX, Real fY, Real fZ)
{
	return ValueNoise(fX,fY,fZ,CardinalBasis);
}
//******************************************************************************
inline Real dg::BSplineNoise(Real fX, Real fY, Real fZ)
{
	return ValueNoise(fX,fY,fZ,BSplineBasis);
}
//******************************************************************************
inline Real dg::FilteredAbs(Real fX, Real fDX)
{
	// Note: based on the idea that the indefinite integral of abs(x) is
	// 		 sign(x) * 1/2 x*x;

	Real fX0 = fX - 0.5 * fDX;
	Real fX1 = fX0 + fDX;

	// first compute the box filter of abs(t) from x-dx/2 to x+dx/2.
	Real fX0Integral = Sign(fX0) * 0.5 * fX0 * fX0;
	Real fX1Integral = Sign(fX1) * 0.5 * fX1 * fX1;

	return (fX1Integral - fX0Integral) / fDX;
}
//******************************************************************************
inline Real dg::FilteredGradientNoise(
	Real fX, Real fY, Real fZ, Real fFilterWidth)
{
	return GradientNoise(fX, fY, fZ) *
		   (1.0f - SmoothStep(0.2, 0.75, fFilterWidth));
}
//******************************************************************************
inline Real DefaultTurbulence(Real fX, Real fY, Real fZ)
{
	// use the default parameters specified in function declaration
	return Turbulence( fX, fY, fZ );
}
//******************************************************************************
inline Real DefaultFBM(Real fX, Real fY, Real fZ)
{
	// use the default parameters specified in function declaration
	return FractionalBrownianMotion( fX, fY, fZ );
}
//******************************************************************************
inline Real DefaultMonoFractal(Real fX, Real fY, Real fZ)
{
	// use the default parameters specified in function declaration
	return MonoFractal( fX, fY, fZ );
}
//******************************************************************************
inline Real DefaultMultiFractal(Real fX, Real fY, Real fZ)
{
	// use the default parameters specified in function declaration
	return MultiFractal( fX, fY, fZ );
}
//******************************************************************************
inline Real DefaultRidgedMultiFractal(Real fX, Real fY, Real fZ)
{
	// use the default parameters specified in function declaration
	return RidgedMultiFractal( fX, fY, fZ );
}
//******************************************************************************
inline Real fBm(
	Real fX, Real fY, Real fZ,
	Real fIncrement, Real fLacunarity, Real fOctaves)
{
	return FractionalBrownianMotion(fX, fY, fZ, fIncrement, fLacunarity, fOctaves);
}

