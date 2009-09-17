#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Translator.h"

Translation *trans = NULL;

/*Insere na lista a nova transucao*/
Translation *CreateTranslation(int size, int posSeparator, char string[500])
{
	Translation *new;
	char *key;
	char *value;

	key = (char*)malloc((posSeparator + 1)*sizeof(char));
	strncpy(key,string,posSeparator);
	key[posSeparator + 1] = '\0';

	string = string + posSeparator + 1;
	value = (char*)malloc((size - posSeparator + 1)*sizeof(char));
	strncpy(value,string,size - posSeparator);
	value[size - posSeparator + 1] = '\0';
	
	new = (Translation *)malloc(sizeof(Translation));
	new->key = key;
	new->value = value;
	return new;
}

/* Libera a mem�ria de lista.*/
void FreeTranslate()
{
	Translation *aux;
	
	if(trans!=NULL)
	{
		while (trans->next!=NULL)
		{ 
			aux=trans;
			while (aux->next->next!=NULL)
			{
				aux=aux->next;
			}
			if(aux->next->key!=NULL)
			{
				free(aux->next->key);
				free(aux->next->value);
			}
			free(aux->next);
			aux->next = NULL;
		}
		if(trans->key!=NULL)
		{
			free(trans->key);
			free(trans->value);
		}
		free(trans);
		trans = NULL;
	}
}

/*Retorna uma lista com as chaves e valores vindas do arquivo de transucao, Parametro � o caminho do arquivo*/
void LoadTranslation(char *filePath)
{
	FILE *file;
	Translation *list, *aux;
	int stringSize, posSeparator;
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
				if(temp[stringSize] == '#')
				{
					posSeparator = stringSize;
				}
				stringSize++;
				temp[stringSize] = getc(file);
			}
			while (temp[stringSize] != '\n' && !feof(file));
			/*Ao chegar ao final da linha aloca a mem�ria e insere na lista*/
			if(!feof(file))
			{
				if(list == NULL)
				{
					list = CreateTranslation(stringSize, posSeparator, temp);
					list->next = NULL;
				}
				else
				{
					aux = CreateTranslation(stringSize, posSeparator, temp);
					aux->next = list;
					list = aux;
				}
			}
		}
	}
	fclose(file);
	trans = list;
}

/*Retorna o valor associado a chave, recebe como parametros a lista de transu��o e uma chave*/
char *Translate(char *key)
{
	Translation *aux;
	aux = trans;
	while (aux != NULL)
	{
		if(strcmp(aux->key,key) == 0)
		{
			return aux->value;
		}
		else
		{
			aux = aux->next;
		}
	}
	return key;
}
