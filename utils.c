#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char *stringToBin(char *string) {
	long unsigned int len = strlen(string);
	char *bin = (char *) malloc(sizeof(char) * (len * 8 + 1));
	bin[len * 8] = '\0';

	for (long unsigned int i = 0; i < len; ++i) {
		for (unsigned int j = 0; j < sizeof(char) * 8; ++j)
			bin[i * 8 + j] = string[i] & (1 << (7 - j)) ? '1' : '0';
	}

	return bin;
}

char *readFile(FILE *f) {
	unsigned int buffer_size = 1024;
	char *string = (char *) malloc(sizeof(char));

	long unsigned int i = 0, read = 0;
	char buffer[buffer_size + 1];
	do {
		read = fread(buffer, sizeof(char), buffer_size, f);
		buffer[read] = '\0';
		string = (char *) realloc(string, sizeof(char) * (i * buffer_size + read + 1));
		memcpy(string + i * buffer_size * sizeof(char), buffer, read + 1);
		++i;
	} while (read == buffer_size);

	return string;
}

char *readFilePath(char *path) {
	FILE *f = fopen(path, "r");
	char *string = readFile(f);
	fclose(f);

	return string;
}

void writeFile(FILE *f, char *string) {
	fwrite(string, sizeof(char), strlen(string), f);
}

void writeFilePath(char *path, char *string) {
	FILE *f = fopen(path, "w");
	writeFile(f, string);
	fclose(f);
}

void fileToBin(char *path, char *binPath) {
	char *string = readFilePath(path);
	char *bin = stringToBin(string);

	free(string);

	writeFilePath(binPath, bin);

	free(bin);
}

long unsigned int fileSize(char *path) {
	FILE *f = fopen(path, "r");

	fseek(f, 0L, SEEK_END);
	long unsigned int size = ftell(f);

	fclose(f);

	return size;
}

bool startsWith(char *prefix, char *string) {
	for (int i = 0; i < strlen(prefix); ++i)
		if (string[i] != prefix[i]) return false;
	return true;
}
