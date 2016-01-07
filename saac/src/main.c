#include "main.h"
#include "util.h"
#include "mail.h"
#include "db.h"
#include "saacproto_serv.h"
#include "acfamily.h"
#include "char.h"
#include "sasql.h"
#include <signal.h>
#include <getopt.h>
#include <netinet/tcp.h>
#include "lock.h"

#define BACKLOGNUM 5

struct membuf {
  int use;
  char buf[512];
//    char buf[1024*128];
  int len;
  int next;
};

struct connection {
  int use;
  int fd;
  int mbtop_ri;
  int mbtop_wi;
  struct sockaddr_in remoteaddr;
  int closed_by_remote;
};

struct membuf *mb;
int mbsize;
int mbuse;

int cpuuse;


int mainsockfd;
struct sockaddr_in localaddr;


struct connection *con;
static int mb_finder = 0;
char tmpbuf[1024 * 32];

struct timeval select_timeout;

time_t sys_time = 0;

extern gmsv gs[MAXCONNECTION];

int tcpstruct_init(char *addr, int port, int timeout_ms, int mem_use);

int tcpstruct_accept1(void);

int tcpstruct_accept(int *tis, int ticount);

int tcpstruct_close(int ti);

int tcpstruct_readline(int ti, char *buf, int len, int k, int r);

int tcpstruct_readline_chop(int ti, char *buf, int len);

int tcpstruct_write(int ti, char *buf, int len);

void set_nodelay(int sock);


#define OK     0
#define TCPSTRUCT_ENOMEM -1
#define TCPSTRUCT_ESOCK -2
#define TCPSTRUCT_EBIND -3
#define TCPSTRUCT_ELISTEN -4
#define TCPSTRUCT_EBUG -6
#define TCPSTRUCT_EINVCIND -7
#define TCPSTRUCT_EREADFIN -8
#define TCPSTRUCT_EHOST -9
#define TCPSTRUCT_ECONNECT -10
#define TCPSTRUCT_ECFULL -11 
#define TCPSTRUCT_ETOOLONG -12
#define TCPSTRUCT_EMBFULL -13
#define TCPSTRUCT_ECLOSEAGAIN -14


int port;
int Total_Charlist;
int Expired_mail;
int Del_Family_or_Member;
int Write_Family;

char *chartime() {
  static char buf[80];
  time_t t;
  t = time(0);
  strcpy(buf, ctime(&t));
  buf[strlen(buf) - 1] = 0;
  return buf;
}

void sighandle(int a) {
  if(a == SIGUSR1) log("sigusr1信号!\n");
  log("得到一个信号! 异常中断......\n");
  writeFamily(familydir);
  writeFMPoint(fmpointdir);
  writeFMSMemo(fmsmemodir);
  exit(1);
}

// Arminius 7.20 memory unlock
void sigusr1(int a) {
  int i;
  FILE *f;
  char key[4096], buf[4096];

  signal(SIGUSR1, sigusr1);

  f = fopen("./unlock.arg", "r");

  if(f) {
    memset(key, 0, 4096);
    fread(key, 4096, 1, f);
    for(i = 0; i < strlen(key); i++) if(key[i] == '\n') key[i] = '\0';

    switch(key[0]) {
      case 'P':  // unlock player
        if(DeleteMemLock(getHash(&key[1]) & 0xff, &key[1], &i)) {
          log("ADM: memunlock: %s success.\n", key);
        } else {
          log("ADM: memunlock: %s failed.\n", key);
        }
        break;
      case 'S':  // unlock server
        DeleteMemLockServer(&key[1]);
        log("ADM: memunlock: %s\n", key);
        break;
      case 'C':  // check player lock
        GetMemLockState(getHash(&key[1]) & 0xff, &key[1], buf);
        sprintf(key, "echo \"%s\" > ./sigusr1.result", buf);
        system(key);
        break;
      case 'L':  // Robin 列出所有Server连线
      log("\nList All Server Conncet!!!!!\n");
        for(i = 0; i < MAXCONNECTION; i++)
          if(gs[i].use) log("\n gs[%d] fd:%d name:%s ", i, gs[i].fd, gs[i].name);
        break;

    }
    log(" sigusr1_over_1 ");
    fclose(f);
    log(" sigusr1_over_2 ");

  }
}

