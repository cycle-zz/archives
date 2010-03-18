#include "SpResourcePath.h"

#ifdef WIN32
	#include <io.h>
#else
	#include <sys/stat.h>
	#include <unistd.h>
#endif
#include <fcntl.h>
// ---------------------------------------------------------------------------

using namespace std;
using namespace Spark;

// ---------------------------------------------------------------------------
SpString SpResourcePath::getPath( const SpString & rkFilename )
{
	FILE * pkFile;
	bool bFound = false;
	for ( unsigned int i = 0; i < m_kSearchPath.size(); i++ )
	{
		m_kPathName = m_kSearchPath[i] + "/" + rkFilename;
		pkFile =::fopen( m_kPathName.c_str(), "r" );

		if ( pkFile != 0 )
		{
			fclose( pkFile );
			bFound = true;
			break;
		}
	}

	if ( bFound == false )
	{
		m_kPathName = rkFilename;
		pkFile =::fopen( m_kPathName.c_str(), "r" );
		if ( pkFile != 0 )
		{
			fclose( pkFile );
			bFound = true;
		}
	}

	if ( bFound == false )
	{
		for ( unsigned int i = 0; i < m_kSearchPath.size(); i++ )
		{
			SpString::SizeType kCurrent;
			SpString kName = rkFilename;
			while ( ( kCurrent = kName.find_first_of( "\\/" ) ) != SpString::npos )
			{
				kCurrent++;

				kName = kName.substr( kCurrent, kName.length() - kCurrent );
				m_kPathName = m_kSearchPath[i] + "/" + kName;
				pkFile =::fopen( m_kPathName.c_str(), "r" );

				if ( pkFile != 0 )
				{
					fclose( pkFile );
					bFound = true;
					break;
				}
			}

			if ( bFound ) break;
		}
	}

	if ( bFound == false )
		return "";

	SpString::SizeType kIndex = m_kPathName.rfind( '\\' );
	if ( kIndex == ( SpString::SizeType ) - 1 )
	{
		kIndex = m_kPathName.rfind( '/' );
	}

	if ( kIndex != ( SpString::SizeType ) - 1 )
		m_kFilePath = m_kPathName.substr( 0, kIndex );
	else
		m_kFilePath = ".";
	return m_kFilePath;
}

// ---------------------------------------------------------------------------
SpString SpResourcePath::getFile( const SpString & rkFilename )
{
	FILE * pkFile;

	unsigned int i = 0;
	for ( i = 0; i < m_kSearchPath.size(); i++ )
	{
		m_kPathName = m_kSearchPath[i] + "/" + rkFilename;
		pkFile = fopen( m_kPathName.c_str(), "r" );

		if ( pkFile != 0 )
		{
			fclose( pkFile );
			return m_kPathName;
		}
	}

	m_kPathName = rkFilename;
	pkFile = fopen( m_kPathName.c_str(), "r" );
	if ( pkFile != 0 )
	{
		fclose( pkFile );
		return m_kPathName;
	}

	for ( i = 0; i < m_kSearchPath.size(); i++ )
	{
		SpString::SizeType kCurrent;
		SpString kName = rkFilename;
		while ( ( kCurrent = kName.find_first_of( "\\/" ) ) != SpString::npos )
		{
			kCurrent++;

			kName = kName.substr( kCurrent, kName.length() - kCurrent );
			m_kPathName = m_kSearchPath[i] + "/" + kName;
			pkFile =::fopen( m_kPathName.c_str(), "r" );

			if ( pkFile != 0 )
			{
				fclose( pkFile );
				return m_kPathName;
			}
		}
	}

	printf( "File not found: %s\n", rkFilename.c_str() );

	return "";
}

// ---------------------------------------------------------------------------
FILE * SpResourcePath::loadDataFile( const SpString & rkFilename, const char * acMode )
{
	FILE * pkFile =::fopen( rkFilename.c_str(), acMode );
	if ( pkFile != 0 )
		return pkFile;

	for ( unsigned int i = 0; i < m_kSearchPath.size(); i++ )
	{
		SpString s = m_kSearchPath[i] + "/" + rkFilename;
		FILE * pkFile =::fopen( s.c_str(), acMode );

		if ( pkFile != 0 )
			return pkFile;

		else if ( !strcmp( m_kSearchPath[i].c_str(), "" ) )
		{
			FILE * pkFile =::fopen( rkFilename.c_str(), acMode );
			if ( pkFile != 0 )
				return pkFile;
		}
	}
	return 0;
}

// ---------------------------------------------------------------------------
char * SpResourcePath::loadTextFile( const char * acFilename )
{
	if ( !acFilename )
		return NULL;

	FileStat kFS;

	if ( getFileStats( acFilename, & kFS ) )
	{
		unsigned long ulSize = kFS.st_size;

		char * acBuffer = new char[ulSize + 1];

		FILE * pkFile = 0;
		if ( !( pkFile = loadDataFile( acFilename, "r" ) ) )
		{
			fprintf( stderr, "Cannot open \"%s\" for read!\n", acFilename );
			return 0;
		}

		int iBytes;
		iBytes = ( int )fread( acBuffer, 1, ulSize, pkFile );

		acBuffer[iBytes] = 0;

		fclose( pkFile );

		return acBuffer;
	}
	fprintf( stderr, "Cannot open file \"%s\" for stat read!\n", acFilename );
	return NULL;
}

// ---------------------------------------------------------------------------
SpString SpResourcePath::loadTextFile( const SpString & rkFilename )
{
	SpString kResult;

	char * acBuffer = loadTextFile( rkFilename.c_str() );

	if ( acBuffer )
	{
		kResult = SpString( acBuffer );
		delete[] acBuffer;
	}

	return kResult;
}

// ---------------------------------------------------------------------------
int SpResourcePath::getFileStats( const SpString & rkFilename, FileStat * pkStat )
{
	if ( m_kSearchPath.size() < 1 )
		m_kSearchPath.push_back( "." );

	for ( unsigned int i = 0; i < m_kSearchPath.size(); i++ )
	{
		SpString kI = m_kSearchPath[i];
		SpString kS = kI + "/" + rkFilename;

#ifdef WIN32
		int iFileHandle =::_open( kS.c_str(), _O_RDONLY );
#else
		int iFileHandle =::open( kS.c_str(), O_RDONLY );
#endif

		if ( iFileHandle >= 0 )
		{

#ifdef WIN32
			int iResult =::_fstat( iFileHandle, pkStat );
#else
			int iResult =::fstat( iFileHandle, pkStat );
#endif

			if ( iResult != 0 )
			{
				fprintf( stderr, "An fstat error occurred.\n" );
				return 0;
			}

#ifdef WIN32
			::_close( iFileHandle );
#else
			::close( iFileHandle );
#endif

			return 1;
		}
	}
	return 0;
}
// ---------------------------------------------------------------------------
