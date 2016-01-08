#include "version.h"
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "configfile.h"
#include "net.h"
#include "npcutil.h"
#include "char.h"
#include "lssproto_serv.h"

#ifdef _ANGEL_SUMMON
extern struct MissionInfo missionlist[MAXMISSION];
extern struct MissionTable missiontable[MAXMISSIONTABLE];
#endif


typedef struct tagConfig {
  char datadir[128];
  char public_key[128];
  char private_key[128];
  char signature[128];

  char configfilename[32];
  unsigned int debuglevel;
  unsigned int usememoryunit;
  unsigned int usememoryunitnum;
  char asname[32];
  unsigned short acservport;
  char acpasswd[32];
  char gsnamefromas[32];

  // Arminius 7.24 manor pk
  char gsid[32];  // game server chinese id
  unsigned short allowmanorpk;  // is this server allow manor pk
  unsigned short port;
  int servernumber;
  int reuseaddr;
  /* Address already used... */
  int do_nodelay;
  int log_write_time;
  int log_io_time;
  int log_game_time;
  int log_netloop_faster;
  int saacwritenum;
  int saacreadnum;
  unsigned short fdnum;
  unsigned int othercharnum;
  unsigned int objnum;
  unsigned int petcharnum;
  unsigned int itemnum;
  unsigned int battlenum;
  unsigned int battleexp;
  char topdir[32];
  char mapdir[32];
  char maptilefile[32];
  char battlemapfile[32];
  char itemfile[32];
  char invfile[32];
  char appearfile[32];
  char titlenamefile[32];
  char titleconfigfile[32];
  char encountfile[32];
  char enemybasefile[32];
  char enemyfile[32];
  char groupfile[32];
  char magicfile[32]; 
#ifdef _ATTACK_MAGIC
  char attmagicfile[32];       // 攻击性咒术
#endif

  char petskillfile[32];
  char itematomfile[32];
  char quizfile[32];
  char lsgenlog[32];
  char storedir[128];
  char npcdir[32];
  char logdir[32];
  char logconfname[32];
  char chatmagicpasswd[32];
#ifdef _STORECHAR
  char storechar[32];
#endif
  unsigned int chatmagiccdkeycheck;
  unsigned int filesearchnum;
  unsigned int npctemplatenum;
  unsigned int npccreatenum;
  unsigned int walksendinterval;
  unsigned int CAsendinterval_ms;
  unsigned int CDsendinterval_ms;
  unsigned int Onelooptime_ms;
  unsigned int Petdeletetime;
  unsigned int Itemdeletetime;
  unsigned int CharSavesendinterval;
  unsigned int addressbookoffmsgnum;
  unsigned int protocolreadfrequency;
  unsigned int allowerrornum;
  unsigned int loghour;
  unsigned int battledebugmsg;
  //ttom add this because the second had this                                         
  unsigned int acwbsize;
  unsigned int acwritesize;
  unsigned int ErrUserDownFlg;
#ifdef _GMRELOAD
  char gmsetfile[32];
#endif
#ifdef _ITEM_QUITPARTY
  char itemquitparty[32];
#endif

#ifdef _DEL_DROP_GOLD
  unsigned int Golddeletetime;
#endif
#ifdef _NEW_PLAYER_CF
  int newplayertrans;
  int newplayerlv;
  int newplayergivepet[5];
  int newplayergiveitem[15];
  int newplayerpetlv;
  int newplayergivegold;
  int ridepetlevel;
#ifdef _VIP_SERVER
  int newplayerpetvip;
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
  int unlawwarpfloor[10];
#endif
#ifdef _WATCH_FLOOR
  int	watchfloor[6];
#endif
#ifdef _BATTLE_FLOOR
  int	battlefloor[6];
#endif
#ifdef _UNREG_NEMA
  char unregname[5][16];
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
  int enemyact;
#endif
  int cpuuse;
#ifdef _FM_JOINLIMIT
  int joinfamilytime;
#endif
} Config;

Config config;


typedef struct tagReadConf {
  char name[32];
  char* charvalue;
  size_t charsize;
  void* value;
  CTYPE valuetype;
} ReadConf;

