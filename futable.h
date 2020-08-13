/*
	File Utility ( Header File for Table Definition )

*/
/************************************************************************
*									*
*	LICENCED MATERIAL OF T.TASHIRO					*
*	REPRODUCTION, USE, MODIFICATION,DISCLOSURE OTHERWISE THAN	*
*	PERMITTED IN THE LICENCE AGREEMENT IS STRICTLY PROHIBITED.	*
*	COPYRIGHT (C) T.TASHIRO 1990.         ALL RIGHTS RESERVED.	*
*									*
*************************************************************************/

char *prog_name;

/* Key-Command Table */
struct KEY_FUNC_TAG key_func[MAX_KEY_FUNC] = {
	{ KEY_MOUSE,	NULL,	FUNC_MOUSE,	0 },
#if !MINIX
	{ KEY_MCOM1,	NULL,	FUNC_CP_TREE,	0 },
	{ KEY_MCOM2,	NULL,	FUNC_DELETE,	0 },
	{ KEY_MCOM3,	NULL,	FUNC_EDIT,	0 },
	{ KEY_MCOM4,	NULL,	FUNC_FIND,	0 },
	{ KEY_MCOM5,	NULL,	FUNC_QUIT,	0 },
	{ KEY_MCOM6,	NULL,	FUNC_SHELL,	0 },
	{ KEY_MCOM7,	NULL,	FUNC_TREE2,	0 },
	{ KEY_MCOM8,	NULL,	FUNC_TREE1,	0 },
	{ KEY_MCOM9,	NULL,	FUNC_EXEC,	0 },
	{ KEY_MCOM10,	NULL,	FUNC_MOUNT,	0 },
	{ KEY_MCOM11,	NULL,	FUNC_UMOUNT,	0 },
	{ KEY_MCOM12,	NULL,	FUNC_SCR_1,	0 },
	{ KEY_MCOM13,	NULL,	FUNC_SCR_2,	0 },
	{ KEY_MCOM14,	NULL,	FUNC_SCR_3,	0 },
	{ KEY_MCOM15,	NULL,	FUNC_SCR_4,	0 },
	{ KEY_EXPOSE,	NULL,	FUNC_RDRAW,	0 },
#endif
	{ KEY_UP,	NULL,	FUNC_UP,	0 },
	{ KEY_DOWN,	NULL,	FUNC_DOWN,	0 },
	{ KEY_LEFT,	NULL,	FUNC_LEFT,	0 },
	{ KEY_RIGHT,	NULL,	FUNC_RIGHT,	0 },
	{ KEY_C_UP,	NULL,	FUNC_UP,	0 },
	{ KEY_C_DOWN,	NULL,	FUNC_DOWN,	0 },
	{ KEY_C_LEFT,	NULL,	FUNC_LEFT,	0 },
	{ KEY_C_RIGHT,	NULL,	FUNC_RIGHT,	0 },
	{ KEY_S_UP,	NULL,	FUNC_S_UP,	0 },
	{ KEY_S_DOWN,	NULL,	FUNC_S_DOWN,	0 },
	{ KEY_DEL,	NULL,	FUNC_DEL,	0 },
	{ KEY_HOME,	NULL,	FUNC_ALLSEL,	0 },
	{ KEY_ZENPEJI,	NULL,	FUNC_S_UP,	0 },
	{ KEY_JIPEJI,	NULL,	FUNC_S_DOWN,	0 },
#ifdef SIGWINCH
	{ KEY_SIGWINCH,	NULL,	FUNC_WINCH,	0 },
#endif
	{ 0,		"\002",		FUNC_LEFT,	0 },
	{ 0,		"\006",		FUNC_RIGHT,	0 },
	{ 0,		"\010",		FUNC_BS,	0 },
	{ 0,		"\011",		FUNC_FNEXPAND,	0 },
	{ 0,		"\012",		FUNC_RET,	0 },
	{ 0,		"\014",		FUNC_RDRAW,	0 },
	{ 0,		"\015",		FUNC_RET,	0 },
	{ 0,		"\016",		FUNC_DOWN,	0 },
	{ 0,		"\020",		FUNC_UP,	0 },
	{ 0,		"\026",		FUNC_S_DOWN,	0 },
	{ 0,		"\030\003",	FUNC_QUIT,	0 },
	{ 0,		"\032",		FUNC_S_UP,	0 },
	{ 0,		"\177",		FUNC_BS,	0 },
	{ 0,		" ",	FUNC_SELECT,	0 },
	{ 0,		"q",	FUNC_QUIT,	0 },
	{ 0,		"d",	FUNC_DELETE,	0 },
	{ 0,		"c",	FUNC_COPY,	0 },
	{ 0,		"C",	FUNC_CP_TREE,	0 },
	{ 0,		"e",	FUNC_EDIT,	0 },
	{ 0,		"x",	FUNC_EXEC,	0 },
	{ 0,		"s",	FUNC_SHELL,	0 },
	{ 0,		"T",	FUNC_TREE1,	0 },
	{ 0,		"t",	FUNC_TREE2,	0 },
	{ 0,		"f",	FUNC_FIND,	0 },
	{ 0,		"1",	FUNC_SCR_1,	0 },
	{ 0,		"2",	FUNC_SCR_2,	0 },
	{ 0,		"3",	FUNC_SCR_3,	0 },
	{ 0,		"4",	FUNC_SCR_4,	0 },
	{ 0,		"/",	FUNC_CHDIR,	0 },
	{ 0,		"r",	FUNC_RENAME,	0 },
	{ 0,		"mo",	FUNC_MOUNT,	0 },
	{ 0,		"um",	FUNC_UMOUNT,	0 },
	{ 0,		"md",	FUNC_MKDIR,	0 },
	{ 0,		"mv",	FUNC_MOVE,	0 },
	{ 0,		"MV",	FUNC_MV_TREE,	0 },
	{ 0,		"al",	FUNC_ARCLIST,	0 },
	{ 0,		"ar",	FUNC_ARCHIVE,	0 },
	{ 0,		"ua",	FUNC_UNARC,	0 },
	{ 0,		"+",	FUNC_PUSHD,	0 },
	{ 0,		"-",	FUNC_POPD,	0 },
	{ 0,		"<",	FUNC_BACKDIR,	0 },
	{ 0,		">",	FUNC_FORWDIR,	0 },
	{ 0,		"j",	FUNC_JUMP,	0 },
	{ -1,		NULL,	-1,		0 }
};

