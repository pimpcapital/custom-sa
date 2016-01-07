#define __HANDLETIME_C__

#include <time.h>
#include <sys/time.h>

#include "common.h"
#include "handletime.h"

#define LSTIME_SECONDS_PER_DAY 5400


#define LSTIME_HOURS_PER_DAY 1024
#define LSTIME_DAYS_PER_YEAR 100


/*
// Nuke 0701: localtime

  struct timeval NowTime;
#ifdef localtime
#undef localtime
#endif

struct tm *localtime(const time_t *timep)
{
	static struct tm lt;
	memset(&lt,0,sizeof(lt));
	lt.tm_sec=*timep %60;
	lt.tm_min=(*timep %3600) / 60;
	lt.tm_hour=(*timep % 86400) / 3600;	
	return &lt;
}
*/
int setNewTime(void) {
  if(gettimeofday(&NowTime, (struct timezone *) NULL) != 0) {
    NowTime.tv_sec = time(0);
    // Nuke 0701: Localtime down
    print("\n time err !! \n");
    return FALSE;
  }
  NowTime.tv_sec += DEBUG_ADJUSTTIME;
  return TRUE;
}


/*******************************************************************
*******************************************************************/
static long era = (long) 912766409 + 5400;

void RealTimeToLSTime(long t, LSTIME *lstime) {
  long lsseconds = t - era;
  long lsdays;

  lstime->year = (int) (lsseconds / (LSTIME_SECONDS_PER_DAY * LSTIME_DAYS_PER_YEAR));

  lsdays = lsseconds / LSTIME_SECONDS_PER_DAY;
  lstime->day = lsdays % LSTIME_DAYS_PER_YEAR;


  lstime->hour = (int) (lsseconds % LSTIME_SECONDS_PER_DAY)
                 * LSTIME_HOURS_PER_DAY / LSTIME_SECONDS_PER_DAY;

  return;
}

LSTIME_SECTION getLSTime(LSTIME *lstime) {
  if(NIGHT_TO_MORNING < lstime->hour
     && lstime->hour <= MORNING_TO_NOON)
    return LS_MORNING;
  else if(NOON_TO_EVENING < lstime->hour
          && lstime->hour <= EVENING_TO_NIGHT)
    return LS_EVENING;
  else if(EVENING_TO_NIGHT < lstime->hour
          && lstime->hour <= NIGHT_TO_MORNING)
    return LS_NIGHT;
  else
    return LS_NOON;
}


