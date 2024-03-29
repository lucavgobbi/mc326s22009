#include "Functions.h"
#include "Analizer.h"

typedef struct {
  int root;
  int size;
} BTree;

typedef struct {
  int nKeys;
  int keys[9];
  int position[9];
  int childs[10];
  int leaf;
  int id;
} BTNode;

int ORDER = 5;
int ParentId = -1;
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
void WriteString(FILE *file, char *str, int *counter)
{
	fwrite(str,strlen(str),1,file);
	(*counter)++;
}

/*Funcao que recebe um arquivo de indice, e um valor a ser buscado, e retorna o int correspondente ao valor encontrado*/
CharPosition BinarySearch(char *filePath, char *value, InputConfiguration * inptCfg)
{
	FILE *file;
	CharPosition Return;
	int position, initial, final, kSize, v1, v2, kPosition;
	char c;
	char temp[50];
	char *key;
	
	Return.index = -1;
	Return.data = -1;

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
				kPosition = position;
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
				if(v1 == v2) 
				{
					fgets(temp,50,file);
					fclose(file);
					Return.index = atoi(temp);
					Return.data = kPosition;
					return Return/*atoi(temp)*/;
				}
				else if(v1 > v2) /*key e maior*/
				{
					if(final == position)
					{
						fclose(file);
						return Return;
					}
					final = position;
				}
				else
				{
					if(initial == position)
					{
						fclose(file);
						return Return;
					}
					initial = position;
				}
			}
			else /*Caso em que procurando um indice chega no final do arquivo*/
			{
				fclose(file);
				return Return;
			}
		}
	}
	fclose(file);
	return Return;
	
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
	/*	WriteString(output,strvar);*/
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
	/*	WriteString(output,keyvar);*/
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
/*============================================n==============* Opcao 9 *========================================================*/

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
	CharPosition t;
	FILE *file;
	
	if(!Error_FileOpen("indexsort"))
	{
		t = (BinarySearch("indexsort", value, inputConfiguration));
		position = t.index;
		printf(" - %d - ",t.data);
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
/*Lab 03*/

char *CopyString(char * str, int size)
{
	char *s = NULL;
	s = (char *)malloc(sizeof(char)*(size));
    s[0] = '\0';
	strcpy(s, str);
	return s;
}

/*Constroi o vetor a partir do buffer, sendo que cada registro do vetor tem tamanho regSize, retorna quantos itens o vetor tem*/
int BuildVector(char *buffer, char *vet[], int regSize)
{
	int i=0, j=0, k=0;
	char *temp = NULL;
	temp = (char *)malloc(sizeof(char)*(regSize + 1));

	while (buffer[i] != '\0')
	{
		if(buffer[i] != '\n')
		{
			temp[k] = buffer[i];
			k++;
		}
		else
		{
            temp[k] = '\0';
			vet[j] = CopyString(temp, k);
			j++;
			k=0;
		}
		i++;
	}
	return j;
}

/*Ordena em memória com bubblesort sempre considerando que o campo é um texto*/
void Order(char *vet[], int vetSize, int field)
{
	int iniPos, finPos, i, j, size;
	char *v1, *v2, *aux;	

	if(field == 2)
	{
		iniPos = GetConfig()->next->initialPosition;
		finPos = GetConfig()->next->finalPosition;
	}else 
	{
		iniPos = GetConfig()->initialPosition;
		finPos = GetConfig()->finalPosition;
	}

	size = finPos - iniPos + 1;

	v1 = (char *)malloc(sizeof(char)*size);
	v2 = (char *)malloc(sizeof(char)*size);

	/*Bubble sort*/
	for(i = 0; i < vetSize; i++)
	{
		for(j = 0; j < vetSize - 1; j++)
		{
			strncpy(v1,vet[j], size);
			strncpy(v2,vet[j+1], size);
			if(strcmp(v1,v2) > 0)
			{
				aux = vet[j];
				vet[j] = vet[j+1];
				vet[j+1] = aux;
			}
		}
	}
}

void FreeVet(char *vet[], int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		free(vet[i]);
	}
}

void WriteFile(char *vet[], int vetSize, int numVet, int *counter, int *countern, int *counterr, int *counterrf, int *numfile, int *nummerge)
{
	FILE *file;
	int i;
	char str[4];
	char bl[1];
	bl[0] = '\n';
	sprintf(str, "t%d", numVet);
	file = fopen(str, "w");
	(*numfile)++;
	for(i = 0; i < vetSize; i++)
	{
		WriteString(file, vet[i], counter);
		if(i != vetSize - 1)
		{
			fwrite(bl,1,1,file);
			(*countern)++;
		}
	}
	fclose(file);
	
}

