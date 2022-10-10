#include <stdio.h>
#include <stdlib.h>

void print_in_order(int arr[], size_t length);
size_t binary_search(int arr[], size_t length, int key);

// binary sort
// chris agrella
// 9/23/2022
int main_binary_search(int argc, char *argv[])
{
    int a[1000] = {};
    for (int i = 0; i < 1000; i++)
    {
        a[i] = i * 2 + 2;
    }

    printf("index of 2: %d\n", binary_search(a, 1000, 2));
    printf("index of 4: %d\n", binary_search(a, 1000, 4));
    printf("index of 6: %d\n", binary_search(a, 1000, 6));
    printf("index of 8: %d\n", binary_search(a, 1000, 8));
    printf("index of 1998: %d\n", binary_search(a, 1000, 1998));
    printf("index of 2000: %d\n", binary_search(a, 1000, 2000));
    printf("index of 2001: %d\n", binary_search(a, 1000, 2001));
    printf("index of 0: %d\n", binary_search(a, 1000, 0));
    printf("index of 9: %d\n", binary_search(a, 1000, 9));

    return 0;
}

size_t binary_search(int arr[], size_t length, int key)
{

    int mid = length / 2;

    if (key < arr[mid])
    {
        // first element is too small?
        if (arr[0] > key)
            return -1;
        return binary_search(arr, mid, key);
    }
    else if (key > arr[mid])
    {
        // last element is too big?
        if (arr[length - 1] < key)
            return -1;

        size_t i = binary_search(arr + mid, (length + 1) / 2, key);
        // dont add the mid point if we get -1
        if (i == -1)
            return i;
        return mid + i;
    }
    else
        return mid;

    return -1;
}