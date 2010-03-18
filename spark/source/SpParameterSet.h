// #############################################################################
//! SpParameterSet.h : Container class for parameters used with GPU programs
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

#ifndef SP_PARAMETER_SET_H
#define SP_PARAMETER_SET_H

#include "SpParameter.h"

#include <vector>

// ---------------------------------------------------------------------------

namespace Spark
{

// ---------------------------------------------------------------------------
//! Container class for parameters used with GPU programs
// ---------------------------------------------------------------------------
class SpParameterSet
{

//! Construction:
public:

    SpParameterSet ();
    SpParameterSet (const SpParameterSet& rkConstants);
    virtual ~SpParameterSet ();

//! Insertion:
public:

	void insert(const SpParameter& rkParam);
	void insert(const SpParameter* pkParam);

//! Retrieval:
public:

    //: Returns null if parameter does not exist
    SpParameterPtr retrieve (const char* acName) const;

    //: Returns null if parameter does not exist
    SpParameterPtr retrieve (int iIndex) const;

//! Attributes:
public:

    int size () const;

//! Internal Data:
protected:

    std::vector<SpParameterPtr> m_kSpParameters;

};

// ---------------------------------------------------------------------------

#include "SpParameterSet.inc"

// ---------------------------------------------------------------------------

}	// end namespace: Spark

#endif
