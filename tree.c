/*
	File Utility ( Get Tree Entry )

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
#include <stdio.h>
#if MINIX
#  undef NULL
#endif
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#if NEWS3400
#  include <sys/dir.h>
#  define dirent	direct
#else
#  include <dirent.h>
#endif
#include <time.h>
#include "key.h"
#include "fu.h"

#define TR_Y_WIDTH (Y_WIDTH-2)
#define SRCH   1
#define NOSRCH 0
#define THERE  2

int trc = 0;
int tdp,tcp;
int tree_flg = FALSE;

char cdir[DIR_LEN];

get_tr(path)
char *path;
{
	int c,lv;
	char buf[255],*p;

	clr_mes_area();
	xt_loc(0,DSP_ROW+2);
	xt_puts("<< Searching Dir. >>");

	for ( c = 0 ; c < trc ; c++ ) free(trent[c].d_name);
	trc = lv = 0;
	if ( set_trent(trc,lv,"/",0) ) return;
	++trc;
	++lv;
	strcpy(buf,path);
	p = strtok(buf,"/");
	while ( p != NULL ) {
		if ( set_trent(trc,lv,p,0) ) return;
		p = strtok(NULL,"/");
		++trc;
		++lv;
	}
	get_tr2(path);
}

set_trent(p,level,name,flg)
int p,level,flg;
char *name;
{
#if !(MINIX | HP9000)
	char *malloc();
#endif

	if ( (trent[p].d_name = (char *)malloc(sizeof(char)*(strlen(name)+1))) == NULL )
		return ERR;
	trent[p].level = level;
	trent[p].src_flg = flg;
	strcpy(trent[p].d_name,name);
	return NORM;
}

extern int sort_tree();

get_tr2(path)
char *path;
{
	int ln,insp,cp,lv;
	char *p;
	DIR *dirp;
	struct dirent *dir;
	struct stat st_buf;
	char dirname[255];

	cp = src_cp(path);
	lv = trent[cp].level + 1;
	trent[cp].src_flg = SRCH;
	++cp;
	if ( (dirp = opendir(path)) == NULL ) return ERR;

	strcpy(dirname,path);
	ln = strlen(dirname);
	if ( ln > 0 && dirname[ln-1] != '/' ) strcat(dirname,"/");
	p = dirname + strlen(dirname);
	while ( (dir = readdir(dirp)) != NULL && trc < TREE_ENT ) {
		strcpy(p,dir->d_name);
		if ( !stat(dirname,&st_buf) ) {
			if ( ( st_buf.st_mode & FILE_TYPE ) == FILE_DIR
				&& strcmp(dir->d_name,"..") != 0
				&& strcmp(dir->d_name,".") != 0 ) {
				if ( !check_trent(cp,dir->d_name,lv) ) {
					if ( (insp = ins_tr(cp,dir->d_name,lv)) < 0 ) break;
					set_trent(insp,lv,dir->d_name,0);
				}
			}
		}
	}
	closedir(dirp);

	return NORM;
}

int
check_trent(p,dname,lv)
int p,lv;
char *dname;
{
	while ( p < trc && trent[p].level >= lv ) {
		if ( trent[p].level == lv ) {
			if ( strcmp(dname,trent[p].d_name) == 0 )
				return TRUE;
		}
		++p;
	}

	return FALSE;
}

int
ins_tr(st,dname,lv)
int st,lv;
char *dname;
{
	int c;

	for ( ; st < trc && trent[st].level >= lv ; st++ ) {
		if ( trent[st].level == lv &&
			strcmp(trent[st].d_name,dname) >= 0 ) break;
	}
	for ( c = trc - 1 ; c >= st ; c-- ) {
		trent[c+1].d_name = trent[c].d_name;
		trent[c+1].level = trent[c].level;
		trent[c+1].src_flg = trent[c].src_flg;
	}
	++trc;

	return st;
}

tree1()
{
	char path[255];

	if ( !tree(path,TRUE) ) {
		chdir(path);
		curp = 0;
		get_file_ent();
		if ( curp >= dpc ) curp = ( 0 > dpc-1 )?0:(dpc-1);
		if ( curp < dp || curp >= dp + DSP_CN )
			dp = ( curp / DSP_CN ) * DSP_CN;
	}
	dsp_fl();
	dsp_com_mes();

	return;
}

tree2()
{
	char path[255];

	if ( !tree(path,FALSE) ) {
		chdir(path);
		curp = 0;
		get_file_ent();
		if ( curp >= dpc ) curp = ( 0 > dpc-1 )?0:(dpc-1);
		if ( curp < dp || curp >= dp + DSP_CN )
			dp = ( curp / DSP_CN ) * DSP_CN;
	}
	dsp_fl();
	dsp_com_mes();

	return;
}

tree(path,flg)
char *path;
int flg;
{
	int c,c2,ky,f,ret;
	char *getenv(),treefn[256],*hp;

	if ( flg ) get_tr("/");
	else get_tr(cwd);
	if ( trc <= 0 ) return -1;

	t_scroff();
	tdp = 0;
	src_tcp(cwd);
	if ( tcp >= tdp + TR_Y_WIDTH ) tdp = (tcp - 10 > 0)?(tcp - 10):0;
	dsp_tr();
	f = TRUE;
	while ( f ) {
		dsp_tr2(tcp,TRUE);
		dsp_path();
		ky = func_in(FALSE,TRUE);
		dsp_tr2(tcp,FALSE);
		if ( ky & FUNC_MASK ) {
			ky = ky & ~(FUNC_MASK);
			switch ( ky ) {
				case FUNC_MOUSE :
					f = tr_mouse(&ky);
					break;
				case FUNC_SELECT :
				case FUNC_TREE1 :
					tr_get_tree();
					break;
				case FUNC_JUMP :
					tr_kjump();
					break;
				case FUNC_UP :
					tr_kup();
					break;
				case FUNC_S_UP :
					tr_ksup();
					break;
				case FUNC_DOWN :
					tr_kdown();
					break;
				case FUNC_S_DOWN :
					tr_ksdown();
					break;
				case FUNC_BS :
				case FUNC_LEFT :
					tr_kleft();
					break;
				case FUNC_RIGHT :
					tr_kright();
					break;
				case FUNC_QUIT :
				case FUNC_RET :
					f = FALSE;
					break;
				default :
					break;
			}
		} else if ( ky == KEY_ESC2 ) f = FALSE;
	}
	if ( ky == FUNC_RET ) {
		get_trpath(path,tcp);
		ret = 0;
	} else {
		*path = '\0';
		ret = -1;
	}
	chdir(cwd);
	t_scron();

	return ret;
}

src_tcp(path)
char *path;
{
	if ( (tcp = src_cp(path)) < 0 ) tcp = 0;
}

int
src_cp(path)
char *path;
{
	int st,cp;
	int level,c,lv;
	char d_name[80],*p;

	for ( c = level = 0 ; c < strlen(path) ; c++ )
		if ( path[c] == '/' ) ++level;
	if ( path[0] == '/' && path[1] == '\0' ) {
		return 0;
	}
	cp = 0;
	p = path + 1;
	st = 1;
	for ( lv = 1 ; lv <= level ; lv++ ) {
		for ( c = 0 ; p[c] != '\0' && p[c] != '/' ; c++ )
			d_name[c] = p[c];
		d_name[c] = '\0';
		if ( p[c] == '/' ) p = p + c + 1;
		for ( c = st ; c < trc && trent[c].level >= lv ; c++ ) {
			if ( trent[c].level == lv
				&& strcmp(trent[c].d_name,d_name) == 0 ) {
				st = c + 1;
				break;
			}
		}
		if ( c >= trc || trent[c].level < lv ) return 0;
	}
	cp = st - 1;

	return cp;
}

int
tr_mouse(ky)
int *ky;
{
	int p;

	if ( m_stat.stat != MOUSE_L_ON ) {
		if ( m_stat.stat == MOUSE_R_ON ) {
			*ky = KEY_ESC2;
			return FALSE;
		}
	} else 	if ( m_stat.y > 0 ) {
		if ( m_stat.x >= X_WIDTH - 2 ) {	/* Scroll Bar */
			if ( m_stat.y-1 < TR_Y_WIDTH/2 ) tr_ksup();
			else tr_ksdown();
		} else {
			*ky = FUNC_RET;
			p = m_stat.y - 1 + tdp;
			if ( p == tcp ) return FALSE;
			if ( p < trc ) tcp = p;
			tr_get_tree();
		}
	}
	return TRUE;
}

