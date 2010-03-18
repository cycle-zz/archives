// #############################################################################
//! SpCopyToTexture3dFb.h : Sliced 3d Copy To Texture (CTT) Feedback via OpenGL
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

#ifndef SP_COPY_TO_TEXTURE_3D_H
#define SP_COPY_TO_TEXTURE_3D_H

#include "SpStreamFeedback.h"
#include "SpGlHeaders.h"

//----------------------------------------------------------------------------

namespace Spark:
{

//----------------------------------------------------------------------------
//! Sliced 3D Copy To Texture (CTT) feedback mechanism via OpenGL
// ---------------------------------------------------------------------------
class SpCopyToTexture3dFb : public SpStreamFeedback
{

//! Construction:
public:

	SpCopyToTexture3dFb(
		GLuint uiTextureId=0,
		int iX=0, int iY=0,
		int iWidth=0, int iHeight=0, int iDepth=0,
		int iOffsetX=0, int iOffsetY=0, int iOffsetZ=0,
		bool bEnableCopy=true)
	:
		m_uiOutputTextureId(uiTextureId),
		m_iX(iX), m_iY(iY),
		m_iWidth(iWidth),
		m_iHeight(iHeight),
		m_iDepth(iDepth),
		m_iOffsetX(iOffsetX),
		m_iOffsetY(iOffsetY),
		m_iOffsetZ(iOffsetZ),
		m_bEnableCopy(bEnableCopy)
	{
		// EMPTY!
	}

	~SpCopyToTexture3dFb()
	{
		// EMPTY!
	}

//! Inherited Methods:
public:

	virtual void setOutputTexture(
		unsigned int uiTextureId,
		int iWidth, int iHeight, int iDepth)
	{
		m_uiOutputTextureId = uiTextureId;
		m_iWidth = iWidth;
		m_iHeight = iHeight;
		m_iDepth = iDepth;
	}


	virtual void updateOutput()
	{
		glBindTexture(GL_TEXTURE_3D, m_uiOutputTextureId);

		if (m_bEnableCopy)
		{
			glCopyTexSubImage3D(
				GL_TEXTURE_3D, 0,
				m_iOffsetX, m_iOffsetY, m_iOffsetZ,
				m_iX, m_iY, m_iWidth, m_iHeight
			);
		}

		glViewport(
			m_iOldViewport[0], m_iOldViewport[1],
			m_iOldViewport[2], m_iOldViewport[3]
		);
	}

//! Operations:
public:

	inline void setOutputRectangle(
		int iX, int iY,
		int iWidth, int iHeight,
		int iOffsetX, int iOffsetY, int iOffsetZ)
	{
		m_iOffsetX = iOffsetX;
		m_iOffsetY = iOffsetY;
		m_iOffsetZ = iOffsetZ;
		m_iX = iX; m_iY = iY;
		m_iWidth = iWidth;
		m_iHeight = iHeight;
	}

	inline void setOutputSlice(int iOffsetZ)
	{
		m_iOffsetX = iOffsetZ;
	}

	inline void setViewport()
	{
		glGetIntegerv(GL_VIEWPORT, m_iOldViewport);
		glViewport(m_iX, m_iY, m_iWidth, m_iHeight);
	}

	inline void bindOutputTexture() const
	{
		glBindTexture(m_eOutputTextureMode, m_uiOutputTextureId);
	}


//! Access Methods:
public:

	void setEnableCopy(bool bEnable)
	{ m_bEnableCopy = bEnable; }

	bool getEnableCopy() const
	{ return m_bEnableCopy;    }

//! Internal Data:
protected:

	GLuint m_uiOutputTextureId;

	int m_iOffsetX;
	int m_iOffsetY;
	int m_iOffsetZ;

	int m_iX;
	int m_iY;

	int m_iWidth;
	int m_iHeight;
	int m_iDepth;

	int m_iOldViewport[4];

	bool m_bEnableCopy;
};

//----------------------------------------------------------------------------

}	// end namespace: Spark

#endif