#include "DataTypes.h"
#include "Image.h"
#include "Color.h"
#include <memory>

using namespace dg;

//******************************************************************************
Image::Image(UInt uiWidth, UInt uiHeight, UInt uiChannels, const Color& rkClearColor)
    : m_kClearColor(rkClearColor),
	  m_uiWidth(uiWidth),
	  m_uiHeight(uiHeight),
	  m_uiChannels(uiChannels),
	  m_afPixels(NULL)
{
	if(m_uiWidth > 0 && m_uiHeight > 0 && m_uiChannels > 0)
	{
		m_uiResolution = m_uiWidth * m_uiHeight * m_uiChannels;
		m_afPixels = new Real[ m_uiResolution ];

		UInt uiIndex = 0;
		for(UInt uiY = 0; uiY < m_uiHeight; uiY++)
			for(UInt uiX = 0; uiX < m_uiWidth; uiX++)
				for(UInt uiC = 0; uiC < m_uiChannels; uiC++)
					m_afPixels[uiIndex++] = m_kClearColor[uiC];
	}
}
//******************************************************************************
Image::~Image()
{
    delete[] m_afPixels;
	m_afPixels = NULL;
}
//******************************************************************************
void Image::resize(	
	UInt uiWidth, UInt uiHeight, UInt uiChannels)
{
	m_uiWidth = uiWidth;
	m_uiHeight = uiHeight;
	m_uiChannels = uiChannels;
	m_uiResolution = m_uiWidth * m_uiHeight * m_uiChannels;
		
	delete[] m_afPixels;
	m_afPixels = NULL;
	
	if(m_uiWidth > 0 && m_uiHeight > 0 && m_uiChannels > 0)
	{
		m_afPixels = new Real[ m_uiResolution ];
		
		UInt uiIndex = 0;
		for(UInt uiY = 0; uiY < m_uiHeight; uiY++)
			for(UInt uiX = 0; uiX < m_uiWidth; uiX++)
				for(UInt uiC = 0; uiC < m_uiChannels; uiC++)
					m_afPixels[uiIndex++] = m_kClearColor[uiC];
	}
}
//******************************************************************************
void Image::blur()
{
	Real* afBlur = new Real[ m_uiResolution ];
	
    memcpy(afBlur, m_afPixels, m_uiResolution * sizeof(Real));

    for (UInt uiY = 1; uiY < m_uiHeight-1; uiY++)
    {
        for (UInt uiX = 1; uiX < m_uiWidth-1; uiX++)
        {
			Real afValues[ m_uiChannels ];
			memset(afValues, 0, m_uiChannels * sizeof(Real));
			
			UInt uiDR = m_uiChannels;
            for(UInt uiDY = -uiDR; uiDY <= uiDR; uiDY += uiDR)
            {
                for (UInt uiDX = -uiDR; uiDX <= uiDR; uiDX += uiDR)
				{
					for( UInt uiC = 0; uiC < m_uiChannels; uiC++ )
						afValues[uiC] += m_afPixels[(uiX+uiDX)+m_uiWidth*(uiY+uiDY) + uiC];
				}
            }
			
			for( UInt uiC = 0; uiC < m_uiChannels; uiC++ )
				afBlur[uiX+m_uiWidth*uiY + uiC] = afValues[uiC]/9.0f;
        }
    }
    memcpy(m_afPixels, afBlur, m_uiResolution * sizeof(Real));
	delete[] afBlur;
}
//******************************************************************************

