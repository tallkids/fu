/*
	Input One Character For Xwindow

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
#include <signal.h>

#if XWINDOW
#include <X11/keysym.h>

#include "key.h"
#include "fu.h"

struct XKTABLE {
	int sym,code,scode,ccode;
} xktable[] = {
	{ XK_BackSpace,		0x08,0x08,0x08 },
	{ XK_Tab,		0x09,0x09,0x09 },
	{ XK_Linefeed,		0x0a,0x0a,0x0a },
	{ XK_Clear,		0x0b,0x0b,0x0b },
	{ XK_Return,		0x0d,0x0d,0x0d },
	{ XK_Pause,		0x13,0x13,0x13 },
	{ XK_Escape,		0x1b,0x1b,0x1b },
	{ XK_Delete,		KEY_DEL,	KEY_S_DEL,	KEY_C_DEL },
	{ XK_Home,		KEY_HOME,	KEY_S_HOME,	KEY_C_HOME },
	{ XK_Left,		KEY_LEFT,	KEY_S_LEFT,	KEY_C_LEFT },
	{ XK_Up,		KEY_UP,		KEY_S_UP,	KEY_C_UP },
	{ XK_Right,		KEY_RIGHT,	KEY_S_RIGHT,	KEY_C_RIGHT },
	{ XK_Down,		KEY_DOWN,	KEY_S_DOWN,	KEY_C_DOWN },
	{ XK_Prior,		KEY_ZENPEJI,	KEY_S_ZENPEJI,	KEY_C_ZENPEJI },
	{ XK_Next,		KEY_JIPEJI,	KEY_S_JIPEJI,	KEY_C_JIPEJI },
#if H2050
	{ XK_Scroll_Left,	KEY_BLEFT,	KEY_S_BLEFT,	KEY_C_BLEFT },
	{ XK_Scroll_Up,		KEY_BUP,	KEY_S_BUP,	KEY_C_BUP },
	{ XK_Scroll_Right,	KEY_BRIGHT,	KEY_S_BRIGHT,	KEY_C_BRIGHT },
	{ XK_Scroll_Down,	KEY_BDOWN,	KEY_S_BDOWN,	KEY_C_BDOWN },
#endif
	{ XK_Insert,		KEY_INS,	KEY_S_INS,	KEY_C_INS },
	{ XK_F1,		KEY_PF1,	KEY_PF1,	KEY_PF1 },
	{ XK_F2,		KEY_PF2,	KEY_PF2,	KEY_PF2 },
	{ XK_F3,		KEY_PF3,	KEY_PF3,	KEY_PF3 },
	{ XK_F4,		KEY_PF4,	KEY_PF4,	KEY_PF4 },
	{ XK_F5,		KEY_PF5,	KEY_PF5,	KEY_PF5 },
	{ XK_F6,		KEY_PF6,	KEY_PF6,	KEY_PF6 },
	{ XK_F7,		KEY_PF7,	KEY_PF7,	KEY_PF7 },
	{ XK_F8,		KEY_PF8,	KEY_PF8,	KEY_PF8 },
	{ XK_F9,		KEY_PF9,	KEY_PF9,	KEY_PF9 },
	{ XK_F10,		KEY_PF10,	KEY_PF10,	KEY_PF10 },
	{ XK_F11,		KEY_PF11,	KEY_PF11,	KEY_PF11 },
	{ XK_F12,		KEY_PF12,	KEY_PF12,	KEY_PF12 },
	{ XK_F13,		KEY_C_PF1,	KEY_C_PF1,	KEY_C_PF1 },
	{ XK_F14,		KEY_C_PF2,	KEY_C_PF2,	KEY_C_PF2 },
	{ XK_F15,		KEY_C_PF3,	KEY_C_PF3,	KEY_C_PF3 },
	{ XK_F16,		KEY_C_PF4,	KEY_C_PF4,	KEY_C_PF4 },
	{ XK_F17,		KEY_C_PF5,	KEY_C_PF5,	KEY_C_PF5 },
	{ XK_F18,		KEY_C_PF6,	KEY_C_PF6,	KEY_C_PF6 },
	{ XK_F19,		KEY_C_PF7,	KEY_C_PF7,	KEY_C_PF7 },
	{ XK_F20,		KEY_C_PF8,	KEY_C_PF8,	KEY_C_PF8 },
	{ XK_F21,		KEY_C_PF9,	KEY_C_PF9,	KEY_C_PF9 },
	{ XK_F22,		KEY_C_PF10,	KEY_C_PF10,	KEY_C_PF10 },
	{ XK_F23,		KEY_C_PF11,	KEY_C_PF11,	KEY_C_PF11 },
	{ XK_F24,		KEY_C_PF12,	KEY_C_PF12,	KEY_C_PF12 }
};

extern struct MOUSE_IN_TAG m_stat;
extern int k_tab_cn;

static int key_buf[MAX_KEYIN];
static int kc = 0;
static int kp = 0;

int
xkey_in(flg)
int flg;	/* flg == TRUE -> if (' ' <= key <= 0x100) then return key */
{
	int c,c2;
	int st,en,st2,en2;
	int flag,ky;

	if ( kc > 0 ) {
		--kc;
		++kp;
		return key_buf[kp];
	}
	st = 0;
	en = k_tab_cn - 1;
	for ( c = 0 ; c < MAX_KEYIN ; c++ ) {
		if ( flg ) key_buf[c] = xgetchr2();
		else key_buf[c] = xgetchr();
		++kc;
		if ( flg && c == 0
			&& key_buf[0] >= ' ' && key_buf[0] <= 0x100 ) break;
		st2 = en;
		en2 = st;
		for ( flag = FALSE , c2 = st ; k_table[c2].func >= 0
			&& c2 <= en ; c2++ ) {
			if ( key_buf[c] == k_table[c2].key[c] ) {
				flag = TRUE;
				if ( c >= MAX_KEYIN-1
					|| k_table[c2].key[c+1] == 0 ) {
					kc = 0;
					return k_table[c2].func;
				}
				if ( st2 >= c2 ) st2 = c2;
				if ( c2 > en2 ) en2 = c2;
			}
		}
		if ( !flag ) break;
		st = st2;
		en = en2;
	}
	kp = 0;
	--kc;

	return key_buf[kp];
}

