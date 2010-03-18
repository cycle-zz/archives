#include "DataTypes.h"
#include "Maths.h"
#include <cmath>

using namespace dg;

//*******************************************************************************
Real dg::LogGamma(Real fX)
{
	const Real afCoeff[6] =
		{
			+ (Real)76.18009173,
			-(Real)86.50532033,
			+ (Real)24.01409822,
			-(Real)1.231739516,
			+ (Real)0.120858003e-02,
			-(Real)0.536382000e-05
		};

	fX -= (Real)1.0;
	Real fTmp = fX + (Real)5.5;
	fTmp -= (fX + ((Real)0.5)) * Log(fTmp);
	Real fSeries = (Real)1.0;
	for (int j = 0; j <= 5; j++)
	{
		fX += (Real)1.0;
		fSeries += afCoeff[j] / fX;
	}
	return -fTmp + dg::Log(((Real)2.50662827465)*fSeries);
}
//*******************************************************************************
//*******************************************************************************
Real dg::Erfc(Real fX)
{
	const Real afCoeff[10] =
		{
			-(Real)1.26551223,
			+ (Real)1.00002368,
			+ (Real)0.37409196,
			+ (Real)0.09678418,
			-(Real)0.18628806,
			+ (Real)0.27886807,
			-(Real)1.13520398,
			+ (Real)1.48851587,
			-(Real)0.82215223,
			+ (Real)0.17087277
		};

	Real fZ = Abs(fX);
	Real fT = ((Real)1.0) / ((Real)1.0 + ((Real)0.5) * fZ);
	Real fSum = afCoeff[9];

	for (int i = 9; i >= 0; i--)
		fSum = fT * fSum + afCoeff[i];

	Real fResult = fT * Exp( -fZ * fZ + fSum);

	return ( fX >= (Real)0.0 ? fResult : (Real)2.0 - fResult );
}
//*******************************************************************************
Real dg::CubicSpan(Real fX, const Real afC[4], const Real afM[4][4])
{
	Real fC3 = afM[0][0] * afC[0] + afM[0][1] * afC[1]
			 + afM[0][2] * afC[2] + afM[0][3] * afC[3];

	Real fC2 = afM[1][0] * afC[0] + afM[1][1] * afC[1]
			 + afM[1][2] * afC[2] + afM[1][3] * afC[3];

	Real fC1 = afM[2][0] * afC[0] + afM[2][1] * afC[1]
			 + afM[2][2] * afC[2] + afM[2][3] * afC[3];

	Real fC0 = afM[3][0] * afC[0] + afM[3][1] * afC[1]
			 + afM[3][2] * afC[2] + afM[3][3] * afC[3];

	return ( ( fC3 * fX + fC2 ) * fX + fC1 ) * fX + fC0;
}
//*******************************************************************************
Real dg::BicubicSpan(Real fU, Real fV, Real afC[4][4])
{
	return (

	fU * (fU * (fU * (fV * (fV * (fV * afC[0][0] + afC[0][1]) + afC[0][2]) + afC[0][3])
				   + (fV * (fV * (fV * afC[1][0] + afC[1][1]) + afC[1][2]) + afC[1][3]))
				   + (fV * (fV * (fV * afC[2][0] + afC[2][1]) + afC[2][2]) + afC[2][3]))
				   + (fV * (fV * (fV * afC[3][0] + afC[3][1]) + afC[3][2]) + afC[3][3])
	);
}
//*******************************************************************************
void dg::MakeBicubicMatrix(
	Real afG[4][4],
	Real afM[4][4],
	Real afC[4][4])
{
	/* temporary */
	Real afT[4][4];

	/* T = G * M^(t) (T gets G times transpose of M)*/
	for (UInt i = 0 ; i < 4 ; i++)
	for (UInt j = 0 ; j < 4 ; j++)
	for (UInt k = 0 ; k < 4 ; k++)
	afT[i][j] += afG[i][k] * afM[j][k];

	/* C = M * T (C gets M times T)*/
	for (UInt i = 0 ; i < 4 ; i++)
	for (UInt j = 0 ; j < 4 ; j++)
	for (UInt k = 0 ; k < 4 ; k++)
	afC[i][j] += afM[i][k] * afT[k][j];
}
//*******************************************************************************

