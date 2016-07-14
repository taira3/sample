// PEmf.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"
#include "PEmf.h"
#include "EmfSpool.h"

class	Emfspool ;

extern "C" {
PEMF_API	CPEmf * Create(void){ return new CPEmf(); }
PEMF_API	void Poi(CPEmf *p){ delete p; }
}

// �����ł��邩.
bool CPEmf::entry( const char *target_file )
{
	// EMFSpool �̉�͏���.
	EmfSpool	*emfspool = new EmfSpool((char*)target_file);

	// �w�肳�ꂽ�t�@�C����EMFSpool�`�����Ó����`�F�b�N.
	bool	res = emfspool->valid() ;

	if( res )
	{
		this->tar_file = string(target_file) ;
	}

	delete emfspool ;

	return res ;
}

// �Ó�������.
bool CPEmf::validate()
{
	return true ;
}

// ����.
bool CPEmf::analyze()
{
	cout << "CPEmf::analyze." << endl ;

	// EMFSpool �̉�͏���.
	EmfSpool	*emfspool = new EmfSpool((char*)this->tar_file.c_str());

	bool	res = false ;

	// ��͌��ʏo�͐�̊��𐮂���.
	if( emfspool->create_output_env((char*)this->tar_file.c_str()) )
	{
		// ��͊J�n.
		res = emfspool->parse();
	}

	delete emfspool ;

	return res ;
}
