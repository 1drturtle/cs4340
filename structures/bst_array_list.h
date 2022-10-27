#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int key;
    bool null;
} Node;

typedef struct array_list
{
    Node *array;
    // max capacity of array in # of elements
    size_t capacity;
    // current size of array in # of elements
    size_t length;

} ArrayList;

ArrayList *create_bst();
void destroy_bst(ArrayList *treePtr);

void print_bst(ArrayList tree);

int main_array_bst(int argc, char *argv[])
{
    ArrayList *bst = NULL;
    bst = create_bst();
    destroy_bst(bst);
    printf("%d\n", bst->capacity);
}

ArrayList *create_bst()
{
    ArrayList *tree = malloc(sizeof(ArrayList));

    tree->capacity = 1;
    tree->length = 0;

    tree->array = calloc(1, sizeof(Node));

    return tree;
}
void destroy_bst(ArrayList *treePtr)
{
    // ????
    free(treePtr->array);
    free(treePtr);
}
void print_bst(ArrayList tree)
{
}

// initial capacity = 1 Node
// calloc (sizeof(Node), capacity)
// arr[i].key = ...

// total # of nodes = sum 2^(i-1)
// cap = old_cap*2 + 1

// parent(i) = (i-1)/2
// left(i)   = (i*2)+1
// right(i)  = (i*2)+2

// give each node a null flag or make ArrayList[*Node]

// merge
// count nodes
// flatten (go left to right, like print_bst_in_order) into lists
// zipper merge into super sorted array
// use binary sort to create BST
