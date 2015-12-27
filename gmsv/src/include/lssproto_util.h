#ifndef _LSSPROTOUTIL_H_
#define _LSSPROTOUTIL_H_

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

struct lssproto_ {
  int (*write_func)(int, char *, int);

  /* write function */
  size_t workbufsize;
  /* size of work area */
  char *work, *arraywork, *escapework, *val_str, *ret_work;
  /* work areas which have same size  */
  char *cryptwork, *jencodecopy, *jencodeout, *compresswork;
  /* these work has bigger size (3times)*/
  char **token_list;
  /* token list */
  unsigned long message_id; /*= 1,  */       /* for generating message IDs */
};

#ifdef _LSSPROTOUTIL_C_
struct lssproto_ lssproto = {
    NULL,
    0,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,
    NULL,
    1,
};
char **lssproto_stringwrapper;
char lssproto_readlogfilename[1024];
char lssproto_writelogfilename[1024];
#else
extern char **lssproto_stringwrapper;
extern struct lssproto_ lssproto;
extern char lssproto_readlogfilename[1024];
extern char lssproto_writelogfilename[1024];
#endif

void lssproto_strcpysafe(char *dest, char *src, int len);

void lssproto_Send(int fd, char *msg);

int lssproto_AllocateCommonWork(int bufsiz);

int lssproto_default_write_wrap(int fd, char *buf, int size);

#endif


