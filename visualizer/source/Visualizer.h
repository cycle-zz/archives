#ifndef DG_VISUALIZER_H
#define DG_VISUALIZER_H

#include "DataTypes.h"
#include "Polygonizer.h"
#include "Hypertexture.h"
#include "RayTracer.h"
#include "Window.h"
#include "Camera.h"
#include "Image.h"

namespace dg
{

//******************************************************************************

class Visualizer : public Window
{

public:

	enum VisualizerMode
	{
		VM_MARCHING_CUBES,
		VM_MARCHING_TETRA,
		VM_RAYTRACE,
		VM_HYPERTEXTURE,
		VM_COUNT
	};

	Visualizer();
	virtual ~Visualizer();

	// initialize/terminate signal handlers
	virtual Bool onStartup();
	virtual Bool onInitialize();

	// window signal handlers
	virtual void onReshape(Int iWidth, Int iHeight);
	virtual void onDisplay();
	virtual void onIdle(){ onDisplay(); }

	// keyboard signal handlers
	virtual void onKeyDown(UChar ucKey, Int iX, Int iY);
	virtual void onSpecialKeyDown(Int iKey, Int iX, Int iY);

	// mouse signal handlers
	virtual void onMouseMotion(Int iX, Int iY, UInt uiModifiers);
	virtual void onMouseClick( Int iButton, Int iState, Int iX, Int iY,UInt uiModifiers);

	// draw methods (these will later be moved to a Renderer class!)
	void drawText();
	void drawPolygons();
	void drawRaytraced();
	void drawHypertexture();

protected:

	// preparation methods
	void setupPolygonizer();
	void setupRayTracer();
	void setupHypertexture();
	void setupCamera(Camera& rkCamera);
	void setupFrustum(Int iWidth, Int iHeight, bool bPerspective );

	// initialization
	void setBackground();
	void setLights();
	void setMaterials();

	// performance measurements
	void startCalcTimer();
	void updateCalcTimer();
	void stopCalcTimer();

	// update methods
	void update(Real fTime);

	// performance data
	Real m_fLastCalcTime;
	UInt m_uiHours;
	UInt m_uiMinutes;
	UInt m_uiSeconds;
	UInt m_uiMilliSecs;

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

	// update flags
	bool m_bRendering;
	bool m_bRayTraced;
	bool m_bHyperTraced;
	bool m_bPolygonized;
	bool m_bKeepInView;
	bool m_bFadeOut;

	// mouse rotation
	Int m_iSpinX;
	Int m_iSpinY;
	Int m_iOrigX;
	Int m_iOrigY;
	
	// current scanline for rendering
	UInt m_uiScanLine;
	UInt m_uiScanIncrement;

	// polygonizer options
	Int m_iCellCount;
	Real m_fScale;
	Real m_fIsoLevel;
	Real m_fUpdateOffset;
	Real m_fTime;
	Polygonizer::MarchMethod m_eMarchMode;

	// display options
	Real m_fTransparency;

	// offset for function evaluation
	Real m_fOffsetX;
	Real m_fOffsetY;
	Real m_fOffsetZ;

	// offset for camera positions
	Real m_fCameraX;
	Real m_fCameraY;
	Real m_fCameraZ;

	// common frustum for all cameras
	Real m_fFrustumLeft;
	Real m_fFrustumRight;
	Real m_fFrustumBottom;
	Real m_fFrustumTop;
	Real m_fFrustumNear;
	Real m_fFrustumFar;

	// polygon display mode
	Int m_ePolyMode;

	// polygonizer and its camera
	Polygonizer m_kPolygonizer;
	Camera m_kPolyCam;

	// scanline raytracer and its camera, and image
	RayTracer m_kRayTracer;
	Camera m_kRayTracerCam;
	Image m_kRayTracerImage;

	// hypertexture renderer and its camera, and image
	Hypertexture m_kHyper;
	Camera m_kHyperCam;
	Image m_kHyperImage;

	// enumerated function index, name, and pointer
	UInt m_uiFuncIndex;
	const char* m_aucFuncName;
	Operator m_pvFunction;

	// enumerated visualization mode
	VisualizerMode m_eVisMode;

	// constants to convert from cell count
	static const Real ms_fCellToRayScale = 2;
	static const Real ms_fCellToHyperStepScale = 0.4;
};

//******************************************************************************

} // end namespace: dg

//******************************************************************************

# endif

