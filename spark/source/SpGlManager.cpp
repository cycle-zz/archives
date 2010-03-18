#include "SpGlHeaders.h"
#include "SpGlManager.h"
#include <cstdio>

//----------------------------------------------------------------------------

using namespace Spark;

//----------------------------------------------------------------------------
void SpGlManager::deleteTexture( unsigned int uiTextureId )
{
	glDeleteTextures(1, &uiTextureId);
}
//----------------------------------------------------------------------------
unsigned int SpGlManager::createTexture(
	int iWidth, int iHeight,
	GLenum eTextureMode, GLenum eImageFormat,
	GLenum ePixelFormat, GLenum eComponentFormat,
	void* pvData)
{

    // generate a new texture id
	unsigned int uiTextureId;
    glGenTextures((GLsizei)1, &uiTextureId);

    // bind the texture
    glBindTexture(eTextureMode, uiTextureId);

	// create the texture
	glTexImage2D(
		eTextureMode, 0,
		eImageFormat,
		iWidth, iHeight, 0,
		ePixelFormat,
		eComponentFormat,
		pvData
	);

	return uiTextureId;
}
//----------------------------------------------------------------------------
unsigned int SpGlManager::createFilteredTexture(
	int iWidth, int iHeight,
	GLenum eTextureMode, GLenum eImageFormat,
	GLenum ePixelFormat, GLenum eComponentFormat,
	GLenum eMinFilterMode, GLenum eMagFilterMode,
	GLenum eSWrapMode, GLenum eTWrapMode,
	void* pvData)
{
	unsigned int uiTextureId;

	uiTextureId = createTexture(
		iWidth, iHeight,
		eTextureMode,
		eImageFormat,
		ePixelFormat,
		eComponentFormat,
		pvData
	);

    glTexParameteri(
		eTextureMode,
		GL_TEXTURE_MIN_FILTER,
		eMinFilterMode
	);

	glTexParameteri(
		eTextureMode,
		GL_TEXTURE_MAG_FILTER,
		eMagFilterMode
	);

    glTexParameteri(
		eTextureMode,
		GL_TEXTURE_WRAP_S,
		eSWrapMode
	);

	glTexParameteri(
		eTextureMode,
		GL_TEXTURE_WRAP_T,
		eTWrapMode
	);

	return uiTextureId;
}
//----------------------------------------------------------------------------
void SpGlManager::printOnError( char *acMsg )
{
    GLenum eErrorCode;
    const GLubyte *acErrorString;

    if ((eErrorCode = glGetError()) != GL_NO_ERROR)
    {
        acErrorString = gluErrorString(eErrorCode);
        fprintf(stderr,"OpenGL ERROR: %s: %s\n", acErrorString, acMsg);
    }
}
//----------------------------------------------------------------------------
