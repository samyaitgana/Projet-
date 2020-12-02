#ifndef __H_TREE
#define __H_TREE

#include <stdio.h>
#include "occurrences.h"

struct TreeNode {
	char c;
	long unsigned int count;
	struct TreeNode *left, *right;
};
typedef struct TreeNode TreeNode;

struct NodeList {
	TreeNode *tree;
	struct NodeList *next;
};
typedef struct NodeList NodeList;

struct Dictionary {
	char c;
	char *code;
	struct Dictionary *next;
};
typedef struct Dictionary Dictionary;

void insertNode(NodeList **list, TreeNode *tree);
TreeNode *popSmallestNode(NodeList **list, OccurrenceArray *occurrences);
TreeNode *buildTree(OccurrenceArray occurences);
TreeNode *buildTreeLL(OccurrenceLL **occurences);
Dictionary **buildDictionary(TreeNode *tree, Dictionary **dict, char *prefix);
void writeDictionary(Dictionary *dict, FILE *f);
void writeDictionaryPath(Dictionary *dict, char *path);

#endif