/* Command Define Table */
struct FUNC_CMD_TAG func_cmd[MAX_FUNC_CMD] = {
	{ f_nop,	NULL,		0 },	/* FUNC_NOP	(func_nop) */
	{ k_mouse,	NULL,		0 },	/* FUNC_MOUSE	(func_mouse) */
	{ k_ret,	NULL,		0 },	/* FUNC_RET	(func_ret) */
	{ k_sp,		NULL,		0 },	/* FUNC_SELECT	(func_select) */
	{ quit_fu,	NULL,		0 },	/* FUNC_QUIT	(func_quit) */
	{ f_delete,	NULL,		0 },	/* FUNC_DELETE	(func_delete) */
	{ f_copy,	NULL,		0 },	/* FUNC_COPY	(func_copy) */
	{ f_cp_tree,	NULL,		0 },	/* FUNC_CP_TREE	(func_cp_tree) */
#if MINIX
	{ NULL,		"elle %*",	1 },	/* FUNC_EDIT	(func_edit) */
#else
#if I386BSD
	{ NULL,		"kemacs %*",	1 },	/* FUNC_EDIT	(func_edit) */
#else
	{ NULL,		"em %*",	1 },	/* FUNC_EDIT	(func_edit) */
#endif
#endif
	{ f_exec,	NULL,		1 },	/* FUNC_EXEC	(func_exec) */
	{ NULL,		"",		1 },	/* FUNC_SHELL	(func_shell) */
	{ tree1,	NULL,		0 },	/* FUNC_TREE1	(func_tree1) */
	{ tree2,	NULL,		0 },	/* FUNC_TREE2	(func_tree2) */
	{ f_find,	NULL,		0 },	/* FUNC_FIND	(func_find) */
	{ k_up,		NULL,		0 },	/* FUNC_UP	(func_up) */
	{ k_down,	NULL,		0 },	/* FUNC_DOWN	(func_down) */
	{ k_left,	NULL,		0 },	/* FUNC_LEFT	(func_left) */
	{ k_right,	NULL,		0 },	/* FUNC_RIGHT	(func_right) */
	{ k_sup,	NULL,		0 },	/* FUNC_S_UP	(func_s_up) */
	{ k_sdown,	NULL,		0 },	/* FUNC_S_DOWN	(func_s_down) */
	{ k_left,	NULL,		0 },	/* FUNC_BS	(func_bs) */
	{ f_delete,	NULL,		0 },	/* FUNC_DEL	(func_del) */
	{ scr_1,	NULL,		0 },	/* FUNC_SCR_1	(func_scr_1) */
	{ scr_2,	NULL,		0 },	/* FUNC_SCR_2	(func_scr_2) */
	{ scr_3,	NULL,		0 },	/* FUNC_SCR_3	(func_scr_3) */
	{ scr_4,	NULL,		0 },	/* FUNC_SCR_4	(func_scr_4) */
	{ f_rdraw,	NULL,		0 },	/* FUNC_RDRAW	(func_rdraw) */
	{ k_all_sel,	NULL,		0 },	/* FUNC_ALLSEL	(func_all_sel) */
	{ NULL,		"cd ",		1 },	/* FUNC_CHDIR	(func_chdir) */
	{ NULL,		"mv \"%1\" ",	1 },	/* FUNC_RENAME	(func_rename) */
	{ NULL,		"mount /dev/fd2d0a /fd1",2 },	/* FUNC_MOUNT	(func_mount) */
	{ NULL,		"umount /dev/fd2d0a",2 },	/* FUNC_UMOUNT	(func_umount) */
	{ NULL,		"mkdir ",	1 },	/* FUNC_MKDIR	(func_mkdir) */
	{ arc_list,	NULL,		0 },	/* FUNC_ARCLIST	(func_arclist) */
	{ arc_pack,	NULL,		0 },	/* FUNC_ARCHIVE	(func_archive) */
	{ arc_unpack,	NULL,		0 },	/* FUNC_UNARC	(func_unarc) */
	{ f_pushd,	NULL,		0 },	/* FUNC_PUSHD	(func_pushd) */
	{ f_popd,	NULL,		0 },	/* FUNC_POPD	(func_popd) */
	{ f_jump,	NULL,		0 },	/* FUNC_JUMP	(func_jump) */
	{ f_move,	NULL,		0 },	/* FUNC_MOVE	(func_move) */
	{ f_mv_tree,	NULL,		0 },	/* FUNC_MV_TREE	(func_mv_tree) */
	{ f_backdir,	NULL,		0 },	/* FUNC_BACKDIR	(func_backdir) */
	{ f_forwdir,	NULL,		0 },	/* FUNC_FORWDIR	(func_forwdir) */
	{ f_winch,	NULL,		0 },	/* FUNC_WINCH	(func_winch) */
	{ NULL,		"",		1 },	/* FUNC_FNEXPAND(func_fn_expand) */
	{ NULL,		NULL,		-1 }
};

