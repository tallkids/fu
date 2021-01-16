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
	int c,ln,cn;
	char tmp[10];

	cn = 0;
	tmp[cn++] = ky;
	c = kj_lenc(ky);
	while ( --c > 0 ) {
		// read continuous kanji code at once
		tmp[cn++] = func_in(TRUE,x);
	}
	if ( (ln = strlen(bf)) < bfmax-cn ) {
		// make rooms to store input data
		for ( c = ln ; c >= cp ; c-- ) bf[c+cn] = bf[c];

		// store input key data
		for ( c = 0 ; c < cn ; c++ ) bf[cp+c] = tmp[c];

		// redraw string input area
		gstr_flush(x);
		cp += cn;

		// get character width
		cn = kj_width(tmp);

		// cursor move forward
		if ( x ) xt_cur_forward(cn);
		else t_cur_forward(cn);
	}
}

gstr_ins(str,x,escape_blank)
char *str;
int x;
int escape_blank;
{
	int c,c2,ln,cn,ky,w;

	// calculate length of insert string
	if ( escape_blank ) {
		// insert back slash before blank
		cn = c = 0;
		while ( str[c] != '\0' ) {
			if ( str[c] == ' ' ) ++cn;
			ln = kj_lenc(str[c]);
			c += ln;
			cn += ln;
		}
	} else cn = strlen(str);

	if ( (ln = strlen(bf)) < bfmax-cn ) {
		// make rooms to store input data
		for ( c = ln ; c >= cp ; c-- ) bf[c+cn] = bf[c];

		// store input key data
		for ( c = 0, c2 = cp ; str[c] != '\0' ; ) {
			if ( escape_blank && str[c] == ' ' ) {
				bf[c2++] = '\\';
			}
			w = kj_lenc(str[c]);
			while ( w-- > 0 ) {
				bf[c2++] = str[c++];
			}
		}

		// redraw string input area
		gstr_flush(x);

		// get character width
		for ( c = cp, w = 0 ; c < cp + cn ; c += kj_lenc(bf[c]) )
			w += kj_width(bf + c);
		cp += cn;

		// cursor move forward
		if ( x ) xt_cur_forward(w);
		else t_cur_forward(w);
	}
}


gstr_bs(x)
int x;
{
	int c,cn,w;

	if ( cp > 0 ) {
		// check the break point of Kanji code
		cn = 1;
		while ( cp - cn > 0 && is_kan_str(bf, cp - cn) ) ++cn;

		// get width of the code
		w = kj_width(bf + cp - cn);

		if ( cp - cn > 0 && w <= 0 ) {	// this is combined character. let's delete one more character
			++cn;
			while ( cp - cn > 0 && is_kan_str(bf, cp - cn) ) ++cn;
			w = kj_width(bf + cp - cn);
		}

		// delete the character codes at once
		for ( c = cp ; bf[c] != '\0' ; c++ ) bf[c-cn] = bf[c];
		bf[c-cn] = '\0';

		// move current buffer position
		cp -= cn;

		// move cursor backward
		if ( x ) xt_cur_backward(w);
		else t_cur_backward(w);

		// redraw string input area
		gstr_flush(x);
	}
}

gstr_del(x)
int x;
{
	int c,ln,cn;

	ln = strlen(bf);
	if ( cp < ln ) {
		// get character code length
		cn = kj_lenc(bf[cp]);

		if ( cp + cn < ln ) {
			// check if next code is combined character code?
			if ( kj_width(bf + cp + cn) <= 0 ) {
				cn += kj_lenc(bf[cp + cn]);
			}
		}

		// delete 'cn' character codes
		for ( c = cp ; c < ln-cn+1 ; c++ ) bf[c] = bf[c+cn];

		// redraw string input area
		gstr_flush(x);
	}
}

