#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *next;
} Node;

// Node create_node

int main_ll(int argc, int *argv[])
{
    // NULL only applies to pointers
    // means: does not point to anything
    // if list points to NULL, is empty
    Node *list = NULL;
    Node node = {42, NULL};
    Node node2 = {12, NULL};
    // node.next POINTS TO node2
    // list POINTS TO node
    node.next = &node2;
    list = &node;

    return 0;
}

Node create_node(int val)
{
}