ReadConf readconf[] =
    {
        {"datadir", &config.datadir, sizeof(config.datadir), NULL, CHAR},
        {"public_key", &config.public_key, sizeof(config.public_key), NULL, CHAR},
        {"private_key", &config.private_key, sizeof(config.private_key), NULL, CHAR},
        {"signature", &config.signature, sizeof(config.signature), NULL, CHAR},

        {"debuglevel", NULL, 0, &config.debuglevel, CHAR},

        {"usememoryunit", NULL, 0, &config.usememoryunit, INT},
        {"usememoryunitnum", NULL, 0, &config.usememoryunitnum, INT},

        {"acserv", &config.asname, sizeof(config.asname), NULL, CHAR},
        {"acservport", NULL, 0, (void *) &config.acservport, SHORT},
        {"acpasswd", &config.acpasswd, sizeof(config.acpasswd), NULL, CHAR},
        {"gameservname", &config.gsnamefromas, sizeof(config.gsnamefromas), NULL, CHAR},

        {"gameservid", &config.gsid, sizeof(config.gsid), NULL, CHAR},
        {"allowmanorpk", NULL, 0, (void *) &config.allowmanorpk, SHORT},

        {"port", NULL, 0, (void *) &config.port, SHORT},
        {"servernumber", NULL, 0, (void *) &config.servernumber, INT},

        {"reuseaddr", NULL, 0, (void *) &config.reuseaddr, INT},
        {"nodelay", NULL, 0, (void *) &config.do_nodelay, INT},
        {"log_write_time", NULL, 0, (void *) &config.log_write_time, INT},
        {"log_io_time", NULL, 0, (void *) &config.log_io_time, INT},
        {"log_game_time", NULL, 0, (void *) &config.log_game_time, INT},
        {"log_netloop_faster", NULL, 0, (void *) &config.log_netloop_faster, INT},
        {"saacwritenum", NULL, 0, (void *) &config.saacwritenum, INT},
        {"saacreadnum", NULL, 0, (void *) &config.saacreadnum, INT},
        {"fdnum", NULL, 0, (void *) &config.fdnum, SHORT},
        {"petnum", NULL, 0, (void *) &config.petcharnum, INT},
        {"othercharnum", NULL, 0, (void *) &config.othercharnum, INT},

        {"objnum", NULL, 0, (void *) &config.objnum, INT},
        {"itemnum", NULL, 0, (void *) &config.itemnum, INT},
        {"battlenum", NULL, 0, (void *) &config.battlenum, INT},
        {"battleexp", NULL, 0, (void *) &config.battleexp, INT},
        {"topdir", &config.topdir, sizeof(config.topdir), NULL, CHAR},
        {"mapdir", &config.mapdir, sizeof(config.mapdir), NULL, CHAR},
        {"maptilefile", &config.maptilefile, sizeof(config.maptilefile), NULL, CHAR},
        {"battlemapfile", &config.battlemapfile, sizeof(config.battlemapfile), NULL, CHAR},

#ifdef _ITEMSET6_TXT
        {"itemset6file", &config.itemfile, sizeof(config.invfile), NULL, CHAR},
#else

#endif
        {"invinciblefile", &config.invfile, sizeof(config.invfile), NULL, CHAR},
        {"appearpositionfile", &config.appearfile, sizeof(config.appearfile), NULL, CHAR},
        {"titlenamefile", &config.titlenamefile, sizeof(config.titlenamefile), NULL, CHAR},
        {"titleconfigfile", &config.titleconfigfile, sizeof(config.titleconfigfile), NULL, CHAR},
        {"encountfile", &config.encountfile, sizeof(config.encountfile), NULL, CHAR},
        {"enemyfile", &config.enemyfile, sizeof(config.enemyfile), NULL, CHAR},
        {"enemybasefile", &config.enemybasefile, sizeof(config.enemybasefile), NULL, CHAR},
        {"groupfile", &config.groupfile, sizeof(config.groupfile), NULL, CHAR},
        {"magicfile", &config.magicfile, sizeof(config.magicfile), NULL, CHAR},
#ifdef _ATTACK_MAGIC
        {"attmagicfile", &config.attmagicfile, sizeof(config.attmagicfile), NULL, CHAR},
#endif

#ifdef _PETSKILL2_TXT
        {"petskillfile2", &config.petskillfile, sizeof(config.petskillfile), NULL, CHAR},
#else
        { "petskillfile1", &config.petskillfile, sizeof( config.petskillfile),NULL,0},
#endif

        {"itematomfile", &config.itematomfile, sizeof(config.itematomfile), NULL, CHAR},
        {"quizfile", &config.quizfile, sizeof(config.quizfile), NULL, CHAR},

        {"lsgenlogfilename", &config.lsgenlog, sizeof(config.lsgenlog), NULL, CHAR},
#ifdef _GMRELOAD
        {"gmsetfile", &config.gmsetfile, sizeof(config.gmsetfile), NULL, CHAR},
#endif

        {"storedir", &config.storedir, sizeof(config.storedir), NULL, CHAR},
        {"npcdir", &config.npcdir, sizeof(config.npcdir), NULL, CHAR},
        {"logdir", &config.logdir, sizeof(config.logdir), NULL, CHAR},
        {"logconfname", &config.logconfname, sizeof(config.logconfname), NULL, CHAR},
        {"chatmagicpasswd", &config.chatmagicpasswd, sizeof(config.chatmagicpasswd), NULL, CHAR},
#ifdef _STORECHAR
        {"storechar", &config.storechar, sizeof(config.storechar), NULL, CHAR},
#endif
        {"chatmagiccdkeycheck", NULL, 0, &config.chatmagiccdkeycheck, INT},
        {"filesearchnum", NULL, 0, &config.filesearchnum, INT},
        {"npctemplatenum", NULL, 0, &config.npctemplatenum, INT},
        {"npccreatenum", NULL, 0, &config.npccreatenum, INT},
        {"walkinterval", NULL, 0, (void *) &config.walksendinterval, INT},
        {"CAinterval", NULL, 0, (void *) &config.CAsendinterval_ms, INT},
        {"CDinterval", NULL, 0, (void *) &config.CDsendinterval_ms, INT},
        {"CharSaveinterval", NULL, 0, (void *) &config.CharSavesendinterval, INT},
        {"Onelooptime", NULL, 0, (void *) &config.Onelooptime_ms, INT},
        {"Petdeletetime", NULL, 0, (void *) &config.Petdeletetime, INT},
        {"Itemdeletetime", NULL, 0, (void *) &config.Itemdeletetime, INT},
        {"addressbookoffmesgnum", NULL, 0,
         (void *) &config.addressbookoffmsgnum, INT},

        {"protocolreadfrequency", NULL, 0,
         (void *) &config.protocolreadfrequency, INT},

        {"allowerrornum", NULL, 0, (void *) &config.allowerrornum, INT},
        {"loghour", NULL, 0, (void *) &config.loghour, INT},
        {"battledebugmsg", NULL, 0, (void *) &config.battledebugmsg, INT},
        {"acwritesize", NULL, 0, (void *) &config.acwritesize, INT},
        {"acwbsize", NULL, 0, (void *) &config.acwbsize, INT},
        {"erruser_down", NULL, 0, (void *) &config.ErrUserDownFlg, INT},

#ifdef _ITEM_QUITPARTY
        {"itemquitparty", &config.itemquitparty, sizeof(config.itemquitparty), NULL, CHAR},
#endif

#ifdef _DEL_DROP_GOLD
        {"Golddeletetime", NULL, 0, (void *) &config.Golddeletetime, INT},
#endif

#ifdef _NEW_PLAYER_CF
        {"TRANS", NULL, 0, (void *) &config.newplayertrans, INT},
        {"LV", NULL, 0, (void *) &config.newplayerlv, INT},
        {"PET1", NULL, 0, (void *) &config.newplayergivepet[1], INT},
        {"PET2", NULL, 0, (void *) &config.newplayergivepet[2], INT},
        {"PET3", NULL, 0, (void *) &config.newplayergivepet[3], INT},
        {"PET4", NULL, 0, (void *) &config.newplayergivepet[4], INT},
        {"ITEM1", NULL, 0, (void *) &config.newplayergiveitem[0], INT},
        {"ITEM2", NULL, 0, (void *) &config.newplayergiveitem[1], INT},
        {"ITEM3", NULL, 0, (void *) &config.newplayergiveitem[2], INT},
        {"ITEM4", NULL, 0, (void *) &config.newplayergiveitem[3], INT},
        {"ITEM5", NULL, 0, (void *) &config.newplayergiveitem[4], INT},
        {"ITEM6", NULL, 0, (void *) &config.newplayergiveitem[5], INT},
        {"ITEM7", NULL, 0, (void *) &config.newplayergiveitem[6], INT},
        {"ITEM8", NULL, 0, (void *) &config.newplayergiveitem[7], INT},
        {"ITEM9", NULL, 0, (void *) &config.newplayergiveitem[8], INT},
        {"ITEM10", NULL, 0, (void *) &config.newplayergiveitem[9], INT},
        {"ITEM11", NULL, 0, (void *) &config.newplayergiveitem[10], INT},
        {"ITEM12", NULL, 0, (void *) &config.newplayergiveitem[11], INT},
        {"ITEM13", NULL, 0, (void *) &config.newplayergiveitem[12], INT},
        {"ITEM14", NULL, 0, (void *) &config.newplayergiveitem[13], INT},
        {"ITEM15", NULL, 0, (void *) &config.newplayergiveitem[14], INT},
        {"PETLV", NULL, 0, (void *) &config.newplayerpetlv, INT},
        {"GOLD", NULL, 0, (void *) &config.newplayergivegold, INT},
        {"RIDEPETLEVEL", NULL, 0, (void *) &config.ridepetlevel, INT},
#ifdef _VIP_SERVER
        {"GIVEVIPPOINT", NULL, 0, (void *) &config.newplayerpetvip, INT},
#endif
#endif

#ifdef _USER_EXP_CF
        { "USEREXP", &config.expfile, sizeof( config.expfile),NULL,0},
#endif

#ifdef _UNLAW_WARP_FLOOR
        {"FLOOR1", NULL, 0, (void *) &config.unlawwarpfloor[0], INT},
        {"FLOOR2", NULL, 0, (void *) &config.unlawwarpfloor[1], INT},
        {"FLOOR3", NULL, 0, (void *) &config.unlawwarpfloor[2], INT},
        {"FLOOR4", NULL, 0, (void *) &config.unlawwarpfloor[3], INT},
        {"FLOOR5", NULL, 0, (void *) &config.unlawwarpfloor[4], INT},
        {"FLOOR6", NULL, 0, (void *) &config.unlawwarpfloor[5], INT},
        {"FLOOR7", NULL, 0, (void *) &config.unlawwarpfloor[6], INT},
        {"FLOOR8", NULL, 0, (void *) &config.unlawwarpfloor[7], INT},
        {"FLOOR6", NULL, 0, (void *) &config.unlawwarpfloor[8], INT},
        {"FLOOR10", NULL, 0, (void *) &config.unlawwarpfloor[9], INT},
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
        {"NAME1", &config.unregname[0], sizeof(config.unregname[0]), NULL, CHAR},
        {"NAME2", &config.unregname[1], sizeof(config.unregname[1]), NULL, CHAR},
        {"NAME3", &config.unregname[2], sizeof(config.unregname[2]), NULL, CHAR},
        {"NAME4", &config.unregname[3], sizeof(config.unregname[3]), NULL, CHAR},
        {"NAME5", &config.unregname[4], sizeof(config.unregname[4]), NULL, CHAR},
#endif
#ifdef _TRANS_LEVEL_CF
        {"CHARTRANS", NULL, 0, (void *) &config.chartrans, INT},
        {"PETTRANS", NULL, 0, (void *) &config.pettrans, INT},
        {"LEVEL", NULL, 0, (void *) &config.yblevel, INT},
        {"MAXLEVEL", NULL, 0, (void *) &config.maxlevel, INT},
#endif
#ifdef _POINT
        {"POINT", NULL, 0, (void *) &config.point, INT},
        {"TRANS0", NULL, 0, (void *) &config.transpoint[0], INT},
        {"TRANS1", NULL, 0, (void *) &config.transpoint[1], INT},
        {"TRANS2", NULL, 0, (void *) &config.transpoint[2], INT},
        {"TRANS3", NULL, 0, (void *) &config.transpoint[3], INT},
        {"TRANS4", NULL, 0, (void *) &config.transpoint[4], INT},
        {"TRANS5", NULL, 0, (void *) &config.transpoint[5], INT},
        {"TRANS6", NULL, 0, (void *) &config.transpoint[6], INT},
        {"TRANS7", NULL, 0, (void *) &config.transpoint[7], INT},
#endif

#ifdef _PET_UP
        {"PETUP", NULL, 0, (void *) &config.petup, INT},
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
        {"CHARLOOPS", NULL, 0, (void *) &config.charloops, INT},
#endif
#ifdef _PLAYER_ANNOUNCE
        {"PANNOUNCE", NULL, 0, (void *) &config.pannounce, INT},
#endif
#ifdef _PLAYER_MOVE
        {"PMOVE", NULL, 0, (void *) &config.pmove, INT},
#endif

        {"recvbuffer", NULL, 0, (void *) &config.recvbuffer, INT},
        {"sendbuffer", NULL, 0, (void *) &config.sendbuffer, INT},
        {"recvlowatbuffer", NULL, 0, (void *) &config.recvlowatbuffer, INT},
        {"runlevel", NULL, 0, (void *) &config.runlevel, INT},

#ifdef _SHOW_VIP_CF
        {"SHOWVIP", NULL, 0, (void *) &config.showvip, INT},
#endif

#ifdef _PLAYER_NUM
        {"PLAYERNUM", NULL, 0, (void *) &config.playernum, INT},
#endif
#ifdef _JZ_CF_DELPETITEM
        {"delitem1", NULL, 0, (void *) &config.DelItem[0], INT},
        {"delitem2", NULL, 0, (void *) &config.DelItem[1], INT},
        {"delitem3", NULL, 0, (void *) &config.DelItem[2], INT},
        {"delitem4", NULL, 0, (void *) &config.DelItem[3], INT},
        {"delitem5", NULL, 0, (void *) &config.DelItem[4], INT},
        {"delpet1", NULL, 0, (void *) &config.DelPet[0], INT},
        {"delpet2", NULL, 0, (void *) &config.DelPet[1], INT},
        {"delpet3", NULL, 0, (void *) &config.DelPet[2], INT},
        {"delpet4", NULL, 0, (void *) &config.DelPet[3], INT},
        {"delpet5", NULL, 0, (void *) &config.DelPet[4], INT},
#endif
#ifdef _BATTLE_GOLD
        {"BATTLEGOLD", NULL, 0, (void *) &config.battlegold, INT},
#endif
#ifdef _ANGEL_TIME
        {"ANGELPLAYERTIME", NULL, 0, (void *) &config.angelplayertime, INT},
        {"ANGELPLAYERMUN", NULL, 0, (void *) &config.angelplayermun, INT},
#endif
#ifdef _RIDEMODE_20
        {"RIDEMODE", NULL, 0, (void *) &config.ridemode, INT},
#endif
#ifdef _FM_POINT_PK
        {"FMPOINTPK", NULL, 0, (void *) &config.fmpointpk, INT},
#endif
#ifdef _ENEMY_ACTION
        {"ENEMYACTION", NULL, 0, (void *) &config.enemyact, INT},
#endif
        {"CPUUSE", NULL, 0, (void *) &config.cpuuse, INT},
#ifdef _FM_JOINLIMIT
        {"JOINFAMILYTIME", NULL, 0, (void *) &config.joinfamilytime, INT},
#endif
    };

