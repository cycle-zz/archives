// #############################################################################
//! SpTexturedGridSg.h : Multi-resolution grid-based stream geometry w/ texturing support
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

#ifndef SP_TEXTURED_GRID_H
#define SP_TEXTURED_GRID_H

#include "SpGlHeaders.h"
#include "SpStreamGeometry.h"

// ---------------------------------------------------------------------------

namespace Spark
{

// ---------------------------------------------------------------------------
//! Multi-resolution grid-based stream geometry w/ texturing support
// ---------------------------------------------------------------------------
class SpTexturedGridSg : public SpStreamGeometry
{

//! Construction:
public:

	SpTexturedGridSg(
		int iRows = 10, int iCols = 10,
		float fMinX = -1.0f, float fMinY = -1.0f,
		float fMaxX = 1.0f, float fMaxY = 1.0f, float fZ=0.0f,
		float fMinS = 0.0f, float fMinT = 0.0f,
		float fMaxS = 1.0f, float fMaxT = 1.0f)
	:
		m_iRows(iRows), m_iCols(iCols),
		m_fMinX(fMinX), m_fMinY(fMinY),
		m_fMaxX(fMaxX), m_fMaxY(fMaxY), m_fZ(fZ),
		m_fMinS(fMinS), m_fMinT(fMinT),
		m_fMaxS(fMaxS), m_fMaxT(fMaxT)
	{
		// EMPTY!
	}

	virtual ~SpTexturedGridSg()
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

		float fDeltaS = m_fMaxS - m_fMinS;
		float fDeltaT = m_fMaxT - m_fMinT;

		//float fCenterS = (fDeltaS / 2.0f) + m_fMinS;
		//float fCenterT = (fDeltaT / 2.0f) + m_fMinT;

		float fDS = fDeltaS / m_iCols;
		float fDT = fDeltaT / m_iRows;

		float fDW = fWidth / m_iCols;
		float fDH = fHeight / m_iRows;

		// just use a single normal direction
		// for the entire grid
		glNormal3f(fCenterX, fCenterY, 1.0);

		float fS = m_fMinS;
		float fT = m_fMinT;

		//glBegin(GL_TRIANGLE_STRIP);
		for (float fY = m_fMinY; fY < m_fMaxY; fY += fDH)
		{
			glBegin(GL_QUAD_STRIP);
			fS = m_fMinS;
			for (float fX = m_fMinX; fX < m_fMaxX; fX += fDW)
			{
				glTexCoord2f(fS, fT);
				glVertex3f(fX, fY, m_fZ);

				glTexCoord2f(fS, fT + fDT);
				glVertex3f(fX, fY + fDH, m_fZ);

				fS += fDS;
			}
			fT += fDT;
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


//! Internal Data:
protected:

	int m_iRows;
	int m_iCols;

	float m_fMinX;
	float m_fMinY;
	float m_fMaxX;
	float m_fMaxY;

	float m_fZ;

	float m_fMinS;
	float m_fMinT;
	float m_fMaxS;
	float m_fMaxT;

};

// ---------------------------------------------------------------------------

}	// end namespace: Spark

#endif

