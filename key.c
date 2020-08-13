/*
	Input One Character

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
#include <termios.h> 
#if MINIX
#  undef NULL
#  include <string.h>
#  undef NULL
#  include <stdlib.h>
#  undef NULL
#  define NULL 0
#else
#  include <string.h>
#  include <memory.h>
#  include <sys/ioctl.h>
#endif
#include <sys/time.h>
#include <errno.h>
#include "key.h"

#define FALSE 0
#define TRUE (!FALSE)

struct KEYTABLE_TAG k_table[] = {
/*	"\030"   , KEY_TORIKESI ,*/	/* torikesi */
	"\033\033" , KEY_ESC2 ,		/* double ESC */
	"\033D"  , KEY_DOWN ,		/* down */
	"\033M"  , KEY_UP ,		/* up */
#if H2050
	"\033N0" , KEY_KAKUTYOU	,	/* kakutyou kinou */
	"\033N1" , KEY_PA1 ,		/* pa1 */
	"\033N2" , KEY_PA2 ,		/* pa2 */
	"\033N3" , KEY_PA3 ,		/* pa3 */
	"\033N5" , KEY_SCREEN ,		/* ctrl + torikesi (screen) */
	"\033N6" , KEY_SRQ ,		/* ctrl + pa2 */
	"\033N7" , KEY_PA4 ,		/* pa4 */
	"\033N8" , KEY_TYUDAN ,		/* ctrl + warikomi */
	"\033N9" , KET_TEST ,		/* ctrl + pa3 */
	"\033N?" , KEY_JIKKOU ,		/* ctrl + jikkou */
	"\033N@" , KEY_FIELD ,		/* field */
	"\033NA" , KEY_PRINT ,		/* print */
	"\033NE" , KEY_HENKANTAISHOU ,	/* hennkann taisyou */
	"\033NO" , KEY_FUNCTION ,	/* function */
	"\033NU" , KEY_SAIHENKAN ,	/* shift + hennkann taisyou */
	"\033N_" , KEY_S_FUNCTION ,	/* shift + function */
	"\033N`" , KEY_DATA ,		/* ctrl + field (data) */
	"\033Na" , KEY_STOPPRINT ,	/* ctrl + print (Stop Print) */
	"\033No" , KEY_C_FUNCTION ,	/* ctrl + function */
#endif
	"\033O0" , KEY_S_HOME ,		/* shift + home */
	"\033O1" , KEY_S_UP ,		/* shift + up */
	"\033O2" , KEY_S_DOWN ,		/* shift + down */
	"\033O3" , KEY_S_RIGHT ,	/* shift + right */
	"\033O4" , KEY_S_LEFT ,		/* shift + left */
#if H2050
	"\033O5" , KEY_S_BUP ,		/* shift + box-up */
	"\033O6" , KEY_S_BDOWN ,	/* shift + box-down */
	"\033O7" , KEY_S_BRIGHT ,	/* shift + box-right */
	"\033O8" , KEY_S_BLEFT ,	/* shift + box-left */
#endif
	"\033O9" , KEY_S_ZENPEJI ,	/* shift + zenpe-ji */
	"\033O:" , KEY_S_JIPEJI ,	/* shift + jipe-ji */
	"\033O;" , KEY_S_INS ,		/* shift + sounyu */
	"\033O<" , KEY_S_DEL ,		/* shift + sakujo */
	"\033O@" , KEY_C_HOME ,		/* ctrl + home */
	"\033OA" , KEY_C_UP ,		/* ctrl + up */
	"\033OB" , KEY_C_DOWN ,		/* ctrl + down */
	"\033OC" , KEY_C_RIGHT ,	/* ctrl + right */
	"\033OD" , KEY_C_LEFT ,		/* ctrl + left */
#if H2050
	"\033OE" , KEY_C_BUP ,		/* ctrl + box-up */
	"\033OF" , KEY_C_BDOWN ,	/* ctrl + box-down */
	"\033OG" , KEY_C_BRIGHT ,	/* ctrl + box-right */
	"\033OH" , KEY_C_BLEFT ,	/* ctrl + box-left */
