// start file: Color.cpp

// #############################################################################
// #
// # Derek Gerstmann
// # dgerstma@acm.org
// #
// #############################################################################

// headers
#include "Color.h"

using namespace dg;

////////////////////////////////////////////////////////////////////////////////
// Color implementation
////////////////////////////////////////////////////////////////////////////////

//******************************************************************************
Color::Color()
{
	m_adC[0] = 0.0;
	m_adC[1] = 0.0;
	m_adC[2] = 0.0;
	m_adC[3] = 1.0;
}
//******************************************************************************
Color::Color(Real dR, Real dG, Real dB, Real dA)
{
	m_adC[0] = dR;
	m_adC[1] = dG;
	m_adC[2] = dB;
	m_adC[3] = dA;
}
//******************************************************************************
Color::Color(const Color & rkColor)
{
	m_adC[0] = rkColor.m_adC[0];
	m_adC[1] = rkColor.m_adC[1];
	m_adC[2] = rkColor.m_adC[2];
	m_adC[3] = rkColor.m_adC[3];
}
//******************************************************************************
Color Color::operator+ (const Color & rkColor) const
{
	Color kSum(
		m_adC[0] + rkColor.m_adC[0],
		m_adC[1] + rkColor.m_adC[1],
		m_adC[2] + rkColor.m_adC[2]
	);
	return kSum;
}
//******************************************************************************
void Color::operator++ (void)
{
	++m_adC[0];
	++m_adC[1];
	++m_adC[2];
	//++m_adC[3];
}
//******************************************************************************
void Color::operator+= (const Color & rkColor)
{
	m_adC[0] += rkColor.m_adC[0];
	m_adC[1] += rkColor.m_adC[1];
	m_adC[2] += rkColor.m_adC[2];
	//m_adC[3] += rkColor.m_adC[3];
}
//******************************************************************************
Color Color::operator- () const
{
	Color kNegate(
		-m_adC[0],
		-m_adC[1],
		-m_adC[2]
	);
	return kNegate;
}
//******************************************************************************
Color Color::operator- (const Color & rkColor) const
{
	Color kDiff(
		m_adC[0] - rkColor.m_adC[0],
		m_adC[1] - rkColor.m_adC[1],
		m_adC[2] - rkColor.m_adC[2]
	);
	return kDiff;
}
//******************************************************************************
void Color::operator-- (void)
{
	--m_adC[0];
	--m_adC[1];
	--m_adC[2];
	//--m_adC[3];
}
//******************************************************************************
void Color::operator-= (const Color & rkColor)
{
	m_adC[0] -= rkColor.m_adC[0];
	m_adC[1] -= rkColor.m_adC[1];
	m_adC[2] -= rkColor.m_adC[2];
	//m_adC[3] -= rkColor.m_adC[3];
}
//******************************************************************************
Color Color::operator* (const Color & rkColor) const
{
	Color kProd(
		m_adC[0] * rkColor.m_adC[0],
		m_adC[1] * rkColor.m_adC[1],
		m_adC[2] * rkColor.m_adC[2]
	);
	return kProd;
}
//******************************************************************************
void Color::operator*= (const Color & rkColor)
{
	m_adC[0] *= rkColor.m_adC[0];
	m_adC[1] *= rkColor.m_adC[1];
	m_adC[2] *= rkColor.m_adC[2];
	//m_adC[3] *= rkColor.m_adC[3];
}
//******************************************************************************
Color Color::operator* (const Int scalar) const
{
	Color kProd(
		m_adC[0] * scalar,
		m_adC[1] * scalar,
		m_adC[2] * scalar
	);
	return kProd;
}
//******************************************************************************
void Color::operator*= (const Int scalar)
{
	m_adC[0] *= scalar;
	m_adC[1] *= scalar;
	m_adC[2] *= scalar;
	m_adC[3] *= scalar;
}
//******************************************************************************
Color Color::operator* (const Real scalar) const
{
	Color kProd(
		m_adC[0] * scalar,
		m_adC[1] * scalar,
		m_adC[2] * scalar
	);
	return kProd;
}
//******************************************************************************
void Color::operator*= (const Real scalar)
{
	m_adC[0] *= scalar;
	m_adC[1] *= scalar;
	m_adC[2] *= scalar;
	//m_adC[3] *= scalar;
}
//******************************************************************************
void Color::operator=(const Color & rkColor)
{
	m_adC[0] = rkColor.m_adC[0];
	m_adC[1] = rkColor.m_adC[1];
	m_adC[2] = rkColor.m_adC[2];
	m_adC[3] = rkColor.m_adC[3];
}
//******************************************************************************
Bool Color::operator==(const Color & rkColor) const
{
	return(
		m_adC[0] == rkColor.m_adC[0] &&
		m_adC[1] == rkColor.m_adC[1] &&
		m_adC[2] == rkColor.m_adC[2] &&
		m_adC[3] == rkColor.m_adC[3]
	);
}
//******************************************************************************
Bool Color::operator!=(const Color & rkColor) const
{
	return( !(*this == rkColor));
}
//******************************************************************************

Color dg::operator* ( Real fScalar, const Color& rkV )
{
	return Color( fScalar * rkV.r(),
				   fScalar * rkV.g(),
				   fScalar * rkV.b() );
}

Color dg::Clamp(const Color& rkV, Real fMin, Real fMax)
{
	Color kC(rkV);
	kC.r() = (rkV.r() > fMax) ? fMax : ((rkV.r() > fMin) ? fMin : rkV.r());
	kC.g() = (rkV.g() > fMax) ? fMax : ((rkV.g() > fMin) ? fMin : rkV.g());
	kC.b() = (rkV.b() > fMax) ? fMax : ((rkV.b() > fMin) ? fMin : rkV.b());
	return kC;
}

//******************************************************************************
const Color Color::BLACK = Color(0.0f, 0.0f, 0.0f);
const Color Color::GRAY = Color(0.5f, 0.5f, 0.5f);
const Color Color::WHITE = Color(1.0f, 1.0f, 1.0f);
//******************************************************************************

// end file: Color.cpp
