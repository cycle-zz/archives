#include "SpGlHeaders.h"
#include "SpGlslFragmentProgram.h"
#include "SpResourcePath.h"
#include "SpString.h"

using namespace Spark;

//----------------------------------------------------------------------------
SpGlslFragmentProgram::SpGlslFragmentProgram (
	const char* acSource)
	: SpGpuProgram(GPU_GLSL_FRAGMENT_PROGRAM)
{
	setSource(acSource);
}
//----------------------------------------------------------------------------
SpGlslFragmentProgram::SpGlslFragmentProgram ()
    : SpGpuProgram(GPU_GLSL_FRAGMENT_PROGRAM)
{
    // EMPTY!
}
//----------------------------------------------------------------------------
int SpGlslFragmentProgram::getParameterRegister( const char* acName )
{
	// get the current program handle, if there is one
	GLuint uiUserData = 0;
	getUserData(&uiUserData, sizeof(GLuint));

	// return if program has not been compiled
	if(!uiUserData)
		return -1;

	// request a uniform location to use as the register
	int iRegister = -1;
	iRegister = glGetUniformLocationARB( uiUserData, acName );

	// return the register index
	return iRegister;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter1i(
	const char* acName, int iX)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform1iARB( iRegister, iX );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter2i(
	const char* acName, int iX, int iY)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform2iARB( iRegister, iX, iY );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter3i(
	const char* acName, int iX, int iY, int iZ)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform3iARB( iRegister, iX, iY, iZ );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter4i(
	const char* acName, int iX, int iY, int iZ, int iW)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform4iARB( iRegister, iX, iY, iZ, iW );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter1iv(
	const char* acName, const int *aiValues, int iCount)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform1ivARB( iRegister, iCount, aiValues );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter2iv(
	const char* acName, const int *aiValues, int iCount)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform2ivARB( iRegister, iCount, aiValues );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter3iv(
	const char* acName, const int *aiValues, int iCount)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform3ivARB( iRegister, iCount, aiValues );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter4iv(
	const char* acName, const int *aiValues, int iCount)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform4ivARB( iRegister, iCount, aiValues );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter1f(
	const char* acName, float fX)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform1fARB( iRegister, fX );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter2f(
	const char* acName, float fX, float fY)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform2fARB( iRegister, fX, fY );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter3f(
	const char* acName, float fX, float fY, float fZ)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform3fARB( iRegister, fX, fY, fZ );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter4f(
	const char* acName, float fX, float fY, float fZ, float fW)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform4fARB( iRegister, fX, fY, fZ, fW );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter1fv(
	const char* acName, const float *afValues, int iCount)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform1fvARB( iRegister, iCount, afValues );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter2fv(
	const char* acName, const float *afValues, int iCount)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform2fvARB( iRegister, iCount, afValues );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter3fv(
	const char* acName, const float *afValues, int iCount)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform3fvARB( iRegister, iCount, afValues );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setParameter4fv(
	const char* acName, const float *afValues, int iCount)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniform4fvARB( iRegister, iCount, afValues );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setMatrixParameter2fv(
	const char* acName, const float *afValues, int iCount)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniformMatrix2fvARB( iRegister, iCount, GL_FALSE, afValues );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setMatrixParameter3fv(
	const char* acName, const float *afValues, int iCount)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniformMatrix3fvARB( iRegister, iCount, GL_FALSE, afValues );
	return true;
}
//----------------------------------------------------------------------------
bool SpGlslFragmentProgram::setMatrixParameter4fv(
	const char* acName, const float *afValues, int iCount)
{
	// get a register for the parameter
	int iRegister = getParameterRegister( acName );
	if(iRegister < 0) return false;

	// assign the parameter to the given register
	glUniformMatrix4fvARB( iRegister, iCount, GL_FALSE, afValues );
	return true;
}
//----------------------------------------------------------------------------
