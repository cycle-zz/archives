// #############################################################################
// # SpStreamBuffer.h : A multi-format OpenGL render-to-texture interface
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

#ifndef SP_GPU_BUFFER_H
#define SP_GPU_BUFFER_H

// =============================================================================
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
// Original SpStreamBuffer code: Mark J. Harris
// Original Render-to-depth-texture support: Thorsten Scheuermann
// Additional Refactoring: Derek Gerstmann
// Linux Copy-to-texture: Eric Werness
// Various Bug Fixes: Daniel (Redge) Sperl
//                    Bill Baxter
//
// =============================================================================

#include <vector>

#include "SpString.h"
#include "SpGlHeaders.h"
// ---------------------------------------------------------------------------

namespace Spark
{

// ---------------------------------------------------------------------------
/* The pixel format for the pbuffer is controlled by the mode string passed
* into the PBuffer constructor. This string can have the following attributes:
*
* To specify the pixel format, use the following syntax.
*   <channels>=<bits>
* <channels> must match one of the following.
*
* r			   - r pixel format (for float buffer).
* rg		   - rg pixel format (for float buffer).
* rgb          - rgb pixel format. 8 bit or 16/32 bit in float buffer mode
* rgba         - same as "rgb alpha" string
*
* <bits> can either be a scalar--meaning the same bit depth for each
* channel-- or a 2-, 3-, 4-component vector matching the specified number of
* channels. Vector components should be comma separated. An optional 'f'
* suffix on the bit depth specifies float components.  In this case <bits>
* must be either "32f" or "16f".  If <bits> is empty, the default 8 bits per
* channel will be used.
*   r=32f
*   rg=16f
*   rgb=8
*   rgb=5,6,5
*
* The following other attributes are supported.
*
* depth=n      - must have n-bit depth buffer, omit n for default (24 bits)
* stencil=n    - must have n-bit stencil buffer, omit n for default (8 bits)
* samples=n    - must support n-sample antialiasing (n can be 2 or 4)
* aux=n        - must have n AUX buffers
* doublebuffer - must support double buffered rendering
*
* tex2D
* texRECT
* texCUBE  - must support binding pbuffer as texture to specified target
*          - binding the depth buffer is also supported by specifying
* depthTex2D
* depthTexRECT
* depthTexCUBE
*          - Both depth and color texture binding, may be specified, but
*            the targets must match!
*            For example: "tex2D depthTex2D" or "texRECT depthTexRECT"
*
* rtt
* ctt      - These mutually exclusive options specify the update method used
*            for render textures that support texture binding. "rtt"
*            indicates that render to texture will be used to update the
*            texture. "ctt" indicates that copy to texture will be used
*            (i.e. glCopyTexSubImage2D()). "rtt" is the default if neither is
*            specified, and one of the "tex*" options above is.
*
*
*---------------------------------------------------------------------------
*
* USAGE NOTES:
*
* * Texture Parameters:
*   The default texture wrap mode is GL_CLAMP_TO_EDGE for all textures, and
*   the default texture filtering modes (min and mag) are GL_NEAREST.
*   To change these parameters, simply bind the SpStreamBuffer (using the
*   bind() method), and set them the way you would for any GL texture object.
*   The same goes for depth textures.
*
* * Enabling Mipmapping:
*   This is similar to the texture parameters above.  When "rtt" is specified
*   in the mode string, "mipmap" must also be specified in order to enable
*   a mipmapped pbuffer.  Then, the mipmaps must be created by enabling the
*   GL_SGIS_GENERATE_MIPMAP texture parameter in the same way as above, and
*   the min filter mode must be set to a mipmap filter mode, as with any
*   mipmapped texture object.
*
* * Enabling Anisotropic Filtering
*   As with the texture parameters above, except as in the following code:
*   glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, max);
*   glTexParameterf(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, <value < max>);
*/
// ---------------------------------------------------------------------------
//! A multi-format OpenGL GPU resident data buffer and render-to-texture (RTT) interface
// ---------------------------------------------------------------------------
class SpStreamBuffer
{

//! Enumerations:
public:

