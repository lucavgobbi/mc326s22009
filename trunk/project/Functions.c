#include "Functions.h"

/*Funcao que recebe um campo no formato fixo, as configuracoes e retorna um ponteiro pra um campo do modo variavel*/
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

/*Funcao que deve ler o arquivo de entrada baseado nas configura��es definidas na lista inputConfiguration
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
		/*Se for o campo fim de registro, escreve quebra de linha e volta do come�o*/
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

/*Fun��o que imprime a lista fixa*/
void Printer(char *info, char *field)
{
        printf("%s", field);
        printf(" : ");
        printf("%s", info);
        printf("\n");
        return;
}

/*Fun��o que lista o arquivo de forma fixa, implementar*/
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
              /*Se for o campo fim de registro, escreve quebra de linha e volta do come�o*/
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

