/*
	File Utility ( Commands )

	Author	T.Tashiro (Nifty PDC02432)	1990-04-16	Ver 1.0
	Fixed	T.Tashiro (Nifty PDC02432)	1991-02-18	Ver 1.0a
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
#if I386BSD
#  include <unistd.h>
#endif
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>
#if NEWS3400
#  include <ctype.h>
#endif
#include "key.h"
#include "fu.h"

f_exec()
{
	char temp[1024];

	if ( !is_file_norm(curp) ) return;
	strcpy(temp,"./");
	strcat(temp,fent[curp].d_name);
	strcat(temp," ");
	f_shell(temp,1);

	return;
}

f_shell(temp,fnc_flg)
char *temp;
int fnc_flg;
{
	int st,f;
	int sc_flg;
	extern int need_redraw;
#if XWINDOW
	int pid,p_pid,c;
	char buf[1024];
	FILE *fp;
#endif

	sc_flg = FALSE;
	if ( fnc_flg & FUNC_SCREEN_FLAG ) sc_flg = TRUE;

	dsp_fl2(curp,REV_DISP);

#if XWINDOW
	XMapRaised(xdisplay,xrootwindow);
	XWarpPointer(xdisplay,None,xrootwindow,0,0,0,0,10,10);
	XSetInputFocus(xdisplay,xrootwindow,RevertToParent,0);
	XFlush(xdisplay);

	dsp_shell();

	p_pid = getpid();
	pipe(shell_pipe);
	if ( (pid = fork_fu()) > 0 ) {
		close(shell_pipe[1]);
		return;
	} else if ( pid == -1 ) return;
	close(shell_pipe[0]);
#else
	clr_mes_area();
	t_loc(0,DSP_ROW+2);
#endif
	f = FALSE;
	while ( TRUE ) {
		if ( sc_flg ) {
			if ( get_str(temp,1000,"Shell"," > ") != 0 || *temp == '\0' )
				break;
			t_puts("\015\012");
		}
		exe_command(temp,sc_flg);
		f = TRUE;
		if ( !sc_flg ) break;
		*temp = '\0';
	}
#if XWINDOW
	t_puts("\015\012");
	kill(p_pid,SIGUSR1);
	if ( (fp = fdopen(shell_pipe[1],"w")) == NULL ) {
		exit();
	}
	if ( f && !(fnc_flg & ALL_FILE_STAY) ) {
		getcwd(buf,1024);
		fprintf(fp,"%s\n",buf);
	} else fprintf(fp,"\n");

	for ( c = 0 ; c < hcn ; c++ ) fprintf(fp,"%s\n",hist[c]);
	fclose(fp);
	exit();
#endif
	if ( f ) {
		if ( !(fnc_flg & ALL_FILE_STAY) ) {
			get_file_ent();
			if ( curp >= dpc ) curp = ( 0 > dpc-1 )?0:(dpc-1);
			if ( curp < dp || curp >= dp + DSP_CN )
				dp = ( curp / DSP_CN ) * DSP_CN;
		}
		dsp_fl();
	} else if ( need_redraw ) {
		dsp_fl();
	}
#if !XWINDOW
	dsp_com_mes();
#endif
}

int
is_select()
{
	if ( maxsel > 0 ) return TRUE;
	return FALSE;
}

int
is_file_norm(c)
int c;
{
	int ft;

	ft = fent[c].st_mode & FILE_TYPE;
	if ( ft != FILE_NORM1 && ft != FILE_NORM2 ) return FALSE;

	return TRUE;
}

int
is_directory(c)
int c;
{
	int ft;

	ft = fent[c].st_mode & FILE_TYPE;
	if ( ft != FILE_DIR ) return FALSE;

	return TRUE;
}

mk_fname(dfn,fn,path)
char *dfn,*fn,*path;
{
	strcpy(dfn,path);
	if ( strcmp(dfn,"/") != 0 ) {
		strcat(dfn,"/");
	}
	strcat(dfn,fn);
}

get_yn(def)
int def;
{
	int ky;

	t_dspcur();
	ky = xgetchr2();
	if ( ky == '\015' ) ky = def;
	t_clrcur();
	if ( ky != 'Y' && ky != 'y' ) return FALSE;

	return TRUE;
}

int
get_how(str)
char *str;
{
	int c,ky;

	t_dspcur();
	ky = xgetchr2();
	if ( ky == '\015' ) ky = *str;
	t_clrcur();
	for ( c = 0 ; str[c] != '\0' ; c++ ) {
		if ( str[c] == ky ) return str[c];
	}

	return str[0];
}

#define REPEAT_MAC	1
#define ALL_MAC		2
#define ONE_MAC		3
#define LIST_MAC	4
#define MAC_ERR		-1

static char combuf[1024];

exe_command(temp,sc_flg)
char *temp;
int sc_flg;
{
	int c,cp,flg,flg2;
	int dp_sv;
	int quote;	/* quotation flag : 1 then \ quote , 2 then single quotation */
	char cnv[10];	/* conversion mode for LIST_MAC */

	*cnv = '\0';
	quote = 0;
	flg = is_select();
	for ( c = 0 , flg2 = 0 ; temp[c] != '\0' ; c++ ) {
		if ( temp[c] == '\'' ) {
			if ( quote & 2 ) quote &= (~2);
			else quote |= 2;
		} else if ( temp[c] == '\\' ) {
			quote |= 1;
		} else if ( temp[c] == '%' && !quote ) {
			if ( temp[c+1] == 'f' ) {
				if ( flg2 != 0 && flg2 != REPEAT_MAC ) {
					flg2 = MAC_ERR;
					break;
				}
				flg2 = REPEAT_MAC;
			} else if ( temp[c+1] == '*' ) {
				if ( flg2 != 0 ) {
					flg2 = MAC_ERR;
					break;
				}
				flg2 = ALL_MAC;
			} else if ( temp[c+1] == '1' ) {
				if ( flg2 != 0 && flg2 != ONE_MAC ) {
					flg2 = MAC_ERR;
					break;
				}
				flg2 = ONE_MAC;
			} else if ( temp[c+1] == 'l' ) {
				if ( flg2 != 0 && flg2 != LIST_MAC ) {
					flg2 = MAC_ERR;
					break;
				}
				cnv[0] = '%';
				cnv[1] = 'L';
				cnv[2] = temp[c+2];
				cnv[3] = temp[c+3];
				cnv[4] = '\0';
				flg2 = LIST_MAC;
			}
		} else quote &= (~1);
	}
	switch ( flg2 ) {
		case 0 :
			exe_no_macro(combuf,temp,flg);
			break;
		case REPEAT_MAC :
			exe_repeat_macro(combuf,temp,flg,sc_flg);
			break;
		case ALL_MAC :
			exe_all_macro(combuf,temp,flg);
			break;
		case ONE_MAC :
			exe_one_macro(combuf,temp,flg);
			break;
		case LIST_MAC :
			exe_list_macro(combuf,temp,cnv,flg);
			break;
		default :
			fprintf(stderr,"%s:macro translation error !\015\n",prog_name);
			break;
	}

	return;
}

