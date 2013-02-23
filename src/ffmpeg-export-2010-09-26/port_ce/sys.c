#ifdef WINCE

#include <Winbase.h>
#include <stdlib.h>
#include <time.h>

void abort()
{
	TerminateProcess(GetCurrentProcess(), 0);
}

float sinf(float x)
{
	return sin(x);
}

//define
float powf(float x, float y)
{
	return ((float)pow((double)(x), (double)(y)));
}


//inline
float ldexpf(float _X, int _Y)
{
	return ((float)ldexp((double)_X, _Y)); 
}

float frexpf(float x, int* expptr)
  {return ((float)frexp((double)x, expptr)); }

//-------------------------------------------------------------------------

//time_t time( time_t *inTT ) 
//{
//	SYSTEMTIME sysTimeStruct;
//	FILETIME fTime;
//	ULARGE_INTEGER int64time;
//	time_t locTT = 0;
//
//	if ( inTT == NULL ) {
//		inTT = &locTT;
//	}
//
//	GetSystemTime( &sysTimeStruct );
//	if ( SystemTimeToFileTime( &sysTimeStruct, &fTime ) ) {
//		memcpy( &int64time, &fTime, sizeof( FILETIME ) );
//		/* Subtract the value for 1970-01-01 00:00 (UTC) */
//		int64time.QuadPart -= 0x19db1ded53e8000;
//		/* Convert to seconds. */
//		int64time.QuadPart /= 10000000;
//		*inTT = int64time.QuadPart;
//	}
//
//	return *inTT;
//}

static struct tm Date;
// the count of days of 12 months
const int SecOfOneDay = 86400 ; // 24*60*60

const short month[2][13]={
	365,31,28,31,30,31,30,31,31,30,31,30,31,
	366,31,29,31,30,31,30,31,31,30,31,30,31
};


int       IsLeapYear(int year)
{
	return (0==year%4       && (0!=year%100 || 0==year%400) );
}

// notify ::::       the result you should see in the time.h of standard c
// eg . 1972/11/28/ 6:30:30
// save as : 72/10/28/ 6:30:30
void       Second2Date(const unsigned long* seconds , struct tm* Date )
{ 
	long totalsec = *(seconds) ;
	int       leapyear;
	int i = 0;
	int weekday;
	int oddsec;

	// judge the year 
	for(i=0 ; ; i++)
	{
		leapyear = IsLeapYear(1970+i);
		totalsec -= (long) (month[leapyear][0] * SecOfOneDay);
		if( totalsec < 0 )
		{
			//        Date->tm_yday = month[leapyear][0]-1;        do not fill this data
			Date->tm_year = 70+i;          // 1970+i-1900 as standard C
			totalsec += (long) (month[leapyear][0] * SecOfOneDay);
			break;
		}
	}

	// judge the weekday 
	weekday = 1900+Date->tm_year-1;       // the 1900 , do not forget !!!!!
	weekday = weekday + (int)(weekday/4) - (int)(weekday/100) + (int)(weekday/400) + (int)(totalsec/SecOfOneDay)+1;
	Date->tm_wday = weekday%7;

	// judge the month
	for( i=1; i<=12 ; i++ )
	{
		totalsec -= (long) (month[leapyear][i] * SecOfOneDay);
		if(totalsec < 0)
		{
			Date->tm_mon = i-1;           // the define of tm_mon (0--11)
			totalsec += (long) (month[leapyear][i] * SecOfOneDay);
			break;
		}
	}

	//       judge the day , hour, min , second
	Date->tm_mday = (int)(totalsec/SecOfOneDay+1) ;

	oddsec = (int)(totalsec%SecOfOneDay);
	Date->tm_hour = (int)(oddsec/3600);

	oddsec = (int)(oddsec%3600);
	Date->tm_min       = (int)(oddsec/60);

	oddsec = (int)(oddsec%60);
	Date->tm_sec = oddsec;

	return;
}

unsigned long       Date2Second(struct tm* Date)
{
	long totalseconds = 0 ;
	int leapyear;
	int index ;

	// now index stands for the year
	for(index=1970; index< (Date->tm_year+1900); index++)
	{
		leapyear = IsLeapYear(index);
		totalseconds += (long)(month[leapyear][0] * SecOfOneDay);
	}

	leapyear = IsLeapYear(index);
	// now index stands for the month
	for(index=1 ; index<(Date->tm_mon+1) ; index++)
	{
		totalseconds += (long)(month[leapyear][index]*SecOfOneDay);
	}

	// day
	totalseconds += (long)((Date->tm_mday-1)*SecOfOneDay);
	// hour , minute ,second
	totalseconds += (long)(Date->tm_hour)*3600;
	totalseconds += (long)(Date->tm_min)*60;
	totalseconds += (long)Date->tm_sec;

	return totalseconds;


}

struct tm* gmtime(const time_t* seconds)
{ 
#ifdef _WIN32_WCE
	memset(&Date,0,sizeof(Date));
	Second2Date( seconds , &Date );
	return &Date;
#else
	return gmtime(seconds);
#endif
}

time_t       mktime(struct tm* Date)
{
#ifdef _WIN32_WCE
	return Date2Second(Date);
#else  
	return mktime(Date);
#endif
}

time_t time(time_t *timer)
{
	SYSTEMTIME systime;
	struct tm st;
	GetSystemTime(&systime);

	st.tm_sec       = systime.wSecond; // second
	st.tm_min       = systime.wMinute; // minute
	st.tm_hour = systime.wHour;       // hour
	st.tm_mday = systime.wDay;       // Specifies the current day of the month
	st.tm_mon       = systime.wMonth - 1; //
	st.tm_year = systime.wYear - 1900; //

	return timer? (*timer = mktime(&st)) : mktime(&st);
}

//-----------------------------------------------------------------------


int __cdecl write(int handle, void *buffer, unsigned int count) {	
	DWORD dwWrite = 0;
	return WriteFile((HANDLE)handle, buffer, count, &dwWrite, NULL) ? dwWrite : -1;
}

int setmode (int fd, int mode)
{
	return 0x8000;
}

char* getenv(const char* inName)
{
	return NULL;
}

void *bsearch( 
			  const void *key,
			  const void *base,
			  size_t num,
			  size_t width,
			  int ( __cdecl *compare ) ( const void *, const void *) 
			  ){
	return NULL;
}

clock_t __cdecl clock(void)
{
	return GetTickCount();
}

#endif //WINCE