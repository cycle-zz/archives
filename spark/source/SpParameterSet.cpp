#include "SpParameterSet.h"

using namespace Spark;

//----------------------------------------------------------------------------
SpParameterSet::SpParameterSet ()
{
	// EMPTY!
}
//----------------------------------------------------------------------------
SpParameterSet::SpParameterSet (const SpParameterSet& rkOther)
{
	// Copy the reference counted shared objects (pointers)
    for (int i = 0; i < rkOther.size(); i++)
        m_kSpParameters.push_back(rkOther.retrieve(i));
}
//----------------------------------------------------------------------------
SpParameterSet::~SpParameterSet ()
{
	// EMPTY!
}
//----------------------------------------------------------------------------
void SpParameterSet::insert ( const SpParameter& rkSpParameter )
{
    for (int i = 0; i < (int)m_kSpParameters.size(); i++)
    {
        if ( m_kSpParameters[i]->isNamed( rkSpParameter.getName()) )
		{
			*m_kSpParameters[i] = rkSpParameter;
			return;
		}
    }

	m_kSpParameters.push_back(
		new SpParameter(rkSpParameter)
	);
}
//----------------------------------------------------------------------------
void SpParameterSet::insert ( const SpParameter* pkSpParameter )
{
    for (int i = 0; i < (int)m_kSpParameters.size(); i++)
    {
        if ( m_kSpParameters[i]->isNamed( pkSpParameter->getName()) )
		{
            *m_kSpParameters[i] = *pkSpParameter;
			return;
		}
    }

	m_kSpParameters.push_back(
		new SpParameter(pkSpParameter)
	);
}
//----------------------------------------------------------------------------
SpParameterPtr SpParameterSet::retrieve (const char* acName) const
{
    for (int i = 0; i < (int)m_kSpParameters.size(); i++)
    {
        if ( m_kSpParameters[i]->isNamed(acName) )
            return retrieve(i);
    }

    // none found
    return 0;
}
//----------------------------------------------------------------------------
