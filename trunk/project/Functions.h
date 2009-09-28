#include "Translator.h"
#include "ConfigManager.h"
#include "ErrorHandler.h"
#include "ConfigFileReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Define.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/*Fun��o que deve ler o arquivo de entrada baseado nas configura��es definidas na lista inputConfioguration
e escrever o arquivo de saida em outputfile, lembrando sempre de utilizar o separador dinamico que pode ser obtido com, (char)separator()[0]*/
void ConvertFile(char *inputFile, char *outputFile, InputConfiguration *inputConfiguration);

/*Fun��o que lista o arquivo de forma fixa*/
void ListFileFixed(char *inputFile, InputConfiguration *inputConfiguration);

/*Fun��o que lista o arquivo de forma variavel*/
void ListFileVariable(char *inputFile, InputConfiguration *inputConfiguration);

void PrintIndex(char * filePath);

/*Funcao que copia a linha do arquivo file para dentro de str e retorna o numero de caracteres da linha.*/
int CopyLine(FILE *file, char*str);

/*Funcao que cria um arquivo contendo as chaves primarias e com o endere�o fisico de cada registro
separados pelo separador dinamico encontrado no arquivo de configuracoes*/
void PrimaryKeyFile (char *inputFile, InputConfiguration *inputConfiguration);

/*Funcao que cria um arquivo ordenado a partir das chaves primarias obtidas na opcao 6*/
void IndexFile (char *inputFile, InputConfiguration *inputConfiguration);

void FindReg(char *input,InputConfiguration *inputConf, char *compare);
