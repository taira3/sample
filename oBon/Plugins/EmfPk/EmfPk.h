#ifdef EMFPK_EXPORTS
#define EMFPK_API __declspec(dllexport)
#else
#define EMFPK_API __declspec(dllimport)
#endif

#include	"../_base/IPlugin.h"

class EmfSpool ;

class CEmfPk : public IPlugin{
public:
	CEmfPk(void)
	{
	}

	int	version()	{ return 2 ;}

	// �����ł��邩.
	bool entry( const char *target_file ) ;

	// �Ó�������.
	bool validate() ;

	// ����.
	bool analyze() ;

private:
	EmfSpool	*p_emfspool ;
	string		tar_file ;
};
