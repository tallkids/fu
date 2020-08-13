/*
	File Utility ( Archiver Support Command )

	Author	T.Tashiro (Nifty PDC02432)	1991-04-02	Ver 1.0
*/
/************************************************************************
*									*
*	LICENCED MATERIAL OF T.TASHIRO					*
*	REPRODUCTION, USE, MODIFICATION,DISCLOSURE OTHERWISE THAN	*
*	PERMITTED IN THE LICENCE AGREEMENT IS STRICTLY PROHIBITED.	*
*	COPYRIGHT (C) T.TASHIRO 1991.         ALL RIGHTS RESERVED.	*
*									*
*************************************************************************/
#include <stdio.h>
#if MINIX
#  undef NULL
#endif
#include <string.h>
#include <signal.h>
#if MINIX
#  undef NULL
#  include <stdlib.h>
#else
#  include <memory.h>
#endif
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "key.h"
#include "fu.h"

int
arc_list()
{
	int arc_type;

	if ( !is_file_norm(curp) ) return;

	if ( (arc_type = check_arcfile(fent[curp].d_name)) >= 0 ) {
		arc_ls2(fent[curp].d_name,arc_type);
	}

#if !(XWINDOW)
	dsp_com_mes();
#endif

	return;
}

int
arc_ls2(fn,type)
char *fn;
int type;
{
	int ln;
	char tfn[255];
	char com[80];

#if XWINDOW
	int pid;

	dsp_fl2(curp,REV_DISP);
	XMapRaised(xdisplay,xrootwindow);
	XWarpPointer(xdisplay,None,xrootwindow,0,0,0,0,10,10);
	XSetInputFocus(xdisplay,xrootwindow,RevertToParent,0);
	XFlush(xdisplay);

	dsp_shell();

	if ( (pid = fork_fu()) > 0 || pid == -1 ) return;
#else
	clr_mes_area();
	t_loc(0,DSP_ROW+3);
#endif

	/* Copy Archive file to the Temporary Directory */
	if ( type == ARC_TAz || type == ARC_TARz ) {
		if ( mk_temp_file(tfn,type) ) goto end_arc_list;
		sprintf(com,"cp %s %s",fn,tfn);
		system(com);
		sprintf(com,"unpack %s",tfn);
		system2(com);
		ln = strlen(tfn);
		tfn[ln-2] = '\0';
	}

	/* List of Archive file */
	if ( type == ARC_LZH ) {
		sprintf(com,"%s v %s ",lzharc,fn);
	} else if ( type == ARC_ZIP ) {
		sprintf(com,"unzip -l %s ",fn);
	} else if ( type == ARC_TAR ) {
		sprintf(com,"tar tvf %s ",fn);
	} else if ( type == ARC_TAZ || type == ARC_TARZ ) {
		sprintf(com,"tar tvfZ %s ",fn);
	} else if ( type == ARC_TGZ || type == ARC_TARGZ ) {
		sprintf(com,"tar tvfz %s ",fn);
	} else	sprintf(com,"tar tvf %s ",tfn);
	strcat(com," | ");
	if ( pager != NULL ) {
		strcat(com,pager);
	} else {
#if !H2050
		strcat(com,"less");
#endif
#if H2050
		strcat(com,"pg");
#endif
	}
	system2(com);

	/* Remove Temporary File */
	if ( type == ARC_TAz || type == ARC_TARz ) {
		unlink(tfn);
	}

	t_puts("<< Enter Any Key >>");
	getchr2();

end_arc_list:
#if XWINDOW
	t_puts("\015\012");
	exit();
#else
	dsp_fl();
	dsp_com_mes();
#endif

	return;
}

int
arc_pack()
{
	char arc_file[80],temp[80];
	int flg,flg2,type;
	extern int need_redraw;

	flg = is_select();

	clr_mes_area();
	if ( flg ) sprintf(temp,"Files Archive to");
	else {
		sprintf(temp,"(%s) Archive to",fent[curp].d_name);
		dsp_fl2(curp,REV_DISP);
	}
	if ( strlen(temp) + 18 >= X_WIDTH ) sprintf(temp,"Arc");
	xt_loc(0,DSP_ROW+2);
	arc_file[0] = '\0';
	if ( xget_str(arc_file,80,temp," : ") ) {
		if ( need_redraw ) dsp_fl();
		dsp_com_mes();
		return;
	}

	get_path(arc_file);

	type = check_arcfile(arc_file);
	if ( type < 0 ) {
		type = arc_mode;
		strcat(arc_file,arc_suf[type]);
	}

	flg = arc_pk2(arc_file,type,flg);

	if ( !flg ) {
		get_file_ent();
		if ( curp >= dpc ) curp = ( 0 > dpc-1 )?0:(dpc-1);
		if ( curp < dp || curp >= dp + DSP_CN )
			dp = ( curp / DSP_CN ) * DSP_CN;
	}
	dsp_fl();
	dsp_com_mes();

	return;
}

