#include "version.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "readmap.h"
#include "object.h"
#include "char.h"
#include "char_base.h"
#include "chatmagic.h"
#include "battle.h"
#include "log.h"
#include "configfile.h"
#include "lssproto_serv.h"
#include "saacproto_cli.h"
#include "family.h"
#include "net.h"

extern int channelMember[FAMILY_MAXNUM][FAMILY_MAXCHANNEL][FAMILY_MAXMEMBER];

#ifdef _TALK_ACTION
void TalkAction(int charaindex, char *message);
#endif

#ifdef _GM_ITEM
static BOOL player_useChatMagic( int charaindex, char* data, BOOL isDebug);
#endif
/*------------------------------------------------------------
 * 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷  锟斤拷末锟斤拷锟斤拷
 ------------------------------------------------------------*/
#define DEBUGCDKEYNUM 100
struct tagDebugCDKey {
	int use;
	char cdkey[9];
};
static struct tagDebugCDKey DebugCDKey[DEBUGCDKEYNUM];

/*====================锟斤拷锟斤拷锟斤拷锟斤拷  芊====================*/
typedef void (*CHATMAGICFUNC)(int,char*);
typedef struct tagCHAR_ChatMagicTable
{
	char*			magicname;
	CHATMAGICFUNC	func;
	BOOL            isdebug;
	int             hash;
	int				level;
	char*			usestring;
}CHAR_ChatMagicTable;

