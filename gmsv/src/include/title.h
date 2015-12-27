#ifndef __TITLE_H__
#define __TITLE_H__

#include "common.h"
#include "util.h"

int TITLE_getTitleIndex(int index);

char *TITLE_makeTitleStatusString(int charaindex, int havetitleindex);

int TITLE_addtitle(int charaindex, int titleindex);

int TITLE_deltitle(int charaindex, int titleindex);

int TITLE_initTitleName(char *filename);

int TITLE_reinitTitleName(void);

int TITLE_initTitleConfig(char *filename);

int TITLE_TitleCheck_Nomsg(int charaindex, int mode, int *addcnt, int *delcnt);

#endif
