/*
	File Utility ( Main Module )

	Author	T.Tashiro (Nifty PDC02432)	1990-04-16	Ver 1.00
	Modify	T.Tashiro (Nifty PDC02432)	1990-04-17	Ver 1.01
		getstr	: Del Key Function
		tree	: Del Key Function
	Modify	T.Tashiro (Nifty PDC02432)	1990-04-17	Ver 1.02
		key_in	: Bug ( key_in() -> key_in(flg) )
	Modify	T.Tashiro (Nifty PDC02432)	1990-04-18	Ver 1.03
		key_in	: Bug ( strncat() -> strncat2() )
	Modify	T.Tashiro (Nifty PDC02432)	1990-04-20	Ver 1.04
		get_keycode : Bug Fix
	Modify	T.Tashiro (Nifty PDC02432)	1990-04-26	Ver 1.05
		getstr.c : Bug Fix ( History )
	Modify	T.Tashiro (Nifty PDC02432)	1990-05-14	Ver 1.06
		command.c : Bug Fix ( type_file() : fopen - fclose )
	Modify	T.Tashiro (Nifty PDC02432)	1990-07-27	Ver 2.00
		useful for vt terminal
		'cd' command can use on shell mode
		display directory path on tree command
		fixed more scroll on typefile command
		add file find function
		can execute shell command continuously
		dir tree diplay mode was useful on copy command
		can change file name display columns
	Modify	T.Tashiro (Nifty PDC02432)	1990-07-27	Ver 2.01
		fu.c : Bug Fix ( strrecmp() )
	Modify	T.Tashiro (Nifty PDC02432)	1990-07-31	Ver 2.02
		fu.c : Modify ( get_str() : history )
	Modify	T.Tashiro (Nifty PDC02432)	1990-08-08	Ver 2.10
		fu.c : Modify ( Mouse Version )
	Modify	T.Tashiro (Nifty PDC02432)	1990-08-23	Ver 2.11
		tree.c : Modify ( Tree search lock select )
	Modify	T.Tashiro (Nifty PDC02432)	1990-09-12	Ver 2.12
		Use Termcap
	Modify	T.Tashiro (Nifty PDC02432)	1990-10-15	Ver 2.13
		debug : getstr & exe_command
	Modify	T.Tashiro (Nifty PDC02432)	1990-10-23	Ver 2.14
		fu.c fu.h : Mouse Command Max 20 -> 40 , Redraw Screen
	Modify	T.Tashiro (Nifty PDC02432)	1991-01-25	Ver 2.20
		fu.c fu.h : Modify
	Modify	T.Tashiro (Nifty PDC02432)	1991-03-28	Ver 2.30
		Modify Source File ReConstruct
		Modify Key Input Routine
		Append Archiver Support
		Append Directory Copy Function
		Append Directory Remove Function
		etc.
	Modify	T.Tashiro (Nifty PDC02432)	1991-03-28	Ver 2.31
		Version Up for Change Screen Row and Column Width
	Modify	T.Tashiro (Nifty PDC02432)	1991-06-21	Ver 2.32
		Add function 'push directory' and 'pop directory'
	Modify	T.Tashiro (Nifty PDC02432)	1991-07-15	Ver 2.33
		Modify for too long filename
	Modify	T.Tashiro (Nifty PDC02432)	1991-07-16	Ver 2.34
		Add function 'Cursor Jump'
	Modify	T.Tashiro (Nifty PDC02432)	1991-09-04	Ver 2.35
		remove 'trmdef()' from system2()
	Modify	T.Tashiro (Nifty PDC02432)	1991-11-26	Ver 3.00
		Add X Window System Version
		Add MINIX Version (Normal or Bcc)
		Display year of file 
		Save Command Line History Buffer
		Execute command in order of your selection
		Save cursor position when execute directory push command
		Make '~' and enviroment variables useful on 'cd' command
		Add the following macro options
			%?@p	file prefix
			%?@s	file suffix
			%?@d	current directory name
			%?@a	dir.name + filename
		Copy and Delete command was adapted to the Symbolic Linked file
		Check Duplicated file on Copy Command
		Change How to Display the Directory Tree
	Modify	T.Tashiro (Nifty PDC02432)	1992-01-21	Ver 3.01
		Bug fix ('~username' username greater than 20 character then 
			 broken other local valiables)
		Add 'move' command
		replace 'search_tcp() -> src_tcp()'
			'search_cp() -> src_cp()'
			'strncat2() -> strnct2()'   for MINIX ACK compiler
		Bug fix (if you try to delete/copy empty directory then
		         core dumped -> fixed)
		Split Source file 'fu.c' -> 'fu.c' and 'kfunc.c'
		fix for Sunview and OpenWindows Shell-Tool termcap
	Modify	T.Tashiro (Nifty PDC02432)	1992-09-07	Ver 3.02
		- change archiver from lharc to lha
		- more display support for ArcList command
		- shell mode information add to xfu
		- when memory available,'%*' macro make effort to use
		- adapted to EUC kanji and kana code
		- automatic code check for X Window kanji and kana font
	Modify	T.Tashiro (Nifty PDC02432)	1992-11-23	Ver 3.03
		- 386BSD(PC-9801) Support
		- PANIX Support
		- Add environmental variables 'FURC' and 'FUHIST'
		- Add screen mode '3'
		- Add './' path when 'x' command
	Modify	T.Tashiro (Nifty PDC02432)	1996-06-21	Ver 3.04
		- SIGWINCH enabled
		- status bar change from "===" to "***" when root user
	Modify	T.Tashiro (Nifty PDC02432)	1997-09-26	Ver 3.05
		- add filename complement ability to getstr()
		- add directory history function (back and forward)
	Modify	T.Tashiro (Nifty PDC02432)	1998-02-04	Ver 3.06
		- fixed bug about core dump at '-a' option
	Modify	T.Tashiro (Nifty PDC02432)	1998-06-18	Ver 3.07
		- adjust column width depend on the filename width when sc_mode = 3
	Modify	T.Tashiro (Nifty PDC02432)	1999-06-09	Ver 3.08
		- BeOS support
	Modify	T.Tashiro (Nifty PDC02432)	2005-05-11	Ver 3.09
		- Cygwin support
		- sort files correctly
		- ignore '@' at the top of filename when filename complement
		- output candidate file list if there are many candidate when
		   file name complemention
		- 'tgz', '.tar.gz', '.zip' file support
	Modify	T.Tashiro (Nifty PDC02432)	2017-07-12	Ver 3.10
		- MacOS support
	Modify	T.Tashiro (Nifty PDC02432)	2021-01-16	Ver 3.20
		- UTF-8 support
		- add FUNC_KILL, FUNC_PASTE, FUNC_HOME and FUNC_END
*/
/************************************************************************
*									*
*	LICENCED MATERIAL OF T.TASHIRO					*
*	REPRODUCTION, USE, MODIFICATION,DISCLOSURE OTHERWISE THAN	*
*	PERMITTED IN THE LICENCE AGREEMENT IS STRICTLY PROHIBITED.	*
*	COPYRIGHT (C) T.TASHIRO 1990.         ALL RIGHTS RESERVED.	*
*									*
*************************************************************************/
#include <stdio.h>
#if MINIX
#  undef NULL
#endif
#include <string.h>
#include <sys/types.h>
#if MINIX
#  undef NULL 
#  include <stdlib.h>
#else
#  include <memory.h>
#  if !(NEWS3400 | I386BSD)
#    include <malloc.h>
#  endif
#  if I386BSD
#    include <sys/malloc.h>
#  endif
#endif
#include <sys/stat.h>
#if NEWS3400
#  include <sys/dir.h>
#  define dirent	direct
#else
#  include <dirent.h>
#endif
#include <signal.h> 
#include <time.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#if MINIX
/*#  include <unistd.h>*/
#endif
#include <errno.h>
#if H2050
#  include <2050/window.h>
#endif
#include "key.h"
#include "fu.h"
#include "futable.h"

