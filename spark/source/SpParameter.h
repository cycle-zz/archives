// #############################################################################
//! SpParameter.h : Storage class for multiple data types for use with GPU programs
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

#ifndef SP_PARAMETER_H
#define SP_PARAMETER_H

#include "SpReference.h"
#include <cstring>

// ---------------------------------------------------------------------------

namespace Spark
{

// ---------------------------------------------------------------------------
//! Storage class for multiple data types for use with GPU programs
// ---------------------------------------------------------------------------
class SpParameter
{

//! Enumerations:
public:

	//: Valid SpParameter Types
	enum Type
	{
		PT_NONE,
		PT_BOOL,
		PT_INT,
		PT_IVEC2,
		PT_IVEC3,
		PT_IVEC4,
		PT_FLOAT,
		PT_VEC2,
		PT_VEC3,
		PT_VEC4,
		PT_MAT2,
		PT_MAT3,
		PT_MAT4,
		PT_MAX_COUNT
	};

	//! Valid SpParameter Options
	enum Option
	{
		PO_NONE,
		PO_COLOR,
		PO_MAX_COLOR
	};

//! Construction:
public:

	SpParameter ();

	SpParameter (
		const char* acName,
		SpParameter::Type eType,
		unsigned int uiRegister=0,
		int iCount=1,
		SpParameter::Option eOption = PO_NONE);

	SpParameter (
		const char* acName,
		const float* afData,
		int iCount,
		SpParameter::Type eType,
		unsigned int uiRegister=0,
		SpParameter::Option eOption = PO_NONE);

	SpParameter (
		const char* acName,
		bool bEnable,
		unsigned int uiRegister=0,
		SpParameter::Option eOption = PO_NONE);

	SpParameter (
		const char* acName,
		int iX,
		unsigned int uiRegister=0,
		SpParameter::Option eOption = PO_NONE);

	SpParameter (
		const char* acName,
		int iX,
		int iY,
		unsigned int uiRegister=0,
		SpParameter::Option eOption = PO_NONE);

	SpParameter (
		const char* acName,
		int iX,
		int iY,
		int iZ,
		unsigned int uiRegister=0,
		SpParameter::Option eOption = PO_NONE);

	SpParameter (
		const char* acName,
		float fX,
		unsigned int uiRegister=0,
		SpParameter::Option eOption = PO_NONE);

	SpParameter (
		const char* acName,
		float fX,
		float fY,
		unsigned int uiRegister=0,
		SpParameter::Option eOption = PO_NONE);

	SpParameter (
		const char* acName,
		float fX,
		float fY,
		float fZ,
		unsigned int uiRegister=0,
		SpParameter::Option eOption = PO_NONE);

	SpParameter (const SpParameter* pkSpParameter);
	SpParameter (const SpParameter& rkConst);
	virtual ~SpParameter ();
	void destroy();

//! Assignment:
public:

	SpParameter& operator= (const SpParameter& rkConst);

//! Access Methods:
public:

	const char* getName() const;

	int getSize () const;
	int getSize( SpParameter::Type eType) const;

	int getCount () const;

	SpParameter::Type getType () const;

	SpParameter::Option getOption () const;
	void setOption (SpParameter::Option eOption);

	unsigned int getRegister () const;
	void setRegister (unsigned int uiRegister);

	const void* getData () const;
	// void* getData ();

	void setData (bool bEnable);

	void setData (int iX);
	void setData (int iX, int iY);
	void setData (int iX, int iY, int iZ);
	void setData (int iX, int iY, int iZ, int iW);

	void setData (float fX);
	void setData (float fX, float fY);
	void setData (float fX, float fY, float fZ);
	void setData (float fX, float fY, float fZ, float fW);

	void setData (const float akData[2][2]);
	void setData (const float akData[3][3]);
	void setData (const float akData[4][4]);

	void setData (const void* pvData, int iCount, SpParameter::Type eType);

	bool isNamed (const char* acName) const;
	bool isBoolean() const;
	bool isInteger() const;
	bool isFloat() const;
	bool hasChanged() const;
	void setChanged(bool bChanged = false);

//! Internal Data:
protected:

	unsigned int m_uiRegister;

	void *m_pvData;

	int m_iSize;
	int m_iCount;

	SpParameter::Type m_eType;
	SpParameter::Option m_eOption;

	char* m_acName;
	bool m_bHasChanged;

	EnableReferencing();
};

// ---------------------------------------------------------------------------

#include "SpParameter.inc"

// ---------------------------------------------------------------------------

typedef SpReference< SpParameter > SpParameterPtr;

// ---------------------------------------------------------------------------

}	// end namespace: Spark

#endif
