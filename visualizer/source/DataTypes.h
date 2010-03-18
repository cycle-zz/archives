// #############################################################################
// # DataTypes.h  - Typedefs for various datatypes
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

#ifndef DG_DATATYPES_H
#define DG_DATATYPES_H

#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>

//******************************************************************************

namespace dg
{

// #############################################################################
// DataTypes - Basic platform independent Datatypes
// #############################################################################

typedef bool			Bool;	// 1 bit (maybe...)
typedef char			Char;	// 8 bit
typedef unsigned char	UChar;	// 8 bit
typedef signed short    Short;	// 16 bit
typedef unsigned short  UShort;	// 16 bit
typedef signed int      Int;	// 32 bit
typedef unsigned int    UInt;	// 32 bit
typedef signed long     Long;	// 32 bit
typedef unsigned long   ULong;	// 32 bit
typedef float			Float;	// 32 bit
typedef double			Double;	// 64 bit
//typedef long double		LongDouble;	// 128 bit

typedef signed char     Int8;	// 8 bit
typedef signed short    Int16;	// 16 bit
typedef signed long     Int32;	// 32 bit
typedef unsigned char   UInt8;	// 8 bit
typedef unsigned short  UInt16;	// 16 bit
typedef unsigned long   UInt32;	// 32 bit

typedef float			Real32;	// 32 bit
typedef double			Real64;	// 64 bit
typedef float			Real;	// default real
//******************************************************************************
#ifdef WIN32
#define isnan _isnan
#define isinf(f) (!_finite((f)))
#endif

#ifdef __APPLE_
extern "C" {
  int isinf(double);
  int isnan(double);
}
#endif // __APPLE__
//******************************************************************************
inline bool IsNaN(Real fV)
{
	return isnan(fV);
}
//******************************************************************************
inline bool IsInf(Real fV)
{
	return isinf(fV);
}
//******************************************************************************
inline Real Validate(Real fV)
{
	if(IsInf(fV) || IsNaN(fV))
		return 0;
	else
		return fV;	
}
//******************************************************************************

} // end namespace: dg

//******************************************************************************

#endif  // end file: DataTypes.h