	enum UpdateMode
	{
		RT_RENDER_TO_TEXTURE,
		RT_COPY_TO_TEXTURE
	};

//! Construction:
public:

	SpStreamBuffer(const char *strMode="rgb tex2D");
	~SpStreamBuffer();

//! Interface:
public:

	//! Call this once before use.  Set bShare to true to share lists, textures,
	//! and program objects between the render texture context and the
	//! current active GL context.
	bool initialize(
		int iWidth, int iHeight,
		bool bShareObjects=true,
		bool bCopyContext=false);

	// !Change the render texture format.
	bool reset(const char* acStrMode,...);

	// !Change the size of the render texture.
	bool resize(int iWidth, int iHeight);

	// !Begin drawing to the texture. (i.e. use as "output" texture)
	bool enable();

	// !Ends drawing to 'current', begins drawing to this SpStreamBuffer
	bool enable(SpStreamBuffer* pkCurrent);

	// !End drawing to the texture.
	bool disable();

	// !Bind the texture to the active texture unit for use as an "input" texture
	void bind() const;

	// !Bind the depth texture to the active texture unit for use as an "input" texture
	void bindDepth() const;

	// !Associate the RTT texture with 'iBuffer' (default is WGL_FRONT_LEFT_ARB)
	bool bindBuffer( int iBuffer );

	// !Enables texture filtering for the texture target based on current state
	void enableTextureFiltering();

	//! Enables the texture target appropriate for this render texture.
	inline void enableTextureTarget() const
	{ if (m_bInitialized) glEnable(m_eTextureTarget); }

	//! Disables the texture target appropriate for this render texture.
	inline void disableTextureTarget() const
	{ if (m_bInitialized) glDisable(m_eTextureTarget); }

	//! Returns the texture ID.
	inline unsigned int getTextureId() const
	{ return m_uiTextureId; }

	//! Returns the depth texture ID.
	inline unsigned int getDepthTextureId() const
	{ return m_uiDepthTextureId; }

	//! Returns the texture target this texture is bound to.
	inline unsigned int getTextureTarget() const
	{ return m_eTextureTarget; }

	//! Conversion operator allows SpStreamBuffer to be passed to GL calls
	inline operator unsigned int() const
	{return m_uiTextureId;}

	//! Returns the width of the offscreen buffer.
	inline int getWidth() const
	{ return m_iWidth;  }

	//! Returns the width of the offscreen buffer.
	inline int getHeight() const
	{ return m_iHeight; }

	//! Returns the maximum S texture coordinate.
	inline int getMaxS() const
	{ return isRectangleTexture() ? m_iWidth : 1; }

	//! Returns the maximum T texture coordinate.
	inline int getMaxT() const
	{ return isRectangleTexture() ? m_iHeight : 1; }

	//! Returns the number of red bits allocated.
	inline int getRedBits() const
	{ return m_uiColorBits[0]; }

	//! Returns the number of green bits allocated.
	inline int getGreenBits() const
	{ return m_uiColorBits[1]; }

	//! Returns the number of blue bits allocated.
	inline int getBlueBits() const
	{ return m_uiColorBits[2]; }

	//! Returns the number of alpha bits allocated.
	inline int getAlphaBits() const
	{ return m_uiColorBits[3]; }

	//! Returns the number of depth bits allocated.
	inline int getDepthBits() const
	{ return m_uiDepthBits; }

	//! Returns the number of stencil bits allocated.
	inline int getStencilBits() const
	{ return m_uiStencilBits; }

	//! Returns the initial mode string used to initialize the buffer
	inline const SpString& getModeString() const // [DG]
	{ return m_kModeString; }

	//! True if this SpStreamBuffer has been properly initialized.
	inline bool isInitialized() const
	{ return m_bInitialized; }

	//! True if this is a texture and not just an offscreen buffer.
	inline bool isTexture() const
	{ return m_bIsTexture; }

	//! True if this is a depth texture and not just an offscreen buffer.
	inline bool isDepthTexture() const
	{ return m_bIsDepthTexture; }