static int netWrite(int ti, char *buf, int len) {
  return tcpstruct_write(ti, buf, len);
}

gmsv gs[MAXCONNECTION];

int login_game_server(int ti, char *svname, char *svpas, char *result, int resultlen, char *retdata, int retdatalen) {
  if(strcmp(svpas, svpass) == 0) {
    log("服务器密码正确 %s\n", svname);
  } else {
    log("服务器密码错误 %s\n", svname);
    snprintf(result, resultlen, "失败");
    snprintf(retdata, retdatalen, "密码错误");
    return 0;
  }
  {
    int i;
    for(i = 0; i < MAXCONNECTION; i++) {
      if(gs[i].use &&
         strcmp(gs[i].name, svname) == 0) {
        snprintf(result, resultlen, "failed");
        snprintf(retdata, retdatalen, "duplicate login");
        return 0;
      }
    }
  }
  snprintf(gs[ti].name, sizeof(gs[ti].name), "%s", svname);
  gs[ti].fd = ti;
  snprintf(result, resultlen, SUCCESSFUL);
  snprintf(retdata, retdatalen, "Nothing special");
  DeleteMemLockServer(svname);  // Arminius 7.31 unlock server
  return 0;
}

int logout_game_server(int ti) {

  gs[ti].use = 0;
  gs[ti].fd = -1;
  gs[ti].name[0] = 0;
  tcpstruct_close(ti);
  return 0;
}

int is_game_server_login(int ti) {
  return gs[ti].use;
}

static int readConfig(char *path) {
  char buf[2048];
  FILE *fp;

  fp = fopen(path, "r");
  if(fp == NULL) { return -2; }

  while(fgets(buf, sizeof(buf), fp)) {
    char command[128];
    char param[128];
    chop(buf);

    easyGetTokenFromString(buf, 1, command, sizeof(command));
    easyGetTokenFromString(buf, 2, param, sizeof(param));

    if(strcmp(command, "port") == 0) {
      port = atoi(param);
      log("端口:%d\n", port);
    } else if(strcmp(command, "logdir") == 0) {
      snprintf(logdir, sizeof(logdir), param);
      log("日志目录:%s\n", logdir);
    } else if(strcmp(command, "chardir") == 0) {
      snprintf(chardir, sizeof(chardir), param);
      log("档案目录:%s\n", chardir);
#ifdef _SLEEP_CHAR
      snprintf(sleepchardir, sizeof(sleepchardir), "%s_sleep", chardir);
      log("睡眠目录:%s\n", sleepchardir);
#endif
    } else if(strcmp(command, "pass") == 0) {
      snprintf(svpass, sizeof(svpass), param);
      log("密码:%s\n", param);
    } else if(strcmp(command, "dbdir") == 0) {
      snprintf(dbdir, sizeof(dbdir), param);
      log("数据目录:%s\n", dbdir);
    } else if(strcmp(command, "rotate_interval") == 0) {
      log_rotate_interval = atoi(param);
      log("日志循环间隔:%d\n", log_rotate_interval);
    } else if(strcmp(command, "maildir") == 0) {
      snprintf(maildir, sizeof(maildir), param);
      log("邮件目录:%s\n", maildir);
      // CoolFish: Family 2001/5/9
    } else if(strcmp(command, "familydir") == 0) {
      snprintf(familydir, sizeof(familydir), param);
      log("家族目录:%s\n", familydir);
    } else if(strcmp(command, "fmpointdir") == 0) {
      snprintf(fmpointdir, sizeof(fmpointdir), param);
      log("庄园表列:%s\n", fmpointdir);
    } else if(strcmp(command, "fmsmemodir") == 0) {
      snprintf(fmsmemodir, sizeof(fmsmemodir), param);
      log("家族备份:%s\n", fmsmemodir);
    } else if(strcmp(command, "Total_Charlist") == 0) {
      Total_Charlist = atoi(param);
      log("更新人物点数间隔:%d秒\n", Total_Charlist);
    } else if(strcmp(command, "Expired_mail") == 0) {
      Expired_mail = atoi(param);
      log("更新过期邮件间隔:%d秒\n", Expired_mail);
    } else if(strcmp(command, "Del_Family_or_Member") == 0) {
      Del_Family_or_Member = atoi(param);
      log("删除家族成员间隔:%d秒\n", Del_Family_or_Member);
    } else if(strcmp(command, "Write_Family") == 0) {
      Write_Family = atoi(param);
      log("更新家族信息间隔:%d秒\n", Write_Family);
    } else if(strcmp(command, "SameIpMun") == 0) {
      sameipmun = atoi(param);
      if(sameipmun > 0) {
        log("同IP允许同时登陆:%d次\n", sameipmun);
      } else {
        log("同IP允许同时登陆:无限制\n");
      }
    }
  }

  fclose(fp);
  return 0;
}


