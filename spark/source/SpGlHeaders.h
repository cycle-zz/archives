// #############################################################################
//! SpGlHeaders.h : Header file for including system dependent OpenGL headers
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

#ifndef SP_OPENGL_HEADERS_H
#define SP_OPENGL_HEADERS_H

#if !defined(__GNUC__)
#  pragma once
#endif

// -----------------------------------------------------------------------------

#include <GL/glew.h>
#ifdef _WIN32
#include <GL/wglew.h>
#include <windows.h>
#else
#include <GL/glxew.h>
#endif

#if defined(WIN32)
#include <GL/wglew.h>
#include <windows.h>
#pragma comment(lib, "gdi32.lib") // required for GetPixelFormat()
#endif

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <AGL/agl.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

// -----------------------------------------------------------------------------

#endif // endif: OPENGL_H
