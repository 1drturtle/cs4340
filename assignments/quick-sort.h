#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void QuickSort(int *arr, size_t size);
size_t partition(int *arr, size_t size);

int main_quick_sort(int argc, char *argv[])
{
    /*
    "Pivot" - one piece of data that is roughly equal to median of data
    everything less of pivot is moved left and everything greater is moved right

    partition
    - find median of 0, mid, end
    - move median to middle of list
    - run quicksort
    - repeat 3 with sub-lists recursively
    https://en.wikipedia.org/wiki/Quicksort#Hoare_partition_scheme
    */
    int A[10] = {10, 1, 9, 2, 8, 3, 7, 4, 6, 5};
    QuickSort(A, 10);
    for (size_t i = 0; i < 10; i++)
    {
        printf("%d, ", A[i]);
    }
    puts("");
}
void QuickSort(int *arr, size_t size)
{
    if (size <= 1)
        return;

    size_t p = partition(arr, size);
    /*
    size=10
    arr, 5
    arr + 5, 5
    */
    QuickSort(arr, size / 2);                         // working
    QuickSort(arr + size / 2, size / 2 + (size % 2)); // broken
}
size_t partition(int *arr, size_t size)
{
    if (size == 1)
        return 0;

    int pivot = arr[size / 2];
    int tmp;

    // TODO: Fix code (j & i become -1, edge case?)
    int i = -1;
    int j = size + 1;

    while (1 == 1)
    {
        while (arr[i] < pivot)
            i++;

        while (arr[j] > pivot)
            j--;

        if (i >= j)
            return j;

        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}