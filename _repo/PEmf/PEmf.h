// �ȉ��� ifdef �u���b�N�� DLL ����̃G�N�X�|�[�g��e�Ղɂ���}�N�����쐬���邽�߂� 
// ��ʓI�ȕ��@�ł��B���� DLL ���̂��ׂẴt�@�C���́A�R�}���h ���C���Œ�`���ꂽ PEMF_EXPORTS
// �V���{���ŃR���p�C������܂��B���̃V���{���́A���� DLL ���g���v���W�F�N�g�Œ�`���邱�Ƃ͂ł��܂���B
// �\�[�X�t�@�C�������̃t�@�C�����܂�ł��鑼�̃v���W�F�N�g�́A 
// PEMF_API �֐��� DLL ����C���|�[�g���ꂽ�ƌ��Ȃ��̂ɑ΂��A���� DLL �́A���̃}�N���Œ�`���ꂽ
// �V���{�����G�N�X�|�[�g���ꂽ�ƌ��Ȃ��܂��B
#ifdef PEMF_EXPORTS
#define PEMF_API __declspec(dllexport)
#else
#define PEMF_API __declspec(dllimport)
#endif

#include	"../Bon/IPlugin.h"

class EmfSpool ;

// ���̃N���X�� PEmf.dll ����G�N�X�|�[�g����܂����B
//class PEMF_API CPEmf : public IPlugin{
class CPEmf : public IPlugin{
public:
	CPEmf(void)
	{
	}

	int	version()	{ return 2 ;}

	// �����ł��邩.
	bool entry( const char *target_file ) ;

	// �Ó�������.
	bool validate() ;

	// ����.
	bool analyze() ;

private:
	EmfSpool	*p_emfspool ;
	string		tar_file ;
};
