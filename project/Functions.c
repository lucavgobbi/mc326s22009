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
e a posicao inicial do registro e retorna o tamanho do registro. Retorna -1 se o registro
estiver vazio ou se input = NULL.*/
int PrintRegister(FILE *input,int initialPosition)
{

	char *registro;
	int byteSize=-1;

	registro = (char *)malloc(sizeof(char)*600);

	if((feof(input)==0)&&(input!=NULL)){
		byteSize = CopyLine(input,registro);
		if(byteSize==0){
			return -1;
		}
		printf("\n");
		fputs(registro,stdout);
		printf(Translate(RegisterInit), initialPosition);
		printf(Translate(RegisterSize), byteSize);
		if(VerifyRegister())
		{
			printf(Translate(ValidRegister));
		}
		else
		{
			printf(Translate(RemovedRegister));
		}
	}

	free(registro);

	return byteSize;
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

/*Retorna o tamnho do arquivo*/
int FileSize(char *filePath)
{
	struct stat st;
	stat(filePath,&st);
	return st.st_size;
}

/*Imprime o tamnho do arquivo*/
void PrintFileSize(char *filePath, char *text)
{
	struct stat st;
	stat(filePath,&st);
	printf(text,FileSize(filePath));
}

void ArrayVar(char *stringfix, char *stringvar, InputConfiguration *inputConf){
	int aux1,count=0,a,b=0;
	InputConfiguration *aux;
	aux = inputConf;

	while(aux!= NULL){
	       aux1=aux->finalPosition;
	       while(stringfix[aux1-1] == ' '){
	              aux1--;
	              b++;
	       }
               for(a=0; a<aux->finalPosition-aux->initialPosition+1-b; a++){
                       stringvar[count+a]=stringfix[aux->initialPosition+a-1];
               }
               count=count+a;
               stringvar[count]=(char)separator()[0];
               count++;
               b=0;
               aux=aux->next;
        }
        return;
}

void BloqPrim(char *str){
	int aux=0;
	while(1){
	if((str[aux]=='#') && (str[aux+1]==(char)separator()[0])){
	printf("#%c",(char)separator()[0]);
	return;}
	printf("%c",str[aux]);
	aux++;}
	return;
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
	str[aux] = '\n';
	str[aux+1] = '\0';
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

	position = (regSize+1)*regNum + 1;

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

/*Funcao que recebe um arquivo de indice, e um valor a ser buscado, e retorna o int correspondente ao valor encontrado*/
int BinarySearch(char *filePath, char *value, InputConfiguration * inptCfg)
{
	FILE *file;
	int position, initial, final, comp, kSize, v1, v2;
	char c;
	char temp[50];
	char *key;
	if(!Error_FileOpen(filePath))
	{
		key = (char *)malloc(sizeof(char)*inptCfg->finalPosition);
		initial = 0;
		final = FileSize(filePath) - 1;
		file = fopen(filePath, "r");
		while(initial < final)
		{
			position =	(final + initial)/2;
			fseek(file, position, SEEK_SET);
			c = getc(file);
			/*Verifica se esta no final de uma linha para pegar um registro valido*/
			
				while(c!= '\n' && position != 0)
				{
					position = position - 1;
					fseek(file, position, SEEK_SET);
					c = getc(file);	
				}
			if (position != 0)
			{
				c = getc(file);
			}
			/*nesse ponto vai estar apontando para um indice ou para o fim do arquivo*/
			if(!feof(file))
			{
				/*agora vai ler  chave*/
				kSize = 0;
				while (c != (char)separator()[0])
				{
					key[kSize] = c;
					c= getc(file);
					kSize++;
				}
				key[kSize] = '\0';
				/*Se achou*/
				v1 = atol(key);
				v2 = atol(value);
				comp = strcmp(key,value);
				if(v1 == v2) 
				{
					fgets(temp,50,file);
					fclose(file);
					return atoi(temp);
				}
				else if(v1 > v2) /*key e maior*/
				{
					if(final == position)
					{
						fclose(file);
						return -1;
					}
					final = position;
				}
				else
				{
					if(initial == position)
					{
						fclose(file);
						return -1;
					}
					initial = position;
				}
			}
			else /*Caso em que procurando um indice chega no final do arquivo*/
			{
				fclose(file);
				return -1;
			}
		}
	}
	fclose(file);
	return -1;
	
}


/*=======================================================FUNCOES PRINCIPAIS====================================================*/






/*==========================================================* Opcao 1 *========================================================*/

/*Funcao que deve ler o arquivo de entrada baseado nas configuracoes definidas na lista inputConfiguration
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
		WriteString(output,strvar);
		/*Pula para o proximo campo e insere o separador*/
		if(aux->next!=NULL)
		{
			aux = aux->next;
			fwrite(separator(),1,1,output);
		}
		/*Se for o campo fim de registro, escreve quebra de linha e volta do comeco*/
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
	PrintFileSize(inputFile,Translate(InputSize));
	PrintFileSize(outputFile,Translate(OutputSize));
}


/*==========================================================* Opcao 2 *========================================================*/

/*Funcao que lista o arquivo de forma fixa, implementar*/
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


/*==========================================================* Opcao 3 *========================================================*/

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


/*==========================================================* Opcao 4 *========================================================*/


void FindReg(char *input,InputConfiguration *inputConf, char *compare){
      	FILE *file;
	char *stringfix,*stringvar;

	file=fopen(input,"r");
  	
	while((file!= NULL) && feof(file)==0){
		stringfix = (char *)malloc(sizeof(char)*300);	
		stringvar = (char *)malloc(sizeof(char)*300);	
		CopyLine(file,stringfix);
		ArrayVar(stringfix,stringvar,inputConf);
		if((strncmp(stringvar,compare,strlen(compare))==0) && (stringvar[strlen(compare)]==(char)separator()[0])){
			BloqPrim(stringvar);
			fclose(file);
			return;
		}
		free(stringfix);
		free(stringvar);
	}
	printf(Translate(RegisterNotFound));
	fclose(file);
	return;
}
		

/*==========================================================* Opcao 5 *========================================================*/



/*==========================================================* Opcao 6 *========================================================*/

/*Funcao que cria um arquivo contendo as chaves primarias e com o endere�o fisico de cada registro
separados pelo separador dinamico encontrado no arquivo de configuracoes*/
void PrimaryKeyFile(char *inputFile, InputConfiguration *inputConfiguration)
{
	char *keyfix, *keyvar, *adress, *aux;
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
	keyvar = (char *)malloc(sizeof(char)*600);

	while(feof(input)==0){
		/*Copia o registro para aux*/
		registerSize = CopyLine(input,aux);
		/*Retorna o primeiro campo em key*/
		keyfix = StringBreak(aux,fieldSize);
		/*Transforma a chave key fix em variavel*/
		FixedToVariable(keyfix,keyvar);
		/*Retorna o endereco em adress*/
		Adress (adress,registerSize,loopCounter);
		/*Monta o formato do indice em key*/
		IndexRegister(keyvar,adress);
		/*Escreve key no arquivo*/
		WriteString(output,keyvar);
		/*Conta o numero de loops*/
		loopCounter++;
		free(keyfix);
	}

	free(keyvar);
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
	if(!Error_FileOpen(filePath))
	{
		FILE *file;
		file = fopen(filePath, "r");
		PrintFileVar(file);
		fclose(file);
	}
	else
	{
		return;
	}
}

/*==========================================================* Opcao 10 *========================================================*/
void BuildIndex(InputConfiguration *inputConfiguration)
{
	IndexFile("_index", inputConfiguration);
}

/*==========================================================* Opcao 11 *========================================================*/

	void SearchInDisk(char * value, char * dataFilePath, InputConfiguration *inputConfiguration)
{
	int position;
	FILE *file;
	
	if(!Error_FileOpen("indexsort"))
	{
		position = BinarySearch("indexsort", value, inputConfiguration);
	}
	else
	{
		return;
	}
	if(position == -1)
	{
		printf(Translate(RegisterNotFound));
	}
	else
	{
		file = fopen(dataFilePath, "r");
		fseek(file, position -1, SEEK_SET);
		PrintRegister(file,position);
		fclose(file);
	}
}