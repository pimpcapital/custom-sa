#define __CONFIGFILE_C__
#include "version.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "util.h"
#include "lssproto_util.h"
#include "configfile.h"
#include "net.h"
#include "npcutil.h"
#include "char.h"
#include "char_data.h"
#include "lssproto_serv.h"

#ifdef _ANGEL_SUMMON
extern struct MissionInfo missionlist[MAXMISSION];
extern struct MissionTable missiontable[MAXMISSIONTABLE];
#endif

/* 涩烂毛忡  允月厌瞻   */
typedef struct tagConfig
{
    /*皿夫弘仿丞  (愤  读卞菲户凶中仃升引分蛲  */
  char    progname[8];
  char    configfilename[32]; /* config白央奶伙   */
    unsigned int debuglevel;   /* 犯田永弘伊矛伙 */
  unsigned int  usememoryunit;    /*丢乒伉及交瓦永玄扔奶术 */
  unsigned int  usememoryunitnum; /*丢乒伉及交瓦永玄醒 */
  char    asname[32];         /*失市它件玄扔□田及  蟆*/
  unsigned short  acservport; /*失市它件玄扔□田及禾□玄  */
  char    acpasswd[32];       /*失市它件玄扔□田尺及由旦伐□玉*/
  char    gsnamefromas[32];   /*
                                 * 失市它件玄扔□田井日苇尹月
                                 * 必□丞扔□田午仄化及  蟆
                                 */
                                 
    // Arminius 7.24 manor pk
  char gsid[32];	// game server chinese id
  unsigned short allowmanorpk;	// is this server allow manor pk
  unsigned short port;        /* 扔□田及谨切熬仃禾□玄 */
	int				servernumber;	/* 必□丞扔□田及  寞 */
	int				reuseaddr;	/* Address already used... 互鞅引日卅中凛及凶户卞 */
  int             do_nodelay;     /* TCP_NODELAY 卞允月井升丹井 */
  int             log_write_time; /* 踏五仇心夫弘毛允月井升丹井［ */
  int             log_io_time;    /* I/O蝈  及凛棉反井月井升丹井［ */
  int             log_game_time;  /* 必□丞及质  蝈  及凛棉毛反井月 */
  int             log_netloop_faster; /* netloop_faster 及夫弘 */
	int				saacwritenum;	/* 失市它件玄扔□田尺及窒谛  卞write允月井 */
	int				saacreadnum;	/* 失市它件玄扔□田井日及dispatch 毛窒荚允月井 */
  unsigned short fdnum;           /*升木分仃戊生弁扑亦件毛忡  允月井 */
  unsigned int   othercharnum;    /*  公及职及平乓仿及醒  */
  unsigned int objnum;            /* 左皮斥尼弁玄及    醒*/
  unsigned int   petcharnum;   	/* 矢永玄及醒    */
  unsigned int itemnum;           /* 失奶  丞及    醒*/
  unsigned int battlenum;         /* 田玄伙及    */
  unsigned int battleexp;         /* 田玄伙及    */
  char    topdir[32];         	/* 玄永皿犯奴伊弁玄伉  */
  char    mapdir[32];         	/* 穴永皿犯奴伊弁玄伉  */
  char    maptilefile[32];    	/* 穴永皿涩烂白央奶伙  */
  char    battlemapfile[32];    	/* 田玄伙穴永皿涩烂白央奶伙  */
  char    itemfile[32];       	/* 失奶  丞涩烂白央奶伙  */
  char    invfile[32];        	/*   衬涩烂白央奶伙  */
  char    appearfile[32];     	/* 请蜇匏  涩烂白央奶伙  */
	char	titlenamefile[32];		/* 惫寞白央奶伙   */
	char	titleconfigfile[32];	/* 惫寞涩烂白央奶伙   */
	char	encountfile[32];		/* 巨件市它件玄涩烂白央奶伙   */
	char	enemybasefile[32];		/* 衬湘  涩烂白央奶伙   */
	char	enemyfile[32];			/* 衬涩烂白央奶伙   */
	char	groupfile[32];			/* 弘伙□皿涩烂白央奶伙   */
	char	magicfile[32];			/* 热诸涩烂白央奶伙   */
#ifdef _ATTACK_MAGIC
  char    attmagicfile[32];       // 攻击性咒术
#endif

	char	petskillfile[32];		/* 矢永玄  热诸涩烂白央奶伙   */
  char    itematomfile[32];       /* 失奶  丞及笺    白央奶伙 */
  char    effectfile[32];     	/* 梢请涩烂白央奶伙  */
  char    quizfile[32];     		/* 弁奶术涩烂白央奶伙  */
  char    lsgenlog[32];       /*扔□田及lsgen 失它玄皿永玄白央奶伙  */
  char    storedir[128];       /*旦玄失犯奴伊弁玄伉    */
  char    npcdir[32];         /*NPC及涩烂白央奶伙毛  仁犯奴伊弁玄伉   */
  char    logdir[32];         /*
                               * 夫弘犯奴伊弁玄伉
                               */
  char    logconfname[32];    /*
                               * 夫弘涩烂白央奶伙  
                               */
  char	chatmagicpasswd[32];	/* 民乓永玄  芊由旦伐□玉 */
#ifdef _STORECHAR
  char	storechar[32];
#endif
	unsigned int 	chatmagiccdkeycheck;	/* 民乓永玄  芊匹CDKEY毛民尼永弁允月井 */
  unsigned int    filesearchnum;     /*白央奶伙毛腹绸匹五月白央奶伙及醒*/
  unsigned int    npctemplatenum;     /*NPC及  件皿伊□玄白央奶伙及醒*/
  unsigned int    npccreatenum;       /*NPC及戏遣白央奶伙及醒*/
  unsigned int    walksendinterval;   /* 汹仁及毛霜月棉厥 */
  unsigned int    CAsendinterval_ms;     /* CA毛霜月棉厥 (ms)*/
  unsigned int    CDsendinterval_ms;     /* CD毛霜月棉厥 (ms)*/
  unsigned int    Onelooptime_ms;     	/* 1伙□皿卞井仃月凛棉 */
	unsigned int	Petdeletetime;		/* 矢永玄互壅  允月凛棉 */
	unsigned int	Itemdeletetime;		/* 失奶  丞互壅  允月凛棉 */
    /* 夫弘奶件  及平乓仿及本□皮毛允月棉厥 */
  unsigned int    CharSavesendinterval;
  unsigned int    addressbookoffmsgnum;  /*
                                          * 失玉伊旦皮永弁卞左白仿奶件
                                          * 丢永本□斥毛
                                          * 窒丢永本□斥酸六月井
                                          */
  unsigned int    protocolreadfrequency;  /*
                                           * 皿夫玄戊伙毛窒立伉    
                                           * 卞  戈井
                                           */
  unsigned int    allowerrornum;          /*
                                           * 巨仿□毛窒蜊引匹袱允井
                                           */
  unsigned int    loghour;          		/*
                                           * 夫弘毛忡绣允月凛对  ＂凛  
                                           */
  unsigned int    battledebugmsg;    		/*
                                           * 田玄伙  及犯田永弘丢永本□斥毛请允井［ㄟ卅日请今卅中
                                           */
  //ttom add this because the second had this                                         
  unsigned int    encodekey;              
  unsigned int    acwbsize;             
  unsigned int    acwritesize;
  unsigned int    ErrUserDownFlg;
  //ttom end
#ifdef _GMRELOAD
	char	gmsetfile[32];				/* GM帐号、权限设定档 */
#endif
#ifdef _ITEM_QUITPARTY
    char itemquitparty[32];
#endif

#ifdef _DEL_DROP_GOLD	
	unsigned int	Golddeletetime;
#endif
#ifdef _NEW_PLAYER_CF
	int	newplayertrans;
	int	newplayerlv;
	int	newplayergivepet[5];
	int newplayergiveitem[15];
	int	newplayerpetlv;
	int newplayergivegold;
	int ridepetlevel;
#ifdef _VIP_SERVER
	int	newplayerpetvip;
#endif
#ifdef _JZ_CF_DELPETITEM
	int DelPet[5];
	int DelItem[5];
#endif
#endif
#ifdef _USER_EXP_CF
	char	expfile[64];
#endif
#ifdef _UNLAW_WARP_FLOOR
	int	unlawwarpfloor[10];
#endif
#ifdef _WATCH_FLOOR
	int	watchfloor[6];
#endif
#ifdef _BATTLE_FLOOR
	int	battlefloor[6];
#endif
#ifdef _UNREG_NEMA
	char	unregname[5][16];
#endif
#ifdef _TRANS_LEVEL_CF
	int chartrans;
	int pettrans;
	int yblevel;
	int maxlevel;
#endif
#ifdef _POINT
int point;
	int transpoint[8];
#endif
#ifdef _VIP_SERVER
	int vippoint;
#endif
#ifdef _PET_UP
	int petup;
#endif
#ifdef _LOOP_ANNOUNCE
	char loopannouncepath[32];
	int loopannouncetime;
	char loopannounce[10][1024];
	int loopannouncemax;
#endif
#ifdef _SKILLUPPOINT_CF
	int skup;
#endif
#ifdef _RIDELEVEL
	int ridelevel;
#endif
#ifdef _REVLEVEL
	int revlevel;
#endif
#ifdef _NEW_PLAYER_RIDE
	int npride;
#endif
#ifdef _FIX_CHARLOOPS
	int charloops;
#endif
#ifdef _PLAYER_ANNOUNCE
	int pannounce;
#endif
#ifdef _PLAYER_MOVE
	int pmove;
#endif
	int recvbuffer;
	int sendbuffer;
	int recvlowatbuffer;
	int runlevel;
#ifdef _SHOW_VIP_CF
	int showvip;
#endif
#ifdef _PLAYER_NUM
	int playernum;
#endif
#ifdef _BATTLE_GOLD
	int battlegold;
#endif
#ifdef _ANGEL_TIME
	int angelplayertime;
	int angelplayermun;
#endif
#ifdef _RIDEMODE_20
	int ridemode;
#endif
#ifdef _FM_POINT_PK
	int fmpointpk;
#endif
#ifdef _ENEMY_ACTION
	int	enemyact;
#endif

#ifdef _CHECK_PEPEAT
	int	CheckRepeat;
#endif
	int	cpuuse;
#ifdef _VIP_ALL
	int	checkvip;
#endif
#ifdef _FM_JOINLIMIT
	int	joinfamilytime;
#endif
}Config;