#define X_CHR_PIC xchw
#define Y_CHR_PIC xchh

#define MAXXKBUF	20
static char xkeybuf[MAXXKBUF],dxkeybuf[MAXXKBUF];
static int xkeyp = -1;
static KeySym xkeysym;

#define XKEY_SHIFT	1
#define XKEY_CNTL	2
static int xkeystat = 0;

static int expose_serial = -1;
int xcurdisp = FALSE;

int xgetchr()
{
	XEvent e;
	int ky,c,cn;
	Window w_root;
	unsigned int x_pos,y_pos,border,depth;

	if ( xkeyp != -1 ) {
		ky = xkeybuf[xkeyp++];
		if ( xkeybuf[xkeyp] == '\0' ) xkeyp = -1;
		return ky;
	}
	ky = 0;
	while ( ky == 0 ) {
		if ( xcurdisp ) xt_dspcur();
		XNextEvent(xdisplay,&e);
		if ( xcurdisp ) xt_clrcur();
		if ( shell_pid > 0 && e.type != Expose ) continue;
		switch ( e.type ) {
			case Expose :
/*
printf("win = %d,count = %d\015\n",e.xexpose.window,e.xexpose.count);
printf("serial = %d,disp = %d\015\n",e.xexpose.serial,e.xexpose.display);
*/
				if ( e.xexpose.window == xwindow
					&& e.xexpose.serial != expose_serial
					&& e.xexpose.count == 0 ) {
					ky = KEY_EXPOSE;
					expose_serial = e.xexpose.serial;
					XGetGeometry(xdisplay,xwindow,&w_root,&x_pos,&y_pos
						,&xwidth,&xheight,&border,&depth);
					xt_column = xwidth / xchw;
					xt_row = xheight / xchh;
					adjust_screen_mode();
				}
				break;
			case KeyPress :
				xkeyp = XLookupString(&e,xkeybuf,MAXXKBUF,&xkeysym,NULL);
				if ( xkeyp <= 0 ) {
					if ( xkeysym == XK_Shift_L || xkeysym == XK_Shift_R ) {
						xkeystat |= XKEY_SHIFT;
					} else if ( xkeysym == XK_Control_L || xkeysym == XK_Control_R ) {
						xkeystat |= XKEY_CNTL;
					}
					xkeyp = -1;
					if ( xkeysym != NoSymbol ) {
						cn = sizeof(xktable) / sizeof(struct XKTABLE);
						for ( c = 0 ; c < cn ; c++ ) {
							if ( xktable[c].sym == xkeysym ) {
								if ( xkeystat & XKEY_SHIFT )
									ky = xktable[c].scode;
								else if ( xkeystat & XKEY_CNTL )
									ky = xktable[c].ccode;
								else ky = xktable[c].code;
							}
						}
/*if ( ky == 0 ) printf("key = %04x\015\n",xkeysym);*/
					}
				} else {
					xkeybuf[xkeyp] = '\0';
					ky = xkeybuf[(xkeyp = 0)];
					if ( xkeybuf[++xkeyp] == 0 ) xkeyp = -1;
/*printf("key = ");
for ( c = 0 ; xkeybuf[c] != '\0' ; c++ )
	printf("%02x",xkeybuf[c]);
printf("\015\n");*/
				}
				break;
			case KeyRelease :
				XLookupString(&e,dxkeybuf,MAXXKBUF,&xkeysym,NULL);
				if ( xkeysym == XK_Shift_L || xkeysym == XK_Shift_R ) {
					xkeystat &= ~XKEY_SHIFT;
				} else if ( xkeysym == XK_Control_L || xkeysym == XK_Control_R ) {
					xkeystat &= ~XKEY_CNTL;
				}
				break;
			case ButtonPress :
				if ( e.xbutton.button == Button1 ) {
					m_stat.stat = MOUSE_L_ON;
					m_stat.st |= MOUSE_L_ON;
				} else if ( e.xbutton.button == Button3 ) {
					m_stat.stat = MOUSE_R_ON;
					m_stat.st |= MOUSE_R_ON;
				}
				m_stat.x = e.xbutton.x / xchw;
				m_stat.y = e.xbutton.y / xchh;
				ky = KEY_MOUSE;
				break;
			case ButtonRelease :
				if ( e.xbutton.button == Button1 ) {
					m_stat.stat = MOUSE_L_OFF;
					m_stat.st &= ~MOUSE_L_ON;
				} else if ( e.xbutton.button == Button3 ) {
					m_stat.stat = MOUSE_R_OFF;
					m_stat.st &= ~MOUSE_R_ON;
				}
				m_stat.x = e.xbutton.x / xchw;
				m_stat.y = e.xbutton.y / xchh;
				ky = KEY_MOUSE;
				break;
		}
	}

	return ky;
}

int xgetchr2()
{
	int ky,dum;

	while ( TRUE ) {
		ky = xgetchr();
		if ( ky != KEY_MOUSE ) break;
		if ( m_stat.stat == MOUSE_L_ON ) {
			ky = 0x0d;
			while ( !(xgetchr() == KEY_MOUSE
				&& m_stat.stat == MOUSE_L_OFF) );
			break;
		} else if ( m_stat.stat == MOUSE_R_ON ) {
			ky = 0x1b;
			while ( !(xgetchr() == KEY_MOUSE
				&& m_stat.stat == MOUSE_R_OFF) );
			break;
		}
	}

	return ky;
}

#endif
