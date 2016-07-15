// PDF.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "PDF.h"


extern "C" {
PDF_API	CPDF * Create(void){ return new CPDF(); }
PDF_API	void Poi(CPDF *p){ delete p; }
}

// これは、エクスポートされたクラスのコンストラクタです。
// クラス定義に関しては PDF.h を参照してください。
CPDF::CPDF()
{
	return;
}

// 処理できるか.
bool CPDF::entry( const char *target_file )
{
	return false ;
}

// 妥当性検証.
bool CPDF::validate()
{
	return false ;
}

// 分析.
bool CPDF::analyze()
{
	return false ;
}
