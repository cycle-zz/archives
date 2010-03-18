// #############################################################################
// # Vector.h  -  Header file for 3D mathematical Vector
// #
// # Created 	: Sat Jan 10 2004
// # Copyright	: (C) 2004 by Derek Gerstmann
// # Email	: dgerstma@acm.org
// #
// #############################################################################

#ifndef DG_VECTOR_H
#define DG_VECTOR_H

// headers
#include "DataTypes.h"

// -----------------------------------------------------------------------------

namespace dg
{

// #############################################################################
/// Vector - Generic 3D mathematical Vector class
// #############################################################################

class Vector
{

public:

	Vector(Real x=0.0f, Real y=0.0f, Real z=0.0f);
	Vector(const Vector & rkV);

	Real x() const;
	Real y() const;
	Real z() const;
	Real& x();
	Real& y();
	Real& z();

	// value methods
	operator const Real* () const;
	operator Real* ();

	// access methods
	const Real* values() const;
	const Vector& value() const;
	Real operator[] (int i) const;
	Real& operator[] (int i);

	// addition
	Vector operator+ (const Vector & rkVector) const;
	void operator+= (const Vector & rkVector);
	void operator++ (void);

	// subtraction
	Vector operator- () const;
	Vector operator- (const Vector & rkVector) const;
	void operator-= (const Vector & rkVector);
	void operator-- (void);

	// multiplication
	Vector operator* (const Vector & rkVector) const;
	void operator*= (const Vector & rkVector);
	Vector operator* (const int scalar) const;
	void operator*= (const int scalar);
	Vector operator* (const Real scalar) const;
	void operator*= (const Real scalar);

	// comparison
	void operator=(const Vector & rkVector);
	bool operator==(const Vector & rkVector) const;
	bool operator!=(const Vector & Value) const;

	// vector methods
	void zero();
	void negate();
	Real length() const;
	Real lengthSquared() const;
	void normalize();

	Real dot(const Vector& rkVector) const;
	Vector cross(const Vector& rkVector) const;
	void cross(const Vector& rkLHS, const Vector& rkRHS);
	Real angle(const Vector rkVector) const;

	// special vectors
	static const Vector ZERO;
	
private:

	Real m_adC[3];	// XYZ

}; // end class: Vector

#include "Vector.inc"
// -----------------------------------------------------------------------------

Vector operator* (Real fScalar, const Vector& rkV);

Real Dot(const Vector& rkA, const Vector& rkB );
Vector Cross(const Vector& rkLHS, const Vector& rkRHS);

Vector Min( const Vector & rkA, const Vector & rkB );
Vector Max( const Vector & rkA, const Vector & rkB );
Vector Normalize(const Vector& rkV);

Vector Min(const Vector& rkV);
Vector Max(const Vector& rkV);
//void Normalize(Vector& rkV);

// -----------------------------------------------------------------------------

} // end namespace: dg 

#endif // endif: VECTOR_H

// end file: Vector.h