static void parseOpts(int argc, char **argv) {
  int c, option_index;

  while(1) {
    static struct option long_options[] = {
        {"nice",     1, 0, 'n'},
        {"help",     0, 0, 'h'},
        {"userinfo", 0, 0, 'i'},
        {"lockuser", 0, 0, 'l'}
    };
    c = getopt_long(argc, argv, "n:hil", long_options, &option_index);
    if(c == -1)break;
    switch(c) {
      case 'h':
        fprintf(stderr,
                "使用方法: saac [-h] [-w port] [-w port] ... \n"
                    "-h : 显示saac的帮助\n"
                    "-w port : 添加一个工作站进程端口\n");
        exit(0);
      case 'i':
        sasql_init();
        sasql_craete_userinfo();
        sasql_close();
        exit(0);
      case 'l':
        sasql_init();
        sasql_craete_lock();
        sasql_close();
        exit(0);
      case 'n':
        nice(atoi(optarg));
        break;
      default: log("不能读懂选项 %c\n", c);
        exit(0);
    }
  }
}

double time_diff(struct timeval subtrahend, struct timeval subtractor);


int main(int argc, char **argv) {
  parseOpts(argc, argv);

  // Nuke +1 1012: Loop counter
  int counter1 = 0;

  int counter2 = 0;

  int counter3 = 0;

  int counter4 = 0;

  signal(SIGUSR1, sigusr1);

  log_rotate_interval = 3600 * 24 * 7;

  Lock_Init();  // Arminius 7.17 memory lock

  UNlockM_Init();

  if(readConfig("acserv.cf") < 0) {
    log("无法在当前目录里读取 acserv.cf .\n");
    exit(1);
  }

  sasql_init();
  dbRead(dbdir);
  log("读取 家族庄园\n");
  readFMSMemo(fmsmemodir);
  log("读取 家族留言\n");
  readFMPoint(fmpointdir);
  log("读取 家族目录\n");
  readFamily(familydir);
  log("准备 档案目录\n");
  prepareDirectories(chardir);
  log("准备 日志目录\n");
  prepareDirectories(logdir);
  log("准备 邮件目录\n");
  prepareDirectories(maildir);

#ifdef _SLEEP_CHAR
  prepareDirectories(sleepchardir);
  log("准备 睡眠档案目录\n");
#endif

  if(readMail(maildir) < 0) {
    log("不能初始化邮件\n");
    exit(1);
  }

  int tcpr;
  if((tcpr = tcpstruct_init(NULL, port, 0, CHARDATASIZE * 16 * MAXCONNECTION)) < 0) {
    log("不能开启TCP: %d\n", tcpr);
    return 1;
  }
  saacproto_InitServer(netWrite, CHARDATASIZE);

  {
    struct sigaction s, os;

    bzero(&s, sizeof(s));
    s.sa_handler = sighandle;
    s.sa_flags = SA_NOMASK;
    sigaction(SIGTERM, &s, &os);

    bzero(&s, sizeof(s));
    s.sa_handler = sighandle;
    s.sa_flags = SA_NOMASK;
    sigaction(SIGINT, &s, &os);

    bzero(&s, sizeof(s));
    s.sa_handler = SIG_IGN;
    s.sa_flags = SA_NOMASK;
    sigaction(SIGPIPE, &s, &os);

  }

#ifdef _AC_SEND_FM_PK     // WON ADD 庄园对战列表储存在AC
  load_fm_pk_list();
#endif

#ifdef _ACFMPK_LIST
  FMPK_LoadList();
#endif
#ifdef _ALLDOMAN
  LOAD_herolist();  // Syu ADD 排行榜NPC
#endif

  log("\n开始工作...\n");

  signal(SIGUSR1, sigusr1);  // Arminius 7.20 memory lock
  int itime = 0;
  while(1) {
    itime++;
    if(itime > cpuuse) {
      itime = 0;
      usleep(1);
    }
    int newti, i;
    static time_t main_loop_time;

    sys_time = time(NULL);

    if(main_loop_time != sys_time) {
      main_loop_time = time(NULL);
      counter1++;
      counter2++;
      counter3++;
      counter4++;
      UNlockM_UnlockPlayer();

      if(counter1 > Total_Charlist) {
        counter1 = 0;
        char *c = ctime(&main_loop_time);
        if(c) {
          struct timeval st, et;
          log("\nTIME:%s\n", c);
          gettimeofday(&st, NULL);
          dbFlush(dbdir);
          gettimeofday(&et, NULL);
          log("Flushed db(%fsec)\n", time_diff(et, st));
          log("档案表列总数:%d NG:%d\n",
              total_ok_charlist, total_ng_charlist);
        }
      }
      if(counter2 > Expired_mail) {
        counter2 = 0;
        struct timeval st, et;
        gettimeofday(&st, NULL);
        expireMail();
        gettimeofday(&et, NULL);
        log("过期邮件(%fsec)\n", time_diff(et, st));
      }
      if(counter4 > Write_Family) // 300( -> 60)
      {
        counter4 = 0;
        struct timeval st, et;
        gettimeofday(&st, NULL);
        writeFamily(familydir);
        writeFMPoint(fmpointdir);
        writeFMSMemo(fmsmemodir);
        gettimeofday(&et, NULL);
        log("记录家族(%fsec)\n", time_diff(et, st));
      }
    }
    newti = tcpstruct_accept1();
    if(newti >= 0) {
      log("同意: %d\n", newti);
      gs[newti].use = 1;
    }

    for(i = 0; i < MAXCONNECTION; i++) {
//        	char buf[CHARDATASIZE * 16;
      char buf[CHARDATASIZE];
      int l;
      l = tcpstruct_readline_chop(i, buf, sizeof(buf) - 1);
      {
        if(!gs[i].use)continue;
        if(l > 0) {
          char debugfun[256];
          buf[l] = 0;
          if(saacproto_ServerDispatchMessage(i, buf, debugfun) < 0) {
            // Nuke start
            tcpstruct_close(i);// avoid the shutdown the gmsv ttom
            log("GMSV(%s) 消息:%s\n", gs[i].name, debugfun);
          }
        } else if(l == TCPSTRUCT_ETOOLONG) {
          log("很长:%d 服务器名::%s\n", i, gs[i].name);
          logout_game_server(i);
        } else if(l < 0) {
          log("关闭:%d 服务器名:%s\n", i, gs[i].name);
          logout_game_server(i);
        } else if(l == 0) { ;
        }
      }
    }
    {
      static struct timeval tv_loop_store;
      struct timeval now;
      double dif;
      gettimeofday(&now, NULL);
      dif = time_diff(now, tv_loop_store);
      tv_loop_store = now;
    }
  }
  return 0;
}

