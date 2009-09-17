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
void ListFileFixed(FILE *file, InputConfiguration *inputConfiguration);

/*Fun��o que lista o arquivo de forma variavel*/
void ListFileVariable(char *inputFile, InputConfiguration *inputConfiguration);
