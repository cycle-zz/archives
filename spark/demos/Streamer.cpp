#include "Streamer.h"

#include "SpWindow.h"
#include "SpGlHeaders.h"
#include "SpGlutHeaders.h"
#include "SpRandom.h"
#include "SpMaths.h"
#include "SpResourcePath.h"
#include "SpGlslVertexProgram.h"
#include "SpGlslFragmentProgram.h"
#include "SpGlManager.h"
#include "SpCopyToTexture.h"
#include "SpMultiTexturedQuad.h"

using namespace Spark;

static const char *gs_acModeStrings[] =
{
	"rgb double tex2D",
    "rgb tex2D rtt",
	"rgba texRECT rtt",
	"r=16f texRECT rtt",
    "rgb=16f texRECT rtt",
	"rgb=16f tex2D rtt",
    "rgb=16f texRECT ctt",
	"rgb=16f tex2D ctt",
    "rgb tex2D",
    "rgba tex2D",
    "rgba=8 ctt",
    "rgba samples=4 tex2D ctt",
    "rgba=8 tex2D mipmap",
    "rgb=5,6,5 tex2D",
    "rgba=16f texRECT",
    "rgba=32f texRECT",
    "rgba=16f texRECT ctt",
    "r=32f texRECT ctt",
    "rgb double tex2D",
    "r=32f texRECT ctt aux=4",
	"rgb=16f texRECT rtt",
	"rgb=16f texRECT ctt",
	"r=16f tex2D rtt"
};

static int gs_iModeStringCount = sizeof(gs_acModeStrings) / sizeof(char*);
static int gs_iCurrentModeString = 0;

//******************************************************************************
Streamer skApp;
//******************************************************************************
Streamer::Streamer( ) :
	SpWindow("Streamer", 0, 0, 512, 512, Color4f(0.0f, 0.0f, 0.0f, 1.0f))
{
	//	EMPTY!
}
//******************************************************************************
Streamer::~Streamer()
{
	//	EMPTY!
}
//******************************************************************************
bool Streamer::onStartup()
{
	SeedRandom(m_kTimer.seconds());

	m_bUsePerspective = true;
	m_bShowInfo = true;
	m_bShowBounds = true;

	m_bAnimate = true;
	m_bUpdate = true;
	m_bRotate = false;

	m_iSpinX = 0;
	m_iSpinY = 0;

	m_iOrigX = 0;
	m_iOrigY = 0;

	m_fTransparency = 0.5;

	m_fCameraX = 0;
	m_fCameraY = 0;
	m_fCameraZ = 0;

	m_fSpacing = 0.5f;
	m_fLacunarity = 2.0345f;
	m_fOctaves = 4;

	m_uiScanLine = 0;
	m_fDisplacement = 0.0f;
	m_uiResolution = 105;
	m_kGrid.setResolution( m_uiResolution, m_uiResolution );

	m_bSpin = true;
	m_bMove = false;

	m_ePolygonMode = GL_FILL;
	m_kTextureScale = Vector3f(10,10,10);
	return true;
}
//******************************************************************************
bool Streamer::onInitialize()
{
    glLoadIdentity();
    gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
    glDisable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.4, 0.6, 0.8, 1);

	m_pkVertexNoise = new SpVertexNoiseBasis();
	m_pkVertexNoise->initialize();
	m_pkVertexNoise->disable();

	m_pkRenderTexture = createRenderTexture(
		gs_acModeStrings[ gs_iCurrentModeString ],
		width(), height()
	);

//	return true;

	m_pkCopyToTexture = new SpCopyToTexture();

	m_pkTurbulence = new SpTurbulenceOp( 1, 1, 1, m_fOctaves, m_fSpacing, m_fLacunarity );
	m_pkTurbulence->setInputStream( m_pkVertexNoise );
	m_pkTurbulence->initialize( m_pkRenderTexture, m_pkCopyToTexture, true );

	setBackground();
	setLights();
	setMaterials();

	onReshape( width(), height() );

