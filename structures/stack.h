#include <stdio.h>

// TODO: Replace with Node when submitting
#include "node.h"

typedef struct stack
{
    int *array;
    // max capacity of array in # of elements
    size_t capacity;
    // current size of array in # of elements
    size_t length;
} Stack;

typedef Stack *StackPointer;
size_t INITIAL_CAPACITY = 8;

StackPointer stack_create();
void stack_clear(StackPointer stackPtr);
void stack_push(StackPointer stackPtr, int value);
int stack_pop(StackPointer stackPtr);
int stack_peek(StackPointer stackPtr);
void stack_print(StackPointer stackPtr);
void resize_if_full(StackPointer stackPtr);

int main_stack(int argc, char *argv[])
{
    // Stack
    // First in, last out
    // Last in, First out

    StackPointer stack = NULL;
    stack = stack_create();

    for (int i = 0; i < 3; i++)
        stack_push(stack, i + 3);

    for (int i = 0; i < 3; i++)
    {
        stack_print(stack);
        printf("pop: %d\n", stack_pop(stack));
    }

    stack_push(stack, 10);
    printf("peek, 10==%d\n", stack_peek(stack));

    for (int i = 0; i < 100; i++)
        stack_push(stack, i);

    stack_print(stack);
    stack_clear(stack);
    puts("clearing");
    stack_print(stack);
}
StackPointer stack_create()
{
    StackPointer new = malloc(sizeof(StackPointer));
    new->length = 0;
    new->capacity = INITIAL_CAPACITY;

    // new.array = malloc(new.capacity * sizeof(int));
    // calloc(length, size) for allocating array
    new->array = calloc(new->capacity, sizeof(int));

    return new;
}

void stack_clear(StackPointer stackPtr)
{
    // we don't care about the actual array
    // if the length is 0 elements are *gone*
    stackPtr->length = 0;
}
void stack_push(StackPointer stackPtr, int value)
{
    resize_if_full(stackPtr);
    stackPtr->array[stackPtr->length] = value;

    stackPtr->length++;
}
int stack_pop(StackPointer stackPtr)
{

    if (stackPtr->length == 0)
        return -1; // TODO: desired case on length==0

    int pop = stackPtr->array[stackPtr->length - 1];
    stackPtr->length--;
    return pop;
}
int stack_peek(StackPointer stackPtr)
{
    if (stackPtr->length == 0)
        return -1; // TODO: desired case on length==0
    return stackPtr->array[stackPtr->length - 1];
}
void stack_print(StackPointer stackPtr)
{
    for (int i = stackPtr->length - 1; i >= 0; --i)
    {
        printf("%d->", stackPtr->array[i]);
    }
    puts("END");
}

void resize_if_full(StackPointer stackPtr)
{
    if (stackPtr->length == stackPtr->capacity)
    {
        stackPtr->capacity *= 2;
        // realloc: re-allocate memory
        stackPtr->array = realloc(stackPtr->array, stackPtr->capacity * sizeof(int));
    }
}