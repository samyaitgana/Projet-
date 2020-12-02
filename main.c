#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "occurrences.h"
#include "tree.h"
#include "translation.h"

int main(int argc, char const *argv[]) {
	fileToBin("files/Alice_input.txt", "files/Alice_binary.txt");
	printf("Size of input: %lu\n", fileSize("files/Alice_input.txt"));
	printf("Size of binary: %lu\n", fileSize("files/Alice_binary.txt"));

	char *string = readFilePath("files/Alice_input.txt");
	OccurrenceArray occurrences = getOccurrences(string);

	printf("Occurrences: ");
	displayOccurrences(occurrences);
	printf("\n");

	TreeNode *tree = buildTree(occurrences);
	Dictionary *dict = NULL;
	buildDictionary(tree, &dict, "");

	printf("Dictionary:\n");
	writeDictionary(dict, stdout);
	writeDictionaryPath(dict, "files/Alice_dico.txt");

	char *compressed = NULL;
	compress(dict, string, &compressed, 0);
	writeFilePath("files/Alice_huffman.txt", compressed);

	printf("Compressed size: %lu\n", fileSize("files/Alice_huffman.txt"));
	float ratio = (float) (fileSize("files/Alice_binary.txt") - fileSize("files/Alice_huffman.txt")) / fileSize("files/Alice_binary.txt") * 100;
	printf("Compression ratio: %.2f%%\n", ratio);

	free(compressed);
	free(string);
	string = NULL;
	compressed = readFilePath("files/Alice_huffman.txt");
	printf("Compressed: %s\n", compressed);

	decompress(dict, compressed, &string, 0);
	printf("Decompressed: %s\n", string);

	return 0;
}
