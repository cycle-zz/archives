// #############################################################################
// # Messages.cpp - Output functions for message handling
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

#include "Messages.h"

#include <cstdio>
#include <cstdlib>

using namespace dg;

//******************************************************************************
static void ProcessError(
    const char * acFormat,
    va_list vArgs,
    const char * acMessage,
    ErrorType eErrorType )
{

#ifndef WIN32

	// osx/unix/linux specific
	char * acErrorBuffer;
	vasprintf( &acErrorBuffer, acFormat, vArgs );

#else

	// win32 specific
	char acErrorBuffer[ 2048 ];
	_vsnprintf( acErrorBuffer, sizeof( acErrorBuffer ), acFormat, vArgs );

#endif

	// Report error
	switch ( eErrorType )
	{
		case ERROR_IGNORE:
			return ;

		case ERROR_CONTINUE:
			fprintf( stderr, "%s %s\n", acMessage, acErrorBuffer );
			break;
			
		case ERROR_ABORT:
			fprintf( stderr, "%s %s\n", acMessage, acErrorBuffer );
			exit( 1 );
	}

#ifndef WIN32

	// osx/unix/linux/etc specific
	free( acErrorBuffer );

#endif

}
//******************************************************************************
inline void dg::Info( const char * acFormat, ... )
{
	va_list vArgs;
	va_start( vArgs, acFormat );
	ProcessError( acFormat, vArgs, "", ERROR_CONTINUE );
	va_end( vArgs );
}
//******************************************************************************
inline void dg::Notice( const char * acFormat, ... )
{
	va_list vArgs;
	va_start( vArgs, acFormat );
	ProcessError( acFormat, vArgs, "NOTICE:", ERROR_CONTINUE );
	va_end( vArgs );
}
//******************************************************************************
inline void dg::Warning( const char * acFormat, ... )
{
	va_list vArgs;
	va_start( vArgs, acFormat );
	ProcessError( acFormat, vArgs, "WARNING:", ERROR_CONTINUE );
	va_end( vArgs );
}
//******************************************************************************
inline void dg::Error( const char * acFormat, ... )
{
	va_list vArgs;
	va_start( vArgs, acFormat );
	ProcessError( acFormat, vArgs, "ERROR:", ERROR_CONTINUE );
	va_end( vArgs );
}
//******************************************************************************
inline void dg::Severe( const char * acFormat, ... )
{
	va_list vArgs;
	va_start( vArgs, acFormat );
	ProcessError( acFormat, vArgs, "FATAL ERROR:", ERROR_ABORT );
	va_end( vArgs );
}
//******************************************************************************