main(argc,argv)
int argc;
char **argv;
{
	int st,c;
	char *getenv(),setupfn[255],*hp;

	prog_name = argv[0];
	get_option(argc,argv);

	st = TRUE;
	if ( (hp = getenv("FURC")) != NULL ) {
		strcpy(setupfn,hp);
		st = setup(setupfn);
	}
	if ( st ) {
		if ( (hp = getenv("HOME")) != NULL ) {
			strcpy(setupfn,hp);
			strcat(setupfn,"/");
			strcat(setupfn,SETUP_FN);
			st = setup(setupfn);
		}
	}
	if ( st ) {
		strcpy(setupfn,"/usr/lib/");
		strcat(setupfn,SETUP_FN);
		st = setup(setupfn);
	}

	st = TRUE;
	if ( (hp = getenv("FUHIST")) != NULL ) {
		strcpy(setupfn,hp);
		st = read_history(setupfn);
	}
	if ( st ) {
		if ( (hp = getenv("HOME")) != NULL ) {
			strcpy(setupfn,hp);
			strcat(setupfn,"/");
			strcat(setupfn,HIST_FILE);
			st = read_history(setupfn);
		}
	}

	pager = getenv("FUPAGER");
	if ( (lzharc = getenv("FULZH")) == NULL ) {
		lzharc = LZHARC;
	}

	for ( c = 0 ; c < DIR_HIST_CN ; c++ ) dir_hist[c] = NULL;
	dir_hcn = 0;

	get_uid_gid();

	user_id = getuid();

	srand(time((long *)0));

#if XWINDOW
/*	signal(SIGCLD,reap_child); */
/*	sighold(SIGCLD); */
	x_init(argc,argv);
	xt_cls();
#endif
	t_init();
	trmset();
#if !(XWINDOW)
	t_cls();
#endif
	get_file_ent();
	adjust_screen_mode();
	sel_file();
}

