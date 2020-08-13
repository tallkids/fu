/*
	File Utility ( Find File Command )

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

f_find()
{
	char temp[MAX_F_TEMP];
	int flg;
	extern int need_redraw;

	xt_loc(0,find_y);
	xt_erase_line();
	xt_loc(0,find_y);
	*temp = '\0';
	if ( xget_str(temp,MAX_F_TEMP,"Find"," : ") ) {
		if ( need_redraw ) dsp_fl();
		dsp_com_mes();
		return;
	}
	if ( *temp == '\0' ) {
		strcpy(f_temp,"*");
	} else	strcpy(f_temp,temp);

	get_file_ent();
	if ( curp >= dpc ) curp = ( 0 > dpc-1 )?0:(dpc-1);
	if ( curp < dp || curp >= dp + DSP_CN )
		dp = ( curp / DSP_CN ) * DSP_CN;
	dsp_fl();

	dsp_com_mes();
	return;
}
