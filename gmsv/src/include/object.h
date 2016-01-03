#ifndef __OBJECT_h__
#define __OBJECT_h__

#include "common.h"

typedef enum {
  OBJTYPE_NOUSE,
      OBJTYPE_CHARA,
      OBJTYPE_ITEM,
      OBJTYPE_GOLD,
#ifdef _MAP_WARPPOINT
  OBJTYPE_WARPPOINT,
#endif
  OBJTYPE_NUM
} OBJTYPE;

typedef struct tagObject {
  OBJTYPE type;

  char objname[256];
  int npcsindex;
  int dir;
  int imagenum;

  int chartype;
  int index;
  int x;
  int y;
  int floor;
#ifdef _DEL_DROP_GOLD
  int time;
#endif
} Object;

int CHECKOBJECT(int index);

int CHECKOBJECTUSE(int index);

int initObjectArray(int num);

int endObjectArray(void);

int _initObjectOne(char *file, int line, Object *ob);

#define initObjectOne(ob) _initObjectOne( __FILE__, __LINE__, ob)

void endObjectOne(int index);

int initObjectFromObjectMember(OBJTYPE type, int index, int x, int y, int floor);

int OBJECT_getType(int index);

int OBJECT_setType(int index, int newvalue);

int OBJECT_getFloor(int index);

int OBJECT_setFloor(int index, int newvalue);

int OBJECT_getX(int index);

int OBJECT_setX(int index, int newvalue);

int OBJECT_getY(int index);

int OBJECT_setY(int index, int newvalue);

int OBJECT_getTime(int index);

int OBJECT_setTime(int index, int newvalue);

int OBJECT_getIndex(int index);

int OBJECT_setIndex(int index, int newvalue);

int OBJECT_getNum(void);

int OBJECT_getchartype(int index);

#endif