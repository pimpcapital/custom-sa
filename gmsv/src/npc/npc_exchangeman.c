#include "version.h"
#include <string.h>
#include "char.h"
#include "npcutil.h"
#include "lssproto_serv.h"
#include "npc_exchangeman.h"
#include "log.h"
#include "battle.h"
#include "handletime.h"
#include "enemy.h"

static void NPC_ExChangeMan_selectWindow(int meindex, int talker, int num);

int NPC_TypeCheck(int meindex, int talker, char *szMes);

int NPC_ExChangeManEventCheck(int meindex, int talker, char *buff1);

int NPC_EventItemCheck(int meindex, int talker, int itemNo, int flg);

int NPC_EventLevelCheck(int meindex, int talker, int level, int flg);

// Arminius 8.14 move to .h (for pet talk)
//int NPC_EventBigSmallCheck(int meindex,int talker,char* buf);
int NPC_EventFreeIfCheck(int meindex, int talker, char *buf, int kosuu, int flg);

int NPC_EventBigSmallLastCheck(int point1, int mypoint, int flg);

int NPC_ENDEventNoCheck(int meindex, int talker, int shiftbit, int flg);

int NPC_NOWEventNoCheck(int meindex, int talker, int shiftbit, int flg);

int NPC_TiemCheck(int meindex, int talker, int time, int flg);

int NPC_EventAddPet(int meindex, int talker, char *buff2, int mode);

int NPC_RandItemGet(int meindex, int talker, int rand_j, char *buf);

int NPC_PetLvCheckType2(int petindex, int meindex, int talker, char *buf, int mode);

int NPC_PetLvCheck(int meindex, int talker, char *buf, int mode);

void NPC_RequestMain(int meindex, int talker, char *buf);

void NPC_AcceptMain(int meindex, int talker, char *buf);

void NPC_MsgDisp(int meindex, int talker, int num);

int NPC_EventAdd(int meindex, int talker, int mode);

int NPC_AcceptDel(int meindex, int talker, int mode);

int NPC_SavePointCheck(int meindex, int talker, int shiftbit, int flg);

int NPC_EventReduce(int meindex, int talker, char *buf);

int NPC_EventDelItem(int meindex, int talker, char *buf, int breakflg);

int NPC_EventDelItemEVDEL(int meindex, int talker, char *buf, char *nbuf, int breakflg);

int NPC_EventAddItem(int meindex, int talker, char *buf);

int NPC_EventFile(int meindex, int talker, char *buf);

int NPC_EventDelPet(int meindex, int talker, int petsel);

void NPC_PetSkillMakeStr(int meindex, int toindex, int select);

void NPC_CleanMain(int meindex, int talker, char *buf);

void NPC_EventPetSkill(int meindex, int talker, char *data);

int NPC_ItemFullCheck(int meindex, int talker, char *buf, int mode, int evcnt);

void NPC_CharmStatus(int talker);

int NPC_ImageCheck(int meindex, int talker, int kosuu, int flg);

int NPC_EventGetCost(int meindex, int talker, char *arg);

int NPC_EventWarpNpc(int meindex, char *buf);


enum {
  CHAR_WORK_EVENTWARP = CHAR_NPCWORKINT4,

};

int NPC_ExChangeManInit(int meindex) {

  char argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
  char buf[1024 * 2];
  int i = 1;
  char buf4[256];

  CHAR_setWorkInt(meindex, CHAR_WORK_EVENTWARP, 1);

  CHAR_setInt(meindex, CHAR_WHICHTYPE, CHAR_TYPEEVENT);


  if(NPC_Util_GetArgStr(meindex, argstr, sizeof(argstr)) == NULL) {
    print("NPC_ExChange.c TypeCheck: GetArgStrErr\n");
    print("NPCName=%s\n", CHAR_getChar(meindex, CHAR_NAME));
    return FALSE;
  }

  i = 1;
  while(getStringFromIndexWithDelim(argstr, "EventEnd", i, buf, sizeof(buf))
        != FALSE) {
    i++;
    if(strstr(buf, "GetItem") != NULL) {
      if(strstr(buf, "ItemFullMsg") == NULL) {
        NPC_Util_GetStrFromStrWithDelim(buf, "EventNo", buf4, sizeof(buf4));
        print("\n### EventNo=%d %s:ItemFullMsg 脱离###", atoi(buf4), CHAR_getChar(meindex, CHAR_NAME));
      }
    }

    if(strstr(buf, "GetPet") != NULL) {
      if(strstr(buf, "PetFullMsg") == NULL) {
        NPC_Util_GetStrFromStrWithDelim(buf, "EventNo", buf4, sizeof(buf4));
        print("\n### ventNo=%d %s:PetFullMsg 脱离 ###", atoi(buf4), CHAR_getChar(meindex, CHAR_NAME));
      }
    }

    if(strstr(buf, "GetEgg") != NULL) {
      if(strstr(buf, "PetFullMsg") == NULL) {
        NPC_Util_GetStrFromStrWithDelim(buf, "EventNo", buf4, sizeof(buf4));
        print("\n### ventNo=%d %s:PetFullMsg 脱离 ###", atoi(buf4), CHAR_getChar(meindex, CHAR_NAME));
      }
    }

    if(strstr(buf, "GetStone") != NULL) {
      if(strstr(buf, "StoneFullMsg") == NULL) {
        NPC_Util_GetStrFromStrWithDelim(buf, "EventNo", buf4, sizeof(buf4));
        print("\n### EventNo=%d %s:StonFullMsg 脱离 ###", atoi(buf4), CHAR_getChar(meindex, CHAR_NAME));
      }
    }

    if(strstr(buf, "DelStone") != NULL) {
      if(strstr(buf, "StoneLessMsg") == NULL) {
        NPC_Util_GetStrFromStrWithDelim(buf, "EventNo", buf4, sizeof(buf4));
        print("\n### EventNo=%d %s:StoneLessMsg 脱离 ###", atoi(buf4), CHAR_getChar(meindex, CHAR_NAME));
      }
    }
  }

  return TRUE;

}

int NPC_EventWarpNpc(int meindex, char *buf) {
  char token[32];
  char buf2[32];
  int floor, x, y;
  int ret;
  int cnt;
  int dcnt = 1;

  cnt = CHAR_getWorkInt(meindex, CHAR_WORK_EVENTWARP);
  while(getStringFromIndexWithDelim(buf, ",", dcnt, buf2, sizeof(buf2)) != FALSE) {
    dcnt++;
  }

  if(dcnt <= cnt)
    cnt = 1;


  while(getStringFromIndexWithDelim(buf, ",", cnt, buf2, sizeof(buf2)) != FALSE) {
    cnt++;
    ret = getStringFromIndexWithDelim(buf2, ".", 1, token, sizeof(token));
    if(ret == FALSE) {
      continue;
    }
    floor = atoi(token);

    ret = getStringFromIndexWithDelim(buf2, ".", 2, token, sizeof(token));
    if(ret == FALSE) {
      continue;
    }
    x = atoi(token);

    ret = getStringFromIndexWithDelim(buf2, ".", 3, token, sizeof(token));
    if(ret == FALSE) {
      continue;
    }
    y = atoi(token);

    CHAR_setWorkInt(meindex, CHAR_WORK_EVENTWARP, cnt);
    CHAR_warpToSpecificPoint(meindex, floor, x, y);
    return TRUE;
  }

  return FALSE;

}

void NPC_ExChangeManTalked(int meindex, int talkerindex, char *szMes, int color) {
  if(CHAR_getInt(talkerindex, CHAR_WHICHTYPE) != CHAR_TYPEPLAYER) {
    return;
  }

  if(NPC_Util_isFaceToFace(meindex, talkerindex, 2) == FALSE) {
    if(NPC_Util_isFaceToChara(talkerindex, meindex, 1) == FALSE) return;
  }

  CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANT, 0);
  CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTSEC, 0);
  CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD, 0);

  NPC_TypeCheck(meindex, talkerindex, szMes);

}

int NPC_TypeCheck(int meindex, int talker, char *szMes) {

  char argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
  char buf[1024 * 2];
  char buf2[512];
  int i = 1;
  int EvNo;
  int evch;

  if(NPC_Util_GetArgStr(meindex, argstr, sizeof(argstr)) == NULL) {
    print("NPC_ExChange.c TypeCheck: GetArgStrErr\n");
    print("NPCName=%s\n", CHAR_getChar(meindex, CHAR_NAME));
    return FALSE;
  }

  while(getStringFromIndexWithDelim(argstr, "EventEnd", i, buf, sizeof(buf)) != FALSE) {
    i++;
    CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANT, 0);
    CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTSEC, 0);

    if(NPC_Util_GetStrFromStrWithDelim(buf, "EventNo", buf2, sizeof(buf2)) == NULL)
      continue;

    if(strstr(buf2, "-") != 0) {
      EvNo = -1;
    } else {
      EvNo = atoi(buf2);
    }

    if(NPC_EventCheckFlg(talker, EvNo) == TRUE) continue;

    if(NPC_Util_GetStrFromStrWithDelim(buf, "KeyWord", buf2, sizeof(buf2)) != NULL) {
      if(strcmp(szMes, buf2) != 0) continue;
      CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANT, i);
    }

    if(NPC_Util_GetStrFromStrWithDelim(buf, "Pet_Name", buf2, sizeof(buf2)) != NULL) {
      CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTSEC, 1);
    }
    evch = NPC_ExChangeManEventCheck(meindex, talker, buf);
    if(evch != -1) {
      if(NPC_Util_GetStrFromStrWithDelim(buf, "TYPE", buf2, sizeof(buf2)) != NULL) {

        if(strstr(buf2, "REQUEST") != NULL) {
          NPC_RequestMain(meindex, talker, buf);
          return TRUE;
        } else if(strstr(buf2, "ACCEPT") != NULL) {
          NPC_AcceptMain(meindex, talker, buf);
          return TRUE;

        } else if(strstr(buf2, "MESSAGE") != NULL) {
          char token[14 * 100];
          char token2[14 * 50];
          if(NPC_Util_GetStrFromStrWithDelim(buf, "NomalMsg", token, sizeof(token)) != NULL) {
            if(NPC_AcceptDel(meindex, talker, 0) == FALSE) return FALSE;
            if(EvNo != -1)
              NPC_NowEventSetFlg(talker, EvNo);
            CHAR_talkToCli(talker, meindex, token, CHAR_COLORWHITE);
            if(NPC_Util_GetStrFromStrWithDelim(buf, "NpcWarp", token2, sizeof(token2)) != NULL) {
              NPC_EventWarpNpc(meindex, token2);
            }
            if(NPC_Util_GetStrFromStrWithDelim(buf, "EndSetFlg", buf2, sizeof(buf2)) != NULL) {
              char buf3[16];
              int k = 1;
              if(EvNo != -1) NPC_NowEventSetFlgCls(talker, EvNo);
              while(getStringFromIndexWithDelim(buf2, ",", k, buf3, sizeof(buf3)) != FALSE) {
                k++;
                NPC_EventSetFlg(talker, atoi(buf3));
              }
            }
            if(NPC_Util_GetStrFromStrWithDelim(buf, "CleanFlg", buf2, sizeof(buf2)) != NULL) {
              char buf3[16];
              int k = 1;
              while(getStringFromIndexWithDelim(buf2, ",", k, buf3, sizeof(buf3)) != FALSE) {
                NPC_NowEndEventSetFlgCls(talker, atoi(buf3));
                k++;
              }
            }
          } else if(NPC_Util_GetStrFromStrWithDelim(buf, "NomalWindowMsg", token, sizeof(token)) != NULL) {
            int fd = getfdFromCharaIndex(talker);
#ifdef _NEWEVENT
            if(NPC_Util_GetStrFromStrWithDelim(buf, "NomalWindowMsg1",
                                               buf2, sizeof(buf2)) != NULL) {
              lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                               WINDOW_BUTTONTYPE_NEXT,
                               CHAR_WINDOWTYPE_WINDOWEVENT_STARTMSG,
                               CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                               token);
            } else {
#endif
              char token2[14 * 50];
              if(NPC_AcceptDel(meindex, talker, 0) == FALSE)
                return FALSE;

              if(EvNo != -1)
                NPC_NowEventSetFlg(talker, EvNo);

              if(NPC_Util_GetStrFromStrWithDelim(buf, "NpcWarp", token2, sizeof(token2)) != NULL)
                NPC_EventWarpNpc(meindex, token2);

              if(NPC_Util_GetStrFromStrWithDelim(buf, "EndSetFlg", buf2, sizeof(buf2)) != NULL) {
                char buf3[16];
                int k = 1;
                if(EvNo != -1) NPC_NowEventSetFlgCls(talker, EvNo);
                while(getStringFromIndexWithDelim(buf2, ",", k, buf3, sizeof(buf3)) != FALSE) {
                  k++;
                  NPC_EventSetFlg(talker, atoi(buf3));
                }
              }
              if(NPC_Util_GetStrFromStrWithDelim(buf, "CleanFlg", buf2, sizeof(buf2)) != NULL) {
                char buf3[16];
                int k = 1;
                while(getStringFromIndexWithDelim(buf2, ",", k, buf3, sizeof(buf3)) != FALSE) {
                  NPC_NowEndEventSetFlgCls(talker, atoi(buf3));
                  k++;
                }
              }
              lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                               WINDOW_BUTTONTYPE_YES,
                               CHAR_WINDOWTYPE_WINDOWEVENT_STARTMSG,
                               CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                               token);
#ifdef _NEWEVENT
            }
#endif
          }

          return TRUE;

        } else if(strstr(buf2, "CLEAN") != NULL) {
          NPC_CleanMain(meindex, talker, buf);
          return TRUE;
        }
      }
    }
  }

  strcpy(buf, "\0");
  if(NPC_Util_GetStrFromStrWithDelim(argstr, "NomalMainMsg", buf, sizeof(buf)) == NULL) {
    print("\n err:NOT FIND NomalMainMsg");
    return FALSE;
  }
  i = 1;
  while(getStringFromIndexWithDelim(buf, ",", i, buf2, sizeof(buf2)) != FALSE) {
    i++;
  }
  i--;
  i = rand() % i + 1;
  getStringFromIndexWithDelim(buf, ",", i, buf2, sizeof(buf2));
  CHAR_talkToCli(talker, meindex, buf2, CHAR_COLORWHITE);
  return TRUE;
}

