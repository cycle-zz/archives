// #############################################################################
// # Timer.h  -  Basic Timer for profiling and retrieving time info
// #
// # Created 	: Sat Jan 10 2004
// # Copyright	: (C) 2004 by Derek Gerstmann
// # Email	: dgerstma@acm.org
// #
// #############################################################################

// ============================================================================
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
// ============================================================================

#ifndef SP_TIMER_H
#define SP_TIMER_H

#include <memory>

// ----------------------------------------------------------------------------

namespace Spark
{

// ----------------------------------------------------------------------------

//! Basic Timer for profiling and retrieving performance/time info
class SpTimer
{

//! Typedefs:
public:

	enum TimerState
	{
		TS_OFF,
		TS_ON,
		TS_HOLD,
		TS_COUNT
	};

//! Construction:
public:

	SpTimer();
	~SpTimer();

//! Operations:
public:

	void start();
	void stop();

	void suspend();
	void resume();
	void reset();
	void count();

	float elapsedTime();
	unsigned int elapsedCount();
	unsigned int elapsedHours();
	unsigned int elapsedMinutes();
	unsigned int elapsedSeconds();
	unsigned int elapsedMilliseconds();

	unsigned int seconds();
	unsigned int milliseconds();

//! Internal Data:
private:

	static unsigned int s_uiSecondsFrequency;
	static unsigned int s_uiMillisecondsFrequency;
	static float s_fInvSecFrequency;

	// state data members
	unsigned int m_uiStartTime;
	unsigned int m_uiStopTime;
	unsigned int m_uiTimeDelta;
	unsigned int m_uiElapsedCount;
	TimerState m_eState;

	static void setupTimerFrequency();
	unsigned int samplePerformanceCounter();

//! Restricted Methods:
private:

	// restricted methods
	SpTimer(const SpTimer& rkSrc);
	SpTimer& operator=(const SpTimer& rkSrc);
};

// ----------------------------------------------------------------------------

#include "SpTimer.inc"

// ----------------------------------------------------------------------------

} // end namespace: Spark

#endif  // end file: SpTimer.h

