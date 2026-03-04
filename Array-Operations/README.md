# Array — Complete Guide

## What is an Array?

An **Array** is the most fundamental data structure in computer science. It stores elements in **contiguous memory locations**, allowing direct access to any element using its **index**.

```
Index:   0     1     2     3     4
       [10]  [20]  [30]  [40]  [50]
        ↑
      base address (arr)
```

Address of `arr[i]` = base address + i × sizeof(element)

This formula is why array access is **O(1)** — the CPU calculates the memory address directly from the index. No traversal, no searching.

---

## Why Arrays Matter (The Foundation of Everything)

Arrays aren't just "the first data structure you learn" — they are the **backbone of nearly every other data structure**:

- **Stacks** → often implemented with arrays
- **Queues** → circular array implementation
- **Heaps** → stored as arrays (parent at `i`, children at `2i+1` and `2i+2`)
- **Hash Tables** → array of buckets
- **Strings** → arrays of characters
- **Matrices** → 2D arrays
- **Dynamic Arrays** → (Python `list`, Java `ArrayList`, C++ `vector`) — resizable arrays

Understanding arrays deeply means understanding memory, caching, and performance.

---

## Static vs Dynamic Arrays

### Static Array (C-style, fixed size)
```c
int arr[10];    // fixed at compile time, stored on stack
```
- Size must be known at compile time
- Cannot grow or shrink
- Very fast (stack allocation)
- Risk of stack overflow if too large

### Dynamic Array (malloc/realloc)
```c
int* arr = (int*)malloc(10 * sizeof(int));    // heap allocation
arr = (int*)realloc(arr, 20 * sizeof(int));   // resize
```
- Size chosen at runtime
- Can grow/shrink with `realloc`
- Slower (heap allocation)
- Must manually `free()` to avoid memory leaks

### Dynamic Array (Python list / Java ArrayList)
These handle resizing automatically:
- When full, allocate a new array of **2× size** and copy elements
- **Amortized O(1)** append — most appends are O(1), occasional resize is O(n), but averaged over n operations it's O(1)

This is how most real-world "arrays" work.

---

## Array vs Linked List (The Fundamental Comparison)

| Feature | Array | Linked List |
|---------|-------|-------------|
| **Access by index** | **O(1)** direct | O(n) traverse |
| **Insert at beginning** | O(n) shift all | **O(1)** update head |
| **Insert at end** | **O(1)** amortized | O(n) or O(1)* |
| **Insert at middle** | O(n) shift | O(n) traverse + O(1) link |
| **Delete at beginning** | O(n) shift all | **O(1)** update head |
| **Delete at end** | **O(1)** | O(n) |
| **Search (unsorted)** | O(n) | O(n) |
| **Search (sorted)** | **O(log n)** binary search | O(n) |
| **Memory layout** | **Contiguous** (cache-friendly) | Scattered (cache-unfriendly) |
| **Memory overhead** | None per element | 1-2 pointers per element |
| **Size flexibility** | Fixed (or amortized resize) | Fully dynamic |

\* O(1) with tail pointer

### The Cache Advantage (Why Arrays Are Fast in Practice)
Modern CPUs load data in **cache lines** (typically 64 bytes). When you access `arr[0]`, the CPU loads `arr[0]` through `arr[15]` (for 4-byte ints) into cache. Subsequent accesses to `arr[1]`, `arr[2]`, etc. are **cache hits** — essentially free.

Linked list nodes are scattered in memory. Each `node->next` access is likely a **cache miss** — up to 100× slower than a cache hit.

**This is why arrays outperform linked lists for traversal even though both are O(n).**

---

## All Operations (29 Total)

### Basic Operations (1-6)
| # | Operation | Time | Space |
|---|-----------|------|-------|
| 1 | Create/Initialize | O(n) | O(n) |
| 2 | Traverse/Display | O(n) | O(1) |
| 3 | Insert at position | O(n) | O(1) |
| 4 | Delete at position | O(n) | O(1) |
| 5 | Search (Linear) | O(n) | O(1) |
| 6 | Update at position | O(1) | O(1) |

