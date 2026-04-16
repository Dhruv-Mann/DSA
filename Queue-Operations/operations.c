#include <stdio.h>
#include <stdlib.h>

/*
 * ============================================================================
 *  QUEUE — COMPLETE OPERATIONS
 *  (Linear, Circular, Deque, Priority Queue)
 *  Each type has BOTH Array and Linked-List implementation.
 * ============================================================================
 *
 *  Queue follows FIFO: First In, First Out.
 *
 *  Core operations:
 *    - enqueue(x)
 *    - dequeue()
 *    - peek()/front()
 *    - display()
 *
 *  Deque operations:
 *    - insertFront(x), insertRear(x)
 *    - deleteFront(), deleteRear()
 *    - peekFront(), peekRear(), display()
 *
 *  Priority Queue rule in this program:
 *    - Lower value = Higher priority (MIN priority queue)
 *
 * ============================================================================
 */

#define MAX_SIZE 100


/* ============================================
 *  PART 1: LINEAR (SIMPLE) QUEUE — ARRAY
 * ============================================ */

struct LinearQueueArray {
    int arr[MAX_SIZE];
    int front;
    int rear;
};

void initLinearArray(struct LinearQueueArray* q) {
    q->front = -1;
    q->rear = -1;
}

int isEmptyLinearArray(struct LinearQueueArray* q) {
    return q->front == -1;
}

int isFullLinearArray(struct LinearQueueArray* q) {
    return q->rear == MAX_SIZE - 1;
}

void enqueueLinearArray(struct LinearQueueArray* q, int value) {
    if (isFullLinearArray(q)) {
        printf("Linear Queue (Array) Overflow! Cannot enqueue %d.\n", value);
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->arr[q->rear] = value;
    printf("Enqueued %d.\n", value);
}

int dequeueLinearArray(struct LinearQueueArray* q) {
    if (isEmptyLinearArray(q)) {
        printf("Linear Queue (Array) Underflow!\n");
        return -1;
    }
    int value = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return value;
}

int peekLinearArray(struct LinearQueueArray* q) {
    if (isEmptyLinearArray(q)) {
        printf("Linear Queue (Array) is empty!\n");
        return -1;
    }
    return q->arr[q->front];
}

void displayLinearArray(struct LinearQueueArray* q) {
    if (isEmptyLinearArray(q)) {
        printf("Linear Queue (Array) is empty!\n");
        return;
    }
    printf("Linear Queue (Array) (front -> rear): ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d", q->arr[i]);
        if (i < q->rear) printf(" | ");
    }
    printf("\n");
}


/* ===================================================
 *  PART 2: LINEAR (SIMPLE) QUEUE — LINKED LIST
 * =================================================== */

struct LinearNode {
    int data;
    struct LinearNode* next;
};

struct LinearQueueLinked {
    struct LinearNode* front;
    struct LinearNode* rear;
};