get_option(argc,argv)
int argc;
char **argv;
{
#if XWINDOW
	int c;
	char *arg;

	win_name = icon_name = prog_name;
	for ( c = 0 ; c < argc ; c++ ) {
		arg = argv[c];
		if ( arg[0] == '-' ) {
			if ( arg[1] == 'd' ) {				/* display */
				if ( ++c >= argc ) fu_usage();
				xdispname = argv[c];
			} else if ( arg[1] == 'g' ) {			/* geometry */
				if ( ++c >= argc ) fu_usage();
				xgeom = argv[c];
			} else if ( arg[1] == 'f' && arg[2] == 'n' ) {	/* font */
				if ( ++c >= argc ) fu_usage();
				xfont = argv[c];
				opt_setflg |= OPT_FONT;
			} else if ( arg[1] == 'f' && arg[2] == 'r' ) {	/* font kana */
				if ( ++c >= argc ) fu_usage();
				xfontj = argv[c];
				opt_setflg |= OPT_RFONT;
			} else if ( arg[1] == 'f' && arg[2] == 'k' ) {	/* font kanji */
				if ( ++c >= argc ) fu_usage();
				xfontk = argv[c];
				opt_setflg |= OPT_KFONT;
			} else if ( arg[1] == 'f' && arg[2] == 'g' ) {	/* foreground */
				if ( ++c >= argc ) fu_usage();
				xforename = argv[c];
				opt_setflg |= OPT_FG;
			} else if ( arg[1] == 'b' ) {			/* background */
				if ( ++c >= argc ) fu_usage();
				xbackname = argv[c];
				opt_setflg |= OPT_BG;
			} else if ( arg[1] == 'n' ) {			/* name (title) */
				if ( ++c >= argc ) fu_usage();
				win_name = icon_name = argv[c];
				opt_setflg |= OPT_NAME;
			} else if ( arg[1] == 'a' ) {			/* ascii code only */
				ascii = TRUE;
			} else if ( arg[1] == 'k' ) {			/* use kanji code */
				ascii = FALSE;
			} else if ( arg[1] == 'e' ) {		/* use euc kanji code */
				os_kj_code = KJ_CODE_EUC;
			} else if ( arg[1] == 's' ) {		/* use shift-jis kanji code */
				os_kj_code = KJ_CODE_SJIS;
			} else if ( arg[1] == 'u' ) {		/* use utf-8 kanji code */
				os_kj_code = KJ_CODE_UTF8;
			} else fu_usage();
		}
	}
#else
	int c,err;
	extern int optind;

	err = FALSE;
	while ( ( c = getopt(argc,argv,"akesu") ) != -1 ) {
		switch ( c ) {

			case 'a' :
				ascii = TRUE;
				break;
			case 'k' :
				ascii = FALSE;
				break;
			case 'e' :
				os_kj_code = KJ_CODE_EUC;	/* use euc code */
				break;
			case 's' :
				os_kj_code = KJ_CODE_SJIS;	/* use shift jis */
				break;
			case 'u' :
				os_kj_code = KJ_CODE_UTF8;	/* use utf-8 code */
				break;
			default :
				err = TRUE;
				break;
		}
	}
/*	for ( ; optind < argc ; optind++ ) {
		fntb[fnc] = argv[optind];
		++fnc;
	}
*/
	if ( err ) fu_usage();
#endif

	return;
}

fu_usage()
{
	fprintf(stderr,"usage: %s [-options ...]\n",prog_name);
	fprintf(stderr,"where options includes:\n");
	fprintf(stderr,"    -a   don't use kanji code\n");
	fprintf(stderr,"    -k   use kanji code\n");
	fprintf(stderr,"    -e   use euc kanji code\n");
	fprintf(stderr,"    -s   use s-jis kanji code\n");
#if XWINDOW
	fprintf(stderr,"    -display host:display    X server name\n");
	fprintf(stderr,"    -geometry geom           geometry of %s\n",prog_name);
	fprintf(stderr,"    -name title              window title name\n");
	fprintf(stderr,"    -fg color                foreground color\n");
	fprintf(stderr,"    -bg color                background color\n");
	fprintf(stderr,"    -fn fontname             font name\n");
	fprintf(stderr,"    -fr font_kana            kana font name\n");
	fprintf(stderr,"    -fk font_kanji           kanji font name\n");
	fprintf(stderr,"    -euc                     treat euc kanji code\n");
	fprintf(stderr,"    -sjisi                   treat s-jis kanji code\n");
#endif

	exit(-1);
}

