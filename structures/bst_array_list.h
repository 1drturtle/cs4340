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
void delete_bst(ArrayList *treePtr, int value);
void destroy_bst(ArrayList *treePtr);
size_t predecessor_bst(ArrayList tree, int index);

void merge_bst(ArrayList tree1, ArrayList tree2);
Node *flatten_bst(ArrayList tree, size_t length);

void print_in_order(ArrayList tree);
void print_level_order(ArrayList tree);
void print_array(ArrayList bst);

// other stuff
size_t parent(size_t index);
size_t right_child(size_t index);
size_t left_child(size_t index);
void resize(ArrayList *treePtr);
// helpers
size_t node_count(ArrayList tree);
bool node_exists(ArrayList tree, size_t index);

int main_array_bst(int argc, char *argv[])
{
    ArrayList *bst = NULL;
    bst = create_bst();
    // root
    insert_bst(bst, 50);
    // depth 1
    insert_bst(bst, 25);
    insert_bst(bst, 75);
    // depth 2
    insert_bst(bst, 30);
    insert_bst(bst, 0);
    // depth 3
    insert_bst(bst, 27);
    insert_bst(bst, 32);

    print_array(*bst);

    puts("before delete");
    print_level_order(*bst);
    // two child
    delete_bst(bst, 50);
    // one child
    delete_bst(bst, 30);
    // no children
    delete_bst(bst, 0);
    puts("after delete");
    print_level_order(*bst);

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
            printf("X ");
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
void print_array(ArrayList bst)
{
    for (size_t i = 0; i < bst.capacity; i++)
    {
        Node n = bst.array[i];

        if (!n.exists)
            printf("X ");
        else
            printf("%d ", n.key);
    }
    puts("");
}

void delete_bst(ArrayList *treePtr, int value)
{
    // delete one item from BST
    static size_t current_index = 0;

    Node node = treePtr->array[current_index];

    if (current_index + 1 >= treePtr->capacity || !node.exists)
    {
        return;
    }
    else if (value == node.key)
    {
        size_t hold = current_index;
        size_t key;
        size_t replacement_index =
            node_exists(*treePtr, left_child(current_index))
                ? left_child(current_index)
                : right_child(current_index);
        if (node_exists(*treePtr, left_child(current_index)) && node_exists(*treePtr, right_child(current_index)))
        {
            // TODO: 2 child case
            replacement_index = predecessor_bst(*treePtr, current_index);
            key = treePtr->array[replacement_index].key;
            delete_bst(treePtr, key);
            treePtr->array[hold].key = key;
        }
        else if (node_exists(*treePtr, replacement_index))
        {
            key = treePtr->array[replacement_index].key;
            delete_bst(treePtr, key);
            treePtr->array[hold].key = key;
        }
        else
        {
            treePtr->array[hold].exists = false;
        }
        /*
        cases: 0 children, 1 child, 2 children

        2 children:
        - replace current with predecessor
        - replace predecessor with predecessor recursively?
        - set last deleted node to exist = false ✅
        1 child:
        - move child value to self
        - recursively move children up
        - last deleted exist = false ✅
        0 children:
        - delete self (exist = false) ✅
        */
        current_index = 0;
    }
    // binary search to find index
    else if (value < node.key)
    {
        current_index = left_child(current_index);
        delete_bst(treePtr, value);
    }
    else if (value > node.key)
    {
        current_index = right_child(current_index);
        delete_bst(treePtr, value);
    }
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

    while (node_exists(tree, right_child(index)))
    {
        index = right_child(index);
    }
    return index;
}
void merge_bst(ArrayList tree1, ArrayList tree2)
{
    // merge
    // count nodes
    size_t length1 = node_count(tree1);
    size_t length2 = node_count(tree2);
    // flatten (go left to right, like print_bst_in_order) into lists

    // zipper merge into super sorted array
    // use binary sort to create BST
}
Node *flatten_bst(ArrayList tree, size_t length)
{
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
size_t node_count(ArrayList tree)
{
    size_t count = 0;
    for (size_t i = 0; i < tree.capacity; i++)
        count += tree.array[i].exists;
    return count;
}
bool node_exists(ArrayList tree, size_t index)
{
    if (index + 1 >= tree.capacity)
        return false;
    return tree.array[index].exists;
}