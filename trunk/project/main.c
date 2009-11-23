#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Functions.h"
#include "Analizer.h"
#include <time.h>

/*Fun��o responsavel por imprimir o menu e retornar apenas uma op��o valida*/
char Menu()
{
	char menuOption;
	printf(Translate(MenuHeader));
	printf(Translate(Menu1), GetConfig()->name);
	printf(Translate(Menu2), GetConfig()->next->name);
	printf(Translate(MenuExit));
	scanf(" %c", &menuOption);
	/*Fica lendo at� que uma op��o valida seja digitada*/
	while(menuOption < 49 || menuOption > 51)
	{
		printf(Translate(MenuError));
		scanf(" %c", &menuOption);	
	}
	return menuOption;
}

int main(int argc, char * argv[])
{
	/*Variaveis*/
	char menuOption; /*Guarda o valor digitado*/
	int *counter, *countern, *counterr, *counterrf, *numfile, *nummerge;
	clock_t endtime,starttime;

	counter = (int *)malloc(sizeof(int));
	countern = (int *)malloc(sizeof(int));
	counterr = (int *)malloc(sizeof(int));
	counterrf = (int *)malloc(sizeof(int));
	numfile = (int *)malloc(sizeof(int));
	nummerge = (int *)malloc(sizeof(int));

	starttime = Time();
	/*Carrega as configura��es*/
	if(!LoadConfig())
	{
		return 0;
	}

	/*Carrega as tradu��es*/
	LoadTranslation(translateFile());

	/*Verifica��o*/
	if(Error_InputParameters(argc, argv) || Error_FileOpen(argv[1]) )
	{
		return 0;
	}

	LoadInputConfiguration(inputConf());
	/*Mantem o menu em loop at� que a op��o de saida seja digitada*/
	menuOption = Menu();
	while(menuOption != '3')
	{
		switch (menuOption)
		{
			case '1' : 
				{
					Sort(argv[1], argv[2], atoi(argv[3]), 1, counter, countern, counterr, counterrf, numfile, nummerge);
				} break;
			case '2' :
				{
					Sort(argv[1], argv[2], atoi(argv[3]), 2, counter, countern, counterr, counterrf, numfile, nummerge);
				} break;
		}
		menuOption = Menu();
	}
	FreeTranslate();
	FreeInputConfiguration();
	FreeConfig();
	endtime=Time();/*
	print((long double)endtime/CLOCKS_PER_SEC,(long double)starttime/CLOCKS_PER_SEC,argv[1],counter,countern,counterr,counterrf,numfile,nummerge);*/
	CreateReport((long double)endtime/CLOCKS_PER_SEC,(long double)starttime/CLOCKS_PER_SEC,argv[1],counter,countern,counterr,counterrf,numfile,nummerge);
	return 0;
}
