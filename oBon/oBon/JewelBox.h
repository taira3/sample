#pragma once
#include	<string>

using namespace	std;
// Plugin

class JewelBox
{
public:
	//JewelBox();
	JewelBox(string v1) :
		relPath(v1)
	{};
	~JewelBox();

public:
	void	reload();
	string	getHelp();
	string	getOpts();

private:
	string relPath;		//!< Plugin.dll‚Ö‚Ì‘Š‘ÎƒpƒX.
};