static CHAR_ChatMagicTable CHAR_cmtbl[]={
	//锟斤拷锟斤拷师专锟斤拷
	{ "programming_engineer",	CHAR_CHAT_DEBUG_engineer,	TRUE,	0,	3, ""},
	{ "petlevelup",	CHAR_CHAT_DEBUG_petlevelup,	TRUE,	0,	2, "锟斤拷锟斤拷锟斤拷锟斤拷 锟饺硷拷 (锟剿猴拷)"},
	{ "petexpup",	CHAR_CHAT_DEBUG_petexpup,	TRUE,	0,	2, "锟斤拷锟斤拷锟斤拷锟斤拷 锟斤拷锟斤拷 (锟剿猴拷)"},
	{ "help",			CHAR_CHAT_DEBUG_help,				TRUE,	0,	1, "指锟斤拷/all"},
#ifdef _EQUIT_NEGLECTGUARD
	{ "setneguard",		CHAR_CHAT_DEBUG_setneguard,			TRUE,	0,	3, "waei"},
#endif
	//锟斤拷锟斤拷锟斤拷锟斤拷
	{ "info",			CHAR_CHAT_DEBUG_info,			TRUE,	0,	1, "锟斤拷值"},
	{ "level",			CHAR_CHAT_DEBUG_level,			TRUE,	0,	1, "锟斤拷值 (锟剿猴拷)"},
	{ "settrans",		CHAR_CHAT_DEBUG_setTrans,		TRUE,	0,	2, "锟斤拷值 (锟剿猴拷)"},
	{ "exp",			CHAR_CHAT_DEBUG_exp,			TRUE,	0,	2, "锟斤拷值 (锟剿猴拷)"},
	{ "hp",				CHAR_CHAT_DEBUG_hp,				TRUE,	0,	2, "锟斤拷值 (锟剿猴拷)"},
	{ "mp",				CHAR_CHAT_DEBUG_mp,				TRUE,	0,	2, "锟斤拷值 (锟剿猴拷)"},
	{ "setmp",			CHAR_CHAT_DEBUG_setmp,			TRUE,	0,	2, "锟斤拷值 (锟剿猴拷)"},
	{ "str",			CHAR_CHAT_DEBUG_str,			TRUE,	0,	2, "锟斤拷值*100 (锟剿猴拷)"},
	{ "dex",			CHAR_CHAT_DEBUG_dex,			TRUE,	0,	2, "锟斤拷值*100 (锟剿猴拷)"},
	{ "tgh",			CHAR_CHAT_DEBUG_tgh,			TRUE,	0,	2, "锟斤拷值*100 (锟剿猴拷)"},
	{ "vital",			CHAR_CHAT_DEBUG_vital,			TRUE,	0,	2, "锟斤拷值*100 (锟剿猴拷)"},
	{ "luck",			CHAR_CHAT_DEBUG_luck,			TRUE,	0,	2, "锟斤拷值 (锟剿猴拷)"},
	{ "superman",		CHAR_CHAT_DEBUG_superman,		TRUE,	0,	2, "(锟剿猴拷)"},
	{ "dp",				CHAR_CHAT_DEBUG_dp,				TRUE,	0,	2, "锟斤拷值 (锟剿猴拷)"},
#ifdef _EQUIT_SEQUENCE
	{ "sequence",		CHAR_CHAT_DEBUG_sequence,		TRUE,	0,	3, "锟斤拷值"},
#endif

	//系统
	{ "announce",		CHAR_CHAT_DEBUG_announce,		TRUE,	0,	1, "锟斤拷锟斤拷"},
	{ "loginannounce",	CHAR_CHAT_DEBUG_loginannounce,	TRUE,	0,	1, "锟斤拷锟斤拷"},
	{ "sysinfo",		CHAR_CHAT_DEBUG_sysinfo,		TRUE,	0,	1, ""},
	{ "effect",			CHAR_CHAT_DEBUG_effect,			TRUE,	0,	1, "alloff/锟斤拷图锟斤拷 锟斤拷效"},
	{ "reset",			CHAR_CHAT_DEBUG_reset,			TRUE,	0,	2, "enemy/encount/magic/warppoint/petskill/pettalk/npc/all"},
	{ "clean_floor",	CHAR_CHAT_DEBUG_cleanfloor,		TRUE,	0,	3, "锟斤拷图锟斤拷"},
	{ "printcount",		CHAR_CHAT_printcount,			TRUE,	0,	1, ""},
	{ "enemyrestart",	CHAR_CHAT_DEBUG_enemyrestart,	TRUE,	0,	3, "锟斤拷"},
	{ "cleanfreepet",	CHAR_CHAT_DEBUG_cleanfreepet,	TRUE,	0,	3, "锟斤拷"},
	
#ifdef _GMRELOAD
	{ "gmreload",		CHAR_CHAT_DEBUG_gmreload,		TRUE,	0,	3, "all/cdkey level"},
#endif

	{ "waeikickall",	CHAR_CHAT_DEBUG_waeikickall,	TRUE,	0,	3, "锟斤拷"},
	//锟斤拷锟斤拷	锟斤拷锟斤拷GM
	{ "debug",			CHAR_CHAT_DEBUG_debug,			TRUE,	0,	1, "on/off"},
	{ "metamo",			CHAR_CHAT_DEBUG_metamo,			TRUE,	0,	1, "锟斤拷锟斤拷图锟斤拷 (锟剿猴拷)"},
	{ "checklock",		CHAR_CHAT_DEBUG_checklock,		TRUE,	0,	1, "锟绞猴拷"},
	{ "shutup",			CHAR_CHAT_DEBUG_shutup,			TRUE,	0,	1, "锟绞猴拷 ON/OFF"},
#ifdef _WAEI_KICK
	{ "gmkick",			CHAR_CHAT_DEBUG_gmkick,			TRUE,	0,	1, "锟绞猴拷 LSLOCK/KICK/DEUNLOCK/UNLOCKALL/LOCK/TYPE/UNLOCK"},
#endif
  { "battlein",		CHAR_CHAT_DEBUG_battlein,		TRUE,	0,	1, "锟斤拷"},
  { "battleout",		CHAR_CHAT_DEBUG_battleout,		TRUE,	0,	1, "锟斤拷"},
	{ "battlewatch",	CHAR_CHAT_DEBUG_battlewatch,	TRUE,	0,	1, "锟斤拷"},
	{ "getuser",		CHAR_CHAT_DEBUG_getuser,		TRUE,	0,	1, "锟斤拷锟斤拷锟斤拷 锟斤拷图锟斤拷 (npc)"},
	{ "warp",			CHAR_CHAT_DEBUG_warp,			TRUE,	0,	1, "锟斤拷图锟斤拷 x y"},
	{ "waeikick",		CHAR_CHAT_DEBUG_waeikick,		TRUE,	0,	1, "锟绞猴拷"},
  { "jail",			CHAR_CHAT_DEBUG_jail,			TRUE,	0,	1, "锟绞猴拷"},
	{ "send",			CHAR_CHAT_DEBUG_send,			TRUE,	0,	1, "floor x y 锟绞猴拷"},
#ifdef _SendTo
	{ "sendto",			CHAR_CHAT_DEBUG_Sendto,			TRUE,	0,	1, "锟绞猴拷"},
#endif
	{ "noenemy",		CHAR_CHAT_DEBUG_noenemy,		TRUE,	0,	1, "on/off"},
	{ "watchevent",		CHAR_CHAT_DEBUG_watchevent,		TRUE,	0,	1, "锟斤拷"},
#ifdef _SEND_EFFECT	   	        // WON ADD AC锟斤拷锟斤拷雪锟斤拷锟斤拷锟斤拷锟斤拷锟叫?	{ "sendeffect",		CHAR_CHAT_DEBUG_sendeffect,		TRUE,	0,	1, ""},
#endif
	{ "silent",			CHAR_CHAT_DEBUG_silent,			TRUE,	0,	2, "锟绞猴拷 锟斤拷锟斤拷"},//锟斤拷锟斤拷
	{ "unlock",			CHAR_CHAT_DEBUG_unlock,			TRUE,	0,	2, "锟绞猴拷"},
	{ "eventclean",		CHAR_CHAT_DEBUG_eventclean,		TRUE,	0,	2, "all/锟斤拷锟?锟绞猴拷 锟斤拷锟斤拷锟斤拷"},
	{ "eventsetend",	CHAR_CHAT_DEBUG_eventsetend,	TRUE,	0,	2, "all/锟斤拷锟?锟绞猴拷 锟斤拷锟斤拷锟斤拷"},
	{ "eventsetnow",	CHAR_CHAT_DEBUG_eventsetnow,	TRUE,	0,	2, "all/锟斤拷锟?锟绞猴拷 锟斤拷锟斤拷锟斤拷"},

	{ "playerspread",	CHAR_CHAT_DEBUG_playerspread,	TRUE,	0,	3, "waei"},
	{ "shutupall",		CHAR_CHAT_DEBUG_shutupall,		TRUE,	0,	3, "锟斤拷"},
	{ "unlockserver",	CHAR_CHAT_DEBUG_unlockserver,	TRUE,	0,	3, "锟斤拷"},
  { "shutdown",		CHAR_CHAT_DEBUG_shutdown,		TRUE,	0,	3, "(锟斤拷锟斤拷)"},

	//锟狡筹拷
	{ "delitem",		CHAR_CHAT_DEBUG_delitem,		TRUE,	0,	1, "all/位锟斤拷"},
	{ "delpet",			CHAR_CHAT_DEBUG_deletepet,		TRUE,	0,	1, "all/位锟斤拷"},
	{ "additem",		CHAR_CHAT_DEBUG_additem,		TRUE,	0,	2, "锟斤拷锟斤拷ID ((锟斤拷锟斤拷) (锟剿猴拷))"},
	{ "petmake",		CHAR_CHAT_DEBUG_petmake,		TRUE,	0,	2, "锟斤拷锟斤拷ID ((锟饺硷拷) (锟剿猴拷))"},
	{ "gold",			CHAR_CHAT_DEBUG_gold,			TRUE,	0,	2, "锟斤拷锟斤拷 (锟剿猴拷)"},

	//锟斤拷锟藉工锟斤拷
	{ "manorpk",		CHAR_CHAT_DEBUG_manorpk,		TRUE,	0,	2, "allpeace/peace 庄园锟斤拷锟?},
	{ "fixfmleader",	CHAR_CHAT_DEBUG_fixfmleader,	TRUE,	0,	2, "锟绞猴拷 1"},
	{ "fixfmpk",		CHAR_CHAT_DEBUG_fixfmpk,		TRUE,	0,	3, ""},
	{ "fixfmdata",		CHAR_CHAT_DEBUG_fixfmdata,		TRUE,	0,	2, ""},

#ifdef _TEST_DROPITEMS
	{ "dropmypet",		CHAR_CHAT_DEBUG_dropmypet,		TRUE,	0,	3, "锟斤拷锟斤拷锟斤拷"},
	{ "dropmyitem",		CHAR_CHAT_DEBUG_dropmyitem,		TRUE,	0,	2, "锟斤拷锟竭憋拷锟?(0/1)"},
#endif
	{ "checktime",		CHAR_CHAT_DEBUG_checktime,		TRUE,	0,	3, ""},

#ifdef _GAMBLE_BANK
	{ "setgamblenum",	CHAR_CHAT_DEBUG_setgamblenum,	TRUE,	0,	3, "锟斤拷值"},
#endif
    // WON ADD 锟斤拷锟斤拷指锟斤拷
	{ "crash",			CHAR_CHAT_DEBUG_crash,			TRUE,	0,	3, ""},
#ifdef _PETSKILL_SETDUCK
	{ "setDuck",		CHAR_CHAT_DEBUG_SetDuck,		TRUE,	0,	3, ""},
#endif

#ifdef _TYPE_TOXICATION
	{ "setTox",			CHAR_CHAT_DEBUG_Toxication,		TRUE,	0,	3, ""},
#endif
	{ "showMem",		CHAR_CHAT_DEBUG_showMem,		TRUE,	0,	2, "锟斤拷"},
	{ "samecode",		CHAR_CHAT_DEBUG_samecode,		TRUE,	0,	3, "pet/item/set 锟斤拷锟斤拷"},
	{ "itemreload",	CHAR_CHAT_DEBUG_itemreload,	TRUE,   0,  2, ""},

	{ "skywalker",	CHAR_CHAT_DEBUG_skywalker,	TRUE,   0,  1, ""},
#ifdef _ITEM_ADDEXP
	{ "itemaddexp",	CHAR_CHAT_DEBUG_itemaddexp,	TRUE,   0,  1, ""},
#endif

#ifdef _DEF_GETYOU	  
	{ "getyou",		    CHAR_CHAT_DEBUG_getyou,			TRUE,   0,  1, "锟斤拷锟斤拷 1~3"},
#endif 
#ifdef _DEF_NEWSEND
	{ "newsend",        CHAR_CHAT_DEBUG_newsend,        TRUE,   0,  1, "floor x y 锟绞猴拷 锟斤拷/要说锟侥伙拷"},   
#endif
#ifdef _DEF_SUPERSEND
	{ "supersend",      CHAR_CHAT_DEBUG_supersend,      TRUE,   0,  3, "floor x y 锟斤拷锟斤拷 锟斤拷/要说锟侥伙拷"},   
#endif

#ifdef _CREATE_MM_1_2
	{ "MM",		CHAR_CHAT_DEBUG_MM,      TRUE,   0,  3, "MM 1/2 (锟剿猴拷)"},
#endif
#ifdef _GM_ITEM
	{ "gmfunction",		CHAR_CHAT_DEBUG_GMFUNCTION,      TRUE,   0,  3, "锟斤拷锟斤拷 锟斤拷锟斤拷 (锟剿猴拷)"},
#endif

#ifdef _GM_RIDE
	{ "setride",		CHAR_CHAT_DEBUG_SETRIDE,      TRUE,   0,  3, "锟斤拷锟斤拷 (锟剿猴拷)"},
	{ "mvride",		CHAR_CHAT_DEBUG_MVRIDE,      TRUE,   0,  3, "锟斤拷锟斤拷 (锟剿猴拷)"},
#endif

#ifdef _LOCK_IP
	{ "addlock",		CHAR_CHAT_DEBUG_ADD_LOCK,      TRUE,   0,  3, "flag 锟剿猴拷/IP IP"},
	{ "dellock",		CHAR_CHAT_DEBUG_DEL_LOCK,      TRUE,   0,  3, "flag 锟剿猴拷/IP IP"},
	{ "showip",		CHAR_CHAT_DEBUG_SHOWIP,      TRUE,   0,  3, "锟剿猴拷"},
#endif	
	{ "setfame",		CHAR_CHAT_DEBUG_SET_FAME,      TRUE,   0,  3, "锟剿猴拷 锟斤拷锟斤拷值"},
	
#ifdef _AUTO_PK
	{ "pktime",		CHAR_CHAT_DEBUG_SET_AUTOPK,      TRUE,   0,  3, "锟斤拷锟斤拷"},
#endif

#ifdef _PLAYER_NUM
	{ "playernum",		CHAR_CHAT_DEBUG_SET_PLAYERNUM,      TRUE,   0,  3, "锟斤拷锟斤拷"},
#endif

#ifdef _RELOAD_CF
	{ "reloadcf",		CHAR_CHAT_DEBUG_SET_RELOADCF,      TRUE,   0,  3, ""},
#endif

#ifdef _TRANS
	{ "trans",		CHAR_CHAT_DEBUG_Trans,      TRUE,   0,  3, "(锟剿猴拷)"},
#endif
#ifdef _MAKE_PET_CF
	{ "petmakecf",		CHAR_CHAT_DEBUG_petmakecf,      TRUE,   0,  3, "锟斤拷锟斤拷锟斤拷 转锟斤拷/锟饺硷拷/锟缴筹拷"},
#endif
#ifdef _MAKE_PET_ABILITY
	{ "petmakeabi",		CHAR_CHAT_DEBUG_petmakeabi,      TRUE,   0,  3, "锟斤拷锟斤拷锟斤拷 转锟斤拷/锟饺硷拷/锟缴筹拷"},
#endif
#ifdef _MAKE_MAP
	{ "delmap",		CHAR_CHAT_DelMap,      TRUE,   0,  3, ""},
	{ "getmap",		CHAR_CHAT_GetMap,      TRUE,   0,  3, ""},
	{ "map",		CHAR_CHAT_Map,      TRUE,   0,  3, ""},
	{ "tile",		CHAR_CHAT_Fixtile,      TRUE,   0,  3, ""},
	{ "obj",		CHAR_CHAT_Fixobj,      TRUE,   0,  3, ""},
	{ "删锟斤拷锟酵?,		CHAR_CHAT_GetMap,      TRUE,   0,  3, ""},
	{ "锟斤拷取锟斤拷图",		CHAR_CHAT_GetMap,      TRUE,   0,  3, ""},
	{ "图片锟斤拷锟斤拷",		CHAR_CHAT_Map,      TRUE,   0,  3, ""},
	{ "图片",		CHAR_CHAT_Fixtile,      TRUE,   0,  3, ""},
	{ "锟斤拷锟斤拷",		CHAR_CHAT_Fixobj,      TRUE,   0,  3, ""},
//	{ "fukuwa",		CHAR_CHAT_Fukuwa,      TRUE,   0,  3, ""},
#endif
/////////////////////////////////////////////////////////////////////////
	//锟斤拷锟斤拷师专锟斤拷
//	{ "programming_engineer",	CHAR_CHAT_DEBUG_engineer,	TRUE,	0,	3, ""},
	{ "锟斤拷锟斤拷燃锟?,	CHAR_CHAT_DEBUG_petlevelup,	TRUE,	0,	2, "锟斤拷锟斤拷锟斤拷锟斤拷 锟饺硷拷 (锟剿猴拷)"},
	{ "锟斤拷锟斤经锟斤拷",	CHAR_CHAT_DEBUG_petexpup,	TRUE,	0,	2, "锟斤拷锟斤拷锟斤拷锟斤拷 锟斤拷锟斤拷 (锟剿猴拷)"},
	{ "锟斤拷锟斤拷",			CHAR_CHAT_DEBUG_help,				TRUE,	0,	1, "指锟斤拷/all"},
#ifdef _EQUIT_NEGLECTGUARD
//	{ "setneguard",		CHAR_CHAT_DEBUG_setneguard,			TRUE,	0,	3, "waei"},
#endif
	//锟斤拷锟斤拷锟斤拷锟斤拷
	{ "锟斤拷锟斤拷锟斤拷息",			CHAR_CHAT_DEBUG_info,			TRUE,	0,	1, "锟斤拷值"},
	{ "锟饺硷拷",			CHAR_CHAT_DEBUG_level,			TRUE,	0,	1, "锟斤拷值 (锟剿猴拷)"},
	{ "转锟斤拷",		CHAR_CHAT_DEBUG_setTrans,		TRUE,	0,	2, "锟斤拷值 (锟剿猴拷)"},
	{ "锟斤拷锟斤拷",			CHAR_CHAT_DEBUG_exp,			TRUE,	0,	2, "锟斤拷值 (锟剿猴拷)"},
	{ "血",				CHAR_CHAT_DEBUG_hp,				TRUE,	0,	2, "锟斤拷值 (锟剿猴拷)"},
	{ "魔锟斤拷",				CHAR_CHAT_DEBUG_mp,				TRUE,	0,	2, "锟斤拷值 (锟剿猴拷)"},
	{ "锟斤拷锟斤拷魔锟斤拷",			CHAR_CHAT_DEBUG_setmp,			TRUE,	0,	2, "锟斤拷值 (锟剿猴拷)"},
	{ "锟斤拷锟斤拷",			CHAR_CHAT_DEBUG_str,			TRUE,	0,	2, "锟斤拷值*100 (锟剿猴拷)"},
	{ "锟斤拷锟斤拷",			CHAR_CHAT_DEBUG_dex,			TRUE,	0,	2, "锟斤拷值*100 (锟剿猴拷)"},
	{ "锟斤拷锟斤拷",			CHAR_CHAT_DEBUG_tgh,			TRUE,	0,	2, "锟斤拷值*100 (锟剿猴拷)"},
	{ "锟斤拷锟斤拷",			CHAR_CHAT_DEBUG_vital,			TRUE,	0,	2, "锟斤拷值*100 (锟剿猴拷)"},
	{ "锟斤拷锟斤拷",			CHAR_CHAT_DEBUG_luck,			TRUE,	0,	2, "锟斤拷值 (锟剿猴拷)"},
	{ "锟斤拷锟斤拷",		CHAR_CHAT_DEBUG_superman,		TRUE,	0,	2, "(锟剿猴拷)"},
	{ "dp",				CHAR_CHAT_DEBUG_dp,				TRUE,	0,	2, "锟斤拷值 (锟剿猴拷)"},

#ifdef _EQUIT_SEQUENCE
	{ "顺锟斤拷",		CHAR_CHAT_DEBUG_sequence,		TRUE,	0,	3, "锟斤拷值"},
#endif

	//系统
	{ "锟斤拷锟斤拷",		CHAR_CHAT_DEBUG_announce,		TRUE,	0,	1, "锟斤拷锟斤拷"},
	{ "锟斤拷陆锟斤拷锟斤拷",	CHAR_CHAT_DEBUG_loginannounce,	TRUE,	0,	1, "锟斤拷锟斤拷"},
	{ "系统锟斤拷息",		CHAR_CHAT_DEBUG_sysinfo,		TRUE,	0,	1, ""},
	{ "锟斤拷图锟斤拷效",			CHAR_CHAT_DEBUG_effect,			TRUE,	0,	1, "alloff/锟斤拷图锟斤拷 锟斤拷效"},
	{ "锟截讹拷",			CHAR_CHAT_DEBUG_reset,			TRUE,	0,	2, "enemy/encount/magic/warppoint/petskill/pettalk/npc/all"},
	{ "锟斤拷锟斤拷图锟斤拷品",	CHAR_CHAT_DEBUG_cleanfloor,		TRUE,	0,	3, "锟斤拷图锟斤拷"},
	{ "统锟斤拷",		CHAR_CHAT_printcount,			TRUE,	0,	1, ""},
	{ "锟截讹拷锟斤拷锟斤拷锟斤拷锟斤拷",	CHAR_CHAT_DEBUG_enemyrestart,	TRUE,	0,	3, "锟斤拷"},
	{ "锟斤拷锟斤拷锟较筹拷锟斤拷",	CHAR_CHAT_DEBUG_cleanfreepet,	TRUE,	0,	3, "锟斤拷"},
	
#ifdef _GMRELOAD
	{ "锟斤拷取GM锟斤拷锟斤拷",		CHAR_CHAT_DEBUG_gmreload,		TRUE,	0,	3, "all/cdkey level"},
#endif

	{ "锟竭筹拷锟斤拷锟斤拷锟斤拷锟?,	CHAR_CHAT_DEBUG_waeikickall,	TRUE,	0,	3, "锟斤拷"},
//	{ "checktrade",		CHAR_CHAT_DEBUG_checktrade,		TRUE,	0,	3, "waei"},
	//锟斤拷锟斤拷	锟斤拷锟斤拷GM
	{ "锟斤拷锟斤拷",			CHAR_CHAT_DEBUG_debug,			TRUE,	0,	1, "锟斤拷锟斤拷 锟斤拷锟斤拷 on/off"},
	{ "锟斤拷锟斤拷",			CHAR_CHAT_DEBUG_metamo,			TRUE,	0,	1, "锟斤拷锟斤拷图锟斤拷 (锟剿猴拷)"},
	{ "锟斤拷锟绞猴拷",		CHAR_CHAT_DEBUG_checklock,		TRUE,	0,	1, "锟绞猴拷"},
	{ "锟斤拷锟斤拷",			CHAR_CHAT_DEBUG_shutup,			TRUE,	0,	1, "锟绞猴拷 ON/OFF"},
#ifdef _WAEI_KICK
	{ "gm锟斤拷锟斤拷",			CHAR_CHAT_DEBUG_gmkick,			TRUE,	0,	1, "锟绞猴拷 LSLOCK/KICK/DEUNLOCK/UNLOCKALL/LOCK/TYPE/UNLOCK"},
#endif
  { "锟斤拷锟斤拷战锟斤拷",		CHAR_CHAT_DEBUG_battlein,		TRUE,	0,	1, "锟斤拷"},
  { "锟斤拷锟斤拷战锟斤拷",		CHAR_CHAT_DEBUG_battleout,		TRUE,	0,	1, "锟斤拷"},
	{ "锟斤拷战",	CHAR_CHAT_DEBUG_battlewatch,	TRUE,	0,	1, "锟斤拷"},
	{ "锟斤拷示锟斤拷息",		CHAR_CHAT_DEBUG_getuser,		TRUE,	0,	1, "锟斤拷锟斤拷锟斤拷 锟斤拷图锟斤拷 (npc)"},
	{ "锟斤拷锟斤拷锟皆硷拷",			CHAR_CHAT_DEBUG_warp,			TRUE,	0,	1, "锟斤拷图锟斤拷 x y"},
	{ "锟竭筹拷锟斤拷锟?,		CHAR_CHAT_DEBUG_waeikick,		TRUE,	0,	1, "锟绞猴拷"},
  { "锟斤拷锟斤拷锟斤拷锟?,			CHAR_CHAT_DEBUG_jail,			TRUE,	0,	1, "锟绞猴拷"},
	{ "锟斤拷锟斤拷",			CHAR_CHAT_DEBUG_send,			TRUE,	0,	1, "锟斤拷图锟斤拷锟?x y 锟绞猴拷"},
#ifdef _SendTo
	{ "锟斤拷锟酵碉拷锟斤拷锟?,			CHAR_CHAT_DEBUG_Sendto,			TRUE,	0,	1, "锟绞猴拷"},
#endif
	{ "锟斤拷锟斤拷锟斤拷",		CHAR_CHAT_DEBUG_noenemy,		TRUE,	0,	1, "on/off"},
	{ "锟斤拷示锟斤拷锟斤拷锟斤拷锟?,		CHAR_CHAT_DEBUG_watchevent,		TRUE,	0,	1, "锟斤拷"},
#ifdef _SEND_EFFECT	   	        // WON ADD AC锟斤拷锟斤拷雪锟斤拷锟斤拷锟斤拷锟斤拷锟叫?	{ "锟斤拷效",		CHAR_CHAT_DEBUG_sendeffect,		TRUE,	0,	1, ""},
#endif
	{ "锟斤拷锟斤拷",			CHAR_CHAT_DEBUG_silent,			TRUE,	0,	2, "锟绞猴拷 锟斤拷锟斤拷"},//锟斤拷锟斤拷
	{ "锟斤拷锟斤拷",			CHAR_CHAT_DEBUG_unlock,			TRUE,	0,	2, "锟绞猴拷"},
	{ "锟斤拷锟斤拷锟斤拷",		CHAR_CHAT_DEBUG_eventclean,		TRUE,	0,	2, "all/锟斤拷锟?锟绞猴拷 锟斤拷锟斤拷锟斤拷"},
	{ "锟斤拷锟斤拷锟斤拷锟?,	CHAR_CHAT_DEBUG_eventsetend,	TRUE,	0,	2, "all/锟斤拷锟?锟绞猴拷 锟斤拷锟斤拷锟斤拷"},
	{ "锟斤拷锟斤拷锟斤拷锟斤拷",	CHAR_CHAT_DEBUG_eventsetnow,	TRUE,	0,	2, "all/锟斤拷锟?锟绞猴拷 锟斤拷锟斤拷锟斤拷"},

	{ "锟斤拷锟斤拷锟斤拷锟斤拷锟绞?,	CHAR_CHAT_DEBUG_playerspread,	TRUE,	0,	3, "waei"},
//	{ "shutupall",		CHAR_CHAT_DEBUG_shutupall,		TRUE,	0,	3, "锟斤拷"},
	{ "锟斤拷锟斤拷锟斤拷锟斤拷",	CHAR_CHAT_DEBUG_unlockserver,	TRUE,	0,	3, "锟斤拷"},
  { "锟截凤拷",		CHAR_CHAT_DEBUG_shutdown,		TRUE,	0,	3, "锟斤拷锟斤拷"},

	//锟狡筹拷
	{ "删锟斤拷锟斤拷品",		CHAR_CHAT_DEBUG_delitem,		TRUE,	0,	1, "all/位锟斤拷"},
	{ "删锟斤拷锟斤拷锟?,			CHAR_CHAT_DEBUG_deletepet,		TRUE,	0,	1, "all/位锟斤拷"},
	{ "锟斤拷锟斤拷锟斤拷品",		CHAR_CHAT_DEBUG_additem,		TRUE,	0,	2, "锟斤拷锟斤拷ID ((锟斤拷锟斤拷) (锟剿猴拷))"},
	{ "锟斤拷锟斤拷锟斤拷锟斤拷",		CHAR_CHAT_DEBUG_petmake,		TRUE,	0,	2, "锟斤拷锟斤拷ID ((锟饺硷拷) (锟剿猴拷))"},
	{ "锟斤拷钱",			CHAR_CHAT_DEBUG_gold,			TRUE,	0,	2, "锟斤拷锟斤拷 (锟剿猴拷)"},

	//锟斤拷锟藉工锟斤拷
//	{ "manorpk",		CHAR_CHAT_DEBUG_manorpk,		TRUE,	0,	2, "allpeace/peace 庄园锟斤拷锟?},
	{ "锟睫革拷锟藉长",	CHAR_CHAT_DEBUG_fixfmleader,	TRUE,	0,	2, "锟绞猴拷 1"},
	{ "锟睫革拷锟斤拷锟斤拷PK",		CHAR_CHAT_DEBUG_fixfmpk,		TRUE,	0,	3, ""},
	{ "锟睫革拷锟斤拷锟斤拷锟斤拷锟?,		CHAR_CHAT_DEBUG_fixfmdata,		TRUE,	0,	2, ""},

#ifdef _TEST_DROPITEMS
	{ "锟斤拷爻锟斤拷锟?,		CHAR_CHAT_DEBUG_dropmypet,		TRUE,	0,	3, "锟斤拷锟斤拷锟斤拷"},
	{ "锟斤拷锟斤拷锟狡?,		CHAR_CHAT_DEBUG_dropmyitem,		TRUE,	0,	3, "锟斤拷锟竭憋拷锟?(0/1)"},
#endif
	{ "锟斤拷示时锟斤拷",		CHAR_CHAT_DEBUG_checktime,		TRUE,	0,	3, ""},

#ifdef _GAMBLE_BANK
	{ "锟斤拷锟?,	CHAR_CHAT_DEBUG_setgamblenum,	TRUE,	0,	3, "锟斤拷值"},
#endif
    // WON ADD 锟斤拷锟斤拷指锟斤拷
	{ "锟斤拷锟斤拷",			CHAR_CHAT_DEBUG_crash,			TRUE,	0,	3, ""},
#ifdef _PETSKILL_SETDUCK
//	{ "setDuck",		CHAR_CHAT_DEBUG_SetDuck,		TRUE,	0,	3, ""},
#endif

#ifdef _TYPE_TOXICATION
	{ "锟叫讹拷",			CHAR_CHAT_DEBUG_Toxication,		TRUE,	0,	3, ""},
#endif
	{ "锟斤拷示锟节达拷",		CHAR_CHAT_DEBUG_showMem,		TRUE,	0,	2, "锟斤拷"},
	{ "锟斤拷锟斤拷",		CHAR_CHAT_DEBUG_samecode,		TRUE,	0,	3, "pet/item/set 锟斤拷锟斤拷"},

	{ "锟斤拷取锟斤拷品",	CHAR_CHAT_DEBUG_itemreload,	TRUE,   0,  2, ""},

	{ "锟斤拷锟斤拷锟斤拷",	CHAR_CHAT_DEBUG_skywalker,	TRUE,   0,  1, ""},
#ifdef _ITEM_ADDEXP
	{ "锟斤拷取锟斤拷锟斤拷锟斤拷品",	CHAR_CHAT_DEBUG_itemaddexp,	TRUE,   0,  1, ""},
#endif
#ifdef _DEF_GETYOU	  
	{ "锟斤拷取锟剿猴拷",		    CHAR_CHAT_DEBUG_getyou,			TRUE,   0,  1, "锟斤拷锟斤拷 1~3"},
#endif 
#ifdef _DEF_NEWSEND
	{ "锟斤拷锟斤拷锟斤拷锟?,        CHAR_CHAT_DEBUG_newsend,        TRUE,   0,  1, "锟斤拷图锟斤拷锟?x y 锟绞猴拷 锟斤拷/要说锟侥伙拷"},   
#endif
#ifdef _DEF_SUPERSEND
	{ "群锟藉传锟斤拷",      CHAR_CHAT_DEBUG_supersend,      TRUE,   0,  3, "锟斤拷图锟斤拷锟?x y 锟斤拷锟斤拷 锟斤拷/要说锟侥伙拷"},   
#endif

#ifdef _GM_ITEM
	{ "权锟斤拷",		CHAR_CHAT_DEBUG_GMFUNCTION,      TRUE,   0,  3, "锟斤拷锟斤拷 锟斤拷锟斤拷 (锟剿猴拷)"},
#endif

#ifdef _GM_RIDE
	{ "锟斤拷锟斤拷锟斤拷锟?,		CHAR_CHAT_DEBUG_SETRIDE,      TRUE,   0,  3, "锟斤拷锟斤拷 (锟剿猴拷)"},
	{ "锟狡筹拷锟斤拷锟?,		CHAR_CHAT_DEBUG_MVRIDE,      TRUE,   0,  3, "锟斤拷锟斤拷 (锟剿猴拷)"},
#endif

#ifdef _LOCK_IP
	{ "锟斤拷",		CHAR_CHAT_DEBUG_ADD_LOCK,      TRUE,   0,  3, "flag 锟剿猴拷/IP IP"},
	{ "锟斤拷锟斤拷锟?,		CHAR_CHAT_DEBUG_DEL_LOCK,      TRUE,   0,  3, "flag 锟剿猴拷/IP IP"},
	{ "锟斤拷示锟斤拷锟絀P",		CHAR_CHAT_DEBUG_SHOWIP,      TRUE,   0,  3, "锟剿猴拷"},
#endif
	{ "锟斤拷锟斤拷",		CHAR_CHAT_DEBUG_SET_FAME,      TRUE,   0,  3, "锟剿猴拷 锟斤拷锟斤拷值"},
#ifdef _AUTO_PK
	{ "pk时锟斤拷",		CHAR_CHAT_DEBUG_SET_AUTOPK,      TRUE,   0,  3, "锟斤拷锟斤拷"},
#endif

#ifdef _PLAYER_NUM
	{ "锟斤拷锟斤拷锟?,		CHAR_CHAT_DEBUG_SET_PLAYERNUM,      TRUE,   0,  3, "锟斤拷锟斤拷"},
#endif
#ifdef _RELOAD_CF
	{ "锟斤拷取锟斤拷锟斤拷",		CHAR_CHAT_DEBUG_SET_RELOADCF,      TRUE,   0,  3, ""},
#endif
#ifdef _TRANS
	{ "锟竭硷拷转锟斤拷",		CHAR_CHAT_DEBUG_Trans,      TRUE,   0,  3, "(锟剿猴拷)"},
#endif
#ifdef _MAKE_PET_CF
	{ "锟斤拷锟斤拷沙锟?,		CHAR_CHAT_DEBUG_petmakecf,      TRUE,   0,  3, "锟斤拷锟斤拷锟斤拷 转锟斤拷/锟饺硷拷/锟缴筹拷"},
#endif
#ifdef _MAKE_PET_ABILITY
	{ "锟斤拷锟斤拷锟斤拷围",		CHAR_CHAT_DEBUG_petmakeabi,      TRUE,   0,  3, "锟斤拷锟斤拷锟斤拷 血 锟斤拷 锟斤拷 锟斤拷"},
#endif
};

void CHAR_initDebugChatCdkey( void)
{
	int i;
	for( i = 0; i < DEBUGCDKEYNUM; i ++ ) {
		DebugCDKey[i].use = FALSE;
		DebugCDKey[i].cdkey[0] = '\0';
	}
}
/*------------------------------------------------------------
 * 锟斤拷锟斤拷锟斤拷锟斤拷  芊锟斤拷甩锟斤拷锟斤拷亘锟斤拷毛锟斤拷锟铰ｏ拷
 * 娄锟窖ｏ拷忒曰锟斤拷
 *  卅锟斤拷
 ------------------------------------------------------------*/
void CHAR_initChatMagic(void)
{
	int i;
	for( i=0 ; i<arraysizeof(CHAR_cmtbl) ; i++ )
		CHAR_cmtbl[i].hash = hashpjw( CHAR_cmtbl[i].magicname);
	for( i = 0; i < DEBUGCDKEYNUM; i ++ ) {
		DebugCDKey[i].use = FALSE;
		DebugCDKey[i].cdkey[0] = '\0';
	}
}

int CHAR_setChatMagicCDKey( int mode, char *cdkey)
{

	int i;
	BOOL found = FALSE;
	if( strlen( cdkey) > 8 ) {
		return -1;
	}
	for( i = 0; i < DEBUGCDKEYNUM; i ++ ) {
		if( DebugCDKey[i].use == FALSE) {
			if( mode == 0 ) {
				DebugCDKey[i].use = TRUE;
				strcpysafe( DebugCDKey[i].cdkey, sizeof( DebugCDKey[i].cdkey), cdkey);
				found = TRUE;
				break;
			}
		}
		else {
			if( mode == 1 ) {
				if( strcmp( DebugCDKey[i].cdkey, cdkey) == 0 ) {
					DebugCDKey[i].use = FALSE;
					DebugCDKey[i].cdkey[0] = '\0';
					found = TRUE;
				}
			}
		}
				
	}
	if( !found ) return -1;
	return i;
}

static CHATMAGICFUNC CHAR_getChatMagicFuncPointer(char* name, BOOL isDebug)
{
	int i;
	int hash = hashpjw( name );
	for( i=0 ; i<arraysizeof(CHAR_cmtbl) ; i++ )
		if( CHAR_cmtbl[i].hash == hash
			&& CHAR_cmtbl[i].isdebug == isDebug
			&& strcmp( CHAR_cmtbl[i].magicname, name ) == 0 )
			return CHAR_cmtbl[i].func;
	return NULL;
}

int CHAR_getChatMagicFuncLevel(char* name,BOOL isDebug)
{
	int i;
	int hash = hashpjw( name );
	for( i=0 ; i<arraysizeof(CHAR_cmtbl) ; i++ )
		if( CHAR_cmtbl[i].hash == hash
			&& CHAR_cmtbl[i].isdebug == isDebug
			&& strcmp( CHAR_cmtbl[i].magicname, name ) == 0 )
			return CHAR_cmtbl[i].level;
	return -1;
}

int CHAR_getChatMagicFuncNameAndString( int ti, char* name, char *usestring, int level, BOOL isDebug)
{
	if( name == NULL || usestring == NULL ) return -1;
	if( ti < 0 || ti >= arraysizeof( CHAR_cmtbl) ) return -1;
	if( CHAR_cmtbl[ ti].isdebug == isDebug &&
		CHAR_cmtbl[ ti].level <= level ){
		sprintf( name,"%s", CHAR_cmtbl[ ti].magicname );
		sprintf( usestring, "%s", CHAR_cmtbl[ ti].usestring );
		return 1;
	}
	return 0;
}

int CHAR_getChatMagicFuncMaxNum( void)
{
	return arraysizeof( CHAR_cmtbl);
}

/*------------------------------------------------------------
 * 锟斤拷锟斤拷锟斤拷锟斤拷  芊
 * 娄锟斤拷
 *  charaindex      int     平锟揭凤拷锟教硷拷锟斤拷锟斤拷锟酵碉拷
 *  message         char*   锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
 *  isDebug         BOOL    锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷  芊锟斤拷锟斤拷
 * 忒曰锟斤拷
 *  卅锟斤拷
 ------------------------------------------------------------*/
static BOOL CHAR_useChatMagic( int charaindex, char* data, BOOL isDebug)
{
	char    magicname[256];
	int     ret;
	int	i;
	int	gmLevel = 0, magicLevel;
	
	CHATMAGICFUNC   func;

#ifdef _GMRELOAD
	extern struct GMINFO gminfo[GMMAXNUM];
#else
#endif
	char *p = CHAR_getChar( charaindex, CHAR_CDKEY);
	if( !p ) {
		fprint( "err nothing cdkey\n");
		return FALSE;
	}

	if( getChatMagicCDKeyCheck() == 1 ){ //锟斤拷一锟斤拷确锟斤拷GM锟绞猴拷
		if( CHAR_getWorkInt( charaindex, CHAR_WORKFLG) & WORKFLG_DEBUGMODE ) {
			gmLevel = CHAR_getWorkInt( charaindex, CHAR_WORKGMLEVEL);
		}else{

#ifdef _GMRELOAD
			for (i = 0; i < GMMAXNUM; i++){
				if (strcmp( p, gminfo[i].cdkey) == 0){
					gmLevel = gminfo[i].level;
					CHAR_setWorkInt( charaindex, CHAR_WORKGMLEVEL, gmLevel);
					break;
				}
			}
#else
#endif

			if( i >= GMMAXNUM ){
				for( i = 0; i < DEBUGCDKEYNUM; i ++ ) {
					if( DebugCDKey[i].use && strcmp( p, DebugCDKey[i].cdkey) == 0 ) {
						break;
					}
				}
				if( i >= DEBUGCDKEYNUM ) return FALSE;
			}
		}

	}else {
		gmLevel = 3;
		CHAR_setWorkInt( charaindex, CHAR_WORKGMLEVEL, gmLevel);
	}

	ret = getStringFromIndexWithDelim( data, " ", 1, magicname,  sizeof( magicname));
	if( ret == FALSE)return FALSE;

	// Robin 0618  chaeck GM Level
	magicLevel = CHAR_getChatMagicFuncLevel( magicname, isDebug);
	if( gmLevel < magicLevel )
		return FALSE;

	func = CHAR_getChatMagicFuncPointer(magicname,isDebug);
	if( func ){
		LogGM( CHAR_getUseName( charaindex), CHAR_getChar( charaindex, CHAR_CDKEY), data, 
			CHAR_getInt( charaindex, CHAR_FLOOR), CHAR_getInt( charaindex, CHAR_X),
			CHAR_getInt( charaindex, CHAR_Y) );
		func( charaindex, data + strlen( magicname)+1);
		return TRUE;
	}else{
		return FALSE;
	}
}

/*------------------------------------------------------------
 * 锟斤拷锟节撅拷锟斤拷锟斤拷毛锟狡伙拷锟斤拷
 * 娄锟斤拷
 *  volume  int     锟斤拷锟斤拷
 * 忒曰锟斤拷
 *  穴锟斤拷锟斤拷匹锟斤拷穴锟斤拷
 ------------------------------------------------------------*/
static int CHAR_getRangeFromVolume( int volume )
{
	static int chatvol[]={
		3,5,7,9,11,13,15,17,19,21,23,25,27,29,31
	};

	if( volume < 0 )return 0;
	else if( arraysizeof( chatvol ) <= volume ) {
		return chatvol[arraysizeof(chatvol)-1];
	}
	return chatvol[volume];
}
/*------------------------------------------------------------
 * 擘硷拷示锟斤拷亘锟斤拷丞毛锟斤拷锟铰ｏ拷锟斤拷卅锟斤拷支曰锟斤拷锟阶ｏ拷
 * 娄锟斤拷
 *  mesg        char*       锟斤拷锟斤拷锟斤拷锟斤拷锟缴猴拷
 * 忒曰锟斤拷
 *  -1 锟斤拷锟斤拷锟藉反锟金公筹拷
 *  0  锟斤拷锟斤拷锟藉反锟阶癸拷锟斤拷
 *  1 锟斤拷曰锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷旯达拷骞达拷谢锟斤拷锟斤拷锟?! 锟斤拷锟斤拷
 ------------------------------------------------------------*/
static int CHAR_getVolume( char* mesg )
{
	int stringlen = strlen( mesg );
	if( stringlen == 0 )
		return 0;
	else if( stringlen == 1 ){
    if ( mesg[ 0 ] == '!' )
      return 1;
    else
      return 0;
  }
  else if ( stringlen == 2 ) {
    if ( mesg[ 1 ] == '!' ) {
      if ( mesg[ 0 ] == '!' )
        return 2;
      else
        return 1;
    }
    else
      return 0;
	}else{
		/*  3锟斤拷锟斤拷   */
		if( mesg[stringlen-1] == '.' ){
			/*  锟金公仇公硷拷锟斤拷  锟斤拷丐曰    */
			if( mesg[stringlen-2] == '.' && mesg[stringlen-3] == '.' ){
				/*  锟金公筹拷    */
				return -1;
			}
			return 0;
		}else{
			/*  锟斤拷锟斤拷锟?! 毛锟斤拷锟斤拷锟斤拷*/
			int exnum=0;
			int i;
			for( i=stringlen-1; i>=0 ; i-- ){
				if( mesg[i] != '!' )
					break;
				else
					exnum++;
			}
			return exnum;
		}
	}
}

/*------------------------------------------------------------
 * 锟斤拷锟斤拷锟斤拷锟斤拷锟解及    锟斤拷锟秸讹拷锟斤拷锟斤拷锟斤拷锟解及      锟斤拷毛锟斤拷曰锟斤拷锟斤拷
 * 娄锟斤拷
 *  message     char*           锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷    
 *  kind        char*           p or s or i卅锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
 *  kindlen     int             kind 锟斤拷赢锟斤拷
 *  body        char**          锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷    锟斤拷锟斤拷锟教硷拷锟斤拷锟斤拷锟缴? 锟斤拷锟斤拷
 * 忒曰锟斤拷
 *  卅锟斤拷
 ------------------------------------------------------------*/
void CHAR_getMessageBody(char* message,char* kind,int kindlen,char** body)
{
    int firstchar;

	/* 1  侬  毛锟斤拷之锟斤拷锟绞ｏ拷1  侬匹丐锟铰筹拷锟界反lssproto.html锟斤拷锟斤拷锟?*/
	// Nuke +1: For invalid message attack
	*body = 0;
    firstchar = message[0];
    if( firstchar == 'P' ||
        firstchar == 'S' ||
        firstchar == 'D'

        // CoolFish: Trade 2001/4/18
	|| firstchar == 'C'
        || firstchar == 'T'
        || firstchar == 'W'
                                
        // CoolFish: Family 2001/5/28
	|| firstchar == 'A'
        || firstchar == 'J'
        || firstchar == 'E'
        || firstchar == 'M'
        
        || firstchar == 'B'
        || firstchar == 'X'
        || firstchar == 'R'
        || firstchar == 'L'

         ){
        if( kindlen >= 2 ){
            kind[0] = firstchar;
            kind[1] = '\0';
        } else {
            return;
        }
    } else {
        return;
    }

	*body = message + 2;
}


static BOOL CHAR_Talk_check( int talkerindex, int talkedindex, int micflg )
{
#if 1
	if( !CHAR_getFlg( talkerindex, CHAR_ISPARTYCHAT )){
		int talker_b_mode = CHAR_getWorkInt( talkerindex, CHAR_WORKBATTLEMODE);
		int talked_b_mode = CHAR_getWorkInt( talkedindex, CHAR_WORKBATTLEMODE);
		if( talker_b_mode != BATTLE_CHARMODE_NONE
			&& CHAR_getInt( talkedindex, CHAR_WHICHTYPE) != CHAR_TYPEPLAYER){
			return FALSE;
		}
		if( micflg != 0 )return TRUE;
		if( talker_b_mode != BATTLE_CHARMODE_NONE && talked_b_mode != BATTLE_CHARMODE_NONE){
			if( CHAR_getWorkInt( talkerindex, CHAR_WORKBATTLEINDEX)
				!= CHAR_getWorkInt( talkedindex, CHAR_WORKBATTLEINDEX)){
				return FALSE;
			}
		}else if( talker_b_mode != BATTLE_CHARMODE_NONE || talked_b_mode != BATTLE_CHARMODE_NONE){
		 	return FALSE;
		}
		return TRUE;
	}
	if( CHAR_getInt( talkerindex, CHAR_WHICHTYPE) == CHAR_TYPEPLAYER) {
		int talker_b_mode = CHAR_getWorkInt( talkerindex, CHAR_WORKBATTLEMODE);
		int talked_b_mode = CHAR_getWorkInt( talkedindex, CHAR_WORKBATTLEMODE);

		if( talker_b_mode != BATTLE_CHARMODE_NONE && CHAR_getInt( talkedindex, CHAR_WHICHTYPE) != CHAR_TYPEPLAYER){
			return FALSE;
		}
		if( micflg != 0 )return TRUE;
		if( CHAR_getWorkInt( talkerindex, CHAR_WORKPARTYMODE) != CHAR_PARTY_NONE ){
			if( CHAR_getWorkInt( talkedindex, CHAR_WORKPARTYMODE) != CHAR_PARTY_NONE){
				if( CHAR_getWorkInt( talkerindex, CHAR_WORKPARTYINDEX1)
					== CHAR_getWorkInt( talkedindex, CHAR_WORKPARTYINDEX1) ){
					return TRUE;
				}
			}
		}else {
			if( talker_b_mode != BATTLE_CHARMODE_NONE && talked_b_mode != BATTLE_CHARMODE_NONE){
				if( CHAR_getWorkInt( talkerindex, CHAR_WORKBATTLEINDEX)
					!= CHAR_getWorkInt( talkedindex, CHAR_WORKBATTLEINDEX)){
					return FALSE;
				}
			}else if( talker_b_mode != BATTLE_CHARMODE_NONE ||
					talked_b_mode != BATTLE_CHARMODE_NONE){
			 	return FALSE;
			}
			return TRUE;
		}
	}
	return FALSE;

#else
	int		MyBattleMode;
	int		ToBattleMode;

	MyBattleMode = CHAR_getWorkInt( talkerindex, CHAR_WORKBATTLEMODE);
	ToBattleMode = CHAR_getWorkInt( talkedindex, CHAR_WORKBATTLEMODE);

	/*   锟斤拷    锟斤拷锟斤拷 */
	if( MyBattleMode == BATTLE_CHARMODE_NONE ) {
		if( ToBattleMode == BATTLE_CHARMODE_NONE ) {
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	/* 锟斤拷    锟斤拷锟斤拷 */
	else {
		/* 锟斤拷  锟狡伙拷锟斤拷卅锟斤拷锟叫卞反霜锟斤拷卅锟叫ｏ拷 */
		if( ToBattleMode == BATTLE_CHARMODE_NONE) {
			return FALSE;
		}
		/*   元锟斤拷  匹  元锟斤拷锟斤拷锟斤拷锟叫憋拷锟狡撅拷霜锟斤拷锟斤拷  卅锟斤拷 */
		if( CHAR_getWorkInt( talkerindex, CHAR_WORKBATTLEINDEX)
			== CHAR_getWorkInt( talkedindex, CHAR_WORKBATTLEINDEX) &&
			CHAR_getWorkInt( talkerindex, CHAR_WORKBATTLESIDE)
			== CHAR_getWorkInt( talkedindex, CHAR_WORKBATTLESIDE ) )
		{
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	return FALSE;
#endif
}

void CHAR_Talk( int fd, int index,char* message,int color, int area )
{
	char    firstToken[64];
	char    messageeraseescape[512];
	char*   messagebody;
	int     mesgvolume=0;
	int     lastvolume=0;
	int     fl,x,y;
	int     stringlen;
	int		micflg = 0;

	int	fmindexi = CHAR_getWorkInt( index, CHAR_WORKFMINDEXI );
	int	channel = CHAR_getWorkInt( index, CHAR_WORKFMCHANNEL );
	int	quickchannel = CHAR_getWorkInt( index, CHAR_WORKFMCHANNELQUICK );
	{
		char   *cdkey = CHAR_getChar( index, CHAR_CDKEY);
		char *charname = CHAR_getChar( index, CHAR_NAME);
		if( strlen(message) > 3 ){
			if( CHAR_getWorkInt( index, CHAR_WORKFLG) & WORKFLG_DEBUGMODE )	{
				// shan begin
				if(strstr( message, "[")&&strstr( message, "]")){
				}else{
					// original
					LogTalk( charname, cdkey, CHAR_getInt( index, CHAR_FLOOR),
							 CHAR_getInt( index, CHAR_X), CHAR_getInt( index, CHAR_Y),
							 message );
				}
				// end
			}
		}
	}
	//bg|0|r0|fc|d4B8|p0|bn|10|bt|10| 
	// Nuke +1 08/27: For invalid message attack
  if ( *message == 0 )
    return ;
	CHAR_getMessageBody(message,firstToken,sizeof(firstToken),
						&messagebody);
        // Nuke +1: For invalid message attack
  if ( !messagebody )
    return ;
                						
	strcpysafe( messageeraseescape,sizeof(messageeraseescape),
				messagebody );
	makeStringFromEscaped( messageeraseescape );
	stringlen = strlen(  messageeraseescape  );
  if ( stringlen <= 0 )
    return ;
   
	if( messageeraseescape[0] == '['
		&& messageeraseescape[stringlen-1] == ']' ){
		char gm[128];
		char* pass = strstr( messageeraseescape+1, getChatMagicPasswd());
		// Arminius: limit ip +2
		unsigned long ip;
		int a,b,c,d,ck;
		messageeraseescape[stringlen-1] = '\0';
		// Arminius: limit ip
		ip=CONNECT_get_userip(fd);
		    
		a=(ip % 0x100); ip=ip / 0x100;
		b=(ip % 0x100); ip=ip / 0x100;
		c=(ip % 0x100); ip=ip / 0x100;
		d=(ip % 0x100);

		if( pass == messageeraseescape+1 ){
			
			if(CHAR_useChatMagic( index,messageeraseescape + 1
							   + strlen(getChatMagicPasswd()) + 1, TRUE)){
				print( "\n锟剿猴拷:%s 锟斤拷锟斤拷:%s\n锟斤拷锟斤拷ip:%d.%d.%d.%d\n使锟斤拷GM锟斤拷锟斤拷%s]\n",CHAR_getChar( index, CHAR_CDKEY), 
															CHAR_getChar( index, CHAR_NAME), a, b, c, d,messageeraseescape);
				sprintf( gm, "锟斤拷使锟斤拷GM锟斤拷锟斤拷%s]锟窖成癸拷", messageeraseescape);
				CHAR_talkToCli( index, -1,gm, CHAR_COLORYELLOW );								
			}
		}else{
			if( CHAR_getWorkInt( index, CHAR_WORKFLG ) & WORKFLG_DEBUGMODE ) {
				if(CHAR_useChatMagic( index,messageeraseescape + 1,TRUE)){
					print( "\n锟剿猴拷:%s 锟斤拷锟斤拷:%s\n锟斤拷锟斤拷ip:%d.%d.%d.%d\n使锟斤拷GM锟斤拷锟斤拷%s]\n",CHAR_getChar( index, CHAR_CDKEY), 
															CHAR_getChar( index, CHAR_NAME), a, b, c, d,messageeraseescape);
					sprintf( gm, "锟斤拷使锟斤拷GM锟斤拷锟斤拷%s]锟窖成癸拷", messageeraseescape);
					CHAR_talkToCli( index, -1,gm, CHAR_COLORYELLOW );
				}
			}else{
#ifdef _GM_ITEM
				if(CHAR_getInt( index, CHAR_GMTIME)>0){
					char magicname[32];
					char token[64];
					getStringFromIndexWithDelim( messageeraseescape + 1, " ", 1, magicname,  sizeof( magicname));
					if(!strcmp( CHAR_getChar( index, CHAR_GMFUNCTION), magicname)){
						player_useChatMagic( index,messageeraseescape + 1,TRUE);
						print( "\n锟剿猴拷:%s 锟斤拷锟斤拷:%s\n锟斤拷锟斤拷ip:%d.%d.%d.%d\n使锟斤拷锟斤拷品锟斤拷锟斤拷%s]锟斤拷锟斤拷剩锟斤拷%d\n", CHAR_getChar( index, CHAR_CDKEY), 
															CHAR_getChar( index, CHAR_NAME), a, b, c, d,messageeraseescape, CHAR_getInt( index, CHAR_GMTIME) - 1);			
						CHAR_setInt( index , CHAR_GMTIME, CHAR_getInt( index, CHAR_GMTIME) - 1 );
						if(CHAR_getInt( index, CHAR_GMTIME) > 0){
							sprintf( token, "锟姐还锟斤拷使锟斤拷%s权锟斤拷%d锟斤拷!", CHAR_getChar( index, CHAR_GMFUNCTION),CHAR_getInt( index, CHAR_GMTIME));
							CHAR_talkToCli( index, -1,token, CHAR_COLORRED );
						}else{
							sprintf( token, "锟斤拷锟窖撅拷没锟斤拷使锟斤拷%s权锟斤拷锟斤拷!", CHAR_getChar( index, CHAR_GMFUNCTION));
							CHAR_talkToCli( index, -1,token, CHAR_COLORRED );
						}
					}else if(!strcmp( "help", magicname) || !strcmp( "锟斤拷锟斤拷", magicname)){
						getStringFromIndexWithDelim( messageeraseescape + 1, " ", 2, magicname,  sizeof( magicname));
						if(!strcmp( CHAR_getChar( index, CHAR_GMFUNCTION), magicname)){
							player_useChatMagic( index,messageeraseescape + 1,TRUE);
							print( "\n锟剿猴拷:%s 锟斤拷锟斤拷:%s\n锟斤拷锟斤拷ip:%d.%d.%d.%d\n使锟矫帮拷锟斤拷锟斤拷锟斤拷%s]\n", CHAR_getChar( index, CHAR_CDKEY), 
															CHAR_getChar( index, CHAR_NAME), a, b, c, d,messageeraseescape);
						}
					}
				}else
#endif
						CHAR_useChatMagic( index,messageeraseescape + 1,FALSE);
			}
		}
		messageeraseescape[stringlen-1] = ']';
		return;
	}else {
		if( CHAR_getWorkInt( index, CHAR_WORKFLG) & WORKFLG_DEBUGMODE ) {
			if( strstr( messageeraseescape, "[") != NULL ||
				strstr( messageeraseescape, "]") != NULL ){
				return;
			}
		}
	}
	
#ifdef _PLAYER_MOVE
	if(getPMove()!=-1){
		if(messageeraseescape[0] == '/' && messageeraseescape[1] == 'g' && messageeraseescape[2] == 'o'){
			int point=CHAR_getInt( index , CHAR_AMPOINT);
			if(point>getPMove() || getPMove()== 0 ){
				char x[4],y[4];
				easyGetTokenFromString( messageeraseescape , 2 , x, sizeof(x));
				easyGetTokenFromString( messageeraseescape , 3 , y, sizeof(y));
				CHAR_warpToSpecificPoint( index, CHAR_getInt( index, CHAR_FLOOR), atoi(x), atoi(y) );
				CHAR_setInt( index , CHAR_AMPOINT, point-getPMove());
			}else
					CHAR_talkToCli( index, -1,"锟斤拷锟窖撅拷没锟斤拷锟姐够锟侥伙拷员锟斤拷锟斤拷顺锟斤拷锟剿ｏ拷", CHAR_COLORRED );
			return;
			}
		}
#endif

#ifdef _PLAYER_ANNOUNCE
	if(getPAnnounce()!=-1){
		if(messageeraseescape[0] == '/' && messageeraseescape[1] == 'g' && messageeraseescape[2] == 'g'){
	
			int point=CHAR_getInt( index , CHAR_AMPOINT);
			if(point>getPAnnounce() || getPAnnounce()== 0 ){
				int i;
			  int playernum = CHAR_getPlayerMaxNum();
				char buff[255];
					char xlbmsg[255];
					char *MyName = CHAR_getChar( index,CHAR_NAME );
			
				easyGetTokenFromString( messageeraseescape , 2 , buff, sizeof(buff));
			  for( i = 0 ; i < playernum ; i++) {
			    if( CHAR_getCharUse(i) != FALSE ) 
			    	 	sprintf( xlbmsg, "<小锟斤拷锟斤拷>%s说锟斤拷%s", MyName, buff);
						 	CHAR_talkToCli( i, -1, xlbmsg, CHAR_COLORGREEN);
			  }
			  CHAR_setInt( index , CHAR_AMPOINT, point-getPAnnounce());
			}else
				CHAR_talkToCli( index, -1,"锟斤拷锟窖撅拷没锟斤拷锟姐够锟侥伙拷员锟斤拷锟斤拷小锟斤拷锟斤拷锟剿ｏ拷", CHAR_COLORRED );
			return;
		}
	}
#endif

#ifdef _TALK_ACTION
	TalkAction(index, messageeraseescape);
#endif	
{
	char token[128];
	sprintf(token,"%d",getCheckVip());
	int len=strlen(token);
}

	mesgvolume = CHAR_getVolume( messageeraseescape );
	if( area == 0 ) area = 3;
	if( mesgvolume == -1 )		lastvolume = -1;
	else lastvolume = area - 1 + mesgvolume;
	if( CHAR_getWorkInt( index, CHAR_WORKFLG ) & WORKFLG_MICMODE ){
		lastvolume = 15;
		micflg = 1;
	}
	fl = CHAR_getInt( index, CHAR_FLOOR) ;
	x  = CHAR_getInt( index, CHAR_X) ;
	y  = CHAR_getInt( index, CHAR_Y) ;
	// Robin 0705 channel
	if( messageeraseescape[0] == ':'){
		if( (channel == -1) && (quickchannel != -1) )
			channel = quickchannel;
		else if( channel != -1 )
			channel = -1;
	}	
	{
		typedef void (*TALKF)(int,int,char*,int,int);
		TALKF   talkedfunc=NULL;
		talkedfunc = (TALKF)CHAR_getFunctionPointer(index, CHAR_TALKEDFUNC);
		if( talkedfunc ) {
			talkedfunc(index,index,messageeraseescape,color, channel);
		}

	}
	if( lastvolume == -1 ){
		int     j;
		int xx[2]={ x, x+CHAR_getDX(CHAR_getInt(index,CHAR_DIR))};
		int yy[2]={ y, y+CHAR_getDY(CHAR_getInt(index,CHAR_DIR))};
		BOOL talk=FALSE;
		for( j=0 ; j<2 ; j ++ ){
			OBJECT  object;
			for( object=MAP_getTopObj(fl,xx[j],yy[j]) ; object ; object = NEXT_OBJECT( object ) ){
				int objindex = GET_OBJINDEX(object);
				int	toindex = OBJECT_getIndex( objindex);
				if( OBJECT_getType(objindex) == OBJTYPE_CHARA && toindex != index ){
					if( CHAR_Talk_check( index, toindex, 0 )) {
						typedef void (*TALKF)(int,int,char*,int,int);
						TALKF   talkedfunc=NULL;
						talkedfunc = (TALKF)CHAR_getFunctionPointer( toindex, CHAR_TALKEDFUNC);
						if( talkedfunc ) {
							talkedfunc(toindex,   index,messageeraseescape,color,-1);
						}
						if( CHAR_getInt(toindex, CHAR_WHICHTYPE) == CHAR_TYPEPLAYER){
							talk = TRUE;
						}
					}
				}
			}
		}
		if( talk )CHAR_setInt(index,CHAR_TALKCOUNT, CHAR_getInt( index, CHAR_TALKCOUNT) + 1);
	}else{
		int range = CHAR_getRangeFromVolume( lastvolume );
		int i,j;
		BOOL    talk=FALSE;
		BOOL	channelTalk=FALSE;
		int		partyindex[CHAR_PARTYMAX];
		for( i = 0; i < CHAR_PARTYMAX; i ++ ) {
			partyindex[i] = -1;
		}
		if( CHAR_getWorkInt( index, CHAR_WORKPARTYMODE) != CHAR_PARTY_NONE )
		{
			for( i = 0; i < CHAR_PARTYMAX; i ++ ) {
				int toindex = CHAR_getPartyIndex( index, i);
				if( CHAR_CHECKINDEX( toindex) && toindex != index) {
					typedef void (*TALKF)(int,int,char*,int,int);
					TALKF   talkedfunc=NULL;
					talkedfunc = (TALKF)CHAR_getFunctionPointer( toindex, CHAR_TALKEDFUNC);
					if( talkedfunc )
						talkedfunc( toindex,index, messageeraseescape, color, -1 );
					talk = TRUE;
					partyindex[i] = toindex;
				}
			}
		}
		if( channel > -1 && fmindexi >= 0 ) {
			int i, tindex;

			channelTalk = TRUE;
			i = 0;
#ifdef _FMVER21			
			if( channel == FAMILY_MAXCHANNEL && CHAR_getInt( index, CHAR_FMLEADERFLAG ) == FMMEMBER_LEADER)
#else
			if( channel == FAMILY_MAXCHANNEL && CHAR_getInt( index, CHAR_FMLEADERFLAG ) == 1)
#endif			
			{
				char buf[512];
				sprintf(buf, "[锟藉长锟姐播]%s: %s", CHAR_getChar( index, CHAR_NAME ), messageeraseescape);
				saacproto_ACFMAnnounce_send( acfd, 
					CHAR_getChar( index, CHAR_FMNAME), 
					CHAR_getInt( index, CHAR_FMINDEX),
					CHAR_getWorkInt( index, CHAR_WORKFMINDEXI),
					buf,
					color
				);
				return;			
			}
			else
			
				for(i=0;i<FAMILY_MAXMEMBER;i++){
					tindex = channelMember[fmindexi][channel][i];
          if ( !CHAR_CHECKINDEX( tindex ) )
            continue;
					if( tindex >= 0 && tindex != index) {
						typedef void (*TALKF)(int,int,char*,int,int);
						TALKF   talkedfunc=NULL;
						
						talkedfunc = (TALKF)CHAR_getFunctionPointer(tindex,CHAR_TALKEDFUNC);
						
						if( talkedfunc )
							talkedfunc( tindex,index, messageeraseescape, color, channel );
					}
				}
									
			talk = TRUE;
			
		}else {
			for( i=x-range/2 ; i<=x+range/2 ; i++ ){
				for( j=y-range/2 ; j<=y+range/2 ; j++ ){
					OBJECT  object;
					for( object = MAP_getTopObj( fl,i,j ) ; object ; object = NEXT_OBJECT(object) ){
						int objindex = GET_OBJINDEX(object);
						int	toindex = OBJECT_getIndex( objindex);
						if( OBJECT_getType(objindex) == OBJTYPE_CHARA && toindex != index ){
							int k;
							for( k = 0; k < CHAR_PARTYMAX; k ++ ) {
								if( toindex == partyindex[k] ) {
									break;
								}
							}
							if( k != CHAR_PARTYMAX )
								continue;
							if( CHAR_Talk_check( index, toindex, micflg ) ) {
								typedef void (*TALKF)(int,int,char*,int,int);
								TALKF   talkedfunc=NULL;
								talkedfunc = (TALKF)CHAR_getFunctionPointer( toindex, CHAR_TALKEDFUNC);
								if( talkedfunc ) {
									talkedfunc( toindex,index, messageeraseescape, color, -1 );
								}
								if( CHAR_getInt( toindex, CHAR_WHICHTYPE) == CHAR_TYPEPLAYER){
									talk = TRUE;
								}
							}
						}
					}
				}
			}
		}
		if( talk ) {
			CHAR_setInt(index,CHAR_TALKCOUNT, CHAR_getInt(index,CHAR_TALKCOUNT) + 1);
		}
		if( CHAR_getInt( index, CHAR_POPUPNAMECOLOR) != color ) {
			CHAR_setInt( index, CHAR_POPUPNAMECOLOR, color);
			if( talk) {
			int opt[1];
				opt[0] = color;
				CHAR_sendWatchEvent( CHAR_getWorkInt( index, CHAR_WORKOBJINDEX),
									CHAR_ACTPOPUPNAME,opt,1,FALSE);
			}
		}
	}
}

BOOL CHAR_talkToCli( int talkedcharaindex,int talkcharaindex,
					 char* message, CHAR_COLOR color )
{
	static char    lastbuf[2048];
	static char    escapebuf[2048];
	static char    mesgbuf[1024];
	int fd;
	int     talkchar=-1;

  if ( !CHAR_CHECKINDEX( talkedcharaindex ) )
    return FALSE;
	if( CHAR_getInt( talkedcharaindex,CHAR_WHICHTYPE ) != CHAR_TYPEPLAYER){
		print("err CHAR_talkToCli CHAR_WHICHTYPE != CHAR_TYPEPLAYER\n");
		return FALSE;
	}
	
	fd = getfdFromCharaIndex( talkedcharaindex );	
	if( fd == -1 ){
		print("err CHAR_talkToCli can't get fd from:%d \n", talkedcharaindex);
		return FALSE;    
	}

	if( color < CHAR_COLORWHITE && color > CHAR_COLORGREEN2 ){
		print("CHAR_talkToCli color err\n");
		return FALSE;
	}
	snprintf( lastbuf, sizeof(lastbuf), "P|%s",
			makeEscapeString( CHAR_appendNameAndTitle(talkcharaindex, message, mesgbuf,sizeof(mesgbuf)),
			escapebuf,sizeof(escapebuf) ));
	if( talkcharaindex == -1 )
		talkchar = -1;
	else
		talkchar = CHAR_getWorkInt(talkcharaindex,CHAR_WORKOBJINDEX);
	lssproto_TK_send( fd, talkchar, lastbuf, color);
	return TRUE;
}

#ifdef _DROPSTAKENEW
void CHAR_talkToFloor(int floor, int talkindex, char* message, CHAR_COLOR color)
{
	int i = 0; 
	int playernum = CHAR_getPlayerMaxNum();
	for (i = 0; i < playernum; i++){
		if (CHAR_getCharUse(i) == FALSE) continue;
	  if ( !CHAR_CHECKINDEX( i ) )
	    continue;
	  if ( CHAR_getInt( i, CHAR_FLOOR ) == floor ) {
			if (CHAR_getWorkInt(i, CHAR_WORKBATTLEMODE) == BATTLE_CHARMODE_NONE)
				CHAR_talkToCli(i, talkindex, message, color);
		}
	}
}
#endif

#ifdef _TALK_ACTION
void TalkAction(int charaindex, char *message)
{
	int i;
	typedef struct{
		char talk[5];
		int action;
	}tagTlakAction;
	tagTlakAction TlakAction[13]={
		{ "锟斤拷锟斤拷", 11},{ "锟斤拷锟斤拷", 12},{ "锟斤拷头", 18},
		{ "锟斤拷锟斤拷", 13},{ "锟斤拷锟斤拷", 14},{ "锟斤拷锟斤拷", 15},
		{ "站锟斤拷", 19},{ "锟竭讹拷", 17},{ "锟轿碉拷", 10},
		{ "锟斤拷锟斤拷", 2 },{ "锟斤拷锟斤拷", 16},{ "锟斤拷锟斤拷", 4 },
		{ "投锟斤拷", 3 }
	};
	for(i=0;i<13;i++)
		if(strstr(message,TlakAction[i].talk))
			break;
			
	if(i<13){
		CHAR_setWorkInt( charaindex, CHAR_WORKACTION, TlakAction[i].action );
		CHAR_sendWatchEvent(CHAR_getWorkInt( charaindex, CHAR_WORKOBJINDEX),	TlakAction[i].action, NULL, 0, TRUE);
	}
}
#endif
#ifdef _GM_ITEM
static BOOL player_useChatMagic( int charaindex, char* data, BOOL isDebug)
{
	char    magicname[256];
	int     ret;
	
	CHATMAGICFUNC   func;

	ret = getStringFromIndexWithDelim( data, " ", 1, magicname,  sizeof( magicname));
	if( ret == FALSE)return FALSE;
	
	func = CHAR_getChatMagicFuncPointer(magicname,isDebug);
	
	if( func ){
		LogGM( CHAR_getUseName( charaindex), CHAR_getChar( charaindex, CHAR_CDKEY), data, 
			CHAR_getInt( charaindex, CHAR_FLOOR), CHAR_getInt( charaindex, CHAR_X),
			CHAR_getInt( charaindex, CHAR_Y) );
		func( charaindex, data + strlen( magicname)+1);
		return TRUE;
	}else{
		return FALSE;
	}
}
#endif