Config config;


typedef struct tagReadConf
{
    char    name[32];
    char  *charvalue;
    size_t  charsize;
    void*    value;
    CTYPE    valuetype;
}ReadConf;

ReadConf readconf[]=
{
    { "debuglevel"      , NULL ,0 , (void*)&config.debuglevel      ,CHAR},

    { "usememoryunit"   , NULL ,0 , (void*)&config.usememoryunit   ,INT},
    { "usememoryunitnum", NULL ,0 , (void*)&config.usememoryunitnum,INT},

    { "acserv",			config.asname,sizeof(config.asname) ,NULL , 0},
    { "acservport",		NULL ,0 , (void*)&config.acservport     ,SHORT},
    { "acpasswd",		config.acpasswd,sizeof( config.acpasswd),NULL,0},
    { "gameservname",	config.gsnamefromas,sizeof(config.gsnamefromas),
     NULL,0},

    // Arminius 7.24 manor pk
    { "gameservid", config.gsid, sizeof(config.gsid), NULL, 0}, 
    { "allowmanorpk", NULL, 0, (void*)&config.allowmanorpk, SHORT},

    { "port",			NULL ,0 , (void*)&config.port           ,SHORT},
    { "servernumber",	NULL ,0 , (void*)&config.servernumber           ,INT},

    { "reuseaddr",			NULL ,0 , (void*)&config.reuseaddr  ,		INT},
    { "nodelay",			NULL , 0 , (void*)&config.do_nodelay ,		INT},
    { "log_write_time", 	NULL, 0 , (void*)&config.log_write_time,	INT},
    { "log_io_time", 		NULL, 0 , (void*)&config.log_io_time, 		INT},
    { "log_game_time",		NULL, 0 , (void*)&config.log_game_time,		INT},
    { "log_netloop_faster", NULL,0,(void*)&config.log_netloop_faster,	INT},
    { "saacwritenum",		NULL,0,(void*)&config.saacwritenum, 		INT},
    { "saacreadnum",		NULL,0,(void*)&config.saacreadnum, 			INT},
    { "fdnum",				NULL ,0 , (void*)&config.fdnum,				SHORT},
    { "petnum",				NULL ,0 , (void*)&config.petcharnum,		INT},
    { "othercharnum",		NULL ,0 , (void*)&config.othercharnum,		INT},

    { "objnum",			NULL ,0 , (void*)&config.objnum,				INT},
    { "itemnum",		NULL ,0 , (void*)&config.itemnum,				INT},
    { "battlenum",		NULL ,0 , (void*)&config.battlenum,				INT},
    { "battleexp",		NULL ,0 , (void*)&config.battleexp,				INT},
    { "topdir"          , config.topdir,sizeof(config.topdir),NULL,0},
    { "mapdir"          , config.mapdir,sizeof(config.mapdir),NULL,0},
    { "maptilefile"     , config.maptilefile,sizeof(config.maptilefile),NULL,0},
    { "battlemapfile"   , config.battlemapfile,sizeof(config.battlemapfile),NULL,0},

#ifdef _ITEMSET6_TXT
	{ "itemset6file",	config.itemfile,	sizeof(config.invfile),	NULL,	0},
#else
#ifdef _ITEMSET5_TXT
	{ "itemset5file",	config.itemfile,	sizeof(config.invfile),	NULL,	0},
#else
#ifdef _ITEMSET4_TXT
	{ "itemset4file"  , config.itemfile,sizeof(config.invfile),NULL,0},
#else
#ifdef _ITEMSET3_ITEM
	{ "itemset3file"  , config.itemfile,sizeof(config.invfile),NULL,0},
#endif
#endif
#endif
#endif
  { "invinciblefile"  , config.invfile,sizeof(config.invfile),NULL,0},
  { "appearpositionfile"  , config.appearfile,sizeof(config.appearfile),NULL,0},
	{ "titlenamefile", config.titlenamefile, sizeof( config.titlenamefile),NULL,0},
	{ "titleconfigfile", config.titleconfigfile, sizeof( config.titleconfigfile),NULL,0},
	{ "encountfile", config.encountfile, sizeof( config.encountfile),NULL,0},
	{ "enemyfile", config.enemyfile, sizeof( config.enemyfile),NULL,0},
	{ "enemybasefile", config.enemybasefile, sizeof( config.enemybasefile),NULL,0},
	{ "groupfile", config.groupfile, sizeof( config.groupfile),NULL,0},
	{ "magicfile", config.magicfile, sizeof( config.magicfile),NULL,0},
#ifdef _ATTACK_MAGIC
	{ "attmagicfile" , config.attmagicfile , sizeof( config.attmagicfile )  , NULL , 0 },
#endif

#ifdef _PETSKILL2_TXT
	{ "petskillfile2", config.petskillfile, sizeof( config.petskillfile),NULL,0},
#else
	{ "petskillfile1", config.petskillfile, sizeof( config.petskillfile),NULL,0},
#endif

    { "itematomfile" , config.itematomfile, sizeof( config.itematomfile),NULL,0},
    { "effectfile"  , config.effectfile,sizeof(config.effectfile),NULL,0},
    { "quizfile"  , config.quizfile,sizeof(config.quizfile),NULL,0},

    { "lsgenlogfilename", config.lsgenlog,sizeof(config.lsgenlog),NULL,0},
#ifdef _GMRELOAD
	{ "gmsetfile", config.gmsetfile, sizeof( config.gmsetfile),NULL,0},
#endif

    { "storedir"        ,config.storedir,sizeof(config.storedir),NULL,0},
    { "npcdir"          ,config.npcdir,sizeof(config.npcdir),NULL,0},
    { "logdir"          ,config.logdir,sizeof(config.logdir),NULL,0},
    { "logconfname"     ,config.logconfname,sizeof(config.logconfname),NULL,0},
    { "chatmagicpasswd", config.chatmagicpasswd, sizeof( config.chatmagicpasswd),NULL,0},
#ifdef _STORECHAR
    { "storechar", config.storechar, sizeof( config.storechar),NULL,0},
#endif
    { "chatmagiccdkeycheck",  NULL,0, &config.chatmagiccdkeycheck,INT},
    { "filesearchnum",  NULL,0, &config.filesearchnum,INT},
    { "npctemplatenum",  NULL,0, &config.npctemplatenum,INT},
    { "npccreatenum",    NULL,0, &config.npccreatenum,INT},
    { "walkinterval" ,NULL,0,(void*)&config.walksendinterval,INT},
    { "CAinterval" ,NULL,0,(void*)&config.CAsendinterval_ms,INT},
    { "CDinterval" ,NULL,0,(void*)&config.CDsendinterval_ms,INT},
    { "CharSaveinterval" ,NULL,0,(void*)&config.CharSavesendinterval,INT},
    { "Onelooptime" ,NULL,0,(void*)&config.Onelooptime_ms,INT},
    { "Petdeletetime" ,NULL,0,(void*)&config.Petdeletetime,INT},
    { "Itemdeletetime" ,NULL,0,(void*)&config.Itemdeletetime,INT},
	 { "addressbookoffmesgnum" ,NULL,0,
      (void*)&config.addressbookoffmsgnum,INT},

    { "protocolreadfrequency" ,NULL,0,
      (void*)&config.protocolreadfrequency,INT},

    { "allowerrornum" ,NULL,0,(void*)&config.allowerrornum,INT},
    { "loghour" ,NULL,0,(void*)&config.loghour,INT},
    { "battledebugmsg" ,NULL,0,(void*)&config.battledebugmsg,INT},
    //ttom add because the second had
    { "encodekey" ,NULL,0,(void*)&config.encodekey,INT},
    { "acwritesize" ,NULL,0,(void*)&config.acwritesize,INT},
    { "acwbsize" ,NULL,0,(void*)&config.acwbsize,INT},
    { "erruser_down" ,NULL,0,(void*)&config.ErrUserDownFlg,INT},    

#ifdef _ITEM_QUITPARTY
    { "itemquitparty",	config.itemquitparty, sizeof(config.itemquitparty) ,NULL , 0},
#endif

#ifdef _DEL_DROP_GOLD
	{ "Golddeletetime" ,NULL,0,(void*)&config.Golddeletetime,	INT},
#endif

#ifdef _NEW_PLAYER_CF
	{ "TRANS" ,NULL,0,(void*)&config.newplayertrans,	INT},
	{ "LV" ,NULL,0,(void*)&config.newplayerlv,	INT},	
	{ "PET1" ,NULL,0,(void*)&config.newplayergivepet[1],	INT},
	{ "PET2" ,NULL,0,(void*)&config.newplayergivepet[2],	INT},	
	{ "PET3" ,NULL,0,(void*)&config.newplayergivepet[3],	INT},	
	{ "PET4" ,NULL,0,(void*)&config.newplayergivepet[4],	INT},	
	{ "ITEM1" ,NULL,0,(void*)&config.newplayergiveitem[0],	INT},
	{ "ITEM2" ,NULL,0,(void*)&config.newplayergiveitem[1],	INT},	
	{ "ITEM3" ,NULL,0,(void*)&config.newplayergiveitem[2],	INT},	
	{ "ITEM4" ,NULL,0,(void*)&config.newplayergiveitem[3],	INT},	
	{ "ITEM5" ,NULL,0,(void*)&config.newplayergiveitem[4],	INT},
	{ "ITEM6" ,NULL,0,(void*)&config.newplayergiveitem[5],	INT},	
	{ "ITEM7" ,NULL,0,(void*)&config.newplayergiveitem[6],	INT},	
	{ "ITEM8" ,NULL,0,(void*)&config.newplayergiveitem[7],	INT},	
	{ "ITEM9" ,NULL,0,(void*)&config.newplayergiveitem[8],	INT},
	{ "ITEM10" ,NULL,0,(void*)&config.newplayergiveitem[9],	INT},	
	{ "ITEM11" ,NULL,0,(void*)&config.newplayergiveitem[10],	INT},	
	{ "ITEM12" ,NULL,0,(void*)&config.newplayergiveitem[11],	INT},	
	{ "ITEM13" ,NULL,0,(void*)&config.newplayergiveitem[12],	INT},	
	{ "ITEM14" ,NULL,0,(void*)&config.newplayergiveitem[13],	INT},	
	{ "ITEM15" ,NULL,0,(void*)&config.newplayergiveitem[14],	INT},
	{ "PETLV" ,NULL,0,(void*)&config.newplayerpetlv,	INT},	
	{ "GOLD" ,NULL,0,(void*)&config.newplayergivegold,	INT},
	{ "RIDEPETLEVEL" ,NULL,0,(void*)&config.ridepetlevel,	INT},
#ifdef _VIP_SERVER
	{ "GIVEVIPPOINT" ,NULL,0,(void*)&config.newplayerpetvip,	INT},
#endif
#endif

#ifdef _USER_EXP_CF
	{ "USEREXP", config.expfile, sizeof( config.expfile),NULL,0},
#endif

#ifdef _UNLAW_WARP_FLOOR
	{ "FLOOR1" ,NULL,0,(void*)&config.unlawwarpfloor[0],	INT},
	{ "FLOOR2" ,NULL,0,(void*)&config.unlawwarpfloor[1],	INT},	
	{ "FLOOR3" ,NULL,0,(void*)&config.unlawwarpfloor[2],	INT},	
	{ "FLOOR4" ,NULL,0,(void*)&config.unlawwarpfloor[3],	INT},	
	{ "FLOOR5" ,NULL,0,(void*)&config.unlawwarpfloor[4],	INT},
	{ "FLOOR6" ,NULL,0,(void*)&config.unlawwarpfloor[5],	INT},
	{ "FLOOR7" ,NULL,0,(void*)&config.unlawwarpfloor[6],	INT},	
	{ "FLOOR8" ,NULL,0,(void*)&config.unlawwarpfloor[7],	INT},	
	{ "FLOOR6" ,NULL,0,(void*)&config.unlawwarpfloor[8],	INT},	
	{ "FLOOR10" ,NULL,0,(void*)&config.unlawwarpfloor[9],	INT},
#endif

#ifdef _WATCH_FLOOR
	{ "WATCHFLOOR" ,NULL,0,(void*)&config.watchfloor[0],	INT},
	{ "WATCHFLOOR1" ,NULL,0,(void*)&config.watchfloor[1],	INT},
	{ "WATCHFLOOR2" ,NULL,0,(void*)&config.watchfloor[2],	INT},	
	{ "WATCHFLOOR3" ,NULL,0,(void*)&config.watchfloor[3],	INT},	
	{ "WATCHFLOOR4" ,NULL,0,(void*)&config.watchfloor[4],	INT},	
	{ "WATCHFLOOR5" ,NULL,0,(void*)&config.watchfloor[5],	INT},
#endif

#ifdef _BATTLE_FLOOR
	{ "BATTLEFLOOR" ,NULL,0,(void*)&config.battlefloor[0],	INT},
	{ "BATTLEFLOOR1" ,NULL,0,(void*)&config.battlefloor[1],	INT},
	{ "BATTLEFLOOR2" ,NULL,0,(void*)&config.battlefloor[2],	INT},	
	{ "BATTLEFLOOR3" ,NULL,0,(void*)&config.battlefloor[3],	INT},	
	{ "BATTLEFLOOR4" ,NULL,0,(void*)&config.battlefloor[4],	INT},	
	{ "BATTLEFLOOR5" ,NULL,0,(void*)&config.battlefloor[5],	INT},
#endif

#ifdef _UNREG_NEMA
	{ "NAME1" ,config.unregname[0], sizeof( config.unregname[0]),NULL,0},
	{ "NAME2" ,config.unregname[1], sizeof( config.unregname[1]),NULL,0},
	{ "NAME3" ,config.unregname[2], sizeof( config.unregname[2]),NULL,0},
	{ "NAME4" ,config.unregname[3], sizeof( config.unregname[3]),NULL,0},
	{ "NAME5" ,config.unregname[4], sizeof( config.unregname[4]),NULL,0},
#endif
#ifdef _TRANS_LEVEL_CF
	{ "CHARTRANS" ,NULL,0,(void*)&config.chartrans,	INT},
	{ "PETTRANS" ,NULL,0,(void*)&config.pettrans,	INT},	
	{ "LEVEL" ,NULL,0,(void*)&config.yblevel,	INT},	
	{ "MAXLEVEL" ,NULL,0,(void*)&config.maxlevel,	INT},	
#endif
#ifdef _POINT
	{ "POINT" ,NULL,0,(void*)&config.point,	INT},
	{ "TRANS0" ,NULL,0,(void*)&config.transpoint[0],	INT},	
	{ "TRANS1" ,NULL,0,(void*)&config.transpoint[1],	INT},	
	{ "TRANS2" ,NULL,0,(void*)&config.transpoint[2],	INT},	
	{ "TRANS3" ,NULL,0,(void*)&config.transpoint[3],	INT},	
	{ "TRANS4" ,NULL,0,(void*)&config.transpoint[4],	INT},	
	{ "TRANS5" ,NULL,0,(void*)&config.transpoint[5],	INT},	
	{ "TRANS6" ,NULL,0,(void*)&config.transpoint[6],	INT},	
	{ "TRANS7" ,NULL,0,(void*)&config.transpoint[7],	INT},	
#endif

#ifdef _PET_UP
	{ "PETUP" ,NULL,0,(void*)&config.petup,	INT},
#endif
#ifdef _LOOP_ANNOUNCE
	{ "ANNOUNCEPATH" ,config.loopannouncepath, sizeof( config.loopannouncepath),NULL,0},
	{ "ANNOUNCETIME" ,NULL,0,(void*)&config.loopannouncetime,	INT},
#endif
#ifdef _SKILLUPPOINT_CF
	{ "SKILLUPPOINT" ,NULL,0,(void*)&config.skup,	INT},	
#endif
#ifdef _RIDELEVEL
	{ "RIDELEVEL" ,NULL,0,(void*)&config.ridelevel,	INT},	
#endif

#ifdef _REVLEVEL
	{ "REVLEVEL" ,NULL,0,(void*)&config.revlevel,	INT},	
#endif
#ifdef _NEW_PLAYER_RIDE
	{ "NPRIDE" ,NULL,0,(void*)&config.npride,	INT},	
#endif
#ifdef _FIX_CHARLOOPS
	{ "CHARLOOPS" ,NULL,0,(void*)&config.charloops,	INT},	
#endif
#ifdef _PLAYER_ANNOUNCE
	{ "PANNOUNCE" ,NULL,0,(void*)&config.pannounce,	INT},
#endif
#ifdef _PLAYER_MOVE
	{ "PMOVE" ,NULL,0,(void*)&config.pmove,	INT},
#endif

	{ "recvbuffer" ,NULL,0,(void*)&config.recvbuffer,	INT},
	{ "sendbuffer" ,NULL,0,(void*)&config.sendbuffer,	INT},
	{ "recvlowatbuffer" ,NULL,0,(void*)&config.recvlowatbuffer,	INT},
	{ "runlevel" ,NULL,0,(void*)&config.runlevel,	INT},
	
#ifdef _SHOW_VIP_CF
	{ "SHOWVIP" ,NULL,0,(void*)&config.showvip,	INT},
#endif

#ifdef _PLAYER_NUM
	{ "PLAYERNUM" ,NULL,0,(void*)&config.playernum,	INT},
#endif
#ifdef _JZ_CF_DELPETITEM
		{ "delitem1"      , NULL ,0 , (void*)&config.DelItem[0]      ,INT},
		{ "delitem2"      , NULL ,0 , (void*)&config.DelItem[1]      ,INT},
		{ "delitem3"      , NULL ,0 , (void*)&config.DelItem[2]      ,INT},
		{ "delitem4"      , NULL ,0 , (void*)&config.DelItem[3]      ,INT},
		{ "delitem5"      , NULL ,0 , (void*)&config.DelItem[4]      ,INT},
		{ "delpet1"      , NULL ,0 , (void*)&config.DelPet[0]      ,INT},
		{ "delpet2"      , NULL ,0 , (void*)&config.DelPet[1]      ,INT},
		{ "delpet3"      , NULL ,0 , (void*)&config.DelPet[2]      ,INT},
		{ "delpet4"      , NULL ,0 , (void*)&config.DelPet[3]      ,INT},
		{ "delpet5"      , NULL ,0 , (void*)&config.DelPet[4]      ,INT},
#endif
#ifdef _BATTLE_GOLD
	{ "BATTLEGOLD" ,NULL,0,(void*)&config.battlegold,	INT},
#endif
#ifdef _ANGEL_TIME
	{ "ANGELPLAYERTIME" ,NULL,0,(void*)&config.angelplayertime,	INT},
	{ "ANGELPLAYERMUN" ,NULL,0,(void*)&config.angelplayermun,	INT},
#endif
#ifdef _RIDEMODE_20
	{ "RIDEMODE" ,NULL,0,(void*)&config.ridemode,	INT},
#endif
#ifdef _FM_POINT_PK
	{ "FMPOINTPK" ,NULL,0,(void*)&config.fmpointpk,	INT},
#endif
#ifdef _ENEMY_ACTION
	{ "ENEMYACTION" ,NULL,0,(void*)&config.enemyact,	INT},
#endif

#ifdef _CHECK_PEPEAT
	{ "CHECKPEPEAT" ,NULL,0,(void*)&config.CheckRepeat,	INT},
#endif
	{ "CPUUSE" ,NULL,0,(void*)&config.cpuuse,	INT},
#ifdef _VIP_ALL
	{ "QQ" ,NULL,0,(void*)&config.checkvip,	INT},
#endif
#ifdef _FM_JOINLIMIT
	{ "JOINFAMILYTIME" ,NULL,0,(void*)&config.joinfamilytime,	INT},
#endif
};

