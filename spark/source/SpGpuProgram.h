// #############################################################################
//! SpGpuProgram.h : Abstract base class for a GPU program
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

#ifndef SP_PROGRAM_H
#define SP_PROGRAM_H

#include "SpReference.h"

#include <memory>

// ---------------------------------------------------------------------------

namespace Spark
{

// ---------------------------------------------------------------------------
//! Abstract base class for a GPU program
// ---------------------------------------------------------------------------
class SpGpuProgram
{

//! Enumerations:
public:

	//: Valid SpGpuProgram Types
	enum Type
	{
		GPU_INVALID_PROGRAM,
		GPU_GLSL_VERTEX_PROGRAM,
		GPU_GLSL_FRAGMENT_PROGRAM,
		GPU_PROGRAM_COUNT,
	};

//! Construction:
public:

	virtual ~SpGpuProgram ();

//! Attributes:
public:

	char* getSource ();
	void setSource (const char* acSpGpuProgram);
	unsigned int getLength();

	SpGpuProgram::Type getType () const;

//! User Data Methods:
public:

	void setUserData (const void* pvData, int iSize);
	void getUserData (void* pvData, int iSize) const;

//! State Methods:
public:

	void setState();
	void resetState();

	void enableClientState(const char* acName);
	void disableClientState(const char* acName);

	void destroy();

//! Parameter Methods:
public:

	virtual bool setParameter1i(const char* acName, int iX);
	virtual bool setParameter2i(const char* acName, int iX, int iY);
	virtual bool setParameter3i(const char* acName, int iX, int iY, int iZ);
	virtual bool setParameter4i(const char* acName, int iX, int iY, int iZ, int iW);

	virtual bool setParameter1iv(const char* acName, const float *afValues, int iCount=1);
	virtual bool setParameter2iv(const char* acName, const float *afValues, int iCount=1);
	virtual bool setParameter3iv(const char* acName, const float *afValues, int iCount=1);
	virtual bool setParameter4iv(const char* acName, const float *afValues, int iCount=1);

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

	SpGpuProgram (SpGpuProgram::Type eType = GPU_INVALID_PROGRAM);

	char* m_acSource;
	char m_acUserData[8];

	unsigned int m_uiLength;

	SpGpuProgram::Type m_eType;

	EnableReferencing();
};

// ---------------------------------------------------------------------------

#include "SpGpuProgram.inc"

// ---------------------------------------------------------------------------

typedef SpReference< SpGpuProgram > SpGpuProgramPtr;

// ---------------------------------------------------------------------------

}	// end namespace: Spark

#endif
