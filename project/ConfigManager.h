typedef struct cfg{
	char *translateFile;
	char *separator;
	char *inputConf;
}cfg;

int LoadConfig();

char *translateFile();

char *separator();

char *inputConf();

void FreeConfig();
