#include "SpWindow.h"
#include "SpGlHeaders.h"
#include "SpGlutKeyBindings.h"
#include "SpGlutHeaders.h"

using namespace Spark;

static unsigned int gs_uiGLUTModifiers = 0;
//----------------------------------------------------------------------------
static void ReshapeCallback(int iWidth, int iHeight)
{
	SpWindow* pkWindow = SpWindow::current();
	if ( pkWindow )
		pkWindow->onReshape(iWidth, iHeight);
}
//----------------------------------------------------------------------------
static void DisplayCallback()
{
	SpWindow* pkWindow = SpWindow::current();
	if ( pkWindow )
		pkWindow->onDisplay();
}
//----------------------------------------------------------------------------
static void IdleCallback()
{
	SpWindow* pkWindow = SpWindow::current();
	if ( pkWindow )
		pkWindow->onIdle();
}
//----------------------------------------------------------------------------
static void UpdateCallback( int iValue )
{
	SpWindow* pkWindow = SpWindow::current();
	if ( pkWindow )
		pkWindow->onUpdate( iValue );
}
//----------------------------------------------------------------------------
static void KeyDownCallback(unsigned char ucKey, int iX, int iY)
{
	SpWindow* pkWindow = SpWindow::current();
	if ( pkWindow )
		pkWindow->onKeyDown(ucKey, iX, iY);
}
//----------------------------------------------------------------------------
static void KeyUpCallback(unsigned char ucKey, int iX, int iY)
{
	SpWindow* pkWindow = SpWindow::current();
	if ( pkWindow )
		pkWindow->onKeyUp(ucKey, iX, iY);
}
//----------------------------------------------------------------------------
static void SpecialKeyDownCallback(int iKey, int iX, int iY)
{
	SpWindow* pkWindow = SpWindow::current();
	if ( pkWindow )
		pkWindow->onSpecialKeyDown(iKey, iX, iY);
}
//----------------------------------------------------------------------------
static void SpecialKeyUpCallback(int iKey, int iX, int iY)
{
	SpWindow* pkWindow = SpWindow::current();
	if ( pkWindow )
		pkWindow->onSpecialKeyUp(iKey, iX, iY);
}
//----------------------------------------------------------------------------
static void MouseClickCallback(int iButton, int iState, int iX, int iY)
{
	SpWindow* pkWindow = SpWindow::current();
	if ( pkWindow )
	{
		int iModifiers = glutGetModifiers();
		gs_uiGLUTModifiers = *(unsigned int*) & iModifiers;
		pkWindow->onMouseClick(iButton, iState, iX, iY, gs_uiGLUTModifiers);
	}
}
//----------------------------------------------------------------------------
static void MotionCallback(int iX, int iY)
{
	SpWindow* pkWindow = SpWindow::current();
	if ( pkWindow )
		pkWindow->onMouseMotion(iX, iY, gs_uiGLUTModifiers);
}
//----------------------------------------------------------------------------
static void PassiveMotionCallback(int iX, int iY)
{
	SpWindow* pkWindow = SpWindow::current();
	if ( pkWindow )
		pkWindow->onPassiveMotion(iX, iY);
}
//----------------------------------------------------------------------------
static void Terminate()
{
	SpWindow* pkWindow = SpWindow::current();
	if ( pkWindow )
	{
		pkWindow->onTerminate();
		glutDestroyWindow(pkWindow->id());
		exit(0);
	}
}
//----------------------------------------------------------------------------
void SpWindow::onTerminate()
{
	glutDestroyWindow(id());
	exit(0);
}
//----------------------------------------------------------------------------
void SpWindow::onUpdate( int iValue )
{
	onUpdate( iValue );
	postRedisplay();

	if( iValue > 0 )
		glutTimerFunc( 60, UpdateCallback, 1 );
}
//----------------------------------------------------------------------------
void SpWindow::makeCurrent()
{
	ms_pkWindow = this;
	glutSetWindow( id() );
}
//----------------------------------------------------------------------------
void SpWindow::postRedisplay()
{
	glutPostWindowRedisplay( id() );
}
//----------------------------------------------------------------------------
void SpWindow::swapBuffers()
{
	glutSwapBuffers();
}
//----------------------------------------------------------------------------
void SpWindow::drawString(const char* pcString, int iX, int iY, const SpColor4f& rkColor)
{
	unsigned int uiLen, i;
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);

	glRasterPos2f(iX, iY);
	glColor4f( rkColor.r(), rkColor.g(), rkColor.b(), rkColor.a() );
	uiLen = (unsigned int) strlen(pcString);
	for (i = 0; i < uiLen; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, pcString[i]);
	}
	glPopAttrib();
}
//----------------------------------------------------------------------------
void SpWindow::drawImage(
	const unsigned char* aucBuffer, unsigned int uiPosX, unsigned int uiPosY,
	unsigned int uiWidth, unsigned int uiHeight, bool bAlpha)
{
	if ( !aucBuffer )
		return;

	// disable everything that isnt needed for drawing the image
	GLboolean bDepthTest = glIsEnabled(GL_DEPTH_TEST);
	GLboolean bLighting = glIsEnabled(GL_LIGHTING);
	GLboolean bTexture2D = glIsEnabled(GL_TEXTURE_2D);
	if ( bDepthTest )
		glDisable(GL_DEPTH_TEST);
	if ( bLighting )
		glDisable(GL_LIGHTING);
	if ( bTexture2D )
		glDisable(GL_TEXTURE_2D);

	// clear out the model and projection matrices
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// create an ortho projection
	glOrtho(0.0,(double)m_iWidth,0.0,(double)m_iHeight,0.0,1.0);

	// set the raster position
	glRasterPos3f(uiPosX, uiPosY, 0.0f);

	// draw a blank image to correct for strange screen glitches
	GLubyte aucBitmap[1] = {0};
	glBitmap(0,0,0.0f,0.0f,0.0f,(float)m_iHeight,aucBitmap);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// flip the image to account for opengl's origin being at bottom left
	glPixelZoom(1.0f,-1.0f);

	// draw the image
	if(bAlpha)
		glDrawPixels((GLint)uiWidth,(GLint)uiHeight,GL_RGBA, GL_UNSIGNED_BYTE,
			(const GLvoid*)aucBuffer);
	else
		glDrawPixels((GLint)uiWidth,(GLint)uiHeight,GL_RGB, GL_UNSIGNED_BYTE,
			(const GLvoid*)aucBuffer);

	// reset the pixel zoom
	glPixelZoom(1.0f,1.0f);

	// reenable states
	if ( bDepthTest )
		glEnable(GL_DEPTH_TEST);
	if ( bLighting )
		glEnable(GL_LIGHTING);
	if ( bTexture2D )
		glEnable(GL_TEXTURE_2D);
}
//----------------------------------------------------------------------------
void SpWindow::drawImage(
	const float* afBuffer, unsigned int uiPosX, unsigned int uiPosY,
	unsigned int uiWidth, unsigned int uiHeight, bool bAlpha)
{
	if ( !afBuffer )
		return;

	// disable everything that isnt needed for drawing the image
	GLboolean bDepthTest = glIsEnabled(GL_DEPTH_TEST);
	GLboolean bLighting = glIsEnabled(GL_LIGHTING);
	GLboolean bTexture2D = glIsEnabled(GL_TEXTURE_2D);
	if ( bDepthTest )
		glDisable(GL_DEPTH_TEST);
	if ( bLighting )
		glDisable(GL_LIGHTING);
	if ( bTexture2D )
		glDisable(GL_TEXTURE_2D);

	// clear out the model and projection matrices
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// create an ortho projection
	glOrtho(0.0,(double)m_iWidth,0.0,(double)m_iHeight,0.0,1.0);

	// set the raster position
	glRasterPos3f(uiPosX, uiPosY, 0.0);

	// draw a blank bitmap to correct for strange screen glitches
	GLubyte aucBitmap[1] = {0};
	glBitmap(0,0,0.0f,0.0f,0.0f,(float)m_iHeight,aucBitmap);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// flip the image to account for opengl's origin being at bottom left
	glPixelZoom(1.0f,-1.0f);

	// draw the image
	if(bAlpha)
		glDrawPixels((GLint)uiWidth,(GLint)uiHeight,GL_RGBA, GL_FLOAT,
			(const GLvoid*)afBuffer);
	else
		glDrawPixels((GLint)uiWidth,(GLint)uiHeight,GL_RGB, GL_FLOAT,
			(const GLvoid*)afBuffer);

	// reset the pixel zoom
	glPixelZoom(1.0f,1.0f);

	// reenable states
	if ( bDepthTest )
		glEnable(GL_DEPTH_TEST);
	if ( bLighting )
		glEnable(GL_LIGHTING);
	if ( bTexture2D )
		glEnable(GL_TEXTURE_2D);
}
//----------------------------------------------------------------------------
int main (int argc, char** argv)
{
	SpWindow* pkWindow = SpWindow::current();
	assert( pkWindow );
	if ( !pkWindow )
		return -1;

	if ( atexit(Terminate) != 0 )
		return -2;

	glutInit(&argc, argv);

	if ( !pkWindow->onStartup() )
		return -3;

	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize( pkWindow->width(), pkWindow->height() );
	pkWindow->setWindowId( glutCreateWindow(pkWindow->title()) );
	glutSetWindow( pkWindow->id() );

	GLenum err = glewInit();
	if (GLEW_OK != err)
		fprintf(stderr, "OpenGL Extension Error: %s\n", glewGetErrorString(err));

	ReshapeCallback(pkWindow->width(), pkWindow->height());
	glutReshapeFunc(ReshapeCallback);
	glutDisplayFunc(DisplayCallback);
	glutIdleFunc(IdleCallback);
	//glutTimerFunc(60, UpdateCallback, 1);
	glutKeyboardFunc(KeyDownCallback);
	glutKeyboardUpFunc(KeyUpCallback);
	glutSpecialFunc(SpecialKeyDownCallback);
	glutSpecialUpFunc(SpecialKeyUpCallback);
	glutMouseFunc(MouseClickCallback);
	glutMotionFunc(MotionCallback);
	glutPassiveMotionFunc(PassiveMotionCallback);
	//pkWindow->onDisplay();

	if ( !pkWindow->onInitialize() )
		return -4;

	glutMainLoop();
	return 0;
}
//----------------------------------------------------------------------------

//#endif

