#include <stdio.h>
#include <stdlib.h>

// Singular node of a Linked List
typedef struct node
{
    int value;
    struct node *next;
} Node;

// Pointer to a Node
typedef Node *NodePtr;

void insert_ll(int value, NodePtr *listPtr);
void destroy_ll(NodePtr *listPtr);

int main_ll(int argc, char *argv[])
{
    // NULL only applies to pointers
    // means: does not point to anything
    // if list points to NULL, is empty
    Node *list = NULL;
    // Node node = {42, NULL};
    // Node node2 = {12, NULL};
    // node.next POINTS TO node2
    // list POINTS TO node
    // node.next = &node2;
    // list = &node;
    // printf("%d\n", list->value);
    list = malloc(sizeof(Node));
    list->next = NULL;
    destroy_ll(&list);

    return 0;
}

// Insert a node into a sorted linked list.
void insert_ll(int value, NodePtr *listPtr)
{
    // Node n = {value, NULL};
    NodePtr list = *listPtr;

    if (list == NULL)
    {
        // manually allocate memory for the node. Will not be destroyed after function call
        NodePtr new = malloc(sizeof(Node));
        *listPtr = new;
    }
}

// Destroy a linked list.
void destroy_ll(NodePtr *listPtr)
{
    NodePtr list = *listPtr;
    if (list != NULL)
    {
        // destroy_ll (memory address of next Node)
        destroy_ll(&(list->next));
        // opposite of malloc
        free(list);
        *listPtr = NULL;
    }
}