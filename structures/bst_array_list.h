typedef struct node
{
    int key;

} Node;

typedef struct array_list
{
    Node *array;
    // max capacity of array in # of elements
    size_t capacity;
    // current size of array in # of elements
    size_t length;

} ArrayList;

// initial capacity = 1 Node
// calloc (sizeof(Node), capacity)
// arr[i].key = ...

// total # of nodes = sum 2^(i-1)
// cap = old_cap*2 + 1
int main_array_bst(int argv, char *argv)
{
}
// parent(i) = (i-1)/2
// left(i)   = (i*2)+1
// right(i)  = (i*2)+2

// give each node a null flag or make ArrayList[*Node]

// merge
// count nodes
// flatten (go left to right, like print_bst_in_order) into lists
// zipper merge into super sorted array
// use binary sort to create BST
