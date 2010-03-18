// #############################################################################
// # SpStreamBuffer.cpp : A multi-format OpenGL render-to-texture interface
// #
// # Created 	: Aug 2004
// # Copyright	: (see license below)
// #
// #############################################################################

// =============================================================================
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
// =============================================================================

// =============================================================================
//
// Copyright (c) 2002-2004 Mark J. Harris
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any
// damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any
// purpose, including commercial applications, and to alter it and
// redistribute it freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you
//    must not claim that you wrote the original software. If you use
//    this software in a product, an acknowledgment in the product
//    documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and
//    must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
// =============================================================================
// Credits:
//
// Original SpStreamBuffer code: Mark J. Harris
// Original Render-to-depth-texture support: Thorsten Scheuermann
// Additional Refactoring: Derek Gerstmann
// OSX Support: Derek Gerstmann
// Linux Copy-to-texture: Eric Werness
// Various Bug Fixes: Daniel (Redge) Sperl
//                    Bill Baxter
//
// =============================================================================

#include "SpStreamBuffer.h"
#include "SpGlHeaders.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#ifdef _WIN32
#pragma warning(disable:4786)
#pragma comment(lib, "gdi32.lib") // required for GetPixelFormat()
#endif

// ---------------------------------------------------------------------------

using namespace std;
using namespace Spark;

// ---------------------------------------------------------------------------
SpStreamBuffer::SpStreamBuffer(const char *acModeString)
:   m_iWidth(0),
	m_iHeight(0),
	m_bIsTexture(false),
	m_bIsDepthTexture(false),
	m_bHasARBDepthTexture(true),            // [Redge]
	m_eUpdateMode(RT_RENDER_TO_TEXTURE),
	m_bInitialized(false),
	m_iNumAuxBuffers(0),
	m_bIsBufferBound(false),
	m_iCurrentBoundBuffer(0),
	m_uiDepthBits(0),
	m_uiStencilBits(0),
	m_bIsFloat(false),
	m_bIsDoubleBuffered(false),
	m_bIsPowerOf2(true),
	m_bIsRectangle(false),
	m_bIsMipMapped(false),
	m_bShareObjects(false),
	m_bCopyContext(false),
#ifdef _WIN32
	m_hDC(NULL),
	m_hGLContext(NULL),
	m_hPixelBuffer(NULL),
	m_hPreviousDC(0),
	m_hPreviousContext(0),
#else
	m_pkDisplay(NULL),
	m_hGLContext(NULL),
	m_hPixelBuffer(0),
	m_hPreviousContext(0),
	m_hPreviousDrawable(0),
#endif
	m_eTextureTarget(GL_NONE),
	m_uiTextureId(0),
	m_uiDepthTextureId(0),
	m_ausPoorDepthTexture(0) // [Redge]
{
	if(acModeString)
		m_kModeString = SpString(acModeString); // [DG]

	m_uiColorBits[0] = m_uiColorBits[1] =
		m_uiColorBits[2] = m_uiColorBits[3] = 0;

#ifdef _WIN32
	m_kPixelFormatAttribs.push_back(WGL_DRAW_TO_PBUFFER_ARB);
	m_kPixelFormatAttribs.push_back(true);
	m_kPixelFormatAttribs.push_back(WGL_SUPPORT_OPENGL_ARB);
	m_kPixelFormatAttribs.push_back(true);

	m_kPixelBufferAttribs.push_back(WGL_PBUFFER_LARGEST_ARB);
	m_kPixelBufferAttribs.push_back(true);
#else
	m_kPixelBufferAttribs.push_back(GLX_RENDER_TYPE_SGIX);
	m_kPixelBufferAttribs.push_back(GLX_RGBA_BIT_SGIX);
	m_kPixelBufferAttribs.push_back(GLX_DRAWABLE_TYPE_SGIX);
	m_kPixelBufferAttribs.push_back(GLX_PBUFFER_BIT_SGIX);
#endif

	parseModeString(acModeString, m_kPixelFormatAttribs, m_kPixelBufferAttribs);

#ifdef _WIN32
	m_kPixelFormatAttribs.push_back(0);
	m_kPixelBufferAttribs.push_back(0);
#else
	m_kPixelFormatAttribs.push_back(None);
#endif
}
// ---------------------------------------------------------------------------
SpStreamBuffer::~SpStreamBuffer()
{
	invalidate();
}
// ---------------------------------------------------------------------------
#ifdef _WIN32
// ---------------------------------------------------------------------------
void wglGetLastError()
{
	//
	// Returns the last windows error generated.
	//

#ifdef _DEBUG

	DWORD iError = GetLastError();
	switch(iError)
	{
	case ERROR_INVALID_PIXEL_FORMAT:
		fprintf(stderr,
				"SpStreamBuffer Win32 Error:  ERROR_INVALID_PIXEL_FORMAT\n");
		break;
	case ERROR_NO_SYSTEM_RESOURCES:
		fprintf(stderr,
				"SpStreamBuffer Win32 Error:  ERROR_NO_SYSTEM_RESOURCES\n");
		break;
	case ERROR_INVALID_DATA:
		fprintf(stderr,
				"SpStreamBuffer Win32 Error:  ERROR_INVALID_DATA\n");
		break;
	case ERROR_INVALID_WINDOW_HANDLE:
		fprintf(stderr,
				"SpStreamBuffer Win32 Error:  ERROR_INVALID_WINDOW_HANDLE\n");
		break;
	case ERROR_RESOURCE_TYPE_NOT_FOUND:
		fprintf(stderr,
				"SpStreamBuffer Win32 Error:  ERROR_RESOURCE_TYPE_NOT_FOUND\n");
		break;
	case ERROR_SUCCESS:
		// no error
		break;
	default:
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			iError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL);

		fprintf(stderr, "SpStreamBuffer Win32 Error %d: %s\n", iError, lpMsgBuf);
		LocalFree( lpMsgBuf );
		break;
	}
	SetLastError(0);