char *
add_mfname(buf,temp,fname,flg)
char *buf;	/* add buffer */
char **temp;	/* template */
char *fname;	/* filename */
{
	char *p,cn,c;

	p = *temp;
	if ( p[1] != 'f' && p[1] != '*' && p[1] != '1'
		&& p[1] != 'l' && p[1] != 'L' ) { /* if error */
		*(buf++) = p[0];
		*(buf++) = p[1];
		*buf = '\0';
		*temp = (*temp) + 2;
		return buf;
	}
	if ( p[1] != 'l' ) {	/* if list macro then no conversion */
		if ( p[2] == '@' && p[3] == 's' ) {		/* suffix */
			for ( cn = strlen(fname) - 1 ; cn >= 0 && fname[cn] != '.' ; cn-- );
			for ( c = cn ; c > 0 && fname[c] != '\0' ; c++ ) *(buf++) = fname[c];
			*buf = '\0';
			*temp = (*temp) + 4;
			return buf;
		} else if ( p[2] == '@' && p[3] == 'p' ) {	/* prefix */
			for ( cn = strlen(fname) - 1 ; cn >= 0 && fname[cn] != '.' ; cn-- );
			if ( cn <= 0 ) cn = strlen(fname);
			for ( c = 0 ; c < cn ; c++ ) *(buf++) = fname[c];
			*buf = '\0';
			*temp = (*temp) + 4;
			return buf;
		} else if ( p[2] == '@' && p[3] == 'd' ) {	/* dir */
			strcpy(buf,cwd);
			*temp = (*temp) + 4;
			return (buf + strlen(cwd));
		} else if ( p[2] == '@' && p[3] == 'a' ) {	/* dir + filename */
			strcpy(buf,cwd);
			if ( strcmp(cwd,"/") != 0 ) strcat(buf,"/");
			strcat(buf,fname);
			*temp = (*temp) + 4;
			return (buf + strlen(buf));
		}
	}

	strcpy(buf,fname);
	*temp = (*temp) + 2;
	if ( p[1] == 'l' ) {
		if ( p[2] == '@'
			&& ( p[3] == 's' || p[3] == 'p' || p[3] == 'd' || p[3] == 'a' ) )
			*temp = (*temp) + 2;
	}
	return (buf + strlen(fname));
}