tr_get_tree()
{
	char path[255];

	get_trpath(path,tcp);
	get_tr2(path);
	tdp = 0;
	src_tcp(path);
	if ( tcp >= tdp + TR_Y_WIDTH ) tdp = (tcp-10 < 0)?0:(tcp-10);
	dsp_tr();

	return;
}

tr_kjump()
{
	int c;
	int ky;

	xt_loc(0,TR_Y_WIDTH+1);
	xt_reverse();
	if ( X_WIDTH >= 25 ) xt_puts("Please keyin 1 char.");
	else xt_puts("keyin char");
	xt_normal();
	xt_puts(" : ");
	ky = xgetchr2();

	xt_loc(0,TR_Y_WIDTH+1);
	if ( X_WIDTH >= 25 ) xt_puts("                       ");
	else xt_puts("             ");

	if ( ky <= ' ' ) {
		beep();
		dsp_com_mes();
		return;
	}
	for ( c = tcp + 1 ; ; c++ ) {
		if ( c >= trc ) c = 0;
		if ( c == tcp ) break;
		if ( trent[c].d_name[0] == ky ) break;
	}

	tcp = c;
	if ( tcp < tdp || tcp >= tdp + TR_Y_WIDTH ) {
		 tdp = (tcp-10 < 0)?0:(tcp-10);
		dsp_tr();
	}

	return;
}

