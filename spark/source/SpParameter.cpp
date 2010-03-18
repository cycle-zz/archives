#include "SpParameter.h"

using namespace Spark;

//----------------------------------------------------------------------------
SpParameter::SpParameter ()
{
	m_bHasChanged = true;
	m_acName = NULL;
	m_uiRegister = 0;
	m_iSize = 0;
	m_pvData = NULL;
	m_iCount = 0;
	m_eType = PT_NONE;
	m_eOption = PO_NONE;
}
//----------------------------------------------------------------------------
SpParameter::SpParameter (const char* acName, SpParameter::Type eType,
	unsigned int uiRegister, int iCount, SpParameter::Option eOption)
{
	m_acName = new char[strlen(acName)+1];
	strcpy(m_acName,acName);

	m_bHasChanged = true;
	m_uiRegister = uiRegister;
	m_iCount = iCount;
	m_eType = eType;
	m_eOption = eOption;
	m_iSize = getSize(eType);
	m_pvData = NULL;

	setData((void*)NULL, m_iCount, m_eType);
}
//----------------------------------------------------------------------------
SpParameter::SpParameter (
	const char* acName,
	const float* afData,
	int iCount,
	SpParameter::Type eType,
	unsigned int uiRegister,
	SpParameter::Option eOption)
{
	m_acName = new char[strlen(acName)+1];
	strcpy(m_acName,acName);

	m_bHasChanged = true;
	m_uiRegister = uiRegister;
	m_iCount = iCount;
	m_eType = eType;
	m_eOption = eOption;
	m_iSize = getSize(eType);
	m_pvData = NULL;

	setData(afData, iCount, eType);
}
//----------------------------------------------------------------------------
SpParameter::SpParameter (
	const char* acName,
	bool bEnable,
	unsigned int uiRegister,
	SpParameter::Option eOption)
{
	m_acName = new char[strlen(acName)+1];
	strcpy(m_acName,acName);

	m_bHasChanged = true;
	m_uiRegister = uiRegister;
	m_eOption = eOption;
	m_pvData = NULL;

	static int aiData[1];
	aiData[0] = bEnable ? 1 : 0;
	setData( aiData, m_iCount, m_eType );
}
//----------------------------------------------------------------------------
SpParameter::SpParameter (
	const char* acName,
	int iX,
	unsigned int uiRegister,
	SpParameter::Option eOption)
{
	m_acName = new char[strlen(acName)+1];
	strcpy(m_acName,acName);

	m_bHasChanged = true;
	m_uiRegister = uiRegister;
	m_eOption = eOption;
	m_pvData = NULL;

	setData(iX);
}
//----------------------------------------------------------------------------
SpParameter::SpParameter (
	const char* acName,
	int iX,
	int iY,
	unsigned int uiRegister,
	SpParameter::Option eOption)
{
	m_acName = new char[strlen(acName)+1];
	strcpy(m_acName,acName);

	m_bHasChanged = true;
	m_uiRegister = uiRegister;
	m_eOption = eOption;
	m_pvData = NULL;

	setData(iX, iY);
}
//----------------------------------------------------------------------------
SpParameter::SpParameter (
	const char* acName,
	int iX,
	int iY,
	int iZ,
	unsigned int uiRegister,
	SpParameter::Option eOption)
{
	m_acName = new char[strlen(acName)+1];
	strcpy(m_acName,acName);

	m_bHasChanged = true;
	m_uiRegister = uiRegister;
	m_eOption = eOption;
	m_pvData = NULL;

	setData(iX, iY, iZ);
}
//----------------------------------------------------------------------------
SpParameter::SpParameter (
	const char* acName,
	float fX,
	unsigned int uiRegister,
	SpParameter::Option eOption)
{
	m_acName = new char[strlen(acName)+1];
	strcpy(m_acName,acName);

	m_bHasChanged = true;
	m_uiRegister = uiRegister;
	m_eOption = eOption;
	m_pvData = NULL;

	setData(fX);
}
//----------------------------------------------------------------------------
SpParameter::SpParameter (
	const char* acName,
	float fX,
	float fY,
	unsigned int uiRegister,
	SpParameter::Option eOption)
{
	m_acName = new char[strlen(acName)+1];
	strcpy(m_acName,acName);

	m_bHasChanged = true;
	m_uiRegister = uiRegister;
	m_eOption = eOption;
	m_pvData = NULL;

	setData(fX,fY);
}
//----------------------------------------------------------------------------
SpParameter::SpParameter (
	const char* acName,
	float fX,
	float fY,
	float fZ,
	unsigned int uiRegister,
	SpParameter::Option eOption)
{
	m_acName = new char[strlen(acName)+1];
	strcpy(m_acName,acName);

	m_bHasChanged = true;
	m_uiRegister = uiRegister;
	m_eOption = eOption;
	m_pvData = NULL;

	setData(fX,fY,fZ);
}
//----------------------------------------------------------------------------
SpParameter::SpParameter (const SpParameter* pkSpParameter)
{
	if ( !pkSpParameter )
		return;

	m_acName = NULL;
	m_pvData = NULL;
	*this = *pkSpParameter;
}
//----------------------------------------------------------------------------
SpParameter::SpParameter (const SpParameter& rkConst)
{
	m_acName = NULL;
	m_pvData = NULL;
	*this = rkConst;
}
//----------------------------------------------------------------------------
SpParameter& SpParameter::operator= (const SpParameter& rkConst)
{
	delete[] m_acName;
	if ( rkConst.m_acName )
	{
		m_acName = new char[strlen(rkConst.m_acName)+1];
		strcpy(m_acName,rkConst.m_acName);
	}
	else
	{
		m_acName = NULL;
	}

	m_bHasChanged = true;
	m_uiRegister = rkConst.m_uiRegister;
	m_iSize = rkConst.m_iSize;
	m_iCount = rkConst.m_iCount;
	m_eType = rkConst.m_eType;
	m_eOption = rkConst.m_eOption;

	setData( rkConst.m_pvData, m_iCount, m_eType );
	return *this;
}
//----------------------------------------------------------------------------
SpParameter::~SpParameter ()
{
	delete[] m_acName;
	destroy();
}
//----------------------------------------------------------------------------
void SpParameter::destroy()
{
	if(isBoolean())
	{
		bool* abData = static_cast<bool*>(m_pvData);

		if(m_iCount > 1)
			delete[] abData;
		else
			delete abData;

		m_pvData = NULL;
		m_bHasChanged = true;

	}
	else if(isInteger())
	{
		int* aiData = static_cast<int*>(m_pvData);

		if(m_iCount > 1)
			delete[] aiData;
		else
			delete aiData;

		m_pvData = NULL;
		m_bHasChanged = true;

	}
	else if(isFloat())
	{
		float* afData = static_cast<float*>(m_pvData);

		if(m_iCount > 1)
			delete[] afData;
		else
			delete afData;

		m_pvData = NULL;
		m_bHasChanged = true;

	}
}
//----------------------------------------------------------------------------
 void SpParameter::setData (
	const void* pvSourceData, int iCount, SpParameter::Type eType)
{
	destroy();

	m_eType = eType;
	m_iSize = getSize( eType );
	m_iCount = iCount;

	if(isBoolean())
	{
		bool* abData = new bool[m_iCount*m_iSize];

		if(!pvSourceData)
			memset(abData, 0, sizeof(bool) * m_iCount * m_iSize);
		else
			memcpy(abData, pvSourceData, sizeof(bool) * m_iCount * m_iSize);

		m_pvData = static_cast<void*>(abData);
	}
	else if(isInteger())
	{
		int* aiData = new int[m_iCount*m_iSize];

		if(!pvSourceData)
			memset(aiData, 0, sizeof(int) * m_iCount * m_iSize);
		else
			memcpy(aiData, pvSourceData, sizeof(int) * m_iCount * m_iSize);

		m_pvData = static_cast<void*>(aiData);
	}
	else if(isFloat())
	{
		float* afData = new float[m_iCount*m_iSize];

		if(!pvSourceData)
			memset(afData, 0, sizeof(float) * m_iCount * m_iSize);
		else
			memcpy(afData, pvSourceData,sizeof(float)*m_iCount*m_iSize);

		m_pvData = static_cast<void*>(afData);
	}
}
//----------------------------------------------------------------------------
void SpParameter::setData (const float akData[2][2])
{
	destroy();

	m_eType = PT_MAT2;
	m_iSize = 4;
	m_iCount = 1;

	float* afData = new float[m_iCount*m_iSize];

	afData[ 0] = akData[0][0];
	afData[ 1] = akData[0][1];

	afData[ 2] = akData[1][0];
	afData[ 3] = akData[1][1];

	m_pvData = static_cast<void*>(afData);
}
//----------------------------------------------------------------------------
void SpParameter::setData (const float akData[3][3])
{
	destroy();

	m_eType = PT_MAT3;
	m_iSize = 9;
	m_iCount = 1;

	float* afData = new float[m_iCount*m_iSize];

	afData[ 0] = akData[0][0];
	afData[ 1] = akData[0][1];
	afData[ 2] = akData[0][2];

	afData[ 3] = akData[1][0];
	afData[ 4] = akData[1][1];
	afData[ 5] = akData[1][2];

	afData[ 6] = akData[2][0];
	afData[ 7] = akData[2][1];
	afData[ 8] = akData[2][2];

	m_pvData = static_cast<void*>(afData);
}
//----------------------------------------------------------------------------
void SpParameter::setData (const float akData[4][4])
{
	destroy();

	m_eType = PT_MAT4;
	m_iSize = 16;
	m_iCount = 1;

	float* afData = new float[m_iCount*m_iSize];

	afData[ 0] = akData[0][0];
	afData[ 1] = akData[0][1];
	afData[ 2] = akData[0][2];
	afData[ 3] = akData[0][3];

	afData[ 4] = akData[1][0];
	afData[ 5] = akData[1][1];
	afData[ 6] = akData[1][2];
	afData[ 7] = akData[1][3];

	afData[ 8] = akData[2][0];
	afData[ 9] = akData[2][1];
	afData[10] = akData[2][2];
	afData[11] = akData[2][3];

	afData[12] = akData[3][0];
	afData[13] = akData[3][1];
	afData[14] = akData[3][2];
	afData[15] = akData[3][3];

	m_pvData = static_cast<void*>(afData);
}
//----------------------------------------------------------------------------
 void SpParameter::setData (bool bEnable)
{
	destroy();

	m_eType = PT_BOOL;
	m_iSize = 1;
	m_iCount = 1;

	bool* abData = new bool[m_iCount*m_iSize];

	abData[0] = bEnable;

	m_pvData = static_cast<void*>(abData);
}
//----------------------------------------------------------------------------
 void SpParameter::setData (int iX)
{
	destroy();

	m_eType = PT_INT;
	m_iSize = 1;
	m_iCount = 1;

	int* aiData = new int[m_iCount*m_iSize];

	aiData[0] = iX;

	m_pvData = static_cast<void*>(aiData);
}
//----------------------------------------------------------------------------
void SpParameter::setData (int iX, int iY)
{
	destroy();

	m_eType = PT_IVEC2;
	m_iSize = 2;
	m_iCount = 1;

	int* aiData = new int[m_iCount*m_iSize];

	aiData[0] = iX;
	aiData[1] = iY;

	m_pvData = static_cast<void*>(aiData);
}
//----------------------------------------------------------------------------
 void SpParameter::setData (int iX, int iY, int iZ)
{
	destroy();

	m_eType = PT_IVEC3;
	m_iSize = 3;
	m_iCount = 1;

	int* aiData = new int[m_iCount*m_iSize];

	aiData[0] = iX;
	aiData[1] = iY;
	aiData[2] = iZ;

	m_pvData = static_cast<void*>(aiData);
}
//----------------------------------------------------------------------------
void SpParameter::setData (int iX, int iY, int iZ, int iW)
{
	destroy();

	m_eType = PT_IVEC4;
	m_iSize = 4;
	m_iCount = 1;

	int* aiData = new int[m_iCount*m_iSize];

	aiData[0] = iX;
	aiData[1] = iY;
	aiData[2] = iZ;
	aiData[3] = iW;

	m_pvData = static_cast<void*>(aiData);
}
//----------------------------------------------------------------------------
 void SpParameter::setData (float fX)
{
	destroy();

	m_eType = PT_FLOAT;
	m_iSize = 1;
	m_iCount = 1;

	float* afData = new float[m_iCount*m_iSize];

	afData[0] = fX;

	m_pvData = static_cast<void*>(afData);
}
//----------------------------------------------------------------------------
 void SpParameter::setData (float fX, float fY)
{
	destroy();

	m_eType = PT_VEC2;
	m_iSize = 2;
	m_iCount = 1;

	float* afData = new float[m_iCount*m_iSize];

	afData[0] = fX;
	afData[1] = fY;

	m_pvData = static_cast<void*>(afData);
}
//----------------------------------------------------------------------------
 void SpParameter::setData (float fX, float fY, float fZ)
{
	destroy();

	m_eType = PT_VEC3;
	m_iSize = 3;
	m_iCount = 1;

	float* afData = new float[m_iCount*m_iSize];

	afData[0] = fX;
	afData[1] = fY;
	afData[2] = fZ;

	m_pvData = static_cast<void*>(afData);
}
//----------------------------------------------------------------------------
 void SpParameter::setData (float fX, float fY, float fZ, float fW)
{
	destroy();

	m_eType = PT_VEC4;
	m_iSize = 4;
	m_iCount = 1;

	float* afData = new float[m_iCount*m_iSize];

	afData[0] = fX;
	afData[1] = fY;
	afData[2] = fZ;
	afData[3] = fW;

	m_pvData = static_cast<void*>(afData);
}
//----------------------------------------------------------------------------
