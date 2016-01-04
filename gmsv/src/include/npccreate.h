#ifndef __READNPCCREATE_H__
#define __READNPCCREATE_H__

#include "util.h"

#define NPC_CREATEFILEMAGIC   "NPCCREATE\n"


#undef EXTERN
#ifdef __NPCCREATE__
#define EXTERN
#else
#define EXTERN extern
#endif


typedef enum {
  NPC_CREATEFLOORID,
  NPC_CREATEBORNLEFTUPX,
  NPC_CREATEBORNLEFTUPY,
  NPC_CREATEBORNRIGHTDOWNX,
  NPC_CREATEBORNRIGHTDOWNY,

  NPC_CREATEMOVELEFTUPX,
  NPC_CREATEMOVELEFTUPY,
  NPC_CREATEMOVERIGHTDOWNX,
  NPC_CREATEMOVERIGHTDOWNY,

  NPC_CREATEDIR,
  NPC_CREATEBASEIMAGENUMBER,
  NPC_CREATETIME,
  NPC_CREATEBORNNUM,

  NPC_CREATEENEMYNUM,
  NPC_CREATEBOUNDARY,
  NPC_CREATEDATE,
  NPC_CREATEIGNOREINVINCIBLE,
  NPC_CREATEFAMILY,
#ifdef _ADD_ACTION
  NPC_CREATEACTION,
#endif
  NPC_CREATEINTNUM,

} NPC_CREATEINT;

typedef enum {
  NPC_CREATENAME,
  NPC_CREATECHARNUM,
} NPC_CREATECHAR;


typedef enum {
  NPC_CREATEWORKENEMYNUM,
  NPC_CREATEWORKMAKESTARTSEC,
  NPC_CREATEWORKMAKESTARTUSEC,
  NPC_CREATEWORKNEVERMAKE,
  NPC_CREATEWORKNUM,

} NPC_CREATEWORK;

typedef struct tagNPC_Create {
  int intdata[NPC_CREATEINTNUM];
  STRING64 chardata[NPC_CREATECHARNUM];
  int workdata[NPC_CREATEWORKNUM];
  int templateindex[8];
  STRING64 arg[8];
} NPC_Create;


EXTERN NPC_Create *NPC_create;
EXTERN int NPC_createnum;
EXTERN int NPC_create_readindex;

int NPC_CHECKCREATEINDEX(int index);

int NPC_isBoundarySet(int createindex);

int NPC_createGetRECT(int createindex, RECT *r);

int NPC_readNPCCreateFiles(char *topdirectory, int createsize);

int NPC_getCreateInt(int index, NPC_CREATEINT element);

int NPC_createCheckGenerateFromTime(int tindex);

void NPC_createInitTime(int index);

void NPC_createIncreaseEnemynum(int index);

void NPC_createDecreaseEnemynum(int index);

int NPC_createCheckMaxEnemynum(int index);

#endif