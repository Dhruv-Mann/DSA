#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef Stack_h
#define Stack_h

struct Stack
{
    int size;
    int top;
    Node **S;
};

void create_stack(struct Stack *st, int size)
{
    st->size = size;
    st->top = -1;
    st->S = (Node **)malloc(st->size * sizeof(Node *));
}

void push(struct Stack *st, Node *x)
{
    if (st->top == st->size - 1)
    {
        printf("Overflow!");
    }
    else
    {
        st->top++;
        st->S[st->top] = x;
    }
}

Node *pop(struct Stack *st)
{
    Node *x = NULL;
    if (st->top == -1)
    {
        printf("Undeflow!");
    }
    else
    {
        x = st->S[st->top--];
    }
    return x;
}

int IsEmpty(struct Stack st)
{
    if (st.top == -1)
    {
        return 1;
    }
    return 0;
}

int isFull(struct Stack st)
{
    return st.top == st.size - 1;
}

#endif