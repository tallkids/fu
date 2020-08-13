/*
	File Utility ( Xwindow Text Screen Library )

	Author	T.Tashiro (Nifty PDC02432)	1991-11-11	Ver 1.0
*/
/************************************************************************
*									*
*	LICENCED MATERIAL OF T.TASHIRO					*
*	REPRODUCTION, USE, MODIFICATION,DISCLOSURE OTHERWISE THAN	*
*	PERMITTED IN THE LICENCE AGREEMENT IS STRICTLY PROHIBITED.	*
*	COPYRIGHT (C) T.TASHIRO 1990.         ALL RIGHTS RESERVED.	*
*									*
*************************************************************************/
#if XWINDOW

#include <stdio.h>
#if !(NEWS3400 | I386BSD)
#    include <malloc.h>
#endif
#if I386BSD
#    include <sys/malloc.h>
#endif
#include "key.h"
#include "fu.h"
#include "xfu_icon"

#define FALSE 0
#define TRUE (!FALSE)

char *xdispname = NULL;
Display *xdisplay;
Window xwindow,xrootwindow;
char *xgeom = NULL;
GC xgc,xgccur,xgct,xgctk,xgctj;
XFontStruct *xfn,*xfnk,*xfnj;
char *xfont = "fixed";
char *xfontj = "fixed";
char *xfontk = "fixed";
unsigned long xback,xfore;
char *xbackname = "black";
char *xforename = "white";
int xchh,xchw;
int xwidth,xheight;

int opt_setflg = 0;		/* Command line option set flag */

int xt_row = 24;		/* Screen Row Width */
int xt_column = 80;		/* Screen Column Width */

int xxpos = 0,xypos = 0;	/* Cursor Position */

char *win_name = "xfu";
char *icon_name = "xfu";
Pixmap icon_pixmap;
XSizeHints size_hints;

extern char *xget_default();

x_init(argc,argv)
int argc;
char **argv;
{
	XEvent e;
	Colormap cmap;
	XColor col0,col1;
	char *getenv(),*hp,*p;
	int dum;
	Window ret_win;

	if ( (hp = getenv("WINDOWID")) != NULL ) {
		xrootwindow = atoi(hp);
	} else xrootwindow = -1;

	if ( (xdisplay = XOpenDisplay(xdispname)) == NULL ) {
		fprintf(stderr,"%s: Cannot open display\n",prog_name);
		exit(1);
	}

	xget_geometry();
	if ( !(opt_setflg & OPT_FONT) ) {
		p = xget_default("Font");
		if ( p != NULL ) xfont = p;
	}
	if ( !(opt_setflg & OPT_RFONT) ) {
		p = xget_default("KanaFont");
		if ( p != NULL ) xfontk = p;
	}
	if ( !(opt_setflg & OPT_KFONT) ) {
		p = xget_default("KanjiFont");
		if ( p != NULL ) xfontj = p;
	}
	if ( !(opt_setflg & OPT_FG) ) {
		p = xget_default("Foreground");
		if ( p != NULL ) xforename = p;
	}
	if ( !(opt_setflg & OPT_BG) ) {
		p = xget_default("Background");
		if ( p != NULL ) xbackname = p;
	}
	if ( !(opt_setflg & OPT_NAME) ) {
		p = xget_default("Title");
		if ( p != NULL ) win_name = icon_name = p;
	}

	xfn = XLoadQueryFont(xdisplay,xfont);
	xfnk = XLoadQueryFont(xdisplay,xfontk);
	xfnj = XLoadQueryFont(xdisplay,xfontj);

	if ( xfn == NULL || xfnk == NULL || xfnj == NULL ) {
		fprintf(stderr,"%s: Cannot open font\n",prog_name);
		exit(1);
	}

	if ( xfnj->min_byte1 > 0x21 ) fn_kj_code = 0;	/* shift-jis */
	else fn_kj_code = 1;	/* jis code */

	if ( xfnk->max_char_or_byte2 >= 0x80 ) fn_ka_code = 0;
	else fn_ka_code = 1;

	xchh = xfn->ascent + xfn->descent;
	xchw = xfn->max_bounds.width;

	xheight = xt_row * xchh;
	xwidth = xt_column * xchw;

	cmap = DefaultColormap(xdisplay,0);
	XAllocNamedColor(xdisplay,cmap,xforename,&col1,&col0);
	xfore = col1.pixel;
	XAllocNamedColor(xdisplay,cmap,xbackname,&col1,&col0);
	xback = col1.pixel;
/*
	xback = BlackPixel(xdisplay,0);
	xfore = WhitePixel(xdisplay,0);
*/
	xwindow = XCreateSimpleWindow(xdisplay,RootWindow(xdisplay,DefaultScreen(xdisplay))
			,100,100,xwidth,xheight,2,xback,xfore);

	xgc = XCreateGC(xdisplay,xwindow,0,0);
	xgccur = XCreateGC(xdisplay,xwindow,0,0);
	xgct = XCreateGC(xdisplay,xwindow,0,0);
	xgctk = XCreateGC(xdisplay,xwindow,0,0);
	xgctj = XCreateGC(xdisplay,xwindow,0,0);

	XSetFont(xdisplay,xgct,xfn->fid);
	XSetFont(xdisplay,xgctk,xfnk->fid);
	XSetFont(xdisplay,xgctj,xfnj->fid);

	icon_pixmap = XCreateBitmapFromData(xdisplay,xwindow,xfu_icon_bits,
			xfu_icon_width,xfu_icon_height);

	size_hints.flags |= ( PSize | PMinSize | PResizeInc );
	size_hints.width = xwidth;
	size_hints.height = xheight;
	size_hints.min_width = xchw * 21;
	size_hints.min_height = xchh * 20;
	size_hints.width_inc = xchw;
	size_hints.height_inc = xchh;

	XSetStandardProperties(xdisplay,xwindow,win_name,icon_name,
		icon_pixmap,argv,argc,&size_hints);

	XSelectInput(xdisplay,xwindow,ExposureMask | KeyPressMask | KeyReleaseMask
		| ButtonPressMask | ButtonReleaseMask );
	XMapWindow(xdisplay,xwindow);
	XNextEvent(xdisplay,&e);	/* dummy event */
	XMapRaised(xdisplay,xwindow);
	XWarpPointer(xdisplay,None,xwindow,0,0,0,0,10,10);
	XSetInputFocus(xdisplay,xwindow,RevertToParent,CurrentTime);
	XFlush(xdisplay);
}

