// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された PCL_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// PCL_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#ifdef PCL_EXPORTS
#define PCL_API __declspec(dllexport)
#else
#define PCL_API __declspec(dllimport)
#endif

#include	"../_base/IPlugin.h"

// このクラスは PCL.dll からエクスポートされました。
class PCL_API CPCL {
public:
	CPCL(void);
	// TODO: メソッドをここに追加してください。

	int	version()	{ return 2 ;}

	// 処理できるか.
	bool entry( const char *target_file ) ;

	// 妥当性検証.
	bool validate() ;

	// 分析.
	bool analyze() ;

};
