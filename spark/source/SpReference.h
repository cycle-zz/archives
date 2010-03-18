// #############################################################################
//! SpReference.h : Reference class with garbage collection for supporting shared objects
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

#ifndef SP_REFERENCE_H
#define SP_REFERENCE_H

// ---------------------------------------------------------------------------

namespace Spark
{

// ---------------------------------------------------------------------------
//! Reference class with garbage collection for supporting shared objects
// ---------------------------------------------------------------------------
template <class ClassType>
class SpReference
{

//! Construction:
public:

    SpReference (ClassType* pkObject = 0);
    SpReference (const SpReference& rkSpReference);
    ~SpReference ();

//! Conversions:
public:

    operator ClassType* () const;
    ClassType& operator* () const;
    ClassType* operator-> () const;

//! Assignment:
public:

    SpReference& operator= (const SpReference& rkSpReference);
    SpReference& operator= (ClassType* pkObject);

//! Comparison:
public:

    bool operator== (ClassType* pkObject) const;
    bool operator!= (ClassType* pkObject) const;
    bool operator== (const SpReference& rkSpReference) const;
    bool operator!= (const SpReference& rkSpReference) const;

//! Internal Data:
protected:

    //: Pointer to the shared object
    ClassType* m_pkPointer;
};

// ---------------------------------------------------------------------------

#include "SpReference.inc"

// ---------------------------------------------------------------------------
// Macro for Enabling SpReference Counting in Class Declaration
// ---------------------------------------------------------------------------

#define EnableReferencing() \
public: \
    void addSpReference () \
    { \
        m_uiSpReferences++; \
    } \
    \
    void removeSpReference () \
    { \
        if ( --m_uiSpReferences == 0 ) \
            delete this; \
    } \
    \
    unsigned int getSpReferenceCount () const \
    { \
        return m_uiSpReferences; \
    } \
    \
private: \
    unsigned int m_uiSpReferences

// ---------------------------------------------------------------------------

#define SpReferenceCast(type,reference) ((type*)(void*)(reference))

// ---------------------------------------------------------------------------

}	// end namespace: Spark

#endif



