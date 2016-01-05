#define _SAACPROTOUTIL_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "saacproto_util.h"
//ttom +1
#define IS_2BYTEWORD(_a_) ( (char)(0x80) <= (_a_) && (_a_) <= (char)(0xFF) )

/*
  lsrpc routines
*/
int saacproto_AllocateCommonWork(int bufsiz) {
  saacproto.workbufsize = bufsiz;
  saacproto.work = NULL;
  saacproto.arraywork = NULL;
  saacproto.escapework = NULL;
  saacproto.val_str = NULL;
  saacproto.token_list = NULL;
  saacproto.cryptwork = NULL;
  saacproto.jencodecopy = NULL;
  saacproto.jencodeout = NULL;
  saacproto.compresswork = NULL;
  saacproto.work = (char *) calloc(1, saacproto.workbufsize);
  saacproto.arraywork = (char *) calloc(1, saacproto.workbufsize);
  saacproto.escapework = (char *) calloc(1, saacproto.workbufsize);
  saacproto.val_str = (char *) calloc(1, saacproto.workbufsize);
  saacproto.token_list = (char **) calloc(1, saacproto.workbufsize * sizeof(char **));
  saacproto.cryptwork = (char *) calloc(1, saacproto.workbufsize * 3);
  saacproto.jencodecopy = (char *) calloc(1, saacproto.workbufsize * 3);
  saacproto.jencodeout = (char *) calloc(1, saacproto.workbufsize * 3);
  saacproto.compresswork = (char *) calloc(1, saacproto.workbufsize * 3);
  memset(saacproto.work, 0, saacproto.workbufsize);
  memset(saacproto.arraywork, 0, saacproto.workbufsize);
  memset(saacproto.escapework, 0, saacproto.workbufsize);
  memset(saacproto.val_str, 0, saacproto.workbufsize);
  memset((char *) saacproto.token_list, 0, saacproto.workbufsize * sizeof(char **));
  memset(saacproto.cryptwork, 0, saacproto.workbufsize * 3);
  memset(saacproto.jencodecopy, 0, saacproto.workbufsize * 3);
  memset(saacproto.jencodeout, 0, saacproto.workbufsize * 3);
  memset(saacproto.compresswork, 0, saacproto.workbufsize * 3);
  if(saacproto.work == NULL ||
     saacproto.arraywork == NULL ||
     saacproto.escapework == NULL ||
     saacproto.val_str == NULL ||
     saacproto.token_list == NULL ||
     saacproto.cryptwork == NULL ||
     saacproto.jencodecopy == NULL ||
     saacproto.jencodeout == NULL ||
     saacproto.compresswork == NULL) {
    free(saacproto.work);
    free(saacproto.val_str);
    free(saacproto.escapework);
    free(saacproto.arraywork);
    free(saacproto.token_list);
    free(saacproto.cryptwork);
    free(saacproto.jencodecopy);
    free(saacproto.jencodeout);
    free(saacproto.compresswork);
    return -1;
  }
  return 0;
}

int saacproto_StringRest() {
  return 0;
/*	free( saacproto.work);
	saacproto.work = NULL;
	saacproto.work = (char*)calloc( 1, saacproto.workbufsize );
	if( saacproto.work == NULL ) return -1;
	return sizeof( saacproto.work);
*/
}

/**********
  Get message information from a network input
**********/
void saacproto_GetMessageInfo(int *id, char *funcname, int len, char **tk) {
  if(tk[0] == NULL || tk[1] == NULL) {
    *id = 0;
    saacproto_strcpysafe(funcname, "", len);
    return;
  }
  *id = strtoul(tk[0], NULL, 10);
  saacproto_strcpysafe(funcname, tk[1], len);
  return;
}

/********************************************
  string utilities
*********************************************/
void saacproto_strcpysafe(char *dest, char *src, int maxlen) {
  int i;
  for(i = 0; i < maxlen - 1; i++) {
    dest[i] = src[i];
    if(src[i] == 0)break;
  }
  dest[i] = 0;
}

void saacproto_strcatsafe(char *dest, char *src, int maxlen) {
  int i, j;


  for(i = 0; i < maxlen - 1; i++) {
    if(dest[i] == 0) {
      for(j = i; j < maxlen - 1; j++) {
        dest[j] = src[j - i];
        if(src[j - i] == 0)break;
      }
      dest[j] = 0;
      break;
    }
  }
}

