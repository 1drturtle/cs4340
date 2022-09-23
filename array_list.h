#include <stdio.h>
#include <stdlib.h>

size_t INITIAL_CAPACITY = 8;

// Sorted, dynamically sized list
typedef struct array_list
{
    int *array;
    // max capacity of array in # of elements
    size_t capacity;
    // current size of array in # of elements
    size_t length;

} ArrayList;

// create a new array list
ArrayList *create_al();
// destroy an array list
void destroy_al(ArrayList *listPtr);
// print out all elements of an array list
void print_al(ArrayList list);
// insert an element into an arraylist.
void insert_al(int value, ArrayList *listPtr);
void resize_if_full(ArrayList *listPtr);

int main_al(int argc, char *argv[])
{
    ArrayList *listPtr = create_al();
    ArrayList list = *listPtr;
    for (int i = 100; i >= 0; --i)
    {
        insert_al(i, listPtr);
    }

    print_al(*listPtr);
    destroy_al(listPtr);
    return 0;
}

ArrayList *create_al()
{
    ArrayList *new = malloc(sizeof(ArrayList));
    new->length = 0;
    new->capacity = INITIAL_CAPACITY;
    // new.array = malloc(new.capacity * sizeof(int));

    // calloc(length, size) for allocating array
    new->array = calloc(new->capacity, sizeof(int));

    return new;
}

void destroy_al(ArrayList *listPtr)
{
    free(listPtr->array);
    free(listPtr);
}

void print_al(ArrayList list)
{
    for (size_t i = 0; i < list.length; i++)
    {
        printf("%d,", list.array[i]);
    }
    puts("");
}

void insert_al(int value, ArrayList *listPtr)
{
    // re-size if full
    resize_if_full(listPtr);

    // insert
    size_t i;
    for (i = (listPtr->length)++;
         i > 0 && (listPtr->array)[i - 1] > value;
         i--)
    {
        listPtr->array[i] = listPtr->array[i - 1];
    }
    listPtr->array[i] = value;
}
void resize_if_full(ArrayList *listPtr)
{
    if (listPtr->length == listPtr->capacity)
    {
        listPtr->capacity *= 2;
        // realloc: re-allocate memory
        listPtr->array = realloc(listPtr->array, listPtr->capacity * sizeof(int));
    }
}