int
read_history(fn)
char *fn;
{
	FILE *fp;
	char buf[512];
	int ln;

	if ( (fp = fopen(fn,"r")) == NULL ) return TRUE;
	for ( hcn = 0 ; fgets(buf,512,fp) != NULL && hcn < HIST_CN ; hcn++ ) {
		ln = strlen(buf);
		if ( ln > 0 && buf[ln-1] == '\n' ) buf[ln-1] = '\0';
		hist[hcn] = (char *)malloc((strlen(buf)+1)*sizeof(char));
		if ( hist[hcn] == NULL ) {
			fprintf(stderr,"%s:cannot allocate memory\n",prog_name);
			fclose(fp);
			return TRUE;
		}
		strcpy(hist[hcn],buf);
	}
	fclose(fp);
	return FALSE;
}

write_history()
{
	char fn[512];
	char *getenv(),*hp;
	FILE *fp;
	int c;

	if ( (hp = getenv("FUHIST")) != NULL ) {
		strcpy(fn,hp);
	} else {
		if ( (hp = getenv("HOME")) == NULL ) return;
		strcpy(fn,hp);
		strcat(fn,"/");
		strcat(fn,HIST_FILE);
	}

	if ( (fp = fopen(fn,"w")) == NULL ) return;
	for ( c = 0 ; c < hcn ; c++ ) {
		fprintf(fp,"%s\n",hist[c]);
	}
	fclose(fp);

}

get_uid_gid()
{
	struct passwd *pw;
	struct passwd *getpwent();
	void endpwent();
	struct group *gp;
	struct group *getgrent();
	void endgrent();
#if !(MINIX | HP9000)
	char *malloc();
#endif

	while ( (pw = getpwent()) != NULL ) {
		if ( uid_cn >= USER_ID_ENT ) break;
		uid[uid_cn].uid = pw->pw_uid;
		if ( (uid[uid_cn].uname = (char *)malloc(sizeof(char)*(strlen(pw->pw_name)+1)))
			== NULL ) break;
		strcpy(uid[uid_cn].uname,pw->pw_name);
		++uid_cn;
	}
	endpwent();

	while ( (gp = getgrent()) != NULL ) {
		if ( gid_cn >= GROUP_ID_ENT ) break;
		gid[gid_cn].gid = gp->gr_gid;
		if ( (gid[gid_cn].gname = (char *)malloc(sizeof(char)*(strlen(gp->gr_name)+1)))
			== NULL ) break;
		strcpy(gid[gid_cn].gname,gp->gr_name);
		++gid_cn;
	}
	endgrent();

	return;
}

set_sc_column()
{
	int c, ln;
	int max_width;

	max_width = SCMD3_COLUMN;
	for ( c = 0 ; c < dpc ; c++ ) {
		if ( (ln = kj_width_str(fent[c].d_name) + 3) > max_width ) max_width = ln;
	}
	sc_column[3] = (max_width > X_WIDTH - 2) ? X_WIDTH - 2 : max_width ;

        if ( sc_mode == 3 ) {
		fname_column = (X_WIDTH - 2) / sc_column[sc_mode];
		dp = (curp / DSP_CN) * DSP_CN;
	}
}

extern int sort_dir();

get_file_ent()
{
	DIR *dirp;
	struct dirent *dir;
	struct stat st_buf;
	char dirname[20];
	int c,st;
#if !(H2050 | MINIX)
	struct stat lst_buf;
	int islink,lst;
#endif

	for ( c = 0 ; c < dpc ; c++ )
		if ( fent[c].d_name ) free(fent[c].d_name);

	dp = dpc = maxsel = 0;
	strcpy(dirname,".");

	if ( (dirp = opendir(dirname)) == NULL ) {
		return;
	}
	while ( (dir = readdir(dirp)) != NULL ) {
		fent[dpc].d_name = (char *)malloc((strlen(dir->d_name) + 1) * sizeof(char));
		if ( fent[dpc].d_name )	strcpy(fent[dpc].d_name,dir->d_name);
		else {
			fprintf(stderr,"%s:Memory allocation failed !",prog_name);
#if XWINDOW
			x_close();
#endif
			trmdef();
#if !(XWINDOW)
			t_loc(X_WIDTH-1,Y_WIDTH-1);
#endif
			printf("\n");
			t_dspcur();
			exit(-1);
		}
		fent[dpc].sel = 0;
		fent[dpc].st_mode = 0;
		fent[dpc].st_nlink = 0;
		fent[dpc].st_uid = -1;
		fent[dpc].st_gid = -1;
		fent[dpc].st_size = 0;
		fent[dpc].st_mtim = 0;
		islink = FALSE;
#if H2050 | MINIX
		st = stat(fent[dpc].d_name,&st_buf);
#else
		if ( !(st = lstat(fent[dpc].d_name,&st_buf)) ) {
			if ( (st_buf.st_mode & FILE_TYPE) == FILE_SLINK ) {
				islink = TRUE;
				lst = stat(fent[dpc].d_name,&lst_buf);
			}
		}
#endif
		if ( !st ) {
			fent[dpc].st_mode = st_buf.st_mode;
			fent[dpc].st_nlink = st_buf.st_nlink;
			fent[dpc].st_uid = st_buf.st_uid;
			fent[dpc].st_gid = st_buf.st_gid;
			fent[dpc].st_size = st_buf.st_size;
			fent[dpc].st_mtim = st_buf.st_mtime;
		}
#if !(H2050 | MINIX)
		if ( islink ) {
			fent[dpc].st_mode = fent[dpc].st_mode << 16;
			if ( !lst ) fent[dpc].st_mode |= lst_buf.st_mode;
		}
#endif
		if ( (fent[dpc].st_mode & FILE_TYPE) == FILE_DIR
			|| strrecmp(f_temp,fent[dpc].d_name) == 0 ) {
			++dpc;
		} else if ( fent[dpc].d_name ) free(fent[dpc].d_name);
	}

	closedir(dirp);

	if ( dpc > 1 ) {
		qsort((char *)fent,dpc,sizeof(struct F_ENT_TAG)
			,sort_dir);
	}

	set_sc_column();

	if ( getcwd(cwd,DIR_LEN) == NULL ) cwd[0] = '\0';

	return;
}

