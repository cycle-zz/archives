// #############################################################################
//! SpStreamGeometry.h : Abstract base class for generating a data stream by rendering geometry
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

#ifndef SP_STREAM_GEOMETRY_H
#define SP_STREAM_GEOMETRY_H

//----------------------------------------------------------------------------

namespace Spark
{

//----------------------------------------------------------------------------
//! Abstract base class for generating a data stream by rendering geometry
//----------------------------------------------------------------------------
class SpStreamGeometry
{

//! Abstract interfaces:
public:

	//! Renders geometry to generate a data stream
	virtual void render() = 0;

};

//----------------------------------------------------------------------------

}	// end namespace: Spark

#endif
