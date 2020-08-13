/*
	File Utility ( Type File Command )

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
#include <sys/types.h>
#include <errno.h>
#include "key.h"
#include "fu.h"

type_file()
{
	int x,ln;
	FILE *fp;
	int dt,ky,dum;

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
	t_cls();
	t_loc(0,0);
#endif
	if ( ( fp = fopen(fent[curp].d_name,"r") ) != NULL ) {
		ln = x = ky = 0;
		while ( (dt = fgetc(fp)) != EOF ) {
			if ( dt == '\n' ) {
				fputc('\15',stdout);
				fputc(dt,stdout);
				++ln;
				x = 0;
			} else if ( dt < 0x20 && ( dt != 0x09 ) ) {
				fputc('?',stdout);
				++x;
			} else {
				if ( ascii )
					dt = ((dt & 0xff) > 0x80)?'?':dt;
				fputc(dt,stdout);
				if ( dt == 0x09 ) x = (( x + 8 ) / 8 ) * 8;
				else ++x;
			}
			if ( x >= t_column ) {
				++ln;
				x = 0;
			}
			if ( ln > t_row - 4 ) {
				t_puts("<< Enter Any Key >>");
				fputc('\15',stdout);
				ky = getchr2();
				t_puts("                   ");
				fputc('\15',stdout);
				if ( ky == 'q' || ky == 'Q'
					|| ky == '\033' ) break;
				if ( ky != ' ' ) ln = 0;
				else ln = t_row - 5;
				x = 0;
			}
		}
		if ( ky != 'q' && ky != 'Q' && ky != '\033'   ) {
			t_puts("<< Enter Any Key >>");
			getchr2();
		}
		fclose(fp);
	}
	dsp_fl();

#if XWINDOW
	t_puts("\015\012");
	exit();
#else
	dsp_com_mes();
#endif

	return;
}


