// #############################################################################
//! SpStreamOutput.h : Abstract base class for an output stream
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

#ifndef SP_STREAM_OUTPUT_H
#define SP_STREAM_OUTPUT_H

namespace Spark
{

//----------------------------------------------------------------------------

class SpStreamInput;

//----------------------------------------------------------------------------
//! Abstract base class for an output stream used fo saving/viewing stream data
//----------------------------------------------------------------------------
class SpStreamOutput
{

//! Construction:
public:

	SpStreamOutput()
	: 	m_bHasChanged(true),
		m_pkInputStream(0)
	{
		// EMPTY!
	}

	virtual ~SpStreamOutput()
	{
		// EMPTY!
	}

//! Operations:
public:

	//! Sets the current source operator
	virtual void setInputStream(SpStreamInput * pkInputStream)
	{
		m_pkInputStream = pkInputStream;
		m_bHasChanged = true;
	}

//! Internal Data:
protected:

	bool m_bHasChanged;

	SpStreamInput * m_pkInputStream;
};

//----------------------------------------------------------------------------

} // end namespace: Spark

#endif
