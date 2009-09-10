/*Aqui serão implementados os metodos que irão ler a tabela de configurações de entrada*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ConfigFileReader.h"

InputConfiguration *cfg = NULL;

void TestCfg()
{
	InputConfiguration *c;
	c = cfg;
	while(c != NULL)
	{
		printf("%s, %c, %d\n", c->name, c->type, c->initialPosition);
		c = c->next;
	}
}

/*Insere na lista a nova cfgucao*/
InputConfiguration *CreateInputConfiguration(int totalSize, char string[500])
{
	InputConfiguration *new;
	int separators[6]; /*Guarda a posição onde serão estão os separadores*/
	char *name;
	/*char *msg;*/
	char *temp;
	int i, j;/*, initialPosition, finalPosition;*/
	i = 0;
	j = 0;

	new = (InputConfiguration *)malloc(sizeof(InputConfiguration));

	while(i < totalSize)
	{
		if(string[i] == '|')
		{
			separators[j] = i;
			j++;
		}
		i++;
	}
	/*Le o nome*/
	name = (char*)malloc((separators[0] + 1)*sizeof(char));
	strncpy(name,string,separators[0]);
	name[separators[0] + 1] = '\0';
	new->name = name;
	string = string + separators[0] + 1;

	/*Le o tipo*/
	new->type = string[0];
	string = string + 2;
	
	/*Le o tamanho*/
	temp = (char*)malloc((separators[2] - separators[1] + 1)*sizeof(char));
	strncpy(temp,string,separators[2] - separators[1]);
	temp[separators[2] - separators[1] + 1] = '\0';
	new->initialPosition = (int)temp;
	string = string + separators[2] - separators[1] + 1;
	return new;
}


/*Retorna uma lista com as chaves e valores vindas do arquivo de cfgucao, Parametro é o caminho do arquivo*/
void LoadInputConfiguration(char *filePath)
{
	FILE *file;
	InputConfiguration *list, *aux;
	int stringSize;
	char temp[500]; /*Vetor temporario onde serao armazenadas as string*/
	file = fopen(filePath, "r");
	list = NULL;
	if (file != NULL)
	{
		while(!feof(file))
		{
			stringSize = 0;
			temp[stringSize] = getc(file);
			do
			{
				stringSize++;
				temp[stringSize] = getc(file);
			}
			while (temp[stringSize] != '\n' && !feof(file));
			temp[stringSize+1] = '\0';
			/*Ao chegar ao final da linha aloca a memória e insere na lista*/
			if(!feof(file))
			{
				if(list == NULL)
				{
					printf("Entrou");
					list = CreateInputConfiguration(stringSize, temp);
					aux = list;
				}
				else
				{
					aux->next = CreateInputConfiguration(stringSize, temp);
					aux = aux->next;
					aux->next = NULL;
				}
			}
		}
	}
	fclose(file);
	cfg = list;
}
