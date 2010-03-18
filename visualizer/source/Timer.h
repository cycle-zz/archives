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

#ifndef DG_TIMER_H
#define DG_TIMER_H

#include "DataTypes.h"
#include <memory>

// ----------------------------------------------------------------------------

namespace dg
{

// #############################################################################
// Basic Timer for profiling and retrieving time info
// #############################################################################

class Timer
{
public:

	enum TimerState
	{
		TS_OFF,
		TS_ON,
		TS_HOLD,
		TS_COUNT
	};

	Timer();
	~Timer();

	// operations
	void start();
	void stop();

	void suspend();
	void resume();
	void reset();
	void count();

	Real elapsedTime();
	UInt elapsedCount();
	UInt elapsedHours();
	UInt elapsedMinutes();
	UInt elapsedSeconds();
	UInt elapsedMilliseconds();

	UInt seconds();
	UInt milliseconds();
	
private:

	static UInt s_uiSecondsFrequency;
	static UInt s_uiMillisecondsFrequency;
	static Real s_fInvSecFrequency;

	// state data members
	UInt m_uiStartTime;
	UInt m_uiStopTime;
	UInt m_uiTimeDelta;
	UInt m_uiElapsedCount;
	TimerState m_eState;
	
	static void setupTimerFrequency();
	UInt samplePerformanceCounter();

	// restricted methods
	Timer(const Timer& Src);
	Timer& operator=(const Timer& Src);
};

//******************************************************************************

#include "Timer.inc"

} // end namespace: dg

//******************************************************************************
#endif  // end file: Timer.h

