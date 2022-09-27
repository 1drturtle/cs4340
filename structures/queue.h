#include <stdio.h>

// TODO: Replace with Node when submitting
#include "node.h"

typedef struct queue
{
    NodePtr head; // front (pop)
    NodePtr tail; // back (push)
} Queue;

typedef Queue *QueuePtr;

void q_push(QueuePtr queuePtr, int value);
int q_pop(QueuePtr queuePtr, int index);
int q_peek(QueuePtr queuePtr, int index);
QueuePtr q_create(QueuePtr queuePtr);
QueuePtr q_destroy(QueuePtr queuePtr);
void q_print(Queue queue);

int main_queue(int argc, char *argv[])
{
    // queue from a linked list
    // stack from a linked list

    // Queue
    // First in, first out
    // last in, last out
    // [------]
    // push to tail
    // pop from head

    // pop push peek create destroy print?
    // pop -> remove head and return (remove tail if length == 1)
    // push -> add to tail, possibly set head
    // peek -> look at head
}