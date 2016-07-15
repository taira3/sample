// KPD.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "KPD.h"


extern "C" {
KPD_API	CKPD * Create(void){ return new CKPD(); }
KPD_API	void Poi(CKPD *p){ delete p; }
}

// これは、エクスポートされたクラスのコンストラクタです。
// クラス定義に関しては KPD.h を参照してください。
CKPD::CKPD()
{
	return;
}

// 処理できるか.
bool CKPD::entry( const char *target_file )
{
	return false ;
}

// 妥当性検証.
bool CKPD::validate()
{
	return false ;
}

// 分析.
bool CKPD::analyze()
{
	return false ;
}
