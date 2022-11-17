#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INITIAL_CAPACITY 1
#define MAX_LOAD 8
#define MIN_LOAD 2

typedef struct node
{
    // the un-hashed key
    char *key;
    // the value
    int val;
    // next node pointer
    struct node *next;
} Node;

typedef Node *NodePtr;

typedef struct hashmap
{
    // array of NodePtr
    NodePtr *array;
    // total # of nodes
    size_t size;
    // number of slots in array
    size_t capacity;

} HashMap;

HashMap *create_hashmap();
void destroy_hashmap(HashMap **mapPtr);
void insert_hashmap(HashMap *mapPtr, char *key, int value);
int get_hashmap(HashMap map, char *key);
int delete_hashmap(HashMap *mapPtr, char *key);
void print_hashmap(HashMap map);

size_t hash_key(char *key, size_t length);
void resize(HashMap *mapPtr);
void insert_node_hashmap(HashMap *mapPtr, NodePtr nodePtr);

int main_chained_hashmap(int argc, char *argv[])
{
    HashMap *mapPtr = create_hashmap();

    char *keys[9] = {"hello", "world", "gaming", "a", "b", "c", "d", "e", "f"};

    // insertion
    // 9 units overloads load factor so a resize occurs & is logged
    for (size_t i = 0; i < 9; i++)
    {
        char *key = keys[i];
        insert_hashmap(mapPtr, key, i + 1);
    }

    // retrieval
    printf("key f, val=%d\n", get_hashmap(*mapPtr, "f"));
    printf("key d, val=%d\n", get_hashmap(*mapPtr, "d"));
    printf("key b, val=%d\n", get_hashmap(*mapPtr, "b"));
    // value not in map *should* return 0
    printf("key zzz (Does not exist), val=%d\n", get_hashmap(*mapPtr, "zzz"));

    // print map after retrieval. Most recent nodes moved to head.
    puts("-- mapping post retrieval --");

    print_hashmap(*mapPtr);

    // deletion test
    // returns value of deleted key (cuz why not)

    // tail
    printf("delete key=hello, val=%d\n", delete_hashmap(mapPtr, "hello"));
    // head
    printf("delete key=b, val=%d\n", delete_hashmap(mapPtr, "b"));
    // middle
    printf("delete key=gaming, val=%d\n", delete_hashmap(mapPtr, "gaming"));
    // val not exist
    printf("delete key=nothing, val=%d\n", delete_hashmap(mapPtr, "nothing"));

    // print map after deletion.
    puts("-- mapping post deletion --");
    print_hashmap(*mapPtr);

    puts("-- deleting to 2 nodes / 2 capacity --");
    // delete below load_factor=2 for resize test
    delete_hashmap(mapPtr, "world");
    delete_hashmap(mapPtr, "a");
    delete_hashmap(mapPtr, "c");
    delete_hashmap(mapPtr, "e");
    puts("-- hashmap post resize --");
    print_hashmap(*mapPtr);

    destroy_hashmap(&mapPtr);
    puts("done");
}