char *xget_default(name)
char *name;
{
	char *p,*str;

	if ( (p = XGetDefault(xdisplay,prog_name,name)) == NULL ) return NULL;
	if ( (str = (char *)malloc((strlen(p)+1) * sizeof(char))) == NULL ) {
		fprintf(stderr,"%s:memory allocation error\n",prog_name);
		exit(-1);
	}
	strcpy(str,p);

	return str;
}

xget_geometry()
{
	char buf[80];
	int gflag,x,y,w,h;

	size_hints.x = size_hints.y = 100;

	if ( xgeom == NULL ) xgeom = XGetDefault(xdisplay,prog_name,"Geometry");
	if ( xgeom != NULL ) {
		strcpy(&buf[1],xgeom);
		buf[0] = '=';
		gflag = XParseGeometry(buf,&x,&y,&w,&h);
		if ( gflag & XValue ) {
			if ( XNegative & gflag )
				x = DisplayWidth(xdisplay,0) + x;
			size_hints.flags |= USPosition;
			size_hints.x = x;
		}
		if ( gflag & YValue ) {
			if ( YNegative & gflag )
				y = DisplayHeight(xdisplay,0) + y;
			size_hints.flags |= USPosition;
			size_hints.y = y;
		}
		if ( gflag & WidthValue ) {
			if ( w >= 21 ) xt_column = w;
		}
		if ( gflag & HeightValue ) {
			if ( h >= 20 ) xt_row = h;
		}
	}
}

x_close()
{
	XWarpPointer(xdisplay,None,xrootwindow,0,0,0,0,10,10);
	XFlush(xdisplay);
	XDestroyWindow(xdisplay,xwindow);
	XCloseDisplay(xdisplay);
}

/***************************************************
	Set Cursor Position to (x,y)
****************************************************/
xt_loc(x,y)
int x,y;
{
	xxpos = x * xchw;
	xypos = y * xchh;
}

/************************************************************
	Erase to the End of Line from Cursor Position
*************************************************************/
xt_erase_line()
{
	XSetForeground(xdisplay,xgc,xfore);
	XFillRectangle(xdisplay,xwindow,xgc,xxpos,xypos,xwidth-xxpos,xchh);
}

xt_erase_line2(endpos)
int endpos;
{
	int xw;

	xw = xwidth-xxpos-endpos * xchw;
	if ( xw <= 0 ) return;
	XSetForeground(xdisplay,xgc,xfore);
	XFillRectangle(xdisplay,xwindow,xgc,xxpos,xypos,xw,xchh);
}

