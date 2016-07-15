// EmfPk.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "EmfPk.h"


extern "C" {
EMFPK_API	CEmfPk * Create(void){ return new CEmfPk(); }
EMFPK_API	void Poi(CEmfPk *p){ delete p; }
}


// 処理できるか.
bool CEmfPk::entry( const char *target_file )
{
	return false ;
}

// 妥当性検証.
bool CEmfPk::validate()
{
	return false ;
}

// 分析.
bool CEmfPk::analyze()
{
	return false ;
}
