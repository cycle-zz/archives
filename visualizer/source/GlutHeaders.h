// start file: GlutHeaders.h

// #############################################################################
// # GlutHeaders.h  -  Header file for including system dependent GLUT headers
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

#ifndef GLUTHEADERS_H
#define GLUTHEADERS_H
#if !defined(__GNUC__)
#  pragma once
#endif

// -----------------------------------------------------------------------------

#include "OpenGLHeaders.h"

// -----------------------------------------------------------------------------

#if defined(WIN32)
#include <windows.h>
#endif

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// -----------------------------------------------------------------------------

#endif // endif: GLUT_HEADERS_H