char *saacproto_mkstr_int(int i) {
#define MKSTR_INT(v) saacproto_Ltoa( (long)(v))
  saacproto_strcpysafe(saacproto.val_str, (char *) MKSTR_INT(i), saacproto.workbufsize);
  saacproto_strcatsafe(saacproto.val_str, " ", saacproto.workbufsize);
  return saacproto.val_str;
}

char *saacproto_mkstr_u_int(unsigned int i) {
#define MKSTR_U_INT(v) saacproto_Ultoa( (unsigned long ) (v) )
  saacproto_strcpysafe(saacproto.val_str, MKSTR_U_INT(i), saacproto.workbufsize);
  saacproto_strcatsafe(saacproto.val_str, " ", saacproto.workbufsize);
  return saacproto.val_str;
}

char *saacproto_mkstr_long(long l) {
#define MKSTR_LONG(v) saacproto_Ltoa( v )
  saacproto_strcpysafe(saacproto.val_str, MKSTR_LONG(l), saacproto.workbufsize);
  saacproto_strcatsafe(saacproto.val_str, " ", saacproto.workbufsize);
  return saacproto.val_str;
}

char *saacproto_mkstr_u_long(unsigned long l) {
#define MKSTR_U_LONG(v) saacproto_Ultoa(v )
  saacproto_strcpysafe(saacproto.val_str, MKSTR_U_LONG(l), saacproto.workbufsize);
  saacproto_strcatsafe(saacproto.val_str, " ", saacproto.workbufsize);
  return saacproto.val_str;
}

char *saacproto_mkstr_short(short s) {
#define MKSTR_SHORT16(v)    saacproto_Ltoa( (long)((int)(v) ))
  saacproto_strcpysafe(saacproto.val_str, MKSTR_SHORT16(s), saacproto.workbufsize);
  saacproto_strcatsafe(saacproto.val_str, " ", saacproto.workbufsize);
  return saacproto.val_str;
}

char *saacproto_mkstr_u_short(short s) {
#define MKSTR_U_SHORT16(v)   saacproto_Ltoa( (long)(  ((long)(v)) & 0xffff ))
  saacproto_strcpysafe(saacproto.val_str, MKSTR_U_SHORT16(s), saacproto.workbufsize);
  saacproto_strcatsafe(saacproto.val_str, " ", saacproto.workbufsize);
  return saacproto.val_str;
}

char *saacproto_mkstr_char(char c) {
#define MKSTR_CHAR8(v)   saacproto_Ltoa( ( long)((int)(v)))
  saacproto_strcpysafe(saacproto.val_str, MKSTR_CHAR8(c), saacproto.workbufsize);
  saacproto_strcatsafe(saacproto.val_str, " ", saacproto.workbufsize);
  return saacproto.val_str;
}

char *saacproto_mkstr_u_char(char c) {
#define MKSTR_U_CHAR8(v)   saacproto_Ltoa( (long)( ((long)(v)) & 0xff ))
  saacproto_strcpysafe(saacproto.val_str, MKSTR_U_CHAR8(c), saacproto.workbufsize);
  saacproto_strcatsafe(saacproto.val_str, " ", saacproto.workbufsize);
  return saacproto.val_str;
}

char *saacproto_mkstr_string(char *a) {
  char *ret = saacproto_escapeString(a);
  saacproto_strcatsafe(ret, " ", saacproto.workbufsize);
  return ret;
}

char *saacproto_mkstr_float(float f) {
  sprintf(saacproto.val_str, "%f ", f);
  return saacproto.val_str;
}

char *saacproto_mkstr_double(double d) {
  sprintf(saacproto.val_str, "%f ", d);
  return saacproto.val_str;
}

char *saacproto_mkstr_int_array(int size, int *array) {
#define MKSTR_ARRAYMACRO(func) \
  {\
     int i;\
         saacproto.arraywork[0] = '\0';\
     for(i=0;i<size;i++){   \
             saacproto_strcatsafe( saacproto.arraywork , func(array[i]) , saacproto.workbufsize );\
     }\
         return saacproto.arraywork;\
    }\

  MKSTR_ARRAYMACRO(saacproto_mkstr_int);
}

char *saacproto_mkstr_u_int_array(int size, int *array) {
  MKSTR_ARRAYMACRO(saacproto_mkstr_u_int);
}

char *saacproto_mkstr_short_array(int size, short *array) {
  MKSTR_ARRAYMACRO(saacproto_mkstr_short);
}

