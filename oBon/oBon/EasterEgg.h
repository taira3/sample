#pragma once

#include "stdafx.h"

#include <stdarg.h>

#include	<winuser.h>
#include	<map>
#include	<list>
#include	<vector>

using namespace std;

//--- from winuser.h
/*
 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
 * 0x40 : unassigned
 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
 */
#if 0
#define VK_A           0x41
#define VK_B           0x42
#define VK_C           0x43
#define VK_D           0x44

#endif // 0
#define	VK_TERM			-1  

typedef struct _val_tag {
	int		type ;
	void	*val;
} val_tag ;

typedef map<int, void*> node ;

class EasterEgg
{
public:
	EasterEgg(void);
	~EasterEgg(void);

private:
	HWND	hWnd ;
	UINT	_msg;

	//
	class	_cmd2 {
	public:
		_cmd2( int first, ... )
		{
			msg = first;
			va_list args;
			va_start(args, first);
			int	i = VK_TERM ;
			while( (i = va_arg( args, int)) != VK_TERM )
			{
				cmd.push_back(i);
			}
			va_end(args);

			OutputDebugString(_T("constructor\n"));
		};

		~_cmd2(void)
		{
			OutputDebugString(_T("destructor\n"));
		};

		int		msg ;
		vector<int>	cmd;
	} ;
	typedef	_cmd2*	_pcmd2;

	class	_state {
	public:
		_state(){
		};

		~_state(void){
		};

	private:
		map<int, _state >	status ;
	public:
//		add( int key );
	};

private:
	bool	OpenKeyTbl();


public:
	bool	knock( int key );
	UINT	msg()	{ return _msg; }
};