int
arc_pk2(fn,type,flg)
char *fn;
int type,flg;
{
	char tfn[255],com[255];
	int c,ret,ln;
	struct stat sbuf;

#if !(XWINDOW)
	clr_mes_area();
	xt_loc(0,DSP_ROW+3);
#endif

	/* Copy Archive file to the Temporary Directory */
	if ( type == ARC_TAz || type == ARC_TARz ) {
		if ( mk_temp_file(tfn,type) ) return TRUE;
		if ( stat(fn,&sbuf) == 0 ) {
			sprintf(com,"cp %s %s",fn,tfn);
			system(com);
			sprintf(com,"unpack %s",tfn);
			system2(com);
		}
		ln = strlen(tfn);
		tfn[ln-2] = '\0';
	} else {
		for ( c = 0 ; fn[c] != '\0' && fn[c] != '/' ; c++ );
		tfn[0] = '\0';
		if ( fn[c] == '\0' ) {
			strcpy(tfn,cwd);
			if ( strcmp(tfn,"/") != 0 ) {
				strcat(tfn,"/");
			}
		}
		strcat(tfn,fn);
	}

	ret = arc_pk3(tfn,type,flg);

	/* Copy Archive File and Remove Temporary File */
	if ( type == ARC_TAz || type == ARC_TARz ) {
		if ( !ret ) {
			sprintf(com,"pack %s",tfn);
			strcat(tfn,".z");
			system2(com);

			sprintf(com,"cp %s %s",tfn,fn);
			system(com);
		}
		unlink(tfn);
	}

	return ret;
}

int
arc_pk3(fn,type,flg)
char *fn;
int type,flg;
{
	char *tarflg;
	char temp[255];
	struct stat sbuf;

	if ( type == ARC_LZH ) {
		sprintf(temp,"%s a %s %%*",lzharc,fn);
	} else if ( type == ARC_ZIP ) {
		sprintf(temp,"zip %s %%*",fn);
	} else {
		if ( type == ARC_TAZ || type == ARC_TARZ ) {
			tarflg = "vfZ";
		} else if ( type == ARC_TGZ || type == ARC_TARGZ ) {
			tarflg = "vfz";
		} else 	tarflg = "vf";
		if ( stat(fn,&sbuf) == 0 ) {
#if !MINIX
			sprintf(temp,"tar r%s %s %%*",tarflg,fn);
#else
			sprintf(temp,"tar c%s %s %%*",tarflg,fn);
#endif
		} else {
			sprintf(temp,"tar c%s %s %%*",tarflg,fn);
		}
	}
	exe_command(temp,FALSE);

	return FALSE;
}