// Arminius 7.12 login announce
char announcetext[8192];
void AnnounceToPlayer(int charaindex)
{
  char *ptr,*qtr;
  
  ptr=announcetext;
  while ((qtr=strstr(ptr,"\n"))!=NULL) {
    qtr[0]='\0';
//    printf("ptr=%s\n",ptr);
    CHAR_talkToCli(charaindex, -1, ptr, CHAR_COLORYELLOW);
    qtr[0]='\n';
    ptr=qtr+1;
  }
  CHAR_talkToCli(charaindex, -1, ptr, CHAR_COLORYELLOW);
  
}

// Robin 0720
void AnnounceToPlayerWN(int fd)
{
	char buf[8192];
	lssproto_WN_send( fd , WINDOW_MESSAGETYPE_LOGINMESSAGE,
		WINDOW_BUTTONTYPE_OK,
		-1, -1,
		makeEscapeString( announcetext, buf, sizeof(buf))
		);
}


void LoadAnnounce(void)
{
    FILE *f;

    memset(announcetext, 0, sizeof(announcetext));
    if ((f=fopen("./announce.txt","r"))!=NULL) {
      fread(announcetext, sizeof(announcetext), 1, f);
      announcetext[sizeof(announcetext)-1]='\0';
      fclose(f);
    }
}
#ifdef _PET_TALKPRO
PTALK pettalktext[PETTALK_MAXID];

