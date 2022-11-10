#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void MergeSort(int *A, size_t length);
void mergesort(int *A, int *B, size_t length);
void print_array(int *array, size_t length);

/*
Merge Sort
11/7
Chris Agrella
*/
int main_merge_sort(int argc, char *argv[])
{
    /*
    Merge Sort
    recursively split array into smaller and smaller pieces

    MergeSort(A, length)
    {
        copy A into B (use memcpy)
        mergesort(B, A, length)
    }
    mergesort(A, B, length)
    {
        if length is 1, return;
        mergesort first half of A into first half of B
            mergesort(A, B, length/2);
        mergesort second half of A into second half of B
            mergesort(A + length/2, B + length/2, length/2); (figure out even/odd)
        merge B into A
    }
    */
    int A[10] = {10, 1, 9, 2, 8, 3, 7, 4, 6, 5};
    puts("array before sort, n=10");
    print_array(A, 10);
    MergeSort(A, 10);
    puts("sorted n=10");
    print_array(A, 10);
    puts("array before sorted n=11");
    int B[11] = {11, 4, 3, 2, 7, 8, 9, 1, 10, 5, 6};
    print_array(B, 11);
    MergeSort(B, 11);
    puts("sorted n=11");
    print_array(B, 11);

    return 0;
}
void print_array(int *array, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        printf("%d, ", array[i]);
    }
    puts("");
}

void MergeSort(int *A, size_t length)
{
    int *B = calloc(length, sizeof(int));
    memcpy(B, A, sizeof(int) * length);
    mergesort(A, B, length);
}

void mergesort(int *A, int *B, size_t length)
{
    if (length <= 1)
        return;

    // first half of B into A
    mergesort(B, A, length / 2);
    // 2nd half of A into B
    mergesort(B + length / 2, A + length / 2, length / 2 + (length % 2));

    // zipper merge
    int *listA = B;
    size_t sizeA = length / 2;
    int *listB = B + length / 2;
    size_t sizeB = length / 2 + (length % 2);

    size_t indexA = 0, indexB = 0;

    while (indexA < sizeA && indexB < sizeB)
    {
        if (*listA < *listB)
            A[(indexA++) + indexB] = *listA++;
        else
            A[indexA + indexB++] = *listB++;
    }
    // add remainder
    for (; indexA < sizeA; indexA++)
        A[indexA + indexB] = *listA++;
    for (; indexB < sizeB; indexB++)
        A[indexA + indexB] = *listB++;
}