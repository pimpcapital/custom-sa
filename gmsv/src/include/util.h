#ifndef __UTIL_H__
#define __UTIL_H__

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"


typedef struct tagSTRING32 {
  char string[32];
} STRING32;

typedef struct tagSTRING64 {
  char string[64];
} STRING64;

typedef struct tagSTRING128 {
  char string[128];
} STRING128;

typedef struct tagRECT {
  int x;
  int y;
  int width;
  int height;
} RECT;
typedef struct tagPOINT {
  int x;
  int y;
} POINT;

typedef enum {
  CHAR, SHORT, INT, DOUBLE
} CTYPE;

void chop(char *src);

void dchop(char *src, char *del);

#define chomp(src)  dchop(src,"\n");

void chompex(char *buf);

void pohcd(char *src, char *del);

void strcpysafe(char *dest, size_t n, const char *src);

void strncpysafe(char *dest, const size_t n, const char *src, const int length);

char *strcatsafe(char *src, int size, char *ap);

int strtolchecknum(char *arg, void *number, int base, CTYPE type);

int strcmptail(char *s1, char *s2);

int textToInt(char *str);

void deleteCharFromString(char *src, char *dels);

void deleteCharFromStringNoEscape(char *src, char *dels);

#define deleteWhiteSpace(src) deleteCharFromStringNoEscape( src," \t" )

char *replaceString(char *src, char oldc, char newc);

int getStringFromIndexWithDelim(char *src, char *delim, int index, char *buf, size_t buflen);

void getFourIntsFromString(char *src, int *int1, int *int2, int *int3, int *int4);

void deleteSequentChar(char *src, char *dels);

int hashpjw(char *s);

int bindlocalhost(int port);

int connectHost(char *hostname, unsigned short port);

int hashpjw(char *s);

int charInclude(char *src, char *include);

int rgetFileName(char *dirname, STRING64 *string, int size);

#define RAND(x, y)   ((x-1)+1+ \
                     (int)( (double)(y-(x-1))*rand()/(RAND_MAX+1.0)) )

int checkStringsUnique(char **strings, int num, int verbose);

char *makeEscapeString(char *src, char *dest, int sizeofdest);

char *makeStringFromEscaped(char *src);

double time_diff(struct timeval subtrahend, struct timeval subtractor);

int PointInRect(RECT *rect, POINT *p);

int CoordinateInRect(RECT *rect, int x, int y);

int clipRect(RECT *rect1, RECT *rect2, RECT *ret);

int isstring1or0(char *string);

void easyGetTokenFromString(char *src, int count, char *output, int len);

int isExistFile(char *filename);

char *cnv10to62(int a, char *out, int outlen);

int checkRedundancy(int *src, int srclen);

unsigned short CheckCRC(unsigned char *p, int size);

double time_diff(struct timeval subtrahend, struct timeval subtractor);


#define ABS(x)      ((x)>=0 ? (x) : -(x))

#define VALIDATEDIR(x)  ({(x)%=8;(x)=((x)+8)%8;})

#define SETLOWVALUE(x, y)  ((x)=((x)&0xffff0000)|( (y)     &0x0000ffff))
#define SETHIGHVALUE(x, y) ((x)=((x)&0x0000ffff)|(((y)<<16)&0xffff0000))
#define MAKE2VALUE(x, y)  ((((x)<<16)&0xffff0000)|((y)&0x0000ffff))

#endif
