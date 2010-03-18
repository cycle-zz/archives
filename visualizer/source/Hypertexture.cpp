#include "Hypertexture.h"
#include "Operators.h"
#include "Random.h"
#include "Camera.h"
#include "Image.h"
#include "Maths.h"
#include "Shading.h"
#include <memory>

using namespace dg;

//******************************************************************************
Hypertexture::Hypertexture(
	DensityFn pvDensityFn,
	ColorFn pvColorFn,
	ShadeFn pvShadeFn,
	Camera* pkCamera)
		: m_kLightColor(5.0f, 5.0f, 5.0f),
		m_kShadowColor(0.0f, 0.0f, 0.25f)
{
	m_fRayEpsilon = 1.0e-4;
	m_fDensityThreshold = 0.5;
	m_fDensityScale = 35;
	m_fStepScale = 3.0;
	m_fShadowStepScale = 2.0;
	m_fShadowFarClip = 1.0;
	m_fShadowDepthThreshold = 2.3;
	m_fIlluminationScale = 0.5;
	m_fOpacityThreshold = 0.9999;

	m_fAmbient = 0.127;
	m_fDiffuse = 1;
	m_fSpecular = 0.3;
	m_fRoughness = 0.1;

	m_fOpacityDensity = 1;
	m_fLightDensity = 1;
	m_fShadowDensity = 1;

	m_fScale = 1.0;
	m_fStepSize = 0.1;
	m_fShadowStepSize = 0.5;
	m_fNoiseFreq = 2.0;
	m_fThreshold = 0.5;

	m_uiRayHits = 0;
	m_uiSamples = 0;
	m_uiMaxSamples = 0;

	m_bJitter = true;
	m_bKeepInView = true;
	m_bFadeOut = false;

	m_pvDensityFn = pvDensityFn;
	m_pvColorFn = pvColorFn;
	m_pvShadeFn = pvShadeFn;
	m_pkCamera = pkCamera;

	m_pvFilteredColorFn = NULL;
	m_pvFilteredDensityFn = NULL;
}
//******************************************************************************
Hypertexture::~Hypertexture()
{
	// EMPTY!
}
//******************************************************************************
void Hypertexture::render()
{
	if(!m_pkCamera)
		return;

	// get the image from the camera
	Image* pkImage = m_pkCamera->getImage();
	if(!pkImage)
		return;

	render(0, pkImage->height());

//    if ( m_bBlur )
//        pkImage->blur();
}
//******************************************************************************
void Hypertexture::render(UInt uiStartLine, UInt uiEndLine)
{
	if(!m_pkCamera)
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

	// set the testing radius
	Real fRadius = fFar - fNear;

	// get the camera frame
	Vector kCamDir = Normalize(m_pkCamera->getDirection());
	Vector kCamRight = m_pkCamera->getRight();
	Vector kCamUp = m_pkCamera->getUp();

	// calculate the increment for ray marching (fixed size)
	Real fMultX = 2.0 / (uiWidth - 1.0f);
	Real fMultY = 2.0 / (uiHeight - 1.0f);
	//Real fIncrement = m_fStepScale * m_pkCamera->getPixelWidth();
	Real fIncrement = m_fStepSize;

	// setup for gathering statistics
	m_uiRayHits = 0;
	m_uiSamples = 0;

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

			// integrate the volume
			Color kColor;
			integrate( kRayDir*fNear, kRayDir, fRadius, fIncrement, kColor );

			// update the image
			pkImage->setColor(uiX, uiY, kColor);
		}
	}
}
//******************************************************************************
void Hypertexture::integrate(
	const Vector& rkPos, const Vector& rkRayDir, Real fRadius,
	Real fStepSize, Color& rkColor)
{
	// setup for integration
	Real fDensity = 0.0;

	// setup for accumulation
	Real fAccumOpacity = 0.0;
	Color kAccumColor;

	// check sphere for intersection points to determine start and end
	Real fT0, fT1;
	Real fHits = RaySphere(rkPos, -rkRayDir, fRadius, m_fRayEpsilon, fT0, fT1);

	// determine the distance to march
	Real fEnd = (fHits > 0) ? fT0 : 0;
	Vector kOrigin = rkPos - fT0 * rkRayDir;

	// set the current distance to the initial step size
	Real fDistance = fStepSize;

	// jitter the starting distance to reduce artifacts for large stepsizes
	if(m_bJitter)
		fDistance *= RandomUnitReal();

	// calculate a reasonable step size
	Real fStride = Min(fStepSize, fEnd - fDistance);

	// integrate forwards from the start vector
	Vector kSamplePos = kOrigin + fDistance * rkRayDir;

	// get the current sample densnity
	Real fPrevDensity = computeDensity(	kSamplePos, fRadius,
										m_fNoiseFreq, fStepSize);

	// get the current sample color
	Color kPrevColor = computeShading( kSamplePos, rkRayDir, fDensity,
									   fRadius, m_fShadowDensity, m_fNoiseFreq,
									   m_fShadowStepSize, m_fDensityThreshold);

	// sharpen at volume boundary
	fPrevDensity = SmoothStep( m_fDensityThreshold,
							   m_fDensityThreshold + ms_fBoundaryOffset,
							   fPrevDensity);

	// continue marching from start to end or total opacity is reached
	while (fDistance <= fEnd && fAccumOpacity < m_fOpacityThreshold )
	{
		// step along the path, always progressing forward
		fStride = Clamp(fStride, ms_fMinStride, fEnd - fDistance);
		fDistance += fStride;

		// calculate the scattered light and density
		kSamplePos = kOrigin + fDistance * rkRayDir;
		Real fCurrentDensity = computeDensity( kSamplePos, fRadius,
											 m_fNoiseFreq, fStepSize);

		// shade if necessary
		Color kCurrentColor;
		if (fCurrentDensity > m_fDensityThreshold)
		{
			kCurrentColor = computeShading( kSamplePos, rkRayDir,
									fCurrentDensity, fRadius, m_fShadowDensity,
									m_fNoiseFreq, m_fShadowStepSize,
									m_fDensityThreshold);

			m_uiRayHits++;
		}

		// sharpen at boundary
		fCurrentDensity = SmoothStep( m_fDensityThreshold,
									  m_fDensityThreshold + ms_fBoundaryOffset,
									  fCurrentDensity);

		// calculate current optical path length
		Real fTau = m_fOpacityDensity * fStride / 2.0 *
					(fCurrentDensity + fPrevDensity);

		// compute color from current density
		Color kTauColor = m_fLightDensity * fStride / 2.0 *
						  (kCurrentColor * fCurrentDensity +
						  kPrevColor * fPrevDensity);

		// apply exponentially decay to path length
		Real fAlpha = 1 - Exp( -fTau );

		// composite with background light
		kAccumColor += (1.0f - fAccumOpacity) * kCurrentColor * fAlpha;
		fAccumOpacity += (1.0f - fAccumOpacity) * fAlpha;

		// setup for next iteration
		fPrevDensity = fCurrentDensity;
		kPrevColor = kTauColor;

		// update stats counter
		m_uiSamples++;
	}

	// return the accumulated result
	rkColor = kAccumColor;
	rkColor.a() = fAccumOpacity;
	if(fAccumOpacity == 0)
		rkColor = m_kBgColor;
}
//******************************************************************************
Real Hypertexture::computeDensity(
	const Vector& rkPos, Real fRadius, Real fNoiseFreq, Real fStepSize)
{
	//Real fSamplePosX = m_fScale * (rkPos.x() + m_kOffset.x());
	//Real fSamplePosY = m_fScale * (rkPos.y() + m_kOffset.y());
	//Real fSamplePosZ = m_fScale * (rkPos.z() + m_kOffset.z());

	Real fSamplePosX = rkPos.x();
	Real fSamplePosY = rkPos.y();
	Real fSamplePosZ = rkPos.z();

	Real fDensity = 0;
	if(m_pvFilteredDensityFn)
	{
		fDensity = m_pvFilteredDensityFn(
						fSamplePosX * fNoiseFreq,
						fSamplePosY * fNoiseFreq,
						fSamplePosZ * fNoiseFreq,
						fStepSize * fNoiseFreq );
	}
	else if(m_pvDensityFn)
	{
		fDensity = m_pvDensityFn(
						fSamplePosX * fNoiseFreq,
						fSamplePosY * fNoiseFreq,
						fSamplePosZ * fNoiseFreq);
	}

	if(m_bKeepInView)
	{
		// apply the density to a sphere at the camera's look point
		Vector kRV = rkPos + m_pkCamera->getPosition() + m_pkCamera->getDirection();
		fRadius = 0.5 * Dot( kRV, kRV );
		fDensity += 1.0 - fRadius * fRadius;
	}
	else if(m_bFadeOut)
	{
		// fade out at sphere
		fDensity *= 1.0 - SmoothStep(0.8, 1.0, rkPos.length() / fRadius);
	}

	return fDensity;
}
//******************************************************************************
Color Hypertexture::computeColor(
	const Vector& rkPos, Real fStepSize)
{
	if(m_pvFilteredColorFn)
	{
		return m_pvFilteredColorFn( rkPos.x(), rkPos.y(), rkPos.z(), fStepSize );
	}
	else if(m_pvColorFn)
	{
		return m_pvColorFn( rkPos.x(), rkPos.y(), rkPos.z() );
	}
	return Color::WHITE;
}
//******************************************************************************
Real Hypertexture::computeShadow(
	const Vector& rkPos, const Vector& rkNormal, const Vector& rkRay,
	Real fRadius, Real fLightDensity,
	Real fNoiseFreq, Real fStepSize, Real fThreshold)
{
	// only shade the back, not the front
	if(Dot(rkNormal, rkRay) < 0)
		return 0.0;

	Real fAccumOpacity = 0;
	Real fRayLen = rkRay.length();
	Vector kRayDir = Normalize(rkRay);

	// check sphere for intersection points to determine start and end
	Real fT0, fT1;
	Real fHits = RaySphere(rkPos, rkRay, fRadius, m_fRayEpsilon, fT0, fT1);

	// determine the distance to march
	Real fEnd = (fHits > 0) ? fT0 : 0;
	fEnd = Min(fEnd, fRayLen);

	// get the start density
	Real fDistance = 0;
	Real fStride = Min(fStepSize, fEnd - fDistance);
	Real fPrevDensity = computeDensity(rkPos, fRadius, fNoiseFreq, fStepSize);

	// sharpen at volume boundary
	fPrevDensity = SmoothStep(fThreshold,
							  fThreshold + ms_fBoundaryOffset,
							  fPrevDensity);

	// continue marching until we reach the end or total opacity
	while (fDistance <= fEnd && fAccumOpacity < m_fOpacityThreshold)
	{
		// take a step and get the scattered light and density
		fStride = Clamp(fStride, ms_fMinStride, fEnd - fDistance);
		fDistance += fStride;

		// compute the sample position
		Vector kSamplePos = rkPos + fDistance * kRayDir;

		// compute the current density
		Real fCurrentDensity = computeDensity(kSamplePos, fRadius,
										   fNoiseFreq, fStepSize);

		// sharpen at volume boundary
		fCurrentDensity = SmoothStep(fThreshold,
									 fThreshold + ms_fBoundaryOffset,
									 fCurrentDensity);

		// compute the optical path length
		Real fTau = fLightDensity * fStride / 2.0 *
					(fCurrentDensity + fPrevDensity);

		// accumulate the opacity with exponential decay
		fAccumOpacity += (1 - fAccumOpacity) * (1 - Exp( -fTau));

		// setup for next iteration
		fPrevDensity = fCurrentDensity;
	}

	// return the accumulated result
	return fAccumOpacity;
}
//******************************************************************************
Color Hypertexture::computeShading(
	const Vector& rkPos, const Vector& rkRayDir,
	Real fIncomingDensity, Real fRadius, Real fDensity,
	Real fNoiseFreq, Real fStepSize, Real fThreshold)
{
	// compute the surface normal at the current position
	Vector kSurfaceNormal = computeNormal(rkPos, fIncomingDensity,
										  fNoiseFreq, fRadius, fStepSize);

	// get the forward facing normal and normalize it
	kSurfaceNormal = FaceForward(kSurfaceNormal, rkRayDir);
	kSurfaceNormal = Normalize(kSurfaceNormal);

	// setup for computing the color of the scattered light
	Color kLightScatter = m_kLightColor;

	// compute shadow if necessary
	if (fDensity > 0)
	{
		kLightScatter *= 1.0f - computeShadow(rkPos, kSurfaceNormal,
											  m_kLightDirection, fRadius,
											  fDensity, fNoiseFreq, fStepSize,
											  fThreshold);
	}

	// shade the surface if necessary
	if(m_pvShadeFn)
	{
		// get the normal for the light direction
		Vector kLightNormal = Normalize(m_kLightDirection);
		Vector kViewNormal = Normalize(rkRayDir);

		// do the shading calculation
		Color kShadedColor = m_pvShadeFn(kSurfaceNormal, kViewNormal,
										 kLightNormal, m_kLightColor,
										 kLightScatter, m_fAmbient,
										 m_fDiffuse, m_fSpecular, m_fRoughness );

		// combine the shaded light with the surface color
		return kShadedColor * computeColor(rkPos, fStepSize);
	}

	// otherwise just combine the shadowed light with the surface color
	return kLightScatter * computeColor(rkPos, fStepSize);
}
//******************************************************************************
Vector Hypertexture::computeNormal(
	const Vector & rkPos, Real fDensity,
	Real fNoiseFreq, Real fRadius, Real fStepSize)
{
	Vector kNormal;
	if( rkPos.length() > fRadius - 0.0051)
	{
		kNormal = rkPos;
	}
	else
	{
		kNormal = (computeDensity(rkPos + Vector(fStepSize / 10.0, 0, 0),
						   fRadius, fNoiseFreq, fStepSize) - fDensity,
				   computeDensity(rkPos + Vector(0, fStepSize / 10.0, 0),
						   fRadius, fNoiseFreq, fStepSize) - fDensity,
				   computeDensity(rkPos + Vector(0, 0, fStepSize / 10.0),
						   fRadius, fNoiseFreq, fStepSize) - fDensity);
	}

	return Normalize(kNormal);
}
//******************************************************************************