/* Command name Definition Table */
char *fnc_name[] = {
	"func_nop",
	"func_mouse",
	"func_ret",
	"func_select",
	"func_quit",
	"func_delete",
	"func_copy",
	"func_cp_tree",
	"func_edit",
	"func_exec",
	"func_shell",
	"func_tree1",
	"func_tree2",
	"func_find",
	"func_up",
	"func_down",
	"func_left",
	"func_right",
	"func_s_up",
	"func_s_down",
	"func_bs",
	"func_del",
	"func_scr_1",
	"func_scr_2",
	"func_scr_3",
	"func_scr_4",
	"func_rdraw",
	"func_all_sel",
	"func_chdir",
	"func_rename",
	"func_mount",
	"func_umount",
	"func_mkdir",
	"func_arclist",
	"func_archive",
	"func_unarc",
	"func_pushd",
	"func_popd",
	"func_jump",
	"func_move",
	"func_mv_tree",
	"func_backdir",
	"func_forwdir",
	"func_winch",
	"func_fn_expand",
	NULL
};

struct F_ENT_TAG fent[FILE_ENT];	/* File Entry Table */
struct TREE_TAG trent[TREE_ENT];	/* Directory Tree Entry Table */
struct USER_ID_TAG uid[USER_ID_ENT];	/* User ID Entry Table */
int uid_cn = 0;				/* Number of User ID Entry */
struct GROUP_ID_TAG gid[GROUP_ID_ENT];	/* Group ID Entry Table */
int gid_cn = 0;				/* Number of Group ID Entry */

