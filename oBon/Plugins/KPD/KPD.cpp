// KPD.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"
#include "KPD.h"


extern "C" {
KPD_API	CKPD * Create(void){ return new CKPD(); }
KPD_API	void Poi(CKPD *p){ delete p; }
}

// ����́A�G�N�X�|�[�g���ꂽ�N���X�̃R���X�g���N�^�ł��B
// �N���X��`�Ɋւ��Ă� KPD.h ���Q�Ƃ��Ă��������B
CKPD::CKPD()
{
	return;
}

// �����ł��邩.
bool CKPD::entry( const char *target_file )
{
	return false ;
}

// �Ó�������.
bool CKPD::validate()
{
	return false ;
}

// ����.
bool CKPD::analyze()
{
	return false ;
}
