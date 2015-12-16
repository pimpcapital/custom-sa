#ifndef __NPC_AIRPLANE_H__
#define __NPC_AIRPLANE_H__

int NPC_AirInit( int meindex );
void NPC_AirLoop( int meindex );
void NPC_AirTalked( int meindex , int talkerindex , char *szMes ,
                     int color );
int NPC_AirCheckAllowItem( int meindex, int charaindex, int pickupmode);
int NPC_AirCheckJoinParty( int meindex, int charaindex, int msgflg);

#endif 
/*__NPC_AIRPLANE_H__*/
