#include "Functions.h"

/*Funcao que recebe um campo no formato fixo, as configuracoes e retorna um ponteiro pra um campo do modo variavel*/
void FixedToVariable(char *fixed, char *variable)
{
	int i,j;

	j=0;
	i=0;

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

/*Funcao auxiliar que imprime uma linha com o formato variavel*/
void PrintFileVar(FILE *input, InputConfiguration *inputConfiguration)
{
	char caracter;
	int byteCounter,initialPosition;

	byteCounter = 0;
	initialPosition = 0;

	caracter = (char)getc(input);
	printf("\n");
	while(feof(input)==0)
	{
		printf("%c", caracter);
		while((caracter!='\n')&&(feof(input)==0))
		{
			caracter = (char)getc(input);
			printf("%c", caracter);
			byteCounter++;
		}
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
		initialPosition = initialPosition + byteCounter + 1;
		byteCounter = 0;
		caracter = (char)getc(input);
	}

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
	int finalp, initialp, regposition, i;

	regposition = 0;
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
	InputConfiguration *aux;
	aux = inputConfiguration;
	outputFile = "out.temp";

	ConvertFile(inputFile,outputFile,inputConfiguration);
	output = fopen(outputFile,"r");

	if(output==NULL)
	{
		return;
	}

	PrintFileVar(output,inputConfiguration);

	fclose(output);
}

int NumberField(InputConfiguration *InputConf)
{
	int counter=0;

	while(InputConf != NULL)
	{
		counter++;
		InputConf = InputConf -> next;
	}
	return counter;
}


/*Fun��o que imprime a lista fixa*/
void Printer(char **vector, char **info, int number)
{
	int aux=0;

	while(aux != number)
	{
		printf("%s", vector[aux]);
		printf(": ");
		printf("%s", info[aux]);
		printf("\n");
		aux++;
	}

	printf("\n");
	return;
}

/*Fun��o que libera a memoria da string dinamica*/
void FreeString(char *string)
{
	if(string != NULL)
	{
		free(string);
	}
	return;
}

/*Fun��o que cada campo da tabela ---- lembrar de retornar o apontador para o inicio da lista do InputConfiguration */
char *ReadField(FILE *file, int finalp, int initialp)
{
	char *strfix;
	strfix=(char*)malloc(sizeof(char)*(finalp-initialp));

	if(file != NULL)
	{
		fread(strfix,initialp-finalp+1,1,file);
	}
	return strfix;
}

/*Fun��o que lista o arquivo de forma fixa, implementar*/
void ListFileFixed(FILE *file, InputConfiguration *inputConfiguration)
{
	InputConfiguration *AuxConf;
	int number=0,aux=0;
	char **vector, **info, *string;

	
	vector = (char**)malloc(sizeof(char)*(NumberField(inputConfiguration)));
	inputConfiguration = AuxConf;
	info = (char**)malloc(sizeof(char)*(NumberField(inputConfiguration)));

	while(inputConfiguration != NULL)
	{
		strcpy(vector[number],inputConfiguration->name);
		string = ReadField(file, inputConfiguration -> initialPosition, inputConfiguration -> finalPosition);
		strcpy(info[number],string); 
		number++;
		inputConfiguration = inputConfiguration -> next;
	}
	
	Printer(vector,info,number);
	while(aux != number)
	{
		FreeString(info[aux]);
		FreeString(vector[aux]);
		aux++;
	}
	free(info);
	free(vector);
	while(feof(file) != 0)
	{
		inputConfiguration = AuxConf;
		ListFileFixed(file, inputConfiguration);
	}

	return;
}
