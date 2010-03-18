//******************************************************************************
inline Vector Hypertexture::getLightDirection() const
{
	return m_kLightDirection;
}
//******************************************************************************
inline void Hypertexture::setLightDirection(const Vector& rkLightDirection)
{
	m_kLightDirection = rkLightDirection;
}
//******************************************************************************
inline Color Hypertexture::getLightColor() const
{
	return m_kLightColor;
}
//******************************************************************************
inline void Hypertexture::setLightColor(const Color& rkLightColor)
{
	m_kLightColor = rkLightColor;
}
//******************************************************************************
inline Real Hypertexture::getDensityScale() const
{
	return m_fDensityScale;
}
//******************************************************************************
inline void Hypertexture::setDensityScale(Real fDensityScale)
{
	m_fDensityScale = fDensityScale;
}
//******************************************************************************
inline Real Hypertexture::getDensityThreshold() const
{
	return m_fDensityThreshold;
}
//******************************************************************************
inline void Hypertexture::setDensityThreshold(Real fDensityThreshold)
{
	m_fDensityThreshold = fDensityThreshold;
}
//******************************************************************************
inline Real Hypertexture::getOpacityThreshold() const
{
	return m_fOpacityThreshold;
}
//******************************************************************************
inline void Hypertexture::setOpacityThreshold(Real fOpacityThreshold)
{
	m_fOpacityThreshold = fOpacityThreshold;
}
//******************************************************************************
inline UInt Hypertexture::getRayHits() const
{
	return m_uiRayHits;
}
//******************************************************************************
inline UInt Hypertexture::getSamples() const
{
	return m_uiSamples;
}
//******************************************************************************
inline void Hypertexture::setBackground(const Color & rkColor)
{
	m_kBgColor = rkColor;
}
//******************************************************************************
inline Color Hypertexture::getBackground() const
{
	return m_kBgColor;
}
//******************************************************************************
inline void Hypertexture::setCamera(Camera* pkCamera)
{
	m_pkCamera = pkCamera;
}
//******************************************************************************
inline const Camera* Hypertexture::getCamera() const
{
	return m_pkCamera;
}
//******************************************************************************
inline void Hypertexture::setDensityFunction(DensityFn pvDensityFn)
{
	m_pvDensityFn = pvDensityFn;
	m_pvFilteredDensityFn = NULL;
}
//******************************************************************************
inline void Hypertexture::setColorFunction(ColorFn pvColorFn)
{
	m_pvFilteredColorFn = NULL;
	m_pvColorFn = pvColorFn;
}
//******************************************************************************
inline void Hypertexture::setShadingFunction(ShadeFn pvShadeFn)
{
	m_pvShadeFn = pvShadeFn;
}
//******************************************************************************
inline void Hypertexture::setFilteredDensityFunction(FilteredDensityFn pvDensityFn)
{
	m_pvFilteredDensityFn = pvDensityFn;
	m_pvDensityFn = NULL;
}
//******************************************************************************
inline void Hypertexture::setFilteredColorFunction(FilteredColorFn pvColorFn)
{
	m_pvFilteredColorFn = pvColorFn;
	m_pvColorFn = NULL;
}
//******************************************************************************
inline UInt Hypertexture::getMaxSamples() const
{
	return m_uiMaxSamples;
}
//******************************************************************************
inline void Hypertexture::setMaxSamples(UInt uiMaxSamples)
{
	m_uiMaxSamples = uiMaxSamples;
}
//******************************************************************************
inline Real Hypertexture::getRayEpsilon() const
{
	return m_fRayEpsilon;
}
//******************************************************************************
inline void Hypertexture::setRayEpsilon(Real fRayEpsilon)
{
	m_fRayEpsilon = fRayEpsilon;
}
//******************************************************************************
inline Real Hypertexture::getShadowFarClip() const
{
	return m_fShadowFarClip;
}
//******************************************************************************
inline void Hypertexture::setShadowFarClip(Real fShadowFarClip)
{
	m_fShadowFarClip = fShadowFarClip;
}
//******************************************************************************
inline Real Hypertexture::getShadowDepthThreshold() const
{
	return m_fShadowDepthThreshold;
}
//******************************************************************************
inline void Hypertexture::setShadowDepthThreshold(Real fShadowDepthThreshold)
{
	m_fShadowDepthThreshold = fShadowDepthThreshold;
}
//******************************************************************************
inline Real Hypertexture::getShadowStepScale() const
{
	return m_fShadowStepScale;
}
//******************************************************************************
inline void Hypertexture::setShadowStepScale(Real fShadowStepScale)
{
	m_fShadowStepScale = fShadowStepScale;
}
//******************************************************************************
inline Real Hypertexture::getStepSize() const
{
	return m_fStepSize;
}
//******************************************************************************
inline void Hypertexture::setStepSize(Real fStepSize)
{
	m_fStepSize = fStepSize;
}
//******************************************************************************
inline Real Hypertexture::getAmbient() const
{
	return m_fAmbient;
}
//******************************************************************************
inline void Hypertexture::setAmbient(Real fAmbient)
{
	m_fAmbient = fAmbient;
}
//******************************************************************************
inline Real Hypertexture::getDiffuse() const
{
	return m_fDiffuse;
}
//******************************************************************************
inline void Hypertexture::setDiffuse(Real fDiffuse)
{
	m_fDiffuse = fDiffuse;
}
//******************************************************************************
inline Real Hypertexture::getSpecular() const
{
	return m_fSpecular;
}
//******************************************************************************
inline void Hypertexture::setSpecular(Real fSpecular)
{
	m_fSpecular = fSpecular;
}
//******************************************************************************
inline Real Hypertexture::getRoughness() const
{
	return m_fRoughness;
}
//******************************************************************************
inline void Hypertexture::setRoughness(Real fRoughness)
{
	m_fRoughness = fRoughness;
}
//******************************************************************************
inline void Hypertexture::setKeepInView( bool bKeepInView )
{
	m_bKeepInView = bKeepInView;
}
//******************************************************************************
inline bool Hypertexture::getKeepInView()
{
	return m_bKeepInView;
}
//******************************************************************************
inline void Hypertexture::setFadeOut( bool bFadeOut )
{
	m_bFadeOut = bFadeOut;
}
//******************************************************************************
inline bool Hypertexture::getFadeOut()
{
	return m_bFadeOut;
}
//******************************************************************************
inline void Hypertexture::setScale(Real fScale)
{
	m_fScale = fScale;
}
//******************************************************************************
inline Real Hypertexture::getScale()
{
	return m_fScale;
}
//******************************************************************************
