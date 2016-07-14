// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された PEMF_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// PEMF_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#ifdef PEMF_EXPORTS
#define PEMF_API __declspec(dllexport)
#else
#define PEMF_API __declspec(dllimport)
#endif

#include	"../Bon/IPlugin.h"

class EmfSpool ;

// このクラスは PEmf.dll からエクスポートされました。
//class PEMF_API CPEmf : public IPlugin{
class CPEmf : public IPlugin{
public:
	CPEmf(void)
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
