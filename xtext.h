/*
	File Utility ( Header File For Xtext.c )

	Author	T.Tashiro (Nifty PDC02432)	1991-11-08	Ver 1.0
*/
/************************************************************************
*									*
*	LICENCED MATERIAL OF T.TASHIRO					*
*	REPRODUCTION, USE, MODIFICATION,DISCLOSURE OTHERWISE THAN	*
*	PERMITTED IN THE LICENCE AGREEMENT IS STRICTLY PROHIBITED.	*
*	COPYRIGHT (C) T.TASHIRO 1991.         ALL RIGHTS RESERVED.	*
*									*
*************************************************************************/

#if XWINDOW

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define OPT_FONT	(1 << 0)
#define OPT_RFONT	(1 << 1)
#define OPT_KFONT	(1 << 2)
#define OPT_FG		(1 << 3)
#define OPT_BG		(1 << 4)
#define OPT_NAME	(1 << 5)

extern char *xdispname;
extern Display *xdisplay;
extern Window xwindow,xrootwindow;
extern char *xgeom;
extern GC xgc,xgccur,xgct,xgctk,xgctj;
extern XFontStruct *xfn,*xfnk,*xfnj;
extern char *xfont,*xfontj,*xfontk;
extern unsigned long xback,xfore;
extern char *xbackname,*xforename;
extern int xchh,xchw;
extern int xwidth,xheight;
extern int xt_row,xt_column;
extern char *win_name;
extern char *icon_name;
extern int opt_setflg;

#endif