char *saacproto_mkstr_u_short_array(int size, short *array) {
  MKSTR_ARRAYMACRO(saacproto_mkstr_u_short);
}

char *saacproto_mkstr_char_array(int size, char *array) {
  MKSTR_ARRAYMACRO(saacproto_mkstr_char);
}

char *saacproto_mkstr_u_char_array(int size, unsigned char *array) {
  MKSTR_ARRAYMACRO(saacproto_mkstr_u_char);
}

char *saacproto_mkstr_float_array(int size, float *array) {
  MKSTR_ARRAYMACRO(saacproto_mkstr_float);
}

char *saacproto_mkstr_double_array(int size, double *array) {
  MKSTR_ARRAYMACRO(saacproto_mkstr_double);
}

/*********************
   translate string into base types
*********************/
int saacproto_demkstr_int(char *a) {
  if(a == (char *) NULL)return 0;
/*	return (int)strtol( a ,NULL , 10);*/
  return saacproto_a62toi(a);
}

unsigned int saacproto_demkstr_u_int(char *a) {
  if(a == (char *) NULL)return 0;
  return (unsigned int) strtoul(a, NULL, 10);
}

long saacproto_demkstr_long(char *a) {
  if(a == (char *) NULL)return 0;
  return (long) strtol(a, NULL, 10);
}

unsigned long saacproto_demkstr_u_long(char *a) {
  if(a == (char *) NULL)return 0;
  return (unsigned long) strtoul(a, NULL, 10);
}

short saacproto_demkstr_short(char *a) {
  if(a == (char *) NULL)return 0;
  return (short) strtol(a, NULL, 10);
}

unsigned short saacproto_demkstr_u_short(char *a) {
  if(a == (char *) NULL)return 0;
  return (unsigned short) strtoul(a, NULL, 10);
}

char saacproto_demkstr_char(char *a) {
  if(a == (char *) NULL)return 0;
  return (char) strtol(a, NULL, 10);
}

unsigned char saacproto_demkstr_u_char(char *a) {
  if(a == (char *) NULL)return 0;
  return (unsigned char) strtoul(a, NULL, 10);
}

float saacproto_demkstr_float(char *a) {
  if(a == (char *) NULL)return 0.0F;
  return (float) atof(a);
}

double saacproto_demkstr_double(char *a) {
  if(a == (char *) NULL)return 0.0F;
  return (double) strtod(a, NULL);
}

char *saacproto_demkstr_string(char *a) {
  if(a == (char *) NULL) {
    saacproto_strcpysafe(saacproto.escapework, "", saacproto.workbufsize);
    return saacproto.escapework;
  }
  return saacproto_descapeString(a);
}

int *saacproto_demkstr_int_array(char **tk, int *buf, int start, int size) {
#define DEMKSTR_ARRAYMACRO(func, defaultvalue)          \
    {\
        int i;\
        for(i=start;i<(start+size);i++){\
            if( tk[i] == NULL ){   \
            buf[i-start]=defaultvalue ;\
            } else {\
            buf[i-start] = func( tk[i] );\
            }\
      }\
        return buf;\
    }
  DEMKSTR_ARRAYMACRO(saacproto_demkstr_int, 0);
}

int *saacproto_demkstr_u_int_array(char **tk, int *buf, int start, int size) {
  DEMKSTR_ARRAYMACRO(saacproto_demkstr_u_int, 0);
}

unsigned int *saacproto_demkstr_long_array(
    char **tk, unsigned int *buf, int start, int size) {
  DEMKSTR_ARRAYMACRO(saacproto_demkstr_long, 0);
}

unsigned long *saacproto_demkstr_u_long_array(
    char **tk, unsigned long *buf, int start, int size) {
  DEMKSTR_ARRAYMACRO(saacproto_demkstr_u_long, 0);
}

short *saacproto_demkstr_short_array(char **tk, short *buf, int start, int size) {
  DEMKSTR_ARRAYMACRO(saacproto_demkstr_short, 0);
}

unsigned short *saacproto_demkstr_u_short_array(
    char **tk, unsigned short *buf, int start, int size) {
  DEMKSTR_ARRAYMACRO(saacproto_demkstr_u_short, 0);
}

char *saacproto_demkstr_char_array(char **tk, char *buf, int start, int size) {
  DEMKSTR_ARRAYMACRO(saacproto_demkstr_u_char, 0);
}

unsigned char *saacproto_demkstr_u_char_array(
    char **tk, unsigned char *buf, int start, int size) {
  DEMKSTR_ARRAYMACRO(saacproto_demkstr_u_char, 0);
}

