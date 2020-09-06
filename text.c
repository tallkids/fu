/*
	File Utility ( Text Screen Library )

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
#include <sys/types.h>
#if BEOS
#  include <termios.h> 
#elif (H2050 | HP9000)
#  include <termio.h> 
#  include <termcap.h> 
#endif
#if MACOS
#  include <curses.h>
#  include <term.h>
#endif
#if I386BSD
#  include <sgtty.h>
#  include <sys/ioctl.h>
#endif
#if SUNSPARC | MINIX
#  include <sgtty.h>
#endif
#include <signal.h> 
#include <fcntl.h>
#if H2050
#  include <2050/window.h>
#endif

#define FALSE 0
#define TRUE (!FALSE)

int ascii = FALSE;	/* flag for kanji */
int t_row = 24;		/* Screen Row Width */
int t_column = 80;	/* Screen Column Width */

#define TCAPMAX 1024
char tcapbuf[TCAPMAX];
char *LOC,*EOL,*CUP,*CUB,*CUF,*REV,*NOR,*DCR,*CCR,*CLS
	,*SMK,*RMK;

#if (H2050 | HP9000)
 struct	termio otermio;		/* original terminal characteristics */
 struct	termio ntermio;		/* new terminal characteristics */
#endif

#if I386BSD
#  define gtty(fd,ld)	ioctl((fd),TIOCGETP,(ld))
#  define stty(fd,ld)	ioctl((fd),TIOCSETP,(ld))
#endif

#if SUNSPARC | MINIX | I386BSD
 struct sgttyb ostate;		/* original tty state */
 struct sgttyb nstate;		/* new tty  mode */
 struct tchars otchars;	/* original terminal special character set */
 struct tchars ntchars = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
#define	TBUFSIZ	128 
 char tobuf[TBUFSIZ];		/* terminal output buffer */
#endif

extern char *prog_name;

/***************************************************
	Terminal Setup for Direct Input
***************************************************/
trmset()
{
#if (H2050 | HP9000)
	short incode,mmode;

	signal(SIGINT,SIG_IGN);
	ioctl(0, TCGETA, &otermio);	/* get old settings */
	ntermio.c_iflag = 0;		/* set new settings */
	ntermio.c_oflag = 0;
	ntermio.c_cflag = otermio.c_cflag;
	ntermio.c_lflag = 0;
	ntermio.c_line = otermio.c_line;
	ntermio.c_cc[VMIN] = 1;
	ntermio.c_cc[VTIME] = 0;
	ioctl(0, TCSETA, &ntermio);
#if H2050
	/* Set Terminal Mode for Mouse */
	incode = W_ICASCII | W_ICJIS8 | W_ICSFTJIS | W_ICAPL | W_ICFUNC
		| W_ICMOUSE ;
	ioctl(0,TICODE,&incode);
	mmode = W_BUTTON;
	ioctl(0,TIMOUSEM,&mmode);
#endif
#endif
#if SUNSPARC | MINIX | I386BSD
	gtty(0, &ostate);			/* get old state */
	gtty(0, &nstate);			/* get base of new state */
	nstate.sg_flags |= RAW;
	nstate.sg_flags &= ~(ECHO|CRMOD);	/* no echo */
	stty(0, &nstate);
	ioctl(0, TIOCGETC, &otchars);		/* get old characters */
	ioctl(0, TIOCSETC, &ntchars);
#if !(MINIX | PANIX)
	setbuffer(stdout, &tobuf[0], TBUFSIZ);
#endif
#if PANIX
	setbuf(stdout, &tobuf[0], TBUFSIZ);
#endif
	signal(SIGTSTP,SIG_DFL);
#endif
	if ( SMK != NULL ) t_puts2(SMK);
}

