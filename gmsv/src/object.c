#include "version.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "handletime.h"

#include "object.h"
#include "buf.h"
#include "readmap.h"

static Object *obj;
static int objnum;

int initObjectArray(int num) {
  int i;
  objnum = num;
  obj = allocateMemory(sizeof(Object) * objnum);

  if(obj == NULL) return FALSE;
  for(i = 0; i < objnum; i++) {
    memset(&obj[i], 0, sizeof(Object));
    obj[i].type = OBJTYPE_NOUSE;
  }
  print("分配 %.2f MB MB 空间...", sizeof(Object) * objnum / 1024.0 / 1024.0);
  return TRUE;
}


int endObjectArray(void) {
  freeMemory(obj);
  return TRUE;
}

int _initObjectOne(char *file, int line, Object *ob) {
  static int allocobjnum = 0;
  int i;
  int first;

  i = allocobjnum;
  first = TRUE;
  while(1) {
    if(!first && i >= allocobjnum) {
      fprint("Can't allocate an object\n");
      return -1;
    }
    if(obj[i].type == OBJTYPE_NOUSE) {
      if(MAP_addNewObj(ob->floor, ob->x, ob->y, i) == 1) {
        memcpy(&obj[i], ob, sizeof(Object));
        allocobjnum = (i + 1 >= objnum) ? 0 : i + 1;
        return i;
      } else {
        allocobjnum = (i + 1 >= objnum) ? 0 : i + 1;
        fprint("MAP_addNewObj error\n");
        return -1;
      }
    } else {
      if(++i >= objnum) {
        i = 0;
        first = FALSE;
      }
    }
  }

  fprint("Can't allocate an object\n");
  return -1;
}

void endObjectOne(int index) {
  if(objnum <= index || index < 0)return;

  if(MAP_removeObj(obj[index].floor, obj[index].x, obj[index].y,
                   index) == FALSE) {
//        fprint( "REMOVE OBJ ERROR  floor:%d  x:%d  y:%d\n",obj[index].floor,obj[index].x, obj[index].y );
  }
  obj[index].type = OBJTYPE_NOUSE;
}

int CHECKOBJECT(int index) {
  if(0 <= index && index < objnum)return TRUE;
  return FALSE;
}

int CHECKOBJECTUSE(int index) {
  if(CHECKOBJECT(index) == FALSE)return FALSE;
  if(obj[index].type == OBJTYPE_NOUSE)return FALSE;
  return TRUE;
}

int OBJECT_getType(int index) {
  return obj[index].type;
}

int OBJECT_getchartype(int index) {
  return obj[index].chartype;
}

int OBJECT_setType(int index, int newvalue) {
  int old;
  old = obj[index].type;
  obj[index].type = newvalue;
  return old;
}

int OBJECT_getFloor(int index) {
  return obj[index].floor;
}

int OBJECT_setFloor(int index, int newvalue) {
  int old;
  old = obj[index].floor;
  obj[index].floor = newvalue;
  return old;
}

int OBJECT_getX(int index) {
  return obj[index].x;
}

int OBJECT_setX(int index, int newvalue) {
  int old;
  old = obj[index].x;
  obj[index].x = newvalue;
  return old;
}

int OBJECT_getY(int index) {
  return obj[index].y;
}

int OBJECT_setY(int index, int newvalue) {
  int old;
  old = obj[index].y;
  obj[index].y = newvalue;
  return old;
}

#ifdef _DEL_DROP_GOLD

int OBJECT_getTime(int index) {
  return obj[index].time;
}

int OBJECT_setTime(int index, int newvalue) {
  int old;
  old = obj[index].time;
  obj[index].time = newvalue;
  return old;
}

#endif

int OBJECT_getIndex(int index) {
  return obj[index].index;
}

int OBJECT_setIndex(int index, int newvalue) {
  int old;
  old = obj[index].index;
  obj[index].index = newvalue;
  return old;
}

int OBJECT_getNum(void) {
  return objnum;
}

int initObjectFromObjectMember(
    OBJTYPE type, int index, int x, int y, int floor) {
  Object obj;
  obj.type = type;
  obj.index = index;
  obj.x = x;
  obj.y = y;
  obj.floor = floor;

  return initObjectOne(&obj);
}