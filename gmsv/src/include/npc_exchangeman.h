#ifndef __NPC_EXCHANGEMAN_H__
#define __NPC_EXCHANGEMAN_H__

void NPC_ExChangeManTalked(int meindex, int talkerindex, char *msg, int color);

int NPC_ExChangeManInit(int meindex);

void NPC_ExChangeManWindowTalked(int meindex, int talkerindex, int seqno, int select, char *data);


int NPC_EventCheckFlg(int talker, int shiftbit);

int NPC_NowEventCheckFlg(int talker, int shiftbit);

// Arminius 8.14 move from .c (for pet talk)
int NPC_EventBigSmallCheck(int meindex, int talker, char *buf);

#endif


