// ---------------------------------------------------------------------------
template<class Real> Real Spark::Abs(Real fValue)
{
	return (fValue < 0 ? -fValue : fValue);
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Ceil(Real fValue)
{
	return (Real)ceil((Real)fValue);
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Clamp(Real fV, Real fMin, Real fMax)
{
	return (fV < fMin) ? fMin : ((fV > fMax) ? fMax : fV);
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Exp(Real fValue)
{
	return (Real)exp((Real)fValue);
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Floor(Real fValue)
{
	return (Real)floor((Real)fValue);
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::InvSqrt(Real fValue)
{
	return (Real)(1.0 / sqrt((Real)fValue));
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Log(Real fValue)
{
	return (Real)log((Real)fValue);
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Pow(Real fBase, Real fExponent)
{
	return (Real)pow((Real)fBase, (Real)fExponent);
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Cub(Real fValue)
{
	return fValue*fValue*fValue;
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Square(Real fValue)
{
	return fValue*fValue;
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Sqr(Real fValue)
{
	return fValue*fValue;
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Sqrt(Real fValue)
{
	return (Real)sqrt((double)fValue);
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Sign(Real fValue)
{
	if ( fValue > (Real)0.0 )
		return (Real)1.0;

	if ( fValue < (Real)0.0 )
		return -(Real)1.0;

	return (Real)0.0;
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Gamma(Real fX)
{
	return Spark::Exp(LogGamma(fX));
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Gaussian( Real fX, Real fStdDev )
{
	return Spark::Exp( -fX*fX / (2*fStdDev*fStdDev) );
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Mod( Real fX, Real fA )
{
	int iN = (int)(fX / fA);

	fX -= iN * fA;
	if ( fX < 0 )
		fX += fA;
	return fX;
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Min( Real fA, Real fB )
{
	return fA < fB ? fA : fB;
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Max( Real fA, Real fB )
{
	return fA > fB ? fA : fB;
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Frac( const Real fX )
{
	return fX - (int)(Floor(fX));
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Erf (Real fX)
{
    return (Real)1.0-Erfc(fX);
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::ArcCosine( Real fValue )
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
// ---------------------------------------------------------------------------
template<class Real> Real Spark::ArcSine( Real fValue )
{
	if ( -( Real ) 1.0 < fValue )
	{
		if ( fValue < ( Real ) 1.0 )
			return ( Real ) asin( ( Real ) fValue );
		else
			return -SpMaths<Real>::HALF_PI;
	}
	else
	{
		return SpMaths<Real>::HALF_PI;
	}
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::ArcTangent( Real fValue )
{
	return ( Real ) atan( ( Real ) fValue );
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::ArcTangent( Real fY, Real fX )
{
	return ( Real ) atan2( ( Real ) fY, ( Real ) fX );
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Cosine( Real fValue )
{
	return (Real)cos( fValue );
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Sine( Real fValue )
{
	return (Real)sin( fValue );
}
// ---------------------------------------------------------------------------
template<class Real> Real Spark::Tangent( Real fValue )
{
	return (Real)tan( fValue );
}
// ---------------------------------------------------------------------------
inline bool Spark::IsPowerOfTwo( int iWidth, int iHeight )
{
	return ((iWidth&(iWidth-1))==0) &&((iHeight&(iHeight-1))==0);
}
// ---------------------------------------------------------------------------
