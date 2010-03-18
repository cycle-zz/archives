#include "Camera.h"
#include "Maths.h"
#include <memory>

using namespace dg;
//******************************************************************************
Camera::Camera(const Vector& rkPos, const Vector& rkDir, 
	const Vector& rkUp, const Vector& rkRight, Real fNear, Real fFar, 
	Real fHalfWidth, Real fHalfHeight, Image* pkImage)
    : m_kPosition(rkPos),
      m_kDirection(rkDir),
      m_kUp(rkUp),
      m_kRight(rkRight),
	  m_fNear(fNear),
	  m_fFar(fFar),
	  m_fHalfWidth(fHalfWidth),
	  m_fHalfHeight(fHalfHeight),
	  m_fPixelWidth(0),
	  m_fPixelHeight(0),
	  m_pkImage(pkImage)
{
	// EMPTY!
}
//******************************************************************************
Camera::~Camera ()
{

}
//******************************************************************************
void Camera::setHorizontalFov(Real fHorizFov)
{
	m_fHalfHeight = 0.5 * Tangent( Radians( fHorizFov ) );
}
//******************************************************************************
inline Real Camera::getHorizontalFov() const
{
	return Degrees( ArcTangent( m_fHalfWidth*(1.0/m_fNear)) );
}
//******************************************************************************
void Camera::setVerticalFov(Real fVertFov)
{
	m_fHalfHeight = 0.5 * Tangent( Radians( fVertFov ) );
}
//******************************************************************************
inline Real Camera::getVerticalFov() const
{
	return Degrees( ArcTangent( m_fHalfHeight*(1.0/m_fNear)) );
}
//******************************************************************************
Vector Camera::getRayDir(UInt uiX, UInt uiY) const
{
/*	
	static UInt uiLastX = 0;
	static UInt uiLastY = 0;
	static Real fLastFX = 0;
	static Real fLastFY = 0;
	
	Real fX = 0;
	if(uiLastX != 0 && uiX == uiLastX)
		fX = fLastFX;
	else
		fX = m_fHalfWidth * (-1.0f + m_fMultiplyX * uiX);

	uiLastX = uiX;
	fLastFX = fX;
	
	Real fY = 0;
	if(uiLastY != 0 && uiY == uiLastY)
		fY = fLastFY;
	else
		fY = m_fHalfHeight * (-1.0f + m_fMultiplyY * uiY);
	
	uiLastY = uiY;
	fLastFY = fY;
	
    // compute ray direction starting from near clip plane
    Vector kRayDir = m_fNear * m_kDirection + fX * m_kRight + fY * m_kUp;
	kRayDir.normalize();

	return( kRayDir );
*/
	
	Vector kRayDir(
		m_kStartRay.x() + uiX * m_fPixelWidth * 
			m_kRight.x() + uiY * m_fPixelHeight * m_kUp.x(),
		m_kStartRay.y() + uiX * m_fPixelWidth * 
			m_kRight.y() + uiY * m_fPixelHeight * m_kUp.y(),
		m_kStartRay.z() + uiX * m_fPixelWidth * 
			m_kRight.z() + uiY * m_fPixelHeight * m_kUp.z()
	);

	kRayDir.normalize();
	return( kRayDir );
}
//******************************************************************************
void Camera::setup()
{
	if(!m_pkImage)
		return;
	
	Real fImageWidth = m_pkImage->width();	
	Real fImageHeight = m_pkImage->height();

    m_fMultiplyX = 2.0 / (fImageWidth - 1.0f);
    m_fMultiplyY = 2.0 / (fImageHeight - 1.0f);

	m_fPixelWidth = 2.0 * m_fHalfWidth / fImageWidth;
	m_fPixelHeight = 2.0 * m_fHalfHeight / fImageHeight;
	
	m_kStartRay.x() = m_kDirection.x() -
					  0.5 * fImageWidth * m_fPixelWidth * m_kRight.x() -
					  0.5 * fImageHeight * m_fPixelHeight * m_kUp.x();
				   
    m_kStartRay.y() = m_kDirection.y() - 
                      0.5 * fImageWidth * m_fPixelWidth * m_kRight.y() -
                      0.5 * fImageHeight * m_fPixelHeight * m_kUp.y();

	m_kStartRay.z() = m_kDirection.z() - 
                      0.5 * fImageWidth * m_fPixelWidth * m_kRight.z() -
                      0.5 * fImageHeight * m_fPixelHeight * m_kUp.z();

//	 relates Noise() to Nyquist limit 
//	m_fSampleScale = -Log2(Tangent(DEGTORAD(0.5*camera->hfov / camera->hres))) - 3.0;	

}
//******************************************************************************