HashMap *create_hashmap()
{
    HashMap *map = malloc(sizeof(HashMap));
    map->array = calloc(INITIAL_CAPACITY, sizeof(NodePtr));
    map->capacity = INITIAL_CAPACITY;
    map->size = 0;

    printf("-- Created HashMap: Capacity=%d, Size=0 --\n", INITIAL_CAPACITY);

    return map;
}
void destroy_hashmap(HashMap **mapPtr)
{
    free((*mapPtr)->array);
    free(*mapPtr);
    *mapPtr = NULL;
    puts("-- HashMap Destroyed --");
}
void insert_hashmap(HashMap *mapPtr, char *key, int value)
{

    NodePtr new = malloc(sizeof(Node));
    new->key = key;
    new->val = value;
    new->next = NULL;

    insert_node_hashmap(mapPtr, new);

    mapPtr->size++;

    resize(mapPtr);
}
void print_hashmap(HashMap map)
{
    for (size_t i = 0; i < map.capacity; i++)
    {
        NodePtr current = map.array[i];
        if (current == NULL)
            puts("NULL");
        else
        {
            while (current != NULL)
            {
                printf("%s:%d, ", current->key, current->val);
                current = current->next;
            }
            puts("");
        }
    }
}
int get_hashmap(HashMap map, char *key)
{
    size_t hash = hash_key(key, map.capacity);
    NodePtr *headPtr = &map.array[hash];
    int out = 0;

    NodePtr node = *headPtr;
    NodePtr prev = NULL;
    // find the node which has the key
    if (node == NULL)
        return out;

    while (node != NULL)
    {
        if (node->key == key)
        {
            out = node->val;
            break;
        }
        prev = node;
        node = node->next;
    }
    // if we didn't find it, return early
    if (out == 0)
        return out;
    // move said node to the head of the list, if we are not at the head already
    if (prev != NULL)
    {
        prev->next = node->next;
        node->next = *headPtr;
        *headPtr = node;
    }
    return out;
}
int delete_hashmap(HashMap *mapPtr, char *key)
{
    size_t hash = hash_key(key, mapPtr->capacity);
    NodePtr *headPtr = &mapPtr->array[hash];
    int out = 0;

    NodePtr node = *headPtr;
    NodePtr prev = NULL;
    // find the node which has the key
    if (node == NULL)
        return out;

    while (node != NULL)
    {
        if (node->key == key)
        {
            out = node->val;
            break;
        }
        prev = node;
        node = node->next;
    }
    // if we didn't find it, return early
    if (out == 0)
        return out;

    // deletion code:
    // set next equal to prev
    // unless, prev is null. then headPtr is moved
    if (prev != NULL)
        prev->next = node->next;
    else
        *headPtr = node->next;

    mapPtr->size--;

    resize(mapPtr);

    return out;
}
// -- utility --

/*
Hash Function
:param str key: The string key to hash
:param size_t length: Capacity of HashMap ArrayList
*/
size_t hash_key(char *key, size_t length)
{
    size_t value = 0;
    for (size_t i = strlen(key); i > 0; --i)
        value = (value % length) * 32 % length + key[i - 1] % length;
    return value % length;
}

void resize(HashMap *mapPtr)
{
    size_t load_factor = mapPtr->size / mapPtr->capacity;
    size_t old_cap = mapPtr->capacity;
    if (load_factor > 8)
    {
        mapPtr->capacity *= 2;
    }
    else if (load_factor < 2 && mapPtr->capacity > 1)
    {
        mapPtr->capacity /= 2;
    }
    else
    {
        return;
    }

    printf("Resizing: cap=%d -> cap=%d\n", old_cap, mapPtr->capacity);
    NodePtr *old = mapPtr->array;
    NodePtr *new = calloc(mapPtr->capacity, sizeof(NodePtr));
    mapPtr->array = new;
    for (size_t i = 0; i < old_cap; i++)
    {
        NodePtr *nPtr = &old[i];
        if (*nPtr == NULL)
            continue;
        while ((*nPtr) != NULL)
        {
            NodePtr n = *nPtr;
            *nPtr = n->next;
            n->next = NULL;
            insert_node_hashmap(mapPtr, n);
        }
    }
    free(old);
}
void insert_node_hashmap(HashMap *mapPtr, NodePtr nodePtr)
{
    size_t hash = hash_key(nodePtr->key, mapPtr->capacity);

    if (mapPtr->array[hash] == NULL)
    {
        mapPtr->array[hash] = nodePtr;
    }
    else
    {
        NodePtr i = mapPtr->array[hash];
        while (i->next != NULL)
        {
            if (i->key == nodePtr->key)
            {
                i->val = nodePtr->val;
                return;
            }
            i = i->next;
        }
        i->next = nodePtr;
    }
}

/*
General Notes:
use hash function to turn string into index
store key in hash index
no infinite memory, collisions are inevitable
resize and shrink when necessary (high and low load factor)

Load Factor Max:  between 2 & 8
Initial Capacity: 1

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
    - *NEW* realloc and move items from first half

More recent accessed, more likely to be accessed again

HASH
----
ASCII value of characters
multiply each one by next largest power of 32

mod to determine index

"abc"
'a'*1 + 'b'*32 + 'c'*32^2
*/