float *saacproto_demkstr_float_array(char **tk, float *buf, int start, int size) {
  DEMKSTR_ARRAYMACRO(saacproto_demkstr_float, (float) 0.0);
}

double *saacproto_demkstr_u_double_array(char **tk, double *buf, int start, int size) {
  DEMKSTR_ARRAYMACRO(saacproto_demkstr_double, (double) 0.0);
}

char *saacproto_escapeString(char *a) {
  int i, c = 0;
  saacproto.escapework[0] = '\0';
  for(i = 0; ; i++) {
    if(a[i] == '\0') {
      saacproto.escapework[c++] = '\0';
      break;
    } else if((char) 0x80 <= a[i] && a[i] <= (char) 0xFF) {
      // for 2 Byte Word
      saacproto.escapework[c++] = a[i++];
      saacproto.escapework[c++] = a[i];
    } else if(a[i] == '\\') {
      saacproto.escapework[c++] = '\\';
      saacproto.escapework[c++] = '\\';
    } else if(a[i] == ' ') {
      saacproto.escapework[c++] = '\\';
      saacproto.escapework[c++] = 'S';
    } else if(a[i] == '\n') {
      saacproto.escapework[c++] = '\\';
      saacproto.escapework[c++] = 'n';
    } else if(a[i] == '\r') {
      saacproto.escapework[c++] = '\\';
      saacproto.escapework[c++] = 'r';
    } else {
      saacproto.escapework[c++] = a[i];
    }
  }
  return saacproto.escapework;
}

char *saacproto_descapeString(char *a) {
  int i, c = 0;
  saacproto.escapework[0] = '\0';
  for(i = 0; ; i++) {
    if(a[i] == '\0') {
      saacproto.escapework[c++] = '\0';
      break;
    } else if((char) 0x80 <= a[i] && a[i] <= (char) 0xFF) {
      // for 2 Byte Word
      saacproto.escapework[c++] = a[i++];
      saacproto.escapework[c++] = a[i];
    } else if(a[i] == '\\') {
      if(a[i + 1] == 0) {     /* null */
        saacproto.escapework[c++] = a[i];
        continue;
      }
      if(a[i + 1] == 'S') {     /* space */
        saacproto.escapework[c++] = ' ';
      } else if(a[i + 1] == 'n') {
        saacproto.escapework[c++] = '\n';
      } else if(a[i + 1] == 'r') {
        saacproto.escapework[c++] = '\r';
      } else if(a[i + 1] == '\\') {
        saacproto.escapework[c++] = '\\';
      } else {
        saacproto.escapework[c++] = a[i];
      }
      i++;
    } else {
      saacproto.escapework[c++] = a[i];
    }
  }
  return saacproto.escapework;
}

void saacproto_splitString(char *src) {
  int i, c = 0;


  if(saacproto_readlogfilename[0] != '\0') {
    FILE *rfp;
    rfp = fopen(saacproto_readlogfilename, "a+");
    if(rfp)fprintf(rfp, "%s\n", src);
    if(rfp)fclose(rfp);
  }
  for(i = 0; ; i++) {
    if(src[i] == '\0') break;
    if(i == 0) {
      saacproto.token_list[c++] = &(src[i]);
    }
    if(src[i] == ' ') {
      saacproto.token_list[c++] = &(src[i + 1]);
    }
  }
  while(*src) {
    if((*src) == ' ' || (*src) == '\n' || (*src) == '\r') *src = '\0';
    src++;
  }
  saacproto.token_list[c] = (char *) NULL;
}

int saacproto_default_write_wrap(int fd, char *buf, int size) {
  return write(fd, buf, size);
}

void saacproto_consumeLine(char *buf, int offset) {
  int i;
  int shift = 0;
  buf += offset;
  for(i = 0; ; i++) {
    if(buf[i] == '\n') {
      shift = i + 1;
      break;
    }
  }
  if(shift == 0)return;
  for(i = shift; ; i++) {
    buf[i - shift] = buf[i];
    if(buf[i] == '\0')break;
  }
}

void saacproto_copyLine(char *src, char *out, int outlen) {
  int i;
  for(i = 0; ; i++) {
    out[i] = src[i];
    if(src[i] == '\n') {
      out[i + 1] = '\0';
      return;
    }
    if(src[i] == '\0')return;
  }
  saacproto_strcpysafe(out, "", outlen);
}

