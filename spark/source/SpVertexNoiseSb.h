// #############################################################################
//! SpVertexNoiseSb.h : Noise generating stream basis using vertices
//
// Created 		: Aug 2004
// Copyright	: (C) 2004 by Derek Gerstmann
// Email		: dgerstma@acm.org
//
// #############################################################################

// =============================================================================
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
// =============================================================================

#ifndef SP_VERTEX_NOISE_STREAM_BASIS_H
#define SP_VERTEX_NOISE_STREAM_BASIS_H

//----------------------------------------------------------------------------

#include "SpGlslVertexProgram.h"
#include "SpGlslFragmentProgram.h"
#include "SpCopyToTextureFb.h"
#include "SpStreamInput.h"
#include "SpTexturedGridSg.h"
#include "SpStreamBasis.h"
#include "SpTuple.h"

//----------------------------------------------------------------------------

namespace Spark
{

//----------------------------------------------------------------------------
//! Noise generating stream basis which operates on vertex data
//----------------------------------------------------------------------------
class SpVertexNoiseSb : public SpStreamBasis
{

//! Construction:
public:

	SpVertexNoiseSb(
		bool bAbsNoise=false,
		float fOffsetX=1, float fOffsetY=1, float fOffsetZ=1,
		float fScaleX=1, float fScaleY=1, float fScaleZ=1,
		unsigned int uiGridResolution = 150,
		unsigned long iSeed=1234);

	virtual ~SpVertexNoiseSb();

//! Operations:
public:

	void initialize();
	void destroy();
	void preload();
	void enable();
	void disable();

	inline void setGridResolution( unsigned int uiResolution )
	{
		m_kGrid.setResolution( uiResolution, uiResolution );
		m_bHasChanged = true;
	}

	inline SpGlslVertexProgram* program()
	{ return m_pkVertexProgram; }

//! Inherited Methods:
public:

	virtual bool hasChanged();
	virtual bool sendOutputToBuffer(
		SpStreamBuffer* pkBuffer, SpCopyToTextureFb *pkCopy
	);

//! Internal Data:
protected:


	//: Permutation table
	int* m_aiP;

	//: Packed Permutation + Gradient table
	SpVector4f* m_akPG;

	//: True if object has already been initialized
	bool m_bIsInitialized;

	//: Seed for prng
	unsigned long m_ulSeed;

	//: Grid for vertex program execution
	SpTexturedGridSg m_kGrid;

	//: GLSL Vertex Program
	SpGlslVertexProgram* m_pkVertexProgram;

	//: GLSL Fragment Program
	SpGlslFragmentProgram* m_pkFragmentProgram;

};

//----------------------------------------------------------------------------

} // end namespace: Spark

#endif
