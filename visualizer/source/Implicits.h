#ifndef DG_IMPLICITS_H
#define DG_IMPLICITS_H

#include "DataTypes.h"
#include "Procedural.h"
#include "Vector.h"

namespace dg
{

//******************************************************************************
Real Torus(Real fX, Real fY, Real fZ);
Real Sphere(Real fX, Real fY, Real fZ);
Real Blob(Real fX, Real fY, Real fZ);
Real TriBlob(Real fX, Real fY, Real fZ);
Real Threads( Real fX, Real fY, Real fZ );
Real Cloth( Real fX, Real fY, Real fZ );
Real Quadric(Real fA, Real fB, Real fC);
Real SuperEllipsoid( Real fX, Real fY, Real fZ, Real fN1, Real fN2 );
Real Heart(Real fX, Real fY, Real fZ);
Real KleinBottle( Real fX, Real fY, Real fZ);
Real TriConnect(Real fX, Real fY, Real fZ);
Real QuadConnect(Real fX, Real fY, Real fZ);
Real Ripples(Real fX, Real fY, Real fZ);
Real VoronoiBumps(Real fX, Real fY, Real fZ);
Real SphericalShell(Real fX, Real fY, Real fZ);
Real SphericalFalloff(Real fX, Real fY, Real fZ);
Real EggShell(Real fX, Real fY, Real fZ);
Real EggFalloff(Real fX, Real fY, Real fZ);
Real TurbulentSpace( Real fX, Real fY, Real fZ );
Real TurbulentSphere( Real fX, Real fY, Real fZ );

//******************************************************************************

} // end namespace dg

#endif
