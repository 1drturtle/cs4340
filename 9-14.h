#include <stdio.h>
#include <stdlib.h>

void print_in_order(int arr[], size_t length);
size_t binary_search(int arr[], size_t length, int target);

int main_9_14(int argc, char *argv[])
{
    // pointers to functions, functions as parameters
    // int and char point to same place, lowest 8 bits of int
    // walk through a larger type with a pointer of a smaller type
    // create x and then y, separated by sizeof(y)
    // memory address points to LEAST significant bit
    // for creating primitives, memory is addressed down
    // ^^ old stuff above ^^

    // negative numbers count down from 11111111... == -1

    int a[8] = {5, 6, 7, 8, 9, 10, 11, 12};
    // print_in_order(a, 4);

    // binary search
    printf("%lld\n", binary_search(a, 8, 9));

    return 0;
}

void print_in_order(int arr[], size_t length)
{
    if (length == 0)
        return;
    printf("%d\n", arr[0]);
    return print_in_order(arr + 1, length - 1);
}

size_t binary_search(int arr[], size_t length, int target)
{
    // if length == 1 && arr[0] == target
    // find middle of array
    // if not target,
    // if target > middle, recursive on upper half (array+length/2, length/2)
    // if target < middle, recursive on lower half (array, length/2)

    // keep track of current search index
    // each function knows what index to look for

    int bounded = 0;

    int mid = arr[length / 2];
    if (mid == target)
    {
        return bounded + length / 2;
    }
    else if (target < mid)
    {
        bounded -= length / 2;
        return bounded + binary_search(arr, length / 2, target);
    }
    else if (target > mid)
    {
        bounded += length / 2;
        return bounded + binary_search(arr + length / 2, length / 2, target);
    }
    return -1;
}