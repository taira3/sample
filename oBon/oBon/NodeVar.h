#pragma once
#include	<string>

using namespace	std;

class NodeVar
{
public:
	NodeVar() ;
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

	NodeVar &operator=(const LPTSTR v) {
		//this->val.ival = v;
		return(*this);
	};
	//NodeVar(const NodeVar&) = delete;
};

