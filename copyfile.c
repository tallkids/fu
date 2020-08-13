/*
	File Utility ( Copy and Move File Command )

	Author	T.Tashiro (Nifty PDC02432)	1990-04-16	Ver 1.0
	Fixed	T.Tashiro (Nifty PDC02432)	1991-02-18	Ver 1.0a
	Fixed	T.Tashiro (Nifty PDC02432)	1991-04-09	Ver 2.0
		Add Copy Directory Function
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
#include <signal.h>
#if MINIX
#  undef NULL
#  include <stdlib.h>
#else
#  if !(NEWS3400 | I386BSD)
#    include <malloc.h>
#  endif
#  if I386BSD
#    include <sys/malloc.h>
#  endif
#endif
#include <sys/types.h>
#include <sys/stat.h>
#if NEWS3400
#  include <sys/dir.h>
#  define dirent	direct
#else
#  include <dirent.h>
#endif
#include <errno.h>
#include "key.h"
#include "fu.h"

#define D_MODE (FILE_DIR | ACC_U_R | ACC_U_W | ACC_U_X | ACC_G_R | ACC_G_X \
 | ACC_O_R | ACC_O_X )

static int cp_mode = 0;
static int is_cp;
static char *cp_str,*cp_str2;

static char temp[255],to_path[255];

f_copy()
{
	cp_str = "Copy";
	cp_str2 = "Cp";
	is_cp = TRUE;
	copymove();
}

f_move()
{
	cp_str = "Move";
	cp_str2 = "Mv";
	is_cp = FALSE;
	copymove();
}

copymove()
{
	int flg,is_dir;
	extern int need_redraw;

	is_dir = FALSE;
	flg = is_select();

	cp_mode = 0;
	clr_mes_area();
	is_dir = FALSE;
	if ( flg ) sprintf(temp,"File %s to",cp_str);
	else {
		if ( (is_dir = is_directory(curp))
			&& (strcmp(fent[curp].d_name,".") == 0
				|| strcmp(fent[curp].d_name,"..") == 0) ) {
			dsp_com_mes();
			return;
		}
		if ( is_dir ) {
			sprintf(temp,"[%s] %s to",fent[curp].d_name,cp_str);
		} else {
			sprintf(temp,"(%s) %s to",fent[curp].d_name,cp_str);
		}
		dsp_fl2(curp,REV_DISP);
	}
	if ( strlen(temp) + 18 >= X_WIDTH ) sprintf(temp,"%s",cp_str2);
	xt_loc(0,DSP_ROW+2);
	to_path[0] = '\0';
	if ( xget_str(to_path,50,temp," : ") || to_path[0] == '\0' ) {
		if ( need_redraw ) dsp_fl();
		dsp_com_mes();
		return;
	}
	get_path(to_path);
	if ( is_dir ) {
		cp_dir(to_path);
		chdir(cwd);
	} else {
		if ( need_redraw ) dsp_fl();
		cp_selfile(to_path);
	}
	get_file_ent();
	if ( curp >= dpc ) curp = ( 0 > dpc-1 )?0:(dpc-1);
	if ( curp < dp || curp >= dp + DSP_CN )
		dp = ( curp / DSP_CN ) * DSP_CN;
	dsp_fl();
	dsp_com_mes();

	return;
}

f_cp_tree()
{
	cp_str = "Copy";
	cp_str2 = "Cp";
	is_cp = TRUE;
	cpmv_tree();
}

f_mv_tree()
{
	cp_str = "Move";
	cp_str2 = "Mv";
	is_cp = FALSE;
	cpmv_tree();
}

cpmv_tree()
{
	int st,flg,is_dir;

	cp_mode = 0;
	is_dir = FALSE;
	flg = is_select();

	is_dir = FALSE;
	if ( !flg && (is_dir = is_directory(curp))
		&& (strcmp(fent[curp].d_name,".") == 0
			|| strcmp(fent[curp].d_name,"..") == 0) ) {
		dsp_com_mes();
		return;
	}
	st = tree(to_path,FALSE);

	dsp_fl();
	dsp_com_mes();
	if ( st || to_path[0] == '\0' )	return;

	if ( is_dir ) {
		cp_dir(to_path);
		chdir(cwd);
	} else {
		dsp_com_mes();
		cp_selfile(to_path);
	}
	get_file_ent();
	if ( curp >= dpc ) curp = ( 0 > dpc-1 )?0:(dpc-1);
	if ( curp < dp || curp >= dp + DSP_CN )
		dp = ( curp / DSP_CN ) * DSP_CN;
	dsp_fl();
	dsp_com_mes();

	return;
}

cp_selfile(to_path)
char *to_path;
{
	char from[255];
	int c,dp_sv,sel;

	if ( is_select() ) {
		dp_sv = dp;
		for ( sel = 1 ; sel <= maxsel ; sel++ ) {
			for ( c = 0 ; c < dpc ; c++ ) {
				if ( fent[c].sel == sel ) {
					dsp_fl3(c,TRUE);
					if ( cp_file(fent[c].d_name,to_path) ) {
						dsp_fl3(c,FALSE);
						return;
					}
					dsp_fl3(c,FALSE);
				}
			}
		}
		dp = dp_sv;
	} else {
		dsp_fl3(curp,TRUE);
		cp_file(fent[curp].d_name,to_path);
	}
}

int
cp_file(from,to)
char *from,*to;
{
	int flg,ln,c;
	struct stat sbuf;
	char to2[255],tmp[255],*from2;

	ln = strlen(from);
	for ( c = ln - 1 ; c >= 0 && from[c] != '/' ; c-- );
	if ( c >= 0 ) from2 = &from[c+1];
	else from2 = from;

	strcpy(to2,to);
	flg = FALSE;
	if ( !stat(to2,&sbuf) ) {
		if ( (sbuf.st_mode & FILE_TYPE) == FILE_DIR ) {
			ln = strlen(to2);
			if ( ln > 0 && to2[ln-1] != '/' ) strcat(to2,"/");
			strcat(to2,from2);
			if ( !stat(to2,&sbuf) ) flg = TRUE;
		} else flg = TRUE;
	}
	if ( flg == TRUE && cp_mode == 0 ) {
		clr_mes_area();
		xt_loc(0,DSP_ROW+2);
		if ( X_WIDTH >= 70 ) {
			sprintf(tmp,"%s Duplicated (Skip,Time,Force,Abort)[s] : ",from2);
		} else	sprintf(tmp,"%s :",from2);
		xt_puts(tmp);
		cp_mode = get_how("sStTfFaA");
	}
	if ( flg == FALSE ) {
		cp_fl2(from,to2);
	} else {
		switch ( cp_mode ) {
			case 'a' :
			case 'A' :
				return TRUE;
			case 's' :
				cp_mode = 0;
			case 'S' :
				break;
			case 't' :
				cp_mode = 0;
			case 'T' :
				if ( chk_ftime(from,to2) )
					cp_fl2(from,to2);
				break;
			case 'f' :
				cp_mode = 0;
			case 'F' :
				cp_fl2(from,to2);
				break;
		}
	}

	return NORM;
}

cp_fl2(from,to)
char *from,*to;
{
	int ln;
	struct stat sbuf;
	char tmp[255];

#if H2050 | MINIX
	if ( is_cp ) sprintf(tmp,"cp '%s' '%s'",from,to);
	else sprintf(tmp,"mv '%s' '%s'",from,to);
	xt_loc(0,1);
	system2(tmp);
#else
	if ( !lstat(from,&sbuf)
		&& (sbuf.st_mode & FILE_TYPE) == FILE_SLINK
		&& (ln = readlink(from,tmp,255)) > 0 ) {
		tmp[ln] = '\0';
		unlink(to);
		if ( symlink(tmp,to) != -1 && !is_cp ) unlink(from);
	} else {
		if ( is_cp ) sprintf(tmp,"cp '%s' '%s'",from,to);
		else sprintf(tmp,"mv '%s' '%s'",from,to);
		xt_loc(0,0);  
		system2(tmp);
	}
#endif
}

chk_ftime(from,to)
char *from,*to;
{
	struct stat sbuf1,sbuf2;

	if ( stat(from,&sbuf1) ) return FALSE;
	if ( stat(to,&sbuf2) ) return TRUE;
	if ( sbuf1.st_mtime > sbuf2.st_mtime ) return TRUE;
	else return FALSE;
}

static char copyfile[255];
struct D_ENTRY {
	char d_name[MAX_DNAME];
	struct D_ENTRY *p;
};

cp_dir(path)
char *path;
{
	int ln;
	struct stat sbuf;
	char tmp[255];

	xt_loc(0,DSP_ROW+3);
	sprintf(tmp,"*** Now %sing ***",cp_str);
	xt_puts(tmp);

#if H2050 | MINIX
	if ( chdir(path) ) {
		mkdir(path,D_MODE);
		if ( chdir(path) ) return;
	}
	mk_fname(copyfile,fent[curp].d_name,cwd);
	cp_dir2(copyfile);
#else
	mk_fname(copyfile,fent[curp].d_name,cwd);
	if ( !lstat(copyfile,&sbuf)
		&& (sbuf.st_mode & FILE_TYPE) == FILE_SLINK
		&& (ln = readlink(copyfile,tmp,255)) > 0 ) {
		tmp[ln] = '\0';
		unlink(path);
		if ( symlink(tmp,path) != -1 && !is_cp ) unlink(copyfile);
	} else {
		if ( chdir(path) ) {
			mkdir(path,D_MODE);
			if ( chdir(path) ) return;
		}
		cp_dir2(copyfile);
	}
#endif
}

int
cp_dir2(path)
char *path;
{
	int flg,ln;
	DIR *dirp;
	struct dirent *dir;
	char copypath[255];
	char tmp[255];
	struct stat sbuf;
	struct D_ENTRY dent,*de,*p;

	strcpy(copypath,path);
	if ( (dirp = opendir(copypath)) == NULL ) {
		fprintf(stderr,"Cannot Open Directory !!\n");
		return -1;
	}
	de = &dent;
	de->p = NULL;
	while ( (dir = readdir(dirp)) != NULL ) {
		if ( strcmp(dir->d_name,".") != 0
			&& strcmp(dir->d_name,"..") != 0 ) {
			if ( (p = (struct D_ENTRY *)malloc(sizeof(struct D_ENTRY)) ) == NULL ) {
				fprintf(stderr,"Cannot Allocate Memory !!\n");
				break;
			}
			de->p = p;
			de = p;
			de->p = NULL;
			strcpy(de->d_name,dir->d_name);
		}
	}
	closedir(dirp);

	de = dent.p;
	flg = FALSE;		/* Error Flag */
	while ( de != NULL ) {
		mk_fname(copyfile,de->d_name,copypath);
#if H2050 | MINIX
		if ( !flg && !stat(copyfile,&sbuf) ) {
#else
		if ( !flg && !lstat(copyfile,&sbuf) ) {
			if ( (sbuf.st_mode & FILE_TYPE) == FILE_SLINK ) {
				if ( (ln = readlink(copyfile,tmp,255)) > 0 ) {
					tmp[ln] = '\0';
					unlink(de->d_name);
					if ( symlink(tmp,de->d_name) != -1 && !is_cp )
						unlink(copyfile);
				}
			} else
#endif
			if ( (sbuf.st_mode & FILE_TYPE) == FILE_DIR ) {
				if ( chdir(de->d_name) ) {
					mkdir(de->d_name,D_MODE);
					flg = chdir(de->d_name);
				}
				if ( !flg ) flg = cp_dir2(copyfile);
			} else {	/* if normal file then copy */
				flg = cp_file(copyfile,".");
			}
		}
		p = de->p;
		if ( de != &dent ) free(de);
		de = p;
 	}

	if ( !flg && !chdir("..") )
		return 0;	/* Normal End */
	else	return -1;	/* Abnormal End */
}
