#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Vector2;

bool v_equals(Vector2*, int, int);

typedef struct _VectorLLNode {
    Vector2 value;
    struct _VectorLLNode* next;
} VectorLLNode;

VectorLLNode* create_vector_node(int, int);
void add_vector_node(VectorLLNode**, VectorLLNode*);
void add_vector_value(VectorLLNode**, int, int);
void free_vector_list(VectorLLNode*);
void pop_vector_list(VectorLLNode**);
bool vector_list_has(VectorLLNode*, int, int);
int vector_list_length(VectorLLNode*);

typedef struct _WordLLNode {
    Vector2 start;
    char* word;
    struct _WordLLNode* next;
} WordLLNode;

WordLLNode* create_word_node(int, int, char*);
void add_word_node(WordLLNode**, WordLLNode*);
void add_word_value(WordLLNode**, int, int, char*);

#endif