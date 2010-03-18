#ifndef DG_IMAGE_H
#define DG_IMAGE_H

#include "DataTypes.h"
#include "Color.h" 

namespace dg
{

//******************************************************************************

class Image
{
	
public:

    Image(	UInt uiWidth = 0, UInt uiHeight = 0, UInt uiChannels = 0, 
		const Color& rkClearColor = Color::GRAY);
		
    ~Image();

	// pixel access methods
	inline const Real* operator[](UInt uiIndex) const;
	inline Real* operator[](UInt uiIndex);
	inline const Real* operator()(UInt uiX, UInt uiY, UInt uiC) const;
	inline Real* operator()(UInt uiX, UInt uiY, UInt uiC);
	inline Color operator()(UInt uiX, UInt uiY) const;
	
	// converts x+y+component to one-dimensional index for arrays
	inline UInt index(UInt uiX, UInt uiY, UInt uiC) const;
	
	// image property access
	inline UInt width() const;
	inline UInt height() const;
	inline UInt channels() const;
	
    inline UInt getWidth() const;
    inline UInt getHeight() const;
	inline UInt getChannels() const;

	// pixel access
	inline const Real* pixels() const;
	inline Real* pixels();
		
	inline const Real* getPixels() const;
	inline Real* getPixels();

	// color access methods
	inline Color getColor(UInt uiX, UInt uiY) const;
	inline void setColor(UInt uiX, UInt uiY, const Color& rkColor);
	
    // color access methods
	inline Color getClearColor() const;
	inline void setClearColor(const Color& rkColor);
	
	// resize methods
	void resize(UInt uiWidth, UInt uiHeight, UInt uiChannels);
	
	// basic blur filter
    void blur();
	
private:

	// clear color
	Color m_kClearColor;
	
    UInt m_uiWidth; 
	UInt m_uiHeight;
	UInt m_uiChannels;
	
	// combined w*h*c
	UInt m_uiResolution;
	
    Real* m_afPixels;
};

//******************************************************************************

#include "Image.inc"

//******************************************************************************

} // end namespace: dg

#endif

