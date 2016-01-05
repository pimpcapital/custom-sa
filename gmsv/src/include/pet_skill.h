#ifndef __PET_SKILL_H__
#define __PET_SKILL_H__

#include "util.h"

typedef enum {
  PETSKILL_FIELD_ALL,
  PETSKILL_FIELD_BATTLE,
  PETSKILL_FIELD_MAP,

} PETSKILL_FIELDTYPE;

typedef enum {
  PETSKILL_TARGET_MYSELF,
  PETSKILL_TARGET_OTHER,
  PETSKILL_TARGET_ALLMYSIDE,
  PETSKILL_TARGET_ALLOTHERSIDE,
  PETSKILL_TARGET_ALL,
  PETSKILL_TARGET_NONE,
  PETSKILL_TARGET_OTHERWITHOUTMYSELF,
  PETSKILL_TARGET_WITHOUTMYSELFANDPET,
} PETSKILL_TARGETTYPE;

typedef enum {
  PETSKILL_ID,
  PETSKILL_FIELD,
  PETSKILL_TARGET,
#ifdef _PETSKILL2_TXT
  PETSKILL_USETYPE,
#endif
  PETSKILL_COST,
  PETSKILL_ILLEGAL,
  PETSKILL_DATAINTNUM,
} PETSKILL_DATAINT;

typedef enum {
  PETSKILL_NAME,
  PETSKILL_COMMENT,
  PETSKILL_FUNCNAME,
  PETSKILL_OPTION,
#ifdef _CFREE_petskill
  PETSKILL_FREE,
  PETSKILL_KINDCODE,
#endif

  PETSKILL_DATACHARNUM,
} PETSKILL_DATACHAR;

typedef struct tagPetskill {
  int data[PETSKILL_DATAINTNUM];
  STRING64 string[PETSKILL_DATACHARNUM];

} Petskill;

typedef int (*PETSKILL_CALLFUNC)(int, int, int, char *);

int PETSKILL_CHECKINDEX(int index);

int PETSKILL_getInt(int index, PETSKILL_DATAINT element);

int PETSKILL_setInt(int index, PETSKILL_DATAINT element, int data);

char *PETSKILL_getChar(int index, PETSKILL_DATACHAR element);

int PETSKILL_setChar(int index, PETSKILL_DATACHAR element, char *new);

int PETSKILL_getPetskillNum(void);

#define    PETSKILL_GetArray(charaindex, havepetskill)  _PETSKILL_GetArray( __FILE__, __LINE__, charaindex, havepetskill)

int _PETSKILL_GetArray(char *file, int line, int charaindex, int havepetskill);

int PETSKILL_initPetskill(char *filename);

int PETSKILL_reinitPetskill(void);

int PETSKILL_getPetskillArray(int petskillid);

PETSKILL_CALLFUNC PETSKILL_getPetskillFuncPointer(char *name);

int PETSKILL_Use(
    int charaindex,
    int toindex,
    int array,
    char *data
    //int isCLI	// Robin 2001/02/26 if owner is player
);

int PETSKILL_ContinuationAttack(
    int charaindex,
    int toindex,
    int array,
    char *data
);

int PETSKILL_ChargeAttack(
    int charaindex,
    int toindex,
    int array,
    char *data
);

int PETSKILL_Guardian(
    int charaindex,
    int toindex,
    int array,
    char *data
);

int PETSKILL_PowerBalance(
    int charaindex,
    int toindex,
    int array,
    char *data
);

int PETSKILL_Mighty(
    int charaindex,
    int toindex,
    int array,
    char *data
);

int PETSKILL_StatusChange(
    int charaindex,
    int toindex,
    int array,
    char *data

);

int PETSKILL_NormalAttack(
    int charaindex,
    int toindex,
    int array,
    char *data

);

int PETSKILL_NormalGuard(
    int charaindex,
    int toindex,
    int array,
    char *data

);

int PETSKILL_None(
    int charaindex,
    int toindex,
    int array,
    char *data

);

int PETSKILL_EarthRound(
    int charaindex,
    int toNo,
    int array,
    char *data

);

int PETSKILL_GuardBreak(
    int charaindex,
    int toNo,
    int array,
    char *data

);

#ifdef _SKILL_GUARDBREAK2//破除防御2 vincent add 2002/05/20

int PETSKILL_GuardBreak2(
    int charaindex,
    int toNo,
    int array,
    char *data

);

#endif

int PETSKILL_Abduct(
    int charaindex,
    int toNo,
    int array,
    char *data

);

int PETSKILL_Steal(
    int charaindex,
    int toNo,
    int array,
    char *data

);

#ifdef _BATTLESTEAL_FIX

int PETSKILL_StealMoney(
    int charaindex,
    int toNo,
    int array,
    char *data

);

#endif

#ifdef _ITEM_INSLAY

int PETSKILL_Inslay(
    int index,
    int toNo,
    int array,
    char *data

);

#endif

#ifdef _PETSKILL_FIXITEM

int PETSKILL_Fixitem(
    int index,
    int toNo,
    int array,
    char *data

);

#endif

int PETSKILL_Merge(
    int charaindex,
    int toNo,
    int array,
    char *data

);

int PETSKILL_NoGuard(
    int charaindex,
    int toNo,
    int array,
    char *data

);

