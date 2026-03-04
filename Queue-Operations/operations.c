#include <stdio.h>
#include <stdlib.h>

/*
 * ============================================================================
 *  QUEUE — COMPLETE OPERATIONS
 *  (Simple Queue, Circular Queue, Linked-List Queue, Deque, Priority Queue)
 * ============================================================================
 *
 *  A Queue is an abstract data type (ADT) that follows the FIFO principle:
 *  First In, First Out.
 *
 *  Think of a line at a ticket counter:
 *    - New people join at the REAR (enqueue).
 *    - The person at the FRONT gets served first (dequeue).
 *
 *  The TWO fundamental operations:
 *    - enqueue(x) : add element x at the rear
 *    - dequeue()  : remove and return the element at the front
 *
 *  Additional operations:
 *    - peek() / front() : return the front element without removing
 *    - isEmpty()        : check if the queue has no elements
 *    - isFull()         : check if the queue is at capacity
 *    - display()        : show all elements
 *
 *  Why it matters:
 *    Queues are essential for:
 *    - BFS (Breadth-First Search) in trees and graphs
 *    - CPU/Disk/Printer scheduling
 *    - Handling requests (web servers, message queues)
 *    - Level-order tree traversal
 *    - Sliding window problems
 *
 * ============================================================================
 */

/* ====================================
 *  PART 1: SIMPLE ARRAY-BASED QUEUE
 * ==================================== */

/*
 * The simplest queue uses an array with two indices: front and rear.
 *
 *   front: index of the first element (the one to dequeue next)
 *   rear:  index of the last element (the one most recently enqueued)
 *
 * Problem with simple queue:
 *   After several enqueue/dequeue operations, front moves forward,
 *   leaving "holes" at the beginning of the array that can never be reused.
 *   The queue reports "full" even though there's unused space.
 *
 *   Example: MAX=5, after enqueue 5 elements then dequeue 3:
 *     arr: [_, _, _, 40, 50]    front=3, rear=4
 *     Indices 0-2 are WASTED. Can't enqueue even though 3 slots are empty.
 *
 * Solution: Use a CIRCULAR QUEUE (Part 2).
 *
 * We include this simple version to show WHY circular queues exist.
 */

#define MAX_SIZE 100

struct SimpleQueue {
    int arr[MAX_SIZE];
    int front;      // index of the front element
    int rear;       // index of the rear element
};

/*
 * Initialise the simple queue.
 * front = -1, rear = -1 means the queue is empty.
 */
void initSimpleQueue(struct SimpleQueue* q) {
    q->front = -1;
    q->rear = -1;
}

int isEmptySimple(struct SimpleQueue* q) {
    return q->front == -1;
}

/*
 * isFull for a simple queue: rear has reached the last index.
 * Note the flaw — even if front > 0 (meaning we've dequeued from the front),
 * those slots are wasted.
 */
int isFullSimple(struct SimpleQueue* q) {
    return q->rear == MAX_SIZE - 1;
}

/*
 * Enqueue: Add an element at the rear.
 *
 * Steps:
 *   1. Check if full.
 *   2. If queue was empty (front == -1), set front = 0.
 *   3. Increment rear.
 *   4. Store the value at arr[rear].
 *
 * Time: O(1).
 */
void enqueueSimple(struct SimpleQueue* q, int value) {
    if (isFullSimple(q)) {
        printf("Queue Overflow! Cannot enqueue %d.\n", value);
        return;
    }
    if (q->front == -1) {
        q->front = 0;      // first element — set front to 0
    }
    q->rear++;
    q->arr[q->rear] = value;
    printf("Enqueued %d.\n", value);
}

/*
 * Dequeue: Remove and return the front element.
 *
 * Steps:
 *   1. Check if empty.
 *   2. Read the value at arr[front].
 *   3. If front == rear (last element), reset both to -1 (queue becomes empty).
 *   4. Otherwise, increment front.
 *
 * The problem: index 'front' moves FORWARD, and the space behind it is wasted.
 *
 * Time: O(1).
 */
