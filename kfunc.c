/*
	File Utility ( Key Func )

	Author	T.Tashiro (Nifty PDC02432)	1992-04-13	Ver 1.00
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
#include "key.h"
#include "fu.h"

int sel_file()
{
	int fc;

#if !XWINDOW
	t_clrcur();
#endif
	dsp_fl();
	dsp_com_mes();

	while ( TRUE ) {
		dsp_fl2(curp,REV_DISP);
		fc = func_in(FALSE,TRUE);
		xt_normal();
		dsp_fl2(curp,NORM_DISP);
		if ( fc & FUNC_MASK )
			com_exe(fc & ~(FUNC_MASK));
	}
}

int
func_in(flg,is_x)
int flg;		/* TRUE -> if ( ky == MOJI ) return ky; */
int is_x;		/* is_xwindow ? */
{
	int ky,c;

#if XWINDOW
	if ( is_x ) ky = xkey_in(flg);
	else ky = key_in(flg);
#else
	ky = key_in(flg);
#endif
	if ( ky >= 0x20 && ky < 0x100 && ky != 0x7f && flg ) return ky;

	if ( ky >= 0x100 ) {	/* Special Keys */
		for ( c = 0 ; key_func[c].kcode >= 0 ; c++ ) {
			if ( key_func[c].kcode == ky ) {
				if ( key_func[c].func < 0 ) return ky;
				return ( key_func[c].func | FUNC_MASK );
			}
		}
	} else {		/* Normal Keys */
		for ( c = 0 ; key_func[c].kcode >= 0 ; c++ )
			key_func[c].flg = TRUE;
		return fnc_in2(flg,ky,is_x);
	}
	return ky;
}

int
fnc_in2(flg,ky,is_x)
int flg,ky,is_x;
{
	int key,c,cn,f;

	key = ky;
	cn = 0;
	while ( TRUE ) {
		f = FALSE;
		for ( c = 0 ; key_func[c].kcode >= 0 ; c++ ) {
			if ( key_func[c].flg && key_func[c].key != NULL
				&& key_func[c].key[cn] == ky ) {
				f = TRUE;
				if ( cn+1 >= MAX_KEYIN
					|| key_func[c].key[cn+1] == '\0' )
					return ( key_func[c].func | FUNC_MASK );
			} else key_func[c].flg = FALSE;
		}
		if ( !f ) break;
		if ( ++cn >= MAX_KEYIN ) break;
#if XWINDOW
		if ( is_x ) ky = xkey_in(flg);
		else ky = key_in(flg);
#else
		ky = key_in(flg);
#endif
	}
	return key;
}

set_sel(cp)
int cp;
{
	fent[cp].sel = ++maxsel;
}

reset_sel(cp)
int cp; 
{
	int c;

	for ( c = 0 ; c < dpc ; c++ ) {
		if ( fent[c].sel > fent[cp].sel ) --fent[c].sel;
	}
	--maxsel;
	fent[cp].sel = 0;
}

quit_fu()
{
#if XWINDOW
	x_close();
#endif
	trmdef();
#if !(XWINDOW)
	t_loc(X_WIDTH-1,Y_WIDTH-1);
#endif
	printf("\n");
	t_dspcur();
	write_history();
	exit(0);
}

