// #############################################################################
// SpAllocate.h : Custom Memory Allocation Routines for Multiple Dimensions
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

#ifndef SP_ALLOCATE_H
#define SP_ALLOCATE_H

//----------------------------------------------------------------------------

namespace Spark
{

//----------------------------------------------------------------------------
template <class T>
void Allocate2D (int iCols, int iRows, T**& raatArray)
{
    raatArray = new T*[iRows];
    raatArray[0] = new T[iRows*iCols];
    for (int iRow = 1; iRow < iRows; iRow++)
        raatArray[iRow] = &raatArray[0][iCols*iRow];
}
//----------------------------------------------------------------------------
template <class T>
void Deallocate2D (T** aatArray)
{
    delete[] aatArray[0];
    delete[] aatArray;
}
//----------------------------------------------------------------------------
template <class T>
void Allocate3D (int iCols, int iRows, int iSlices, T***& raaatArray)
{
    raaatArray = new T**[iSlices];
    for (int iSlice = 0; iSlice < iSlices; iSlice++)
    {
        raaatArray[iSlice] = new T*[iRows];
        for (int iRow = 0; iRow < iRows; iRow++)
            raaatArray[iSlice][iRow] = new T[iCols];
    }
}
//----------------------------------------------------------------------------
template <class T>
void Deallocate3D (int iRows, int iSlices, T*** aaatArray)
{
    for (int iSlice = 0; iSlice < iSlices; iSlice++)
    {
        for (int iRow = 0; iRow < iRows; iRow++)
            delete[] aaatArray[iSlice][iRow];
        delete[] aaatArray[iSlice];
    }
    delete[] aaatArray;
}
//----------------------------------------------------------------------------

}	// end namespace: Spark

#endif