# Singly Linked List — Complete Guide

## What is a Singly Linked List?

A **Singly Linked List (SLL)** is the most basic linked data structure. Each node contains:
- **Data** — the value stored
- **Next** — a pointer to the next node

```
head → [10] → [20] → [30] → [40] → NULL
```

The last node's `next` is `NULL`, marking the end of the list. The `head` pointer always points to the first node.

Unlike an **array**, linked list nodes are **not stored contiguously in memory** — each node is independently allocated on the heap and connected via pointers.

---

## Why Use a Linked List? (Array vs Linked List)

This is THE fundamental comparison in data structures. Understanding it deeply will help you choose the right structure for every problem.

### The Core Tradeoff: Random Access vs Dynamic Insert/Delete

**Arrays** store elements in contiguous memory:
```
arr: [10][20][30][40][50]    ← all in a row in memory
      0   1   2   3   4     ← indices give O(1) access
```

**Linked Lists** store elements scattered in memory, connected by pointers:
```
head → [10|*] → [20|*] → [30|*] → NULL
        0xA0      0xF4      0x2C        ← scattered addresses
```

| Operation | Array | Singly Linked List |
|-----------|-------|--------------------|
| **Access by index** | **O(1)** — direct calculation | O(n) — must traverse |
| **Insert at beginning** | O(n) — shift all elements | **O(1)** — just update head |
| **Insert at end** | O(1) amortized* | O(n) — must find last node† |
| **Insert at middle** | O(n) — shift elements | O(n) — traverse + O(1) link |
| **Delete at beginning** | O(n) — shift all elements | **O(1)** — just move head |
| **Delete at end** | O(1)* | O(n) — must find second-to-last |
| **Delete at middle** | O(n) — shift elements | O(n) — traverse + O(1) unlink |
| **Search** | O(n) linear, O(log n) binary† | O(n) — always linear |
| **Memory** | Fixed/contiguous, cache-friendly | Dynamic, scattered, not cache-friendly |
| **Size** | Fixed (or amortized resize) | Dynamic (grows/shrinks freely) |

\* With dynamic arrays (like Python lists, Java ArrayList)
† O(1) with a tail pointer
‡ Binary search only works on sorted arrays

### When to Use a Linked List Over an Array
1. **Frequent insertions/deletions at the beginning** — O(1) vs O(n)
2. **Unknown size** — no need to pre-allocate or resize
3. **No random access needed** — you always traverse sequentially
4. **Building other data structures** — stacks, queues, hash table chaining, adjacency lists

### When to Use an Array Over a Linked List
1. **Need random access** — `arr[i]` is O(1), linked list is O(n)
2. **Cache performance matters** — arrays are contiguous, much faster for sequential access
3. **Memory efficiency** — no pointer overhead per element
4. **Binary search** — only works with O(1) index access
5. **Known, fixed size** — arrays are simpler and faster

### The Memory Layout Matters More Than You Think
```
Array:        [10][20][30][40][50]   ← CPU cache loads all at once (cache line)
Linked List:  [10|*]...[20|*]...[30|*]   ← each node may cause a cache miss
```
On modern CPUs, a cache miss can be **100x slower** than a cache hit. This is why arrays often outperform linked lists even when Big-O says they should be the same (e.g., traversal is O(n) for both, but array traversal is much faster in practice).

---

## How a Singly Linked List Works (Mental Model)

### The Head Pointer
`head` is your only entry point. Every operation starts from `head` and follows `next` pointers.

If `head` is `NULL`, the list is empty.

### The Traversal Pattern
Almost every operation uses this pattern:
```c
struct Node* temp = head;
while (temp != NULL) {
    // process temp->data
    temp = temp->next;
}
```
This is O(n) — you visit every node once.

### The "One Behind" Pattern
For deletion and insertion at a position, you need the node **before** the target:
```c
// To insert/delete at position p, stop at position p-1
struct Node* temp = head;
for (int i = 1; i < position - 1; i++) {
    temp = temp->next;
}
// Now temp is the node BEFORE the target
```
This is because you need to update `temp->next` to splice in or remove a node.

### The Three-Pointer Reversal
Reversing a linked list uses three pointers:
```
prev = NULL, current = head, next = NULL

While current != NULL:
    next = current->next     ← save next
    current->next = prev     ← reverse the link
    prev = current           ← advance prev
    current = next           ← advance current

head = prev                  ← prev is the new head
```
This is asked in almost every coding interview. Practice until you can write it from memory.

---

## All Operations

| # | Operation | Time | Description |
|---|-----------|------|-------------|
| 1 | Create List | O(n) | Build a list of n nodes from user input |
| 2 | Traverse/Display | O(n) | Visit every node and print its value |
| 3 | Insert at Beginning | O(1) | New node becomes the head |
| 4 | Insert at End | O(n) | Traverse to last node, append |
| 5 | Insert at Position | O(n) | Walk to position-1, splice in |
| 6 | Delete at Beginning | O(1) | Move head forward, free old head |
| 7 | Delete at End | O(n) | Walk to second-to-last, remove last |
| 8 | Delete at Position | O(n) | Walk to position-1, bypass target |
| 9 | Delete by Value | O(n) | Find first node with value, unlink it |
| 10 | Search | O(n) | Walk until value found or end reached |
| 11 | Count Nodes | O(n) | Traverse and count |
| 12 | Reverse | O(n) | Three-pointer in-place reversal |
| 13 | Sort (Bubble) | O(n²) | Swap data between adjacent nodes |

---

## Where SLL is Actually Used (Real World)

### 1. Hash Table Chaining (Separate Chaining)
When two keys hash to the same index, the collisions are stored in a linked list at that index. This is the most common hash table collision resolution strategy.
```
hash_table[0] → NULL
hash_table[1] → [key1|*] → [key5|*] → NULL    ← collision chain
hash_table[2] → [key2|*] → NULL
```