double time_diff(struct timeval subtrahend, struct timeval subtractor) {
  return ((subtrahend.tv_sec - subtractor.tv_sec)
          + (subtrahend.tv_usec
             - subtractor.tv_usec) / (double) 1E6);
}


int get_rotate_count() {
  unsigned int t = (unsigned int) time(NULL);
  return (t / log_rotate_interval) * log_rotate_interval;
}

static int findregBlankMemBuf();

static int unregMemBuf(int index);

static int findregBlankCon();

static int getFreeMem();

static int appendReadBuffer(int index, char *data, int len);

static int appendWriteBuffer(int index, char *data, int len);

static int appendMemBufList(int top, char *data, int len);

static int consumeMemBufList(int top, char *out, int len, int flag, int copyflag);

static int getLineReadBuffer(int index, char *buf, int len);

int tcpstruct_init(char *addr, int p, int timeout_ms, int mem_use) {
  mbsize = mem_use / sizeof(struct membuf);
  mbuse = 0;
  mb_finder = 0;
  mb = (struct membuf *) calloc(1, mbsize * sizeof(struct membuf));

  if(mb == NULL) return TCPSTRUCT_ENOMEM;
  bzero(mb, mbsize * sizeof(struct membuf));

  con = (struct connection *) calloc(1, MAXCONNECTION * sizeof(struct connection));
  if(con == NULL) {
    free(mb);
    return TCPSTRUCT_ENOMEM;
  } else {
    int i;
    for(i = 0; i < MAXCONNECTION; i++) {
      con[i].use = 0;
      con[i].fd = -1;
    }
  }
  select_timeout.tv_sec = timeout_ms / 1000;
  select_timeout.tv_usec = (timeout_ms - (timeout_ms / 1000) * 1000) * 1000;

  /* socket */
  mainsockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(mainsockfd < 0) return TCPSTRUCT_ESOCK;

  /* bind */
  bzero(&localaddr, sizeof(localaddr));
  localaddr.sin_family = AF_INET;
  localaddr.sin_port = htons(p);

  if(addr) {
    localaddr.sin_addr.s_addr = inet_addr(addr);
  } else {
    localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  }
  if(bind(mainsockfd, (struct sockaddr *) &localaddr,
          sizeof(localaddr)) < 0)
    return TCPSTRUCT_EBIND;

  /* listen */
  if(listen(mainsockfd, BACKLOGNUM) < 0) return TCPSTRUCT_ELISTEN;

  return OK;
}

