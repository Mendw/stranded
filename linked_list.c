#include "linked_list.h"
#include <stdio.h>

bool v_equals(Vector2* vector, int x, int y) {
    return vector->x == x && vector->y == y;
};

VectorLLNode* create_vector_node(int x, int y) {
    VectorLLNode* node = malloc(sizeof(VectorLLNode));
    node->value.x = x;
    node->value.y = y;
    node->next = NULL;

    return node;
}

void add_vector_node(VectorLLNode** list_ptr, VectorLLNode* node) {
    if (*list_ptr == NULL) {
        *list_ptr = node;
        return;
    }
    

    VectorLLNode* list = *list_ptr;
    while (list->next != NULL) list = list->next;
    list->next = node;
}

void add_vector_value(VectorLLNode** list_ptr, int x, int y) {
    VectorLLNode* node = create_vector_node(x, y);
    add_vector_node(list_ptr, node);
}

void free_vector_list(VectorLLNode* list) {
    if (list == NULL) return;

    VectorLLNode* next = list->next;
    free(list);

    free_vector_list(next);
}

void pop_vector_list(VectorLLNode** list_ptr) {
    if (*list_ptr == NULL) return;
    
    VectorLLNode* list = *list_ptr;
    if (list->next == NULL) {
        *list_ptr = NULL;
    }

    while(list->next->next != NULL) list = list->next;
    free(list->next);
    list->next = NULL;
}

bool vector_list_has(VectorLLNode* list, int x, int y) {
    if (list == NULL) return false;
    if (v_equals(&list->value, x, y)) return true;
    return vector_list_has(list->next, x, y);
}

int vector_list_length(VectorLLNode* list) {
    int length = 0;
    for (; list != NULL; length++, list = list->next);
    return length;
}

WordLLNode* create_word_node(int x, int y, char* word) {
    WordLLNode* node = malloc(sizeof(WordLLNode));
    node->start.x = x;
    node->start.y = y;
    node->word = word;
    node->next = NULL;

    return node;
}
void add_word_node(WordLLNode** list_ptr, WordLLNode* node) {
    if (*list_ptr == NULL) {
        *list_ptr = node;
        return;
    }

    WordLLNode* list = *list_ptr;
    while (list->next != NULL) list = list->next;
    list->next = node;
}

void add_word_value(WordLLNode** list_ptr, int x, int y, char* word) {
    WordLLNode* node = create_word_node(x, y, word);
    add_word_node(list_ptr, node);
}