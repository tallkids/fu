/*
	File Utility ( Delete File Command )

	Author	T.Tashiro (Nifty PDC02432)	1990-04-16	Ver 1.0
	Fixed	T.Tashiro (Nifty PDC02432)	1991-02-18	Ver 1.0a
	Fixed	T.Tashiro (Nifty PDC02432)	1991-04-09	Ver 2.0
		Add Delete Directory Function
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
#define dirent	direct
#else
#  include <dirent.h>
#endif
#include <errno.h>
#include "key.h"
#include "fu.h"

f_delete()
{
	int flg,ft,st,curp2,is_dir;
	int c,cn,ky,dp_sv,def,sel;
	char buf[255];

	is_dir = FALSE;
	flg = is_select();

	clr_mes_area();
	if ( flg ) {
		xt_loc(0,DSP_ROW+2);
		if ( X_WIDTH >= 37 ) xt_puts("Are You Sure to Delete ?(y/n)[n] : ");
		else xt_puts("Ok ?(y/n)[n] : ");
		if ( st = get_yn('n') ) {
			dp_sv = dp;
			for ( sel = 1 ; sel <= maxsel ; sel++ ) {
				for ( c = 0 , curp2 = curp ; c < dpc ; c++ ) {
					if ( fent[c].sel == sel ) {
						dsp_fl3(c,TRUE);
						if ( !unlink(fent[c].d_name) )
							if ( c < curp2 ) --curp;
						dsp_fl3(c,FALSE);
					}
				}
			}
			dp = dp_sv;
		}
	} else {
		dsp_fl2(curp,REV_DISP);

		if ( !is_file_norm(curp) && !(is_dir = is_directory(curp)) ) {
			dsp_com_mes();
			return;
		} else if ( is_dir && ( strcmp(fent[curp].d_name,".") == 0
			|| strcmp(fent[curp].d_name,"..") == 0 ) ) {
			dsp_com_mes();
			return;
		}

		xt_loc(0,DSP_ROW+2);
		if ( is_dir ) {
			sprintf(buf,"[%s] Are You Sure to Delete ?(y/n)[n] : "
				,fent[curp].d_name);
			def = 'n';
		} else {
			sprintf(buf,"(%s) Are You Sure to Delete ?(y/n)[y] : "
				,fent[curp].d_name);
			def = 'y';
		}
		if ( strlen(buf) + 2 >= X_WIDTH ) sprintf(buf,"Ok ?(y/n)[y] : ");
		xt_puts(buf);

		if ( st = get_yn(def) ) {
			if ( is_dir ) deldir(curp);
			else unlink(fent[curp].d_name);
		}
	}

	if ( st ) {
		get_file_ent();
		if ( curp >= dpc ) curp = ( 0 > dpc-1 )?0:(dpc-1);
		if ( curp < dp || curp >= dp + DSP_CN )
			dp = ( curp / DSP_CN ) * DSP_CN;
		dsp_fl();
	}

	dsp_com_mes();
	return;

}

static char delfile[255];
struct D_ENTRY {
	char d_name[MAX_DNAME];
	struct D_ENTRY *p;
};

deldir(cp)
int cp;
{
	int c;
	struct stat sbuf;

	xt_loc(0,DSP_ROW+3);
	xt_puts("*** Now deleting ***");

	mk_fname(delfile,fent[cp].d_name,cwd);
#if H2050 | MINIX
	if ( !stat(delfile,&sbuf) && (sbuf.st_mode & FILE_TYPE) != FILE_DIR ) {
#else
	if ( !lstat(delfile,&sbuf) && (sbuf.st_mode & FILE_TYPE) != FILE_DIR ) {
#endif
		unlink(delfile);
		return;
	}
	deldir2(delfile);

	mk_fname(delfile,fent[cp].d_name,cwd);
	rmdir(delfile);
}

deldir2(path)
char *path;
{
	DIR *dirp;
	struct dirent *dir;
	char delpath[255];
	struct stat sbuf;
	struct D_ENTRY dent,*de,*p;

	strcpy(delpath,path);
	if ( (dirp = opendir(delpath)) == NULL ) {
		fprintf(stderr,"Cannot Open Directory !!\n");
		return;
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
	while ( de != NULL ) {
		mk_fname(delfile,de->d_name,delpath);
#if H2050 | MINIX
		if ( !stat(delfile,&sbuf) ) {
			if ( (sbuf.st_mode & FILE_TYPE) == FILE_DIR ) {
#else
		if ( !lstat(delfile,&sbuf) ) {
			if ( (sbuf.st_mode & FILE_TYPE) == FILE_DIR ) {
#endif
				deldir2(delfile);
				mk_fname(delfile,de->d_name,delpath);
				rmdir(delfile);
			} else {	/* if normalfile then remove */
				unlink(delfile);
			}
		}
		p = de->p;
		if ( de != &dent ) free(de);
		de = p;
 	}

	return;
}
