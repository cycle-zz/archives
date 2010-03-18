// #############################################################################
//! SpResourcePath.h : Resource utility class for querying a file system and loading data
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

#ifndef SP_RESOURCE_PATH_H
#define SP_RESOURCE_PATH_H

#ifdef _WIN32
#  pragma warning(disable:4786)   // symbol size limitation ... STL
#endif

#include "SpString.h"

#include <stdio.h>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>

// ---------------------------------------------------------------------------

namespace Spark
{

// ---------------------------------------------------------------------------
//! Resource utility class for querying a file system and loading datafiles
// ---------------------------------------------------------------------------
class SpResourcePath
{

//! Type Definitions:
public:

#ifdef WIN32
	typedef struct _stat FileStat;
#else
	typedef struct stat FileStat;
#endif

//! Access Methods:
public:

	inline SpString& filepath()
	{ return m_kFilePath; }

	inline const SpString& filepath() const
	{ return m_kFilePath; }

	inline SpString& pathname()
	{ return m_kPathName; }

	inline const SpString& pathname() const
	{ return m_kPathName; }

	inline SpStringArray& searchpath()
	{ return m_kSearchPath; }

	inline const SpStringArray& searchpath() const
	{ return m_kSearchPath; }

//! Attributes:
public:

	inline void addPath(const SpString& rkPathname)
	{ m_kSearchPath.push_back( rkPathname ); }

    SpString getPath(const SpString& rkFilename);
    SpString getFile(const SpString& rkFilename);

//! File Methods:
public:

	char* loadTextFile(const char* acFilename);
	SpString loadTextFile(const SpString& rkFilename);
    FILE* loadDataFile(const SpString& rkFilename, const char * acMode = "rb");
    int getFileStats(const SpString& rkFilename, FileStat* pkStat);

//! Internal Data:
private:

    SpString m_kFilePath;
    SpString m_kPathName;
    SpStringArray m_kSearchPath;

};

// ---------------------------------------------------------------------------

}	 // end namespace: Spark

#endif