/***************************************************
	Cursor Backwards
****************************************************/
xt_cur_backward(cn)
int cn;
{
	int c;

	for ( c = 0 ; c < cn ; c++ ) {
		xxpos -= xchw;
		if ( xxpos < 0 ) {
			if ( xypos - xchh >= 0 ) {
				xypos -= xchh;
				xxpos = t_column * xchw - xchw;
			} else  xxpos += xchw;
		}
	}
}

/***************************************************
	Cursor Forward
****************************************************/
xt_cur_forward(cn)
int cn;
{
	int c;

	for ( c = 0 ; c < cn ; c++ ) {
		xxpos += xchw;
		if ( xxpos >= xwidth ) {
			if ( xypos + xchh < xheight ) {
				xypos += xchh;
				xxpos = 0;
			} else xxpos -= xchw;
		}
	}
}

/***************************************************
	Cursor Display
****************************************************/
xt_clrcur()
{
	XSetFunction(xdisplay,xgccur,GXinvert);
/*	XSetForeground(xdisplay,xgccur,xfore); */
	XFillRectangle(xdisplay,xwindow,xgccur,xxpos,xypos,xchw,xchh);
}

/***************************************************
	Clear Cursor
****************************************************/
xt_dspcur()
{
	XSetFunction(xdisplay,xgccur,GXinvert);
/*	XSetForeground(xdisplay,xgccur,xfore); */
	XFillRectangle(xdisplay,xwindow,xgccur,xxpos,xypos,xchw,xchh);
}

/***************************************************
	Set Reverse/Normal Mode
****************************************************/
#define REVERSE TRUE
#define NORMAL FALSE

static int xterm_mode = NORMAL;

xt_reverse()
{
	if ( xterm_mode != REVERSE ) {
		XSetForeground(xdisplay,xgct,xfore);
		XSetBackground(xdisplay,xgct,xback);
		XSetForeground(xdisplay,xgctk,xfore);
		XSetBackground(xdisplay,xgctk,xback);
		XSetForeground(xdisplay,xgctj,xfore);
		XSetBackground(xdisplay,xgctj,xback);
	}
	xterm_mode = REVERSE;
}

xt_normal()
{
	if ( xterm_mode != NORMAL ) {
		XSetForeground(xdisplay,xgct,xback);
		XSetBackground(xdisplay,xgct,xfore);
		XSetForeground(xdisplay,xgctk,xback);
		XSetBackground(xdisplay,xgctk,xfore);
		XSetForeground(xdisplay,xgctj,xback);
		XSetBackground(xdisplay,xgctj,xfore);
	}
	xterm_mode = NORMAL;
}

/***************************************************
	Screen Clear
****************************************************/
xt_cls()
{
	XClearWindow(xdisplay,xwindow);
}

/***************************************************
	Output One Character
****************************************************/
static int kanji1 = -1;

xt_putc(ch)
int ch;
{
	char kk[2],ch2;
	unsigned int f,s;

	ch2 = ch;
	if ( kanji1 > 0 ) {
		if ( os_kj_code == 0 ) {	/* shift jis */
			if ( fn_kj_code == 0 ) {
				kk[0] = kanji1;
				kk[1] = ch2;
			} else {
				f = kanji1;
				s = ch2;
				sjtoj(&f,&s);
				kk[0] = f;
				kk[1] = s;
			}
			XDrawImageString16(xdisplay,xwindow,xgctj
				,xxpos,xypos + xfnj->ascent,kk,2);
			kanji1 = -1;
			xxpos += (xchw * 2);
		} else {			/* euc code */
			if ( is_kana(kanji1) ) {
				if ( fn_ka_code == 0 ) ch2 &= 0xff;
				else ch2 &= 0x7f;
				XDrawImageString(xdisplay,xwindow,xgctk
						,xxpos,xypos + xfnk->ascent,&ch2,1);
				kanji1 = -1;
				xxpos += xchw;
			} else {
				if ( fn_kj_code == 1 ) {
					kk[0] = kanji1 & 0x7f;
					kk[1] = ch2 & 0x7f;
				} else {
					f = kanji1 & 0x7f;
					s = ch2 & 0x7f;
					jtosj(&f,&s);
					kk[0] = f;
					kk[1] = s;
				}
				XDrawImageString16(xdisplay,xwindow,xgctj
					,xxpos,xypos + xfnj->ascent,kk,2);
				kanji1 = -1;
				xxpos += (xchw * 2);
			}
		}
	} else if ( is_kan1(ch2) ) {
		kanji1 = ch & 0xff;
		return;
	} else if ( is_kana(ch2) > 0 ) {
		if ( fn_ka_code == 0 ) ch2 &= 0xff;
		else ch2 &= 0x7f;
		XDrawImageString(xdisplay,xwindow,xgctk
				,xxpos,xypos + xfnk->ascent,&ch2,1);
		xxpos += xchw;
	} else {
		XDrawImageString(xdisplay,xwindow,xgct
			,xxpos,xypos + xfn->ascent,&ch2,1);
		xxpos += xchw;
	}
	if ( xxpos >= xwidth ) {
		if ( xypos + xchh < xheight ) {
			xypos += xchh;
			xxpos = 0;
		} else xxpos -= xchw;
	}
}

