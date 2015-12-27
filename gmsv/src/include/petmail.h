#ifndef  __PETMAIL_H__
#define __PETMAIL_H__

#include "version.h"

#define PETMAIL_OFFMSG_TIMEOUT      ( 3 * 24 * 3600 )
#define PETMAIL_CHECK_OFFMSG_EXPIRE_INTERVAL  3600
#define PETMAIL_OFFMSG_TEXTLEN 512

#define     PETMAIL_EFFECTMAX  1

#define    PETMAIL_SPOOLFLOOR    777
#define    PETMAIL_SPOOLX      30
#define    PETMAIL_SPOOLY      30

#define    PETMAIL_LOOPINTERVAL1  500
#define    PETMAIL_LOOPINTERVAL2  5000

typedef struct {
  int use;
  time_t send_tm;
  int color;
  char text[PETMAIL_OFFMSG_TEXTLEN];
  char destcd[CDKEYLEN];
  char destcharname[CHARNAMELEN];
  char srccd[CDKEYLEN];
  char srccharname[CHARNAMELEN];

} PETMAIL_offmsg;

void PETMAIL_Loopfunc(int index);

int PETMAIL_CheckPlayerExist(int index, int mode);

int PETMAIL_initOffmsgBuffer(int count);

int PETMAIL_addOffmsg(int fromindex, char *tocdkey, char *tocharaname,
                      char *text, int color);

PETMAIL_offmsg *PETMAIL_getOffmsg(int offmsgindex);

int PETMAIL_deleteOffmsg(int offmsgindex);

void PETMAIL_proc(void);

int storePetmail(void);

int PETMAIL_sendPetMail(int cindex, int aindex,
                        int havepetindex, int haveitemindex, char *text, int color);

#ifdef _PETMAIL_DEFNUMS

void CHAR_AutoPickupMailPet(int charaindex, int petindex);

#endif

int PETMAIL_getPetMailTotalnums(void);

void PETMAIL_delPetMailTotalnums(int numflg);

void PETMAIL_setPetMailTotalnums(int numflg);

int PETMAIL_CheckIsMyOffmsg(int fromindex, char *tocdkey, char *tocharaname);

#endif
