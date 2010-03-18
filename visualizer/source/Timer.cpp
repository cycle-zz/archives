// #############################################################################
// # Timer.cpp  -  Basic Timer for profiling and gathering time info
// #
// # Created 	: Sat Jan 10 2004
// # Copyright	: (C) 2004 by Derek Gerstmann
// # Email	: dgerstma@acm.org
// #
// #############################################################################

// ===================================================================
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
// ===================================================================


#include "Timer.h"

#ifdef __APPLE__
#include <ctime>
#else
#include <sys/time.h>
#endif


using namespace dg;

//******************************************************************************
UInt Timer::s_uiSecondsFrequency = 0;
UInt Timer::s_uiMillisecondsFrequency = 0;
Real Timer::s_fInvSecFrequency = 0.0f;
//******************************************************************************
Timer::Timer():
	m_uiElapsedCount(0),
	m_eState(TS_OFF)
{
	setupTimerFrequency();
	reset();
}
//******************************************************************************
void Timer::setupTimerFrequency()
{
	if (!s_uiSecondsFrequency)
	{

#ifdef WIN32
		LARGE_INTEGER iFrequency;
		QueryPerformanceFrequency(&iFrequency);

		s_uiSecondsFrequency = iFrequency.LowPart;
		s_uiMillisecondsFrequency = iFrequency.LowPart/1000;
#else
		struct timeval kFrequency;
		struct timezone kTZ;

	gettimeofday(&kFrequency, &kTZ);
	s_uiSecondsFrequency = 1000000;
	s_uiMillisecondsFrequency = 1000;
#endif

		s_fInvSecFrequency = 1.0f/(Real)s_uiSecondsFrequency;
	}
}
//******************************************************************************
UInt Timer::samplePerformanceCounter()
{

#ifdef WIN32
		LARGE_INTEGER iSample;
		QueryPerformanceCounter(&iSample);
		return iSample.LowPart;
#else
		struct timeval kSample;
		struct timezone kTZ;

	gettimeofday(&kSample, &kTZ);
		return kSample.tv_sec * 1000000 + kSample.tv_usec;
#endif
}
//******************************************************************************
// end file: Timer.cpp
