
#include "SpVertexNoiseSb.h"
#include "SpGlslVertexProgram.h"
#include "SpGlslFragmentProgram.h"
#include "SpGlslManager.h"
#include "SpGlutHeaders.h"
#include "SpTuple.h"
#include "SpRandom.h"

//----------------------------------------------------------------------------

using namespace Spark;

//----------------------------------------------------------------------------

// must be same as B in VertexNoise.glsl
static int gs_iTableSize = 64;
static const SpString gs_kFPColoredFragmentFilename = "ColoredFragment.fp";
static const SpString gs_kVPOneOctaveNoiseFilename = "OneOctaveNoise.vp";
static const SpString gs_kVPOneOctaveAbsNoiseFilename = "OneOctaveAbsNoise.vp";

//----------------------------------------------------------------------------
SpVertexNoiseSb::SpVertexNoiseSb(
	bool bAbsNoise,
	float fOffsetX, float fOffsetY, float fOffsetZ,
	float fScaleX, float fScaleY, float fScaleZ,
	unsigned int uiGridResolution,
	unsigned long ulSeed)
:
	SpStreamBasis(
		fOffsetX, fOffsetY, fOffsetZ, fScaleX, fScaleY, fScaleZ, 1.0f),
	m_aiP(0),
	m_akPG(0),
	m_ulSeed(ulSeed),
	m_pkVertexProgram(0),
	m_pkFragmentProgram(0)
{
	m_kGrid.setResolution(uiGridResolution, uiGridResolution);

	if(bAbsNoise)
		m_pkVertexProgram = SpGlslManager::loadVertexProgramFromFile(
			gs_kVPOneOctaveAbsNoiseFilename.c_str()
		);
	else
		m_pkVertexProgram = SpGlslManager::loadVertexProgramFromFile(
			gs_kVPOneOctaveNoiseFilename.c_str()
		);

	m_pkFragmentProgram = SpGlslManager::loadFragmentProgramFromFile(
		gs_kFPColoredFragmentFilename.c_str()
	);

	m_bHasChanged = true;

	assert(m_pkVertexProgram);
	assert(m_pkFragmentProgram);
}
//----------------------------------------------------------------------------
SpVertexNoiseSb::~SpVertexNoiseSb()
{
	destroy();
}
//----------------------------------------------------------------------------
void SpVertexNoiseSb::initialize()
{
	// delete the tables if they already exist
	if( m_aiP ) delete[] m_aiP;
	m_aiP = NULL;

	if( m_akPG ) delete[] m_akPG;
	m_akPG = NULL;

	// seed the randon number generator
	SeedRandom(m_ulSeed);

	// allocate storage for the permutation table
	m_aiP = new int[gs_iTableSize*2+2];

	// allocate storage for the gradient table
	m_akPG = new SpVector4f[gs_iTableSize*2+2];

	// initalize random gradients
	int i;
	for(i=0; i<gs_iTableSize; i++)
	{
		m_aiP[i] = i;
		m_akPG[i][0] = RandomSymmetricFloat();
		m_akPG[i][1] = RandomSymmetricFloat();
		m_akPG[i][2] = RandomSymmetricFloat();
		m_akPG[i] = Normalize(m_akPG[i]);
	}

	// initialize permutation table (random shuffle)
	for(i=0; i<gs_iTableSize; i++)
	{
		int j, t;
		j = (RandomUInt() >> 4) % gs_iTableSize;
		t = m_aiP[i];
		m_aiP[i] = m_aiP[j];
		m_aiP[j] = t;

		// set the permutation index to the 4th vector component (w)
		m_akPG[i][3] = (float) m_aiP[i];

		// mirror first half of table into second half
		m_akPG[i+gs_iTableSize][0] = m_akPG[i][0];
		m_akPG[i+gs_iTableSize][1] = m_akPG[i][1];
		m_akPG[i+gs_iTableSize][2] = m_akPG[i][2];
		m_akPG[i+gs_iTableSize][3] = m_akPG[i][3];
	}

	// set the last values to the first for wrap-around
	m_akPG[gs_iTableSize*2] = m_akPG[0];
	m_akPG[(gs_iTableSize*2)+1] = m_akPG[1];

	// compile the program and submit the parameter data
	SpGlslManager::compile(m_pkVertexProgram);
	SpGlslManager::bind(m_pkVertexProgram);
	m_pkVertexProgram->setParameter4fv(
		"pg[0]", m_akPG[0].values(), gs_iTableSize*2+2
	);

	// toggle initialized flag
	m_bIsInitialized = true;
}
//----------------------------------------------------------------------------
void SpVertexNoiseSb::destroy()
{
	// delete the tables if they already exist
	if( m_aiP ) delete[] m_aiP;
	m_aiP = NULL;

	if( m_akPG ) delete[] m_akPG;
	m_akPG = NULL;

	if(m_pkVertexProgram)
	{
		SpGlslManager::release(m_pkVertexProgram);
		delete m_pkVertexProgram;
	}
}
//----------------------------------------------------------------------------
void SpVertexNoiseSb::preload()
{
	if(!m_bIsInitialized)
		initialize();
}
//----------------------------------------------------------------------------
void SpVertexNoiseSb::enable()
{
	if(!m_bIsInitialized)
		initialize();

	if(m_pkVertexProgram)
	{
		SpGlslManager::enable(m_pkVertexProgram);
		m_pkVertexProgram->setParameter1f( "Exponent", m_fWeight );
		m_pkVertexProgram->setParameter1f( "Offset", 0.0f );
	}

	if(m_pkFragmentProgram)
	{
		SpGlslManager::enable(m_pkFragmentProgram);
	}
}
//----------------------------------------------------------------------------
void SpVertexNoiseSb::disable()
{
	if(m_pkVertexProgram)
		SpGlslManager::disable(m_pkVertexProgram);

	if(m_pkFragmentProgram)
		SpGlslManager::disable(m_pkFragmentProgram);

}
//----------------------------------------------------------------------------
bool SpVertexNoiseSb::hasChanged()
{
	return m_bHasChanged;
}
//----------------------------------------------------------------------------
bool SpVertexNoiseSb::sendOutputToBuffer(
	SpStreamBuffer* pkBuffer, SpCopyToTextureFb *pkCopy)
{
	//if(m_bHasChanged)
	{
		if (pkBuffer->isInitialized() && pkBuffer->enable())
		{
			if (pkBuffer->isDoubleBuffered()) glDrawBuffer(GL_BACK);

			enable();

			glMatrixMode(GL_TEXTURE);
			glLoadIdentity();
			glTranslatef( m_fOffsetX, m_fOffsetY, m_fOffsetZ );
			glScalef( m_fScaleX, m_fScaleY,	m_fScaleZ );

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_kGrid.render();

			glPopMatrix();

			disable();

			glMatrixMode(GL_TEXTURE);
			glLoadIdentity();
			glMatrixMode(GL_MODELVIEW);

			if(pkCopy)
				pkCopy->updateOutput();

			pkBuffer->disable();
			glFlush();
			m_bHasChanged = false;
			return true;
		}
	}
	//m_bHasChanged = false;
	return false;
}
//----------------------------------------------------------------------------
