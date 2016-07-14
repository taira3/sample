#pragma once

#include <vector>
#include <algorithm>

#include "IPlugin.h"

#include "common.h"

#include <string>
using namespace std;

// Bon Framework
//   DLL Manager.



class BonFW
{
public:
	BonFW(void);
	virtual ~BonFW(void);

	// // DLL�̊m�F.
	bool	load();
	void	dispose();

	bool	entry( string target );
	bool	analyze();

	bool	createWorkspace();

	void	set_target( string val )	{ targetFilename = val ; }

private:
	vector<HMODULE> m_handles; // DLL�̃n���h�����L��

	class PluginInfo {
	public:
		PluginInfo():
		  hMod(NULL),
		  pInst(NULL)
		  {};
		PluginInfo(HMODULE v1, IPlugin *v2 ):
		  hMod(v1),
		  pInst(v2)
		  {};

		~PluginInfo(){}
//	private:
	public:	// 
		HMODULE	hMod ;
		IPlugin	*pInst ;
	};

	vector<PluginInfo*>	plugins ;
	PluginInfo			*cur_plugin ;
	string				targetFilename ;

private:
	PluginInfo* getPluginInfo( string dllName );

};