static void NPC_ExChangeMan_selectWindow(int meindex, int talker, int num) {

  switch(num) {
    case 0:
      NPC_MsgDisp(meindex, talker, 0);
      break;

    case 1:
      NPC_MsgDisp(meindex, talker, 5);
      break;

    case 2:
      NPC_MsgDisp(meindex, talker, 6);
      break;

    case 3:
      NPC_MsgDisp(meindex, talker, 11);
      break;
  }

}

void NPC_RequestMain(int meindex, int talker, char *buf) {
  int shiftbit;
  char buf2[128];

  NPC_Util_GetStrFromStrWithDelim(buf, "EventNo", buf2, sizeof(buf2));
  shiftbit = atoi(buf2);

  if(NPC_NowEventCheckFlg(talker, shiftbit) == TRUE) {
    NPC_ExChangeMan_selectWindow(meindex, talker, 0);
  } else {
    NPC_ExChangeMan_selectWindow(meindex, talker, 1);
  }
}

void NPC_AcceptMain(int meindex, int talker, char *buf) {
  NPC_ExChangeMan_selectWindow(meindex, talker, 2);
}

void NPC_CleanMain(int meindex, int talker, char *buf) {
  NPC_ExChangeMan_selectWindow(meindex, talker, 3);
}

void NPC_ExChangeManWindowTalked(int meindex, int talkerindex, int seqno, int select, char *data) {
  if(NPC_Util_CharDistance(talkerindex, meindex) > 2) {
    return;
  }


  switch(seqno) {

    case CHAR_WINDOWTYPE_WINDOWEVENT_CLEANMSG:
      if(select == WINDOW_BUTTONTYPE_YES) {
        NPC_MsgDisp(meindex, talkerindex, 12);
      }
      break;

#ifdef _NEWEVENT
    case CHAR_WINDOWTYPE_WINDOWEVENT_STARTMSG:
      if(select == WINDOW_BUTTONTYPE_NEXT) {
        CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD, CHAR_getWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD) + 1);
        NPC_MsgDisp(meindex, talkerindex, 99);
      } else if(select == WINDOW_BUTTONTYPE_PREV) {
        CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD, CHAR_getWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD) - 1);
        NPC_MsgDisp(meindex, talkerindex, 99);
      }
      break;
#else
      case CHAR_WINDOWTYPE_WINDOWEVENT_STARTMSG:
      break;
#endif
    case CHAR_WINDOWTYPE_WINDOWEVENT_REQTHANK:
      if(select == WINDOW_BUTTONTYPE_NEXT) {
        CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD, CHAR_getWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD) + 1);
        NPC_MsgDisp(meindex, talkerindex, 22);
      } else if(select == WINDOW_BUTTONTYPE_PREV) {
        CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD, CHAR_getWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD) - 1);
        NPC_MsgDisp(meindex, talkerindex, 22);
      }
      break;

    case CHAR_WINDOWTYPE_WINDOWEVENT_ACCTHANK:
      if(select == WINDOW_BUTTONTYPE_NEXT) {
        CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD, CHAR_getWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD) + 1);
        NPC_MsgDisp(meindex, talkerindex, 82);
      } else if(select == WINDOW_BUTTONTYPE_PREV) {
        CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD, CHAR_getWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD) - 1);
        NPC_MsgDisp(meindex, talkerindex, 82);
      }
      break;

    case CHAR_WINDOWTYPE_WINDOWEVENT_NOWEVENT:
      if(select == WINDOW_BUTTONTYPE_YES) {
        NPC_MsgDisp(meindex, talkerindex, 7);
      } else if(select == WINDOW_BUTTONTYPE_NO) {
        NPC_MsgDisp(meindex, talkerindex, 1);
      }
      break;

    case CHAR_WINDOWTYPE_WINDOWEVENT_REQMAINMSG:
      if(select == WINDOW_BUTTONTYPE_YES) {
        CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD, 0);
        NPC_MsgDisp(meindex, talkerindex, 2);
      } else if(select == WINDOW_BUTTONTYPE_NO) {

      } else if(select == WINDOW_BUTTONTYPE_NEXT) {
        CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD, CHAR_getWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD) + 1);
        NPC_MsgDisp(meindex, talkerindex, 55);
      } else if(select == WINDOW_BUTTONTYPE_PREV) {
        CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD, CHAR_getWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD) - 1);
        NPC_MsgDisp(meindex, talkerindex, 55);
      }
      break;

    case CHAR_WINDOWTYPE_WINDOWEVENT_ACCMAINMSG:
      if(select == WINDOW_BUTTONTYPE_YES) {
        CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD, 0);
#ifdef _NEWEVENT
        NPC_MsgDisp(meindex, talkerindex, 81);
#else
        NPC_MsgDisp( meindex, talkerindex, 8);
#endif
      } else if(select == WINDOW_BUTTONTYPE_NO) {
      } else if(select == WINDOW_BUTTONTYPE_NEXT) {
        CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD,
                        CHAR_getWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD) + 1);
        NPC_MsgDisp(meindex, talkerindex, 66);
      } else if(select == WINDOW_BUTTONTYPE_PREV) {
        CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD,
                        CHAR_getWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD) - 1);
        NPC_MsgDisp(meindex, talkerindex, 66);
      }
      break;

#ifdef _NEWEVENT
    case CHAR_WINDOWTYPE_WINDOWEVENT_ACCTHANKNEW:
      if(select == WINDOW_BUTTONTYPE_OK) {
        CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD, 0);
        NPC_MsgDisp(meindex, talkerindex, 8);
      } else if(select == WINDOW_BUTTONTYPE_NEXT) {
        CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD, CHAR_getWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD) + 1);
        NPC_MsgDisp(meindex, talkerindex, 81);
      } else if(select == WINDOW_BUTTONTYPE_PREV) {
        CHAR_setWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD, CHAR_getWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD) - 1);
        NPC_MsgDisp(meindex, talkerindex, 81);
      }
      break;
#endif
    case CHAR_WINDOWTYPE_WINDOWPETSKILLSHOP:
      if(CHAR_getWorkInt(talkerindex, CHAR_WORKSHOPRELEVANTTRD) == 0) {
        NPC_EventPetSkill(meindex, talkerindex, data);
        NPC_MsgDisp(meindex, talkerindex, 25);
      } else {
        NPC_EventPetSkill(meindex, talkerindex, data);
        NPC_MsgDisp(meindex, talkerindex, 88);
      }
      break;
  }
}

int NPC_ExChangeManEventCheck(int meindex, int talker, char *buff1) {
  char buff2[512];
  char buff3[128];
  char buf[512];
  int i = 1, j = 1;
  int loop = 0;

  NPC_Util_GetStrFromStrWithDelim(buff1, "EVENT", buf, sizeof(buf));

  while(getStringFromIndexWithDelim(buf, ",", i, buff2, sizeof(buff2)) != FALSE) {
    i++;
    if(strstr(buff2, "&") != NULL) {
      j = 1;
      loop = 0;
      while(getStringFromIndexWithDelim(buff2, "&", j, buff3, sizeof(buff3)) != FALSE) {
        j++;
        if(NPC_EventBigSmallCheck(meindex, talker, buff3) == FALSE) {
          loop = 1;
          break;
        }
      }

      if(loop == 0) {
        i--;
        return i;
      }
    } else {
      if(NPC_EventBigSmallCheck(meindex, talker, buff2) == TRUE) {
        i--;
        return i;
      }
    }

  }

  return -1;

}

int NPC_EventBigSmallCheck(int meindex, int talker, char *buf) {

  char buff2[128];
  int kosuu;

  if(strstr(buf, "PET") != NULL) {
    if(strstr(buf, "EV") != NULL) {
      if(NPC_PetLvCheck(meindex, talker, buf, 1) != FALSE)
        return TRUE;
    } else {
      if(NPC_PetLvCheck(meindex, talker, buf, 0) != FALSE)
        return TRUE;
    }
    return FALSE;
  }

  if(strstr(buf, "<") != NULL) {
    getStringFromIndexWithDelim(buf, "<", 2, buff2, sizeof(buff2));
    kosuu = atoi(buff2);
    getStringFromIndexWithDelim(buf, "<", 1, buff2, sizeof(buff2));

    if(NPC_EventFreeIfCheck(meindex, talker, buff2, kosuu, 1) == TRUE) {
      return TRUE;
    }

  } else if(strstr(buf, ">") != NULL) {
    getStringFromIndexWithDelim(buf, ">", 2, buff2, sizeof(buff2));
    kosuu = atoi(buff2);
    getStringFromIndexWithDelim(buf, ">", 1, buff2, sizeof(buff2));

    if(NPC_EventFreeIfCheck(meindex, talker, buff2, kosuu, 2) == TRUE) {
      return TRUE;
    }

  } else if(strstr(buf, "!=") != NULL) {
    getStringFromIndexWithDelim(buf, "!=", 2, buff2, sizeof(buff2));
    kosuu = atoi(buff2);
    getStringFromIndexWithDelim(buf, "!=", 1, buff2, sizeof(buff2));
    if(NPC_EventFreeIfCheck(meindex, talker, buff2, kosuu, 3) == TRUE) {
      return TRUE;
    }

  } else if(strstr(buf, "=") != NULL) {
    getStringFromIndexWithDelim(buf, "=", 2, buff2, sizeof(buff2));
    kosuu = atoi(buff2);
    getStringFromIndexWithDelim(buf, "=", 1, buff2, sizeof(buff2));

    if(strstr(buf, "*") != NULL) {
      if(NPC_EventReduce(meindex, talker, buf) == TRUE) {
        return TRUE;
      }
    } else if(NPC_EventFreeIfCheck(meindex, talker, buff2, kosuu, 0) == TRUE) {
      return TRUE;
    }
  }

  return FALSE;

}

int NPC_EventFreeIfCheck(int meindex, int talker, char *buf, int kosuu, int flg) {

  if(strcmp(buf, "LV") == 0) {
    if(NPC_EventLevelCheck(meindex, talker, kosuu, flg) == TRUE) {
      return TRUE;
    }
  }

  if(strcmp(buf, "ITEM") == 0) {
    if(NPC_EventItemCheck(meindex, talker, kosuu, flg) == TRUE) {
      return TRUE;
    }
  }

  if(strcmp(buf, "ENDEV") == 0) {
    if(NPC_ENDEventNoCheck(meindex, talker, kosuu, flg) == TRUE) {
      return TRUE;
    }
  }

  if(strcmp(buf, "NOWEV") == 0) {
    if(NPC_NOWEventNoCheck(meindex, talker, kosuu, flg) == TRUE) {
      return TRUE;
    }
  }

  if(strcmp(buf, "SP") == 0) {
    if(NPC_SavePointCheck(meindex, talker, kosuu, flg) == TRUE) {
      return TRUE;
    }
  }

  if(strcmp(buf, "TIME") == 0) {
    if(NPC_TiemCheck(meindex, talker, kosuu, flg) == TRUE) {
      return TRUE;
    }
  }

  if(strcmp(buf, "IMAGE") == 0) {
    if(NPC_ImageCheck(meindex, talker, kosuu, flg) == TRUE) {
      return TRUE;
    }
  }

#ifdef _ADD_reITEM
  if(strstr(buf, "reITEM") != NULL) {
    int i, count = 0, itemindex = -1;
    for(i = CHAR_STARTITEMARRAY; i < CHAR_MAXITEMHAVE; i++) {
      itemindex = CHAR_getItemIndex(talker, i);
      if(!ITEM_CHECKINDEX(itemindex))
        ++count;
    }
    if(NPC_EventBigSmallLastCheck(kosuu, count, flg) == TRUE)
      return TRUE;
  }
#endif

  return FALSE;

}

int NPC_PetLvCheck(int meindex, int talker, char *buf, int mode) {
  char argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
  char buff2[16];
  char buf3[8];
  int petno;
  int baseno;
  int petlevel = 0;
  int flg = 0;
  int mypetlevel = 0;
  int i = 0;
  int petindex;
  char name[512];
  int cnt = 0;
  int loop;


  getStringFromIndexWithDelim(buf, "-", 2, buff2, sizeof(buff2));
  if(strstr(buff2, "*") != NULL) {
    getStringFromIndexWithDelim(buff2, "*", 1, buf3, sizeof(buf3));
    petno = atoi(buf3);
    getStringFromIndexWithDelim(buff2, "*", 2, buf3, sizeof(buf3));
    loop = atoi(buf3);

  } else {
    petno = atoi(buff2);
    loop = 1;

  }

  for(i = 0; i < CHAR_MAXPETHAVE; i++) {
    if(loop == cnt) return TRUE;

    petindex = CHAR_getCharPet(talker, i);
    if(petindex == -1) continue;

    baseno = CHAR_getInt(petindex, CHAR_PETID);

    if((baseno == petno) && (CHAR_getInt(petindex, CHAR_ENDEVENT) == mode)) {
      mypetlevel = CHAR_getInt(petindex, CHAR_LV);
      getStringFromIndexWithDelim(buf, "-", 1, buff2, sizeof(buff2));

      if(strstr(buf, "<") != NULL) {
        flg = 1;
        getStringFromIndexWithDelim(buff2, "<", 2, buf3, sizeof(buf3));
      } else if(strstr(buf, ">") != NULL) {
        getStringFromIndexWithDelim(buff2, ">", 2, buf3, sizeof(buf3));
        flg = 2;
      } else if(strstr(buf, "=") != NULL) {
        getStringFromIndexWithDelim(buff2, "=", 2, buf3, sizeof(buf3));
        flg = 0;
      }

      petlevel = atoi(buf3);

      if(NPC_EventBigSmallLastCheck(petlevel, mypetlevel, flg) == TRUE) {
        if(CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANTSEC) == 1) {
          char *usename;

          if(NPC_Util_GetArgStr(meindex, argstr, sizeof(argstr)) == NULL) {
            print("PetLevel:GetArgStrErr");
            return FALSE;
          }

          usename = CHAR_getUseName(petindex);
          NPC_Util_GetStrFromStrWithDelim(argstr, "Pet_Name", name, sizeof(name));

          if(strcmp(name, usename) == 0) {
            cnt++;
            continue;
          }
        } else {
          CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTSEC, 0);
          cnt++;
          continue;
        }
      }
    }
  }

  if(loop == cnt) return TRUE;
  if(i == CHAR_MAXPETHAVE) return FALSE;

  return FALSE;
}