int
sort_dir(ent1,ent2)
struct F_ENT_TAG *ent1,*ent2;
{
	int md1,md2;

        if ( strcmp(ent1->d_name, ".") == 0 ) return -1;
        if ( strcmp(ent2->d_name, ".") == 0 ) return 1;
        if ( strcmp(ent1->d_name, "..") == 0 ) return -1;
        if ( strcmp(ent2->d_name, "..") == 0 ) return 1;

	md1 = ent1->st_mode & FILE_TYPE;
	md2 = ent2->st_mode & FILE_TYPE;
	if ( md1 != md2 && md1 == FILE_DIR ) return -1;
	else if ( md1 != md2 && md2 == FILE_DIR ) return 1;
	return strcmp(ent1->d_name,ent2->d_name);
}

strrecmp(str1,str2)
char *str1,*str2;
{
	char *p;

	p = str2;
	while ( *str1 != '\0' && *str2 != '\0' ) {
		if ( *str1 != '?' ) {
			if ( *str1 == '*' ) {
				if ( *(str1 + 1) == '\0'
					|| *(str1 + 1) == ' ' ) return 0;
				while ( *str2 != '\0' ) {
					if ( strrecmp(str1+1,str2) == 0 )
						return 0;
					++str2;
				}
				while ( *str1 != ' ' && *str1 != '\0' ) ++str1;
				while ( *str1 == ' ' ) ++str1;
				if ( *str1 == '\0' ) return -1;
				str2 = p;
				continue;
			} else if ( *str1 == ' ' ) {
				while ( *str1 == ' ' ) ++str1;
				if ( *str1 == '\0' ) return -1;
				str2 = p;
				continue;
			} else {
				if ( *str1 != *str2 ) {
					while ( *str1 != ' ' && *str1 != '\0' )
						++str1;
					while ( *str1 == ' ' ) ++str1;
					if ( *str1 == '\0' ) return -1;
					str2 = p;
					continue;
				}
			}
		}
		++str1;
		++str2;
	}
	if ( *str2 == '\0' && (*str1 == '\0' || *str1 == ' ') ) return 0;
	return -1;
}

adjust_screen_mode()
{
	if ( X_WIDTH - 2 < sc_column[3] ) {
		sc_mode = 4;
	} else if ( X_WIDTH - 2 < sc_column[2] ) {
		sc_mode = 3;
	} else if ( X_WIDTH - 2 < sc_column[1] ) {
		sc_mode = 2;
	}
	fname_column = (X_WIDTH - 2) / sc_column[sc_mode];
	dp = (curp / DSP_CN) * DSP_CN;
}