#endif
	"\033OI" , KEY_C_ZENPEJI ,	/* ctrl + zenpe-ji */
	"\033OJ" , KEY_C_JIPEJI ,	/* ctrl + jipe-ji */
	"\033OK" , KEY_C_INS ,		/* ctrl + sounyu */
	"\033OL" , KEY_C_DEL ,		/* ctrl + sakujo */
	"\033OP" , KEY_PF1 ,		/* pf1 */
	"\033OQ" , KEY_PF2 ,		/* pf2 */
	"\033OR" , KEY_PF3 ,		/* pf3 */
	"\033OS" , KEY_PF4 ,		/* pf4 */
	"\033OT" , KEY_PF5 ,		/* pf5 */
	"\033OU" , KEY_PF6 ,		/* pf6 */
	"\033OV" , KEY_PF7 ,		/* pf7 */
	"\033OW" , KEY_PF8 ,		/* pf8 */
	"\033OX" , KEY_PF9 ,		/* pf9 */
	"\033OY" , KEY_PF10 ,		/* pf10 */
	"\033OZ" , KEY_PF11 ,		/* pf11 */
	"\033O[" , KEY_PF12 ,		/* pf12 */
	"\033O\\" , KEY_C_PF1 ,		/* ctrl + pf1 */
	"\033O]" , KEY_C_PF2 ,		/* ctrl + pf2 */
	"\033O^" , KEY_C_PF3 ,		/* ctrl + pf3 */
	"\033O_" , KEY_C_PF4 ,		/* ctrl + pf4 */
	"\033O`" , KEY_C_PF5 ,		/* ctrl + pf5 */
	"\033Oa" , KEY_C_PF6 ,		/* ctrl + pf6 */
	"\033Ob" , KEY_C_PF7 ,		/* ctrl + pf7 */
	"\033Oc" , KEY_C_PF8 ,		/* ctrl + pf8 */
	"\033Od" , KEY_C_PF9 ,		/* ctrl + pf9 */
	"\033Oe" , KEY_C_PF10 ,		/* ctrl + pf10 */
	"\033Of" , KEY_C_PF11 ,		/* ctrl + pf11 */
	"\033Og" , KEY_C_PF12 ,		/* ctrl + pf12 */
#if H2050
	"\033[ @" , KEY_BLEFT ,		/* box-left */
	"\033[ A" , KEY_BRIGHT ,	/* box-right */
#endif
	"\033[@" , KEY_INS ,		/* sounyu */
	"\033[A" , KEY_UP ,		/* up */
	"\033[B" , KEY_DOWN ,		/* down */
	"\033[C" , KEY_RIGHT ,		/* right */
	"\033[D" , KEY_LEFT ,		/* left */
	"\033[P" , KEY_DEL ,		/* sakujo */
#if H2050
	"\033[S" , KEY_BUP ,		/* box-up */
	"\033[T" , KEY_BDOWN ,		/* box-down */
#endif
	"\033[U" , KEY_JIPEJI ,		/* jipe-ji */
	"\033[V" , KEY_ZENPEJI ,	/* zenpe-ji */
	"\033[a" , KEY_RIGHT ,		/* right */
	"\033[f" , KEY_HOME ,		/* home */
	"\033[j" , KEY_LEFT ,		/* left */
/*	"\034"   , KEY_DUP , */		/* DUP */
/*	"\036"   , KEY_FM , */		/* ctrl + DUP (FM) */
	NULL,KEY_END,
};

int k_tab_cn = sizeof(k_table) / sizeof(struct KEYTABLE_TAG);

struct MOUSE_IN_TAG m_stat = { 0,0,0,0 };

static int key_buf[MAX_KEYIN];
static int kc = 0;
static int kp = 0;

