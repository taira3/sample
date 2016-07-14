// PEmf.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "PEmf.h"
#include "EmfSpool.h"

class	Emfspool ;

extern "C" {
PEMF_API	CPEmf * Create(void){ return new CPEmf(); }
PEMF_API	void Poi(CPEmf *p){ delete p; }
}

// 処理できるか.
bool CPEmf::entry( const char *target_file )
{
	// EMFSpool の解析処理.
	EmfSpool	*emfspool = new EmfSpool((char*)target_file);

	// 指定されたファイルがEMFSpool形式か妥当性チェック.
	bool	res = emfspool->valid() ;

	if( res )
	{
		this->tar_file = string(target_file) ;
	}

	delete emfspool ;

	return res ;
}

// 妥当性検証.
bool CPEmf::validate()
{
	return true ;
}

// 分析.
bool CPEmf::analyze()
{
	cout << "CPEmf::analyze." << endl ;

	// EMFSpool の解析処理.
	EmfSpool	*emfspool = new EmfSpool((char*)this->tar_file.c_str());

	bool	res = false ;

	// 解析結果出力先の環境を整えて.
	if( emfspool->create_output_env((char*)this->tar_file.c_str()) )
	{
		// 解析開始.
		res = emfspool->parse();
	}

	delete emfspool ;

	return res ;
}