dsp_com_mes()
{
	int x,y;
	int c;
	char buf[1000];

	dsp_cdir();

	clr_mes_area();
	y = DSP_ROW + 2;
	x = 10;
	xt_loc(0,DSP_ROW+1);
	xt_reverse();
	if ( TITLEMINX <= X_WIDTH ) {
		sprintf(buf,"== File Management Utility Ver.3.20 ");
		for ( c = strlen(buf) ; c < X_WIDTH - 13 ; c++ ) buf[c] = '=';
		buf[c] = '\0';
		strcat(buf," T.Tashiro ==");
	} else {
		sprintf(buf,"== fu 3.10 ");
		for ( c = strlen(buf) ; c < X_WIDTH - 7 ; c++ ) buf[c] = '=';
		buf[c] = '\0';
		strcat(buf," T.T ==");
	}
	if ( user_id == 0 ) {
		for ( c = 0 ; buf[c] != '\0' ; c++ ) {
			if ( buf[c] == '=' ) buf[c] = '*';
		}
	}
	xt_puts(buf);
	xt_normal();
	xt_loc(0,DSP_ROW+2);
	xt_reverse();
	xt_puts("Command");
	xt_normal();
	xt_puts(" : ");
	for ( c = 0 ; com[c].str != NULL ; c++ ) {
		if ( x + strlen(com[c].str) >= X_WIDTH ) {
			x = 10;
			if ( y >= Y_WIDTH-2 ) break;
			++y;
		}
		com[c].x = x;
		com[c].y = y;
		com[c].len = strlen(com[c].str);
		xt_loc(x,y);
		xt_puts(com[c].str);
		x = x + strlen(com[c].str) + 1;
	}
	for ( ; com[c].str != NULL ; c++ ) {
		com[c].x = com[c].y = com[c].len = -1;
	}
	find_y = y+1;
	xt_loc(0,find_y);
	xt_reverse();
	xt_puts("Find");
	xt_normal();
	xt_puts(" : ");
	strcpy(buf,f_temp);
	buf[X_WIDTH - 7] = '\0';
	xt_puts(f_temp);
}


clr_mes_area()
{
	int y,c;

#if !XWINDOW
	t_scroff();
#endif
	for ( y = DSP_ROW + 2 ; y < Y_WIDTH ; y++ ) {
		xt_loc(0,y);
		xt_erase_line();
	}
#if !XWINDOW
	t_scron();
#endif

	return;
}

dsp_cdir()
{
	int ln;
	char buf[300];

	xt_loc(0,0);
	xt_reverse();
	xt_puts("Current Dir");
	xt_normal();
	sprintf(buf,"(%1d) : ",pushd_cn);
	xt_puts(buf);
	ln = X_WIDTH - 17;
	strncpy(buf,cwd,ln);
	buf[ln] = '\0';
	xt_puts(buf);
	xt_erase_line();
}

com_exe(fc)
int fc;
{
	int st;
	char temp[MAX_STR];

	if ( func_cmd[fc].func != NULL ) (*func_cmd[fc].func)();
	else {
		if ( func_cmd[fc].temp != NULL && func_cmd[fc].temp[1] != '\0' ) {
			strcpy(temp,func_cmd[fc].temp);
		} else *temp = '\0';
		f_shell(temp,func_cmd[fc].flg);
	}
}

f_nop()
{
}

dsp_fl3(cp,flg)
int cp,flg;
{
	int ret;

	ret = FALSE;
	if ( cp < dp || cp >= dp + DSP_CN ) {
		dp = ( cp / DSP_CN ) * DSP_CN;
		dsp_fl();
		dsp_com_mes();
		ret = TRUE;
	}
	if ( flg ) dsp_fl2(cp,REV_DISP);
	else dsp_fl2(cp,NORM_DISP);

	return ret;
}

beep()
{
	fprintf(stdout,"\007");
	fflush(stdout);
}