/* Key name Definition Table */
struct KNAME_TAG kname[] = {
#if !MINIX
	{ KEY_MCOM1		, "key_m_com1" },
	{ KEY_MCOM2		, "key_m_com2" },
	{ KEY_MCOM3		, "key_m_com3" },
	{ KEY_MCOM4		, "key_m_com4" },
	{ KEY_MCOM5		, "key_m_com5" },
	{ KEY_MCOM6		, "key_m_com6" },
	{ KEY_MCOM7		, "key_m_com7" },
	{ KEY_MCOM8		, "key_m_com8" },
	{ KEY_MCOM9		, "key_m_com9" },
	{ KEY_MCOM10		, "key_m_com10" },
	{ KEY_MCOM11		, "key_m_com11" },
	{ KEY_MCOM12		, "key_m_com12" },
	{ KEY_MCOM13		, "key_m_com13" },
	{ KEY_MCOM14		, "key_m_com14" },
	{ KEY_MCOM15		, "key_m_com15" },
	{ KEY_MCOM16		, "key_m_com16" },
	{ KEY_MCOM17		, "key_m_com17" },
	{ KEY_MCOM18		, "key_m_com18" },
	{ KEY_MCOM19		, "key_m_com19" },
	{ KEY_MCOM20		, "key_m_com20" },
	{ KEY_MCOM21		, "key_m_com21" },
	{ KEY_MCOM22		, "key_m_com22" },
	{ KEY_MCOM23		, "key_m_com23" },
	{ KEY_MCOM24		, "key_m_com24" },
	{ KEY_MCOM25		, "key_m_com25" },
	{ KEY_MCOM26		, "key_m_com26" },
	{ KEY_MCOM27		, "key_m_com27" },
	{ KEY_MCOM28		, "key_m_com28" },
	{ KEY_MCOM29		, "key_m_com29" },
	{ KEY_MCOM30		, "key_m_com30" },
	{ KEY_MCOM31		, "key_m_com31" },
	{ KEY_MCOM32		, "key_m_com32" },
	{ KEY_MCOM33		, "key_m_com33" },
	{ KEY_MCOM34		, "key_m_com34" },
	{ KEY_MCOM35		, "key_m_com35" },
	{ KEY_MCOM36		, "key_m_com36" },
	{ KEY_MCOM37		, "key_m_com37" },
	{ KEY_MCOM38		, "key_m_com38" },
	{ KEY_MCOM39		, "key_m_com39" },
	{ KEY_MCOM40		, "key_m_com40" },
#endif
#if H2050
	{ KEY_TORIKESI		, "key_torikesi" } ,
#endif
	{ KEY_DOWN		, "key_down" } ,
	{ KEY_UP		, "key_up" } ,
#if H2050
	{ KEY_KAKUTYOU		, "key_kakutyou" } ,
	{ KEY_PA1		, "key_pa1" } ,
	{ KEY_PA2		, "key_pa2" } ,
	{ KEY_PA3		, "key_pa3" } ,
	{ KEY_SCREEN		, "key_screen" } ,
	{ KEY_SRQ		, "key_srq" } ,
	{ KEY_PA4		, "key_pa4" } ,
	{ KEY_TYUDAN		, "key_tyudan" } ,
	{ KET_TEST		, "ket_test" } ,
	{ KEY_JIKKOU		, "key_jikkou" } ,
	{ KEY_FIELD		, "key_field" } ,
	{ KEY_PRINT		, "key_print" } ,
	{ KEY_HENKANTAISHOU	, "key_henkantaishou" } ,
	{ KEY_FUNCTION		, "key_function" } ,
	{ KEY_SAIHENKAN		, "key_saihenkan" } ,
	{ KEY_S_FUNCTION	, "key_s_function" } ,
	{ KEY_DATA		, "key_data" } ,
	{ KEY_STOPPRINT		, "key_stopprint" } ,
	{ KEY_C_FUNCTION	, "key_c_function" } ,
#endif
	{ KEY_S_HOME		, "key_s_home" } ,
	{ KEY_S_UP		, "key_s_up" } ,
	{ KEY_S_DOWN		, "key_s_down" } ,
	{ KEY_S_RIGHT		, "key_s_right" } ,
	{ KEY_S_LEFT		, "key_s_left" } ,
#if H2050
	{ KEY_S_BUP		, "key_s_bup" } ,
	{ KEY_S_BDOWN		, "key_s_bdown" } ,
	{ KEY_S_BRIGHT		, "key_s_bright" } ,
	{ KEY_S_BLEFT		, "key_s_bleft" } ,
#endif
	{ KEY_S_ZENPEJI		, "key_s_zenpeji" } ,
	{ KEY_S_JIPEJI		, "key_s_jipeji" } ,
	{ KEY_S_INS		, "key_s_ins" } ,
	{ KEY_S_DEL		, "key_s_del" } ,
	{ KEY_C_HOME		, "key_c_home" } ,
	{ KEY_C_UP		, "key_c_up" } ,
	{ KEY_C_DOWN		, "key_c_down" } ,
	{ KEY_C_RIGHT		, "key_c_right" } ,
	{ KEY_C_LEFT		, "key_c_left" } ,
#if H2050
	{ KEY_C_BUP		, "key_c_bup" } ,
	{ KEY_C_BDOWN		, "key_c_bdown" } ,
	{ KEY_C_BRIGHT		, "key_c_bright" } ,
	{ KEY_C_BLEFT		, "key_c_bleft" } ,
#endif
	{ KEY_C_ZENPEJI		, "key_c_zenpeji" } ,
	{ KEY_C_JIPEJI		, "key_c_jipeji" } ,
	{ KEY_C_INS		, "key_c_ins" } ,
	{ KEY_C_DEL		, "key_c_del" } ,
	{ KEY_PF1		, "key_pf1" } ,
	{ KEY_PF2		, "key_pf2" } ,
	{ KEY_PF3		, "key_pf3" } ,
	{ KEY_PF4		, "key_pf4" } ,
	{ KEY_PF5		, "key_pf5" } ,
	{ KEY_PF6		, "key_pf6" } ,
	{ KEY_PF7		, "key_pf7" } ,
	{ KEY_PF8		, "key_pf8" } ,
	{ KEY_PF9		, "key_pf9" } ,
	{ KEY_PF10		, "key_pf10" } ,
	{ KEY_PF11		, "key_pf11" } ,
	{ KEY_PF12		, "key_pf12" } ,
	{ KEY_C_PF1		, "key_c_pf1" } ,
	{ KEY_C_PF2		, "key_c_pf2" } ,
	{ KEY_C_PF3		, "key_c_pf3" } ,
	{ KEY_C_PF4		, "key_c_pf4" } ,
	{ KEY_C_PF5		, "key_c_pf5" } ,
	{ KEY_C_PF6		, "key_c_pf6" } ,
	{ KEY_C_PF7		, "key_c_pf7" } ,
	{ KEY_C_PF8		, "key_c_pf8" } ,
	{ KEY_C_PF9		, "key_c_pf9" } ,
	{ KEY_C_PF10		, "key_c_pf10" } ,
	{ KEY_C_PF11		, "key_c_pf11" } ,
	{ KEY_C_PF12		, "key_c_pf12" } ,
#if H2050
	{ KEY_BLEFT		, "key_bleft" } ,
	{ KEY_BRIGHT		, "key_bright" } ,
#endif
	{ KEY_INS		, "key_ins" } ,
	{ KEY_DEL		, "key_del" } ,
#if H2050
	{ KEY_BUP		, "key_bup" } ,
	{ KEY_BDOWN		, "key_bdown" } ,
#endif
	{ KEY_JIPEJI		, "key_jipeji" } ,
	{ KEY_ZENPEJI		, "key_zenpeji" } ,
	{ KEY_RIGHT		, "key_right" } ,
	{ KEY_HOME		, "key_home" } ,
	{ KEY_LEFT		, "key_left" } ,
#if H2050
	{ KEY_DUP		, "key_dup" } ,
	{ KEY_FM		, "key_fm" } ,
#endif
	{ 0,NULL }
};

