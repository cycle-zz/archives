// #############################################################################
// # SpTuple.h	: Template Class for Mathematical SpTuples.
// #
// # Created 	: May 2004
// # Copyright	: (C) 2004 by Derek Gerstmann
// # Email		: dgerstma@acm.org
// #
// #############################################################################

// =============================================================================
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
// =============================================================================


#ifndef SP_TUPLE_H
#define SP_TUPLE_H

#include "SpMaths.h"

#include <memory>
#include <cassert>

// -----------------------------------------------------------------------------

namespace Spark
{

// -----------------------------------------------------------------------------
//! N-Dimensional data class with support for vector mathematics
// -----------------------------------------------------------------------------
template <unsigned int N, class Real>
class SpTuple
{

//! Construction
public:

	SpTuple ();
    SpTuple (Real fValue);
    SpTuple (const Real* afSpTuple, unsigned int uiN = N);
    SpTuple (const SpTuple& rkV);

//! Coordinate Access
public:

    const Real* values() const;
    Real* values();
    Real operator[] (unsigned int i) const;
    Real& operator[] (unsigned int i);

//! Assignment:
public:

    SpTuple& operator= (const SpTuple& rkV);

//! Comparison
public:

    bool operator== (const SpTuple& rkV) const;
    bool operator!= (const SpTuple& rkV) const;
    bool operator<  (const SpTuple& rkV) const;
    bool operator<= (const SpTuple& rkV) const;
    bool operator>  (const SpTuple& rkV) const;
    bool operator>= (const SpTuple& rkV) const;

//! Arithmetic:
public:

    SpTuple operator+ (const SpTuple& rkV) const;
    SpTuple operator- (const SpTuple& rkV) const;
    SpTuple operator+ (Real fScalar) const;
    SpTuple operator- (Real fScalar) const;
    SpTuple operator* (Real fScalar) const;
    SpTuple operator/ (Real fScalar) const;
    SpTuple operator- () const;

// Updates:
public:

    SpTuple& operator+= (const SpTuple& rkV);
    SpTuple& operator-= (const SpTuple& rkV);
    SpTuple& operator+= (Real fScalar);
    SpTuple& operator-= (Real fScalar);
    SpTuple& operator*= (Real fScalar);
    SpTuple& operator/= (Real fScalar);

//! Comparison:
protected:

    int compare(const SpTuple& rkV) const;

//! Internal Data:
protected:

	Real m_afValues[N];
};

// -----------------------------------------------------------------------------
//! 2D tuple data class with support for vector mathematics
// -----------------------------------------------------------------------------
template< class Real >
class SpTuple2 : public SpTuple<2, Real>
{

//! Construction
public:

	SpTuple2 (const SpTuple<2, Real>& rkV)
	: SpTuple<2, Real>( rkV ){ return; }

	SpTuple2(Real fX = 0, Real fY = 0)
	{ x() = fX; y() = fY; }

//! Position Coordinate Access:
public:

	Real x() const { return m_afValues[0]; }
	Real& x() { return m_afValues[0]; }
	Real y() const { return m_afValues[1]; }
	Real& y() { return m_afValues[1]; }

//! Texture Coordinate Access:
public:

	Real s() const { return m_afValues[0]; }
	Real& s() { return m_afValues[0]; }
	Real t() const { return m_afValues[1]; }
	Real& t() { return m_afValues[1]; }

};

// -----------------------------------------------------------------------------
//! 3D tuple data class with support for vector mathematics
// -----------------------------------------------------------------------------
template< class Real>
class SpTuple3 : public SpTuple<3, Real>
{

//! Construction
public:

	SpTuple3 (const SpTuple<3, Real>& rkV)
		: SpTuple<3, Real>( rkV ){ return; }

	SpTuple3(Real fX = 0, Real fY = 0, Real fZ = 0)
	{ x() = fX; y() = fY; z() = fZ; }

//! Position Coordinate Access:
public:

	Real x() const { return m_afValues[0]; }
	Real& x() { return m_afValues[0]; }
	Real y() const { return m_afValues[1]; }
	Real& y() { return m_afValues[1]; }
	Real z() const { return m_afValues[2]; }
	Real& z() { return m_afValues[2]; }

//! Color Component Access:
public:

	Real r() const { return m_afValues[0]; }
	Real& r() { return m_afValues[0]; }
	Real g() const { return m_afValues[1]; }
	Real& g() { return m_afValues[1]; }
	Real b() const { return m_afValues[2]; }
	Real& b() { return m_afValues[2]; }

//! Texture Coordinate Access:
public:

	Real s() const { return m_afValues[0]; }
	Real& s() { return m_afValues[0]; }
	Real t() const { return m_afValues[1]; }
	Real& t() { return m_afValues[1]; }
	Real p() const { return m_afValues[2]; }
	Real& p() { return m_afValues[2]; }
};

// -----------------------------------------------------------------------------
//! 4D tuple data class with support for vector mathematics
// -----------------------------------------------------------------------------
template< class Real>
class SpTuple4 : public SpTuple<4, Real>
{

//! Construction
public:

