// start file: Matrix.cpp

// #############################################################################
// #
// # Derek Gerstmann
// # dgerstma@u.washington.edu
// #
// #############################################################################

// headers
#include "Matrix.h"
#include "DataTypes.h"
#include "Maths.h"
#include "Vector.h"
#include <memory>
#include <algorithm>
using std::swap;

////////////////////////////////////////////////////////////////////////////////
// Matrix implementation
////////////////////////////////////////////////////////////////////////////////

using namespace dg;

//******************************************************************************
Matrix::Matrix()
{
	m_afV[0][1] = m_afV[0][2] = m_afV[0][3] =
	m_afV[1][0] = m_afV[1][2] = m_afV[1][3] =
	m_afV[2][0] = m_afV[2][1] = m_afV[2][3] =
	m_afV[3][0] = m_afV[3][1] = m_afV[3][2] = 0.0f;
	m_afV[0][0] = m_afV[1][1] = m_afV[2][2] = m_afV[3][3] = 1.0f;
}	
//******************************************************************************
Matrix::Matrix(Real afV[16])
{
	m_afV[0][0] = afV[0];
	m_afV[0][1] = afV[1];
	m_afV[0][2] = afV[2];
	m_afV[0][3] = afV[3];
	m_afV[1][0] = afV[4];
	m_afV[1][1] = afV[5];
	m_afV[1][2] = afV[6];
	m_afV[1][3] = afV[7];
	m_afV[2][0] = afV[8];
	m_afV[2][1] = afV[9];
	m_afV[2][2] = afV[10];
	m_afV[2][3] = afV[11];
	m_afV[3][0] = afV[12];
	m_afV[3][1] = afV[13];
	m_afV[3][2] = afV[14];
	m_afV[3][3] = afV[15];
}
//******************************************************************************
Matrix::Matrix(
	Real fV00, Real fV01, Real fV02, Real fV03,
	Real fV10, Real fV11, Real fV12, Real fV13,
	Real fV20, Real fV21, Real fV22, Real fV23,
	Real fV30, Real fV31, Real fV32, Real fV33)
{
	m_afV[0][0] = fV00;
	m_afV[0][1] = fV01;
	m_afV[0][2] = fV02;
	m_afV[0][3] = fV03;
	m_afV[1][0] = fV10;
	m_afV[1][1] = fV11;
	m_afV[1][2] = fV12;
	m_afV[1][3] = fV13;
	m_afV[2][0] = fV20;
	m_afV[2][1] = fV21;
	m_afV[2][2] = fV22;
	m_afV[2][3] = fV23;
	m_afV[3][0] = fV30;
	m_afV[3][1] = fV31;
	m_afV[3][2] = fV32;
	m_afV[3][3] = fV33;
}
//******************************************************************************
Matrix::Matrix(const Real afV[4][4])
{
	m_afV[0][0] = afV[0][0];
	m_afV[0][1] = afV[0][1];
	m_afV[0][2] = afV[0][2];
	m_afV[0][3] = afV[0][3];
	m_afV[1][0] = afV[1][0];
	m_afV[1][1] = afV[1][1];
	m_afV[1][2] = afV[1][2];
	m_afV[1][3] = afV[1][3];
	m_afV[2][0] = afV[2][0];
	m_afV[2][1] = afV[2][1];
	m_afV[2][2] = afV[2][2];
	m_afV[2][3] = afV[2][3];
	m_afV[3][0] = afV[3][0];
	m_afV[3][1] = afV[3][1];
	m_afV[3][2] = afV[3][2];
	m_afV[3][3] = afV[3][3];
}
//******************************************************************************
Matrix::Matrix(const Vector &rkW, const Vector &rkV, const Vector &rkU)
{
	m_afV[0][0] = rkW.x(); m_afV[0][1] = rkW.y(); m_afV[0][2] = rkW.z();
	m_afV[1][0] = rkV.x(); m_afV[1][1] = rkV.y(); m_afV[1][2] = rkV.z();
	m_afV[2][0] = rkU.x(); m_afV[2][1] = rkU.y(); m_afV[2][2] = rkU.z();

	m_afV[0][3] = m_afV[1][3] = m_afV[2][3] = 0;
	m_afV[3][0] = m_afV[3][1] = m_afV[3][2] = 0;
	m_afV[3][3] = 1.0;
}
//******************************************************************************
/*
Matrix::Matrix(const Matrix& rkMatrix)
{
	m_afV[0][0] = rkMatrix.m_afV[0][0];
	m_afV[0][1] = rkMatrix.m_afV[0][1];
	m_afV[0][2] = rkMatrix.m_afV[0][2];
	m_afV[0][3] = rkMatrix.m_afV[0][3];
	m_afV[1][0] = rkMatrix.m_afV[1][0];
	m_afV[1][1] = rkMatrix.m_afV[1][1];
	m_afV[1][2] = rkMatrix.m_afV[1][2];
	m_afV[1][3] = rkMatrix.m_afV[1][3];
	m_afV[2][0] = rkMatrix.m_afV[2][0];
	m_afV[2][1] = rkMatrix.m_afV[2][1];
	m_afV[2][2] = rkMatrix.m_afV[2][2];
	m_afV[2][3] = rkMatrix.m_afV[2][3];
	m_afV[3][0] = rkMatrix.m_afV[3][0];
	m_afV[3][1] = rkMatrix.m_afV[3][1];
	m_afV[3][2] = rkMatrix.m_afV[3][2];
	m_afV[3][3] = rkMatrix.m_afV[3][3];
}
*/
//******************************************************************************
void Matrix::getRow( UInt uiRow, Vector & rkV ) const
{
	rkV = Vector( 
			m_afV[ 0 ] [ uiRow ], 
			m_afV[ 1 ] [ uiRow ], 
			m_afV[ 2 ] [ uiRow ] );
}
//******************************************************************************
void Matrix::getColumn( UInt uiCol, Vector & rkV ) const
{
	rkV = Vector( 
			m_afV[ uiCol ] [ 0 ], 
			m_afV[ uiCol ] [ 1 ], 
			m_afV[ uiCol ] [ 2 ] );
}
//******************************************************************************
Matrix Matrix::transpose() const
{
	Matrix kM;
	for ( UInt iRow = 0; iRow < 4; iRow++ )
		for ( UInt iCol = 0; iCol < 4; iCol++ )
			kM.m_afV[ iCol ] [ iRow ] = m_afV[ iRow ] [ iCol ];
	
	return kM;
}
//******************************************************************************
Matrix Matrix::inverse() const
{
	UInt auiXCol[ 4 ], auiXRow[ 4 ];
	UInt auiPivot[ 4 ] = { 0, 0, 0, 0 };

	Real afMInv[ 4 ][ 4 ];
	memcpy( afMInv, m_afV, 4 * 4 * sizeof( Real ) );

	for ( UInt i = 0; i < 4; i++ )
	{
		Int iRow = -1, iCol = -1;
		Real big = 0.;
	
		// choose pivot
		for ( UInt j = 0; j < 4; j++ )
		{
			if ( auiPivot[ j ] != 1 )
			{
				for ( UInt k = 0; k < 4; k++ )
				{
					if ( auiPivot[ k ] == 0 )
					{
						if ( fabsf( afMInv[ j ][ k ] ) >= big )
						{
							big = Real( Abs( afMInv[ j ][ k ] ) );
							iRow = j;
							iCol = k;
						}
					}
					else
						if ( auiPivot[ k ] > 1 )
							return Matrix();
							//Error( "Singular matrix in MatrixInvert" );
				}
			}
		}
		++auiPivot[ iCol ];
		
		// Swap rows _iRow_ and _iCol_ for pivot
		if ( iRow != iCol )
		{
			for ( UInt k = 0; k < 4; ++k )
				swap( afMInv[ iRow ][ k ], afMInv[ iCol ][ k ] );
		}
		auiXRow[ i ] = iRow;
		auiXCol[ i ] = iCol;
		
		if ( afMInv[ iCol ][ iCol ] == 0. )
			return Matrix();
			//Error( "Singular matrix in MatrixInvert" );
		
		// Set $m[iCol][iCol]$ to one by scaling row _iCol_ appropriately
		Real fPivotInv = 1.f / afMInv[ iCol ][ iCol ];
		afMInv[ iCol ][ iCol ] = 1.f;
		for ( UInt j = 0; j < 4; j++ )
			afMInv[ iCol ][ j ] *= fPivotInv;
		
		// Subtract this row from others to zero out their columns
		for ( Int j = 0; j < 4; j++ )
		{
			if ( j != iCol )
			{
				Real fSave = afMInv[ j ][ iCol ];
				afMInv[ j ][ iCol ] = 0;
				for ( UInt k = 0; k < 4; k++ )
					afMInv[ j ][ k ] -= afMInv[ iCol ][ k ] * fSave;
			}
		}
	}
	
	// Swap columns to reflect permutation
	for ( Int j = 3; j >= 0; j-- )
	{
		if ( auiXRow[ j ] != auiXCol[ j ] )
		{
			for ( UInt k = 0; k < 4; k++ )
				swap( afMInv[ k ][ auiXRow[ j ] ], 
				      afMInv[ k ][ auiXCol[ j ] ] );
		}
	}
	return Matrix( afMInv );

}
//******************************************************************************
Matrix& Matrix::operator *= ( const Matrix & rkM )
{
	UInt iRow, iCol, iPlace;

	for ( iRow = 0; iRow < 4; iRow++ )
	{
		for ( iCol = 0; iCol < 4; iCol++ )
		{
			m_afV[ iRow ] [ iCol ] = 0.0;
			for ( iPlace = 0; iPlace < 4; iPlace++ )
			{
				m_afV[ iRow ] [ iCol ] += m_afV[ iRow ] [ iPlace ] * 
										  rkM.m_afV[ iPlace ] [ iCol ];
			}
		}
	}
	return *this;
}
//******************************************************************************
Matrix Matrix::operator+( const Matrix& rkM ) const
{
	Matrix kRet;
	UInt iRow, iCol;
	for ( iRow = 0; iRow < 4; iRow++ )
	{
		for ( iCol = 0; iCol < 4; iCol++ )
		{
			kRet.m_afV[ iRow ][ iCol ] = m_afV[ iRow ][ iCol ] + 
										 rkM.m_afV[ iRow ][ iCol ];
		}
	}
	return kRet;
}
//******************************************************************************
Matrix Matrix::operator-( const Matrix& rkM ) const
{
	Matrix kRet;
	UInt iRow, iCol;
	for ( iRow = 0; iRow < 4; iRow++ )
	{
		for ( iCol = 0; iCol < 4; iCol++ )
		{
			kRet.m_afV[ iRow ][ iCol ] = m_afV[ iRow ][ iCol ] - 
										 rkM.m_afV[ iRow ][ iCol ];
		}
	}
	return kRet;
}
//******************************************************************************
Matrix Matrix::operator * ( const Matrix & rkM ) const
{
	UInt iRow, iCol, iPlace;
	static Matrix kM;

	for ( iRow = 0; iRow < 4; iRow++ )
	{
		for ( iCol = 0; iCol < 4; iCol++ )
		{
			kM.m_afV[ iRow ] [ iCol ] = 0.0;
			for ( iPlace = 0; iPlace < 4; iPlace++ )
			{
				kM.m_afV[ iRow ] [ iCol ] += m_afV[ iRow ] [ iPlace ] * 
											 rkM.m_afV[ iPlace ] [ iCol ];
			}
		}
	}

	return kM;
}
//******************************************************************************
Matrix& Matrix::operator+=( const Matrix &rkM )
{
	UInt iRow, iCol;
	for ( iRow = 0; iRow < 4; iRow++ )
	{
		for ( iCol = 0; iCol < 4; iCol++ )
		{
			m_afV[ iRow ][ iCol ] += rkM.m_afV[ iRow ][ iCol ];
		}
	}
	return *this;
}
//******************************************************************************
Matrix& Matrix::operator-=( const Matrix &rkM )
{
	UInt iRow, iCol;
	for ( iRow = 0; iRow < 4; iRow++ )
	{
		for ( iCol = 0; iCol < 4; iCol++ )
		{
			m_afV[ iRow ][ iCol ] -= rkM.m_afV[ iRow ][ iCol ];
		}
	}
	return *this;
}
//******************************************************************************
Matrix Matrix::operator * ( Real fC ) const
{

	static Matrix kM;

	for ( UInt iRow = 0; iRow < 4; iRow++ )
		for ( UInt iCol = 0; iCol < 4; iCol++ )
			kM.m_afV[ iCol ] [ iRow ] = m_afV[ iRow ] [ iCol ] * fC;

	return kM;
}
//******************************************************************************
Matrix Matrix::operator / ( Real fC ) const
{
	UInt iRow, iCol;
	static Matrix kM;
	
	if( fC == (Real)0.0f )
	{
		for ( iRow = 0; iRow < 4; iRow++ )
		{
			for ( iCol = 0; iCol < 4; iCol++ )
			{
				kM.m_afV[ iRow ] [ iCol ] = INFINITY;
			}
		}		
	}
	else
	{
        Real fInvC = ((Real)1.0)/fC;
		for ( UInt iRow = 0; iRow < 4; iRow++ )
			for ( UInt iCol = 0; iCol < 4; iCol++ )
				kM.m_afV[ iCol ] [ iRow ] = m_afV[ iRow ] [ iCol ] * fInvC;
	}

	return kM;
}
//******************************************************************************
Vector Matrix::operator * ( const Vector & rkV ) const
{
	Vector kV(
	
	    (	m_afV[ 0 ] [ 0 ] * rkV.x() + 
			m_afV[ 1 ] [ 0 ] * rkV.y() + 
			m_afV[ 2 ] [ 0 ] * rkV.z() + 
			m_afV[ 3 ] [ 0 ] ),
			
	    ( 	m_afV[ 0 ] [ 1 ] * rkV.x() + 
			m_afV[ 1 ] [ 1 ] * rkV.y() + 
			m_afV[ 2 ] [ 1 ] * rkV.z() + 
			m_afV[ 3 ] [ 1 ] ),
			
	    ( 	m_afV[ 0 ] [ 2 ] * rkV.x() + 
			m_afV[ 1 ] [ 2 ] * rkV.y() + 
			m_afV[ 2 ] [ 2 ] * rkV.z() + 
			m_afV[ 3 ] [ 2 ] )
	);
	return ( kV );
}
//******************************************************************************
Matrix Matrix::buildRotation( const Vector & rkFrom, const Vector & rkTo )
{
	// compute dot product between From and To
	Real fCosAngle = rkFrom.dot( rkTo );

	Real fEpsilon = 10e-4;
	if ( Abs( fCosAngle - 1 ) < fEpsilon ) 	/// dot product close to 1.0
	{
		// rotate by an angle of zero with an arbitrary direction
		return buildRotation( 0.0, 1 );	// use y axis
	}
	else
		if ( Abs( fCosAngle + 1.0 ) < fEpsilon ) 	// dot product close to 0.0
		{
			// find an orthogonal direction to create axis
			Vector kOrtho;

			if ( Abs( rkFrom.x() ) < Abs( rkFrom.y() ) )
			{
				if ( Abs( rkFrom.x() ) < Abs( rkFrom.z() ) )
				{
					kOrtho = Vector( 1.0, 0.0, 0.0 );	// use x axis.
				}
				else
				{
					kOrtho = Vector( 0.0, 0.0, 1.0 );	// use z axis
				}
			}
			else
				if ( Abs( rkFrom.y() ) < Abs( rkFrom.z() ) )
				{
					kOrtho = Vector( 0.0, 1.0, 0.0 );	// use y axis
				}
				else
				{
					kOrtho = Vector( 0.0, 0.0, 1.0 );	// use z axis
				}

			// find orthogonal axis to use for rotation
			Vector kAxis( rkFrom.cross( kOrtho ) );	// Axis = From x Ortho (cross prod)
			kAxis.normalize();

			Real fAngle = ArcCosine( fCosAngle );	// find rotation angle

			// create new rotation matrix about new axis
			return buildRotation( fAngle, kAxis );
		}
		else
		{
			// find orthogonal axis to use for rotation
			Vector kAxis( rkFrom.cross( rkTo ) );	// Axis = From x To (cross prod)
			Real fAngle = ArcCosine( fCosAngle );	// find rotation angle

			// create new rotation matrix about new axis
			return buildRotation( fAngle, kAxis );
		}
}
//******************************************************************************
Matrix Matrix::buildTransform( const Vector & rkT, const Matrix & rkR, const Vector & rkS )
{
	Matrix kT(
	    rkS.x() * rkR.m_afV[ 0 ] [ 0 ], rkS.y() * rkR.m_afV[ 0 ] [ 1 ],
	    rkS.z() * rkR.m_afV[ 0 ] [ 2 ], 0.0f,
	    rkS.x() * rkR.m_afV[ 1 ] [ 0 ], rkS.y() * rkR.m_afV[ 1 ] [ 1 ],
	    rkS.z() * rkR.m_afV[ 1 ] [ 2 ], 0.0f,
	    rkS.x() * rkR.m_afV[ 2 ] [ 0 ], rkS.y() * rkR.m_afV[ 2 ] [ 1 ],
	    rkS.z() * rkR.m_afV[ 2 ] [ 2 ], 0.0f,
	    rkT.x(), rkT.y(), rkT.z(), 1.0f );

	return kT;
}
//******************************************************************************
Matrix Matrix::buildIdentity()
{
	Matrix kM(
	    1.0, 0.0, 0.0, 0.0,
	    0.0, 1.0, 0.0, 0.0,
	    0.0, 0.0, 1.0, 0.0,
	    0.0, 0.0, 0.0, 1.0 );
	return kM;
}
//******************************************************************************
Matrix Matrix::buildScale( const Vector & rkV )
{
	Matrix kM;
	kM.m_afV[ 0 ] [ 0 ] = rkV.x();
	kM.m_afV[ 1 ] [ 1 ] = rkV.y();
	kM.m_afV[ 2 ] [ 2 ] = rkV.z();
	return kM;
}
//******************************************************************************
Matrix Matrix::buildTranslation( const Vector & rkV )
{
	Matrix kM;
	kM.m_afV[ 0 ] [ 3 ] = rkV.x();
	kM.m_afV[ 1 ] [ 3 ] = rkV.y();
	kM.m_afV[ 2 ] [ 3 ] = rkV.z();
	return kM;
}
//******************************************************************************
Matrix Matrix::buildRotation( Real fX, Real fY, Real fZ )
{
	Matrix kX = buildRotation( fX, 0 );
	Matrix kY = buildRotation( fY, 1 );
	Matrix kZ = buildRotation( fZ, 2 );

	return kZ * ( kY * kX );
}
//******************************************************************************
Matrix Matrix::buildRotation( const Vector & rkV )
{
	Matrix kX = buildRotation( rkV.x(), 0 ); /// X axis
	Matrix kY = buildRotation( rkV.y(), 1 ); /// Y axis
	Matrix kZ = buildRotation( rkV.z(), 2 ); /// Z axis

	return kZ * ( kY * kX );
}
//******************************************************************************
Matrix Matrix::buildRotation( Real fA, Vector & rkDir )
{
	rkDir.normalize();

	//	dA *= -M_PI_OVER_180;
	fA = Radians( fA );
	Real fCos = Cosine( fA );
	Real fSin = Cosine( fA );

	Matrix kM;
	kM.m_afV[ 0 ] [ 0 ] = ( rkDir.x() * rkDir.x() ) * 
						  ( 1.0 - fCos ) + fCos;
	kM.m_afV[ 0 ] [ 1 ] = ( rkDir.x() * rkDir.y() ) * 
						  ( 1.0 - fCos ) - ( rkDir.z() * fSin );
	kM.m_afV[ 0 ] [ 2 ] = ( rkDir.x() * rkDir.z() ) * 
						  ( 1.0 - fCos ) + ( rkDir.y() * fSin );

	kM.m_afV[ 1 ] [ 0 ] = ( rkDir.y() * rkDir.x() ) * 
						  ( 1.0 - fCos ) + ( rkDir.z() * fSin );
	kM.m_afV[ 1 ] [ 1 ] = ( rkDir.y() * rkDir.y() ) * 
						  ( 1.0 - fCos ) + fCos;
	kM.m_afV[ 1 ] [ 2 ] = ( rkDir.y() * rkDir.z() ) * 
						  ( 1.0 - fCos ) - ( rkDir.x() * fSin );

	kM.m_afV[ 2 ] [ 0 ] = ( rkDir.z() * rkDir.x() ) * 
						  ( 1.0 - fCos ) - ( rkDir.y() * fSin );
	kM.m_afV[ 2 ] [ 1 ] = ( rkDir.z() * rkDir.y() ) * 
						  ( 1.0 - fCos ) + ( rkDir.x() * fSin );
	kM.m_afV[ 2 ] [ 2 ] = ( rkDir.z() * rkDir.z() ) * 
						  ( 1.0 - fCos ) + fCos;

	kM.m_afV[ 0 ] [ 3 ] = kM.m_afV[ 1 ] [ 3 ] = kM.m_afV[ 2 ] [ 3 ] = 0;
	kM.m_afV[ 3 ] [ 0 ] = kM.m_afV[ 3 ] [ 1 ] = kM.m_afV[ 3 ] [ 2 ] = 0;
	kM.m_afV[ 3 ] [ 3 ] = 1.0;

	return kM;
}
//******************************************************************************
Matrix Matrix::buildRotation( Real fA, UInt eAxis )
{
	//	dA *= M_PI_OVER_180;
	fA = Radians( fA );
	Real fCos = Cosine( fA );
	Real fSin = Sine( fA );

	Matrix kM( Matrix::IDENTITY );

	switch ( eAxis )
	{
			/// X axis
		case( 0 ) :
			{
				kM.m_afV[ 1 ] [ 1 ] = fCos;
				kM.m_afV[ 1 ] [ 2 ] = -fSin;
				kM.m_afV[ 2 ] [ 1 ] = fSin;
				kM.m_afV[ 2 ] [ 2 ] = fCos;
				break;
			}
			/// Y axis
		case( 1 ) :
			{
				kM.m_afV[ 0 ] [ 0 ] = fCos;
				kM.m_afV[ 0 ] [ 2 ] = fSin;
				kM.m_afV[ 2 ] [ 0 ] = -fSin;
				kM.m_afV[ 2 ] [ 2 ] = fCos;
				break;
			}
			/// Z axis
		case( 2 ) :
			{
				kM.m_afV[ 0 ] [ 0 ] = fCos;
				kM.m_afV[ 0 ] [ 1 ] = -fSin;
				kM.m_afV[ 1 ] [ 0 ] = fSin;
				kM.m_afV[ 1 ] [ 1 ] = fCos;
				break;
			}
	};

	return kM;
}
/*
//------------------------------------------------------------------------------
Matrix Matrix::buildPerspective( const Frustum & rkF )
{
	Matrix kM;

	kM.m_afV[ 0 ] [ 0 ] = ( 2.0f * rkF.near() ) / ( rkF.right() - rkF.left() );
	kM.m_afV[ 0 ] [ 1 ] = 0.0f;
	kM.m_afV[ 0 ] [ 2 ] = ( rkF.right() + rkF.left() ) / ( rkF.right() - rkF.left() );
	kM.m_afV[ 0 ] [ 3 ] = 0.0f;

	kM.m_afV[ 1 ] [ 0 ] = 0.0f;
	kM.m_afV[ 1 ] [ 1 ] = ( 2.0f * rkF.near() ) / ( rkF.top() - rkF.bottom() );
	kM.m_afV[ 1 ] [ 2 ] = ( rkF.top() + rkF.bottom() ) / ( rkF.top() - rkF.bottom() );
	kM.m_afV[ 1 ] [ 3 ] = 0.0f;

	kM.m_afV[ 2 ] [ 0 ] = 0.0f;
	kM.m_afV[ 2 ] [ 1 ] = 0.0f;
	kM.m_afV[ 2 ] [ 2 ] = -( rkF.far() + rkF.near() ) / ( rkF.far() - rkF.near() );
	kM.m_afV[ 2 ] [ 3 ] = -( 2.0f * rkF.far() * rkF.near() ) / ( rkF.far() - rkF.near() );

	kM.m_afV[ 3 ] [ 0 ] = 0.0f;
	kM.m_afV[ 3 ] [ 1 ] = 0.0f;
	kM.m_afV[ 3 ] [ 2 ] = 0.0f;
	kM.m_afV[ 3 ] [ 3 ] = 1.0f;

	return kM;
}
//------------------------------------------------------------------------------
Matrix Matrix::buildOrthographic( const Frustum & rkF )
{
	Matrix kM;

	kM.m_afV[ 0 ] [ 0 ] = 2.0f / ( rkF.right() - rkF.left() );
	kM.m_afV[ 0 ] [ 1 ] = 0.0f;
	kM.m_afV[ 0 ] [ 2 ] = 0.0f;
	kM.m_afV[ 0 ] [ 3 ] = -( rkF.right() + rkF.left() ) / ( rkF.right() - rkF.left() );

	kM.m_afV[ 1 ] [ 0 ] = 0.0f;
	kM.m_afV[ 1 ] [ 1 ] = 2.0f / ( rkF.top() - rkF.bottom() );
	kM.m_afV[ 1 ] [ 2 ] = 0.0f;
	kM.m_afV[ 1 ] [ 3 ] = -( rkF.top() + rkF.bottom() ) / ( rkF.top() - rkF.bottom() );

	kM.m_afV[ 2 ] [ 0 ] = 0.0f;
	kM.m_afV[ 2 ] [ 1 ] = 0.0f;
	kM.m_afV[ 2 ] [ 2 ] = -2.0f / ( rkF.far() - rkF.near() );
	kM.m_afV[ 2 ] [ 3 ] = -( rkF.far() + rkF.near() ) / ( rkF.far() - rkF.near() );

	kM.m_afV[ 3 ] [ 0 ] = 0.0f;
	kM.m_afV[ 3 ] [ 1 ] = 0.0f;
	kM.m_afV[ 3 ] [ 2 ] = 0.0f;
	kM.m_afV[ 3 ] [ 3 ] = 1.0f;

	return kM;
}
//------------------------------------------------------------------------------
Matrix Matrix::buildInversePerspective( const Frustum & rkF )
{
	Matrix kM;

	kM.m_afV[ 0 ] [ 0 ] = ( rkF.right() - rkF.left() ) / ( 2.0f * rkF.near() );
	kM.m_afV[ 0 ] [ 1 ] = 0.0f;
	kM.m_afV[ 0 ] [ 2 ] = 0.0f;
	kM.m_afV[ 0 ] [ 3 ] = ( rkF.right() + rkF.left() ) / ( 2.0f * rkF.near() );

	kM.m_afV[ 1 ] [ 0 ] = 0.0f;
	kM.m_afV[ 1 ] [ 1 ] = ( rkF.top() - rkF.bottom() ) / ( 2.0f * rkF.near() );
	kM.m_afV[ 1 ] [ 2 ] = 0.0f;
	kM.m_afV[ 1 ] [ 3 ] = ( rkF.top() + rkF.bottom() ) / ( 2.0f * rkF.near() );

	kM.m_afV[ 2 ] [ 0 ] = 0.0f;
	kM.m_afV[ 2 ] [ 1 ] = 0.0f;
	kM.m_afV[ 2 ] [ 2 ] = 0.0f;
	kM.m_afV[ 2 ] [ 3 ] = 1.0f;

	kM.m_afV[ 3 ] [ 0 ] = 0.0f;
	kM.m_afV[ 3 ] [ 1 ] = 0.0f;
	kM.m_afV[ 3 ] [ 2 ] = -( rkF.far() - rkF.near() ) / ( 2.0f * rkF.far() * rkF.near() );
	kM.m_afV[ 3 ] [ 3 ] = ( rkF.far() + rkF.near() ) / ( 2.0f * rkF.far() * rkF.near() );

	return kM;
}
//------------------------------------------------------------------------------
*/
Matrix Matrix::fromAxisToAngle( const Vector & rkAxis, const Real fAngle )
{
	Real fRadians = Radians( fAngle );

	Real fCos = Cosine( fRadians );
	Real fSin = Sine( fRadians );
	Real fOneMinusCos = 1.0f - fCos;

	Real fX2 = Sqr( rkAxis.x() );
	Real fY2 = Sqr( rkAxis.y() );
	Real fZ2 = Sqr( rkAxis.z() );

	Real fXYM = rkAxis.x() * rkAxis.y() * fOneMinusCos;
	Real fXZM = rkAxis.x() * rkAxis.z() * fOneMinusCos;
	Real fYZM = rkAxis.y() * rkAxis.z() * fOneMinusCos;

	Real fXSin = rkAxis.x() * fSin;
	Real fYSin = rkAxis.y() * fSin;
	Real fZSin = rkAxis.z() * fSin;

	Matrix kM;
	kM.m_afV[ 0 ] [ 0 ] = fX2 * fOneMinusCos + fCos;
	kM.m_afV[ 1 ] [ 0 ] = fXYM - fZSin;
	kM.m_afV[ 2 ] [ 0 ] = fXZM + fYSin;
	kM.m_afV[ 3 ] [ 0 ] = 0.0f;

	kM.m_afV[ 0 ] [ 1 ] = fXYM + fZSin;
	kM.m_afV[ 1 ] [ 1 ] = fY2 * fOneMinusCos + fCos;
	kM.m_afV[ 2 ] [ 1 ] = fYZM - fXSin;
	kM.m_afV[ 3 ] [ 1 ] = 0.0f;

	kM.m_afV[ 0 ] [ 2 ] = fXZM - fYSin;
	kM.m_afV[ 1 ] [ 2 ] = fYZM + fXSin;
	kM.m_afV[ 2 ] [ 2 ] = fZ2 * fOneMinusCos + fCos;
	kM.m_afV[ 3 ] [ 2 ] = 0.0f;

	kM.m_afV[ 3 ] [ 0 ] = 0.0f;
	kM.m_afV[ 3 ] [ 1 ] = 0.0f;
	kM.m_afV[ 3 ] [ 2 ] = 0.0f;
	kM.m_afV[ 3 ] [ 3 ] = 1.0f;

	return kM;
}
//------------------------------------------------------------------------------

// #############################################################################
// constant definitions
// #############################################################################

//------------------------------------------------------------------------------
const Matrix Matrix::ZERO =
    Matrix(
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    );
//------------------------------------------------------------------------------
const Matrix Matrix::IDENTITY =
    Matrix(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
//------------------------------------------------------------------------------
