// PCL.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "PCL.h"


extern "C" {
PCL_API	CPCL * Create(void){ return new CPCL(); }
PCL_API	void Poi(CPCL *p){ delete p; }
}

// これは、エクスポートされたクラスのコンストラクタです。
// クラス定義に関しては PCL.h を参照してください。
CPCL::CPCL()
{
	return;
}

// 処理できるか.
bool CPCL::entry( const char *target_file )
{
	return false ;
}

// 妥当性検証.
bool CPCL::validate()
{
	return false ;
}

// 分析.
bool CPCL::analyze()
{
	return false ;
}
