// EmfPk.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"
#include "EmfPk.h"


extern "C" {
EMFPK_API	CEmfPk * Create(void){ return new CEmfPk(); }
EMFPK_API	void Poi(CEmfPk *p){ delete p; }
}


// �����ł��邩.
bool CEmfPk::entry( const char *target_file )
{
	return false ;
}

// �Ó�������.
bool CEmfPk::validate()
{
	return false ;
}

// ����.
bool CEmfPk::analyze()
{
	return false ;
}
