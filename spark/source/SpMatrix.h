// #############################################################################
//! SpSpMatrix.h : Mathematical SpMatrix class for vector algebra
//
// Created 		: Aug 2004
// Copyright	: (C) 2004 by Derek Gerstmann
// Email		: dgerstma@acm.org
//
// #############################################################################

// =============================================================================
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
// =============================================================================

#ifndef SP_MATRIX_H
#define SP_MATRIX_H

// ---------------------------------------------------------------------------
#include "SpSpTuple.h"

// ---------------------------------------------------------------------------

namespace Spark
{

// ---------------------------------------------------------------------------
//! NxN Matrix base class for vector algebra
// ---------------------------------------------------------------------------
template <unsigned int N, class Real>
class SpMatrix
{
public:

    SpMatrix ();
    SpMatrix (bool bZero);
    SpMatrix (const SpMatrix& rkM);

    // member access
    operator const Real* () const;
    operator Real* ();
    const Real* operator[] (unsigned int uiRow) const;
    Real* operator[] (unsigned int uiRow);
    Real operator() (unsigned int uiRow, unsigned int uiCol) const;
    Real& operator() (unsigned int uiRow, unsigned int uiCol);

    SpTuple<N,Real> getRow (unsigned int uiRow) const;
    void setRow (unsigned int uiRow, const SpTuple<N,Real>& rkV);

    SpTuple<N,Real> getColumn (unsigned int uiCol) const;
	void setColumn (unsigned int uiCol, const SpTuple<N,Real>& rkV);

    // assignment
    SpMatrix& operator= (const SpMatrix& rkM);

    // comparison
    bool operator== (const SpMatrix& rkM) const;
    bool operator!= (const SpMatrix& rkM) const;
    bool operator<  (const SpMatrix& rkM) const;
    bool operator<= (const SpMatrix& rkM) const;
    bool operator>  (const SpMatrix& rkM) const;
    bool operator>= (const SpMatrix& rkM) const;

    // arithmetic operations
    SpMatrix operator+ (const SpMatrix& rkM) const;
    SpMatrix operator- (const SpMatrix& rkM) const;
    SpMatrix operator* (const SpMatrix& rkM) const;
    SpMatrix operator* (Real fScalar) const;
    SpMatrix operator/ (Real fScalar) const;
    SpMatrix operator- () const;

    // arithmetic updates
    SpMatrix& operator+= (const SpMatrix& rkM);
    SpMatrix& operator-= (const SpMatrix& rkM);
    SpMatrix& operator*= (Real fScalar);
    SpMatrix& operator/= (Real fScalar);

    // matrix-vector operations
    SpTuple<N,Real> operator* (const SpTuple<N,Real>& rkV) const;  // M * v

protected:

    // support for comparisons
    int compare(const SpMatrix& rkM) const;

    Real m_afValues[N][N];
};

// ---------------------------------------------------------------------------

// c * M
template <unsigned int N, class Real>
SpMatrix<N,Real> operator* (Real fScalar, const SpMatrix<N,Real>& rkM);

// v^T * M
template <unsigned int N, class Real>
SpTuple<N,Real> operator* (const SpTuple<N,Real>& rkV, const SpMatrix<N,Real>& rkM);

// ---------------------------------------------------------------------------
//! 2x2 pMatrix class for vector algebra
// ---------------------------------------------------------------------------
template <class Real>
class SpMatrix2 : public SpMatrix<2,Real>
{
public:

    // construction
    SpMatrix2 ();
    SpMatrix2 (const SpMatrix2& rkM);
    SpMatrix2 (const SpMatrix<2,Real>& rkM);
    SpMatrix2 (Real fM00, Real fM01, Real fM10, Real fM11);
    SpMatrix2 (const Real afEntry[4], bool bRowMajor);
    SpMatrix2 (const SpTuple2<Real>& rkU, const SpTuple2<Real>& rkV, bool bColumns);
    SpMatrix2 (const SpTuple2<Real>* akV, bool bColumns);

    // create a diagonal matrix
    SpMatrix2 (Real fM00, Real fM11);

    // create a rotation matrix (positive angle - counterclockwise)
    SpMatrix2 (Real fAngle);

    // assignment
    SpMatrix2& operator= (const SpMatrix2& rkM);
    SpMatrix2& operator= (const SpMatrix<2,Real>& rkM);
};

// ---------------------------------------------------------------------------
//! 3x3 Matrix class for vector algebra
// ---------------------------------------------------------------------------
template <class Real>
class SpMatrix3 : public SpMatrix<3,Real>
{
public:
    // construction
    SpMatrix3();

	SpMatrix3(const SpMatrix3& rkM);

	SpMatrix3(const SpMatrix<3,Real>& rkM);

	SpMatrix3(Real fM00, Real fM01, Real fM02,
            Real fM10, Real fM11, Real fM12,
            Real fM20, Real fM21, Real fM22);

    SpMatrix3 (const Real afEntry[9], bool bRowMajor);

	SpMatrix3 (const SpTuple3<Real>& rkU, const SpTuple3<Real>& rkV,
		     const SpTuple3<Real>& rkW, bool bColumns);

    SpMatrix3 (const SpTuple3<Real>* akV, bool bColumns);

    // Create rotation matrices (positive angle - counterclockwise).  The
    // angle must be in radians, not degrees.
    SpMatrix3 (const SpTuple3<Real>& rkAxis, Real fAngle);
    void FromAxisAngle (const SpTuple3<Real>& rkAxis, Real fAngle);

    // assignment
    SpMatrix3& operator= (const SpMatrix3& rkM);
    SpMatrix3& operator= (const SpMatrix<3,Real>& rkM);
};

// ---------------------------------------------------------------------------
//! 4x4 Matrix class for vector algebra
// ---------------------------------------------------------------------------
template <class Real>
class SpMatrix4 : public SpMatrix<4,Real>
{
public:

    // construction
    SpMatrix4 ();

	SpMatrix4 (const SpMatrix4& rkM);

    SpMatrix4 (const SpMatrix<4,Real>& rkM);

    SpMatrix4 (Real fM00, Real fM01, Real fM02, Real fM03,
             Real fM10, Real fM11, Real fM12, Real fM13,
             Real fM20, Real fM21, Real fM22, Real fM23,
             Real fM30, Real fM31, Real fM32, Real fM33);

    SpMatrix4 (const Real afEntry[16], bool bRowMajor);

    // assignment
    SpMatrix4& operator= (const SpMatrix4& rkM);
    SpMatrix4& operator= (const SpMatrix<4,Real>& rkM);

};

// ---------------------------------------------------------------------------

}

// ---------------------------------------------------------------------------

#endif
