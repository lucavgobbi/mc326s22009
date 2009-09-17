typedef struct Translation{
	char *key;
	char *value;
	struct Translation *next;
}Translation;

/*Retorna uma lista com as chaves e valores vindas do arquivo de traducao, Parametro � o caminho do arquivo*/
void LoadTranslation(char *filePath);

/*Retorna o valor associado a chave, recebe como parametros a lista de tradu��o e uma chave*/
char *Translate(char *key);

void FreeTranslate();
