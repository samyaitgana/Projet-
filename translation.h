#ifndef __H_TRANSLATION
#define __H_TRANSLATION

#include "tree.h"

void compress(Dictionary *dict, char *string, char **compressed, long unsigned int prefix);
void decompress(Dictionary *dict, char *compressed, char **string, long unsigned int prefix);

#endif
