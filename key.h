/*
	Header File for Key-Input Module

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

#define MAX_KEYIN		5
/* #define MAX_KEY_TAB		500 */

#define USER_KEY		0x300

#define MOUSE_L_ON		0x01
#define MOUSE_R_ON		0x02
#define MOUSE_L_OFF		0x06
#define MOUSE_R_OFF		0x07
#define MOUSE_DRUG		0x0c

#define KEY_MOUSE		0x100	/* Change Mouse Status */
#define KEY_MCOM1		0x101
#define KEY_MCOM2		0x102
#define KEY_MCOM3		0x103
#define KEY_MCOM4		0x104
#define KEY_MCOM5		0x105
#define KEY_MCOM6		0x106
#define KEY_MCOM7		0x107
#define KEY_MCOM8		0x108
#define KEY_MCOM9		0x109
#define KEY_MCOM10		0x10a
#define KEY_MCOM11		0x10b
#define KEY_MCOM12		0x10c
#define KEY_MCOM13		0x10d
#define KEY_MCOM14		0x10e
#define KEY_MCOM15		0x10f
#define KEY_MCOM16		0x110
#define KEY_MCOM17		0x111
#define KEY_MCOM18		0x112
#define KEY_MCOM19		0x113
#define KEY_MCOM20		0x114
#define KEY_MCOM21		0x115
#define KEY_MCOM22		0x116
#define KEY_MCOM23		0x117
#define KEY_MCOM24		0x118
#define KEY_MCOM25		0x119
#define KEY_MCOM26		0x11a
#define KEY_MCOM27		0x11b
#define KEY_MCOM28		0x11c
#define KEY_MCOM29		0x11d
#define KEY_MCOM30		0x11e
#define KEY_MCOM31		0x11f
#define KEY_MCOM32		0x120
#define KEY_MCOM33		0x121
#define KEY_MCOM34		0x122
#define KEY_MCOM35		0x123
#define KEY_MCOM36		0x124
#define KEY_MCOM37		0x125
#define KEY_MCOM38		0x126
#define KEY_MCOM39		0x127
#define KEY_MCOM40		0x128
#define KEY_EXPOSE		0x180
#define KEY_TORIKESI		0x201
#define KEY_DOWN		0x202
#define KEY_UP			0x203
#define KEY_KAKUTYOU		0x204
#define KEY_PA1			0x205
#define KEY_PA2			0x206
#define KEY_PA3			0x207
#define KEY_SCREEN		0x208
#define KEY_SRQ			0x209
#define KEY_PA4			0x20a
#define KEY_TYUDAN		0x20b
#define KET_TEST		0x20c
#define KEY_JIKKOU		0x20d
#define KEY_FIELD		0x20e
#define KEY_PRINT		0x20f
#define KEY_HENKANTAISHOU	0x210
#define KEY_FUNCTION		0x211
#define KEY_SAIHENKAN		0x212
#define KEY_S_FUNCTION		0x213
#define KEY_DATA		0x214
#define KEY_STOPPRINT		0x215
#define KEY_C_FUNCTION		0x216
#define KEY_S_HOME		0x217
#define KEY_S_UP		0x218
#define KEY_S_DOWN		0x219
#define KEY_S_RIGHT		0x21a
#define KEY_S_LEFT		0x21b
#define KEY_S_BUP		0x21c
#define KEY_S_BDOWN		0x21d
#define KEY_S_BRIGHT		0x21e
#define KEY_S_BLEFT		0x21f
#define KEY_S_ZENPEJI		0x220
#define KEY_S_JIPEJI		0x221
#define KEY_S_INS		0x222
#define KEY_S_DEL		0x223
#define KEY_C_HOME		0x224
#define KEY_C_UP		0x225
#define KEY_C_DOWN		0x226
#define KEY_C_RIGHT		0x227
#define KEY_C_LEFT		0x228
#define KEY_C_BUP		0x229
#define KEY_C_BDOWN		0x22a
#define KEY_C_BRIGHT		0x22b
#define KEY_C_BLEFT		0x22c
#define KEY_C_ZENPEJI		0x22d
#define KEY_C_JIPEJI		0x22e
#define KEY_C_INS		0x22f
#define KEY_C_DEL		0x230
#define KEY_PF1			0x231
#define KEY_PF2			0x232
#define KEY_PF3			0x233
#define KEY_PF4			0x234
#define KEY_PF5			0x235
#define KEY_PF6			0x236
#define KEY_PF7			0x237
#define KEY_PF8			0x238
#define KEY_PF9			0x239
#define KEY_PF10		0x23a
#define KEY_PF11		0x23b
#define KEY_PF12		0x23c
#define KEY_C_PF1		0x23d
#define KEY_C_PF2		0x23e
#define KEY_C_PF3		0x23f
#define KEY_C_PF4		0x240
#define KEY_C_PF5		0x251
#define KEY_C_PF6		0x252
#define KEY_C_PF7		0x253
#define KEY_C_PF8		0x254
#define KEY_C_PF9		0x255
#define KEY_C_PF10		0x256
#define KEY_C_PF11		0x257
#define KEY_C_PF12		0x258
#define KEY_BLEFT		0x259
#define KEY_BRIGHT		0x25a
#define KEY_INS			0x25b
#define KEY_DEL			0x25c
#define KEY_BUP			0x25d
#define KEY_BDOWN		0x25e
#define KEY_JIPEJI		0x25f
#define KEY_ZENPEJI		0x260
#define KEY_RIGHT		0x261
#define KEY_HOME		0x262
#define KEY_LEFT		0x263
#define KEY_DUP			0x264
#define KEY_FM			0x265
#define KEY_SIGWINCH		0x300
#define KEY_END			-1
/*
#define KEY_ESC2		0x1b
*/
#define KEY_ESC2		0x200

struct KEYTABLE_TAG {
	char *key;
	int func;
};

extern struct KEYTABLE_TAG k_table[];

struct MOUSE_IN_TAG {
	int stat,st;
	int x,y;
};

extern struct MOUSE_IN_TAG m_stat;
