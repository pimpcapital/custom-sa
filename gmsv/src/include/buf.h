#ifndef __BUF_H__
#define __BUF_H__

#include "common.h"
void memEnd( void );
int configmem( int unit , int unitnumber );
int memInit( void );
void*   allocateMemory( const unsigned int nbyte );
void freeMemory( void* freepointer );
void showMem( char *buf);
#endif 
