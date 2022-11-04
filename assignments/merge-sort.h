#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void MergeSort(int *A, size_t length);
void mergesort(int *A, int *B, size_t length);

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
    MergeSort(A, 10);
    return 0;
}

void MergeSort(int *A, size_t length)
{
    int *B = calloc(length, sizeof(int));
    memcpy(B, A, sizeof(int) * length);
    mergesort(A, B, length);
}

void mergesort(int *A, int *B, size_t length)
{
    if (length == 1)
        return;

    mergesort(A, B, length / 2);
    mergesort(A + length / 2, B + length / 2, length / 2);

    // merge B into A w/ Zipper
}