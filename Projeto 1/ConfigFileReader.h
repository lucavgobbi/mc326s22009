typedef struct InputConfiguration{
	char *name;
	char type;
	int initialPosition;
	int finalPosition;
	char notNull;
	char *msg;
	struct InputConfiguration *next;
}InputConfiguration;

/*Carrega as configurações*/
void LoadInputConfiguration(char *filePath);

void TestCfg();

/*Retorna a lista de config*/
InputConfiguration *GetConfig();
