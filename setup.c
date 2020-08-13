/*
	File Utility ( Setup Module )

	Author	T.Tashiro (Nifty PDC02432)	1991-02-18	Ver 1.0
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
#if MINIX
#  undef NULL
#endif
#include <string.h>
#include <sys/types.h>
#if MINIX
#  undef NULL
#  include <stdlib.h>
#else
#  if !(NEWS3400 | I386BSD)
#    include <malloc.h>
#    include <memory.h>
#  endif
#  if I386BSD
#    include <sys/malloc.h>
#    include <memory.h>
#  endif
#endif
#include <sys/stat.h>
#include "key.h"
#include "fu.h"

/***************************************************
	Setup Key-Command,Command menu
****************************************************/
int
setup(fn)
char *fn;
{
	FILE *fp;
	char *p,buf[255],temp[255],key[20],flag[20],*get_setup();
	int tb,ky,comc;

	if ( ( fp = fopen(fn,"r") ) == NULL ) return TRUE;
	comc = 0;
	while ( fgets(buf,255,fp) != NULL ) {
		if ( buf[0] == '#' ) {
			if ( strncmp(buf,"#com",4) != 0 ) continue;
			comc += get_m_command(comc,buf);
		} else {
			p = get_setup(buf,key,20,FALSE);
			p = get_setup(p,flag,20,FALSE);
			p = get_setup(p,temp,80,TRUE);
			ky = get_keycode(key);
			if ( (tb = get_fnccode(ky,key)) < 0 ) continue;
			set_func_cmd(tb,temp,flag);
		}
	}
	if ( comc ) {
		com[comc].str = NULL;
		com[comc].key = com[comc].x = com[comc].y = com[comc].len = 0;
	}
	fclose(fp);

	return FALSE;
}

/***************************************************
	Read Command Menu
****************************************************/
int
get_m_command(comc,buf)
int comc;
char *buf;
{
	int c,ln;
	char *p,*str;

	buf += 4;
	c = 0;
	while ( comc < MAX_MCOM && *buf != '\0' ) {
		while ( *buf != '\042' && *buf != '\0' ) ++buf;
		if ( *buf == '\0' ) break;
		p = ++buf;
		for ( ln = 0 ; *buf != '\042' && *buf != '\0' ; ++buf ) ++ln;
		if ( *buf != '\0' ) {
			if ( (str = (char *)malloc(ln+1)) == NULL ) break;
			if ( ln > 0 ) memcpy(str,p,ln);
			str[ln] = '\0';
			com[comc].str = str;
			com[comc].key = KEY_MCOM1 + comc;
			com[comc].x = com[comc].y = com[comc].len = 0;
			++comc;
			++c;
			++buf;
		}
	}
	return c;
}

/***************************************************
	Get Setup Parameter
****************************************************/
char *
get_setup(p,buf,ln,f)
int ln,f;
char *p,*buf;
{
	int c;

	while ( *p == ' ' || *p == '\t' ) ++p;
	c = 0;
	while ( *p != '\0' && *p != '\n' && c < ln-1 ) {
		if ( !f && (*p == ' ' || *p == '\t') ) break;
		*(buf++) = *(p++);
		++c;
	}
	*buf = '\0';
	while ( *p != '\0' && *p != '\n' ) {
		if ( !f && (*p == ' ' || *p == '\t') ) break;
		++p;
	}

	return p;
}

/***************************************************
	Get Keycode
****************************************************/
int
get_keycode(key)
char *key;
{
	int ky,c,c2,p;
	char str[5];

	if ( key[0] == '\42' ) {
		convert_keystr(key,str);
		strcpy(key,str);
		return ( src_ky(key) );
	} else {
		for ( c = 0 ; kname[c].ky != 0 ; c++ )
			if ( strcmp(kname[c].kname,key) == 0 ) break;
		ky = kname[c].ky;
	}

	return ky;
}

/***************************************************
	Convert C Formed Key String to Character
****************************************************/
convert_keystr(key,str)
char *key,*str;
{
	int c,c2,p,ky;
	char nm[4];

	for ( c = 0 , p = 1 ; c < 4 ; c++ ) {
		if ( key[p] == '\42' || key[p] == '\0' ) break;
		if ( key[p] == '\\' ) {
			++p;
			if ( '0' <= key[p] && key[p] <= '9' ) {
				for ( c2 = 0 ; c2 < 3 ; c2++ )
					if ( key[p] < '0' || key[p] > '9' )
						break;
					else nm[c2] = key[p++];
				nm[c2] = '\0';
				sscanf(nm,"%o",&ky);
				str[c] = ky;
			} else str[c] = key[p++];
		} else	str[c] = key[p++];
	}
	str[c] = '\0';

	return;
}

/***************************************************
	Get Command Code
****************************************************/
int
get_fnccode(ky,key)
int ky;
char *key;
{
	int c;

	for ( c = 0 ; key_func[c].kcode >= 0 ; c++ ) {
		if ( ky != 0 && key_func[c].kcode == ky ) return c;
		if ( ky == 0 && key_func[c].kcode == 0
			&& strcmp(key_func[c].key,key) == 0 ) return c;
		
	}

	if ( c >= MAX_KEY_FUNC - 1 ) return -1;
	key_func[c].key = NULL;
	if ( ky == 0 ) {
		key_func[c].key = (char *)malloc(sizeof(char)*(strlen(key)+1));
		if ( key_func[c].key == NULL ) {
			fprintf(stderr,"%s:insufficient memory !\n",prog_name);
			return -1;
		}
		strcpy(key_func[c].key,key);
	}
	key_func[c].kcode = ky;
	key_func[c].func = -1;
	key_func[c+1].kcode = key_func[c+1].func = -1;
	key_func[c+1].key = NULL;

	return c;
}

/***************************************************
	Set Command Code
****************************************************/
set_func_cmd(tb,temp,flag)
int tb;
char *temp,*flag;
{
	int cn,c;

	if ( temp[0] != '$' ) {
		for ( cn = 0 ; func_cmd[cn].flg >= 0 ; cn++ );
		if ( cn >= MAX_FUNC_CMD - 1 ) return;
		func_cmd[cn].temp = (char *)malloc(sizeof(char)*(strlen(temp)+1));
		if ( func_cmd[cn].temp == NULL ) {
			fprintf(stderr,"%s:insufficient memory !\n",prog_name);
			return;
		}
		key_func[tb].func = cn;
		func_cmd[cn].func = NULL;
		strcpy(func_cmd[cn].temp,temp);
		func_cmd[cn].flg = atoi(flag);

		func_cmd[cn+1].func = NULL;
		func_cmd[cn+1].temp = NULL;
		func_cmd[cn+1].flg = -1;
	} else {
		for ( c = 0 ; fnc_name[c] != NULL ; c++ )
			if ( strcmp(fnc_name[c],&temp[1]) == 0 ) break;
		if ( fnc_name[c] == NULL ) return;
		if ( c == FUNC_NOP ) {	/* Delete entry.*/
/* if you nedded insert 'free(key_func[].key)' sentence
	but it is confusued you to including static and dynamic area */
			c = tb;
			do {
				memcpy((char *)&key_func[c]
					,(char *)&key_func[c+1]
					,sizeof(struct KEY_FUNC_TAG));
			} while ( key_func[c++].kcode >= 0 && c < MAX_KEY_FUNC );
		} else key_func[tb].func = c;
	}

	return;	
}