/*Divide o arquivo e chama a ordena para cada trecho do arquivo e retorna o numero de arquivos no qual foi dividido... obs: as partes do arquivo são t#*/
int Split(char *input, int memSize, int field, int *counter, int *countern, int *counterr, int *counterrf, int *numfile, int *nummerge)
{
	int fileSize, numFiles, readSize, maxRegs, i, readed, vetSize;
	char *buffer, **vet;
	FILE *file;

	vet = NULL;

	maxRegs = memSize / (GetRegisterSize() + 1); /*Numero maximo de registros por pagina*/
	fileSize = FileSize(input); /*Tamanho do arquivo*/
	readSize = (maxRegs * (GetRegisterSize() + 1)); /*Tamanho em bytes de cada conjunto de registros não quebrados, ou seja, registros inteiros que podem ser guardados na memória*/
	numFiles = fileSize / readSize; /*Numero de arquivos necessários para pegar todos registros*/
	if (fileSize % readSize > 1)
	{
		numFiles++;
	}
	file = fopen(input, "r");
	
	*numfile = numFiles;
    	buffer = (char *)malloc(sizeof(char)*readSize + 1);
	/*Iteração pra cada arquivo*/
	for(i = 0; i < numFiles; i++)
	{
		vet = (char **)malloc(sizeof(char *)*maxRegs);
		readed = fread(buffer, 1, readSize, file);
		buffer[readed] = '\0';
		vetSize = BuildVector(buffer, vet, GetRegisterSize() + 1);
		Order(vet, vetSize, field);
		WriteFile(vet, vetSize, i, counter, countern, counterr, counterrf, numfile, nummerge);
		FreeVet(vet,vetSize);
	}
	fclose(file);
	return numFiles;	
}

/*Renomeia os arquivos de entrada e nomeia o arquivos de saida automaticamente como i/2*/
void MergeTwo(char *i1, char *i2, int i, int field, int *counter, int *countern, int *counterr, int *counterrf, int *numfile, int *nummerge)
{
	FILE *f1, *f2, *output;
	char outName[5],tempName[5], c1, c2, bl[1];
	char *reg1, *reg2, *key1, *key2;
	int iniPos, finPos, keySize, regSize;

	reg1 = reg2 = key1 = key2 = NULL;


	bl[0] = '\n';

	if(field == 2)
	{
		iniPos = GetConfig()->next->initialPosition;
		finPos = GetConfig()->next->finalPosition;
	}
	else 
	{
		iniPos = GetConfig()->initialPosition;
		finPos = GetConfig()->finalPosition;
	}

	keySize = finPos - iniPos + 1;
	regSize = GetRegisterSize();

	key1 = (char *)malloc(sizeof(char)*keySize);
	key2 = (char *)malloc(sizeof(char)*keySize);

	reg1 = (char *)malloc(sizeof(char)*(regSize + 1));
	reg2 = (char *)malloc(sizeof(char)*(regSize + 1));
	
	/*Renomeia os arquivos de entrada*/
	/*Define o nome para o novo arquivo de saida*/
	sprintf(outName, "t%d", i/2);
	sprintf(tempName, "s%d", i);
	/*Abre os arquivos*/
	f1 = fopen(i1, "r");
	f2 = fopen(i2, "r");
	output = fopen(tempName, "w");
	(*numfile)++;

	/*Faz o merge*/
	fgets(reg1, regSize+1, f1);
	(*counterrf)++;
	fgets(reg2, regSize+1, f2);
	(*counterrf)++;

	while(c1 != EOF && c2 != EOF)
	{
		strncpy(key1,reg1, keySize);
		strncpy(key2,reg2, keySize);
		if(strcmp(key1,key2) > 0)
		{
			c2 = getc(f2);
			(*counterr)++;
			WriteString(output, reg2, counter);
			fwrite(bl,1,1,output);
			(*countern)++;
			fgets(reg2, regSize+1, f2);
			(*counterrf)++;
		}
		else
		{
			c1 = getc(f1);
			(*counterr)++;
			WriteString(output, reg1, counter);
			fwrite(bl,1,1,output);
			(*countern)++;
			fgets(reg1, regSize+1, f1);
			(*counterrf)++;
		}
	}

	/*Copia todo o Arq 1*/
	if(c1 != EOF)
	{
		while(c1 != EOF)
		{
			c1 = getc(f1);
			(*counterr)++;
			WriteString(output, reg1, counter);
			if(c1 != EOF)
			{
				fwrite(bl,1,1,output);
				(*countern)++;
			}
			fgets(reg1, regSize+1, f1);
			(*counterrf)++;
		}
	}
	if(c2 != EOF)
	{
		while(c2 != EOF)
		{
			c2 = getc(f2);
			(*counterr)++;
			WriteString(output, reg2, counter);
			if(c2 != EOF)
			{
				fwrite(bl,1,1,output);
				(*countern)++;
			}
			fgets(reg2, regSize+1, f2);
			(*counterrf)++;
		}
	}


	free(key1);
	free(key2);
	free(reg1);
	free(reg2);
	fclose(output);
	fclose(f1);
	fclose(f2);
	/*Deleta os arquivos de entrada*/
	remove(i1);
	remove(i2);
	rename(tempName,outName);
}

