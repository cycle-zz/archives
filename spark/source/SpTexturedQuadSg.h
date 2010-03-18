// #############################################################################
//! SpTexturedQuadSg.h : Quad-based stream geometry w/ texturing support
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

#ifndef SP_TEXTURED_QUAD_SG_H
#define SP_TEXTURED_QUAD_SG_H

#include "SpGlHeaders.h"
#include "SpStreamGeometry.h"


//----------------------------------------------------------------------------

namespace Spark:
{

//----------------------------------------------------------------------------
//! Quad-based stream geometry w/ texturing support
//----------------------------------------------------------------------------
class SpTexturedQuadSg : public SpStreamGeometry
{

//! Construction:
public:

	SpTexturedQuadSg(
		float fMinX = 0.0f, float fMinY = 0.0f,
		float fMaxX = 1.0f, float fMaxY = 1.0f, float fZ=0.5f
		float fMinS = 0.0f, float fMinT = 0.0f,
		float fMaxS = 1.0f, float fMaxT = 1.0f)
	) :
		m_fMinX(fMinX), m_fMinY(fMinY),
		m_fMaxX(fMaxX), m_fMaxY(fMaxY), m_fZ(fZ),
		m_fMinS(fMinS), m_fMinT(fMinT),
		m_fMaxS(fMaxS), m_fMaxT(fMaxT)
	{
		// EMPTY!
	}

	virtual ~SpTexturedQuadSg()
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
			glTexCoord2f(m_fMinS, m_fMinT); glVertex3f(m_fMinX, m_fMinY, m_fZ);
			glTexCoord2f(m_fMaxS, m_fMinT); glVertex3f(m_fMaxX, m_fMinY, m_fZ);
			glTexCoord2f(m_fMaxS, m_fMaxT); glVertex3f(m_fMaxX, m_fMaxY, m_fZ);
			glTexCoord2f(m_fMinS, m_fMaxT); glVertex3f(m_fMinX, m_fMaxY, m_fZ);
		}
		glEnd();
	}

	inline void setVertexCoordRect(
		float fMinX, float fMinY, float fMaxX, float fMaxY, float fZ = 0.5f)
	{
		m_fMinX = fMinX; m_fMaxX = fMaxX;
		m_fMinY = fMinY; m_fMaxY = fMaxY;
		m_fZ = fZ;
	}

	inline void setTexCoordRect(
		float fMinS, float fMinT, float fMaxS, float fMaxT)
	{
		m_fMinS = fMinS; m_fMaxS = fMaxS;
		m_fMinT = fMinT; m_fMaxT = fMaxT;
	}

protected:

	float m_fMinX;
	float m_fMinY;
	float m_fMaxX;
	float m_fMaxY;

	float m_fZ;

	float m_fMinS;
	float m_fMaxS;
	float m_fMinT;
	float m_fMaxT;

};

//----------------------------------------------------------------------------

}	// end namespace: Spark

#endif