int
arc_unpack()
{
	char arc_path[80],temp[80];
	int flg,flg2,c,type,sel;
	extern int need_redraw;

	flg = is_select();
	if ( !flg && !is_file_norm(curp) ) return;

	clr_mes_area();
	if ( flg ) sprintf(temp,"Files Unarchive to");
	else {
		sprintf(temp,"(%s) Unarchive to",fent[curp].d_name);
		dsp_fl2(curp,REV_DISP);
	}
	if ( strlen(temp) + 18 >= X_WIDTH ) sprintf(temp,"UArc");
	xt_loc(0,DSP_ROW+2);
	arc_path[0] = '\0';
	if ( xget_str(arc_path,40,temp," : ") ) {
		if ( need_redraw ) dsp_fl();
		dsp_com_mes();
		return;
	}

	get_path(arc_path);

	flg2 = FALSE;
	if ( flg ) {
		for ( sel = 1 ; sel <= maxsel ; sel++ ) {
			for ( c = 0 ; c < dpc ; c++ ) {
			    if ( fent[c].sel == sel ) {
				if ( (type = check_arcfile(fent[c].d_name)) >= 0 ) {
					flg2 = TRUE;
					arc_up2(fent[c].d_name,type,arc_path);
				} else {
					clr_mes_area();
					xt_loc(0,DSP_ROW+2);
					sprintf(temp,"File %s is not archive file !! Hit any key ..."
						,fent[c].d_name);
					xt_puts(temp);
					xgetchr2();
				}
			    }
			}
		}
	} else {
		if ( (type = check_arcfile(fent[curp].d_name)) >= 0 ) {
			flg2 = TRUE;
			arc_up2(fent[curp].d_name,type,arc_path);
		} else {
			clr_mes_area();
			xt_loc(0,DSP_ROW+2);
			sprintf(temp,"File %s is not archive file !! Hit any key ..."
				,fent[curp].d_name);
			xt_puts(temp);
			xgetchr2();
		}
	}

	if ( flg2 ) {
		get_file_ent();
		if ( curp >= dpc ) curp = ( 0 > dpc-1 )?0:(dpc-1);
		if ( curp < dp || curp >= dp + DSP_CN )
			dp = ( curp / DSP_CN ) * DSP_CN;
	}
	dsp_fl();
	dsp_com_mes();

	return;
}

int
arc_up2(arc_fn,type,path)
char *arc_fn;
int type;
char *path;
{
	int ln;
	char tfn[255];
	char com[255];

#if !(XWINDOW)
	clr_mes_area();
	t_loc(0,DSP_ROW+3);
#endif

	/* Copy Archive file to the Temporary Directory */
	if ( type == ARC_TAz || type == ARC_TARz ) {
		if ( mk_temp_file(tfn,type) ) return;
		sprintf(com,"cp %s %s",arc_fn,tfn);
		system(com);
		sprintf(com,"unpack %s",tfn);
		system2(com);
		ln = strlen(tfn);
		tfn[ln-2] = '\0';
	} else {
		strcpy(tfn,cwd);
		if ( strcmp(tfn,"/") != 0 ) {
			strcat(tfn,"/");
		}
		strcat(tfn,arc_fn);
	}

	/* Output Archive file */
	if ( type == ARC_LZH ) {
		sprintf(com,"%s x %s",lzharc,tfn);
	} else if ( type == ARC_ZIP ) {
		sprintf(com,"unzip %s",tfn);
	} else if ( type == ARC_TAR ) {
		sprintf(com,"tar xovf %s",tfn);
	} else if ( type == ARC_TAZ || type == ARC_TARZ ) {
		sprintf(com,"tar xovfZ %s",tfn);
	} else if ( type == ARC_TGZ || type == ARC_TARGZ ) {
		sprintf(com,"tar xovfz %s ",tfn);
	} else	sprintf(com,"tar xovf %s",tfn);

	if ( path[0] == '\0' || chdir(path) == 0 ) {
		system2(com);
		if ( path[0] != '\0' ) chdir(cwd);
	}

	/* Remove Temporary File */
	if ( type == ARC_TAz || type == ARC_TARz ) {
		unlink(tfn);
	}

	return;
}

int
check_arcfile(fn)
char *fn;
{
	int ln,ln2;
	int c,type;

	ln = strlen(fn);
	type = -1;
	for ( c = 0 ; arc_suf[c] != NULL ; c++ ) {
		ln2 = strlen(arc_suf[c]);
		if ( ln > ln2 ) {
			if ( strcmp(&fn[ln - ln2],arc_suf[c]) == 0 ) {
				type = c;
				break;
			}
		}
	}

	return type;
}

int
mk_temp_file(fn,type)
char *fn;
int type;
{
	struct stat sbuf;
	char tfn[20],suf[20];

	mk_suffix(suf,type);

	while ( TRUE ) {
		strcpy(fn,TEMP_DIR);
		sprintf(tfn,"fu%d",rand());
		strcat(fn,tfn);
		strcat(fn,suf);
		if ( stat(fn,&sbuf) != 0 ) {
			if ( errno == ENOENT ) return 0;
			return -1;
		}
	}
}

mk_suffix(suf,type)
char *suf;
int type;
{
	if ( type == ARC_TAz ) {
		type = ARC_TARz;
	} else if ( type == ARC_TAZ ) {
		type = ARC_TARZ;
	}
	strcpy(suf,arc_suf[type]);
}
