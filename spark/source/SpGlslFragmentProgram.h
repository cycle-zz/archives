// #############################################################################
//! SpGlslFragmentProgram.h : Interface for a GLSL Fragment Program
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

#ifndef SP_GLSL_FRAGMENT_PROGRAM_H
#define SP_GLSL_FRAGMENT_PROGRAM_H

#include "SpGpuProgram.h"

// ---------------------------------------------------------------------------

namespace Spark
{

// ---------------------------------------------------------------------------
//! Interface for a GLSL Fragment Program
// ---------------------------------------------------------------------------
class SpGlslFragmentProgram : public SpGpuProgram
{

//! Construction:
public:

	SpGlslFragmentProgram (const char* acSource);

//! Parameter Methods:
public:

	virtual bool setParameter1i(const char* acName, int iX);
    virtual bool setParameter2i(const char* acName, int iX, int iY);
    virtual bool setParameter3i(const char* acName, int iX, int iY, int iZ);
	virtual bool setParameter4i(const char* acName, int iX, int iY, int iZ, int iW);

	virtual bool setParameter1iv(const char* acName, const int *aiValues, int iCount=1);
    virtual bool setParameter2iv(const char* acName, const int *aiValues, int iCount=1);
    virtual bool setParameter3iv(const char* acName, const int *aiValues, int iCount=1);
    virtual bool setParameter4iv(const char* acName, const int *aiValues, int iCount=1);

	virtual bool setParameter1f(const char* acName, float fX);
    virtual bool setParameter2f(const char* acName, float fX, float fY);
    virtual bool setParameter3f(const char* acName, float fX, float fY, float fZ);
	virtual bool setParameter4f(const char* acName, float fX, float fY, float fZ, float fW);

	virtual bool setParameter1fv(const char* acName, const float *afValues, int iCount=1);
    virtual bool setParameter2fv(const char* acName, const float *afValues, int iCount=1);
    virtual bool setParameter3fv(const char* acName, const float *afValues, int iCount=1);
    virtual bool setParameter4fv(const char* acName, const float *afValues, int iCount=1);

	virtual bool setMatrixParameter2fv(const char* acName, const float *afValues, int iCount=1);
    virtual bool setMatrixParameter3fv(const char* acName, const float *afValues, int iCount=1);
    virtual bool setMatrixParameter4fv(const char* acName, const float *afValues, int iCount=1);


//! Internal Data:
protected:

    //: Access to default constructor is restricted.
    SpGlslFragmentProgram ();

	//: Returns a register index for the parameter name, or -1 if an error occured
	int getParameterRegister( const char* acName );

};

// ---------------------------------------------------------------------------

}	// end namespace: Spark

#endif
