typedef struct InputConfiguration{
	char *name;
	char type;
	int initialPosition;
	int finalPosition;
	char notNull;
	char *msg;
	struct InputConfiguration *next;
}InputConfiguration;

void LoadInputConfiguration(char *filePath);

void TestCfg();
