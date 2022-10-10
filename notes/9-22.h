#include <stdio.h>

typedef struct node
{
    int value;
    struct node *next;
} Node;

typedef Node *NodePtr;

typedef struct queue
{
    NodePtr head;
    NodePtr tail;
} Queue;

int main_9_22()
{
    // Queue
    // First in, first out
    // last in, last out
    // [------]

    // Stack
    // First in, last out
    // Last in, First out

    // Linked list can only be accessed linearly
    // Array list can be accessed "randomly"
    return 0;
}