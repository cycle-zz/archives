//----------------------------------------------------------------------------

#include "SpWindow.h"
using namespace Spark;

SpWindow* SpWindow::ms_pkWindow = NULL;

//******************************************************************************
SpWindow::SpWindow (
	char* acWindowTitle, int iX, int iY,
    int iWidth, int iHeight, const SpColor4f& rkBgColor)
{
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
SpWindow::~SpWindow ()
{
    assert( ms_pkWindow != NULL );
	onTerminate();
    ms_pkWindow = NULL;
}
//******************************************************************************
bool SpWindow::onStartup()
{
    return true;
}
//******************************************************************************
bool SpWindow::onInitialize()
{
    return true;
}
//******************************************************************************
void SpWindow::onMove(int iX, int iY)
{
    m_iX = iX;
    m_iY = iY;
}
//******************************************************************************
void SpWindow::onReshape(int iWidth, int iHeight)
{
    m_iWidth = iWidth;
    m_iHeight = iHeight;
}
//******************************************************************************
void SpWindow::onDisplay()
{
    // EMPTY!
}
//******************************************************************************
void SpWindow::onIdle()
{
	onUpdate( m_kTimer.elapsedCount() );
	postRedisplay();
}
//******************************************************************************
void SpWindow::onKeyDown(unsigned char ucKey, int, int)
{
    // quit SpWindow if the ESCAPE key is pressed
    if ( ucKey == KEY_ESCAPE )
        onTerminate();
}
//******************************************************************************
void SpWindow::onKeyUp(unsigned char, int, int)
{
	// EMPTY!
}
//******************************************************************************
void SpWindow::onSpecialKeyDown(int, int, int)
{
	// EMPTY!
}
//******************************************************************************
void SpWindow::onSpecialKeyUp(int, int, int)
{
	// EMPTY!
}
//******************************************************************************
void SpWindow::onMouseClick(
	int iButton, int, int iX, int iY, unsigned int)
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
void SpWindow::onMouseMotion(int, int, unsigned int)
{
	// EMPTY!
}
//******************************************************************************
void SpWindow::onPassiveMotion(int, int)
{
	// EMPTY!
}
//******************************************************************************
void SpWindow::updateClicks()
{
    m_iClicks++;
	if(m_iClicks > 999999)
		m_iClicks = 1;
}
//******************************************************************************
void SpWindow::drawFrameRate(int iX, int iY, const SpColor4f& rkColor)
{
	float fElapsed = 0;
    if ( --m_iTimer == 0 )
    {
		fElapsed = (float)m_kTimer.elapsedSeconds();
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

