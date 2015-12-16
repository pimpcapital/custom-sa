#ifndef  __PET_H__
#define __PET_H__

/*
 * 矢永玄楮  及涩烂匹允［
 */
#include "version.h"
#include "common.h"

#define PETFEEDTIME	60*60	// 宠物蛋喂养时间(秒)
//#define PETFEEDTIME	5	// 宠物蛋喂养时间(秒)

int PET_DEBUG_initPetOne( int charaindex);
int PET_dropPet( int charaindex, int havepetindex);
int PET_dropPetFollow( int charaindex, int havepetindex, int fl, int x, int y);
int PET_dropPetFLXY( int charaindex, int havepetindex, int fl, int x, int y);
int PET_dropPetAbsolute( int petindex, int floor, int x, int y,int net);
int PET_createPetFromCharaIndex( int charaindex, int enemyindex);
int PET_SelectBattleEntryPet( int charaindex, int petarray);
int PET_initCharOneArray( Char *ch);
int PET_isPutPoint( int fl,int x, int y);


int PET_getBaseForAllocpoint( int toindex, int *work);
void PET_showEditBaseMsg( int charaindex, int toindex, int itemindex, int *work);

int CHAR_DelPetForIndex( int charaindex, int petindex);

#endif