gstr_left(x)
int x;
{
	int c,cn,w;

	if ( cp > 0 ) {
		// check the break point of Kanji code
		cn = 1;
		while ( cp - cn > 0 && is_kan_str(bf, cp - cn) ) ++cn;

		// get width of the code
		w = kj_width(bf + cp - cn);

		if ( cp - cn > 0 && w <= 0 ) {	// this is combined character. let's delete one more character
			++cn;
			while ( cp - cn > 0 && is_kan_str(bf, cp - cn) ) ++cn;
			w = kj_width(bf + cp - cn);
		}

		// move current buffer position
		cp -= cn;

		// move cursor backward
		if ( x ) xt_cur_backward(w);
		else t_cur_backward(w);
	}
}

gstr_right(x)
int x;
{
	int c,ln,cn,w;

	ln = strlen(bf);
	if ( cp < ln ) {
		// get character code length and width
		cn = kj_lenc(bf[cp]);
		w = kj_width(bf + cp);

		if ( cp + cn < ln ) {
			// check if next code is combined character code?
			if ( kj_width(bf + cp + cn) <= 0 ) {
				cn += kj_lenc(bf[cp + cn]);
			}
		}

		// move current buffer position
		cp += cn;

		// move cursor forward
		if ( x ) xt_cur_forward(w);
		else t_cur_forward(w);
	}
}

gstr_up(x)
int x;
{
	int c,w;

	if ( hc > 0 ) {
		// calculate current cursor position
		w = c = 0;
		while ( c < cp ) {
			w += kj_width(bf + c);
			c += kj_lenc(bf[c]);
		}

		// move cursor to the top of string input area
		if ( x ) xt_cur_backward(w);
		else t_cur_backward(w);

		// get one string from history buffer
		--hc;
		strncpy(bf,hist[hc],bfmax-1);
		bf[bfmax - 1] = '\0';

		// draw new string
		if ( x ) {
			xt_puts(bf);
			xt_erase_line();
		} else {
			t_puts(bf);
			t_erase_line();
		}

		// setup new current buffer position
		cp = strlen(bf);
	}
}

gstr_down(x)
int x;
{
	int c,w;

	if ( hc < hcn ) {
		// calculate current cursor position
		w = c = 0;
		while ( c < cp ) {
			w += kj_width(bf + c);
			c += kj_lenc(bf[c]);
		}

		// move cursor to the top of string input area
		if ( x ) xt_cur_backward(w);
		else t_cur_backward(w);

		// get one string from history buffer
		++hc;
		if ( hc < hcn ) {
			strncpy(bf,hist[hc],bfmax-1);
			bf[bfmax - 1] = '\0';
		} else {
			bf[0] = '\0';
		}

		// draw new string
		if ( x ) {
			xt_puts(bf);
			xt_erase_line();
		} else {
			t_puts(bf);
			t_erase_line();
		}

		// setup new current buffer position
		cp = strlen(bf);
	}
}

