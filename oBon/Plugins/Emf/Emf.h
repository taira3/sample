// �ȉ��� ifdef �u���b�N�� DLL ����̃G�N�X�|�[�g��e�Ղɂ���}�N�����쐬���邽�߂� 
// ��ʓI�ȕ��@�ł��B���� DLL ���̂��ׂẴt�@�C���́A�R�}���h ���C���Œ�`���ꂽ EMF_EXPORTS
// �V���{���ŃR���p�C������܂��B���̃V���{���́A���� DLL ���g���v���W�F�N�g�Œ�`���邱�Ƃ͂ł��܂���B
// �\�[�X�t�@�C�������̃t�@�C�����܂�ł��鑼�̃v���W�F�N�g�́A 
// EMF_API �֐��� DLL ����C���|�[�g���ꂽ�ƌ��Ȃ��̂ɑ΂��A���� DLL �́A���̃}�N���Œ�`���ꂽ
// �V���{�����G�N�X�|�[�g���ꂽ�ƌ��Ȃ��܂��B
#ifdef EMF_EXPORTS
#define EMF_API __declspec(dllexport)
#else
#define EMF_API __declspec(dllimport)
#endif

#include	"../_base/IPlugin.h"

// ���̃N���X�� Emf.dll ����G�N�X�|�[�g����܂����B
class EMF_API CEmf : public IPlugin {
public:
	CEmf(void);
	// TODO: ���\�b�h�������ɒǉ����Ă��������B

	//
	int	version()	{ return 2 ;}

	// �����ł��邩.
	bool entry( const char *target_file ) ;

	// �Ó�������.
	bool validate() ;

	// ����.
	bool analyze() ;

};
