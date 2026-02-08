# Single Linked List Operations (C)

A menu-driven C program that implements common singly linked list operations with dynamic memory allocation.

## Features
- Create a list with N nodes
- Traverse and display the list
- Insert at beginning, end, or a 1-based position
- Delete from beginning, end, or a 1-based position
- Delete by value
- Search for a value (returns position)
- Count nodes
- Reverse the list
- Sort the list (bubble sort)

## Build and Run

### Windows (MinGW GCC)
```bash
gcc operations.c -o operations
./operations
```

### Linux/macOS (GCC/Clang)
```bash
gcc operations.c -o operations
./operations
```

## Notes
- The program uses a global `head` pointer for the list.
- Input positions are 1-based.
- Exiting the program frees all allocated nodes.

## File
- `operations.c` - implementation of all linked list operations and the menu loop.