void initLinearLinked(struct LinearQueueLinked* q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmptyLinearLinked(struct LinearQueueLinked* q) {
    return q->front == NULL;
}

void enqueueLinearLinked(struct LinearQueueLinked* q, int value) {
    struct LinearNode* newNode = (struct LinearNode*)malloc(sizeof(struct LinearNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (isEmptyLinearLinked(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("Enqueued %d.\n", value);
}

int dequeueLinearLinked(struct LinearQueueLinked* q) {
    if (isEmptyLinearLinked(q)) {
        printf("Linear Queue (Linked List) Underflow!\n");
        return -1;
    }
    struct LinearNode* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return value;
}

int peekLinearLinked(struct LinearQueueLinked* q) {
    if (isEmptyLinearLinked(q)) {
        printf("Linear Queue (Linked List) is empty!\n");
        return -1;
    }
    return q->front->data;
}

void displayLinearLinked(struct LinearQueueLinked* q) {
    if (isEmptyLinearLinked(q)) {
        printf("Linear Queue (Linked List) is empty!\n");
        return;
    }
    printf("Linear Queue (Linked List) (front -> rear): ");
    struct LinearNode* temp = q->front;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) printf(" | ");
        temp = temp->next;
    }
    printf("\n");
}

void freeLinearLinked(struct LinearQueueLinked* q) {
    while (q->front != NULL) {
        struct LinearNode* temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
}


/* ====================================
 *  PART 3: CIRCULAR QUEUE — ARRAY
 * ==================================== */

struct CircularQueueArray {
    int arr[MAX_SIZE];
    int front;
    int rear;
    int count;
};

void initCircularArray(struct CircularQueueArray* q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isEmptyCircularArray(struct CircularQueueArray* q) {
    return q->count == 0;
}

int isFullCircularArray(struct CircularQueueArray* q) {
    return q->count == MAX_SIZE;
}

void enqueueCircularArray(struct CircularQueueArray* q, int value) {
    if (isFullCircularArray(q)) {
        printf("Circular Queue (Array) Overflow!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->arr[q->rear] = value;
    q->count++;
    printf("Enqueued %d.\n", value);
}

int dequeueCircularArray(struct CircularQueueArray* q) {
    if (isEmptyCircularArray(q)) {
        printf("Circular Queue (Array) Underflow!\n");
        return -1;
    }
    int value = q->arr[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->count--;
    return value;
}

int peekCircularArray(struct CircularQueueArray* q) {
    if (isEmptyCircularArray(q)) {
        printf("Circular Queue (Array) is empty!\n");
        return -1;
    }
    return q->arr[q->front];
}

void displayCircularArray(struct CircularQueueArray* q) {
    if (isEmptyCircularArray(q)) {
        printf("Circular Queue (Array) is empty!\n");
        return;
    }
    printf("Circular Queue (Array) (front -> rear): ");
    int idx = q->front;
    for (int i = 0; i < q->count; i++) {
        printf("%d", q->arr[idx]);
        if (i < q->count - 1) printf(" | ");
        idx = (idx + 1) % MAX_SIZE;
    }
    printf("\n");
}


/* ==========================================
 *  PART 4: CIRCULAR QUEUE — LINKED LIST
 * ========================================== */

/*
 * We keep a rear pointer.
 * front is rear->next when queue is non-empty.
 */
struct CircularNode {
    int data;
    struct CircularNode* next;
};

struct CircularQueueLinked {
    struct CircularNode* rear;
    int count;
};

void initCircularLinked(struct CircularQueueLinked* q) {
    q->rear = NULL;
    q->count = 0;
}

int isEmptyCircularLinked(struct CircularQueueLinked* q) {
    return q->rear == NULL;
}

void enqueueCircularLinked(struct CircularQueueLinked* q, int value) {
    struct CircularNode* newNode = (struct CircularNode*)malloc(sizeof(struct CircularNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;

    if (isEmptyCircularLinked(q)) {
        newNode->next = newNode;
        q->rear = newNode;
    } else {
        newNode->next = q->rear->next;
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
    printf("Enqueued %d.\n", value);
}

int dequeueCircularLinked(struct CircularQueueLinked* q) {
    if (isEmptyCircularLinked(q)) {
        printf("Circular Queue (Linked List) Underflow!\n");
        return -1;
    }

    struct CircularNode* front = q->rear->next;
    int value = front->data;

    if (front == q->rear) {
        q->rear = NULL;
    } else {
        q->rear->next = front->next;
    }

    free(front);
    q->count--;
    return value;
}

int peekCircularLinked(struct CircularQueueLinked* q) {
    if (isEmptyCircularLinked(q)) {
        printf("Circular Queue (Linked List) is empty!\n");
        return -1;
    }
    return q->rear->next->data;
}

void displayCircularLinked(struct CircularQueueLinked* q) {
    if (isEmptyCircularLinked(q)) {
        printf("Circular Queue (Linked List) is empty!\n");
        return;
    }

    printf("Circular Queue (Linked List) (front -> rear): ");
    struct CircularNode* temp = q->rear->next;
    for (int i = 0; i < q->count; i++) {
        printf("%d", temp->data);
        if (i < q->count - 1) printf(" | ");
        temp = temp->next;
    }
    printf("\n");
}

void freeCircularLinked(struct CircularQueueLinked* q) {
    while (!isEmptyCircularLinked(q)) {
        dequeueCircularLinked(q);
    }
}


/* ====================================
 *  PART 5: DEQUE — ARRAY
 * ==================================== */

struct DequeArray {
    int arr[MAX_SIZE];
    int front;
    int rear;
    int count;
};

void initDequeArray(struct DequeArray* d) {
    d->front = 0;
    d->rear = MAX_SIZE - 1;
    d->count = 0;
}

int isEmptyDequeArray(struct DequeArray* d) {
    return d->count == 0;
}

int isFullDequeArray(struct DequeArray* d) {
    return d->count == MAX_SIZE;
}

void insertFrontArray(struct DequeArray* d, int value) {
    if (isFullDequeArray(d)) {
        printf("Deque (Array) Overflow!\n");
        return;
    }
    d->front = (d->front - 1 + MAX_SIZE) % MAX_SIZE;
    d->arr[d->front] = value;
    d->count++;
    printf("Inserted %d at front.\n", value);
}

void insertRearArray(struct DequeArray* d, int value) {
    if (isFullDequeArray(d)) {
        printf("Deque (Array) Overflow!\n");
        return;
    }
    d->rear = (d->rear + 1) % MAX_SIZE;
    d->arr[d->rear] = value;
    d->count++;
    printf("Inserted %d at rear.\n", value);
}

int deleteFrontArray(struct DequeArray* d) {
    if (isEmptyDequeArray(d)) {
        printf("Deque (Array) Underflow!\n");
        return -1;
    }
    int value = d->arr[d->front];
    d->front = (d->front + 1) % MAX_SIZE;
    d->count--;
    return value;
}

int deleteRearArray(struct DequeArray* d) {
    if (isEmptyDequeArray(d)) {
        printf("Deque (Array) Underflow!\n");
        return -1;
    }
    int value = d->arr[d->rear];
    d->rear = (d->rear - 1 + MAX_SIZE) % MAX_SIZE;
    d->count--;
    return value;
}

int peekFrontDequeArray(struct DequeArray* d) {
    if (isEmptyDequeArray(d)) {
        printf("Deque (Array) is empty!\n");
        return -1;
    }
    return d->arr[d->front];
}

int peekRearDequeArray(struct DequeArray* d) {
    if (isEmptyDequeArray(d)) {
        printf("Deque (Array) is empty!\n");
        return -1;
    }
    return d->arr[d->rear];
}

void displayDequeArray(struct DequeArray* d) {
    if (isEmptyDequeArray(d)) {
        printf("Deque (Array) is empty!\n");
        return;
    }
    printf("Deque (Array) (front -> rear): ");
    int idx = d->front;
    for (int i = 0; i < d->count; i++) {
        printf("%d", d->arr[idx]);
        if (i < d->count - 1) printf(" | ");
        idx = (idx + 1) % MAX_SIZE;
    }
    printf("\n");
}


/* ==========================================
 *  PART 6: DEQUE — LINKED LIST
 * ========================================== */

struct DequeNode {
    int data;
    struct DequeNode* prev;
    struct DequeNode* next;
};

struct DequeLinked {
    struct DequeNode* front;
    struct DequeNode* rear;
    int count;
};

void initDequeLinked(struct DequeLinked* d) {
    d->front = NULL;
    d->rear = NULL;
    d->count = 0;
}

int isEmptyDequeLinked(struct DequeLinked* d) {
    return d->front == NULL;
}

void insertFrontLinked(struct DequeLinked* d, int value) {
    struct DequeNode* newNode = (struct DequeNode*)malloc(sizeof(struct DequeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = d->front;

    if (isEmptyDequeLinked(d)) {
        d->front = newNode;
        d->rear = newNode;
    } else {
        d->front->prev = newNode;
        d->front = newNode;
    }
    d->count++;
    printf("Inserted %d at front.\n", value);
}

void insertRearLinked(struct DequeLinked* d, int value) {
    struct DequeNode* newNode = (struct DequeNode*)malloc(sizeof(struct DequeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = d->rear;

    if (isEmptyDequeLinked(d)) {
        d->front = newNode;
        d->rear = newNode;
    } else {
        d->rear->next = newNode;
        d->rear = newNode;
    }
    d->count++;
    printf("Inserted %d at rear.\n", value);
}

int deleteFrontLinked(struct DequeLinked* d) {
    if (isEmptyDequeLinked(d)) {
        printf("Deque (Linked List) Underflow!\n");
        return -1;
    }
    struct DequeNode* temp = d->front;
    int value = temp->data;
    d->front = d->front->next;

    if (d->front == NULL) {
        d->rear = NULL;
    } else {
        d->front->prev = NULL;
    }

    free(temp);
    d->count--;
    return value;
}

int deleteRearLinked(struct DequeLinked* d) {
    if (isEmptyDequeLinked(d)) {
        printf("Deque (Linked List) Underflow!\n");
        return -1;
    }
    struct DequeNode* temp = d->rear;
    int value = temp->data;
    d->rear = d->rear->prev;

    if (d->rear == NULL) {
        d->front = NULL;
    } else {
        d->rear->next = NULL;
    }

    free(temp);
    d->count--;
    return value;
}

int peekFrontDequeLinked(struct DequeLinked* d) {
    if (isEmptyDequeLinked(d)) {
        printf("Deque (Linked List) is empty!\n");
        return -1;
    }
    return d->front->data;
}

int peekRearDequeLinked(struct DequeLinked* d) {
    if (isEmptyDequeLinked(d)) {
        printf("Deque (Linked List) is empty!\n");
        return -1;
    }
    return d->rear->data;
}

void displayDequeLinked(struct DequeLinked* d) {
    if (isEmptyDequeLinked(d)) {
        printf("Deque (Linked List) is empty!\n");
        return;
    }
    printf("Deque (Linked List) (front -> rear): ");
    struct DequeNode* temp = d->front;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) printf(" | ");
        temp = temp->next;
    }
    printf("\n");
}

void freeDequeLinked(struct DequeLinked* d) {
    while (d->front != NULL) {
        struct DequeNode* temp = d->front;
        d->front = d->front->next;
        free(temp);
    }
    d->rear = NULL;
    d->count = 0;
}


/* ====================================
 *  PART 7: PRIORITY QUEUE — ARRAY
 * ==================================== */

/*
 * MIN Priority Queue:
 * Smaller value => Higher priority.
 */
struct PriorityQueueArray {
    int arr[MAX_SIZE];
    int size;
};

void initPriorityArray(struct PriorityQueueArray* pq) {
    pq->size = 0;
}

int isEmptyPriorityArray(struct PriorityQueueArray* pq) {
    return pq->size == 0;
}

int isFullPriorityArray(struct PriorityQueueArray* pq) {
    return pq->size == MAX_SIZE;
}

void enqueuePriorityArray(struct PriorityQueueArray* pq, int value) {
    if (isFullPriorityArray(pq)) {
        printf("Priority Queue (Array) Overflow!\n");
        return;
    }
    pq->arr[pq->size] = value;
    pq->size++;
    printf("Enqueued %d with priority %d (lower = higher priority).\n", value, value);
}

int dequeuePriorityArray(struct PriorityQueueArray* pq) {
    if (isEmptyPriorityArray(pq)) {
        printf("Priority Queue (Array) Underflow!\n");
        return -1;
    }

    int minIdx = 0;
    for (int i = 1; i < pq->size; i++) {
        if (pq->arr[i] < pq->arr[minIdx]) {
            minIdx = i;
        }
    }

    int value = pq->arr[minIdx];
    for (int i = minIdx; i < pq->size - 1; i++) {
        pq->arr[i] = pq->arr[i + 1];
    }
    pq->size--;
    return value;
}

int peekPriorityArray(struct PriorityQueueArray* pq) {
    if (isEmptyPriorityArray(pq)) {
        printf("Priority Queue (Array) is empty!\n");
        return -1;
    }

    int minIdx = 0;
    for (int i = 1; i < pq->size; i++) {
        if (pq->arr[i] < pq->arr[minIdx]) {
            minIdx = i;
        }
    }
    return pq->arr[minIdx];
}

void displayPriorityArray(struct PriorityQueueArray* pq) {
    if (isEmptyPriorityArray(pq)) {
        printf("Priority Queue (Array) is empty!\n");
        return;
    }
    printf("Priority Queue (Array): ");
    for (int i = 0; i < pq->size; i++) {
        printf("%d", pq->arr[i]);
        if (i < pq->size - 1) printf(" | ");
    }
    printf("\n");
}


/* ==========================================
 *  PART 8: PRIORITY QUEUE — LINKED LIST
 * ========================================== */

/*
 * We keep list sorted in ascending order.
 * Front always has highest priority (minimum value).
 */
struct PriorityNode {
    int data;
    struct PriorityNode* next;
};

struct PriorityQueueLinked {
    struct PriorityNode* front;
    int size;
};

void initPriorityLinked(struct PriorityQueueLinked* pq) {
    pq->front = NULL;
    pq->size = 0;
}

int isEmptyPriorityLinked(struct PriorityQueueLinked* pq) {
    return pq->front == NULL;
}

void enqueuePriorityLinked(struct PriorityQueueLinked* pq, int value) {
    struct PriorityNode* newNode = (struct PriorityNode*)malloc(sizeof(struct PriorityNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (isEmptyPriorityLinked(pq) || value < pq->front->data) {
        newNode->next = pq->front;
        pq->front = newNode;
    } else {
        struct PriorityNode* temp = pq->front;
        while (temp->next != NULL && temp->next->data <= value) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    pq->size++;
    printf("Enqueued %d with priority %d (lower = higher priority).\n", value, value);
}

int dequeuePriorityLinked(struct PriorityQueueLinked* pq) {
    if (isEmptyPriorityLinked(pq)) {
        printf("Priority Queue (Linked List) Underflow!\n");
        return -1;
    }
    struct PriorityNode* temp = pq->front;
    int value = temp->data;
    pq->front = pq->front->next;
    free(temp);
    pq->size--;
    return value;
}

int peekPriorityLinked(struct PriorityQueueLinked* pq) {
    if (isEmptyPriorityLinked(pq)) {
        printf("Priority Queue (Linked List) is empty!\n");
        return -1;
    }
    return pq->front->data;
}

void displayPriorityLinked(struct PriorityQueueLinked* pq) {
    if (isEmptyPriorityLinked(pq)) {
        printf("Priority Queue (Linked List) is empty!\n");
        return;
    }
    printf("Priority Queue (Linked List): ");
    struct PriorityNode* temp = pq->front;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) printf(" | ");
        temp = temp->next;
    }
    printf("\n");
}

void freePriorityLinked(struct PriorityQueueLinked* pq) {
    while (pq->front != NULL) {
        struct PriorityNode* temp = pq->front;
        pq->front = pq->front->next;
        free(temp);
    }
    pq->size = 0;
}


/* ============================================
 *  PART 9: MAIN MENU
 * ============================================ */

void displayMenu() {
    printf("\n============================================================");
    printf("\n               QUEUE OPERATIONS MENU");
    printf("\n============================================================");

    printf("\n --- LINEAR (SIMPLE) QUEUE - ARRAY ---");
    printf("\n1.  Enqueue (Linear Array)");
    printf("\n2.  Dequeue (Linear Array)");
    printf("\n3.  Peek (Linear Array)");
    printf("\n4.  Display (Linear Array)");

    printf("\n --- LINEAR (SIMPLE) QUEUE - LINKED LIST ---");
    printf("\n5.  Enqueue (Linear Linked)");
    printf("\n6.  Dequeue (Linear Linked)");
    printf("\n7.  Peek (Linear Linked)");
    printf("\n8.  Display (Linear Linked)");

    printf("\n --- CIRCULAR QUEUE - ARRAY ---");
    printf("\n9.  Enqueue (Circular Array)");
    printf("\n10. Dequeue (Circular Array)");
    printf("\n11. Peek (Circular Array)");
    printf("\n12. Display (Circular Array)");

    printf("\n --- CIRCULAR QUEUE - LINKED LIST ---");
    printf("\n13. Enqueue (Circular Linked)");
    printf("\n14. Dequeue (Circular Linked)");
    printf("\n15. Peek (Circular Linked)");
    printf("\n16. Display (Circular Linked)");

    printf("\n --- DEQUE - ARRAY ---");
    printf("\n17. Insert Front (Deque Array)");
    printf("\n18. Insert Rear (Deque Array)");
    printf("\n19. Delete Front (Deque Array)");
    printf("\n20. Delete Rear (Deque Array)");
    printf("\n21. Peek Front (Deque Array)");
    printf("\n22. Peek Rear (Deque Array)");
    printf("\n23. Display (Deque Array)");

    printf("\n --- DEQUE - LINKED LIST ---");
    printf("\n24. Insert Front (Deque Linked)");
    printf("\n25. Insert Rear (Deque Linked)");
    printf("\n26. Delete Front (Deque Linked)");
    printf("\n27. Delete Rear (Deque Linked)");
    printf("\n28. Peek Front (Deque Linked)");
    printf("\n29. Peek Rear (Deque Linked)");
    printf("\n30. Display (Deque Linked)");

    printf("\n --- PRIORITY QUEUE - ARRAY ---");
    printf("\n31. Enqueue (Priority Array)");
    printf("\n32. Dequeue (Priority Array)");
    printf("\n33. Peek (Priority Array)");
    printf("\n34. Display (Priority Array)");

    printf("\n --- PRIORITY QUEUE - LINKED LIST ---");
    printf("\n35. Enqueue (Priority Linked)");
    printf("\n36. Dequeue (Priority Linked)");
    printf("\n37. Peek (Priority Linked)");
    printf("\n38. Display (Priority Linked)");

    printf("\n39. Exit");
    printf("\n============================================================");
    printf("\nEnter your choice: ");
}

int main() {
    int choice, value;

    struct LinearQueueArray linearArray;
    struct LinearQueueLinked linearLinked;
    struct CircularQueueArray circularArray;
    struct CircularQueueLinked circularLinked;
    struct DequeArray dequeArray;
    struct DequeLinked dequeLinked;
    struct PriorityQueueArray priorityArray;
    struct PriorityQueueLinked priorityLinked;

    initLinearArray(&linearArray);
    initLinearLinked(&linearLinked);
    initCircularArray(&circularArray);
    initCircularLinked(&circularLinked);
    initDequeArray(&dequeArray);
    initDequeLinked(&dequeLinked);
    initPriorityArray(&priorityArray);
    initPriorityLinked(&priorityLinked);

    printf("\n*** QUEUE OPERATIONS PROGRAM ***\n");

    while (1) {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Exiting program.\n");
            break;
        }

        switch (choice) {
            /* Linear (Array) */
            case 1:
                printf("\nEnter value to enqueue: ");
                scanf("%d", &value);
                enqueueLinearArray(&linearArray, value);
                break;
            case 2:
                value = dequeueLinearArray(&linearArray);
                if (value != -1) printf("Dequeued: %d\n", value);
                break;
            case 3:
                value = peekLinearArray(&linearArray);
                if (value != -1) printf("Front element: %d\n", value);
                break;
            case 4:
                displayLinearArray(&linearArray);
                break;

            /* Linear (Linked List) */
            case 5:
                printf("\nEnter value to enqueue: ");
                scanf("%d", &value);
                enqueueLinearLinked(&linearLinked, value);
                break;
            case 6:
                value = dequeueLinearLinked(&linearLinked);
                if (value != -1) printf("Dequeued: %d\n", value);
                break;
            case 7:
                value = peekLinearLinked(&linearLinked);
                if (value != -1) printf("Front element: %d\n", value);
                break;
            case 8:
                displayLinearLinked(&linearLinked);
                break;

            /* Circular (Array) */
            case 9:
                printf("\nEnter value to enqueue: ");
                scanf("%d", &value);
                enqueueCircularArray(&circularArray, value);
                break;
            case 10:
                value = dequeueCircularArray(&circularArray);
                if (value != -1) printf("Dequeued: %d\n", value);
                break;
            case 11:
                value = peekCircularArray(&circularArray);
                if (value != -1) printf("Front element: %d\n", value);
                break;
            case 12:
                displayCircularArray(&circularArray);
                break;

            /* Circular (Linked List) */
            case 13:
                printf("\nEnter value to enqueue: ");
                scanf("%d", &value);
                enqueueCircularLinked(&circularLinked, value);
                break;
            case 14:
                value = dequeueCircularLinked(&circularLinked);
                if (value != -1) printf("Dequeued: %d\n", value);
                break;
            case 15:
                value = peekCircularLinked(&circularLinked);
                if (value != -1) printf("Front element: %d\n", value);
                break;
            case 16:
                displayCircularLinked(&circularLinked);
                break;

            /* Deque (Array) */
            case 17:
                printf("\nEnter value to insert at front: ");
                scanf("%d", &value);
                insertFrontArray(&dequeArray, value);
                break;
            case 18:
                printf("\nEnter value to insert at rear: ");
                scanf("%d", &value);
                insertRearArray(&dequeArray, value);
                break;
            case 19:
                value = deleteFrontArray(&dequeArray);
                if (value != -1) printf("Deleted from front: %d\n", value);
                break;
            case 20:
                value = deleteRearArray(&dequeArray);
                if (value != -1) printf("Deleted from rear: %d\n", value);
                break;
            case 21:
                value = peekFrontDequeArray(&dequeArray);
                if (value != -1) printf("Front element: %d\n", value);
                break;
            case 22:
                value = peekRearDequeArray(&dequeArray);
                if (value != -1) printf("Rear element: %d\n", value);
                break;
            case 23:
                displayDequeArray(&dequeArray);
                break;

            /* Deque (Linked List) */
            case 24:
                printf("\nEnter value to insert at front: ");
                scanf("%d", &value);
                insertFrontLinked(&dequeLinked, value);
                break;
            case 25:
                printf("\nEnter value to insert at rear: ");
                scanf("%d", &value);
                insertRearLinked(&dequeLinked, value);
                break;
            case 26:
                value = deleteFrontLinked(&dequeLinked);
                if (value != -1) printf("Deleted from front: %d\n", value);
                break;
            case 27:
                value = deleteRearLinked(&dequeLinked);
                if (value != -1) printf("Deleted from rear: %d\n", value);
                break;
            case 28:
                value = peekFrontDequeLinked(&dequeLinked);
                if (value != -1) printf("Front element: %d\n", value);
                break;
            case 29:
                value = peekRearDequeLinked(&dequeLinked);
                if (value != -1) printf("Rear element: %d\n", value);
                break;
            case 30:
                displayDequeLinked(&dequeLinked);
                break;

            /* Priority (Array) */
            case 31:
                printf("\nEnter value (lower value = higher priority): ");
                scanf("%d", &value);
                enqueuePriorityArray(&priorityArray, value);
                break;
            case 32:
                value = dequeuePriorityArray(&priorityArray);
                if (value != -1) printf("Dequeued highest priority: %d\n", value);
                break;
            case 33:
                value = peekPriorityArray(&priorityArray);
                if (value != -1) printf("Highest priority element: %d\n", value);
                break;
            case 34:
                displayPriorityArray(&priorityArray);
                break;

            /* Priority (Linked List) */
            case 35:
                printf("\nEnter value (lower value = higher priority): ");
                scanf("%d", &value);
                enqueuePriorityLinked(&priorityLinked, value);
                break;
            case 36:
                value = dequeuePriorityLinked(&priorityLinked);
                if (value != -1) printf("Dequeued highest priority: %d\n", value);
                break;
            case 37:
                value = peekPriorityLinked(&priorityLinked);
                if (value != -1) printf("Highest priority element: %d\n", value);
                break;
            case 38:
                displayPriorityLinked(&priorityLinked);
                break;

            case 39:
                printf("\nExiting program. Goodbye!\n");
                freeLinearLinked(&linearLinked);
                freeCircularLinked(&circularLinked);
                freeDequeLinked(&dequeLinked);
                freePriorityLinked(&priorityLinked);
                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    freeLinearLinked(&linearLinked);
    freeCircularLinked(&circularLinked);
    freeDequeLinked(&dequeLinked);
    freePriorityLinked(&priorityLinked);
    return 0;
}