int NPC_PetLvCheckType2(int petindex, int meindex, int talker, char *buf, int mode) {
  char argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
  char buff2[16];
  char buf3[8];
  int petno;
  int baseno;
  int petlevel = 0;
  int flg = 0;
  int mypetlevel = 0;
  char name[512];

  getStringFromIndexWithDelim(buf, "-", 2, buff2, sizeof(buff2));
  if(strstr(buff2, "*") != NULL) {
    getStringFromIndexWithDelim(buff2, "*", 1, buf3, sizeof(buf3));
    petno = atoi(buf3);
  } else {
    petno = atoi(buff2);
  }

  baseno = CHAR_getInt(petindex, CHAR_PETID);

  if((baseno == petno) && (CHAR_getInt(petindex, CHAR_ENDEVENT) == mode)) {
    mypetlevel = CHAR_getInt(petindex, CHAR_LV);
    getStringFromIndexWithDelim(buf, "-", 1, buff2, sizeof(buff2));

    if(strstr(buf, "<") != NULL) {
      flg = 1;
      getStringFromIndexWithDelim(buff2, "<", 2,
                                  buf3, sizeof(buf3));
    } else if(strstr(buf, ">") != NULL) {
      getStringFromIndexWithDelim(buff2, ">", 2, buf3, sizeof(buf3));
      flg = 2;
    } else if(strstr(buf, "=") != NULL) {
      getStringFromIndexWithDelim(buff2, "=", 2, buf3, sizeof(buf3));
      flg = 0;
    }

    petlevel = atoi(buf3);

    if(NPC_EventBigSmallLastCheck(petlevel, mypetlevel, flg) == TRUE) {
      if(CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANTSEC) == 1) {
        char *usename;

        if(NPC_Util_GetArgStr(meindex, argstr, sizeof(argstr)) == NULL) {
          print("PetLevel:GetArgStrErr");
          return FALSE;
        }

        usename = CHAR_getUseName(petindex);
        NPC_Util_GetStrFromStrWithDelim(argstr, "Pet_Name", name, sizeof(name));

        if(strcmp(name, usename) == 0) {
          return TRUE;
        }
      } else {
        CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTSEC, 0);
        return TRUE;
      }
    }
  }

  return FALSE;

}

int NPC_SavePointCheck(int meindex, int talker, int shiftbit, int flg) {
  int point;

  point = CHAR_getInt(talker, CHAR_SAVEPOINT);

  if((point & (1 << shiftbit)) == (1 << shiftbit)) {
    if(flg == 3) return FALSE;
    return TRUE;
  }

  if(flg == 3) return TRUE;
  return FALSE;
}

int NPC_ImageCheck(int meindex, int talker, int kosuu, int flg) {
  int image;

  image = CHAR_getInt(talker, CHAR_IMAGETYPE);

  if(NPC_EventBigSmallLastCheck(image, kosuu, flg) == TRUE) {
    return TRUE;
  }
  return FALSE;

}

int NPC_TiemCheck(int meindex, int talker, int time, int flg) {
  LSTIME nowlstime;
  int now;

  RealTimeToLSTime(NowTime.tv_sec, &nowlstime);
  now = getLSTime(&nowlstime);

  if(NPC_EventBigSmallLastCheck(time, now, flg) == TRUE) {
    return TRUE;
  }
  return FALSE;

}

int NPC_EventItemCheck(int meindex, int talker, int itemNo, int flg) {
  //Change fix 不检查穿戴在身上的道具
  for(int i = CHAR_STARTITEMARRAY; i < CHAR_MAXITEMHAVE; i++) {

    int itemindex = CHAR_getItemIndex(talker, i);
    if(ITEM_CHECKINDEX(itemindex)) {
      int id = ITEM_getInt(itemindex, ITEM_ID);

      if(NPC_EventBigSmallLastCheck(itemNo, id, flg) == TRUE) {
        if(flg == 0) return TRUE;
        continue;
      } else {
        if(flg == 0) continue;
        return FALSE;
      }
    }
  }

  if(flg == 3) return TRUE;

  return FALSE;

}

int NPC_EventLevelCheck(int meindex, int talker, int level, int flg) {

  int mylevel = CHAR_getInt(talker, CHAR_LV);

  if(NPC_EventBigSmallLastCheck(level, mylevel, flg) == TRUE) {
    if(flg == 3) return FALSE;
    return TRUE;
  }

  if(flg == 3) return TRUE;
  return FALSE;

}

int NPC_ENDEventNoCheck(int meindex, int talker, int shiftbit, int flg) {
  if(NPC_EventCheckFlg(talker, shiftbit) == TRUE) {
    if(flg == 3) return FALSE;
    return TRUE;
  }

  if(flg == 3) return TRUE;
  return FALSE;
}


int NPC_NOWEventNoCheck(int meindex, int talker, int shiftbit, int flg) {
  if(NPC_NowEventCheckFlg(talker, shiftbit) == TRUE) {
    if(flg == 3) return TRUE;
    return TRUE;
  }

  if(flg == 3) return TRUE;
  return FALSE;
}

int NPC_EventBigSmallLastCheck(int point1, int mypoint, int flg) {

  if(flg == 0) {
    if(point1 == mypoint) {
      return TRUE;
    }
  } else if(flg == 1) {
    if(mypoint < point1) {
      return TRUE;
    }
  } else if(flg == 2) {
    if(mypoint > point1) {
      return TRUE;
    }
  } else if(flg == 3) {
    if(point1 != mypoint) {
      return TRUE;
    }
  }
  return FALSE;
}

void NPC_MsgDisp(int meindex, int talker, int num) {
  char argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
#ifdef _NEWEVENT
  char buf[4096];
  char token2[4096];
  char buf2[4096];
  char token[4096];
  char tmp[4096];
#else
  char buf[1024*2];
	char token2[50*14];
	char buf2[512];
	char token[512];
	char tmp[32];
#endif
  int i = 1;
  int work = 0;
  int EvNo = 0;
  int fd = getfdFromCharaIndex(talker);
  int buttontype = WINDOW_BUTTONTYPE_OK;
  int windowtype = CHAR_WINDOWTYPE_WINDOWEVENT_STARTMSG;
  int evch;


  if(NPC_Util_GetArgStr(meindex, argstr, sizeof(argstr)) == NULL) {
    print("MsgDisp:GetArgStrErr");
    print("NPCName=%s\n", CHAR_getChar(meindex, CHAR_NAME));
    return;
  }
  if(num == 22 || num == 82 || num == 55 || num == 66) {
    int pwork;

    pwork = CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD);
    pwork = (pwork / 100) - 1;

    getStringFromIndexWithDelim(argstr, "EventEnd", pwork, buf, sizeof(buf));

  } else {
    while(getStringFromIndexWithDelim(argstr, "EventEnd", i, buf, sizeof(buf)) != FALSE) {
      i++;
      CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTSEC, 0);

      NPC_Util_GetStrFromStrWithDelim(buf, "EventNo", buf2, sizeof(buf2));
      if(strstr(buf2, "-1") != 0) {
        EvNo = -1;
      } else {
        EvNo = atoi(buf2);
      }
      EvNo = atoi(buf2);

      if(NPC_EventCheckFlg(talker, EvNo) == TRUE) continue;

      if(NPC_Util_GetStrFromStrWithDelim(buf, "Pet_Name", buf2, sizeof(buf2)) != NULL) {
        CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTSEC, 1);
      }

      if(NPC_Util_GetStrFromStrWithDelim(buf, "KeyWord", buf2, sizeof(buf2))
         != NULL) {
        if(CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANT) != i) continue;
      }

      evch = NPC_ExChangeManEventCheck(meindex, talker, buf);

      if(evch != -1) {

        //	if(NPC_ExChangeManEventCheck( meindex, talker, buf) == TRUE) {
        break;
      }
    }
  }

  //print(" NPC_MsgDisp:%d ", num);

  switch(num) {
    case 0:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "StopMsg", buf2, sizeof(buf2)) != NULL) {
        strcpysafe(token, sizeof(buf2), buf2);
        buttontype = WINDOW_BUTTONTYPE_YESNO;
        windowtype = CHAR_WINDOWTYPE_WINDOWEVENT_NOWEVENT;
      }
      break;

    case 1:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "NoStopMsg", buf2, sizeof(buf2)) != NULL) {
        strcpysafe(token, sizeof(buf2), buf2);

      }
      break;

    case 7:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "EndStopMsg", buf2, sizeof(buf2)) != NULL) {
        strcpysafe(token, sizeof(buf2), buf2);

        NPC_EventAdd(meindex, talker, 1);

        NPC_NowEventSetFlgCls(talker, EvNo);

        if(CHAR_getInt(talker, CHAR_CHARM) > 0) {
          CHAR_setInt(talker, CHAR_CHARM, CHAR_getInt(talker, CHAR_CHARM) - 1);
          CHAR_complianceParameter(talker);
          CHAR_send_P_StatusString(talker, CHAR_P_STRING_CHARM);
          NPC_CharmStatus(talker);
        }
      }
      break;

    case 2:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "ThanksMsg", buf2, sizeof(buf2)) != NULL) {
        strcpysafe(token, sizeof(buf2), buf2);
        if(NPC_EventAdd(meindex, talker, 0) != FALSE) {
          NPC_NowEventSetFlg(talker, EvNo);
        }
        else {
          return;
        }


        if(NPC_Util_GetStrFromStrWithDelim(buf, "EndSetFlg", buf2, sizeof(buf2)) != NULL) {
          char buf3[16];
          int k = 1;
          if(EvNo != -1) NPC_NowEventSetFlgCls(talker, EvNo);

          while(getStringFromIndexWithDelim(buf2, ",", k, buf3, sizeof(buf3)) != FALSE) {
            k++;
            NPC_EventSetFlg(talker, atoi(buf3));
          }
        }

        if(NPC_Util_GetStrFromStrWithDelim(buf, "CleanFlg", buf2, sizeof(buf2)) != NULL) {
          char buf3[16];
          int k = 1;

          k = 1;
          while(getStringFromIndexWithDelim(buf2, ",", k, buf3, sizeof(buf3)) != FALSE) {
            NPC_NowEndEventSetFlgCls(talker, atoi(buf3));
            k++;
          }
        }


      }
      CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD, 1);
      work = CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD);
      work = work + (i * 100);
      CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD, work);

      if(NPC_Util_GetStrFromStrWithDelim(buf, "NpcWarp", token2, sizeof(token2)) != NULL) {
        NPC_EventWarpNpc(meindex, token2);
      }

      if(strstr(buf, "ThanksMsg2") != NULL) {
        lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                         WINDOW_BUTTONTYPE_NEXT,
                         CHAR_WINDOWTYPE_WINDOWEVENT_REQTHANK,
                         CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                         token);
        return;
      }

      break;

    case 22:

      work = CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD);
      work = work % 100;

      if(work == 1) {
        if(NPC_Util_GetStrFromStrWithDelim(buf, "ThanksMsg", buf2, sizeof(buf2)) != NULL) {
          strcpysafe(token, sizeof(buf2), buf2);
        }

        if(strstr(buf, "ThanksMsg2") != NULL) {

          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_NEXT,
                           CHAR_WINDOWTYPE_WINDOWEVENT_REQTHANK,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        }

      } else {

        sprintf(tmp, "ThanksMsg%d", work);
        if(NPC_Util_GetStrFromStrWithDelim(buf, tmp, buf2, sizeof(buf2)) != NULL) {
          strcpysafe(token, sizeof(buf2), buf2);
        }

        work++;
        sprintf(tmp, "ThanksMsg%d", work);


        if(strstr(buf, tmp) != NULL) {

          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_NEXT,
                           CHAR_WINDOWTYPE_WINDOWEVENT_REQTHANK,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        } else {
          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_OK,
                           CHAR_WINDOWTYPE_WINDOWEVENT_REQTHANK,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        }
      }
      break;

    case 25:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "ThanksMsg", buf2, sizeof(buf2)) != NULL) {
        strcpysafe(token, sizeof(buf2), buf2);
        if(NPC_EventAdd(meindex, talker, 2) != FALSE) {
          NPC_NowEventSetFlg(talker, EvNo);
        }
      }
      break;


    case 3:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "NomalMsg", buf2, sizeof(buf2)) != NULL) {
        strcpysafe(token, sizeof(buf2), buf2);
      }
      break;

    case 4:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "ItemFullMsg", buf2, sizeof(buf2)) != NULL) {
        strcpysafe(token, sizeof(buf2), buf2);
      }
      break;

    case 5:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "RequestMsg", buf2, sizeof(buf2)) != NULL) {
        if(strstr(buf2, "%8d") != NULL) {
          char buf3[64];
          int cost;

          NPC_Util_GetStrFromStrWithDelim(buf, "DelStone", buf3, sizeof(buf3));
          cost = NPC_EventGetCost(meindex, talker, buf3);

          sprintf(token, buf2, cost);

        } else {
          strcpysafe(token, sizeof(buf2), buf2);
        }
        buttontype = WINDOW_BUTTONTYPE_YESNO;
        windowtype = CHAR_WINDOWTYPE_WINDOWEVENT_REQMAINMSG;
      }

      CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD, 1);
      work = CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD);
      work = work + (i * 100);
      CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD, work);

      if(strstr(buf, "RequestMsg2") != NULL) {
        lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                         WINDOW_BUTTONTYPE_NEXT,
                         CHAR_WINDOWTYPE_WINDOWEVENT_REQMAINMSG,
                         CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                         token);
        return;
      }
      break;

    case 55:

      work = CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD);
      work = work % 100;

      if(work == 1) {
        if(NPC_Util_GetStrFromStrWithDelim(buf, "RequestMsg", buf2, sizeof(buf2)) != NULL) {
          strcpysafe(token, sizeof(buf2), buf2);
        }

        if(strstr(buf, "RequestMsg2") != NULL) {
          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_NEXT,
                           CHAR_WINDOWTYPE_WINDOWEVENT_REQMAINMSG,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        }
      } else {

        sprintf(tmp, "RequestMsg%d", work);
        if(NPC_Util_GetStrFromStrWithDelim(buf, tmp, buf2, sizeof(buf2)) != NULL) {
          strcpysafe(token, sizeof(buf2), buf2);
        }
        work++;
        sprintf(tmp, "RequestMsg%d", work);
        if(strstr(buf, tmp) != NULL) {

          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_NEXT,
                           CHAR_WINDOWTYPE_WINDOWEVENT_REQMAINMSG,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        } else {
          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_YESNO,
                           CHAR_WINDOWTYPE_WINDOWEVENT_REQMAINMSG,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        }
      }
      break;


    case 6:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "AcceptMsg", buf2, sizeof(buf2)) != NULL) {
        if(strstr(buf2, "%8d") != NULL) {
          char buf3[64];
          int cost;

          NPC_Util_GetStrFromStrWithDelim(buf, "DelStone", buf3, sizeof(buf3));
          cost = NPC_EventGetCost(meindex, talker, buf3);

          sprintf(token, buf2, cost);
        } else {
          strcpysafe(token, sizeof(buf2), buf2);
        }
        buttontype = WINDOW_BUTTONTYPE_YESNO;
        windowtype = CHAR_WINDOWTYPE_WINDOWEVENT_ACCMAINMSG;
      }

      CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD, 1);
      work = CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD);
      work = work + (i * 100);
      CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD, work);

      if(strstr(buf, "AcceptMsg2") != NULL) {
        lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                         WINDOW_BUTTONTYPE_NEXT,
                         CHAR_WINDOWTYPE_WINDOWEVENT_ACCMAINMSG,
                         CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                         token);
        return;
      }
      break;


    case 66:
      work = CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD);
      work = work % 100;

      if(work == 1) {
        if(NPC_Util_GetStrFromStrWithDelim(buf, "AcceptMsg", buf2, sizeof(buf2)) != NULL) {
          strcpysafe(token, sizeof(buf2), buf2);
        }

        if(strstr(buf, "AcceptMsg2") != NULL) {
          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_NEXT,
                           CHAR_WINDOWTYPE_WINDOWEVENT_ACCMAINMSG,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        }
      } else {

        sprintf(tmp, "AcceptMsg%d", work);
        if(NPC_Util_GetStrFromStrWithDelim(buf, tmp, buf2, sizeof(buf2)) != NULL) {
          strcpysafe(token, sizeof(buf2), buf2);
        }
        work++;
        sprintf(tmp, "AcceptMsg%d", work);
        if(strstr(buf, tmp) != NULL) {

          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_NEXT,
                           CHAR_WINDOWTYPE_WINDOWEVENT_ACCMAINMSG,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        } else {
          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_YESNO,
                           CHAR_WINDOWTYPE_WINDOWEVENT_ACCMAINMSG,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        }
      }
      break;

    case 8:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "ThanksMsg", buf2, sizeof(buf2)) != NULL) {
        strcpysafe(token, sizeof(buf2), buf2);
        if(NPC_AcceptDel(meindex, talker, 0) == FALSE) {
          return;
        }

        if(NPC_Util_GetStrFromStrWithDelim(buf, "EndSetFlg", buf2, sizeof(buf2)) != NULL) {
          char buf3[16];
          int k = 1;
          if(EvNo != -1)
            NPC_NowEventSetFlgCls(talker, EvNo);

          while(getStringFromIndexWithDelim(buf2, ",", k, buf3, sizeof(buf3)) != FALSE) {
            k++;
            NPC_EventSetFlg(talker, atoi(buf3));
          }
        }

        if(NPC_Util_GetStrFromStrWithDelim(buf, "Charm", buf2, sizeof(buf2)) != NULL) {
          if(CHAR_getInt(talker, CHAR_CHARM) < 100 && EvNo > 0) {
            if(CHAR_getInt(talker, CHAR_CHARM) + atoi(buf2) > 100) {
              CHAR_setInt(talker, CHAR_CHARM, 100);
            } else {
              CHAR_setInt(talker, CHAR_CHARM, CHAR_getInt(talker, CHAR_CHARM) + atoi(buf2));
            }

            CHAR_complianceParameter(talker);
            CHAR_send_P_StatusString(talker, CHAR_P_STRING_CHARM);
            NPC_CharmStatus(talker);
          }
        }

        if(NPC_Util_GetStrFromStrWithDelim(buf, "CleanFlg", buf2, sizeof(buf2)) != NULL) {
          char buf3[16];
          int k = 1;
          while(getStringFromIndexWithDelim(buf2, ",", k, buf3, sizeof(buf3)) != FALSE) {
            NPC_NowEndEventSetFlgCls(talker, atoi(buf3));
            k++;
          }
        }
      }
      CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD, 1);
      work = CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD);
      work = work + (i * 100);
      CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD, work);

      if(NPC_Util_GetStrFromStrWithDelim(buf, "NpcWarp", token2, sizeof(token2)) != NULL) {
        NPC_EventWarpNpc(meindex, token2);
      }
