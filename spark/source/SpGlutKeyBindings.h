// #############################################################################
//! SpGlutKeyBindings.h : Glut Specific key binding definitions
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

#ifndef SP_GLUT_KEY_BINDINGS_H
#define SP_GLUT_KEY_BINDINGS_H

#include "SpGlHeaders.h"
#include "SpGlutHeaders.h"

// ---------------------------------------------------------------------------

using namespace Spark;

// ---------------------------------------------------------------------------

const int SpWindow::KEY_ESCAPE = 0x1B;
const int SpWindow::KEY_LEFT_ARROW = GLUT_KEY_LEFT;
const int SpWindow::KEY_RIGHT_ARROW = GLUT_KEY_RIGHT;
const int SpWindow::KEY_UP_ARROW = GLUT_KEY_UP;
const int SpWindow::KEY_DOWN_ARROW = GLUT_KEY_DOWN;
const int SpWindow::KEY_HOME = GLUT_KEY_HOME;
const int SpWindow::KEY_END = GLUT_KEY_END;
const int SpWindow::KEY_PAGE_UP = GLUT_KEY_PAGE_UP;
const int SpWindow::KEY_PAGE_DOWN = GLUT_KEY_PAGE_DOWN;
const int SpWindow::KEY_INSERT = GLUT_KEY_INSERT;
const int SpWindow::KEY_DELETE = 0x2E;
const int SpWindow::KEY_F1 = GLUT_KEY_F1;
const int SpWindow::KEY_F2 = GLUT_KEY_F2;
const int SpWindow::KEY_F3 = GLUT_KEY_F3;
const int SpWindow::KEY_F4 = GLUT_KEY_F4;
const int SpWindow::KEY_F5 = GLUT_KEY_F5;
const int SpWindow::KEY_F6 = GLUT_KEY_F6;
const int SpWindow::KEY_F7 = GLUT_KEY_F7;
const int SpWindow::KEY_F8 = GLUT_KEY_F8;
const int SpWindow::KEY_F9 = GLUT_KEY_F9;
const int SpWindow::KEY_F10 = GLUT_KEY_F10;
const int SpWindow::KEY_F11 = GLUT_KEY_F11;
const int SpWindow::KEY_F12 = GLUT_KEY_F12;

// ---------------------------------------------------------------------------

const int SpWindow::KEY_SHIFT = GLUT_ACTIVE_SHIFT;
const int SpWindow::KEY_CONTROL = GLUT_ACTIVE_CTRL;
const int SpWindow::KEY_ALT = GLUT_ACTIVE_ALT;
const int SpWindow::KEY_COMMAND = 0;

// ---------------------------------------------------------------------------

const int SpWindow::MOUSE_LEFT_BUTTON = GLUT_LEFT_BUTTON;
const int SpWindow::MOUSE_MIDDLE_BUTTON = GLUT_MIDDLE_BUTTON;
const int SpWindow::MOUSE_RIGHT_BUTTON = GLUT_RIGHT_BUTTON;
const int SpWindow::MOUSE_UP = GLUT_UP;
const int SpWindow::MOUSE_DOWN = GLUT_DOWN;

// ---------------------------------------------------------------------------

#endif
