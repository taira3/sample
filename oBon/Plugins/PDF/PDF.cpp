// PDF.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"
#include "PDF.h"


extern "C" {
PDF_API	CPDF * Create(void){ return new CPDF(); }
PDF_API	void Poi(CPDF *p){ delete p; }
}

// ����́A�G�N�X�|�[�g���ꂽ�N���X�̃R���X�g���N�^�ł��B
// �N���X��`�Ɋւ��Ă� PDF.h ���Q�Ƃ��Ă��������B
CPDF::CPDF()
{
	return;
}

// �����ł��邩.
bool CPDF::entry( const char *target_file )
{
	return false ;
}

// �Ó�������.
bool CPDF::validate()
{
	return false ;
}

// ����.
bool CPDF::analyze()
{
	return false ;
}
