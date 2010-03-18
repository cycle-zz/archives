#ifndef SP_STREAMER_H
#define SP_STREAMER_H

#include "SpWindow.h"
#include "SpGridSg.h"
#include "SpGlManager.h"
#include "SpGlslManager.h"
#include "SpStreamBuffer.h"
#include "SpVertexNoiseSb.h"
#include "SpTurbulenceOp.h"
#include "SpMultiTexturedGridSg.h"
#include "SpMultiTexturedQuadSg.h"

namespace Spark
{

//******************************************************************************

class Streamer : public SpWindow
{

public:

	Streamer();
	virtual ~Streamer();

	// initialize/terminate signal handlers
	virtual bool onStartup();
	virtual bool onInitialize();

	// window signal handlers
	virtual void onReshape(int iWidth, int iHeight);
	virtual void onDisplay();
	virtual void onIdle(){ onUpdate(m_kTimer.elapsedCount()); }

	// keyboard signal handlers
	virtual void onKeyDown(unsigned char ucKey, int iX, int iY);
	virtual void onSpecialKeyDown(int iKey, int iX, int iY);

	// mouse signal handlers
	virtual void onMouseMotion(int iX, int iY, unsigned int uiModifiers);
	virtual void onMouseClick( int iButton, int iState, int iX, int iY,unsigned int uiModifiers);

	// update methods
	virtual void onUpdate( int iValue );

	// draw methods (these will later be moved to a Renderer class!)
	void drawText();
	void process();


protected:

	// preparation methods
	void setupFrustum(int iWidth, int iHeight, bool bPerspective );
	SpStreamBuffer* createRenderTexture(const char *acModeString, int iResX, int iResY);
	void destroyRenderTexture(SpTreamBuffer* pkBuffer);
	void updateDisplay(SpTreamBuffer* pkBuffer, int, int);

	// initialization
	void setBackground();
	void setLights();
	void setMaterials();

	// performance measurements
	void startCalcTimer();
	void updateCalcTimer();
	void stopCalcTimer();

	// performance data
	float m_fLastCalcTime;
	unsigned int m_uiHours;
	unsigned int m_uiMinutes;
	unsigned int m_uiSeconds;
	unsigned int m_uiMilliSecs;

	// toggle perspective view for polygon vis
	bool m_bUsePerspective;

	// toggle hud
	bool m_bShowInfo;

	// toggle update
	bool m_bUpdate;

	// toggle rotation
	bool m_bRotate;

	// toggle bounds
	bool m_bShowBounds;

	// toggle spin
	bool m_bSpin;

	// toggle move
	bool m_bMove;

	// toggle lighting or color by normal
	bool m_bLight;

	// current time
	float m_fTime;

	// mouse rotation
	int m_iSpinX;
	int m_iSpinY;
	int m_iOrigX;
	int m_iOrigY;

	float m_fOctaves;
	float m_fLacunarity;
	float m_fSpacing;

	// current scanline for rendering
	unsigned int m_uiScanLine;
	unsigned int m_uiScanIncrement;

	unsigned int m_uiResolution;

	// display options
	float m_fTransparency;

	// offset for camera positions
	float m_fCameraX;
	float m_fCameraY;
	float m_fCameraZ;

	// common frustum for all cameras
	float m_fFrustumLeft;
	float m_fFrustumRight;
	float m_fFrustumBottom;
	float m_fFrustumTop;
	float m_fFrustumNear;
	float m_fFrustumFar;

	float m_fDisplacement;

	int m_ePolygonMode;
	int m_iModelIndex;

	bool m_bAnimate;
	SpVector3f m_kTextureScale;
	SpVector3f m_kTextureOffset;

	SpGridSg m_kGrid;

    	SpMultiTexturedQuadSg m_kTexturedGrid;

	SpVertexNoiseSb* m_pkVertexNoise;
	SpTurbulenceOp* m_pkTurbulence;

	SpCopyToTextureFb* m_pkCopyToTexture;
	SpStreamBuffer* m_pkRenderTexture;
};

//******************************************************************************

} // end namespace: Spark

//******************************************************************************

# endif