int tcpstruct_accept1(void) {
  int tis[BACKLOGNUM];
  int ret;

  ret = tcpstruct_accept(tis, 1);
  if(ret < 0) {
    return ret;
  } else if(ret == 1) {
    return tis[0];
  } else {
    return TCPSTRUCT_EBUG;
  }
}

int tcpstruct_accept(int *tis, int ticount) {
  int i;
  int sret = 0;
  int accepted = 0;
  struct timeval t;
  fd_set rfds, wfds, efds;
  FD_ZERO(&rfds);
  FD_ZERO(&wfds);
  FD_ZERO(&efds);

  for(i = 0; i < MAXCONNECTION; i++) {
    if(con[i].use &&
       con[i].fd >= 0 && con[i].closed_by_remote == 0) {
      FD_SET(con[i].fd, &rfds);
      FD_SET(con[i].fd, &wfds);
      FD_SET(con[i].fd, &efds);


      t = select_timeout;
      sret = select(con[i].fd + 1, &rfds, (fd_set *) NULL, (fd_set *) NULL, &t);
      if(sret > 0) {
        if((con[i].fd >= 0) && FD_ISSET(con[i].fd, &rfds)) {
          int fr = getFreeMem();
          int rr, readsize;
          if(fr <= 0) continue;
          if(fr > sizeof(tmpbuf)) {
            readsize = sizeof(tmpbuf);
          } else {
            readsize = fr;
          }
          rr = read(con[i].fd, tmpbuf, readsize);
          if(rr <= 0) {
            con[i].closed_by_remote = 1;
          } else {
            appendReadBuffer(i, tmpbuf, rr);
          }
        }
      }

      t = select_timeout;
      sret = select(con[i].fd + 1, (fd_set *) NULL, &wfds, (fd_set *) NULL, &t);
      if(sret > 0) {
        if((con[i].fd >= 0) && FD_ISSET(con[i].fd, &wfds)) {
          char send_buf[4096];
          memset(send_buf, 0, sizeof(send_buf));
          int l = consumeMemBufList(con[i].mbtop_wi, send_buf, sizeof(send_buf), 0, 1);
          if(l > 0) {
            int rr = write(con[i].fd, send_buf, l);
            if(rr < 0) {
              con[i].closed_by_remote = 1;
            } else {
              consumeMemBufList(con[i].mbtop_wi, send_buf, l, 1, 0);
            }
          }
        }
      }
    }
  }

  for(i = 0; i < ticount; i++) {
    int asret;
    t.tv_sec = 0;
    t.tv_usec = 0;
    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    FD_ZERO(&efds);
    FD_SET(mainsockfd, &rfds);
    FD_SET(mainsockfd, &wfds);
    FD_SET(mainsockfd, &efds);
    asret = select(mainsockfd + 1, &rfds, &wfds, (fd_set *) NULL, &t);
    // Nuke 20040610: add asret>0 to avoid signal interrupt in select
    if((asret > 0) && FD_ISSET(mainsockfd, &rfds)) {
      struct sockaddr_in c;
      int len, newsockfd;
      int newcon;
      bzero(&c, sizeof(c));
      len = sizeof(c);
      fprintf(stderr, "i can accept ");
      newcon = findregBlankCon();
      if(newcon < 0) continue;
      newsockfd = accept(mainsockfd, (struct sockaddr *) &c, &len);
      log("同意: %d\n", newsockfd);
      if(newsockfd < 0) {
        unregMemBuf(newcon);
        continue;
      }
      set_nodelay(newsockfd);
      con[newcon].fd = newsockfd;
      memcpy(&con[newcon].remoteaddr, &c, sizeof(c));
      tis[accepted] = newcon;
      accepted++;
    }
  }

  return accepted;
}

