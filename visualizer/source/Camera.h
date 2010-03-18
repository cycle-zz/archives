#ifndef DG_CAMERA_H
#define DG_CAMERA_H

#include "DataTypes.h"
#include "Transform.h"
#include "Vector.h"
#include "Color.h" 
#include "Image.h"

namespace dg
{

//******************************************************************************

class Camera
{
	
public:

    Camera(
		const Vector& rkPos = Vector(0.0f,0.0f,0.0f), 
		const Vector& rkDir = Vector(0.0f,0.0f,1.0f), 
		const Vector& rkUp = Vector(0.0f,1.0f,0.0f), 
		const Vector& rkRight = Vector(1.0f,0.0f,0.0f),
		Real fNear = 0.1f, Real fFar=10.0f, 
		Real fHalfWidth = 0.5f, Real fHalfHeight = 0.5f,
		Image* pkImage=NULL);
		
    ~Camera();

	// initialization
	void setup();

	// camera position access methods
    inline Vector getPosition() const;
    inline void setPosition(const Vector& rkPosition);
	
	// camera direction access methods
    inline Vector getDirection() const;
    inline void setDirection(const Vector& rkDirection);
	
	// camera up vector access methods
    inline Vector getUp() const;
    inline void setUp(const Vector& rkUp);
	
	// camera right vector access methods
    inline Vector getRight() const;
    inline void setRight(const Vector& rkRight);

	// near clipping plane access methods
	inline void setNear(Real fNear);
	inline Real getNear() const;

	// far clipping plane access methods
	inline void setFar(Real fFar);
	inline Real getFar() const;

	// half width access methods = 0.5 * Tan( Radians( HorizFov ) )  
	inline void setHalfWidth(Real fHalfWidth);
	inline Real getHalfWidth() const;

	// horzontal fov converion methods 
	inline void setHorizontalFov(Real fHorizFov);
	inline Real getHorizontalFov() const;

	// half height access methods = 0.5 * Tan( Radians( VertFov ) )  
	inline void setHalfHeight(Real fHalfHeight);
	inline Real getHalfHeight() const;

	// vertical fov converion methods 
	inline void setVerticalFov(Real fVertFov);
	inline Real getVerticalFov() const;
	
	// background color access methods
	inline void setBackground(const Color& rkColor);
	inline Color getBackground() const;

	// calculates a ray direction based on current view
	Vector getRayDir(UInt uiX, UInt uiY) const;

	// return a ray direction corresponding to [0,0] in image
	inline Vector getStartRayDir() const;
	
    // image access methods
	inline void setImage(Image* pkImage);
	
	inline const Image* getImage() const;
	inline Image* getImage();

	// image property methods
    inline UInt getImageWidth() const;
    inline UInt getImageHeight() const;
	inline UInt getImageChannels() const;

	// pixel size methods
	inline Real getPixelWidth() const;
	inline Real getPixelHeight() const;
	
private:

    // camera and view frustum
    Vector m_kPosition;
	Vector m_kDirection;
	Vector m_kUp;
	Vector m_kRight;
	
	// ray direction that corresponds to [0,0] in image
	Vector m_kStartRay;
	
	// clipping and fov
    Real m_fNear;
	Real m_fFar;
	Real m_fHalfWidth;
	Real m_fHalfHeight;
	
	// background properties
	Color m_kBgColor;
	
	// pixel size for current view
    Real m_fPixelWidth;
	Real m_fPixelHeight;
    
	// multiply factors for ray generation
    Real m_fMultiplyX;
    Real m_fMultiplyY;
    
	// rendered image
	Image* m_pkImage;
		
};

//******************************************************************************

#include "Camera.inc"

//******************************************************************************

} // end namespace: dg

#endif

