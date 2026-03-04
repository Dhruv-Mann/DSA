# Doubly Linked List — Complete Guide

## What is a Doubly Linked List?

A **Doubly Linked List (DLL)** is a linear data structure where each node contains three fields:
- **Data** — the value stored
- **Next** — pointer to the next node
- **Prev** — pointer to the previous node

```
NULL <-> [10] <-> [20] <-> [30] <-> [40] <-> NULL
          ^                                   
         head                                 
```

The first node's `prev` is `NULL` and the last node's `next` is `NULL`.

---

## Why Use a Doubly Linked List?

### 1. Bidirectional Traversal
The most obvious advantage. You can traverse forward (head → tail) AND backward (tail → head). A singly linked list only goes one way.

**Real use case:** A music player's playlist — you need "next track" AND "previous track."

### 2. O(1) Deletion When You Have the Node Pointer
This is the MAIN algorithmic reason to use a DLL over SLL.

In a **singly linked list**, if someone gives you a pointer to a node and says "delete this," you need to traverse from the head to find the node before it (to update its `next`). That's O(n).

In a **doubly linked list**, you already have `node->prev`, so you can unlink the node in O(1):
```c
node->prev->next = node->next;
node->next->prev = node->prev;
free(node);
```

**Real use case:** LRU (Least Recently Used) Cache — the #1 interview question that uses DLL. You need to remove arbitrary nodes in O(1) and move them to the front.

### 3. Easier Implementation of Certain Operations
- **Delete the last node**: SLL needs O(n) to find the second-to-last node. DLL can find it via `lastNode->prev`.
- **Insert before a given node**: SLL needs to traverse from head to find the predecessor. DLL just uses `node->prev`.
- **Reverse traversal**: SLL requires reversing the list first or using a stack. DLL does it natively.

---

## Comparison: SLL vs DLL vs Array

| Operation | Array | Singly LL | Doubly LL |
|-----------|-------|-----------|-----------|
| Access by index | **O(1)** | O(n) | O(n) |
| Insert at beginning | O(n) | **O(1)** | **O(1)** |
| Insert at end | O(1)* | O(n)† | O(n)† |
| Insert at position | O(n) | O(n) | O(n) |
| Delete at beginning | O(n) | **O(1)** | **O(1)** |
| Delete at end | O(1)* | O(n) | O(n)† |
| Delete given node ptr | O(n) | O(n) | **O(1)** ✨ |
| Search | O(n) | O(n) | O(n) |
| Backward traversal | O(n) | O(n)‡ | **O(n)** native |
| Memory per element | Lowest | Medium | **Highest** |

\* Array: O(1) amortized with dynamic arrays  
† Can be O(1) with a tail pointer  
‡ SLL needs reversal or a stack for backward traversal  

### Key Takeaway
Choose DLL over SLL when you need:
- Frequent deletion of arbitrary nodes (given a pointer)
- Bidirectional traversal
- Browser-like forward/back navigation

Choose SLL when:
- Memory is tight (no extra `prev` pointer per node)
- You only traverse forward
- Simpler implementation is preferred

---

## Where DLL is Actually Used (Real World)

### 1. LRU Cache (THE classic DLL application)
- Uses a **DLL + HashMap** together
- HashMap gives O(1) lookup to find a node
- DLL gives O(1) removal and insertion (move to front)
- When cache is full, remove the tail node (least recently used)
- **LeetCode 146: LRU Cache** — one of the most common interview questions

### 2. Browser History
- Back button = move to `prev`
- Forward button = move to `next`
- Each page visited is a node

### 3. Undo/Redo Systems
- Each state is a node
- Undo = go to `prev`
- Redo = go to `next`

### 4. Operating System Process Scheduling
- Ready queue, blocked queue often use doubly linked lists
- Processes need to be removed from arbitrary positions quickly

### 5. Text Editors
- Each line of text can be a node
- Cursor moving up/down = `prev`/`next`
- Inserting/deleting lines is O(1) when you have the node

### 6. Memory Allocators (e.g., malloc internals)
- Free blocks are maintained in a DLL
- When a block is freed, it merges with adjacent free blocks
- `prev` pointer makes finding adjacent blocks O(1)

---

## Implementing DLL Using Other Data Structures

### DLL Using Arrays (Array Simulation)
You can simulate a DLL using three arrays:
```
data[]:  [10, 20, 30, 40]
next[]:  [ 1,  2,  3, -1]    (-1 means NULL)
prev[]:  [-1,  0,  1,  2]
```
- `data[i]` = value at node i
- `next[i]` = index of the next node
- `prev[i]` = index of the previous node

This is called a **static linked list** and is used when:
- Dynamic memory allocation (malloc) is not available (e.g., embedded systems)
- You want cache-friendly memory layout (arrays are contiguous in memory)

### XOR Linked List (Memory-Efficient DLL)
A clever trick that stores both `prev` and `next` in a SINGLE pointer field:
```
node->npx = prev XOR next
```
- To go forward: `next = prev XOR node->npx`
- To go backward: `prev = next XOR node->npx`

This halves the extra pointer overhead (one pointer instead of two), but makes the code much harder to read/debug. Rarely used in practice.

---

## Time Complexity Summary

| Operation | Time | Space |
|-----------|------|-------|
| Create (n nodes) | O(n) | O(n) |
| Traverse (forward/backward) | O(n) | O(1) |
| Insert at beginning | O(1) | O(1) |
| Insert at end | O(n)* | O(1) |
| Insert at position | O(n) | O(1) |
| Delete at beginning | O(1) | O(1) |
| Delete at end | O(n)* | O(1) |
| Delete at position | O(n) | O(1) |
| Delete given node pointer | **O(1)** | O(1) |
| Search | O(n) | O(1) |
| Reverse | O(n) | O(1) |
| Sort (bubble) | O(n²) | O(1) |

\* O(1) with a tail pointer

---

## Space Overhead
- SLL: `sizeof(data) + sizeof(pointer)` per node
- DLL: `sizeof(data) + 2 × sizeof(pointer)` per node
- On a 64-bit system with `int` data: SLL node = 16 bytes, DLL node = 24 bytes (50% more memory)

---

## Common Mistakes
1. **Forgetting to update `prev`** — Every insert/delete must update pointers in BOTH directions.
2. **Not handling edge cases** — Empty list, single-node list, head deletion, tail deletion.
3. **Memory leaks** — Always `free()` deleted nodes.
4. **Dangling pointers** — After deleting a node, don't access it.

---

## Build and Run

```bash
gcc operations.c -o operations
./operations
```

## File
- `operations.c` — Menu-driven implementation of all doubly linked list operations with detailed comments.
- `README.md` — This conceptual guide.