#ifdef _NEWEVENT
#else
      if(strstr( buf, "ThanksMsg2") != NULL){
					lssproto_WN_send( fd, WINDOW_MESSAGETYPE_MESSAGE,
								WINDOW_BUTTONTYPE_NEXT,
								CHAR_WINDOWTYPE_WINDOWEVENT_ACCTHANK,
								CHAR_getWorkInt( meindex, CHAR_WORKOBJINDEX),
								token);
					return;
				}
#endif
      break;

#ifdef _NEWEVENT
    case 81:
      work = CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD);
      work = work % 100;
      sprintf(tmp, "ThanksMsg%d", work + 1);
      if(work == 0 && strstr(buf, tmp) == NULL) {
        if(NPC_Util_GetStrFromStrWithDelim(buf, "ThanksMsg", buf2, sizeof(buf2)) != NULL)
          strcpysafe(token, sizeof(buf2), buf2);
        if(strstr(buf, "ThanksMsg2") != NULL)
          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_NEXT,
                           CHAR_WINDOWTYPE_WINDOWEVENT_ACCTHANKNEW,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
        else
          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_OK,
                           CHAR_WINDOWTYPE_WINDOWEVENT_ACCTHANKNEW,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
        return;
      }
      else {
        if(NPC_Util_GetStrFromStrWithDelim(buf, tmp, buf2, sizeof(buf2)) != NULL)
          strcpysafe(token, sizeof(buf2), buf2);
        work++;
        sprintf(tmp, "ThanksMsg%d", work + 1);

        if(strstr(buf, tmp) != NULL) {
          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_NEXT,
                           CHAR_WINDOWTYPE_WINDOWEVENT_ACCTHANKNEW,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        } else {
          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_OK,
                           CHAR_WINDOWTYPE_WINDOWEVENT_ACCTHANKNEW,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        }
      }

      break;
#endif

    case 82:
      work = CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD);
      work = work % 100;

      if(work == 1) {
        if(NPC_Util_GetStrFromStrWithDelim(buf, "ThanksMsg", buf2, sizeof(buf2))
           != NULL) {
          strcpysafe(token, sizeof(buf2), buf2);
        }

        if(strstr(buf, "ThanksMsg2") != NULL) {
          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_NEXT,
                           CHAR_WINDOWTYPE_WINDOWEVENT_ACCTHANK,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        }
      } else {
        sprintf(tmp, "ThanksMsg%d", work);
        if(NPC_Util_GetStrFromStrWithDelim(buf, tmp, buf2, sizeof(buf2)) != NULL) {
          strcpysafe(token, sizeof(buf2), buf2);
        }
        work++;
        sprintf(tmp, "ThanksMsg%d", work);

        if(strstr(buf, tmp) != NULL) {
          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_NEXT,
                           CHAR_WINDOWTYPE_WINDOWEVENT_ACCTHANK,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        } else {
          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_OK,
                           CHAR_WINDOWTYPE_WINDOWEVENT_ACCTHANK,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        }
      }
      break;

    case 88:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "ThanksMsg", buf2, sizeof(buf2)) != NULL) {
        strcpysafe(token, sizeof(buf2), buf2);
        if(NPC_AcceptDel(meindex, talker, 1) == FALSE) {
          return;
        }

        if(NPC_Util_GetStrFromStrWithDelim(buf, "EndSetFlg", buf2, sizeof(buf2)) != NULL) {
          char buf3[16];
          int k = 1;

          if(EvNo != -1)
            NPC_NowEventSetFlgCls(talker, EvNo);

          while(getStringFromIndexWithDelim(buf2, ",", k, buf3, sizeof(buf3)) != FALSE) {
            k++;
            NPC_EventSetFlg(talker, atoi(buf3));
          }
        }

        if(NPC_Util_GetStrFromStrWithDelim(buf, "Charm", buf2, sizeof(buf2)) != NULL) {
          if(CHAR_getInt(talker, CHAR_CHARM) < 100 && EvNo > 0) {
            if(CHAR_getInt(talker, CHAR_CHARM) + atoi(buf2) > 100) {
              CHAR_setInt(talker, CHAR_CHARM, 100);
            } else {
              CHAR_setInt(talker, CHAR_CHARM, CHAR_getInt(talker, CHAR_CHARM) + atoi(buf2));
            }
            CHAR_complianceParameter(talker);
            CHAR_send_P_StatusString(talker, CHAR_P_STRING_CHARM);
            NPC_CharmStatus(talker);
          }
        }
      }

      break;


    case 9:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "NomalWindowMsg", buf2, sizeof(buf2)) != NULL) {
        strcpysafe(token, sizeof(buf2), buf2);
        if(EvNo != -1) NPC_NowEventSetFlg(talker, EvNo);
      }
#ifdef _NEWEVENT
      CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD, 1);
      work = CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD);
      work = work + (i * 100);
      CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD, work);

      if(strstr(buf, "NomalWindowMsg2") != NULL) {
        lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                         WINDOW_BUTTONTYPE_NEXT,
                         CHAR_WINDOWTYPE_WINDOWEVENT_STARTMSG,
                         CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                         token);
        return;
      }
#endif
      break;

#ifdef _NEWEVENT
    case 99:
      work = CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD);
      work = work % 100;

      if(work == 1) {
        if(NPC_Util_GetStrFromStrWithDelim(buf, "NomalWindowMsg1", buf2, sizeof(buf2)) != NULL)
          strcpysafe(token, sizeof(buf2), buf2);

        if(strstr(buf, "NomalWindowMsg2") != NULL) {
          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_NEXT,
                           CHAR_WINDOWTYPE_WINDOWEVENT_STARTMSG,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        }
      } else {

        sprintf(tmp, "NomalWindowMsg%d", work);
        if(NPC_Util_GetStrFromStrWithDelim(buf, tmp,
                                           buf2, sizeof(buf2))
           != NULL) {
          strcpysafe(token, sizeof(buf2), buf2);
        }
        work++;
        sprintf(tmp, "NomalWindowMsg%d", work);
        if(strstr(buf, tmp) != NULL) {
          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_NEXT,
                           CHAR_WINDOWTYPE_WINDOWEVENT_STARTMSG,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        } else {
          int fd = getfdFromCharaIndex(talker);
          char token2[14 * 50];
          if(NPC_AcceptDel(meindex, talker, 0) == FALSE)
            return;

          if(EvNo != -1) NPC_NowEventSetFlg(talker, EvNo);

          if(NPC_Util_GetStrFromStrWithDelim(buf, "NpcWarp", token2, sizeof(token2)) != NULL) {
            NPC_EventWarpNpc(meindex, token2);
          }

          if(NPC_Util_GetStrFromStrWithDelim(buf, "EndSetFlg", buf2, sizeof(buf2)) != NULL) {
            char buf3[16];
            int k = 1;

            if(EvNo != -1) NPC_NowEventSetFlgCls(talker, EvNo);

            while(getStringFromIndexWithDelim(buf2, ",", k, buf3, sizeof(buf3)) != FALSE) {
              k++;
              NPC_EventSetFlg(talker, atoi(buf3));
            }
          }
          if(NPC_Util_GetStrFromStrWithDelim(buf, "CleanFlg", buf2, sizeof(buf2)) != NULL) {
            char buf3[16];
            int k = 1;
            while(getStringFromIndexWithDelim(buf2, ",", k, buf3, sizeof(buf3)) != FALSE) {
              NPC_NowEndEventSetFlgCls(talker, atoi(buf3));
              k++;
            }
          }
          lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                           WINDOW_BUTTONTYPE_YES,
                           CHAR_WINDOWTYPE_WINDOWEVENT_STARTMSG,
                           CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                           token);
          return;
        }
      }
      break;
#endif
    case 10:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "PetFullMsg", buf2, sizeof(buf2)) != NULL) {
        strcpysafe(token, sizeof(buf2), buf2);
        print(" PetFullMsg:%s ", token);
      }
      else {
        print(" PetFullMsg_Error:%d ", __LINE__);
      }
      break;

    case 11:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "CleanMainMsg", buf2, sizeof(buf2)) != NULL) {
        strcpysafe(token, sizeof(buf2), buf2);
        buttontype = WINDOW_BUTTONTYPE_YESNO;
        windowtype = CHAR_WINDOWTYPE_WINDOWEVENT_CLEANMSG;
      }
      break;
    case 12:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "CleanFlgMsg", buf2, sizeof(buf2)) != NULL) {
        char buf3[64];
        int loop = 1;
        strcpysafe(token, sizeof(buf2), buf2);
        NPC_Util_GetStrFromStrWithDelim(buf, "CleanFlg", buf2, sizeof(buf2));
        while(getStringFromIndexWithDelim(buf2, ",", loop, buf3, sizeof(buf3)) != FALSE) {
          NPC_NowEndEventSetFlgCls(talker, atoi(buf3));
          loop++;
        }
      }
      break;

    case 13:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "StoneFullMsg", buf2, sizeof(buf2))
         != NULL) {
        strcpysafe(token, sizeof(buf2), buf2);
      }
      break;

    case 14:
      if(NPC_Util_GetStrFromStrWithDelim(buf, "StoneLessMsg", buf2, sizeof(buf2)) != NULL) {
        strcpysafe(token, sizeof(buf2), buf2);
      }
      break;
  }

