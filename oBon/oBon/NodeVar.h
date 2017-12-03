#pragma once
#include	<string>
//#include	<vector>

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
	} val ;
	string	str_val;
	wstring	wstr_val;
	enum {
		TYPE_INT,
		TYPE_PVOID
	};

public:
	// ‘ã“ü‰‰ŽZŽq
	NodeVar &operator=(const int v);
	NodeVar &operator=(const LPWSTR v);
	NodeVar &operator=(const LPSTR v);

private:

	void	_let(const LPWSTR v);
	void	_let(const LPSTR v);
	void	_let(const int v);

	std::wstring m2w_capi(std::string const& src);
	std::string w2m_capi(std::wstring const& src);
	std::wstring m2w_winapi(std::string const& src);
	std::string w2m_winapi(std::wstring const& src);

};

