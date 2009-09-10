#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Functions.h"


/*Função responsavel por imprimir o menu e retornar apenas uma opção valida*/
char Menu()
{
	char menuOption;
	printf("Menu:\n\n");
	printf(Translate("Menu1"));
	printf(Translate("Menu2"));
	printf(Translate("Menu3"));
	scanf(" %c", &menuOption);
	/*Fica lendo até que uma opção valida seja digitada*/
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

	/*Carrega as configurações*/
	if(!LoadConfig())
	{
		return 0;
	}

	/*Carrega as traduções*/
	LoadTranslation(traslateFile());

	/*Verificação dos parametros de entrada*/
	if(Error_InputParameters(argc, argv))
	{
		return 0;
	}

	LoadInputConfiguration(argv[1]);

	/*Mantem o menu em loop até que a opção de saida seja digitada*/
	menuOption = Menu();
	while(menuOption != '4')
	{
		switch (menuOption)
		{
			case '1' : 
				{
					printf(Translate("AskOutPath"));
					scanf("%s", outputPath);
					ConvertFile(argv[1], outputPath, GetConfig());
				}break;
			case '2' :
				{
					ListFileFixed(argv[1], GetConfig());
				} break;
			case '3' : 
				{
					ListFileVariable(argv[1], GetConfig());
				} break;
		}
		menuOption = Menu();
	}
	
	return 0;
}