int d_key = USER_KEY;

/* Table for Command Menu */
struct COM_POS_TAG com[MAX_MCOM+1] = {
	"Copy"		,KEY_MCOM1,0,0,0,
	"Delete"	,KEY_MCOM2,0,0,0,
	"Edit"		,KEY_MCOM3,0,0,0,
	"Find"		,KEY_MCOM4,0,0,0,
	"Quit"		,KEY_MCOM5,0,0,0,
	"Shell"		,KEY_MCOM6,0,0,0,
	"Tree"		,KEY_MCOM7,0,0,0,
	"eXecute"	,KEY_MCOM8,0,0,0,
	"Mount"		,KEY_MCOM9,0,0,0,
	"UnMount"	,KEY_MCOM10,0,0,0,
	"(1)"		,KEY_MCOM11,0,0,0,
	"(2)"		,KEY_MCOM12,0,0,0,
	"(3)"		,KEY_MCOM13,0,0,0,
	"(4)"		,KEY_MCOM14,0,0,0,
	NULL		,0,0,0,0
};

int arc_mode = ARC_LZH;

char *arc_suf[] = {
	".lzh",		/* lharc		(ARC_LZH)  */
	".tar",		/* tar			(ARC_TAR)  */	
	".taz",		/* tar + pack		(ARC_TAz)  */
	".taZ",		/* tar + compress	(ARC_TAZ)  */
	".tar.z",	/* tar + pack		(ARC_TARz) */
	".tar.Z",	/* tar + compress	(ARC_TARZ) */
	".tgz",		/* tar + gzip		(ARC_TGZ)  */
	".tar.gz",	/* tar + gzip		(ARC_TARGZ) */
	".zip",		/* zip			(ARC_ZIP) */
	NULL
};

