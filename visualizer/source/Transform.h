#ifndef DG_TRANSFORM_H
#define DG_TRANSFORM_H 

#include "DataTypes.h"
#include "Matrix.h"
#include "Vector.h" 

namespace dg 
{
	
// *****************************************************************************

class Transform
{

public:

	inline Transform();
	inline Transform(Real afMatrix[4][4]);
	inline Transform(Matrix* pkMatrix, bool bTakeOwnership=false);
	inline Transform(Matrix* pkMatrix, Matrix* pkInverse, bool bTakeOwnership=false);
	inline ~Transform();

	inline Transform getInverse() const;
	inline Transform getInverse(bool bTransferOwnership);

	inline Vector operator()(const Vector &rkVector, bool bNormal) const;
	inline void operator()(const Vector &rkSource, Vector& rkDest, bool bNormal) const;
	Transform operator*(const Transform &rkOther) const;
	
private:

	bool m_bOwnMatrices;
	Matrix* m_pkMatrix;
	Matrix* m_pkInverse;
};

// *****************************************************************************
Transform Translate(const Vector &rkDelta);
Transform Scale(Real fX, Real fY, Real fZ);
Transform RotateX(Real fDegrees);
Transform RotateY(Real fDegrees);
Transform RotateZ(Real fDegrees);
Transform Rotate(Real fDegrees, const Vector &rkAxis);
Transform LookAt(const Vector &rkPos, const Vector &rkLook, const Vector &rkUp);
Transform Orthographic(Real fNear, Real fFar);
Transform Perspective(Real fFov, Real fNear, Real fFar);
// *****************************************************************************

#include "Transform.inc"

// *****************************************************************************

} // end namespace dg

// *****************************************************************************

#endif //