//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
//    glDisable(GL_LIGHTING);
//    glEnable(GL_COLOR_MATERIAL);
//    glEnable(GL_DEPTH_TEST);
	return true;
}
//******************************************************************************
void Streamer::onReshape( int iWidth, int iHeight )
{
    if (iHeight == 0) iHeight = 1;

	Window::onReshape(iWidth, iHeight);

    glViewport(0, 0, iWidth, iHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

//	gluPerspective(60.0, (GLfloat)iWidth/(GLfloat)iHeight, 1, 5.0);
/*
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
*/
	glMatrixMode( GL_MODELVIEW );
}
//******************************************************************************
void Streamer::onDisplay()
{

	//m_pkVertexNoise->setScale(
	//	m_kTextureScale[0],
	//	m_kTextureScale[1],
	//	m_kTextureScale[2]
	//);
	//m_pkVertexNoise->setGridResolution( m_uiResolution );
	//m_pkVertexNoise->sendOutputToBuffer( m_pkRenderTexture, m_pkCopyToTexture);

	m_pkVertexNoise->setScale(
		m_kTextureScale[0],
		m_kTextureScale[1],
		m_kTextureScale[2]
	);
	m_pkVertexNoise->setGridResolution( m_uiResolution );

	m_pkTurbulence->setIncrement( m_fSpacing );
	m_pkTurbulence->setLacunarity( m_fLacunarity );
	m_pkTurbulence->setOctaves( m_fOctaves );

	if(m_pkTurbulence->sendOutputToBuffer( m_pkRenderTexture, m_pkCopyToTexture ))
		updateDisplay(m_pkRenderTexture, m_kTextureScale[1], m_kTextureScale[1]);

	if(m_bShowInfo)
		drawText();

	//glFlush();

	//swapBuffers();
	updateClicks();
}
//******************************************************************************
void Streamer::process()
{
}
//******************************************************************************
void Streamer::drawText()
{
/*
	GLint iMatrixMode;
	GLint iVP[4];

	int iLine = 0;
	int iCharSpacing = 3;
	int iLineSpacing = 13;
	int iStartOffest = 7;

	int iW = width();
	int iH = height();

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
		sprintf(acOutString, "Sample Rays [ %d ] - RayHits [ %d ] - Step Size [ %f ] - Noise Freq [ %f ] - Resolution [ %d x %d ]",
			m_kHyper.getSamples(), m_kHyper.getRayHits(), m_kHyper.getStepSize(), m_kHyper.getNoiseFrequency(), iW, iH);

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
*/
}
//******************************************************************************
void Streamer::onMouseMotion( int iX, int iY, unsigned int uiModifiers )
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
void Streamer::onMouseClick( int iButton, int iState, int iX, int iY, unsigned int uiModifiers)
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
	}
}
//******************************************************************************
void Streamer::onKeyDown( unsigned char ucKey, int, int )
{

	// this should be in the switch statement, but gcc v3.3 complains
	if(ucKey == KEY_ESCAPE)
	{
		onTerminate();
		exit(0);
	}

	// handle the key event
	switch (ucKey)
	{
		case 'm':
		{
			++gs_iCurrentModeString %= gs_iModeStringCount;
			destroyRenderTexture(m_pkRenderTexture);

			m_pkRenderTexture = createRenderTexture(
				gs_acModeStrings[gs_iCurrentModeString],
				width(), height()
			);

			if(m_pkTurbulence)
				delete m_pkTurbulence;

			m_pkTurbulence = new SpTurbulenceOp(
				1, 1, 1, m_fOctaves, m_fSpacing, m_fLacunarity
			);
			m_pkTurbulence->setInputStream( m_pkVertexNoise );
			break;
		}
		case ' ':
		{
			m_bAnimate = !m_bAnimate;
			fprintf(stderr, "Animation: %s\n",
				(!m_bAnimate) ? "Disabled" : "Enabled");
		}
		case '=':
		case '+':
			m_kTextureScale[0] = m_kTextureScale[1] = m_kTextureScale[2] *= 0.95f;
			fprintf(stderr, "Texture Scale: %f\n", m_kTextureScale[1]);
			break;
		case '-':
		case '_':
			m_kTextureScale[0] = m_kTextureScale[1] = m_kTextureScale[2] *= 1.05f;
			fprintf(stderr, "Texture Scale: %f\n", m_kTextureScale[1]);
			break;
		case '[':
			m_uiResolution += 1;
			fprintf(stderr, "Grid Resolution: %d\n", m_uiResolution);
			break;
		case ']':
			if(m_uiResolution > 1)
				m_uiResolution -= 1;
			fprintf(stderr, "Grid Resolution: %d\n", m_uiResolution);
			break;
		case 'w' :
		{
			fprintf(stderr, "Wireframe Mode: %s\n",
				(m_ePolygonMode == GL_FILL) ? "Disabled" : "Enabled");

			if (m_ePolygonMode == GL_LINE)
				m_ePolygonMode = GL_FILL;
			else
				m_ePolygonMode = GL_LINE;
			postRedisplay();
			break;
		}
		case '\'':
			m_fDisplacement += 0.1f;
			break;
		case ';':
			m_fDisplacement -= 0.1f;
			break;
		case 'g':
			m_iModelIndex = 1;
			break;
		case 'L':
			m_fLacunarity *= 1.001f;
			fprintf(stderr, "Lacunarity: %f\n", m_fLacunarity);
			break;
		case 'l':
			m_fLacunarity *= 0.999f;
			fprintf(stderr, "Lacunarity: %f\n", m_fLacunarity);
			break;
		case 'S':
			m_fSpacing *= 1.05f;
			fprintf(stderr, "Spacing: %f\n", m_fSpacing);
			break;
		case 's':
			m_fSpacing *= 0.95f;
			fprintf(stderr, "Spacing: %f\n", m_fSpacing);
			break;
		case 'O':
			m_fOctaves *= 1.05f;
			fprintf(stderr, "Octaves: %f\n", m_fOctaves);
			break;
		case 'o':
			m_fOctaves *= 0.95f;
			fprintf(stderr, "Octaves: %f\n", m_fOctaves);
			break;

	};

	postRedisplay();
}
//******************************************************************************
void Streamer::onSpecialKeyDown( int iKey, int, int )
{
/*
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
*/
}
//******************************************************************************
void Streamer::setBackground()
{
	float afBackgroundColor[] = {0.10f, 0.10f, 0.10f, 1.00f };

	glClearColor( afBackgroundColor[0],
				  afBackgroundColor[1],
				  afBackgroundColor[2],
				  afBackgroundColor[3] );

	// glClearDepth( 1.0 );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

}
//******************************************************************************
void Streamer::setLights()
{
	float afLightAmbient [] = {0.50, 0.50, 0.50, 1.00 };
	float afLightDiffuse [] = {0.75, 0.75, 0.75, 1.00 };
	float afLightSpecular[] = {1.00, 1.00, 1.00, 1.00 };

//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, m_ePolygonMode);

//	glLightfv( GL_LIGHT0, GL_AMBIENT, afLightAmbient);
//	glLightfv( GL_LIGHT0, GL_DIFFUSE, afLightDiffuse);
//	glLightfv( GL_LIGHT0, GL_SPECULAR, afLightSpecular);
//	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);

//	glEnable( GL_LIGHT0 );
}
//******************************************************************************
void Streamer::setMaterials()
{
	float fAlpha = 1.0f - m_fTransparency;
	float fShininess = 0.20f;

	float afAmbientRed [] =   { 0.25f, 0.10f, 0.00f, fAlpha };
	float afAmbientBlue [] =  { 0.00f, 0.00f, 0.25f, fAlpha };

	float afDiffuseRed [] =   { 1.00f, 0.80f, 0.00f, fAlpha };
	float afDiffuseBlue [] =  { 0.00f, 0.00f, 0.75f, fAlpha };

	float afSpecularWhite[] = { 0.50f, 0.50f, 0.50f, fAlpha*0.5f };
/*
	glMaterialfv(GL_BACK, GL_AMBIENT, afAmbientBlue);
	glMaterialfv(GL_BACK, GL_DIFFUSE, afDiffuseBlue);
	glMaterialfv(GL_FRONT, GL_AMBIENT, afAmbientRed);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, afDiffuseRed);
	glMaterialfv(GL_FRONT, GL_SPECULAR, afSpecularWhite);
	glMaterialf( GL_FRONT, GL_SHININESS, fShininess);

	glEnable( GL_BLEND );
//	glBlendFunc();
*/
}
//******************************************************************************
void Streamer::setupFrustum( int iWidth, int iHeight, bool bPerspective )
{
	float fAspect = 0;
	float fVolume = 0;

	if (iWidth <= iHeight)
		fAspect = (float)iHeight / (float)iWidth;
	else
		fAspect = (float)iWidth / (float)iHeight;

	if(!bPerspective)
	{
		fVolume = Sqrt(2) / 2.0f;
		m_fFrustumNear = -100 * fVolume;
		m_fFrustumFar = 100 * fVolume;
	}
	else
	{
		m_fFrustumNear = 0.1f;
		m_fFrustumFar = 100;
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
void Streamer::startCalcTimer()
{
	m_kTimer.reset();
	m_kTimer.start();

	m_uiHours = 0;
	m_uiMinutes = 0;
	m_uiSeconds = 0;
	m_uiMilliSecs = 0;
}
//******************************************************************************
void Streamer::stopCalcTimer()
{
	// dont stop the timer, just grab the current time values
	updateCalcTimer();
}
//******************************************************************************
void Streamer::updateCalcTimer()
{
	m_uiHours = m_kTimer.elapsedHours();
	m_uiMinutes = m_kTimer.elapsedMinutes() % 60;
	m_uiSeconds = m_kTimer.elapsedSeconds() % 60;
	m_uiMilliSecs = m_kTimer.elapsedMilliseconds() % 1000;
}
//******************************************************************************
void Streamer::onUpdate(int iDT)
{
//	m_fTime = iDT;

	if(m_bAnimate)
		m_kTextureOffset[1] -= 0.01f;

	postRedisplay();
}
//******************************************************************************
SpGpuBuffer* Streamer::createRenderTexture(const char *acModeString, int iResX, int iResY)
{
    printf("\nCreating GPU Buffer with mode string: \"%s\"\n", acModeString);

    SpGpuBuffer* pkNewBuffer = new SpGpuBuffer();
    pkNewBuffer->reset(acModeString);
    if (!pkNewBuffer->initialize(iResX, iResY))
    {
        fprintf(stderr, "GPU Buffer Initialization failed!\n");
    }

    // setup the rendering context for the GPU Buffer
    if (pkNewBuffer->enable())
    {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-1, 1, -1, 1, 0, 10);
		glViewport(0, 0, width(), height());

//		skApp.onReshape(iResX, iResY);
//        glMatrixMode(GL_MODELVIEW);
//        glLoadIdentity();
//        gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
//        glEnable(GL_LIGHTING);
//        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
//        glEnable(GL_CULL_FACE);
//        glEnable(GL_DEPTH_TEST);
//        glClearColor(0.2, 0.2, 0.2, 1);

		pkNewBuffer->disable();
    }

	pkNewBuffer->enableTextureFiltering();
	GlManager::printOnError( "creating GPU buffer" );

    return pkNewBuffer;
}
//******************************************************************************
void Streamer::destroyRenderTexture(SpGpuBuffer* pkBuffer)
{
    delete pkBuffer;
}
//******************************************************************************
void Streamer::updateDisplay(SpGpuBuffer* pkBuffer, int rectAngle, int torusAngle)
{
/*
	if (pkBuffer->isInitialized() && pkBuffer->enable())
	{
		if (pkBuffer->isDoubleBuffered()) glDrawBuffer(GL_BACK);
        m_pkVertexNoise->enable();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        glRotatef(m_iSpinX, 1, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(1,1,0);

        if (pkBuffer->isFloatTexture())
        {
			GlslManager::enableFragmentPassThrough();
        }
		glPolygonMode(GL_FRONT_AND_BACK, m_ePolygonMode);
        glutSolidTorus(0.25, 1, m_uiResolution, m_uiResolution);

        if (pkBuffer->isFloatTexture())
        {
			GlslManager::disableFragmentPrograms();
        }

        glPopMatrix();
		m_pkVertexNoise->disable();
	    pkBuffer->disable();
    }

	m_pkVertexNoise->sendOutputToBuffer
*/
    glColor3f(1, 1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glRotatef(rectAngle / 10, 0, 1, 0);

    if (pkBuffer->isTexture())
	{
        if (pkBuffer->isDoubleBuffered())
			pkBuffer->bindBuffer(WGL_BACK_LEFT_ARB);

		pkBuffer->bind();
    }

    if (pkBuffer->isFloatTexture())
    {
		GlslManager::enableTexturePassThrough(pkBuffer->isRectangleTexture());
        glActiveTexture(GL_TEXTURE0_ARB);
    }

    pkBuffer->enableTextureTarget();

    float maxS = (float)pkBuffer->getMaxS();
    float maxT = (float)pkBuffer->getMaxT();

    glBegin(GL_QUADS);
    glTexCoord2f(0,       0); glVertex2f(-1, -1);
    glTexCoord2f(maxS,    0); glVertex2f( 1, -1);
    glTexCoord2f(maxS, maxT); glVertex2f( 1,  1);
    glTexCoord2f(0,    maxT); glVertex2f(-1,  1);
    glEnd();

    if (pkBuffer->isFloatTexture())
    {
		GlslManager::disableFragmentPrograms();
    }

    pkBuffer->disableTextureTarget();

    glPopMatrix();
	glFlush();
    glutSwapBuffers();
}
//******************************************************************************
