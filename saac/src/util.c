#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "main.h"
#include "util.h"

#define min(x, y) ({typeof(x) __x=(x),__y=(y);(__x < __y) ? __x : __y; })
#define max(x, y) ({typeof(x) __x=(x),__y=(y);(__x < __y) ? __y : __x; })
#define IS_2BYTEWORD(_a_) ( (char)(0x80) <= (_a_) && (_a_) <= (char)(0xFF) )
#define PRIME 211

int hashpjw(char *s) {
  char *p;
  unsigned int h = 0, g;
  for(p = s; *p; p++) {
    h = (h << 4) + (*p);
    if((g = h & 0xf0000000) != 0) {
      h = h ^ (g >> 24);
      h = h ^ g;
    }
  }
  return h % PRIME;
}

int getHash(char *s) {
  int i;
  int h = 0;

  for(i = 0; ; i++) {
    if(s[i] == 0) {
      break;
    }
    h += s[i];
  }
  return h;
}

void easyGetTokenFromString(char *src, int count, char *output, int len) {
  int i;
  int counter = 0;

  if(len <= 0)return;

#define ISSPACETAB(c)   ( (c) == ' ' || (c) == '\t' )

  for(i = 0; ; i++) {
    if(src[i] == '\0') {
      output[0] = '\0';
      return;
    }
    if(i > 0 && !ISSPACETAB(src[i - 1]) &&
       !ISSPACETAB(src[i])) {
      continue;
    }

    if(!ISSPACETAB(src[i])) {
      counter++;
      if(counter == count) {
        int j;
        for(j = 0; j < len - 1; j++) {
          if(src[i + j] == '\0' ||
             ISSPACETAB(src[i + j])) {
            break;
          }
          output[j] = src[i + j];
        }
        output[j] = '\0';
        return;

      }
    }

  }
}

void prepareDirectories(char *base) {
  int i;
  char dname[1024];

  for(i = 0; i < 256; i++) {
    int ret;
    snprintf(dname, sizeof(dname), "%s/0x%x", base, i);
    ret = mkdir(dname, 0755);
    if(ret < 0 && errno != EEXIST) {
      log("mkdir error:%d %s: %s\n", ret, strerror(errno), dname);
    }
    if(ret == 0) log(".");
  }
}

void makeDirFilename(char *out, int outlen, char *base, int dirchar, char *child) {
  snprintf(out, outlen, "%s/0x%x/%s", base, dirchar & 0xff, child);
}

#define FALSE 0
#define TRUE  1

typedef struct tagEscapeChar {
  char escapechar;
  char escapedchar;
} EscapeChar;
static EscapeChar escapeChar[] =
    {
        {'\n', 'n'},
        {',',  'c'},
        {'|',  'z'},
        {'\\', 'y'},
    };

char *makeStringFromEscaped(char *src) {
  int srclen = strlen(src);
  int searchindex = 0;

  for(int i = 0; i < srclen; i++) {
    // for 2Byte Word
    if(IS_2BYTEWORD(src[i])) {
      src[searchindex++] = src[i++];
      src[searchindex++] = src[i];
    } else {
      if(src[i] == '\\') {
        int j;

        i++;
        for(j = 0; j < sizeof(escapeChar) / sizeof(escapeChar[0]); j++) {
          if(escapeChar[j].escapedchar == src[i]) {
            src[searchindex++] = escapeChar[j].escapechar;
            break;
          }
        }
        if(escapeChar[j].escapedchar != src[i])
          src[searchindex++] = src[i];
      } else {
        src[searchindex++] = src[i];
      }
    }
  }
  src[searchindex] = '\0';
  return src;
}

char *makeEscapeString(char *src, char *dest, int sizeofdest) {
  int srclen = strlen(src);
  int destindex = 0;

  for(int i = 0; i < srclen; i++) {
    int dirty = FALSE;
    char escapechar = '\0';
    if(destindex + 1 >= sizeofdest) break;
    if(IS_2BYTEWORD(src[i])) {
      if(destindex + 2 >= sizeofdest) break;
      dest[destindex] = src[i];
      dest[destindex + 1] = src[i + 1];
      destindex += 2;
      i++;
      continue;
    }

    for(int j = 0; j < sizeof(escapeChar) / sizeof(escapeChar[0]); j++) {
      if(src[i] == escapeChar[j].escapechar) {
        dirty = TRUE;
        escapechar = escapeChar[j].escapedchar;
        break;
      }
    }
    if(dirty == TRUE) {
      if(destindex + 2 < sizeofdest) {
        dest[destindex] = '\\';
        dest[destindex + 1] = escapechar;
        destindex += 2;
        continue;   
      } else {
        dest[destindex] = '\0';
        return dest;
      }
    } else {
      dest[destindex] = src[i];
      destindex++;
    }
  }

  dest[destindex] = '\0';
  return dest;
}

#undef FALSE
#undef TRUE


int
strcatsafe(char *dest, int destlen, char *append) {
  int dl = strlen(dest);
  int al = strlen(append);

  if((dl + al) >= destlen) {
    return -1;
  } else {
    strcat(dest, append);
  }
  return 0;
}

char *chop(char *s) {
  int l = strlen(s);
  if(l >= 1) {
    s[l - 1] = 0;
  }
  return s;
}

char *strncpy2(char *dest, const char *src, size_t n) {
  if(n > 0) {
    char *d = dest;
    const char *s = src;
    int i;
    for(i = 0; i < n; i++) {
      if(*(s + i) == 0) {
        *(d + i) = '\0';
        return dest;
      }
      if(*(s + i) & 0x80) {
        *(d + i) = *(s + i);
        i++;
        if(i >= n) {
          *(d + i - 1) = '\0';
          break;
        }
        *(d + i) = *(s + i);
      } else
        *(d + i) = *(s + i);
    }
  }
  return dest;
}

void strncpysafe(char *dest, const size_t n, const char *src, const int length) {

  int Short;
  Short = min(strlen(src), length);

  if(n < Short + 1) {
    strncpy2(dest, src, n - 1);
    dest[n - 1] = '\0';

  } else if(n <= 0) {
    return;
  } else {
    strncpy2(dest, src, Short);
    dest[Short] = '\0';
  }
}

void strcpysafe(char *dest, size_t n, const char *src) {
  if(!src) {
    *dest = '\0';
    return;
  }
  if(n <= 0)
    return;
    
  else if(n < strlen(src) + 1) {
    strncpy2(dest, src, n - 1);
    dest[n - 1] = '\0';
  } else
    strcpy(dest, src);

}

char *ScanOneByte(char *src, char delim) {
  if(!src) return NULL;

  for(; src[0] != '\0'; src++) {
    if(IS_2BYTEWORD(src[0])) {
      if(src[1] != 0) {
        src++;
      }
      continue;
    }
    if(src[0] == delim) {
      return src;
    }
  }
  return NULL;
}

int easyGetTokenFromBuf(char *src, char *delim, int count, char *output, int len) {
  int i;
  int length = 0;
  int addlen = 0;
  int oneByteMode = 0; 

  if(strlen(delim) == 1) { 
    oneByteMode = 1;
  }
  for(i = 0; i < count; i++) {
    char *last;
    src += addlen;

    if(oneByteMode) {
      last = ScanOneByte(src, delim[0]);
    } else {
      last = strstr(src, delim);
    }
    if(last == NULL) {
      strcpysafe(output, len, src);

      if(i == count - 1)
        return 1;

      return 0;
    }
    
    length = last - src;
    addlen = length + strlen(delim);
  }
  strncpysafe(output, len, src, length);

  return 1;
}

