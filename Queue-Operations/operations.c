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
 *  Think of a supermarket checkout line:
 *    - New customers join at the REAR.
 *    - The customer at the FRONT is served first.
 *
 *  Core operations:
 *    - enqueue(x)   : add element x at the rear
 *    - dequeue()    : remove and return the element at the front
 *    - peek()/front(): view the front element without removing it
 *    - display()    : print all elements from front to rear
 *
 *  Deque (Double-Ended Queue) operations:
 *    - insertFront(x), insertRear(x)  : insert at either end
 *    - deleteFront(), deleteRear()    : remove from either end
 *    - peekFront(), peekRear()        : inspect either end
 *
 *  Priority Queue rule in this program:
 *    - Lower value = Higher priority (MIN priority queue)
 *    - The element with the smallest value is always dequeued first.
 *
 *  Four queue variants demonstrated:
 *    1. Linear Queue  — simple FIFO; wastes space after dequeues (array)
 *    2. Circular Queue — wraps around to reuse freed space (array)
 *    3. Deque          — insertions and deletions at BOTH ends
 *    4. Priority Queue — dequeue in priority order, not arrival order
 *
 * ============================================================================
 */

#define MAX_SIZE 100


/* ============================================
 *  PART 1: LINEAR (SIMPLE) QUEUE — ARRAY
 * ============================================ */

/*
 * Array-based linear queue uses a fixed-size array with two indices:
 *   - 'front' : index of the element to be dequeued next
 *   - 'rear'  : index of the last enqueued element
 *
 * Both start at -1 to indicate an empty queue.
 *
 * Enqueue: increment rear, store value at arr[rear].
 * Dequeue: read arr[front], then increment front.
 *
 * Key limitation:
 *   Once rear reaches MAX_SIZE-1 the queue reports FULL even if elements
 *   were dequeued from the front, because the freed slots at the start of
 *   the array can never be reused. This is fixed by the Circular Queue.
 *
 * Advantages:
 *   - Very simple implementation.
 *   - Cache-friendly (contiguous memory).
 *
 * Disadvantages:
 *   - Fixed size.
 *   - Space wastage after dequeues (the "false full" problem).
 */
struct LinearQueueArray {
    int arr[MAX_SIZE];  // underlying storage
    int front;          // index of the front element (-1 = empty)
    int rear;           // index of the rear element  (-1 = empty)
};

/*
 * Initialises the linear array queue.
 * Both front and rear are set to -1 (sentinel for "empty").
 */
void initLinearArray(struct LinearQueueArray* q) {
    q->front = -1;
    q->rear = -1;
}

/*
 * Checks if the linear array queue is empty.
 * The queue is empty when front is -1 (nothing has been enqueued,
 * or every enqueued element has been dequeued).
 */
int isEmptyLinearArray(struct LinearQueueArray* q) {
    return q->front == -1;
}

/*
 * Checks if the linear array queue is full.
 * Full when rear has reached the last valid index (MAX_SIZE - 1).
 * Note: even if front > 0 (some space freed), we still call it full —
 * this is the classical linear queue limitation.
 */
int isFullLinearArray(struct LinearQueueArray* q) {
    return q->rear == MAX_SIZE - 1;
}

/*
 * Enqueue: Adds a value at the REAR of the linear array queue.
 *
 * Steps:
 *   1. Check for overflow (rear == MAX_SIZE - 1).
 *   2. If the queue was empty (front == -1), set front = 0 so the
 *      queue knows where dequeuing starts.
 *   3. Increment rear and store the value at arr[rear].
 *
 * Why set front = 0 on the first enqueue?
 *   front stays at -1 until there is actually something to dequeue.
 *   The first element goes into arr[0] (rear becomes 0), and front
 *   must also point to 0 so dequeue returns the correct element.
 *
 * Time: O(1). Space: O(1).
 */
void enqueueLinearArray(struct LinearQueueArray* q, int value) {
    if (isFullLinearArray(q)) {
        printf("Linear Queue (Array) Overflow! Cannot enqueue %d.\n", value);
        return;
    }
    if (q->front == -1) {
        q->front = 0;   // first element — activate front
    }
    q->rear++;
    q->arr[q->rear] = value;
    printf("Enqueued %d.\n", value);
}

