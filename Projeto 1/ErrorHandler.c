#include "ErrorHandler.h"
#include <stdio.h>
#include <stdlib.h>

/*Classe que manipula os erros, 
todas as verifica��es de erros devem ser implementadas aqui, seguindo o seguinte padr�o:
A fun��o deve retornar 0 ou 1, 1 para o caso de erro, e 0 para o caso de sucesso, todas as mensagens de erro devem ser exibidas internamente nesta classe
O padr�o de nome � Error_Descri��o da verifica��o*/

int Error_InputParameters(int argc, char * argv[])
{
	if(argc != 2)
	{
		printf("Invalid Parameters");
		return 1;
	}
	return 0;
}
