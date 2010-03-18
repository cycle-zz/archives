#include "SpStreamOperator.h"
#include "SpGlHeaders.h"

using namespace Spark;

// -----------------------------------------------------------------------------
SpStreamOperator::SpStreamOperator()
	: SpStreamOutput(), SpStreamInput()
{
	// EMPTY!
}
//----------------------------------------------------------------------------
SpStreamOperator::~SpStreamOperator()
{
	// EMPTY!
}
//----------------------------------------------------------------------------
void SpStreamOperator::setInputStream(SpStreamInput * pkInputStream)
{
	SpStreamOutput::setInputStream(pkInputStream);
	m_bHasChanged = true;
}
//----------------------------------------------------------------------------
bool SpStreamOperator::hasChanged()
{
	if (m_bHasChanged)
		return true;

	if (m_pkInputStream)
	{
		m_bHasChanged = m_pkInputStream->hasChanged();
	}

	return m_bHasChanged;
}
//----------------------------------------------------------------------------
bool SpStreamOperator::sendOutputToBuffer(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy)
{
	if(m_bHasChanged)
		return compute(pkBuffer, pkCopy);

	return true;
}
//----------------------------------------------------------------------------
bool SpStreamOperator::compute(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy)
{
	bool bSuccess = true;

	// Activate the output steam, if necessary
	if(!enableOutputStream(pkBuffer, pkCopy))
		bSuccess = false;

	// Set the necessary state for the stream operation
	if(!setupState(pkBuffer, pkCopy))
		bSuccess = false;

	// Perform the stream operation
	if(!processStream(pkBuffer, pkCopy))
		bSuccess = false;

	// Put the results of the operation into the output stream.
	if(!updateOutputStream(pkBuffer, pkCopy))
		bSuccess = false;

	// Reset state
	if(!resetState(pkBuffer, pkCopy))
		bSuccess = false;

	// Deactivate the output stream, if necessary
	if(!disableOutputStream(pkBuffer, pkCopy))
		bSuccess = false;

	return bSuccess;
}
//----------------------------------------------------------------------------
bool SpStreamOperator::enableOutputStream(SpStreamBuffer*, SpStreamFeedback*)
{
	return true;
}
//----------------------------------------------------------------------------
bool SpStreamOperator::setupState(SpStreamBuffer*, SpStreamFeedback*)
{
	return true;
}
//----------------------------------------------------------------------------
bool SpStreamOperator::processStream(SpStreamBuffer*, SpStreamFeedback*)
{
	return true;
}
//----------------------------------------------------------------------------
bool SpStreamOperator::updateOutputStream(SpStreamBuffer*, SpStreamFeedback*)
{
	return true;
}
//----------------------------------------------------------------------------
bool SpStreamOperator::resetState(SpStreamBuffer*, SpStreamFeedback*)
{
	return true;
}
//----------------------------------------------------------------------------
bool SpStreamOperator::disableOutputStream(SpStreamBuffer*, SpStreamFeedback*)
{
	return true;
}
//----------------------------------------------------------------------------
