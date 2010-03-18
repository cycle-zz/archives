// #############################################################################
// # Random.h - LGM Random Number Generator (see license info below)
// #
// # Created 	: May 2004
// # Copyright	: (C) 2004 by Derek Gerstmann
// # Email		: dgerstma@acm.org
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

#ifndef SP_RANDOM_H
#define SP_RANDOM_H

namespace Spark
{

// -----------------------------------------------------------------------------
/*
   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote
        products derived from this software without specific prior written
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
// -----------------------------------------------------------------------------
//! Initializes the random number table
// -----------------------------------------------------------------------------
void SeedRandom(unsigned long seed);

// -----------------------------------------------------------------------------
//!Generates a random 32bit unsigned int
// -----------------------------------------------------------------------------
unsigned int RandomUInt(void);

// -----------------------------------------------------------------------------
//! Generates a random real number on [0,1]-real-interval
// -----------------------------------------------------------------------------
float RandomUnitFloat(void);

// -----------------------------------------------------------------------------
//! Generates a random real number on [0,1)-real-interval
// -----------------------------------------------------------------------------
float RandomUnitOpenFloat(void);

// -----------------------------------------------------------------------------
//! Generates a random real number on [-1,1]
// -----------------------------------------------------------------------------
inline float RandomSymmetricFloat(void)
{
    return (2.0f*RandomUnitFloat() - 1.0f);
}

// -----------------------------------------------------------------------------
//! Generates a random real number on [-min, max]
// -----------------------------------------------------------------------------
inline float RandomIntervalFloat(float fMin, float fMax)
{
    return fMin+(fMax-fMin)*((float)RandomUnitFloat());
}
// -----------------------------------------------------------------------------

} // end namespace: Spark

#endif // endif: DG_RANDOM_H