#ifdef _NEWEVENT
  if(num != 8)
#endif
    lssproto_WN_send(fd, WINDOW_MESSAGETYPE_MESSAGE,
                     buttontype,
                     windowtype,
                     CHAR_getWorkInt(meindex, CHAR_WORKOBJINDEX),
                     token);

}

int NPC_EventAdd(int meindex, int talker, int mode) {

  char buf[64];
  char buff2[128];
  int j = 1, i = 0;
  int kosuucnt = 0;
  int itemindex;
  char buff[1024 * 2];
  int rand_j = 0;
  int rand_flg = 0;
  int rand_cnt = 0;
  int evcnt;
  int b_flg = 0;

  evcnt = NPC_EventFile(meindex, talker, buff);

  if(evcnt == -1) return FALSE;

//	if(NPC_EventFile( meindex, talker, buff) == FALSE) return FALSE;

  if(NPC_ItemFullCheck(meindex, talker, buff, mode, evcnt) == FALSE) {
    NPC_MsgDisp(meindex, talker, 4);
    return FALSE;
  }

  if(NPC_Util_GetStrFromStrWithDelim(buff, "DelStone", buff2, sizeof(buff2))
     != NULL) {
    int stone;

    stone = NPC_EventGetCost(meindex, talker, buff2);

    if((CHAR_getInt(talker, CHAR_GOLD) - stone) < 0) {
      NPC_MsgDisp(meindex, talker, 14);
      return FALSE;
    }
  }


  if((NPC_Util_GetStrFromStrWithDelim(buff, "pet_skill", buff2, sizeof(buff2))
      != NULL) && mode == 0) {
    if(mode == 0) {
      NPC_PetSkillMakeStr(meindex, talker, 1);
      return TRUE;
    }
  }


  if(mode == 2)
    mode = 0;

  if(NPC_Util_GetStrFromStrWithDelim(buff, "GetPet", buff2, sizeof(buff2)) != NULL) {
    if(mode == 0) {
      if(NPC_EventAddPet(meindex, talker, buff2, 0) == FALSE) {
        NPC_MsgDisp(meindex, talker, 10);
        return FALSE;
      }
    } else if(mode == 1) {

    }
  }

  // Robin add 从NPC取宠物蛋
  if(NPC_Util_GetStrFromStrWithDelim(buff, "GetEgg", buff2, sizeof(buff2))
     != NULL) {
    if(mode == 0) {
      if(NPC_EventAddEgg(meindex, talker, buff2, 0) == FALSE) {
        print(" AddEgg_Error:%d ", __LINE__);
        NPC_MsgDisp(meindex, talker, 10);
        return FALSE;
      }
    } else if(mode == 1) {

    }
  }

  if(NPC_Util_GetStrFromStrWithDelim(buff, "DelItem", buff2, sizeof(buff2)) != NULL) {
    if(strstr(buff2, "EVDEL") != NULL) {
      char work[256];
      char nbuf[256];

      NPC_Util_GetStrFromStrWithDelim(buf, "EVENT", buff2, sizeof(buff2));
      getStringFromIndexWithDelim(buff2, ",", evcnt, work, sizeof(work));

      if(strstr(buff, "Break") != NULL) {
        b_flg = 1;
      } else {
        b_flg = 0;
      }

      if(NPC_Util_GetStrFromStrWithDelim(buff, "NotDel", nbuf, sizeof(nbuf)) != NULL) {
        NPC_EventDelItemEVDEL(meindex, talker, work, nbuf, b_flg);
      } else {
        NPC_EventDelItemEVDEL(meindex, talker, work, "-1", b_flg);
      }

    } else {
      if(strstr(buff, "Break") != NULL) {
        b_flg = 1;
      } else {
        b_flg = 0;
      }

      NPC_EventDelItem(meindex, talker, buff2, b_flg);
    }
  }

  if(NPC_Util_GetStrFromStrWithDelim(buff, "DelStone", buff2, sizeof(buff2)) != NULL) {
    char token[128];
    int stone = NPC_EventGetCost(meindex, talker, buff2);

    CHAR_setInt(talker, CHAR_GOLD, CHAR_getInt(talker, CHAR_GOLD) - stone);

    CHAR_send_P_StatusString(talker, CHAR_P_STRING_GOLD);
    sprintf(token, "付出%d的stone。", stone);
    CHAR_talkToCli(talker, -1, token, CHAR_COLORWHITE);
  }


  if(NPC_Util_GetStrFromStrWithDelim(buff, "GetRandItem", buf, sizeof(buf)) != NULL) {
    j = 1;
    while(getStringFromIndexWithDelim(buf, ",", j, buff2, sizeof(buff2)) != FALSE) {
      j++;
      rand_j++;
    }
    rand_cnt = 1;
  }


  if(NPC_Util_GetStrFromStrWithDelim(buff, "GetItem", buf, sizeof(buf)) != NULL) {
    if(mode == 0) {
      j = 1;
      while(getStringFromIndexWithDelim(buf, ",", j, buff2, sizeof(buff2)) != FALSE) {
        j++;
      }

      j--;
      for(i = CHAR_STARTITEMARRAY; i < CHAR_MAXITEMHAVE; i++) {
        itemindex = CHAR_getItemIndex(talker, i);
        if(!ITEM_CHECKINDEX(itemindex)) {
          kosuucnt++;
        }
      }
      j = j + rand_cnt;
      if(kosuucnt < j) {
        NPC_MsgDisp(meindex, talker, 4);
        return FALSE;

      } else {
        if(NPC_Util_GetStrFromStrWithDelim(buff, "GetRandItem", buff2, sizeof(buff2)) != NULL) {
          rand_flg = 1;
          NPC_RandItemGet(meindex, talker, rand_j, buff2);
        }
        if(NPC_EventAddItem(meindex, talker, buf) == FALSE) return FALSE;
      }
    } else if(mode == 1) {
      if(strstr(buff, "Break") != NULL) {
        b_flg = 1;
      } else {
        b_flg = 0;
      }
      NPC_EventDelItem(meindex, talker, buf, b_flg);
    }
  }

  if((NPC_Util_GetStrFromStrWithDelim(buff, "GetRandItem", buf, sizeof(buf)) != NULL) && (rand_flg == 0) && mode == 0) {
    for(i = CHAR_STARTITEMARRAY; i < CHAR_MAXITEMHAVE; i++) {
      itemindex = CHAR_getItemIndex(talker, i);
      if(!ITEM_CHECKINDEX(itemindex)) {
        kosuucnt++;
      }
    }
    if(kosuucnt == 0) {
      NPC_MsgDisp(meindex, talker, 4);
      return FALSE;
    }


    NPC_RandItemGet(meindex, talker, rand_j, buf);
  }

#ifdef _EXCHANGEMAN_REQUEST_DELPET
  if(NPC_Util_GetStrFromStrWithDelim(buff, "DelPet", buff2, sizeof(buff2)) != NULL && mode == 0) {
    char buf4[32];
    char buf5[256];
    int i = 1;
    char work[256];
    int j = 1;

    if(strstr(buff2, "EVDEL") != NULL) {
      NPC_Util_GetStrFromStrWithDelim(buf, "EVENT", buf5, sizeof(buf5));
      getStringFromIndexWithDelim(buf5, ",", evcnt, buff2, sizeof(buff2));
      while(getStringFromIndexWithDelim(buff2, "&", j, work, sizeof(work)) != FALSE) {
        j++;
        if(strstr(work, "PET") != NULL) {
          if(strstr(work, "EV") != NULL) {
            if(NPC_PetLvCheck(meindex, talker, work, 1) == FALSE) return FALSE;
          } else {
            if(NPC_PetLvCheck(meindex, talker, work, 0) == FALSE) return FALSE;
          }
        }
      }
      j = 1;
      while(getStringFromIndexWithDelim(buff2, "&", j, work, sizeof(work)) != FALSE) {
        j++;
        if(strstr(work, "PET") == NULL) continue;

        if(strstr(work, "*") != NULL) {
          int cnt = 0;
          int petcnt = 0;
          int petindex;

          getStringFromIndexWithDelim(work, "*", 2, buf4, sizeof(buf4));
          cnt = atoi(buf4);

          for(i = 0; i < CHAR_MAXPETHAVE; i++) {
            petindex = CHAR_getCharPet(talker, i);

            if(petindex == -1) continue;

            if(strstr(work, "EV") != NULL) {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 1)
                 == FALSE) {
                continue;
              }
            } else {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 0) == FALSE) {
                continue;
              }
            }

            if(NPC_EventDelPet(meindex, talker, i) == FALSE) return FALSE;

            petcnt++;
            if(cnt == petcnt)
              break;

          }
        } else {
          for(i = 0; i < CHAR_MAXPETHAVE; i++) {
            int petindex = CHAR_getCharPet(talker, i);
            if(!CHAR_CHECKINDEX(petindex))
              continue;

            if(strstr(buff2, "EV") != NULL) {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 1) == FALSE) {
                continue;
              }
            } else {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 0) == FALSE) {
                continue;
              }
            }

            if(NPC_EventDelPet(meindex, talker, i) == FALSE) return FALSE;
          }
        }
      }

    } else {
      while(getStringFromIndexWithDelim(buff2, ",", j, work, sizeof(work)) != FALSE) {
        j++;
        if(strstr(work, "PET") != NULL) {
          if(strstr(work, "EV") != NULL) {
            if(NPC_PetLvCheck(meindex, talker, work, 1) == FALSE) return FALSE;
          } else {
            if(NPC_PetLvCheck(meindex, talker, work, 0) == FALSE) return FALSE;
          }
        }
      }
      j = 1;

      while(getStringFromIndexWithDelim(buff2, ",", j, work, sizeof(work)) != FALSE) {
        j++;
        if(strstr(work, "*") != NULL) {
          int cnt = 0;
          int petcnt = 0;
          int petindex;

          getStringFromIndexWithDelim(work, "*", 2, buf4, sizeof(buf4));
          cnt = atoi(buf4);

          for(i = 0; i < CHAR_MAXPETHAVE; i++) {
            petindex = CHAR_getCharPet(talker, i);

            if(petindex == -1) continue;

            if(strstr(work, "EV") != NULL) {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 1) == FALSE) {
                continue;
              }
            } else {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 0) == FALSE) {
                continue;
              }
            }

            if(NPC_EventDelPet(meindex, talker, i) == FALSE) return FALSE;

            petcnt++;
            if(cnt == petcnt) break;
          }
        } else {
          for(i = 0; i < CHAR_MAXPETHAVE; i++) {
            int petindex = CHAR_getCharPet(talker, i);

            if(!CHAR_CHECKINDEX(petindex)) continue;

            if(strstr(buff2, "EV") != NULL) {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 1) == FALSE) {
                continue;
              }
            } else {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 0) == FALSE) {
                continue;
              }
            }
            if(NPC_EventDelPet(meindex, talker, i) == FALSE) return FALSE;
          }
        }
      }
    }
  }
#endif
  return TRUE;

}

int NPC_RandItemGet(int meidex, int talker, int rand_j, char *buf) {
  char buff2[64];
  int randitem;
  int ret;
  int itemindex;
  char token[128];

  if(rand_j == 0) {
    print("Event:由於０的介入，出现错误。");
    return FALSE;
  }

  randitem = rand() % rand_j;
  if(randitem == 0) randitem = rand_j;

  getStringFromIndexWithDelim(buf, ",", randitem, buff2, sizeof(buff2));

  itemindex = ITEM_makeItemAndRegist(atoi(buff2));

  if(itemindex == -1) return FALSE;

  ret = CHAR_addItemSpecificItemIndex(talker, itemindex);
  if(ret < 0 || ret >= CHAR_MAXITEMHAVE) {
    print("npc_exchangeman.c: additem error itemindex[%d]\n", itemindex);
    ITEM_endExistItemsOne(itemindex);
    return FALSE;
  }

  if(itemindex != -1) {
    LogItem(
        CHAR_getChar(talker, CHAR_NAME),
        CHAR_getChar(talker, CHAR_CDKEY),
#ifdef _add_item_log_name  // WON ADD 在item的log中增加item名称
        itemindex,
#else
        ITEM_getInt( itemindex, ITEM_ID),
#endif
        "EventAddItem(任务需求所得到的道具)",
        CHAR_getInt(talker, CHAR_FLOOR),
        CHAR_getInt(talker, CHAR_X),
        CHAR_getInt(talker, CHAR_Y),
        ITEM_getChar(itemindex, ITEM_UNIQUECODE),
        ITEM_getChar(itemindex, ITEM_NAME),
        ITEM_getInt(itemindex, ITEM_ID)
    );
  }

  sprintf(token, "收下了%s", ITEM_getChar(itemindex, ITEM_NAME));
  CHAR_talkToCli(talker, -1, token, CHAR_COLORWHITE);

  CHAR_sendItemDataOne(talker, ret);
  return TRUE;

}