### 2. Stack Implementation
A stack backed by a SLL uses the head as the top:
- Push = insert at beginning → O(1)
- Pop = delete from beginning → O(1)

### 3. Queue Implementation
A queue backed by a SLL uses head as front and a tail pointer as rear:
- Enqueue = insert at end (via tail pointer) → O(1)
- Dequeue = delete from beginning → O(1)

### 4. Adjacency List (Graph Representation)
Graphs are commonly stored as an array of linked lists:
```
vertex 0 → [1] → [4] → NULL
vertex 1 → [0] → [2] → [3] → NULL
vertex 2 → [1] → NULL
```
Each vertex has a linked list of its neighbors. This is memory-efficient for sparse graphs.

### 5. Polynomial Representation
Each term of a polynomial is a node: `(coefficient, exponent, next)`
```
3x² + 5x + 2 → [3,2|*] → [5,1|*] → [2,0|*] → NULL
```

### 6. Operating System: Free List
OS memory managers maintain a linked list of free memory blocks. When you call `malloc`, it searches this free list for a suitable block.

---

## Implementing SLL Using Other Data Structures

### SLL Using an Array (Static Linked List)
When dynamic memory isn't available (embedded systems), simulate a linked list with arrays:
```
data[]: [10, 20, 30, 40]
next[]: [ 1,  2,  3, -1]    (-1 = NULL)
head = 0
```
`data[head]` = 10, `next[head]` = 1, so `data[1]` = 20, and so on.

This preserves linked list's O(1) insert/delete advantage while using contiguous memory.

---

## Common Linked List Problems (LeetCode)

| Problem | Difficulty | Key Technique |
|---------|-----------|---------------|
| Reverse Linked List (#206) | Easy | Three-pointer reversal |
| Merge Two Sorted Lists (#21) | Easy | Two-pointer merge |
| Linked List Cycle (#141) | Easy | Floyd's slow/fast pointers |
| Remove Nth Node From End (#19) | Medium | Two-pointer gap technique |
| Reorder List (#143) | Medium | Find middle + reverse + merge |
| Add Two Numbers (#2) | Medium | Carry-based addition |
| Copy List with Random Pointer (#138) | Medium | HashMap or interleaving |
| Palindrome Linked List (#234) | Easy | Reverse second half + compare |
| Intersection of Two Lists (#160) | Easy | Length difference technique |
| Sort List (#148) | Medium | Merge sort on linked list |
| LRU Cache (#146) | Medium | DLL + HashMap (SLL won't work here) |
| Reverse Nodes in k-Group (#25) | Hard | Recursive reversal |

### Floyd's Cycle Detection (Tortoise & Hare)
Detect if a linked list has a cycle:
```
slow = head      (moves 1 step)
fast = head      (moves 2 steps)

while fast != NULL and fast->next != NULL:
    slow = slow->next
    fast = fast->next->next
    if slow == fast:
        return "cycle detected"

return "no cycle"
```
If there's a cycle, the fast pointer will "lap" the slow pointer and they'll meet. O(n) time, O(1) space.

### Finding the Middle Node
Same slow/fast technique:
```
slow = head, fast = head
while fast != NULL and fast->next != NULL:
    slow = slow->next
    fast = fast->next->next
return slow    ← this is the middle
```
When fast reaches the end, slow is exactly at the middle. Used in merge sort on linked lists.

---

## Comparison: SLL vs DLL vs CLL vs CDLL

| Feature | SLL | DLL | CLL | CDLL |
|---------|-----|-----|-----|------|
| Pointers per node | 1 | 2 | 1 | 2 |
| Forward traversal | Yes | Yes | Yes (loop) | Yes (loop) |
| Backward traversal | No | Yes | No | Yes (loop) |
| Insert at beginning | O(1) | O(1) | O(n)* | O(1) |
| Delete given node ptr | O(n) | O(1) | O(n) | O(1) |
| Access to tail | O(n) | O(n) | O(n) | O(1) |
| Memory per node | Lowest | Higher | Lowest | Higher |
| Complexity | Simplest | Medium | Medium | Highest |

\* O(1) with tail pointer

**SLL is the simplest and most fundamental.** Master it first, then the others are just variations with extra pointers and circular links.

---

## Time Complexity Summary

| Operation | Time | Space |
|-----------|------|-------|
| Create (n nodes) | O(n) | O(n) |
| Traverse | O(n) | O(1) |
| Insert at beginning | O(1) | O(1) |
| Insert at end | O(n)* | O(1) |
| Insert at position | O(n) | O(1) |
| Delete at beginning | O(1) | O(1) |
| Delete at end | O(n) | O(1) |
| Delete at position | O(n) | O(1) |
| Search | O(n) | O(1) |
| Reverse | O(n) | O(1) |
| Sort (bubble) | O(n²) | O(1) |

\* O(1) with a tail pointer

---

## Common Mistakes
1. **Losing the head** — traversing with `head` directly instead of using a `temp` pointer.
2. **Not handling empty list** — always check `head == NULL` before any operation.
3. **Memory leaks** — every `malloc` must have a corresponding `free` when the node is deleted.
4. **Off-by-one in position** — clearly define whether positions are 0-based or 1-based (this implementation uses 1-based).
5. **Forgetting to update head** — when deleting or inserting at position 1, `head` must change.
6. **Not freeing nodes on exit** — the program should free all nodes before terminating.

---

## Build and Run

```bash
gcc operations.c -o operations
./operations
```

## Files
- `operations.c` — Menu-driven implementation of all singly linked list operations with detailed comments.
- `README.md` — This conceptual guide.
