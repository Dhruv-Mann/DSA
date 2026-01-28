# 🧮 Dynamic Array Operations System

A comprehensive Menu-Driven program implemented in C that demonstrates complete control over **Dynamic Memory Allocation**.

This project serves as a playground for array manipulations, allowing users to perform 15 different operations on a dynamically resized array in real-time.

## 🚀 Features & Operations

The program provides a console-based interface to perform the following:

### 🔹 Core Operations
1.  **Creation & Initialization:** Dynamically allocates memory (`malloc`) for an array of size *N*.
2.  **Traversal:** Visits and displays all elements currently in the array.
3.  **Insertion:** Adds a new element at any specified index. Automatically expands memory (`realloc`) to fit the new data.
4.  **Deletion:** Removes an element from any specified index. Automatically shrinks memory to optimize usage.
5.  **Update:** Modifies the value of an existing element at a specific index.

### 🔹 Search & Sort
6.  **Linear Search:** Scans the array to find the index of a specific target value.
7.  **Bubble Sort:** Sorts the entire array in ascending order using the Bubble Sort algorithm.
8.  **Merge Arrays:** Takes a second array input from the user and merges it with the current array into a single continuous block.

### 🔹 Utilities
9.  **Copy Array:** Creates a deep copy of the current array into a new memory block.
10. **Reverse Array:** Reverses the order of elements in-place using the two-pointer approach.
11. **Count Elements:** Returns the total number of elements currently stored.

### 🔹 Statistical Functions
12. **Find Minimum:** Scans the array to identify the smallest value.
13. **Find Maximum:** Scans the array to identify the largest value.
14. **Sum of Elements:** Calculates the total sum of all integers in the array.
15. **Average:** Computes the arithmetic mean of the dataset.

## ⚙️ Technical Highlights
* **Dynamic Memory Management:** Uses `malloc`, `realloc`, and `free` to manage memory manually, preventing memory leaks and ensuring efficient space usage.
* **Pointer Arithmetic:** Utilizes pointers for array traversal and manipulation instead of standard indexing where appropriate.
* **Error Handling:** Includes robust checks for:
    * Memory allocation failures (checking for `NULL`).
    * Invalid array indices (out of bounds).
    * Operations on empty arrays.

## 💻 How to Run
1.  **Compile the program:**
    ```bash
    gcc Array_Operations.c -o array_app
    ```
2.  **Run the executable:**
    ```bash
    ./array_app
    ```
3.  **Follow the on-screen menu:** Enter the number corresponding to the operation you wish to perform.

---
*Developed by Dhruv Mann*
