#include "common.h"
#include "readmap.h"
#include "char.h"
#include "lssproto_serv.h"


int MAP_walkAbleFromPoint(int ff, int fx, int fy, int isfly) {
  int map[2];

  if(!MAP_getTileAndObjData(ff, fx, fy, &map[0], &map[1])) {
    return FALSE;
  }

  if(isfly) {
    int i;
    for(i = 0; i < 2; i++)
      if(MAP_getImageInt(map[i], MAP_HAVEHEIGHT) == TRUE) {
        return FALSE;
      }
    return TRUE;
  } else {
    switch(MAP_getImageInt(map[1], MAP_WALKABLE)) {
      case 0:
        return FALSE;
      case 1:
        if(MAP_getImageInt(map[0], MAP_WALKABLE) == 1) {
          return TRUE;
        } else {
          return FALSE;
        }
      case 2:
        return TRUE;
      default:
        return FALSE;
        break;
    }
  }
  return FALSE;
}

int MAP_walkAble(int index, int ff, int fx, int fy) {
  if(CHAR_getFlg(index, CHAR_ISTRANSPARENT)) return TRUE;

  // Arminius 7.9 Airplane ok
  if(CHAR_getInt(index, CHAR_WHICHTYPE) == CHAR_TYPEBUS)
    return TRUE;

  if(CHAR_getWorkInt(index, CHAR_WORKPARTYMODE) == CHAR_PARTY_CLIENT) {
    int oyaindex = CHAR_getWorkInt(index, CHAR_WORKPARTYINDEX1);
    if(CHAR_CHECKINDEX(oyaindex)) {
      if(CHAR_getInt(oyaindex, CHAR_WHICHTYPE) == CHAR_TYPEBUS)
        return TRUE;
    }
  }

  return MAP_walkAbleFromPoint(ff, fx, fy, CHAR_getFlg(index, CHAR_ISFLYING) | CHAR_getWorkInt(index, CHAR_WORKSKYWALKER));
}

int MAP_sendArroundCharNeedFD(int fd, int charaindex) {
  int x = CHAR_getInt(charaindex, CHAR_X);
  int y = CHAR_getInt(charaindex, CHAR_Y);
  int fl = CHAR_getInt(charaindex, CHAR_FLOOR);
  int size = MAP_CHAR_DEFAULTSEESIZ;
  RECT seekr, retr;
  seekr.x = x - (size / 2);
  seekr.y = y - (size / 2);
  seekr.width = size;
  seekr.height = size;

  int tilesum, objsum, eventsum;
  char* stringdata = MAP_getChecksumFromRECT(fl, &seekr, &retr, &tilesum, &objsum, &eventsum);
  if(stringdata == NULL)
    return FALSE;
  lssproto_MC_send(fd, fl, retr.x, retr.y, retr.x + retr.width, retr.y + retr.height, tilesum, objsum, eventsum, stringdata);
  return TRUE;
}

int MAP_sendArroundChar(int charaindex) {
  int fd = getfdFromCharaIndex(charaindex);
  if(fd == -1)
    return FALSE;
  return MAP_sendArroundCharNeedFD(fd, charaindex);
}
