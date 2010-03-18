// #############################################################################
//! SpTurbulenceOp.h : Turbulence stream operator to be used with a stream basis
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

#ifndef SP_GLSL_TURBULENCE_OP_H
#define SP_GLSL_TURBULENCE_OP_H

#include "SpGridSg.h"
#include "SpStreamOperator.h"
#include "SpStreamBuffer.h"
#include "SpStreamBasis.h"
#include "SpGpuProgram.h"
#include "SpStreamFeedback.h"
#include "SpGlslVertexProgram.h"
#include "SpGlslFragmentProgram.h"

//----------------------------------------------------------------------------

namespace Spark
{

//----------------------------------------------------------------------------
//! Turbulence stream operator to be used with a stream basis class
//----------------------------------------------------------------------------
class SpTurbulenceOp : public SpStreamOperator
{

//! Construction:
public:

	SpTurbulenceOp(
		float fX=1, float fY=1, float fZ=1,
		float fOctaves = 4,
		float fIncrement = 0.5f,
		float fLacunarity = 2.0345f);

	virtual ~SpTurbulenceOp();

	//: Initializes internal data members
	void initialize(
		SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy, bool bCreateTextures);

//! Access Methods:
public:

	virtual void setInputStream(SpStreamBasis *pkInputStream);
	virtual void setInputStream(SpStreamInput* pkInputStream);

	void setOctaves(float fOctaves);
	float getOctaves() const;

	void setLacunarity(float fLacunarity);
	float getLacunarity() const;

	void setIncrement(float fIncrement);
	float getIncrement() const;

	virtual void setOffset(float fX, float fY, float fZ);
	virtual void getOffset(float& rfX, float& rfY, float& rfZ) const;

//! Internal Methods:
protected:

	//: Activates the output stream, if necessary
	virtual bool enableOutputStream(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy);

	//: Sets the necessary state for the stream operation
	virtual bool setupState(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy);

	//: Performs the stream operation
	virtual bool processStream(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy);

	//: Puts the results of the operation into the output stream.
	virtual bool updateOutputStream(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy);

	//: Resets the state
	virtual bool resetState(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy);

	//: Deactivates the output stream, if necessary
	virtual bool disableOutputStream(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy);

//! Internal Data:
protected:

	float m_fOffsetX;
	float m_fOffsetY;
	float m_fOffsetZ;

	float m_fX;
	float m_fY;
	float m_fZ;

	float m_fOctaves;
	float m_fIncrement;
	float m_fLacunarity;

	unsigned int m_uiCurrentPass;
	unsigned int m_uiMaxOctaves;
	double * m_adExponents;

	bool m_bInitialized;
	bool m_bCreateTextures;
	bool m_bInputIsBasis;

	SpGridSg m_kGrid;

	unsigned int* m_auiTextures;
	unsigned int m_uiTextureCount;

	SpGlslVertexProgram* m_pkIdentityVertexProgram;
	SpGlslFragmentProgram* m_pkAddMultiTextureProgram;
};

//----------------------------------------------------------------------------

}	// end namespace: Spark

#endif
