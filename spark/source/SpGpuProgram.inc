//----------------------------------------------------------------------------
inline char* SpGpuProgram::getSource ()
{
    return m_acSource;
}
//----------------------------------------------------------------------------
inline unsigned int SpGpuProgram::getLength()
{
	return m_uiLength;
}
//----------------------------------------------------------------------------
inline SpGpuProgram::Type SpGpuProgram::getType () const
{
    return m_eType;
}
//----------------------------------------------------------------------------
inline void SpGpuProgram::setUserData (const void* pvData, int iSize)
{
    memcpy(m_acUserData,pvData,iSize*sizeof(char));
}
//----------------------------------------------------------------------------
inline void SpGpuProgram::getUserData (void* pvData, int iSize) const
{
    memcpy(pvData,m_acUserData,iSize*sizeof(char));
}
//----------------------------------------------------------------------------
