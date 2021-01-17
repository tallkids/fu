/*
	File Utility ( Header File )

	Author	T.Tashiro (Nifty PDC02432)	1990-04-16	Ver 1.0
*/
/************************************************************************
*									*
*	LICENCED MATERIAL OF T.TASHIRO					*
*	REPRODUCTION, USE, MODIFICATION,DISCLOSURE OTHERWISE THAN	*
*	PERMITTED IN THE LICENCE AGREEMENT IS STRICTLY PROHIBITED.	*
*	COPYRIGHT (C) T.TASHIRO 1990.         ALL RIGHTS RESERVED.	*
*									*
*************************************************************************/

#if XWINDOW
#  include "xtext.h"
#else
#  define xt_cls()		t_cls()
#  define xt_cur_backward(x)	t_cur_backward(x)
#  define xt_cur_forward(x)	t_cur_forward(x)
#  define xt_erase_line()	t_erase_line()
#  define xt_flush()		t_flush()
#  define xt_loc(x,y)		t_loc(x,y)
#  define xt_putc(x)		t_putc(x)
#  define xt_puts(x)		t_puts(x)
#  define xt_normal()		t_normal()
#  define xt_reverse()		t_reverse()

#  define xget_str(x,y,p1,p2)	get_str(x,y,p1,p2)
#  define xkey_in(x)		key_in(x)
#  define xgetchr()		getchr()
#  define xgetchr2()		getchr2()

#  define xt_row		t_row
#  define xt_column		t_column
#endif

#if MINIX
   typedef unsigned short ushort;
#  undef NULL
#  define NULL 0
#endif

#define FALSE 0
#define TRUE (!FALSE)

#define NORM FALSE
#define ERR TRUE

#define FILE_TYPE 0170000
#define   FILE_FIFO  0010000
#define   FILE_CHAR  0020000
#define   FILE_DIR   0040000
#define   FILE_BLOCK 0060000
#define   FILE_NORM1 0100000
#define   FILE_NORM2 0000000
#define   FILE_SLINK 0120000
#define   FILE_SOCK  0140000
#define ACC_U_R 0000400
#define ACC_U_W 0000200
#define ACC_U_X 0000100
#define ACC_G_R 0000040
#define ACC_G_W 0000020
#define ACC_G_X 0000010
#define ACC_O_R 0000004
#define ACC_O_W 0000002
#define ACC_O_X 0000001
#define SET_UID	0004000
#define SET_GID	0002000
#define STICKY	0001000

#define SLINK_FILE 0x10000

#define HALF_YEAR	(60L*60L*24L*30L*6L)

#define FUNC_MASK	0x8000
#define FUNC_NOP	0
#define FUNC_MOUSE	1
#define FUNC_RET	2
#define FUNC_SELECT	3
#define FUNC_QUIT	4
#define FUNC_DELETE	5
#define FUNC_COPY	6
#define FUNC_CP_TREE	7
#define FUNC_EDIT	8
#define FUNC_EXEC	9
#define FUNC_SHELL	10
#define FUNC_TREE1	11
#define FUNC_TREE2	12
#define FUNC_FIND	13
#define FUNC_UP		14
#define FUNC_DOWN	15
#define FUNC_LEFT	16
#define FUNC_RIGHT	17
#define FUNC_S_UP	18
#define FUNC_S_DOWN	19
#define FUNC_BS		20
#define FUNC_DEL	21
#define FUNC_SCR_1	22
#define FUNC_SCR_2	23
#define FUNC_SCR_3	24
#define FUNC_SCR_4	25
#define FUNC_RDRAW	26
#define FUNC_ALLSEL	27
#define FUNC_CHDIR	28
#define FUNC_RENAME	29
#define FUNC_MOUNT	30
#define FUNC_UMOUNT	31
#define FUNC_MKDIR	32
#define FUNC_ARCLIST	33
#define FUNC_ARCHIVE	34
#define FUNC_UNARC	35
#define FUNC_PUSHD	36
#define FUNC_POPD	37
#define FUNC_JUMP	38
#define FUNC_MOVE	39
#define FUNC_MV_TREE	40
#define FUNC_BACKDIR	41
#define FUNC_FORWDIR	42
#define FUNC_WINCH	43
#define FUNC_FNEXPAND	44
#define FUNC_KILL	45
#define FUNC_PASTE	46
#define FUNC_HOME	47
#define FUNC_END	48

#if MINIX
#  define FILE_ENT		512
#  define TREE_ENT		512
#  define USER_ID_ENT		20
#  define GROUP_ID_ENT		20
#  define DIR_LEN		128
#  define MAX_F_TEMP		60
#  define MAX_KEY_FUNC		150
#  define MAX_FUNC_CMD		100
#  define MAX_DNAME		19
#  define MAX_MCOM		40
#  define MAX_STR		1024
#  define HIST_CN		15
#  define DIR_HIST_CN		10
#else
#  define FILE_ENT		10240
#  define TREE_ENT		1024
#  define USER_ID_ENT		1024
#  define GROUP_ID_ENT		256
#  define DIR_LEN		256
#  define MAX_F_TEMP		60
#  define MAX_KEY_FUNC		200
#  define MAX_FUNC_CMD		200
#  define MAX_DNAME		256
#  define MAX_MCOM		40
#  define MAX_STR		1024
#  define HIST_CN		30
#  define DIR_HIST_CN		30
#endif

