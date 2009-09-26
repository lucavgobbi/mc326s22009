#include "Functions.h"

/*=======================================================FUNCOES AUXILIARES====================================================*/

/*Funcao que recebe um campo no formato fixo e retorna um ponteiro pra um campo do modo variavel*/
void FixedToVariable(char *fixed, char *variable)
{
	int i=0,j=0;

	while(1)
	{
		while(fixed[i]==' ')
		{
			i++;
		}
		if(fixed[i]=='\0')
		{
			variable[j]=fixed[i];
			break;
		}
		while(j!=i)
		{
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

/*Funcao auxiliar que imprime apenas um registro. Recebe como parametros o stream do arquivo
e a posicao inicial do registro e retorna o tamanho do registro. Retorna 0 se o registro
estiver vazio ou se input = NULL.*/
int PrintRegister(FILE *input,int initialPosition)
{

	char caracter;
	int byteCounter;

	byteCounter = 0;

	/*Verfica primeiro caracter para ver se nao e eof*/
	caracter = (char)getc(input);

	if((feof(input)==0)&&(input!=NULL)){
		while((caracter!='\n')&&(feof(input)==0))
		{
			printf("%c", caracter);
			caracter = (char)getc(input);
			byteCounter++;
		}
		printf("\n");

		printf(Translate("RegisterInit"), initialPosition);
		printf(Translate("RegisterSize"), byteCounter);
		if(VerifyRegister())
		{
			printf(Translate("ValidRegister"));
		}
		else
		{
			printf(Translate("RemovedRegister"));
		}
	}

	 return byteCounter;
}

/*Funcao auxiliar que imprime uma linha com o formato variavel*/
void PrintFileVar(FILE *input)
{
	int initialPosition;

	initialPosition = 0;

	printf("\n");
	while(feof(input)==0)
	{
		initialPosition = initialPosition + PrintRegister(input,initialPosition) + 1;
	}
	printf("\n");
}

void PrintFileSize(char *filePath, char *text)
{
	struct stat st;
	stat(filePath,&st);
	printf(text,st.st_size);
}

/*Funcao que imprime a lista fixa*/
void Printer(char *info, char *field)
{
        printf("%s", field);
        printf(" : ");
        printf("%s", info);
        printf("\n");
        return;
}

/*Funcao que copia a linha do arquivo file para dentro de str e retorna o numero de caracteres da linha.*/
int CopyLine(FILE *file, char*str)
{
	int aux;
	char carac;
	aux = 0;
	carac = (char)getc(file);
	while(carac != '\n' && !feof(file))
	{
		str[aux] = carac;
		carac = (char)getc(file);
		aux++;
	}
	str[aux+1] = '\n';
	return aux;
}

/*Recebe uma string e retorna uma com size bytes dela*/
char* StringBreak(char *str, int size)
{
	char *ans;

	ans = (char *)malloc(strlen(str)*sizeof(char));

	strncpy(ans,str,size);
	ans[size]='\0';

	return ans;
}

/*Retorna o endereco do registro no arquivo*/
void Adress(char* adress, int regSize, int regNum)
{
	int position;

	position = regSize*regNum+1;

	sprintf(adress, "%d", position);

}

/*Recebe as duas strings com o conteudo do indice e retorna uma string
no formato do indice em str1*/
void IndexRegister(char *str1, char *str2)
{
	strcat(str1,separator());
	strcat(str1,str2);
	strcat(str1,"\n");
}

/*Funcao que copia o conteudo de str para dentro do arquivo file*/
void WriteString(FILE *file, char *str)
{
	fwrite(str,strlen(str),1,file);
}





/*=======================================================FUNCOES PRINCIPAIS====================================================*/






/*==========================================================* Opcao 1 *========================================================*/

/*Funcao que deve ler o arquivo de entrada baseado nas configuraï¿½ï¿½es definidas na lista inputConfiguration
e escrever o arquivo de saida em outputfile, lembrando sempre de utilizar o separador dinamico que pode ser obtido com, (char)separator()[0]*/
void ConvertFile(char *inputFile, char *outputFile, InputConfiguration *inputConfiguration)
{
	FILE *input,*output;
	InputConfiguration *aux;
	char *strfix, *strvar;
	int finalp, initialp, regposition = 0;

	aux = inputConfiguration;

	/*Abre os arquivos*/
	input = fopen(inputFile,"r");
	output = fopen(outputFile,"w");

	if((input==NULL)||(output==NULL))
	{
		return;
	}

	/*Aloca memorias*/
	strfix = (char *)malloc(sizeof(char)*600);
	strvar = (char *)malloc(sizeof(char)*600);

	while(feof(input)==0)
	{
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
		if(aux->next!=NULL)
		{
			aux = aux->next;
			fwrite(separator(),1,1,output);
		}
		/*Se for o campo fim de registro, escreve quebra de linha e volta do comeï¿½o*/
		else
		{
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
	PrintFileSize(inputFile,Translate("InputSize"));
	PrintFileSize(outputFile,Translate("OutputSize"));
}


/*==========================================================* Opcao 2 *========================================================*/

/*Funcao que lista o arquivo de forma variavel
Para reutilizacao das funcoes ja existentes a funcao cria um arquivo temporario de saida
*/
void ListFileVariable(char *inputFile, InputConfiguration *inputConfiguration)
{
	char *outputFile;
	FILE *output;
	outputFile = "out.temp";

	ConvertFile(inputFile,outputFile,inputConfiguration);
	output = fopen(outputFile,"r");

	if(output==NULL)
	{
		return;
	}

	PrintFileVar(output);

	fclose(output);
}


/*==========================================================* Opcao 3 *========================================================*/

/*Funï¿½ï¿½o que lista o arquivo de forma fixa, implementar*/
void ListFileFixed(char *inputFile, InputConfiguration *inputConfiguration)
{
        FILE *input;
        InputConfiguration *aux;
        char *strfix;
        int finalp, initialp, regposition=0;

		aux = inputConfiguration;
        /*Abre os arquivos*/
        input = fopen(inputFile,"r");

 	if(input==NULL)
        {
              return;
        }

        /*Aloca memorias*/
        strfix = (char *)malloc(sizeof(char)*600);
        while(feof(input)==0)
        {
              finalp = aux->finalPosition;
              initialp = aux->initialPosition;
              /*Percorre o arquivo ate o inicio do campo*/
              fseek(input,initialp+regposition-1,SEEK_SET);
              /*Le o campo fixo*/
              fread(strfix,finalp-initialp+2,1,input);
              strfix[finalp-initialp+1]='\0';
              /*Escreve o campo variavel no arquivo de saida*/
              if(aux -> next!= NULL)
              {
                       Printer(strfix, aux->name);
                       aux=aux->next;
              }
              /*Se for o campo fim de registro, escreve quebra de linha e volta do comeï¿½o*/
              else
              {
                      printf("\n");
                      aux = inputConfiguration;
                      regposition = regposition+finalp+1;
              }
        }
        /*Libera memoria e fecha arquivos*/
        free(strfix);
        fclose(input);
        return;
}


/*==========================================================* Opcao 4 *========================================================*/



/*==========================================================* Opcao 5 *========================================================*/



/*==========================================================* Opcao 6 *========================================================*/

/*Funcao que cria um arquivo contendo as chaves primarias e com o endereço fisico de cada registro
separados pelo separador dinamico encontrado no arquivo de configuracoes*/
void PrimaryKeyFile(char *inputFile, InputConfiguration *inputConfiguration)
{
	char *key, *adress, *aux;
	int registerSize, fieldSize, loopCounter=0;
	FILE *input, *output;

	fieldSize = (inputConfiguration->finalPosition) - (inputConfiguration->initialPosition) + 1;

	input = fopen(inputFile,"r");
	output = fopen("index","w");

	if(input==NULL)
	{
		return;
	}

	aux = (char *)malloc(sizeof(char)*600);
	adress = (char *)malloc(sizeof(char)*10);

	while(feof(input)==0){
		/*Copia o registro para aux*/
		registerSize = CopyLine(input,aux);
		/*Retorna o primeiro campo em key*/
		key = StringBreak(aux,fieldSize);
		/*Retorna o endereço em adress*/
		Adress (adress,registerSize,loopCounter);
		/*Monta o formato do indice em key*/
		IndexRegister(key,adress);
		/*Escreve key no arquivo*/
		WriteString(output,key);
		/*Conta o numero de loops*/
		loopCounter++;
		free(key);
	}

	free(aux);
	free(adress);
	fclose(input);
	fclose(output);
}


/*==========================================================* Opcao 7 *========================================================*/

/*Funcao que cria um arquivo ordenado a partir das chaves primarias obtidas na opcao 6*/
void IndexFile (char *inputFile, InputConfiguration *inputConfiguration)
{

	PrimaryKeyFile(inputFile,inputConfiguration);

	if ( fork()==0 ){
		execl("/usr/bin/sort","sort","-nk1,2","-t",separator(),"-o","indexsort","index",NULL);
	}
}


/*==========================================================* Opcao 8 *========================================================*/
/*==========================================================* Opcao 9 *========================================================*/

void PrintIndex(char * filePath)
{
	InputConfiguration *tmpCfg;
	tmpCfg = LoadInputConfigurationAux("index.dat");
	ListFileFixed(filePath, tmpCfg);
}