int tcpstruct_close(int ti) {

  if(ti < 0 || ti >= MAXCONNECTION) return TCPSTRUCT_EINVCIND;
  if(con[ti].use == 0) {
    return TCPSTRUCT_ECLOSEAGAIN;
  }
  close(con[ti].fd);
  con[ti].use = 0;
  con[ti].fd = -1;

  consumeMemBufList(con[ti].mbtop_ri, NULL, mbsize * sizeof(mb[0].buf), 1, 0);
  consumeMemBufList(con[ti].mbtop_wi, NULL, mbsize * sizeof(mb[0].buf), 1, 0);
  unregMemBuf(con[ti].mbtop_ri);
  unregMemBuf(con[ti].mbtop_wi);
  con[ti].mbtop_ri = -1;
  con[ti].mbtop_wi = -1;
  return OK;
}

int tcpstruct_readline(int ti, char *buf, int len, int kend, int kend_r) {
  int l;
  int minus = 0;

  if(ti < 0 || ti >= MAXCONNECTION || con[ti].use == 0)
    return TCPSTRUCT_EINVCIND;

  l = getLineReadBuffer(ti, buf, len);
  if(l == 0) {
    if(con[ti].closed_by_remote) {
      return TCPSTRUCT_EREADFIN;
    } else {
      return 0;
    }
  }

  if(kend) {
    if(buf[l - 1] == '\n') {
      buf[l - 1] = 0;
      minus = -1;
    }
  }
  if(kend_r) {
    if(buf[l - 1] == '\r') {
      buf[l - 1] = 0;
      minus = -1;
    }
    if(buf[l - 2] == '\r') {
      buf[l - 2] = 0;
      minus = -2;
    }
  }
  return l + minus;
}

