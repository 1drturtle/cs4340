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
void print_ll(NodePtr list);
void delete_ll(int value, NodePtr *listPtr);
void purge_ll(int value, NodePtr *listPtr);

int main_ll(int argc, char *argv[])
{
    // NULL only applies to pointers
    // means: does not point to anything
    // if list points to NULL, is empty
    NodePtr list = NULL;
    NodePtr *listPtr = &list;
    // Node node = {42, NULL};
    // Node node2 = {12, NULL};
    // node.next POINTS TO node2
    // list POINTS TO node
    // node.next = &node2;
    // list = &node;
    // printf("%d\n", list->value);

    // Manually Allocate list to the size of Node
    insert_ll(42, listPtr);
    insert_ll(42, listPtr);
    insert_ll(6, listPtr);

    purge_ll(42, listPtr);

    print_ll(list);
    // destroy it
    destroy_ll(&list);

    return 0;
}

// Insert a node into a sorted linked list.
void insert_ll(int value, NodePtr *listPtr)
{
    NodePtr list = *listPtr;

    if (list == NULL || value <= list->value)
    {
        // manually allocate memory for the node. Will not be destroyed after function call
        NodePtr new = malloc(sizeof(Node));
        new->value = value;
        // the next element is NULL if list == NULL else next is list->next.
        new->next = list;
        *listPtr = new;
    }
    else // continue
        insert_ll(value, &(list->next));
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

void print_ll(NodePtr list)
{
    if (list != NULL)
    {
        printf("%d->", list->value);
        print_ll(list->next);
    }
    else
        printf("%s\n", list);
}

void delete_ll(int value, NodePtr *listPtr)
{
    NodePtr list = *listPtr;
    if (list != NULL)
    {
        // sorted list so stop if the current value is bigger than search value
        if (list->value < value)
            delete_ll(value, &(list->next));
        else if (list->value == value)
        {
            *listPtr = list->next;
            free(list);
        }
    }
}

void purge_ll(int value, NodePtr *listPtr)
{
    NodePtr list = *listPtr;
    if (list != NULL)
    {
        purge_ll(value, &(list->next));
        if (value == list->value)
        {
            *listPtr = list->next;
            free(list);
        }
    }
}