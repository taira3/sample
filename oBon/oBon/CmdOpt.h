#pragma once

#include	"NodeVar.h"

class CmdOpt
{
public:
	CmdOpt(NodeVar	v) :
		mode_help(false),
		mode_version(false),
		mode_gui(true),
		node(v)
	{
		Paerse();
	};
	~CmdOpt();

private:
	NodeVar	node;
	bool	mode_help;			//!< Help mode.
	bool	mode_version;		//!< Version mode.
	bool	mode_gui;			//!< GUI mode.

private:
	bool	Paerse();			//!< ƒIƒvƒVƒ‡ƒ“‚Ì‰ðÍ

public:
	bool	IsHelp()	{ return mode_help; }
	bool	IsVersion() { return mode_version; }
	bool	IsGUI() { return mode_gui; }
	bool	IsCUI() { return !mode_gui; }
};

