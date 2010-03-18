#ifndef DG_VOLUMES_H
#define DG_VOLUMES_H

#include "DataTypes.h"
#include "Implicits.h"
#include "Procedural.h"
#include "Color.h"

namespace dg
{

// *****************************************************************************
inline Color FilteredClownColorVolume( Real fX, Real fY, Real fZ, Real fStepSize );
// *****************************************************************************
inline Real ClownDensityVolume( Real fX, Real fY, Real fZ );
inline Real CloudDensityVolume( Real fX, Real fY, Real fZ );
inline Real CumulusDensityVolume( Real fX, Real fY, Real fZ );
inline Real CellCloudDensityVolume( Real fX, Real fY, Real fZ );
inline Real SphericalShellDensityVolume(Real fX, Real fY, Real fZ);
inline Real SphericalFalloffDensityVolume(Real fX, Real fY, Real fZ);
inline Real EggShellDensityVolume(Real fX, Real fY, Real fZ);
inline Real EggFalloffDensityVolume(Real fX, Real fY, Real fZ);
inline Real TurbulentSpaceDensityVolume( Real fX, Real fY, Real fZ );
inline Real TurbulentSphereDensityVolume( Real fX, Real fY, Real fZ );
inline Real ClothDensityVolume( Real fX, Real fY, Real fZ );

inline Real FilteredClownDensityVolume( Real fX, Real fY, Real fZ, Real fStepSize=0.1 );
inline Real FilteredCloudDensityVolume( Real fX, Real fY, Real fZ, Real fStepSize=0.1 );
inline Real FilteredCumulusDensityVolume( Real fX, Real fY, Real fZ, Real fStepSize=0.1 );
// *****************************************************************************

#include "Volumes.inc"

} // end namespace dg

// *****************************************************************************

#endif