int
key_in(flg)
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
	en = sizeof(k_table) / sizeof(struct KEYTABLE_TAG) - 1;
	for ( c = 0 ; c < MAX_KEYIN ; c++ ) {
		if ( flg ) key_buf[c] = getchr2();
		else key_buf[c] = getchr();
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

#define MAX_CHR 255
#define X_CHR_PIC 12
#define Y_CHR_PIC 26

static int chr_p = 0;
static int chr_cn = 0;
static unsigned char chr_buf[MAX_CHR];

#ifdef SIGWINCH
static int signal_winch = FALSE;
extern int t_row,t_column;	/* screen row and column width */

void
gettsize()
{
/*	int r,c;
	char tcbuf[1024];
	char *vt_type;

	signal(SIGWINCH,gettsize);

	if ( (vt_type = getenv("TERM")) == NULL ) {
		return;
	}
	if ( tgetent(tcbuf,vt_type) != 1) {
		return;
	}

	r = tgetnum("li");
	c = tgetnum("co");
	if ( r != -1 && c != -1 ) {
		t_row = r;
		t_column = c;
	}

	signal_winch = TRUE;

	return;
*/
	struct winsize tsize;

	signal(SIGWINCH,gettsize);

	if ( ioctl(2, TIOCGWINSZ, &tsize) != -1 ){
		t_row = tsize.ws_row;
		if ( t_row <= 0 ) t_row = 24;
		t_column = tsize.ws_col;
		if ( t_column <= 0 ) t_column = 80;
	}

	signal_winch = TRUE;

	return;
}
#endif

int
getchr()
{
	fd_set rdes;
	struct timeval tv;
	int cn;
	int c,x,y;

	while ( TRUE ) {
		while ( chr_p >= chr_cn ) {
			FD_ZERO(&rdes);
			FD_SET(0,&rdes);
			tv.tv_sec = 5;
			tv.tv_usec = 0;
			cn = select(1,&rdes,(fd_set *)0,(fd_set *)0
				,(struct timeval *)&tv);
#ifdef SIGWINCH
			if ( cn == -1 && errno == EINTR && signal_winch ) {
				signal_winch = FALSE;
				return KEY_SIGWINCH;
			}
#endif
			if ( cn <= 0 ) continue;

			chr_cn = read(0,chr_buf,MAX_CHR);
			chr_p = 0;
		}
		if ( chr_cn >= chr_p+4 && chr_buf[chr_p] == 0x1b
			&& chr_buf[chr_p+1] == 0x25
			&& chr_buf[chr_p+2] == 0x35
			&& chr_buf[chr_p+3] == 0x55 ) {
			chr_p += 4;
			m_stat.stat = chr_buf[chr_p+1];
			x = m_stat.x;
			y = m_stat.y;
			m_stat.x = chr_buf[chr_p+2] * 256 + chr_buf[chr_p+3];
			m_stat.y = chr_buf[chr_p+4] * 256 + chr_buf[chr_p+5];
			m_stat.x /= X_CHR_PIC;
			m_stat.y /= Y_CHR_PIC;
			chr_p += (chr_buf[chr_p] + 1);
			if ( m_stat.stat == MOUSE_DRUG ) {
				if ( (m_stat.st & MOUSE_DRUG) && x == m_stat.x
					&& y == m_stat.y ) continue;
				m_stat.st |= MOUSE_DRUG;
			} else m_stat.st &= ~MOUSE_DRUG;
			switch ( m_stat.stat ) {
				case MOUSE_L_ON :
					m_stat.st |= MOUSE_L_ON;
					break;
				case MOUSE_R_ON :
					m_stat.st |= MOUSE_R_ON;
					break;
				case MOUSE_L_OFF :
					m_stat.st &= ~MOUSE_L_ON;
					break;
				case MOUSE_R_OFF :
					m_stat.st &= ~MOUSE_R_ON;
					break;
			}
			return KEY_MOUSE;
		} else break;
	}

	return chr_buf[chr_p++];
}

int
getchr2()
{
	int ky,dum;

	while ( TRUE ) {
		ky = getchr();
		if ( ky != KEY_MOUSE ) break;
		if ( m_stat.stat == MOUSE_L_ON ) {
			ky = 0x0d;
			while ( !(getchr() == KEY_MOUSE
				&& m_stat.stat == MOUSE_L_OFF) );
			break;
		} else if ( m_stat.stat == MOUSE_R_ON ) {
			ky = 0x1b;
			while ( !(getchr() == KEY_MOUSE
				&& m_stat.stat == MOUSE_R_OFF) );
			break;
		}
	}

	return ky;
}

int
src_ky(str)
char *str;
{
	int c,c2,cn,st;

	for ( cn = 0 ; k_table[cn].func != KEY_END ; cn++ );
	c = src_ky2(str,0,cn-1);
	if ( k_table[c].func != KEY_END
		&& strcmp(str,k_table[c].key) == 0 ) {
		return k_table[c].func;
	}

	return 0;
}

int
src_ky2(str,st,en)
char *str;
int st,en;
{
	int p,res;

	if ( st >= en ) return st;
	p = st + (en - st)/2;
	if ( (res = strcmp(str,k_table[p].key)) == 0 ) return p;
	if ( res > 0 ) {
		return src_ky2(str,p+1,en);
	} else {
		return src_ky2(str,st,p-1);
	}
}

flush_keybuf()
{
#if H2050
	ioctl(0,TCFLSH,0);
#endif
}
