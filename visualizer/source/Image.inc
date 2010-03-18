//******************************************************************************
inline const Real* Image::operator[](UInt uiIndex) const
{
	if(uiIndex < m_uiResolution)
		return m_afPixels + uiIndex;
	else
		return NULL;
}
//******************************************************************************
inline Real* Image::operator[](UInt uiIndex)
{
	if(uiIndex < m_uiResolution)
		return m_afPixels + uiIndex;
	else
		return NULL;
}
//******************************************************************************
inline const Real* Image::operator()(UInt uiX, UInt uiY, UInt uiC) const
{
	UInt uiIndex = index(uiX, uiY, uiC); 
	if(uiIndex < m_uiResolution)
		return m_afPixels + uiIndex;
	else
		return NULL;
}
//******************************************************************************
inline Real* Image::operator()(UInt uiX, UInt uiY, UInt uiC)
{
	UInt uiIndex = index(uiX, uiY, uiC); 
	if(uiIndex < m_uiResolution)
		return m_afPixels + uiIndex;
	else
		return NULL;
}
//******************************************************************************
inline Color Image::operator()(UInt uiX, UInt uiY) const
{
	Color kColor;
	UInt uiIndex = index(uiX, uiY, 0); 
	if( uiIndex < m_uiResolution)
	{
		for(UInt uiC = 0; uiC < m_uiChannels; uiC++)
			kColor[uiC] = m_afPixels[ index(uiX, uiY, uiC) ];
	}
	
	return kColor;
}
//******************************************************************************
inline UInt Image::index(UInt uiX, UInt uiY, UInt uiC) const
{
	return uiX * m_uiChannels + uiY * m_uiWidth * m_uiChannels + uiC;
}
//******************************************************************************
inline UInt Image::width() const
{
	return m_uiWidth;
}
//******************************************************************************
inline UInt Image::height() const
{
	return m_uiHeight;
}
//******************************************************************************
inline UInt Image::channels() const
{
	return m_uiChannels;
}
//******************************************************************************
inline const Real* Image::pixels() const
{
	return m_afPixels;
}
//******************************************************************************
inline Real* Image::pixels()
{
	return m_afPixels;	
}
//******************************************************************************
inline UInt Image::getWidth() const
{
	return m_uiWidth;
}
//******************************************************************************
inline UInt Image::getHeight() const
{
	return m_uiHeight;
}
//******************************************************************************
inline UInt Image::getChannels() const
{
	return m_uiChannels;
}
//******************************************************************************
inline const Real* Image::getPixels() const
{
	return m_afPixels;
}
//******************************************************************************
inline Real* Image::getPixels()
{
	return m_afPixels;
}
//******************************************************************************//******************************************************************************
inline Color Image::getColor(UInt uiX, UInt uiY) const
{
	Color kColor;
	UInt uiIndex = index(uiX, uiY, 0); 
	if( uiIndex < m_uiResolution)
	{
		for(UInt uiC = 0; uiC < m_uiChannels; uiC++)
			kColor[uiC] = m_afPixels[ index(uiX, uiY, uiC) ];
	}
	
	return kColor;
}
//******************************************************************************//******************************************************************************
inline void Image::setColor(UInt uiX, UInt uiY, const Color& rkColor )
{
	UInt uiIndex = index(uiX, uiY, 0); 
	if( uiIndex < m_uiResolution)
	{
		for(UInt uiC = 0; uiC < m_uiChannels; uiC++)
			m_afPixels[ index(uiX, uiY, uiC) ] = rkColor[uiC];
	}
}
//******************************************************************************//******************************************************************************
inline Color Image::getClearColor() const
{
	return m_kClearColor;
}
//******************************************************************************//******************************************************************************
inline void Image::setClearColor(const Color& rkColor )
{
	m_kClearColor = rkColor;
}
//******************************************************************************//******************************************************************************