void LoadPetTalk(void)
{
	FILE *fp;
	char fn[256];
	char line[ 4096];
	char talkmem[4096];
	int maxid=0;
	char buf1[256], buf2[256], buf3[256];
	int talkNO=-1, mark=-1, i;
	int len = sizeof( talkmem);
	
	memset(talkmem, 0, sizeof(talkmem));
	sprintf(fn, "%s/pettalk/pettalk.menu", getNpcdir());

	for( i=0;i<PETTALK_MAXID;i++)	{
		pettalktext[i].ID = -1;
		strcpy( pettalktext[i].DATA, "\0");
	}

	print("\n装载宠物对话文件:%s...", fn);
	fp = fopen( fn, "r");
    if( fp != NULL ) {
		while( fgets( line, sizeof( line), fp)) {
			if( strlen( talkmem) != 0 ) {
				if( talkmem[strlen( talkmem) -1] != '|' ) {
					strcatsafe( talkmem, len, "|");		
				}
			}
			chompex( line);
			strcatsafe( talkmem,len,  line);
		}
		fclose( fp);
    }else	{
		print("错误:找不到文件!");
	}

	talkNO=1;
	while( getStringFromIndexWithDelim( talkmem,"END",talkNO, buf1, sizeof( buf1)) != FALSE	){
		talkNO++;
		if( NPC_Util_GetStrFromStrWithDelim( buf1, "PETTEMPNO", buf2, sizeof( buf2)) == NULL  )
			continue;
		mark=1;
		strcpy( fn,"\0");

		if( getStringFromIndexWithDelim( buf2,",", mark+1,buf3,sizeof( buf3)) != FALSE )	{
			pettalktext[maxid].ID = atoi( buf3);
			if( getStringFromIndexWithDelim( buf2,",", mark,buf3,sizeof( buf3)) != FALSE )	{
				sprintf(fn, "%s/pettalk/%s", getNpcdir(), buf3);
				//print("\n ...file:%s", fn);
				fp = fopen( fn, "r");
				if( fp != NULL )	{
					char line[4096];
					while( fgets( line, sizeof( line), fp ) ) {
						if( strlen( pettalktext[maxid].DATA) != 0 ) {
							if( pettalktext[maxid].DATA[strlen( pettalktext[maxid].DATA) -1] != '|' ) {
								strcatsafe( pettalktext[maxid].DATA, sizeof( pettalktext[maxid].DATA), "|");
							}
						}
						chompex( line);
						strcatsafe( pettalktext[maxid].DATA, sizeof( pettalktext[maxid].DATA), line);
					}
					maxid++;
					fclose( fp);
				}else	{
					print("错误:[%s] 找不到!", fn);
					pettalktext[maxid].ID=-1;
				}
			}else	{
				pettalktext[maxid].ID=-1;
			}
		}
		print(".");
		if( maxid >= PETTALK_MAXID )
			break;
	}
	print("最大ID=%d...", maxid);
	{
		int haveid=0;
		for( i=0;i<PETTALK_MAXID;i++)	{
			if( pettalktext[i].ID >= 0 )	{
				haveid++;
			}
		}
		print("载入总数=%d", haveid);
	}

}

