//----------------------------------------------------------------------------
inline const char* SpParameter::getName () const
{
    return m_acName;
}
//----------------------------------------------------------------------------
inline unsigned int SpParameter::getRegister () const
{
    return m_uiRegister;
}
//----------------------------------------------------------------------------
inline bool SpParameter::hasChanged() const
{
	return m_bHasChanged;
}
//----------------------------------------------------------------------------
inline void SpParameter::setChanged(bool bChanged)
{
	m_bHasChanged = bChanged;
}
//----------------------------------------------------------------------------
inline const void* SpParameter::getData() const
{
	return m_pvData;
}
//----------------------------------------------------------------------------
inline int SpParameter::getSize( SpParameter::Type eType) const
{
	int iSize = 0;
	switch (eType)
	{
		case SpParameter::PT_BOOL:
			iSize = 1;
			break;
        case SpParameter::PT_INT:
			iSize = 1;
			break;
        case SpParameter::PT_FLOAT:
			iSize = 1;
			break;
        case SpParameter::PT_IVEC2:
			iSize = 2;
			break;
        case SpParameter::PT_IVEC3:
			iSize = 3;
			break;
        case SpParameter::PT_IVEC4:
			iSize = 4;
			break;
		case SpParameter::PT_VEC2:
			iSize = 2;
			break;
        case SpParameter::PT_VEC3:
			iSize = 3;
			break;
        case SpParameter::PT_VEC4:
			iSize = 4;
			break;
        case SpParameter::PT_MAT2:
			iSize = 4;
			break;
        case SpParameter::PT_MAT3:
			iSize = 9;
			break;
        case SpParameter::PT_MAT4:
			iSize = 16;
			break;
		default:
			iSize = 0;
    }
    return iSize;
}
//----------------------------------------------------------------------------
inline int SpParameter::getSize () const
{
    return m_iSize;
}
//----------------------------------------------------------------------------
inline int SpParameter::getCount () const
{
    return m_iCount;
}
//----------------------------------------------------------------------------
inline SpParameter::Type SpParameter::getType () const
{
    return m_eType;
}
//----------------------------------------------------------------------------
inline SpParameter::Option SpParameter::getOption () const
{
    return m_eOption;
}
//----------------------------------------------------------------------------
inline void SpParameter::setRegister (unsigned int uiRegister)
{
    m_uiRegister = uiRegister;
}
//----------------------------------------------------------------------------
inline void SpParameter::setOption (SpParameter::Option eOption)
{
    m_eOption = eOption;
}
//----------------------------------------------------------------------------
inline bool SpParameter::isNamed (const char* acName) const
{
    if ( ( !m_acName ) || ( !acName ) )
        return false;

    return ( !strcmp(acName,m_acName) );
}
//----------------------------------------------------------------------------
inline bool SpParameter::isBoolean() const
{
	switch (m_eType)
	{
        case SpParameter::PT_BOOL:
			return true;
			break;
		default:
			return false;
			break;
    }
    return false;
}
//----------------------------------------------------------------------------
inline bool SpParameter::isInteger() const
{
	switch (m_eType)
	{
        case SpParameter::PT_INT:
        case SpParameter::PT_IVEC2:
        case SpParameter::PT_IVEC3:
        case SpParameter::PT_IVEC4:
			return true;
			break;
		default:
			return false;
			break;
    }
    return false;
}
//----------------------------------------------------------------------------
inline bool SpParameter::isFloat() const
{
	switch (m_eType)
	{
        case SpParameter::PT_FLOAT:
		case SpParameter::PT_VEC2:
        case SpParameter::PT_VEC3:
        case SpParameter::PT_VEC4:
        case SpParameter::PT_MAT2:
        case SpParameter::PT_MAT3:
        case SpParameter::PT_MAT4:
			return true;
			break;
		default:
			return false;
			break;
    }
    return false;
}
//----------------------------------------------------------------------------
