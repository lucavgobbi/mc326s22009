/*Analizer library*/
#include <time.h>

clock_t Time();

long double ExecuteTime(long double endtime, long double starttime);

int NumberReg(char *input);

int TotalWrite(int counter, int countern);

int TotalGet(int counterr, int counterrf);

void CreateReport(long double endtime,long double starttime, char *input, int *counter, int *countern, int *counterr, int *counterrf, int *numfile, int *nummerge);

void print(long double endtime,long double starttime, char *input, int *counter, int *countern, int *counterr, int *counterrf, int *numfile, int *nummerge);
