#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void bubblesort(int a[], int n) {
  bool sorted;
  int i, j, tmp;
  for (i = 0, sorted = false; !sorted && i < n - 1; ++i) {
    sorted = true;
    for (int j = 0; j < n - 1 - i; ++j) {
      if (a[j] > a[j + 1]) {
        tmp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = tmp;
        sorted = false;
      }
    }
  }
}

void insertion_sort_recursive(int a[], int n) {
  int i, j, value;
  for (i = 1; i < n; ++i) {
    value = a[i];
    for (j = i; j > 0 && a[j - 1] > value; --j) {
      a[j] = a[j - 1];
    }
    a[j] = value;
  }
}

void selectionsort(int a[], int n) {
  int i, j, min, tmp;
  // we don't look at he last element since we do that in finding minimum
  for (min = i = 0; i < n - 1; min = ++i) {
    // find the next smallest value's index
    for (j = i + 1; j < n; ++j) {
      if (a[min] > a[j])
        min = j;
    }
    // swap if we don't have the same index
    // can't have same value due to less than comparison
    if (min != i) {
      tmp = a[min];
      a[min] = a[i];
      a[i] = tmp;
    }
  }
}