k_mouse()
{
	int c,x,y,p,ky;

	if ( m_stat.stat != MOUSE_R_ON && m_stat.stat != MOUSE_L_ON
		&& m_stat.stat != MOUSE_DRUG ) return;
	if ( m_stat.y < 0 ) return;
	else if ( m_stat.y > 0 && m_stat.y <= DSP_ROW ) { /* File Disp Area */
		if ( m_stat.x >= X_WIDTH - 2 ) {/* Scroll Bar */
			if ( m_stat.stat == MOUSE_L_ON ) {
				if ( m_stat.y <= DSP_ROW/2 ) k_sup();
				else	k_sdown();
			}
		} else {			/* File Area */
			x = m_stat.x / sc_column[sc_mode];
			y = m_stat.y - 1;
			p = x * DSP_ROW + y + dp;
			if ( p < dpc ) {
				k_ms_selected(p);
			}
		}
	} else if ( m_stat.stat == MOUSE_L_ON ) {	/* Other Commands */
		for ( c = 0 ; com[c].str != NULL ; c++ ) {
			if ( m_stat.y == com[c].y && m_stat.x >= com[c].x
				&& m_stat.x < com[c].x + com[c].len ) {
				break;
			}
		}
		while ( !(xgetchr() == KEY_MOUSE
			&& m_stat.stat == MOUSE_L_OFF) );
		if ( com[c].str != NULL ) {
			ky = com[c].key;
			for ( c = 0 ; key_func[c].kcode >= 0 ; c++ )
				if ( key_func[c].kcode == ky ) break;
			if ( key_func[c].kcode >= 0 && key_func[c].func >= 0 )
				com_exe(key_func[c].func);
		} else if ( m_stat.y == DSP_ROW + 1 ) {
			if ( X_WIDTH >= TITLEMINX && m_stat.x >= 3 && m_stat.x <= 34 )
				dsp_fu_message();
			else if ( X_WIDTH >= TITLEMINX && m_stat.x >= X_WIDTH - 12 && m_stat.x <= X_WIDTH - 4 )
				dsp_personal_message();
			else if ( X_WIDTH < TITLEMINX && m_stat.x >= 3 && m_stat.x <= 9 )
				dsp_fu_message();
			else if ( X_WIDTH < TITLEMINX && m_stat.x >= X_WIDTH - 6 && m_stat.x <= X_WIDTH - 4 )
				dsp_personal_message();
		} else if ( m_stat.y == find_y ) {
			f_find();
		} else if ( m_stat.y == 0 ) {
			com_change_dir();
		}
	}
}

k_ms_selected(p)
int p;
{
	int ft;

	ft = fent[p].st_mode & FILE_TYPE;
	if ( m_stat.stat == MOUSE_L_ON ) {	/* Left Button was Pushed */
		if ( p != curp ) {
			curp = p;
		} else if ( ft == FILE_DIR ) {
			while ( !(xgetchr() == KEY_MOUSE
				&& m_stat.stat == MOUSE_L_OFF) );
			curp = p;
			change_dir();
		} else if ( ft == FILE_NORM1 || ft == FILE_NORM2 ) {
			if ( fent[curp].sel ) {
				while ( !(xgetchr() == KEY_MOUSE
					&& m_stat.stat == MOUSE_L_OFF) );
				type_file();
				dsp_com_mes();
			} else {
				set_sel(curp);
				dsp_fl2(curp,REV_DISP);
			}
		}
	} else if ( m_stat.stat == MOUSE_DRUG && (m_stat.st & MOUSE_L_ON) ) {
		curp = p;
		if ( (ft == FILE_NORM1 || ft == FILE_NORM2)
			&& !fent[curp].sel ) {
			set_sel(curp);
			dsp_fl2(curp,REV_DISP);
		}
	} else {				/* Right Button was Pushed */
		curp = p;
		if ( fent[curp].sel ) {
			reset_sel(curp);
			dsp_fl2(curp,REV_DISP);
		}
	}
}

static char *fu_message[] = {
	"+------------------------------------------------------------+",
	"|                                                            |",
	"|   F i l e  M a n a g e m e n t  U t i l i t y    Ver3.20   |",
	"|                                                            |",
	"| Licenced Material of T.Tashiro                             |",
	"| Reproduction, use, modification,disclosure otherwise than  |",
	"| permitted in the licence agreement is strictly prohibited. |",
	"| Copyright (c) T.Tashiro 1991-2005.    All rights reserved. |",
	"+------------------------------------------------------------+",
	NULL
};

