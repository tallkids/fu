
      �t�������v�r�p�t�@�C���Ǘ����[�e�B���e�B  �y  ����  Ver3.07  �z

                                         Copyright (C) 1990-1998 T.Tashiro

�P�D�T�v
    �����͂t�������v�r��Ńt�@�C���̍폜�A�R�s�[�A�f�B���N�g���c���[�̕\����
  ���ȒP�ɍs�����߂̃c�[���ł��B���̑��ɁA�G�f�B�^�̋N���A�V�F���̎��s�i�q�X
  �g���[�@�\�t���j���ł���ȂǁA�������V�F���̂����Ɏg�p���鎖���ł��܂��B
  �܂��A�R�}���h���s�̂��߂̃L�[�A�T�C���ύX��A�R�}���h�̒ǉ��o�^�Ȃǂ�
  �ȒP�ɂł��A���[�U�̍D�݂ŃJ�X�^�}�C�Y���鎖���ł��܂��B

�Q�D�����̃R���p�C���y�уC���X�g�[��
  �Q�D�P �R���p�C��
     make�����s���܂��B���̍ۂ̃I�v�V�����őΉ��@���ݒ肵�܂��B

        make hpux         HP-UX on HP9000 series
        make linux        Linux
        make bsdi         BSDI
        make h2050        HI-UX on HITACHI 2050 series
        make i386bsd      386BSD
        make panix        PANIX
        make minix        Minix
        make sunos        SunOS
        make news3400     NEWS3400

       ������̏ꍇ��xfu���쐬����ꍇ�͋@�햼�̃I�v�V������'-x'��t���ĉ������B
       ��:  make hpux-x

       ����: �茳�ɋ@�B���Ȃ����� hpux �� linux, bsdi �ȊO�͎����Ă܂���B
             (���ꂩ�p�b�`������ĉ������B)

       �J�����g�f�B���N�g����'fu'(X�o�[�W�����ł�'xfu')���쐬����܂��B

�@�Q�D�Q �C���X�g�[��
    'fu'('xfu')���R�}���h�����p�X�̒ʂ��Ă���A�f�B���N�g���ɃR�s�[����B
        �i'/usr/local/bin'���Ɋi�[���鎖���A�����߂��܂��j

�R�D�����̋N�����@
 �R�D�P �m�[�}���o�[�W����('fu')
  �t�H�[�}�b�g:
    $ fu [options]

  �I�v�V����:
    -a                       ASCII�R�[�h�݂̂̕\�����[�h�ɂ���B
                             �������������ꍇ�ɂ�'?'�Œu�����ĕ\������B
    -k                       �����R�[�h���g�p�\�Ƃ���B(�f�t�H���g)
    -s                       �����R�[�h��Shift-JIS���g�p����B
                             (H2050,HP9000�ł̓f�t�H���g)
    -e                       �����R�[�h��EUC���g�p����B
                             (SunSPARC,MINIX���ł̓f�t�H���g)

 �R�D�Q X�Ή��o�[�W����('xfu')
  �t�H�[�}�b�g:
    $ xfu [options]

  �I�v�V����:
    -a                       ASCII�R�[�h�݂̂̕\�����[�h�ɂ���B
                             �������������ꍇ�ɂ�'?'�Œu�����ĕ\������B
    -k                       �����R�[�h���g�p�\�Ƃ���B(�f�t�H���g)
    -s                       �����R�[�h��Shift-JIS���g�p����B
                             (H2050,HP9000�ł̓f�t�H���g)
    -e                       �����R�[�h��EUC���g�p����B
    -display host:display    X Window�T�[�o�z�X�g��
    -geometry geom           xfu�̃E�C���h�E�W�I���g��
    -name title              �E�C���h�E�^�C�g����
    -fg color                �t�H�A�O�����h�J���[
    -bg color                �o�b�N�O�����h�J���[
    -fn fontname             ASCII�����t�H���g��
    -fr font_kana            ���������t�H���g��
    -fk font_kanji           ���������t�H���g��

  ���\�[�X:
    xfu.Title:               �E�C���h�E�^�C�g����(��:'Xfu')
    xfu.Geometry:            �E�C���h�E�W�I���g��(��:'21x40+20+20')
    xfu.Foreground:          �t�H�A�O�����h�J���[(��:'White')
    xfu.Background:          �o�b�N�O�����h�J���[(��:'Black')
    xfu.Font:                ASCII�����t�H���g��(��:'asc08')
    xfu.KanaFont:            ���������t�H���g��(��:'j7kana08')
    xfu.KanjiFont:           ���������t�H���g��(��:'sjis16')

�S�D�����̕\�����
  �����ɂ̓t�@�C���\����ʂƁA�f�B���N�g���\����ʂ�����܂��B�������ȉ���
  �����܂��B
  �S�D�P �t�@�C���\�����
--------------------------------------------------------------------------------
Current Dir(0) : /usr/tashiro
 [.             ]drwxr-xr-x 11/08 18:01  .profile       -rw-r--r-- 11/05 10:01^^
 [..            ]drwxr-xr-x 11/08 11:10  .rhosts        -rw-r--r-- 10/30 09:01
 [DDC           ]drwxrwxrwx 11/01 19:24  .setup.fu      -rw-r--r-- 07/29 16:49
 [JUS_FREE      ]drwxr-xr-x 10/15 16:22  .setup.mfu     -rw-r--r-- 10/29 11:05PP
 [Wnn           ]drwxrwxrwx 10/25 1990   .wsdb.def      -rw-r--r-- 10/29 15:49RR
 [bin           ]drwxr-xr-x 11/08 11:10  .tree.fu       -rw-r--r-- 11/05 09:59EE
 [bitmaps       ]drwxr-xr-x 10/28 13:00  .xinitrc       -rw-r--r-- 10/09 08:11VV
 [comm          ]drwxr-xr-x 10/30 16:06  .xsession      -rw-r--r-- 10/09 08:50
 [projectA      ]drwxr-xr-x 09/27 15:18  calendar       -rw-r--r-- 11/07 09:55
 [image         ]drwxr-xr-x 08/01 21:58  emacs.rc       -rw-r--r-- 05/20 08:25--
 [nfs           ]drwxr-xr-x 12/26 1990   jldx00         -rw-rw-rw- 09/27 17:22
 [rex           ]drwxr-xr-x 10/07 20:59  jldx10         -rw-rw-rw- 09/27 17:24
 [rexapp        ]drwxr-xr-x 10/29 10:58  kankan         -rw-rw-rw- 10/24 09:10NN
 [test          ]drwxr-xr-x 10/15 07:55                                       EE
 [tool          ]drwxr-xr-x 11/07 13:19                                       XX
 [txt           ]drwxr-xr-x 10/29 10:52                                       TT
  .Xresources    -rw-r--r-- 11/05 10:18
  .dbacc.def     -rw-r--r-- 10/28 13:51
  .mwmrc         -rw-r--r-- 10/30 08:43                                       vv
== File Management Utility Ver.3.05 =============================== T.Tashiro ==
Command : Copy Delete Edit Find Quit Shell Tree eXecute Mount UnMount (1) (2)
          (4)
Find : *
--------------------------------------------------------------------------------

      (1) 1�s     ��΃f�B���N�g���p�X���\������܂��B
                  ���ʓ��̐��l�͂��̎��_�ŃX�^�b�N�ɐς܂�Ă���p�X�̐���\���B
      (2) 2-20�s  �t�@�C�����̕\���̈�(79-80�J�����̓X�N���[���o�[)
        �E1��\�����[�h�̏ꍇ
   * calendar       -rw-r--r--   1 tashiro  group        1384 Apr  8 10:16 1991
            �J����      ��  ��
            1      : '*'�őI����Ԃɂ��鎖�������B
            2,17   : '[',']'�ł��̃t�@�C�����f�B���N�g���ł��鎖�������B
            3-16   : �t�@�C����
            18     : 'd'�́A�f�B���N�g���ł��邱�Ƃ������B
                     'c'�́A�L�����N�^�f�o�C�X�ł��邱�Ƃ������B
                     'b'�́A�u���b�N�f�o�C�X�ł��邱�Ƃ������B
                     'p'�́AFIFO�f�o�C�X�ł��邱�Ƃ������B
                     's'�́A�\�P�b�g�f�o�C�X�ł��邱�Ƃ������B
            19-21  : 'r','w','x'�́A���ꂼ��I�[�i�[�̓ǂݍ��݁A�������݁A���s
                     ���������B���s����'s'�̏ꍇset uid�r�b�g�������Ă���.
            22-24  : 'r','w','x'�́A���ꂼ��O���[�v�̓ǂݍ��݁A�������݁A���s
                     ���������B���s����'s'�̏ꍇset gid�r�b�g�������Ă���.
            25-27  : 'r','w','x'�́A���ꂼ�ꑼ���[�U�̓ǂݍ��݁A�������݁A���s
                     ���������B���s����'t'�̏ꍇsticky�r�b�g�������Ă���.
            29-31  : �t�@�C���̃����N��
            33-40  : �t�@�C���̃I�[�i�[��
            42-49  : �t�@�C���̃I�[�i�[�O���[�v��
            51-58  : �t�@�C���T�C�Y(Byte�P��)
            60-65  : �t�@�C�����Ō�ɕύX���ꂽ���^��
            67-71  : �t�@�C�����Ō�ɕύX���ꂽ���F��
            73-76  : �t�@�C�����Ō�ɕύX���ꂽ�N
        �E2��\�����[�h�̏ꍇ
          * calendar       drwxrw-r-x 04/17 17:17
            �J����      ��  ��
            1      : '*'�őI����Ԃɂ��鎖�������B
            2,17   : '[',']'�ł��̃t�@�C�����f�B���N�g���ł��鎖�������B
            3-16   : �t�@�C����
            18     : 'd'�́A�f�B���N�g���ł��邱�Ƃ������B
                     'c'�́A�L�����N�^�f�o�C�X�ł��邱�Ƃ������B
                     'b'�́A�u���b�N�f�o�C�X�ł��邱�Ƃ������B
                     'p'�́AFIFO�f�o�C�X�ł��邱�Ƃ������B
                     's'�́A�\�P�b�g�f�o�C�X�ł��邱�Ƃ������B
            19-21  : 'r','w','x'�́A���ꂼ��I�[�i�[�̓ǂݍ��݁A�������݁A���s
                     ���������B���s����'s'�̏ꍇset uid�r�b�g�������Ă���.
            22-24  : 'r','w','x'�́A���ꂼ��O���[�v�̓ǂݍ��݁A�������݁A���s
                     ���������B���s����'s'�̏ꍇset gid�r�b�g�������Ă���.
            25-27  : 'r','w','x'�́A���ꂼ�ꑼ���[�U�̓ǂݍ��݁A�������݁A���s
                     ���������B���s����'t'�̏ꍇstickey�r�b�g�������Ă���.
            29-33  : �t�@�C�����Ō�ɕύX���ꂽ���^��
            35-39  : �t�@�C�����Ō�ɕύX���ꂽ���F��(�ύX����Ă��甼�N�ȏ�
	             �o���Ă���ꍇ�ύX�����N���\�������)
        �E4��\�����[�h�̏ꍇ
          * calendar
            �J����      ��  ��
            1      : '*'�őI����Ԃɂ��鎖�������B
            2,17   : '[',']'�ł��̃t�@�C�����f�B���N�g���ł��鎖�������B
            3-16   : �t�@�C����
      (3) 21�s    �C���t�H���[�V�������C�� �����̐������̂ƃo�[�W����
      (4) 22-23�s �R�}���h���j���[         �g�p�ł����ȃR�}���h
      (5) 24�s    �t�@�C���������}�X�N

   (��)�EX-Window��xterm���ōs����ύX���Ă���ꍇ�͂���ɍ��킹�ĕ\��������
         ����܂��B(�_�C�i�~�b�N�ɂ͕ύX����܂���)
       �E'xfu'�ł̓E�C���h�E��ό`�����邱�Ƃɂ��s���^�񐔂��_�C�i�~�b�N��
         �ύX����܂��B

  �S�D�Q �f�B���N�g���\�����
--------------------------------------------------------------------------------
Path : /hd/tashiro/GAEA
 /              >                                                             ^^
 +- hd             >
     +- tashiro
         +- DDC            >
         +- GAEA           >                                                  PP
         +- JUS_FREE       >                                                  RR
         +- Wnn            >                                                  EE
         +- bin                                                               VV
         |   +- mo_eps         >
         +- bitmaps        >
         +- compkg         >
         |   +- vos3           >                                              --
         |       +- single_chk
         +- gtproject      >
         +- image          >                                                  NN
         +- nfs            >                                                  EE
         +- rex            >                                                  XX
         +- rexapp         >                                                  TT
         +- test           >
         +- tool           >
         +- txt            >
                                                                              vv
--------------------------------------------------------------------------------
      (1) 1�s     �J�[�\�����w���Ă���f�B���N�g���̐�΃p�X
      (2) 2-23�s  �f�B���N�g���c���[�\���̈�(79-80�J�����̓X�N���[���o�[)
                  '>'�����ɂ��Ă���f�B���N�g���́A�������f�B���N�g��������

�T�D�����̃L�[����Ƌ@�\
    �g�p���Ă���WS��2050��H-Window�̏ꍇ�܂��́A'xfu'�̏ꍇ�ɂ̓}�E�X���g�p��
  �邱�Ƃ��ł��܂��B�}�E�X�̎g�p���@�ɂ��Ă͎��ۂɃI�y���[�V�������s�Ȃ�����
  �ōl���ĉ������B
    (��)�����Ɏ����Ă���̂�2050�̃f�t�H���g�̐ݒ�ł��B
  �T�D�P �t�@�C���\����ʂł̃L�[����Ƌ@�\
      ���L�[      �F  �t�@�C���I��p�J�[�\���̈ړ�
      SHIFT + ��    �F  �P�őO�̃t�@�C���\����ʂɈړ�
      SHIFT + ��    �F  �P�Ō�̃t�@�C���\����ʂɈړ�
      �O�ŃL�[      �F  �P�őO�̃t�@�C���\����ʂɈړ�
      ���ŃL�[      �F  �P�Ō�̃t�@�C���\����ʂɈړ�
      �X�y�[�X�L�[  �F  �J�[�\���ʒu�ɂ���t�@�C���̑I����Ԃ̐؂�ւ�
      ���^�[���L�[  �F  �f�B���N�g���t�@�C���̏ꍇ
                            ���f�B���N�g���̈ړ�
                        �A�[�J�C�u�t�@�C���̏ꍇ
                            ���A�[�J�C�u����Ă���t�@�C�����ꗗ��\��
                        ���̑��̃t�@�C���̏ꍇ
                            ���t�@�C�����e�̕\���i���������\���j
      �폜�L�[      �F  �t�@�C��/�f�B���N�g���̍폜
      Home�L�[      �F  �J�����g�f�B���N�g���̑S�Ẵt�@�C����I��/�I������
      Ctrl-B        �F  �J�[�\�������Ɉړ�
      Ctrl-F        �F  �J�[�\�����E�Ɉړ�
      Ctrl-N        �F  �J�[�\�������Ɉړ�
      Ctrl-P        �F  �J�[�\������Ɉړ�
      Ctrl-Z        �F  �P�őO�̃t�@�C���\����ʂɈړ�
      Ctrl-V        �F  �P�Ō�̃t�@�C���\����ʂɈړ�
      Ctrl-L        �F  ��ʂ̍ĕ`��
      Ctrl-X Ctrl-C �F  �����̏I��
      "+"           �F  �J�����g�f�B���N�g�����X�^�b�N�ɐς�
      "-"           �F  �X�^�b�N�ɐς܂ꂽ�f�B���N�g�����J�����g�ɂ���
      "/"           �F  �J�����g�f�B���N�g���̕ύX("cd")
      "1"           �F  1��t�@�C���\�����[�h�ɂ���
      "2"           �F  2��t�@�C���\�����[�h�ɂ���
      "4"           �F  4��t�@�C���\�����[�h�ɂ���
      "c"           �F  �t�@�C��/�f�B���N�g���̃R�s�[ (��)
      "C"           �F  �t�@�C��/�f�B���N�g���̃R�s�[ (��)
                        (�f�B���N�g���c���[�ɂ��R�s�[��w��)
      "d"           �F  �t�@�C��/�f�B���N�g���̍폜
      "e"           �F  �G�f�B�^�̋N�� ("em":Micro Emacs)
      "f"           �F  �t�@�C���\���}�X�N�̎w��
      "j"           �F  �t�@�C�����̐擪1�������w�肵�A�J�[�\�����ړ�����
      "q"           �F  �����̏I��
      "r"           �F  �t�@�C���̃��l�[��(�ړ�)
      "s"           �F  �V�F���R�}���h�̎��s
      "t"           �F  �f�B���N�g���c���[�̕\���ƁA�J�����g�f�B���N�g���̈ړ�
      "T"           �F  �J�����g�f�B���N�g����"/"�Ƃ����A"t"�R�}���h
      "x"           �F  �t�@�C�������s�R�}���h�Ƃ݂Ȃ����s
      "mo"          �F  "/dev/fd2d0a"��"/fd1"�Ƀ}�E���g
      "um"          �F  "/dev/fd2d0a"�̃}�E���g�̉���
      "md"          �F  �f�B���N�g���̍쐬("mkdir")
      "al"          �F  �A�[�J�C�u�t�@�C���̓��e�\��
      "ar"          �F  �t�@�C���̃A�[�J�C�u���s
      "ua"          �F  �A�[�J�C�u�t�@�C������̃t�@�C���̎��o��
      "mv"          �F  �t�@�C��/�f�B���N�g���̈ړ� (��)
      "MV"          �F  �t�@�C��/�f�B���N�g���̈ړ� (��)
                        (�f�B���N�g���c���[�ɂ��ړ���w��)

    (��) "c","C","mv"�܂���"MV"�R�}���h�Ńt�@�C���̕���/�ړ���Ɋ��Ƀt�@�C����
         ���݂��Ă���ꍇ�ǂ����邩�𕷂��Ă��܂��B�����őI���ł��鏈�����ȉ�
         �Ɏ����܂��B
           's' : Skip ���̃t�@�C���̓R�s�[/�ړ����Ȃ�
           't' : Time �ύX�����𒲂׃R�s�[/�ړ����̕����V������΃R�s�[/�ړ�����
           'f' : Force �����I�ɃR�s�[/�ړ�����
           'a' : Abort �R�s�[/�ړ��͍s�Ȃ킸�R�}���h�𔲂���
         ������啶���œ��͂���Ƃ���ȍ~�̃R�s�[/�ړ����Ɏw�肳��Ă���S��
         �̃t�@�C���ɂ��Ă��̏������K�p����܂��B

  �T�D�Q �f�B���N�g���\����ʂł̃L�[����Ƌ@�\
      SHIFT + ��    �F  �P�őO�̃f�B���N�g���\����ʂɈړ�
      SHIFT + ��    �F  �P�Ō�̃f�B���N�g���\����ʂɈړ�
      �O�ŃL�[      �F  �P�őO�̃t�@�C���\����ʂɈړ�
      ���ŃL�[      �F  �P�Ō�̃t�@�C���\����ʂɈړ�
      ���^�[���L�[  �F  �J�[�\���̎����f�B���N�g���Ɉړ�
      ESC ESC       �F  �f�B���N�g���\����ʂ𔲂���
      �X�y�[�X�L�[  �F  �J�[�\���ʒu�̃f�B���N�g������
      Ctrl-N (or��) �F  �J�[�\�������Ɉړ�
      Ctrl-P (or��) �F  �J�[�\������Ɉړ�
      Ctrl-F (or�E) �F  �J�[�\�������Ɉړ�(�J�[�\���ʒu���������f�B���N�g��
                        �̏ꍇ�������s�Ȃ��J�[�\���ړ�����)
      Ctrl-B (or��) �F  �J�[�\������̊K�w�̃f�B���N�g���Ɉړ�
      Ctrl-Z        �F  �P�őO�̃t�@�C���\����ʂɈړ�
      Ctrl-V        �F  �P�Ō�̃t�@�C���\����ʂɈړ�
      "T"           �F  �J�[�\���ʒu�̃f�B���N�g������
      "q"           �F  �f�B���N�g���\����ʂ𔲂���

  �T�D�R ��������͎��̃L�[����Ƌ@�\
      ����L�[    �F  �P�O�ɓ��͂��ꂽ������̕\��
      �����L�[    �F  ���\������Ă��鎟�ɓ��͂��ꂽ������̕\��
      �E���L�[    �F  �J�[�\�����E�Ɉړ�
      �����L�[    �F  �J�[�\�������Ɉړ�
      ��ރL�[      �F  �J�[�\���ʒu�̂P���̕������폜
      �폜�L�[      �F  �J�[�\���ʒu�̕����̍폜
      ESC ESC       �F  ������̓��͂̒��f
      ���^�[���L�[  �F  ������̊m��
      �����L�[      �F  ���͂��ꂽ�������J�[�\���ʒu�ɑ}��

  �T�D�S ���̑��̏ꍇ�̃L�[����
      ��{�I��ESC ESC�܂��́A"q"�ő���A�\���̒��f���s���܂��B

�U�D�R�}���h�e���v���[�g
    'Shell','Exec'�R�}���h�œ��͂��ꂽ�������Z�b�g�A�b�v�t�@�C�����ɋL�q
�@���ꂽ�R�}���h�������'fu'�ɂ���ă}�N��������W�J������ɃV�F���Ŏ��s��
�@�Ă��܂��i�ȍ~�����̓��͕�����y�уZ�b�g�A�b�v�t�@�C�����̃R�}���h����
�@����R�}���h�e���v���[�g�ƌĂт܂��B�j

          ��      ��                  ��
      �R�}���h�e���v���[�g          "em %*" (test.c test2.c test.h���I��
              ��                             ���)
      �}�N��������I����Ԃɂ���    "em test.c test2.c test.h"
      �t�@�C�����ɓW�J
              ��
      �V�F�����N�����A�R�}���h��
      �n���B

  �y�R�}���h�e���v���[�g�Ŏg�p�ł���}�N�������z
      %f : �I����Ԃɂ���t�@�C���܂��́A�J�[�\��     "chmod u+x %f"
           �ʒu�̃t�@�C�����������u�����A���s����B          ��
                                                      "chmod u+x test"
                                                      "chmod u+x test2"
                                                            .......

      %1 : �J�[�\���ʒu�ɂ���t�@�C�����Œu����       "mv %1 test2"
           ���s����B                                        ��
                                                      "mv test test2"

      %* : �I����Ԃɂ���t�@�C���܂��́A�J�[�\��     "em %*"
           �ʒu�ɂ���t�@�C�������ł��邾���u������          ��
           ��C�Ɏ��s����B                           "em test1.c test2.c ..."

      %l : �I����Ԃɂ���t�@�C���܂��́A�J�[�\��     "cpio -o <%l >pak"
           �ʒu�ɂ���t�@�C�����̃��X�g���ꎞ�t�@�C��        ��
           �Ɋi�[���A���̃t�@�C�����Œu��������B�@�@ "cpio -o <.tempfile >pak"
                                                                   ��
 �@                                                 �t�@�C�������X�g�t�@�C��
  �y�}�N�������̏C���q�z
    �}�N�������ɂ͈ȉ��Ɏ���4��ނ̏C���q��t���邱�Ƃ��ł��܂��B
    (��͑S�ăJ�[�\���ʒu�̃t�@�C������"/usr/tashiro/aaa.bbb.c"�ł���Ɖ���)
      @p : �t�@�C�����̃v���t�B�b�N�X (��: "%1@p" -> "aaa.bbb")
      @s : �t�@�C�����̃T�t�B�b�N�X   (��: "%*@s" -> ".c")
      @d : �J�����g�f�B���N�g���p�X   (��: "%1@d" -> "/usr/tashiro")
      @a : �t�@�C���̃t���p�X��       (��: "%1@d" -> "/usr/tashiro/aaa.bbb.c")

�V�D�����̃J�X�^�}�C�Y
�@�V�D�P �Z�b�g�A�b�v�t�@�C���ɂ��J�X�^�}�C�Y
    �T�D�Ŏ������L�[�A�T�C���̓f�t�H���g�̏�Ԃł���A�Z�b�g�A�b�v�t�@�C����
�@�쐬���鎖�ŁA�L�[�A�T�C���̕ύX�A�@�\�̒ǉ����ȒP�ɍs�������ł��܂��B
�@  �Z�b�g�A�b�v�t�@�C����'/usr/lib'�܂��͊e���[�U�̃z�[���f�B���N�g����
  '.setup.fu'�̖��O�ō쐬���ĉ������i�ǂ���ɂ�����ƃz�[���f�B���N�g���ɂ�
�@����̂��L���ɂȂ�܂��B�j
�@�@�@���F�Z�b�g�A�b�v�t�@�C����'fu'�����グ���ɂ̂ݓǂݍ��܂�܂��B
  �@�ȉ��ɂ̓Z�b�g�A�b�v�t�@�C���̃t�H�[�}�b�g�������܂��B

  (1) '#'�Ŏn�܂�s�̓R�����g�Ƃ݂Ȃ��܂��B
  (2) '#com'�Ŏn�܂�s�́A�R�}���h���j���[���i��ʉ����j�ɕ\�����镶�����
�@�@�@�w����s�Ȃ��܂��B(�����s�ɕ����\)
      ��: #com "Copy" "Delete" "Edit" "Find" "MaKe" "PRint" "Quit" "Shell"
          #com "Tree" "searchTree" "View" "eXecute"
  (3) ���̑��̏ꍇ
      "keyname  switch  com_temp"
              ��      ��
            �P�ȏ�̋󔒂܂���TAB
        keyname  : �R�}���h���A�T�C������L�[�̎w��
                    ���p��'"'�ň͂܂�Ă���ꍇ�́A�͂܂ꂽ��������A�L�[
�@�@�@�@�@�@�@�@�@�@�R�[�h�Ƃ݂Ȃ��܂��B
                      ���ꕶ���̋L�q���@
                         \000 : '\'�ɑ����R���̂W�i����ASCII�R�[�h�Ƃ݂Ȃ��ϊ�
                         \"   : '"'�Ƃ݂Ȃ�
                         \\   : '\'�Ƃ݂Ȃ�
                    ����ȊO�̏ꍇ�́A�����Ŋ��ɒ�`����Ă���L�[�̖��O�Ƃ�
�@�@�@�@�@�@�@�@�@�@�Ȃ��܂��B
�@�@�@�@�@�@�@�@�@�@��F "\033[A"    (esc),'[','A'
                         key_down    �����L�[�i2050�ł����������Ȃ������j
                         "del"       'd','e','l'
        switch   : �R�}���h���s���̃��[�h�w��i�O���R�}���h�̂ݗL���j
                    1 : 'Shell>'���[�h�ɂȂ�R�}���h�e���v���[�g�����[�U���C
                        ����������s����B
                    0 : 'Shell>'���[�h�ɂ͂Ȃ炸�����s����B
        com_temp : �A�T�C���������R�}���h
                    '$'�Ŏn�܂�ꍇ�ɂ͈ȍ~������R�}���h���Ƃ݂Ȃ��܂��B
                    ����ȊO�̏ꍇ�ɂ̓R�}���h�e���v���[�g�Ƃ݂Ȃ��܂��B
        �i���j �L�[�����X�g�y�сA�R�}���h�����X�g�́A�W�D�ɋL�ڂ��܂��B

  �y�Z�b�g�A�b�v�t�@�C���̗�z
      #
      #      File Utility Command Setup File
      #
      "e"         0     em %*
      "E"         1     em %*
      "pk"        1     cpio -p <%l >
      "up"        1     cat %1 | cpio -i
      "\016"      0     $func_down
      "\020"      0     $func_up
      "\030\003"  0     $func_quit
      key_zenpeji 0     $func_s_up
      key_jipeji  0     $func_s_down
�@�@�i�A�[�J�C�u����Ă���'.setup.fu','.setup.fu.vi'�͗�ł��Q�l�ɂ���
      �������j

�@�V�D�Q �w�b�_�t�@�C���̕ύX�ɂ��J�X�^�}�C�Y
�@�@�ȉ���'fu'�̃w�b�_�t�@�C���Œ�`����Ă���萔��ϐ��ɂ��Đ������܂��B
�@������K���ɏC�����A���R���p�C�����邱�ƂŃJ�X�^�}�C�Y�ł��܂��B
  �y'fu.h'���̒萔�z
    #define FILE_ENT     1024    �t�@�C�������i�[����G���g���̐�
    #define TREE_ENT     1024�@�@'t'�R�}���h���ŕ\���ł���f�B���N�g����
    #define USER_ID_ENT  1024�@�@���[�UID�ƃ��[�U���̑Ή����i�[����G���g����
�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ �i'/etc/passwd'�̃G���g����葽�����ĉ������j
    #define GROUP_ID_ENT 256     �O���[�vID�̑Ή����i�[����G���g����
�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ �i'/etc/group'�̃G���g����葽�����ĉ������j
    #define MAX_KEY_FUNC 200�@�@ �L�[�Ƌ@�\�̑Ή���o�^����G���g����
                                 �i�Œ�ł�'.setup.fu'�̃G���g��+80�͕K�v�j
    #define MAX_FUNC_CMD 200�@�@ �@�\��o�^����G���g����
                                 �i�Œ�ł�'.setup.fu'�̃G���g��+60�͕K�v�j
    #define HIST_CN      30�@�@�@�q�X�g���o�b�t�@�̍s��
    #define LZHARC       "lha"   '*.lzh'�t�@�C���ɑ΂���A�[�J�C�o���w��

  �y'futable.h'���̕ϐ��z
    int sc_mode = 2;          �N�����̉�ʕ\�����[�h
                                 1 : 1��t�@�C���\�����[�h
                                 2 : 2��t�@�C���\�����[�h
                                 4 : 4��t�@�C���\�����[�h
    int arc_mode = ARC_LZH;   �f�t�H���g�̃A�[�J�C�o
                                 ARC_LZH  : 'lha'            ('*.lzh')
                                 ARC_TAR  : 'tar'            ('*.tar')
                                 ARC_TAz  : 'tar'+'pack'     ('*.taz')
                                 ARC_TAZ  : 'tar'+'compress' ('*.taZ')
                                 ARC_TARz : 'tar'+'pack'     ('*.tar.z')
                                 ARC_TARZ : 'tar'+'compress' ('*.tar.Z')

�W�D�����œo�^���Ă���L�[���y�сA�R�}���h��
  �W�D�P �L�[�����X�g(�قƂ�ǂ�2050�ł̂ݎg�p��)
    "key_torikesi"      :  ���
    "key_down"          :  ��
    "key_up"            :  ��
    "key_kakutyou"      :  �@�\�g��
    "key_pa1"           :  �o�`�P
    "key_pa2"           :  �o�`�Q
    "key_pa3"           :  �o�`�R
    "key_screen"        :  �X�N���[��
    "key_srq"           :  �r�q�p
    "key_pa4"           :  �o�`�S
    "key_tyudan"        :  ���f
    "ket_test"          :  �e�X�g
    "key_jikkou"        :  ���s
    "key_field"         :  �t�B�[���h
    "key_print"         :  ���
    "key_henkantaishou" :  �ϊ��Ώ�
    "key_function"      :  �t�@���N�V����
    "key_saihenkan"     :  �ĕϊ�
    "key_s_function"    :  SHFT + �t�@���N�V����
    "key_data"          :  �f�[�^
    "key_stopprint"     :  ������~
    "key_c_function"    :  CTRL + �t�@���N�V����
    "key_s_home"        :  SHIFT + home
    "key_s_up"          :  SHIFT + ��
    "key_s_down"        :  SHIFT + ��
    "key_s_right"       :  SHIFT + ��
    "key_s_left"        :  SHIFT + ��
    "key_s_bup"         :  SHIFT + [��]
    "key_s_bdown"       :  SHIFT + [��]
    "key_s_bright"      :  SHIFT + [��]
    "key_s_bleft"       :  SHIFT + [��]
    "key_s_zenpeji"     :  SHIFT + �O��
    "key_s_jipeji"      :  SHIFT + ����
    "key_s_ins"         :  SHIFT + �}��
    "key_s_del"         :  SHIFT + �폜
    "key_c_home"        :  CTRL + home
    "key_c_up"          :  CTRL + ��
    "key_c_down"        :  CTRL + ��
    "key_c_right"       :  CTRL + ��
    "key_c_left"        :  CTRL + ��
    "key_c_bup"         :  CTRL + [��]
    "key_c_bdown"       :  CTRL + [��]
    "key_c_bright"      :  CTRL + [��]
    "key_c_bleft"       :  CTRL + [��]
    "key_c_zenpeji"     :  CTRL + �O��
    "key_c_jipeji"      :  CTRL + ����
    "key_c_ins"         :  CTRL + �}��
    "key_c_del"         :  CTRL + �폜
    "key_pf1"           :  �o�e�P
    "key_pf2"           :  �o�e�Q
    "key_pf3"           :  �o�e�R
    "key_pf4"           :  �o�e�S
    "key_pf5"           :  �o�e�T
    "key_pf6"           :  �o�e�U
    "key_pf7"           :  �o�e�V
    "key_pf8"           :  �o�e�W
    "key_pf9"           :  �o�e�X
    "key_pf10"          :  �o�e�P�O
    "key_pf11"          :  �o�e�P�P
    "key_pf12"          :  �o�e�P�Q
    "key_c_pf1"         :  CTRL + �o�e�P
    "key_c_pf2"         :  CTRL + �o�e�Q
    "key_c_pf3"         :  CTRL + �o�e�R
    "key_c_pf4"         :  CTRL + �o�e�S
    "key_c_pf5"         :  CTRL + �o�e�T
    "key_c_pf6"         :  CTRL + �o�e�U
    "key_c_pf7"         :  CTRL + �o�e�V
    "key_c_pf8"         :  CTRL + �o�e�W
    "key_c_pf9"         :  CTRL + �o�e�X
    "key_c_pf10"        :  CTRL + �o�e�P�O
    "key_c_pf11"        :  CTRL + �o�e�P�P
    "key_c_pf12"        :  CTRL + �o�e�P�Q
    "key_bleft"         :  [��]
    "key_bright"        :  [��]
    "key_ins"           :  �}��
    "key_del"           :  �폜
    "key_bup"           :  [��]
    "key_bdown"         :  [��]
    "key_jipeji"        :  ����
    "key_zenpeji"       :  �O��
    "key_right"         :  ��
    "key_home"          :  home
    "key_left"          :  ��
    "key_dup"           :  DUP
    "key_fm"            :  FM
    "key_m_com1"        :  �}�E�X�ŃR�}���h���j���[��1�Ԃ߂��N���b�N
        ...                                  ...
    "key_m_com40"       :  �}�E�X�ŃR�}���h���j���[��40�Ԃ߂��N���b�N

  �W�D�Q �R�}���h�����X�g
    "func_nop"          :  �������Ȃ�(�L�[�ݒ�����ׂ̈̃_�~�[�R�}���h)
    "func_mouse"        :  �}�E�X�̓��������Ɏg�p(���[�U�g�p�s��)
    "func_ret"          :  �t�@�C���̓��e�\���^�f�B���N�g���̈ړ�
    "func_select"       :  �t�@�C���̑I��
    "func_quit"         :  �����𔲂���
    "func_delete"       :  �t�@�C��/�f�B���N�g���̍폜
    "func_copy"         :  �t�@�C��/�f�B���N�g���̃R�s�[
    "func_cp_tree"      :  �t�@�C��/�f�B���N�g���̃R�s�[
                           (�c���[�\���ɂ���ăR�s�[��w��)
    "func_edit"         :  �t�@�C���̃G�f�B�g
    "func_exec"         :  �t�@�C�������s
    "func_shell"        :  �V�F���̋N��
    "func_tree1"        :  �f�B���N�g���̃c���[�\���\��
    "func_tree2"        :  �f�B���N�g���̃c���[�\����T�����A�\��
    "func_find"         :  �t�@�C���\���}�X�N�̎w��
    "func_up"           :  �J�[�\���̏�����̈ړ�
    "func_down"         :  �J�[�\���̉������̈ړ�
    "func_left"         :  �J�[�\���̍������̈ړ�
    "func_right"        :  �J�[�\���̉E�����̈ړ�
    "func_s_up"         :  �P�őO�Ɉړ�
    "func_s_down"       :  �P�Ō�Ɉړ�
    "func_bs"           :  �o�b�N�X�y�[�X�R�}���h(��������͎�)
    "func_del"          :  �f���[�g�R�}���h(��������͎�)
    "func_scr_1"        :  1��t�@�C���\�����[�h��
    "func_scr_2"        :  2��t�@�C���\�����[�h��
    "func_scr_4"        :  4��t�@�C���\�����[�h��
    "func_rdraw"        :  ��ʂ̍ĕ`��
    "func_all_sel"      :  �\������Ă���t�@�C���S����I����Ԃɂ���
    "func_chdir"        :  �J�����g�f�B���N�g���̕ύX
    "func_rename"       :  �t�@�C�����̕ύX(�t�@�C���̈ړ�)
    "func_mount"        :  �t���b�s�[�f�B�X�N�̃}�E���g(/dev/fd2d0a -> /fd1)
    "func_umount"       :  �t���b�s�[�f�B�X�N�̃A���}�E���g
    "func_mkdir"        :  �f�B���N�g���̍쐬
    "func_arclist"      :  �A�[�J�C�u�t�@�C���̓��e�\��
    "func_archive"      :  �t�@�C���̃A�[�J�C�u
    "func_unarc"        :  �t�@�C���̃A���A�[�J�C�u
    "func_pushd"        :  �J�����g�f�B���N�g�����X�^�b�N�Ƀv�b�V��
    "func_popd"         :  �X�^�b�N����f�B���N�g�����|�b�v
    "func_jump"         :  �t�@�C�����̐擪1�������w�肵�A�J�[�\�����ړ� 
    "func_move"         :  �t�@�C��/�f�B���N�g���̈ړ�
    "func_mv_tree"      :  �t�@�C��/�f�B���N�g���̈ړ�
                           (�c���[�\���ɂ���ăR�s�[��w��)
    "func_backdir"      :  ��O�̃f�B���N�g���Ɉړ�
    "func_forwdir"      :  ���̃f�B���N�g���Ɉړ�

�X�D���p������
  �{�v���O�����̓t���[�E�G�A�Œ��쌠�͕������Ă��܂���B�Ȃ��z�z�A�ύX���ɍ�
���Ă͈ȉ��Ɏ������ӎ�����K������ĉ������B

  (1) ���쌠�\���y�ѕ\����ʒ��̍�҂̖��O���폜�܂��͕ύX���Ȃ��ŉ������B
  (2) �l�Ŏg�p����ꍇ�Ɍ��莩�R�ɉ��ς��č\���܂���B
  (3) �Ĕz�z�ɍۂ��Ă͈ȉ��̎���������ĉ������B
    (a) �K�������ōs�Ȃ��ĉ������B(�A���A�X�������̎���͏����܂�)
    (b) �Œ���T�t�B�b�N�X��'.doc'�̃t�@�C���͓Y�t���Ă��������B
    (c) �o�[�W�����A�b�v�ɂ͂ł������Ή����ĉ������B
    (d) �ł���΍�҂܂Ō��񉺂����B(�`���͂���܂���)
  (4) ���ς����{�v���O�����܂��́A�{�v���O�����̈ꕔ���g�p�����v���O��������
      �J����ꍇ�͈ȉ��̎���������ĉ������B
    (a) �I���W�i���Ƃ̍��𖾊m�ɂ��ĉ������B
    (b) ���O�ɍ�҂܂ł��A���������B
    (c) �������g�p���ċ��Ȃ����v�𓾂�s�ׂ͍s�Ȃ�Ȃ��ŉ������B
  (5) �{�v���O�������p�\�R���ʐM�ȊO�̃��f�B�A�Ō��J����ꍇ�͕K����҂̗���
      �𓾂ĉ������B
�@(6) �{�v���O�������g�p�������Ƃɂ���Đ��������Q�͕ۏ؂��������˂܂��B

�P�O�D��  ��
  Ver 1.00  1990/04/16  T.Tashiro
    �V�K�쐬
  Ver 1.01  1990/04/17  T.Tashiro
    ��������͋y�сA�f�B���N�g���c���[�\�����̍폜�����ǉ�
  Ver 1.02  1990/04/17  T.Tashiro
    �L�[���͊֐��̃o�O���Ƃ�
  Ver 1.03  1990/04/18  T.Tashiro
    �L�[���͊֐��̃o�O���Ƃ�
  Ver 1.04  1990/04/20  T.Tashiro
    1�������̓��[�`���̃o�O�t�B�b�N�X
  Ver 1.05  1990/04/20  T.Tashiro
    �q�X�g���[�@�\�̃o�O�t�B�b�N�X
  Ver 1.06  1990/05/14  T.Tashiro
    �e�L�X�g�t�@�C���̕\�����̃o�O���t�B�b�N�X
  Ver 2.00  1990/07/23  T.Tashiro
    VT Terminal����g�p�\��
    shell�R�}���h��cd�������悤�ɂȂ���
    shell�R�}���h��A�����s�\��
    �f�B���N�g���c���[�\����ʂ�path�ʒu��\��
    �e�L�X�g�t�@�C���̕\�����������������̂��C��
    �t�@�C���������̃}�X�N�@�\��ǉ�
    copy���Ƀf�B���N�g���c���[���g�p��
    �t�@�C���\����ʂ̕������ύX��
  Ver 2.01  1990/07/27  T.Tashiro
    �t�@�C�������}�X�N�ƃt�@�C�����Ƃ̔�r�֐��̃o�O���t�B�b�N�X
  Ver 2.02  1990/07/31  T.Tashiro
    �q�X�g���[�@�\��ύX
  Ver 2.10  1990/08/08  T.Tashiro
    2050�}�E�X�Ή��o�[�W����
  Ver 2.11  1990/07/27  T.Tashiro
    �f�B���N�g���c���[�̌�������/�񋖉@�\��ǉ�
  Ver 2.12  1990/09/12  T.Tashiro
    termcap�G���g�����g�p����悤�ɕύX����
  Ver 2.13  1990/10/15  T.Tashiro
    �R�}���h�}�N���̉�͕��̃o�O���t�B�b�N�X
  Ver 2.14  1990/10/23  T.Tashiro
    �R�}���h���j���[�̍ő�l��20����40�ɕύX
  Ver 2.20  1991/01/25  T.Tashiro
    ���C�����[�`����ύX
  Ver 2.30  1991/03/28  T.Tashiro
    �v���O�����̓����\���̕ύX
    �A�[�J�C�o�̃T�|�[�g
    �f�B���N�g���P�ʂ̃R�s�[/�폜�̃T�|�[�g
  Ver 2.31  1991/03/28  T.Tashiro
    ��ʂ̍s���̕ω��ɑΉ�����悤�ɕύX
  Ver 2.32  1991/06/21  T.Tashiro
    �f�B���N�g���X�^�b�N�@�\��ǉ�
  Ver 2.33  1991/07/15  T.Tashiro
    14�����ȏ�̃t�@�C�����ɑΉ�
  Ver 2.34  1991/07/16  T.Tashiro
    1���������̃J�[�\���W�����v�@�\
  Ver 2.35  1991/09/04  T.Tashiro
    �O���R�}���h���s��̒[���ݒ�̎�荞�݂���߂�
  Ver 3.00  1991/11/26  T.Tashiro
    X Window System �Ή��I�v�V����������
    MINIX �Ή��̃I�v�V����������
    ���N�ȏ�O�̃t�@�C���͎����̕\���łȂ��N��\������悤�ɂ���
    Shell�R�}���h�Ȃǂ̃q�X�g���o�b�t�@���t�@�C���ɑޔ�����悤�ύX
    �R�}���h�����s���鎞,�I���������Ƀt�@�C������u��������悤�ύX
    �f�B���N�g����push����ۃJ�[�\���ʒu���o����悤�ɕύX
    '~'����ϐ���cd�R�}���h��copy�R�}���h�Ŏg�p�ł���悤�ύX
    �}�N�����C������}�N���I�v�V�������g�p�\�ɂ���
    �V���{���b�N�����N���ꂽ�t�@�C���̃R�s�[�̓����N�̒��蒼����
    �V���{���b�N�����N���ꂽ�t�@�C���̍폜�͖{�̂Ƃ̃A�������N�ɕύX
    copy�R�}���h�ŃR�s�[��t�@�C�������ɑ��݂��邩�𒲂ׁA������₢���킹��
    �l�ɂ���
    tree�R�}���h�ŃT�[�`����͍̂ŏ��J�����g�f�B���N�g���݂̂ɂ��A���̌�w��
    ���ꂽ�f�B���N�g���̂݃T�[�`����悤�ɕύX����
    (Ver3.00�ւ̃o�[�W�����A�b�v�ɂ����蔒�䗲����(GBA01426)�ɑ���ȋ��͂𒸂��A
     tree�R�}���h��V���{���b�N�����N�ւ̑Ή��ȂǂŃ\�[�X�R�[�h���Q�l�ɂ�����
     �����܂����B�����Ɋ��Ӓv���܂��B)
  Ver 3.01  1991/01/21  T.Tashiro
    "c"�R�}���h���ł�'~username'�����̃f�B���N�g���w��Ń��[�U����20���ȏゾ��
    ���삪�s����ɂȂ�o�O���t�B�b�N�X�i���䗲����̎w�E�j
    "mv"�����"MV"�R�}���h��ǉ�
    MINIX ACK�p��'search_tcp()'��'src_tcp()','search_cp()'��'src_cp()'��
    'strncat2()'��'strnct2()'�ɕύX
    'fu.c'���傫���Ȃ肷�����̂�'fu.c'��'kfunc.c'�ɕ�������
�@�@��̃f�B���N�g�����R�s�[�^�폜���悤�Ƃ���ƃn���O����o�O���C��
    Sunview��OpenWindows��Shell-Tool�ł�'fu'���g�p�ł���悤�ɂ���
  Ver 3.02  1991/09/07  T.Tashiro
�@�@�T�t�B�b�N�X��'.lzh'�̃t�@�C���̃f�t�H���g�̃A�[�J�C�o��'lha'�ɕύX
�@�@�A�[�J�C�u�t�@�C���̓��e�\���̏o�͂�more/pg�Ńp�C�v����l�ɕύX
�@�@xfu�ŃV�F�����[�h���ɂ͉�ʂɂ��̎|�\������悤�ύX
�@�@'%*'�}�N���Ń������̋�������t�@�C������u��������悤�ύX
�@�@EUC�����R�[�h�ɑΉ�
�@�@xfu�ŃJ�i�̃t�H���g�t�@�C���̃R�[�h�͈͂������F������悤�ɂ���
�@�@���̑��ׂ̍����o�O�̏C��
  Ver 3.03  1993/05/22  T.Tashiro
�@�@�f�B���N�g���̍폜�Ńt�@�C������14�������z������̂�����ƈُ�I������
�@�@�o�O���C��
�@�@�R�s�\�����[�h��ǉ�
  Ver 3.04  1996/07/09  T.Tashiro
�@�@hpterm���̃E�C���h�E�g�̕ό`�ɒǏ]����@�\��ǉ�
�@�@root�Ŏ��s�����ꍇ�̓^�C�g����'='��'*'�ŕ\��
  Ver 3.05  1997/09/26  T.Tashiro
�@�@TAB�L�[�Ńt�@�C������⊮����@�\��ǉ�
�@�@'<','>'�L�[�ň�O�̃f�B���N�g���ɖ߂�/�ēx��ɐi�ދ@�\��ǉ�
  Ver 3.06  1998/02/04  T.Tashiro
�@�@'-a'�I�v�V������t���ċN�������core dump����o�O���C��
  Ver 3.07  1998/06/18  T.Tashiro
�@�@�R��\�����[�h�̏ꍇ�A�����t�@�C����������ƂP��̕��𒲐�����
�@�@�t�@�C�������S�ĕ\�������悤�ɂ����B

�P�P�D�o�O���̑�
�@����'fu'�ɂ͈ȉ��̕s��_���������Ă��܂����C������Ă��܂���B
  (1) HP9000���'hpterm'���Ŏg�p����ƃ��o�[�X�\�������������鎖������܂��B
  �@�@�i�@�\�I�ɂ͖�肠��܂���j
  (2) 'xfu'��2050�ȊO�̋@��Ŏg�p����Ƌ����I�������B���ɁASun���
      OpenWindows�͑����������B�i'XMapRaized','XSetInputFocus'�ӂ肪�E�C��
      �h�E�}�l�[�W���Ƃ��񂩂�����j

�P�Q�D���̑�
  �v���O������      �F  �t�������v�r�p�t�@�C���Ǘ����[�e�B���e�B�i�����j
  �K�p�@��y�тn�r  �F  HITACHI 2050�t�@�~���[,HI-UX Rel3 �ȍ~
                        Sun SPARC Station SunOS
                        HP9000 Series HP-UX
                        MINIX Ver1.5 (PC-9801 ASCII-MINIX)
                        Linux on AT�݊��@
                        Sony NEWS 3400 NEWS-OS (Ver 3.91R)
                        Sony NEWS 3800 NEWS-OS (Ver 4.0.1R)
  �v���O���~���O����F  �t�m�h�w  �b
  �v���O�����쐬��  �F  �c�� �� (Nifty-ID PDC02432)
