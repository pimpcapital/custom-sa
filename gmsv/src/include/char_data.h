#ifndef __CHAR_DATA_H__
#define __CHAR_DATA_H__

#include "item.h"
#include "char.h"


#define CHAR_CLASS01_PASSLV     20

#define BATEBAN	2
#define FIRSTPOSITIONMAXINDEX   1
#define ELDERINDEXSTART     FIRSTPOSITIONMAXINDEX+BATEBAN+1

typedef struct tagLevelUpPattern
{
#if 1
    struct  Exptbl{
        int origin;
        int multi;
    }exptbl[3];
    int     hpupminpoint;   /*  hp 及丐互月   斓袄*/
    int     hpupmaxpoint;   /*  hp 及丐互月   斓袄*/

    int     needexp;        /*    邰卅烦董袄    */
#else
    int     uppoint[5];
#endif
}LevelUpPattern;

/*====================赓渝袄｝伊皮伙失永皿楮溢====================*/
int CHAR_getDefaultChar( Char*  nc, int imagenumber );

/*====================隶    ｝  飓  寞赘尹楮溢====================*/
int CHAR_getNewImagenumberFromEquip( int basebaseimagenumber,
                                     ITEM_CATEGORY category );
/*====================  飓  寞  侬   ->   寞楮溢====================*/
//void CHAR_initSeekGraphicNumberFromString();
int CHAR_seekGraphicNumberFromString( char* string );



/*====================平乓仿及赓渝袄楮溢====================*/
int CHAR_getInitElderPosition( Char* ch,int hometown);
int CHAR_getElderPosition( int elderindex, int* fl, int* x, int* y );

void CHAR_setInitValues( Char* ch );


/*====================  衬匏  楮溢====================*/
typedef enum
{
    CHAR_INVAREA,
    CHAR_CANNOTDROPAREA,
    CHAR_CANNOTMAGICAREA,
	CHAR_AREAKIND_NONE,
}CHAR_AREAKIND;

int CHAR_initInvinciblePlace( char* filename );
int CHAR_isCannotMagicArea( int floor , int x, int y, int magicnum );
int CHAR_initAppearPosition( char* filename );
int CHAR_isInvincibleArea( int floor , int x, int y );
int CHAR_isAppearPosition( int floor, int *x, int *y);
int CHAR_isCannotDropArea( int floor , int x, int y );


/* 赢  楮溢 */
int CHAR_ElderSetPosition( int elderindex ,int fl,int x ,int y);



/*************************************************
酵烂伊矛伙失永皿质  
*************************************************/


int GetEnemyExp( int level );

int CHAR_GetLevelExp( int charaindex, int level );

int CHAR_LevelUpCheck( int charaindex , int toindex);

int CHAR_PetLevelUp( int petindex );

int CHAR_checkFaceImageNumber( int imagenumber, int faceimagenumber);
int CHAR_checkPlayerImageNumber( int imagenumber);

int CHAR_PetTakeLevelUp( int petindex, int lv);	//强制宠物升级
int CHAR_PetTakeDrop( int petindex, int floor, int ox, int oy);	//强制丢弃宠物升级

int PETTRANS_PetTransManStatus( int toindex, int petindex1, int petindex2);
#ifdef _PET_2TRANS
int NPC_PetTransManGetAns( int total1, int total2, int LV, int rank, int tran);
#else
int NPC_PetTransManGetAns( int total1, int total2, int LV, int rank);
#endif //_PET_2TRANS

#ifdef _CHIKULA_STONE
void CHAR_AutoChikulaStone( int charaindex, int Dflg);
#endif

int CHAR_findSurplusPetBox( int charaindex );

#ifdef _USER_EXP_CF
void setNeedLevelUpTbls(int level,int exp);
void setMaxLevel(int level);
#endif 
#ifdef _FM_METAMO
void CHAR_ReMetamo( int charaindex );
#endif 
#ifdef _NEW_PLAYER_RIDE
void CHAR_PlayerRide( int charaindex );
#endif 
#ifdef _USER_EXP_CF
int LoadEXP( char* filename );
#endif 
#endif 
