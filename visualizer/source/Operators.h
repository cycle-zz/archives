#ifndef DG_OPERATORS_H
#define DG_OPERATORS_H

#include "DataTypes.h"
#include "Volumes.h"
#include "Implicits.h"
#include "Procedural.h"

namespace dg
{

// *****************************************************************************

typedef Real (*Operator)(Real fX, Real fY, Real fZ);

// *****************************************************************************

struct OperatorSpec
{
	Operator op;
	const char* name;
};

// *****************************************************************************

static const OperatorSpec ImplicitFunc[] =
{
	{ Torus, "Torus" },
	{ Threads, "Threads" },
	{ Blob, "Blob" },
	{ Heart, "Heart" },
	{ KleinBottle, "KleinBottle" },
	{ TriConnect, "TriConnect"},
	{ QuadConnect, "QuadConnect"},
	{ Ripples, "Ripples"},
	{ VoronoiBumps, "VoronoiBumps"},
	{ GradientNoise, "GradientNoise" },
};
static const UInt ImplicitFuncCount = 10;

// *****************************************************************************

static const OperatorSpec DensityFunc[] =
{
	{ ClownDensityVolume, "ClownDensityVolume" },
	{ CloudDensityVolume, "CloudDensityVolume" },
	{ CumulusDensityVolume, "CumulusDensityVolume"},
	{ CellCloudDensityVolume, "CellCloudDensityVolume" },
//	{ SphericalShellDensityVolume, "SphericalShellDensityVolume" },
//	{ SphericalFalloffDensityVolume,  "SphericalFalloffDensityVolume" },
//	{ EggShellDensityVolume, "EggShellDensityVolume" },
//	{ EggFalloffDensityVolume, "EggFalloffDensityVolume" },
//	{ TurbulentSpaceDensityVolume, "TurbulentSpaceDensityVolume" },
//	{ TurbulentSphereDensityVolume, "TurbulentSphereDensityVolume" },
//	{ ClothDensityVolume, "ClothDensityVolume" },
};
static const UInt DensityFuncCount = 4;

// *****************************************************************************

} // end namespace dg

#endif