make_exe_str(buf,temp,d_name)
char *buf,*temp;
char *d_name;
{
	char buf2[1024],*p,*tmp;
	int quote;	/* quotation flag : 1 then \ quote , 2 then single quotation */

	p = buf2;
	tmp = temp;
	quote = 0;
	while ( *tmp != '\0' ) {
		if ( *tmp == '\'' ) {
			*(p++) = *(tmp++);
			if ( quote & 2 ) quote &= (~2);
			else quote |= 2;
		} else if ( *tmp == '\\' ) {
			*(p++) = *(tmp++);
			quote |= 1;
		} else if ( *tmp == '%' && *(tmp + 1) != '\0' && !quote ) {
			p = add_mfname(p,&tmp,d_name);
		} else {
			*(p++) = *(tmp++);
			quote &= (~1);
		}
	}
	*p = '\0';
	strcpy(buf,buf2);

	return;
}


exe_no_macro(buf,temp)
char *buf,*temp;
{
	system2(temp);
}

exe_repeat_macro(buf,temp,flg,sc_flg)
char *buf,*temp;
int flg;
int sc_flg;
{
	int c,dp_sv,sel;

	if ( flg ) {
		dp_sv = dp;
		for ( sel = 1 ; sel <= maxsel ; sel++ ) {
			for ( c = 0 ; c < dpc ; c++ ) {
				if ( fent[c].sel == sel ) {
					if ( !sc_flg ) dsp_fl3(c,TRUE);
					make_exe_str(buf,temp,fent[c].d_name);
					system2(buf);
					if ( !sc_flg ) dsp_fl3(c,FALSE);
				}
			}
		}
		dp = dp_sv;
	} else {
		make_exe_str(buf,temp,fent[curp].d_name);
		system2(buf);
	}
}

exe_all_macro(buf,temp,flg)
char *buf,*temp;
int flg;
{
	int c,sel,sz;
	char *buf2,*bp,*p;
	char *cnv,*tmp;
	int quote;	/* quotation flag : 1 then \ quote , 2 then single quotation */

	tmp = temp;
	sz = 1024;
	if ( (bp = buf2 = (char *)malloc(sz)) == NULL ) {
		fprintf(stderr,"%s:cannot allocate memory for execute command\n",prog_name);
		return;
	}
	quote = 0;
	while ( *tmp != '\0' ) {
		if ( *tmp == '\'' ) {
			*(bp++) = *(tmp++);
			if ( quote & 2 ) quote &= (~2);
			else quote |= 2;
		} else if ( *tmp == '\\' ) {
			*(bp++) = *(tmp++);
			quote |= 1;
		} else if ( *tmp == '%' && *(tmp+1) == '*' ) {
			break;
		} else {
			*(bp++) = *(tmp++);
			quote &= (~1);
		}
	}
	*bp = '\0';
	cnv = tmp;

	if ( flg ) {
		for ( sel = 1 ; sel <= maxsel ; sel++ ) {
			for ( c = 0 ; c < dpc ; c++ ) {
				if ( fent[c].sel == sel ) {
					tmp = cnv;
					bp = add_mfname(bp,&tmp,fent[c].d_name);
					*(bp++) = ' ';
					if ( bp - buf2 > sz - 200 ) {
	/* abnormal indent */
	sz += sz;
	if ( (p = (char *)realloc(buf2,sz)) == NULL ) {
		fprintf(stderr,"%s:cannot allocate memory for execute command\015\n",prog_name);
		free(buf2);
		return;
	}
	bp = p + (bp - buf2);
	buf2 = p;
	/* abnormal indent */
					}
				}
			}
		}
	} else {
		bp = add_mfname(bp,&tmp,fent[curp].d_name);
		*(bp++) = ' ';
	}
	strcpy(bp,tmp);
	system2(buf2);
	free(buf2);

	return;
}

exe_one_macro(buf,temp,flg)
char *buf,*temp;
int flg;
{
	int c,dp_sv;

	make_exe_str(buf,temp,fent[curp].d_name);
	system2(buf);
}

