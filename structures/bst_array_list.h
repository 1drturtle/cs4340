#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node
{
    int key;
    bool exists;
} Node;

typedef Node *NodePtr;

typedef struct array_list
{
    Node *array;
    // max capacity of array in # of elements
    size_t capacity;

} ArrayList;

ArrayList *create_bst();

void insert_bst(ArrayList *treePtr, int value);
void delete_bst(ArrayList *treePtr);
void destroy_bst(ArrayList *treePtr);
void predecessor_bst(ArrayList tree, int index);
void merge_bst(ArrayList tree1, ArrayList tree2);
void print_in_order(ArrayList tree);
void print_level_order(ArrayList tree);

// other stuff
size_t parent(size_t index);
size_t right_child(size_t index);
size_t left_child(size_t index);
void resize(ArrayList *treePtr);
// helpers

int main_array_bst(int argc, char *argv[])
{
    ArrayList *bst = NULL;
    bst = create_bst();
    insert_bst(bst, 50);
    insert_bst(bst, 25);
    insert_bst(bst, 75);
    insert_bst(bst, 30);
    insert_bst(bst, 0);
    print_level_order(*bst);
}

ArrayList *create_bst()
{
    ArrayList *tree = malloc(sizeof(ArrayList));

    // initial capacity = 1 Node
    // calloc (sizeof(Node), capacity)

    tree->capacity = 1;

    tree->array = calloc(1, sizeof(Node));

    return tree;
}
void insert_bst(ArrayList *treePtr, int value)
{
    size_t index = 0;
    while (treePtr->array[index].exists)
    {
        if (value > treePtr->array[index].key)
        {
            index = right_child(index);
        }
        else if (value <= treePtr->array[index].key)
        {
            index = left_child(index);
        }
        if (index >= treePtr->capacity)
            resize(treePtr);
    }
    treePtr->array[index].key = value;
    treePtr->array[index].exists = true;
}
void print_in_order(ArrayList tree)
{
    // left to right (ascending)
    
}
void print_level_order(ArrayList tree)
{
    // cap = old_cap*2 + 1
    size_t index = 0, last_print = 0;

    Node n;

    while (index < tree.capacity)
    {
        n = tree.array[index];

        if (!n.exists)
            printf("NULL ");
        else
            printf("%d ", n.key);

        index++;
        if (index == (last_print * 2 + 1))
        {
            last_print = index;
            puts("");
        }
    }
}

// HELPERS
// parent(i) = (i-1)/2
size_t parent(size_t index)
{
    return (index - 1) / 2;
}
// right(i)  = (i*2)+2
size_t right_child(size_t index)
{
    return (index * 2) + 2;
}
// left(i)   = (i*2)+1
size_t left_child(size_t index)
{
    return index * 2 + 1;
}
void resize(ArrayList *treePtr)
{
    // cap = old_cap*2 + 1
    size_t old_capacity = treePtr->capacity;
    treePtr->capacity = treePtr->capacity * 2 + 1;
    treePtr->array = realloc(treePtr->array, sizeof(Node) * treePtr->capacity);
    // set all new nodes to null
    memset(treePtr->array + old_capacity, 0, sizeof(Node) * (treePtr->capacity - old_capacity));
}

// arr[i].key = ...

// total # of nodes = sum 2^(i-1)

// give each node a null flag or make ArrayList[*Node]

// merge
// count nodes
// flatten (go left to right, like print_bst_in_order) into lists
// zipper merge into super sorted array
// use binary sort to create BST
