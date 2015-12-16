#ifndef __NPC_BUS_H__
#define __NPC_BUS_H__

int NPC_BusInit( int meindex );
void NPC_BusLoop( int meindex );
void NPC_BusTalked( int meindex , int talkerindex , char *szMes ,
                     int color );
int NPC_BusCheckAllowItem( int meindex, int charaindex, int pickupmode);
int NPC_BusCheckJoinParty( int meindex, int charaindex, int msgflg);

#endif

