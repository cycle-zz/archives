// #############################################################################
// # Set.h  -  Header for a generic unordered set of unique objects
// #
// # Created 	: Sat Jan 10 2004
// # Copyright	: (C) 2004 by Derek Gerstmann
// # Email	: dgerstma@acm.org
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

#ifndef DG_SET_H
#define DG_SET_H

// headers
#include "DataTypes.h"
#include <memory>

// -----------------------------------------------------------------------------

namespace dg
{

// #############################################################################
// Set - template ADT class for an unordered set of unique objects
// #############################################################################

template <class TYPE>
class Set
{

public:

	// constructors
	Set(UInt iCapacity=1, UInt iResize=10);
	Set(const Set& rkSet);

	// destructor
	~Set();

	// operator methods
	Set& operator=(const Set& rkSet);

	// size methods
	inline UInt capacity() const;
	inline UInt resize() const;
	inline UInt size() const;

	// retrieval methods
	inline const TYPE* values() const;
	inline const TYPE& operator[] (UInt uiIndex) const;
	inline TYPE& element(UInt uiIndex) const;

	
	inline operator const TYPE* () const
	{
		return m_atElements;
	}
	inline operator TYPE* ()
	{
		return m_atElements;
	}

	// insertion & removal methods
	bool insert(const TYPE& rkElement, bool bCheck=false);
	void force(const TYPE& rkElement);	// no checking
	bool remove(const TYPE& rkElement);
	bool exists(const TYPE& rkElement) const;
	int find(const TYPE& rkElement) const;
	void erase(UInt uiCapacity=1, UInt uiGrowBy=10);
	void clear();

protected:

	UInt		m_uiCapacity;	// maximum capacity of set
	UInt		m_uiResize;		// value to resize by when set is full
	UInt		m_uiSize;		// current size of set
	TYPE*		m_atElements;	// elements of set

}; // end class: Set

#include "Set.inc"

} // end namespace: dg

#endif // endif: DG_SET_H

// end file: Set.h

