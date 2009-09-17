typedef struct InputConfiguration{
	char *name;
	char type;
	int initialPosition;
	int finalPosition;
	char notNull;
	char *msg;
	struct InputConfiguration *next;
}InputConfiguration;

/*Carrega as configura��es*/
void LoadInputConfiguration(char *filePath);

void TestCfg();

void FreeInputConfiguration();

/*Retorna a lista de config*/
InputConfiguration *GetConfig();