### Sorting & Searching (7, 16-17)
| # | Operation | Time | Space |
|---|-----------|------|-------|
| 7 | Sort (Bubble) | O(n²) | O(1) |
| 16 | Binary Search | O(log n) | O(1) |
| 17 | Find All Occurrences | O(n) | O(1) |

### Manipulation (8-10, 18-20)
| # | Operation | Time | Space |
|---|-----------|------|-------|
| 8 | Merge Two Arrays | O(n+m) | O(n+m) |
| 9 | Copy Array | O(n) | O(n) |
| 10 | Reverse (in-place) | O(n) | O(1) |
| 18 | Rotate Left by k | O(n) | O(1) |
| 19 | Rotate Right by k | O(n) | O(1) |
| 20 | Remove Duplicates | O(n²) | O(n) |

### Statistical (11-15, 21-22, 27-29)
| # | Operation | Time | Space |
|---|-----------|------|-------|
| 11 | Count Elements | O(1) | O(1) |
| 12 | Find Minimum | O(n) | O(1) |
| 13 | Find Maximum | O(n) | O(1) |
| 14 | Sum of Elements | O(n) | O(1) |
| 15 | Average of Elements | O(n) | O(1) |
| 21 | Second Largest | O(n) | O(1) |
| 22 | Second Smallest | O(n) | O(1) |
| 27 | Product of Elements | O(n) | O(1) |
| 28 | Find Median | O(n²)* | O(n) |
| 29 | Standard Deviation | O(n) | O(1) |

### Analysis (23-26)
| # | Operation | Time | Space |
|---|-----------|------|-------|
| 23 | Check if Sorted | O(n) | O(1) |
| 24 | Frequency Count | O(n²) | O(1) |
| 25 | Find Missing Number | O(n) | O(1) |
| 26 | Find All Duplicates | O(n²) | O(1) |

\* O(n²) due to sorting step; could be O(n) with quickselect algorithm

---

## Key Algorithms Explained

### Binary Search — The Most Important Array Algorithm
```
Prerequisite: Array MUST be sorted

left = 0, right = n-1
while left <= right:
    mid = left + (right - left) / 2    ← avoids overflow vs (left+right)/2
    if arr[mid] == target: return mid
    if arr[mid] < target: left = mid + 1
    else: right = mid - 1
return -1  (not found)
```
Eliminates half the search space each step → **O(log n)**.
For 1 billion elements, binary search takes at most **30 comparisons** vs 1 billion for linear search.

### Array Rotation by Reversal (Elegant O(n) trick)
To rotate left by k positions:
```
Original:     [1, 2, 3, 4, 5, 6, 7]    rotate left by 3
Step 1: Reverse first k:     [3, 2, 1, 4, 5, 6, 7]
Step 2: Reverse remaining:   [3, 2, 1, 7, 6, 5, 4]
Step 3: Reverse all:         [4, 5, 6, 7, 1, 2, 3]    ✓
```
Three in-place reversals. O(n) time, O(1) extra space. No temporary array needed.

### Two-Pointer Technique
Many array problems use two pointers moving toward or away from each other:
```
Remove duplicates from sorted array:
slow = 0
for fast = 1 to n-1:
    if arr[fast] != arr[slow]:
        slow++
        arr[slow] = arr[fast]
return slow + 1  (new length)
```
O(n) time, O(1) space. Used in countless LeetCode problems.

---

## Where Arrays Are Actually Used (Real World)

### 1. Image Processing
An image is a 2D array of pixels. Every photo you see on screen is stored and manipulated as an array.

### 2. Databases
Database tables are essentially arrays of records. B-trees (which power database indices) use arrays within each node.

### 3. String Processing
Strings are arrays of characters. Every text editor, search engine, and compiler works with character arrays.

### 4. Audio/Video
Audio samples and video frames are stored as arrays. Playback = traversal. Editing = insert/delete.

### 5. Scientific Computing
Matrices (2D arrays) are the foundation of linear algebra, machine learning, and physics simulations. Libraries like NumPy are optimized array operations.

