/*
	File Utility ( Get String )

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
#else
#  include <dirent.h>
#endif
#include <signal.h> 
#if MINIX
#  undef NULL
#  include <stdlib.h>
#else
#  if !(NEWS3400 | I386BSD)
#    include <malloc.h>
#    include <termio.h> 
#  endif
#  if I386BSD
#    include <sys/malloc.h>
#  endif
#endif
#include <pwd.h>
#include <time.h>
#include "key.h"
#include "fu.h"

static int cp,hc;
static int x0,y0,bfmax;
static char *bf;

char *get_pathname();

static int many_candidate = FALSE;
static char *prompt1, *prompt2;
int need_redraw = FALSE;

int
get_str(buf,bufmax,p1,p2)
char *buf;
int bufmax;
char *p1, *p2;
{
	return getstr2(buf,bufmax,FALSE,p1,p2);
}

#if XWINDOW
extern int xcurdisp;

int
xget_str(buf,bufmax,p1,p2)
char *buf;
int bufmax;
char *p1, *p2;
{
	int r;

	xcurdisp = TRUE;
	r = getstr2(buf,bufmax,TRUE,p1,p2);
	xcurdisp = FALSE;

	return r;
}
#endif

int
getstr2(buf,bufmax,x,p1,p2)
char *buf;
int bufmax,x;
char *p1, *p2;
{
	int c,ky;

	need_redraw = FALSE;

	prompt1 = p1;
	prompt2 = p2;

	gstr_prompt(x);

	flush_keybuf();
	bf = buf;
	bfmax = bufmax;
	cp = strlen(buf);
	t_clrcur();
	if ( x ) xt_puts(buf);
	else t_puts(buf);
	t_dspcur();
	hc = hcn;
	while ( 1 ) {
		ky = func_in(TRUE,x);

		if ( (ky & ~(FUNC_MASK)) != FUNC_FNEXPAND ) {
			many_candidate = FALSE;
		}

 		if ( ky & FUNC_MASK ) {
			ky = ky & ~(FUNC_MASK);
			if ( ky == FUNC_RET ) break;
			else if ( ky == FUNC_BS ) {
				gstr_bs(x);
			} else if ( ky == FUNC_DEL ) {
				gstr_del(x);
			} else if ( ky == FUNC_LEFT ) {
				gstr_left(x);
			} else if ( ky == FUNC_RIGHT ) {
				gstr_right(x);
			} else if ( ky == FUNC_UP ) {
				gstr_up(x);
			} else if ( ky == FUNC_DOWN ) {
				gstr_down(x);
			} else if ( ky == FUNC_FNEXPAND ) {
				gstr_fn_expand(x);
			}
		} else if ( ky == KEY_ESC2 ) {
			t_clrcur();
			return TRUE;
		} else if ( ky >= 0x20 && ky < 0x100 ) {
			gstr_key(ky,x);
		}
	}
	t_clrcur();
	if ( *bf != '\0' ) {
		if ( hcn >= HIST_CN ) {
			free(hist[0]);
			for ( c = 0 ; c < hcn-1 ; c++ ) hist[c] = hist[c+1];
			--hcn;
		}
		if ( (hist[hcn] = (char *)malloc(sizeof(char)*(strlen(bf)+1)))
			!= NULL ) {
			strcpy(hist[hcn],bf);
			++hcn;
		}
	}

	return FALSE;
}

gstr_prompt(x)
int x;
{
	if ( x ) {
		xt_reverse();
		xt_puts(prompt1);
		xt_normal();
		xt_puts(prompt2);
	} else {
		t_reverse();
		t_puts(prompt1);
		t_normal();
		t_puts(prompt2);
	}
}

gstr_key(ky,x)
int ky,x;
{
	int c,ln,ky2,cn;

	cn = 1;
	if ( is_kan1(ky) ) {
		ky2 = func_in(TRUE,x);
		++cn;
	}
	if ( (ln = strlen(bf)) < bfmax-cn ) {
		for ( c = ln ; c >= cp ; c-- ) bf[c+cn] = bf[c];
		bf[cp] = ky;
		if ( cn > 1 ) bf[cp+1] = ky2;
		gstr_flush(x);
		cp += cn;
		if ( cn > 1 && is_kana(ky) ) cn = 1;
		if ( x ) xt_cur_forward(cn);
		else t_cur_forward(cn);
	}
}

gstr_bs(x)
int x;
{
	int c,cn,cn2;

	if ( cp > 0 ) {
		cn = 1;
		if ( cp > 1 && is_kan_str(bf,cp-2) ) cn = 2;
		if ( cn > 1 && !is_kana(bf[cp-2]) ) cn2 = 2;	/* for euc kana */
		else cn2 = 1;
		for ( c = cp ; bf[c] != '\0' ; c++ ) bf[c-cn] = bf[c];
		bf[c-cn] = '\0';
		cp -= cn;
		if ( x ) xt_cur_backward(cn2);
		else t_cur_backward(cn2);
		gstr_flush(x);
	}
}

