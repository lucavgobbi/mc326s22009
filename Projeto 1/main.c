#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Functions.h"

/*Fun��o responsavel por imprimir o menu e retornar apenas uma op��o valida*/
char Menu()
{
	char menuOption;
	printf(Translate("MenuHeader"));
	printf(Translate("Menu1"));
	printf(Translate("Menu2"));
	printf(Translate("Menu3"));
	printf(Translate("Menu4"));
	scanf(" %c", &menuOption);
	/*Fica lendo at� que uma op��o valida seja digitada*/
	while(menuOption < 49 || menuOption > 52)
	{
		printf(Translate("MenuError"));
		scanf(" %c", &menuOption);	
	}
	return menuOption;
}

int main(int argc, char * argv[])
{
	/*Variaveis*/
	char menuOption; /*Guarda o valor digitado*/
	char outputPath[100];
	FILE *file;

	/*Carrega as configura��es*/
	if(!LoadConfig())
	{
		return 0;
	}

	/*Carrega as tradu��es*/
	LoadTranslation(translateFile());

	/*Verifica��o*/
	if(Error_InputParameters(argc, argv) || Error_FileOpen(argv[1]) || Error_FileOpen(argv[2]))
	{
		return 0;
	}

	LoadInputConfiguration(argv[1]);

	/*Mantem o menu em loop at� que a op��o de saida seja digitada*/
	menuOption = Menu();
	while(menuOption != '4')
	{
		switch (menuOption)
		{
			case '1' : 
				{
					printf(Translate("AskOutPath"));
					scanf("%s", outputPath);
					ConvertFile(argv[2], outputPath, GetConfig());
				}break;
			case '2' :
				{
					file = fopen(argv[2], "r");
					ListFileFixed(file, GetConfig());
					fclose(file);
				} break;
			case '3' : 
				{
					ListFileVariable(argv[2], GetConfig());
				} break;
		}
		menuOption = Menu();
	}
	
	return 0;
}