/***************************************************
	Output String (Kanji/Ascii)
****************************************************/
xt_puts(str)
char *str;
{
	char *p,*p2;
	int cn;
	unsigned int msk;
	unsigned int f,s;

	if ( ascii )
		for ( p = str ; *p != '\0' ; ++p )
			*p = ((*p & 0xff) > 0x80)?'?':*p;

	msk = ( fn_ka_code == 0 )?0xff:0x7f;

	while ( *str != '\0' ) {
		if ( is_kana(*str) ) {
			cn = 1;
			p = p2 = str++;
			if ( os_kj_code != 0 ) {
				*p2 = *str;
				++str;
			}
			*p2 &= msk;
			++p2;
			while ( is_kana(*str) ) {
				++str;
				++cn;
				if ( os_kj_code != 0 ) {
					*p2 = *str;
					++str;
				}
				*p2 &= msk;
				++p2;
			}
			XDrawImageString(xdisplay,xwindow,xgctk
				,xxpos,xypos + xfnk->ascent,p,cn);
			xxpos += (xchw * cn);
		} else if ( is_kan1(*str) ) {
			cn = 1;
			p = str;
			if ( *(str+1) != '\0' ) {
				f = *str;
				s = *(str+1);
				if ( os_kj_code == 1 ) {
					f &= 0x7f;
					s &= 0x7f;
					if ( fn_kj_code == 0 )
						jtosj(&f,&s);
				} else if ( os_kj_code == 0 && fn_kj_code == 1 ) {
					sjtoj(&f,&s);
				}
				*str = f;
				*(str+1) = s;
				str += 2;
				++cn;
				while ( !is_kana(*str) && is_kan1(*str) ) {
					if ( *(str+1) == '\0' ) {
						++str;
						break;
					}
					f = *str;
					s = *(str+1);
					if ( os_kj_code == 1 ) {
						f &= 0x7f;
						s &= 0x7f;
						if ( fn_kj_code == 0 )
							jtosj(&f,&s);
					} else if ( os_kj_code == 0 && fn_kj_code == 1 ) {
						sjtoj(&f,&s);
					}
					*str = f;
					*(str+1) = s;
					str += 2;
					cn += 2;
				}
				XDrawImageString16(xdisplay,xwindow,xgctj
					,xxpos,xypos + xfnj->ascent,p,cn);
			} else ++str;
			xxpos += (xchw * cn);
		} else {
			cn = 1;
			p = str++;
			while ( is_norm(*str) ) {
				++str;
				++cn;
			}
			XDrawImageString(xdisplay,xwindow,xgct
				,xxpos,xypos + xfn->ascent,p,cn);
			xxpos += (xchw * cn);
		}
	}
/*
	for ( p = str ; *p != '\0' ; ++p )
		xt_putc(*p);
*/
	xt_flush();
}

sjtoj(first,second)
unsigned int *first,*second;
{
	*first &= 0xff;
	*second &= 0xff;
	*first = ( *first <= 0x9f )?(*first - 0x71):(*first - 0xb1);
	*first = *first * 2 + 1;
	if ( *second > 0x7f ) --(*second);
	if ( *second >= 0x9e ) {
		*second -= 0x7d;
		++*first;
	} else *second -= 0x1f;
}

jtosj(first,second)
unsigned int *first,*second;
{
	*first &= 0xff;
	*second &= 0xff;
	*second = ( (*first % 2) == 0 )?(*second + 0x7d):(*second + 0x1f);
	if ( *second >= 0x7f ) ++(*second);
	*first = (*first - 0x21) / 2;
	*first += 0x81;
	if ( *first > 0x9f ) *first += 0x40;
}

/***************************************************
	Flush Output Buffer
****************************************************/
xt_flush()
{
	XFlush(xdisplay);
}

#endif	/* End if for xtext.c */