// Arminius 7.12 login announce
char announcetext[8192];

void AnnounceToPlayer(int charaindex) {
  char *ptr, *qtr;

  ptr = announcetext;
  while((qtr = strstr(ptr, "\n")) != NULL) {
    qtr[0] = '\0';
//    printf("ptr=%s\n",ptr);
    CHAR_talkToCli(charaindex, -1, ptr, CHAR_COLORYELLOW);
    qtr[0] = '\n';
    ptr = qtr + 1;
  }
  CHAR_talkToCli(charaindex, -1, ptr, CHAR_COLORYELLOW);

}

void AnnounceToPlayerWN(int fd) {
  char buf[8192];
  lssproto_WN_send(fd, WINDOW_MESSAGETYPE_LOGINMESSAGE, WINDOW_BUTTONTYPE_OK, -1, -1, makeEscapeString(announcetext, buf, sizeof(buf))
  );
}


void LoadAnnounce(void) {
  FILE *f;

  memset(announcetext, 0, sizeof(announcetext));
  if((f = fopen("./announce.txt", "r")) != NULL) {
    fread(announcetext, sizeof(announcetext), 1, f);
    announcetext[sizeof(announcetext) - 1] = '\0';
    fclose(f);
  }
}

#ifdef _PET_TALKPRO
PTALK pettalktext[PETTALK_MAXID];

