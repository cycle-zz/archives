// #############################################################################
//! SpStreamBasis.h : Abstract base class for a stream basis
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

#ifndef SP_STREAM_BASIS_H
#define SP_STREAM_BASIS_H

#include "SpStreamInput.h"

//----------------------------------------------------------------------------

namespace Spark
{

//----------------------------------------------------------------------------
//! Abstract base class for a stream basis for spectral synthesis
//----------------------------------------------------------------------------
class SpStreamBasis : public SpStreamInput
{

//! Construction:
public:

	SpStreamBasis(
		float fOffsetX=1, float fOffsetY=1, float fOffsetZ=1,
		float fScaleX=1, float fScaleY=1, float fScaleZ=1,
		float fWeight=1)
	:   SpStreamInput(),
		m_fOffsetX(fOffsetX),
		m_fOffsetY(fOffsetY),
		m_fOffsetZ(fOffsetZ),
		m_fScaleX(fScaleX),
		m_fScaleY(fScaleY),
		m_fScaleZ(fScaleZ),
		m_fWeight(fWeight)
	{
		// EMPTY!
	}

	virtual ~SpStreamBasis()
	{
		// EMPTY!
	}

//! Methods:
public:

	virtual bool hasChanged() = 0;

	virtual bool sendOutputToBuffer(
		SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy
	) = 0;

	virtual void setScale( float fX, float fY, float fZ )
	{
		m_fScaleX = fX;
		m_fScaleY = fY;
		m_fScaleZ = fZ;
		m_bHasChanged = true;
	}

	virtual void getScale( float& rfX, float& rfY, float& rfZ ) const
	{
		rfX = m_fScaleX;
		rfY = m_fScaleY;
		rfZ = m_fScaleZ;
	}

	virtual void setOffset( float fX, float fY, float fZ )
	{
		m_fOffsetX = fX;
		m_fOffsetY = fY;
		m_fOffsetZ = fZ;
		m_bHasChanged = true;
	}

	virtual void getOffset( float& rfX, float& rfY, float& rfZ ) const
	{
		rfX = m_fOffsetX;
		rfY = m_fOffsetY;
		rfZ = m_fOffsetZ;
	}

	virtual void setWeight( float fWeight )
	{
		m_fWeight = fWeight;
		m_bHasChanged = true;
	}

	virtual float getWeight() const
	{
		return m_fWeight;
	}

//! Internal Data:
protected:

	//: Offset for noise evaluation
	float m_fOffsetX;
	float m_fOffsetY;
	float m_fOffsetZ;

	//: Scale for noise evaluation
	float m_fScaleX;
	float m_fScaleY;
	float m_fScaleZ;

	//: Weight for spectral distribtuion
	float m_fWeight;

	//: True if object has been modified
	bool m_bHasChanged;
};

//----------------------------------------------------------------------------

} // end namespace: Spark

#endif // SOURCE_OPERATOR_H
