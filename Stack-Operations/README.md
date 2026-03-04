# Stack — Complete Guide

## What is a Stack?

A **Stack** is an abstract data type (ADT) that follows the **LIFO** principle: **Last In, First Out**.

The last element added is the first one removed — like a stack of plates.

```
    | 30 |  ← TOP (push here, pop from here)
    | 20 |
    | 10 |
    +----+
    BOTTOM
```

### Core Operations
| Operation | Description | Time |
|-----------|-------------|------|
| `push(x)` | Add element x to the top | O(1) |
| `pop()` | Remove and return the top element | O(1) |
| `peek()` / `top()` | Return top element without removing | O(1) |
| `isEmpty()` | Check if stack has no elements | O(1) |
| `isFull()` | Check if stack is at capacity (array only) | O(1) |

ALL stack operations are **O(1)**. This is what makes stacks so efficient.

---

## Why Use a Stack? (The Real Importance)

Stacks aren't just a data structure to learn — they are **fundamental to how computers work**.

### 1. Function Call Stack (How Your Code Actually Runs)
When you call a function, the computer:
1. **Pushes** the current function's state (local variables, return address) onto the **call stack**.
2. Executes the new function.
3. When it returns, **pops** the saved state and resumes.

This is why **recursion** works — each recursive call pushes a frame, and returns pop frames:
```
factorial(3)  →  push frame for factorial(3)
  factorial(2)  →  push frame for factorial(2)
    factorial(1)  →  push frame for factorial(1)
    returns 1     →  pop frame, back to factorial(2)
  returns 2       →  pop frame, back to factorial(3)
returns 6         →  pop frame, done
```

**Stack overflow** = too many frames pushed (usually infinite recursion).

