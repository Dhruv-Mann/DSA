# Queue — Complete Guide

## What is a Queue?

A **Queue** is an abstract data type (ADT) that follows the **FIFO** principle: **First In, First Out**.

The first element added is the first one removed — like a line at a ticket counter.

```
FRONT                          REAR
  ↓                              ↓
| 10 | 20 | 30 | 40 | 50 |
  ↑ dequeue here      enqueue here ↑
```

### Core Operations
| Operation | Description | Time |
|-----------|-------------|------|
| `enqueue(x)` | Add element x at the rear | O(1) |
| `dequeue()` | Remove and return the front element | O(1) |
| `peek()` / `front()` | Return front element without removing | O(1) |
| `isEmpty()` | Check if queue has no elements | O(1) |
| `isFull()` | Check if at capacity (array-based) | O(1) |

ALL core operations are **O(1)**.

---

## Why Use a Queue? (The Real Importance)

### 1. BFS (Breadth-First Search) — THE #1 Use
BFS uses a queue to explore nodes level by level:
```
enqueue(start)
while queue is not empty:
    node = dequeue()
    process node
    enqueue all unvisited neighbors
```

This explores nodes in order of their **distance** from the start.

**Where BFS (and therefore queues) are essential:**
- Shortest path in unweighted graphs
- Level-order tree traversal
- Finding connected components
- Web crawlers (process URLs in order discovered)
- Social network "degrees of separation"

**Stack → DFS, Queue → BFS. You MUST know both for non-linear DS.**

### 2. CPU Scheduling
Operating systems use queues to manage processes:
- **FCFS (First Come First Served)**: Simple queue of processes.
- **Round Robin**: Circular queue — each process gets a time slice, then goes to the back of the queue.
- **Priority Scheduling**: Priority queue — highest priority runs first.
- **Multilevel Queue**: Multiple queues, one per priority level.

### 3. Print Spooler
When you send documents to a printer, they're queued. The first document sent prints first.

### 4. Message Queues (Real-World Software)
- **RabbitMQ**, **Apache Kafka**, **Amazon SQS** — all message queue systems.
- Producers enqueue messages, consumers dequeue them.
- This pattern powers microservices, event-driven architectures, and most large-scale web apps.

### 5. Buffer for Data Streams
- **Keyboard buffer**: Keystrokes are queued and processed in order.
- **Network packets**: Arriving packets are queued for processing.
- **Video streaming**: Frames are buffered (queued) so playback is smooth.

---

## Five Types of Queues

### 1. Simple Queue
Standard FIFO queue. Limitation: wasted space in array implementation.

### 2. Circular Queue
Wraps around to reuse space. Solves the wasted space problem.
```
Simple:   [_, _, _, 40, 50]  ← indices 0-2 wasted after dequeue
Circular: [60, 70, _, 40, 50] ← rear wraps to index 0, reuses space
```

### 3. Deque (Double-Ended Queue)
Insert/delete at BOTH ends. Can act as both a stack and a queue.

### 4. Priority Queue
Elements have priorities. Highest priority dequeues first, not FIFO.
- Array-based: O(n) dequeue (find min/max)
- **Heap-based: O(log n) dequeue** (the real-world implementation)

### 5. Circular Deque
A deque with circular array implementation. Combines deque flexibility with circular space efficiency.

---

## Comparison of Queue Types

| Feature | Simple Q | Circular Q | Linked Q | Deque | Priority Q |
|---------|----------|-----------|----------|-------|-----------|
| FIFO | Yes | Yes | Yes | Optional | No |
| Space reuse | No | **Yes** | N/A | **Yes** | N/A |
| Fixed size | Yes | Yes | **No** | Yes | Yes |
| Insert front | No | No | No | **Yes** | No |
| Insert rear | Yes | Yes | Yes | **Yes** | Yes |
| Delete front | Yes | Yes | Yes | **Yes** | Yes* |
| Delete rear | No | No | No | **Yes** | No |
| Priority order | No | No | No | No | **Yes** |

\* Priority queue dequeues the highest-priority element, which may not be at the front.

---

## Implementing Queues Using Other Data Structures

### Queue Using Two Stacks (Classic Interview Question)
Since a stack is LIFO and a queue is FIFO, you need two stacks to "reverse" the order:

**Method (Costly Dequeue):**
```
Stack1 = for enqueue
Stack2 = for dequeue

enqueue(x):
    push x to Stack1          → O(1)

dequeue():
    if Stack2 is empty:
        while Stack1 not empty:
            pop from Stack1, push to Stack2    → transfers in reverse order
    return pop from Stack2                     → O(1) amortized
```

**Why this works:** Stack1 stores elements in push order. When we transfer to Stack2, the order reverses — now the bottom of Stack1 (oldest element) is at the top of Stack2 (first to pop = FIFO!).

**Amortized O(1)** per operation — each element is moved at most twice.

