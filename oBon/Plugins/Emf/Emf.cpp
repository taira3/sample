// Emf.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"
#include "Emf.h"


extern "C" {
EMF_API	CEmf * Create(void){ return new CEmf(); }
EMF_API	void Poi(CEmf *p){ delete p; }
}

// ����́A�G�N�X�|�[�g���ꂽ�N���X�̃R���X�g���N�^�ł��B
// �N���X��`�Ɋւ��Ă� Emf.h ���Q�Ƃ��Ă��������B
CEmf::CEmf()
{
	return;
}

// �����ł��邩.
bool CEmf::entry( const char *target_file )
{
	return false ;
}

// �Ó�������.
bool CEmf::validate()
{
	return false ;
}

// ����.
bool CEmf::analyze()
{
	return false ;
}
