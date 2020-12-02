#include <stdlib.h>
#include <string.h>
#include "translation.h"
#include "utils.h"

void compress(Dictionary *dict, char *string, char **compressed, long unsigned int prefix) {
	if (*compressed == NULL) {
		*compressed = (char *) malloc(sizeof(char));
		(*compressed)[0] = '\0';
		prefix = 0;
	}
	if (string[0] == '\0') return;

	Dictionary *letter = dict;
	while (letter->next != NULL && letter->c != string[0])
		letter = letter->next;

	long unsigned int length = strlen(letter->code);
	*compressed = (char *) realloc(*compressed, sizeof(char) * (prefix + length + 1));
	memcpy(*compressed + prefix * sizeof(char), letter->code, length + 1);

	compress(dict, string + sizeof(char), compressed, prefix + length);
}

void decompress(Dictionary *dict, char *compressed, char **string, long unsigned int prefix) {
	if (*string == NULL) {
		*string = (char *) malloc(sizeof(char));
		(*string)[0] = '\0';
		prefix = 0;
	}
	if (compressed[0] == '\0') return;

	Dictionary *letter = dict;
	while (letter->next != NULL && !startsWith(letter->code, compressed))
		letter = letter->next;

	*string = (char *) realloc(*string, sizeof(char) * (prefix + 2));
	(*string)[prefix] = letter->c;
	(*string)[prefix + 1] = '\0';

	decompress(dict, compressed + strlen(letter->code) * sizeof(char), string, prefix + 1);
}
