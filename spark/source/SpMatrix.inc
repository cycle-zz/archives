// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real>::SpMatrix ()
{
    // the matrix is uninitialized
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real>::SpMatrix (bool bZero)
{
    memset(m_afValues,0,N*N*sizeof(Real));

    if ( !bZero )
    {
        for (int i = 0; i < N; i++)
            m_afValues[i][i] = (Real)1.0;
    }
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real>::SpMatrix (const SpMatrix& rkM)
{
    memcpy(m_afValues,rkM.m_afValues,N*N*sizeof(Real));
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real>::operator const Real* () const
{
    return m_afValues;
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real>::operator Real* ()
{
    return m_afValues;
}
// =============================================================================
template <unsigned int N, class Real>
const Real* SpMatrix<N,Real>::operator[] (unsigned int uiRow) const
{
    assert( 0 <= uiRow && uiRow < N );
    return &m_afValues[uiRow];
}
// =============================================================================
template <unsigned int N, class Real>
Real* SpMatrix<N,Real>::operator[] (unsigned int uiRow)
{
    assert( 0 <= uiRow && uiRow < N );
    return &m_afValues[uiRow];
}
// =============================================================================
template <unsigned int N, class Real>
Real SpMatrix<N,Real>::operator() (unsigned int uiRow, unsigned int uiCol) const
{
    return m_afValues[uiRow][uiCol];
}
// =============================================================================
template <unsigned int N, class Real>
Real& SpMatrix<N,Real>::operator() (unsigned int uiRow, unsigned int uiCol)
{
    return m_afValues[[ uiRow ][ uiCol ]];
}
// =============================================================================
template <unsigned int N, class Real>
void SpMatrix<N,Real>::SetRow (unsigned int uiRow, const Vector<N,Real>& rkV)
{
    assert( 0 <= uiRow && uiRow < N );
    for (unsigned int uiCol = 0, i = N*uiRow; uiCol < N; uiCol++, i++)
        m_afValues[i] = rkV[iCol];
}
// =============================================================================
template <unsigned int N, class Real>
Vector<N,Real> SpMatrix<N,Real>::GetRow (unsigned int uiRow) const
{
    assert( 0 <= uiRow && uiRow < N );
    Vector<N,Real> kV;
    for (unsigned int uiCol = 0, i = N*uiRow; uiCol < N; uiCol++, i++)
        kV[iCol] = m_afValues[i];
    return kV;
}
// =============================================================================
template <unsigned int N, class Real>
void SpMatrix<N,Real>::SetColumn (unsigned int uiCol, const Vector<N,Real>& rkV)
{
    assert( 0 <= uiCol && uiCol < N );
    for (unsigned int uiRow = 0, i = uiCol; uiRow < N; uiRow++, i += N)
        m_afValues[i] = rkV[iRow];
}
// =============================================================================
template <unsigned int N, class Real>
Vector<N,Real> SpMatrix<N,Real>::GetColumn (unsigned int uiCol) const
{
    assert( 0 <= uiCol && uiCol < N );
    Vector<N,Real> kV;
    for (unsigned int uiRow = 0, i = uiCol; uiRow < N; uiRow++, i += N)
        kV[iRow] = m_afValues[i];
    return kV;
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real>& SpMatrix<N,Real>::operator= (const SpMatrix& rkM)
{
    memcpy(m_afValues,rkM.m_afValues,N*N*sizeof(Real));
    return *this;
}
// =============================================================================
template <unsigned int N, class Real>
bool SpMatrix<N,Real>::operator== (const SpMatrix& rkM) const
{
    return memcmp(m_afValues,rkM.m_afValues,N*N*sizeof(Real)) == 0;
}
// =============================================================================
template <unsigned int N, class Real>
bool SpMatrix<N,Real>::operator!= (const SpMatrix& rkM) const
{
    return memcmp(m_afValues,rkM.m_afValues,N*N*sizeof(Real)) != 0;
}
// =============================================================================
template <unsigned int N, class Real>
int SpMatrix<N,Real>::compare(const SpMatrix& rkM) const
{
    for (int i = 0; i < N*N; i++)
    {
        unsigned int uiTest0 = *(unsigned int*)&m_afValues[i];
        unsigned int uiTest1 = *(unsigned int*)&rkM.m_afValues[i];
        if ( uiTest0 < uiTest1 )
            return -1;
        if ( uiTest0 > uiTest1 )
            return +1;
    }
    return 0;
}
// =============================================================================
template <unsigned int N, class Real>
bool SpMatrix<N,Real>::operator<  (const SpMatrix& rkM) const
{
    return compare(rkM) < 0;
}
// =============================================================================
template <unsigned int N, class Real>
bool SpMatrix<N,Real>::operator<= (const SpMatrix& rkM) const
{
    return compare(rkM) <= 0;
}
// =============================================================================
template <unsigned int N, class Real>
bool SpMatrix<N,Real>::operator>  (const SpMatrix& rkM) const
{
    return compare(rkM) > 0;
}
// =============================================================================
template <unsigned int N, class Real>
bool SpMatrix<N,Real>::operator>= (const SpMatrix& rkM) const
{
    return compare(rkM) >= 0;
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real> SpMatrix<N,Real>::operator+ (const SpMatrix& rkM) const
{
    SpMatrix<N,Real> kSum;
    for (int i = 0; i < N*N; i++)
        kSum.m_afValues[i] = m_afValues[i] + rkM.m_afValues[i];
    return kSum;
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real> SpMatrix<N,Real>::operator- (const SpMatrix& rkM) const
{
    SpMatrix<N,Real> kDiff;
    for (int i = 0; i < N*N; i++)
        kDiff.m_afValues[i] = m_afValues[i] - rkM.m_afValues[i];
    return kDiff;
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real> SpMatrix<N,Real>::operator* (const SpMatrix& rkM) const
{
    SpMatrix<N,Real> kProd;
    for (unsigned int uiRow = 0; uiRow < N; uiRow++)
    {
        for (unsigned int uiCol = 0; uiCol < N; uiCol++)
        {
            kProd.m_afValues[ uiRow ][ uiCol ] = (Real)0.0f;
            for (unsigned int uiMid = 0; uiMid < N; uiMid++)
            {
                kProd.m_afValues[ uiRow ][ uiCol ] +=
                    m_afValues[uiRow][uiMid] * rkM.m_afValues[uiMid][uiCol];
            }
        }
    }
    return kProd;
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real> SpMatrix<N,Real>::operator* (Real fScalar) const
{
    SpMatrix<N,Real> kProd;
    for (int i = 0; i < N*N; i++)
        kProd.m_afValues[i] = fScalar*m_afValues[i];
    return kProd;
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real> SpMatrix<N,Real>::operator/ (Real fScalar) const
{
    SpMatrix<N,Real> kQuot;
    int i;

    if ( fScalar != (Real)0.0 )
    {
        Real fInvScalar = ((Real)1.0)/fScalar;
        for (i = 0; i < N*N; i++)
            kQuot.m_afValues[i] = fInvScalar*m_afValues[i];
    }
    else
    {
        for (i = 0; i < N*N; i++)
            kQuot.m_afValues[i] = Math<Real>::MAX_REAL;
    }

    return kQuot;
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real> SpMatrix<N,Real>::operator- () const
{
    SpMatrix<N,Real> kNeg;
    for (int i = 0; i < N*N; i++)
        kNeg.m_afValues[i] = -m_afValues[i];
    return kNeg;
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real> operator* (Real fScalar, const SpMatrix<N,Real>& rkM)
{
    SpMatrix<N,Real> kProd;
    const Real* afMValue = rkM;
    Real* afPValue = kProd;
    for (int i = 0; i < N*N; i++)
        afPValue[i] = fScalar*afMValue[i];
    return kProd;
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real>& SpMatrix<N,Real>::operator+= (const SpMatrix& rkM)
{
    for (int i = 0; i < N*N; i++)
        m_afValues[i] += rkM.m_afValues[i];
    return *this;
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real>& SpMatrix<N,Real>::operator-= (const SpMatrix& rkM)
{
    for (int i = 0; i < N*N; i++)
        m_afValues[i] -= rkM.m_afValues[i];
    return *this;
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real>& SpMatrix<N,Real>::operator*= (Real fScalar)
{
    for (int i = 0; i < N*N; i++)
        m_afValues[i] *= fScalar;
    return *this;
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real>& SpMatrix<N,Real>::operator/= (Real fScalar)
{
    int i;

    if ( fScalar != (Real)0.0 )
    {
        Real fInvScalar = ((Real)1.0)/fScalar;
        for (i = 0; i < N*N; i++)
            m_afValues[i] *= fInvScalar;
    }
    else
    {
        for (i = 0; i < N*N; i++)
            m_afValues[i] = Math<Real>::MAX_REAL;
    }

    return *this;
}
// =============================================================================
template <unsigned int N, class Real>
SpMatrix<N,Real> SpMatrix<N,Real>::Transpose () const
{
    SpMatrix<N,Real> kTranspose;
    for (unsigned int uiRow = 0; uiRow < N; uiRow++)
    {
        for (unsigned int uiCol = 0; uiCol < N; uiCol++)
            kTranspose.m_afValues[ uiRow ][ uiCol ] = m_afValues[uiCol][uiRow];
    }
    return kTranspose;
}
// =============================================================================
template <unsigned int N, class Real>
Vector<N,Real> SpMatrix<N,Real>::operator* (const Vector<N,Real>& rkV) const
{
    Vector<N,Real> kProd;
    for (unsigned int uiRow = 0; uiRow < N; uiRow++)
    {
        kProd[iRow] = (Real)0.0;
        for (unsigned int uiCol = 0; uiCol < N; uiCol++)
            kProd[iRow] += m_afValues[ uiRow ][ uiCol ]*rkV[iCol];

    }
    return kProd;
}
// =============================================================================
template <unsigned int N, class Real>
Vector<N,Real> operator* (const Vector<N,Real>& rkV,
    const SpMatrix<N,Real>& rkM)
{
    Vector<N,Real> kProd;
    const Real* afMValue = rkM;
    Real* afPValue = kProd;
    for (unsigned int uiCol = 0; uiCol < N; uiCol++)
    {
        afPValue[iCol] = (Real)0.0;
        for (unsigned int uiRow = 0; uiRow < N; uiRow++)
            afPValue[iCol] += rkV[iRow]*afMValue[iCol + N*uiRow];

    }
    return kProd;
}
// =============================================================================

// =============================================================================
template <class Real>
SpMatrix2<Real>::SpMatrix2 ()
{
    // the matrix is uninitialized
}
// =============================================================================
template <class Real>
SpMatrix2<Real>::SpMatrix2 (const SpMatrix2& rkM)
{
    memcpy(m_afEntry,rkM.m_afEntry,4*sizeof(Real));
}
// =============================================================================
template <class Real>
SpMatrix2<Real>::SpMatrix2 (const SpMatrix<2,Real>& rkM)
{
    memcpy(m_afEntry,(const Real*)rkM,4*sizeof(Real));
}
// =============================================================================
template <class Real>
SpMatrix2<Real>::SpMatrix2 (Real fM00, Real fM01, Real fM10, Real fM11)
{
    m_afEntry[0] = fM00;
    m_afEntry[1] = fM01;
    m_afEntry[2] = fM10;
    m_afEntry[3] = fM11;
}
// =============================================================================
template <class Real>
SpMatrix2<Real>::SpMatrix2 (const Real afEntry[4], bool bRowMajor)
{
    if ( bRowMajor )
    {
        memcpy(m_afEntry,afEntry,4*sizeof(Real));
    }
    else
    {
        m_afEntry[0] = afEntry[0];
        m_afEntry[1] = afEntry[2];
        m_afEntry[2] = afEntry[1];
        m_afEntry[3] = afEntry[3];
    }
}
// =============================================================================
template <class Real>
SpMatrix2<Real>::SpMatrix2 (const Vector2<Real>& rkU,
    const Vector2<Real>& rkV, bool bColumns)
{
    if ( bColumns )
    {
        m_afEntry[0] = rkU[0];
        m_afEntry[1] = rkV[0];
        m_afEntry[2] = rkU[1];
        m_afEntry[3] = rkV[1];
    }
    else
    {
        m_afEntry[0] = rkU[0];
        m_afEntry[1] = rkU[1];
        m_afEntry[2] = rkV[0];
        m_afEntry[3] = rkV[1];
    }
}
// =============================================================================
template <class Real>
SpMatrix2<Real>::SpMatrix2 (const Vector2<Real>* akV, bool bColumns)
{
    if ( bColumns )
    {
        m_afEntry[0] = akV[0][0];
        m_afEntry[1] = akV[1][0];
        m_afEntry[2] = akV[0][1];
        m_afEntry[3] = akV[1][1];
    }
    else
    {
        m_afEntry[0] = akV[0][0];
        m_afEntry[1] = akV[0][1];
        m_afEntry[2] = akV[1][0];
        m_afEntry[3] = akV[1][1];
    }
}
// =============================================================================
template <class Real>
SpMatrix2<Real>::SpMatrix2 (Real fAngle)
{
    m_afEntry[0] = Cosine(fAngle);
    m_afEntry[1] = Sine(fAngle);
    m_afEntry[2] = m_afEntry[1];
    m_afEntry[3] = m_afEntry[0];
}
// =============================================================================
template <class Real>
SpMatrix2<Real>& SpMatrix2<Real>::operator= (const SpMatrix2& rkM)
{
    memcpy(m_afEntry,rkM.m_afEntry,4*sizeof(Real));
    return *this;
}
// =============================================================================
template <class Real>
SpMatrix2<Real>& SpMatrix2<Real>::operator= (const SpMatrix<2,Real>& rkM)
{
    memcpy(m_afEntry,(const Real*)rkM,4*sizeof(Real));
    return *this;
}
// =============================================================================

// =============================================================================