dsp_fu_message()
{
	int x,y,c;

	for ( c = 0 ; fu_message[c] != NULL ; c++ );
	y = (DSP_ROW - c) / 2;
	x = (X_WIDTH - strlen(fu_message[0])) / 2;
	if ( x < 2 || y < 2 ) return;
	for ( c = 0 ; fu_message[c] != NULL ; c++, y++ ) {
		xt_loc(x,y);
		xt_puts(fu_message[c]);
	}
	xgetchr2();
	dsp_fl();
	dsp_com_mes();

	return;
}

static char *per_message[] = {
	"+-----------------------------+",
	"|                             |",
	"|      T . T a s h i r o      |",
	"|                             |",
	"|  Blood Type : O             |",
	"|  Nifty-ID   : PDC02432      |",
	"|                             |",
        "+-----------------------------+",
	NULL
};

dsp_personal_message()
{
	int x,y,c;

	for ( c = 0 ; per_message[c] != NULL ; c++ );
	y = DSP_ROW - c;
	x = X_WIDTH - strlen(per_message[0]) - 4;
	if ( x < 2 || y < 2 ) return;
	for ( c = 0 ; per_message[c] != NULL ; c++, y++ ) {
		xt_loc(x,y);
		xt_puts(per_message[c]);
	}
	xgetchr2();
	dsp_fl();
	dsp_com_mes();

	return;
}

com_change_dir()
{
	char temp[256],*p;
	char temp2[512];
	char *getenv();
	extern int need_redraw;

	xt_loc(0,0);
	*temp = '\0';
	xt_loc(17,0);
	if ( xget_str(temp,60,temp2,"Current Dir") ) {
		if ( need_redraw ) dsp_fl();
		dsp_com_mes();
		return;
	}
	p = temp;
	if ( *p == '\0' )
		if ( (p = getenv("HOME")) == NULL )
			return TRUE;
	h_chdir(p);
	get_file_ent();
	if ( curp >= dpc ) curp = ( 0 > dpc-1 )?0:(dpc-1);
	if ( curp < dp || curp >= dp + DSP_CN )
		dp = ( curp / DSP_CN ) * DSP_CN;
	dsp_fl();
	dsp_com_mes();

	return;
}

k_up()
{
	--curp;
	if ( curp < 0 ) curp = 0;
	if ( curp < dp ) {
		dp -= DSP_CN;
		dsp_fl();
		dsp_com_mes();
	}
	return;
}

k_down()
{
	++curp;
	if ( curp >= dpc )
	curp = (0 == dpc)?0:(dpc-1);
	if ( curp >= dp + DSP_CN ) {
		dp += DSP_CN;
		dsp_fl();
		dsp_com_mes();
	}
	return;
}

k_right()
{
	if ( (curp - dp) / DSP_ROW < fname_column - 1
		&& curp + DSP_ROW < dpc ) {
		curp += DSP_ROW;
	}
	return;
}

k_left()
{
	if ( curp - dp >= DSP_ROW ) {
		curp -= DSP_ROW;
	}
	return;
}

k_sup()
{
	if ( dp - DSP_CN >= 0 ) {
		dp -= DSP_CN;
		curp -= DSP_CN;
		dsp_fl();
		dsp_com_mes();
	} else {
		curp = 0;
	}
	return;
}

k_sdown()
{
	if ( dp + DSP_CN < dpc ) {
		dp += DSP_CN;
		curp += DSP_CN;
		if ( curp >= dpc ) curp = (dpc - 1 >= 0)?(dpc - 1):0;
		dsp_fl();
		dsp_com_mes();
	} else {
		curp = ( dpc - 1 < 0 )?0:( dpc - 1 );
	}
}

k_home()
{
	if ( dp - DSP_CN >= 0 ) {
		dp = curp = 0;
		dsp_fl();
		dsp_com_mes();
	} else {
		curp = 0;
	}
	return;
}