/*
 * Dequeue: Removes and returns the element at the FRONT.
 *
 * Steps:
 *   1. Check for underflow (queue is empty).
 *   2. Read value at arr[front].
 *   3. If front == rear, this was the last element — reset both to -1
 *      (queue is now empty again).
 *   4. Otherwise, just increment front to move to the next element.
 *
 * Why reset to -1 when the last element is removed?
 *   If we only did front++, front would equal rear+1 but neither would
 *   be -1, so isEmpty() would falsely report non-empty.
 *   Resetting to -1 restores the canonical "empty" sentinel.
 *
 * Time: O(1). Space: O(1).
 */
int dequeueLinearArray(struct LinearQueueArray* q) {
    if (isEmptyLinearArray(q)) {
        printf("Linear Queue (Array) Underflow!\n");
        return -1;
    }
    int value = q->arr[q->front];
    if (q->front == q->rear) {
        // Last element removed — reset queue to empty state
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;     // move front pointer one step toward rear
    }
    return value;
}

/*
 * Peek: Returns the front element WITHOUT removing it.
 * The queue state is completely unchanged after this call.
 */
int peekLinearArray(struct LinearQueueArray* q) {
    if (isEmptyLinearArray(q)) {
        printf("Linear Queue (Array) is empty!\n");
        return -1;
    }
    return q->arr[q->front];
}

/*
 * Display: Prints all elements from front to rear.
 * Iterates from index 'front' to 'rear' inclusive.
 */
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

/*
 * Linked-list-based linear queue uses a singly linked list with two
 * pointers maintained at the struct level:
 *   - 'front' : points to the node that will be dequeued next (head)
 *   - 'rear'  : points to the node most recently enqueued (tail)
 *
 * Enqueue: allocate a new node, attach it after rear, advance rear.
 * Dequeue: save front, advance front to front->next, free saved node.
 *
 * Advantages over array-based:
 *   - No fixed size — grows dynamically.
 *   - No "false full" problem — every dequeue truly frees memory.
 *
 * Disadvantages:
 *   - Extra memory per node for the 'next' pointer.
 *   - malloc/free overhead.
 *   - Not cache-friendly (nodes scattered in heap).
 */
struct LinearNode {
    int data;
    struct LinearNode* next;
};

struct LinearQueueLinked {
    struct LinearNode* front;   // points to the first node (dequeue end)
    struct LinearNode* rear;    // points to the last node  (enqueue end)
};

/*
 * Initialises the linked-list linear queue.
 * Both pointers are NULL — the queue is empty.
 */
void initLinearLinked(struct LinearQueueLinked* q) {
    q->front = NULL;
    q->rear = NULL;
}

/*
 * Checks if the linked-list linear queue is empty.
 * Empty when front is NULL (no nodes exist).
 */
int isEmptyLinearLinked(struct LinearQueueLinked* q) {
    return q->front == NULL;
}

/*
 * Enqueue: Adds a new node at the REAR of the linked-list queue.
 *
 * Steps:
 *   1. Allocate and initialise the new node (next = NULL).
 *   2. If the queue is empty, both front and rear point to the new node.
 *   3. Otherwise, link the current rear's next to the new node,
 *      then advance rear to the new node.
 *
 * Why maintain a rear pointer?
 *   Without it, enqueue would have to traverse the entire list to find
 *   the last node — O(n) per enqueue. With rear, it's O(1).
 *
 * Time: O(1). Space: O(1) per enqueue.
 */
