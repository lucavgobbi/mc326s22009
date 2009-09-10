typedef struct Translation{
	char *key;
	char *value;
	struct Translation *next;
}Translation;

/*Retorna uma lista com as chaves e valores vindas do arquivo de traducao, Parametro é o caminho do arquivo*/
void LoadTranslation(char *filePath);

/*Retorna o valor associado a chave, recebe como parametros a lista de tradução e uma chave*/
char *Translate(char *key);