	//! True if this is a floating point buffer / texture.
	inline bool isFloatTexture() const
	{ return m_bIsFloat; }

	//! True if this is a double-buffered pbuffer
	inline bool isDoubleBuffered() const
	{ return m_bIsDoubleBuffered; }

	//! True if this texture has non-power-of-two dimensions.
	inline bool isRectangleTexture() const
	{ return m_bIsRectangle; }

	//! True if this pbuffer has a depth buffer.
	inline bool hasDepth() const
	{ return (m_uiDepthBits > 0); }

	//! True if this pbuffer has a stencil buffer.
	inline bool hasStencil() const
	{ return (m_uiStencilBits > 0); }

	//! True if this texture has mipmaps.
	inline bool isMipMapped() const
	{ return m_bIsMipMapped; }

	/**
	* @fn isPowerOfTwo(int n)
	* @brief Returns true if /param n is an integer power of 2.
	*
	* Taken from Steve Baker's Cute Code Collection.
	* http://www.sjbaker.org/steve/software/cute_code.html
	*/
	static bool isPowerOfTwo(int n)
	{ return ((n&(n-1))==0); }

//! Internal Typedefs:
protected:

	typedef std::pair<SpString, SpString> KeyVal;
	typedef std::vector<int> IntArray;

//! Internal Methods:
protected:

	bool invalidate();

	void parseModeString(
		const char *acModeString,
		IntArray &rkPixelFormatAttribs,
		IntArray &rkPixelBufferAttribs
	);

	IntArray parseBitVector(SpString bitVector);
	KeyVal getKeyValuePair(SpString token);

	bool verifyExtensions();
	bool initializeTextures();

	void captureBuffer();
	bool releaseBoundBuffers();
	bool makeCurrent();
	bool bindDepthBuffer( ) const;

//! Internal Data:
protected:

	int          m_iWidth;     // width of the pbuffer
	int          m_iHeight;    // height of the pbuffer

	bool         m_bIsTexture;
	bool         m_bIsDepthTexture;
	bool         m_bHasARBDepthTexture; // [Redge]

	UpdateMode   m_eUpdateMode;

	bool         m_bInitialized;

	unsigned int m_iNumAuxBuffers;
	bool         m_bIsBufferBound;
	int          m_iCurrentBoundBuffer;

	unsigned int m_uiComponents;
	unsigned int m_uiColorBits[4];
	unsigned int m_uiDepthBits;
	unsigned int m_uiStencilBits;


	bool         m_bIsFloat;
	bool         m_bIsDoubleBuffered;
	bool         m_bIsPowerOf2;
	bool         m_bIsRectangle;
	bool         m_bIsMipMapped;

	bool         m_bShareObjects;
	bool         m_bCopyContext;

#ifdef _WIN32
	HDC          m_hDC;        // Handle to a device context.
	HGLRC        m_hGLContext; // Handle to a GL context.
	HPBUFFERARB  m_hPixelBuffer;   // Handle to a pbuffer.

	HGLRC        m_hPreviousContext;
	HDC          m_hPreviousDC;

#else
	Display     *m_pkDisplay;
	GLXContext   m_hGLContext;
	GLXPbuffer   m_hPixelBuffer;

	GLXContext   m_hPreviousContext;
	GLXDrawable  m_hPreviousDrawable;

#endif

	// Texture stuff
	GLenum       m_eTextureTarget;
	unsigned int m_uiTextureId;
	unsigned int m_uiDepthTextureId;

	unsigned short* m_ausPoorDepthTexture; // [Redge]

	IntArray 	m_kPixelFormatAttribs;
	IntArray 	m_kPixelBufferAttribs;

	SpString		m_kModeString;


//! Restricted Methods:
private:

	//! Using these could lead to some odd behavior
	SpStreamBuffer(const SpStreamBuffer&);
	SpStreamBuffer& operator=(const SpStreamBuffer&);

};

// ---------------------------------------------------------------------------

} // end namespace: Spark

#endif