#ifdef _ATTACK_MAGIC

int PETSKILL_AttackMagic(
    int charaindex,
    int toindex,
    int array,
    char *data
);

#endif

#ifdef _VARY_WOLF

int PETSKILL_Vary(int cindex, int tindex, int id, char *data);

#endif

#ifdef _SKILL_WILDVIOLENT_ATT

//vincent add 2002/05/16
int PETSKILL_WildViolentAttack(
    int charaindex,
    int toindex,
    int array,
    char *data
);

#endif

#ifdef _SKILL_SPEEDY_ATT

//vincent add 2002/05/16
int PETSKILL_SpeedyAttack(
    int charaindex,
    int toindex,
    int array,
    char *data
);

#endif

#ifdef _SKILL_SACRIFICE

//vincent add 2002/05/30
int PETSKILL_Sacrifice(
    int charaindex,
    int toindex,
    int array,
    char *data
);

#endif

#ifdef _SKILL_REFRESH

//vincent add 2002/08/08
int PETSKILL_Refresh(
    int charaindex,
    int toindex,
    int array,
    char *data
);

#endif

#ifdef _SKILL_WEAKEN  //vincent宠技:虚弱

int PETSKILL_Weaken(
    int charaindex,
    int toindex,
    int array,
    char *data
);

#endif

#ifdef _SKILL_DEEPPOISON  //vincent宠技:剧毒 

int PETSKILL_Deeppoison(
    int charaindex,
    int toindex,
    int array,
    char *data
);

#endif

#ifdef _SKILL_BARRIER  //vincent宠技:魔障

int PETSKILL_Barrier(
    int charaindex,
    int toindex,
    int array,
    char *data
);

#endif

#ifdef _SKILL_ROAR //vincent宠技:大吼

int PETSKILL_Roar(
    int charaindex,
    int toindex,
    int array,
    char *data
);

#endif

#ifdef _PSKILL_FALLGROUND

int PETSKILL_FallGround(int charaindex, int toNo, int array, char *data);

#endif
#ifdef _PRO_BATTLEENEMYSKILL

int ENEMYSKILL_ReLife(int enemyindex, int toNo, int array, char *data);

int ENEMYSKILL_ReHP(int enemyindex, int toNo, int array, char *data);

int ENEMYSKILL_EnemyHelp(int enemyindex, int toNo, int array, char *data);

#endif

#ifdef _SKILL_DAMAGETOHP

int PETSKILL_DamageToHp(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _PETSKILL_TIMID

int PETSKILL_BattleTimid(int charaindex, int toNo, int array, char *data);

#endif
#ifdef _PETSKILL_2TIMID

int PETSKILL_2BattleTimid(int charaindex, int toNo, int array, char *data);

#endif
#ifdef _PETSKILL_ANTINTER

int PETSKILL_AntInter(int charaindex, int toindex, int array, char *data);    // 宠物技能战斗模组
#endif

#ifdef _PETSKILL_PROPERTY

int PETSKILL_BattleProperty(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _PETSKILL_TEAR

int PETSKILL_BattleTearDamage(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _BATTLE_LIGHTTAKE

int PETSKILL_Lighttakeed(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _BATTLE_ATTCRAZED

int PETSKILL_AttackCrazed(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _Skill_MPDAMAGE

int PETSKILL_MpDamage(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _PETSKILL_SETDUCK

int PETSKILL_SetDuck(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _MAGICPET_SKILL

int PETSKILL_SetMagicPet(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _SKILL_TOOTH

int PETSKILL_ToothCrushe(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _PSKILL_MODIFY

int PETSKILL_Modifyattack(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _PSKILL_MDFYATTACK

int PETSKILL_Mdfyattack(int charaindex, int toNo, int array, char *data);

#endif


#ifdef _MAGIC_SUPERWALL

int PETSKILL_MagicStatusChange(int charaindex, int toindex, int array, char *data);

#endif

#ifdef _PET_SKILL_SARS        // WON ADD 毒煞蔓延

int PETSKILL_Sars(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _SONIC_ATTACK        // WON ADD 音波攻击

int PETSKILL_Sonic(int charaindex, int toNo, int array, char *data);

#endif
#ifdef _PETSKILL_REGRET

int PETSKILL_Regret(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _PETSKILL_GYRATE

int PETSKILL_Gyrate(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _PETSKILL_RETRACE

int PETSKILL_Retrace(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _PETSKILL_HECTOR

int PETSKILL_Hector(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _PETSKILL_FIREKILL

int PETSKILL_Firekill(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _PETSKILL_DAMAGETOHP   //暗月狂狼(嗜血技的变体) 

int PETSKILL_DamageToHp2(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _PETSKILL_BECOMEFOX

int PETSKILL_BecomeFox(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _PETSKILL_BECOMEPIG

int PETSKILL_BecomePig(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _PETSKILL_SHOWMERCY

int PETSKILL_ShowMercy(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _PETSKILL_COMBINED

int PETSKILL_Combined(int charaindex, int toNo, int array, char *data);

#endif

#ifdef _PETSKILL_BATTLE_MODEL

int PETSKILL_BattleModel(int charaindex, int toindex, int array, char *data);    // 宠物技能战斗模组
#endif

#endif
