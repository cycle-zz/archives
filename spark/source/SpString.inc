/*
// ---------------------------------------------------------------------------
inline bool SpString::operator==(const SpString& rkStr)
{
	return (compare(rkStr) == 0);
}
// ---------------------------------------------------------------------------
inline bool SpString::operator!=(const SpString& rkStr)
{
	return (compare(rkStr) != 0);
}
*/
// ---------------------------------------------------------------------------
inline SpString& SpString::operator=(const SpString& rkStr)
{
	assign(rkStr);
	return (*this);
}
// ---------------------------------------------------------------------------
inline SpString& SpString::operator=(const std::string& rkStr)
{
	assign(rkStr);
	return (*this);
}
// ---------------------------------------------------------------------------
inline SpString& SpString::operator=(const char *acS)
{
	assign(acS);
	return (*this);
}
// ---------------------------------------------------------------------------
inline SpString& SpString::operator=(char c)
{
	assign(1,c);
	return (*this);
}
// ---------------------------------------------------------------------------
inline SpString& SpString::operator+=(const SpString& rkStr)
{
	append(rkStr);
	return (*this);
}
// ---------------------------------------------------------------------------
inline SpString& SpString::operator+=(const std::string& rkStr)
{
	append(rkStr);
	return (*this);
}
// ---------------------------------------------------------------------------
inline SpString& SpString::operator+=(const char *s)
{
	append(s);
	return (*this);
}
// ---------------------------------------------------------------------------
inline SpString& SpString::operator+=(char c)
{
	append(1,c);
	return (*this);
}
// ---------------------------------------------------------------------------
inline SpString& SpString::operator+(const SpString& rkStr)
{
	append(rkStr);
	return (*this);
}
// ---------------------------------------------------------------------------
inline SpString& SpString::operator+(const std::string& rkStr)
{
	append(rkStr);
	return (*this);
}
// ---------------------------------------------------------------------------
inline SpString& SpString::operator+(const char *s)
{
	append(s);
	return (*this);
}
// ---------------------------------------------------------------------------
inline SpString& SpString::operator+(char c)
{
	append(1,c);
	return (*this);
}
// ---------------------------------------------------------------------------
inline bool SpString::operator<(const SpString& rkStr)
{
	return(compare(rkStr) < 0);
};
// ---------------------------------------------------------------------------
inline SpString::operator const char* () const
{
	return c_str();
}
// ---------------------------------------------------------------------------
template< class Class >
SpString& SpString::add( const Class& rtValue)
{
	SpStringStreamType kStream;
	kStream << rtValue;
	*this += kStream.str();
	return *this;
}
// ---------------------------------------------------------------------------