dsp_fl2(cp,revflg)
int cp,revflg;
{
	int x,y,s,c,c2,fn_c;
	struct tm *tim;
	char buf[512],buf2[512];
	char *ctime(),*p;
	ushort st_mode;

	x = (( cp - dp ) / DSP_ROW) * sc_column[sc_mode];
	y = ( cp - dp ) % DSP_ROW+1;
	xt_loc(x,y);
	if ( cp >= dpc ) {
		for ( c = 0 ; c < sc_column[sc_mode] ; c++ ) buf[c] = ' ';
		buf[c] = '\0';
		xt_puts(buf);
		return;
	}
	*buf = '\0';
	if ( fent[cp].sel ) strcat(buf,"*");
	else strcat(buf," ");
#if !(H2050 | MINIX)
	if ( fent[cp].st_mode & 0xffff0000 )
		st_mode = fent[cp].st_mode >> 16;
	else st_mode = fent[cp].st_mode;
#else
	st_mode = fent[cp].st_mode;
#endif
	s = 0;
	if ( (fent[cp].st_mode & FILE_TYPE) == FILE_DIR ) s = 1;
	if ( s == 0 ) strcat(buf," ");
	else strcat(buf,"[");
	if ( sc_mode == 3 ) fn_c = sc_column[sc_mode] - 3;
	else fn_c = 14;
	strcpy(buf2,fent[cp].d_name);
	for ( c = c2 = 0 ; c < fn_c ; ) {
		if ( buf2[c2] == '\0' || (c + kj_width(buf2 + c2)) > fn_c ) {
			buf2[c2] = ' ';
			buf2[c2+1] = '\0';
			c++;
			c2++;
		} else {
			c += kj_width(buf2 + c2);
			c2 += kj_lenc(buf2[c2]);
		}
	}
	buf2[c2] = '\0';
	strcat(buf,buf2);
	if ( s == 0 ) strcat(buf," ");
	else strcat(buf,"]");
	if ( sc_mode == 4 ) {
/*		strcat(buf,"  ");	*/
	} else if ( sc_mode <= 2 ) {
		switch ( st_mode & FILE_TYPE ) {
			case FILE_FIFO :
				strcat(buf,"p");
				break;	
			case FILE_CHAR :
				strcat(buf,"c");
				break;
			case FILE_DIR :
				strcat(buf,"d");
				break;
			case FILE_BLOCK :
				strcat(buf,"b");
				break;
			case FILE_SLINK :
				strcat(buf,"l");
				break;
			case FILE_SOCK :
				strcat(buf,"s");
				break;
			default :
				strcat(buf,"-");
				break;
		}
		if ( st_mode & ACC_U_R ) strcat(buf,"r");
		else strcat(buf,"-");
		if ( st_mode & ACC_U_W ) strcat(buf,"w");
		else strcat(buf,"-");
		if ( (st_mode & SET_UID)
			&& (st_mode & ACC_U_X) ) strcat(buf,"s");
		else if ( (st_mode & SET_UID)
			&& !(st_mode & ACC_U_X) ) strcat(buf,"S");
		else if ( st_mode & ACC_U_X ) strcat(buf,"x");
		else strcat(buf,"-");
		if ( st_mode & ACC_G_R ) strcat(buf,"r");
		else strcat(buf,"-");
		if ( st_mode & ACC_G_W ) strcat(buf,"w");
		else strcat(buf,"-");
		if ( (st_mode & SET_GID)
			&& (st_mode & ACC_G_X) ) strcat(buf,"s");
		else if ( (st_mode & SET_GID)
			&& !(st_mode & ACC_G_X) ) strcat(buf,"l");
		else if ( st_mode & ACC_G_X ) strcat(buf,"x");
		else strcat(buf,"-");
		if ( st_mode & ACC_O_R ) strcat(buf,"r");
		else strcat(buf,"-");
		if ( st_mode & ACC_O_W ) strcat(buf,"w");
		else strcat(buf,"-");
		if ( (st_mode & STICKY)
			&& (st_mode & ACC_O_X) ) strcat(buf,"t");
		else if ( (st_mode & STICKY)
			&& !(st_mode & ACC_O_X) ) strcat(buf,"T");
		else if ( st_mode & ACC_O_X ) strcat(buf,"x");
		else strcat(buf,"-");

		if ( sc_mode == 2 ) {
			tim = localtime(&fent[cp].st_mtim);
			if ( now - fent[cp].st_mtim < HALF_YEAR ) {
				sprintf(buf2," %02d/%02d %02d:%02d"
					,tim->tm_mon+1,tim->tm_mday
					,tim->tm_hour,tim->tm_min);
			} else {
				sprintf(buf2," %02d/%02d %4d "
					,tim->tm_mon+1,tim->tm_mday
					,tim->tm_year + 1900);
			}
			strcat(buf,buf2);
		} else {
			sprintf(buf2,"%4d ",fent[cp].st_nlink);
			strcat(buf,buf2);
			strcpy(buf2,"        ");
			for ( c = 0 ; c < uid_cn ; c++ ) {
				if ( uid[c].uid == fent[cp].st_uid ) {
					sprintf(buf2,"%-8s",uid[c].uname);
					break;
				}
			}
			strcat(buf,buf2);
			strcat(buf," ");
			strcpy(buf2,"        ");
			for ( c = 0 ; c < gid_cn ; c++ ) {
				if ( gid[c].gid == fent[cp].st_gid ) {
					sprintf(buf2,"%-8s",gid[c].gname);
					break;
				}
			}
			strcat(buf,buf2);
			strcat(buf," ");
			sprintf(buf2,"%8ld ",fent[cp].st_size);
			strcat(buf,buf2);
			p = ctime(&fent[cp].st_mtim);
			strcpy(buf2,p+4);
			buf2[12] = buf2[20] = '\0';
			strcat(buf,buf2);
			strcat(buf,&buf2[15]);
/*			strcat(buf,"       "); */
		}
	}
	if ( revflg == REV_DISP ) xt_reverse();
#if HP9000
	if ( revflg == NORM_DISP ) xt_normal();
#endif
	xt_puts(buf);
	if ( revflg == REV_DISP ) xt_normal();

	return;
}

/* static char *scrbar = "^  PREV  -  NEXT  v"; */
static char *scrbar1 = "^  PREV";
static char *scrbar2 = "NEXT  v";