tr_ksup()
{
	int dp;

	if ( tdp < 0 || tcp <= 0 ) return;

	dp = tdp;
	tcp -= TR_Y_WIDTH;
	tdp -= TR_Y_WIDTH;
	if ( tcp < 0 ) tcp = 0;
	if ( tdp < 0 ) tdp = 0;
	if ( dp != tdp ) dsp_tr();
}

tr_kup()
{
	int scr,c;

	if ( tcp <= 0 ) return;

	if ( tcp <= tdp ) {
		scr = ( tdp > 10 )?10:tdp;
		tdp -= scr;
		dsp_tr();
	}
	--tcp;
}

tr_ksdown()
{
	if ( tdp + TR_Y_WIDTH > trc - 1 ) {
		tcp = trc - 1;
		return;
	}

	tcp += TR_Y_WIDTH;
	tdp += TR_Y_WIDTH;
	if ( tcp > trc - 1 ) tcp = trc - 1;
	dsp_tr();
}

tr_kdown()
{
	int c;

	if ( tcp >= trc - 1 ) return;

	if ( tcp - tdp >= TR_Y_WIDTH - 1 ) {
		tdp += 10;
		dsp_tr();
	}
	++tcp;
}

tr_kleft()
{
	int c;

	if ( tcp <= 0 ) return;
	for ( c = tcp - 1 ; c >= 0 ; c-- )
		if ( trent[c].level < trent[tcp].level ) break;
	if ( c >= 0 ) tcp = c;
	else --tcp;

	if ( tcp < tdp ) {
		tdp = tcp - 10;
		if ( tdp < 0 ) tdp = 0;
		dsp_tr();
	}
}

tr_kright()
{
	int flg;
	char path[255];

	flg = FALSE;
	if ( !(trent[tcp].src_flg & SRCH ) ) {
		get_trpath(path,tcp);
		get_tr2(path);
		tdp = 0;
		src_tcp(path);
		flg = TRUE;
	}
	if ( tcp < trc - 1 ) ++tcp;
	if ( tcp - tdp > TR_Y_WIDTH - 1 || tcp < tdp ) {
		tdp = tcp - 10;
		if ( tdp < 0 ) tdp = 0;
		dsp_tr();
	} else if ( flg ) dsp_tr();
}

get_trpath(path,cp)
char *path;
int cp;
{
	int c,c2;
	int level;

	*path = '\0';
	c2 = 0;
	for ( level = 1 ; level <= trent[cp].level ; level++ ) {
		for ( c = c2 ; c <= cp ; c++ ) {
			if ( trent[c].level == level ) c2 = c;
		}
		if ( trent[c2].d_name[0] != '/' ) strcat(path,"/");
		strcat(path,trent[c2].d_name);
	}
	if ( *path == '\0' ) {
		*path = '/';
		*(path+1) = '\0';
	}
}

