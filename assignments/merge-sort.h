#include <stdlib.h>

int main_merge_sort(int argc, char *argv[])
{
    // Merge Sort
    // recursively split array into smaller and smaller pieces
    /*
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
}