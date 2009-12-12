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
	
	CreateRoot();
	
	/*Mantem o menu em loop at� que a op��o de saida seja digitada*/
	menuOption = Menu();
	while(menuOption != '3')
	{
		switch (menuOption)
		{
			case '1' :
				{
					PrimaryKeyFile(argv[1], GetConfig());
				}
			case '2' :
				{
					InsertTree(7, 7000, 0);
					InsertTree(1, 1000, 0);
					InsertTree(3, 3000, 0);
					InsertTree(2, 2000, 0);
					InsertTree(5, 5000, 0);
					InsertTree(6, 6000, 0);
				}
		}
		menuOption = Menu();
	}
	FreeTranslate();
	FreeInputConfiguration();
	FreeConfig();
	return 0;
}
