#include <stdio.h>
#include <stdlib.h>

// equivalent to Union[short, char]
// size is largest of options
// can have only one of its attributes
union number
{
    long long x;
    // OR
    double y;
};

int main_9_16(int argc, char **argv)
{
    union number example;
    printf("sizeof(example): %zu\n", sizeof(example));

    // void pointer is a un-typed pointer
    // to use it, it must be given a type later
    void *ptr;
    ptr = (void *)&example;
    // errors due to type void
    // ptr->x;
    // to fix;
    ((union number *)ptr)->x;

    // const values
    // must be initialzed on declaration
    const int x = 5;
    // but we can change them with a pointer
    // (C doesn't like this)
    int *xptr = &x;
    *xptr = 4;
    // this value cannot change via assignment
    const int *cptr = &x;
    int *const c_ptr = &x;
    // cptr = &(example.x); This breaks, as *const cannot change the Pointer
    const int *const constant_ptr = &x; // Both the value and pointer are constant
    printf("%d", x);

    return 0;
}