void LoadPetTalk(void) {
  FILE *fp;
  char fn[256];
  char line[4096];
  char talkmem[4096];
  int maxid = 0;
  char buf1[256], buf2[256], buf3[256];
  int talkNO = -1, mark = -1, i;
  int len = sizeof(talkmem);

  memset(talkmem, 0, sizeof(talkmem));
  sprintf(fn, "%s/pettalk/pettalk.menu", getNpcdir());

  for(i = 0; i < PETTALK_MAXID; i++) {
    pettalktext[i].ID = -1;
    strcpy(pettalktext[i].DATA, "\0");
  }

  print("\n装载宠物对话文件:%s...", fn);
  fp = fopen(fn, "r");
  if(fp != NULL) {
    while(fgets(line, sizeof(line), fp)) {
      if(strlen(talkmem) != 0) {
        if(talkmem[strlen(talkmem) - 1] != '|') {
          strcatsafe(talkmem, len, "|");
        }
      }
      chompex(line);
      strcatsafe(talkmem, len, line);
    }
    fclose(fp);
  } else {
    print("错误:找不到文件!");
  }

  talkNO = 1;
  while(getStringFromIndexWithDelim(talkmem, "END", talkNO, buf1, sizeof(buf1)) != FALSE) {
    talkNO++;
    if(NPC_Util_GetStrFromStrWithDelim(buf1, "PETTEMPNO", buf2, sizeof(buf2)) == NULL)
      continue;
    mark = 1;
    strcpy(fn, "\0");

    if(getStringFromIndexWithDelim(buf2, ",", mark + 1, buf3, sizeof(buf3)) != FALSE) {
      pettalktext[maxid].ID = atoi(buf3);
      if(getStringFromIndexWithDelim(buf2, ",", mark, buf3, sizeof(buf3)) != FALSE) {
        sprintf(fn, "%s/pettalk/%s", getNpcdir(), buf3);
        //print("\n ...file:%s", fn);
        fp = fopen(fn, "r");
        if(fp != NULL) {
          char line[4096];
          while(fgets(line, sizeof(line), fp)) {
            if(strlen(pettalktext[maxid].DATA) != 0) {
              if(pettalktext[maxid].DATA[strlen(pettalktext[maxid].DATA) - 1] != '|') {
                strcatsafe(pettalktext[maxid].DATA, sizeof(pettalktext[maxid].DATA), "|");
              }
            }
            chompex(line);
            strcatsafe(pettalktext[maxid].DATA, sizeof(pettalktext[maxid].DATA), line);
          }
          maxid++;
          fclose(fp);
        } else {
          print("错误:[%s] 找不到!", fn);
          pettalktext[maxid].ID = -1;
        }
      } else {
        pettalktext[maxid].ID = -1;
      }
    }
    print(".");
    if(maxid >= PETTALK_MAXID)
      break;
  }
  print("最大ID=%d...", maxid);
  {
    int haveid = 0;
    for(i = 0; i < PETTALK_MAXID; i++) {
      if(pettalktext[i].ID >= 0) {
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

void Load_GambleBankItems(void) {

  FILE *fp;
  char filename[256];
  char buf1[256];
  char name[128];
  int num, ID, type;
  int i = 0;
  snprintf(filename, sizeof filename, "%s/%s", getDataDir(), "gambleitems.txt");
  print("\n加载赌博物品文件 %s ...", filename);
  fp = fopen(filename, "r");
  if(fp != NULL) {
    while(fgets(buf1, sizeof(buf1), fp) != NULL) {
      if(strstr(buf1, "#") != 0) continue;
      sscanf(buf1, "%s %d %d %d", name, &ID, &num, &type);
      strcpy(GB_ITEMS[i].name, name);
      GB_ITEMS[i].Gnum = num;
      GB_ITEMS[i].ItemId = ID;
      GB_ITEMS[i].type = type;
      i++;
    }
    print("最大ID: %d ", i);
    fclose(fp);
  } else {
    print("错误 找不到文件 %s", filename);
  }

}

#endif


#ifdef _CFREE_petskill
PETSKILL_CODES Code_skill[PETSKILL_CODE];

void Load_PetSkillCodes(void) {
  FILE *fp;
  char filename[256];
  char buf1[256];
  char name[128];
  char type[256];
  int num, ID;
  int i = 0;
  snprintf(filename, sizeof filename, "%s/%s", getDataDir(), "skillcode.txt");
  print("\n加载宠物技能编码文件:%s...", filename);
  fp = fopen(filename, "r");
  if(fp != NULL) {
    while(fgets(buf1, sizeof(buf1), fp) != NULL) {
      sscanf(buf1, "%s %d %d %s", name, &num, &ID, type);
      strcpy(Code_skill[i].name, name);
      Code_skill[i].TempNo = num;
      Code_skill[i].PetId = ID;
      strcpy(Code_skill[i].Code, type);
      i++;
      if(i >= PETSKILL_CODE) break;
    }
    fclose(fp);
  } else {
    print("打不到文件 %s", filename);
  }
  print("完成\n");
}

#endif

#ifdef _GMRELOAD

int LoadGMSet(char *filename) {
  FILE *fp;
  int i = 0, gm_num = 0;
  fp = fopen(filename, "r");
  if(fp == NULL) {
    print("无法打开文件\n");
    return FALSE;
  }
  for(i = 0; i < GMMAXNUM; i++) {
    strcpy(gminfo[i].cdkey, "");
    gminfo[i].level = 0;
  }
  while(1) {
    char line[64], cdkey[64], level[64];
    if(fgets(line, sizeof(line), fp) == NULL) break;
    chop(line);
    //change 使gmset.txt可以增加注解*******
    if(line[0] == '#')
      continue;
    for(i = 0; i < strlen(line); i++) {
      if(line[i] == '#') {
        line[i] = '\0';
        break;
      }
    }
    //*************************************
    gm_num = gm_num + 1;
    if(gm_num > GMMAXNUM) break;
    easyGetTokenFromString(line, 1, cdkey, sizeof(cdkey));
    if(strcmp(cdkey, "") == 0) break;
    strncpy(gminfo[gm_num].cdkey, cdkey, sizeof(gminfo[gm_num].cdkey));
    easyGetTokenFromString(line, 2, level, sizeof(level));
    if(strcmp(level, "") == 0) break;
    gminfo[gm_num].level = atoi(level);
  }
  fclose(fp);
  return TRUE;
}

#endif

char* getDataDir() {
  return config.datadir;
}

char* getPublicKey() {
  return config.public_key;
}

char* getPrivateKey() {
  return config.private_key;
}

char* getSignature() {
  return config.signature;
}

char *getConfigfilename(void) {
  return config.configfilename;
}

void setConfigfilename(char *newv) {
  strcpysafe(config.configfilename, sizeof(config.configfilename), newv);
}

unsigned int getDebuglevel(void) {
  return config.debuglevel;
}

unsigned int setDebuglevel(unsigned int newv) {
  int old = config.debuglevel;
  config.debuglevel = newv;
  return old;
}

unsigned int getMemoryunit(void) {
  return config.usememoryunit;
}

unsigned int getMemoryunitnum(void) {
  return config.usememoryunitnum;
}

char *getAccountservername(void) {
  return config.asname;
}

unsigned short getAccountserverport(void) {
  return config.acservport;
}

char *getAccountserverpasswd(void) {
  return config.acpasswd;
}

char *getGameservername(void) {
  return config.gsnamefromas;
}

// Arminius 7.24 manor pk
char *getGameserverID(void) {
  if(config.gsid[strlen(config.gsid) - 1] == '\n')
    config.gsid[strlen(config.gsid) - 1] = '\0';

  return config.gsid;
}

unsigned short getAllowManorPK(void) {
  return config.allowmanorpk;
}

unsigned short getPortnumber(void) {
  return config.port;
}

int getServernumber(void) {
  return config.servernumber;
}

int getReuseaddr(void) {
  return config.reuseaddr;
}

int getNodelay(void) {
  return config.do_nodelay;
}

int getLogWriteTime(void) {
  return config.log_write_time;
}

int getLogIOTime(void) {
  return config.log_io_time;
}

int getLogGameTime(void) {
  return config.log_game_time;
}

int getLogNetloopFaster(void) {
  return config.log_netloop_faster;
}

int getSaacwritenum(void) {
  return config.saacwritenum;
}

void setSaacwritenum(int num) {
  config.saacwritenum = num;
}

int getSaacreadnum(void) {
  return config.saacreadnum;
}

void setSaacreadnum(int num) {
  config.saacreadnum = num;
}

unsigned int getFdnum(void) {
  return config.fdnum;
}

unsigned int getPetcharnum(void) {
  return config.petcharnum;
}

unsigned int getOtherscharnum(void) {
  return config.othercharnum;
}

unsigned int getObjnum(void) {
  return config.objnum;
}

unsigned int getItemnum(void) {
  return config.itemnum;
}

unsigned int getBattlenum(void) {
  return config.battlenum;
}

#ifdef _GET_BATTLE_EXP
                                                                                                                        unsigned int getBattleexp( void )
{
    return config.battleexp;
}
#endif

char *getTopdir(void) {
  return config.topdir;
}

char *getMapdir(void) {
  return config.mapdir;
}

char *getMaptilefile(void) {
  return config.maptilefile;
}

char *getBattleMapfile(void) {
  return config.battlemapfile;
}

char *getItemfile(void) {
  return config.itemfile;
}

char *getInvfile(void) {
  return config.invfile;
}

char *getAppearfile(void) {
  return config.appearfile;
}

char *getTitleNamefile(void) {
  return config.titlenamefile;
}

char *getTitleConfigfile(void) {
  return config.titleconfigfile;
}

char *getEncountfile(void) {
  return config.encountfile;
}

char *getEnemyfile(void) {
  return config.enemyfile;
}

char *getEnemyBasefile(void) {
  return config.enemybasefile;
}

char *getGroupfile(void) {
  return config.groupfile;
}

char *getMagicfile(void) {
  return config.magicfile;
}

#ifdef _ATTACK_MAGIC

char *getAttMagicfileName(void) {
  return config.attmagicfile;
}

#endif


char *getPetskillfile(void) {
  return config.petskillfile;
}


#ifdef _ITEM_QUITPARTY

char *getitemquitparty(void) {
  return config.itemquitparty;
}

#endif

char *getItematomfile(void) {
  return config.itematomfile;
}


char *getQuizfile(void) {
  return config.quizfile;
}

char *getLsgenlogfilename(void) {
  return config.lsgenlog;
}

#ifdef _GMRELOAD

char *getGMSetfile(void) {
  return config.gmsetfile;
}

#endif

char *getStoredir(void) {
  return config.storedir;
}

#ifdef _STORECHAR

char *getStorechar(void) {
  return config.storechar;
}

#endif

char *getNpcdir(void) {
  return config.npcdir;
}

char *getLogdir(void) {
  return config.logdir;
}

char *getLogconffile(void) {
  return config.logconfname;
}

char *getChatMagicPasswd(void) {
  return config.chatmagicpasswd;
}

unsigned getChatMagicCDKeyCheck(void) {
  return config.chatmagiccdkeycheck;
}

unsigned int getFilesearchnum(void) {
  return config.filesearchnum;
}

unsigned int getNpctemplatenum(void) {
  return config.npctemplatenum;
}

unsigned int getNpccreatenum(void) {
  return config.npccreatenum;
}

unsigned int getWalksendinterval(void) {
  return config.walksendinterval;
}

void setWalksendinterval(unsigned int interval) {
  config.walksendinterval = interval;
}

unsigned int getCAsendinterval_ms(void) {
  return config.CAsendinterval_ms;
}

void setCAsendinterval_ms(unsigned int interval_ms) {
  config.CAsendinterval_ms = interval_ms;
}

unsigned int getCDsendinterval_ms(void) {
  return config.CDsendinterval_ms;
}

void setCDsendinterval_ms(unsigned int interval_ms) {
  config.CDsendinterval_ms = interval_ms;
}

unsigned int getOnelooptime_ms(void) {
  return config.Onelooptime_ms;
}

void setOnelooptime_ms(unsigned int interval_ms) {
  config.Onelooptime_ms = interval_ms;
}

unsigned int getPetdeletetime(void) {
  return config.Petdeletetime;
}

void setPetdeletetime(unsigned int interval) {
  config.Petdeletetime = interval;
}

unsigned int getItemdeletetime(void) {
  return config.Itemdeletetime;
}

void setItemdeletetime(unsigned int interval) {
  config.Itemdeletetime = interval;
}

unsigned int getCharSavesendinterval(void) {
  return config.CharSavesendinterval;
}

void setCharSavesendinterval(unsigned int interval) {
  config.CharSavesendinterval = interval;
}

unsigned int getAddressbookoffmsgnum(void) {
  return config.addressbookoffmsgnum;
}

unsigned int getProtocolreadfrequency(void) {
  return config.protocolreadfrequency;
}

unsigned int getAllowerrornum(void) {
  return config.allowerrornum;
}

unsigned int getLogHour(void) {
  return config.loghour;
}

unsigned int getBattleDebugMsg(void) {
  return config.battledebugmsg;
}

void setBattleDebugMsg(unsigned int num) {
  config.battledebugmsg = num;
}

void defaultConfig(char *argv0) {
  char *program = rindex(argv0, '/');
  if(program == NULL)
    program = argv0;
  else
    program++;
  strcpysafe(config.configfilename, sizeof(config.configfilename), "config/setup.cf");
}


void lastConfig(void) {
  char entry[256];
  snprintf(entry, sizeof(entry), "%s/%s", &config.topdir, config.mapdir);
  strcpysafe(config.mapdir, sizeof(config.mapdir), entry);

  snprintf(entry, sizeof(entry), "%s/%s", config.topdir, config.maptilefile);
  strcpysafe(config.maptilefile, sizeof(config.maptilefile), entry);

  snprintf(entry, sizeof(entry), "%s/%s", config.topdir, config.battlemapfile);
  strcpysafe(config.battlemapfile, sizeof(config.battlemapfile), entry);

  snprintf(entry, sizeof(entry), "%s/%s", &config.topdir, config.itemfile);
  strcpysafe(config.itemfile, sizeof(config.itemfile), entry);

  snprintf(entry, sizeof(entry), "%s/%s", &config.topdir, config.invfile);
  strcpysafe(config.invfile, sizeof(config.invfile), entry);

  snprintf(entry, sizeof(entry), "%s/%s", &config.topdir, config.appearfile);
  strcpysafe(config.appearfile, sizeof(config.appearfile), entry);

  snprintf(entry, sizeof(entry), "%s/%s", &config.topdir, config.quizfile);
  strcpysafe(config.quizfile, sizeof(config.quizfile), entry);

  snprintf(entry, sizeof(entry), "%s/%s", &config.topdir, config.titlenamefile);
  strcpysafe(config.titlenamefile, sizeof(config.titlenamefile), entry);

  snprintf(entry, sizeof(entry), "%s/%s", &config.topdir, config.lsgenlog);
  strcpysafe(config.lsgenlog, sizeof(config.lsgenlog), entry);

  snprintf(entry, sizeof(entry), "%s/%s", &config.topdir, config.npcdir);
  strcpysafe(config.npcdir, sizeof(config.npcdir), entry);

#ifdef _STORECHAR
  /*   */
  snprintf(entry, sizeof(entry), "%s/%s", &config.topdir, config.storechar);
  strcpysafe(config.storechar, sizeof(config.storechar), entry);
#endif

}

void substitutePointerFromType(void *to, CTYPE type, double value) {
  switch(type) {
    case CHAR:
      *(char *) to = (char) value;
      break;
    case SHORT:
      *(short *) to = (short) value;
      break;
    case INT:
      *(int *) to = (int) value;
      break;
    case DOUBLE:
      *(double *) to = value;
      break;
  }
}

int readconfigfile(char *filename) {
  FILE *f = fopen(filename, "r");
  char linebuf[256];
  int linenum = 0;
  while(fgets(linebuf, sizeof(linebuf), f)) {
    linenum++;
    deleteWhiteSpace(linebuf);

    if(linebuf[0] == '#')
      continue;

    if(linebuf[0] == '\n')
      continue;

    chomp(linebuf);
    char firstToken[256];
    if(getStringFromIndexWithDelim(linebuf, "=", 1, firstToken, sizeof(firstToken)) == FALSE) {
      print("Find error at %s in line %d. Ignore\n", filename, linenum);
      continue;
    }

    for(int i = 0; i < arraysizeof(readconf); i++) {
      if(strcmp(readconf[i].name, firstToken) == 0) {
        char secondToken[256];
        int ret = getStringFromIndexWithDelim(linebuf, "=", 2, secondToken, sizeof(secondToken));
        if(ret == FALSE) {
          print("Find error at %s in line %d. Ignore", filename, linenum);
          break;
        }

        if(readconf[i].charvalue != NULL)
          strcpysafe(readconf[i].charvalue, readconf[i].charsize, secondToken);

        if(readconf[i].value != NULL) {
          if(strcmp("ON", secondToken) == 0) {
            substitutePointerFromType(readconf[i].value, readconf[i].valuetype, 1.0);
          } else if(strcmp("OFF", secondToken) == 0) {
            substitutePointerFromType(readconf[i].value, readconf[i].valuetype, 1.0);
          } else {
            strtolchecknum(secondToken, (int *) readconf[i].value, 10, readconf[i].valuetype);
          }
        }
        break;
      }
    }
  }
  fclose(f);
  lastConfig();
  return TRUE;
}

unsigned int setAcWBSize(void) {
  AC_WBSIZE = config.acwbsize;
  return AC_WBSIZE;
}

unsigned int getAcwriteSize(void) {
  return config.acwritesize;
}

unsigned int getErrUserDownFlg(void) {
  return config.ErrUserDownFlg;
}


#ifdef _DEL_DROP_GOLD

unsigned int getGolddeletetime(void) {
  if(config.Golddeletetime > 0)
    return config.Golddeletetime;
  else
    return config.Itemdeletetime;
}

void setIGolddeletetime(unsigned int interval) {
  config.Golddeletetime = interval;
}

#endif

#ifdef _NEW_PLAYER_CF

int getNewplayertrans(void) {
  if(config.newplayertrans > 7)
    return 7;
  else if(config.newplayertrans >= 0)
    return config.newplayertrans;
  else
    return 0;
}

int getNewplayerlv(void) {
  if(config.newplayerlv > 160)
    return 160;
  else if(config.newplayerlv > 0)
    return config.newplayerlv;
  else
    return 0;
}

int getNewplayerpetlv(void) {
  if(config.newplayerpetlv > 160)
    return 160;
  else if(config.newplayerpetlv > 0)
    return config.newplayerpetlv;
  else
    return 0;
}

int getNewplayergivepet(unsigned int index) {
  if(config.newplayergivepet[index] > 0)
    return config.newplayergivepet[index];
  else
    return -1;
}

int getNewplayergiveitem(unsigned int index) {
  if(config.newplayergiveitem[index] > 0)
    return config.newplayergiveitem[index];
  else
    return -1;
}

void setNewplayergivepet(unsigned int index, unsigned int interval) {
  config.newplayergivepet[index] = interval;
}

int getNewplayergivegold(void) {
  if(config.newplayergivegold > 1000000)
    return 1000000;
  else if(config.newplayergivegold < 0)
    return 0;
  else
    return config.newplayergivegold;
}

int getRidePetLevel(void) {
  if(config.ridepetlevel > 0)
    return config.ridepetlevel;
  else
    return -1;
}

#ifdef _VIP_SERVER

int getNewplayergivevip(void) {
  return config.newplayerpetvip < 0 ? 0 : config.newplayerpetvip;
}

#endif
#endif

#ifdef _UNLAW_WARP_FLOOR

int getUnlawwarpfloor(unsigned int index) {
  if(config.unlawwarpfloor[index] > 0)
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

char *getUnregname(int index) {
  return config.unregname[index];
}

#endif

#ifdef _TRANS_LEVEL_CF

int getChartrans(void) {
  if(config.chartrans > 6)
    config.chartrans = 6;
  return config.chartrans;
}

int getPettrans(void) {
  if(config.pettrans > 2)
    return 2;
  else if(config.pettrans < -1)
    return -1;
  return config.pettrans;
}

int getYBLevel(void) {
  if(config.yblevel > config.maxlevel)
    config.yblevel = config.maxlevel;
  return config.yblevel;
}

int getMaxLevel(void) {
  return config.maxlevel;
}

#endif

#ifdef _POINT

char *getPoint(void) {
  return (config.point > 0) ? "是" : "否";
}

int getTransPoint(int index) {
  return config.transpoint[index];
}

#endif

#ifdef _PET_UP

char *getPetup(void) {
  return (config.petup > 0) ? "是" : "否";
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

int getCharloops(void) {
  return config.charloops - 1;
}

#endif

#ifdef _PLAYER_ANNOUNCE

int getPAnnounce(void) {
  return (config.pannounce > -1) ? config.pannounce : -1;
}

#endif
#ifdef _PLAYER_MOVE

int getPMove(void) {
  return (config.pmove > -1) ? config.pmove : -1;
}

#endif

int getrecvbuffer(void) {
  if(config.recvbuffer < 0)
    return 0;
  else if(config.recvbuffer > 128)
    return 128;
  else
    return config.recvbuffer;
}

int getsendbuffer(void) {
  if(config.sendbuffer < 0)
    return 0;
  else if(config.sendbuffer > 128)
    return 128;
  else
    return config.sendbuffer;
}

int getrecvlowatbuffer(void) {
  if(config.recvlowatbuffer < 0)
    return 0;
  else if(config.recvlowatbuffer > 1024)
    return 1024;
  else
    return config.recvlowatbuffer;
}

int getrunlevel(void) {
  if(config.runlevel < -20)
    return -20;
  else if(config.runlevel > 19)
    return 19;
  else
    return config.runlevel;

}

#ifdef _SHOW_VIP_CF

int getShowVip(void) {
  if(config.showvip > 2)
    return 2;
  else if(config.showvip < 0)
    return 0;
  else
    return config.showvip;
}

#endif

#ifdef _PLAYER_NUM

int getPlayerNum(void) {
  return config.playernum;
}

void setPlayerNum(int num) {
  config.playernum = num;
}

#endif
#ifdef _JZ_CF_DELPETITEM

int getDelPet(int Num) {
  return config.DelPet[Num];
}

int getDelItem(int Num) {
  return config.DelItem[Num];
}

#endif
#ifdef _BATTLE_GOLD

int getBattleGold(void) {
  if(config.battlegold < 0)
    return 0;
  else if(config.battlegold > 100)
    return 100;
  else
    return config.battlegold;

}

#endif

#ifdef _ANGEL_TIME

int getAngelPlayerTime(void) {
  return (config.angelplayertime > 1) ? config.angelplayertime : 1;
}

int getAngelPlayerMun(void) {
  return (config.angelplayermun > 2) ? config.angelplayermun : 2;
}

#endif

#ifdef _RIDEMODE_20

int getRideMode(void) {
  if(config.ridemode < 0)
    config.ridemode = 0;
  return config.ridemode;
}

#endif
#ifdef _FM_POINT_PK

char *getFmPointPK(void) {
  return (config.fmpointpk > 0) ? "是" : "否";
}

#endif
#ifdef _ENEMY_ACTION

int getEnemyAction(void) {
  if(config.enemyact > 100)
    return 100;
  else if(config.enemyact < 1)
    return 1;
  else
    return config.enemyact;
}

#endif

int getCpuUse(void) {
  return config.cpuuse;
}

#ifdef _FM_JOINLIMIT

int getJoinFamilyTime(void) {
  return config.joinfamilytime;
}

#endif
