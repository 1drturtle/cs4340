#include <stdio.h>
#include <stdlib.h>

void print_in_order(int arr[], size_t length);
size_t binary_search(int arr[], size_t length, int key);

int main_binary_sort(int argc, char *argv[])
{
    // int a[1000] = {};
    // for (int i = 0; i < 1000; i++)
    // {
    //     a[i] = i * 2 + 2;
    // }

    // printf("%d\n", binary_search(a, 1000, 2));
    // printf("%d\n", binary_search(a, 1000, 4));
    // printf("%d\n", binary_search(a, 1000, 6));
    // printf("%d\n", binary_search(a, 1000, 8));

    // // breaks
    // printf("%d\n", binary_search(a, 1000, 0));
    // printf("%d\n", binary_search(a, 1000, 9));

    int a[4] = {0, 1, 2, 3};
    printf("%d\n", binary_search(a, 4, 4));

    return 0;
}

size_t binary_search(int arr[], size_t length, int key)
{
    int mid = length / 2;
    int current = arr[mid];

    if (current > key)
        return binary_search(arr, mid, key);
    else if (current < key)
        return mid + binary_search(arr + mid, (length + 1) / 2, key);
    else
        return mid;
}