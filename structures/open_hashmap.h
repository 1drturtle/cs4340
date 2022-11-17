#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INITIAL_CAPACITY 1

typedef struct open_node
{
    char *key;
    int val;
    bool tombstone;
} Node;

typedef Node *NodePtr;

typedef struct open_hashmap
{
    // Array of NodePtrs
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

void print_hashmap(HashMap map);

size_t hash_key(char *key, size_t length);
void insert_node_hashmap(HashMap *mapPtr, NodePtr nodePtr);
void resize(HashMap *mapPtr);
int delete_hashmap(HashMap *mapPtr, char *key);

void main_open_hashmap(int argc, char *argv[])
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
    HashMap *new = malloc(sizeof(HashMap));
    new->array = calloc(INITIAL_CAPACITY, sizeof(NodePtr));
    new->size = 0;
    new->capacity = INITIAL_CAPACITY;
    return new;
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
    // create node
    NodePtr new = malloc(sizeof(Node));
    new->key = key;
    new->val = value;
    new->tombstone = false;

    // increment and maybe resize
    mapPtr->size++;
    resize(mapPtr);

    // call node insert
    insert_node_hashmap(mapPtr, new);
}
int delete_hashmap(HashMap *mapPtr, char *key)
{
    size_t hash = hash_key(key, mapPtr->capacity);
    size_t compare = mapPtr->capacity;
    for (size_t i = hash; i < compare; i++)
    {
        NodePtr cur = mapPtr->array[i];
        // TODO: Ensure this is intended use (doubling back over)
        if (cur == NULL)
            return 0;
        else if (cur->tombstone)
            continue;
        else if (cur->key == key)
        {
            // decrement and maybe resize
            mapPtr->size--;
            cur->tombstone = true;
            resize(mapPtr);
            return cur->val;
        }
        if (hash != 0 && i == mapPtr->capacity)
        {
            i = 0;
            compare = hash;
        }
    }
    return 0;
}

int get_hashmap(HashMap map, char *key)
{
    size_t hash = hash_key(key, map.capacity);
    size_t compare = map.capacity;
    for (size_t i = hash; i < compare; i++)
    {
        NodePtr cur = map.array[i];
        // TODO: Ensure this is intended use (doubling back over)
        if (cur == NULL)
            return 0;
        else if (cur->tombstone)
            continue;
        else if (cur->key == key)
            return cur->val;
        if (hash != 0 && i == map.capacity)
        {
            i = 0;
            compare = hash;
        }
    }
    return 0;
}

void print_hashmap(HashMap map)
{
    puts("-- printing hashmap --");
    for (size_t i = 0; i < map.capacity; i++)
    {
        NodePtr n = map.array[i];
        if (n == NULL)
            puts("NULL");
        else if (n->tombstone == true)
            puts("RIP");
        else
            printf("%s:%d\n", n->key, n->val);
    }
}

void insert_node_hashmap(HashMap *mapPtr, NodePtr nodePtr)
{
    // Open Addressing time!
    size_t hash = hash_key(nodePtr->key, mapPtr->capacity);
    // go from arr[hash] to arr[end], then arr[0] to arr[hash - 1]
    size_t smallest_spot = mapPtr->capacity;
    if (mapPtr->array[hash] != NULL)
    {
        size_t compare = mapPtr->capacity;
        for (size_t i = hash; i < compare; i++)
        {
            NodePtr cur = mapPtr->array[i];
            // TODO: Ensure this is intended use (doubling back over)
            if (cur == NULL)
            {
                // blank space
                smallest_spot = i < smallest_spot ? i : smallest_spot;
                break;
            }
            else if (cur->tombstone)
                smallest_spot = i < smallest_spot ? i : smallest_spot;

            if (hash != 0 && i == mapPtr->capacity - 1)
            {
                i = 0;
                compare = hash;
            }
        }
    }
    else
    {
        smallest_spot = hash;
    }
    mapPtr->array[smallest_spot] = nodePtr;
}

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
    double load_factor = (double)mapPtr->size / mapPtr->capacity;
    size_t old_cap = mapPtr->capacity;
    if (load_factor > 0.70)
    {
        mapPtr->capacity *= 2;
    }
    else if (load_factor < 0.25)
    {
        mapPtr->capacity /= 2;
    }
    else
        return;

    printf("Resizing: cap=%d -> cap=%d\n", old_cap, mapPtr->capacity);
    NodePtr *old = mapPtr->array;
    NodePtr *new = calloc(mapPtr->capacity, sizeof(NodePtr));
    mapPtr->array = new;

    for (size_t i = 0; i < old_cap; i++)
    {
        NodePtr n = old[i];
        if (n != NULL && n->tombstone == false)
            insert_node_hashmap(mapPtr, n);
    }
}
/*
Open Addressing

ArrayList[NodePtr]
- Insert
    - search until empty spot
    - if key already exists, overwrite
    - otherwise, insert at first tombstone/empty spot fre

- when index is full
- simply put it somewhere else (farther down)

when you delete something,
- put a tombstone signifying something existed but was deleted
- [A, X, C]

resize
- new 2x size array-list
- rehash and move everything

- scenario:
hash function likes to cluster
- fix:
https://en.wikipedia.org/wiki/Quadratic_probing
For m = 2^n, a good choice for the constants are c1 = c2 = 1/2

H + i/2 + i^2/2 ... mod length
*/