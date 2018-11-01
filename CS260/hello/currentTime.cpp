
#include <ctime>

char * getTime()
{
	time_t			rawTime;
	tm *			currTime;
	char *			currTimeStr;

	time(&rawTime);
	currTime = localtime(&rawTime);
	currTimeStr = asctime(currTime);

	return currTimeStr;
}