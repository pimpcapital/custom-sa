#ifndef _SASQL_H_
#define _SASQL_H_

#include "version.h"

#define FALSE 0
#define TRUE 1

void sasql_close(void);

int sasql_init(void);

int sasql_query(char *nm, char *pas);

int sasql_update(char *nm, char *path);

int sasql_logindate(char *nm);

int sasql_register(char *id, char *ps);

int sasql_craete_userinfo(void);

int sasql_craete_lock(void);

int sasql_chehk_lock(char *idip);

int sasql_add_lock(char *idip);

int sasql_del_lock(char *idip);

#endif
