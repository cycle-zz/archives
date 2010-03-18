// #############################################################################
//! SpGlManager.h : Static manager class for interfacing with OpenGL
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

#ifndef SP_GL_MANAGER_H
#define SP_GL_MANAGER_H

// ---------------------------------------------------------------------------

namespace Spark
{

// ---------------------------------------------------------------------------
//! Static manager class for interfacing with OpenGL
// ---------------------------------------------------------------------------
class SpGlManager
{

//! Construction:
public:
	~SpGlManager();

//! Operations:
public:

	static void deleteTexture(unsigned int uiTextureId);

	static unsigned int createTexture(
		int iWidth, int iHeight,
		GLenum eTextureMode = GL_TEXTURE_2D,
		GLenum eImageFormat = GL_RGBA8,
		GLenum ePixelFormat = GL_RGBA,
		GLenum eComponentFormat = GL_FLOAT,
		void* pvData = NULL);

	static unsigned int createFilteredTexture(
		int iWidth, int iHeight,
		GLenum eTextureMode = GL_TEXTURE_2D,
		GLenum eImageFormat = GL_RGBA8,
		GLenum ePixelFormat = GL_RGBA,
		GLenum eComponentFormat = GL_FLOAT,
		GLenum eMinFilterMode = GL_NEAREST,
		GLenum eMagFilterMode = GL_NEAREST,
		GLenum eSWrapMode = GL_CLAMP_TO_EDGE,
		GLenum eTWrapMode = GL_CLAMP_TO_EDGE,
		void* pvData = NULL);

	static void printOnError( char *acMsg );

//! Restricted:
private:

	SpGlManager();
};

// ---------------------------------------------------------------------------

} 	// end namespace: Spark

#endif
