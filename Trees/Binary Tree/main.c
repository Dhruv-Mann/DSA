#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

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
    return 0;
}