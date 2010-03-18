//******************************************************************************
inline Vector RayTracer::getLightDirection() const
{
	return m_kLightDirection;
}
//******************************************************************************
inline void RayTracer::setLightDirection(const Vector& rkLightDirection)
{
	m_kLightDirection = rkLightDirection;
}
//******************************************************************************
inline void RayTracer::setLightColor(const Color & rkColor)
{
	m_kLightColor = rkColor;
}
//******************************************************************************
inline Color RayTracer::getLightColor() const
{
	return m_kLightColor;
}
//******************************************************************************
inline Real RayTracer::getNormalEpsilon() const
{
	return m_fNormalEpsilon;
}
//******************************************************************************
inline void RayTracer::setNormalEpsilon(Real fNormalEpsilon)
{
	m_fNormalEpsilon = fNormalEpsilon;
}
//******************************************************************************
inline Real RayTracer::getRayEpsilon() const
{
	return m_fRayEpsilon;
}
//******************************************************************************
inline void RayTracer::setRayEpsilon(Real fRayEpsilon)
{
	m_fRayEpsilon = fRayEpsilon;
}
//******************************************************************************
inline Real RayTracer::getIsoLevel() const
{
	return m_fIsoLevel;
}
//******************************************************************************
inline void RayTracer::setIsoLevel(Real fIsoLevel)
{
	m_fIsoLevel = fIsoLevel;
}
//******************************************************************************
inline UInt RayTracer::getSamples() const
{
	return m_uiSamples;
}
//******************************************************************************
inline void RayTracer::setSamples(UInt uiSamples)
{
	m_uiSamples = uiSamples;
}
//******************************************************************************
inline UInt RayTracer::getRayHits() const
{
	return m_uiRayHits;
}
//******************************************************************************
inline void RayTracer::setBlur(bool bBlur)
{
	m_bBlur = bBlur;
}
//******************************************************************************
inline bool RayTracer::getBlur() const
{
	return m_bBlur;
}
//******************************************************************************
inline void RayTracer::setBaseColor(const Color & rkColor)
{
	m_kBaseColor = rkColor;
}
//******************************************************************************
inline Color RayTracer::getBaseColor() const
{
	return m_kBaseColor;
}
//******************************************************************************
inline void RayTracer::setBackground(const Color & rkColor)
{
	m_kBgColor = rkColor;
}
//******************************************************************************
inline Color RayTracer::getBackground() const
{
	return m_kBgColor;
}
//******************************************************************************
inline void RayTracer::setCamera(Camera* pkCamera)
{
	m_pkCamera = pkCamera;
}
//******************************************************************************
inline const Camera* RayTracer::getCamera() const
{
	return m_pkCamera;
}
//******************************************************************************
inline void RayTracer::setFunction(Function pvFunction)
{
	m_pvFunction = pvFunction;
}
//******************************************************************************
inline Real RayTracer::sample(Real fX, Real fY, Real fZ)
{
	if(m_pvFunction)
		return m_pvFunction(fX, fY, fZ);
	else
		return 0.0f;
}
//******************************************************************************
inline Real RayTracer::getAmbient() const
{
	return m_fAmbient;
}
//******************************************************************************
inline void RayTracer::setAmbient(Real fAmbient)
{
	m_fAmbient = fAmbient;
}
//******************************************************************************
inline Real RayTracer::getDiffuse() const
{
	return m_fDiffuse;
}
//******************************************************************************
inline void RayTracer::setDiffuse(Real fDiffuse)
{
	m_fDiffuse = fDiffuse;
}
//******************************************************************************
inline Real RayTracer::getSpecular() const
{
	return m_fSpecular;
}
//******************************************************************************
inline void RayTracer::setSpecular(Real fSpecular)
{
	m_fSpecular = fSpecular;
}
//******************************************************************************
inline Real RayTracer::getRoughness() const
{
	return m_fRoughness;
}
//******************************************************************************
inline void RayTracer::setRoughness(Real fRoughness)
{
	m_fRoughness = fRoughness;
}
//******************************************************************************

