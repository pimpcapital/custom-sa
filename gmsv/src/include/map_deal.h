#ifndef __MAP_DEAL_H__
#define __MAP_DEAL_H__

int MAP_walkAbleFromPoint(int ff, int fx, int fy, int isfly);

int MAP_walkAble(int index, int ff, int fx, int fy);

int MAP_sendArroundCharNeedFD(int fd, int charaindex);

int MAP_sendArroundChar(int charaindex);

#endif 