dsp_path()
{
	char buf[512];

	get_trpath(buf,tcp);
	buf[X_WIDTH-7] = '\0';
	xt_loc(0,0);
	xt_erase_line();
	xt_puts("Path : ");
	xt_puts(buf);
}

dsp_tr2(cp,flg)
int cp,flg;
{
	int c,c2,f,ln;
	char buf[1000],*p;

	xt_loc(0,cp - tdp + 1);
	if ( cp < trc ) {
		*buf = '\0';
		for ( c = 0 ; c < trent[cp].level - 1 ; c++ ) {
			for ( c2 = cp+1 , f = FALSE 
				; c2 < trc && trent[c2].level >= c+1 ; c2++ )
				if ( trent[c2].level == c+1 ) f = TRUE;
			if ( f ) strnct2(buf," |  ",X_WIDTH);
			else strnct2(buf,"    ",X_WIDTH);
		}
		if ( trent[cp].level > 0 ) {
			for ( c2 = cp+1 , f = FALSE , c = trent[cp].level
				; c2 < trc && trent[c2].level >= c ; c2++ )
				if ( trent[c2].level == c ) f = TRUE;
			if ( f && trent[cp+1].level >= trent[cp].level )
				strnct2(buf," +-",X_WIDTH);
			else	strnct2(buf," +-",X_WIDTH);
		}
		strnct2(buf," ",X_WIDTH);
		xt_puts(buf);
		p = buf + strlen(buf);
		ln = strlen(trent[cp].d_name);
		ln = strlen(buf) + ((ln > 14)?ln:14);
		if ( ln >= X_WIDTH - 2 ) ln = X_WIDTH - 2;
		strnct2(buf,trent[cp].d_name,X_WIDTH);
		strnct2(buf,"              ",X_WIDTH);
		if ( p - buf < ln ) {
			buf[ln] = '\0';
			if ( flg ) xt_reverse();
#if HP9000
			else xt_normal();
#endif
			xt_puts(p);
			if ( flg ) xt_normal();
		}
		if ( !(trent[cp].src_flg & SRCH) ) xt_puts(" >");
	}

	return;
}

static char *scrbar1 = "^   PREV";
static char *scrbar2 = "NEXT   v";

dsp_tr()
{
	int c,c2;
	char buf[1000];

#if !XWINDOW
	xt_cls();
#endif
	for ( c = tdp ; c < tdp + TR_Y_WIDTH && c < trc ; c++ ) {
		dsp_tr2(c,FALSE);
#if XWINDOW
		xt_erase_line2(2);
#endif
	}

#if XWINDOW
	for ( ; c < tdp + TR_Y_WIDTH ; c++ ) {
		xt_loc(0,c - tdp + 1);
		xt_erase_line2(2);
	}
#endif
	xt_loc(0,Y_WIDTH-1);
	xt_erase_line();

	buf[2] = '\0';
	xt_reverse();
	for ( c = 0 ; scrbar1[c] != '\0' ; c++ ) {
		xt_loc(X_WIDTH-2,c+1);
		buf[0] = buf[1] = scrbar1[c];
#if HP9000
		xt_reverse();
#endif
		xt_puts(buf);
	}
	for ( c2 = 0 ; c2 < (TR_Y_WIDTH - strlen(scrbar1) - strlen(scrbar2)) ; c++,c2++ ) {
		xt_loc(X_WIDTH-2,c+1);
#if HP9000
		xt_reverse();
#endif
		if ( c == TR_Y_WIDTH / 2 ) xt_puts("--");
		else xt_puts("  ");
	}
	for ( c2 = 0 ; c < TR_Y_WIDTH && scrbar2[c2] != '\0' ; c++,c2++ ) {
		xt_loc(X_WIDTH-2,c+1);
		buf[0] = buf[1] = scrbar2[c2];
#if HP9000
		xt_reverse();
#endif
		xt_puts(buf);
	}
	xt_normal();
	return;
}
