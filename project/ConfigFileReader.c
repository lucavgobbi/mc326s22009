/*Aqui ser�o implementados os metodos que ir�o ler a tabela de configura��es de entrada*/
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
		printf("%s, %c, %d, %d, %c, %s\n", c->name, c->type, c->initialPosition, c->finalPosition, c->notNull, c->msg);
		c = c->next;
	}
}

/* Libera a mem�ria de lista.*/
void FreeInputConfiguration()
{
	InputConfiguration *aux;
	
	if(cfg!=NULL)
	{
		while (cfg->next!=NULL)
		{ 
			aux=cfg;
			while (aux->next->next!=NULL)
			{
				aux=aux->next;
			}
			if(aux->next->name!=NULL)
			{
			/*	free(aux->next->name);
				free(aux->next->msg);*/
			}
			free(aux->next);
			aux->next = NULL;
		}

		if(cfg->name!=NULL)
		{
			free(cfg->name);
			free(cfg->msg);
		}
		free(cfg);
		cfg = NULL;
	}
}

/*Retorna a lista de config*/
InputConfiguration *GetConfig()
{
	return cfg;
}

/*Insere na lista a nova cfgucao*/
InputConfiguration *CreateInputConfiguration(int totalSize, char string[500])
{
	InputConfiguration *new;
	int separators[6]; /*Guarda a posi��o onde ser�o est�o os separadores*/
	char *name;
	char *msg;
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
	
	/*Le a posi��o inicial*/
	temp = (char*)malloc((separators[2] - separators[1])*sizeof(char));
	strncpy(temp,string,separators[2] - separators[1] - 1);
	temp[separators[2] - separators[1]] = '\0';
	new->initialPosition = atoi(temp);
	string = string + separators[2] - separators[1];
	free(temp);

	/*Le a posi��o Final*/
	temp = (char*)malloc((separators[3] - separators[2])*sizeof(char));
	strncpy(temp,string,separators[3] - separators[2] - 1);
	temp[separators[3] - separators[2]] = '\0';
	new->finalPosition = atoi(temp);
	string = string + separators[3] - separators[2];
	free(temp);

	/*Le a obrigatoriedade*/
	new->notNull = string[0];
	string = string + separators[4] - separators[3];

	/*Le o msg*/
	msg = (char*)malloc((separators[5] - separators[4])*sizeof(char));
	strncpy(msg,string,strlen(string)-2);
	
	new->msg = msg;

	return new;
}


/*Retorna uma lista com as chaves e valores vindas do arquivo de cfgucao, Parametro � o caminho do arquivo*/
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
			/*Ao chegar ao final da linha aloca a mem�ria e insere na lista*/
			if(!feof(file))
			{
				if(list == NULL)
				{
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
