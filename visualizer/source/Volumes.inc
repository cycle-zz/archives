// *****************************************************************************
inline Real ClownDensityVolume( Real fX, Real fY, Real fZ )
{
	return FilteredClownDensityVolume( fX, fY, fZ );
}
// *****************************************************************************
inline Real CloudDensityVolume( Real fX, Real fY, Real fZ )
{
	return FilteredCloudDensityVolume( fX, fY, fZ );
}
// *****************************************************************************
inline Real CumulusDensityVolume( Real fX, Real fY, Real fZ )
{
	return FilteredCumulusDensityVolume( fX, fY, fZ );
}
// *****************************************************************************
inline Color FilteredClownColorVolume( Real fX, Real fY, Real fZ, Real fStepSize )
{
	// generate a wacko mostly green color using filtered gradient noise
	return Color(
		0.5 + 0.5 * FilteredGradientNoise( fX, fY, fZ, fStepSize ),
		0.75,
		0.5 + 0.5 * FilteredGradientNoise( fX - 10, fY - 10, fZ - 10, fStepSize ));
}
// *****************************************************************************
inline Real FilteredClownDensityVolume( Real fX, Real fY, Real fZ, Real fStepSize )
{
	// generate a wacko density volume using nicely filtered fBm
	Real fDensity = 0.5 + 0.5 * FilteredFBM(fX, fY, fZ, fStepSize,
											0.6, 2.0345, 3);

	return fDensity;
}
// *****************************************************************************
inline Real FilteredCloudDensityVolume( Real fX, Real fY, Real fZ, Real fStepSize )
{
	// use fbm as the basis for the density calculation
	Real fDensity = 0.5 + 0.5 *	FilteredFBM(fX, fY, fZ, fStepSize,
											0.65, 2.0345, 7);

	return fDensity;
}
// *****************************************************************************
inline Real FilteredCumulusDensityVolume( Real fX, Real fY, Real fZ, Real fStepSize )
{
	// use filtered turbulence as the basis
	Real fDensity = 0.5 + 0.5 * FilteredTurbulence( fX, fY, fZ, fStepSize,
													  0.8, 2.0345, 6);

	return fDensity;
}
// *****************************************************************************
inline Real CellCloudDensityVolume( Real fX, Real fY, Real fZ )
{
	// sample the voronoi noise function
	Real fRX, fRY, fRZ;
	Real fDensity = 1.0 - VoronoiNoise( fX, fY, fZ, 1, fRX, fRY, fRZ);

	// increase contrast
	fDensity = pow(Clamp(fDensity, 0.0, 1.0), 7.28);

	return fDensity;
}
// *****************************************************************************
inline Real SphericalShellDensityVolume(Real fX, Real fY, Real fZ)
{
	return SphericalShell(fX, fY, fZ);
}
// *****************************************************************************
inline Real SphericalFalloffDensityVolume(Real fX, Real fY, Real fZ)
{
	return SphericalFalloff(fX, fY, fZ);
}
// *****************************************************************************
inline Real EggShellDensityVolume(Real fX, Real fY, Real fZ)
{
	return EggShell(fX, fY, fZ);
}
// *****************************************************************************
inline Real EggFalloffDensityVolume(Real fX, Real fY, Real fZ)
{
	return EggFalloff(fX, fY, fZ);
}
// *****************************************************************************
inline Real TurbulentSpaceDensityVolume( Real fX, Real fY, Real fZ )
{
	return TurbulentSpace( fX, fY, fZ );
}
// *****************************************************************************
inline Real TurbulentSphereDensityVolume( Real fX, Real fY, Real fZ )
{
	return TurbulentSphere( fX, fY, fZ );
}
// *****************************************************************************
inline Real ClothDensityVolume( Real fX, Real fY, Real fZ )
{
	return Cloth( fX, fY, fZ );
}
// *****************************************************************************
