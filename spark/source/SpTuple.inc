//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real>::SpTuple ()
{
	// For efficiency in construction of large arrays of vectors, the
	// default constructor does not initialize the tuple.
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real>::SpTuple (Real fValue)
{
	memset(m_afValues,fValue,N*sizeof(Real));
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real>::SpTuple (const Real* afValues, unsigned int uiN)
{
	if( uiN > N )
		uiN = N;
	else
		memset(m_afValues,0,N*sizeof(Real));

	memcpy(m_afValues,afValues,uiN*sizeof(Real));
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real>::SpTuple (const SpTuple& rkV)
{
	memcpy(m_afValues,rkV.m_afValues,N*sizeof(Real));
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
const Real* SpTuple<N,Real>::values() const
{
	return m_afValues;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
Real* SpTuple<N,Real>::values()
{
	return m_afValues;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
Real SpTuple<N,Real>::operator[] (unsigned int i) const
{
	assert( i < N );
	return m_afValues[i];
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
Real& SpTuple<N,Real>::operator[] (unsigned int i)
{
	assert( i < N );
	return m_afValues[i];
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real>& SpTuple<N,Real>::operator= (const SpTuple& rkV)
{
	memcpy(m_afValues,rkV.m_afValues,N*sizeof(Real));
	return *this;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
bool SpTuple<N,Real>::operator== (const SpTuple& rkV) const
{
	return memcmp(m_afValues,rkV.m_afValues,N*sizeof(Real)) == 0;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
bool SpTuple<N,Real>::operator!= (const SpTuple& rkV) const
{
	return memcmp(m_afValues,rkV.m_afValues,N*sizeof(Real)) != 0;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
int SpTuple<N,Real>::compare(const SpTuple& rkV) const
{
	for (int i = 0; i < N; i++)
	{
		unsigned int uiTest0 = *(unsigned int*)&m_afValues[i];
		unsigned int uiTest1 = *(unsigned int*)&rkV.m_afValues[i];
		if ( uiTest0 < uiTest1 )
			return -1;
		if ( uiTest0 > uiTest1 )
			return +1;
	}
	return 0;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
bool SpTuple<N,Real>::operator< (const SpTuple& rkV) const
{
	return compare(rkV) < 0;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
bool SpTuple<N,Real>::operator<= (const SpTuple& rkV) const
{
	return compare(rkV) <= 0;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
bool SpTuple<N,Real>::operator> (const SpTuple& rkV) const
{
	return compare(rkV) > 0;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
bool SpTuple<N,Real>::operator>= (const SpTuple& rkV) const
{
	return compare(rkV) >= 0;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real> SpTuple<N,Real>::operator+ (const SpTuple& rkV) const
{
	SpTuple<N,Real> kSum;
	for (int i = 0; i < N; i++)
		kSum.m_afValues[i] = m_afValues[i] + rkV.m_afValues[i];
	return kSum;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real> SpTuple<N,Real>::operator- (const SpTuple& rkV) const
{
	SpTuple<N,Real> kDiff;
	for (int i = 0; i < N; i++)
		kDiff.m_afValues[i] = m_afValues[i] - rkV.m_afValues[i];
	return kDiff;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real> SpTuple<N,Real>::operator+ (Real fScalar) const
{
	SpTuple<N,Real> kProd;
	for (int i = 0; i < N; i++)
		kProd.m_afValues[i] = fScalar+m_afValues[i];
	return kProd;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real> SpTuple<N,Real>::operator- (Real fScalar) const
{
	SpTuple<N,Real> kProd;
	for (int i = 0; i < N; i++)
		kProd.m_afValues[i] = fScalar-m_afValues[i];
	return kProd;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real> SpTuple<N,Real>::operator* (Real fScalar) const
{
	SpTuple<N,Real> kProd;
	for (int i = 0; i < N; i++)
		kProd.m_afValues[i] = fScalar*m_afValues[i];
	return kProd;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real> SpTuple<N,Real>::operator/ (Real fScalar) const
{
	SpTuple<N,Real> kQuot;
	int i;

	if ( fScalar != (Real)0.0 )
	{
		Real fInvScalar = ((Real)1.0)/fScalar;
		for (i = 0; i < N; i++)
			kQuot.m_afValues[i] = fInvScalar*m_afValues[i];
	}
	else
	{
		for (i = 0; i < N; i++)
			kQuot.m_afValues[i] = REAL_MAX;
	}

	return kQuot;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real> SpTuple<N,Real>::operator- () const
{
	SpTuple<N,Real> kNeg;
	for (int i = 0; i < N; i++)
		kNeg.m_afValues[i] = -m_afValues[i];
	return kNeg;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real> operator* (Real fScalar, const SpTuple<N,Real>& rkV)
{
	SpTuple<N,Real> kProd;
	for (int i = 0; i < N; i++)
		kProd[i] = fScalar*rkV[i];
	return kProd;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real>& SpTuple<N,Real>::operator+= (const SpTuple& rkV)
{
	for (int i = 0; i < N; i++)
		m_afValues[i] += rkV.m_afValues[i];
	return *this;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real>& SpTuple<N,Real>::operator-= (const SpTuple& rkV)
{
	for (int i = 0; i < N; i++)
		m_afValues[i] -= rkV.m_afValues[i];
	return *this;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real>& SpTuple<N,Real>::operator+= (Real fScalar)
{
	for (int i = 0; i < N; i++)
		m_afValues[i] += fScalar;
	return *this;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real>& SpTuple<N,Real>::operator-= (Real fScalar)
{
	for (int i = 0; i < N; i++)
		m_afValues[i] -= fScalar;
	return *this;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real>& SpTuple<N,Real>::operator*= (Real fScalar)
{
	for (int i = 0; i < N; i++)
		m_afValues[i] *= fScalar;
	return *this;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real>& SpTuple<N,Real>::operator/= (Real fScalar)
{
	int i;

	if ( fScalar != (Real)0.0 )
	{
		Real fInvScalar = ((Real)1.0)/fScalar;
		for (i = 0; i < N; i++)
			m_afValues[i] *= fInvScalar;
	}
	else
	{
		for (i = 0; i < N; i++)
			m_afValues[i] = REAL_MAX;
	}

	return *this;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
Real Spark::Length (const SpTuple<N,Real>& rkV)
{
	Real fSqrLen = (Real)0.0;
	for (int i = 0; i < N; i++)
		fSqrLen += rkV[i] * rkV[i];
	return (Real)sqrt(fSqrLen);
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
Real Spark::LengthSquared(const SpTuple<N,Real>& rkV)
{
	Real fSqrLen = (Real)0.0;
	for (int i = 0; i < N; i++)
		fSqrLen += rkV[i] * rkV[i];
	return fSqrLen;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
Real Spark::Dot(const SpTuple<N,Real>& rkA, const SpTuple<N,Real>& rkB)
{
	Real fDot = (Real)0.0;
	for (int i = 0; i < N; i++)
		fDot += rkA[i] * rkB[i];
	return fDot;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real> Spark::Normalize(const SpTuple<N,Real>& rkV)
{
	SpTuple<N, Real> kN(rkV);
	Real fLength = Length(rkV);
	int i;

	if ( fLength > SpMaths<Real>::EPSILON )
	{
		Real fInvLength = ((Real)1.0)/fLength;
		for (i = 0; i < N; i++)
			kN[i] *= fInvLength;
	}
	else
	{
		fLength = (Real)0.0;
		for (i = 0; i < N; i++)
			kN[i] = (Real)0.0;
	}

	return kN;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real> Spark::Clamp(const SpTuple<N,Real>& rkV, Real fMin, Real fMax)
{
	SpTuple<N,Real> kC( rkV );
	for (int i = 0; i < N; i++)
	{
		kC[i] = (kC[i] < fMin) ? fMin : ((kC[i] > fMax) ? fMax : kC[i]);
	}

	return kC;
}
//----------------------------------------------------------------------------
template <unsigned int N, class Real>
SpTuple<N,Real> Spark::Offset(const SpTuple<N,Real>& rkV, Real fOffset)
{
	SpTuple<N,Real> kC( rkV );
	for (int i = 0; i < N; i++)
	{
		kC[i] += fOffset;
	}

	return kC;
}
//----------------------------------------------------------------------------
template <class Real>
SpTuple3<Real> Spark::Normalize(const SpTuple3<Real>& rkV)
{
	SpTuple3<Real> kN = rkV;
	Real fDistance = Sqrt(kN[0]*kN[0]+kN[1]*kN[1]+kN[2]*kN[2]);
	if (fDistance != 0.0)
	{
		kN[0] /= fDistance;
		kN[1] /= fDistance;
		kN[2] /= fDistance;
	}
	else
	{
		kN[0] = kN[1] = kN[2] = 0;
	}
	return kN;
}
//----------------------------------------------------------------------------
template <class Real>
SpTuple3<Real> Spark::NormalizedCross(
	const SpTuple3<Real>& rkV1, const SpTuple3<Real> & rkV2)
{
	SpTuple3<Real> kNC;

	kNC[0] = rkV1[1]*rkV2[2] - rkV1[2]*rkV2[1];
	kNC[1] = rkV1[2]*rkV2[0] - rkV1[0]*rkV2[2];
	kNC[2] = rkV1[0]*rkV2[1] - rkV1[1]*rkV2[0];
	return Normalize(kNC);
}
//----------------------------------------------------------------------------
template <class Real>
SpTuple3<Real> Spark::Cross(
	const SpTuple3<Real>& rkV1, const SpTuple3<Real> & rkV2)
{
	SpTuple3<Real> kNC;

	kNC[0] = rkV1[1]*rkV2[2] - rkV1[2]*rkV2[1];
	kNC[1] = rkV1[2]*rkV2[0] - rkV1[0]*rkV2[2];
	kNC[2] = rkV1[0]*rkV2[1] - rkV1[1]*rkV2[0];
	return kNC;
}
//----------------------------------------------------------------------------
template <class Real>
SpTuple4<Real> Spark::Normalize(const SpTuple4<Real>& rkV)
{
	SpTuple4<Real> kN = rkV;
	Real fDistance = Sqrt(kN[0]*kN[0]+kN[1]*kN[1]+kN[2]*kN[2]);
	if (fDistance != 0.0)
	{
		kN[0] /= fDistance;
		kN[1] /= fDistance;
		kN[2] /= fDistance;
	}
	else
	{
		kN[0] = kN[1] = kN[2] = 0;
	}
	kN[3] = 1.0;
	return kN;
}
//----------------------------------------------------------------------------
template <class Real>
SpTuple4<Real> Spark::NormalizedCross(
	const SpTuple4<Real>& rkV1, const SpTuple4<Real> & rkV2)
{
	SpTuple4<Real> kNC;

	kNC[0] = rkV1[1]*rkV2[2] - rkV1[2]*rkV2[1];
	kNC[1] = rkV1[2]*rkV2[0] - rkV1[0]*rkV2[2];
	kNC[2] = rkV1[0]*rkV2[1] - rkV1[1]*rkV2[0];
	kNC[3] = 1.0;
	return Normalize(kNC);
}
//----------------------------------------------------------------------------
template <class Real>
SpTuple4<Real> Spark::Cross(
	const SpTuple4<Real>& rkV1, const SpTuple4<Real> & rkV2)
{
	SpTuple4<Real> kNC;

	kNC[0] = rkV1[1]*rkV2[2] - rkV1[2]*rkV2[1];
	kNC[1] = rkV1[2]*rkV2[0] - rkV1[0]*rkV2[2];
	kNC[2] = rkV1[0]*rkV2[1] - rkV1[1]*rkV2[0];
	kNC[3] = 1.0;
	return kNC;
}
//----------------------------------------------------------------------------
