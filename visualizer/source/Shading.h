#ifndef DG_SHADING_H
#define DG_SHADING_H

#include "DataTypes.h"
#include "Vector.h"
#include "Color.h"
#include "Maths.h"
#include "Set.h"

namespace dg
{

// just a basic distant light
struct Light
{
	Vector direction;
	Real intensity;
	Color color;
};

typedef Set<Light*> LightSet;


//******************************************************************************

inline Color Ambient(
	const Color& rkLightColor)
{
	return rkLightColor;
}

inline Color Diffuse(
	const Vector& rkSurfaceNormal, 
	const Vector& rkLightDir,
	const Color& rkLightColor)
{
	// only single light source contribution for now!
	return rkLightColor * Max( 0.0f, Dot(rkSurfaceNormal, rkLightDir) ); 
}

inline Color Specular(
	const Vector& rkSurfaceNormal, 
	const Vector& rkViewDir, 
	const Vector& rkLightDir,
	const Color& rkLightColor,
	Real fRoughness)
{
	// only single light source contribution for now!
	Vector kHalfway = Normalize( Normalize(rkViewDir) + Normalize(rkLightDir) );
	return rkLightColor * Pow( Max( 0.0f, Dot(rkSurfaceNormal, kHalfway) ), 1.0/fRoughness); 
}

// computes the color of a surface using a simple lambertian (matte) BRDF.
inline Color Lambertian(
	const Vector& rkSurfaceNormal,
	const Vector& rkLightDir,
	const Color& rkLightColor,
    const Color& rkBaseColor,
    Real fAmbient=1.0, Real fDiffuse=0.8)
{
    return rkBaseColor * (fAmbient * Ambient(rkLightColor) + 
		   fDiffuse * Diffuse(rkSurfaceNormal, rkLightDir, rkLightColor));
}

// computes the color of a surface using a simple plastic-like BRDF.
inline Color Phong(
	const Vector& rkSurfaceNormal,
	const Vector& rkViewDir,
	const Vector& rkLightDir,
	const Color& rkLightColor,
    const Color& rkBaseColor,
    Real fAmbient=1.0, Real fDiffuse=0.8, 
	Real fSpecular=0.5, Real fRoughness=0.1)
{
    return rkBaseColor * (fAmbient * Ambient(rkLightColor) + 
		   fDiffuse * Diffuse(rkSurfaceNormal, rkLightDir, rkLightColor)) +
           fSpecular * Specular( rkSurfaceNormal, -Normalize( rkViewDir ), 
		   						 rkLightDir, rkLightColor, fRoughness);
}

Real RaySphere(
	Real fEX, Real fEY, Real fEZ, 
	Real fIX, Real fIY, Real fIZ,
    Real fRadius, Real fEpsilon,
	Real& rfT0, Real& rfT1);

Real RaySphere(
	const Vector& rkPos, 
	const Vector& rkRayDir,
    Real fRadius, Real fEpsilon,
	Real& rfT0, Real& rfT1);

//******************************************************************************

inline Vector FaceForward( 
	const Vector& rkN, 
	const Vector& rkI);

inline Vector FaceForward( 
	const Vector& rkN, 
	const Vector& rkI, 
	const Vector& rkRef);
	
//******************************************************************************

#include "Shading.inc"

//******************************************************************************

} // end namespace dg

//******************************************************************************

#endif
