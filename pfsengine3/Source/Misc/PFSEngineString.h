#pragma once
#include "SFML/System/String.hpp"
#include <iostream>
#include <string>
// ----------------------------------------------------------------------------
/**
 * Wrapper class for strings.
 */
class PString
{
public:
	PString(const std::string& str = std::string());
	PString(const char* cstr);

	const char* CStr() const;
	size_t Size() const;

	template<typename ... Args>
	static PString Printf(const char * format, Args ... args);

	static PString FromInt(int i);
	static PString FromFloat(float f);

public:
	inline PString operator=(const PString& other);
	inline PString operator=(const char* cstr);

	/**
	 * Concatenation.
	 */
	inline PString operator+(const PString& other) const;
	inline PString operator+(const char* other) const;
	inline PString operator+=(const PString& other);
	inline PString operator+=(const char* other);

	friend inline std::ostream& operator<<(std::ostream& os, const PString& str);

	friend inline bool operator<(const PString& left, const PString& right);
	friend inline bool operator==(const PString& left, const PString& right);
	friend inline bool operator!=(const PString& left, const PString& right);

	inline operator sf::String() const;
	inline operator std::string() const;

	inline const char* operator*() const;

private:
	std::string _cppstr;
};
// ----------------------------------------------------------------------------
template<typename ... Args>
PString PString::Printf(const char * format, Args ... args)
{
	size_t size = snprintf(nullptr, 0, format, args ...) + 1; // Extra space for '\0'

	if (size <= 0)
	{
		throw std::runtime_error("Error during formatting."); 
	}
	
	std::unique_ptr<char[]> buf(new char[size]);
	
	snprintf(buf.get(), size, format, args ...);
	
	return PString(std::string(buf.get(), buf.get() + size - 1)); // We don't want the '\0' inside
}
// ----------------------------------------------------------------------------
PString PString::operator=(const PString& other)
{
	_cppstr = other._cppstr;

	return *this;
}
// ----------------------------------------------------------------------------
PString PString::operator=(const char* cstr)
{
	_cppstr = cstr;

	return *this;
}
// ----------------------------------------------------------------------------
PString PString::operator+(const PString& other) const
{
	return PString(_cppstr + other._cppstr);
}
// ----------------------------------------------------------------------------
PString PString::operator+(const char* other) const
{
	return PString(_cppstr + other);
}
// ----------------------------------------------------------------------------
PString PString::operator+=(const PString& other)
{
	_cppstr += other._cppstr;
	return *this;
}
// ----------------------------------------------------------------------------
PString PString::operator+=(const char* other)
{
	_cppstr += other;
	return *this;
}
// ----------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const PString& str)
{
	return os << str._cppstr;
}
// ----------------------------------------------------------------------------
bool operator<(const PString& left, const PString& right)
{
	return left._cppstr < right._cppstr;
}
// ----------------------------------------------------------------------------
bool operator==(const PString& left, const PString& right)
{
	return left._cppstr == right._cppstr;
}
// ----------------------------------------------------------------------------
bool operator!=(const PString& left, const PString& right)
{
	return !(left < right);
}
// ----------------------------------------------------------------------------
PString::operator sf::String() const
{
	return sf::String(_cppstr);
}
// ----------------------------------------------------------------------------
PString::operator std::string() const
{
	return _cppstr;
}
// ----------------------------------------------------------------------------
const char* PString::operator*() const
{
	return _cppstr.c_str();
}
// ----------------------------------------------------------------------------