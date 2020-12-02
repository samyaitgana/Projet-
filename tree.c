#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

void insertNode(NodeList **list, TreeNode *tree) {
	while (*list != NULL && (*list)->tree->count < tree->count)
		list = &(*list)->next;

	NodeList *node = (NodeList *) malloc(sizeof(NodeList));
	node->tree = tree;
	node->next = *list;
	*list = node;
}

TreeNode *popSmallestNode(NodeList **list, OccurrenceArray *occurrences) {
	TreeNode *node;

	if (occurrences->size == 0 && *list == NULL) {
		return NULL;
	} else if (occurrences->size > 0 && (*list == NULL || occurrences->array[occurrences->size - 1].count < (*list)->tree->count)) {
		Occurrence occurrence = popSmallestOccurrence(occurrences);

		node = (TreeNode *) malloc(sizeof(TreeNode));
		node->c = occurrence.c;
		node->count = occurrence.count;
		node->left = NULL;
		node->right = NULL;
	} else {
		NodeList *tmp = *list;
		*list = tmp->next;
		node = tmp->tree;
		free(tmp);
	}

	return node;
}

TreeNode *buildTree(OccurrenceArray occurrences) {
	NodeList *list = NULL;

	int size = occurrences.size;
	while (occurrences.size > 0 || list->next != NULL) {
		TreeNode *node1 = popSmallestNode(&list, &occurrences),
				 *node2 = popSmallestNode(&list, &occurrences);

		TreeNode *tree = (TreeNode *) malloc(sizeof(TreeNode));
		tree->c = '\0';
		tree->count = (node1 != NULL ? node1->count : 0) + (node2 != NULL ? node2->count : 0);
		tree->left = node1;
		tree->right = node2;

		insertNode(&list, tree);
	}

	occurrences.size = size;

	TreeNode *tree = list->tree;
	free(list);
	return tree;
}

TreeNode *buildTreeLL(OccurrenceLL **occurrences) {
	TreeNode *tree = NULL;

	while (*occurrences != NULL) {
		OccurrenceLL *occurrence = popSmallestOccurrenceLL(occurrences);

		TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
		node->c = occurrence->c;
		node->count = occurrence->count;
		node->left = NULL;
		node->right = NULL;

		TreeNode *top = (TreeNode *) malloc(sizeof(TreeNode));
		top->c = '\0';
		top->count = node->count + (tree != NULL ? tree->count : 0);
		top->left = node;
		top->right = tree;
		tree = top;
	}

	return tree;
}

Dictionary **buildDictionary(TreeNode *tree, Dictionary **dict, char *prefix) {
	if (tree == NULL) return dict;

	long unsigned int depth = strlen(prefix);

	if (tree->c != '\0') {
		*dict = (Dictionary *) malloc(sizeof(Dictionary));
		(*dict)->c = tree->c;
		(*dict)->code = (char *) malloc(sizeof(char) * (depth + 1));
		(*dict)->next = NULL;

		strcpy((*dict)->code, prefix);
		return &(*dict)->next;
	} else {
		char *code = (char *) malloc(sizeof(char) * (depth + 2));
		strcpy(code, prefix);
		code[depth + 1] = '\0';

		code[depth] = '0';
		dict = buildDictionary(tree->left, dict, code);
		code[depth] = '1';
		dict = buildDictionary(tree->right, dict, code);

		free(code);
		return dict;
	}
}

void writeDictionary(Dictionary *dict, FILE *f) {
	if (dict == NULL) return;

	fprintf(f, "%c:%s\n", dict->c, dict->code);

	writeDictionary(dict->next, f);
}

void writeDictionaryPath(Dictionary *dict, char *path) {
	FILE *f = fopen(path, "w");
	writeDictionary(dict, f);
	fclose(f);
}