#else
char pettalktext[4096];
void LoadPetTalk(void)
{
  FILE *fp;
  char fn[256];
  char	line[ 4096];
  int len = sizeof( pettalktext);
  
  memset(pettalktext, 0, sizeof(pettalktext));
  sprintf(fn, "%s/pettalk/pettalk.mem", getNpcdir());
  
  fp = fopen( fn, "r");
    if( fp != NULL ) {
		print("\n\n 读取 pettalk.mem");
		while( fgets( line, sizeof( line), fp)) {
			if( strlen( pettalktext) != 0 ) {
				if( pettalktext[strlen( pettalktext) -1] != '|' ) {
					strcatsafe( pettalktext, len, "|");		
				}
			}
			chompex( line);
			strcatsafe( pettalktext,len,  line);
		}
		fclose( fp);
		print("\n %s", pettalktext);
    }else	{
		print("\n 不能找到 pettalk.mem");
	}
}
#endif

#ifdef _GAMBLE_BANK
GAMBLEBANK_ITEMS GB_ITEMS[GAMBLEBANK_ITEMSMAX];

void Load_GambleBankItems( void)
{

	FILE *fp;
	char filename[256];
	char buf1[256];
	char name[128];
	int num,ID,type;
	int i=0;
	sprintf(filename, "./data/gambleitems.txt" );
	print("\n加载赌博物品文件 %s ...", filename);
	fp = fopen( filename, "r");
    if( fp != NULL ) {
		while( fgets( buf1, sizeof( buf1), fp) != NULL )	{
			if( strstr( buf1, "#") != 0 ) continue;
			sscanf( buf1,"%s %d %d %d", name, &ID, &num , &type);
			strcpy( GB_ITEMS[i].name, name);
			GB_ITEMS[i].Gnum = num;
			GB_ITEMS[i].ItemId = ID;
			GB_ITEMS[i].type = type;
			i++;
		}
		print("最大ID: %d ", i);
		fclose( fp);
    }else	{
		print("错误 找不到文件 %s", filename);
	}

}
#endif


#ifdef _CFREE_petskill
PETSKILL_CODES Code_skill[PETSKILL_CODE];
void Load_PetSkillCodes( void)
{
	FILE *fp;
	char filename[256];
	char buf1[256];
	char name[128];
	char type[256];
	int num,ID;
	int i=0;
	sprintf(filename, "./data/skillcode.txt" );
	print("\n加载宠物技能编码文件:%s...", filename);
	fp = fopen( filename, "r");
    if( fp != NULL ) {
		while( fgets( buf1, sizeof( buf1), fp) != NULL )	{
			sscanf( buf1,"%s %d %d %s", name, &num, &ID, type);
			strcpy( Code_skill[i].name, name);
			Code_skill[i].TempNo = num;
			Code_skill[i].PetId = ID;
			strcpy( Code_skill[i].Code, type);
			i++;
			if( i >= PETSKILL_CODE ) break;
		}
		fclose( fp);
    }else	{
		print("打不到文件 %s", filename);
	}
	print("完成\n");
}
#endif

#ifdef _GMRELOAD
int LoadGMSet( char* filename )
{
	FILE* fp;
	int i = 0, gm_num = 0;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		print("无法打开文件\n");
		return FALSE;
	}
	for (i = 0; i < GMMAXNUM; i++)
	{
		strcpy(gminfo[i].cdkey, "");
		gminfo[i].level = 0;
	}
	while(1){
		char	line[64], cdkey[64], level[64];
		if (fgets(line, sizeof(line), fp) == NULL)	break;
		chop(line);
		//change 使gmset.txt可以增加注解*******
		if( line[0] == '#' )
			continue;
		for( i=0; i<strlen(line); i++ ){
            if( line[i] == '#' ){
			    line[i] = '\0';
		        break;
			}
		}
		//*************************************
		gm_num = gm_num + 1;
		if (gm_num > GMMAXNUM)	break;
		easyGetTokenFromString(line, 1, cdkey, sizeof(cdkey));
		if (strcmp(cdkey, "") == 0)	break;
		strncpy(gminfo[gm_num].cdkey, cdkey, sizeof(gminfo[gm_num].cdkey));
		easyGetTokenFromString(line, 2, level, sizeof(level));
		if (strcmp(level, "") == 0)	break;
		gminfo[gm_num].level = atoi(level);
	}
	fclose(fp);
	return TRUE;
}
#endif

char* getProgname( void )
{
    return config.progname;
}

