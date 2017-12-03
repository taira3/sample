#include "StdAfx.h"
#include "EasterEgg.h"

#include <initializer_list>

#pragma warning(disable : 4200)  

EasterEgg::EasterEgg(void)
{
	OpenKeyTbl();
}

EasterEgg::~EasterEgg(void)
{
}

//
bool EasterEgg::OpenKeyTbl()
{
	
	struct	_cmd_{
		int		msg ;
		std::vector<int>	cmd;
	};

	class keys
	{
	public:
		keys()
		{
			msg = 0;
		};
		keys(std::initializer_list<struct _cmd_> c)
		{
			for (struct _cmd_ o : c)
			{
				this->create(o);
			}
		};
		keys(std::initializer_list<int> c)
		{
			for (int o : c)
			{
				//this->create(o);
			}
		};

		~keys() {};

	private:
		std::map<int, keys*> m;
		int		msg;

		//
		void create(struct _cmd_ &o)
		{
			if (o.cmd.size() == 0)
			{
				this->msg = o.msg;
				return;
			}

			//
			int k = o.cmd[0];
			o.cmd.erase(o.cmd.begin());

			//
			if (this->m.count(k) == 0)
			{
				this->m.insert(std::make_pair(k, new keys()));
			}

			return this->m[k]->create(o);
		}

		

	};

	keys	r({
		{ 1,{ 'A',2,3,4,5,1 } },
		{ 1,{ 1,2,3,4 } }
	});

	keys	r1(
//	{
//	{ 1, 1,2,3,4,5,1 },
	{ 1, 1, 2, 3, 4, 5, 1  }
//	}
	);

	return true;
}

//
bool	EasterEgg::knock( int key )
{
	return true ;
}
