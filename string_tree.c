#include "string_tree.h"

TreeNode* create_node(const char* value) {
    TreeNode* node = malloc(sizeof(TreeNode));

    int value_len = strlen(value);
    char* node_value = malloc(sizeof(char) * (value_len + 1));
    strcpy(node_value, value);

    node->value = node_value;
    node->left = node->right = NULL;

    return node;
}

void st_insert_node(TreeNode** tree_ptr, TreeNode* node) {
    if (*tree_ptr == NULL) {
        *tree_ptr = node; 
        return;
    }

    int value_diff = strcmp((*tree_ptr)->value, node->value);
    if (value_diff > 0) return st_insert_node(&(*tree_ptr)->left, node);
    if (value_diff < 0) return st_insert_node(&(*tree_ptr)->right, node);
}

void st_insert_value(TreeNode** tree_ptr, const char* value) {
    TreeNode* node = create_node(value);
    st_insert_node(tree_ptr, node);
}

bool is_prefix(const char* prefix, const char* string) {
    return strncmp(prefix, string, strlen(prefix)) == 0;
}

bool _search_tree(TreeNode* tree, const char* value, bool* partial_match_ptr) {
    if (tree == NULL) return false;

    int value_diff = strcmp(tree->value, value);

    *partial_match_ptr = (*partial_match_ptr) || is_prefix(value, tree->value);
    if (value_diff > 0) return _search_tree(tree->left, value, partial_match_ptr);
    if (value_diff < 0) return _search_tree(tree->right, value, partial_match_ptr);
    return true;
}

int search_tree(TreeNode* tree, const char* value) {
    bool partial_match = false;
    bool total_match = _search_tree(tree, value, &partial_match);

    if (total_match) return TOTAL_MATCH;
    if (partial_match) return PARTIAL_MATCH;
    return NO_MATCH;
}