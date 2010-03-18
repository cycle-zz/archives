#ifndef DG_HYPERTEXTURE_H
#define DG_HYPERTEXTURE_H

#include "DataTypes.h"
#include "Camera.h"
#include "Vector.h"
#include "Color.h"

namespace dg
{

//******************************************************************************

class Hypertexture
{

public:

	typedef Real (*DensityFn)(Real fX, Real fY, Real fZ);
	typedef Real (*FilteredDensityFn)(Real fX, Real fY, Real fZ, Real fDT);

	typedef Color (*ColorFn)(Real fX, Real fY, Real fZ);
	typedef Color (*FilteredColorFn)(Real fX, Real fY, Real fZ, Real fDT);

	typedef Color (*ShadeFn)(const Vector& rkSurfaceNormal,
							 const Vector& rkViewDir,
							 const Vector& rkLightDir,
							 const Color& rkLightColor,
							 const Color& rkBaseColor,
							 Real fAmbient, Real fDiffuse,
							 Real fSpecular, Real fRoughness);

	Hypertexture::Hypertexture(
		DensityFn pvDensityFn=NULL,
		ColorFn pvColorFn=NULL,
		ShadeFn pvShadeFn=NULL,
		Camera* pkCamera=NULL);

	~Hypertexture();

	// function methods
	inline void setDensityFunction(DensityFn pvDensityFn);
	inline void setColorFunction(ColorFn pvColorFn);
	inline void setShadingFunction(ShadeFn pvShadeFn);
	inline void setFilteredDensityFunction(FilteredDensityFn pvDensityFn);
	inline void setFilteredColorFunction(FilteredColorFn pvColorFn);

	// camera access methods
	inline void setCamera(Camera* pkCamera);
	inline const Camera* getCamera() const;

	// light direction access methods (only single direction light supported!)
	inline Vector getLightDirection() const;
	inline void setLightDirection(const Vector& rkLight);

	// light color access methods (only single direction light supported!)
	inline Color getLightColor() const;
	inline void setLightColor(const Color& rkLight);

	// function evaluation scale access methods
	inline void setScale(Real fScale);
	inline Real getScale();

	// surface properties
	inline Real getAmbient() const;
	inline void setAmbient(Real fAmbient);

	inline Real getDiffuse() const;
	inline void setDiffuse(Real fDiffuse);

	inline Real getSpecular() const;
	inline void setSpecular(Real fSpecular);

	inline Real getRoughness() const;
	inline void setRoughness(Real fRoughness);

	// ray epsilon access methods
	inline void setRayEpsilon(Real fEpsilon);
	inline Real getRayEpsilon() const;

	// density threshold access methods
	inline Real getDensityScale() const;
	inline void setDensityScale(Real fDensityScale);

	// density threshold access methods
	inline Real getDensityThreshold() const;
	inline void setDensityThreshold(Real fDensityThreshold);

	// transparency epsilon access methods
	inline Real getOpacityThreshold() const;
	inline void setOpacityThreshold(Real fOpacityThreshold);

	// shadow clipping plane access methods
	inline Real getShadowFarClip() const;
	inline void setShadowFarClip(Real fShadowFarClip);

	// shadow depth threshold access methods (2.3 ~= 10% ambient light)
	inline Real getShadowDepthThreshold() const;
	inline void setShadowDepthThreshold(Real fShadowDepthThreshold);

	// shadow step size access methods
	inline Real getShadowStepScale() const;
	inline void setShadowStepScale(Real fShadowStepScale);

	// step size access methods
	inline Real getStepSize() const;
	inline void setStepSize(Real fStepSize);

	// sample limiting access methods
	inline void setMaxSamples(UInt uiMax);
	inline UInt getMaxSamples() const;

	// statistic information from last render
	inline UInt getRayHits() const;
	inline UInt getSamples() const;

	// background color access methods
	inline void setBackground(const Color& rkColor);
	inline Color getBackground() const;

	// keep in view access methods
	inline void setKeepInView( bool bKeepInView );
	inline bool getKeepInView();

	// fade out access methods
	inline void setFadeOut( bool bFadeOut );
	inline bool getFadeOut();

	// perform the raymarch
	void render();
	void render(UInt uiStartLine, UInt uiEndLine);

private:

	// integrate the volume
	void integrate(
			const Vector& rkPos, const Vector& rkRayDir, Real fRadius,
			Real fIncrement, Color& rkColor);

	// sample and calculate illumination
	Color computeShading(
		const Vector& rkPos, const Vector& rkRayDir,
		Real fIncomingDensity, Real fRadius, Real fDensity,
		Real fNoiseFreq, Real fStepSize, Real fThreshold);

	// sample and calculate density
	Real computeDensity(
		const Vector& rkPos, Real fRadius,
		Real fNoiseFreq, Real fStepSize);

	// sample and calculate self shadowing
	Real computeShadow(
		const Vector& rkPos, const Vector& rkNormal, const Vector& rkRay,
		Real fRadius, Real fIncomingDensity,
		Real fNoiseFreq, Real fStepSize, Real fThreshold);

	Color computeColor(const Vector& rkPos, Real fStepSize);

	Vector computeNormal(
		const Vector & rkPos, Real fDensity,
		Real fNoiseFreq, Real fRadius, Real fStepSize);

	// light properties
	Vector m_kLightDirection;
	Color m_kLightColor;

	// material properties
	Real m_fAmbient;
	Real m_fDiffuse;
	Real m_fSpecular;
	Real m_fRoughness;

	// scale and offset
	Real m_fScale;
	Vector m_kOffset;

	Real m_fRadius;
	Real m_fOpacityDensity;
	Real m_fLightDensity;
	Real m_fShadowDensity;
	Real m_fStepSize;
	Real m_fShadowStepSize;
	Real m_fNoiseFreq;
	Real m_fThreshold;

	Real m_fStepScale;
	Real m_fRayEpsilon;
	Real m_fDensityScale;
	Real m_fDensityThreshold;
	Real m_fShadowFarClip;
	Real m_fShadowStepScale;
	Real m_fShadowDepthThreshold;

	Real m_fOpacityThreshold;
	Real m_fIlluminationScale;

	// material properties
	Color m_kShadowColor;
	Color m_kBgColor;

	// statistic of rendered image
	UInt m_uiMaxSamples;

	UInt m_uiSamples;
	UInt m_uiRayHits;

	// flag for enabling jittered sample strides
	bool m_bJitter;

	// flag for restricting evaluation to current camera look point
	bool m_bKeepInView;

	// flag for fading the hypertexture out at a spherical boundary
	bool m_bFadeOut;

	// function to evaluate and visualize
	DensityFn m_pvDensityFn;
	ColorFn m_pvColorFn;
	ShadeFn m_pvShadeFn;
	FilteredDensityFn m_pvFilteredDensityFn;
	FilteredColorFn m_pvFilteredColorFn;

	// camera for current view and image to render to
	Camera* m_pkCamera;

	static const Real ms_fMinStride = 0.005f;
	static const Real ms_fBoundaryOffset = 0.01f;

};

//******************************************************************************

#include "Hypertexture.inc"

//******************************************************************************

} // end namespace: dg

#endif

