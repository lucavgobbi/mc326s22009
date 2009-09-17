typedef struct cfg{
	char *translateFile;
	char *separator;
}cfg;

int LoadConfig();

char *translateFile();

char *separator();

void FreeConfig();
