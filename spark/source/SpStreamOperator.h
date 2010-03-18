// #############################################################################
//! SpStreamOperator.h : Abstract base class for a stream operator
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

#ifndef SP_STREAM_OPERATOR_H
#define SP_STREAM_OPERATOR_H

#include "SpStreamOutput.h"
#include "SpStreamInput.h"
#include "SpStreamBuffer.h"

//----------------------------------------------------------------------------

namespace Spark
{

//----------------------------------------------------------------------------
//! Abstract base class for a stream operator which modifies an input stream
//----------------------------------------------------------------------------
class SpStreamOperator: public SpStreamOutput, public SpStreamInput
{

//! Construction:
public:

	SpStreamOperator();
	virtual ~SpStreamOperator();

//! Operations:
public:

	//: Sets the current input stream
	virtual void setInputStream(SpStreamInput * pkInputStream);

	//: Returns true if the current state has been modified
	virtual bool hasChanged();

	//: Returns the output buffer
	virtual bool sendOutputToBuffer( SpStreamBuffer* pkBuffer, SpStreamFeedback * pkOutput);

//! Internal Methods:
protected:

	//: Performs the stream computation
	virtual bool compute(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy);

	//: Activates the output stream, if necessary
	virtual bool enableOutputStream(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy);

	//: Sets the necessary state for the stream operation
	virtual bool setupState(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy);

	//: Performs the stream operation
	virtual bool processStream(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy);

	//: Puts the results of the operation into the output stream.
	virtual bool updateOutputStream(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy);

	//: Resets the state
	virtual bool resetState(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy);

	//: Deactivates the output stream, if necessary
	virtual bool disableOutputStream(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy);

};

//----------------------------------------------------------------------------

}	// end namespace: Spark

#endif
