/*
	File Utility ( Push Directory and Pop Directory )

	Author	T.Tashiro (Nifty PDC02432)	1991-06-21	Ver 1.0
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

int
f_pushd()
{
	if ( pushd_cn >= MAX_PUSHD ) {
		beep();
	} else {
		push_dir[pushd_cn] = (char *)malloc(sizeof(char)
			* (strlen(cwd)+1+strlen(fent[curp].d_name)+1));
		if ( push_dir[pushd_cn] != NULL ) {
			strcpy(push_dir[pushd_cn],cwd);
			strcpy((push_dir[pushd_cn] + strlen(cwd) + 1)
				,fent[curp].d_name);
			++pushd_cn;
			dsp_cdir();
		} else beep();
	}

	return NORM;
}

int
f_popd()
{
	char *fn;
	int c,flg;

	if ( pushd_cn > 0 ) {
		flg = FALSE;	/* redraw display flag */
		--pushd_cn;
		if ( strcmp(push_dir[pushd_cn],cwd) != NULL ) {
			h_chdir(push_dir[pushd_cn]);
			curp = 0;
			get_file_ent();
			flg = TRUE;
		}
		fn = push_dir[pushd_cn] + strlen(push_dir[pushd_cn]) + 1;
		for ( c = 0 ; c < dpc ; c++ )
			if ( strcmp(fent[c].d_name,fn) == 0 ) break;
		if ( c < dpc ) curp = c;
		if ( curp < dp || curp >= dp + DSP_CN ) {
			dp = ( curp / DSP_CN ) * DSP_CN;
			flg = TRUE;
		}
		free(push_dir[pushd_cn]);
		if ( flg ) dsp_fl();
		dsp_com_mes();
	}

	return NORM;
}

int
f_backdir()
{
	char *fn;
	int c,flg;
	char *buf;

	if ( dir_hcn > 0 ) {
		if ( dir_hcn >= DIR_HIST_CN || dir_hist[dir_hcn] == NULL ) {
			if ( (buf = (char *)malloc(sizeof(char)
				* (strlen(cwd)+1+strlen(fent[curp].d_name)+1))) == NULL ) {
				return -1;
			}
			if ( dir_hcn >= DIR_HIST_CN ) {
				free(dir_hist[0]);
				for ( c = 0 ; c < DIR_HIST_CN - 1 ; c++ ) {
					dir_hist[c] = dir_hist[c+1];
				}
				dir_hist[c] = NULL;
				--dir_hcn;
			}
			strcpy(buf,cwd);
			strcpy(buf + strlen(cwd) + 1,fent[curp].d_name);
			dir_hist[dir_hcn] = buf;
		}
		flg = FALSE;	/* redraw display flag */
		--dir_hcn;
		if ( strcmp(dir_hist[dir_hcn],cwd) != NULL ) {
			chdir(dir_hist[dir_hcn]);
			curp = 0;
			get_file_ent();
			flg = TRUE;
		}
		fn = dir_hist[dir_hcn] + strlen(dir_hist[dir_hcn]) + 1;
		for ( c = 0 ; c < dpc ; c++ )
			if ( strcmp(fent[c].d_name,fn) == 0 ) break;
		if ( c < dpc ) curp = c;
		if ( curp < dp || curp >= dp + DSP_CN ) {
			dp = ( curp / DSP_CN ) * DSP_CN;
			flg = TRUE;
		}
		if ( flg ) dsp_fl();
		dsp_com_mes();
	}

	return NORM;
}

int
f_forwdir()
{
	char *fn;
	int c,flg;

	if ( dir_hcn < DIR_HIST_CN - 1 && dir_hist[dir_hcn+1] != NULL ) {
		flg = FALSE;	/* redraw display flag */
		++dir_hcn;
		if ( strcmp(dir_hist[dir_hcn],cwd) != NULL ) {
			chdir(dir_hist[dir_hcn]);
			curp = 0;
			get_file_ent();
			flg = TRUE;
		}
		fn = dir_hist[dir_hcn] + strlen(dir_hist[dir_hcn]) + 1;
		for ( c = 0 ; c < dpc ; c++ )
			if ( strcmp(fent[c].d_name,fn) == 0 ) break;
		if ( c < dpc ) curp = c;
		if ( curp < dp || curp >= dp + DSP_CN ) {
			dp = ( curp / DSP_CN ) * DSP_CN;
			flg = TRUE;
		}
		if ( flg ) dsp_fl();
		dsp_com_mes();
	}

	return NORM;
}

