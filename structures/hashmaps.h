#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    // the un-hashed key
    char *key;
    // the value
    int val;
    // next node pointer
    struct node *next;
} Node;

typedef struct hashmap
{
    // array of nodes
    Node *array;
    // total # of nodes
    size_t size;
    // number of slots in array
    size_t capacity;

} HashMap;

int main_hashmap(int argc, char *argv[])
{
    // use hash function to turn string into index
    // store key in hash index
    // no infinite memory, collisions are inevitable
}

/*
Assignment one: Separate Chaining
- Each element has another structure. Hash to index, key to correct node
    - string -> any number
    - number % slots
        - ensure every number has an equal chance (not very important)
- ArrayList of LinkedLists
- Keep track of # of total elements
    - Load factor: total number of elements (elements / capacity)
    - Resize when load factor greater then threshold
- Insert, Update, or Read node
  - beginning of linked list
- re-size when there are too many elements
    - Re-hash each key
    - Move each node to new correct area
    - Malloc, move new nodes, free

More recent accessed, more likely to be accessed again
*/