/*Faz o merge no arquivo output do numero de arquivos que foram passados*/
void Merge(char *output, int numFiles, int field, int *counter, int *countern, int *counterr, int *counterrf, int *numfile, int *nummerge)
{
	int i;
	char a[4], b[4];

	/*Vai mergeando de 2 em 2 os arquivos*/
	if(numFiles > 1)
	{
		for(i = 0; i < numFiles; i=i+2)
		{
			if(numFiles - i != 1)
			{
				sprintf(a, "t%d", i);
				sprintf(b, "t%d", i+1);
				MergeTwo(a, b, i, field, counter, countern, counterr, counterrf, numfile, nummerge);
				(*nummerge)++;
			}
			else
			{
				sprintf(a, "t%d", i);
				sprintf(b, "t%d", i/2);
				rename(a, b);
			}
	
		}
		/*Apos mergear todos os arquivos, verfica quantos arquivos resultantes sobraram e recursa, em caso de sobrar 1 arquivo, renomeia para output*/
		if(numFiles % 2 > 0)
		{
			Merge(output, (numFiles/2) + 1,field, counter, countern, counterr, counterrf, numfile, nummerge);
		}
		else
		{
			if(numFiles != 2)
			{
				Merge(output, (numFiles/2), field, counter, countern, counterr, counterrf, numfile, nummerge);
			}
			else
			{
				rename("t0", output);
			}
			
		}
	}
	else
	{
		rename("t0", output);
	}
}

/*Faz o sort*/
void Sort(char *input, char *output, int memSize, int field, int *counter, int *countern, int *counterr, int *counterrf, int *numfile, int *nummerge)
{
	Merge(output, Split(input, memSize, field, counter, countern, counterr, counterrf, numfile, nummerge), field, counter, countern, counterr, counterrf, numfile, nummerge);
}

/*========================== LAB 4 ==================================*/

void SetOrder(int order)
{
	ORDER = order;
}

void BatchInsert(char *inputFile, InputConfiguration *inputConfiguration)
{
	char *keyfix, *adress, *aux;
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
		keyfix = StringBreak(aux,fieldSize);
		/*Retorna o endereco em adress*/
		Adress (adress,registerSize,loopCounter);
		/*Monta o formato do indice em key*/
		IndexRegister(keyfix,adress);
		/*Escreve key no arquivo*/
		InsertTree(atol(keyfix), atol(adress), 0);
	/*	WriteString(output,keyvar);*/
		/*Conta o numero de loops*/
		loopCounter++;
		free(keyfix);
	}

	free(aux);
	free(adress);
	fclose(input);
	fclose(output);
}

/*Grava os dados do no em memoria para o arquivo*/
void WriteNode(BTNode *node) 
{
	FILE *file;
	char filename[10];
	int i;
	
	sprintf(filename, "%d%s", node->id, "TREE");
	file = fopen(filename, "w"); 
	
	  /*Gravacao se e folha ou no*/
	fprintf(file, "%d\n", node->leaf);

	
	/*Gravacao do numero de chaves*/
	fprintf(file, "%d\n", node->nKeys);

	/*Gravacao das chaves*/
	for (i = 0; i < node->nKeys; ++i) 
	{
		fprintf(file, "%d ", node->keys[i]);
	}
	
	fprintf(file, "\n");
	
	/*Gravacao das chaves*/
	for (i = 0; i < node->nKeys; ++i) 
	{
		fprintf(file, "%d ", node->position[i]);
	}

	fprintf(file, "\n");

	/*Gravacao dos apontadores ou nrrs, caso seja folha*/
	for (i = 0; i <= node->nKeys; ++i) 
	{
		fprintf(file, "%d ", node->childs[i]);
	}

	fprintf(file, "\n");
	fclose(file); 
}