	SpTuple4 (const SpTuple<4, Real>& rkV)
		: SpTuple<4, Real>( rkV ){ return; }

	SpTuple4(Real fX = 0, Real fY = 0, Real fZ = 0, Real fW = 1)
	{ x() = fX; y() = fY; z() = fZ; w() = fW; }

//! Position Coordinate Access:
public:

	Real x() const { return m_afValues[0]; }
	Real& x() { return m_afValues[0]; }
	Real y() const { return m_afValues[1]; }
	Real& y() { return m_afValues[1]; }
	Real z() const { return m_afValues[2]; }
	Real& z() { return m_afValues[2]; }
	Real w() const { return m_afValues[3]; }
	Real& w() { return m_afValues[3]; }

//! Color Component Access:
public:

	Real r() const { return m_afValues[0]; }
	Real& r() { return m_afValues[0]; }
	Real g() const { return m_afValues[1]; }
	Real& g() { return m_afValues[1]; }
	Real b() const { return m_afValues[2]; }
	Real& b() { return m_afValues[2]; }
	Real a() const { return m_afValues[3]; }
	Real& a() { return m_afValues[3]; }

//! Texture Coordinate Access:
public:

	Real s() const { return m_afValues[0]; }
	Real& s() { return m_afValues[0]; }
	Real t() const { return m_afValues[1]; }
	Real& t() { return m_afValues[1]; }
	Real p() const { return m_afValues[2]; }
	Real& p() { return m_afValues[2]; }
	Real q() const { return m_afValues[3]; }
	Real& q() { return m_afValues[3]; }
};

// -----------------------------------------------------------------------------

template <unsigned int N, class Real>
SpTuple<N,Real> operator* (Real fScalar, const SpTuple<N,Real>& rkV);

template <unsigned int N, class Real>
Real Length( const SpTuple<N,Real>& rkV );

template <unsigned int N, class Real>
Real LengthSquared( const SpTuple<N,Real>& rkV );

template <unsigned int N, class Real>
Real Dot(const SpTuple<N,Real>& rkA, const SpTuple<N,Real>& rkB);

template <unsigned int N, class Real>
SpTuple<N,Real> Normalize(const SpTuple<N,Real>& rkV);

template <unsigned int N, class Real>
SpTuple<N,Real> Clamp(const SpTuple<N,Real>& rkV, Real fMin, Real fMax);

template <unsigned int N, class Real>
SpTuple<N,Real> Offset(const SpTuple<N,Real>& rkV, Real fOffset);

// -----------------------------------------------------------------------------

template <class Real>
SpTuple3<Real> Normalize(const SpTuple3<Real>& rkV);

template <class Real>
SpTuple3<Real> NormalizedCross(const SpTuple3<Real>& rkV1, const SpTuple3<Real> & rkV2);

template <class Real>
SpTuple3<Real> Cross(const SpTuple3<Real>& rkV1, const SpTuple3<Real> & rkV2);

// -----------------------------------------------------------------------------

template <class Real>
SpTuple4<Real> Normalize(const SpTuple4<Real>& rkV);

template <class Real>
SpTuple4<Real> NormalizedCross(const SpTuple4<Real>& rkV1, const SpTuple4<Real> & rkV2);

template <class Real>
SpTuple4<Real> Cross(const SpTuple4<Real>& rkV1, const SpTuple4<Real> & rkV2);

// -----------------------------------------------------------------------------

#include "SpTuple.inc"

// -----------------------------------------------------------------------------

typedef SpTuple2<float> vec2;
typedef SpTuple3<float> vec3;
typedef SpTuple4<float> vec4;

typedef SpTuple2<int> ivec2;
typedef SpTuple3<int> ivec3;
typedef SpTuple4<int> ivec4;

typedef SpTuple2<bool> bvec2;
typedef SpTuple3<bool> bvec3;
typedef SpTuple4<bool> bvec4;

typedef SpTuple2<float> float2;
typedef SpTuple3<float> float3;
typedef SpTuple4<float> float4;

typedef SpTuple2<float> SpVector2f;
typedef SpTuple3<float> SpVector3f;
typedef SpTuple4<float> SpVector4f;

typedef SpTuple3<char> SpColor3b;
typedef SpTuple4<char> SpColor4b;

typedef SpTuple3<unsigned char> SpColor3ub;
typedef SpTuple4<unsigned char> SpColor4ub;

typedef SpTuple3<int> SpColor3i;
typedef SpTuple4<int> SpColor4i;

typedef SpTuple3<unsigned int> SpColor3ui;
typedef SpTuple4<unsigned int> SpColor4ui;

typedef SpTuple3<float> SpColor3f;
typedef SpTuple4<float> SpColor4f;

// -----------------------------------------------------------------------------

}	// end namespace

#endif
