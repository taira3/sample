#include "StdAfx.h"
#include "BonFW.h"

class PathString ;

BonFW::BonFW(void)
{
}

BonFW::~BonFW(void)
{
	dispose();
}

/**
 * @fn
 * Pluginの読み込み.
 * @brief Plugin-DLLか確認し、Pluginであれば保持する.
 * @detail 保持した情報はデストラクタで開放する.その為、Plugin-DLLの入れ替えはアプリ起動時は不可とする.
 */
bool BonFW::load()
{
	// 自分と同じ場所にあるdllを全て見てみる.
    CHAR   szPath[ _MAX_PATH ] = { 0 };
	DWORD	pathSize = ::GetModuleFileNameA( NULL, szPath, MAX_PATH );

	PathString	ps(szPath);
	ps.add_path("BonPack");
	ps.rep_fnam("*");
	ps.rep_ext("dll");

	WIN32_FIND_DATAA FindFileData;
	HANDLE	hFind = FindFirstFileA(ps.c_str(), &FindFileData);
	if( hFind )
	{
		do 
		{
			// ディレクトリは対象外(通常無いとは思うが).
			if( FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				continue ;
			}

			// Plugin-DLLかチェック
			PluginInfo	*pi = getPluginInfo( string(FindFileData.cFileName) ) ;
			if( pi != NULL )
			{
				plugins.push_back( pi );
			}
		}
		while( FindNextFileA(hFind, &FindFileData) );
	}

	return false;
}

/**
 * @fn
 * Pluginの開放.
 * @brief Pluginとして読み込んだ情報を開放する.
 * @detail 個々のPlugin-DLLの開放処理は、それぞれの開放処理(Poi)に委譲する.
 */
void BonFW::dispose()
{
	// DLLの開放.
	for each (PluginInfo* it in plugins)
	{
		POII	poi = (POII) GetProcAddress(it->hMod, "Poi"); 
		if( poi != NULL )
		{
			poi( it->pInst );
		}

		FreeLibrary( it->hMod );

		delete it ;
    }
}

/**
 * @fn
 * Pluginの取得.
 * @brief Plugin-DLLを判断し、読み込む.
 * @detail DLL内にInstance生成処理(Create)があれば、Plugin-DLLと見なす.
 */
BonFW::PluginInfo* BonFW::getPluginInfo( string dllName )
{
	PluginInfo	*res = NULL ;

	HMODULE	hMod = LoadLibraryA( dllName.c_str() );
	if( hMod )
	{
		CREATEI	create = (CREATEI) GetProcAddress(hMod, "Create"); 
		if( create != NULL )
		{
			IPlugin *i = NULL ;
			try
			{
				// Plugin側でInstanceを生成すること.
				i = (*create)();
				i->version();

				res = new PluginInfo( hMod, i ) ;
			}
			catch(...)
			{
				// あらゆる例外は失敗と見なし、対象のPluginは使用しない.
				if( i )
				{
					delete i ;
				}
			}
		}

		if( res == NULL )
		{
			FreeLibrary( hMod );
		}
	}
	return res;
}

// in : taeget ... filename
bool BonFW::entry( string target )
{
	bool	res = false ;

	for each (PluginInfo* it in plugins)
	{
		if( it->pInst->entry( target.c_str() ) )
		{
			res = true ;
			this->cur_plugin = it ;
			this->set_target( target );
			break;
		}
    }

	return res ;
}

//
bool	BonFW::analyze()
{
	bool	res = false ;
	if( this->cur_plugin )
	{
		res = this->cur_plugin->pInst->analyze();
	}
	return res ;

	//return !this->cur_plugin ? false : this->cur_plugin->pInst->analyze();
}

bool	BonFW::createWorkspace()
{
	// ターゲットと同じ名前のフォルダをワークスペースとする.
	//   OSの制限については考慮しない.
	

	return true ;
}
