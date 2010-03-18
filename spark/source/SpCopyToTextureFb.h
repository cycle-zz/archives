// #############################################################################
//! SpCopyToTextureFb.h : Copy To Texture (CTT) Feedback Mechanism via OpenGL
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

#ifndef SP_COPY_TO_TEXTURE_H
#define SP_COPY_TO_TEXTURE_H

#include "SpStreamFeedback.h"
#include "SpGlHeaders.h"

//----------------------------------------------------------------------------

namespace Spark
{

//----------------------------------------------------------------------------
//! Copy To Texture (CTT) feedback mechanism via OpenGL
// ---------------------------------------------------------------------------
class SpCopyToTextureFb : public SpStreamFeedback
{

//! Construction:
public:

	inline SpCopyToTextureFb(
		GLuint uiTextureId=0,
		GLenum eTextureMode=0,
		int iX=0, int iY=0,
		int iOffsetX=0, int iOffsetY=0,
		int iWidth=0, int iHeight=0,
		bool bEnableCopy = true)
	:
		m_uiOutputTextureId(uiTextureId),
		m_eOutputTextureMode(eTextureMode),
		m_iX(iX), m_iY(iY),
		m_iWidth(iWidth), m_iHeight(iHeight),
		m_iOffsetX(iOffsetX), m_iOffsetY(iOffsetY),
		m_bEnableCopy(bEnableCopy)
	{
		// EMPTY!
	}

	virtual ~SpCopyToTextureFb()
	{
		// EMPTY!
	}

//! Inherited Methods:
public:

	virtual void setOutputTexture(
		unsigned int uiTextureId,
		int eTextureMode,
		int iWidth, int iHeight)
	{
		m_uiOutputTextureId = uiTextureId;
		m_eOutputTextureMode = eTextureMode;
		m_iWidth = iWidth;
		m_iHeight = iHeight;
	}

	virtual void updateOutput()
	{
		glBindTexture(m_eOutputTextureMode, m_uiOutputTextureId);

		if (m_bEnableCopy)
		{
			glCopyTexSubImage2D(
				m_eOutputTextureMode, 0,
				m_iOffsetX, m_iOffsetY,
				m_iX, m_iY,
				m_iWidth, m_iHeight
			);
		}
	}

//! Operations:
public:

	inline void setOutputRectangle(
		int iX, int iY,
		int iWidth, int iHeight,
		int iOffsetX, int iOffsetY)
	{
		m_iX = iX;
		m_iY = iY;
		m_iWidth = iWidth;
		m_iHeight = iHeight;
		m_iOffsetX = iOffsetX;
		m_iOffsetY = iOffsetY;
	}

	inline void setupViewport()
	{
		glGetIntegerv(GL_VIEWPORT, m_iOldViewport);
		glViewport(m_iX, m_iY, m_iWidth, m_iHeight);
	}

	inline void bindOutputTexture() const
	{
		glBindTexture(m_eOutputTextureMode, m_uiOutputTextureId);
	}

	inline void restoreViewport() const
	{
		glViewport(
			m_iOldViewport[0], m_iOldViewport[1],
			m_iOldViewport[2], m_iOldViewport[3]
		);
	}

//! Access Methods:
public:

	inline void setEnableCopy(bool bEnable)
	{ m_bEnableCopy = bEnable; }

	inline bool getEnableCopy() const
	{ return m_bEnableCopy;    }


//! Internal Data:
protected:

	GLuint m_uiOutputTextureId;
	GLenum m_eOutputTextureMode;

	int m_iX;
	int m_iY;
	int m_iWidth;
	int m_iHeight;
	int m_iOffsetX;
	int m_iOffsetY;

	int m_iOldViewport[4];

	bool m_bEnableCopy;
};

//----------------------------------------------------------------------------

}	// end namespace: Spark

#endif
