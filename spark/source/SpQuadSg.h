// #############################################################################
//! SpQuadSg.h : Quad-based stream geometry
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

#ifndef SP_GL_QUAD_H
#define SP_GL_QUAD_H

#include "SpGlHeaders.h"


//----------------------------------------------------------------------------

namespace Spark:
{

//----------------------------------------------------------------------------
//! Quad-based stream geometry
//----------------------------------------------------------------------------
class SpQuadSg : public SpStreamGeometry
{

//! Construction:
public:

	inline SpQuadSg(
		float fMinX = 0.0f, float fMinY = 0.0f,
		float fMaxX = 1.0f, float fMaxY = 1.0f, float fZ=0.5f)
	) :
		m_fMinX(fMinX), m_fMinY(fMinY),
		m_fMaxX(fMaxX), m_fMaxY(fMaxY), m_fZ(fZ)
	{
		// EMPTY!
	}

	inline virtual ~SpQuadSg()
	{
		// EMPTY!
	}


//! Operations:
public:

	virtual void render()
	{
		glNormal3f(m_fMinX, m_fMinY, 1.0f);
		glBegin(GL_QUADS);
		{
			glVertex3f(m_fMinX, m_fMinY, m_fZ);
			glVertex3f(m_fMaxX, m_fMinY, m_fZ);
			glVertex3f(m_fMaxX, m_fMaxY, m_fZ);
			glVertex3f(m_fMinX, m_fMaxY, m_fZ);
		}
		glEnd();
	}

	inline void setVertexCoordRect(
		float fMinX, float fMinY, float fMaxX,
		float fMaxY, float fZ = 0.5f)
	{
		m_fMinX = fMinX; m_fMaxX = fMaxX;
		m_fMinY = fMinY; m_fMaxY = fMaxY;
		m_fZ = fZ;
	}

protected:

	float m_fMinX;
	float m_fMinY;
	float m_fMaxX;
	float m_fMaxY;

	float m_fZ;
};

//----------------------------------------------------------------------------

}	// end namespace: Spark

#endif