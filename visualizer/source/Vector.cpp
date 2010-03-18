// start file: Vector.cpp
//
// #############################################################################
// # Vector.cpp  -  Implementation for 3D mathematical Vector
// #
// # Created 	: Sat Jan 10 2004
// # Copyright	: (C) 2004 by Derek Gerstmann
// # Email	: dgerstma@acm.org
// #
// #############################################################################

// headers
#include "Vector.h"
#include "DataTypes.h"
// -----------------------------------------------------------------------------

// #############################################################################
// Vector - Generic 3D mathematical Vector class
// #############################################################################

using namespace dg;

// -----------------------------------------------------------------------------
Vector::Vector( Real x, Real y, Real z )
{
	m_adC[0] = x;
	m_adC[1] = y;
	m_adC[2] = z;
}
// -----------------------------------------------------------------------------
Vector::Vector( const Vector & rkReal )
{
	m_adC[0] = rkReal.x();
	m_adC[1] = rkReal.y();
	m_adC[2] = rkReal.z();
}
//------------------------------------------------------------------------------
Vector Vector::operator + ( const Vector & rkVector ) const
{
	return Vector(
	m_adC[0] + rkVector.m_adC[0],
	m_adC[1] + rkVector.m_adC[1],
	m_adC[2] + rkVector.m_adC[2] );
}
//------------------------------------------------------------------------------
void Vector::operator += ( const Vector & rkVector )
{
	m_adC[0] += rkVector.m_adC[0];
	m_adC[1] += rkVector.m_adC[1];
	m_adC[2] += rkVector.m_adC[2];
}
//------------------------------------------------------------------------------
void Vector::operator ++( void )
{
	++m_adC[0];
	++m_adC[1];
	++m_adC[2];
}
//------------------------------------------------------------------------------
Vector Vector::operator - () const
{
	return Vector( -m_adC[0], -m_adC[1], -m_adC[2] );
}
//------------------------------------------------------------------------------
Vector Vector::operator - ( const Vector & rkVector ) const
{
	return Vector(
		m_adC[0] - rkVector.m_adC[0],
		m_adC[1] - rkVector.m_adC[1],
		m_adC[2] - rkVector.m_adC[2] );
}
//------------------------------------------------------------------------------
void Vector::operator -= ( const Vector & rkVector )
{
	m_adC[0] -= rkVector.m_adC[0];
	m_adC[1] -= rkVector.m_adC[1];
	m_adC[2] -= rkVector.m_adC[2];
}
//------------------------------------------------------------------------------
void Vector::operator --( void )
{
	--m_adC[0];
	--m_adC[1];
	--m_adC[2];
}
//------------------------------------------------------------------------------
Vector Vector::operator * ( const Vector & rkVector ) const
{
	return Vector(
		m_adC[0] * rkVector.m_adC[0],
		m_adC[1] * rkVector.m_adC[1],
		m_adC[2] * rkVector.m_adC[2] );
}
//------------------------------------------------------------------------------
void Vector::operator *= ( const Vector & rkVector )
{
	m_adC[0] *= rkVector.m_adC[0];
	m_adC[1] *= rkVector.m_adC[1];
	m_adC[2] *= rkVector.m_adC[2];
}
//------------------------------------------------------------------------------
Vector Vector::operator * ( const int scalar ) const
{
	return Vector( m_adC[0] * scalar, m_adC[1] * scalar, m_adC[2] * scalar );
}
//------------------------------------------------------------------------------
void Vector::operator *= ( const int scalar )
{
	m_adC[0] *= scalar;
	m_adC[1] *= scalar;
	m_adC[2] *= scalar;
}
//------------------------------------------------------------------------------
Vector Vector::operator * ( const Real scalar ) const
{
	return Vector( m_adC[0] * scalar, m_adC[1] * scalar, m_adC[2] * scalar );
}
//------------------------------------------------------------------------------
void Vector::operator *= ( const Real scalar )
{
	m_adC[0] *= scalar;
	m_adC[1] *= scalar;
	m_adC[2] *= scalar;
}
//------------------------------------------------------------------------------
void Vector::operator = ( const Vector & rkVector )
{
	m_adC[0] = rkVector.m_adC[0];
	m_adC[1] = rkVector.m_adC[1];
	m_adC[2] = rkVector.m_adC[2];
}
//------------------------------------------------------------------------------
void Vector::zero()
{
	* this = Vector::ZERO;
}
//------------------------------------------------------------------------------
void Vector::negate()
{
	m_adC[0] = -m_adC[0];
	m_adC[1] = -m_adC[1];
	m_adC[2] = -m_adC[2];
}
//------------------------------------------------------------------------------
bool Vector::operator == ( const Vector & rkVector ) const
{
	return (
		m_adC[0] == rkVector.m_adC[0] &&
		m_adC[1] == rkVector.m_adC[1] &&
		m_adC[2] == rkVector.m_adC[2] );
}
//------------------------------------------------------------------------------
bool Vector::operator != ( const Vector & rkReal ) const
{
	return ( !( * this == rkReal ) );
}
//------------------------------------------------------------------------------
Real Vector::length() const
{
	return ( sqrt( x() * x() + y() * y() + z() * z() ) );
}
//------------------------------------------------------------------------------
Real Vector::lengthSquared() const
{
	return ( x() * x() + y() * y() + z() * z() );
}
//------------------------------------------------------------------------------
void Vector::normalize()
{
	Real fLengthSquared = x() * x() + y() * y() + z() * z();

	if( fLengthSquared > 0 )
	{
		Real fLength = sqrt( fLengthSquared );
		Real fScale = 1.0 / fLength;
		m_adC[0] *= fScale;
		m_adC[1] *= fScale;
		m_adC[2] *= fScale;
	}
}
//------------------------------------------------------------------------------
Real Vector::dot( const Vector & rkVector ) const
{
	return (
	rkVector.m_adC[0] * m_adC[0] +
	rkVector.m_adC[1] * m_adC[1] +
	rkVector.m_adC[2] * m_adC[2] );
}
//------------------------------------------------------------------------------
Vector Vector::cross( const Vector & rkVector ) const
{
	return Vector(
	( y() * rkVector.z() - z() * rkVector.y() ),
	( z() * rkVector.x() - x() * rkVector.z() ),
	( x() * rkVector.y() - y() * rkVector.x() ) );
}
//------------------------------------------------------------------------------
void Vector::cross( const Vector & rkLHS, const Vector & rkRHS )
{
	m_adC[0] = ( rkLHS.y() * rkRHS.z() - rkLHS.z() * rkRHS.y() );
	m_adC[1] = ( rkLHS.z() * rkRHS.x() - rkLHS.x() * rkRHS.z() );
	m_adC[2] = ( rkLHS.x() * rkRHS.y() - rkLHS.y() * rkRHS.x() );
}
//------------------------------------------------------------------------------
Real Vector::angle( const Vector rkVector ) const
{
	// angle = arcos( (A dot B) / (|A||B|) )
	Real dDot( dot( rkVector ) );
	Real dLA( length() );
	Real dLB( rkVector.length() );
	Real dDen( dLA * dLB );

	if( dDen > 0.0 )
		return acos( dDot / dDen );
	else
		return 0.0;
}
//------------------------------------------------------------------------------
Real dg::Dot(const Vector& rkA, const Vector& rkB )
{
	return (
		rkA.x() * rkB.x() +
		rkA.y() * rkB.y() +
		rkA.z() * rkB.z() 
	);
}
//------------------------------------------------------------------------------
Vector dg::Cross(const Vector& rkA, const Vector& rkB)
{
	return Vector(
		( rkA.y() * rkB.z() - rkA.z() * rkB.y() ),
		( rkA.z() * rkB.x() - rkA.x() * rkB.z() ),
		( rkA.x() * rkB.y() - rkA.y() * rkB.x() ) 
	);
}
//------------------------------------------------------------------------------
Vector dg::Min( const Vector & rkA, const Vector & rkB )
{
	Real fX, fY, fZ;
	if( rkA.x() < rkB.x() ) fX = rkA.x(); else fX = rkB.x();
	if( rkA.y() < rkB.y() ) fY = rkA.y(); else fY = rkB.y();
	if( rkA.z() < rkB.z() ) fZ = rkA.z(); else fZ = rkB.z();
	return Vector( fX, fY, fZ );
}
//------------------------------------------------------------------------------
Vector dg::Max( const Vector & rkA, const Vector & rkB )
{
	Real fX, fY, fZ;
	if( rkA.x() > rkB.x() ) fX = rkA.x(); else fX = rkB.x();
	if( rkA.y() > rkB.y() ) fY = rkA.y(); else fY = rkB.y();
	if( rkA.z() > rkB.z() ) fZ = rkA.z(); else fZ = rkB.z();
	return Vector( fX, fY, fZ );
}
//------------------------------------------------------------------------------
Vector dg::Normalize(const Vector& rkV)
{
	Vector kNV( rkV );
	Real fLengthSquared = kNV.lengthSquared();

	if( fLengthSquared > 0 )
	{
		Real fLength = sqrt( fLengthSquared );
		Real fScale = 1.0 / fLength;
		kNV.x() *= fScale;
		kNV.y() *= fScale;
		kNV.z() *= fScale;
	}
	return kNV;
}
//------------------------------------------------------------------------------
Vector dg::operator* ( Real fScalar, const Vector& rkV )
{
	return Vector( fScalar * rkV.x(),
				   fScalar * rkV.y(),
				   fScalar * rkV.z() );
}

// #############################################################################
// constant definitions
// #############################################################################

//----------------------------------------------------------------------------
const Vector Vector::ZERO = Vector( 0.0f, 0.0f, 0.0f );
//----------------------------------------------------------------------------

// end file: Vector.cpp