#define X_WIDTH (xt_column)
#define Y_WIDTH (xt_row)
/*#define DSP_COLUMN (sc_mode)*/
#define DSP_ROW			(Y_WIDTH - 5)
#define DSP_CN			(DSP_ROW * fname_column)
#define FUNC_TAB		80
#define TITLEMINX		51
#define SCMD3_COLUMN		26			/* minimum column width when sc_mode = 3 */
#define SETUP_FN		".setup.fu"
#define FU_TEMP_FILE		".fuXXXXXX"
#if XWINDOW
#define FU_TEMP2_FILE		"/tmp/.fu2XXXXXX"
#endif
#define HIST_FILE		".history.fu"
#define TEMP_DIR		"/tmp/"
#define MAX_PUSHD		9

#define NORM_DISP		FALSE
#define REV_DISP		TRUE

#define KJ_CODE_SJIS		0
#define KJ_CODE_EUC		1
#define KJ_CODE_UTF8		2

/* Definition for func_cmd.flg */
#define FUNC_SCREEN_FLAG	1	/* Query Before and After Cmmand Execution */
#define ALL_FILE_STAY		2	/* This Command Not Chane File Status */

/* Definition for archive file */
#define ARC_LZH		0
#define ARC_TAR		1
#define ARC_TAz		2
#define ARC_TAZ		3
#define ARC_TARz	4
#define ARC_TARZ	5
#define ARC_TGZ		6
#define ARC_TARGZ	7
#define ARC_ZIP		8

#define LZHARC		"lha"

struct KEY_FUNC_TAG {
	int kcode;
	char *key;
	int func;
	int flg;
};

struct FUNC_CMD_TAG {
	int (*func)();
	char *temp;
	int flg;
};

struct F_ENT_TAG {
	int sel;
	char *d_name;
#if H2050 | MINIX
	ushort st_mode;
#else
	u_long st_mode;
#endif
	short st_nlink;
	ushort st_uid;
	ushort st_gid;
	off_t st_size;
	time_t st_mtim;
};

struct TREE_TAG {
	int level;
	char *d_name;
	int src_flg;		/* TRUE -> Tree Search */
};

struct KNAME_TAG {
	int ky;
	char *kname;
};

struct USER_ID_TAG {
	ushort uid;
	char *uname;
};

struct GROUP_ID_TAG {
	ushort gid;
	char *gname;
};

struct COM_POS_TAG {
	char *str;
	int key,x,y,len;
};


extern char *prog_name;

extern int arc_mode;
extern char *arc_suf[];

extern struct KEY_FUNC_TAG key_func[];
extern struct FUNC_CMD_TAG func_cmd[];
extern char *fnc_name[];
extern struct COM_POS_TAG com[];
extern int d_key;

extern struct F_ENT_TAG fent[];
extern struct TREE_TAG trent[];
extern struct KNAME_TAG kname[];
extern struct USER_ID_TAG uid[];
extern int uid_cn;
extern struct GROUP_ID_TAG gid[];
extern int gid_cn;

extern int user_id;

extern int maxsel;

extern char f_temp[];

extern char *hist[];
extern int hcn;

extern char *dir_hist[];	/* Directory History Buffer */
extern int dir_hcn;		/* Number of Dir. History Buffer */

extern char *pager;		/* Show File Command */
extern char *lzharc;		/* Show File Command */

extern int dp,dpc;
extern int curp;
extern int t_row,t_column;	/* screen row and column width */
extern int sc_mode;		/* screen mode 1,2 or 4 */
extern int fname_column;	/* # of filename display columns */
extern int sc_column[];

extern char cwd[];
extern char edit_temp[];
extern char *push_dir[];	/* Pushed directory */
extern int pushd_cn;		/* Number of pushed directory */

extern int find_y;		/* Find y position */

extern int ascii;		/* text.c */
extern int os_kj_code;		/* os kanji code (0:sjis,1:euc) */
extern int fn_kj_code;		/* font kanji code  (0:sjis,1:jis) */
extern int fn_ka_code;		/* font kana code  (0:a0-df,1:20-5f) */

extern long now;		/* now time */

#if XWINDOW
extern int shell_pid;		/* shell process-id */
extern int shell_pipe[];	/* shell - X interface pipeline */
#endif

extern int get_str();
#if XWINDOW
extern int xget_str();
#endif

extern int kj_lenc();
extern int kj_width();

extern char *skip_sp();
extern int f_nop();
extern int quit_fu();
extern int k_mouse();
extern int k_ret();
extern int k_sp();
extern int k_left();
extern int k_right();
extern int k_up();
extern int k_down();
extern int k_sup();
extern int k_sdown();
extern int k_home();
extern int k_end();
extern int f_rdraw();
extern int k_all_sel();
extern int f_delete();
extern int scr_1();
extern int scr_2();
extern int scr_3();
extern int scr_4();
extern int f_copy();
extern int f_cp_tree();
extern int f_find();
extern int f_edit();
extern int f_exec();
extern int f_shell();
extern int f_jump();
extern int f_move();
extern int f_mv_tree();
extern int shell_esc();
extern int tree1();
extern int tree2();
extern int arc_list();
extern int arc_pack();
extern int arc_unpack();
extern int f_pushd();
extern int f_popd();
extern int f_backdir();
extern int f_forwdir();
extern int f_winch();

extern int beep();
extern int dsp_cdir();
extern int h_chdir();

#if XWINDOW
extern int fork_fu();
extern int reap_child();
extern int sig_usr1();
#endif