int ReadNode(BTNode *node, int nodeId) 
{
	  
	FILE *file;
	char filename[10];
	int i;
	
	/*Colocando id do arquivo na estrutura*/
	node->id = nodeId;
	
	sprintf(filename, "%d%s", nodeId, "TREE");
	file = fopen(filename, "r");
	
	if (file) {
		
		fscanf(file, "%d", &node->leaf);
		
		fscanf(file, "%d", &node->nKeys);
		
		/*leitura das chaves*/
		for ( i = 0; i < node->nKeys; ++i) 
		{
			fscanf(file, "%d", &node->keys[i]);
		}
		
		for ( i = 0; i < node->nKeys; ++i) 
		{
			fscanf(file, "%d", &node->position[i]);
		}
		
		for ( i = 0; i <= node->nKeys; ++i) 
		{
			fscanf(file, "%d", &node->childs[i]);
		}

		fclose(file); 
		return 1;
		
	} 
	else 
	{
		return 0; /* Nao existe o arquivo. */
	}

}

BTNode * CreateNode() 
{
  BTNode * temp = (BTNode*)malloc(sizeof(BTNode));
  temp->nKeys = 0;
  return temp;
}

void CreateRoot() 
{
	int i;
	BTNode *root;
	
	root = CreateNode();
	root->leaf = 1; /*A raiz é nó folha quando criada*/
	root->id = 0;
	for (i = 0; i < ORDER; i++) 
	{
		root->keys[i] = -1;
		root->position[i] = -1;
		root->childs[i] = -1;
	}
	root->childs[i] = -1;
	
	WriteNode(root);
	free(root);
}

int SplitNode(int key, int pos, int nodeId)
{
	BTNode *node, *nodeParent;

	node = CreateNode();
	
	/*Se tem um pai*/
	if(ParentId > -1)
	{
		nodeParent = CreateNode();
		ReadNode(node, nodeId);
	}
	else /*Se não tem pai, ou sejá, é raiz*/
	{
		
	}
	return 0;
}

void RootSplit(int key, int pos, int nodeId)
{
	int i, j;
	BTNode *node, *root, *node2;
	node = CreateNode();
	root = CreateNode();
	node2 = CreateNode();
	
	for (i = 0; i < ORDER; i++) 
	{
		root->keys[i] = -1;
		root->position[i] = -1;
		root->childs[i] = -1;
		node2->keys[i] = -1;
		node2->position[i] = -1;
		node2->childs[i] = -1;
	}
	
	ReadNode(node, nodeId);
	i = ORDER/2;
	j = 0;
	
	root->id = 0;
	node->id = 1;
	node2->id = 2;
	
	root->keys[0] = node->keys[i];
	root->position[0] = node->position[i];
	node->keys[i] = -1;
	node->position[i] = -1;
	
	root->childs[0] = 1;
	root->childs[1] = 2;
	node->nKeys = i;
	node2->nKeys = i-1;
	/*Copia os itens*/
	for(i = i+1; i < ORDER - 1; i++)
	{
		node2->keys[j] = node->keys[i];
		node2->position[j] = node->position[i];
		node->keys[i] = -1;
		node->position[i] = -1;
		j++;
	}
	
	for(i = 0; i < ORDER - 1; i++)
	{
		node2->childs[i] = -1;
		node->childs[i] = -1;
	}
	
	root->nKeys = 1;
	node->leaf = 1;
	node2->leaf = 1;
	
	WriteNode(root);
	WriteNode(node);
	WriteNode(node2);
	
	free(root);
	free(node);
	free(node2);
	
	InsertTree(key, pos, 0);
}

int InsertTree(int key, int pos, int nodeId) 
{
	int i = 0, j, result = false, size, parent; /*, idChild*/
	BTNode *node;

	node = CreateNode();
	ReadNode(node, nodeId);
	parent = ParentId;
	/*Procura a posição*/
	while (node->keys[i] <= key && i < node->nKeys) 
	{
		i++;
	}
	
	/*Se achou*/
	if (i > 0)
	{
		if (node->keys[i-1] == key)
		{
			return result;
		}
	}
	
	/*se estiver em uma folha*/
	if (node->leaf == 1)
	{
		/*Se não estourou a ordem*/
		if(node->nKeys < ORDER-1)/* Abre espaco para a nova chave no vetor de chaves do noh. */
		{
			j = node->nKeys;
			node->childs[j+1] = node->childs[j];
			for(; j > i; j--) 
			{
				node->childs[j] = node->childs[j-1];
				node->keys[j] = node->keys[j-1];
				node->position[j] = node->position[j-1];
			}
			node->keys[i] = key;
			node->position[i] = pos;

			size = (node->nKeys)++;

			WriteNode(node);
			free(node);
			result = 1;
		}
		else /*Faz o split*/
		{
			/*Se for pai*/
			if (parent == -1)
			{
				RootSplit(key, pos, nodeId);
			}
		}
	}
	else /*Se não for folha procura a folha onde deve inserir*/
	{
		ParentId = nodeId;
		result = InsertTree(key, pos, node->childs[i]);
	}
	
	if (size == ORDER) return -1; /*Estouro, deve ser tratado, pois o estouro pode nao ser real*/
	else return result;	
}