gstr_del(x)
int x;
{
	int c,ln,cn;

	ln = strlen(bf);
	if ( cp < ln ) {
		cn = 1;
		if ( cp < ln - 1 && is_kan_str(bf,cp) ) cn = 2;
		for ( c = cp ; c < ln-cn+1 ; c++ ) bf[c] = bf[c+cn];
		gstr_flush(x);
	}
}

gstr_left(x)
int x;
{
	int cn;

	if ( cp > 0 ) {
		cn = 1;
		if ( cp > 1 && is_kan_str(bf,cp-2) ) cn = 2;
		cp -= cn;
		if ( cn > 1 && is_kana(bf[cp]) ) cn = 1;	/* for euc kana */
		if ( x ) xt_cur_backward(cn);
		else t_cur_backward(cn);
	}
}

gstr_right(x)
int x;
{
	int cn;

	if ( cp < strlen(bf) ) {
		cn = 1;
		if ( is_kan1(bf[cp]) ) cn = 2;
		cp += cn;
		if ( cn > 1 && is_kana(bf[cp-cn]) ) cn = 1;	/* for euc kana */
		if ( x ) xt_cur_forward(cn);
		else t_cur_forward(cn);
	}
}

gstr_up(x)
int x;
{
	int c,l;

	if ( hc > 0 ) {
		if ( os_kj_code != 0 ) {	/* if euc code */
			l = cp;
			for ( c = 0 ; c < l ; c++ )
				if ( (bf[c] & 0xff) == 0x8e ) --cp;
		}
		if ( x ) xt_cur_backward(cp);
		else t_cur_backward(cp);
		--hc;
		strncpy(bf,hist[hc],bfmax-1);
		bf[bfmax - 1] = '\0';
		if ( x ) {
			xt_puts(bf);
			xt_erase_line();
		} else {
			t_puts(bf);
			t_erase_line();
		}
		cp = strlen(bf);
	}
}

gstr_down(x)
int x;
{
	int c,l;

	if ( hc < hcn ) {
		if ( os_kj_code != 0 ) {	/* if euc code */
			l = cp;
			for ( c = 0 ; c < l ; c++ )
				if ( (bf[c] & 0xff) == 0x8e ) --cp;
		}
		if ( x ) xt_cur_backward(cp);
		else t_cur_backward(cp);
		++hc;
		if ( hc < hcn ) {
			strncpy(bf,hist[hc],bfmax-1);
			bf[bfmax - 1] = '\0';
		} else {
			bf[0] = '\0';
		}
		if ( x ) {
			xt_puts(bf);
			xt_erase_line();
		} else {
			t_puts(bf);
			t_erase_line();
		}
		cp = strlen(bf);
	}
}

gstr_flush(x)
int x;
{
	int c,l;
	int ln,cn;

	cn = 0;
	if ( cp > 0 && is_kan_str(bf,cp-1) ) cn = 1;
	ln = strlen(bf+cp) + cn;
	t_clrcur();
	if ( cn > 0 ) {
		if ( x ) xt_cur_backward(cn);
		else t_cur_backward(cn);
	}
	l = ln;
	if ( os_kj_code != 0 ) {	/* if euc code */
		for ( c = 0 ; c < ln ; c++ )
			if ( (bf[cp-cn+c] & 0xff) == 0x8e ) --l;
	}
	if ( x ) {
		xt_puts(bf+cp-cn);
		xt_erase_line();
		xt_cur_backward(l-cn);
	} else {
		t_puts(bf+cp-cn);
		t_erase_line();
		t_cur_backward(l-cn);
	}
	t_dspcur();

	return;
}

char **candidate_list;
int ncandidate, ncand_list;

int
new_candidate()
{
	candidate_list = NULL;
	ncandidate = ncand_list = 0;

	return 0;
}

