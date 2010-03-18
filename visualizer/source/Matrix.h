// start file: Matrix.h

// #############################################################################
// #
// # Derek Gerstmann
// # dgerstma@u.washington.edu
// #
// #############################################################################

#ifndef DG_MATRIX_H
#define DG_MATRIX_H

#include "DataTypes.h"
#include "Maths.h"
#include "Vector.h"
#include "Matrix.h"


// -----------------------------------------------------------------------------

namespace dg
{
	
class Transform;

//******************************************************************************
// Matrix - Basic 4x4 mathematical matrix (right handed, row-column ordering)
//******************************************************************************

class Matrix
{

public:

	// give transform access to private data members
	friend class Transform;
	
	Matrix();
	
	Matrix(
		Real fV00, Real fV01, Real fV02, Real fV03,
		Real fV10, Real fV11, Real fV12, Real fV13,
		Real fV20, Real fV21, Real fV22, Real fV23,
		Real fV30, Real fV31, Real fV32, Real fV33 );

	Matrix( const Real afV[4] [4] );
	Matrix::Matrix(Real afV[16]);
	Matrix( const Vector & rkW, const Vector & rkV, const Vector & rkU );
	
	//inline operator const Real** () const
	//{
	//	return m_afV;
	//}

	inline operator Real** ()
	{
		return (Real**)m_afV;
	}
	
	const Real * values() const;
	Real * values();
	
	void setValues( const Real** afV );
	void setValues( const Real afV[16] );
	
	void setBase( const Vector & rkW, const Vector & rkV, const Vector & rkU );
	void getBase( Vector & rkW, Vector & rkV, Vector & rkU ) const;

	void getRow( UInt uiRow, Vector & rkV ) const;
	void getColumn( UInt uiCol, Vector & rkV ) const;

	// arithmetic operations
	Matrix operator+ (const Matrix& rkM) const;
	Matrix operator- (const Matrix& rkM) const;
	Matrix operator* (const Matrix& rkM) const;
	Matrix operator* (Real fScalar) const;
	Matrix operator/ (Real fScalar) const;
	Matrix operator- () const;

	// arithmetic updates
	Matrix& operator+= (const Matrix& rkM);
	Matrix& operator-= (const Matrix& rkM);
	Matrix& operator*= (const Matrix& rkM);
	Matrix& operator*= (Real fScalar);
	Matrix& operator/= (Real fScalar);

	Vector operator * ( const Vector & rkV ) const;

	void identity();
	void zero();

	Matrix transpose() const;
	Matrix inverse() const;

	//	Utility functions
	static Matrix buildIdentity();
	static Matrix buildScale( const Vector & rkS );
	static Matrix buildRotation( Real fA, Vector & rkDir );
	static Matrix buildRotation( Real fX, Real fY, Real fZ );
	static Matrix buildRotation( const Vector & rkFrom, const Vector & rkTo );
	static Matrix buildRotation( const Vector & rkA );
	static Matrix buildRotation( Real dA, UInt eAxis );
	static Matrix buildTranslation( const Vector & rkT );
	static Matrix buildTransform( const Vector & rkT, 
								  const Matrix & rkR, 
								  const Vector & rkS );

//	static Matrix buildPerspective( const Frustum & rkF );
//	static Matrix buildOrthographic( const Frustum & rkF );
//	static Matrix buildInversePerspective( const Frustum & rkF );
	static Matrix fromAxisToAngle( const Vector & rkAxis, const Real dAngle );

	// special matrices
	static const Matrix ZERO;
	static const Matrix IDENTITY;

private:

	Real m_afV[4][4];	//	stored as: [column][row]

};

// -----------------------------------------------------------------------------

#include "Matrix.inc"

// -----------------------------------------------------------------------------

} // end namespace: dg

#endif // endif: Matrix.h

//end file: Matrix.h
