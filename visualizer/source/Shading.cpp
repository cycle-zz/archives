#include "Shading.h"

using namespace dg;


//******************************************************************************
Real dg::RaySphere(
	const Vector& rkPos, 
	const Vector& rkRayDir,
    Real fRadius, Real fEpsilon,
	Real& rfT0, Real& rfT1)
{
	Real fEDotI = Dot( rkPos, rkRayDir );
	Real fEDotE = Dot( rkPos, rkPos );
	
    Real fB = 2.0 * fEDotI;
    Real fC = fEDotE - fRadius*fRadius;
	
    Real fDiscrim = fB*fB - 4.0 * fC;
    Real fSolutions = 0;
    if(fDiscrim > 0) 
	{   
		// two solutions
		fDiscrim = sqrt(fDiscrim);
		rfT0 = (-fDiscrim - fB) / 2.0;
		if(rfT0 > fEpsilon) 
		{
			rfT1 = (fDiscrim - fB) / 2.0;
			fSolutions = 2;
		} 
		else 
		{
			rfT0 = (fDiscrim - fB) / 2.0;
			fSolutions = (rfT0 > fEpsilon) ? 1 : 0;
		}
    } 
	else if (fDiscrim == 0) 
	{  
		// one solution on the edge
		rfT0 = -fB/2.0;
		fSolutions = (rfT0 > fEpsilon) ? 1 : 0;
    } 
	else 
	{                    
		// imaginary solution -> no intersection
		fSolutions = 0;
    }
    return fSolutions;
}
//******************************************************************************
Real dg::RaySphere(
	Real fEX, Real fEY, Real fEZ, 
	Real fIX, Real fIY, Real fIZ,
    Real fRadius, Real fEpsilon,
	Real& rfT0, Real& rfT1)
{
	Real fEDotI = fEX * fIX + fEY * fIY + fEZ * fIZ;
	Real fEDotE = fEX * fEX + fEY * fEY + fEZ * fEZ;
	
    Real fB = 2.0 * fEDotI;
    Real fC = fEDotE - fRadius*fRadius;
	
    Real fDiscrim = fB*fB - 4.0 * fC;
    Real fSolutions = 0;
    if(fDiscrim > 0) 
	{   
		// two solutions
		fDiscrim = sqrt(fDiscrim);
		rfT0 = (-fDiscrim - fB) / 2.0;
		if(rfT0 > fEpsilon) 
		{
			rfT1 = (fDiscrim - fB) / 2.0;
			fSolutions = 2;
		} 
		else 
		{
			rfT0 = (fDiscrim - fB) / 2.0;
			fSolutions = (rfT0 > fEpsilon) ? 1 : 0;
		}
    } 
	else if (fDiscrim == 0) 
	{  
		// one solution on the edge
		rfT0 = -fB/2.0;
		fSolutions = (rfT0 > fEpsilon) ? 1 : 0;
    } 
	else 
	{                    
		// imaginary solution -> no intersection
		fSolutions = 0;
    }
    return fSolutions;
}
//******************************************************************************

