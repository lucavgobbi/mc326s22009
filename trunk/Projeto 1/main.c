#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Translator.h"
#include "ConfigManager.h"
#include "ErrorHandler.h"
#include "ConfigFileReader.h"

/*Fun��o responsavel por imprimir o menu e retornar apenas uma op��o valida*/
char Menu()
{
	char menuOption;
	printf("Menu:\n\n");
	printf(Translate("Menu1"));
	printf(Translate("Menu2"));
	printf(Translate("Menu3"));
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

	/*Carrega as configura��es*/
	if(!LoadConfig())
	{
		return 0;
	}

	/*Carrega as tradu��es*/
	LoadTranslation(traslateFile());

	/*Verifica��o dos parametros de entrada*/
	if(Error_InputParameters(argc, argv))
	{
		return 0;
	}

	LoadInputConfiguration(argv[1]);

	TestCfg();

	/*Mantem o menu em loop at� que a op��o de saida seja digitada*/
	menuOption = Menu();
	while(menuOption != '4')
	{
		switch (menuOption)
		{
			case '1' : break;
			case '2' : break;
			case '3' : break;
		}
		menuOption = Menu();
	}
	
	return 0;
}