dsp_fl()
{
	int c,c2,i;
	char buf[90];

#if !XWINDOW
	xt_cls();
#endif
	dsp_cdir();

	now = time((long *)0);
#if XWINDOW
	for ( c = 0 ; c < DSP_CN ; c++ ) {
#else
	for ( c = 0 ; c < DSP_CN && c + dp < dpc  ; c++ ) {
#endif
		dsp_fl2(c+dp,NORM_DISP);
	}
#if HP9000
	xt_loc(0,0);
#endif

#if XWINDOW
	for ( c = 0 ; c < DSP_ROW ; c++ ) {
		xt_loc(sc_column[sc_mode] * fname_column,c+1);
		xt_erase_line2(2);
	}
#endif
	buf[2] = '\0';
	xt_reverse();
	for ( c = 0 ; c < DSP_ROW && scrbar1[c] != '\0' ; c++ ) {
		xt_loc(X_WIDTH-2,c+1);
#if HP9000
		xt_reverse();
#endif
		buf[0] = buf[1] = scrbar1[c];
		xt_puts(buf);
	}
	for ( c2 = 0 ; c2 < (DSP_ROW - strlen(scrbar1) - strlen(scrbar2)) ; c++,c2++ ) {
		xt_loc(X_WIDTH-2,c+1);
#if HP9000
		xt_reverse();
#endif
		if ( c == DSP_ROW / 2 ) xt_puts("--");
		else xt_puts("  ");
	}
	for ( c2 = 0 ; c < DSP_ROW && scrbar2[c2] != '\0' ; c++,c2++ ) {
		xt_loc(X_WIDTH-2,c+1);
#if HP9000
		xt_reverse();
#endif
		buf[0] = buf[1] = scrbar2[c2];
		xt_puts(buf);
	}
	xt_normal();

#if XWINDOW
	if ( shell_pid > 0 ) dsp_shell();
#endif

	return;
}

#if XWINDOW
static char *shell_message[] = {
	"+----------------------------+",
	"|   SSSS  h         ll  ll   |",
	"|  S    S h     ee   l   l   |",
	"|   SS    hhh  e  e  l   l   |",
	"|     SS  h  h eeee  l   l   |",
	"|  S    S h  h e     l   l   |",
	"|   SSSS  h  h  ee  lll lll  |",
        "+----------------------------+",
	NULL
};

dsp_shell()
{
	int x,y,c;

	for ( c = 0 ; shell_message[c] != NULL ; c++ );
	y = (DSP_ROW - c) / 2;
	x = (X_WIDTH - strlen(shell_message[0])) / 2 - 2;
	if ( x < 2 || y < 2 ) return;
	for ( c = 0 ; shell_message[c] != NULL ; c++, y++ ) {
		xt_loc(x,y);
		xt_puts(shell_message[c]);
	}

	return;
}

int
fork_fu()
{
	if ( (shell_pid = fork()) == 0 ) {
		signal(SIGCLD,SIG_IGN);
		signal(SIGUSR1,SIG_IGN);
		return 0;
	} else if ( shell_pid != -1 ) {
		signal(SIGCLD,reap_child);
		signal(SIGUSR1,sig_usr1);
	}
	return shell_pid;
}

int
reap_child()
{
	int pid,st;

	pid = wait(&st);
	if ( pid == shell_pid ) shell_pid = -1;

	XMapRaised(xdisplay,xwindow);
	XWarpPointer(xdisplay,None,xwindow,0,0,0,0,10,10);
	XSetInputFocus(xdisplay,xwindow,RevertToParent,0);
	XFlush(xdisplay);
}

int
sig_usr1()
{
	int ln,c,f;
	char buf[1024];
	FILE *fp;

	if ( (fp = fdopen(shell_pipe[0],"r")) == NULL ) {
		return;
	}
	while ( fgets(buf,1024,fp) == NULL )
		if ( errno != EINTR ) return;
	f = FALSE;
	ln = strlen(buf);
	if ( ln > 0 && buf[ln-1] == '\n' ) buf[ln-1] = '\0';
	if ( *buf != '\n' && *buf != '\0' ) {
		h_chdir(buf);
		f = TRUE;
	}

	for ( c = 0 ; c < hcn ; c++ ) free(hist[c]);
	for ( hcn = 0 ; hcn < HIST_CN ; hcn++ ) {
		while ( fgets(buf,1024,fp) == NULL )
			if ( errno != EINTR ) break;
		ln = strlen(buf);
		if ( ln > 0 && buf[ln-1] == '\n' ) buf[ln-1] = '\0';
		hist[hcn] = (char *)malloc((strlen(buf)+1)*sizeof(char));
		if ( hist[hcn] == NULL ) return;
		strcpy(hist[hcn],buf);
	}
	fclose(fp);

	if ( f ) {
		get_file_ent();
		if ( curp >= dpc ) curp = ( 0 > dpc-1 )?0:(dpc-1);
		if ( curp < dp || curp >= dp + DSP_CN )
			dp = ( curp / DSP_CN ) * DSP_CN;
	}
	dsp_fl();
	dsp_fl2(curp,REV_DISP);
}
#endif