int
add_candidate(char *name)
{
	int c;
	char *ptr;
	char **list;

	// are there any empty entry?
	if ( ncand_list < ncandidate + 1 ) {
		// allocate candidate list
		list = (char **)malloc((ncandidate + 256) * sizeof(char *));
		if ( list == NULL ) {
			return -1;
		}

		// copy old listed pointers to new list
		for ( c = 0 ; c < ncand_list ; c++ ) {
			list[c] = candidate_list[c];
		}

		// free old list
		if ( ncand_list > 0 ) free(candidate_list);
		candidate_list = list;
		ncand_list = ncandidate + 256;
	}

	// allocate entry for new name
	ptr = malloc(strlen(name) + 1);
	if ( ptr == NULL ) return -1;

	// copy name to new entry
	strcpy(ptr, name);
	candidate_list[ncandidate] = ptr;
	++ncandidate;

	return 0;
}

int
free_candidate()
{
	int c;
	for ( c = 0 ; c < ncandidate ; c++ ) {
		free(candidate_list[c]);
	}
	if ( ncand_list > 0 ) free(candidate_list);

	return 0;
}

int
print_candidate(xwin)
int xwin;
{
	int c, c2, w, x;
	int maxlen;

	t_clrcur();

	// determine maximum name length
	maxlen = 0;
	for ( c = 0 ; c < ncandidate ; c++ ) {
		if ( strlen(candidate_list[c]) > maxlen ) {
			maxlen = strlen(candidate_list[c]);
		}
	}

	// calc. number of files in one line
	w = X_WIDTH / (maxlen+1);

	// show candidate names
	x = -1;
	for ( c = 0 ; c < ncandidate ; c++ ) {
		if ( (c % w) == 0 ) {
			x = -1;
			t_puts("\015\n");
		}

		// print blank spaces to align names
		for ( c2 = x ; c2 >= 0 && c2 < maxlen+1 ; c2++ ) {
			t_puts(" ");
		}
		t_puts(candidate_list[c]);
		x = strlen(candidate_list[c]);
	}
	t_puts("\015\n");

	gstr_prompt(xwin);

	if ( xwin ) xt_puts(bf);
	else t_puts(bf);
	xt_erase_line();
	xt_cur_backward(strlen(bf) - cp);

	t_dspcur();

	need_redraw = TRUE;

	return 0;
}

gstr_fn_expand(x)
int x;
{
	DIR *dirp;
	struct dirent *dir;
	int c,st,en,ln,all_ln,only_one;
	char fn[1024],path[1024],*end_path;
	char candidate[1024];
	struct stat st_buf;
	struct passwd *pw,*getpwent();
	void endpwent();

	/* extract incompleted pathname which user specified */
	st = 0;
	for ( c = 0 ; bf[c] != '\0' && c < cp ; c++ ) {
		if ( bf[c] == ' ' || bf[c] == '|' || bf[c] == '>'
			|| bf[c] == '<' || bf[c] == '"' || bf[c] == '\'' || bf[c] == '@' ) {
			st = c + 1;
		}
		if ( is_kan1(bf[c]) ) ++c;
	}
	en = st;
	for ( c = 0 ; bf[en] != '\0' && en < cp ; en++, c++ ) {
		fn[c] = bf[en];
		if ( is_kan1(bf[en]) ) {
			++c;
			++en;
			fn[c] = bf[en];
		}
	}
	fn[c] = '\0';

	/* no token then do nothing */
//	if ( *fn == '\0' ) return;

	/* extract directory path part */
	end_path = get_pathname(fn,path);
	ln = strlen(end_path);

	/* check if home directory specified */
	if ( strcmp(path,".") == 0 && *fn == '~' ) {
		*candidate = '\0';
		only_one = TRUE;
		endpwent();
		new_candidate();
		while ( (pw = getpwent()) != NULL ) {
			if ( ln == 0 || strncmp(end_path+1,pw->pw_name,ln-1) == 0 ) {
				add_candidate(pw->pw_name);
				if ( *candidate != '\0' || !only_one ) {
					/* check how many characters has been matched to the current candidate */
					for ( c = 0 ; pw->pw_name[c] != '\0'
						 && pw->pw_name[c] == candidate[c] ; c++ );

					if ( c < ln-1 ) {
						*candidate = '\0';
						break;
					}
					candidate[c] = '\0';
					only_one = FALSE;
				} else {
					strcpy(candidate,pw->pw_name);
				}
			}
		}
		endpwent();

		/* many candidate ? */
		if ( only_one == FALSE && strlen(candidate) == ln ) {
			if ( many_candidate ) {
				// print out candidate
				print_candidate();
			}
			many_candidate = TRUE;
		}

		free_candidate();

		/* are there candidate ? */
		if ( *candidate == '\0' ) return;

		/* insert filename */
		all_ln = strlen(candidate);
		for ( c = ln-1 ; c < all_ln ; c++ ) {
			gstr_key(candidate[c],x);
		}
		if ( only_one ) {
			gstr_key('/',x);
		}
		return;
	}

	/* expand environment variables and '~' descriptions */
	get_path(path);
	if ( strcmp(path,"/") != 0 ) strcat(path,"/");

	if ( (dirp = opendir(path)) == NULL ) {
		return;
	}
	*candidate = '\0';
	only_one = TRUE;
	new_candidate();
	while ( (dir = readdir(dirp)) != NULL ) {
		if ( ln == 0 || strncmp(end_path,dir->d_name,ln) == 0 ) {
			add_candidate(dir->d_name);
			if ( *candidate != '\0' || !only_one ) {
				/* check how many characters has been matched to the current candidate */
				for ( c = 0 ; dir->d_name[c] != '\0'
					 && dir->d_name[c] == candidate[c] ; c++ );

				if ( c < ln ) {
					*candidate = '\0';
					break;
				}
				candidate[c] = '\0';
				only_one = FALSE;
			} else {
				strcpy(candidate,dir->d_name);
			}
		}
	}
	closedir(dirp);

	/* many candidate ? */
	if ( only_one == FALSE && strlen(candidate) == ln ) {
		if ( many_candidate ) {
			// print out candidate
			print_candidate();
		}
		many_candidate = TRUE;
	}

	free_candidate();

	/* are there candidate ? */
	if ( *candidate == '\0' ) return;

	/* insert filename */
	all_ln = strlen(candidate);
	for ( c = ln ; c < all_ln ; c++ ) {
		gstr_key(candidate[c],x);
	}
	if ( only_one ) {
		/* check if this file is the directory */
		/* if Yes then append '/' otherwise append ' ' to the end of string */
		strcat(path,candidate);
		if ( stat(path,&st_buf) == 0 ) {
			if ( (st_buf.st_mode & FILE_TYPE) == FILE_DIR ) {
				gstr_key('/',x);
			} else {
				gstr_key(' ',x);
			}
		}
	}

	return;
}

