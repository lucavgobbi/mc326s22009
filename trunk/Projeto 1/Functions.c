#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"

typedef enum {false=0, true=1} Boolean;

/*Funcao que retorna uma string com o caracter de fim de registro*/
char *RegisterEnd(InputConfiguration *inputConfiguration){

	InputConfiguration *aux;

	aux = inputConfiguration;

	while(aux->next!=NULL){
		aux = aux->next;
	}

	return aux->msg;

}

/*Funcao que recebe um campo no formato fixo, as configuracoes e retorna um ponteiro pra um campo do modo variavel*/
void FixedToVariable(char *fixed, char *variable)
{
	int i,j;

	j=0;
	i=0;

	while(1){
		while(fixed[i]==' '){
			i++;
		}
		if(fixed[i]=='\0'){
			variable[j]=fixed[i];
			break;
		}
		while(j!=i){
			variable[j]=' ';
			j++;
		}
		variable[j]=fixed[i];
		i++;
		j++;
	}
}

/*Funcao que verifica se um registro e valido ou se foi removido*/
Boolean VerifyRegister()
{
	return true;/*Temporario*/
}

/*Funcao auxiliar que imprime uma linha com o formato variavel*/
void PrintFileVar(FILE *input, InputConfiguration *inputConfiguration)
{
	char caracter;
	int byteCounter,initialPosition;

	byteCounter = 0;
	initialPosition = 0;

	caracter = (char)getc(input);
	printf("\n");
	while(feof(input)==0){
		printf("%c", caracter);
		while((caracter!='\n')&&(feof(input)==0)){
			caracter = (char)getc(input);
			printf("%c", caracter);
			byteCounter++;
		}
		printf("o registro se inicia na posicao %d\n", initialPosition);
		printf("o registro tem tamanho %d bytes\n", byteCounter);
		if(VerifyRegister()){
			printf("o registro e valido\n");
		}
		else{
			printf("o registro foi removido\n");
		}
		printf("\n");
		initialPosition = initialPosition + byteCounter + 1;
		byteCounter = 0;
		caracter = (char)getc(input);
	}

}

/*Funcao que deve ler o arquivo de entrada baseado nas configurações definidas na lista inputConfiguration
e escrever o arquivo de saida em outputfile, lembrando sempre de utilizar o separador dinamico que pode ser obtido com, (char)separator()[0]*/
void ConvertFile(char *inputFile, char *outputFile, InputConfiguration *inputConfiguration)
{
	FILE *input,*output;
	InputConfiguration *aux;
	char *strfix, *strvar;
	int finalp, initialp, regposition, i;

	regposition = 0;
	aux = inputConfiguration;

	/*Abre os arquivos*/
	input = fopen(inputFile,"r");
	output = fopen(outputFile,"w");

	if((input==NULL)||(output==NULL)){
		return;
	}

	/*Aloca memorias*/
	strfix = (char *)malloc(sizeof(char)*600);
	strvar = (char *)malloc(sizeof(char)*600);

	while(feof(input)==0){
		i=0;
		finalp = aux->finalPosition;
		initialp = aux->initialPosition;
		/*Percorre o arquivo ate o inicio do campo*/
		fseek(input,initialp+regposition-1,SEEK_SET);
		/*Le o campo fixo*/
		fread(strfix,finalp-initialp+2,1,input);
		strfix[finalp-initialp+1]='\0';
		/*Transforma o campo fixo em variavel*/
		FixedToVariable(strfix, strvar);
		/*Escreve o campo variavel no arquivo de saida*/
		fwrite(strvar,strlen(strvar),1,output);
		/*Pula para o proximo campo e insere o separador*/
		if(aux->next!=NULL){
			aux = aux->next;
			fwrite(separator(),1,1,output);
		}
		/*Se for o campo fim de registro, escreve quebra de linha e volta do começo*/
		else{
			fwrite("\n",1,1,output);
			aux = inputConfiguration;
			regposition = regposition+finalp+1;
		}
	}

	/*Libera memoria e fecha arquivos*/
	free(strvar);
	free(strfix);
	fclose(input);
	fclose(output);
}

/*Funcao que lista o arquivo de forma fixa, implementar*/
void ListFileFixed(char *inputFile, InputConfiguration *inputConfiguration)
{

}

/*Funcao que lista o arquivo de forma variavel*/
void ListFileVariable(char *inputFile, InputConfiguration *inputConfiguration)
{
	char *outputFile;
	FILE *output;
	InputConfiguration *aux;

	aux = inputConfiguration;
	outputFile = "out.txt";

	ConvertFile(inputFile,outputFile,inputConfiguration);
	output = fopen(outputFile,"r");

	if(output==NULL){
		return;
	}

	PrintFileVar(output,inputConfiguration);

	fclose(output);
}

