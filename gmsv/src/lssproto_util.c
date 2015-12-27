#define _LSSPROTOUTIL_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lssproto_util.h"
//ttom +2 for degug
#define IS_2BYTEWORD(_a_) ( (char)(0x80) <= (_a_) && (_a_) <= (char)(0xFF) )

#include "common.h"

/*
  lsrpc routines
*/
int lssproto_AllocateCommonWork(int bufsiz) {
  lssproto.workbufsize = bufsiz;
  lssproto.work = NULL;
  lssproto.arraywork = NULL;
  lssproto.escapework = NULL;
  lssproto.val_str = NULL;
  lssproto.token_list = NULL;
  lssproto.cryptwork = NULL;
  lssproto.jencodecopy = NULL;
  lssproto.jencodeout = NULL;
  lssproto.compresswork = NULL;
  lssproto.work = (char *) calloc(1, lssproto.workbufsize);
  lssproto.arraywork = (char *) calloc(1, lssproto.workbufsize);
  lssproto.escapework = (char *) calloc(1, lssproto.workbufsize);
  lssproto.val_str = (char *) calloc(1, lssproto.workbufsize);
  lssproto.token_list = (char **) calloc(1, lssproto.workbufsize * sizeof(char **));
  lssproto.cryptwork = (char *) calloc(1, lssproto.workbufsize * 3);
  lssproto.jencodecopy = (char *) calloc(1, lssproto.workbufsize * 3);
  lssproto.jencodeout = (char *) calloc(1, lssproto.workbufsize * 3);
  lssproto.compresswork = (char *) calloc(1, lssproto.workbufsize * 3);
  memset(lssproto.work, 0, lssproto.workbufsize);
  memset(lssproto.arraywork, 0, lssproto.workbufsize);
  memset(lssproto.escapework, 0, lssproto.workbufsize);
  memset(lssproto.val_str, 0, lssproto.workbufsize);
  memset((char *) lssproto.token_list, 0, lssproto.workbufsize * sizeof(char **));
  memset(lssproto.cryptwork, 0, lssproto.workbufsize * 3);
  memset(lssproto.jencodecopy, 0, lssproto.workbufsize * 3);
  memset(lssproto.jencodeout, 0, lssproto.workbufsize * 3);
  memset(lssproto.compresswork, 0, lssproto.workbufsize * 3);
  if(lssproto.work == NULL ||
     lssproto.arraywork == NULL ||
     lssproto.escapework == NULL ||
     lssproto.val_str == NULL ||
     lssproto.token_list == NULL ||
     lssproto.cryptwork == NULL ||
     lssproto.jencodecopy == NULL ||
     lssproto.jencodeout == NULL ||
     lssproto.compresswork == NULL) {
    free(lssproto.work);
    free(lssproto.val_str);
    free(lssproto.escapework);
    free(lssproto.arraywork);
    free(lssproto.token_list);
    free(lssproto.cryptwork);
    free(lssproto.jencodecopy);
    free(lssproto.jencodeout);
    free(lssproto.compresswork);
    return -1;
  }
  return 0;
}

void lssproto_strcpysafe(char *dest, char *src, int maxlen) {
  int i;
  for(i = 0; i < maxlen - 1; i++) {
    dest[i] = src[i];
    if(src[i] == 0)break;
  }
  dest[i] = 0;
}

int lssproto_default_write_wrap(int fd, char *buf, int size) {
  return write(fd, buf, size);
}

void lssproto_Send(int fd, char *msg) {
  if(lssproto_writelogfilename[0] != '\0') {
    FILE *wfp = fopen(lssproto_writelogfilename, "a+");
    if(wfp)fprintf(wfp, "%s\n", msg);
    if(wfp)fclose(wfp);

  }
  /* add a newline character*/
  unsigned int l = strlen(msg);
  if(l < lssproto.workbufsize * 3) {
    msg[l] = '\n';
    msg[l + 1] = 0;
    l++;
  }
  else {
    print("\n lssproto.workbufsize:%d len:%d ", lssproto.workbufsize, l);
  }
  lssproto.write_func(fd, msg, l);
}