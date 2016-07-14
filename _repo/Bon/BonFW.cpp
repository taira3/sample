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
 * Plugin�̓ǂݍ���.
 * @brief Plugin-DLL���m�F���APlugin�ł���Εێ�����.
 * @detail �ێ��������̓f�X�g���N�^�ŊJ������.���ׁ̈APlugin-DLL�̓���ւ��̓A�v���N�����͕s�Ƃ���.
 */
bool BonFW::load()
{
	// �����Ɠ����ꏊ�ɂ���dll��S�Č��Ă݂�.
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
			// �f�B���N�g���͑ΏۊO(�ʏ햳���Ƃ͎v����).
			if( FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				continue ;
			}

			// Plugin-DLL���`�F�b�N
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
 * Plugin�̊J��.
 * @brief Plugin�Ƃ��ēǂݍ��񂾏����J������.
 * @detail �X��Plugin-DLL�̊J�������́A���ꂼ��̊J������(Poi)�ɈϏ�����.
 */
void BonFW::dispose()
{
	// DLL�̊J��.
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
 * Plugin�̎擾.
 * @brief Plugin-DLL�𔻒f���A�ǂݍ���.
 * @detail DLL����Instance��������(Create)������΁APlugin-DLL�ƌ��Ȃ�.
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
				// Plugin����Instance�𐶐����邱��.
				i = (*create)();
				i->version();

				res = new PluginInfo( hMod, i ) ;
			}
			catch(...)
			{
				// �������O�͎��s�ƌ��Ȃ��A�Ώۂ�Plugin�͎g�p���Ȃ�.
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
	// �^�[�Q�b�g�Ɠ������O�̃t�H���_�����[�N�X�y�[�X�Ƃ���.
	//   OS�̐����ɂ��Ă͍l�����Ȃ�.
	

	return true ;
}
