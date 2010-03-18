// #############################################################################
//! SpGridSg.h : Multi-resolution grid-based stream geometry w/ multi-texturing support
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

#ifndef SP_MULTI_TEXTURED_GRID_H
#define SP_MULTI_TEXTURED_GRID_H

#include "SpGlHeaders.h"
#include "SpStreamGeometry.h"

//----------------------------------------------------------------------------

namespace Spark
{

//----------------------------------------------------------------------------
//! Multi-resolution grid-based stream geometry w/ multi-texturing support
//----------------------------------------------------------------------------
class SpMultiTexturedGridSg : public SpStreamGeometry
{

//! Construction:
public:

	inline SpMultiTexturedGridSg(
		int iRows = 1, int iCols = 1,
		float fMinX = 0.0f, float fMinY = 0.0f,
		float fMaxX = 1.0f, float fMaxY = 1.0f, float fZ=0.0f,
		float fMinS = 0.0f, float fMinT = 0.0f,
		float fMaxS = 1.0f, float fMaxT = 1.0f)
	:
		m_iRows(iRows), m_iCols(iCols),
		m_fMinX(fMinX), m_fMinY(fMinY),
		m_fMaxX(fMaxX), m_fMaxY(fMaxY), m_fZ(fZ)
	{
		glGetIntegerv(GL_MAX_TEXTURE_UNITS, &m_iTextureUnitCount);

		m_afMinS = new float[m_iTextureUnitCount];
		m_afMaxS = new float[m_iTextureUnitCount];
		m_afMinT = new float[m_iTextureUnitCount];
		m_afMaxT = new float[m_iTextureUnitCount];

		setTexCoordRect(fMinS, fMinT, fMaxS, fMaxT);
	}

	inline virtual ~SpMultiTexturedGridSg()
	{
		delete [] m_afMinS;
		delete [] m_afMaxS;
		delete [] m_afMinT;
		delete [] m_afMaxT;
	}

//! Operations:
public:

	virtual void render()
	{

		float fWidth = m_fMaxX - m_fMinX;
		float fHeight = m_fMaxY - m_fMinY;

		float fCenterX = (fWidth / 2.0f) + m_fMinX;
		float fCenterY = (fHeight / 2.0f) + m_fMinX;

		float fDeltaS = m_afMaxS[0] - m_afMinS[0];
		float fDeltaT = m_afMaxT[0] - m_afMinT[0];

		float fCenterS = (fDeltaS / 2.0f) + m_afMinS[0];
		float fCenterT = (fDeltaT / 2.0f) + m_afMinT[0];

		float fDS = fDeltaS / m_iCols;
		float fDT = fDeltaT / m_iRows;

		float fDW = fWidth / m_iCols;
		float fDH = fHeight / m_iRows;

		// just use a single normal direction
		// for the entire grid
		glNormal3f(fCenterX, fCenterY, 1.0);

		float fS = m_afMinS[0];
		float fT = m_afMinT[0];
		int i = 0;

		for (float fY = m_fMinY; fY < m_fMaxY; fY += fDH)
		{
			glBegin(GL_QUAD_STRIP);
			fS = m_afMinS[0];
			for (float fX = m_fMinX; fX < m_fMaxX; fX += fDW)
			{
				for (i = 0; i < m_iTextureUnitCount; ++i)
					glMultiTexCoord2f(GL_TEXTURE0 + i, fS, fT);
				glVertex3f(fX, fY, m_fZ);

				for (i = 0; i < m_iTextureUnitCount; ++i)
					glMultiTexCoord2f(GL_TEXTURE0 + i, fS, fT + fDT);
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

	inline void setTexCoordRect(
		float fMinS, float fMinT, float fMaxS, float fMaxT)
	{
		for (int i = 0; i < m_iTextureUnitCount; ++i)
		{
			setSingleTexCoordRect(i, fMinS, fMinT, fMaxS, fMaxT);
		}
	}

	inline void setVertexCoordRect(
		float fMinX, float fMinY, float fMaxX, float fMaxY, float fZ=0.5f)
	{
		m_fMinX = fMinX; m_fMaxX = fMaxX;
		m_fMinY = fMinY; m_fMaxY = fMaxY;
		m_fZ = fZ;
	}


//! Internal Methods:
protected:

	inline void setSingleTexCoordRect(
		int iTexUnit, float fMinS, float fMinT, float fMaxS, float fMaxT)
	{
		m_afMinS[iTexUnit] = fMinS; m_afMaxS[iTexUnit] = fMaxS;
		m_afMinT[iTexUnit] = fMinT; m_afMaxT[iTexUnit] = fMaxT;
	}


//! Internal Data:
protected:

	int m_iTextureUnitCount;

	int m_iRows;
	int m_iCols;

	float m_fMinX;
	float m_fMinY;
	float m_fMaxX;
	float m_fMaxY;

	float m_fZ;

	float *m_afMinS;
	float *m_afMaxS;
	float *m_afMinT;
	float *m_afMaxT;
};

//----------------------------------------------------------------------------

} // end namespace: Spark

#endif