// #############################################################################
//! SpString.h : String utility class for character data
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


#ifndef SP_STRING_H
#define SP_STRING_H

// headers
#include <string>
#include <sstream>
#include <vector>
#include <list>

using std::vector;
using std::list;
using std::string;
using std::stringstream;

// ---------------------------------------------------------------------------

namespace Spark
{

// ---------------------------------------------------------------------------

#if WCHAR_STRINGS
    typedef std::wstring SpStringBase;
#else
    typedef std::string SpStringBase;
#endif

class SpString;
typedef std::stringstream SpStringStreamType;
typedef std::vector<SpString> SpStringArray;
typedef std::list<SpString> SpStringList;
typedef std::pair<SpString, SpString> SpStringPair;

// ---------------------------------------------------------------------------
//! String utility class for character data
// ---------------------------------------------------------------------------
class SpString : public SpStringBase
{

//! Typedefs:
public:

	typedef size_type SizeType;

//! Construction:
public:

	SpString();
	SpString(const SpString& rkStr);
	SpString(const string& rkStr);
	SpString(const char* acStr);
	SpString(const char* acStr, SizeType kLength);
	SpString(const SpString& rkStr, SizeType kStart, SizeType kEnd);
	SpString(SizeType kLength, char c);

//! Operations:
public:

	inline SpString& operator=(const SpString& rkStr);
	inline SpString& operator=(const std::string& rkStr);
	inline SpString& operator=(const char *acStr);
	inline SpString& operator=(char c);

	// append data from various sources
	inline SpString& operator+=(const SpString& rkStr);
	inline SpString& operator+=(const std::string& rkStr);
	inline SpString& operator+=(const char *acStr);
	inline SpString& operator+=(char c);

	// append data from various sources
	inline SpString& operator+(const SpString& rkStr);
	inline SpString& operator+(const std::string& rkStr);
	inline SpString& operator+(const char *acStr);
	inline SpString& operator+(char c);

	// test equality and inequality (case sensitive)
	//inline bool operator==(const SpString& rkStr);
	//inline bool operator!=(const SpString& rkStr);

//! Utilites:
public:

	// clear method (for older stdlibs that don't have it)
	void clear();

	// template operator for appending another type into the string.
	template<class Class> SpString& add(const Class &rtValue);

	// c-string support
	inline operator const char* () const;

	// operator that allows SpString to be used as an STL map key value
	inline bool operator<(const SpString& rkStr);

	// special strings
	static const SpString EMPTY;

};
// ---------------------------------------------------------------------------

#include "SpString.inc"

// ---------------------------------------------------------------------------

} // end namespace: Adorn

#endif // AD_STRING_H
