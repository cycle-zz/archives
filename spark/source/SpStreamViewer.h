// #############################################################################
//! SpStreamViewer.h : Stream viewer output class for visualizing a data stream
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

#ifndef SP_STREAM_VIEWER_H
#define SP_STREAM_VIEWER_H

#include "SpTexturedQuadSg.h"

namespace Spark
{

//----------------------------------------------------------------------------

class SpStreamOutput;

//----------------------------------------------------------------------------
//! Stream viewer output class for visualizing a data stream
//----------------------------------------------------------------------------
class SpStreamViewer : public SpStreamOutput
{

//! Construction:
public:

	SpStreamViewer() : SpStreamOutput, m_pkQuad(0)
	{
		m_pkQuad = new SpTexturedQuadSg;
	}

	virtual ~GpuStreamViewer()
	{
		// EMPTY!
	}

//! Operations:
public:

	virtual void setViewport(int iX, int iY, int iWidth, int iHeight) = 0;
	virtual void onResize(int iWidth, int iHeight) = 0;
	virtual void onDisplay() = 0;

//! Internal Data:
protected:

	SpTexturedQuadSg * m_pkQuad;
};

//----------------------------------------------------------------------------

} // end namespace: Spark

#endif