gstr_flush(x)
int x;
{
	int c,cn,w,w2;

	cn = w = 0;
	if ( cp > 0 ) {
		// check the break point of Kanji code
		cn = 1;
		while ( cp - cn > 0 && is_kan_str(bf, cp - cn) ) ++cn;

		// get width of the code
		w = kj_width(bf + cp - cn);

		if ( cp - cn > 0 && w <= 0 ) {	// this is combined character
			++cn;
			while ( cp - cn > 0 && is_kan_str(bf, cp - cn) ) ++cn;
			w = kj_width(bf + cp - cn);
		}
	}

	// move cursor backward
	t_clrcur();
	if ( cn > 0 ) {
		if ( x ) xt_cur_backward(w);
		else t_cur_backward(w);
	}

	// calculate cursor original position
	c = w2 = 0;
	while ( bf[cp + c] != '\0' ) {
		w2 += kj_width(bf + cp + c);
		c += kj_lenc(bf[cp + c]);
	}

	// redraw string and move cursor to original position
	if ( x ) {
		xt_puts(bf+cp-cn);
		xt_erase_line();
		xt_cur_backward(w2);
	} else {
		t_puts(bf+cp-cn);
		t_erase_line();
		t_cur_backward(w2);
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
	int c, c2, w, w2, x;
	int maxlen;

	t_clrcur();

	// determine maximum name length
	maxlen = 0;
	for ( c = 0 ; c < ncandidate ; c++ ) {
		if ( (w = kj_width_str(candidate_list[c])) > maxlen ) {
			maxlen = w;
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
		x = kj_width_str(candidate_list[c]);
	}
	t_puts("\015\n");

	gstr_prompt(xwin);

	if ( xwin ) xt_puts(bf);
	else t_puts(bf);
	xt_erase_line();

	// calculate cursor original position
	c = w2 = 0;
	while ( bf[cp + c] != '\0' ) {
		w2 += kj_width(bf + cp + c);
		c += kj_lenc(bf[cp + c]);
	}
	xt_cur_backward(w2);

	t_dspcur();

	need_redraw = TRUE;

	return 0;
}

gstr_fn_expand(x)
int x;
{
	DIR *dirp;
	struct dirent *dir;
	int c,c2,st,en,ln,all_ln,only_one,w;
	char fn[1024],path[1024],*end_path;
	char candidate[1024];
	struct stat st_buf;
	struct passwd *pw,*getpwent();
	void endpwent();

	/* extract incompleted pathname which user specified */
	st = 0;
	for ( c = 0 ; bf[c] != '\0' && c < cp ; ) {
		if ( bf[c] == '\\' && c+1 < cp && bf[c+1] != '\0' ) ++c;
		else if ( bf[c] == ' ' || bf[c] == '|' || bf[c] == '>'
			|| bf[c] == '<' || bf[c] == '"' || bf[c] == '\'' || bf[c] == '@' ) {
			st = c + 1;
		}
		c += kj_lenc(bf[c]);
	}
	en = st;
	for ( c = 0 ; bf[en] != '\0' && en < cp ; ) {
		if ( bf[en] == '\\' ) en++;
		if ( bf[en] != '\0' ) {
			c2 = kj_lenc(bf[en]);
			while ( c2-- > 0 ) fn[c++] = bf[en++];
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
					for ( c = 0 ; pw->pw_name[c] != '\0' ; ) {
						w = kj_lenc(pw->pw_name[c]);
						c2 = 0;
						while ( w > 0 ) {
							if ( pw->pw_name[c+c2] != candidate[c+c2] ) break;
							--w;
							++c2;
						}
						if ( w > 0 ) break;
						c += c2;
					}
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
		if ( ln - 1 < all_ln ) gstr_ins(candidate + ln - 1, x, TRUE);
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
				for ( c = 0 ; dir->d_name[c] != '\0' ; ) {
					w = kj_lenc(dir->d_name[c]);
					c2 = 0;
					while ( w > 0 ) {
						if ( dir->d_name[c+c2] != candidate[c+c2] ) break;
						--w;
						++c2;
					}
					if ( w > 0 ) break;
					c += c2;
				}
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
	if ( ln < all_ln ) gstr_ins(candidate + ln, x, TRUE);
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
	int c, c2;
	char *p,*end_path;

	p = end_path = NULL;
	for ( c = 0 ; fn[c] != '\0' ; c++ ) {
		path[c] = fn[c];
		if ( fn[c] == '/' ) {
			p = path + c;
			end_path = fn + c + 1;
		}
		c2 = kj_lenc(fn[c]);
		while ( --c2 > 0 ) {
			++c;
			path[c] = fn[c];
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
	if ( kj_lenc(dt) > 1 ) return TRUE;
	return FALSE;
}

is_kana(dt)
int dt;
{
	dt &= 0xff;
	if ( os_kj_code == KJ_CODE_SJIS ) {
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
	if ( os_kj_code == KJ_CODE_SJIS ) {	/* use shift-jis */
		if ( dt == '\0' ) return FALSE;
		if ( dt >= 0x81 && dt <= 0x9f ) return FALSE;
		if ( dt >= 0xe0 && dt <= 0xea ) return FALSE;
		if ( dt >= 0xa1 && dt <= 0xdf ) return FALSE;
		return TRUE;
	} else {				/* use euc or / utf-8 code */
		if ( dt == '\0' ) return FALSE;
		if ( dt & 0x80 ) return FALSE;
		else return TRUE;
	}
}

/*
	check if the position is middle of continuous bytes of Kanji code    	    	    	
 */
is_kan_str(str,p)
char *str;
int p;
{
	int c, cn;

	c = 0;
	while ( c < p ) {
		// get length of the code
		cn = kj_lenc(str[c]);

		// if code has some bytes and specified position is the middle of continous bytes ?
		if ( cn > 1 && c + cn > p ) return TRUE;

		// move to next code
		c += cn;
	}

	return FALSE;
}

int
kj_lenc(dt)
int dt;
{
	dt &= 0xff;
	if ( os_kj_code == KJ_CODE_SJIS ) {		/* shift jis */
		if ( dt >= 0x81 && dt <= 0x9f ) return 2;	/* 0x81 - 0x9f -> 2byte code */
		if ( dt >= 0xe0 && dt <= 0xea ) return 2;	/* 0xe0 - 0xea -> 2byte code */
		return 1;					/* other one is 1byte code */
	
	} else if ( os_kj_code == KJ_CODE_SJIS ) {	/* euc code */
		if ( dt < 0x80 ) return 1;			/* 0x00 - 0x80 -> 1byte code */
		return 2;					/* 0x81 - 0xff -> 2byte code */
	} else if ( os_kj_code == KJ_CODE_UTF8 ) {	/* utf-8 code */
		if ( dt < 0x80 ) return 1;			/* 0x00 - 0x7f -> 1byte code */
		else if ( dt < 0xc0 ) return 1;			/* 0x80 - 0xbf -> 2nd or later char code */
		else if ( dt < 0xe0 ) return 2;			/* 0xc0 - 0xdf -> 2byte code */
		else if ( dt < 0xf0 ) return 3;			/* 0xe0 - 0xef -> 3byte code */
		else if ( dt < 0xf8 ) return 4;			/* 0xf0 - 0xf7 -> 4byte code */
		else if ( dt < 0xfc ) return 5;			/* 0xf8 - 0xfb -> 5byte code */
		return 6;					/* 0xfc - 0xfd -> 6byte code */
	}
	return 0; /* kanji code error */
}

int
kj_width_str(str)
char *str;
{
	int c, w;

	for ( c = w = 0 ; str[c] != '\0' ; c += kj_lenc(str[c]) ) {
		w += kj_width(str + c);
	}

	return w;
}

int
kj_width(str)
char *str;
{
	int dt, dt2, dt3;

	dt = *str & 0xff;
	dt2 = *(str+1) & 0xff;
	dt3 = *(str+2) & 0xff;
	if ( os_kj_code == KJ_CODE_SJIS ) {		/* shift jis */
		if ( dt >= 0x81 && dt <= 0x9f ) return 2;	/* 0x81 - 0x9f -> full width */
		if ( dt >= 0xe0 && dt <= 0xea ) return 2;	/* 0xe0 - 0xea -> full width */
		return 1;					/* other one is half width */
	} else if ( os_kj_code == KJ_CODE_SJIS ) {	/* euc code */
		if ( dt < 0x80 || dt == 0x8e ) return 1;	/* 0x00 - 0x80, 0x8e -> half width */
		return 2;					/* 0x81 - 0xff -> full width */
	} else if ( os_kj_code == KJ_CODE_UTF8 ) {	/* utf-8 code */
		if ( dt < 0x80 ) return 1;			/* 0x00 - 0x7f -> half width */
		else if ( dt == 0xe2 && dt2 == 0x80 && dt3 >= 0x98 && dt3 <= 0x9f  ) return 1;
		else if ( dt == 0xef && dt2 == 0xbd && dt3 >= 0xa1  ) return 1;	/* 0xefbda1 - 0xefbdbf -> half width(kana) */
		else if ( dt == 0xef && dt2 == 0xbe && dt3 <= 0x9f  ) return 1;	/* 0xefbe80 - 0xefbe9f -> half width(kana) */
		else if ( dt == 0xe3 && dt2 == 0x82 && dt3 == 0x99 ) return 0;	/* 0xe38299 -> combine character(DAKUON) */
		else if ( dt == 0xe3 && dt2 == 0x82 && dt3 == 0x9a ) return 0;	/* 0xe3829a -> combine character(HANDAKUON) */
		return 2;					/* other one is full width */
	}
	return 0; /* kanji code error */
}
