//*******************************************************************************
inline Real dg::Abs(Real fValue)
{
	return (fValue < 0 ? -fValue : fValue);
}
//*******************************************************************************
inline Real dg::Ceil(Real fValue)
{
	return (Real)ceil((Real)fValue);
}
//*******************************************************************************
inline Real dg::Clamp(Real fV, Real fMin, Real fMax)
{
	return (fV < fMin) ? fMin : ((fV > fMax) ? fMax : fV);
}
//*******************************************************************************
inline Real dg::Exp(Real fValue)
{
	return (Real)exp((Real)fValue);
}
//*******************************************************************************
inline Real dg::Floor(Real fValue)
{
	return (Real)floor((Real)fValue);
}
//*******************************************************************************
inline Real dg::InvSqrt(Real fValue)
{
	return (Real)(1.0 / sqrt((Real)fValue));
}
//*******************************************************************************
inline Real dg::Log(Real fValue)
{
	return (Real)log((Real)fValue);
}
//*******************************************************************************
inline Real dg::Pow(Real fBase, Real fExponent)
{
	return (Real)pow((Real)fBase, (Real)fExponent);
}
//*******************************************************************************
inline Real dg::Cub(Real fValue)
{
	return fValue*fValue*fValue;
}
//*******************************************************************************
inline Real dg::Square(Real fValue)
{
	return fValue*fValue;
}
//*******************************************************************************
inline Real dg::Sqr(Real fValue)
{
	return fValue*fValue;
}
//*******************************************************************************
inline Real dg::Sqrt(Real fValue)
{
	return (Real)sqrt((Real)fValue);
}
//*******************************************************************************
inline Real dg::Sign(Real fValue)
{
	if ( fValue > (Real)0.0 )
		return (Real)1.0;

	if ( fValue < (Real)0.0 )
		return -(Real)1.0;

	return (Real)0.0;
}
inline Real dg::Gamma(Real fX)
{
	return dg::Exp(LogGamma(fX));
}
//*******************************************************************************
inline Real dg::Gaussian( Real fX, Real fStdDev )
{
	return dg::Exp( -fX*fX / (2*fStdDev*fStdDev) );
}
//*******************************************************************************
inline Real dg::Mod( Real fX, Real fA )
{
	int iN = (int)(fX / fA);

	fX -= iN * fA;
	if ( fX < 0 )
		fX += fA;
	return fX;
}
//*******************************************************************************
inline Real dg::Min( Real fA, Real fB )
{
	return fA < fB ? fA : fB;
}
//*******************************************************************************
inline Real dg::Max( Real fA, Real fB )
{
	return fA > fB ? fA : fB;
}
//*******************************************************************************
inline Real dg::Frac( const Real fX )
{
	return fX - (Int)(Floor(fX));
}
//*******************************************************************************
inline Real dg::Erf(Real fX)
{
	return (Real)1.0 -erfc(fX);
}
//*******************************************************************************
inline Real dg::ArcCosine( Real fValue )
{
	if ( -( Real ) 1.0 < fValue )
	{
		if ( fValue < ( Real ) 1.0 )
			return ( Real ) acos( ( Real ) fValue );
		else
			return ( Real ) 0.0;
	}
	else
	{
		return PI;
	}
}
//*******************************************************************************
inline Real dg::ArcSine( Real fValue )
{
	if ( -( Real ) 1.0 < fValue )
	{
		if ( fValue < ( Real ) 1.0 )
			return ( Real ) asin( ( Real ) fValue );
		else
			return -HALF_PI;
	}
	else
	{
		return HALF_PI;
	}
}
//*******************************************************************************
inline Real dg::ArcTangent( Real fValue )
{
	return ( Real ) atan( ( Real ) fValue );
}
//*******************************************************************************
inline Real dg::ArcTangent( Real fY, Real fX )
{
	return ( Real ) atan2( ( Real ) fY, ( Real ) fX );
}
//*******************************************************************************
inline Real dg::Cosine( Real fValue )
{
	return cos( fValue );
}
//*******************************************************************************
inline Real dg::Sine( Real fValue )
{
	return sin( fValue );
}
//*******************************************************************************
inline Real dg::Tangent( Real fValue )
{
	return tan( fValue );
}