### Queue Using Linked List
- Front pointer → head of list (dequeue here)
- Rear pointer → tail of list (enqueue here)
- Both operations O(1)

### Queue Using Circular Array
The modulo trick: `next_index = (current_index + 1) % capacity`

### Priority Queue Using Heap
- **Binary Min-Heap** for min-priority queue
- **Binary Max-Heap** for max-priority queue
- O(log n) insert and delete — vastly better than O(n) array version
- This is how `std::priority_queue` (C++), `PriorityQueue` (Java), and `heapq` (Python) work

### Deque Using CDLL
A Circular Doubly Linked List gives O(1) insert/delete at both ends — perfect for a deque.

---

## Stack vs Queue — When to Use Which

| Scenario | Use Stack | Use Queue |
|----------|-----------|-----------|
| DFS (Depth-First Search) | ✓ | |
| BFS (Breadth-First Search) | | ✓ |
| Undo/Redo | ✓ | |
| Task scheduling | | ✓ |
| Expression evaluation | ✓ | |
| Print job management | | ✓ |
| Browser back button | ✓ | |
| Buffering data streams | | ✓ |
| Function call management | ✓ | |
| Level-order traversal | | ✓ |

**Memory aid:**
- **Stack**: goes DEEP (DFS, recursion, nested structures)
- **Queue**: goes WIDE (BFS, level-by-level, fair scheduling)

---

## Common Queue Problems (LeetCode)

| Problem | Difficulty | Key Idea |
|---------|-----------|----------|
| Implement Queue using Stacks (#232) | Easy | Two-stack trick |
| Implement Stack using Queues (#225) | Easy | Self-rotation trick |
| Number of Recent Calls (#933) | Easy | Queue with time window |
| Sliding Window Maximum (#239) | Hard | Monotonic deque |
| Rotting Oranges (#994) | Medium | Multi-source BFS |
| Walls and Gates (#286) | Medium | Multi-source BFS |
| Course Schedule (#207) | Medium | Topological sort (BFS with queue) |
| Binary Tree Level Order (#102) | Medium | BFS with queue |
| Open the Lock (#752) | Medium | BFS shortest path |
| Design Circular Queue (#622) | Medium | Circular array |
| Design Circular Deque (#641) | Medium | Circular array |
| Task Scheduler (#621) | Medium | Priority queue / greedy |
| Find Median from Data Stream (#295) | Hard | Two priority queues (heaps) |

### The BFS Pattern (Most Important Queue Pattern)
```
queue = [start]
visited = {start}

while queue not empty:
    node = dequeue()
    if node is goal: return result
    for neighbor in node.neighbors:
        if neighbor not in visited:
            visited.add(neighbor)
            enqueue(neighbor)
```

This pattern solves MANY graph/tree problems. Master it.

---

## The Circular Queue — Why It Matters

The circular queue's modulo trick is used EVERYWHERE:
- Ring buffers in operating systems
- Circular logging (overwrite oldest logs)
- Audio/video streaming buffers
- Network packet buffers
- The `ArrayDeque` in Java uses a circular array

```
Key formula: next_index = (current_index + 1) % capacity
             prev_index = (current_index - 1 + capacity) % capacity
```

The `+ capacity` in the prev formula prevents negative modulo (C quirk).

---

## Time Complexity Summary

| Operation | Simple Q | Circular Q | Linked Q | Deque | Priority Q (Array) | Priority Q (Heap) |
|-----------|----------|-----------|----------|-------|--------------------|-------------------|
| Enqueue | O(1) | O(1) | O(1) | O(1) | O(1) | O(log n) |
| Dequeue | O(1) | O(1) | O(1) | O(1) | O(n) | O(log n) |
| Peek | O(1) | O(1) | O(1) | O(1) | O(n) | O(1) |
| isEmpty | O(1) | O(1) | O(1) | O(1) | O(1) | O(1) |
| Space | O(n) | O(n) | O(n) | O(n) | O(n) | O(n) |

---

## Common Mistakes
1. **Simple queue space waste** — using a simple queue when a circular queue is needed.
2. **Circular queue modulo** — forgetting `% MAX_SIZE` when incrementing front/rear.
3. **Negative modulo in C** — `(-1) % 5` is -1 in C, not 4. Always add capacity: `(-1 + 5) % 5 = 4`.
4. **Empty vs Full confusion in circular queue** — both have `front == rear`. Use a count variable or sacrifice one slot to distinguish.
5. **Linked queue rear update** — after dequeue, if `front` becomes `NULL`, you must also set `rear = NULL`.
6. **Using array priority queue in production** — O(n) dequeue is too slow. Use a heap for O(log n).

---

## Build and Run

```bash
gcc operations.c -o operations
./operations
```

## Files
- `operations.c` — Five queue implementations (simple, circular, linked list, deque, priority queue) with detailed comments.
- `README.md` — This conceptual guide.
