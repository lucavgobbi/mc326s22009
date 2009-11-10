#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ConfigManager.h"

cfg *config;

int LoadConfig()
{
	FILE *file;
	cfg *confTemp;
	confTemp = (cfg*)malloc(sizeof(cfg));
	confTemp->translateFile = (char *)malloc(sizeof(char)*30);
	confTemp->separator = (char *)malloc(sizeof(char)*1);
	confTemp->inputConf = (char *)malloc(sizeof(char)*30);
	file = fopen("cfg", "r");
	if (file != NULL)
	{
		fscanf(file, "%s", confTemp->translateFile);
		fscanf(file, "%s", confTemp->separator);
		fscanf(file, "%s", confTemp->inputConf);
	}
	else
	{
		printf("Configuration file not found.\n");
		return 0;
	}
	fclose(file);
	config = confTemp;
	return 1;
}

void FreeConfig()
{
	free(config->translateFile);
	free(config->separator);
	free(config);
}

char *translateFile()
{
	return config->translateFile;
}

char *separator()
{
	return config->separator;
}

char *inputConf()
{
	return config->inputConf;
}
