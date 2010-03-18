
//----------------------------------------------------------------------------
template <class ClassType>
SpReference<ClassType>::SpReference (ClassType* pkObject)
{
    m_pkPointer = pkObject;
    if ( m_pkPointer )
        m_pkPointer->addSpReference();
}
//----------------------------------------------------------------------------
template <class ClassType>
SpReference<ClassType>::SpReference (const SpReference& rkSpReference)
{
    m_pkPointer = rkSpReference.m_pkPointer;
    if ( m_pkPointer )
        m_pkPointer->addSpReference();
}
//----------------------------------------------------------------------------
template <class ClassType>
SpReference<ClassType>::~SpReference ()
{
    if ( m_pkPointer )
        m_pkPointer->removeSpReference();
}
//----------------------------------------------------------------------------
template <class ClassType>
SpReference<ClassType>::operator ClassType* () const
{
    return m_pkPointer;
}
//----------------------------------------------------------------------------
template <class ClassType>
ClassType& SpReference<ClassType>::operator* () const
{
    return *m_pkPointer;
}
//----------------------------------------------------------------------------
template <class ClassType>
ClassType* SpReference<ClassType>::operator-> () const
{
    return m_pkPointer;
}
//----------------------------------------------------------------------------
template <class ClassType>
SpReference<ClassType>& SpReference<ClassType>::operator= (const SpReference& rkSpReference)
{
    if ( m_pkPointer != rkSpReference.m_pkPointer )
    {
        if ( rkSpReference.m_pkPointer )
            rkSpReference.m_pkPointer->addSpReference();

        if ( m_pkPointer )
            m_pkPointer->removeSpReference();

        m_pkPointer = rkSpReference.m_pkPointer;
    }
    return *this;
}
//----------------------------------------------------------------------------
template <class ClassType>
SpReference<ClassType>& SpReference<ClassType>::operator= (ClassType* pkObject)
{
    if ( m_pkPointer != pkObject )
    {
        if ( pkObject )
            pkObject->addSpReference();

        if ( m_pkPointer )
            m_pkPointer->removeSpReference();

        m_pkPointer = pkObject;
    }
    return *this;
}
//----------------------------------------------------------------------------
template <class ClassType>
bool SpReference<ClassType>::operator== (ClassType* pkObject) const
{
    return ( m_pkPointer == pkObject );
}
//----------------------------------------------------------------------------
template <class ClassType>
bool SpReference<ClassType>::operator!= (ClassType* pkObject) const
{
    return ( m_pkPointer != pkObject );
}
//----------------------------------------------------------------------------
template <class ClassType>
bool SpReference<ClassType>::operator== (const SpReference& rkSpReference) const
{
    return ( m_pkPointer == rkSpReference.m_pkPointer );
}
//----------------------------------------------------------------------------
template <class ClassType>
bool SpReference<ClassType>::operator!= (const SpReference& rkSpReference) const
{
    return ( m_pkPointer != rkSpReference.m_pkPointer );
}
//----------------------------------------------------------------------------