### 2. DFS (Depth-First Search)
DFS uses a stack (explicitly or via recursion's call stack):
```
Push start node
While stack not empty:
    Pop a node
    Process it
    Push all unvisited neighbors
```
This is THE algorithm for tree/graph traversal. You WILL need this for non-linear DS.

### 3. Expression Evaluation
Compilers use stacks to:
- Convert **infix** (`A + B * C`) to **postfix** (`A B C * +`)
- Evaluate postfix expressions
- Parse programming language syntax

### 4. Balanced Parentheses
```
({[]})  → Balanced ✓
({[}])  → Unbalanced ✗
```
For each opener, push. For each closer, pop and check if it matches. After processing, stack should be empty.

### 5. Undo/Redo
- Every action → push onto undo stack.
- Undo → pop from undo stack, push onto redo stack.
- Redo → pop from redo stack, push onto undo stack.

### 6. Browser Back/Forward
- Visit new page → push onto back stack, clear forward stack.
- Back button → pop from back stack, push onto forward stack.
- Forward button → pop from forward stack, push onto back stack.

---

## Two Implementations: Array vs Linked List

### Array-Based Stack
```
arr[]:  [10, 20, 30, _, _, _, ...]
top = 2    (index of the topmost element)
```

**Push**: `arr[++top] = value`  
**Pop**: `return arr[top--]`

| Aspect | Detail |
|--------|--------|
| Size | Fixed (must declare MAX upfront) |
| Push/Pop | O(1) |
| Overflow | Possible (when top == MAX-1) |
| Memory | No per-element overhead, cache-friendly |
| Simplicity | Very simple |

### Linked-List-Based Stack
```
top → [30] → [20] → [10] → NULL
```

The **head** of the linked list IS the **top** of the stack.

**Push** = insert at beginning: `newNode->next = top; top = newNode;`  
**Pop** = delete from beginning: `temp = top; top = top->next; free(temp);`

| Aspect | Detail |
|--------|--------|
| Size | Dynamic (grows/shrinks as needed) |
| Push/Pop | O(1) |
| Overflow | Only when system memory runs out |
| Memory | Extra pointer per element, not cache-friendly |
| Simplicity | Slightly more complex (malloc/free) |

### Which to Use?
| Situation | Recommendation |
|-----------|---------------|
| Know the max size | Array-based |
| Unknown/variable size | Linked-list-based |
| Performance critical | Array-based (better cache locality) |
| Memory constrained | Array-based (no pointer overhead) |
| Frequent resize needed | Linked-list-based |
| Exam/interview default | Array-based (simpler to write) |

---

## Implementing a Stack Using Other Data Structures

### Stack Using Queue(s)
A common interview question. Since a queue is FIFO and a stack is LIFO, you need **two queues** (or one queue with self-rotation):

**Method (one queue, costly push):**
```
push(x):
    enqueue x
    Rotate (n-1) times: dequeue from front, enqueue to back
    // Now x is at the front (ready to be "popped" first)

pop():
    return dequeue()
```

**Push is O(n), Pop is O(1).**

### Stack Using Two Queues (costly pop)
```
push(x): enqueue to Q1

pop():
    Move all elements except last from Q1 to Q2
    Dequeue the last element from Q1 (this is the "top")
    Swap Q1 and Q2
```

### Stack Using Dynamic Array (like Python list / Java ArrayList)
Most real-world stacks are implemented this way:
- Python's `list.append()` and `list.pop()` = push and pop
- Java's `ArrayDeque` is preferred over the `Stack` class

---

## Stack vs Queue vs Deque

| Feature | Stack | Queue | Deque |
|---------|-------|-------|-------|
| Principle | LIFO | FIFO | Both |
| Insert | Top only | Rear only | Both ends |
| Remove | Top only | Front only | Both ends |
| Used for | DFS, undo, parsing | BFS, scheduling | Sliding window, both |
| Can simulate | — | Stack (with effort) | Stack AND Queue |

A **deque** (double-ended queue) can act as BOTH a stack and a queue, making it the most flexible.

---

## Common Stack Problems (LeetCode)

| Problem | Difficulty | Key Idea |
|---------|-----------|----------|
| Valid Parentheses (#20) | Easy | Push openers, pop for closers |
| Min Stack (#155) | Medium | Two stacks: main + min tracker |
| Evaluate Reverse Polish Notation (#150) | Medium | Postfix evaluation |
| Daily Temperatures (#739) | Medium | Monotonic stack |
| Largest Rectangle in Histogram (#84) | Hard | Monotonic stack |
| Trapping Rain Water (#42) | Hard | Stack or two-pointer |
| Next Greater Element (#496, #503) | Medium | Monotonic stack |
| Decode String (#394) | Medium | Stack of strings/counts |
| Asteroid Collision (#735) | Medium | Stack simulation |
| Basic Calculator (#224, #227) | Hard | Stack + parsing |

### Monotonic Stack (IMPORTANT PATTERN)
A stack where elements are always in sorted order (increasing or decreasing). Used to find the "next greater/smaller element" efficiently.

```
Problem: For each element, find the next greater element.
Input:  [2, 1, 2, 4, 3]
Output: [4, 2, 4, -1, -1]

Algorithm:
    Traverse RIGHT to LEFT.
    For each element:
        Pop all stack elements ≤ current (they can't be anyone's answer)
        If stack is not empty, top = next greater element
        If stack is empty, no greater element exists → -1
        Push current element
```

This is O(n) instead of the naive O(n²). Very commonly tested.

---

## Time & Space Complexity

| Operation | Array Stack | LL Stack |
|-----------|------------|----------|
| Push | O(1) | O(1) |
| Pop | O(1) | O(1) |
| Peek | O(1) | O(1) |
| isEmpty | O(1) | O(1) |
| Search | O(n) | O(n) |
| Space | O(n) fixed | O(n) dynamic |

---

## Common Mistakes
1. **Stack underflow** — popping from an empty stack. Always check `isEmpty()` first.
2. **Stack overflow** — pushing to a full array stack. Always check `isFull()` first.
3. **Using array index 0 as empty** — use `top = -1` for empty, not `top = 0`.
4. **Forgetting to free** — in linked-list stack, every pop must `free()` the node.
5. **Confusing LIFO with FIFO** — stack = LIFO, queue = FIFO.

---

## Build and Run

```bash
gcc operations.c -o operations
./operations
```

## Files
- `operations.c` — Array-based stack, linked-list-based stack, and 3 applications (balanced parentheses, infix-to-postfix, postfix evaluation).
- `README.md` — This conceptual guide.