#endif // _DEBUG
}
#endif
// ---------------------------------------------------------------------------
void PrintExtensionError( char* acMessage, ... )
{
	//
	// Prints an error about missing OpenGL extensions.
	//

	fprintf(stderr,
			"Error: SpStreamBuffer requires the following unsupported "
			"OpenGL extensions: \n");
	char acBuffer[512];
	va_list kArgs;
	va_start(kArgs, acMessage);
#ifdef _WIN32
	_vsnprintf( acBuffer, 512, acMessage, kArgs );
#else
	vsnprintf( acBuffer, 512, acMessage, kArgs );
#endif
	va_end(kArgs);

	fprintf(stderr, acMessage);
}
// ---------------------------------------------------------------------------
bool SpStreamBuffer::initialize(int iWidth, int iHeight,
								bool bShareObjects       /* = true */,
								bool bCopyContext        /* = false */)
{
	//
	// This function creates the actual buffer.  It can only be called once a GL
	// context has already been created.
	//

	assert(iWidth > 0 && iHeight > 0);

	m_iWidth = iWidth; m_iHeight = iHeight;
	m_bIsPowerOf2 = isPowerOfTwo(iWidth) && isPowerOfTwo(iHeight);

	m_bShareObjects = bShareObjects;
	m_bCopyContext  = bCopyContext;

	// Check if this is an NVXX GPU and verify necessary extensions.
	if (!verifyExtensions())
		return false;

	if (m_bInitialized)
		invalidate();

#if _WIN32
	// Get the current kContext.
	HDC hDC = wglGetCurrentDC();
	if (NULL == hDC)
		wglGetLastError();
	HGLRC hGLRC = wglGetCurrentContext();
	if (NULL == hGLRC)
		wglGetLastError();

	int iFormat = 0;
	unsigned int iNumFormats;

	if (m_bCopyContext)
	{
		// Get the pixel format for the on-iScreen window.
		iFormat = GetPixelFormat(hDC);
		if (iFormat == 0)
		{
			fprintf(stderr,
					"SpStreamBuffer Error: GetPixelFormat() failed.\n");
			return false;
		}
	}
	else
	{
		if (!wglChoosePixelFormatARB(hDC, &m_kPixelFormatAttribs[0], NULL,
									 1, &iFormat, &iNumFormats))
		{
			fprintf(stderr,
				"SpStreamBuffer Error: wglChoosePixelFormatARB() failed.\n");
			wglGetLastError();
			return false;
		}
		if ( iNumFormats <= 0 )
		{
			fprintf(stderr,
					"SpStreamBuffer Error: Couldn't find a suitable "
					"pixel format.\n");
			wglGetLastError();
			return false;
		}
	}

	// Create the p-buffer.
	m_hPixelBuffer = wglCreatePbufferARB(hDC, iFormat, m_iWidth, m_iHeight,
										 &m_kPixelBufferAttribs[0]);
	if (!m_hPixelBuffer)
	{
		fprintf(stderr,
				"SpStreamBuffer Error: wglCreatePbufferARB() failed.\n");
		wglGetLastError();
		return false;
	}

	// Get the device kContext.
	m_hDC = wglGetPbufferDCARB( m_hPixelBuffer);
	if ( !m_hDC )
	{
		fprintf(stderr,
				"SpStreamBuffer Error: wglGetGetPbufferDCARB() failed.\n");
		wglGetLastError();
		return false;
	}

	// Create a gl kContext for the p-buffer.
	if (m_bCopyContext)
	{
		// Let's use the same gl kContext..
		// Since the device kContexts are compatible (i.e. same pixelformat),
		// we should be able to use the same gl rendering kContext.
		m_hGLContext = hGLRC;
	}
	else
	{
		m_hGLContext = wglCreateContext( m_hDC );
		if ( !m_hGLContext )
		{
			fprintf(stderr,
					"SpStreamBuffer Error: wglCreateContext() failed.\n");
			wglGetLastError();
			return false;
		}
	}

	// Share lists, texture objects, and program objects.
	if( m_bShareObjects )
	{
		if( !wglShareLists(hGLRC, m_hGLContext) )
		{
			fprintf(stderr,
					"SpStreamBuffer Error: wglShareLists() failed.\n");
			wglGetLastError();
			return false;
		}
	}

	// Determine the actual iWidth and iHeight we were able to create.
	wglQueryPbufferARB( m_hPixelBuffer, WGL_PBUFFER_WIDTH_ARB, &m_iWidth );
	wglQueryPbufferARB( m_hPixelBuffer, WGL_PBUFFER_HEIGHT_ARB, &m_iHeight );

	m_bInitialized = true;

	// get the actual number of bits allocated:
	int iAttribute = WGL_RED_BITS_ARB;
	//int bits[6];
	int iValue;
	m_uiColorBits[0] =
		(wglGetPixelFormatAttribivARB(m_hDC, iFormat, 0, 1, &iAttribute, &iValue))
		? iValue : 0;
	iAttribute = WGL_GREEN_BITS_ARB;
	m_uiColorBits[1] =
		(wglGetPixelFormatAttribivARB(m_hDC, iFormat, 0, 1, &iAttribute, &iValue))
		? iValue : 0;
	iAttribute = WGL_BLUE_BITS_ARB;
	m_uiColorBits[2] =
		(wglGetPixelFormatAttribivARB(m_hDC, iFormat, 0, 1, &iAttribute, &iValue))
		? iValue : 0;
	iAttribute = WGL_ALPHA_BITS_ARB;
	m_uiColorBits[3] =
		(wglGetPixelFormatAttribivARB(m_hDC, iFormat, 0, 1, &iAttribute, &iValue))
		? iValue : 0;
	iAttribute = WGL_DEPTH_BITS_ARB;
	m_uiDepthBits =
		(wglGetPixelFormatAttribivARB(m_hDC, iFormat, 0, 1, &iAttribute, &iValue))
		? iValue : 0;
	iAttribute = WGL_STENCIL_BITS_ARB;
	m_uiStencilBits =
		(wglGetPixelFormatAttribivARB(m_hDC, iFormat, 0, 1, &iAttribute, &iValue))
		? iValue : 0;
	iAttribute = WGL_DOUBLE_BUFFER_ARB;
	m_bIsDoubleBuffered =
		(wglGetPixelFormatAttribivARB(m_hDC, iFormat, 0, 1, &iAttribute, &iValue))
		? (iValue?true:false) : false;

#if defined(_DEBUG) | defined(DEBUG)
	fprintf(stderr, "Created a %dx%d SpStreamBuffer with BPP(%d, %d, %d, %d)",
		m_iWidth, m_iHeight,
		m_uiColorBits[0], m_uiColorBits[1],
		m_uiColorBits[2], m_uiColorBits[3]);
	if (m_uiDepthBits) fprintf(stderr, " depth=%d", m_uiDepthBits);
	if (m_uiStencilBits) fprintf(stderr, " stencil=%d", m_uiStencilBits);
	if (m_bIsDoubleBuffered) fprintf(stderr, " double buffered");
	fprintf(stderr, "\n");
#endif

#else // !_WIN32
	m_pkDisplay = glXGetCurrentDisplay();
	GLXContext kContext = glXGetCurrentContext();
	int iScreen = DefaultScreen(m_pkDisplay);
	XVisualInfo *pkVisualInfo;

	int iFormat; iFormat = 0;
	int iNumFormats; iNumFormats = 0;
	int iAttribute; iAttribute = 0;

	GLXFBConfigSGIX *pkFBConfigs;
	int iConfigs;

	pkFBConfigs = glXChooseFBConfigSGIX(m_pkDisplay, iScreen,
									  &m_kPixelFormatAttribs[0], &iConfigs);

	if (iConfigs == 0 || !pkFBConfigs)
	{
		fprintf(stderr,
			"SpStreamBuffer Error: Couldn't find a suitable pixel format.\n");
		return false;
	}

	// Pick the first returned format that will return a pbuffer
	for (int i=0;i<iConfigs;i++)
	{
		m_hPixelBuffer = glXCreateGLXPbufferSGIX(m_pkDisplay, pkFBConfigs[i],
											m_iWidth, m_iHeight, NULL);
		if (m_hPixelBuffer)
		{
			m_hGLContext = glXCreateContextWithConfigSGIX(m_pkDisplay,
														 pkFBConfigs[i],
														 GLX_RGBA_TYPE,
														 m_bShareObjects ? kContext : NULL,
														 True);
			break;
		}
	}

	if (!m_hPixelBuffer)
	{
		fprintf(stderr,
				"SpStreamBuffer Error: glXCreateGLXPbufferSGIX() failed.\n");
		return false;
	}

	if(!m_hGLContext)
	{
		// Try indirect
		m_hGLContext = glXCreateContext(m_pkDisplay, pkVisualInfo,
									   m_bShareObjects ? kContext : NULL, False);
		if ( !m_hGLContext )
		{
			fprintf(stderr,
					"SpStreamBuffer Error: glXCreateContext() failed.\n");
			return false;
		}
	}

	glXQueryGLXPbufferSGIX(m_pkDisplay, m_hPixelBuffer, GLX_WIDTH_SGIX,
						   (GLuint*)&m_iWidth);
	glXQueryGLXPbufferSGIX(m_pkDisplay, m_hPixelBuffer, GLX_HEIGHT_SGIX,
						   (GLuint*)&m_iHeight);

	m_bInitialized = true;

	// XXX Query the color format

#endif


	// Now that the pbuffer is created, allocate any texture objects needed,
	// and initialize them (for CTT updates only).  These must be allocated
	// in the kContext of the pbuffer, though, or the RT won't work without
	// wglShareLists.
#ifdef _WIN32
	if (false == wglMakeCurrent( m_hDC, m_hGLContext))
	{
		wglGetLastError();
		return false;
	}
#else
	m_hPreviousContext = glXGetCurrentContext();
	m_hPreviousDrawable = glXGetCurrentDrawable();

	if (False == glXMakeCurrent(m_pkDisplay, m_hPixelBuffer, m_hGLContext))
	{
		return false;
	}
#endif

	bool result = initializeTextures();
#ifdef _WIN32
	bindBuffer(WGL_FRONT_LEFT_ARB);
	bindDepthBuffer();
#endif


#ifdef _WIN32
	// make the previous rendering context current
	if (false == wglMakeCurrent( hDC, hGLRC))
	{
		wglGetLastError();
		return false;
	}
#else
	if (False == glXMakeCurrent(m_pkDisplay,
								m_hPreviousDrawable, m_hPreviousContext))
	{
		return false;
	}
#endif

	return result;
}
// ---------------------------------------------------------------------------
bool SpStreamBuffer::invalidate()
{
	// Returns the buffer memory to the graphics device.

	m_uiColorBits[0] = m_uiColorBits[1] =
		m_uiColorBits[2] = m_uiColorBits[3] = 0;
	m_uiDepthBits = 0;
	m_uiStencilBits = 0;

	if (m_bIsTexture)
		glDeleteTextures(1, &m_uiTextureId);
	if (m_bIsDepthTexture)
	{
		// [Redge]
		if (!m_bHasARBDepthTexture)
			delete[] m_ausPoorDepthTexture;

		// [/Redge]
		glDeleteTextures(1, &m_uiDepthTextureId);
	}

#if _WIN32
	if ( m_hPixelBuffer )
	{
		// Check if we are currently rendering in the pbuffer
		if (wglGetCurrentContext() == m_hGLContext)
			wglMakeCurrent(0,0);

		if (!m_bCopyContext)
			wglDeleteContext( m_hGLContext);

		wglReleasePbufferDCARB( m_hPixelBuffer, m_hDC);
		wglDestroyPbufferARB( m_hPixelBuffer );
		m_hPixelBuffer = 0;
		return true;
	}
#else
	if ( m_hPixelBuffer )
	{
		if(glXGetCurrentContext() == m_hGLContext)
			// XXX I don't know if this is right at all
			glXMakeCurrent(m_pkDisplay, m_hPixelBuffer, 0);

		glXDestroyGLXPbufferSGIX(m_pkDisplay, m_hPixelBuffer);
		m_hPixelBuffer = 0;
		return true;
	}
#endif

	// [WVB] do we need to call releaseBoundBuffers() too?
	return false;
}
// ---------------------------------------------------------------------------
bool SpStreamBuffer::reset(const char *acModeString, ...)
{
	//
	// Causes the buffer to delete itself.  User must call initialize() again
	// before use.
	//

	m_iWidth = 0; m_iHeight = 0;
	m_bIsTexture = false;
	m_bIsDepthTexture = false,
	m_bHasARBDepthTexture = true;
	m_eUpdateMode = RT_RENDER_TO_TEXTURE;
	m_bInitialized = false;
	m_iNumAuxBuffers = 0;
	m_bIsBufferBound = false;
	m_iCurrentBoundBuffer = 0;
	m_uiDepthBits = 0;
	m_uiStencilBits = 0;
	m_bIsDoubleBuffered = false;
	m_bIsFloat = false;
	m_bIsPowerOf2 = true;
	m_bIsRectangle = false;
	m_bIsMipMapped = false;
	m_bShareObjects = false;
	m_bCopyContext = false;
	m_eTextureTarget = GL_NONE;
	m_uiTextureId = 0;
	m_uiDepthTextureId = 0;
	m_ausPoorDepthTexture = 0;
	m_kPixelFormatAttribs.clear();
	m_kPixelBufferAttribs.clear();

	if (isInitialized() && !invalidate())
	{
		fprintf(stderr, "SpStreamBuffer::reset(): failed to invalidate.\n");
		return false;
	}

	m_uiColorBits[0] = m_uiColorBits[1] =
		m_uiColorBits[2] = m_uiColorBits[3] = 0;

#ifdef _WIN32
	m_kPixelFormatAttribs.push_back(WGL_DRAW_TO_PBUFFER_ARB);
	m_kPixelFormatAttribs.push_back(true);
	m_kPixelFormatAttribs.push_back(WGL_SUPPORT_OPENGL_ARB);
	m_kPixelFormatAttribs.push_back(true);

	m_kPixelBufferAttribs.push_back(WGL_PBUFFER_LARGEST_ARB);
	m_kPixelBufferAttribs.push_back(true);
#else
	m_kPixelBufferAttribs.push_back(GLX_RENDER_TYPE_SGIX);
	m_kPixelBufferAttribs.push_back(GLX_RGBA_BIT_SGIX);
	m_kPixelBufferAttribs.push_back(GLX_DRAWABLE_TYPE_SGIX);
	m_kPixelBufferAttribs.push_back(GLX_PBUFFER_BIT_SGIX);
#endif

	va_list kArgs;
	char acStringBuffer[256];
	va_start(kArgs,acModeString);
#ifdef _WIN32
	_vsnprintf( acStringBuffer, 256, acModeString, kArgs );
#else
	vsnprintf( acStringBuffer, 256, acModeString, kArgs );
#endif
	va_end(kArgs);

	parseModeString(acStringBuffer, m_kPixelFormatAttribs, m_kPixelBufferAttribs);

#ifdef _WIN32
	m_kPixelFormatAttribs.push_back(0);
	m_kPixelBufferAttribs.push_back(0);
#else
	m_kPixelFormatAttribs.push_back(None);
#endif
	return true;
}
// ---------------------------------------------------------------------------
bool SpStreamBuffer::resize(int iWidth, int iHeight)
{
	//
	// Like reset() this causes the buffer to delete itself.
	// But unlike reset(), this call re-initializes the SpStreamBuffer.
	// Note that resize() will not work after calling reset(), or before
	// calling initialize() the first time.
	//

	if (!m_bInitialized)
	{
		fprintf(stderr, "SpStreamBuffer::resize(): must initialize() first.\n");
		return false;
	}
	if (iWidth == m_iWidth && iHeight == m_iHeight) {
		return true;
	}

	// Do same basic work as _Invalidate, but don't reset all our flags
	if (m_bIsTexture)
		glDeleteTextures(1, &m_uiTextureId);
	if (m_bIsDepthTexture)
		glDeleteTextures(1, &m_uiDepthTextureId);
#ifdef _WIN32
	if ( m_hPixelBuffer )
	{
		// Check if we are currently rendering in the pbuffer
		if (wglGetCurrentContext() == m_hGLContext)
			wglMakeCurrent(0,0);
		if (!m_bCopyContext)
			wglDeleteContext( m_hGLContext);
		wglReleasePbufferDCARB( m_hPixelBuffer, m_hDC);
		wglDestroyPbufferARB( m_hPixelBuffer );
		m_hPixelBuffer = 0;
		return true;
	}
#else
	if ( m_hPixelBuffer )
	{
		if(glXGetCurrentContext() == m_hGLContext)
			// XXX I don't know if this is right at all
			glXMakeCurrent(m_pkDisplay, m_hPixelBuffer, 0);
		glXDestroyGLXPbufferSGIX(m_pkDisplay, m_hPixelBuffer);
		m_hPixelBuffer = 0;
	}
#endif
	else {
		fprintf(stderr, "SpStreamBuffer::resize(): failed to resize.\n");
		return false;
	}
	m_bInitialized = false;
	return initialize(iWidth, iHeight, m_bShareObjects, m_bCopyContext);
}
// ---------------------------------------------------------------------------
bool SpStreamBuffer::enable()
{
	// Activates rendering to the SpStreamBuffer.

	if (!m_bInitialized)
	{
		fprintf(stderr,
				"SpStreamBuffer::enable(): Texture is not initialized!\n");
		return false;
	}
#ifdef _WIN32
	// cache the current context so we can reset it when disable() is called.
	m_hPreviousDC      = wglGetCurrentDC();
	if (NULL == m_hPreviousDC)
		wglGetLastError();
	m_hPreviousContext = wglGetCurrentContext();
	if (NULL == m_hPreviousContext)
		wglGetLastError();
#else
	m_hPreviousContext = glXGetCurrentContext();
	m_hPreviousDrawable = glXGetCurrentDrawable();
#endif

	releaseBoundBuffers();

	return makeCurrent();
}
// ---------------------------------------------------------------------------
bool SpStreamBuffer::disable()
{
	// Ends rendering to the SpStreamBuffer.

	if (!m_bInitialized)
	{
		fprintf(stderr,
				"SpStreamBuffer::disable() : Texture is not initialized!\n");
		return false;
	}

	captureBuffer();

#ifdef _WIN32
	// make the previous rendering context current
	if (FALSE == wglMakeCurrent( m_hPreviousDC, m_hPreviousContext))
	{
		wglGetLastError();
		return false;
	}
#else
	if (False == glXMakeCurrent(m_pkDisplay, m_hPreviousDrawable,
								m_hPreviousContext))
	{
		return false;
	}
#endif

	// rebind the textures to a buffers for RTT
	bindBuffer(m_iCurrentBoundBuffer);
	bindDepthBuffer();

	return true;
}
// ---------------------------------------------------------------------------
bool SpStreamBuffer::enable(SpStreamBuffer* pkCurrent)
{
	//
	// When performing a series of operations where you modify one texture after
	// another, it is more efficient to use this method instead of the equivalent
	// 'EndCapture'/'BeginCapture' pair.  This method switches directly to the
	// new context rather than changing to the default context, and then to the
	// new context.
	//
	// SpStreamBuffer doesn't have any mechanism for determining if
	// 'current' really is currently active, so no error will be thrown
	// if it is not.
	//

	bool bContextReset;
	bContextReset = false;

	if (pkCurrent == this) {
		return true; // no switch necessary
	}
	if (!pkCurrent) {
		// treat as normal Begin if pkCurrent is 0.
		return enable();
	}
	if (!m_bInitialized)
	{
		fprintf(stderr,
			"SpStreamBuffer::enable(SpStreamBuffer*): Texture is not initialized!\n");
		return false;
	}
	if (!pkCurrent->m_bInitialized)
	{
		fprintf(stderr,
			"SpStreamBuffer::enable(SpStreamBuffer): 'Current' texture is not initialized!\n");
		return false;
	}

	// Sync pkCurrent pbuffer with its CTT texture if necessary
	pkCurrent->captureBuffer();

	// pass along the previous context so we can reset it when
	// disable() is called.
#ifdef _WIN32
	m_hPreviousDC      = pkCurrent->m_hPreviousDC;
	if (NULL == m_hPreviousDC)
		wglGetLastError();
	m_hPreviousContext = pkCurrent->m_hPreviousContext;
	if (NULL == m_hPreviousContext)
		wglGetLastError();
#else
	m_hPreviousContext = pkCurrent->m_hPreviousContext;
	m_hPreviousDrawable = pkCurrent->m_hPreviousDrawable;
#endif

	// Unbind textures before making context pkCurrent
	if (!releaseBoundBuffers())
	  return false;

	// Make the pbuffer context pkCurrent
	if (!makeCurrent())
		return false;

	// Rebind buffers of initial SpStreamBuffer
	pkCurrent->bindBuffer(m_iCurrentBoundBuffer);
	pkCurrent->bindDepthBuffer();

	return true;
}
// ---------------------------------------------------------------------------
void SpStreamBuffer::bind() const
{
	// Binds RGB texture.

	if (m_bInitialized && m_bIsTexture)
	{
		glBindTexture(m_eTextureTarget, m_uiTextureId);
	}
}
// ---------------------------------------------------------------------------
void SpStreamBuffer::bindDepth() const
{
	// Binds depth texture.

	if (m_bInitialized && m_bIsDepthTexture)
	{
		glBindTexture(m_eTextureTarget, m_uiDepthTextureId);
	}
}
// ---------------------------------------------------------------------------
bool SpStreamBuffer::bindBuffer( int iBuffer )
{
	// Associate the RTT texture id with 'iBuffer' (e.g. WGL_FRONT_LEFT_ARB)

	// Must bind the texture too
	if (m_bInitialized && m_bIsTexture)
	{
		glBindTexture(m_eTextureTarget, m_uiTextureId);

#if _WIN32
		if (RT_RENDER_TO_TEXTURE == m_eUpdateMode && m_bIsTexture &&
			(!m_bIsBufferBound || m_iCurrentBoundBuffer != iBuffer))
		{
			if (FALSE == wglBindTexImageARB(m_hPixelBuffer, iBuffer))
			{
				//  WVB: WGL API considers binding twice to the same buffer
				//  to be an error.  But we don't want to
				//wglGetLastError();
				//return false;
				SetLastError(0);
			}
			m_bIsBufferBound = true;
			m_iCurrentBoundBuffer = iBuffer;
		}
#endif
		iBuffer = 0;
	}
	return true;
}
// ---------------------------------------------------------------------------
bool SpStreamBuffer::bindDepthBuffer() const
{
	// Associate the RTT depth texture id with the depth buffer

#ifdef WIN32
	if (m_bInitialized && m_bIsDepthTexture &&
		RT_RENDER_TO_TEXTURE == m_eUpdateMode)
	{
		glBindTexture(m_eTextureTarget, m_uiDepthTextureId);
		if (FALSE == wglBindTexImageARB(m_hPixelBuffer, WGL_DEPTH_COMPONENT_NV))
		{
			wglGetLastError();
			return false;
		}
	}
#endif
	return true;
}
// ---------------------------------------------------------------------------
void SpStreamBuffer::parseModeString(
	const char *acModeString,
#ifdef _WIN32
	vector<int>	&rkPixelFormatAttribs,
	vector<int> &rkPixelBufferAttribs
#else
	vector<int>	&rkPixelFormatAttribs,
	vector<int>	&
#endif
	)
{
	// Parses the user-specified mode SpString for SpStreamBuffer parameters.

	if (!acModeString || strcmp(acModeString, "") == 0)
		return;

	m_uiComponents = 0;
	m_eUpdateMode = RT_RENDER_TO_TEXTURE;

	int  iDepthBits = 0;
	bool bHasStencil = false;
	bool bBind2D   = false;
	bool bBindRECT = false;
	bool bBindCUBE = false;

	char *acMode = strdup(acModeString);


	vector<SpString> kTokens;
	char *acBuffer = strtok(acMode, " ");
	while (acBuffer != NULL)
	{
		kTokens.push_back(acBuffer);
		acBuffer = strtok(NULL, " ");
	}

	for (unsigned int i = 0; i < kTokens.size(); i++)
	{
		SpString kToken = kTokens[i];

		KeyVal kKeyValuePair = getKeyValuePair(kToken);


		if (kKeyValuePair.first == "rgb" && (m_uiComponents <= 1))
		{
			if (kKeyValuePair.second.find("f") != kKeyValuePair.second.npos)
				m_bIsFloat = true;

			vector<int> kBitVector = parseBitVector(kKeyValuePair.second);

			if (kBitVector.size() < 3) // expand the scalar to a vector
			{
				kBitVector.push_back(kBitVector[0]);
				kBitVector.push_back(kBitVector[0]);
			}

#ifdef _WIN32
			rkPixelFormatAttribs.push_back(WGL_RED_BITS_ARB);
			rkPixelFormatAttribs.push_back(kBitVector[0]);
			rkPixelFormatAttribs.push_back(WGL_GREEN_BITS_ARB);
			rkPixelFormatAttribs.push_back(kBitVector[1]);
			rkPixelFormatAttribs.push_back(WGL_BLUE_BITS_ARB);
			rkPixelFormatAttribs.push_back(kBitVector[2]);
#else
			rkPixelFormatAttribs.push_back(GLX_RED_SIZE);
			rkPixelFormatAttribs.push_back(kBitVector[0]);
			rkPixelFormatAttribs.push_back(GLX_GREEN_SIZE);
			rkPixelFormatAttribs.push_back(kBitVector[1]);
			rkPixelFormatAttribs.push_back(GLX_BLUE_SIZE);
			rkPixelFormatAttribs.push_back(kBitVector[2]);
#endif
			m_uiComponents += 3;
			continue;
		}
		else if (kKeyValuePair.first == "rgb")
			fprintf(stderr,
					"SpStreamBuffer Warning: mistake in components definition "
					"(rgb + %d).\n",
					m_uiComponents);


		if (kKeyValuePair.first == "rgba" && (m_uiComponents == 0))
		{
			if (kKeyValuePair.second.find("f") != kKeyValuePair.second.npos)
				m_bIsFloat = true;

			vector<int> kBitVector = parseBitVector(kKeyValuePair.second);

			if (kBitVector.size() < 4) // expand the scalar to a vector
			{
				kBitVector.push_back(kBitVector[0]);
				kBitVector.push_back(kBitVector[0]);
				kBitVector.push_back(kBitVector[0]);
			}

#ifdef _WIN32
			rkPixelFormatAttribs.push_back(WGL_RED_BITS_ARB);
			rkPixelFormatAttribs.push_back(kBitVector[0]);
			rkPixelFormatAttribs.push_back(WGL_GREEN_BITS_ARB);
			rkPixelFormatAttribs.push_back(kBitVector[1]);
			rkPixelFormatAttribs.push_back(WGL_BLUE_BITS_ARB);
			rkPixelFormatAttribs.push_back(kBitVector[2]);
			rkPixelFormatAttribs.push_back(WGL_ALPHA_BITS_ARB);
			rkPixelFormatAttribs.push_back(kBitVector[3]);
#else
			rkPixelFormatAttribs.push_back(GLX_RED_SIZE);
			rkPixelFormatAttribs.push_back(kBitVector[0]);
			rkPixelFormatAttribs.push_back(GLX_GREEN_SIZE);
			rkPixelFormatAttribs.push_back(kBitVector[1]);
			rkPixelFormatAttribs.push_back(GLX_BLUE_SIZE);
			rkPixelFormatAttribs.push_back(kBitVector[2]);
			rkPixelFormatAttribs.push_back(GLX_ALPHA_SIZE);
			rkPixelFormatAttribs.push_back(kBitVector[3]);
#endif
			m_uiComponents = 4;
			continue;
		}
		else if (kKeyValuePair.first == "rgba")
			fprintf(stderr,
					"SpStreamBuffer Warning: mistake in components definition "
					"(rgba + %d).\n",
					m_uiComponents);

		if (kKeyValuePair.first == "r" && (m_uiComponents <= 1))
		{
			if (kKeyValuePair.second.find("f") != kKeyValuePair.second.npos)
				m_bIsFloat = true;

			vector<int> kBitVector = parseBitVector(kKeyValuePair.second);

#ifdef _WIN32
			rkPixelFormatAttribs.push_back(WGL_RED_BITS_ARB);
			rkPixelFormatAttribs.push_back(kBitVector[0]);
#else
			rkPixelFormatAttribs.push_back(GLX_RED_SIZE);
			rkPixelFormatAttribs.push_back(kBitVector[0]);
#endif
			m_uiComponents++;
			continue;
		}
		else if (kKeyValuePair.first == "r")
			fprintf(stderr,
					"SpStreamBuffer Warning: mistake in components definition "
					"(r + %d).\n",
					m_uiComponents);

		if (kKeyValuePair.first == "rg" && (m_uiComponents <= 1))
		{
			if (kKeyValuePair.second.find("f") != kKeyValuePair.second.npos)
				m_bIsFloat = true;

			vector<int> kBitVector = parseBitVector(kKeyValuePair.second);

			if (kBitVector.size() < 2) // expand the scalar to a vector
			{
				kBitVector.push_back(kBitVector[0]);
			}

#ifdef _WIN32
			rkPixelFormatAttribs.push_back(WGL_RED_BITS_ARB);
			rkPixelFormatAttribs.push_back(kBitVector[0]);
			rkPixelFormatAttribs.push_back(WGL_GREEN_BITS_ARB);
			rkPixelFormatAttribs.push_back(kBitVector[1]);
#else
			rkPixelFormatAttribs.push_back(GLX_RED_SIZE);
			rkPixelFormatAttribs.push_back(kBitVector[0]);
			rkPixelFormatAttribs.push_back(GLX_GREEN_SIZE);
			rkPixelFormatAttribs.push_back(kBitVector[1]);
#endif
			m_uiComponents += 2;
			continue;
		}
		else if (kKeyValuePair.first == "rg")
			fprintf(stderr,
					"SpStreamBuffer Warning: mistake in components definition "
					"(rg + %d).\n",
					m_uiComponents);

		if (kKeyValuePair.first == "depth")
		{
			if (kKeyValuePair.second == "")
				iDepthBits = 24;
			else
				iDepthBits = strtol(kKeyValuePair.second.c_str(), 0, 10);
			continue;
		}

		if (kKeyValuePair.first == "stencil")
		{
			bHasStencil = true;
#ifdef _WIN32
			rkPixelFormatAttribs.push_back(WGL_STENCIL_BITS_ARB);
#else
			rkPixelFormatAttribs.push_back(GLX_STENCIL_SIZE);
#endif
			if (kKeyValuePair.second == "")
				rkPixelFormatAttribs.push_back(8);
			else
				rkPixelFormatAttribs.push_back(strtol(kKeyValuePair.second.c_str(), 0, 10));
			continue;
		}

		if (kKeyValuePair.first == "samples")
		{
#ifdef _WIN32
			rkPixelFormatAttribs.push_back(WGL_SAMPLE_BUFFERS_ARB);
			rkPixelFormatAttribs.push_back(1);
			rkPixelFormatAttribs.push_back(WGL_SAMPLES_ARB);
			rkPixelFormatAttribs.push_back(strtol(kKeyValuePair.second.c_str(), 0, 10));
#endif
			continue;

		}

		if (kKeyValuePair.first == "doubleacBufferfer" || kKeyValuePair.first == "double")
		{
#ifdef _WIN32
			rkPixelFormatAttribs.push_back(WGL_DOUBLE_BUFFER_ARB);
			rkPixelFormatAttribs.push_back(true);
#else
			rkPixelFormatAttribs.push_back(GLX_DOUBLEBUFFER);
			rkPixelFormatAttribs.push_back(True);
#endif
			continue;
		}

		if (kKeyValuePair.first == "aux")
		{
#ifdef _WIN32
			rkPixelFormatAttribs.push_back(WGL_AUX_BUFFERS_ARB);
#else
			rkPixelFormatAttribs.push_back(GLX_AUX_BUFFERS);
#endif
			if (kKeyValuePair.second == "")
				rkPixelFormatAttribs.push_back(0);
			else
				rkPixelFormatAttribs.push_back(strtol(kKeyValuePair.second.c_str(), 0, 10));
			continue;
		}

		if (kToken.find("tex") == 0)
		{
			m_bIsTexture = true;

			if ((kKeyValuePair.first == "texRECT") && GLEW_NV_texture_rectangle)
			{
				m_bIsRectangle = true;
				bBindRECT = true;
			}
			else if (kKeyValuePair.first == "texCUBE")
			{
				bBindCUBE = true;
			}
			else
			{
				bBind2D = true;
			}

			continue;
		}

		if (kToken.find("depthTex") == 0)
		{
			m_bIsDepthTexture = true;

			if ((kKeyValuePair.first == "depthTexRECT") && GLEW_NV_texture_rectangle)
			{
				m_bIsRectangle = true;
				bBindRECT = true;
			}
			else if (kKeyValuePair.first == "depthTexCUBE")
			{
				bBindCUBE = true;
			}
			else
			{
				bBind2D = true;
			}

			continue;
		}

		if (kKeyValuePair.first == "mipmap")
		{
			m_bIsMipMapped = true;
			continue;
		}

		if (kKeyValuePair.first == "rtt")
		{
			m_eUpdateMode = RT_RENDER_TO_TEXTURE;
			continue;
		}

		if (kKeyValuePair.first == "ctt")
		{
			m_eUpdateMode = RT_COPY_TO_TEXTURE;
			continue;
		}

		fprintf(stderr,
				"SpStreamBuffer Error: Unknown pacBufferfer attribute: %s\n",
				kToken.c_str());
	}

	// Processing of some options must be last because of interactions.

	// Check for inconsistent texture targets
	if (m_bIsTexture && m_bIsDepthTexture && !(bBind2D ^ bBindRECT ^ bBindCUBE))
	{
		fprintf(stderr,
				"SpStreamBuffer Warning: Depth and Color texture targets "
				"should match.\n");
	}

	// Apply default bit format if none specified
#ifdef _WIN32
	if (0 == m_uiComponents)
	{
		rkPixelFormatAttribs.push_back(WGL_RED_BITS_ARB);
		rkPixelFormatAttribs.push_back(8);
		rkPixelFormatAttribs.push_back(WGL_GREEN_BITS_ARB);
		rkPixelFormatAttribs.push_back(8);
		rkPixelFormatAttribs.push_back(WGL_BLUE_BITS_ARB);
		rkPixelFormatAttribs.push_back(8);
		rkPixelFormatAttribs.push_back(WGL_ALPHA_BITS_ARB);
		rkPixelFormatAttribs.push_back(8);
		m_uiComponents = 4;
	}
#endif

	// Depth bits
	if (m_bIsDepthTexture && !iDepthBits)
		iDepthBits = 24;

#ifdef _WIN32
	rkPixelFormatAttribs.push_back(WGL_DEPTH_BITS_ARB);
#else
	rkPixelFormatAttribs.push_back(GLX_DEPTH_SIZE);
#endif
	rkPixelFormatAttribs.push_back(iDepthBits); // default

	if (!bHasStencil)
	{
#ifdef _WIN32
		rkPixelFormatAttribs.push_back(WGL_STENCIL_BITS_ARB);
		rkPixelFormatAttribs.push_back(0);
#else
		rkPixelFormatAttribs.push_back(GLX_STENCIL_SIZE);
		rkPixelFormatAttribs.push_back(0);
#endif

	}
	if (m_uiComponents < 4)
	{
		// Can't do this right now -- on NVIDIA drivers, currently get
		// a non-functioning pacBufferfer if ALPHA_BITS=0 and
		// WGL_BIND_TO_TEXTURE_RGB_ARB=true

		//rkPixelFormatAttribs.push_back(WGL_ALPHA_BITS_ARB);
		//rkPixelFormatAttribs.push_back(0);
	}

#ifdef _WIN32
	if (!WGLEW_NV_render_depth_texture && m_bIsDepthTexture && (RT_RENDER_TO_TEXTURE == m_eUpdateMode))
	{
#if defined(DEBUG) || defined(_DEBUG)
		fprintf(stderr, "SpStreamBuffer Warning: No support found for "
				"render to depth texture.\n");
#endif
#endif
		m_bIsDepthTexture = false;
#ifdef _WIN32
	}
#endif

	if ((m_bIsTexture || m_bIsDepthTexture) &&
		(RT_RENDER_TO_TEXTURE == m_eUpdateMode))
	{
#ifdef _WIN32
		if (bBindRECT)
		{
			rkPixelBufferAttribs.push_back(WGL_TEXTURE_TARGET_ARB);
			rkPixelBufferAttribs.push_back(WGL_TEXTURE_RECTANGLE_NV);
		}
		else if (bBindCUBE)
		{
			rkPixelBufferAttribs.push_back(WGL_TEXTURE_TARGET_ARB);
			rkPixelBufferAttribs.push_back(WGL_TEXTURE_CUBE_MAP_ARB);
		}
		else if (bBind2D)
		{
			rkPixelBufferAttribs.push_back(WGL_TEXTURE_TARGET_ARB);
			rkPixelBufferAttribs.push_back(WGL_TEXTURE_2D_ARB);
		}

		if (m_bIsMipMapped)
		{
			rkPixelBufferAttribs.push_back(WGL_MIPMAP_TEXTURE_ARB);
			rkPixelBufferAttribs.push_back(true);
		}

#elif defined(DEBUG) || defined(_DEBUG)
		printf("SpStreamBuffer Error: Render to Texture not "
			   "supported in Linux\n");
#endif
	}

	// Set the pixel type
	if (m_bIsFloat)
	{
#ifdef _WIN32
		if (WGLEW_NV_float_buffer)
		{
			rkPixelFormatAttribs.push_back(WGL_PIXEL_TYPE_ARB);
			rkPixelFormatAttribs.push_back(WGL_TYPE_RGBA_ARB);

			rkPixelFormatAttribs.push_back(WGL_FLOAT_COMPONENTS_NV);
			rkPixelFormatAttribs.push_back(true);
		}
		else
		{
			rkPixelFormatAttribs.push_back(WGL_PIXEL_TYPE_ARB);
			rkPixelFormatAttribs.push_back(WGL_TYPE_RGBA_FLOAT_ATI);
		}
#else
		if (GLXEW_NV_float_buffer)
		{
			rkPixelFormatAttribs.push_back(GLX_FLOAT_COMPONENTS_NV);
			rkPixelFormatAttribs.push_back(1);
		}
#endif
	}
	else
	{
#ifdef _WIN32
		rkPixelFormatAttribs.push_back(WGL_PIXEL_TYPE_ARB);
		rkPixelFormatAttribs.push_back(WGL_TYPE_RGBA_ARB);
#endif
	}

	// Set up texture binding for render to texture
	if (m_bIsTexture && (RT_RENDER_TO_TEXTURE == m_eUpdateMode))
	{

#ifdef _WIN32
		if (m_bIsFloat)
		{
			if (WGLEW_NV_float_buffer)
			{
				switch(m_uiComponents)
				{
				case 1:
					rkPixelFormatAttribs.push_back(WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_R_NV);
					rkPixelFormatAttribs.push_back(true);

					rkPixelBufferAttribs.push_back(WGL_TEXTURE_FORMAT_ARB);
					rkPixelBufferAttribs.push_back(WGL_TEXTURE_FLOAT_R_NV);
					break;
				case 2:
					rkPixelFormatAttribs.push_back(WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RG_NV);
					rkPixelFormatAttribs.push_back(true);

					rkPixelBufferAttribs.push_back(WGL_TEXTURE_FORMAT_ARB);
					rkPixelBufferAttribs.push_back(WGL_TEXTURE_FLOAT_RG_NV);
					break;
				case 3:
					rkPixelFormatAttribs.push_back(WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGB_NV);
					rkPixelFormatAttribs.push_back(true);

					rkPixelBufferAttribs.push_back(WGL_TEXTURE_FORMAT_ARB);
					rkPixelBufferAttribs.push_back(WGL_TEXTURE_FLOAT_RGB_NV);
					break;
				case 4:
					rkPixelFormatAttribs.push_back(WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGBA_NV);
					rkPixelFormatAttribs.push_back(true);

					rkPixelBufferAttribs.push_back(WGL_TEXTURE_FORMAT_ARB);
					rkPixelBufferAttribs.push_back(WGL_TEXTURE_FLOAT_RGBA_NV);
					break;
				default:
					fprintf(stderr,
							"SpStreamBuffer Warning: Bad number of components "
							"(r=1,rg=2,rgb=3,rgba=4): %d.\n",
							m_uiComponents);
					break;
				}
			}
			else
			{
				if (4 == m_uiComponents)
				{
					rkPixelFormatAttribs.push_back(WGL_BIND_TO_TEXTURE_RGBA_ARB);
					rkPixelFormatAttribs.push_back(true);

					rkPixelBufferAttribs.push_back(WGL_TEXTURE_FORMAT_ARB);
					rkPixelBufferAttribs.push_back(WGL_TEXTURE_RGBA_ARB);
				}
				else
				{
					// standard ARB_render_texture only supports 3 or 4 channels
					rkPixelFormatAttribs.push_back(WGL_BIND_TO_TEXTURE_RGB_ARB);
					rkPixelFormatAttribs.push_back(true);

					rkPixelBufferAttribs.push_back(WGL_TEXTURE_FORMAT_ARB);
					rkPixelBufferAttribs.push_back(WGL_TEXTURE_RGB_ARB);
				}
			}

		}
		else
		{
			switch(m_uiComponents)
			{
			case 3:
				rkPixelFormatAttribs.push_back(WGL_BIND_TO_TEXTURE_RGB_ARB);
				rkPixelFormatAttribs.push_back(true);

				rkPixelBufferAttribs.push_back(WGL_TEXTURE_FORMAT_ARB);
				rkPixelBufferAttribs.push_back(WGL_TEXTURE_RGB_ARB);
				break;
			case 4:
				rkPixelFormatAttribs.push_back(WGL_BIND_TO_TEXTURE_RGBA_ARB);
				rkPixelFormatAttribs.push_back(true);

				rkPixelBufferAttribs.push_back(WGL_TEXTURE_FORMAT_ARB);
				rkPixelBufferAttribs.push_back(WGL_TEXTURE_RGBA_ARB);
				break;
			default:
				fprintf(stderr,
						"SpStreamBuffer Warning: Bad number of components "
						"(r=1,rg=2,rgb=3,rgba=4): %d.\n", m_uiComponents);
				break;
			}
		}
#elif defined(DEBUG) || defined(_DEBUG)
		fprintf(stderr,
				"SpStreamBuffer Error: Render to Texture not supported in "
				"Linux\n");
#endif
	}

	if (m_bIsDepthTexture && (RT_RENDER_TO_TEXTURE == m_eUpdateMode))
	{
#ifdef _WIN32
		if (m_bIsRectangle)
		{
			rkPixelFormatAttribs.push_back(WGL_BIND_TO_TEXTURE_RECTANGLE_DEPTH_NV);
			rkPixelFormatAttribs.push_back(true);

			rkPixelBufferAttribs.push_back(WGL_DEPTH_TEXTURE_FORMAT_NV);
			rkPixelBufferAttribs.push_back(WGL_TEXTURE_DEPTH_COMPONENT_NV);
		}
		else
		{
			rkPixelFormatAttribs.push_back(WGL_BIND_TO_TEXTURE_DEPTH_NV);
			rkPixelFormatAttribs.push_back(true);

			rkPixelBufferAttribs.push_back(WGL_DEPTH_TEXTURE_FORMAT_NV);
			rkPixelBufferAttribs.push_back(WGL_TEXTURE_DEPTH_COMPONENT_NV);
		}
#elif defined(DEBUG) || defined(_DEBUG)
		printf("SpStreamBuffer Error: Render to Texture not supported in "
			   "Linux\n");
#endif
	}
}
// ---------------------------------------------------------------------------
SpStreamBuffer::KeyVal SpStreamBuffer::getKeyValuePair(SpString kToken)
{
	// Parses expressions of the form "X=Y" into a pair (X,Y).

	SpString::size_type kCurrent = 0;
	if ((kCurrent = kToken.find("=")) != kToken.npos)
	{
		SpString kKey = kToken.substr(0, kCurrent);
		SpString kValue = kToken.substr(kCurrent+1, kToken.length()-kCurrent+1);
		return KeyVal(kKey, kValue);
	}
	else
		return KeyVal(kToken, "");
}
// ---------------------------------------------------------------------------
vector<int> SpStreamBuffer::parseBitVector(SpString kBitVector)
{
	// Parses expressions of the form "=r,g,b,a" into a vector: (r,g,b,a)

	vector<SpString> kPieces;
	vector<int> kBits;

	if (kBitVector == "")
	{
		kBits.push_back(8);  // if a depth isn't specified, use default 8 kBits
		return kBits;
	}

	SpString::SizeType kCurrent = 0;
	SpString::SizeType kNext = 0;
	do
	{
		kNext = kBitVector.find_first_of(", \n", kCurrent);
		kPieces.push_back(SpString(kBitVector, kCurrent, kNext - kCurrent));
		kCurrent = kNext+1;
	} while (kNext != kBitVector.npos );

	for ( vector<SpString>::iterator it = kPieces.begin(); it != kPieces.end(); it++)
	{
		kBits.push_back(strtol(it->c_str(), 0, 10));
	}

	return kBits;
}
// ---------------------------------------------------------------------------
bool SpStreamBuffer::verifyExtensions()
{
	// Checks that the necessary extensions are available based on RT mode.

#ifdef _WIN32
	if (!WGLEW_ARB_pbuffer)
	{
		PrintExtensionError("WGL_ARB_pbuffer");
		return false;
	}
	if (!WGLEW_ARB_pixel_format)
	{
		PrintExtensionError("WGL_ARB_pixel_format");
		return false;
	}
	if (m_bIsTexture && !WGLEW_ARB_render_texture)
	{
		PrintExtensionError("WGL_ARB_render_texture");
		return false;
	}
	if (m_bIsRectangle && !GLEW_NV_texture_rectangle)
	{
		PrintExtensionError("GL_NV_texture_rectangle");
		return false;
	}
	if (m_bIsFloat && !(GLEW_NV_float_buffer || WGLEW_ATI_pixel_format_float))
	{
		PrintExtensionError("GL_NV_float_buffer or GL_ATI_pixel_format_float");
		return false;

	}
	if (m_bIsFloat && m_bIsTexture && !(GLEW_NV_float_buffer || GLEW_ATI_texture_float))
	{
		PrintExtensionError("NV_float_buffer or ATI_texture_float");
	}
	if (m_bIsDepthTexture && !GLEW_ARB_depth_texture)
	{
		// [Redge]
#if defined(_DEBUG) | defined(DEBUG)
		fprintf(stderr,
				"SpStreamBuffer Warning: "
				"OpenGL extension GL_ARB_depth_texture not available.\n"
				"         Using glReadPixels() to emulate behavior.\n");
#endif
		m_bHasARBDepthTexture = false;
		//PrintExtensionError("GL_ARB_depth_texture");
		//return false;
		// [/Redge]
	}
	SetLastError(0);
#else
	if (!GLXEW_SGIX_pbuffer)
	{
		PrintExtensionError("GLX_SGIX_pbuffer");
		return false;
	}
	if (!GLXEW_SGIX_fbconfig)
	{
		PrintExtensionError("GLX_SGIX_fbconfig");
		return false;
	}
	if (m_bIsDepthTexture)
	{
		PrintExtensionError("I don't know: FIXME!");
		return false;
	}
	if (m_bIsFloat && m_bIsTexture && !GLXEW_NV_float_buffer)
	{
		PrintExtensionError("GLX_NV_float_buffer");
		return false;
	}
	if (m_eUpdateMode == RT_RENDER_TO_TEXTURE)
	{
		PrintExtensionError("Some GLX render texture extension: FIXME!");
		return false;
	}
#endif

	return true;
}
// ---------------------------------------------------------------------------
bool SpStreamBuffer::initializeTextures()
{
	// Initializes the state of textures used by the SpStreamBuffer.

	// Determine the appropriate texture formats and filtering modes.
	if (m_bIsTexture || m_bIsDepthTexture)
	{
		if (m_bIsRectangle && GLEW_NV_texture_rectangle)
			m_eTextureTarget = GL_TEXTURE_RECTANGLE_NV;
		else
			m_eTextureTarget = GL_TEXTURE_2D;
	}

	if (m_bIsTexture)
	{
		glGenTextures(1, &m_uiTextureId);
		glBindTexture(m_eTextureTarget, m_uiTextureId);

		// Use clamp to edge as the default texture wrap mode for all tex
		glTexParameteri(m_eTextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_eTextureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// Use NEAREST as the default texture filtering mode.
		glTexParameteri(m_eTextureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(m_eTextureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


		if (RT_COPY_TO_TEXTURE == m_eUpdateMode)
		{
			GLuint iInternalFormat;
			GLuint iFormat;

			if (m_bIsFloat)
			{
				if (m_bIsMipMapped)
				{
					fprintf(stderr,
						"SpStreamBuffer Error: mipmapped float textures not "
						"supported.\n");
					return false;
				}

				switch(m_uiComponents)
				{
				case 1:
					if (GLEW_NV_float_buffer)
					{
						iInternalFormat = (m_uiColorBits[0] > 16) ?
							GL_FLOAT_R32_NV : GL_FLOAT_R16_NV;
					}
					else if (GLEW_ATI_texture_float)
					{
						iInternalFormat = (m_uiColorBits[0] > 16) ?
							GL_LUMINANCE_FLOAT32_ATI :
							GL_LUMINANCE_FLOAT16_ATI;
					}
					iFormat = GL_LUMINANCE;
					break;
				case 2:
					if (GLEW_NV_float_buffer)
					{
						iInternalFormat = (m_uiColorBits[0] > 16) ?
							GL_FLOAT_RG32_NV : GL_FLOAT_RG16_NV;
					}
					else if (GLEW_ATI_texture_float)
					{
						iInternalFormat = (m_uiColorBits[0] > 16) ?
							GL_LUMINANCE_ALPHA_FLOAT32_ATI :
							GL_LUMINANCE_ALPHA_FLOAT16_ATI;
					}
					iFormat = GL_LUMINANCE_ALPHA;
					break;
				case 3:
					if (GLEW_NV_float_buffer)
					{
						iInternalFormat = (m_uiColorBits[0] > 16) ?
							GL_FLOAT_RGB32_NV : GL_FLOAT_RGB16_NV;
					}
					else if (GLEW_ATI_texture_float)
					{
						iInternalFormat = (m_uiColorBits[0] > 16) ?
							GL_RGB_FLOAT32_ATI : GL_RGB_FLOAT16_ATI;
					}
					iFormat = GL_RGB;
					break;
				case 4:
					if (GLEW_NV_float_buffer)
					{
						iInternalFormat = (m_uiColorBits[0] > 16) ?
							GL_FLOAT_RGBA32_NV : GL_FLOAT_RGBA16_NV;
					}
					else if (GLEW_ATI_texture_float)
					{
						iInternalFormat = (m_uiColorBits[0] > 16) ?
							GL_RGBA_FLOAT32_ATI : GL_RGBA_FLOAT16_ATI;
					}
					iFormat = GL_RGBA;
					break;
				default:
					printf("SpStreamBuffer Error: "
						   "Invalid number of components: %d\n",
						   m_uiComponents);
					return false;
				}
			}
			else // non-float
			{
				if (4 == m_uiComponents)
				{
					iInternalFormat = GL_RGBA8;
					iFormat = GL_RGBA;
				}
				else
				{
					iInternalFormat = GL_RGB8;
					iFormat = GL_RGB;
				}
			}

			// Allocate the texture image (but pass it no data for now).
			glTexImage2D(m_eTextureTarget, 0, iInternalFormat,
						 m_iWidth, m_iHeight, 0, iFormat, GL_FLOAT, NULL);
		}
	}

	if (m_bIsDepthTexture)
	{
		glGenTextures(1, &m_uiDepthTextureId);
		glBindTexture(m_eTextureTarget, m_uiDepthTextureId);

		// Use clamp to edge as the default texture wrap mode for all tex
		glTexParameteri(m_eTextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_eTextureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// Use NEAREST as the default texture filtering mode.
		glTexParameteri(m_eTextureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(m_eTextureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		if (RT_COPY_TO_TEXTURE == m_eUpdateMode)
		{
			// [Redge]
			if (m_bHasARBDepthTexture)
			{
				// Allocate the texture image (but pass it no data for now).
				glTexImage2D(m_eTextureTarget, 0, GL_DEPTH_COMPONENT,
							 m_iWidth, m_iHeight, 0, GL_DEPTH_COMPONENT,
							 GL_FLOAT, NULL);
			}
			else
			{
				// allocate memory for depth texture
				// Since this is slow, we warn the user in debug mode. (above)
				m_ausPoorDepthTexture = new unsigned short[m_iWidth * m_iHeight];
				glTexImage2D(m_eTextureTarget, 0, GL_LUMINANCE16,
							 m_iWidth, m_iHeight, 0, GL_LUMINANCE,
							 GL_UNSIGNED_SHORT, m_ausPoorDepthTexture);
			}
			// [/Redge]
		}
	}

	return true;
}
// ---------------------------------------------------------------------------
void SpStreamBuffer::captureBuffer()
{
	// Does the actual copying for RenderTextures with RT_COPY_TO_TEXTURE

#ifdef _WIN32
	if (RT_COPY_TO_TEXTURE == m_eUpdateMode)
	{
		if (m_bIsTexture)
		{
			glBindTexture(m_eTextureTarget, m_uiTextureId);
			glCopyTexSubImage2D(m_eTextureTarget,
								0, 0, 0, 0, 0, m_iWidth, m_iHeight);
		}
		if (m_bIsDepthTexture)
		{
			glBindTexture(m_eTextureTarget, m_uiDepthTextureId);
			// HOW TO COPY DEPTH TEXTURE??? Supposedly this just magically works...
			// [Redge]
			if (m_bHasARBDepthTexture)
			{
				glCopyTexSubImage2D(m_eTextureTarget, 0, 0, 0, 0, 0,
									m_iWidth, m_iHeight);
			}
			else
			{
				// no 'real' depth texture available, so behavior has to be emulated
				// using glReadPixels (beware, this is (naturally) slow ...)
				glReadPixels(0, 0, m_iWidth, m_iHeight, GL_DEPTH_COMPONENT,
							 GL_UNSIGNED_SHORT, m_ausPoorDepthTexture);
				glTexImage2D(m_eTextureTarget, 0, GL_LUMINANCE16,
							 m_iWidth, m_iHeight, 0, GL_LUMINANCE,
							 GL_UNSIGNED_SHORT, m_ausPoorDepthTexture);
			}
			// [/Redge]
		}
	}

#else
	assert(m_bIsTexture);
	glBindTexture(m_eTextureTarget, m_uiTextureId);
	glCopyTexSubImage2D(m_eTextureTarget, 0, 0, 0, 0, 0, m_iWidth, m_iHeight);
#endif

}
// ---------------------------------------------------------------------------
bool SpStreamBuffer::releaseBoundBuffers()
{
	// Releases buffer bindings on RenderTextures with RT_RENDER_TO_TEXTURE

#ifdef _WIN32
	if (m_bIsTexture && RT_RENDER_TO_TEXTURE == m_eUpdateMode)
	{
		glBindTexture(m_eTextureTarget, m_uiTextureId);

		// release the pbuffer from the render texture object
		if (0 != m_iCurrentBoundBuffer && m_bIsBufferBound)
		{
			if (FALSE == wglReleaseTexImageARB(m_hPixelBuffer, m_iCurrentBoundBuffer))
			{
				wglGetLastError();
				return false;
			}
			m_bIsBufferBound = false;
		}
	}

	if (m_bIsDepthTexture && RT_RENDER_TO_TEXTURE == m_eUpdateMode)
	{
		glBindTexture(m_eTextureTarget, m_uiDepthTextureId);

		// release the pbuffer from the render texture object
		if (FALSE == wglReleaseTexImageARB(m_hPixelBuffer, WGL_DEPTH_COMPONENT_NV))
		{
			wglGetLastError();
			return false;
		}
	}

#else
	// textures can't be bound in Linux
#endif
	return true;
}
// ---------------------------------------------------------------------------
bool SpStreamBuffer::makeCurrent()
{
#ifdef _WIN32
	// make the pbuffer's rendering context current.
	if (FALSE == wglMakeCurrent( m_hDC, m_hGLContext))
	{
		wglGetLastError();
		return false;
	}
#else
	if (false == glXMakeCurrent(m_pkDisplay, m_hPixelBuffer, m_hGLContext))
	{
		return false;
	}
#endif

	return true;
}
// ---------------------------------------------------------------------------
void SpStreamBuffer::enableTextureFiltering()
{
	if (isMipMapped())
	{
		// Enable trilinear filtering so we can see the mipmapping
		if (isTexture())
		{
			bind();
			glTexParameteri(getTextureTarget(),
							GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(getTextureTarget(),
							GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(getTextureTarget(),
							GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
		}

		if (isDepthTexture())
		{
			bindDepth();
			glTexParameteri(getTextureTarget(),
							GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(getTextureTarget(),
							GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(getTextureTarget(),
							GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
		}
	}
	else if (!(isRectangleTexture() || isFloatTexture()))
	{
		if (isTexture())
		{
			bind();
			glTexParameteri(getTextureTarget(),
							GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(getTextureTarget(),
							GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		if (isDepthTexture())
		{
			bindDepth();
			glTexParameteri(getTextureTarget(),
							GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(getTextureTarget(),
							GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
}
// ---------------------------------------------------------------------------
