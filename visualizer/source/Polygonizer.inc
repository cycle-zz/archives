//******************************************************************************
inline void Polygonizer::setFunction( Function pvFunction )
{
	m_pvFunction = pvFunction;
}
//******************************************************************************
inline void Polygonizer::setInverseNormals(bool bInverseNormals)
{
	m_bInverseNormals = bInverseNormals;
}
//******************************************************************************
inline bool Polygonizer::getInverseNormals()
{
	return m_bInverseNormals;
}
//******************************************************************************
inline void Polygonizer::setCellCount( Int iCellCount )
{
	m_iCellCount = iCellCount;
	m_fDelta = 1.0 / m_iCellCount;
}
//******************************************************************************
inline Int Polygonizer::getCellCount()
{
	return m_iCellCount;
}
//******************************************************************************
inline void Polygonizer::setIsoLevel( Real fIsoLevel )
{
	m_fIsoLevel = fIsoLevel;
}
//******************************************************************************
inline Real Polygonizer::getIsoLevel()
{
	return m_fIsoLevel;
}
//******************************************************************************
inline Real Polygonizer::getIntersect(
	Real fV1, Real fV2, Real fLevel)
{
	Real fDelta = fV2 - fV1;

	if (fDelta == 0.0)
		return 0.5;
	else
		return (fLevel - fV1) / fDelta;
}
//******************************************************************************
inline void Polygonizer::getColor(
	Color &rkColor, Vector &rkPos, Vector &rkNormal)
{
	// not using color, so cast it to void to avoid compiler warnings
	(void) rkColor;

	// get the current normal coordinates
	Real fX = rkNormal.x();
	Real fY = rkNormal.y();
	Real fZ = rkNormal.z();

	// assign the rgb color values
	rkColor.r() = (fX > 0.0 ? fX : 0.0) +
				  (fY < 0.0 ? -0.5 * fY : 0.0) +
				  (fZ < 0.0 ? -0.5 * fZ : 0.0);

	rkColor.g() = (fY > 0.0 ? fY : 0.0) +
				  (fZ < 0.0 ? -0.5 * fZ : 0.0) +
				  (fX < 0.0 ? -0.5 * fX : 0.0);

	rkColor.b() = (fZ > 0.0 ? fZ : 0.0) +
				  (fX < 0.0 ? -0.5 * fX : 0.0) +
				  (fY < 0.0 ? -0.5 * fY : 0.0);
}
//******************************************************************************
inline void Polygonizer::setOffset( Real fX, Real fY, Real fZ )
{
	m_kOffset.x() = fX;
	m_kOffset.y() = fY;
	m_kOffset.z() = fZ;
}
//******************************************************************************
inline void Polygonizer::getOffset(Real& fX, Real& fY, Real& fZ )
{
	fX = m_kOffset.x();
	fY = m_kOffset.y();
	fZ = m_kOffset.z();
}
//******************************************************************************
inline void Polygonizer::setEpsilon(Real fEpsilon)
{
	m_fEpsilon = fEpsilon;
}
//******************************************************************************
inline Real Polygonizer::getEpsilon()
{
	return m_fEpsilon;
}
//******************************************************************************
inline void Polygonizer::setScale(Real fScale)
{
	m_fScale = fScale;
}
//******************************************************************************
inline Real Polygonizer::getScale()
{
	return m_fScale;
}
//******************************************************************************
inline Real Polygonizer::sample(Real fX, Real fY, Real fZ)
{
	return m_pvFunction(m_fScale * (fX + m_kOffset.x()),
						m_fScale * (fY + m_kOffset.y()),
						m_fScale * (fZ + m_kOffset.z()));
}
//******************************************************************************

