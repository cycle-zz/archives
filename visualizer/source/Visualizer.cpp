#include "Window.h"
#include "Implicits.h"
#include "Operators.h"
#include "Shading.h"
#include "Volumes.h"
#include "Visualizer.h"
#include "GlutHeaders.h"
#include "Random.h"
#include "Matrix.h"

using namespace dg;

Visualizer skApp;

//******************************************************************************
Visualizer::Visualizer( ) :
	Window("Visualizer", 0, 0, 600, 600, Color(0.1f, 0.1f, 0.1f, 1.0f)),
	m_uiFuncIndex(4), m_eVisMode(VM_MARCHING_TETRA)
{
	//	EMPTY!
}
//******************************************************************************
Visualizer::~Visualizer()
{
	//	EMPTY!
}
//******************************************************************************
Bool Visualizer::onStartup()
{
	SeedRandom(m_kTimer.seconds());
	m_uiFuncIndex = RandomInt();
	
	m_bShowInfo = true;
	m_bShowBounds = true;

	m_bRayTraced = false;
	m_bHyperTraced = false;
	m_bPolygonized = false;
	m_bUpdate = true;
	m_bRotate = false;

	m_iSpinX = 0;
	m_iSpinY = 0;

	m_iOrigX = 0;
	m_iOrigY = 0;

	m_iCellCount = 20;

	m_fScale = 5;
	m_fIsoLevel = 0.01;
	m_fTime = 0.0;

	m_fTransparency = 0.5;
	m_fOffsetX = -0.5;
	m_fOffsetY = -0.5;
	m_fOffsetZ = -0.5;

	m_fCameraX = 0;
	m_fCameraY = 0;
	m_fCameraZ = 0;
	
	m_uiScanLine = 0;

	m_bSpin = true;
	m_bMove = false;
	m_bLight = true;
	m_bFadeOut = true;
	m_bKeepInView = true;
	m_bRendering = false;
	m_bUsePerspective = false;

	m_uiFuncIndex = m_uiFuncIndex % ImplicitFuncCount;
	m_aucFuncName = ImplicitFunc[ m_uiFuncIndex ].name;
	m_pvFunction = ImplicitFunc[ m_uiFuncIndex ].op;

	m_ePolyMode = GL_FILL;
	m_eMarchMode = Polygonizer::MM_CUBES;

	m_kRayTracer.setFunction( m_pvFunction );
	m_kRayTracer.setCamera( &m_kRayTracerCam );
	m_kRayTracer.setLightDirection( m_kRayTracerCam.getDirection() );

	m_kHyper.setDensityFunction( m_pvFunction );
	m_kHyper.setCamera( &m_kHyperCam );
	m_kHyper.setLightDirection( m_kHyperCam.getDirection() );

	return true;
}
//******************************************************************************
Bool Visualizer::onInitialize()
{
	setBackground();
	setLights();
	setMaterials();

	setupPolygonizer();

	onReshape( width(), height() );

	return true;
}
//******************************************************************************
void Visualizer::onReshape( Int iWidth, Int iHeight )
{
	Window::onReshape(iWidth, iHeight);

	setupFrustum( iWidth, iHeight, m_bUsePerspective );
	glViewport( 0, 0, iWidth, iHeight );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if( m_bUsePerspective )
	{
		glFrustum(
			m_fFrustumLeft, m_fFrustumRight,
			m_fFrustumBottom, m_fFrustumTop,
			m_fFrustumNear, m_fFrustumFar);
	}
	else
	{
		glOrtho(
			m_fFrustumLeft, m_fFrustumRight,
			m_fFrustumBottom, m_fFrustumTop,
			m_fFrustumBottom, m_fFrustumFar);
	}

	glMatrixMode( GL_MODELVIEW );
}
//******************************************************************************
void Visualizer::onDisplay()
{
	// setup the background
	setBackground();

	if (m_bMove)
	{
		m_fTime += 0.025;
		update(m_fTime);
		m_bUpdate = true;
	}

	if(m_eVisMode == VM_MARCHING_CUBES || m_eVisMode == VM_MARCHING_TETRA)
		drawPolygons();
	else if(m_eVisMode == VM_RAYTRACE)
		drawRaytraced();
	else if(m_eVisMode == VM_HYPERTEXTURE)
		drawHypertexture();

	if(m_bShowInfo)
		drawText();

	swapBuffers();
	updateClicks();
}
//******************************************************************************
void Visualizer::drawRaytraced()
{
	// if scene was already rendered, just redraw it and return
	if(m_bRayTraced)
	{
		// setup the background
		setBackground();

		// draw the image
		drawImage( m_kRayTracerImage.pixels(), 0, 0,
				   m_kRayTracerImage.width(), m_kRayTracerImage.height(), true );
		return;
	}
	
	// setup for rendering
	if(m_bRendering == false)
	{
		// start the timer
		startCalcTimer();
		
		// set the increment based on the image resolution
		m_uiScanIncrement = (UInt)( 10 * (1.0 / m_kRayTracerImage.height()) * 1000 );

		// initialize render loop
		m_bRendering = true;

		// setup the background
		setBackground();

		// draw info
		if(m_bShowInfo)
			drawText();
		
		// swap the buffers so the render message shows up
		swapBuffers();
	}
	
	// render the scene incrementally, so we can periodically update the screen
	if(m_uiScanLine < m_kRayTracerImage.height())
	{
		// render the scanline range
		m_kRayTracer.render(m_uiScanLine, m_uiScanLine + m_uiScanIncrement);

		// increment for next iteration
		m_uiScanLine += m_uiScanIncrement;

		// update the timer
		updateCalcTimer();

	}
	else
	{
		// stop the timer
		stopCalcTimer();

		// toggle the update flags
		m_bUpdate = false;
		m_bRayTraced = true;
		m_bRendering = false;

		// reset the scanline index
		m_uiScanLine = 0;
	}

	// setup the background
	setBackground();

	// get the index to the last valid scanline
	UInt uiLast = m_uiScanLine > m_kRayTracerImage.height() ?
				  m_kRayTracerImage.height() : m_uiScanLine;

	// draw the image, up to the current scanline
	drawImage( m_kRayTracerImage.pixels(), 0, 0,
			   m_kRayTracerImage.width(), uiLast, true );

	if(m_bShowInfo)
		drawText();

}
//******************************************************************************
void Visualizer::drawHypertexture()
{
	// if scene was already rendered, just redraw it and return
	if(m_bHyperTraced)
	{
		// setup the background
		setBackground();

		// draw the image
		drawImage( m_kHyperImage.pixels(), 0, 0,
				   m_kHyperImage.width(), m_kHyperImage.height(), true );
		return;
	}
	
	// setup for rendering
	if(m_bRendering == false)
	{
		// start the timer
		startCalcTimer();
		
		// set the increment based on the image resolution
		m_uiScanIncrement = (UInt)( 2 * (1.0 / m_kHyperImage.height()) * 1000 );

		// initialize render loop
		m_bRendering = true;

		// setup the background
		setBackground();

		// draw info
		if(m_bShowInfo)
			drawText();
		
		// swap the buffers so the render message shows up
		swapBuffers();
	}
	
	// render the scene incrementally, so we can periodically update the screen
	if(m_uiScanLine < m_kHyperImage.height())
	{
		// render the scanline range
		m_kHyper.render(m_uiScanLine, m_uiScanLine + m_uiScanIncrement);

		// increment for next iteration
		m_uiScanLine += m_uiScanIncrement;

		// update the timer
		updateCalcTimer();
	}
	else
	{
		// stop the timer
		stopCalcTimer();
		
		// toggle the update flags
		m_bUpdate = false;
		m_bHyperTraced = true;
		m_bRendering = false;
		
		// reset the scanline index 
		m_uiScanLine = 0;
	}
	
	// get the index to the last valid scanline
	UInt uiLast = m_uiScanLine > m_kHyperImage.height() ? 
				  m_kHyperImage.height() : m_uiScanLine;

	// setup the background
	setBackground();

	// draw the image, up to the current scanline
	drawImage( m_kHyperImage.pixels(), 0, 0,
			   m_kHyperImage.width(), uiLast, true );

	// draw info
	if(m_bShowInfo)
		drawText();
}
//******************************************************************************
void Visualizer::drawPolygons()
{
	// intialize camera
	setupCamera( m_kPolyCam );

	// update if necessary
	if(m_bUpdate || !m_bPolygonized)
	{
		startCalcTimer();
		m_kPolygonizer.evaluate(m_eMarchMode);
		stopCalcTimer();
		m_bUpdate = false;
		m_bPolygonized = true;
	}

	// set view matrix
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Vector kPos = m_kPolyCam.getPosition();
	Vector kUp = m_kPolyCam.getUp();
	Vector kLookAt = kPos + m_kPolyCam.getDirection();

	gluLookAt(kPos.x(), kPos.y(), kPos.z(),
			  kLookAt.x(), kLookAt.y(), kLookAt.z(),
			  kUp.x(), kUp.y(), kUp.z());

	glPushMatrix();

	if(m_bShowBounds)
	{
		glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		glColor3f(1.0, 1.0, 1.0);
		glutWireCube(1.0);
		glPopAttrib();
	}

	glPushMatrix();
	glTranslatef( -0.5, -0.5, -0.5);
	glBegin(GL_TRIANGLES);

	UInt uiVertexCount = m_kPolygonizer.getVertices().size();
	for (UInt i = 0; i < uiVertexCount; i++)
	{
		glNormal3f(	m_kPolygonizer.getNormals()[i].x(),
					m_kPolygonizer.getNormals()[i].y(),
					m_kPolygonizer.getNormals()[i].z());

		if(!m_bLight)
			glColor3f(	m_kPolygonizer.getColors()[i].r(),
						m_kPolygonizer.getColors()[i].g(),
						m_kPolygonizer.getColors()[i].b());

		glVertex3f(	m_kPolygonizer.getVertices()[i].x(),
					m_kPolygonizer.getVertices()[i].y(),
					m_kPolygonizer.getVertices()[i].z());
	}
	glEnd();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}
