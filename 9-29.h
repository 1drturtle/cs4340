#include <stdio.h>

void test(int y);

typedef struct node
{
    char attr;
} Node;

int main_9_29(int argc, char *argv[])
{
    struct node *ptr = NULL;

    printf("%d\n", ptr->attr);
    printf("%d\n", (*ptr).attr);
    return 0;
}

void test(int x)
{
    printf("%d\n", x);
}