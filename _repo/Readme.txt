�ėp��̓c�[��

�t�@�C�����̉�̓c�[�����쐬���Ă���ƊǗ����ώG�ɂȂ�̂�
�N�����������ʉ������A�v���Ƃ���Bon���J������B

�t�@�C�����̉�̓c�[���́APlugin�Ƃ��Ĉ����B

���񋟌`���i�\�z���j

1.Default�`��
�@Bon(GUI)+Plugin�t�H���_�̌`��
�@�J������Plugin�́APlugin�t�H���_�ɒu�����Ƃŗ��p�\�B
�@Bon.exe
�@[Plugin]
�@  Plugin1.dll
�@  Plugin2.dll

2.CUI�̌`��
�@Bon(CUI)+Plugin�t�H���_�̌`��
�@�J������Plugin�́APlugin�t�H���_�ɒu�����Ƃŗ��p�\�B
�@Bon.exe
�@[Plugin]
�@  Plugin1.dll
�@  Plugin2.dll
�@
3.��̉�(GUI)
�@Bon(GUI)��Plugin����DLL��Static�Ń����N�����`���B
�@�����N�ς݂�Plugin�̂ݗ��p�\�BPlugin�̒ǉ��̓r���h���K�v�B
�@Bon.exe
�@
4.��̉�(CUI)
�@Bon(CUI)��Plugin����DLL��Static�Ń����N�����`���B
�@�����N�ς݂�Plugin�̂ݗ��p�\�BPlugin�̒ǉ��̓r���h���K�v�B
�@Bon.exe

�������\��

Bon�����\���Ƃ���
�EPlugin�Ǘ� (BonFW:Bon Framework)
�E���ʏ��� (BonRT:Bon Runtime)
���j�Ƃ��AGUI��������CUI����Ăяo���B

Plugin��DLL��BonFW�ŊǗ�����B

Plugin�͎���I/F�ɑΉ�����K�v������B
  Init()
  Info()
  Functions()
  Dispose()

Plugin�͎���I/F�̑Ή��ɂ��Ă͔C�ӂƂ���B
  [Pre/Post]Load( filename )
    �t�@�C���̓ǂݍ���.
    
  [Pre/Post]Save( filename ) / Dump()
    �t�@�C���̕ۑ�.
    ��͏��̕ۑ�or�\��
    
  [Pre/Post]Analyze( handle ) or Parse( handle )
    ���
    Bon����́A�ʃX���b�h�ŌĂ΂��
    
  [Pre/Post]Verify( handle )
    �Ó����m�F.

  �ȉ��A���Y�ݒ�
   ?
  Command()
   ?
  [Pre/Post]Event
   ?
  [Pre/Post]Notify
  