// #############################################################################
//! SpStreamFeedback.h : Abstract Base Class for a Stream Feedback Mechanism
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

#ifndef SP_STREAM_FEEDBACK_H
#define SP_STREAM_FEEDBACK_H

//----------------------------------------------------------------------------

namespace Spark
{

//----------------------------------------------------------------------------

//! Abstract base class for a stream feedback mechanism for returning results
class SpStreamFeedback
{

public:

	virtual void setOutputTexture(
		unsigned int uiTextureId,
		int, int, int ) = 0;

	virtual void updateOutput() = 0;
};

//----------------------------------------------------------------------------

}	// end namespace: Spark

#endif
