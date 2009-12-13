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
	printf(Translate(Menu1));
	printf(Translate(MenuExit));
	scanf(" %c", &menuOption);
	/*Fica lendo at� que uma op��o valida seja digitada*/
	while(menuOption < 49 || menuOption > 52)
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
	
	SetOrder(atoi(argv[2]));
	
	CreateRoot();
	
	/*Mantem o menu em loop at� que a op��o de saida seja digitada*/
	menuOption = Menu();
	while(menuOption != '3')
	{
		switch (menuOption)
		{
			case '1' :
				{
					BatchInsert(argv[1], GetConfig());
				}
		}
		menuOption = Menu();
	}
	FreeTranslate();
	FreeInputConfiguration();
	FreeConfig();
	return 0;
}
