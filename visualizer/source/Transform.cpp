#include "Transform.h"
#include "Maths.h"

using namespace dg;

// *****************************************************************************
Transform dg::Translate(const Vector &rkDelta) 
{
	Matrix *pkMatrix, *pkInverse;
	pkMatrix = new Matrix(1, 0, 0, rkDelta.x(),
	                      0, 1, 0, rkDelta.y(),
						  0, 0, 1, rkDelta.z(),
						  0, 0, 0,       1);
	
	pkInverse = new Matrix(1, 0, 0, -rkDelta.x(),
                           0, 1, 0, -rkDelta.y(),
                           0, 0, 1, -rkDelta.z(),
                           0, 0, 0,        1);
						 
	return Transform(pkMatrix, pkInverse, true);
}
// *****************************************************************************
Transform dg::Scale(Real fX, Real fY, Real fZ) 
{
	Matrix *pkMatrix, *pkInverse;
	pkMatrix = new Matrix(fX, 0, 0, 0,
                      	  0, fY, 0, 0,
						  0, 0, fZ, 0,
						  0, 0, 0, 1);
						  
	pkInverse = new Matrix(1.0f/fX, 0,       0, 0,
                           0, 1.0f/fY,       0, 0,
                           0,       0, 1.0f/fZ, 0,
                           0,       0,       0, 1);
						   
	return Transform(pkMatrix, pkInverse, true);
}
// *****************************************************************************
Transform dg::RotateX(Real fDegrees) 
{
	Real fSin = Sine(Radians(fDegrees));
	Real fCos = Cosine(Radians(fDegrees));
	
	Matrix *pkMatrix = new Matrix(1,    0,     0, 0,
                                  0, fCos, -fSin, 0,
                                  0, fSin,  fCos, 0,
                                  0,    0,     0, 1);
								  
	Matrix *pkInverse = new Matrix( pkMatrix->transpose() );
	return Transform(pkMatrix, pkInverse, true);
}
// *****************************************************************************
Transform dg::RotateY(Real fDegrees) 
{
	Real fSin = Sine(Radians(fDegrees));
	Real fCos = Cosine(Radians(fDegrees));
	
	Matrix *pkMatrix = new Matrix(fCos,   0, -fSin, 0,
                                     0,   1,     0, 0,
                                  fSin,   0,  fCos, 0,
                                     0,   0,     0, 1);
	
	Matrix *pkInverse = new Matrix( pkMatrix->transpose() );
	return Transform(pkMatrix, pkInverse, true);
}
// *****************************************************************************
Transform dg::RotateZ(Real fDegrees) 
{
	Real fSin = Sine(Radians(fDegrees));
	Real fCos = Cosine(Radians(fDegrees));
	
	Matrix *pkMatrix = new Matrix(fCos, -fSin, 0, 0,
                                  fSin,  fCos, 0, 0,
                                     0,     0, 1, 0,
                                     0,     0, 0, 1);

	Matrix *pkInverse = new Matrix( pkMatrix->transpose() );
	return Transform(pkMatrix, pkInverse, true);
}
// *****************************************************************************
Transform dg::Rotate(Real fDegrees, const Vector &rkAxis) 
{
	Vector kA = Normalize(rkAxis);
	Real fSin = Sine(Radians(fDegrees));
	Real fCos = Cosine(Radians(fDegrees));
	Real afM[4][4];

	afM[0][0] = kA.x() * kA.x() + (1.f - kA.x() * kA.x()) * fCos;
	afM[0][1] = kA.x() * kA.y() * (1.f - fCos) - kA.z() * fSin;
	afM[0][2] = kA.x() * kA.z() * (1.f - fCos) + kA.y() * fSin;
	afM[0][3] = 0;

	afM[1][0] = kA.x() * kA.y() * (1.f - fCos) + kA.z() * fSin;
	afM[1][1] = kA.y() * kA.y() + (1.f - kA.y() * kA.y()) * fCos;
	afM[1][2] = kA.y() * kA.z() * (1.f - fCos) - kA.x() * fSin;
	afM[1][3] = 0;

	afM[2][0] = kA.x() * kA.z() * (1.f - fCos) - kA.y() * fSin;
	afM[2][1] = kA.y() * kA.z() * (1.f - fCos) + kA.x() * fSin;
	afM[2][2] = kA.z() * kA.z() + (1.f - kA.z() * kA.z()) * fCos;
	afM[2][3] = 0;

	afM[3][0] = 0;
	afM[3][1] = 0;
	afM[3][2] = 0;
	afM[3][3] = 1;

	Matrix *pkMatrix = new Matrix(afM);
	Matrix *pkInverse = new Matrix( pkMatrix->transpose() );
	return Transform(pkMatrix, pkInverse, true);
}
// *****************************************************************************
Transform dg::LookAt(const Vector &rkPos, const Vector &rkLook, const Vector &rkUp) 
{
	Real afM[4][4];

	// initialize fourth column of viewing matrix
	afM[0][3] = rkPos.x();
	afM[1][3] = rkPos.y();
	afM[2][3] = rkPos.z();
	afM[3][3] = 1;

	// initialize first three columns of viewing matrix
	Vector kDir = Normalize(rkLook - rkPos);
	Vector kRight = Cross(kDir, Normalize(rkUp));
	Vector kNewUp = Cross(kRight, kDir);
	afM[0][0] = kRight.x();
	afM[1][0] = kRight.y();
	afM[2][0] = kRight.z();
	afM[3][0] = 0.;
	afM[0][1] = kNewUp.x();
	afM[1][1] = kNewUp.y();
	afM[2][1] = kNewUp.z();
	afM[3][1] = 0.;
	afM[0][2] = kDir.x();
	afM[1][2] = kDir.y();
	afM[2][2] = kDir.z();
	afM[3][2] = 0.;

	// camera to world
	Matrix *pkMatrix = new Matrix(afM);
	
	// world to camera
	Matrix *pkInverse = new Matrix( pkMatrix->inverse() );
	
	return Transform(pkInverse, pkMatrix, true);
}
// *****************************************************************************
Transform dg::Transform::operator*(const Transform &rkXForm) const 
{
	Matrix* pkM1 = new Matrix( *m_pkMatrix * *rkXForm.m_pkMatrix );
	Matrix* pkM2 = new Matrix( *m_pkInverse * *rkXForm.m_pkInverse );
	return Transform(pkM1, pkM2, true);
}
// *****************************************************************************
Transform dg::Orthographic(Real fNear, Real fFar) 
{
	return Scale(1.0f, 1.0f, 1.0f / (fFar - fNear)) * 
		   Translate( Vector(0.0f, 0.0f, -fNear) );
}
// *****************************************************************************
Transform dg::Perspective(Real fFov, Real fNear, Real fFar) 
{
	Real fInvDenom = 1.0f/(fFar - fNear);
	Matrix *pkPersp = new Matrix(1, 0,       0,          0,
	                  			 0, 1,       0,          0,
								 0, 0, fFar*fInvDenom, -fFar*fNear*fInvDenom,
								 0, 0,       1,          0);

	Real fInvTanAng = 1.0f / tanf(Radians(fFov) / 2.0f);
	
	return Scale(fInvTanAng, fInvTanAng, 1) * Transform(pkPersp, true);
}
// *****************************************************************************