### 6. Heaps and Priority Queues
Binary heaps are stored as arrays without pointers:
```
        10
       /  \
      20    30
     / \
    40   50

Array: [10, 20, 30, 40, 50]
Parent of i: (i-1)/2
Left child of i: 2i+1
Right child of i: 2i+2
```
This is used in Dijkstra's algorithm, heap sort, and priority queues.

---

## Common Array Problems (LeetCode)

| Problem | Difficulty | Key Technique |
|---------|-----------|---------------|
| Two Sum (#1) | Easy | HashMap |
| Best Time to Buy & Sell Stock (#121) | Easy | Track min so far |
| Contains Duplicate (#217) | Easy | HashSet |
| Maximum Subarray (#53) | Medium | Kadane's algorithm |
| Product of Array Except Self (#238) | Medium | Prefix/suffix products |
| Merge Intervals (#56) | Medium | Sort + merge |
| 3Sum (#15) | Medium | Sort + two pointers |
| Container With Most Water (#11) | Medium | Two pointers |
| Trapping Rain Water (#42) | Hard | Two pointers or stack |
| Sliding Window Maximum (#239) | Hard | Monotonic deque |
| Rotate Array (#189) | Medium | Reversal trick |
| Move Zeroes (#283) | Easy | Two pointers |
| Next Permutation (#31) | Medium | Right-to-left scan |
| First Missing Positive (#41) | Hard | Cyclic sort |
| Median of Two Sorted Arrays (#4) | Hard | Binary search |

### Key Patterns to Master
1. **Two Pointers** — For sorted arrays, pair finding, partitioning
2. **Sliding Window** — For contiguous subarrays with constraints
3. **Prefix Sum** — For range sum queries in O(1)
4. **Kadane's Algorithm** — Maximum subarray sum in O(n)
5. **Binary Search** — For sorted arrays, rotated arrays, search space reduction
6. **Cyclic Sort** — For arrays containing numbers 1 to n

---

## Sorting Algorithms Comparison (for arrays)

| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | No |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | No |
| Counting Sort | O(n+k) | O(n+k) | O(n+k) | O(k) | Yes |
| Radix Sort | O(nk) | O(nk) | O(nk) | O(n+k) | Yes |

The `Sorting/` folder in this repo has implementations of all of these.

---

## Multi-Dimensional Arrays

### 2D Array (Matrix)
```c
int matrix[3][4];    // 3 rows, 4 columns

// Row-major order (C): stored row by row in memory
// [row0_col0, row0_col1, ..., row1_col0, row1_col1, ...]
```

Used for:
- Graphs (adjacency matrix)
- Dynamic programming tables
- Image processing
- Game boards (chess, tic-tac-toe)

### Common Matrix Operations
- **Transpose**: swap `matrix[i][j]` with `matrix[j][i]`
- **Rotate 90°**: transpose + reverse each row
- **Spiral traversal**: 4-boundary shrinking technique

---

## Common Mistakes
1. **Off-by-one errors** — Array indices start at 0. `arr[n]` is OUT OF BOUNDS for size n.
2. **Buffer overflow** — Writing past the array boundary. C doesn't check bounds.
3. **Not freeing dynamic arrays** — Every `malloc` needs a `free`.
4. **Integer overflow in search** — `(left + right) / 2` can overflow. Use `left + (right - left) / 2`.
5. **Shifting inefficiency** — Inserting/deleting at position 0 requires shifting ALL elements. Consider a linked list if this is frequent.
6. **Forgetting realloc can fail** — Always check the return value. Assign to a temp pointer first to avoid losing the original.
7. **Using VLAs in production** — Variable-length arrays (`int arr[n]`) are stack-allocated and can cause stack overflow. Use `malloc` for large arrays.

---

## Build and Run

```bash
gcc Array-operations.c -o array_ops
./array_ops
```

## Files
- `Array-operations.c` — 29 array operations with categorized menu, complete with error handling and memory management.
- `Array-operations.py` — Python implementation of array operations.
- `README.md` — This conceptual guide.
