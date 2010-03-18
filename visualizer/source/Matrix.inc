//******************************************************************************
inline const Real * Matrix::values() const	
{ 
	return ( Real * ) m_afV; 
}
//******************************************************************************
inline Real * Matrix::values() 
{ 
	return ( Real * ) m_afV; 
}
//******************************************************************************
inline void Matrix::identity()
{
	m_afV[0][1] = m_afV[0][2] = m_afV[0][3] =
	m_afV[1][0] = m_afV[1][2] = m_afV[1][3] =
	m_afV[2][0] = m_afV[2][1] = m_afV[2][3] =
	m_afV[3][0] = m_afV[3][1] = m_afV[3][2] = 0.0f;
	m_afV[0][0] = m_afV[1][1] = m_afV[2][2] = m_afV[3][3] = 1.0f;
}
//******************************************************************************
inline void Matrix::setValues(const Real** afV)
{
	m_afV[0][0] = afV[0][0];
	m_afV[0][1] = afV[0][1];
	m_afV[0][2] = afV[0][2];
	m_afV[0][3] = afV[0][3];
	m_afV[1][0] = afV[1][0];
	m_afV[1][1] = afV[1][1];
	m_afV[1][2] = afV[1][2];
	m_afV[1][3] = afV[1][3];
	m_afV[2][0] = afV[2][0];
	m_afV[2][1] = afV[2][1];
	m_afV[2][2] = afV[2][2];
	m_afV[2][3] = afV[2][3];
	m_afV[3][0] = afV[3][0];
	m_afV[3][1] = afV[3][1];
	m_afV[3][2] = afV[3][2];
	m_afV[3][3] = afV[3][3];
}
//******************************************************************************
inline void Matrix::setValues(const Real afV[16])
{
	m_afV[0][0] = afV[0];
	m_afV[0][1] = afV[1];
	m_afV[0][2] = afV[2];
	m_afV[0][3] = afV[3];
	m_afV[1][0] = afV[4];
	m_afV[1][1] = afV[5];
	m_afV[1][2] = afV[6];
	m_afV[1][3] = afV[7];
	m_afV[2][0] = afV[8];
	m_afV[2][1] = afV[9];
	m_afV[2][2] = afV[10];
	m_afV[2][3] = afV[11];
	m_afV[3][0] = afV[12];
	m_afV[3][1] = afV[13];
	m_afV[3][2] = afV[14];
	m_afV[3][3] = afV[15];
}
//******************************************************************************
inline void Matrix::setBase(const Vector &rkW, const Vector &rkV, const Vector &rkU)
{
	m_afV[0][0] = rkW.x(); m_afV[0][1] = rkW.y(); m_afV[0][2] = rkW.z();
	m_afV[1][0] = rkV.x(); m_afV[1][1] = rkV.y(); m_afV[1][2] = rkV.z();
	m_afV[2][0] = rkU.x(); m_afV[2][1] = rkU.y(); m_afV[2][2] = rkU.z();

	m_afV[0][3] = m_afV[1][3] = m_afV[2][3] = 0;
	m_afV[3][0] = m_afV[3][1] = m_afV[3][2] = 0;
	m_afV[3][3] = 1.0;
}
//******************************************************************************
inline void Matrix::getBase(Vector &rkW, Vector &rkV, Vector &rkU) const
{
	rkW[0] = m_afV[0][0]; rkW[1] = m_afV[0][1]; rkW[2] = m_afV[0][2];
	rkU[0] = m_afV[1][0]; rkU[1] = m_afV[1][1]; rkU[2] = m_afV[1][2];
	rkV[0] = m_afV[2][0]; rkV[1] = m_afV[2][1]; rkV[2] = m_afV[2][2];
}
//******************************************************************************
inline void Matrix::zero()
{
	m_afV[0][0] = 0.0f;
	m_afV[0][1] = 0.0f;
	m_afV[0][2] = 0.0f;
	m_afV[0][3] = 0.0f;
	m_afV[1][0] = 0.0f;
	m_afV[1][1] = 0.0f;
	m_afV[1][2] = 0.0f;
	m_afV[1][3] = 0.0f;
	m_afV[2][0] = 0.0f;
	m_afV[2][1] = 0.0f;
	m_afV[2][2] = 0.0f;
	m_afV[2][3] = 0.0f;
	m_afV[3][0] = 0.0f;
	m_afV[3][1] = 0.0f;
	m_afV[3][2] = 0.0f;
	m_afV[3][3] = 0.0f;
}
//******************************************************************************
// end file: Matrix.inl
