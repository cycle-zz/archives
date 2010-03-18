// #############################################################################
//! SpQuadSg.h : Quad-based stream geometry w/ multi-texturing support
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

#ifndef SP_MULTI_TEXTURED_QUAD_H
#define SP_MULTI_TEXTURED_QUAD_H

#include "SpGlHeaders.h"
#include "SpStreamGeometry.h"


//----------------------------------------------------------------------------

namespace Spark
{

//----------------------------------------------------------------------------
//! Quad-based stream geometry w/ multi-texturing support
//----------------------------------------------------------------------------
class SpMultiTexturedQuadSg : public SpStreamGeometry
{

//! Construction:
public:

	inline SpMultiTexturedQuadSg(
		float fMinX = 0.0f, float fMinY = 0.0f,
		float fMaxX = 1.0f, float fMaxY = 1.0f, float fZ=0.5f,
		float fMinS = 0.0f, float fMinT = 0.0f,
		float fMaxS = 1.0f, float fMaxT = 1.0f)
	:
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

	inline virtual ~SpMultiTexturedQuadSg()
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
		glNormal3f(m_fMinX, m_fMinY, 1.0f);
		glBegin(GL_QUADS);
		{
			int i;

			// Lower Left
			for (i = 0; i < m_iTextureUnitCount; ++i)
				glMultiTexCoord2f(GL_TEXTURE0 + i, m_afMinS[i], m_afMinT[i]);
			glVertex3f(m_fMinX, m_fMinY, m_fZ);

			// Lower Right
			for (i = 0; i < m_iTextureUnitCount; ++i)
				glMultiTexCoord2f(GL_TEXTURE0 + i, m_afMaxS[i], m_afMinT[i]);
			glVertex3f(m_fMaxX, m_fMinY, m_fZ);

			// Upper Right
			for (i = 0; i < m_iTextureUnitCount; ++i)
				glMultiTexCoord2f(GL_TEXTURE0 + i, m_afMaxS[i], m_afMaxT[i]);
			glVertex3f(m_fMaxX,  m_fMaxY, m_fZ);

			// Upper Left
			for (i = 0; i < m_iTextureUnitCount; ++i)
				glMultiTexCoord2f(GL_TEXTURE0 + i, m_afMinS[i], m_afMaxT[i]);
			glVertex3f(m_fMinX,  m_fMaxY, m_fZ);

		}
		glEnd();

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