int NPC_AcceptDel(int meindex, int talker, int mode) {

  char buf[1024 * 2];
  char buff2[256];
  int rand_j = 0;
  int j = 0;
  int evcnt;
  int b_flg = 0;
  evcnt = NPC_EventFile(meindex, talker, buf);
  if(evcnt == -1) return FALSE;

//	if(NPC_EventFile(meindex,talker,buf)==FALSE) return FALSE;

  if(NPC_ItemFullCheck(meindex, talker, buf, mode, evcnt) == FALSE) {
    NPC_MsgDisp(meindex, talker, 4);
    return FALSE;
  }

  if(NPC_Util_GetStrFromStrWithDelim(buf, "DelStone", buff2, sizeof(buff2))
     != NULL) {
    int stone;
    stone = NPC_EventGetCost(meindex, talker, buff2);

    if((CHAR_getInt(talker, CHAR_GOLD) - stone) < 0) {
      NPC_MsgDisp(meindex, talker, 14);
      return FALSE;
    }
  }

  if(NPC_Util_GetStrFromStrWithDelim(buf, "GetStone", buff2, sizeof(buff2)) != NULL) {
    int stone = atoi(buff2);

    if((CHAR_getInt(talker, CHAR_GOLD) + stone) >= CHAR_getMaxHaveGold(talker)) {
      NPC_MsgDisp(meindex, talker, 13);
      return FALSE;
    }
  }

  if((NPC_Util_GetStrFromStrWithDelim(buf, "pet_skill", buff2, sizeof(buff2))
      != NULL) && mode == 0) {
    if(mode == 0) {
      CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTTRD, 1);
      NPC_PetSkillMakeStr(meindex, talker, 1);
      return TRUE;
    }
  }

  if(NPC_Util_GetStrFromStrWithDelim(buf, "DelPet", buff2, sizeof(buff2)) != NULL) {
    char buf4[32];
    char buf5[256];
    int i = 1;
    char work[256];
    int j = 1;

    if(strstr(buff2, "EVDEL") != NULL) {
      NPC_Util_GetStrFromStrWithDelim(buf, "EVENT", buf5, sizeof(buf5));
      getStringFromIndexWithDelim(buf5, ",", evcnt, buff2, sizeof(buff2));


      while(getStringFromIndexWithDelim(buff2, "&", j, work, sizeof(work)) != FALSE) {
        j++;

        if(strstr(work, "PET") != NULL) {
          if(strstr(work, "EV") != NULL) {
            if(NPC_PetLvCheck(meindex, talker, work, 1) == FALSE) return FALSE;
          } else {
            if(NPC_PetLvCheck(meindex, talker, work, 0) == FALSE) return FALSE;
          }
        }
      }
      j = 1;


      while(getStringFromIndexWithDelim(buff2, "&", j, work, sizeof(work)) != FALSE) {
        j++;
        if(strstr(work, "PET") == NULL) continue;

        if(strstr(work, "*") != NULL) {
          int cnt = 0;
          int petcnt = 0;
          int petindex;

          getStringFromIndexWithDelim(work, "*", 2, buf4, sizeof(buf4));
          cnt = atoi(buf4);

          for(i = 0; i < CHAR_MAXPETHAVE; i++) {
            petindex = CHAR_getCharPet(talker, i);

            if(petindex == -1) continue;

            if(strstr(work, "EV") != NULL) {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 1) == FALSE) {
                continue;
              }
            } else {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 0) == FALSE) {
                continue;
              }
            }

            if(NPC_EventDelPet(meindex, talker, i) == FALSE) return FALSE;
            petcnt++;
            if(cnt == petcnt)
              break;
          }
        } else {
          for(i = 0; i < CHAR_MAXPETHAVE; i++) {
            int petindex = CHAR_getCharPet(talker, i);
            if(!CHAR_CHECKINDEX(petindex))
              continue;
            if(strstr(buff2, "EV") != NULL) {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 1) == FALSE) {
                continue;
              }
            } else {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 0) == FALSE) {
                continue;
              }
            }

            if(NPC_EventDelPet(meindex, talker, i) == FALSE)
              return FALSE;
          }
        }
      }

    } else {
      while(getStringFromIndexWithDelim(buff2, ",", j, work, sizeof(work)) != FALSE) {
        j++;
        if(strstr(work, "PET") != NULL) {
          if(strstr(work, "EV") != NULL) {
            if(NPC_PetLvCheck(meindex, talker, work, 1) == FALSE) return FALSE;
          } else {
            if(NPC_PetLvCheck(meindex, talker, work, 0) == FALSE) return FALSE;
          }
        }
      }
      j = 1;


      while(getStringFromIndexWithDelim(buff2, ",", j, work, sizeof(work)) != FALSE) {
        j++;
        if(strstr(work, "*") != NULL) {
          int cnt = 0;
          int petcnt = 0;
          int petindex;

          getStringFromIndexWithDelim(work, "*", 2, buf4, sizeof(buf4));
          cnt = atoi(buf4);

          for(i = 0; i < CHAR_MAXPETHAVE; i++) {
            petindex = CHAR_getCharPet(talker, i);

            if(petindex == -1) continue;

            if(strstr(work, "EV") != NULL) {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 1) == FALSE) {
                continue;
              }
            } else {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 0) == FALSE) {
                continue;
              }
            }

            if(NPC_EventDelPet(meindex, talker, i) == FALSE)
              return FALSE;

            petcnt++;
            if(cnt == petcnt) break;

          }
        } else {
          for(i = 0; i < CHAR_MAXPETHAVE; i++) {
            int petindex = CHAR_getCharPet(talker, i);

            if(!CHAR_CHECKINDEX(petindex))
              continue;

            if(strstr(buff2, "EV") != NULL) {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 1) == FALSE) {
                continue;
              }
            } else {
              if(NPC_PetLvCheckType2(petindex, meindex, talker, work, 0) == FALSE) {
                continue;
              }
            }

            if(NPC_EventDelPet(meindex, talker, i) == FALSE)
              return FALSE;
          }
        }
      }
    }
  }



  if(NPC_Util_GetStrFromStrWithDelim(buf, "GetStone", buff2, sizeof(buff2)) != NULL) {
    char token[128];

    int stone = atoi(buff2);
    CHAR_setInt(talker, CHAR_GOLD, CHAR_getInt(talker, CHAR_GOLD) + stone);
    CHAR_send_P_StatusString(talker, CHAR_P_STRING_GOLD);

    sprintf(token, "得到%d的stone", stone);
    CHAR_talkToCli(talker, -1, token, CHAR_COLORWHITE);
  }


  if(NPC_Util_GetStrFromStrWithDelim(buf, "GetPet", buff2, sizeof(buff2)) != NULL) {
    if(NPC_EventAddPet(meindex, talker, buff2, 1) == FALSE) {
      NPC_MsgDisp(meindex, talker, 10);
      return FALSE;
    }
  }

  // Robin add 从NPC取宠物蛋
  if(NPC_Util_GetStrFromStrWithDelim(buf, "GetEgg", buff2, sizeof(buff2)) != NULL) {
    if(NPC_EventAddEgg(meindex, talker, buff2, 1) == FALSE) {
      print(" AddEgg_Error:%d ", __LINE__);
      NPC_MsgDisp(meindex, talker, 10);
      return FALSE;
    }
  }

  if(NPC_Util_GetStrFromStrWithDelim(buf, "DelItem", buff2, sizeof(buff2)) != NULL) {
    if(strstr(buff2, "EVDEL") != NULL) {
      char work[256];
      char nbuf[256];

      NPC_Util_GetStrFromStrWithDelim(buf, "EVENT", buff2, sizeof(buff2));
      getStringFromIndexWithDelim(buff2, ",", evcnt, work, sizeof(work));

      if(strstr(buf, "Break") != NULL) {
        b_flg = 1;
      } else {
        b_flg = 0;
      }

      if(NPC_Util_GetStrFromStrWithDelim(buf, "NotDel", nbuf, sizeof(nbuf)) != NULL) {
        NPC_EventDelItemEVDEL(meindex, talker, work, nbuf, b_flg);
      } else {
        NPC_EventDelItemEVDEL(meindex, talker, work, "-1", b_flg);
      }
    } else {
      if(strstr(buf, "Break") != NULL) {
        b_flg = 1;
      } else {
        b_flg = 0;
      }
      NPC_EventDelItem(meindex, talker, buff2, b_flg);
    }
  }


  if(NPC_Util_GetStrFromStrWithDelim(buf, "DelStone", buff2, sizeof(buff2))
     != NULL) {
    int stone;
    char token[128];

    stone = NPC_EventGetCost(meindex, talker, buff2);

    CHAR_setInt(talker, CHAR_GOLD, CHAR_getInt(talker, CHAR_GOLD) - stone);
    CHAR_send_P_StatusString(talker, CHAR_P_STRING_GOLD);
    sprintf(token, "付出%d的stone。", stone);
    CHAR_talkToCli(talker, -1, token, CHAR_COLORWHITE);
  }

  if(NPC_Util_GetStrFromStrWithDelim(buf, "GetRandItem", buff2, sizeof(buff2))
     != NULL) {
    char buf3[32];
    j = 1;
    while(getStringFromIndexWithDelim(buff2, ",", j, buf3, sizeof(buf3))
          != FALSE) {
      j++;
      rand_j++;
    }
    NPC_RandItemGet(meindex, talker, rand_j, buff2);
  }


  if(NPC_Util_GetStrFromStrWithDelim(buf, "GetItem", buff2, sizeof(buff2)) != NULL) {
    NPC_EventAddItem(meindex, talker, buff2);
  }

  CHAR_complianceParameter(talker);
  CHAR_send_P_StatusString(talker,
                           CHAR_P_STRING_ATK | CHAR_P_STRING_DEF |
                           CHAR_P_STRING_CHARM | CHAR_P_STRING_QUICK |
                           CHAR_P_STRING_WATER | CHAR_P_STRING_FIRE |
                           CHAR_P_STRING_WIND | CHAR_P_STRING_EARTH
  );

  return TRUE;

}

int NPC_EventDelPet(int meindex, int talker, int petsel) {
  char szPet[128];
  int defpet;
  char msgbuf[64];

  int fd = getfdFromCharaIndex(talker);

  int petindex = CHAR_getCharPet(talker, petsel);

  if(!CHAR_CHECKINDEX(petindex))
    return FALSE;

  if(CHAR_getInt(talker, CHAR_RIDEPET) == petsel) {

    //CHAR_talkToCli( talker, -1, "骑乘中的宠物无法交出！", CHAR_COLORYELLOW );
    //return	FALSE;

    CHAR_setInt(talker, CHAR_RIDEPET, -1);
    CHAR_send_P_StatusString(talker, CHAR_P_STRING_RIDEPET);
    CHAR_complianceParameter(talker);
    CHAR_sendCToArroundCharacter(CHAR_getWorkInt(talker, CHAR_WORKOBJINDEX));
    print(" DelRidePet ");
  }
  print(" EventDelPet ");

  if(CHAR_getWorkInt(CONNECT_getCharaindex(fd), CHAR_WORKBATTLEMODE) != BATTLE_CHARMODE_NONE)
    return FALSE;
  defpet = CHAR_getInt(talker, CHAR_DEFAULTPET);
  if(defpet == petsel) {
    CHAR_setInt(talker, CHAR_DEFAULTPET, -1);
    lssproto_KS_send(fd, -1, TRUE);
  }

  snprintf(msgbuf, sizeof(msgbuf), "交出%s。", CHAR_getChar(petindex, CHAR_NAME));
  CHAR_talkToCli(talker, -1, msgbuf, CHAR_COLORWHITE);

  LogPet(
      CHAR_getChar(talker, CHAR_NAME),
      CHAR_getChar(talker, CHAR_CDKEY),
      CHAR_getChar(petindex, CHAR_NAME),
      CHAR_getInt(petindex, CHAR_LV),
      "EvnetDell(任务删除)",
      CHAR_getInt(talker, CHAR_FLOOR),
      CHAR_getInt(talker, CHAR_X),
      CHAR_getInt(talker, CHAR_Y),
      CHAR_getChar(petindex, CHAR_UNIQUECODE)
  );


  CHAR_setCharPet(talker, petsel, -1);
  CHAR_endCharOneArray(petindex);
  snprintf(szPet, sizeof(szPet), "K%d", petsel);
  CHAR_sendStatusString(talker, szPet);

  return TRUE;

}

int NPC_EventAddPet(int meindex, int talker, char *buff2, int mode) {
  int ret;
  char msgbuf[64];
  int enemynum;
  int enemyid;
  int i;
  int petindex;

  for(i = 0; i < CHAR_MAXPETHAVE; i++) {
    petindex = CHAR_getCharPet(talker, i);
    if(petindex == -1) break;
  }

  if(i == CHAR_MAXPETHAVE)
    return FALSE;

  if(strstr(buff2, ",") != NULL) {
    char buf2[16];
    while(getStringFromIndexWithDelim(buff2, ",", i, buf2, sizeof(buf2)) != FALSE) {
      i++;
    }
    i--;
    i = rand() % i + 1;
    getStringFromIndexWithDelim(buff2, ",", i, buf2, sizeof(buf2));
    enemyid = atoi(buf2);
  } else {
    enemyid = atoi(buff2);
  }

  enemynum = ENEMY_getEnemyNum();
  for(i = 0; i < enemynum; i++) {
    if(ENEMY_getInt(i, ENEMY_ID) == enemyid) {
      break;
    }
  }

  if(i == enemynum)
    return FALSE;

  ret = ENEMY_createPetFromEnemyIndex(talker, i);

  for(i = 0; i < CHAR_MAXPETHAVE; i++) {
    if(CHAR_getCharPet(talker, i) == ret)
      break;
  }
  if(i == CHAR_MAXPETHAVE) i = 0;
  if(CHAR_CHECKINDEX(ret) == TRUE) {
    CHAR_setMaxExpFromLevel(ret, CHAR_getInt(ret, CHAR_LV));
  }

  petindex = CHAR_getCharPet(talker, i);

  if(!CHAR_CHECKINDEX(petindex))
    return FALSE;
  CHAR_complianceParameter(petindex);
  snprintf(msgbuf, sizeof(msgbuf), "K%d", i);
  CHAR_sendStatusString(talker, msgbuf);

  snprintf(msgbuf, sizeof(msgbuf), "W%d", i);
  CHAR_sendStatusString(talker, msgbuf);
  snprintf(msgbuf, sizeof(msgbuf), "拿到%s。", CHAR_getChar(petindex, CHAR_NAME));
  CHAR_talkToCli(talker, -1, msgbuf, CHAR_COLORWHITE);

  LogPet(
      CHAR_getChar(talker, CHAR_NAME),
      CHAR_getChar(talker, CHAR_CDKEY),
      CHAR_getChar(petindex, CHAR_NAME),
      CHAR_getInt(petindex, CHAR_LV),
      "EventGet(任务得到)",
      CHAR_getInt(talker, CHAR_FLOOR),
      CHAR_getInt(talker, CHAR_X),
      CHAR_getInt(talker, CHAR_Y),
      CHAR_getChar(petindex, CHAR_UNIQUECODE)
  );


  if(mode == 0) {
    CHAR_setInt(petindex, CHAR_ENDEVENT, 1);
  }

  return TRUE;

}

