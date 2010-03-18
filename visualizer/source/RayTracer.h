#ifndef DG_TRACER_H
#define DG_TRACER_H

#include "DataTypes.h"
#include "Camera.h"
#include "Vector.h"
#include "Color.h"
#include "Maths.h"
namespace dg
{

//******************************************************************************

class RayTracer
{

public:
	typedef Real (*Function)(Real fX, Real fY, Real fZ);

	RayTracer(Function pvFunction=NULL, Camera* pkCamera=NULL);
	~RayTracer();

	// camera access methods
	inline void setCamera(Camera* pkCamera);
	inline const Camera* getCamera() const;

	// function access methods
	inline void setFunction(Function pvFunction);

	// light direction access methods (only single direction light supported!)
	inline Vector getLightDirection() const;
	inline void setLightDirection(const Vector& rkLight);

	// light color access methods (only single direction light supported!)
	inline Color getLightColor() const;
	inline void setLightColor(const Color& rkLight);

	// normal epsilon access methods
	inline void setNormalEpsilon(Real fEpsilon);
	inline Real getNormalEpsilon() const;

	// ray epsilon access methods
	inline void setRayEpsilon(Real fEpsilon);
	inline Real getRayEpsilon() const;

	// iso level access methods
	inline void setIsoLevel(Real fLevel);
	inline Real getIsoLevel() const;

	// max samples access methods
	inline void setSamples(UInt uiSamples);
	inline UInt getSamples() const;

	// statistics methods
	inline UInt getRayHits() const;

	// enable/disable blur access methods
	inline void setBlur(bool bBlur);
	inline bool getBlur() const;

	// background color access methods
	inline void setBackground(const Color& rkColor);
	inline Color getBackground() const;

	// surface properties
	inline Real getAmbient() const;
	inline void setAmbient(Real fAmbient);

	inline Real getDiffuse() const;
	inline void setDiffuse(Real fDiffuse);

	inline Real getSpecular() const;
	inline void setSpecular(Real fSpecular);

	inline Real getRoughness() const;
	inline void setRoughness(Real fRoughness);

	inline Color getBaseColor() const;
	inline void setBaseColor(const Color& rkBase);

	// perform the scanline raytrace
	void render();
	void render(UInt uiStartLine, UInt uiEndLine);

private:

	// integrate across surface
	void integrate( Vector& rkPos, Vector& rkRayDir,
					Real fIncrement, Color& rkColor);

	// find intersection of ray with surface
	void computeIntersection(
		float fS0, float fF0, const Vector& rkP0, float fS1,
		float fF1, const Vector& rkP1, const Vector& kRayDir,
		Vector& rkPos, Vector& rkNormal);

	// normal evalution (samples given function multiple times with offset)
	Vector computeNormal(Real fX, Real fY, Real fZ);

	// sample the implicit function at the given position
	inline Real sample(Real fX, Real fY, Real fZ);


	// light properties
	Vector m_kLightDirection;
	Color m_kLightColor;

	// sampling properties
	Real m_fIsoLevel;
	Real m_fRayEpsilon;
	Real m_fNormalEpsilon;

	// material properties
	Color m_kBaseColor;
	Color m_kBgColor;

	Real m_fAmbient;
	Real m_fDiffuse;
	Real m_fSpecular;
	Real m_fRoughness;

	// enable blurring for fast anti-aliasing
	bool m_bBlur;

	// max samples to evaluate
	UInt m_uiSamples;

	// sampling statistics
	UInt m_uiRayHits;

	// function to evaluate and visualize
	Function m_pvFunction;

	// camera to render through
	Camera* m_pkCamera;
};

//******************************************************************************

#include "RayTracer.inc"

//******************************************************************************

} // end namespace: dg

#endif

