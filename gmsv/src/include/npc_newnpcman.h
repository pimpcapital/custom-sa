#ifndef __NPC_NEWNPCMAN_H__
#define __NPC_NEWNPCMAN_H__
int NPC_NewNpcManInit( int meindex );
void NPC_NewNpcManLoop( int meindex);
void NPC_NewNpcManTalked( int meindex , int talkerindex , char *msg , int color );
void NPC_NewNpcManWindowTalked( int meindex, int talkerindex, int seqno, int select, char *data);
#endif

