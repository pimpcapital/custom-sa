#ifndef __NPC_ROOMADMINNEW_H__
#define __NPC_ROOMADMINNEW_H__


void NPC_RoomAdminNewTalked( int meindex , int talkerindex , char *msg , int color );
void NPC_RoomAdminNewLoop( int meindex );
int NPC_RoomAdminNewInit( int meindex );

int NPC_RankingInit( int meindex );
void NPC_RankingTalked( int meindex , int talkerindex , char *msg ,int color );

int NPC_PrintpassmanInit( int meindex );
void NPC_PrintpassmanTalked( int meindex , int talkerindex , char *msg ,int color );

#if 0
typedef struct roomadmin_tag
{
    int index;              /*   盒及index */

    char doorname[256];     /* 公及  盒及玉失�?  �? */
    char explanation[256];  /*      */
    char passwd[256];       /* 由旦伐□�? */
    int expire_time_mod;    /* 匏锹 */
    time_t expire_time;     /* 渝蜃濠木及凛�? */
    int least_cost;         /*   斓嗯�? */

}NPC_ROOMINFO;
#endif

typedef struct npc_roomadminnew_tag {
	int		expire;
	char	cdkey[CDKEYLEN];
	char	charaname[32];
	char	passwd[9];
}NPC_ROOMINFO;

typedef struct npc_roomadminnew_ranking_tag {
	int		gold;				/*   诳嗯�? */
	int		biddate;			/*   诳凛�? */
	char	cdkey[CDKEYLEN];	/*   午仄凶谛�?    平□ */
	char	charaname[32];		/*   午仄凶谛�?  �? */
	char	owntitle[32];		/* 惫寞*/

}NPC_RANKING_INFO;

#endif /*__NPC_ROOMADMINNEW_H__*/

int NPC_RoomAdminNew_ReadFile( char *roomname, NPC_ROOMINFO *data);
