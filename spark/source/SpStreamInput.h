// #############################################################################
//! SpStreamInput.h : Abstract base class for an input stream
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

#ifndef SP_STREAM_INPUT_H
#define SP_STREAM_INPUT_H

#include "SpStreamBuffer.h"
#include "SpStreamFeedback.h"

//----------------------------------------------------------------------------

namespace Spark
{

//----------------------------------------------------------------------------
//! Abstract base class for an input stream for loading/generating a data stream
//----------------------------------------------------------------------------
class SpStreamInput
{

//! Construction:
public:

	SpStreamInput()
	{
		// EMPTY!
	}

	virtual~SpStreamInput()
	{
		// EMPTY!
	}

//! Methods:
public:

	virtual bool hasChanged() = 0;

	virtual bool sendOutputToBuffer(
		SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy	) = 0;

};

//----------------------------------------------------------------------------

} // end namespace: Spark

#endif
