//3350 software engineering
//2017
//timer functions
//
#include <unistd.h>
#include <ctime>
//#include <cmath>
#include <cstring>

//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 60.0;
const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
double physicsCountdown=0.0;
double timeSpan=0.0;
//unsigned int upause=0;
double timeDiff(struct timespec *start, struct timespec *end)
{
	//return the difference in two times.
	return (double)(end->tv_sec - start->tv_sec ) +
		(double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void timeCopy(struct timespec *dest, struct timespec *source)
{
	//copy one time structure to another.
	memcpy(dest, source, sizeof(struct timespec));
}
//-----------------------------------------------------------------------------


