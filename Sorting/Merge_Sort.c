#include <stdio.h>
#include <stdlib.h>

/*
 * ==================== MERGE SORT ALGORITHM ====================
 * 
 * ALGORITHM: Merge_Sort(arr[], left, right)
 * 
 *   Step 1: Check if left < right (base case for recursion)
 *   Step 2: Calculate middle index: mid = left + (right - left) / 2
 *   Step 3: Recursively call Merge_Sort for the first half:
 *           Merge_Sort(arr, left, mid)
 *   Step 4: Recursively call Merge_Sort for the second half:
 *           Merge_Sort(arr, mid + 1, right)
 *   Step 5: Merge the two sorted halves into a sorted subarray:
 *           Merge(arr, temp, left, mid, right)
 * 
 * ------------------------------------------------------------------
 * 
 * MERGE PROCEDURE: Merge(arr, temp, left, mid, right)
 * 
 *   Step 1: Initialize pointers:
 *           i = left (start of left half)
 *           j = mid + 1 (start of right half)
 *           k = left (start of temp array)
 * 
 *   Step 2: Compare elements from both halves and copy smaller to temp:
 *           While (i <= mid AND j <= right):
 *               If arr[i] <= arr[j]:
 *                   temp[k] = arr[i]
 *                   Increment i and k
 *               Else:
 *                   temp[k] = arr[j]
 *                   Increment j and k
 * 
 *   Step 3: Copy remaining elements from left half (if any) to temp
 *   Step 4: Copy remaining elements from right half (if any) to temp
 *   Step 5: Copy sorted elements from temp back to original arr
 * 
 * ==================================================================
 * 
 * COMPLEXITY ANALYSIS:
 * 
 *   - Time Complexity: 
 *       Best Case: O(n log n) - consistently divides and merges
 *       Average Case: O(n log n)
 *       Worst Case: O(n log n)
 * 
 *   - Space Complexity: O(n) (requires auxiliary array for merging)
 *   - Stability: Stable (equal elements maintain relative order)
 *   - Recurrence Relation: T(n) = 2T(n/2) + O(n)
 * 
 * ------------------------------------------------------------------
 * 
 * CHARACTERISTICS:
 * 
 *   - Divide and Conquer algorithm
 *   - Not in-place (requires extra memory)
 *   - Predictable performance (same time regardless of input data)
 *   - Stable sorting algorithm (crucial for complex data structures)
 *   - Preferred for Linked Lists sorting
 *   - Optimization: Allocated temp array once to prevent Heap fragmentation
 * 
 * ------------------------------------------------------------------
 * 
 * HOW IT WORKS:
 * 
 *   - Divides the array into two halves recursively until size becomes 1
 *   - Merges the halves back together in sorted order
 *   - Uses an auxiliary array to hold sorted elements before copying back
 * 
 * ==================================================================
 */

// Global variables shared across functions
int n;
int *arr;

// Reads input size, validates, allocates array, and loads elements
void create()
{
    // Read desired array size
    printf("Enter the number of elements of the array: ");
    scanf("%d", &n);

    // Validate size to avoid invalid/negative lengths
    if (n <= 0)
    {
        printf("Invalid number of elements.\n");
        exit(1);
    }

    // Allocate contiguous memory for n integers
    // We use malloc to support large arrays without Stack Overflow
    arr = (int *)malloc(sizeof(int) * n);
    if (arr == NULL)
    {
        // Handle allocation failure gracefully
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Read n elements into the array
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
}

// Merges two sorted subarrays into the temp array and copies back
void merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left;      // Pointer for left subarray
    int j = mid + 1;   // Pointer for right subarray
    int k = left;      // Pointer for temp array

    // Compare elements from both subarrays and pick the smaller one
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Copy any remaining elements of the left subarray
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Copy any remaining elements of the right subarray
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Copy the sorted subarray from temp back to the original array
    // We only copy the range [left...right] that we just processed
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

// Core recursive function for Merge Sort
void mergeSortRecursive(int arr[], int temp[], int left, int right) {
    if (left < right) {
        // Calculate mid point to split array
        // (left + right) / 2 can overflow for very large integers, so we use:
        int mid = left + (right - left) / 2;

        // Recursively sort the first and second halves
        mergeSortRecursive(arr, temp, left, mid);
        mergeSortRecursive(arr, temp, mid + 1, right);

        // OPTIMIZATION: Check if array is already sorted
        // If the last element of left half is <= first element of right half,
        // no merge is needed.
        if (arr[mid] <= arr[mid + 1]) {
            return;
        }

        // Merge the sorted halves
        merge(arr, temp, left, mid, right);
    }
}

// Wrapper function to manage memory allocation
// This makes the code cleaner and optimized by allocating 'temp' only ONCE
void Merge_Sort_Wrapper(int arr[], int n) {
    // Edge case: empty or single-element array is already sorted
    if (n < 2) return;

    // Allocate auxiliary memory ONCE here
    // This is much faster than allocating inside the recursive 'merge' function
    int *temp = (int *)malloc(sizeof(int) * n);
    
    if (temp == NULL) {
        printf("Memory allocation for temp array failed!\n");
        exit(1);
    }

    // Start the recursive sort
    mergeSortRecursive(arr, temp, 0, n - 1);

    // Free the auxiliary memory
    free(temp);
}

// Program entry: build array, sort, display results, and clean up
int main()
{
    create();                   // Read input and allocate array
    
    Merge_Sort_Wrapper(arr, n); // Sort using optimized Merge Sort

    // Output the sorted array
    printf("Sorted Array: \n\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Release allocated memory to prevent memory leaks
    free(arr);
    arr = NULL; // Avoid dangling pointer
    
    return 0;
}