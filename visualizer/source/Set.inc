// #############################################################################
// # Set.inc  -  Template Include file for a generic Unordered Set of Objects
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

// #############################################################################
// Set - template ADT class for an unordered set of objects
// #############################################################################

//--------------------------------------------------------------------------------
template <class TYPE>
Set<TYPE>::Set(UInt uiCapacity, UInt uiResize)
{
    m_uiCapacity = uiCapacity;
    m_uiResize = uiResize;
    m_uiSize = 0;
    m_atElements = new TYPE[uiCapacity];
}
//--------------------------------------------------------------------------------
template <class TYPE>
Set<TYPE>::Set(const Set& rkSet)
{
    m_uiCapacity = rkSet.m_uiCapacity;
    m_uiResize = rkSet.m_uiResize;
    m_uiSize = rkSet.m_uiSize;
    m_atElements = new TYPE[m_uiCapacity];
    memcpy(m_atElements,rkSet.m_atElements,m_uiCapacity*sizeof(TYPE));
}
//--------------------------------------------------------------------------------
template <class TYPE>
Set<TYPE>::~Set()
{
    delete[] m_atElements;
}
//--------------------------------------------------------------------------------
template <class TYPE>
Set<TYPE>& Set<TYPE>::operator= (const Set& rkSet)
{
    delete[] m_atElements;
    
    m_uiCapacity = rkSet.m_uiCapacity;
    m_uiResize = rkSet.m_uiResize;
    m_uiSize = rkSet.m_uiSize;
    m_atElements = new TYPE[m_uiCapacity];

    memcpy(m_atElements,rkSet.m_atElements,m_uiCapacity*sizeof(TYPE));
    return *this;
}
//--------------------------------------------------------------------------------
template <class TYPE>
UInt Set<TYPE>::capacity() const
{
    return m_uiCapacity;
}
//--------------------------------------------------------------------------------
template <class TYPE>
UInt Set<TYPE>::resize() const
{
    return m_uiResize;
}
//--------------------------------------------------------------------------------
template <class TYPE>
UInt Set<TYPE>::size() const
{
    return m_uiSize;
}
//--------------------------------------------------------------------------------
template <class TYPE>
const TYPE* Set<TYPE>::values() const
{
    return m_atElements;
}
//--------------------------------------------------------------------------------
template <class TYPE>
const TYPE& Set<TYPE>::operator[] (UInt i) const
{
    return m_atElements[i];
}
//--------------------------------------------------------------------------------
template <class TYPE>
TYPE& Set<TYPE>::element(UInt i) const
{
    return m_atElements[i];
}
//--------------------------------------------------------------------------------
template <class TYPE>
bool Set<TYPE>::insert(const TYPE& rkElement, bool bCheck)
{
	if(bCheck)
	{
		for (UInt i = 0; i < m_uiSize; i++)
		{
			if ( rkElement == m_atElements[i] )
				return false;
		}
	}

    if ( m_uiSize == m_uiCapacity )
    {
        // array is full, resize it
        UInt iNewCapacity = m_uiCapacity + m_uiResize;
        TYPE* atNewElement = new TYPE[iNewCapacity];

        memcpy(atNewElement,m_atElements,m_uiCapacity*sizeof(TYPE));
        delete[] m_atElements;

        m_atElements = atNewElement;
        m_uiCapacity = iNewCapacity;
    }

    m_atElements[m_uiSize++] = rkElement;
    return true;
}
//--------------------------------------------------------------------------------
template <class TYPE>
void Set<TYPE>::force(const TYPE& rkElement)
{
    if ( m_uiSize == m_uiCapacity )
    {
        // array is full, resize it
        UInt iNewCapacity = m_uiCapacity + m_uiResize;

        TYPE* atNewElement = new TYPE[iNewCapacity];
        memcpy(atNewElement,m_atElements,m_uiCapacity*sizeof(TYPE));
        delete[] m_atElements;

        m_atElements = atNewElement;
        m_uiCapacity = iNewCapacity;
    }

    m_atElements[m_uiSize++] = rkElement;
}
//--------------------------------------------------------------------------------
template <class TYPE>
bool Set<TYPE>::remove(const TYPE& rkElement)
{
    for (UInt i = 0; i < m_uiSize; i++)
    {
        if ( rkElement == m_atElements[i] )
        {
            // element exists, shift array to fill in empty slot
            for (UInt j = i+1; j < m_uiSize; j++, i++)
                m_atElements[i] = m_atElements[j];

            m_uiSize--;
            return true;
        }
    }

    return false;
}
//--------------------------------------------------------------------------------
template <class TYPE>
bool Set<TYPE>::exists(const TYPE& rkElement) const
{
    for (UInt i = 0; i < m_uiSize; i++)
    {
        if ( rkElement == m_atElements[i] )
            return true;
    }

    return false;
}
//--------------------------------------------------------------------------------
template <class TYPE>
int Set<TYPE>::find(const TYPE& rkElement) const
{
    for (UInt i = 0; i < m_uiSize; i++)
    {
        if ( rkElement == m_atElements[i] )
			return i;
    }

    return -1;
}
//--------------------------------------------------------------------------------
template <class TYPE>
void Set<TYPE>::clear()
{
    m_uiSize = 0;
}
//--------------------------------------------------------------------------------
template <class TYPE>
void Set<TYPE>::erase(UInt uiCapacity, UInt uiResize)
{
    delete[] m_atElements;
    m_uiCapacity = uiCapacity;
    m_uiResize = uiResize;
    m_uiSize = 0;
    m_atElements = new TYPE[uiCapacity];
}
//--------------------------------------------------------------------------------

// end file: Set.inc
