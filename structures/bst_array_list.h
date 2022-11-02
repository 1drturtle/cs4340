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
size_t predecessor_bst(ArrayList tree, int index);
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
    for (size_t i = 0; i < bst->capacity; i++)
    {
        Node n = bst->array[i];

        if (!n.exists)
            printf("NULL ");
        else
            printf("%d ", n.key);
    }
    puts("");

    print_level_order(*bst);
    printf("%d\n", predecessor_bst(*bst, 1));
    destroy_bst(bst);
    puts("Done");
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
    static size_t curent_index = 0;
    // recursive left
    if (!tree.array[curent_index].exists)
    {
        return;
    }
    curent_index = left_child(curent_index);
    print_in_order(tree);

    curent_index = parent(curent_index);
    printf("%d, ", tree.array[curent_index].key);

    curent_index = right_child(curent_index);
    print_in_order(tree);

    curent_index = parent(curent_index);

    if (curent_index == 0)
        puts("");
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

void delete_bst(ArrayList *treePtr)
{
    // delete one item from BST
    // binary search to find index
    // cases: 0 children, 1 child, 2 children
}
void destroy_bst(ArrayList *treePtr)
{
    free(treePtr->array);
    free(treePtr);
    treePtr = NULL;
}
size_t predecessor_bst(ArrayList tree, int index)
{
    // finds the next smallest node from the node at index

    // if left_index+1 >= capacity || node does not exist, return
    index = left_child(index);
    if (index + 1 >= tree.capacity || !tree.array[index].exists)
        return parent(index);

    // left once, then right
    while (right_child(index) + 1 < tree.capacity && tree.array[right_child(index)].exists)
    {
        index = right_child(index);
    }
    return index;
}
void merge_bst(ArrayList tree1, ArrayList tree2)
{
    // merge
    // count nodes
    // flatten (go left to right, like print_bst_in_order) into lists
    // zipper merge into super sorted array
    // use binary sort to create BST
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
// resize the array to the next row size
void resize(ArrayList *treePtr)
{
    // cap = old_cap*2 + 1
    size_t old_capacity = treePtr->capacity;
    treePtr->capacity = treePtr->capacity * 2 + 1;
    treePtr->array = realloc(treePtr->array, sizeof(Node) * treePtr->capacity);
    // set all new nodes to null
    memset(treePtr->array + old_capacity, 0, sizeof(Node) * (treePtr->capacity - old_capacity));
}
