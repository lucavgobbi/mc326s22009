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

InputConfiguration *LoadInputConfigurationAux(char *filePath);

void TestCfg();

void FreeInputConfiguration();

int GetRegisterSize();

/*Retorna a lista de config*/
InputConfiguration *GetConfig();
