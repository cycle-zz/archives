// #############################################################################
//! SpWindow.h : Abstract base class for a graphical display window
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

#ifndef SP_WINDOW_H
#define SP_WINDOW_H

#include "SpTimer.h"
#include "SpTuple.h"

#ifdef WIN32
#include <assert.h>
#endif

//----------------------------------------------------------------------------

namespace Spark
{

//----------------------------------------------------------------------------
//! Abstract base class for a graphical display window
//----------------------------------------------------------------------------
class SpWindow
{

// Typedefs:
public:

	// include the key bindings within the window class definition
	#include "SpKeyBindings.h"

// Construction:
public:

	virtual ~SpWindow();

// Callbacks:
public:

	// initialize/terminate signal handlers
    virtual bool onStartup();
    virtual bool onInitialize();
    virtual void onTerminate();

    // window signal handlers
	virtual void onMove(int iX, int iY);
    virtual void onReshape(int iWidth, int iHeight);
	virtual void onUpdate( int iValue );
    virtual void onDisplay();

	// keyboard signal handlers
    virtual void onKeyDown(unsigned char ucKey, int iX, int iY);
    virtual void onKeyUp(unsigned char ucKey, int iX, int iY);
    virtual void onSpecialKeyDown(int iKey, int iX, int iY);
    virtual void onSpecialKeyUp(int iKey, int iX, int iY);

    // mouse signal handlers
    virtual void onPassiveMotion(int iX, int iY);
	virtual void onMouseMotion(int iX, int iY, unsigned int uiModifiers);
	virtual void onMouseClick( int iButton, int iState, int iX, int iY,unsigned int uiModifiers);

	// idle signal handlers
	virtual void onIdle();

	// draw methods (later will be moved to a proper Renderer class)
	void drawImage(
		const unsigned char* aucBuffer,
		unsigned int uiPosX, unsigned int uiPosY, unsigned int uiWidth,
		unsigned int uiHeight, bool bAlpha);

	void drawImage(
		const float* afBuffer,
		unsigned int uiPosX, unsigned int uiPosY, unsigned int uiWidth,
		unsigned int uiHeight, bool bAlpha);

	void drawString(const char* pcString, int iX, int iY, const SpColor4f& rkColor);
    void drawFrameRate(int iX, int iY, const SpColor4f& rkColor);

// Special Request Methods:
public:

	// special request methods
	virtual void postRedisplay();
	virtual void swapBuffers();

	// performance query methods
    void updateClicks();

// State Methods:
public:

    // access to the unique SpWindow object
    static SpWindow* current();
	void makeCurrent();

    // access to members set by constructor
    char* title();
    unsigned int x();
    unsigned int y();
    unsigned int width();
    unsigned int height();
    const SpColor4f& bg();
	SpTimer& timer();

    void setWindowId(int iSpWindowID);
    int id();

// Internal Methods:
protected:

	// restricted construction (must be derived!)
	SpWindow(char* acWindowTitle, int iX, int iY, int iWidth,
		int iHeight, const SpColor4f& rkBgColor);

// Internal Data:
protected:

	// mouse update data members
    bool m_bMouseDown;
	bool m_bLeftMousePressed;
	bool m_bRightMousePressed;
	bool m_bMiddleMousePressed;
	int m_iLastMouseX;
	int m_iLastMouseY;

	// performance measurements
	float m_fFrameRate;
    int m_iClicks;
	int m_iTimer;
	int m_iMaxTimer;

	// window data members
    static SpWindow* ms_pkWindow;
    char* m_acWindowTitle;
    int m_iSpWindowID;
	int m_iX, m_iY;
	int m_iWidth, m_iHeight;
    SpColor4f m_kBgColor;
	SpTimer m_kTimer;
};

//----------------------------------------------------------------------------

#include "SpWindow.inc"

//----------------------------------------------------------------------------

} // end namespace: Spark

# endif
