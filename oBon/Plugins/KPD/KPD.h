// �ȉ��� ifdef �u���b�N�� DLL ����̃G�N�X�|�[�g��e�Ղɂ���}�N�����쐬���邽�߂� 
// ��ʓI�ȕ��@�ł��B���� DLL ���̂��ׂẴt�@�C���́A�R�}���h ���C���Œ�`���ꂽ KPD_EXPORTS
// �V���{���ŃR���p�C������܂��B���̃V���{���́A���� DLL ���g���v���W�F�N�g�Œ�`���邱�Ƃ͂ł��܂���B
// �\�[�X�t�@�C�������̃t�@�C�����܂�ł��鑼�̃v���W�F�N�g�́A 
// KPD_API �֐��� DLL ����C���|�[�g���ꂽ�ƌ��Ȃ��̂ɑ΂��A���� DLL �́A���̃}�N���Œ�`���ꂽ
// �V���{�����G�N�X�|�[�g���ꂽ�ƌ��Ȃ��܂��B
#ifdef KPD_EXPORTS
#define KPD_API __declspec(dllexport)
#else
#define KPD_API __declspec(dllimport)
#endif

#include	"../_base/IPlugin.h"

// ���̃N���X�� KPD.dll ����G�N�X�|�[�g����܂����B
class KPD_API CKPD : public IPlugin {
public:
	CKPD(void);
	// TODO: ���\�b�h�������ɒǉ����Ă��������B

	int	version()	{ return 2 ;}

	// �����ł��邩.
	bool entry( const char *target_file ) ;

	// �Ó�������.
	bool validate() ;

	// ����.
	bool analyze() ;

};
