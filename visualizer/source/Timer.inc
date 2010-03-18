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

//******************************************************************************
inline Timer::~Timer()
{
	// EMPTY!
}
//******************************************************************************
inline void Timer::start()
{
	m_uiStartTime = samplePerformanceCounter();
	m_uiElapsedCount = 0;
	m_eState = TS_ON;
}
//******************************************************************************
inline void Timer::stop()
{
	//m_uiElapsedCount = elapsedCount();
	m_eState = TS_OFF;
}
//******************************************************************************
inline void Timer::suspend()
{
	if (m_eState == TS_ON)
	{
		m_uiElapsedCount = elapsedCount();
		m_eState = TS_HOLD;
	}
}
//******************************************************************************
inline void Timer::resume()
{
	if (m_eState == TS_HOLD)
	{
		// get the current time
		m_uiStartTime = samplePerformanceCounter();

		// roll the start time back by our previous delta
		m_uiStartTime -= m_uiTimeDelta;

		m_uiElapsedCount = 0;
		m_eState = TS_ON;
	}
}
//******************************************************************************
inline void Timer::reset()
{
	m_uiElapsedCount = 0;
	memset(&m_uiStartTime, 0, sizeof(m_uiStartTime));
	memset(&m_uiStopTime, 0, sizeof(m_uiStopTime));
	memset(&m_uiTimeDelta, 0, sizeof(m_uiTimeDelta));
	setupTimerFrequency();	
}
//----------------------------------------------------------------------------
inline void Timer::count()
{
    m_uiElapsedCount++;
}
//******************************************************************************
inline Real Timer::elapsedTime()
{
	if (m_eState != TS_ON)
	{
		return (Real)m_uiElapsedCount*s_fInvSecFrequency;
	}
	else
	{
		m_uiStopTime = samplePerformanceCounter();
		m_uiTimeDelta = m_uiStopTime - m_uiStartTime;

		Real fReportedTime = (Real)m_uiTimeDelta*s_fInvSecFrequency;

		return(fReportedTime);
	}
}
//******************************************************************************
inline UInt Timer::elapsedHours()
{
	return elapsedMinutes() / 60;
}
//******************************************************************************
inline UInt Timer::elapsedMinutes()
{
	return elapsedSeconds() / 60;
}
//******************************************************************************
inline UInt Timer::elapsedSeconds()
{
	if (m_eState != TS_ON)
	{
		return m_uiElapsedCount/s_uiSecondsFrequency;
	}
	else
	{
//		Real fElapsed = elapsedTime();
//		return( (UInt) fElapsed );
		
		m_uiStopTime = samplePerformanceCounter();
		m_uiTimeDelta = m_uiStopTime - m_uiStartTime;

		UInt iReportedTime = m_uiTimeDelta/s_uiSecondsFrequency;

		return(iReportedTime);
	}
}
//******************************************************************************
inline UInt Timer::elapsedMilliseconds()
{

	if (m_eState != TS_ON)
	{
		return m_uiElapsedCount/s_uiMillisecondsFrequency;
	}
	else
	{
//		Real fElapsed = elapsedTime();
//		return( (UInt) fElapsed/1000 );

		m_uiStopTime = samplePerformanceCounter();
		m_uiTimeDelta = m_uiStopTime - m_uiStartTime;

		UInt uiReportedTime = m_uiTimeDelta/s_uiMillisecondsFrequency;

		return(uiReportedTime);
	}
}
//******************************************************************************
inline UInt Timer::elapsedCount()
{
	return m_uiElapsedCount;
}
//******************************************************************************
inline UInt Timer::seconds()
{
	return samplePerformanceCounter()/s_uiSecondsFrequency;
}
//******************************************************************************
inline UInt Timer::milliseconds()
{
	return samplePerformanceCounter()/s_uiMillisecondsFrequency;
}
//******************************************************************************