void enqueueLinearLinked(struct LinearQueueLinked* q, int value) {
    struct LinearNode* newNode = (struct LinearNode*)malloc(sizeof(struct LinearNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;   // new node is the last — points to nothing

    if (isEmptyLinearLinked(q)) {
        // First node — both ends point to it
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;    // old rear points forward to new node
        q->rear = newNode;          // rear advances to the new last node
    }
    printf("Enqueued %d.\n", value);
}

/*
 * Dequeue: Removes and returns the element at the FRONT.
 *
 * Steps:
 *   1. Save front in temp.
 *   2. Read temp->data.
 *   3. Advance front to front->next.
 *   4. If the new front is NULL, the queue became empty — also null rear.
 *   5. Free temp.
 *
 * Why null rear when front becomes NULL?
 *   If only front were nulled, rear would still point to the freed node —
 *   a dangling pointer. Nulling rear too keeps the struct consistent.
 *
 * Time: O(1). Space: O(1).
 */
int dequeueLinearLinked(struct LinearQueueLinked* q) {
    if (isEmptyLinearLinked(q)) {
        printf("Linear Queue (Linked List) Underflow!\n");
        return -1;
    }
    struct LinearNode* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;  // move front to the next node

    if (q->front == NULL) {
        q->rear = NULL;         // queue is now empty — sync rear
    }

    free(temp);
    return value;
}

/*
 * Peek: Returns the front element without removing it.
 */
int peekLinearLinked(struct LinearQueueLinked* q) {
    if (isEmptyLinearLinked(q)) {
        printf("Linear Queue (Linked List) is empty!\n");
        return -1;
    }
    return q->front->data;
}

/*
 * Display: Traverses from front to rear, printing each node's data.
 */
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

/*
 * Frees all nodes in the linked-list linear queue to prevent memory leaks.
 * Called during program exit to clean up heap-allocated memory.
 */
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

/*
 * The circular array queue solves the "false full" problem of the linear queue.
 *
 * Key idea: treat the array as a RING by wrapping indices with modulo arithmetic.
 *   rear  = (rear + 1) % MAX_SIZE  on enqueue
 *   front = (front + 1) % MAX_SIZE on dequeue
 *
 * This lets dequeued slots at the front be reused when the rear wraps around.
 *
 * We track 'count' separately to distinguish full from empty:
 *   - count == 0        → empty (front == rear ambiguity resolved)
 *   - count == MAX_SIZE → full
 *
 * Initial state: front = 0, rear = -1, count = 0.
 *   rear starts at -1 so the first enqueue increments it to 0 and stores at arr[0].
 */
struct CircularQueueArray {
    int arr[MAX_SIZE];
    int front;
    int rear;
    int count;  // number of elements currently in the queue
};

/*
 * Initialises the circular array queue.
 */
void initCircularArray(struct CircularQueueArray* q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

/*
 * Checks if the circular array queue is empty (count == 0).
 */
int isEmptyCircularArray(struct CircularQueueArray* q) {
    return q->count == 0;
}

/*
 * Checks if the circular array queue is full (count == MAX_SIZE).
 * Using 'count' avoids the front == rear ambiguity.
 */
int isFullCircularArray(struct CircularQueueArray* q) {
    return q->count == MAX_SIZE;
}

/*
 * Enqueue: Adds a value at the REAR using circular index arithmetic.
 *
 * New rear = (rear + 1) % MAX_SIZE ensures the index wraps from
 * MAX_SIZE-1 back to 0 when the array is not actually full.
 * This is what makes the queue "circular".
 *
 * Time: O(1).
 */
void enqueueCircularArray(struct CircularQueueArray* q, int value) {
    if (isFullCircularArray(q)) {
        printf("Circular Queue (Array) Overflow!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;    // advance rear circularly
    q->arr[q->rear] = value;
    q->count++;
    printf("Enqueued %d.\n", value);
}

/*
 * Dequeue: Removes and returns the element at the FRONT using circular indexing.
 *
 * After removing, front advances circularly:
 *   front = (front + 1) % MAX_SIZE
 * The slot at the old front is now "free" and will be reused on future enqueues.
 *
 * Time: O(1).
 */
int dequeueCircularArray(struct CircularQueueArray* q) {
    if (isEmptyCircularArray(q)) {
        printf("Circular Queue (Array) Underflow!\n");
        return -1;
    }
    int value = q->arr[q->front];
    q->front = (q->front + 1) % MAX_SIZE;  // advance front circularly
    q->count--;
    return value;
}

/*
 * Peek: Returns the front element without removing it.
 */
int peekCircularArray(struct CircularQueueArray* q) {
    if (isEmptyCircularArray(q)) {
        printf("Circular Queue (Array) is empty!\n");
        return -1;
    }
    return q->arr[q->front];
}

/*
 * Display: Prints all 'count' elements starting from 'front', wrapping around.
 * We use 'idx' and advance it circularly: idx = (idx + 1) % MAX_SIZE.
 */
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
        idx = (idx + 1) % MAX_SIZE;    // wrap index around
    }
    printf("\n");
}


/* ==========================================
 *  PART 4: CIRCULAR QUEUE — LINKED LIST
 * ========================================== */

/*
 * Linked-list circular queue: every node's 'next' always points to
 * another node — the list forms an actual ring in memory.
 *
 * Design choice: we keep only a REAR pointer.
 *   - front is always rear->next (the node after the last is the first).
 *   - This allows both enqueue (add after rear) and dequeue (remove
 *     rear->next) in O(1) with a single pointer.
 *
 * When the queue has only one node, it points to itself.
 * When the queue is empty, rear == NULL.
 */
struct CircularNode {
    int data;
    struct CircularNode* next;
};

struct CircularQueueLinked {
    struct CircularNode* rear;  // points to the last enqueued node
    int count;
};

/*
 * Initialises the circular linked queue.
 * rear = NULL means the queue is empty.
 */
void initCircularLinked(struct CircularQueueLinked* q) {
    q->rear = NULL;
    q->count = 0;
}

/*
 * Checks if the circular linked queue is empty.
 * Empty when rear is NULL (the ring has no nodes).
 */
int isEmptyCircularLinked(struct CircularQueueLinked* q) {
    return q->rear == NULL;
}

/*
 * Enqueue: Inserts a new node AFTER rear (at the logical front direction),
 * then advances rear to the new node so it becomes the new last.
 *
 * For a non-empty queue:
 *   newNode->next = rear->next    (new node points to current front)
 *   rear->next    = newNode       (old rear links forward to new node)
 *   rear          = newNode       (new node is now the rear)
 *
 * For an empty queue:
 *   newNode->next = newNode       (self-link — single-node ring)
 *   rear          = newNode
 *
 * Visual before/after (2-element example):
 *   Before: rear -> [B] -> [A] -> [B] (circular)
 *   After:  rear -> [C] -> [A] -> [B] -> [C] (circular)
 *
 * Time: O(1).
 */
void enqueueCircularLinked(struct CircularQueueLinked* q, int value) {
    struct CircularNode* newNode = (struct CircularNode*)malloc(sizeof(struct CircularNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;

    if (isEmptyCircularLinked(q)) {
        newNode->next = newNode;    // self-link: only node in the ring
        q->rear = newNode;
    } else {
        newNode->next = q->rear->next;  // new node points to current front
        q->rear->next = newNode;        // old rear links to new node
        q->rear = newNode;              // new node becomes the rear
    }
    q->count++;
    printf("Enqueued %d.\n", value);
}

/*
 * Dequeue: Removes and returns the FRONT element (rear->next).
 *
 * For a queue with more than one node:
 *   front       = rear->next             (identify the front node)
 *   rear->next  = front->next            (rear skips over front)
 *   free(front)
 *
 * For a single-node queue (front == rear):
 *   rear = NULL                          (queue becomes empty)
 *   free(front)
 *
 * Time: O(1).
 */
int dequeueCircularLinked(struct CircularQueueLinked* q) {
    if (isEmptyCircularLinked(q)) {
        printf("Circular Queue (Linked List) Underflow!\n");
        return -1;
    }

    struct CircularNode* front = q->rear->next; // front is always rear->next
    int value = front->data;

    if (front == q->rear) {
        // Only one node in the ring — removing it empties the queue
        q->rear = NULL;
    } else {
        q->rear->next = front->next;    // rear now points directly to new front
    }

    free(front);
    q->count--;
    return value;
}

/*
 * Peek: Returns the front element (rear->next->data) without removing it.
 */
int peekCircularLinked(struct CircularQueueLinked* q) {
    if (isEmptyCircularLinked(q)) {
        printf("Circular Queue (Linked List) is empty!\n");
        return -1;
    }
    return q->rear->next->data; // front is always rear->next
}

/*
 * Display: Traverses all 'count' nodes starting from rear->next (front),
 * following next pointers around the ring.
 */
void displayCircularLinked(struct CircularQueueLinked* q) {
    if (isEmptyCircularLinked(q)) {
        printf("Circular Queue (Linked List) is empty!\n");
        return;
    }

    printf("Circular Queue (Linked List) (front -> rear): ");
    struct CircularNode* temp = q->rear->next;  // start from front
    for (int i = 0; i < q->count; i++) {
        printf("%d", temp->data);
        if (i < q->count - 1) printf(" | ");
        temp = temp->next;
    }
    printf("\n");
}

/*
 * Frees all nodes in the circular linked queue.
 * Re-uses dequeue to free them one at a time.
 */
void freeCircularLinked(struct CircularQueueLinked* q) {
    while (!isEmptyCircularLinked(q)) {
        dequeueCircularLinked(q);
    }
}


/* ====================================
 *  PART 5: DEQUE — ARRAY
 * ==================================== */

/*
 * Deque (Double-Ended Queue): a generalised queue that allows
 * insertions and deletions at BOTH the front and the rear.
 *
 * This is implemented as a circular array (same modulo trick as Part 3)
 * so that:
 *   - insertFront wraps front backward: front = (front - 1 + MAX_SIZE) % MAX_SIZE
 *   - insertRear  advances rear forward: rear  = (rear  + 1) % MAX_SIZE
 *   - deleteFront advances front:        front = (front + 1) % MAX_SIZE
 *   - deleteRear  wraps rear backward:   rear  = (rear  - 1 + MAX_SIZE) % MAX_SIZE
 *
 * The "+MAX_SIZE" before modulo prevents negative results in C
 * (C's % can produce negative values for negative operands).
 *
 * Initial state: front = 0, rear = MAX_SIZE - 1, count = 0.
 *   rear starts at MAX_SIZE - 1 so the first insertRear increments to 0.
 *   front starts at 0 so the first insertFront decrements to MAX_SIZE - 1.
 */
struct DequeArray {
    int arr[MAX_SIZE];
    int front;
    int rear;
    int count;
};

/*
 * Initialises the deque array.
 */
void initDequeArray(struct DequeArray* d) {
    d->front = 0;
    d->rear = MAX_SIZE - 1;
    d->count = 0;
}

/*
 * Checks if the deque array is empty.
 */
int isEmptyDequeArray(struct DequeArray* d) {
    return d->count == 0;
}

/*
 * Checks if the deque array is full.
 */
int isFullDequeArray(struct DequeArray* d) {
    return d->count == MAX_SIZE;
}

/*
 * Insert at FRONT: decrements front circularly, then stores the value.
 *
 * front = (front - 1 + MAX_SIZE) % MAX_SIZE
 *   The "+MAX_SIZE" handles the wrap-around when front is already 0:
 *   (0 - 1 + MAX_SIZE) % MAX_SIZE = (MAX_SIZE - 1) — wraps to the last index.
 *
 * Time: O(1).
 */
void insertFrontArray(struct DequeArray* d, int value) {
    if (isFullDequeArray(d)) {
        printf("Deque (Array) Overflow!\n");
        return;
    }
    d->front = (d->front - 1 + MAX_SIZE) % MAX_SIZE;   // wrap front backward
    d->arr[d->front] = value;
    d->count++;
    printf("Inserted %d at front.\n", value);
}

/*
 * Insert at REAR: increments rear circularly, then stores the value.
 * Same as a normal circular enqueue.
 *
 * Time: O(1).
 */
void insertRearArray(struct DequeArray* d, int value) {
    if (isFullDequeArray(d)) {
        printf("Deque (Array) Overflow!\n");
        return;
    }
    d->rear = (d->rear + 1) % MAX_SIZE; // advance rear circularly
    d->arr[d->rear] = value;
    d->count++;
    printf("Inserted %d at rear.\n", value);
}

/*
 * Delete from FRONT: reads arr[front], then advances front circularly.
 * Same as a normal circular dequeue.
 *
 * Time: O(1).
 */
int deleteFrontArray(struct DequeArray* d) {
    if (isEmptyDequeArray(d)) {
        printf("Deque (Array) Underflow!\n");
        return -1;
    }
    int value = d->arr[d->front];
    d->front = (d->front + 1) % MAX_SIZE;   // advance front circularly
    d->count--;
    return value;
}

/*
 * Delete from REAR: reads arr[rear], then decrements rear circularly.
 *
 * rear = (rear - 1 + MAX_SIZE) % MAX_SIZE
 *   Symmetric to insertFront — the "+MAX_SIZE" handles the wrap when rear == 0.
 *
 * Time: O(1).
 */
int deleteRearArray(struct DequeArray* d) {
    if (isEmptyDequeArray(d)) {
        printf("Deque (Array) Underflow!\n");
        return -1;
    }
    int value = d->arr[d->rear];
    d->rear = (d->rear - 1 + MAX_SIZE) % MAX_SIZE;  // wrap rear backward
    d->count--;
    return value;
}

/*
 * Peek at FRONT: returns arr[front] without modifying any index.
 */
int peekFrontDequeArray(struct DequeArray* d) {
    if (isEmptyDequeArray(d)) {
        printf("Deque (Array) is empty!\n");
        return -1;
    }
    return d->arr[d->front];
}

/*
 * Peek at REAR: returns arr[rear] without modifying any index.
 */
int peekRearDequeArray(struct DequeArray* d) {
    if (isEmptyDequeArray(d)) {
        printf("Deque (Array) is empty!\n");
        return -1;
    }
    return d->arr[d->rear];
}

/*
 * Display: prints 'count' elements starting from 'front', wrapping circularly.
 */
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

/*
 * Linked-list deque uses a DOUBLY linked list so we can insert and
 * delete at both ends in O(1).
 *
 * Why doubly linked?
 *   Deleting from the REAR of a singly linked list requires traversing
 *   to the second-to-last node — O(n). With a prev pointer, we reach
 *   the predecessor of rear directly — O(1).
 *
 * We maintain both 'front' and 'rear' pointers:
 *   - front: the node at the front end (insertFront / deleteFront side)
 *   - rear : the node at the rear end  (insertRear  / deleteRear  side)
 *
 * Every node has 'prev' and 'next':
 *   - front->prev == NULL (nothing before the first node)
 *   - rear->next  == NULL (nothing after the last node)
 */
struct DequeNode {
    int data;
    struct DequeNode* prev;    // pointer to the previous node
    struct DequeNode* next;    // pointer to the next node
};

struct DequeLinked {
    struct DequeNode* front;   // first node (front end)
    struct DequeNode* rear;    // last node  (rear end)
    int count;
};

/*
 * Initialises the linked deque.
 */
void initDequeLinked(struct DequeLinked* d) {
    d->front = NULL;
    d->rear = NULL;
    d->count = 0;
}

/*
 * Checks if the linked deque is empty.
 */
int isEmptyDequeLinked(struct DequeLinked* d) {
    return d->front == NULL;
}

/*
 * Insert at FRONT: prepends a new node before the current front.
 *
 * Steps:
 *   1. Allocate new node; set prev = NULL, next = current front.
 *   2. If the deque is empty, both front and rear point to the new node.
 *   3. Otherwise, link the old front's prev back to the new node,
 *      then update front to the new node.
 *
 * Time: O(1).
 */
void insertFrontLinked(struct DequeLinked* d, int value) {
    struct DequeNode* newNode = (struct DequeNode*)malloc(sizeof(struct DequeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->prev = NULL;           // new front has no predecessor
    newNode->next = d->front;       // new node points forward to old front

    if (isEmptyDequeLinked(d)) {
        d->front = newNode;
        d->rear = newNode;
    } else {
        d->front->prev = newNode;   // old front points backward to new node
        d->front = newNode;         // update front pointer
    }
    d->count++;
    printf("Inserted %d at front.\n", value);
}

/*
 * Insert at REAR: appends a new node after the current rear.
 *
 * Steps:
 *   1. Allocate new node; set next = NULL, prev = current rear.
 *   2. If the deque is empty, both front and rear point to the new node.
 *   3. Otherwise, link the old rear's next forward to the new node,
 *      then update rear to the new node.
 *
 * Time: O(1).
 */
void insertRearLinked(struct DequeLinked* d, int value) {
    struct DequeNode* newNode = (struct DequeNode*)malloc(sizeof(struct DequeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;           // new rear has no successor
    newNode->prev = d->rear;        // new node points backward to old rear

    if (isEmptyDequeLinked(d)) {
        d->front = newNode;
        d->rear = newNode;
    } else {
        d->rear->next = newNode;    // old rear points forward to new node
        d->rear = newNode;          // update rear pointer
    }
    d->count++;
    printf("Inserted %d at rear.\n", value);
}

/*
 * Delete from FRONT: removes the front node.
 *
 * Steps:
 *   1. Save front in temp, read its data.
 *   2. Advance front to front->next.
 *   3. If the new front is NULL, the deque is empty — also null rear.
 *   4. Otherwise, clear the new front's prev (no predecessor).
 *   5. Free temp.
 *
 * Time: O(1).
 */
int deleteFrontLinked(struct DequeLinked* d) {
    if (isEmptyDequeLinked(d)) {
        printf("Deque (Linked List) Underflow!\n");
        return -1;
    }
    struct DequeNode* temp = d->front;
    int value = temp->data;
    d->front = d->front->next;      // advance front past the removed node

    if (d->front == NULL) {
        d->rear = NULL;             // deque became empty — sync rear
    } else {
        d->front->prev = NULL;      // new front has no predecessor
    }

    free(temp);
    d->count--;
    return value;
}

/*
 * Delete from REAR: removes the rear node.
 *
 * Steps:
 *   1. Save rear in temp, read its data.
 *   2. Move rear to rear->prev (only possible because of the prev pointer).
 *   3. If the new rear is NULL, the deque is empty — also null front.
 *   4. Otherwise, clear the new rear's next (no successor).
 *   5. Free temp.
 *
 * This is O(1) ONLY because we have a doubly linked list.
 * In a singly linked list this would be O(n).
 */
int deleteRearLinked(struct DequeLinked* d) {
    if (isEmptyDequeLinked(d)) {
        printf("Deque (Linked List) Underflow!\n");
        return -1;
    }
    struct DequeNode* temp = d->rear;
    int value = temp->data;
    d->rear = d->rear->prev;        // move rear backward using prev pointer

    if (d->rear == NULL) {
        d->front = NULL;            // deque became empty — sync front
    } else {
        d->rear->next = NULL;       // new rear has no successor
    }

    free(temp);
    d->count--;
    return value;
}

/*
 * Peek at FRONT: returns front->data without modifying the deque.
 */
int peekFrontDequeLinked(struct DequeLinked* d) {
    if (isEmptyDequeLinked(d)) {
        printf("Deque (Linked List) is empty!\n");
        return -1;
    }
    return d->front->data;
}

/*
 * Peek at REAR: returns rear->data without modifying the deque.
 */
int peekRearDequeLinked(struct DequeLinked* d) {
    if (isEmptyDequeLinked(d)) {
        printf("Deque (Linked List) is empty!\n");
        return -1;
    }
    return d->rear->data;
}

/*
 * Display: traverses from front to rear, printing each node's data.
 */
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

/*
 * Frees all nodes in the linked deque to prevent memory leaks.
 */
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
 * MIN Priority Queue — Array implementation:
 *   Smaller value => Higher priority.
 *   The element with the smallest value is always dequeued first.
 *
 * Storage: an unsorted array.
 *
 * Enqueue: O(1) — just append to the end of the array.
 * Dequeue: O(n) — must scan the entire array to find the minimum,
 *          then shift elements left to close the gap.
 * Peek:    O(n) — same linear scan to find the minimum.
 *
 * Trade-off:
 *   Fast insertion but slow removal. Suitable when insertions are
 *   frequent and removals are rare. A heap-based priority queue
 *   achieves O(log n) for both, but is more complex to implement.
 */

/*
 * MIN Priority Queue:
 * Smaller value => Higher priority.
 */
struct PriorityQueueArray {
    int arr[MAX_SIZE];  // unsorted storage of elements
    int size;           // current number of elements
};

/*
 * Initialises the priority queue array.
 * size = 0 means no elements present.
 */
void initPriorityArray(struct PriorityQueueArray* pq) {
    pq->size = 0;
}

/*
 * Checks if the priority queue array is empty.
 */
int isEmptyPriorityArray(struct PriorityQueueArray* pq) {
    return pq->size == 0;
}

/*
 * Checks if the priority queue array is full.
 */
int isFullPriorityArray(struct PriorityQueueArray* pq) {
    return pq->size == MAX_SIZE;
}

/*
 * Enqueue: Appends the value at the end of the unsorted array.
 *
 * No sorting is done on insertion — the minimum is found lazily
 * at dequeue/peek time.
 *
 * Time: O(1).
 */
void enqueuePriorityArray(struct PriorityQueueArray* pq, int value) {
    if (isFullPriorityArray(pq)) {
        printf("Priority Queue (Array) Overflow!\n");
        return;
    }
    pq->arr[pq->size] = value;  // append at the end
    pq->size++;
    printf("Enqueued %d with priority %d (lower = higher priority).\n", value, value);
}

/*
 * Dequeue: Finds and removes the element with the MINIMUM value.
 *
 * Steps:
 *   1. Linear scan to find minIdx (the index of the smallest element).
 *   2. Save the minimum value.
 *   3. Shift all elements after minIdx one position to the left to
 *      close the gap (maintain a contiguous array).
 *   4. Decrement size.
 *
 * Time: O(n) — one linear scan + up to O(n) shifts.
 */
int dequeuePriorityArray(struct PriorityQueueArray* pq) {
    if (isEmptyPriorityArray(pq)) {
        printf("Priority Queue (Array) Underflow!\n");
        return -1;
    }

    // Find the index of the minimum element (highest priority)
    int minIdx = 0;
    for (int i = 1; i < pq->size; i++) {
        if (pq->arr[i] < pq->arr[minIdx]) {
            minIdx = i;
        }
    }

    int value = pq->arr[minIdx];
    // Shift elements left to fill the gap left by the removed element
    for (int i = minIdx; i < pq->size - 1; i++) {
        pq->arr[i] = pq->arr[i + 1];
    }
    pq->size--;
    return value;
}

/*
 * Peek: Returns the minimum value without removing it.
 * Same linear scan as dequeue but without modifying the array.
 *
 * Time: O(n).
 */
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

/*
 * Display: prints all elements in their current unsorted array order.
 * Note: this does NOT show them in priority order — just storage order.
 */
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
 * MIN Priority Queue — Linked List implementation:
 *   The linked list is kept SORTED IN ASCENDING ORDER at all times.
 *   The front (head) always holds the element with the lowest value
 *   (highest priority).
 *
 * Enqueue: O(n) — must find the correct sorted position by traversal.
 * Dequeue: O(1) — the highest-priority element is always at the front.
 * Peek:    O(1) — just read front->data.
 *
 * Trade-off:
 *   Slower insertion but O(1) removal. Suitable when removals are
 *   frequent. Contrast with the array version where insertion is O(1)
 *   but removal is O(n).
 *
 * We keep list sorted in ascending order.
 * Front always has highest priority (minimum value).
 */
struct PriorityNode {
    int data;
    struct PriorityNode* next;
};

struct PriorityQueueLinked {
    struct PriorityNode* front; // head of sorted list (highest priority)
    int size;
};

/*
 * Initialises the priority queue linked list.
 */
void initPriorityLinked(struct PriorityQueueLinked* pq) {
    pq->front = NULL;
    pq->size = 0;
}

/*
 * Checks if the priority queue linked list is empty.
 */
int isEmptyPriorityLinked(struct PriorityQueueLinked* pq) {
    return pq->front == NULL;
}

/*
 * Enqueue: Inserts a new node in the correct sorted position.
 *
 * Two cases:
 *   a) Insert at HEAD — if the queue is empty OR if the new value is
 *      smaller than the current front (new element has highest priority).
 *   b) Insert in MIDDLE/END — walk the list until we find the first
 *      node whose next value is GREATER than 'value', then splice in.
 *
 * The while-loop condition:
 *   temp->next != NULL && temp->next->data <= value
 *   Stops at the node just before the first node that is LARGER than value,
 *   preserving ascending sorted order.
 *
 * Time: O(n) — may need to traverse the entire list.
 */
void enqueuePriorityLinked(struct PriorityQueueLinked* pq, int value) {
    struct PriorityNode* newNode = (struct PriorityNode*)malloc(sizeof(struct PriorityNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (isEmptyPriorityLinked(pq) || value < pq->front->data) {
        // New node has the highest priority — goes to the front
        newNode->next = pq->front;
        pq->front = newNode;
    } else {
        // Find the correct sorted position
        struct PriorityNode* temp = pq->front;
        while (temp->next != NULL && temp->next->data <= value) {
            temp = temp->next;
        }
        // Splice newNode between temp and temp->next
        newNode->next = temp->next;
        temp->next = newNode;
    }

    pq->size++;
    printf("Enqueued %d with priority %d (lower = higher priority).\n", value, value);
}

/*
 * Dequeue: Removes and returns the front node (smallest value = highest priority).
 *
 * Because the list is always sorted, the highest-priority element is
 * always at the head. Removal is simply "delete at head" — O(1).
 *
 * Time: O(1).
 */
int dequeuePriorityLinked(struct PriorityQueueLinked* pq) {
    if (isEmptyPriorityLinked(pq)) {
        printf("Priority Queue (Linked List) Underflow!\n");
        return -1;
    }
    struct PriorityNode* temp = pq->front;
    int value = temp->data;
    pq->front = pq->front->next;    // advance head past the removed node
    free(temp);
    pq->size--;
    return value;
}

/*
 * Peek: Returns front->data (highest priority element) without removing it.
 * O(1) because the list is sorted and the front is always the minimum.
 */
int peekPriorityLinked(struct PriorityQueueLinked* pq) {
    if (isEmptyPriorityLinked(pq)) {
        printf("Priority Queue (Linked List) is empty!\n");
        return -1;
    }
    return pq->front->data;
}

/*
 * Display: traverses from front to the last node in sorted ascending order.
 * Since the list is maintained sorted, this shows elements from highest
 * to lowest priority (smallest to largest value).
 */
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

/*
 * Frees all nodes in the priority queue linked list.
 */
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

    // Declare all eight queue instances (one per variant)
    struct LinearQueueArray linearArray;
    struct LinearQueueLinked linearLinked;
    struct CircularQueueArray circularArray;
    struct CircularQueueLinked circularLinked;
    struct DequeArray dequeArray;
    struct DequeLinked dequeLinked;
    struct PriorityQueueArray priorityArray;
    struct PriorityQueueLinked priorityLinked;

    // Initialise all queues before use
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
                // Free all heap-allocated linked structures before exiting
                freeLinearLinked(&linearLinked);
                freeCircularLinked(&circularLinked);
                freeDequeLinked(&dequeLinked);
                freePriorityLinked(&priorityLinked);
                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    // Cleanup in case the loop exits via the scanf failure branch
    freeLinearLinked(&linearLinked);
    freeCircularLinked(&circularLinked);
    freeDequeLinked(&dequeLinked);
    freePriorityLinked(&priorityLinked);
    return 0;
}
