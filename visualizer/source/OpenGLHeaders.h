// start file: OpenGL.h

// #############################################################################
// # OpenGL.h  -  Header file for including system dependent OpenGL headers
// #
// # Created 	: Sat Jan 10 2004
// # Copyright	: (C) 2004 by Derek Gerstmann
// # Email	: dgerstma@acm.org
// #
// #############################################################################

// =============================================================================
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
// =============================================================================

#ifndef OPENGLHEADERS_H
#define OPENGLHEADERS_H
#if !defined(__GNUC__)
#  pragma once
#endif

// -----------------------------------------------------------------------------

#if defined(WIN32)
#include <windows.h>
#endif

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

// -----------------------------------------------------------------------------

#endif // endif: OPENGL_H
