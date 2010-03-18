// #############################################################################
//! SpGlslManager.h : Static manager class for interfacing with GLSL
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

#ifndef SP_GLSL_MANAGER_H
#define SP_GLSL_MANAGER_H

#include "SpGpuProgram.h"
#include "SpResourcePath.h"

// ---------------------------------------------------------------------------

namespace Spark
{

// ---------------------------------------------------------------------------

class SpGlslVertexProgram;
class SpGlslFragmentProgram;

// ---------------------------------------------------------------------------
//! Static manager class for interfacing with GLSL
// ---------------------------------------------------------------------------
class SpGlslManager
{

//! Construction:
public:
	~SpGlslManager();

//! Operations:
public:

	//: Returns true if the program is successfully compiled
	static bool compile(SpGpuProgram* pkSpGpuProgram);

	//: Returns true if the program is successfully bound
	static bool bind(SpGpuProgram* pkSpGpuProgram);

	//: Returns true if the program is successfully enabled
	static bool enable( SpGpuProgram* pkSpGpuProgram );

	//: Returns true if the program is successfully disabled
	static bool disable( SpGpuProgram* pkSpGpuProgram );

	//: Returns true if the program is successfully destroyed
	static bool release(SpGpuProgram* pkSpGpuProgram);

	//: Returns true if the program is supported by the loader and the system
	static bool isSupported(const SpGpuProgram* pkSpGpuProgram);

	//: Returns NULL if invalid or nonexistant file
	static SpGpuProgram* loadFromFile(const char* acFilename, SpGpuProgram::Type);

	//: Returns NULL if invalid or nonexistant file
	static SpGlslVertexProgram* loadVertexProgramFromFile(const char* acFilename);

	//: Returns NULL if invalid or nonexistant file
	static SpGlslFragmentProgram* loadFragmentProgramFromFile(const char* acFilename);

	//: Outputs detailed error info for a given object
	static void printInfoLog(unsigned int uiHandle);

	//: Returns the current resource path used during load
	static SpResourcePath& searchpath();

	//: Initializes a minimal fragment program which passes texture data through
	static void enableTexturePassThrough(bool bIsRectangle=false);

	//: Initializes a minimal fragment program which passes color data through
	static void enableFragmentPassThrough();

	static void enableFragmentPrograms();
	static void enableVertexPrograms();
	static void disableFragmentPrograms();
	static void disableVertexPrograms();

//! Internal Data:
protected:

	//: Search path for loading program data
	static SpResourcePath ms_kSpResourcePath;

//! Static Data:
protected:

	static SpGpuProgram* ms_apkCurrent[SpGpuProgram::GPU_PROGRAM_COUNT];

//! Restricted:
private:

	SpGlslManager();
};

// ---------------------------------------------------------------------------

} 	// end namespace: Spark

#endif
