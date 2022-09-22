#include <stdio.h>
#include <stdlib.h>

typedef struct array_list
{
    int *array;
    // max capacity of array in # of elements
    size_t capacity;
    // current size of array in # of elements
    size_t length;

} ArrayList;

ArrayList *create_al();
void destroy_al(ArrayList *listPtr);
void print_al(ArrayList list);
void insert_al(int value, ArrayList *listPtr);

int main_al(int argc, char *argv[])
{
    ArrayList *listPtr = create_al();
    ArrayList list = *listPtr;
    print_al(list);
    destroy_al(listPtr);
    return 0;
}

ArrayList *create_al()
{
    ArrayList *new = malloc(sizeof(ArrayList));
    new->length = 0;
    new->capacity = 8;
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
}