int dequeueSimple(struct SimpleQueue* q) {
    if (isEmptySimple(q)) {
        printf("Queue Underflow! Cannot dequeue.\n");
        return -1;
    }
    int value = q->arr[q->front];
    if (q->front == q->rear) {
        // Last element — queue becomes empty
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;     // move front forward (wastes the old slot)
    }
    return value;
}

int peekSimple(struct SimpleQueue* q) {
    if (isEmptySimple(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->arr[q->front];
}

void displaySimple(struct SimpleQueue* q) {
    if (isEmptySimple(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue (front → rear): ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d", q->arr[i]);
        if (i < q->rear) printf(" | ");
    }
    printf("\n");
}


/* ===================================
 *  PART 2: CIRCULAR QUEUE (Array)
 * =================================== */

/*
 * A Circular Queue solves the "wasted space" problem of a simple queue.
 *
 * Instead of treating the array as linear, we treat it as CIRCULAR:
 * when rear reaches the end of the array, it wraps around to index 0.
 *
 * This is achieved using the MODULO operator:
 *   next index = (current index + 1) % MAX_SIZE
 *
 * Visually (MAX=5):
 *   Linear view:  [0] [1] [2] [3] [4]
 *   Circular view: after index 4, we wrap to index 0.
 *
 * Example:
 *   After enqueue(10,20,30,40,50): front=0, rear=4, FULL
 *   Dequeue 3 times: front=3, rear=4
 *   Enqueue(60): rear = (4+1)%5 = 0 → arr[0] = 60
 *   Enqueue(70): rear = (0+1)%5 = 1 → arr[1] = 70
 *   Now: arr = [60, 70, _, 40, 50], front=3, rear=1 — space is REUSED!
 *
 * Full condition:  (rear + 1) % MAX == front
 *   This sacrifices ONE slot (can store MAX-1 elements) to distinguish
 *   full from empty. Alternative: use a count variable.
 *
 * Empty condition: front == -1  (or count == 0 if using count)
 */

struct CircularQueue {
    int arr[MAX_SIZE];
    int front;
    int rear;
    int count;      // track number of elements (avoids the 1-slot sacrifice)
};

void initCircularQueue(struct CircularQueue* q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isEmptyCircular(struct CircularQueue* q) {
    return q->count == 0;
}

int isFullCircular(struct CircularQueue* q) {
    return q->count == MAX_SIZE;
}

/*
 * Circular Enqueue: Add element at rear, wrapping around if needed.
 *
 * Steps:
 *   1. Check if full.
 *   2. rear = (rear + 1) % MAX_SIZE   → wrap around
 *   3. Store value at arr[rear].
 *   4. Increment count.
 *
 * The modulo operation is the KEY to circularity.
 * When rear is at MAX_SIZE-1: (MAX_SIZE-1 + 1) % MAX_SIZE = 0 → wraps to front!
 */
void enqueueCircular(struct CircularQueue* q, int value) {
    if (isFullCircular(q)) {
        printf("Circular Queue Overflow! Cannot enqueue %d.\n", value);
        return;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;    // wrap around
    q->arr[q->rear] = value;
    q->count++;
    printf("Enqueued %d.\n", value);
}

/*
 * Circular Dequeue: Remove and return front element, wrapping around if needed.
 *
 * Steps:
 *   1. Check if empty.
 *   2. Read value at arr[front].
 *   3. front = (front + 1) % MAX_SIZE   → wrap around
 *   4. Decrement count.
 *
 * Unlike the simple queue, the dequeued slot WILL be reused when rear wraps.
 */
int dequeueCircular(struct CircularQueue* q) {
    if (isEmptyCircular(q)) {
        printf("Circular Queue Underflow! Cannot dequeue.\n");
        return -1;
    }
    int value = q->arr[q->front];
    q->front = (q->front + 1) % MAX_SIZE;  // wrap around
    q->count--;
    return value;
}

int peekCircular(struct CircularQueue* q) {
    if (isEmptyCircular(q)) {
        printf("Circular queue is empty!\n");
        return -1;
    }
    return q->arr[q->front];
}

void displayCircular(struct CircularQueue* q) {
    if (isEmptyCircular(q)) {
        printf("Circular queue is empty!\n");
        return;
    }
    printf("Circular Queue (front → rear): ");
    int idx = q->front;
    for (int i = 0; i < q->count; i++) {
        printf("%d", q->arr[idx]);
        if (i < q->count - 1) printf(" | ");
        idx = (idx + 1) % MAX_SIZE;    // wrap around during display too
    }
    printf("\n");
    printf("Size: %d / %d\n", q->count, MAX_SIZE);
}


/* =======================================
 *  PART 3: LINKED-LIST-BASED QUEUE
 * ======================================= */

/*
 * Linked-list queue uses two pointers: front and rear.
 *   - front: points to the first node (dequeue happens here)
 *   - rear:  points to the last node  (enqueue happens here)
 *
 * Why two pointers?
 *   - Enqueue at rear: rear->next = newNode; rear = newNode;  → O(1)
 *   - Dequeue at front: temp = front; front = front->next; free(temp); → O(1)
 *
 * If we only had one pointer:
 *   - With only front: enqueue would be O(n) (traverse to end)
 *   - With only rear: dequeue would be O(n) (traverse to second-to-last)
 *
 * Advantages:
 *   - Dynamic size — no overflow (unless system memory runs out)
 *   - No wasted space
 *
 * Disadvantages:
 *   - Extra memory for pointers
 *   - Not cache-friendly
 */

struct QueueNode {
    int data;
    struct QueueNode* next;
};

struct LinkedQueue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

void initLinkedQueue(struct LinkedQueue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmptyLinked(struct LinkedQueue* q) {
    return q->front == NULL;
}

/*
 * Linked Enqueue: Add a new node at the rear.
 *
 * Steps:
 *   1. Create a new node.
 *   2. If queue is empty: front = rear = newNode.
 *   3. Otherwise: rear->next = newNode; rear = newNode.
 *
 * Time: O(1).
 */
void enqueueLinked(struct LinkedQueue* q, int value) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (isEmptyLinked(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;    // old rear points to new node
        q->rear = newNode;          // rear moves to new node
    }
    printf("Enqueued %d.\n", value);
}

/*
 * Linked Dequeue: Remove the front node.
 *
 * Steps:
 *   1. Check if empty.
 *   2. Save front in temp.
 *   3. front = front->next.
 *   4. If front becomes NULL, also set rear = NULL (queue is empty).
 *   5. Free temp.
 *
 * Time: O(1).
 */
int dequeueLinked(struct LinkedQueue* q) {
    if (isEmptyLinked(q)) {
        printf("Queue Underflow!\n");
        return -1;
    }
    struct QueueNode* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;     // queue is now empty
    }

    free(temp);
    return value;
}

int peekLinked(struct LinkedQueue* q) {
    if (isEmptyLinked(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->front->data;
}

void displayLinked(struct LinkedQueue* q) {
    if (isEmptyLinked(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue (front → rear): ");
    struct QueueNode* temp = q->front;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) printf(" | ");
        temp = temp->next;
    }
    printf("\n");
}


/* ====================================
 *  PART 4: DEQUE (Double-Ended Queue)
 * ==================================== */

/*
 * A Deque (Double-Ended Queue, pronounced "deck") allows insertion
 * and deletion at BOTH ends — front AND rear.
 *
 * Operations:
 *   - insertFront(x)  : add at front
 *   - insertRear(x)   : add at rear
 *   - deleteFront()   : remove from front
 *   - deleteRear()    : remove from rear
 *
 * A deque can act as:
 *   - A STACK    (push/pop from the same end)
 *   - A QUEUE    (enqueue at rear, dequeue from front)
 *   - BOTH at the same time
 *
 * Implementation: Circular array (same wrapping technique as circular queue).
 *
 * Real uses:
 *   - Sliding window maximum/minimum (LeetCode #239)
 *   - Work-stealing schedulers (threads steal from the back of another's deque)
 *   - Palindrome checking
 *   - Browser history with tab groups
 */

struct Deque {
    int arr[MAX_SIZE];
    int front;
    int rear;
    int count;
};

void initDeque(struct Deque* d) {
    d->front = 0;
    d->rear = -1;
    d->count = 0;
}

int isEmptyDeque(struct Deque* d) {
    return d->count == 0;
}

int isFullDeque(struct Deque* d) {
    return d->count == MAX_SIZE;
}

/*
 * Insert at front: move front BACKWARD (with wrap) and store.
 *
 * front = (front - 1 + MAX_SIZE) % MAX_SIZE
 *
 * Why "+ MAX_SIZE"?
 *   If front is 0, (0 - 1) = -1, and -1 % MAX_SIZE is implementation-defined in C.
 *   Adding MAX_SIZE first ensures the result is always positive:
 *   (0 - 1 + 100) % 100 = 99 → wraps to the end of the array.
 */
void insertFront(struct Deque* d, int value) {
    if (isFullDeque(d)) {
        printf("Deque Overflow!\n");
        return;
    }
    d->front = (d->front - 1 + MAX_SIZE) % MAX_SIZE;   // move front backward
    d->arr[d->front] = value;
    d->count++;
    printf("Inserted %d at front.\n", value);
}

/*
 * Insert at rear: move rear FORWARD (with wrap) and store.
 * Same as circular queue enqueue.
 */
void insertRear(struct Deque* d, int value) {
    if (isFullDeque(d)) {
        printf("Deque Overflow!\n");
        return;
    }
    d->rear = (d->rear + 1) % MAX_SIZE;
    d->arr[d->rear] = value;
    d->count++;
    printf("Inserted %d at rear.\n", value);
}

/*
 * Delete from front: read arr[front], move front FORWARD (with wrap).
 * Same as circular queue dequeue.
 */
int deleteFront(struct Deque* d) {
    if (isEmptyDeque(d)) {
        printf("Deque Underflow!\n");
        return -1;
    }
    int value = d->arr[d->front];
    d->front = (d->front + 1) % MAX_SIZE;
    d->count--;
    return value;
}

/*
 * Delete from rear: read arr[rear], move rear BACKWARD (with wrap).
 * This is what makes deque special — you can "pop" from the back too.
 */
int deleteRear(struct Deque* d) {
    if (isEmptyDeque(d)) {
        printf("Deque Underflow!\n");
        return -1;
    }
    int value = d->arr[d->rear];
    d->rear = (d->rear - 1 + MAX_SIZE) % MAX_SIZE;
    d->count--;
    return value;
}

int peekFrontDeque(struct Deque* d) {
    if (isEmptyDeque(d)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return d->arr[d->front];
}

int peekRearDeque(struct Deque* d) {
    if (isEmptyDeque(d)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return d->arr[d->rear];
}

void displayDeque(struct Deque* d) {
    if (isEmptyDeque(d)) {
        printf("Deque is empty!\n");
        return;
    }
    printf("Deque (front → rear): ");
    int idx = d->front;
    for (int i = 0; i < d->count; i++) {
        printf("%d", d->arr[idx]);
        if (i < d->count - 1) printf(" | ");
        idx = (idx + 1) % MAX_SIZE;
    }
    printf("\n");
}


/* =======================================
 *  PART 5: PRIORITY QUEUE (Array-Based)
 * ======================================= */

/*
 * A Priority Queue is a queue where each element has a PRIORITY.
 * Elements with HIGHER priority are dequeued FIRST, regardless of
 * their insertion order. (Not strictly FIFO.)
 *
 * This is a BASIC array-based implementation. In practice, priority
 * queues are implemented using HEAPS (binary heap) for O(log n)
 * insert/delete. This array version is O(n) — included here for
 * understanding the concept.
 *
 * Real uses:
 *   - Dijkstra's shortest path algorithm (needs efficient priority queue)
 *   - Prim's minimum spanning tree
 *   - CPU scheduling (higher-priority processes run first)
 *   - Huffman coding (data compression)
 *   - A* pathfinding
 *   - Event-driven simulation
 *
 * Two types:
 *   - MIN priority queue: smallest value = highest priority (dequeued first)
 *   - MAX priority queue: largest value = highest priority
 *
 * We implement MIN priority queue here (common in graph algorithms).
 */

struct PriorityQueue {
    int arr[MAX_SIZE];
    int size;
};

void initPriorityQueue(struct PriorityQueue* pq) {
    pq->size = 0;
}

int isEmptyPQ(struct PriorityQueue* pq) {
    return pq->size == 0;
}

int isFullPQ(struct PriorityQueue* pq) {
    return pq->size == MAX_SIZE;
}

/*
 * Enqueue: Just add at the end. O(1).
 * (We don't sort on insert — we find the min on dequeue.)
 */
void enqueuePQ(struct PriorityQueue* pq, int value) {
    if (isFullPQ(pq)) {
        printf("Priority Queue Overflow!\n");
        return;
    }
    pq->arr[pq->size] = value;
    pq->size++;
    printf("Enqueued %d with priority %d (lower = higher priority).\n", value, value);
}

/*
 * Dequeue: Find the element with the MINIMUM value (highest priority),
 * remove it, and shift remaining elements.
 *
 * THIS is the O(n) part. With a heap, this would be O(log n).
 *
 * Steps:
 *   1. Find the index of the minimum element.
 *   2. Save its value.
 *   3. Shift all elements after it left by one (to fill the gap).
 *   4. Decrement size.
 */
int dequeuePQ(struct PriorityQueue* pq) {
    if (isEmptyPQ(pq)) {
        printf("Priority Queue Underflow!\n");
        return -1;
    }

    // Find the minimum element
    int minIdx = 0;
    for (int i = 1; i < pq->size; i++) {
        if (pq->arr[i] < pq->arr[minIdx]) {
            minIdx = i;
        }
    }

    int value = pq->arr[minIdx];

    // Shift elements to fill the gap
    for (int i = minIdx; i < pq->size - 1; i++) {
        pq->arr[i] = pq->arr[i + 1];
    }
    pq->size--;

    return value;
}

int peekPQ(struct PriorityQueue* pq) {
    if (isEmptyPQ(pq)) {
        printf("Priority Queue is empty!\n");
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

void displayPQ(struct PriorityQueue* pq) {
    if (isEmptyPQ(pq)) {
        printf("Priority Queue is empty!\n");
        return;
    }
    printf("Priority Queue: ");
    for (int i = 0; i < pq->size; i++) {
        printf("%d", pq->arr[i]);
        if (i < pq->size - 1) printf(" | ");
    }
    printf("\n");
}


/* ============================================
 *  PART 6: MAIN MENU
 * ============================================ */

void displayMenu() {
    printf("\n=============================================");
    printf("\n           QUEUE OPERATIONS MENU");
    printf("\n=============================================");
    printf("\n --- Simple Queue ---");
    printf("\n1.  Enqueue (Simple)");
    printf("\n2.  Dequeue (Simple)");
    printf("\n3.  Peek (Simple)");
    printf("\n4.  Display (Simple)");
    printf("\n --- Circular Queue ---");
    printf("\n5.  Enqueue (Circular)");
    printf("\n6.  Dequeue (Circular)");
    printf("\n7.  Peek (Circular)");
    printf("\n8.  Display (Circular)");
    printf("\n --- Linked List Queue ---");
    printf("\n9.  Enqueue (Linked List)");
    printf("\n10. Dequeue (Linked List)");
    printf("\n11. Peek (Linked List)");
    printf("\n12. Display (Linked List)");
    printf("\n --- Deque (Double-Ended Queue) ---");
    printf("\n13. Insert at Front (Deque)");
    printf("\n14. Insert at Rear (Deque)");
    printf("\n15. Delete from Front (Deque)");
    printf("\n16. Delete from Rear (Deque)");
    printf("\n17. Display (Deque)");
    printf("\n --- Priority Queue ---");
    printf("\n18. Enqueue (Priority)");
    printf("\n19. Dequeue (Priority)");
    printf("\n20. Peek (Priority)");
    printf("\n21. Display (Priority)");
    printf("\n22. Exit");
    printf("\n=============================================");
    printf("\nEnter your choice: ");
}

int main() {
    int choice, value;

    // Initialise all queue types
    struct SimpleQueue simpleQ;
    initSimpleQueue(&simpleQ);

    struct CircularQueue circularQ;
    initCircularQueue(&circularQ);

    struct LinkedQueue linkedQ;
    initLinkedQueue(&linkedQ);

    struct Deque deque;
    initDeque(&deque);

    struct PriorityQueue priorityQ;
    initPriorityQueue(&priorityQ);

    printf("\n*** QUEUE OPERATIONS PROGRAM ***\n");

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            // Simple Queue
            case 1:
                printf("\nEnter value to enqueue: ");
                scanf("%d", &value);
                enqueueSimple(&simpleQ, value);
                break;
            case 2:
                value = dequeueSimple(&simpleQ);
                if (value != -1) printf("Dequeued: %d\n", value);
                break;
            case 3:
                value = peekSimple(&simpleQ);
                if (value != -1) printf("Front element: %d\n", value);
                break;
            case 4:
                displaySimple(&simpleQ);
                break;

            // Circular Queue
            case 5:
                printf("\nEnter value to enqueue: ");
                scanf("%d", &value);
                enqueueCircular(&circularQ, value);
                break;
            case 6:
                value = dequeueCircular(&circularQ);
                if (value != -1) printf("Dequeued: %d\n", value);
                break;
            case 7:
                value = peekCircular(&circularQ);
                if (value != -1) printf("Front element: %d\n", value);
                break;
            case 8:
                displayCircular(&circularQ);
                break;

            // Linked List Queue
            case 9:
                printf("\nEnter value to enqueue: ");
                scanf("%d", &value);
                enqueueLinked(&linkedQ, value);
                break;
            case 10:
                value = dequeueLinked(&linkedQ);
                if (value != -1) printf("Dequeued: %d\n", value);
                break;
            case 11:
                value = peekLinked(&linkedQ);
                if (value != -1) printf("Front element: %d\n", value);
                break;
            case 12:
                displayLinked(&linkedQ);
                break;

            // Deque
            case 13:
                printf("\nEnter value to insert at front: ");
                scanf("%d", &value);
                insertFront(&deque, value);
                break;
            case 14:
                printf("\nEnter value to insert at rear: ");
                scanf("%d", &value);
                insertRear(&deque, value);
                break;
            case 15:
                value = deleteFront(&deque);
                if (value != -1) printf("Deleted from front: %d\n", value);
                break;
            case 16:
                value = deleteRear(&deque);
                if (value != -1) printf("Deleted from rear: %d\n", value);
                break;
            case 17:
                displayDeque(&deque);
                break;

            // Priority Queue
            case 18:
                printf("\nEnter value (value = priority, lower = higher): ");
                scanf("%d", &value);
                enqueuePQ(&priorityQ, value);
                break;
            case 19:
                value = dequeuePQ(&priorityQ);
                if (value != -1) printf("Dequeued highest priority: %d\n", value);
                break;
            case 20:
                value = peekPQ(&priorityQ);
                if (value != -1) printf("Highest priority element: %d\n", value);
                break;
            case 21:
                displayPQ(&priorityQ);
                break;

            case 22:
                printf("\nExiting program. Goodbye!\n");
                // Free linked queue nodes
                while (linkedQ.front != NULL) {
                    struct QueueNode* temp = linkedQ.front;
                    linkedQ.front = linkedQ.front->next;
                    free(temp);
                }
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
