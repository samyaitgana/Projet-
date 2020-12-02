#ifndef __H_UTILS
#define __H_UTILS

#include <stdbool.h>

char *stringToBin(char *string);
char *readFile(FILE *f);
char *readFilePath(char *path);
void writeFile(FILE *f, char *string);
void writeFilePath(char *path, char *string);
void fileToBin(char *path, char *binPath);
long unsigned int fileSize(char *path);
bool startsWith(char *prefix, char *string);

#endif
