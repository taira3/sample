// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された KPD_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// KPD_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#ifdef KPD_EXPORTS
#define KPD_API __declspec(dllexport)
#else
#define KPD_API __declspec(dllimport)
#endif

#include	"../_base/IPlugin.h"

// このクラスは KPD.dll からエクスポートされました。
class KPD_API CKPD : public IPlugin {
public:
	CKPD(void);
	// TODO: メソッドをここに追加してください。

	int	version()	{ return 2 ;}

	// 処理できるか.
	bool entry( const char *target_file ) ;

	// 妥当性検証.
	bool validate() ;

	// 分析.
	bool analyze() ;

};
