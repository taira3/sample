#include "StdAfx.h"
#include "EasterEgg.h"

#pragma warning(disable : 4200)  

EasterEgg::EasterEgg(void)
{
	OpenKeyTbl();
}

EasterEgg::~EasterEgg(void)
{
}

bool EasterEgg::OpenKeyTbl()
{
	
	struct	_cmd_{
		int		msg ;
		int	cmd[];
	} *cmds ;
/*	
	= {
		{1,  {1,2,3,4,5,1} },
		{1,  {1,2,3,4} },
	};
*/
	
//	VKEY_UP
//vector<int> aa{1, 2, 3, 4};

	int a[] = { 1,2,3 };
//	a = { 5,2,3 };

//	test( new []int(){ VK_UP,2,3,4,5, VK_TERM } );
//	test( { VK_UP,2,3,4,5, VK_TERM } );
//	test( a );
//	test( a = {3,4});

//	vector<int> v = {1,2,3,4,5};
//std::vector<int> v = {1, 2, 3, 4};
//	test2( v );

	test3( new _cmd2(1,2,3,VK_TERM));

	return true;
}
void	EasterEgg::test( int tbl[] )
{
	
	return ;
}

void	EasterEgg::test2( vector<int> a )
{
	return ;
}
void	EasterEgg::test3( _cmd2 *p )
{

	if( p != NULL )
	{
		delete p ;
	}

	return ;
}
bool	EasterEgg::knock( int key )
{
	return true ;
}