//******************************************************************************
void Visualizer::drawText()
{
	GLint iMatrixMode;
	GLint iVP[4];

	Int iLine = 0;
	Int iCharSpacing = 3;
	Int iLineSpacing = 13;
	Int iStartOffest = 7;

	Int iW = width();
	Int iH = height();

	Color kTextColor(1.0, 0.8, 0.0, 1.0);

	Char acOutString [256] = "";

	// disable lighting
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);

	// save the current viewport
	glGetIntegerv(GL_VIEWPORT, iVP);
	glViewport(0, 0, iW, iH);

	// save the current matrixmode
	glGetIntegerv(GL_MATRIX_MODE, &iMatrixMode);

	// clear out the projection matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// clear out the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// start outputting from the bottom of the screen, upwards
	glScalef(2.0f / iW, -2.0f / iH, 1.0f);
	glTranslatef(-iW / 2.0f, -iH / 2.0f, 0.0f);

	// set the current text color
	glColor4f( kTextColor.r(), kTextColor.g(), kTextColor.b(), kTextColor.a() );

	// output a notice if rendering
	if(m_bRendering)
	{
		sprintf(acOutString, "... RENDERING ...");

		drawString(acOutString, width()/2 - strlen(acOutString) * iCharSpacing,
			height()/2 - (iLineSpacing), kTextColor);
	}

	if(m_eVisMode == VM_MARCHING_CUBES)
	{
		sprintf(acOutString, "Vis Method [ Marching Cubes ] - Function [ %s ] - Calc Time [ %02u:%02u:%02u.%02u sec ]",
			m_aucFuncName, m_uiHours, m_uiMinutes, m_uiSeconds, m_uiMilliSecs);
		drawString(acOutString, 10,
			iH - (iLineSpacing * iLine++) - iStartOffest, kTextColor);
	}
	else if(m_eVisMode == VM_MARCHING_TETRA)
	{
		sprintf(acOutString, "Vis Method [ Marching Tetra ] - Function [ %s ] - Calc Time [ %02u:%02u:%02u.%02u sec ]",
			m_aucFuncName, m_uiHours, m_uiMinutes, m_uiSeconds, m_uiMilliSecs);
		drawString(acOutString, 10,
			iH - (iLineSpacing * iLine++) - iStartOffest, kTextColor);
	}
	else if(m_eVisMode == VM_RAYTRACE)
	{
		sprintf(acOutString, "Vis Method [ Raytraced ] - Function [ %s ] - Calc Time [ %02u:%02u:%02u.%02u sec ]",
			m_aucFuncName, m_uiHours, m_uiMinutes, m_uiSeconds, m_uiMilliSecs);
		drawString(acOutString, 10,
			iH - (iLineSpacing * iLine++) - iStartOffest, kTextColor);
	}
	else if(m_eVisMode == VM_HYPERTEXTURE)
	{
		sprintf(acOutString, "Vis Method [ Hypertexture ] - Function [ %s ] - Calc Time [ %02u:%02u:%02u.%02u sec ]",
			m_aucFuncName, m_uiHours, m_uiMinutes, m_uiSeconds, m_uiMilliSecs);
		drawString(acOutString, 10,
			iH - (iLineSpacing * iLine++) - iStartOffest, kTextColor);
	}

	// format the text
	sprintf(acOutString, "IsoLevel [ %0.3f ] - Scale [ %0.3f ] - Offset [ %0.3f %0.3f %0.3f ] - Spin[ %d %d ]",
		m_fIsoLevel, 1.0f/m_fScale, m_fOffsetX, m_fOffsetY, m_fOffsetZ,
		m_iSpinX%360, m_iSpinY%360);

	// draw the text to the screen
	drawString(acOutString, 10,
		iH - (iLineSpacing * iLine++) - iStartOffest, kTextColor);

	// output appropriate text for the current mode
	if(m_eVisMode == VM_MARCHING_CUBES || m_eVisMode == VM_MARCHING_TETRA )
	{
		sprintf(acOutString, "Cells [ %d x %d x %d ] - Polygons [ %d ] - Vertices [ %d ]",
			m_iCellCount, m_iCellCount, m_iCellCount,
			m_kPolygonizer.getVertices().size()/3,
			m_kPolygonizer.getVertices().size());

		drawString(acOutString, 10,
			iH - (iLineSpacing * iLine++) - iStartOffest, kTextColor);
	}
	else if(m_eVisMode == VM_RAYTRACE)
	{
		sprintf(acOutString, "Sample Rays [ %d ] - Ray Hits [ %d ] - Resolution [ %d x %d ]",
			(UInt)(m_iCellCount * ms_fCellToRayScale), m_kRayTracer.getRayHits(), iW, iH);

		drawString(acOutString, 10,
			iH - (iLineSpacing * iLine++) - iStartOffest, kTextColor);
	}
	else if(m_eVisMode == VM_HYPERTEXTURE)
	{
		sprintf(acOutString, "Sample Rays [ %d ] - RayHits [ %d ] - Step Size [ %f ] - Resolution [ %d x %d ]",
			m_kHyper.getSamples(), m_kHyper.getRayHits(), m_kHyper.getStepSize(), iW, iH);

		drawString(acOutString, 10,
			iH - (iLineSpacing * iLine++) - iStartOffest, kTextColor);
	}

	// restore the projection matrix
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);

	// restore the previous matrix
	glPopMatrix();
	glMatrixMode(iMatrixMode);

	// restor the previous attributes
	glPopAttrib();

	// restore the previous viewport
	glViewport(iVP[0], iVP[1], iVP[2], iVP[3]);
}
//******************************************************************************
void Visualizer::onMouseMotion( Int iX, Int iY, UInt )
{
	if( m_bRotate )
	{
		// accumulate rotation from update deltas (not great, but it works)
		m_iSpinY = ( m_iSpinY + (iX - m_iOrigX) );
		m_iSpinX = ( m_iSpinX + (iY - m_iOrigY) );
		m_iOrigX = iX;
		m_iOrigY = iY;
	}
}
//******************************************************************************
void Visualizer::onMouseClick( Int iButton, Int iState, Int iX, Int iY,UInt uiModifiers)
{
	Window::onMouseClick(iButton, iState, iX, iY, uiModifiers);

	// clear the rotation flag
	m_bRotate = false;
	if ( m_bLeftMousePressed || m_bRightMousePressed || m_bMiddleMousePressed )
	{
		// save the current update position
		m_iOrigX = iX;
		m_iOrigY = iY;

		// toggle the rotation flag
		m_bRotate = true;

		// reset the visulization mode to marching tetra
		if(m_eVisMode == VM_RAYTRACE || m_eVisMode == VM_HYPERTEXTURE)
			m_eVisMode = VM_MARCHING_TETRA;
	}
}
//******************************************************************************
void Visualizer::onKeyDown( UChar ucKey, Int, Int )
{
	// stop any rendering if a key is pressed
	if( m_bRendering )
	{
		// reset the rendering flag
		m_bRendering = false;
		
		// toggle completion for raytracer
		if(m_eVisMode == VM_RAYTRACE)
			m_bRayTraced =true;
		
		// toggle completion for hypertexture
		if(m_eVisMode == VM_HYPERTEXTURE)
			m_bHyperTraced =true;
		
		// reset the scanline index
		m_uiScanLine = 0;
		
		// just return, don't handle the key event!
		return;
	}
	
	switch (ucKey)
	{
		case 'i':
		{
			m_bShowInfo = !m_bShowInfo;
			break;
		}
		case 'b' :
		{
			m_bShowBounds = !m_bShowBounds;
			break;
		}
		case 'j' :
		{
			m_bFadeOut = !m_bFadeOut;
			break;
		}
		case 'k' :
		{
			m_bKeepInView = !m_bKeepInView;
			break;
		}
		case '+' :
		case '=' :
		{
			++m_iCellCount;
			m_kPolygonizer.setCellCount( m_iCellCount );
			setupPolygonizer();
			break;
		}
		case '-' :
		{
			if (m_iCellCount > 1)
			{
				--m_iCellCount;
				m_kPolygonizer.setCellCount( m_iCellCount );
				setupPolygonizer();
			}
			break;
		}
		case 'e' :
		{
			m_eVisMode = VM_HYPERTEXTURE;
			setupHypertexture();
			break;
		}
		case 'r' :
		{
			m_eVisMode = VM_RAYTRACE;
			setupRayTracer();
			break;
		}
		case 't' :
		{
			m_eMarchMode = Polygonizer::MM_TETRA;
			m_eVisMode = VM_MARCHING_TETRA;
			setupPolygonizer();
			break;
		}
		case 'y' :
		{
			m_eMarchMode = Polygonizer::MM_CUBES;
			m_eVisMode = VM_MARCHING_CUBES;
			setupPolygonizer();
			break;
		}
		case '[' :
		{
			if (m_fScale < 100.0)
			{
				m_fScale *= 1.1;
				m_kPolygonizer.setScale( m_fScale );
				setupPolygonizer();
			}
			break;
		}
		case ']' :
		{
			if (m_fScale > 0.0001)
			{
				m_fScale /= 1.1;
				m_kPolygonizer.setScale( m_fScale );
				setupPolygonizer();
			}
			break;
		}
		case 'n' :
		{
			if (m_bLight)
				glDisable(GL_LIGHTING); //use vertex colors
			else
				glEnable(GL_LIGHTING); //use lit material color

			m_bLight = !m_bLight;
			break;
		}
		case 'l' :
		{
			if (m_ePolyMode == GL_LINE)
				m_ePolyMode = GL_FILL;
			else
				m_ePolyMode = GL_LINE;
			glPolygonMode(GL_FRONT_AND_BACK, m_ePolyMode);
			break;
		}
		case '<':
		{
			if(m_fTransparency < 1.0)
			{
				m_fTransparency *= 1.05;
				setMaterials();
			}
			break;
		}
		case '>':
		{
			if(m_fTransparency > 0.0)
			{
				m_fTransparency /= 1.05;
				setMaterials();
			}
			break;
		}
		case 'f':
		{
			UInt i = m_uiFuncIndex;
			while( i == m_uiFuncIndex )
				m_uiFuncIndex = RandomInt() % ImplicitFuncCount;

			m_bUpdate = true;
			m_bRayTraced = false;
			m_bHyperTraced = false;
			m_bPolygonized = false;
			setupPolygonizer();
			break;
		}
		case 'g':
		{
			m_uiFuncIndex++;
			m_bUpdate = true;
			m_bRayTraced = false;
			m_bHyperTraced = false;
			m_bPolygonized = false;
			setupPolygonizer();
			break;			
		}
		case 'w':
		{
			if(m_fCameraZ < m_fFrustumFar)
				m_fCameraZ += 0.1;
			break;
		}
		case 's':
		{
			if(m_fCameraZ > 0)
				m_fCameraZ -= 0.1;
			break;
		}
		case 'p':
		{
			m_bUsePerspective = !m_bUsePerspective;
			onReshape(width(),height());
			break;
		}
		case 'm':
		{
			m_bMove = !m_bMove;
			setupPolygonizer();
			break;
		}
	}
}
//******************************************************************************
void Visualizer::onSpecialKeyDown( Int iKey, Int, Int )
{
	switch (iKey)
	{
		case GLUT_KEY_PAGE_UP :
			{
				if (m_fIsoLevel < 10000.0)
				{
					m_fIsoLevel *= 1.1;
					m_kPolygonizer.setIsoLevel( m_fIsoLevel );
					setupPolygonizer();
				}
			}
			break;
		case GLUT_KEY_PAGE_DOWN :
			{
				if (m_fIsoLevel > 0.0)
				{
					m_fIsoLevel /= 1.1;
					m_kPolygonizer.setIsoLevel( m_fIsoLevel );
					setupPolygonizer();
				}
			}
			break;
		case GLUT_KEY_HOME :
			{
				m_fOffsetZ += 0.1;
				m_kPolygonizer.setOffset( m_fOffsetX, m_fOffsetY, m_fOffsetZ );
				setupPolygonizer();
			}
			break;
		case GLUT_KEY_END :
			{
				m_fOffsetZ -= 0.1;
				m_kPolygonizer.setOffset( m_fOffsetX, m_fOffsetY, m_fOffsetZ );
				setupPolygonizer();
			}
			break;
		case GLUT_KEY_LEFT:
			{
				m_fOffsetX += 0.1;
				m_kPolygonizer.setOffset( m_fOffsetX, m_fOffsetY, m_fOffsetZ );
				setupPolygonizer();
			}
			break;
		case GLUT_KEY_RIGHT :
			{
				m_fOffsetX -= 0.1;
				m_kPolygonizer.setOffset( m_fOffsetX, m_fOffsetY, m_fOffsetZ );
				setupPolygonizer();
			}
			break;
		case GLUT_KEY_UP :
			{
				m_fOffsetY -= 0.1;
				m_kPolygonizer.setOffset( m_fOffsetX, m_fOffsetY, m_fOffsetZ );
				setupPolygonizer();
			}
			break;
		case GLUT_KEY_DOWN :
			{
				m_fOffsetY += 0.1;
				m_kPolygonizer.setOffset( m_fOffsetX, m_fOffsetY, m_fOffsetZ );
				setupPolygonizer();
			}
			break;

	}
}
//******************************************************************************
void Visualizer::setupPolygonizer()
{
	m_uiFuncIndex = m_uiFuncIndex % ImplicitFuncCount;
	m_aucFuncName = ImplicitFunc[ m_uiFuncIndex ].name;
	m_pvFunction = ImplicitFunc[ m_uiFuncIndex ].op;

	// set the current options
	m_kPolygonizer.setCellCount( m_iCellCount );
	m_kPolygonizer.setScale( m_fScale );
	m_kPolygonizer.setIsoLevel( m_fIsoLevel );
	m_kPolygonizer.setOffset( m_fOffsetX, m_fOffsetY, m_fOffsetZ );
	m_kPolygonizer.setFunction( m_pvFunction );

	m_bPolygonized = false;
	m_bUpdate = true;
	postRedisplay();
	return;
}
//******************************************************************************
void Visualizer::setupRayTracer()
{
	m_uiFuncIndex = m_uiFuncIndex % ImplicitFuncCount;
	m_aucFuncName = ImplicitFunc[ m_uiFuncIndex ].name;
	m_pvFunction = ImplicitFunc[ m_uiFuncIndex ].op;

	// setup the camera
	setupCamera(m_kRayTracerCam);

	// setup the image
	m_kRayTracerImage.setClearColor( bg() );
	m_kRayTracerImage.resize( width(), height(), 4 );
	m_kRayTracerCam.setImage( &m_kRayTracerImage );

	// initialize raytracer
	m_kRayTracer.setSamples((UInt)(m_iCellCount * ms_fCellToRayScale));

	// set the light to the cameras direction
	m_kRayTracer.setLightDirection( -m_kRayTracerCam.getDirection() );

	// blur the resulting image to reduce aliasing
	m_kRayTracer.setBlur(true);

	// set the current isolevel
	m_kRayTracer.setIsoLevel(m_fIsoLevel);

	// set the background and material colors
	//m_kRayTracer.setBackground( bg() );
	m_kRayTracer.setBaseColor( Color(0.0, 0.10, 1.5) );
	m_kRayTracer.setFunction( m_pvFunction );

	// toggle update flags
	m_bRayTraced = false;
	m_bUpdate = true;

	// request refresh
	postRedisplay();
	return;
}
//******************************************************************************
void Visualizer::setupHypertexture()
{
	m_uiFuncIndex = m_uiFuncIndex % DensityFuncCount;
	m_aucFuncName = DensityFunc[ m_uiFuncIndex ].name;
	m_pvFunction = DensityFunc[ m_uiFuncIndex ].op;

	// setup the camera for current view
	setupCamera(m_kHyperCam);

	// setup the image
	//m_kHyperImage.setClearColor( bg() );
	m_kHyperImage.resize( width(), height(), 4 );
	m_kHyperCam.setImage( &m_kHyperImage );

	// set the light to the cameras direction
	//m_kHyper.setLightDirection( -m_kHyperCam.getDirection() );
	m_kHyper.setStepSize( ms_fCellToHyperStepScale / m_iCellCount);

	// set the background and material colors
	//m_kHyper.setBackground( bg() );

	m_kHyper.setDensityFunction( m_pvFunction );
	m_kHyper.setFilteredColorFunction( FilteredClownColorVolume );
	m_kHyper.setKeepInView( m_bKeepInView );
	m_kHyper.setFadeOut( m_bFadeOut );
	m_kHyper.setScale( 1.0f/m_fScale );

	//m_kHyper.setShadingFunction( Phong );

	// toggle update flags
	m_bHyperTraced = false;
	m_bUpdate = true;

	// request refresh
	postRedisplay();
	return;
}
//******************************************************************************
void Visualizer::setBackground()
{
	Real afBackgroundColor[] = {0.10, 0.10, 0.10, 1.00 };

	glClearColor( afBackgroundColor[0],
				  afBackgroundColor[1],
				  afBackgroundColor[2],
				  afBackgroundColor[3] );

	glClearDepth( 1.0 );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

}
//******************************************************************************
void Visualizer::setLights()
{
	Real afLightAmbient [] = {0.50, 0.50, 0.50, 1.00 };
	Real afLightDiffuse [] = {0.75, 0.75, 0.75, 1.00 };
	Real afLightSpecular[] = {1.00, 1.00, 1.00, 1.00 };

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, m_ePolyMode);

	glLightfv( GL_LIGHT0, GL_AMBIENT, afLightAmbient);
	glLightfv( GL_LIGHT0, GL_DIFFUSE, afLightDiffuse);
	glLightfv( GL_LIGHT0, GL_SPECULAR, afLightSpecular);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);

	glEnable( GL_LIGHT0 );
}
//******************************************************************************
void Visualizer::setMaterials()
{
	Real fAlpha = 1.0 - m_fTransparency;
	Real fShininess = 0.20;

	Real afAmbientRed [] =   { 0.25, 0.10, 0.00, fAlpha };
	Real afAmbientBlue [] =  { 0.00, 0.00, 0.25, fAlpha };

	Real afDiffuseRed [] =   { 1.00, 0.80, 0.00, fAlpha };
	Real afDiffuseBlue [] =  { 0.00, 0.00, 0.75, fAlpha };

	Real afSpecularWhite[] = { 0.50, 0.50, 0.50, fAlpha*0.5 };

	glMaterialfv(GL_BACK, GL_AMBIENT, afAmbientBlue);
	glMaterialfv(GL_BACK, GL_DIFFUSE, afDiffuseBlue);
	glMaterialfv(GL_FRONT, GL_AMBIENT, afAmbientRed);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, afDiffuseRed);
	glMaterialfv(GL_FRONT, GL_SPECULAR, afSpecularWhite);
	glMaterialf( GL_FRONT, GL_SHININESS, fShininess);

	glEnable( GL_BLEND );
