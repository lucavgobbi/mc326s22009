#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Functions.h"

/*Fun��o responsavel por imprimir o menu e retornar apenas uma op��o valida*/
char Menu()
{
	char menuOption;
	printf(Translate(MenuHeader));
	printf(Translate(Menu1));
	printf(Translate(Menu2));
	printf(Translate(Menu3));
	printf(Translate(Menu4));
	printf(Translate(Menu6));
	printf(Translate(Menu7));
	printf(Translate(Menu8));
	printf(Translate(Menu9));
	printf(Translate(MenuExit));
	scanf(" %c", &menuOption);
	/*Fica lendo at� que uma op��o valida seja digitada*/
	while(menuOption < 96 || menuOption > 108)
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
	char  outputPath[100];
	char compare[6];

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
	while(menuOption != 'k')
	{
		switch (menuOption)
		{
			case 'a' : 
				{
					printf(Translate(AskOutPath));
					scanf("%s", outputPath);
					ConvertFile(argv[2], outputPath, GetConfig());
				} break;
			case 'b' :
				{
					printf("\n");
				        printf(Translate(RegisterBegin));
				        printf("\n");
				        ListFileFixed(argv[2], GetConfig());
				} break;
			case 'c' : 
				{
					ListFileVariable(argv[2], GetConfig());
				} break;
			case 'd' :
				{
					printf(Translate(EnterPK));
				        printf("\n");
					scanf("%s", compare);
					FindReg(argv[2],GetConfig(),compare);
				        printf("\n");
				}
			case 'e' :
				{
					PrimaryKeyFile(argv[2], GetConfig());
				} break;
			case 'f' :
				{
					IndexFile(argv[2], GetConfig());
				} break;
			case 'g' : 
				{
					PrintIndex("index");
				} break;
			case 'h' : 
				{
					PrintIndex("indexsort");
					
				} break;
			case 'i' :
				{
					printf(Translate(EnterPK));
				    printf("\n");
					scanf("%s", compare);
					printf("Resultado: %d",BinarySearch("indexsort", compare, GetConfig()));
				}
		}
		menuOption = Menu();
	}
	FreeTranslate();
	FreeInputConfiguration();
	FreeConfig();
	return 0;
}
