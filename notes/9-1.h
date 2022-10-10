#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ARRAY_SIZE 100
#define MAX_VAL 100

void selection_sort_iterative(int a[], int n);
void insertion_sort_iterative(int a[], int n);

void selection_sort_recursive(int a[], int n);
int selection_helper(int arr[], int n);

void insertion_sort_recursive(int arr[], int size);
void insertion_helper(int arr[], int size, int value);

void fill_array(int a[], int n);
void print_array(int a[], int n);
void copy_array(int src[], int dst[], size_t size);

float mean(int a[], int size);
float median(int a[], int size);
int *mode(int a[], int size);

int main_9_1(void)
{
    srand(42);

    int nums[ARRAY_SIZE];
    int base_nums[ARRAY_SIZE];

    clock_t start, end;

    fill_array(base_nums, ARRAY_SIZE);
    puts("original:");
    print_array(base_nums, ARRAY_SIZE);

    // did not make copy array function since sizeof parameter changes with scope
    memcpy(nums, base_nums, sizeof(nums));
    start = clock();
    selection_sort_recursive(nums, ARRAY_SIZE);
    end = clock();
    printf("Recursive Selection Sort: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
    print_array(nums, ARRAY_SIZE);

    memcpy(nums, base_nums, sizeof(nums));
    start = clock();
    insertion_sort_recursive(nums, ARRAY_SIZE);
    end = clock();
    printf("Recursive Insertion Sort: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
    print_array(nums, ARRAY_SIZE);

    memcpy(nums, base_nums, sizeof(nums));
    start = clock();
    selection_sort_iterative(nums, ARRAY_SIZE);
    end = clock();
    printf("Iterative Selection Sort: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
    print_array(nums, ARRAY_SIZE);

    memcpy(nums, base_nums, sizeof(nums));
    start = clock();
    insertion_sort_iterative(nums, ARRAY_SIZE);
    end = clock();
    printf("Iterative Insertion Sort: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
    print_array(nums, ARRAY_SIZE);

    // Mean
    int test[4] = {5, 5, 2, 2};
    printf("Mean: %.1f\n", mean(nums, ARRAY_SIZE));
    // Median
    printf("Median: %.1f\n", median(nums, ARRAY_SIZE));
    // Mode
    mode(nums, ARRAY_SIZE);

    return 0;
}

// re-randomize list after a sort
void fill_array(int a[], int n)
{
    for (int i = 0; i < n; ++i)
        a[i] = rand() % n;
}

void print_array(int a[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d,", a[i]);
    puts("");
}
void copy_array(int src[], int dst[], size_t size)
{
    memcpy(dst, src, size);
}

/*
selection_sort(array, size)
{
    base case: end of array
    otherwise:
        selection_helper()
        swap 0 and min_index
        selection_sort(array+1, size-1)
}

selection_helper(array, size)
{
    base case: end of array
        return 0
    otherwise:
        min = selection_helper(arr+1, size-1) +1
        compare (arr[0] & min) and return min_index
}
*/
void selection_sort_recursive(int arr[], int size)
{
    int next_min, tmp;

    if (size == 1)
        return;

    // find next minimum index
    next_min = selection_helper(arr, size);

    // we swap
    tmp = arr[0];
    arr[0] = arr[next_min];
    arr[next_min] = tmp;

    // go again
    return selection_sort_recursive(arr + 1, size - 1);
}

int selection_helper(int array[], int size)
{
    if (size == 1)
        return 0;
    int min = selection_helper(array + 1, size - 1) + 1;
    if (array[0] > array[min])
        return min;
    return 0;
}

/*
recursive insertion sort

insertion_sort(array, size)
    base case: one-element, return
    otherwise:
        sort first elements
        insertion_sort(arr, size - 1);
        insertion_helper(arr, size-1, current_value);

insertion_helper(array, size, value)
    base_case: size == 1 || value >= array[size - 2]
        array[size - 1] = value
    otherwise:
        array[size - 1] = array[size - 2];
        insertion_helper(array, size - 1, value)

*/
void insertion_sort_recursive(int arr[], int size)
{
    if (size == 1)
        return;

    insertion_sort_recursive(arr, size - 1);

    // helper function to move thing
    insertion_helper(arr, size, arr[size - 1]);
}
void insertion_helper(int arr[], int size, int value)
{
    if (size == 1 || value >= arr[size - 2])
        arr[size - 1] = value;
    else
    {
        arr[size - 1] = arr[size - 2];
        insertion_helper(arr, size - 1, value);
    }
}

void selection_sort_iterative(int a[], int n)
{
    int i, j, min, tmp;
    // we don't look at he last element since we do that in finding minimum
    for (min = i = 0; i < n - 1; min = ++i)
    {
        // find the next smallest value's index
        for (j = i + 1; j < n; ++j)
        {
            if (a[min] > a[j])
                min = j;
        }
        // swap if we don't have the same index
        // can't have same value due to less than comparison
        if (min != i)
        {
            tmp = a[min];
            a[min] = a[i];
            a[i] = tmp;
        }
    }
}
void insertion_sort_iterative(int a[], int n)
{
    int i, j, value;
    for (i = 1; i < n; ++i)
    {
        value = a[i];
        for (j = i; j > 0 && a[j - 1] > value; --j)
        {
            a[j] = a[j - 1];
        }
        a[j] = value;
    }
}

float mean(int a[], int size)
{
    float total = 0.0;
    for (int i = 0; i < size; i++)
    {
        total += a[i];
    }
    return total / size;
}
float median(int a[], int size)
{
    float median = 0;

    if (size % 2 == 1)
    {
        int median_index = (size / 2);
        return a[median_index];
    }
    else
    {
        median += a[size / 2 - 1] + a[size / 2];
        median /= 2;
        return median;
    }
}
int *mode(int a[], int size)
{
    int counts[MAX_VAL] = {};
    for (int i = 0; i < size; i++)
    {
        counts[a[i]]++;
    }
    // find the highest #
    int highest_count = 0;
    for (int i = 0; i < size; i++)
    {
        if (counts[i] > highest_count)
            highest_count = counts[i];
    }
    printf("Modes: ");
    for (int i = 0; i < MAX_VAL; i++)
    {
        if (counts[i] == highest_count)
            printf("%d, ", i);
    }
    puts(" ");
}