// Robin add NPC给宠物蛋
int NPC_EventAddEgg(int meindex, int talker, char *buff2, int mode) {
  int ret;
  char msgbuf[64];
  int enemynum;
  int enemyid;
  int petid;
  int raise;
  int i;
  int petindex;
  char buf2[32];
  char buf3[32];

  print("\n 给蛋啦!!:%s ", buff2);

  for(i = 0; i < CHAR_MAXPETHAVE; i++) {
    petindex = CHAR_getCharPet(talker, i);
    if(petindex == -1) break;
  }

  if(i == CHAR_MAXPETHAVE) {
    print(" AddEgg_Error:%d ", __LINE__);
    return FALSE;
  }


  if(strstr(buff2, ",") != NULL) { // 是否为随机给与
    while(getStringFromIndexWithDelim(buff2, ",", i, buf2, sizeof(buf2))
          != FALSE) {
      i++;
    }
    i--;
    i = rand() % i + 1;
    getStringFromIndexWithDelim(buff2, ",", i, buf2, sizeof(buf2));

  } else {
    strcpy(buf2, buff2);
  }

  getStringFromIndexWithDelim(buf2, ";", 1, buf3, sizeof(buf3));
  enemyid = atoi(buf3); // 宠物蛋ID
  getStringFromIndexWithDelim(buf2, ";", 2, buf3, sizeof(buf3));
  petid = atoi(buf3); // 孵出的宠物ID
  getStringFromIndexWithDelim(buf2, ";", 3, buf3, sizeof(buf3));
  raise = atoi(buf3); //   养次数


  // 将enemyid转成enemybaseid
  enemynum = ENEMY_getEnemyNum();
  for(i = 0; i < enemynum; i++) {
    if(ENEMY_getInt(i, ENEMY_ID) == petid) {
      break;
    }
  }
  if(i == enemynum) {
    print(" AddEgg_Error:%d ", __LINE__);
    return FALSE;
  }
  petid = ENEMY_getInt(i, ENEMY_TEMPNO);


  enemynum = ENEMY_getEnemyNum();
  for(i = 0; i < enemynum; i++) {
    if(ENEMY_getInt(i, ENEMY_ID) == enemyid) {
      break;
    }
  }
  if(i == enemynum) {
    print(" AddEgg_Error:%d ", __LINE__);
    return FALSE;
  }

  ret = ENEMY_createPetFromEnemyIndex(talker, i);

  for(i = 0; i < CHAR_MAXPETHAVE; i++) {
    if(CHAR_getCharPet(talker, i) == ret)
      break;
  }
  if(i == CHAR_MAXPETHAVE) i = 0;
  if(CHAR_CHECKINDEX(ret) == TRUE) {
    CHAR_setMaxExpFromLevel(ret, CHAR_getInt(ret, CHAR_LV));
  }

  petindex = CHAR_getCharPet(talker, i);

  if(!CHAR_CHECKINDEX(petindex)) {
    print(" AddEgg_Error:%d ", __LINE__);
    return FALSE;
  }

  CHAR_complianceParameter(petindex);
  snprintf(msgbuf, sizeof(msgbuf), "K%d", i);
  CHAR_sendStatusString(talker, msgbuf);

  snprintf(msgbuf, sizeof(msgbuf), "W%d", i);
  CHAR_sendStatusString(talker, msgbuf);
  snprintf(msgbuf, sizeof(msgbuf), "拿到%s。", CHAR_getChar(petindex, CHAR_NAME));
  CHAR_talkToCli(talker, -1, msgbuf, CHAR_COLORWHITE);

  LogPet(
      CHAR_getChar(talker, CHAR_NAME),
      CHAR_getChar(talker, CHAR_CDKEY),
      CHAR_getChar(petindex, CHAR_NAME),
      CHAR_getInt(petindex, CHAR_LV),
      "EventGetEgg(任务得到)",
      CHAR_getInt(talker, CHAR_FLOOR),
      CHAR_getInt(talker, CHAR_X),
      CHAR_getInt(talker, CHAR_Y),
      CHAR_getChar(petindex, CHAR_UNIQUECODE)
  );


  if(mode == 0) {
    CHAR_setInt(petindex, CHAR_ENDEVENT, 1);
  }
  return TRUE;

}

int NPC_EventDelItem(int meindex, int talker, char *buf, int breakflg) {

  int i = 1, j = 1, k = 1;
  char buff3[128];
  char buf2[32];
  int itemindex;
  char token[256];

  while(getStringFromIndexWithDelim(buf, ",", k, buff3, sizeof(buff3)) != FALSE) {
    k++;
    if(strstr(buff3, "*") != NULL) {
      int itemno;
      int kosuu;
      int id;
      int cnt = 0;

      getStringFromIndexWithDelim(buff3, "*", 1, buf2, sizeof(buf2));
      itemno = atoi(buf2);
      getStringFromIndexWithDelim(buff3, "*", 2, buf2, sizeof(buf2));
      kosuu = atoi(buf2);

      if(breakflg != 1) {
      } else {
        for(i = 0; i < CHAR_MAXITEMHAVE; i++) {
          itemindex = CHAR_getItemIndex(talker, i);
          if(ITEM_CHECKINDEX(itemindex)) {
            id = ITEM_getInt(itemindex, ITEM_ID);
            if(itemno == id) {
              cnt++;
              LogItem(
                  CHAR_getChar(talker, CHAR_NAME),
                  CHAR_getChar(talker, CHAR_CDKEY),
#ifdef _add_item_log_name  // WON ADD 在item的log中增加item名称
                  itemindex,
#else
                  ITEM_getInt( itemindex, ITEM_ID),  // 失奶  丞  寞
#endif
                  "EventDelItem(任务需求所收回的道具)",
                  CHAR_getInt(talker, CHAR_FLOOR),
                  CHAR_getInt(talker, CHAR_X),
                  CHAR_getInt(talker, CHAR_Y),
                  ITEM_getChar(itemindex, ITEM_UNIQUECODE),
                  ITEM_getChar(itemindex, ITEM_NAME),
                  ITEM_getInt(itemindex, ITEM_ID)
              );

              if(breakflg == 1) {
                sprintf(token, "%s 坏了", ITEM_getChar(itemindex, ITEM_NAME));
                CHAR_talkToCli(talker, -1, token, CHAR_COLORWHITE);
              } else {
                sprintf(token, "交出%s", ITEM_getChar(itemindex, ITEM_NAME));
                CHAR_talkToCli(talker, -1, token, CHAR_COLORWHITE);
              }
              CHAR_setItemIndex(talker, i, -1);
              ITEM_endExistItemsOne(itemindex);
              CHAR_sendItemDataOne(talker, i);

              if(cnt == kosuu) {
                break;
              }
            }
          }
        }
      }
    }
    else {
      for(j = 0; j < CHAR_MAXITEMHAVE; j++) {
        itemindex = CHAR_getItemIndex(talker, j);

        if(ITEM_CHECKINDEX(itemindex)) {
          if(atoi(buff3) == ITEM_getInt(itemindex, ITEM_ID)) {
            LogItem(
                CHAR_getChar(talker, CHAR_NAME),
                CHAR_getChar(talker, CHAR_CDKEY),
#ifdef _add_item_log_name  // WON ADD 在item的log中增加item名称
                itemindex,
#else
                ITEM_getInt( itemindex, ITEM_ID),
#endif
                "EventDelItem(任务需求所收回的道具)",
                CHAR_getInt(talker, CHAR_FLOOR),
                CHAR_getInt(talker, CHAR_X),
                CHAR_getInt(talker, CHAR_Y),
                ITEM_getChar(itemindex, ITEM_UNIQUECODE),
                ITEM_getChar(itemindex, ITEM_NAME),
                ITEM_getInt(itemindex, ITEM_ID)
            );
            if(breakflg == 1) {
              sprintf(token, "%s 坏了", ITEM_getChar(itemindex, ITEM_NAME));
              CHAR_talkToCli(talker, -1, token, CHAR_COLORWHITE);
            } else {
              sprintf(token, "交出%s。", ITEM_getChar(itemindex, ITEM_NAME));
              CHAR_talkToCli(talker, -1, token, CHAR_COLORWHITE);
            }
            CHAR_setItemIndex(talker, j, -1);
            ITEM_endExistItemsOne(itemindex);
            CHAR_sendItemDataOne(talker, j);
          }
        }
      }
    }
  }

  return TRUE;
}

int NPC_EventDelItemEVDEL(int meindex, int talker, char *buf, char *nbuf, int breakflg) {

  int k = 1, l = 1;
  char buff3[128];
  char buf2[32];
  char buf4[32];


  while(getStringFromIndexWithDelim(buf, "&", k, buf4, sizeof(buf4)) != FALSE) {
    int itemno;
    k++;
    if(strstr(buf4, "ITEM") == NULL) continue;
    getStringFromIndexWithDelim(buf4, "=", 2, buff3, sizeof(buff3));

    if(strstr(buff3, "*") != NULL) {
      int kosuu;
      char token[256];
      int i, itemindex, id, cnt;
      getStringFromIndexWithDelim(buff3, "*", 1, buf2, sizeof(buf2));
      itemno = atoi(buf2);
      getStringFromIndexWithDelim(buff3, "*", 2, buf2, sizeof(buf2));
      kosuu = atoi(buf2);
      if(strstr(nbuf, "-1") == NULL) {
        l = 1;
        while(getStringFromIndexWithDelim(nbuf, ",", l, buf2, sizeof(buf2))) {
          l++;
          if(itemno == atoi(buf2)) {
            l = -1;
            break;
          }
        }
        if(l == -1) continue;
      }
      cnt = 0;
      for(i = 0; i < CHAR_MAXITEMHAVE; i++) {
        itemindex = CHAR_getItemIndex(talker, i);
        if(ITEM_CHECKINDEX(itemindex)) {
          id = ITEM_getInt(itemindex, ITEM_ID);
          if(itemno == id) {
            cnt++;
            LogItem(
                CHAR_getChar(talker, CHAR_NAME),
                CHAR_getChar(talker, CHAR_CDKEY),
#ifdef _add_item_log_name  // WON ADD 在item的log中增加item名称
                itemindex,
#else
                ITEM_getInt( itemindex, ITEM_ID),  /* 失奶  丞  寞 */
#endif
                "EventDelItem(任务需求所收回的道具)",
                CHAR_getInt(talker, CHAR_FLOOR),
                CHAR_getInt(talker, CHAR_X),
                CHAR_getInt(talker, CHAR_Y),
                ITEM_getChar(itemindex, ITEM_UNIQUECODE),
                ITEM_getChar(itemindex, ITEM_NAME),
                ITEM_getInt(itemindex, ITEM_ID)
            );
            if(breakflg == 1) {
              sprintf(token, "%s 坏了", ITEM_getChar(itemindex, ITEM_NAME));
              CHAR_talkToCli(talker, -1, token, CHAR_COLORWHITE);
            } else {
              sprintf(token, "交出%s", ITEM_getChar(itemindex, ITEM_NAME));
              CHAR_talkToCli(talker, -1, token, CHAR_COLORWHITE);
            }
            CHAR_setItemIndex(talker, i, -1);
            ITEM_endExistItemsOne(itemindex);
            CHAR_sendItemDataOne(talker, i);
            if(cnt == kosuu) {
              break;
            }
          }
        }
      }
    } else {
      int j, itemindex;
      char token[256];
      if(strstr(nbuf, "-1") == NULL) {
        l = 1;
        while(getStringFromIndexWithDelim(nbuf, ",", l, buf2, sizeof(buf2))) {
          l++;
          if(atoi(buff3) == atoi(buf2)) {
            l = -1;
            break;
          }
        }
        if(l == -1) continue;
      }
      itemno = -1;
      for(j = 0; j < CHAR_MAXITEMHAVE; j++) {
        itemindex = CHAR_getItemIndex(talker, j);
        if(ITEM_CHECKINDEX(itemindex)) {
          if(atoi(buff3) == ITEM_getInt(itemindex, ITEM_ID)) {
            LogItem(
                CHAR_getChar(talker, CHAR_NAME),
                CHAR_getChar(talker, CHAR_CDKEY),
#ifdef _add_item_log_name  // WON ADD 在item的log中增加item名称
                itemindex,
#else
                ITEM_getInt( itemindex, ITEM_ID),  /* 失奶  丞  寞 */
#endif
                "EventDelItem(任务需求所收回的道具)",
                CHAR_getInt(talker, CHAR_FLOOR),
                CHAR_getInt(talker, CHAR_X),
                CHAR_getInt(talker, CHAR_Y),
                ITEM_getChar(itemindex, ITEM_UNIQUECODE),
                ITEM_getChar(itemindex, ITEM_NAME),
                ITEM_getInt(itemindex, ITEM_ID)
            );
            if(breakflg == 1) {
              sprintf(token, "%s 坏了", ITEM_getChar(itemindex, ITEM_NAME));
              CHAR_talkToCli(talker, -1, token, CHAR_COLORWHITE);
            } else {
              sprintf(token, "交出%s。", ITEM_getChar(itemindex, ITEM_NAME));
              CHAR_talkToCli(talker, -1, token, CHAR_COLORWHITE);
            }
            CHAR_setItemIndex(talker, j, -1);
            ITEM_endExistItemsOne(itemindex);
            CHAR_sendItemDataOne(talker, j);
          }
        }
      }
    }
  }

  return TRUE;
}

