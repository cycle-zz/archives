//******************************************************************************
inline Vector dg::FaceForward( 
	const Vector& rkN, 
	const Vector& rkI)
{
	return (Dot(rkI, rkN) > 0) ? -rkN : rkN;
}

//******************************************************************************
inline Vector dg::FaceForward( 
	const Vector& rkN, 
	const Vector& rkI, 
	const Vector& rkRef)
{
	return (Dot(rkI, rkRef) > 0) ? -rkN : rkN;
}

//******************************************************************************
