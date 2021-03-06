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

	// 処理できるか.
	bool entry( const char *target_file ) ;

	// 妥当性検証.
	bool validate() ;

	// 分析.
	bool analyze() ;

private:
	EmfSpool	*p_emfspool ;
	string		tar_file ;
};
