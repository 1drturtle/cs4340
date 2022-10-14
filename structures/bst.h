#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    struct node *left;
    struct node *right;
} Node;

typedef Node *NodePtr;

void print_bst(NodePtr tree);
void print_bst_in_order(NodePtr tree);
void insert_bst(int value, NodePtr *treePtr);
void destroy_bst(NodePtr *treePtr);
void delete_bst(int value, NodePtr *treePtr);
NodePtr *successor_bst(NodePtr *treePtr);
size_t find_depth_bst(NodePtr tree);

int main_binary_tree(int argc, char *argv[])
{
    // binary search tree
    // search: O(log_2(n))

    NodePtr tree = NULL;

    insert_bst(50, &tree);
    insert_bst(100, &tree);
    insert_bst(0, &tree);
    insert_bst(50, &tree);
    insert_bst(1, &tree);

    print_bst(tree);
    // print_bst_in_order(tree);
    delete_bst(50, &tree);
    print_bst(tree);

    // printf("depth: %d\n", find_depth_bst(tree));
    destroy_bst(&tree);

    return 0;
}
void print_bst(NodePtr tree)
{
    static size_t depth = 0;

    if (tree == NULL)
        return;

    ++depth;
    print_bst(tree->right);
    --depth;

    for (size_t i = 0; i < depth; i++)
    {
        printf("  ");
    }

    printf("%d\n", tree->key);

    ++depth;
    print_bst(tree->left);
    --depth;

    if (depth == 0)
        puts("");
}
void print_bst_in_order(NodePtr tree)
{
    static size_t depth = 0;

    if (tree == NULL)
        return;
    ++depth;
    print_bst_in_order(tree->left);
    --depth;

    printf("%d,", tree->key);

    ++depth;
    print_bst_in_order(tree->right);
    --depth;

    if (depth == 0)
        puts("");
}
void insert_bst(int value, NodePtr *treePtr)
{
    NodePtr tree = *treePtr;
    if (tree == NULL)
    {
        tree = malloc(sizeof(Node));
        tree->key = value;
        tree->left = tree->right = NULL;
        *treePtr = tree;
    }
    else if (value < tree->key)
        insert_bst(value, &(tree->left));
    else
        insert_bst(value, &(tree->right));
}
void destroy_bst(NodePtr *treePtr)
{
    NodePtr tree = *treePtr;
    if (tree == NULL)
        return;
    destroy_bst(&(tree->left));
    destroy_bst(&(tree->right));

    free(tree);
    *treePtr = NULL;
}

NodePtr *successor_bst(NodePtr *treePtr)
{
    *treePtr = (*treePtr)->right;
    while ((*treePtr)->left)
        *treePtr = (*treePtr)->left;
    return treePtr;
}
void delete_bst(int value, NodePtr *treePtr)
{
    NodePtr tree = *treePtr;
    if (tree == NULL)
        return;
    else if (value < tree->key)
        delete_bst(value, &(tree->left));
    else if (value > tree->key)
        delete_bst(value, &(tree->right));
    else
    {
        // find the child
        NodePtr child = tree->right ? tree->right : tree->left;
        // first case: No children!
        if (child == NULL)
        {
            // first, we simply free the current node
            free(*treePtr);
            // then, we point the node to NULL (child is NULL in this case)
            *treePtr = child;
        }
        // second case: One child
        else if (!tree->right || !tree->left)
        {
            // free ourself
            free(*treePtr);
            // put our child as the node (deleting the current node)
            *treePtr = child;
        }
        // third case: two children
        else
        {
            // find successor node
            NodePtr *childPtr = successor_bst(treePtr);
            NodePtr child = *childPtr;
            // move the old node's children to new node
            child->left = tree->left;
            child->right = tree->right;
            // free the old node
            free(*treePtr);
            // set the child as the current node
            *treePtr = child;

            // KLEINER

            // move successor's child up
            //
        }
    }
}
size_t find_depth_bst(NodePtr tree)
{
    static size_t depth = 0;
    static size_t max_depth = 0;

    if (tree == NULL)
        return 0;

    if (depth > max_depth)
        max_depth = depth;

    ++depth;
    find_depth_bst(tree->left);
    --depth;

    ++depth;
    find_depth_bst(tree->right);
    --depth;

    if (depth == 0)
    {
        size_t d = max_depth;
        max_depth = 0;
        return d;
    }
}
void print_bst_vertical(NodePtr tree)
{
    if (tree == NULL)
        return;
    size_t depth = find_depth_bst(tree);
    // NodePtr treeList[][];
}