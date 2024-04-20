#ifndef STRTREE_H
#define STRTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct _TreeNode {
    char* value;
    struct _TreeNode* left;
    struct _TreeNode* right;
} TreeNode;

enum search_tree_result {
    NO_MATCH, PARTIAL_MATCH, TOTAL_MATCH
};

void st_insert_value(TreeNode**, const char*);
int search_tree(TreeNode*, const char *);

#endif