char *
get_pathname(fn,path)
char *fn;
char *path;
{
	int c;
	char *p,*end_path;

	p = end_path = NULL;
	for ( c = 0 ; fn[c] != '\0' ; c++ ) {
		path[c] = fn[c];
		if ( fn[c] == '/' ) {
			p = path + c;
			end_path = fn + c + 1;
		}
		if ( is_kan1(fn[c]) ) {
			path[c] = fn[c];
			++c;
		}
	}
	if ( p != NULL ) {
		*p = '\0';
		if ( *path == '\0' ) {
			strcpy(path,"/");
		}
	} else {
		strcpy(path,".");
		end_path = fn;
	}

	return end_path;
}

is_kan1(dt)
int dt;
{
	dt &= 0xff;
	if ( os_kj_code == 0 ) {	/* use shift jis */
		if ( dt >= 0x81 && dt <= 0x9f ) return TRUE;
		if ( dt >= 0xe0 && dt <= 0xea ) return TRUE;
		return FALSE;
	} else {			/* use euc code */
		if ( dt & 0x80 ) return TRUE;
		else return FALSE;
	}
}

is_kan2(dt)
int dt;
{
	dt &= 0xff;
	if ( os_kj_code == 0 ) {	/* use shift-jis */
		if ( dt >= 0x3e && dt <= 0xfd ) return TRUE;
		return FALSE;
	} else {			/* use euc code */
		if ( dt & 0x80 ) return TRUE;
		else return FALSE;
	}
}

is_kana(dt)
int dt;
{
	dt &= 0xff;
	if ( os_kj_code == 0 ) {
		if ( dt >= 0xa1 && dt <= 0xdf ) return TRUE;
	} else {
		if ( dt == 0x8e ) return TRUE;
	}
	return FALSE;
}

is_norm(dt)
int dt;
{
	dt &= 0xff;
	if ( os_kj_code == 0 ) {	/* use shift-jis */
		if ( dt == '\0' ) return FALSE;
		if ( dt >= 0x81 && dt <= 0x9f ) return FALSE;
		if ( dt >= 0xe0 && dt <= 0xea ) return FALSE;
		if ( dt >= 0xa1 && dt <= 0xdf ) return FALSE;
		return TRUE;
	} else {			/* use euc code */
		if ( dt == '\0' ) return FALSE;
		if ( dt & 0x80 ) return FALSE;
		else return TRUE;
	}
}

is_kan_str(str,p)
char *str;
int p;
{
	int k,c;

	k = FALSE;
	for ( c = 0 ; c <= p ; c++ ) {
		if ( !k && is_kan1(str[c]) ) k = TRUE;
		else k = FALSE;
	}

	return k;
}
