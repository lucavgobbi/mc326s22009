#include "Translator.h"
#include "ConfigManager.h"
#include "ErrorHandler.h"
#include "ConfigFileReader.h"

/*Função que deve ler o arquivo de entrada baseado nas configurações definidas na lista inputConfioguration
e escrever o arquivo de saida em outputfile, lembrando sempre de utilizar o separador dinamico que pode ser obtido com, (char)separator()[0]*/
void ConvertFile(char *inputFile, char *outputFile, InputConfiguration *inputConfiguration);

/*Função que lista o arquivo de forma fixa*/
void ListFileFixed(char *inputFile, InputConfiguration *inputConfiguration);
/*Função que lista o arquivo de forma variavel*/
void ListFileVariable(char *inputFile, InputConfiguration *inputConfiguration);