char* getConfigfilename( void )
{
    return config.configfilename;
}

void setConfigfilename( char* newv )
{
    strcpysafe( config.configfilename, sizeof( config.configfilename ),
                newv );
}

unsigned int getDebuglevel( void )
{
    return config.debuglevel;
}

unsigned int setDebuglevel( unsigned int newv )
{
    int old;
    old = config.debuglevel;
    config.debuglevel = newv;
    return old;
}

unsigned int getMemoryunit( void )
{
    return config.usememoryunit;
}

unsigned int getMemoryunitnum( void )
{
    return config.usememoryunitnum;
}

char*   getAccountservername( void )
{
    return config.asname;
}

unsigned short   getAccountserverport( void )
{
    return config.acservport;
}

char*   getAccountserverpasswd( void )
{
    return config.acpasswd;
}

char*   getGameservername( void )
{
    return config.gsnamefromas;
}

// Arminius 7.24 manor pk
char* getGameserverID( void )
{
    if (config.gsid[strlen(config.gsid)-1]=='\n')
      config.gsid[strlen(config.gsid)-1]='\0';
      
    return config.gsid;
}

unsigned short getAllowManorPK( void )
{
    return config.allowmanorpk;
}

unsigned short getPortnumber( void )
{
    return config.port;
}

int getServernumber( void )
{
    return config.servernumber;
}

int getReuseaddr( void )
{
    return config.reuseaddr;
}

int getNodelay( void )
{
    return config.do_nodelay;
}
int getLogWriteTime(void)
{
    return config.log_write_time;
}
int getLogIOTime( void)
{
    return config.log_io_time;
}
int getLogGameTime(void)
{
    return config.log_game_time;
}
int getLogNetloopFaster(void)
{
    return config.log_netloop_faster;
}

int getSaacwritenum( void )
{
    return config.saacwritenum;
}

void setSaacwritenum( int num )
{
    config.saacwritenum = num;
}

int getSaacreadnum( void )
{
    return config.saacreadnum;
}

void setSaacreadnum( int num )
{
    config.saacreadnum = num;
}

unsigned int getFdnum( void )
{
    return config.fdnum;
}

unsigned int getPetcharnum( void )
{
    return config.petcharnum;
}

unsigned int getOtherscharnum( void )
{
    return config.othercharnum;
}

unsigned int getObjnum( void )
{
    return config.objnum;
}

unsigned int getItemnum( void )
{
    return config.itemnum;
}

unsigned int getBattlenum( void )
{
    return config.battlenum;
}

#ifdef _GET_BATTLE_EXP
unsigned int getBattleexp( void )
{
    return config.battleexp;
}
#endif

char* getTopdir( void )
{
    return config.topdir;
}

char* getMapdir( void )
{
    return config.mapdir;
}

char* getMaptilefile( void )
{
    return config.maptilefile;
}

char* getBattleMapfile( void )
{
    return config.battlemapfile;
}

char* getItemfile( void )
{
    return config.itemfile;
}

char* getInvfile( void )
{
    return config.invfile;
}

char* getAppearfile( void )
{
    return config.appearfile;
}

char* getEffectfile( void )
{
    return config.effectfile;
}

char* getTitleNamefile( void )
{
    return config.titlenamefile;
}

char* getTitleConfigfile( void )
{
    return config.titleconfigfile;
}

char* getEncountfile( void )
{
    return config.encountfile;
}

char* getEnemyfile( void )
{
    return config.enemyfile;
}

char* getEnemyBasefile( void )
{
    return config.enemybasefile;
}

char* getGroupfile( void )
{
    return config.groupfile;
}

char* getMagicfile( void )
{
    return config.magicfile;
}

#ifdef _ATTACK_MAGIC

char* getAttMagicfileName( void )
{
    return config.attmagicfile;
}

#endif


char* getPetskillfile( void )
{
    return config.petskillfile;
}


#ifdef _ITEM_QUITPARTY
char* getitemquitparty( void )
{
    return config.itemquitparty;
}
#endif

char *getItematomfile( void )
{
    return config.itematomfile;
}


char* getQuizfile( void )
{
    return config.quizfile;
}

char* getLsgenlogfilename( void )
{
    return config.lsgenlog;
}

#ifdef _GMRELOAD
char* getGMSetfile( void )
{
    return config.gmsetfile;
}
#endif

char* getStoredir( void )
{
    return config.storedir;
}
#ifdef _STORECHAR
char* getStorechar( void )
{
    return config.storechar;
}
#endif

char* getNpcdir( void )
{
    return config.npcdir;
}

char* getLogdir( void )
{
    return config.logdir;
}

char* getLogconffile( void )
{
    return config.logconfname;
}

char* getChatMagicPasswd( void )
{
    return config.chatmagicpasswd;
}

unsigned getChatMagicCDKeyCheck( void )
{
    return config.chatmagiccdkeycheck;
}

unsigned int getFilesearchnum( void )
{
    return config.filesearchnum;
}

unsigned int getNpctemplatenum( void )
{
    return config.npctemplatenum;
}

unsigned int getNpccreatenum( void )
{
    return config.npccreatenum;
}

unsigned int getWalksendinterval( void )
{
    return config.walksendinterval;
}

void setWalksendinterval( unsigned int interval )
{
    config.walksendinterval = interval;
}

unsigned int getCAsendinterval_ms( void )
{
    return config.CAsendinterval_ms;
}

void setCAsendinterval_ms( unsigned int interval_ms )
{
    config.CAsendinterval_ms = interval_ms;
}

unsigned int getCDsendinterval_ms( void )
{
    return config.CDsendinterval_ms;
}

void setCDsendinterval_ms( unsigned int interval_ms )
{
	config.CDsendinterval_ms = interval_ms;
}

unsigned int getOnelooptime_ms( void )
{
    return config.Onelooptime_ms;
}

void setOnelooptime_ms( unsigned int interval_ms )
{
	config.Onelooptime_ms = interval_ms;
}

unsigned int getPetdeletetime( void )
{
    return config.Petdeletetime;
}

void setPetdeletetime( unsigned int interval )
{
	config.Petdeletetime = interval;
}

unsigned int getItemdeletetime( void )
{
    return config.Itemdeletetime;
}

void setItemdeletetime( unsigned int interval )
{
	config.Itemdeletetime = interval;
}

unsigned int getCharSavesendinterval( void )
{
    return config.CharSavesendinterval;
}

void setCharSavesendinterval( unsigned int interval)
{
	config.CharSavesendinterval = interval;
}

unsigned int getAddressbookoffmsgnum( void )
{
    return config.addressbookoffmsgnum;
}

unsigned int getProtocolreadfrequency( void )
{
    return config.protocolreadfrequency;
}

unsigned int getAllowerrornum( void )
{
    return config.allowerrornum;
}

unsigned int getLogHour( void )
{
    return config.loghour;
}

unsigned int getBattleDebugMsg( void )
{
    return config.battledebugmsg;
}

void setBattleDebugMsg( unsigned int num )
{
    config.battledebugmsg = num;
}



/*
 * Config及犯白巧伙玄袄毛瑁户月楮醒
 * 娄醒
 *  argv0   char*   戊穴件玉仿奶件娄醒及  赓
 */
void defaultConfig( char* argv0 )
{
    char* program = rindex(argv0, '/');
    if(program == NULL)
        program = argv0;
    else
        program++;
    strcpysafe(config.progname, sizeof(config.progname), program);
    strcpysafe(config.configfilename, sizeof(config.configfilename), "config/setup.cf");
}

/*
 * 涩烂白央奶伙  毛  氏分  匹及质  毛垫丹［
 * 娄醒
 *  卅仄
 * 忒曰袄
 *  卅仄
 */
