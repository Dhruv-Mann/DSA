# DSA — Data Structures & Algorithms in C

My journey through Data Structures & Algorithms, started at the beginning of Sem 2. Every implementation is written in **C** with detailed step-by-step comments so the code reads like a tutorial.

---

## Repository Structure

| Folder | What's Inside |
|--------|--------------|
| **Array-Operations/** | 29 array operations (insert, delete, search, sort, merge, rotate …) |
| **Single Linked List-Operations/** | 13 singly-linked-list operations |
| **Doubly Linked List-Operations/** | 15 doubly-linked-list operations |
| **Circular Linked List-Operations/** | 12 circular-linked-list operations |
| **Circular Doubly Linked List-Operations/** | 15 circular-doubly-linked-list operations |
| **Stack-Operations/** | Array & linked-list stacks + 3 applications (balanced parens, infix→postfix, postfix eval) |
| **Queue-Operations/** | 5 queue variants — simple, circular, linked-list, deque, priority queue |
| **Sorting/** | 8 sorting algorithms (Bubble, Selection, Insertion, Merge, Quick, Counting, Radix, Bucket) |
| **Leetcodes-Python/** | LeetCode solutions in Python |
| **SEM-2 Labs (C)/** | Lab programs from Semester 2 |

Each data-structure folder contains:
- **`operations.c`** — fully working, menu-driven C program with every operation implemented and commented.
- **`README.md`** — conceptual guide: *what* it is, *why* it matters, comparisons, real-world uses, common mistakes, and LeetCode problems.

---

## Sorting Algorithms at a Glance

| Algorithm | Best | Average | Worst | Space | Stable? |
|-----------|------|---------|-------|-------|---------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | No |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| Counting Sort | O(n + k) | O(n + k) | O(n + k) | O(k) | Yes |
| Radix Sort | O(nk) | O(nk) | O(nk) | O(n + k) | Yes |
| Bucket Sort | O(n + k) | O(n + k) | O(n²) | O(n) | Yes |

---

## LeetCode Solutions

| # | Problem | File |
|---|---------|------|
| 1 | Two Sum | `1_Two_Sum.py` |
| 27 | Remove Element | `27_Remove_Element.py` |
| 35 | Search Insert Position | `35_Search_Insert_Position.py` |
| 49 | Group Anagrams | `49_Group_Anagrams.py` |
| 69 | Sqrt(x) | `69_Sqrt(x).py` |
| 217 | Contains Duplicate | `217_Contains_Duplicate.py` |
| 242 | Valid Anagram | `242_Valid_Anagram.py` |
| 367 | Valid Perfect Square | `367_Valid_Perfect_Square.py` |
| 704 | Binary Search | `704_Binary_Search.py` |
| 744 | Find Smallest Letter Greater Than Target | `744_Find_Smallest_Letter_Greater_Than_Target.py` |

---

## How to Use

```bash
# compile any operations file
gcc "Doubly Linked List-Operations/operations.c" -o dll

# run it
./dll          # Linux / macOS
dll.exe        # Windows
```

Every program is **menu-driven** — just follow the on-screen prompts.

---

## Roadmap

- [x] Arrays
- [x] Singly Linked List
- [x] Doubly Linked List
- [x] Circular Linked List
- [x] Circular Doubly Linked List
- [x] Stacks
- [x] Queues
- [x] Sorting Algorithms
- [ ] Trees (Binary Tree, BST, AVL)
- [ ] Heaps & Priority Queues (heap-based)
- [ ] Hashing
- [ ] Graphs (BFS, DFS, Dijkstra, …)
- [ ] Tries
- [ ] Dynamic Programming

---

## Quick Reference — When to Use What

| Need | Best DS |
|------|---------|
| Fast random access by index | Array |
| Frequent insert/delete at ends | Doubly Linked List / Deque |
| LIFO (undo, recursion, DFS) | Stack |
| FIFO (scheduling, BFS) | Queue |
| Round-robin / continuous cycling | Circular Linked List |
| O(1) insert + delete at both ends, bidirectional traversal | Circular Doubly Linked List |
| Sorted data + fast search | Sorted Array + Binary Search |
| Priority-based processing | Priority Queue / Heap |

---

> *"The purpose of abstraction is not to be vague, but to create a new semantic level in which one can be absolutely precise."* — Edsger Dijkstra
