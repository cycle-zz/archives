//----------------------------------------------------------------------------

#include "Window.h"
using namespace dg;

Window* Window::ms_pkWindow = NULL;

//******************************************************************************
Window::Window (
	char* acWindowTitle, Int iX, Int iY,
    Int iWidth, Int iHeight, const Color& rkBgColor)
{
    assert( ms_pkWindow == NULL );
    ms_pkWindow = this;

    m_acWindowTitle = acWindowTitle;
    m_iX = iX;
    m_iY = iY;
	m_iClicks = 0;
    m_iWidth = iWidth;
    m_iHeight = iHeight;
    m_kBgColor = rkBgColor;
	m_iMaxTimer = 30;
	m_iTimer = m_iMaxTimer;
}
//******************************************************************************
Window::~Window ()
{
    assert( ms_pkWindow != NULL );
    ms_pkWindow = NULL;
}
//******************************************************************************
Bool Window::onStartup()
{
    return true;
}
//******************************************************************************
Bool Window::onInitialize()
{
    return true;
}
//******************************************************************************
void Window::onMove(Int iX, Int iY)
{
    m_iX = iX;
    m_iY = iY;
}
//******************************************************************************
void Window::onReshape(Int iWidth, Int iHeight)
{
    m_iWidth = iWidth;
    m_iHeight = iHeight;
}
//******************************************************************************
void Window::onDisplay()
{
    // EMPTY!
}
//******************************************************************************
void Window::onIdle()
{
	onDisplay();
}
//******************************************************************************
void Window::onKeyDown(UChar ucKey, Int, Int)
{
    // quit Window if the ESCAPE key is pressed
    if ( ucKey == KEY_ESCAPE )
        onTerminate();
}
//******************************************************************************
void Window::onKeyUp(UChar, Int, Int)
{
	// EMPTY!
}
//******************************************************************************
void Window::onSpecialKeyDown(Int, Int, Int)
{
	// EMPTY!
}
//******************************************************************************
void Window::onSpecialKeyUp(Int, Int, Int)
{
	// EMPTY!
}
//******************************************************************************
void Window::onMouseClick(
	Int iButton, Int, Int iX, Int iY, UInt)
{
	m_bLeftMousePressed = false;
	m_bRightMousePressed = false;
	m_bMiddleMousePressed = false;

	switch( iButton )
	{
		case(0):
			m_bLeftMousePressed = true;
			break;
		case(1):
			m_bMiddleMousePressed = true;
			break;
		case(2):
			m_bRightMousePressed = true;
			break;
		default:
			m_bLeftMousePressed = true;
			break;
	};
	
	m_bMouseDown = true;
	m_iLastMouseX = iX;
	m_iLastMouseY = iY;
}
//******************************************************************************
void Window::onMouseMotion(Int, Int, UInt)
{
	// EMPTY!
}
//******************************************************************************
void Window::onPassiveMotion(Int, Int)
{
	// EMPTY!
}
//******************************************************************************
void Window::updateClicks()
{
    m_iClicks++;
	if(m_iClicks > 999999)
		m_iClicks = 1;
}
//******************************************************************************
void Window::drawFrameRate(Int iX, Int iY, const Color& rkColor)
{
	Real fElapsed = 0;
    if ( --m_iTimer == 0 )
    {
		fElapsed = m_kTimer.elapsedSeconds();
        if ( fElapsed > 0.0f )
            m_fFrameRate = m_iClicks/fElapsed;
        else
            m_fFrameRate = 0.0f;
		
        m_iTimer = m_iMaxTimer;
		m_iClicks = 0;
    }
	
    char acMessage[1024];
    sprintf(acMessage,"FrameRate: %.1lf fps",	(double)m_fFrameRate);
    drawString(acMessage, iX, iY, rkColor);
}
//******************************************************************************

