#include "RayTracer.h"
#include "Maths.h"
#include "Shading.h"
#include <memory>

using namespace dg;
//******************************************************************************
RayTracer::RayTracer(Function pvFunction, Camera* pkCamera)
	: 	m_kLightColor(1.0f, 1.0f, 1.0f),
		m_kBaseColor(1.0f, 1.0f, 1.0f, 1.0f)
{
	m_fNormalEpsilon = 0.01;
	m_fRayEpsilon = 1.0e-4f;
	m_fIsoLevel = 0.0f;
	m_bBlur = false;

	m_fAmbient = 0.127;
	m_fDiffuse = 1;
	m_fSpecular = 0.3;
	m_fRoughness = 0.1;

	m_pvFunction = pvFunction;
	m_pkCamera = pkCamera;
}
//******************************************************************************
RayTracer::~RayTracer ()
{
	// EMPTY!
}
//******************************************************************************
void RayTracer::render()
{
	if(!m_pvFunction || !m_pkCamera)
		return;

	// get the image from the camera
	Image* pkImage = m_pkCamera->getImage();
	if(!pkImage)
		return;

	render(0, pkImage->height());

	if ( m_bBlur )
		pkImage->blur();
}
//******************************************************************************
void RayTracer::render(UInt uiStartLine, UInt uiEndLine)
{
	if(!m_pvFunction || !m_pkCamera)
		return;

	// get the image from the camera
	Image* pkImage = m_pkCamera->getImage();
	if(!pkImage)
		return;

	// get the image size
	UInt uiWidth = pkImage->width();
	UInt uiHeight = pkImage->height();

	// get the clipping planes
	Real fNear = m_pkCamera->getNear();
	Real fFar = m_pkCamera->getFar();
	Real fHW = m_pkCamera->getHalfWidth();
	Real fHH = m_pkCamera->getHalfHeight();

	// get the camera frame
	Vector kCamPos = m_pkCamera->getPosition();
	Vector kCamDir = Normalize(m_pkCamera->getDirection());
	Vector kCamRight = m_pkCamera->getRight();
	Vector kCamUp = m_pkCamera->getUp();

	// calculate the increment for ray marching (fixed size)
	Real fMultX = 2.0 / (uiWidth - 1.0f);
	Real fMultY = 2.0 / (uiHeight - 1.0f);
	Real fIncrement = (fFar - fNear)/(fNear*(m_uiSamples - 1.0));

	// setup for gathering statistics
	m_uiRayHits = 0;

	// render each scanline from top to bottom
	for( UInt uiY = uiStartLine; uiY < uiEndLine && uiY < uiHeight; uiY++ )
	{
		// calculate the pixels location
		Real fY = fHH * (-1.0f + fMultY * uiY);

		// render the scanline
		for( UInt uiX = 0; uiX < uiWidth; uiX++ )
		{
			// calculate the pixels location
			Real fX = fHW * (-1.0f + fMultX * uiX);

			// compute ray direction starting from near clip plane
			Vector kRayDir = fNear * kCamDir + fX * kCamRight + fY * kCamUp;

			// set the background color
			pkImage->setColor(uiX, uiY, m_kBgColor);

			// integrate across the surface
			Color kColor;
			integrate( kCamPos, kRayDir, fIncrement, kColor );

			// update the image
			pkImage->setColor(uiX, uiY, kColor);
		}
	}
}
//******************************************************************************
void RayTracer::integrate(
	Vector& rkPos, Vector& rkRayDir, Real fIncrement, Color& rkSampleColor)
{
	// compute a value for the start point of the ray
	Real fDist1 = 1.0;		// start at 1.0
	Vector kPos1 = rkPos;
	Real fValue1 = sample( kPos1.x(), kPos1.y(), kPos1.z());

	// normalize the current light direction for later use
	Vector kLightNormal = Normalize(m_kLightDirection);

	// continue sampling until all samples are covered
	for(UInt uiS = 0; uiS < m_uiSamples; uiS++)
	{
		// compute a value for next increment
		Real fDist2 = 1.0 + fIncrement * uiS;
		Vector kPos2 = rkPos + fDist2 * rkRayDir;
		Real fValue2 = sample(kPos2.x(), kPos2.y(), kPos2.z());

		//if ( fF0*fF1 <= m_fIsoLevel )
		if( fValue1 * fValue2 <= 0.0 )
		{
			// do a simple bisect to find the inersection with the surface
			Vector kPos, kSurfaceNormal;
			computeIntersection(
				fDist1, fValue1, kPos1,
				fDist2, fValue2, kPos2,
				rkRayDir, kPos, kSurfaceNormal);

			// normalize the current ray dir and reverse it for view dir
			Vector kViewNormal = -Normalize(rkRayDir);

			// get the forward facing normal
			kSurfaceNormal = FaceForward(kSurfaceNormal, kViewNormal);

			// shade the sample using standard phong shading (plastic-like)
			rkSampleColor = Phong( kSurfaceNormal, kViewNormal,
								   kLightNormal,m_kLightColor, m_kBaseColor,
								   m_fAmbient, m_fDiffuse, m_fSpecular,
								   m_fRoughness );

			// increment stats counter
			m_uiRayHits++;
			return;
		}

		// offset for next sample
		fDist1 = fDist2;
		kPos1 = kPos2;
		fValue1 = fValue2;
	}
}
//******************************************************************************
void RayTracer::computeIntersection(
	Real fDist1, Real fValue1, const Vector& rkPos1,
	Real fDist2, Real fValue2, const Vector& rkPos2,
	const Vector& rkRayDir, Vector& rkPos, Vector& rkNormal)
{
	// return if value1 intersects
	if ( Abs(fValue1) <= m_fRayEpsilon )
	{
		rkPos = rkPos1;
		rkNormal = computeNormal(rkPos.x(), rkPos.y(), rkPos.z());
		return;
	}

	// return if value1 intersects
	if ( Abs(fValue2) <= m_fRayEpsilon )
	{
		rkPos = rkPos2;
		rkNormal = computeNormal(rkPos.x(), rkPos.y(), rkPos.z());
		return;
	}

	// bisect until an intersection is found or max iterations are reached
	const UInt uiMax = 8;
	for(UInt i = 0; i < uiMax; i++)
	{
		Real fD = 0.5f * (fDist1 + fDist2);
		rkPos = m_pkCamera->getPosition() + fD * rkRayDir;
		Real fV = sample(rkPos.x(), rkPos.y(), rkPos.z());

		// stop if value intersects
		if ( Abs(fV) <= m_fRayEpsilon )
			break;

		//if ( fV*fValue1 < m_fIsoLevel )
		if ( fV * fValue1 < 0.0 )
		{
			fDist2 = fD;
			fValue2 = fV;
		}
		else
		{
			fDist1 = fD;
			fValue1 = fV;
		}
	}

	// get a normal for the current position
	rkNormal = computeNormal(rkPos.x(), rkPos.y(), rkPos.z());
}
//******************************************************************************
Vector RayTracer::computeNormal(Real fX, Real fY, Real fZ)
{
	Vector kNormal;
	kNormal.x() = sample(fX - m_fNormalEpsilon, fY, fZ) -
				  sample(fX + m_fNormalEpsilon, fY, fZ);

	kNormal.y() = sample(fX, fY - m_fNormalEpsilon, fZ) -
				  sample(fX, fY + m_fNormalEpsilon, fZ);

	kNormal.z() = sample(fX, fY, fZ - m_fNormalEpsilon) -
				  sample(fX, fY, fZ + m_fNormalEpsilon);
	Normalize(kNormal);
	return kNormal;
}
//******************************************************************************