void lastConfig( void )
{
    char    entry[256];
    /*  穴永皿犯奴伊弁玄伉及涩烂    */
    snprintf(entry, sizeof(entry), "%s/%s", config.topdir, config.mapdir);
    strcpysafe(config.mapdir, sizeof(config.mapdir), entry);

    /*  穴永皿涩烂白央奶伙  及涩烂    */
    snprintf(entry,sizeof(entry),"%s/%s",
             config.topdir,config.maptilefile);
    strcpysafe(config.maptilefile, sizeof(config.maptilefile), entry);

    /*  田玄伙穴永皿涩烂白央奶伙  及涩烂    */
    snprintf(entry,sizeof(entry),"%s/%s",
             config.topdir,config.battlemapfile);
    strcpysafe(config.battlemapfile, sizeof(config.battlemapfile), entry);

    /*  失奶  丞涩烂白央奶伙  及涩烂    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.itemfile);
    strcpysafe(config.itemfile, sizeof(config.itemfile), entry);

    /*    衬涩烂白央奶伙  及涩烂    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.invfile);
    strcpysafe(config.invfile, sizeof(config.invfile), entry);

    /*  请蜇匏  涩烂白央奶伙  及涩烂    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.appearfile);
    strcpysafe(config.appearfile, sizeof(config.appearfile), entry);

    /*  梢请涩烂白央奶伙  及涩烂    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.effectfile);
    strcpysafe(config.effectfile, sizeof(config.effectfile), entry);

    /*  弁奶术涩烂白央奶伙  及涩烂    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.quizfile);
    strcpysafe(config.quizfile, sizeof(config.quizfile), entry);

    /*  惫寞  白央奶伙  及涩烂    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.titlenamefile);
    strcpysafe(config.titlenamefile, sizeof(config.titlenamefile), entry);

    /*  lsgen 失它玄皿永玄白央奶伙      */
    snprintf(entry,sizeof(entry),"%s/%s", config.topdir,config.lsgenlog);
    strcpysafe(config.lsgenlog, sizeof(config.lsgenlog), entry);

    /*  旦玄失犯奴伊弁玄伉及涩烂    */
/*
    snprintf(entry,sizeof(entry), "%s/%s",config.topdir,config.storedir);
    strcpysafe(config.storedir, sizeof(config.storedir), entry);
*/
    /*  NPC涩烂玄永皿犯奴伊弁玄伉及涩烂    */
    snprintf(entry,sizeof(entry), "%s/%s",config.topdir,config.npcdir);
    strcpysafe(config.npcdir, sizeof(config.npcdir), entry);

#ifdef _STORECHAR
    /*   */
    snprintf(entry,sizeof(entry), "%s/%s",config.topdir,config.storechar);
    strcpysafe(config.storechar, sizeof(config.storechar), entry);
#endif

}


/*
 * 禾奶件正□午赝濠卅滇树  毛  匀化医  毛允月楮醒
 * 娄醒
 *  to      void*   袄毛医  允月禾奶件正
 *  type    CTYPE   to及滇毛瑁户月
 *  value   double  to卞医  允月袄
 * 忒曰袄
 *  卅仄
 */
void substitutePointerFromType( void* to , CTYPE type ,double value)
{
    switch( type  ){
    case CHAR:
        *(char*)to = (char)value;
        break;
    case SHORT:
        *(short*)to = (short)value;
        break;
    case INT:
        *(int*)to = (int)value;
        break;
    case DOUBLE:
        *(double*)to = (double)value;
        break;
    }
}

int readconfigfile( char* filename )
{
    FILE* f = fopen(filename, "r");
    char linebuf[256];
    int linenum = 0;
    while(fgets(linebuf, sizeof(linebuf), f))
	{
        char firstToken[256];
        int i;
        int ret;

        linenum ++;

        deleteWhiteSpace(linebuf);          /* remove whitespace    */

        if( linebuf[0] == '#' )continue;        /* comment */
        if( linebuf[0] == '\n' )continue;       /* none    */

        chomp( linebuf );                    /* remove tail newline  */
        ret = getStringFromIndexWithDelim( linebuf, "=", 1, firstToken, sizeof(firstToken) );
        if( ret == FALSE ){
            print( "Find error at %s in line %d. Ignore\n", filename , linenum);
            continue;
        }

        for( i = 0 ; i < arraysizeof( readconf ) ; i ++ ){
            if( strcmp( readconf[i].name ,firstToken ) == 0 ){
                /* match */
                char secondToken[256];      /*2    及  侬  */
                /* delim "=" 匹2    及玄□弁件毛  月*/
                ret = getStringFromIndexWithDelim(linebuf, "=", 2, secondToken, sizeof(secondToken) );

                if( ret == FALSE ){
                    print( "Find error at %s in line %d. Ignore",
                           filename , linenum);
                    break;
                }


                /*NULL分匀凶日医  仄卅中*/
                if( readconf[i].charvalue != NULL )
                    strcpysafe( readconf[i].charvalue
                                ,readconf[i].charsize, secondToken);

                /*NULL分匀凶日医  仄卅中*/
                if( readconf[i].value != NULL ) {
                    if( strcmp( "ON" ,secondToken ) == 0 ) {
                        /*ON分匀凶日1毛  木月*/
                        substitutePointerFromType( readconf[i].value,
                                                   readconf[i].valuetype,
                                                   1.0);

                    }else if( strcmp( "OFF" ,secondToken ) == 0 ) {
                        /*OFF分匀凶日1毛  木月*/
                        substitutePointerFromType( readconf[i].value,
                                                   readconf[i].valuetype,
                                                   1.0);
                    }else {
                        strtolchecknum(secondToken,
                                       (int*)readconf[i].value,
                                       10, readconf[i].valuetype);
					}
				}
                break;
            }
        }
    }
    fclose( f );
    lastConfig();
    return TRUE;
}
//ttom add this becaus the second had this function 
/*------------------------------------------------------------
 * 巨件戊□玉平□毛涩烂允月
 * 娄醒
 *  卅仄
 * 忒曰袄
 *  unsigned int 平□毛忒允
------------------------------------------------------------*/
unsigned int setEncodeKey( void )
{
   JENCODE_KEY = config.encodekey;
   return JENCODE_KEY;
}
/*------------------------------------------------------------
* 失市它件玄扔□田□卞踏五  戈田永白央及扔奶术毛涩烂允月
* 娄醒
*  卅仄
* 忒曰袄
*  unsigned int 平□毛忒允
------------------------------------------------------------*/
unsigned int setAcWBSize( void )
{
    AC_WBSIZE = config.acwbsize;
    return AC_WBSIZE;
}
unsigned int getAcwriteSize( void )
{
    return config.acwritesize;
}
unsigned int getErrUserDownFlg( void )
{
    return config.ErrUserDownFlg;
}
    

#ifdef _DEL_DROP_GOLD
unsigned int getGolddeletetime( void )
{
    if( config.Golddeletetime > 0 )
		return config.Golddeletetime;
	else
		return config.Itemdeletetime;
}
void setIGolddeletetime( unsigned int interval )
{
	config.Golddeletetime = interval;
}
#endif

#ifdef _NEW_PLAYER_CF
int getNewplayertrans( void )
{
  if(config.newplayertrans > 7)
		return 7;
	else if(config.newplayertrans >= 0)
		return config.newplayertrans;
	else
		return 0;
}
int getNewplayerlv( void )
{
  if(config.newplayerlv > 160)
		return 160;
	else if(config.newplayerlv >0)
		return config.newplayerlv;
	else
		return 0;
}
int getNewplayerpetlv( void )
{
  if(config.newplayerpetlv > 160)
		return 160;
	else if(config.newplayerpetlv > 0)
		return config.newplayerpetlv;
	else
		return 0;
}

int getNewplayergivepet( unsigned int index )
{
  if(config.newplayergivepet[index] > 0 )
		return config.newplayergivepet[index];
	else
		return -1;
}

int getNewplayergiveitem( unsigned int index )
{
  if(config.newplayergiveitem[index] > 0 )
		return config.newplayergiveitem[index];
	else
		return -1;
}

