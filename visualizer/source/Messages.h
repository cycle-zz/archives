// #############################################################################
// # Messages.h - Output functions for message handling
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

#ifndef DG_MESSAGES_H
#define DG_MESSAGES_H

#include <cstdio>
#include <cstdarg>

//*****************************************************************************
#ifdef __GNUG__
#define PRINT_FUNC __attribute__ \
	((__format__ (__printf__, 1, 2)))
#else
#define PRINT_FUNC
#endif // __GNUG__

//*****************************************************************************

namespace dg
{

//*****************************************************************************
	
enum ErrorType
{
	ERROR_IGNORE,
	ERROR_CONTINUE,
	ERROR_ABORT	
};

extern void Info(const char * acMessage, ...) PRINT_FUNC;
extern void Notice(const char * acMessage, ...) PRINT_FUNC;
extern void Warning(const char * acMessage, ...) PRINT_FUNC;
extern void Error(const char * acMessage, ...) PRINT_FUNC;
extern void Severe(const char * acMessage, ...) PRINT_FUNC;

//*****************************************************************************

}

//*****************************************************************************

#endif // end DG_MESSAGES_H
