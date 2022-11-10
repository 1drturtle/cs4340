#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct name
{
    char *first;
    char *middle;
    char *last;
} Name;

typedef Name *NamePtr;

char **create_arr(size_t size);
void resize_arr(char **arr, size_t new_size);
char **copy_arr(char **arr, size_t size);
void concat_array(char *string, char **arr, size_t size);
char *full_name(NamePtr namePtr);

int main(int argc, char *argv[])
{
    // question 1
    puts("-- question 1 --");
    puts("-> string array 1 element");
    puts("-> printing i=0 (NULL)");
    char **str_array = create_arr(1);
    puts(str_array[0]);
    puts("-> set i=0 to hello, world");
    str_array[0] = "hello, world";
    puts(str_array[0]);

    // question 2
    puts("-- question 2 --");
    resize_arr(str_array, 3);
    puts("-> resize to 3 * 2 = 6");
    puts("-> set i=5 to hello, world");
    str_array[5] = "hello, world";
    puts(str_array[5]);

    // question 3
    puts("-- question 3 --");
    str_array[0] = "string 0";
    str_array[1] = "string 1";
    str_array[2] = "string 2";

    puts("-> copying str array");
    char **copy = copy_arr(str_array, 3);

    puts("-> modifying str in copy");
    copy[1] = "modified string 1";

    puts("-> printing original");
    puts(str_array[1]);

    puts("-> printing modified");
    puts(copy[1]);

    // done with copy
    free(copy);

    // question 4
    // not sure if you meant that they need to be separated by spaces, but since it wasn't included in assignment assuming no
    puts("-- question 4");
    // 8 characters long * 3 strings + NULL
    puts("-> creating string to copy to");
    char *concat = calloc(8 * 3 + 1, sizeof(char));

    puts("-> concat str_array into new string");
    concat_array(concat, str_array, 3);

    puts("-> printing concatenated string");
    puts(concat);

    // done with concat & str_array
    free(concat);
    free(str_array);

    // question 5
    // should the strings from the full_name be free'd? yes
    // would they be if they were stored? yes
    // am I lazy? yes
    puts("-- question 5 --");
    NamePtr namePtr = malloc(sizeof(Name));
    char *full;

    puts("-> John NULL NULL");
    namePtr->first = "John";
    namePtr->middle = NULL;
    namePtr->last = NULL;
    puts(full_name(namePtr));

    puts("-> John NULL Doe");
    namePtr->last = "Doe";
    puts(full_name(namePtr));

    puts("-> John Middle Doe");
    namePtr->middle = "Middle";
    puts(full_name(namePtr));

    puts("-> NULL NULL Doe");
    namePtr->first = NULL;
    namePtr->middle = NULL;
    puts(full_name(namePtr));

    puts("-> NULL NULL NULL");
    namePtr->last = NULL;
    puts(full_name(namePtr));

    // done with NamePtr.
    // I think the strings need to be free'd too?
    free(namePtr->first);
    free(namePtr->middle);
    free(namePtr->last);

    free(namePtr);
}

char **create_arr(size_t size)
{
    // clear and allocate, return
    return calloc(size, sizeof(char *));
}
void resize_arr(char **arr, size_t new_size)
{
    // re-allocate, return
    arr = realloc(arr, 2 * new_size * sizeof(char *));
}
char **copy_arr(char **arr, size_t size)
{
    // create new array to store values
    char **new = create_arr(size);
    for (size_t i = 0; i < size; i++)
    {
        // create space for new string
        char *new_str = malloc(sizeof(char) * strlen(arr[i]) + 1);
        // copy string into space
        strcpy(new_str, arr[i]);
        // point array at new space
        new[i] = new_str;
    }
    return new;
}
void concat_array(char *string, char **arr, size_t size)
{
    // for each
    for (size_t i = 0; i < size; i++)
        // concat to end
        strcat(string, arr[i]);
}
char *full_name(NamePtr namePtr)
{
    // dereference namePtr
    Name name = *namePtr;

    // calculate name of string
    size_t name_size = 0;
    if (name.first != NULL)
        name_size += strlen(name.first) + 1;
    if (name.middle != NULL)
        name_size += strlen(name.middle) + 1;
    if (name.last != NULL)
        name_size += strlen(name.last) + 1;

    // create full name string
    char *full_name = calloc(name_size, sizeof(char));

    // add each part of name, and a space if necessary.
    if (name.first != NULL)
    {
        strcat(full_name, name.first);
    }
    if (name.middle != NULL)
    {
        if (name.first != NULL)
            strcat(full_name, " ");
        strcat(full_name, name.middle);
    }
    if (name.last != NULL)
    {
        if (name.first != NULL || name.middle != NULL)
            strcat(full_name, " ");
        strcat(full_name, name.last);
    }
    return full_name;
}