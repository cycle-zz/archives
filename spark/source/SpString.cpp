// headers
#include "SpString.h"

// ---------------------------------------------------------------------------

using namespace Spark;

// ---------------------------------------------------------------------------
// Static Declarations:
// ---------------------------------------------------------------------------
const SpString SpString::EMPTY = "";

// ---------------------------------------------------------------------------
// Construction:
// ---------------------------------------------------------------------------
SpString::SpString() : SpStringBase()
{
	// EMPTY!
}
// ---------------------------------------------------------------------------
SpString::SpString(const SpString& rkStr) :
	SpStringBase( static_cast< const SpStringBase& >(rkStr) )
{
	// EMPTY!
}
// ---------------------------------------------------------------------------
SpString::SpString( const SpStringBase& rkStr )
	: SpStringBase( rkStr )
{
	// EMPTY!
}
// ---------------------------------------------------------------------------
SpString::SpString( const char* pacStr )
	: SpStringBase( pacStr )
{
	// EMPTY!
}
// ---------------------------------------------------------------------------
SpString::SpString( const char* pacStr, SpString::SizeType kLength )
	: SpStringBase( pacStr, kLength )
{
	// EMPTY!
}
// ---------------------------------------------------------------------------
SpString::SpString(const SpString& rkStr, SizeType kStart, SizeType kEnd)
	: SpStringBase( rkStr, kStart, kEnd )
{
	// EMPTY@
}
// ---------------------------------------------------------------------------
SpString::SpString( SpString::SizeType kLength, char c )
	: SpStringBase( kLength, c )
{
	// EMPTY!
}
// ---------------------------------------------------------------------------
void SpString::clear()
{
	resize(0);
}
// ---------------------------------------------------------------------------