trmset2()
{
#if (H2050 | HP9000)
	short incode,mmode;

	signal(SIGINT,SIG_IGN);
	ioctl(0, TCGETA, &ntermio);
	ntermio.c_iflag = 0;		/* set new settings */
	ntermio.c_oflag = 0;
	ntermio.c_lflag = 0;
	ntermio.c_cc[VMIN] = 1;
	ntermio.c_cc[VTIME] = 0;
	ioctl(0, TCSETA, &ntermio);
#  if H2050
	/* Set Terminal Mode for Mouse */
	incode = W_ICASCII | W_ICJIS8 | W_ICSFTJIS | W_ICAPL | W_ICFUNC
		| W_ICMOUSE ;
	ioctl(0,TICODE,&incode);
	mmode = W_BUTTON;
	ioctl(0,TIMOUSEM,&mmode);
#  endif
#endif
#if SUNSPARC | MINIX | I386BSD
	gtty(0, &nstate);			/* get base of new state */
	nstate.sg_flags |= RAW;
	nstate.sg_flags &= ~(ECHO|CRMOD);	/* no echo */
	stty(0, &nstate);
	ioctl(0, TIOCSETC, &ntchars);
#  if !(MINIX | PANIX)
	setbuffer(stdout, &tobuf[0], TBUFSIZ);
#  endif
#  if PANIX
	setbuf(stdout, &tobuf[0], TBUFSIZ);
#  endif
	signal(SIGTSTP,SIG_DFL);
#endif 
	if ( SMK != NULL ) t_puts2(SMK);
}

/***************************************************
	Terminal Setup for Default I/O
***************************************************/
trmdef()
{
#if (H2050 | HP9000)
	short incode;

	ioctl(0, TCSETA, &otermio);	/* restore terminal settings */

#if H2050
	incode = W_ICASCII | W_ICJIS8 | W_ICSFTJIS | W_ICAPL | W_ICFUNC;
	ioctl(0,TICODE,&incode);
#endif
#endif
#if SUNSPARC | MINIX | I386BSD
	stty(0, &ostate);
	ioctl(0, TIOCSETC, &otchars);
#endif 
	signal(SIGINT,SIG_DFL);
	if ( RMK != NULL ) t_puts2(RMK);
}

/***************************************************
	Setup for Terminal Control Sequence
***************************************************/
t_init()
{
	char *getenv();
	char *t, *p, *tgetstr();
	char tcbuf[2048];
	char *vt_type;

	if ( (vt_type = getenv("TERM")) == NULL ) {
		fprintf(stderr,"%s:Please set TERM !",prog_name);
		exit(-1);
	}
	if ( tgetent(tcbuf, vt_type) != 1) {
		fprintf(stderr,"%s:Unknown terminal type %s !"
			,prog_name,vt_type);
		exit(-1);
	}

#ifdef SIGWINCH
	gettsize();
#else
	if ( (t_row = tgetnum("li")) == -1 ) {
		fprintf(stderr,"%s:termcap entry incomplete (lines)"
			,prog_name);
		exit(-1);
	}
	if ( t_row <= 0 ) t_row = 24;
 
	if ( (t_column = tgetnum("co")) == -1 ) {
		fprintf(stderr,"%s:Termcap entry incomplete (columns)"
			,prog_name);
		exit(-1);
	}
	if ( t_column <= 0 ) t_column = 80;
#endif

        p = tcapbuf;
	LOC = tgetstr("cm",&p);
	EOL = tgetstr("ce",&p);
	CUP = tgetstr("up",&p);
	CUB = tgetstr("le",&p);
	if ( CUB == NULL ) CUB = "\010";	/* for Sun */
	CUF = tgetstr("nd",&p);
#if I386BSD
	REV = tgetstr("so",&p);
#else
	REV = tgetstr("mr",&p);
#endif
	NOR = tgetstr("se",&p);
	CCR = tgetstr("vi",&p);
	DCR = tgetstr("ve",&p);
	CLS = tgetstr("cl",&p);
	SMK = tgetstr("ks",&p);
	RMK = tgetstr("ke",&p);

	if ( LOC == NULL || EOL == NULL || CUB == NULL || CUF == NULL
		|| REV == NULL || NOR == NULL || CLS == NULL ) {
		fprintf(stderr,"%s:Incomplete termcap entry",prog_name);
		exit(-1);
	}
	if ( DCR == NULL ) DCR = "\33[97l";
	if ( CCR == NULL ) CCR = "\33[97h";

	if ( p >= &tcapbuf[TCAPMAX] ) {
		fprintf(stderr,"%s:Terminal description too big !"
			,prog_name);
		exit(-1);
	}

	return;
}