int user_id = -1;		/* current user id number */

int maxsel = 0;			/* maximum number of selected mark */

int find_y;			/* Row Position of "FIND:" */

char f_temp[MAX_F_TEMP] = "*";	/* Find Option Template */

char *hist[HIST_CN];		/* Command History Buffer */
int hcn = 0;			/* Number of History Buffer */

char *dir_hist[DIR_HIST_CN];	/* Directory History Buffer */
int dir_hcn = 0;		/* Number of Dir. History Buffer */

char *pager = NULL;		/* Show File Command */
char *lzharc = NULL;		/* Show File Command */

int dp = 0,dpc = 0;		/* Displayed File Entry Position */
int curp = 0;			/* Cursor Position of File Entry */
int sc_mode = 2;		/* screen mode 1,2 or 4 */
int fname_column = 2;		/* # of filename display columns */
int sc_column[] = { -1,76,39,26,17 };
				/* Column Width of Each Screen Mode */

char cwd[DIR_LEN];		/* Current Directory */
char *push_dir[MAX_PUSHD];	/* Pushed directory */
int pushd_cn = 0;		/* Number of pushed directory */

#if H2050 | HP9000
int os_kj_code = 0;		/* os kanji code (0:sjis,1:euc) */
#else
int os_kj_code = 1;		/* os kanji code (0:sjis,1:euc) */
#endif
int fn_kj_code = 0;		/* font kanji code  (0:sjis,1:jis) */
int fn_ka_code = 0;		/* font kana code  (0:a0-df,1:20-5f) */

long now;			/* now time */

#if XWINDOW
int shell_pid = -1;		/* shell process-id */
int shell_pipe[2] = { -1,-1 };	/* shell - X interface pipeline */
#endif