int NPC_EventAddItem(int meindex, int talker, char *buf) {

  char buff3[128];
  int i = 1;
  int itemindex;
  char buf3[32];
  int ret;
  char token[256];

  while(getStringFromIndexWithDelim(buf, ",", i, buff3, sizeof(buff3)) != FALSE) {
    i++;
    if(strstr(buff3, "*") != NULL) {

      int itemno;
      int kosuu;
      int loop = 0;

      getStringFromIndexWithDelim(buff3, "*", 1, buf3, sizeof(buf3));
      itemno = atoi(buf3);
      getStringFromIndexWithDelim(buff3, "*", 2, buf3, sizeof(buf3));
      kosuu = atoi(buf3);

      for(loop = 0; loop < kosuu; loop++) {
        itemindex = ITEM_makeItemAndRegist(itemno);

        if(itemindex == -1) return FALSE;

        ret = CHAR_addItemSpecificItemIndex(talker, itemindex);
        if(ret < 0 || ret >= CHAR_MAXITEMHAVE) {
          print("npc_exchange:ACCEPTadditem error itemindex[%d]\n", itemindex);
          ITEM_endExistItemsOne(itemindex);
          return FALSE;
        }

        if(itemindex != -1) {
          LogItem(
              CHAR_getChar(talker, CHAR_NAME),
              CHAR_getChar(talker, CHAR_CDKEY),
#ifdef _add_item_log_name  // WON ADD 在item的log中增加item名称
              itemindex,
#else
              ITEM_getInt( itemindex, ITEM_ID),  /* 失奶  丞  寞 */
#endif
              "EventAddItem(任务需求所得到的道具)",
              CHAR_getInt(talker, CHAR_FLOOR),
              CHAR_getInt(talker, CHAR_X),
              CHAR_getInt(talker, CHAR_Y),
              ITEM_getChar(itemindex, ITEM_UNIQUECODE),
              ITEM_getChar(itemindex, ITEM_NAME),
              ITEM_getInt(itemindex, ITEM_ID)
          );
        }
        sprintf(token, "拿到%s。", ITEM_getChar(itemindex, ITEM_NAME));
        CHAR_talkToCli(talker, -1, token, CHAR_COLORWHITE);

        CHAR_sendItemDataOne(talker, ret);
      }
    } else {
      itemindex = ITEM_makeItemAndRegist(atoi(buff3));

      if(itemindex == -1)
        return FALSE;

      ret = CHAR_addItemSpecificItemIndex(talker, itemindex);
      if(ret < 0 || ret >= CHAR_MAXITEMHAVE) {
        print("npc_exchange.c: ACCEPTadditem error itemindex[%d]\n", itemindex);
        ITEM_endExistItemsOne(itemindex);
        return FALSE;
      }

      if(itemindex != -1) {
        LogItem(
            CHAR_getChar(talker, CHAR_NAME),
            CHAR_getChar(talker, CHAR_CDKEY),
#ifdef _add_item_log_name  // WON ADD 在item的log中增加item名称
            itemindex,
#else
            ITEM_getInt( itemindex, ITEM_ID),
#endif
            "EventAddItem(任务需求所得到的道具)",
            CHAR_getInt(talker, CHAR_FLOOR),
            CHAR_getInt(talker, CHAR_X),
            CHAR_getInt(talker, CHAR_Y),
            ITEM_getChar(itemindex, ITEM_UNIQUECODE),
            ITEM_getChar(itemindex, ITEM_NAME),
            ITEM_getInt(itemindex, ITEM_ID)
        );
      }
      sprintf(token, "拿到%s。", ITEM_getChar(itemindex, ITEM_NAME));
      CHAR_talkToCli(talker, -1, token, CHAR_COLORWHITE);

      CHAR_sendItemDataOne(talker, ret);
    }
  }

  return TRUE;
}

int NPC_EventFile(int meindex, int talker, char *arg) {

  char argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
  char buff2[256];
  char buf[1024 * 2];
  int i = 1;
  int EvNo = 0;
  int evch;

  if(NPC_Util_GetArgStr(meindex, argstr, sizeof(argstr)) == NULL) {
    print("GetArgStrErr");
    return -1;
  }

  while(getStringFromIndexWithDelim(argstr, "EventEnd", i, buf, sizeof(buf)) != FALSE) {
    CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTSEC, 0);
    i++;
    NPC_Util_GetStrFromStrWithDelim(buf, "EventNo", buff2, sizeof(buff2));
    EvNo = atoi(buff2);

    if(NPC_EventCheckFlg(talker, EvNo) == TRUE) continue;

    if(NPC_Util_GetStrFromStrWithDelim(buf, "Pet_Name", buff2, sizeof(buff2)) != NULL) {
      CHAR_setWorkInt(talker, CHAR_WORKSHOPRELEVANTSEC, 1);
    }
    if(NPC_Util_GetStrFromStrWithDelim(buf, "KeyWord", buff2, sizeof(buff2))
       != NULL) {
      if(CHAR_getWorkInt(talker, CHAR_WORKSHOPRELEVANT) != i) continue;
    }

    evch = NPC_ExChangeManEventCheck(meindex, talker, buf);

    if(evch != -1) {
      strcpysafe(arg, sizeof(buf), buf);
      return evch;
    }
  }

  return -1;

}

int NPC_EventReduce(int meindex, int talker, char *buf) {

  char buf2[512];
  char buf3[256];
  int id = 0;
  int i;
  int itemindex;
  int itemno;
  int kosuu;
  int cnt = 0;

  getStringFromIndexWithDelim(buf, "=", 2, buf2, sizeof(buf2));
  getStringFromIndexWithDelim(buf2, "*", 1, buf3, sizeof(buf3));
  itemno = atoi(buf3);
  getStringFromIndexWithDelim(buf2, "*", 2, buf3, sizeof(buf3));
  kosuu = atoi(buf3);

  for(i = 0; i < CHAR_MAXITEMHAVE; i++) {
    itemindex = CHAR_getItemIndex(talker, i);
    if(ITEM_CHECKINDEX(itemindex)) {
      id = ITEM_getInt(itemindex, ITEM_ID);
      if(itemno == id) {
        //change add 增加对堆叠的判断
        int pilenum = ITEM_getInt(itemindex, ITEM_USEPILENUMS);
        if(pilenum)
          cnt += pilenum;
        else
          cnt++;

        if(cnt >= kosuu) {
          return TRUE;
        }
      }
    }
  }

  return FALSE;

}

void NPC_EventPetSkill(int meindex, int talker, char *data) {
  int skillID = 0;
  char buf[64];
  char argstr[1024];
  char msg[512];
  char msgbuf[128];
  int fd = getfdFromCharaIndex(talker);
  int evcnt;

  if(NPC_Util_CharDistance(talker, meindex) > 2)
    return;

  evcnt = NPC_EventFile(meindex, talker, argstr);

  if(evcnt == -1)
    return;

  makeStringFromEscaped(data);

  getStringFromIndexWithDelim(data, "|", 1, buf, sizeof(buf));
  int skill = atoi(buf);
  getStringFromIndexWithDelim(data, "|", 2, buf, sizeof(buf));
  int pet = atoi(buf);
  getStringFromIndexWithDelim(data, "|", 3, buf, sizeof(buf));
  int slot = atoi(buf);
  getStringFromIndexWithDelim(data, "|", 4, buf, sizeof(buf));
  int cost = atoi(buf);

  if(NPC_Util_GetStrFromStrWithDelim(argstr, "pet_skill", msg, sizeof(msg)) != NULL) {
    getStringFromIndexWithDelim(msg, ",", skill, buf, sizeof(buf));
    skillID = atoi(buf);
  }
  slot--;


  int petindex = CHAR_getCharPet(talker, pet - 1);

  if(petindex == -1) {
    print("PetindexErr");
    return;
  }

  if(CHAR_getWorkInt(CONNECT_getCharaindex(fd), CHAR_WORKBATTLEMODE) != BATTLE_CHARMODE_NONE)
    return;

  CHAR_setPetSkill(petindex, slot, skillID);
  CHAR_setInt(talker, CHAR_GOLD, (CHAR_getInt(talker, CHAR_GOLD) - cost));
  snprintf(msgbuf, sizeof(msgbuf), "W%d", pet - 1);
  CHAR_sendStatusString(talker, msgbuf);
  CHAR_sendStatusString(talker, "P");
}

int NPC_ItemFullCheck(int meindex, int talker, char *buf, int mode, int evcnt) {

  char buff2[256];
  int i = 1, j = 1;
  int maxitem = 0;
  int kosuucnt = 0;
  int itemindex;
  char buf3[256];
  int rand_j = 0;
  int rand_cnt = 0;
  char nbuf[256];
  char buff6[16];
  int l = 1;

  if(NPC_Util_GetStrFromStrWithDelim(buf, "DelItem", buff2, sizeof(buff2)) != NULL) {
    if(strstr(buff2, "EVDEL") != NULL) {
      char buff4[64];
      char buff5[32];

      i = 1;
      NPC_Util_GetStrFromStrWithDelim(buf, "EVENT", buff2, sizeof(buff2));
      getStringFromIndexWithDelim(buff2, ",", evcnt, buf3, sizeof(buf3));

      while(getStringFromIndexWithDelim(buf3, "&", j, buff4, sizeof(buff4))) {
        j++;
        if(strstr(buff4, "ITEM") != NULL) {
          if(strstr(buff4, "*") != NULL) {
            int itemno;

            l = 1;
            getStringFromIndexWithDelim(buff4, "=", 2, buff5, sizeof(buff5));
            getStringFromIndexWithDelim(buff5, "*", 1, buff6, sizeof(buff6));
            itemno = atoi(buff6);

            if(NPC_Util_GetStrFromStrWithDelim(buf, "NotDel", nbuf, sizeof(nbuf)) != NULL) {
              while(getStringFromIndexWithDelim(nbuf, ",", l, buff6, sizeof(buff6))) {
                l++;
                if(itemno == atoi(buff6)) {
                  l = -1;
                  break;
                }
              }
            }
            if(l == -1) continue;
            getStringFromIndexWithDelim(buff5, "*", 2, buff6, sizeof(buff6));
            maxitem -= atoi(buff6);
          } else {
            getStringFromIndexWithDelim(buff4, "=", 2, buff5, sizeof(buff5));
            l = 1;

            if(NPC_Util_GetStrFromStrWithDelim(buf, "NotDel", nbuf, sizeof(nbuf)) != NULL) {
              while(getStringFromIndexWithDelim(nbuf, ",", l, buff6, sizeof(buff6))) {
                l++;
                if(atoi(buff5) == atoi(buff6)) {
                  l = -1;
                  break;
                }
              }
            }
            if(l == -1) continue;
            for(i = CHAR_STARTITEMARRAY; i < CHAR_MAXITEMHAVE; i++) {
              itemindex = CHAR_getItemIndex(talker, i);
              if(ITEM_CHECKINDEX(itemindex)) {
                if(atoi(buff5) == ITEM_getInt(itemindex, ITEM_ID)) {
                  maxitem--;
                }
              }
            }
          }
        }
      }
    } else {
      char buff3[128];
      i = 1;
      while(getStringFromIndexWithDelim(buff2, ",", i, buff3, sizeof(buff3)) != FALSE) {
        i++;
        if(strstr(buff3, "*") != NULL) {
          getStringFromIndexWithDelim(buff3, "*", 2, buf3, sizeof(buf3));
          maxitem -= atoi(buf3);
        } else {
          for(i = CHAR_STARTITEMARRAY; i < CHAR_MAXITEMHAVE; i++) {
            itemindex = CHAR_getItemIndex(talker, i);
            if(ITEM_CHECKINDEX(itemindex)) {
              if(atoi(buff3) == ITEM_getInt(itemindex, ITEM_ID)) {
                maxitem--;
              }
            }
          }
        }
      }

    }
  }

  if(NPC_Util_GetStrFromStrWithDelim(buf, "GetRandItem", buff2, sizeof(buff2)) != NULL && mode == 0) {
    j = 1;
    while(getStringFromIndexWithDelim(buff2, ",", j, buf3, sizeof(buf3)) != FALSE) {
      j++;
      rand_j++;
    }
    rand_cnt = 1;
    for(i = CHAR_STARTITEMARRAY; i < CHAR_MAXITEMHAVE; i++) {
      itemindex = CHAR_getItemIndex(talker, i);
      if(!ITEM_CHECKINDEX(itemindex)) {
        kosuucnt++;
      }
    }
    if(maxitem == 0 && kosuucnt == 0) {
      return FALSE;
    }
  }


  if(NPC_Util_GetStrFromStrWithDelim(buf, "GetItem", buff2, sizeof(buff2)) != NULL && mode == 0) {
    char buff3[256];
    j = 1;
    while(getStringFromIndexWithDelim(buff2, ",", j, buff3, sizeof(buff3)) != FALSE) {
      j++;
      if(strstr(buff3, "*") != NULL) {
        getStringFromIndexWithDelim(buff3, "*", 2, buf3, sizeof(buf3));
        maxitem += atoi(buf3);
      } else {
        maxitem++;
      }
    }
    kosuucnt = 0;
    for(i = CHAR_STARTITEMARRAY; i < CHAR_MAXITEMHAVE; i++) {
      itemindex = CHAR_getItemIndex(talker, i);
      if(!ITEM_CHECKINDEX(itemindex)) {
        kosuucnt++;
      }
    }
    maxitem = maxitem + rand_cnt;
    if(kosuucnt < maxitem) {
      return FALSE;
    }
  }


  return TRUE;
}

void NPC_CharmStatus(int talker) {
  char petsend[64];
  for(int i = 0; i < CHAR_MAXPETHAVE; i++) {
    int petindex = CHAR_getCharPet(talker, i);
    if(petindex == -1)
      continue;
    if(!CHAR_CHECKINDEX(talker))
      continue;
    CHAR_complianceParameter(petindex);
    sprintf(petsend, "K%d", i);
    CHAR_sendStatusString(talker, petsend);
  }
}

int NPC_EventGetCost(int meindex, int talker, char *arg) {

  int cost;
  int level;
  char buf[32];
  if(strstr(arg, "LV") != NULL) {
    level = CHAR_getInt(talker, CHAR_LV);
    getStringFromIndexWithDelim(arg, "*", 2, buf, sizeof(buf));
    cost = level * atoi(buf);
  } else {
    cost = atoi(arg);
  }
  return cost;

}

