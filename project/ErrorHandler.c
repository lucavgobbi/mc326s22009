#include "ErrorHandler.h"
#include <stdio.h>
#include <stdlib.h>

/*Classe que manipula os erros, 
todas as verifica��es de erros devem ser implementadas aqui, seguindo o seguinte padr�o:
A fun��o deve retornar 0 ou 1, 1 para o caso de erro, e 0 para o caso de sucesso, todas as mensagens de erro devem ser exibidas internamente nesta classe
O padr�o de nome � Error_Descri��o da verifica��o*/

int Error_InputParameters(int argc, char * argv[])
{
	if(argc != 3)
	{
		printf("Incorrect parameters number");
		return 1;
	}
	return 0;
}

int Error_FileOpen(char * filePath)
{
	FILE *file;
	file = fopen(filePath, "r");

	if (file != NULL)
	{
		fclose(file);
		return 0;
	}
	printf("Error while opening file %s\n", filePath);
	return 1;
}
