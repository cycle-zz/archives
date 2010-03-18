//----------------------------------------------------------------------------
inline SpParameterPtr SpParameterSet::retrieve (int iIndex) const
{
    return m_kSpParameters[iIndex];
}
//----------------------------------------------------------------------------
inline int SpParameterSet::size () const
{
    return (int)m_kSpParameters.size();
}
//----------------------------------------------------------------------------
