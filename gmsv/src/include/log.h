#ifndef __LOG_H__
#define __LOG_H__

#include <time.h>

typedef enum {
  LOG_TALK,
  LOG_PROC,
  LOG_ITEM,
  LOG_STONE,
  LOG_PET,
  LOG_TENSEI,
  LOG_KILL,     //ttom 12/26/2000 kill the pet & items
  LOG_TRADE,  // CoolFish: 2001/4/19
  LOG_HACK,  // Arminius 2001/6/14
  LOG_SPEED,  // Nuke 0626
  LOG_FMPOP,  // CoolFish: 2001/9/12
  LOG_FAMILY, // Robin 10/02
  LOG_GM,     // Shan
#ifdef _GAMBLE_ROULETTE
  LOG_GAMBLE,
#endif

  LOG_LOGIN,
  PETTRANS,
//Syu 增加庄园战胜负Log
      LOG_FMPKRESULT,

// Syu ADD 新增家族个人银行存取Log (不含家族银行)
      LOG_BANKSTONELOG,

  LOG_ACMESS,
  LOG_PKCONTEND,
  LOG_TYPE_NUM,
} LOG_TYPE;

void closeAllLogFile(void);

int initLog(char *filename);

void printl(LOG_TYPE logtype, char *format, ...);

void LogAcMess(int fd, char *type, char *mess);

void LogItem(
    char *CharName,
    char *CharID,
    int ItemNo,
    char *Key,
    int floor,
    int x,
    int y,
    char *uniquecode,
    char *itemname, int itemID
);

void LogPetTrans(
    char *cdkey, char *uniwuecde, char *uniwuecde2, char *CharName, int floor, int x, int y,
    int petID1, char *PetName1, int petLV, int petrank, int vital1, int str1, int tgh1, int dex1, int total1,
    int petID2, char *PetName2, int vital2, int str2, int tgh2, int dex2, int total2,
    int work0, int work1, int work2, int work3, int ans, int trans
);

void LogPet(
    char *CharName,
    char *CharID,
    char *PetName,
    int PetLv,
    char *Key,
    int floor,
    int x,
    int y,
    char *uniquecode
);

void LogTensei(
    char *CharName,
    char *CharID,
    char *Key,
    int level,
    int transNum,
    int quest,
    int home,
    int item,
    int pet,
    int vital,
    int b_vital,
    int str,
    int b_str,
    int tgh,
    int b_tgh,
    int dex,
    int b_dex
);

// Syu ADD 新增家族个人银行存取Log (不含家族银行)
void LogFamilyBankStone(
    char *CharName,
    char *CharId,
    int Gold,
    int MyGold,
    char *Key,
    int floor,
    int x,
    int y,
    int banksum
);

void LogStone(
    int TotalGold,
    char *CharName,
    char *CharId,
    int Gold,
    int MyGold,
    char *Key,
    int floor,
    int x,
    int y
);

void LogTalk(
    char *CharName,
    char *CharID,
    int floor,
    int x,
    int y,
    char *message
);

//ttom 12/26/2000 kill pet & items
void LogKill(
    char *CharName,
    char *CharId,
    char *CharPet_Item
);
//ttom

void LogTrade(char *message);

void LogFMPOP(char *message);

enum {
  HACK_NOTHING,
  HACK_GETFUNCFAIL,
  HACK_NOTDISPATCHED,
  HACK_CHECKSUMERROR,
  HACK_HP,
  HACK_TYPE_NUM,
} HACK_TYPE;

void logHack(int fd, int errcode);

void closeAllLogFile(void);

int openAllLogFile(void);

void LogFamily(
    char *FMName,
    int fmindex,
    char *charName,
    char *charId,
    char *keyWord,
    char *data
);


void LogGM(
    char *CharName,    //角色名称
    char *CharID,      //玩家ID
    char *Message,     //指令内容
    int floor,
    int x,
    int y
);


void LogLogin(
    char *CharID,   //玩家ID
    char *CharName, //角色名称
    int saveIndex,
    char *ipadress
);

#ifdef _GAMBLE_ROULETTE

void LogGamble(
    char *CharName, //角色名称
    char *CharID,   //玩家ID
    char *Key,      //说明
    int floor,
    int x,
    int y,
    int player_stone,  //所拥有金钱
    int Gamble_stone,  //下注本金
    int get_stone,    //获得
    int Gamble_num,
    int flg  //flg = 1 玩家 2 庄家
);

#endif

void LogBankStone(
    char *CharName,
    char *CharId,
    int meindex,
    int Gold,
    char *Key,
    int floor,
    int x,
    int y,
    int my_gold,
    int my_personagold
);

//Syu 增加庄园战胜负Log
void Logfmpk(
    char *winner, int winnerindex, int num1,
    char *loser, int loserindex, int num2, char *date, char *buf1, char *buf2, int flg);

void backupAllLogFile(struct tm *ptm);

void LogPetPointChange(
    char *CharName, char *CharID, char *PetName, int petindex, int errtype,
    int PetLv, char *Key, int floor, int x, int y);

#endif