//	glBlendFunc();

}
//******************************************************************************
void Visualizer::setupCamera(Camera& rkCamera)
{

	// translate the camera due to function scale (not needed for polygonizer)
	Vector kTranslate;
	Vector kCameraPos( m_fCameraX, m_fCameraY, m_fCameraZ );
	if(&rkCamera != &m_kPolyCam)
	{
		setupFrustum( width(), height(), false );
		kTranslate = Vector(-m_fOffsetX, -m_fOffsetY, -m_fScale-m_fOffsetZ);

		// intialize view frustum
		rkCamera.setNear( m_fFrustumNear + m_fScale);
		rkCamera.setFar( m_fFrustumFar );
	}
	else
	{
		setupFrustum( width(), height(), m_bUsePerspective );
		if(!m_bUsePerspective)
			kTranslate = Vector(-m_fOffsetX, -m_fOffsetY, -m_fOffsetZ);
		else
			kTranslate = Vector(-0.5, -0.5, -0.5);

		// intialize view frustum
		rkCamera.setNear( m_fFrustumNear );
		rkCamera.setFar( m_fFrustumFar );
	}

	// intialize camera frame
	rkCamera.setPosition( kCameraPos - kTranslate );

	//rkCamera.setPosition( kTranslate );
	rkCamera.setDirection( Vector(0.0f,0.0f,-1.0f) );
	rkCamera.setUp( Vector(0.0f,1.0f,0.0f) );
	rkCamera.setRight( Vector(-1.0f,0.0f,0.0f) );

	// set the fov to 90 degrees
	if( m_fFrustumRight > m_fFrustumLeft )
		rkCamera.setHalfWidth( m_fFrustumRight - m_fFrustumLeft );
	else
		rkCamera.setHalfWidth( m_fFrustumLeft - m_fFrustumRight );

	if( m_fFrustumTop > m_fFrustumBottom )
		rkCamera.setHalfHeight( m_fFrustumTop - m_fFrustumBottom );
	else
		rkCamera.setHalfHeight( m_fFrustumBottom - m_fFrustumTop );

	// rotate to current view
	Matrix kMR;
	Real fLength = rkCamera.getPosition().length();

	// first rotate about x axis
	kMR = Matrix::buildRotation( Vector(m_iSpinX/2.0f, 0, 0));
	rkCamera.setDirection( kMR*rkCamera.getDirection() );
	rkCamera.setUp( kMR*rkCamera.getUp() );
	rkCamera.setPosition(-fLength*rkCamera.getDirection());

	// then rotate about y axis
	kMR = Matrix::buildRotation( Vector(0, m_iSpinY/2.0f, 0));
	rkCamera.setDirection( kMR*rkCamera.getDirection() );
	rkCamera.setUp( kMR*rkCamera.getUp() );
	rkCamera.setPosition(-fLength*rkCamera.getDirection());
}
//******************************************************************************
void Visualizer::setupFrustum( Int iWidth, Int iHeight, bool bPerspective )
{
	Real fAspect = 0;
	Real fVolume = 0;

	if (iWidth <= iHeight)
		fAspect = (Real)iHeight / (Real)iWidth;
	else
		fAspect = (Real)iWidth / (Real)iHeight;

	if(!bPerspective)
	{
		fVolume = sqrt(2) / 2.0;
		m_fFrustumNear = -10 * fVolume;
		m_fFrustumFar = 10 * fVolume;
	}
	else
	{
		m_fFrustumNear = 0.1;
		m_fFrustumFar = 10;
		fVolume = m_fFrustumNear;	// 45 degrees
	}

	if (iWidth <= iHeight)
	{
		m_fFrustumLeft = -fVolume;
		m_fFrustumRight = fVolume;
		m_fFrustumBottom = -fVolume * fAspect;
		m_fFrustumTop = fVolume * fAspect;
	}
	else
	{
		m_fFrustumLeft = -fVolume * fAspect;
		m_fFrustumRight = fVolume * fAspect;
		m_fFrustumBottom = -fVolume;
		m_fFrustumTop = fVolume;
	}
}
//******************************************************************************
void Visualizer::startCalcTimer()
{
	m_kTimer.reset();
	m_kTimer.start();

	m_uiHours = 0;
	m_uiMinutes = 0;
	m_uiSeconds = 0;
	m_uiMilliSecs = 0;
}
//******************************************************************************
void Visualizer::stopCalcTimer()
{
	// dont stop the timer, just grab the current time values
	updateCalcTimer();
}
//******************************************************************************
void Visualizer::updateCalcTimer()
{
	m_uiHours = m_kTimer.elapsedHours();
	m_uiMinutes = m_kTimer.elapsedMinutes() % 60;
	m_uiSeconds = m_kTimer.elapsedSeconds() % 60;
	m_uiMilliSecs = m_kTimer.elapsedMilliseconds() % 1000;
}
//******************************************************************************
void Visualizer::update(Real fDT)
{
	m_fUpdateOffset = 0.8 + Sine(fDT);

	m_fOffsetX = -0.5f * m_fUpdateOffset;
	m_fOffsetY = -0.5f * m_fUpdateOffset;
	m_fOffsetZ = -0.5f * m_fUpdateOffset;

	if(m_eVisMode == VM_MARCHING_CUBES || m_eVisMode == VM_MARCHING_TETRA)
		setupPolygonizer();
	else if(m_eVisMode == VM_RAYTRACE)
		setupRayTracer();
	else if(m_eVisMode == VM_HYPERTEXTURE)
		setupHypertexture();

	m_fTime = fDT;
}
//******************************************************************************

