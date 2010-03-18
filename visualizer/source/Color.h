// start file: Color.h

// #############################################################################
// #
// # Derek Gerstmann
// # dgerstma@acm.org
// #
// #############################################################################

#ifndef DG_COLOR_H
#define DG_COLOR_H

// headers
#include "DataTypes.h"

// -----------------------------------------------------------------------------

namespace dg
{
// -----------------------------------------------------------------------------

// #############################################################################
// Color - floating point color class with red, green, blue, and alpha components
// #############################################################################

// -----------------------------------------------------------------------------
class Color
{

public:

	Color();
	Color(Real dR, Real dG, Real dB, Real dA=1.0);
	Color(const Color & rkColor);

	Real r() const;
	Real g() const;
	Real b() const;
	Real a() const;
	Real& r();
	Real& g();
	Real& b();
	Real& a();

	Real operator()(UInt uiC) const;
	Real operator[](UInt uiC) const;
	Real& operator()(UInt uiC);
	Real& operator[](UInt uiC);
	Real getComponent(UInt uiC) const;
	const Color& value();
	Real* values();

	void set(const Color& v);
	void set(Real r, Real g, Real b, Real a=1.0);
	void setRed(Real r);
	void setGreen(Real g);
	void setBlue(Real b);
	void setAlpha(Real a);
	void setComponent(Real n, UInt c);

	void operator=(const Color & rkColor);
	Bool operator==(const Color & rkColor) const;
	Bool operator!=(const Color & rkColor) const;
	Color operator+ (const Color & rkColor) const;
	void operator++ (void);
	void operator+= (const Color & rkColor);
	Color operator- () const;
	Color operator- (const Color & rkColor) const;
	void operator-- (void);
	void operator-= (const Color & rkColor);
	Color operator* (const Color & rkColor) const;
	void operator*= (const Color & rkColor);
	Color operator* (const Int scalar) const;
	void operator*= (const Int scalar);
	Color operator* (const Real scalar) const;
	void operator*= (const Real scalar);

	void zero();
	void negate();
	
	static const Color BLACK;
	static const Color GRAY;
	static const Color WHITE;
	
private:

	Real m_adC[4];	// RGBA
	
}; // end class: Color

//******************************************************************************


Color operator* (Real fScalar, const Color& rkV);
Color Clamp(const Color& rkV, Real fMin, Real fMax);


#include "Color.inc"

//******************************************************************************

} // end namespace: dg

#endif // endif: DG_COLOR_H

// end file: Color.h
