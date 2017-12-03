#include "stdafx.h"
#include "NodeVar.h"

using namespace std;

#define USE_WIN32API	1

//
NodeVar::NodeVar()
{
}

//
NodeVar::~NodeVar()
{
}

//
NodeVar &NodeVar::operator=(const int v)
{
	this->val.ival = v;
	return(*this);
}

//
NodeVar &NodeVar::operator=(const LPWSTR v)
{
	_let(v);
	return(*this);
}

//
NodeVar &NodeVar::operator=(const LPSTR v)
{
	_let(v);
	return(*this);
}

//
void	NodeVar::_let(const LPWSTR v)
{
	wstr_val = v;
#ifdef USE_WIN32API
	str_val = w2m_winapi(wstr_val);
#else
	str_val = w2m_capi(wstr_val);
#endif
}

//
void	NodeVar::_let(const LPSTR v)
{
	str_val = v;
#ifdef USE_WIN32API
	wstr_val = m2w_winapi(str_val);
#else
	wstr_val = m2w_capi(str_val);
#endif
}

//
void	NodeVar::_let(const int v)
{
	val.ival = v;
}

//
wstring NodeVar::m2w_capi(std::string const& src)
{
	size_t len = 0;
	errno_t err = ::_mbstowcs_s_l(
		&len,
		NULL,		0,					// dest
		src.data(),	_TRUNCATE,			// src
		::_create_locale(LC_ALL, "jpn"));

	wstring	result;

	if (err == 0 && len >0 )
	{
		wchar_t	*dest = new wchar_t[len];

		::_mbstowcs_s_l(
			&len, 
			dest, 		len,			// dest
			src.data(),	_TRUNCATE,		// src
			::_create_locale(LC_ALL, "jpn"));
	
		result = dest;

		delete[] dest;
	}

	return result;
}

//
string NodeVar::w2m_capi(std::wstring const& src)
{
	size_t len = 0;
	errno_t err = ::_wcstombs_s_l(
		&len,
		NULL,		0,			// dest
		src.data(),	_TRUNCATE,	// src
		::_create_locale(LC_ALL, "jpn"));

	string	result;

	if (err == 0 && len > 0)
	{
		char *dest = new char[len];

		::_wcstombs_s_l(
			&len,
			dest,		len,		// dest
			src.data(),	_TRUNCATE,	// src
			::_create_locale(LC_ALL, "jpn"));

		result = dest;

		delete[] dest;
	}

	return result;
}

//
wstring NodeVar::m2w_winapi(string const& src)
{
	int len = ::MultiByteToWideChar(
		CP_ACP, 
		0U, 
		src.data(), -1,			// src
		nullptr, 	0U);		// dest

	wstring	result;

	if (len)
	{
		wchar_t	*dest = new wchar_t[len];

		::MultiByteToWideChar(
			CP_ACP, 
			0U, 
			src.data(), -1,		// src
			dest, 		len);	// dest

		result = dest;

		delete[] dest;
	}

	return result;
}

// wide char to multi char. 
string NodeVar::w2m_winapi(wstring const& src)
{
	int len = ::WideCharToMultiByte(
		CP_ACP, 
		0U,
		src.data(),	-1,			// src
		nullptr,	0,			// dest
		nullptr,
		nullptr);

	string	result;

	if (len)
	{
		char *dest = new char[len];
		
		::WideCharToMultiByte(
			CP_ACP,
			0U,
			src.data(),	-1,		// src
			dest,		len,	// dest
			nullptr,
			nullptr);

		result = dest;

		delete[] dest;
	}

	return result;
}
