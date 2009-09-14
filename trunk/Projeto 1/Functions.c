#include <stdio.h>
#include <stdlib.h>
#include "Functions.h"

/*Colocar Mensagens dos printfs e defines nos seus respectivos lugares*/

#define RegisterEnd "#"
typedef enum {false=0, true=1} Boolean;

/*Função que recebe um campo no formato fixo, as configurações e retorna um ponteiro pra um campo do modo variavel*/
void FixedToVariable(char *fixed, InputConfiguration *inputConfiguration, char *variable)
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

/*Função auxiliar que imprime uma linha com o formato variavel*/
void PrintFileVar(FILE *input)
{
	char caracter;
	int byteCounter,initialPosition;

	byteCounter = 0;
	initialPosition = 0;

	while(feof(input)==0){
		do{
			caracter = (char)getc(input);
			printf("%c", caracter);
			byteCounter++;
		}while(caracter!=(char)RegisterEnd);
		printf("o registro se inicia na posicao %d\n", initialPosition);
		printf("o registro tem tamanho %d bytes\n", byteCounter);
		if(VerifyRegister()){
			printf("o registro e valido\n");
		}
		else{
			printf("o registro foi removido\n");
		}
		printf("\n");
	}
}

/*Função que deve ler o arquivo de entrada baseado nas configurações definidas na lista inputConfiguration
e escrever o arquivo de saida em outputfile, lembrando sempre de utilizar o separador dinamico que pode ser obtido com, (char)separator()[0]*/
void ConvertFile(char *inputFile, char *outputFile, InputConfiguration *inputConfiguration)
{
	FILE *input,*output;
	InputConfiguration *aux;
	char *strfix, *strvar;
	int finalp, initialp;

	aux = inputConfiguration;
	input = fopen(inputFile,"r");
	output = fopen(outputFile,"w");

	while(feof(input)==0){
		finalp = inputConfiguration->finalPosition;
		initialp = inputConfiguration->initialPosition;
		/*Le o campo*/
		fread(strfix,initialp-finalp+1,1,input);
		/*Transforma o campo fixo em variavel*/
		FixedToVariable(strfix, inputConfiguration, strvar);
		/*Escreve o campo variavel no arquivo de saida*/
		fwrite(strvar,sizeof(strvar),1,output);
		fwrite(separator(),1,1,output);
		/*Pula para o proximo campo*/
		if(aux->next!=NULL){
			aux = aux->next;
			/*Se for o campo fim de registro, marca e volta do começo*/
			if(aux->next==NULL){
				fwrite(RegisterEnd,1,1,output);
				aux = inputConfiguration;
			}
		}
	}
}

/*Função que lista o arquivo de forma fixa, implementar*/
void ListFileFixed(char *inputFile, InputConfiguration *inputConfiguration)
{

}

/*Função que lista o arquivo de forma variavel*/
void ListFileVariable(char *inputFile, InputConfiguration *inputConfiguration)
{
	char *outputFile;
	FILE *output;
	InputConfiguration *aux;

	aux = inputConfiguration;
	outputFile = "out.txt";

	ConvertFile(inputFile,outputFile,inputConfiguration);
	output = fopen(outputFile,"r");

	PrintFileVar(output);
}

