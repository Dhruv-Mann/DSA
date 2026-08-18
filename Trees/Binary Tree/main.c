#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "Stack.h"

Node *root = NULL;

void TreeCreate()
{
    struct Node *p, *t;
    int x;
    struct Circular_Queue q;
    create(&q, 100);

    printf("Enter root value: ");
    scanf("%d", &x);

    root = (Node *)malloc(sizeof(Node));
    root->data = x;
    root->lchild = root->rchild = NULL;
    enqueue(&q, root);

    while (!isEmpty(q))
    {
        p = dequeue(&q);
        if (p == NULL)
            break;

        printf("Enter the value of left child of %d: ", p->data);
        scanf("%d", &x);
        if (x != -1)
        {
            t = (Node *)malloc(sizeof(Node));
            t->data = x;
            t->lchild = t->rchild = NULL;
            p->lchild = t;
            enqueue(&q, t);
        }
        printf("Enter the value of right child of %d: ", p->data);
        scanf("%d", &x);
        if (x != -1)
        {
            t = (Node *)malloc(sizeof(Node));
            t->data = x;
            t->lchild = t->rchild = NULL;
            p->rchild = t;
            enqueue(&q, t);
        }
    }
}

// Recursive traversal--

void Preorder(Node *p)
{
    if (p)
    {
        printf("%d ", p->data);
        Preorder(p->lchild);
        Preorder(p->rchild);
    }
}
void Inorder(Node *p)
{
    if (p)
    {
        Inorder(p->lchild);
        printf("%d ", p->data);
        Inorder(p->rchild);
    }
}
void Postorder(Node *p)
{
    if (p)
    {
        Postorder(p->lchild);
        Postorder(p->rchild);
        printf("%d ", p->data);
    }
}

// Iterative Traversal--

void IPreorder(Node *p)
{
    struct Stack stk;
    create_stack(&stk, 100);

    while (p || !IsEmpty(stk))
    {
        if (p)
        {
            printf("%d ", p->data);
            push(&stk, p);
            p = p->lchild;
        }
        else
        {
            p = pop(&stk);
            p = p->rchild;
        }
    }
}

void IInorder(Node *p)
{
    struct Stack stk;
    create_stack(&stk, 100);

    while (p || !IsEmpty(stk))
    {
        if (p)
        {
            push(&stk, p);
            p = p->lchild;
        }
        else
        {
            p = pop(&stk);
            printf("%d ", p->data);
            p = p->rchild;
        }
    }
}

void IPostorder(Node *p)
{
    struct Stack stk;
    Node *lastVisited = NULL;
    Node *peekNode = NULL;
    create_stack(&stk, 100);

    while (p || !IsEmpty(stk))
    {
        if (p)
        {
            push(&stk, p);
            p = p->lchild;
        }
        else
        {
            peekNode = stk.S[stk.top];

            if (peekNode->rchild && lastVisited != peekNode->rchild)
            {
                p = peekNode->rchild;
            }
            else
            {
                printf("%d ", peekNode->data);
                lastVisited = pop(&stk);
            }
        }
    }
}

void LevelOrderTraversal(struct Node *root)
{
    struct Circular_Queue q;
    create(&q, 100);

    printf("%d ", root->data);
    enqueue(&q, root);

    while (!isEmpty(q))
    {
        root = dequeue(&q);
        if (root->lchild)
        {
            printf("%d ", root->lchild->data);
            enqueue(&q, root->lchild);
        }
        if (root->rchild)
        {
            printf("%d ", root->rchild->data);
            enqueue(&q, root->rchild);
        }
    }
}

int main()
{

    TreeCreate();
    printf("Preorder: ");
    Preorder(root);
    printf("\n");
    printf("Postorder: ");

    Postorder(root);
    printf("\n");
    printf("Inorder: ");

    Inorder(root);
    printf("\n");

    printf("Iterative Preorder: ");
    IPreorder(root);
    printf("\n");

    printf("Iterative Postorder: ");
    IPostorder(root);
    printf("\n");

    printf("Iterative Inorder: ");
    IInorder(root);
    printf("\n");

    printf("Level Order Traversal: ");
    LevelOrderTraversal(root);
    printf("\n");
    return 0;
}