// Emf.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "Emf.h"


extern "C" {
EMF_API	CEmf * Create(void){ return new CEmf(); }
EMF_API	void Poi(CEmf *p){ delete p; }
}

// これは、エクスポートされたクラスのコンストラクタです。
// クラス定義に関しては Emf.h を参照してください。
CEmf::CEmf()
{
	return;
}

// 処理できるか.
bool CEmf::entry( const char *target_file )
{
	return false ;
}

// 妥当性検証.
bool CEmf::validate()
{
	return false ;
}

// 分析.
bool CEmf::analyze()
{
	return false ;
}