int tcpstruct_readline_chop(int ti, char *buf, int len) {
  return tcpstruct_readline(ti, buf, len, 1, 1);
}

int tcpstruct_write(int ti, char *buf, int len) {
  if(ti < 0 || ti >= MAXCONNECTION || con[ti].use == 0)
    return TCPSTRUCT_EINVCIND;
  return appendWriteBuffer(ti, buf, len);
}

static int appendReadBuffer(int index, char *data, int len) {
  int top;

  top = con[index].mbtop_ri;
  for(; ;) {
    int nextind = mb[top].next;

    if(nextind == -1) break;
    top = nextind;
  }
  return appendMemBufList(top, data, len);
}

static int appendWriteBuffer(int index, char *data, int len) {
  int top;
  top = con[index].mbtop_wi;
  for(; ;) {
    int nextind = mb[top].next;
    if(nextind == -1) break;
    top = nextind;
  }
  return appendMemBufList(top, data, len);
}

static int appendMemBufList(int top, char *data, int len) {
  int fr = getFreeMem();
  int rest = len;
  int data_topaddr = 0;

  if(len >= fr) {
    FILE *fp;
    if((fp = fopen("badsysinfo.txt", "a+")) != NULL) {
      fprintf(fp, "appendMemBufList() len:%d / fr:%d err !! \n", len, fr);
      fclose(fp);
    }
    //andy_log
    log("appendMemBufList() len:%d / fr:%d err !! \n", len, fr);
    return -1;
  }
  data[len] = 0;
  for(; ;) {
    int blanksize = sizeof(mb[0].buf) - mb[top].len;
    int cpsize = (rest <= blanksize) ? rest : blanksize;
    memcpy(mb[top].buf + mb[top].len, data + data_topaddr, cpsize);
    mb[top].len += cpsize;
    if(rest <= blanksize) {
      return len;
    } else {
      int newmb;
      rest -= cpsize;
      data_topaddr += cpsize;
      if((newmb = findregBlankMemBuf()) == TCPSTRUCT_EMBFULL) {
        FILE *fp;
        if((fp = fopen("badsysinfo.txt", "a+")) != NULL) {
          fprintf(fp, "find newmb == TCPSTRUCT_EMBFULL err data:%s !!\n", data);
          fclose(fp);
        }
        log("find newmb == TCPSTRUCT_EMBFULL err data:%s !!\n", data);
      }
      mb[top].next = newmb;
      top = mb[top].next;
    }
  }
  return TCPSTRUCT_EBUG;
}

static int consumeMemBufList(int top, char *out, int len, int consumeflag, int copyflag) {
  int total = 0;
  int top_store = top;
  for(; ;) {
    int cpsize;
    if(top == -1) break;
    cpsize = (mb[top].len <= (len - total)) ?
             mb[top].len : (len - total);

    if(copyflag) memcpy(out + total, mb[top].buf, cpsize);
    total += cpsize;

    if(consumeflag) {
      mb[top].len -= cpsize;
      if(mb[top].len > 0) {
        memmove(mb[top].buf, mb[top].buf + cpsize, sizeof(mb[top].buf) - cpsize);
      }
    }
    top = mb[top].next;
    if(total == len) {
      break;
    }
  }

  if(consumeflag) {
    top = mb[top_store].next;
    for(; ;) {
      if(top == -1)break;
      if(mb[top].len == 0) {
        int prev;
        mb[top_store].next = mb[top].next;
        prev = top;
        top = mb[top].next;
        unregMemBuf(prev);
      } else {
        top = mb[top].next;
      }
    }
  }

  return total;
}