k_end()
{
	if ( dp + DSP_CN < dpc ) {
		dp = (dpc / (DSP_CN-1)) * DSP_CN;
		curp = ( dpc - 1 < 0 )?0:( dpc - 1 );
		dsp_fl();
		dsp_com_mes();
	} else {
		curp = ( dpc - 1 < 0 )?0:( dpc - 1 );
	}
}

k_sp()
{
	int ft;

	if ( curp < dpc ) {
		ft = fent[curp].st_mode & FILE_TYPE;
		if ( ft == FILE_NORM1 || ft == FILE_NORM2 ) {
			if ( fent[curp].sel ) reset_sel(curp);
			else set_sel(curp);
		}
	}
	dsp_fl2(curp,NORM_DISP);
	k_down();

	return;
}

k_ret()
{
	int ft,c,arc_type;
	char temp[MAX_STR];

	ft = fent[curp].st_mode & FILE_TYPE;
	if ( ft == FILE_DIR ) change_dir();
	else if ( ft == FILE_NORM1 || ft == FILE_NORM2 ) {
		if ( (arc_type = check_arcfile(fent[curp].d_name)) >= 0 ) {
			arc_ls2(fent[curp].d_name,arc_type);
		} else if ( pager ) {
			sprintf(temp,"%s %s",pager,"%1");
			f_shell(temp,ALL_FILE_STAY);
		} else type_file();
		dsp_com_mes();
	}

	return;
}

f_rdraw()
{
	dsp_fl();
	dsp_com_mes();
}

k_all_sel()
{
	int ft;
	int c,sel;

	for ( c = 0 ; c < dpc ; c++ )
		if ( fent[c].sel ) break;

	if ( c >= dpc ) sel = 1;	/* All Select */
	else sel = 0;			/* All Deselect */

	maxsel = 0;

	for ( c = 0 ; c < dpc ; c++ ) {
		ft = fent[c].st_mode & FILE_TYPE;
		if ( ft == FILE_NORM1 || ft == FILE_NORM2 )
			if ( sel == 0 ) fent[c].sel = 0;
			else fent[c].sel = ++maxsel;
	}

	dsp_fl();
	dsp_com_mes();

	return;
}

scr_1()
{
	scr_set(1);
}

scr_2()
{
	scr_set(2);
}

scr_3()
{
	scr_set(3);
}

scr_4()
{
	scr_set(4);
}

scr_set(cl)
int cl;
{
	int sm,fc;

	if ( sc_mode == cl ) return;
	sm = cl;
	fc = (X_WIDTH - 2) / sc_column[sm];
	if ( fc <= 0 ) return;
	sc_mode = sm;
	fname_column = fc;
	dp = ( curp / DSP_CN ) * DSP_CN;
	dsp_fl();
	dsp_com_mes();

	return;
}

change_dir()
{
	int c,ln,ln2;
	char cwd2[DIR_LEN];

	strcpy(cwd2,cwd);

	h_chdir(fent[curp].d_name);
	dp = dpc = curp = 0;
	get_file_ent();
	if ( dpc >= 2 && strcmp(fent[1].d_name,"..") == 0 ) curp = 1;
	ln = strlen(cwd);
	ln2 = strlen(cwd2);
	if ( ln2 > ln ) {
		if ( strcmp(cwd,"/") == 0 ) ln = 0;
		for ( c = 0 ; c < dpc ; c++ ) {
			if ( ((fent[c].st_mode & FILE_TYPE) == FILE_DIR)
				&& strcmp(&cwd2[ln+1],fent[c].d_name) == 0 ) {
				curp = c;
				break;
			}
		}
		dp = ( curp / DSP_CN ) * DSP_CN;
	}

	dsp_fl();
	dsp_com_mes();
}

f_winch()
{
	int fc;

	fc = (X_WIDTH - 2) / sc_column[sc_mode];
	if ( fc <= 0 ) return;
	fname_column = fc;
	dp = ( curp / DSP_CN ) * DSP_CN;
	dsp_fl();
	dsp_com_mes();

	return;
}

