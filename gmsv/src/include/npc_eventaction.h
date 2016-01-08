#ifndef _PRO_NPCFIX_H
#define _PRO_NPCFIX_H
//ANDY_Edit
int ActionNpc_CheckMenuFree( int meindex, int toindex, char *npcarg, int nums);
int ActionNpc_CheckFree( int meindex, int toindex, char *npcarg);
int Action_RunDoEventAction( int meindex, int toindex, char *buf1);
int ActionNpc_WarpPoint(int meindex,int talker,char *npcarg);
int Action_PartyCheck( int meindex, int talker);
int NPC_ActionAddGold( int talker, int Golds);
int NPC_ActionDelGold( int talker,char *buf);
#ifdef _DP_NPC
int NPC_ActionDP( int talker,char *buf);
#endif
#ifdef _VIP_SHOP
int NPC_ActionDelVipPoint( int talker,char *buf);
#endif
// WON ADD
int NPC_ActionAddGold2( int talker,char *buf);
int NPC_ActionDelPet( int toindex,char *buf);
#ifdef _NPC_NewDelPet
int NPC_ActionNewDelPet( int talker,char *msg);
#endif
int NPC_ActionAddPet( int talker, char *buf);
int NPC_ActionDelItem( int talker,char *buf);
int NPC_ActionAddItem( int talker, char *buf);
int NPC_ActionSetEend( int talkerindex, char * buf);
int NPC_ActionSetNow( int toindex, char * buf);
int NPC_ActionClearEvent( int toindex, char * buf);

int NPC_ActionCheckTrans(int meindex,int talker,int trans,int flg);
#ifdef _VIP_SHOP
int NPC_ActionVipPointCheck(int meindex,int talker,int point,int flg);
#endif
#ifdef _VIP_RIDE
int NPC_ActionVipCheck(int meindex,int talker,int vip,int flg);
#endif
#ifdef _MOMENTUM_NPC
int NPC_ActionMomentumCheck(int meindex,int talker,int Momentum,int flg);
#endif
#ifdef _DP_NPC
int NPC_ActionDPCheck(int meindex,int talker,int DP,int flg);
#endif
int NPC_ActionLevelCheck(int meindex,int talker,int level,int flg);

int NPC_ActionGoldCheck(int meindex,int talker,int Golds,int flg);
int NPC_ActionPartyCheck( int toindex, int nums, int flg);
int NPC_ActionReItemCheck( int toindex, int nums, int flg);
int NPC_ActionRePetCheck( int toindex, int nums, int flg);
int ActionCheckMyPet( int meindex, int talker, int petLv, int flg, int petid);
int NPC_ActionBigSmallLastCheck(int point1,int mypoint,int flg);

int NPC_ActionItemCheck(int meindex,int talker,int itemNo, int flg);
int NPC_ActioneEquitCheck(int meindex,int talker,int itemNo, int flg);

int NPC_ActionFreeIfCheck(int meindex,int talker, char* buf, char *opt, int kosuu,int flg, int temp);

int NPC_ActionBigSmallCheck(int meindex,int talker,char* buf);
int NPC_ActionPassCheck( int meindex, int talker, char *buf);
int NPC_ActionWarpManReduce(int meindex,int talker,char *buf);
#ifdef _NPC_ActionFreeCmp 
int NPC_ActionWarpManReduce2(int meindex,int talker,char *buf);
#endif
#ifdef _NPCCHANGE_PLAYERIMG	//andy
int NPC_ActionChangePlayerBBI( int meindex, int charindex, char *Img);
int NPC_CheckPlayerBBI( int meindex, int charindex, int BBI, int flg);
#endif

int showString( int meindex, char *showstr,int flg);
int NPC_getTimeXYPoint( int meindex, int Mode);
int NPC_getTimeData( int meindex, char *npcarg, int *born, int *dead, int loopspeed);
void NPC_TimeDefineDo( int meindex, int born, int dead, int typeMode);
int NPC_CheckTimeDefine( char *timetype);

void GetRand_WarpPoint( char *buf, int *fl, int *x, int *y );

int NPC_ActionDuelRankCheck(int meindex,int talker,int rank,int flg);
int NPC_ActionDuelPointCheck(int meindex,int talker,int rank,int flg);

#ifdef _TREASURE_BOX
int NPC_ActionTreasureTypeCheck( int meindex, int level, int type, int flg);
#endif
int NPC_ActionTreasureRandItemGet(int meidex,int talker,int rand_j,char *buf);
void NPC_ActionLevelAndTransUp( int meindex, int charindex, int level,
							   int skillpoint, int exp, int ridepet);
void NPC_ActionDoPileClearItem( int toindex, int itemID);

#ifdef _NPC_ADDWARPMAN1
int NPC_ActionPartyCountCheck( int toindex, int nums, int flg);
int NPC_ActionManCountCheck( int toindex, int nums, int flg);//检查男生人数
int NPC_ActionWomanCountCheck( int toindex, int nums, int flg);//检查女生人数
#endif

#endif