static int getLineReadBuffer(int index, char *buf, int len) {

  int top = con[index].mbtop_ri;
  int ti = 0, breakflag = 0;

  for(; ;) {
    int i;
    int l = mb[top].len;
    if(top == -1)break;
    for(i = 0; i < l; i++) {
      if(mb[top].buf[i] == '\n') {
        breakflag = 1;
        break;
      }
      ti++;
    }
    if(breakflag)break;
    top = mb[top].next;
  }
  if(ti > len) {
    return TCPSTRUCT_ETOOLONG;
  }
  if(breakflag == 0) {
    return 0;
  }

  return consumeMemBufList(con[index].mbtop_ri, buf, ti + 1, 1, 1);
}

static int getFreeMem() {
  return (mbsize - mbuse) * sizeof(mb[0].buf);
}

static int findregBlankMemBuf() {
  int i;
  for(i = 0; i < mbsize; i++) {
    mb_finder++;
    if(mb_finder >= mbsize || mb_finder < 0) mb_finder = 0;

    if(mb[mb_finder].use == 0) {
      mb[mb_finder].use = 1;
      mb[mb_finder].len = 0;
      mb[mb_finder].next = -1;
      mbuse++;
      return mb_finder;
    }
  }
  return TCPSTRUCT_EMBFULL;
}

static int unregMemBuf(int index) {
  mb[index].use = 0;
  mb[index].next = -1;
  mb[index].len = 0;
  mbuse--;
  return OK;
}

static int findregBlankCon() {
  for(int i = 1; i < MAXCONNECTION; i++) {
    if(con[i].use == 0) {
      con[i].use = 1;
      con[i].fd = -1;

      con[i].mbtop_ri = findregBlankMemBuf();
      if(con[i].mbtop_ri < 0) {
        fprintf(stderr, "EMBFULL\n");
        return TCPSTRUCT_EMBFULL;
      }

      con[i].mbtop_wi = findregBlankMemBuf();
      if(con[i].mbtop_wi < 0) {
        unregMemBuf(con[i].mbtop_ri);
        fprintf(stderr, "EMBFULL\n");
        return TCPSTRUCT_EMBFULL;
      }
      bzero(&con[i].remoteaddr, sizeof(struct sockaddr_in));
      con[i].closed_by_remote = 0;
      return i;
    }
  }
  return TCPSTRUCT_ECFULL;
}

char *getGSName(int i) {
  return gs[i].name;
}

void checkGSUCheck(char *id) {
  int i;
  char gname[256];
  if(!id[0]) return;
  memset(gname, 0, sizeof(gname));
  if(LockNode_getGname((getHash(id) & 0xff), id, gname) <= 0) {
    log("无法从游戏中找到账号:%x/%s !!\n", getHash(id), id);
    return;
  }
  log("\n");
  for(i = 0; i < MAXCONNECTION; i++) {
    if(gs[i].name[0] && strcmp(gs[i].name, gname) == 0) {
      log("发送解锁检查[%s] 到 %d.%x/%s 服务器:%d !!\n", id, i, getHash(id), gname, gs[i].fd);
      saacproto_ACUCheck_send(gs[i].fd, id);
      return;
    }
  }

  int ret = -1;
  if(!isLocked(id)) {
    log("删除内存信息: 用户:%x/%s 没有锁定!!\n", getHash(id), id);
  }
  if(DeleteMemLock(getHash(id) & 0xff, id, &ret)) {

  } else {
    log("不能解锁 %x:%s !\n", getHash(id), id);
  }
}

void set_nodelay(int sock) {
  int flag = 1;
  int result = setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));
  if(result < 0) {
    log("不能设置延迟.\n");
  } else {
    log("设置延迟: fd:%d\n", sock);
  }
}

void gmsvBroadcast(int fd, char *p1, char *p2, char *p3, int flag) {
  for(int i = 0; i < MAXCONNECTION; i++) {
    if((flag == 1) && (i == fd)) continue;
    if(gs[i].use && gs[i].name[0]) {
      saacproto_Broadcast_send(i, p1, p2, p3);
    }
  }
}

