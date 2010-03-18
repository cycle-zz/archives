#ifndef DG_WINDOW_H
#define DG_WINDOW_H

#include "DataTypes.h"
#include "Timer.h"
#include "Color.h"

namespace dg
{

//******************************************************************************
class Window
{

public:

	#include "KeyBindings.h"

	virtual ~Window();

	// initialize/terminate signal handlers
    virtual Bool onStartup();
    virtual Bool onInitialize();
    virtual void onTerminate();

    // window signal handlers
	virtual void onMove(Int iX, Int iY);
    virtual void onReshape(Int iWidth, Int iHeight);
	virtual void onUpdate( Int iValue );
    virtual void onDisplay();
	
	// special request methods
	virtual void postRedisplay();
	virtual void swapBuffers();
	
	// keyboard signal handlers
    virtual void onKeyDown(UChar ucKey, Int iX, Int iY);
    virtual void onKeyUp(UChar ucKey, Int iX, Int iY);
    virtual void onSpecialKeyDown(Int iKey, Int iX, Int iY);
    virtual void onSpecialKeyUp(Int iKey, Int iX, Int iY);

    // mouse signal handlers
    virtual void onPassiveMotion(Int iX, Int iY);
	virtual void onMouseMotion(Int iX, Int iY, UInt uiModifiers);
	virtual void onMouseClick( Int iButton, Int iState, Int iX, Int iY,UInt uiModifiers);
	
	// idle signal handlers
	virtual void onIdle();
	
	// draw methods (later will be moved to a proper Renderer class)
	void drawImage(
		const UChar* aucBuffer, 
		UInt uiPosX, UInt uiPosY, UInt uiWidth, 
		UInt uiHeight, bool bAlpha);
			
	void drawImage(
		const Real* afBuffer,
		UInt uiPosX, UInt uiPosY, UInt uiWidth, 
		UInt uiHeight, bool bAlpha);
		
	void drawString(const Char* pcString, Int iX, Int iY, const Color& rkColor);
    void drawFrameRate(Int iX, Int iY, const Color& rkColor);
	
	// performance query methods
    void updateClicks();

    // access to the unique Window object
    static Window* current();
	void makeCurrent();

    // access to members set by constructor
    char* title();
    UInt x();
    UInt y();
    UInt width();
    UInt height();
    const Color& bg();
	Timer& timer();

    void setWindowID(Int iWindowID);
    Int id();
	
protected:
	
	// construction and destruction
	Window(char* acWindowTitle, Int iX, Int iY, Int iWidth,
			Int iHeight, const Color& rkBgColor);
	    
	// mouse update data members
    Bool m_bMouseDown;
	Bool m_bLeftMousePressed;
	Bool m_bRightMousePressed;
	Bool m_bMiddleMousePressed;
	Int m_iLastMouseX;
	Int m_iLastMouseY;

	// performance measurements
	Real m_fFrameRate;
    Int m_iClicks;
	Int m_iTimer;
	Int m_iMaxTimer;
	
	// window data members
    static Window* ms_pkWindow;
    char* m_acWindowTitle;
    Int m_iWindowID; 
	Int m_iX, m_iY;
	Int m_iWidth, m_iHeight;
    Color m_kBgColor;
	Timer m_kTimer;
};

//******************************************************************************

#include "Window.inc"

//******************************************************************************

} // end namespace: dg

# endif
