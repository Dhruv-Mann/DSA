# Circular Linked List — Complete Guide

## What is a Circular Linked List?

A **Circular Linked List (CLL)** is a variation of a singly linked list where the last node's `next` pointer points back to the **first node** instead of `NULL`.

```
Regular SLL:   head -> [10] -> [20] -> [30] -> NULL

Circular SLL:  head -> [10] -> [20] -> [30] --+
                        ^                      |
                        +----------------------+
```

There is **no NULL** in the list. Following `next` pointers forever will loop through the list repeatedly.

---

## Why Use a Circular Linked List?

### 1. Round-Robin Scheduling
The #1 use case. When you have a set of items and need to cycle through them repeatedly:
- **CPU scheduling**: Each process gets a time slice, then control moves to the next. After the last process, it wraps to the first.
- **Multiplayer games**: Player 1 → Player 2 → Player 3 → back to Player 1.
- **Token ring networks**: A token passes from one node to the next in a circle.

With a regular SLL, you'd need special logic to "wrap around" from the last node to the first. With a CLL, it happens naturally — just follow `next`.

### 2. Looping Through Data
Any situation where data is naturally circular:
- **Music playlist on repeat**: After the last song, play the first song.
- **Slideshow**: After the last slide, show the first.
- **Circular buffer / Ring buffer**: A fixed-size buffer where new data overwrites the oldest data.

### 3. Josephus Problem
A famous algorithm problem: N people stand in a circle. Starting from a person, count k people and eliminate the k-th person. Repeat until one person remains.  
A CLL is the natural data structure for this — eliminate a node, keep counting in the circle.

---

## Comparison: SLL vs Circular SLL vs DLL

| Feature | SLL | Circular SLL | DLL |
|---------|-----|-------------|-----|
| Last node points to | NULL | HEAD | NULL |
| Traversal direction | Forward only | Forward (loop) | Both |
| Reach head from last node | O(n) | **O(1)** | O(n)* |
| Insert at beginning | O(1) | O(n)† | O(1) |
| Insert at end | O(n) | O(n)† | O(n)* |
| Delete at beginning | O(1) | O(n)† | O(1) |
| Extra memory per node | 1 pointer | 1 pointer | 2 pointers |
| Infinite loop risk | None | **Yes** | None |
| Natural for cycling | No | **Yes** | No |

\* O(1) with a tail pointer  
† O(n) because you need the last node to update its `next`. Can be O(1) if you maintain a tail pointer.

### Key Takeaway
- Use **CLL** when your problem is inherently circular (cycling, round-robin, ring structures).
- Use **SLL** for simple forward-only traversal where you need a clear "end."
- Use **DLL** when you need backward traversal or O(1) arbitrary deletion.

---

## The Tail Pointer Optimization

In many CLL implementations, instead of maintaining a `head` pointer, you maintain a **tail** pointer (pointing to the last node). This gives you:
- **Head access**: `tail->next` is the head. O(1).
- **Insert at beginning**: O(1) — create node, point it to `tail->next`, update `tail->next`.
- **Insert at end**: O(1) — create node, point it to `tail->next`, update `tail->next`, then `tail = newNode`.
- **Delete at beginning**: O(1) — `tail->next = tail->next->next`.

This is a common optimization in production code.

```
Tail pointer version:

     tail
      |
      v
[10] -> [20] -> [30] --+
 ^                      |
 +----------------------+

tail->next = head = [10]
```

---

## Where CLL is Actually Used (Real World)

### 1. Operating System — Round-Robin CPU Scheduling
- Each process gets a fixed time quantum.
- After one process's time expires, move to the next.
- After the last process, cycle back to the first.
- CLL makes this seamless — no boundary check needed.

### 2. Circular Buffers / Ring Buffers
- Used in I/O operations, audio streaming, network packet buffers.
- Fixed-size buffer where the producer writes and consumer reads.
- When the buffer is full, new data overwrites the oldest.
- The "wrapping around" behavior maps perfectly to a CLL.

### 3. Token Ring Networks
- In older network protocols (Token Ring / IEEE 802.5), a token is passed around a ring of computers.
- Only the computer holding the token can transmit.
- This is literally a circular linked list of network nodes.

### 4. Multiplayer Board Games
- Players take turns in a cycle.
- After the last player, control returns to the first.
- Represented naturally as a CLL of player states.

### 5. Fibonacci Heap (Advanced)
- Used internally in Fibonacci heaps (which power the fastest known Dijkstra's algorithm).
- The root list of a Fibonacci heap is a circular doubly linked list.

---

## Implementing CLL Using Other Data Structures

### Using an Array (Circular Array)
```
arr[] = [10, 20, 30, 40]
size = 4
current_index = 0

Next element: arr[(current_index + 1) % size]
```
The modulo operator (`%`) provides the "wrapping" behavior.  
This is how **circular queues** are implemented — a circular linked list concept backed by an array.

### Converting SLL to CLL
If you have a regular SLL, just find the last node and set `lastNode->next = head`. Done.
```c
struct Node* temp = head;
while (temp->next != NULL) temp = temp->next;
temp->next = head;  // Now it's circular
```

---

## Common Pitfall: Infinite Loops

The #1 bug with circular linked lists is the **infinite loop**:
```c
// WRONG — this loops forever in a CLL!
while (temp != NULL) {
    temp = temp->next;
}

// CORRECT — stop when we return to head
do {
    temp = temp->next;
} while (temp != head);
```

Always use `do-while` for traversal or check against the starting node.

---

## Time Complexity Summary

| Operation | Time | Notes |
|-----------|------|-------|
| Create (n nodes) | O(n) | |
| Traverse | O(n) | |
| Insert at beginning | O(n) | O(1) with tail pointer |
| Insert at end | O(n) | O(1) with tail pointer |
| Insert at position | O(n) | |
| Delete at beginning | O(n) | O(1) with tail pointer |
| Delete at end | O(n) | |
| Delete at position | O(n) | |
| Search | O(n) | |
| Sort (bubble) | O(n²) | |

---

## Build and Run

```bash
gcc operations.c -o operations
./operations
```

## Files
- `operations.c` — Menu-driven implementation of all circular linked list operations with detailed comments.
- `README.md` — This conceptual guide.
