#include <stdio.h>
#include "Analizer.h"
#include <stdlib.h>
#include <time.h>
#include "ConfigFileReader.h"
#include <strings.h>

clock_t Time()
{	
	return clock();	
}

long double ExecuteTime(long double endtime, long double starttime)
{
	return endtime - starttime;
}

int NumberReg(char *input)
{
	int numreg = 0;
	int aux=0;
	FILE *file;
	char carac;

	file = fopen(input, "r");
	
	while(carac != EOF){
	
		carac = getc(file);
		aux ++;	
		if(aux % (GetRegisterSize()+1) == 0){
			numreg++;}
	}

	fclose(file);
	return numreg;
}

int Total(int *counter, int *countern)
{
	return (*counter) + (*countern);
}

void CreateReport(long double endtime,long double starttime, char *input, int *counter, int *countern, int *counterr, int *counterrf, int *numfile, int *nummerge)
{
	int numreg, numwrite, numread, numsort, auxfile;
	double exetime;
	char string[]="exetime,numreg,numwrite,numread,numsort,numfile";
	char aux[30]; 
	FILE *report;

	exetime = ExecuteTime(endtime, starttime);
	numreg = NumberReg(input);
	numwrite = Total(counter, countern);
	numread = Total(counterr, counterrf);
	numsort = *nummerge;
	auxfile = *numfile;

	report = fopen("report","w");
	sprintf(aux,"%f",exetime);
	fputs(string,report);
	fputs("\n",report);
	fputs(aux,report);
	fputs(",",report);
	sprintf(aux,"%d",numreg);
	fputs(aux,report);
	fputs(",",report);
	sprintf(aux,"%d",numwrite);
	fputs(aux,report);
	fputs(",",report);
	sprintf(aux,"%d",numread);
	fputs(aux,report);
	fputs(",",report);
	sprintf(aux,"%d",numsort);
	fputs(aux,report);
	fputs(",",report);
	sprintf(aux,"%d",auxfile);
	fputs(aux,report);
	fclose(report);
	return;
}

void print(long double endtime, long double starttime, char *input, int *counter, int *countern, int *counterr, int *counterrf, int *numfile, int *nummerge)
{
	int numsort,auxfile,numread,numwrite,numreg;
	long double exetime;
	exetime = ExecuteTime(endtime, starttime);
	numreg = NumberReg(input);
	numwrite = Total(counter, countern);
	numread = Total(counterr, counterrf);
	numsort = *nummerge;
	auxfile = *numfile;
	
	printf("\n");
	printf("%.4Lf", endtime);
	printf("\n");
	printf("%.4Lf", starttime);
	printf("\n");
	printf("%d", *counter);
	printf("\n");
	printf("%d", *countern);
	printf("\n");
	printf("%d", *counterr);
	printf("\n");
	printf("%d", *counterrf);
	printf("\n");
	printf("%d", *numfile);
	printf("\n");
	printf("%d", *nummerge);
	printf("\n");
	printf("%.4Lf", exetime);
	printf("\n");
	printf("%d", numreg);
	printf("\n");
	printf("%d", numwrite);
	printf("\n");
	printf("%d", numread);
	printf("\n");

	return;
}

