#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *next;
} Node;

typedef Node *NodePtr;

typedef struct queue
{
    NodePtr head; // front (pop)
    NodePtr tail; // back (push)
} Queue;

typedef Queue *QueuePtr;

void q_push(QueuePtr queuePtr, int value);
int q_pop(QueuePtr queuePtr);
int q_peek(QueuePtr queuePtr);
QueuePtr q_create();
void q_clear(QueuePtr queuePtr);
void q_print(QueuePtr queuePtr);

// chris agrella
// 10/1/2022
int main(int argc, char *argv[])
{
    // queue from a linked list
    // stack from a linked list

    // Queue
    // First in, first out
    // last in, last out
    // [------]
    // push to tail
    // pop from head

    // pop peek push print clear
    puts("Queue Code");

    QueuePtr queue = NULL;
    queue = q_create();
    q_push(queue, 1);
    q_push(queue, 5);
    q_push(queue, 6);

    q_print(queue); // 6->5->1->END

    printf("peek: %d\n", q_peek(queue)); // top = 6
    printf("pop: %d\n", q_pop(queue));   // pop 6
    printf("peek: %d\n", q_peek(queue)); // top = 5

    q_print(queue); // 5->1->END

    q_clear(queue);
    q_print(queue);                      // no elements, END
    printf("peek: %d\n", q_peek(queue)); // no elements (-1)

    puts("---");
}
QueuePtr q_create()
{
    QueuePtr q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}
void q_clear(QueuePtr queuePtr)
{
    NodePtr tmp;
    while (queuePtr->head != NULL)
    {
        tmp = queuePtr->head;
        queuePtr->head = queuePtr->head->next;
        free(tmp);
    }
}
void q_push(QueuePtr queuePtr, int value)
{
    NodePtr node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;

    // list is emtpy
    if (queuePtr->head == NULL)
    {
        queuePtr->head = node;
        queuePtr->tail = node;
    }
    // insert into existing
    else
    {
        node->next = queuePtr->head;
        queuePtr->head = node;
    }
}
int q_pop(QueuePtr queuePtr)
{

    NodePtr pop;
    int val;

    if (queuePtr->head == NULL)
        return -1; // TODO: null value return
    // get value of head
    pop = queuePtr->head;
    val = pop->value;
    // set head equal to next
    queuePtr->head = queuePtr->head->next;
    // free old head
    free(pop);
    // return val;
    return val;
}
int q_peek(QueuePtr queuePtr)
{
    if (queuePtr->head == NULL)
        return -1; // TODO: null value return

    return queuePtr->head->value;
}
void q_print(QueuePtr queuePtr)
{
    NodePtr cur = queuePtr->head;
    while (cur != NULL)
    {
        printf("%d->", cur->value);
        cur = cur->next;
    }
    puts("END");
}