exe_list_macro(buf,temp,cnv,flg)
char *buf,*temp,*cnv;
int flg;
{
	int c,sel;
	FILE *fp;
	char fn[20],file[256];
	char *p,*p2;

	strcpy(fn,mktemp(FU_TEMP_FILE));
	make_exe_str(buf,temp,fn);

	if ( ( fp = fopen(fn,"w") ) == NULL ) return;
	if ( flg ) {
		for ( sel = 1 ; sel <= maxsel ; sel++ ) {
			for ( c = 0 ; c < dpc ; c++ ) {
				if ( fent[c].sel == sel ) {
					p = cnv;
					add_mfname(file,&p,fent[c].d_name);
					fputs(file,fp);
					fputs("\n",fp);
				}
			}
		}
	} else {
		p = cnv;
		add_mfname(file,&p,fent[curp].d_name);
		fputs(file,fp);
		fputs("\n",fp);
	}
	fclose(fp);

	system2(buf);

	unlink(fn);

	return;
}

system2(str)
char *str;
{
	if ( check_cmmand(str) ) return;
	t_dspcur();
	trmdef();
#if BEOS
	signal(SIGINT, SIG_IGN);
#endif
	system(str);
	printf("\n");
	trmset2();
	t_clrcur();

	return;
}

int
check_cmmand(cmd)
char *cmd;
{
	int ln;
	char *tmp,*p;
	char *env,*getenv();

	ln = strlen(cmd);
	ln = (ln < 1024)?1024:ln;
	if ( (tmp = (char *)malloc(ln + 1)) == NULL ) {
		fprintf(stderr,"%s:cannot allocate memoru for command execution\015\n"
				,prog_name);
		return TRUE;
	}
	strcpy(tmp,cmd);
	p = skip_sp(tmp);
	if ( strncmp(p,"cd",2) == 0
		&& (*(p+2) == '\0' || *(p+2) == ' ' || *(p+2) == '\t') ) {
		p += 2;
		p = skip_sp(p);
		if ( *p == '\0' ) {
			if ( (env = getenv("HOME")) == NULL ) {
				free(tmp);
				return TRUE;
			}
			strcpy(p,env);
		} else get_path(p);
		if ( h_chdir(p) ) {
			t_puts("change dir command was failed !!\015\n");
		}
		free(tmp);
		return TRUE;
	}
	free(tmp);
	return FALSE;
}

get_path(path)
char *path;
{
	int c;
	char *env,*p,*getenv();
	char tmp[1024],name[20];
	struct passwd *pwd,*getpwnam();

	tmp[0] = '\0';
	p = path;
	if ( *p == '~' ) {
		if ( *(path + 1) == '/' || *(path + 1) == '\0' ) {	/* your home dir */
			if ( (env = getenv("HOME")) == NULL ) return;
			strcat(tmp,env);
			++p;
		} else {	/* other users home dir */
			++p;
			for ( c = 0 ; c < 19 && *p != '\0' && *p != '/'; c++ )
				name[c] = *(p++);
			name[c] = '\0';
			if ( (pwd = getpwnam(name)) == NULL ) return;
			strcat(tmp,pwd->pw_dir);
		}
	}

	if ( *p == '/' ) {
		strcat(tmp,"/");
		++p;
	}
	p = strtok(p,"/");
	while ( p != NULL ) {
		if ( *p != '$' ) {
			strcat(tmp,p);
		} else {
			if ( (env = getenv(p+1)) != NULL ) {
				strcat(tmp,env);
			} else {
				strcat(tmp,p);
			}
		}
		p = strtok(NULL,"/");
		if ( p != NULL ) strcat(tmp,"/");
	}
	strcpy(path,tmp);

	return;
}

strnct2(str1,str2,cn)
char *str1,*str2;
int cn;
{
	int ln,c;

	ln = strlen(str1);
	for ( c = ln ; c < cn ; c++ ,str2++ ) {
		str1[c] = *str2;
		if ( *str2 == '\0' ) break;
	}
	str1[cn-1] = '\0';

	return;
}

char *
skip_sp(str)
char *str;
{
	while ( *str != '\0' && ( *str == ' ' || *str == '\t' ) ) ++str;
	return str;
}

int
h_chdir(target_dir)
char *target_dir;
{
	int c;
	char *buf;

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
	if ( dir_hist[dir_hcn] != NULL ) {
		for ( c = dir_hcn ; c < DIR_HIST_CN ; c++ ) {
			free(dir_hist[c]);
			dir_hist[c] = NULL;
		}
	}
	strcpy(buf,cwd);
	strcpy(buf + strlen(cwd) + 1,fent[curp].d_name);
	if ( chdir(target_dir) ) {
		free(buf);
		return -1;
	}
	dir_hist[dir_hcn] = buf;
	++dir_hcn;

	return 0;
}
