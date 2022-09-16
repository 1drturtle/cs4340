#include <stdio.h>

void fun_9_9(int[]);

int main_9_9(int argc, char *argv[])
{

    int arr[] = {1, 2, 3, 4, 5, 6};
    fun_9_9(arr);
    return 0;
}
void fun_9_9(int arr[5])
{
    // size of array in function header does nothing
    // like below
    printf("%zu bytes\n", sizeof(arr));
    printf("%d\n", arr[5]);
}