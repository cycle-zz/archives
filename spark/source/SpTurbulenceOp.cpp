#include "SpTurbulenceOp.h"
#include "SpGlslManager.h"
#include "SpGlslVertexProgram.h"
#include "SpGlslFragmentProgram.h"
#include "SpStreamOperator.h"
#include "SpGlutHeaders.h"
#include "SpGlManager.h"
#include "SpMaths.h"

#include <cassert>

// ---------------------------------------------------------------------------

using namespace Spark;

//----------------------------------------------------------------------------

// Filenames for the vertex and fragment programs being used internally
static const SpString kVPTex2DFilename = "VPAddMultiTex2D8.glsl";
static const SpString kFPTex2DFilename = "FPAddMultiTex2D16.glsl";
static const SpString kFPTex2DRectFilename = "FPAddMultiTex2DRect16.glsl";

// Must match the parameters in the fragment program being used
static const SpString kTextureParam = "texture";

//----------------------------------------------------------------------------
SpTurbulenceOp::SpTurbulenceOp(
	float fX, float fY, float fZ,
	float fOctaves,
	float fIncrement,
	float fLacunarity)
:
	SpStreamOperator(),
	m_fOffsetX(fX),
	m_fOffsetY(fY),
	m_fOffsetZ(fZ),
	m_fX(fX), m_fY(fY), m_fZ(fZ),
	m_fOctaves(fOctaves),
	m_fIncrement(fIncrement),
	m_fLacunarity(fLacunarity),
	m_uiCurrentPass(0),
	m_adExponents(0),
	m_bInitialized(false),
	m_bCreateTextures(true),
	m_pkIdentityVertexProgram(0),
	m_pkAddMultiTextureProgram(0)
{
	GLint iMaxTextureUnits = 0;

	// GL_MAX_TEXTURE_UNITS is the "old" constant for
	// fixed function multi-texturing, and has a max value of 4.
	// Since NV30+ cards have 16+ texture units, this is a waste
	// of unused resources.
	//
	// GL_MAX_TEXTURE_IMAGE_UNITS_ARB is suppose to report the
	// number of available texture units for programmable
	// shader programs, so lets use that instead.

	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS_ARB, &iMaxTextureUnits);
	m_uiMaxOctaves = iMaxTextureUnits;

	// clamp the octave count to the texture unit count, and user value
	if(fOctaves > m_uiMaxOctaves)
	{
		fOctaves = (float)m_uiMaxOctaves;
	}
	else
	{
		m_uiMaxOctaves = (unsigned int)fOctaves;
	}

	// create the exponent array of spectral weights, fill with 0 for now
	m_adExponents = new double[m_uiMaxOctaves];
	memset(m_adExponents, 0, sizeof(double) * m_uiMaxOctaves);

	// set the number of texture units based on octave count
	m_uiTextureCount = (int)fOctaves;
	float fRemainder = fOctaves - (int)fOctaves;

	if ( fRemainder )
		m_uiTextureCount++;

	if ( m_uiTextureCount > m_uiMaxOctaves )
		m_uiTextureCount = m_uiMaxOctaves;

	// create the texture index array, and fill with 0 for now
	m_auiTextures = new unsigned int[ m_uiTextureCount ];
	memset(m_auiTextures, 0, sizeof(unsigned int) * m_uiTextureCount);

	fprintf(stderr, "Turblence: Octaves[%d] Textures[%d]\n",
			(int)m_fOctaves, m_uiTextureCount);
}
//----------------------------------------------------------------------------
SpTurbulenceOp::~SpTurbulenceOp()
{
	for (unsigned int iTex = 0; iTex < m_uiTextureCount; iTex++)
		SpGlManager::deleteTexture(m_auiTextures[iTex]);

	delete[] m_adExponents;
	delete[] m_auiTextures;
}
//----------------------------------------------------------------------------
void SpTurbulenceOp::initialize(
	SpStreamBuffer* pkBuffer, SpStreamFeedback *, bool bCreateTextures)
{
	if(!pkBuffer)
		return;

	// load the vertex program
	if(!m_pkIdentityVertexProgram)
	{
		if(pkBuffer->isRectangleTexture())
		{
			// non-power of two
			m_pkIdentityVertexProgram = SpGlslManager::loadVertexProgramFromFile(
				kVPTex2DFilename.c_str()
			);
		}
		else
		{
			// use the same vertex program for non-rectangle textures
			m_pkIdentityVertexProgram = SpGlslManager::loadVertexProgramFromFile(
				kVPTex2DFilename.c_str()
			);
		}

		assert(m_pkIdentityVertexProgram);
		SpGlslManager::compile(m_pkIdentityVertexProgram);
	}

	// load the fragment program
	if(!m_pkAddMultiTextureProgram)
	{
		if(pkBuffer->isRectangleTexture())
		{
			// rectangle program
			m_pkAddMultiTextureProgram = SpGlslManager::loadFragmentProgramFromFile(
				kFPTex2DRectFilename.c_str()
			);
		}
		else
		{
			// power of two program
			m_pkAddMultiTextureProgram = SpGlslManager::loadFragmentProgramFromFile(
				kFPTex2DFilename.c_str()
			);
		}

		assert(m_pkAddMultiTextureProgram);
		SpGlslManager::compile(m_pkAddMultiTextureProgram);
	}

	// compute spectral weights for each frequency
	for( unsigned int i = 0; i < m_uiMaxOctaves; i++ )
		m_adExponents[i] = Pow( (double)m_fLacunarity, (double)i * -m_fIncrement );


	// create textures for each octave and store texture ids
	if(bCreateTextures)
	{
		if(m_auiTextures[0])
		{
			// delete any existing textures
			for (unsigned int iTex = 0; iTex < m_uiTextureCount; iTex++)
				SpGlManager::deleteTexture(m_auiTextures[iTex]);
		}
		for (unsigned int iTex = 0; iTex < m_uiTextureCount; iTex++)
		{
			m_auiTextures[iTex] = SpGlManager::createFilteredTexture(
				pkBuffer->getWidth(),
				pkBuffer->getHeight(),
				pkBuffer->getTextureTarget()
			);
		}
		m_bCreateTextures = false;
	}

	// toggle initialized state
	m_bInitialized = true;
	m_uiCurrentPass = 0;
}
//----------------------------------------------------------------------------
bool SpTurbulenceOp::enableOutputStream(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy)
{
	if(!pkBuffer || !pkCopy)
		return false;

	if(m_uiCurrentPass < m_fOctaves)
	{
		pkCopy->setOutputTexture(
			m_auiTextures[m_uiCurrentPass],
			pkBuffer->getTextureTarget(),
			pkBuffer->getWidth(), pkBuffer->getHeight()
		);
	}
	return true;
}
//----------------------------------------------------------------------------
bool SpTurbulenceOp::setupState(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy)
{
	if(!pkBuffer || !pkCopy)
		return false;

	if(!m_bInitialized)
		initialize(pkBuffer, pkCopy, m_bCreateTextures);

	if(m_uiCurrentPass == 0)
	{
		m_fX = m_fOffsetX;
		m_fY = m_fOffsetY;
		m_fZ = m_fOffsetZ;
	}

	if(m_uiCurrentPass < m_fOctaves && m_bInputIsBasis)
	{
		SpStreamBasis* pkBasis = static_cast<SpStreamBasis*>(m_pkInputStream);
		pkBasis->setWeight( (float)m_adExponents[m_uiCurrentPass] );
		pkBasis->setOffset( m_fX, m_fY, m_fZ );
	}
	return true;
}
//----------------------------------------------------------------------------
bool SpTurbulenceOp::processStream(SpStreamBuffer* pkBuffer, SpStreamFeedback *pkCopy)
{
	if(m_uiCurrentPass < m_fOctaves)
	{
		return m_pkInputStream->sendOutputToBuffer( pkBuffer, pkCopy );
	}
	return true;
}
//----------------------------------------------------------------------------
bool SpTurbulenceOp::updateOutputStream(
	SpStreamBuffer* pkBuffer, SpStreamFeedback *)
{
	if(m_uiCurrentPass >= m_fOctaves)
	{
		if (pkBuffer->isInitialized() && pkBuffer->enable())
		{
			if (pkBuffer->isDoubleBuffered()) glDrawBuffer(GL_BACK);

			pkBuffer->enable();

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			{
				SpGlslManager::enable(m_pkIdentityVertexProgram);
				SpGlslManager::enable(m_pkAddMultiTextureProgram);

				// bind all of the textures to the appropriate parameter values
				// and make then active for the programmable shaders
				for(unsigned int i = 0; i < m_uiTextureCount; i++)
				{
					SpString kCurrentParam = kTextureParam;
					kCurrentParam.add(i);
					glActiveTexture(GL_TEXTURE0 + i);
					glBindTexture( pkBuffer->getTextureTarget(), m_auiTextures[i] );
					m_pkAddMultiTextureProgram->setParameter1i(kCurrentParam, i);
				}

				float fMaxS = (float)pkBuffer->getMaxS();
				float fMaxT = (float)pkBuffer->getMaxT();

				glBegin(GL_QUADS);
				glTexCoord2f(0, 0);			glVertex2f(-1, -1);
				glTexCoord2f(fMaxS, 0);		glVertex2f( 1, -1);
				glTexCoord2f(fMaxS, fMaxT); glVertex2f( 1,  1);
				glTexCoord2f(0, fMaxT);		glVertex2f(-1,  1);
				glEnd();

				SpGlslManager::disable(m_pkIdentityVertexProgram);
				SpGlslManager::disable(m_pkAddMultiTextureProgram);
			}
			glPopMatrix();
			pkBuffer->disable();
			m_bHasChanged = false;
			glFlush();
			//glutSwapBuffers();
			return true;
		}
	}
	//m_bHasChanged = true;
	return false;
}
//----------------------------------------------------------------------------
bool SpTurbulenceOp::resetState(
	SpStreamBuffer*, SpStreamFeedback *)
{
	if(m_uiCurrentPass < m_fOctaves)
	{
		// multipy in the lacunarity to create the gaps between octaves
		m_fX *= m_fLacunarity;
		m_fY *= m_fLacunarity;
		m_fZ *= m_fLacunarity;

		// increment the current pass number
		m_uiCurrentPass++;
		m_bHasChanged = true;
	}
	else
	{
		// reset the current pass to zero
		m_uiCurrentPass = 0;

		// reset the evaluation point to original offset
		m_fX = m_fOffsetX;
		m_fY = m_fOffsetY;
		m_fZ = m_fOffsetZ;
	}
	return true;
}
//----------------------------------------------------------------------------
bool SpTurbulenceOp::disableOutputStream(
	SpStreamBuffer* , SpStreamFeedback *)
{
	return true;
}
//----------------------------------------------------------------------------
void SpTurbulenceOp::setLacunarity(float fLacunarity)
{
	if(fLacunarity == m_fLacunarity)
		return;

	m_fLacunarity = fLacunarity;
	m_bInitialized = false;
	m_bHasChanged = true;
}
//----------------------------------------------------------------------------
float SpTurbulenceOp::getLacunarity() const
{
	return m_fLacunarity;

}
//----------------------------------------------------------------------------
void SpTurbulenceOp::setIncrement(float fIncrement)
{
	if(fIncrement == m_fIncrement)
		return;

	m_fIncrement = fIncrement;
	m_bInitialized = false;
	m_bHasChanged = true;
}
//----------------------------------------------------------------------------
float SpTurbulenceOp::getIncrement() const
{
	return m_fIncrement;
}
//----------------------------------------------------------------------------
void SpTurbulenceOp::setOffset(float fX, float fY, float fZ)
{
	m_fOffsetX = fX;
	m_fOffsetY = fY;
	m_fOffsetZ = fZ;
	m_uiCurrentPass = 0;
	m_bHasChanged = true;
}
//----------------------------------------------------------------------------
void SpTurbulenceOp::getOffset(float& rfX, float& rfY, float& rfZ) const
{
	rfX = m_fOffsetX;
	rfY = m_fOffsetY;
	rfZ = m_fOffsetZ;
}
//----------------------------------------------------------------------------
void SpTurbulenceOp::setOctaves(float fOctaves)
{
	if(fOctaves == m_fOctaves)
		return;

	m_fOctaves = fOctaves;
	if(m_fOctaves > m_uiMaxOctaves)
	{
		m_bInitialized = false;
		m_bCreateTextures = true;
	}
	m_bHasChanged = true;
}
//----------------------------------------------------------------------------
float SpTurbulenceOp::getOctaves() const
{
	return m_fOctaves;
}
//----------------------------------------------------------------------------
void SpTurbulenceOp::setInputStream(SpStreamBasis* pkInputStream)
{
	SpStreamOperator::setInputStream(pkInputStream);
	m_bInputIsBasis = true;
}
//----------------------------------------------------------------------------
void SpTurbulenceOp::setInputStream(SpStreamInput* pkInputStream)
{
	SpStreamOperator::setInputStream(pkInputStream);
	m_bInputIsBasis = false;
}
//----------------------------------------------------------------------------