// WON ADD
unsigned long saacproto_GetNewMessageID(void) {
  return saacproto.message_id++;
}

void saacproto_Send(int fd, char *msg) {
  if(saacproto_writelogfilename[0] != '\0') {
    FILE *wfp = fopen(saacproto_writelogfilename, "a+");
    if(wfp)fprintf(wfp, "%s\n", msg);
    if(wfp)fclose(wfp);
  }
  /* add a newline character*/
  unsigned int l = strlen(msg);
  if(l < saacproto.workbufsize * 3) {
    msg[l] = '\n';
    msg[l + 1] = 0;
    l++;
  }
  saacproto.write_func(fd, msg, l);
}

/****************
  create a header which has function name and new Message ID
****************/
void saacproto_CreateHeader(char *out, char *fname) {
  sprintf(out, "%lu %s ", saacproto_GetNewMessageID(), fname);
}

void saacproto_CreateHeaderID(char *out, unsigned long msgid, char *fname) {
  sprintf(out, "%u %s ", (unsigned int) msgid, fname);
}

char *saacproto_Ltoa(long v) {
  static char _ltoa_out[64];
  saacproto_cnv10to62((int) v, _ltoa_out, sizeof(_ltoa_out));
/*	sprintf( _ltoa_out , "%d" , (int)v );*/
  return _ltoa_out;
}

char *saacproto_Ultoa(unsigned long v) {
  static char _ultoa_out[64];
  sprintf(_ultoa_out, "%u", (unsigned int) v);
  return _ultoa_out;
}

/****************
   string address wrapper
****************/
char *saacproto_wrapStringAddr(char *copy, int maxcopylen, char *src) {
  saacproto_strcpysafe(copy, src, maxcopylen);
  return copy;
}

void saacproto_bzero(char *b, int siz) {
  unsigned int i;
  int *p;
  p = (int *) b;
  for(i = 0; i < siz / sizeof(int); i++) {
    *(p + i) = 0;
  }
  for(i = 0; i < siz % sizeof(int); i++) {
    *(b + siz - 1 - i) = 0;
  }
}

/***************
    copy buffer
***************/
void saacproto_bcopy(char *s, char *d, int siz) {
  unsigned int i;
  int *ps, *pd;
  ps = (int *) s;
  pd = (int *) d;
  for(i = 0; i < siz / sizeof(int); i++) {
    *(pd + i) = *(ps + i);
  }
  for(i = 0; i < siz % sizeof(int); i++) {
    *(d + siz - 1 - i) = *(s + siz - 1 - i);
  }
}

/* Convert 62-base digits to 10 digits */
int saacproto_a62toi(char *a) {
  int ret = 0;
  int minus;
  if(a[0] == '-') {
    minus = -1;
    a++;
  } else {
    minus = 1;
  }

  while(*a != '\0') {
    ret *= 62;
    if('0' <= (*a) && (*a) <= '9')
      ret += (*a) - '0';
    else if('a' <= (*a) && (*a) <= 'z')
      ret += (*a) - 'a' + 10;
    else if('A' <= (*a) && (*a) <= 'Z')
      ret += (*a) - 'A' + 36;
    else
      return 0;
    a++;
  }
  return ret * minus;
}

/*  Convert 10-base digits into 62-base digits. */
char *saacproto_cnv10to62(int a, char *out, int outlen) {
  int i, j;
  char base[] = {"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
  int tmp[64];
  int src;
  int minus;
  int baselen = sizeof(base) - 1;
  if(a < 0) {
    minus = 1;
    a *= -1;
  } else {
    minus = 0;
  }
  /* special case */
  if(a < baselen) {
    if(minus) {
      *(out) = '-';
      *(out + 1) = base[a];
      *(out + 2) = '\0';
      return (out);
    } else {
      *out = base[a];
      *(out + 1) = '\0';
      return (out);
    }
  }
  src = a;
  for(i = 0; src >= baselen; i++) {
    tmp[i] = src % baselen;
    src /= baselen;
  }
  i--;
  if(minus) {
    *out = '-';
    *(out + 1) = base[src];
    for(j = 2; i >= 0; i--, j++) {
      if(j > outlen - 2) return NULL;
      *(out + j) = base[tmp[i]];
    }
  } else {
    *out = base[src];
    for(j = 1; i >= 0; i--, j++) {
      if(j > outlen - 2) return NULL;
      *(out + j) = base[tmp[i]];
    }
  }
  *(out + j) = '\0';
  return (out);
}
