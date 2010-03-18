#include "SpGpuProgram.h"

//----------------------------------------------------------------------------

using namespace Spark;

//----------------------------------------------------------------------------
SpGpuProgram::SpGpuProgram (SpGpuProgram::Type eType)
	:  m_eType(eType)
{
	memset(m_acUserData,0,8*sizeof(char));
	m_acSource = 0;
	m_uiLength = 0;
}
//----------------------------------------------------------------------------
SpGpuProgram::~SpGpuProgram ()
{
	delete[] m_acSource;
}
//----------------------------------------------------------------------------
void SpGpuProgram::setSource (const char* acSpGpuProgram)
{
	delete[] m_acSource;

	m_uiLength = (unsigned int) strlen(acSpGpuProgram);
	m_acSource = new char[m_uiLength+1];

	strcpy(m_acSource,acSpGpuProgram);
	m_acSource[m_uiLength] = 0;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter1i(
	const char*, int )
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter2i(
	const char*, int, int)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter3i(
	const char*, int, int, int)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter4i(
	const char*, int, int, int, int)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter1iv(
	const char*, const float *, int)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter2iv(
	const char*, const float *, int)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter3iv(
	const char*, const float *, int)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter4iv(
	const char*, const float *, int)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter1f(
	const char*, float)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter2f(
	const char*, float, float)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter3f(
	const char*, float, float, float)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter4f(
	const char*, float, float, float, float)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter1fv(
	const char*, const float *, int)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter2fv(
	const char*, const float *, int)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter3fv(
	const char*, const float *, int)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setParameter4fv(
	const char*, const float *, int)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setMatrixParameter2fv(
	const char*, const float *, int)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setMatrixParameter3fv(
	const char*, const float *, int)
{
	return false;
}
//----------------------------------------------------------------------------
bool SpGpuProgram::setMatrixParameter4fv(
	const char*, const float *, int)
{
	return false;
}
//----------------------------------------------------------------------------
