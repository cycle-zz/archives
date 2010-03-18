#include "SpGlHeaders.h"
#include "SpGpuProgram.h"
#include "SpGlslManager.h"
#include "SpGlslVertexProgram.h"
#include "SpGlslFragmentProgram.h"
#include "SpResourcePath.h"
#include "SpString.h"
#include <iostream>

//----------------------------------------------------------------------------

using namespace std;
using namespace Spark;

//----------------------------------------------------------------------------
SpResourcePath SpGlslManager::ms_kSpResourcePath;
SpGpuProgram* SpGlslManager::ms_apkCurrent[SpGpuProgram::GPU_PROGRAM_COUNT];
//----------------------------------------------------------------------------
SpGlslManager::~SpGlslManager()
{
	for( int i = 0; i < SpGpuProgram::GPU_PROGRAM_COUNT; i++)
	{
		if( ms_apkCurrent[i] != NULL )
		{
			SpGpuProgram* pkSpGpuProgram = ms_apkCurrent[i];
		release(pkSpGpuProgram);
			//ms_apkCurrent[i] = NULL;
		}
	}
}
//----------------------------------------------------------------------------
bool SpGlslManager::compile( SpGpuProgram* pkSpGpuProgram )
{
	if(!isSupported(pkSpGpuProgram))
		return false;

	GLenum eType = 0;

	if( pkSpGpuProgram->getType() == SpGpuProgram::GPU_GLSL_FRAGMENT_PROGRAM )
		eType = GL_FRAGMENT_SHADER_ARB;
	else
		eType = GL_VERTEX_SHADER_ARB;

	unsigned int uiHandle = 0;
	uiHandle = glCreateProgramObjectARB();

	GLhandleARB uiObject = glCreateShaderObjectARB(eType);
	GLint iLength = (GLint)pkSpGpuProgram->getLength();

	const GLcharARB* aakSource = pkSpGpuProgram->getSource();
	glShaderSourceARB(uiObject, 1, &aakSource, &iLength);

	// compile shader object
	glCompileShaderARB(uiObject);

	// Check for errors and warnings...
	GLint iCompiled = 0;
	glGetObjectParameterivARB(uiObject, GL_OBJECT_COMPILE_STATUS_ARB, &iCompiled);

	// Check for errors and warnings...
	if ( !iCompiled )
	{
		// Find the error position
		GLint iErrorPos;
		glGetIntegerv( GL_PROGRAM_ERROR_POSITION_ARB, &iErrorPos );

		// Print program errors and warnings string.
		fprintf( stderr, "GLSL Compile Error at Position: %d\n",
			iErrorPos );

		printInfoLog( uiObject );
		//fprintf( stderr, pkSpGpuProgram->getSource());
		return false;
	}

	// attach vertex shader to program object
	glAttachObjectARB(uiHandle, uiObject);

	// delete vertex object, no longer needed
	glDeleteObjectARB(uiObject);

	// attempt to link the program
	glLinkProgramARB(uiHandle);

	// get the link status
	GLint iLinkStatus = 0;
	glGetObjectParameterivARB(uiHandle, GL_OBJECT_LINK_STATUS_ARB, &iLinkStatus);

	// Check for errors and warnings...
	if (!iLinkStatus)
	{
		// Find the error position
		GLint iErrorPos;
		glGetIntegerv( GL_PROGRAM_ERROR_POSITION_ARB, &iErrorPos );

		// Print program errors and warnings string.
		const GLubyte *acErrorString;
		acErrorString = glGetString( GL_PROGRAM_ERROR_STRING_ARB );
		fprintf( stderr, "GLSL Linking Error at Position: %d\n%s\n",
			iErrorPos, acErrorString );

		printInfoLog( uiObject );
		//fprintf( stderr, pkSpGpuProgram->getSource());
		return false;
	}

	// assign the program handle to the program object
	pkSpGpuProgram->setUserData(&uiHandle, sizeof(GLuint));
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslManager::bind( SpGpuProgram* pkSpGpuProgram )
{
	GLuint uiUserData;

	// get the current id, if there is one
	pkSpGpuProgram->getUserData(&uiUserData, sizeof(GLuint));
	if ( !uiUserData )
	{
		// compile the shader to get a new id
		compile(pkSpGpuProgram);

		// get the updated id from the compile
		pkSpGpuProgram->getUserData(&uiUserData, sizeof(GLuint));
	}

	glUseProgramObjectARB(uiUserData);
	ms_apkCurrent[ pkSpGpuProgram->getType() ] = pkSpGpuProgram;
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslManager::enable( SpGpuProgram* pkSpGpuProgram )
{
	GLuint uiUserData;

	// get the current id, if there is one
	pkSpGpuProgram->getUserData(&uiUserData, sizeof(GLuint));
	if ( !uiUserData )
	{
		// compile the shader to get a new id
		compile(pkSpGpuProgram);

		// get the updated id from the compile
		pkSpGpuProgram->getUserData(&uiUserData, sizeof(GLuint));
	}

	glUseProgramObjectARB(uiUserData);
	ms_apkCurrent[ pkSpGpuProgram->getType() ] = pkSpGpuProgram;
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslManager::disable( SpGpuProgram* )
{
	glUseProgramObjectARB(0);
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslManager::release( SpGpuProgram* pkSpGpuProgram )
{
	GLuint uiUserData;
	pkSpGpuProgram->getUserData(&uiUserData, sizeof(GLuint));

	if ( uiUserData )
	{
	glDeleteProgramsARB(1,&uiUserData);
	uiUserData = 0;

	pkSpGpuProgram->setUserData(&uiUserData, sizeof(GLuint));
	}

	glUseProgramObjectARB(0);

	return true;
}
//----------------------------------------------------------------------------
bool SpGlslManager::isSupported(const SpGpuProgram* pkSpGpuProgram)
{
	static bool bFirstTime = true;
	static bool bSupported = true;

	if(bFirstTime)
	{
		if (GL_TRUE != glewGetExtension("GL_ARB_fragment_shader"))
		{
			fprintf(stderr, "GLSL ERROR: GL_ARB_fragment_shader extension is not available!\n");
			bSupported = false;
		}

		if (GL_TRUE != glewGetExtension("GL_ARB_vertex_shader"))
		{
			fprintf(stderr, "GLSL ERROR: GL_ARB_vertex_shader extension is not available!\n");
			bSupported = false;
		}

		if (GL_TRUE != glewGetExtension("GL_ARB_shader_objects"))
		{
			fprintf(stderr, "GLSL ERROR: GL_ARB_shader_objects extension is not available!\n");
			bSupported = false;
		}

		bFirstTime = false;
	}

	if( bSupported &&
		(pkSpGpuProgram->getType() == SpGpuProgram::GPU_GLSL_VERTEX_PROGRAM ||
	pkSpGpuProgram->getType() == SpGpuProgram::GPU_GLSL_FRAGMENT_PROGRAM ))
	return true;

	return false;
}
//----------------------------------------------------------------------------
SpGpuProgram* SpGlslManager::loadFromFile(const char* acFilename, SpGpuProgram::Type eType)
{
	if(eType == SpGpuProgram::GPU_GLSL_VERTEX_PROGRAM)
		return (SpGpuProgram*)loadVertexProgramFromFile(acFilename);

	if(eType == SpGpuProgram::GPU_GLSL_VERTEX_PROGRAM)
		return (SpGpuProgram*)loadFragmentProgramFromFile(acFilename);

	return NULL;
}
//----------------------------------------------------------------------------
SpGlslVertexProgram* SpGlslManager::loadVertexProgramFromFile(const char* acFilename)
{
	const char* acSource = SpGlslManager::searchpath().loadTextFile( acFilename );

	if(!acSource) return NULL;

	SpGlslVertexProgram* pkVP = new SpGlslVertexProgram(acSource);
	delete[] acSource;

	return pkVP;
}
//----------------------------------------------------------------------------
SpGlslFragmentProgram* SpGlslManager::loadFragmentProgramFromFile(const char* acFilename)
{
	const char* acSource = SpGlslManager::searchpath().loadTextFile( acFilename );

	if(!acSource) return NULL;

	SpGlslFragmentProgram* pkFP = new SpGlslFragmentProgram(acSource);
	delete[] acSource;

	return pkFP;
}
//----------------------------------------------------------------------------
SpResourcePath& SpGlslManager::searchpath()
{
	return ms_kSpResourcePath;
}
//----------------------------------------------------------------------------
void SpGlslManager::printInfoLog(unsigned int uiHandle)
{
	int iMaxLength = 0;
	glGetObjectParameterivARB(uiHandle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &iMaxLength);

	char *acInfoLog = new char[iMaxLength];
	glGetInfoLogARB(uiHandle, iMaxLength, &iMaxLength, acInfoLog);
	fprintf(stderr, "GLSL InfoLog: \n%s", acInfoLog);
	delete[] acInfoLog;
}
//----------------------------------------------------------------------------
void SpGlslManager::enableTexturePassThrough(bool bRectangle)
{
	static bool bLastRectangleOption = false;
	static bool bInitialized = false;
	static GLuint iTextureProgram = 0;

	static const char* acTextureRectProgram =
		"!!ARBfp1.0\n"
		"TEX result.color, fragment.texcoord[0], texture[0], RECT;\n"
		"END\n";

	static const char* acTexture2dProgram =
		"!!ARBfp1.0\n"
		"TEX result.color, fragment.texcoord[0], texture[0], 2D;\n"
		"END\n";

	if(!bInitialized || bLastRectangleOption != bRectangle)
	{
		glGenProgramsARB(1, &iTextureProgram);

		const char* acTextureProgram = 0;

		if(bRectangle)
			acTextureProgram = acTextureRectProgram;
		else
			acTextureProgram = acTexture2dProgram;

		glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, iTextureProgram);

		glProgramStringARB(
			GL_FRAGMENT_PROGRAM_ARB,
			GL_PROGRAM_FORMAT_ASCII_ARB,
			(GLsizei)strlen(acTextureProgram),
			acTextureProgram
		);

		bLastRectangleOption = bRectangle;
		bInitialized = true;
	}

	glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, iTextureProgram);
	glEnable(GL_FRAGMENT_PROGRAM_ARB);
	glActiveTexture(GL_TEXTURE0_ARB);
}
//----------------------------------------------------------------------------
void SpGlslManager::enableFragmentPassThrough()
{
	static bool bInitialized = false;
	static GLuint iPassThroughProgram = 0;

	static const char* acPassThroughProgram =
		"!!ARBfp1.0\n"
		"MOV result.color, fragment.color.primary;\n"
		"END\n";

	if(!bInitialized)
	{
		glGenProgramsARB(1, &iPassThroughProgram);

		glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, iPassThroughProgram);

		glProgramStringARB(
			GL_FRAGMENT_PROGRAM_ARB,
			GL_PROGRAM_FORMAT_ASCII_ARB,
			(GLsizei)strlen(acPassThroughProgram),
			acPassThroughProgram
		);

		bInitialized = true;
	}

	glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, iPassThroughProgram);
}
//----------------------------------------------------------------------------
void SpGlslManager::enableFragmentPrograms()
{
	glEnable(GL_FRAGMENT_PROGRAM_ARB);
}
//----------------------------------------------------------------------------
void SpGlslManager::enableVertexPrograms()
{
	glEnable(GL_VERTEX_PROGRAM_ARB);
}
//----------------------------------------------------------------------------
void SpGlslManager::disableFragmentPrograms()
{
	glDisable(GL_FRAGMENT_PROGRAM_ARB);
}
//----------------------------------------------------------------------------
void SpGlslManager::disableVertexPrograms()
{
	glDisable(GL_VERTEX_PROGRAM_ARB);
}
