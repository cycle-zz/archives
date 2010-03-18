// #############################################################################
//! SpGridSg.h : Multi resolution grid based stream geometry
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

#ifndef SP_GRID_SG_H
#define SP_GRID_SG_H

#include "SpGlHeaders.h"
#include "SpStreamGeometry.h"

// ---------------------------------------------------------------------------

namespace Spark
{

// ---------------------------------------------------------------------------
//! Multi-resolution grid-based stream geometry
// ---------------------------------------------------------------------------
class SpGridSg : public SpStreamGeometry
{

//! Construction:
public:

	SpGridSg(
		int iRows=10, int iCols=10,
		float fMinX = -1.0f, float fMinY = -1.0f,
		float fMaxX = 1.0f, float fMaxY = 1.0f, float fZ=0.5f)
	:
		m_iRows(iRows), m_iCols(iCols),
		m_fMinX(fMinX), m_fMinY(fMinY),
		m_fMaxX(fMaxX), m_fMaxY(fMaxY), m_fZ(fZ)
	{
		// EMPTY!
	}

	virtual ~SpGridSg()
	{
		// EMPTY!
	}

//! Operations:
public:

	virtual void render()
	{
		float fWidth = m_fMaxX - m_fMinX;
		float fHeight = m_fMaxY - m_fMinY;

		float fCenterX = (fWidth / 2.0f) + m_fMinX;
		float fCenterY = (fHeight / 2.0f) + m_fMinX;

		float fDW = fWidth / m_iCols;
		float fDH = fHeight / m_iRows;

		// just use a single normal direction
		// for the entire grid
		glNormal3f(fCenterX, fCenterY, 1.0);
		for (float fY = m_fMinY; fY < m_fMaxY; fY += fDH)
		{
			glBegin(GL_QUAD_STRIP);
			for (float fX = m_fMinX; fX < m_fMaxX; fX += fDW)
			{
				glVertex3f(fX, fY, m_fZ);
				glVertex3f(fX, fY + fDH, m_fZ);
			}
			glEnd();
		}
	}

	inline void setResolution(
		int iRows, int iCols)
	{
		m_iRows = iRows;
		m_iCols = iCols;
	}


	inline void setVertexCoordRect(
		float fMinX, float fMinY,
		float fMaxX, float fMaxY, float fZ = 0.5f)
	{
		m_fMinX = fMinX; m_fMaxX = fMaxX;
		m_fMinY = fMinY; m_fMaxY = fMaxY;
		m_fZ = fZ;
	}


//! Internal Methods:
protected:

	int m_iRows;
	int m_iCols;

	float m_fMinX;
	float m_fMinY;
	float m_fMaxX;
	float m_fMaxY;

	float m_fZ;

};

// ---------------------------------------------------------------------------

}	// end namespace: Spark

#endif

