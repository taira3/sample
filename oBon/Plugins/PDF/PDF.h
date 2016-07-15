// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された PDF_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// PDF_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#ifdef PDF_EXPORTS
#define PDF_API __declspec(dllexport)
#else
#define PDF_API __declspec(dllimport)
#endif

#include	"../_base/IPlugin.h"

// このクラスは PDF.dll からエクスポートされました。
class PDF_API CPDF : public IPlugin {
public:
	CPDF(void);
	// TODO: メソッドをここに追加してください。

	int	version()	{ return 2 ;}

	// 処理できるか.
	bool entry( const char *target_file ) ;

	// 妥当性検証.
	bool validate() ;

	// 分析.
	bool analyze() ;

};
