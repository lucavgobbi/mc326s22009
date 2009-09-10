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
	confTemp->traslateFile = (char *)malloc(sizeof(char)*30);
	confTemp->separator = (char *)malloc(sizeof(char)*1);
	file = fopen("cfg", "r");
	if (file != NULL)
	{
		fscanf(file, "%s", confTemp->traslateFile);
		fscanf(file, "%s", confTemp->separator);
	}
	else
	{
		printf("Configuration file not found.");
		return 0;
	}
	fclose(file);
	config = confTemp;
	return 1;
}

char *traslateFile()
{
	return config->traslateFile;
}

char *separator()
{
	return config->separator;
}
