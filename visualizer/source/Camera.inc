//******************************************************************************
inline Vector Camera::getPosition() const
{
    return m_kPosition;	
}
//******************************************************************************
inline void Camera::setPosition(const Vector& rkPosition)
{
	m_kPosition = rkPosition;
}
//******************************************************************************
inline Vector Camera::getDirection() const
{
    return m_kDirection;	
}
//******************************************************************************
inline void Camera::setDirection(const Vector& rkDirection)
{
	m_kDirection = rkDirection;
}
//******************************************************************************
inline Vector Camera::getUp() const
{
    return m_kUp;	
}
//******************************************************************************
inline void Camera::setUp(const Vector& rkUp)
{
	m_kUp = rkUp;
}
//******************************************************************************
inline Vector Camera::getRight() const
{
    return m_kRight;	
}
//******************************************************************************
inline void Camera::setRight(const Vector& rkRight)
{
	m_kRight = rkRight;
}
//******************************************************************************
inline Real Camera::getNear() const
{
    return m_fNear;	
}
//******************************************************************************
inline void Camera::setNear(Real fNear)
{
	m_fNear = fNear;
}
//******************************************************************************
inline Real Camera::getFar() const
{
    return m_fFar;	
}
//******************************************************************************
inline void Camera::setFar(Real fFar)
{
	m_fFar = fFar;
}
//******************************************************************************
inline Real Camera::getHalfWidth() const
{
    return m_fHalfWidth;	
}
//******************************************************************************
inline void Camera::setHalfWidth(Real fHalfWidth)
{
	m_fHalfWidth = fHalfWidth;
}
//******************************************************************************
inline Real Camera::getHalfHeight() const
{
    return m_fHalfHeight;	
}
//******************************************************************************
inline void Camera::setHalfHeight(Real fHalfHeight)
{
	m_fHalfHeight = fHalfHeight;
}
//******************************************************************************
inline UInt Camera::getImageWidth() const
{
	if(m_pkImage)
		return m_pkImage->getWidth();
	else 
		return 0;
}
//******************************************************************************
inline UInt Camera::getImageHeight() const
{
	if(m_pkImage)
		return m_pkImage->getHeight();
	else 
		return 0;
}
//******************************************************************************
inline UInt Camera::getImageChannels() const
{
	if(m_pkImage)
		return m_pkImage->getChannels();
	else 
		return 0;
}
//******************************************************************************
inline void Camera::setImage(Image* pkImage)
{
    m_pkImage = pkImage;
}
//******************************************************************************
inline const Image* Camera::getImage() const
{
    return m_pkImage;
}
//******************************************************************************
inline Image* Camera::getImage()
{
    return m_pkImage;
}
//******************************************************************************
inline void Camera::setBackground(const Color & rkColor)
{
	m_kBgColor = rkColor;
}
//******************************************************************************
inline Color Camera::getBackground() const
{
	return m_kBgColor;
}
//******************************************************************************
inline Vector Camera::getStartRayDir() const
{
	return m_kStartRay;
}
//******************************************************************************
inline Real Camera::getPixelWidth() const
{
	return m_fPixelWidth;
}
//******************************************************************************
inline Real Camera::getPixelHeight() const
{
	return m_fPixelHeight;
}
//******************************************************************************