/***************************************************
	Set Cursor Position to (x,y)
****************************************************/
t_loc(x,y)
int x,y;
{
        t_puts2(tgoto(LOC,x,y));
}

/************************************************************
	Erase to the End of Line from Cursor Position
*************************************************************/
t_erase_line()
{
	t_puts2(EOL);
}

/***************************************************
	Set Color Attribution
****************************************************/
/*
t_color(col)
int col;
{
	char buf[80];

	col = (col > 7)?(col+42):(col+30);
	sprintf(buf,"\33[%dm",col);
	t_puts(buf);
}
*/

/***************************************************
	Cursor One Row Up
****************************************************/
/*
t_cur_up()
{
	t_puts("\33[A");
}
*/

/***************************************************
	Cursor Backwards
****************************************************/
t_cur_backward(cn)
int cn;
{
	int c;

	for ( c = 0 ; c < cn ; c++ ) {
		t_puts2(CUB);
	}
}

/***************************************************
	Cursor Forward
****************************************************/
t_cur_forward(cn)
int cn;
{
	int c;

	for ( c = 0 ; c < cn ; c++ ) {
		t_puts2(CUF);
	}
}

/***************************************************
	Set Reverse/Normal Mode
****************************************************/
#define REVERSE TRUE
#define NORMAL FALSE

static int term_mode = NORMAL;

t_reverse()
{
#if HP9000
	t_puts2(REV);
#else
	if ( term_mode != REVERSE ) {
		t_puts2(REV);
	}
	term_mode = REVERSE;
#endif
}

t_normal()
{
#if HP9000
	t_puts2(NOR);
#else
	if ( term_mode != NORMAL ) {
		t_puts2(NOR);
	}
	term_mode = NORMAL;
#endif
}

/***************************************************
	Cursor Display Mode
****************************************************/
t_clrcur()
{
#if !HP9000
	t_puts2(CCR);
#endif
}

/***************************************************
	Cursor Not Display Mode
****************************************************/
t_dspcur()
{
#if !HP9000
	t_puts2(DCR);
#endif
}

/***************************************************
	Set Screen to Scroll Mode
****************************************************/
t_scron()
{
/*	t_puts("\33[99l"); */
}

/***************************************************
	Set Screen to No Scroll Mode
****************************************************/
t_scroff()
{
/*	t_puts("\33[99h"); */
}

/***************************************************
	Screen Clear
****************************************************/
t_cls()
{
	t_puts2(CLS);
}

/***************************************************
	Output One Character
****************************************************/
t_putc(ch)
int ch;
{
	fputc(ch,stdout);
}

/***************************************************
	Output String
****************************************************/
t_puts2(str)
char *str;
{
	tputs(str,1,t_putc);
	t_flush();
}

/***************************************************
	Output String (Kanji/Ascii)
****************************************************/
t_puts(str)
char *str;
{
	char *p;
	char buf[4096];

	if ( ascii ) {
		strcpy(buf,str);
		for ( p = buf ; *p != '\0' ; ++p )
			*p = ((*p & 0xff) > 0x80)?'?':*p;
		str = buf;
	}
	fputs(str,stdout);

	t_flush();
}

/***************************************************
	Flush Output Buffer
****************************************************/
t_flush()
{
	fflush(stdout);
}
