#pragma once
#include	<string>

using namespace	std;

class NodeVar
{
public:
	NodeVar();
	NodeVar(LPWSTR v) { _let(v); }
	NodeVar(LPSTR v) { _let(v); }
	NodeVar(int v) { _let(v); }
	~NodeVar();

	//default;
private:
	int	type;
	union
	{
		void*	vpval;
		int		ival;
		string	*szval;
//		wstring	wszval;
	} val ;
	enum {
		TYPE_INT,
		TYPE_PVOID
	};

public:
	// ‘ã“ü‰‰ŽZŽq
	NodeVar &operator=(const int v) {
		this->val.ival = v;
		return(*this);
	};

#if 0
	NodeVar &operator=(const LPTSTR v) {
		//this->val.ival = v;
		/*
		TCHAR  infoBuf[32767]
GetWindowsDirectory(infoBuf, 32767); 
wstring test(&infoBuf[0]); //convert to wstring
string test2(test.begin(), test.end()); //and convert to string.
*/
		//wchar_t  LPWSTR


		return(*this);
	};
#endif

	NodeVar &operator=(const LPWSTR v) {
		_let(v);
		return(*this);
	};

	NodeVar &operator=(const LPSTR v) {
		_let(v);
		return(*this);
	};

private:

	NodeVar	_let(const LPWSTR v)
	{
		return(*this);
	}
	NodeVar	_let(const LPSTR v)
	{
		return(*this);
	}
	NodeVar	_let(const int v)
	{
		return(*this);
	}
	//NodeVar(const NodeVar&) = delete;
};

