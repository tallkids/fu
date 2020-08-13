/*
	File Utility ( Cursor Jump Command )

	Author	T.Tashiro (Nifty PDC02432)	1991-07-16	Ver 1.0
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
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include "key.h"
#include "fu.h"

f_jump()
{
	int c;
	int ky;

	clr_mes_area();
	xt_loc(0,DSP_ROW+2);
	xt_reverse();
	if ( X_WIDTH >= 25 ) xt_puts("Please keyin 1 char.");
	else xt_puts("keyin char");
	xt_normal();
	xt_puts(" : ");
	ky = xgetchr2();

	if ( ky <= ' ' ) {
		beep();
		dsp_com_mes();
		return;
	}
	for ( c = curp + 1 ; ; c++ ) {
		if ( c >= dpc ) c = 0;
		if ( c == curp ) break;
		if ( fent[c].d_name[0] == ky ) break;
	}

	curp = c;
	if ( curp >= dp && curp < dp + DSP_CN ) {
		dsp_com_mes();
		return;
	}
	if ( curp >= dpc ) curp = ( 0 > dpc-1 )?0:(dpc-1);
	if ( curp < dp || curp >= dp + DSP_CN )
		dp = ( curp / DSP_CN ) * DSP_CN;
	dsp_fl();
	dsp_com_mes();

	return;
}
