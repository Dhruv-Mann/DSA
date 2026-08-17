#ifndef Queue_h
#define Queue_h

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node *lchild;
    int data;
    struct Node *rchild;
};

typedef struct Node Node;  //  so we don't need to write struct Node everywhere, just Node

struct Circular_Queue
{
    int size;
    int front;
    int rear;
    Node **Q;
};

void create(struct Circular_Queue *q, int size)
{
    q->size = size;
    q->front = q->rear = 0;
    q->Q = (Node **)malloc((size_t)q->size * sizeof(Node *));
}

void enqueue(struct Circular_Queue *q, Node *x)
{
    if ((q->rear + 1) % q->size == q->front)
    {
        printf("Queue is full!");
    }
    else
    {
        q->rear = (q->rear + 1) % q->size;
        q->Q[q->rear] = x;
    }
}

Node *dequeue(struct Circular_Queue *q)
{
    Node *x = NULL;
    if (q->front == q->rear)
    {
        printf("Queue is empty!");
        return NULL;
    }
    else
    {
        q->front = (q->front + 1) % q->size;
        x = q->Q[q->front];
    }
    return x;
}
int isEmpty(struct Circular_Queue q)
{
    return q.front == q.rear;
}
#endif
