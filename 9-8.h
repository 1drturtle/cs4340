#include <stdio.h>

void print_size_of(int arr[][3], size_t n);
void print_size_of_more(int **arr);
void pass_by_value(int x);
void pass_by_value_array(int arr[], size_t s);

int main_9_8(int argc, char **argv)
{
    int a[][3] = {{1, 2, 3}, {4, 5, 6}};
    printf("%p\n", a);
    printf("%d\n", *(*a + 5));

    int *b = *a; // b now has the memory address of the first sub-array of a.
    printf("%d\n", *(b + 5));

    puts("");

    printf("%p, %p\n", a, *a);
    int c[3];
    printf("%p, %p\n", c, *c);

    // for (size_t i = 0, j; i < 2; ++i)
    //     // for (j = 0; j < 3; ++j)
    //     printf("%p,", *(a + i));
    // puts("");

    int x = 6;
    int *xptr = &x;
    // xptr holds memory address of x via & unary operator
    printf("%p\n", xptr);
    // * unary operator to "dereference memory address"
    printf("%d\n", *xptr);

    // print_size_of_more(a);

    // Arrays of strings
    char *strings[] = {"Keethan",
                       "Kleiner",
                       "Rainbow",
                       "Valve"};
    for (size_t i = 0; i < 4; i++)
        puts(strings[i]);
    char **s = strings;
    for (size_t i = 0; i < 4; ++i)
        // De-reference the array + index i
        puts(*(s + i));

    for (size_t i = 0; i < argc; ++i)
        puts(*(argv + i));
    /*
    pass by reference
    - changes made within function are modified
    pass by value
    - changes made within function are not modified
    */
    int y = 6;
    pass_by_value(y);
    printf("%d\n", y);
    c[0] = 6;
    pass_by_value_array(c, 3);
    printf("%d\n", c[0]);
    /*
    pass-by-object reference
    Immutable objects are not re-assigned but mutable objects are modified in a local scope of a function
    */

    return 0;
}
void print_size_of(int arr[][3], size_t n)
{
    printf("%zu\n", sizeof(arr));
    printf("%zu\n", sizeof(arr[0]));
}

void print_size_of_more(int **arr)
{
    printf("%zu\n", sizeof(arr));
    printf("%zu\n", sizeof(*arr));
    printf("%p, %p\n", arr, *arr);
    printf("%p\n", *arr + 3);
}
void pass_by_value(int x)
{
    x = 5;
}
void pass_by_value_array(int arr[], size_t s)
{
    arr[0] = 5;
}