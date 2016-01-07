#ifndef __HANDLETIME_H__ 
#define __HANDLETIME_H__

#include <sys/time.h>

#include "common.h"

#undef EXTERN
#ifdef __HANDLETIME_C__
#define EXTERN
#else  /*__HANDLETIME_C__*/
#define EXTERN extern
#endif

EXTERN struct timeval NowTime;
EXTERN int     DEBUG_ADJUSTTIME;

int setNewTime( void );
// WON REM
//struct tm *localtime(const time_t *timep);

/*仇仇井日票｝HiO［LS凛棉楮溢［*/
/*    凛棉150(坌)*60=9000  =750*12 匹   LS1     */
/*  LS1200凛棉  LS1     */
/*  LS100  匹   LS1     */
typedef struct tagLSTIME
{
	int year;
	int day;
	int hour;
}LSTIME;

#define NIGHT_TO_MORNING	700
#define MORNING_TO_NOON		930
#define NOON_TO_EVENING		200
#define EVENING_TO_NIGHT	300

typedef enum
{
	LS_NIGHT = 0,
	LS_MORNING ,
	LS_NOON ,
	LS_EVENING ,
}LSTIME_SECTION;

void RealTimeToLSTime(long t , LSTIME *lstime);
LSTIME_SECTION getLSTime (LSTIME *lstime);

#endif  
