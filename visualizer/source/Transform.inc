// *****************************************************************************
inline Transform::Transform()
{
	m_pkMatrix = m_pkInverse = new Matrix;
	m_bOwnMatrices = true;
}
// *****************************************************************************
inline Transform::Transform(Real afMatrix[4][4])
{
	m_pkMatrix = new Matrix(afMatrix[0][0], afMatrix[0][1], 
							afMatrix[0][2], afMatrix[0][3],
							afMatrix[1][0], afMatrix[1][1], 
							afMatrix[1][2], afMatrix[1][3],
							afMatrix[2][0], afMatrix[2][1], 
							afMatrix[2][2], afMatrix[2][3],
							afMatrix[3][0], afMatrix[3][1], 
							afMatrix[3][2], afMatrix[3][3]);
							
	*m_pkInverse = *m_pkMatrix->inverse();
	m_bOwnMatrices = true;
}
// *****************************************************************************
inline Transform::Transform(Matrix* pkMatrix, bool bTakeOwnership)
{
	m_pkMatrix = pkMatrix;
	*m_pkInverse = *m_pkMatrix->inverse();
	m_bOwnMatrices = bTakeOwnership;
}
// *****************************************************************************
inline Transform::Transform(
	Matrix* pkMatrix, Matrix* pkInverse, bool bTakeOwnership)
{
	m_pkMatrix = pkMatrix;
	m_pkInverse = pkInverse;
	m_bOwnMatrices = bTakeOwnership;
}
// *****************************************************************************
inline Transform::~Transform()
{
	if(m_bOwnMatrices)
	{
		delete m_pkMatrix;
		delete m_pkInverse;
		m_pkMatrix = NULL;
		m_pkInverse = NULL;
	}
}
// *****************************************************************************
inline Transform Transform::getInverse() const
{
	return Transform(m_pkInverse, m_pkMatrix, false);
}
// *****************************************************************************
inline Transform Transform::getInverse(bool bTransferOwnership)
{
	m_bOwnMatrices = !bTransferOwnership;
	return Transform(m_pkInverse, m_pkMatrix, bTransferOwnership);
}
// *****************************************************************************
inline Vector Transform::operator()(
	const Vector &rkVector, bool bNormal) const
{
	Real fX = rkVector.x();
	Real fY = rkVector.y();
	Real fZ = rkVector.z();

	if (bNormal)
	{
		return Normalize(
		           Vector(m_pkInverse->m_afV[0][0] * fX + 
				   		  m_pkInverse->m_afV[1][0] * fY + 
						  m_pkInverse->m_afV[2][0] * fZ,
		                  m_pkInverse->m_afV[0][1] * fY + 
						  m_pkInverse->m_afV[1][1] * fY + 
						  m_pkInverse->m_afV[2][1] * fZ,
		                  m_pkInverse->m_afV[0][2] * fZ + 
						  m_pkInverse->m_afV[1][2] * fY + 
						  m_pkInverse->m_afV[2][2] * fZ)
		);
	}

	return Vector(m_pkMatrix->m_afV[0][0] * fX + 
				  m_pkMatrix->m_afV[0][1] * fY + 
				  m_pkMatrix->m_afV[0][2] * fZ,
	              m_pkMatrix->m_afV[1][0] * fX + 
				  m_pkMatrix->m_afV[1][1] * fY + 
				  m_pkMatrix->m_afV[1][2] * fZ,
	              m_pkMatrix->m_afV[2][0] * fX + 
				  m_pkMatrix->m_afV[2][1] * fY + 
				  m_pkMatrix->m_afV[2][2] * fZ);
}
// *****************************************************************************
inline void Transform::operator()(
	const Vector &rkSource, Vector& rkDest, bool bNormal) const
{
	Real fX = rkSource.x();
	Real fY = rkSource.y();
	Real fZ = rkSource.z();

	rkDest.x() = m_pkMatrix->m_afV[0][0] * fX + 
				 m_pkMatrix->m_afV[0][1] * fY + 
				 m_pkMatrix->m_afV[0][2] * fZ;
				  
	rkDest.y() = m_pkMatrix->m_afV[1][0] * fX + 
				 m_pkMatrix->m_afV[1][1] * fY + 
				 m_pkMatrix->m_afV[1][2] * fZ;
				  
	rkDest.z() = m_pkMatrix->m_afV[2][0] * fX + 
				 m_pkMatrix->m_afV[2][1] * fY + 
				 m_pkMatrix->m_afV[2][2] * fZ;

	if (bNormal)
		rkDest.normalize();
}
// *****************************************************************************

