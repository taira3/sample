// PCL.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"
#include "PCL.h"


extern "C" {
PCL_API	CPCL * Create(void){ return new CPCL(); }
PCL_API	void Poi(CPCL *p){ delete p; }
}

// ����́A�G�N�X�|�[�g���ꂽ�N���X�̃R���X�g���N�^�ł��B
// �N���X��`�Ɋւ��Ă� PCL.h ���Q�Ƃ��Ă��������B
CPCL::CPCL()
{
	return;
}

// �����ł��邩.
bool CPCL::entry( const char *target_file )
{
	return false ;
}

// �Ó�������.
bool CPCL::validate()
{
	return false ;
}

// ����.
bool CPCL::analyze()
{
	return false ;
}
