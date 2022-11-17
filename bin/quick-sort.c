#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void QuickSort(int *arr, size_t size);
size_t partition(int *arr, size_t size);
void mid_of_three(int *arr, size_t size);
void print_array(int *arr, size_t size);
int medianThree(int a, int b, int c);

int main(int argc, char *argv[])
{
    srand(42);
    size_t LIST_SIZE = 21;
    int array[21];
    for (size_t i = 0; i < LIST_SIZE; i++)
    {
        array[i] = rand() % LIST_SIZE;
    }
    print_array(array, LIST_SIZE);
    QuickSort(array, LIST_SIZE);
    print_array(array, LIST_SIZE);
}
void QuickSort(int *arr, size_t size)
{
    if (size <= 1)
        return;
    mid_of_three(arr, size);
    size_t p = partition(arr, size);

    QuickSort(arr, p);
    // A[10]
    // p = 5
    // 0..5 == 6
    // 6..9
    QuickSort(arr + p, size - p);
}
size_t partition(int *arr, size_t size)
{
    if (size <= 1)
    {
        return 0;
    }
    int pivot = arr[size / 2];

    // Left index
    int i = -1;

    // Right index
    int j = size;

    int tmp;

    while (1 == 1)
    {
        do
        {
            i++;
        } while (arr[i] < pivot);

        do
        {
            j--;
        } while (arr[j] > pivot);

        // If the indices crossed, return
        if (i >= j)
            return i;

        // Swap the elements at the left and right indices
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}
void mid_of_three(int *arr, size_t size)
{
    int tmp;
    if (arr[0] > arr[size / 2])
    {
        tmp = arr[0];
        arr[0] = arr[size / 2];
        arr[size / 2] = tmp;
    }
    if (arr[size / 2] > arr[size - 1])
    {
        tmp = arr[size - 1];
        arr[size - 1] = arr[size / 2];
        arr[size / 2] = tmp;
    }
}
void print_array(int *arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
        printf("%d, ", arr[i]);
    puts("");
}