void setNewplayergivepet( unsigned int index ,unsigned int interval)
{
	config.newplayergivepet[index] = interval;
}

int getNewplayergivegold( void )
{
  if(config.newplayergivegold > 1000000)
		return 1000000;
	else if(config.newplayergivegold < 0)
		return 0;
	else
		return config.newplayergivegold;
}
int getRidePetLevel( void )
{
  if(config.ridepetlevel > 0 )
		return config.ridepetlevel;
	else
		return -1;
}
#ifdef _VIP_SERVER
int getNewplayergivevip( void )
{
	return config.newplayerpetvip < 0?0:config.newplayerpetvip;
}
#endif
#endif

#ifdef _UNLAW_WARP_FLOOR
int getUnlawwarpfloor( unsigned int index )
{
  if(config.unlawwarpfloor[index] > 0 )
		return config.unlawwarpfloor[index];
	else
		return -1;
}
#endif

#ifdef _WATCH_FLOOR
int getWatchFloor( unsigned int index )
{
  if(config.watchfloor[index] > 0 )
		return config.watchfloor[index];
	else
		return -1;
}
char* getWatchFloorCF( void )
{
	return (config.watchfloor[0]>0)? "是":"否";
}
#endif

#ifdef _BATTLE_FLOOR
int getBattleFloor( unsigned int index )
{
  if(config.battlefloor[index] > 0 )
		return config.battlefloor[index];
	else
		return -1;
}
char* getBattleFloorCF( void )
{
	return (config.battlefloor[0]>0)? "是":"否";
}
#endif

#ifdef _USER_EXP_CF

char* getEXPfile( void )
{
    return config.expfile;
}
#endif

#ifdef _UNREG_NEMA
char* getUnregname( int index )
{
    return config.unregname[index];
}
#endif

#ifdef _TRANS_LEVEL_CF
int getChartrans( void )
{
		if(config.chartrans>6)
			config.chartrans=6;
    return config.chartrans;
}
int getPettrans( void )
{
		if(config.pettrans>2)
			return 2;
		else if(config.pettrans<-1)
			return -1;
    return config.pettrans;
}
int getYBLevel( void )
{
		if(config.yblevel>config.maxlevel)
			config.yblevel=config.maxlevel;
    return config.yblevel;
}
int getMaxLevel( void )
{
    return config.maxlevel;
}
#endif

#ifdef _POINT
char* getPoint( void )
{
		return (config.point>0)? "是":"否";
}
int getTransPoint( int index )
{
		return config.transpoint[index];
}
#endif

#ifdef _PET_UP
char* getPetup( void )
{
		return (config.petup>0)? "是":"否";
}
#endif
#ifdef _LOOP_ANNOUNCE
char* getLoopAnnouncePath( void )
{
		return config.loopannouncepath;
}
int loadLoopAnnounce( void )
{
	FILE* fp;
	int i = 0;
	config.loopannouncemax=0;
	fp = fopen(config.loopannouncepath, "r");
	if (fp == NULL)
	{
		print("无法打开文件\n");
		return FALSE;
	}
	while(1){
		char	line[1024];
		if (fgets(line, sizeof(line), fp) == NULL)	break;
		chop(line);

		if( line[0] == '#' )
			continue;
		for( i=0; i<10; i++ ){
            if( line[i] == '#' ){
			    line[i] = '\0';
		        break;
			}
		}
		//*************************************
		strcpy(config.loopannounce[config.loopannouncemax],line);
		config.loopannouncemax++;
	}
	fclose(fp);
	return TRUE;
}
int getLoopAnnounceTime( void )
{
    return (config.loopannouncetime<0)?-1:config.loopannouncetime;
}
int getLoopAnnounceMax( void )
{
    return (config.loopannouncemax>0)?config.loopannouncemax:0;
}
char* getLoopAnnounce( int index )
{
    return config.loopannounce[index];
}
#endif

#ifdef _SKILLUPPOINT_CF
int getSkup( void )
{
    return (config.skup>0)?config.skup:0;
}
#endif
#ifdef _RIDELEVEL
int getRideLevel( void )
{
    return config.ridelevel;
}
#endif
#ifdef _REVLEVEL
char* getRevLevel( void )
{
		return (config.revlevel>0)?"是":"否";
}
#endif
#ifdef _NEW_PLAYER_RIDE
char* getPlayerRide( void )
{
		if(config.npride>2)
			return "配套送虎加雷";
		else if(config.npride==2)
			return "配套送雷";
		else if(config.npride==1)
			return "配套送虎";
		else
			return "不送配套骑宠";
}
#endif

#ifdef _FIX_CHARLOOPS
int getCharloops( void )
{
    return config.charloops-1;
}
#endif

#ifdef _PLAYER_ANNOUNCE
int getPAnnounce( void )
{
    return (config.pannounce>-1)?config.pannounce:-1;
}
#endif
#ifdef _PLAYER_MOVE
int getPMove( void )
{
    return (config.pmove>-1)?config.pmove:-1;
}
#endif

int getrecvbuffer( void )
{
		if(config.recvbuffer<0)
	    return 0;
	  else if(config.recvbuffer>128)
	    return 128;
	  else
	  	return config.recvbuffer;
}

int getsendbuffer( void )
{
		if(config.sendbuffer<0)
	    return 0;
	  else if(config.sendbuffer>128)
	    return 128;
	  else
	  	return config.sendbuffer;
}

int getrecvlowatbuffer( void )
{
		if(config.recvlowatbuffer<0)
	    return 0;
	  else if(config.recvlowatbuffer>1024)
	    return 1024;
	  else
	  	return config.recvlowatbuffer;
}

int getrunlevel( void )
{
		if(config.runlevel<-20)
	    return -20;
	  else if(config.runlevel>19)
	    return 19;
	  else
	  	return config.runlevel;

}

#ifdef _SHOW_VIP_CF
int getShowVip( void )
{
		if(config.showvip>2)
			return 2;
		else if(config.showvip<0)
			return 0;
		else
			return config.showvip;
}
#endif

#ifdef _PLAYER_NUM
int getPlayerNum( void )
{
		return config.playernum;
}
void setPlayerNum( int num )
{
		config.playernum=num;
}
#endif
#ifdef _JZ_CF_DELPETITEM
int getDelPet(int Num)
{
	return config.DelPet[Num];
}

int getDelItem(int Num)
{
	return config.DelItem[Num];
}
#endif
#ifdef _BATTLE_GOLD
int getBattleGold( void )
{
		if(config.battlegold<0)
	    return 0;
	  else if(config.battlegold>100)
	    return 100;
	  else
	  	return config.battlegold;

}
#endif

#ifdef _ANGEL_TIME
int getAngelPlayerTime( void )
{
		return (config.angelplayertime>1)?config.angelplayertime:1;
}
int getAngelPlayerMun( void )
{
		return (config.angelplayermun>2)?config.angelplayermun:2;
}
#endif

#ifdef _RIDEMODE_20
int getRideMode( void )
{
		if(config.ridemode<0)
			config.ridemode=0;
		return config.ridemode;
}
#endif
#ifdef _FM_POINT_PK
char *getFmPointPK( void )
{
		return (config.fmpointpk>0)?"是":"否";
}
#endif
#ifdef _ENEMY_ACTION
int getEnemyAction( void )
{
		if(config.enemyact>100)
			return 100;
		else if(config.enemyact<1)
			return 1;
		else
			return config.enemyact;
}
#endif

int getCpuUse( void )
{
	return config.cpuuse;
}
#ifdef _CHECK_PEPEAT
int getCheckRepeat( void )
{
		return (config.CheckRepeat>0)?1:0;
}
#endif

#ifdef _VIP_ALL
int getCheckVip( void )
{
		return config.checkvip;
}
#endif

#ifdef _FM_JOINLIMIT
int getJoinFamilyTime( void )
{
		return config.joinfamilytime;
}
#endif
