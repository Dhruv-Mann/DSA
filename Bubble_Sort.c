#include <stdio.h>
#include <stdlib.h>

/*
 * ==================== BUBBLE SORT ALGORITHM ====================
 * 
 * ALGORITHM: Bubble_Sort(arr[], n)
 * 
 * Step 1: Start
 * 
 * Step 2: Initialize outer loop counter i = 0
 * 
 * Step 3: Repeat Steps 4 to 10 while i < n
 * 
 * Step 4: Set swapped = 0 (flag to detect if any swap occurs)
 * 
 * Step 5: Initialize inner loop counter j = 0
 * 
 * Step 6: Repeat Steps 7 to 9 while j < n-i-1
 * 
 * Step 7: Compare arr[j] with arr[j+1]
 * 
 * Step 8: If arr[j] > arr[j+1], then
 *           - Swap arr[j] and arr[j+1]
 *           - Set swapped = 1
 * 
 * Step 9: Increment j by 1
 * 
 * Step 10: If swapped = 0, then break the loop (array is already sorted)
 *          Else increment i by 1 and continue
 * 
 * Step 11: Array is now sorted in ascending order
 * 
 * Step 12: Stop
 * 
 * ==================================================================
 * 
 * COMPLEXITY ANALYSIS:
 *  - Time Complexity: 
 *      Best Case: O(n) - when array is already sorted
 *      Average Case: O(n²)
 *      Worst Case: O(n²) - when array is reverse sorted
 *  - Space Complexity: O(1) (in-place sorting)
 *  - Stability: Stable (equal elements maintain relative order)
 *  - Number of Swaps: O(n²) in worst case
 *  - Number of Comparisons: O(n²) - maximum n(n-1)/2 comparisons
 * 
 * CHARACTERISTICS:
 *  - In-place sorting algorithm
 *  - Adaptive (performs well on nearly sorted arrays with optimization)
 *  - Simple to implement and understand
 *  - Stable sorting algorithm
 *  - Best suited for small datasets or educational purposes
 *  - Optimization: Early termination when no swaps occur
 * 
 * HOW IT WORKS:
 *  - Repeatedly compares adjacent elements and swaps if they're in wrong order
 *  - Larger elements "bubble up" to the end of the array in each pass
 *  - After each pass, the largest unsorted element reaches its final position
 *  - Process continues until no more swaps are needed
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
    printf("enter the number of elements of the array: ");
    scanf("%d", &n);

    // Validate size to avoid invalid/negative lengths
    if (n <= 0)
    {
        printf("Inavlid number of elements: ");
        exit(1);
    }

    // Allocate contiguous memory for n integers
    arr = (int *)malloc(sizeof(int) * n);
    if (arr == NULL)
    {
        // Handle allocation failure gracefully
        printf("Mmemory allocation failed!");
        exit(1);
    }

    // Read n elements into the array
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
}
// Swaps two integer values using pointers
void swap(int *x, int *y)
{
    // Use temporary variable to exchange values
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Sorts the array in ascending order using Bubble Sort
void Bubble_Sort(int arr[], int n)
{
    // Outer loop: repeated passes through the array
    // After i passes, the last i elements are in their correct sorted positions
    for (int i = 0; i < n; i++)
    {
        // Flag to detect if any swaps occurred in this pass (optimization for early termination)
        int swapped = 0;

        // Inner loop: compare adjacent pairs and swap if out of order
        // j < n - i - 1 because the last i elements are already sorted
        for (int j = 0; j < n - i - 1; j++)
        {
            // If current element is greater than next, they're out of order
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);  // Bubble larger element towards the end
                swapped = 1;                  // Mark that a swap occurred
            }
        }

        // If no swaps happened this pass, array is already sorted
        if (swapped == 0)
            break;  // Early termination optimization
    }
}

// Program entry: build array, sort, display results, and clean up
int main()
{
    create();                         // Read input and allocate array
    Bubble_Sort(arr, n);              // Sort in ascending order

    // Output the sorted array
    printf("Sorted Array: \n\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    // Release allocated memory and avoid dangling pointer
    free(arr);
    arr = NULL;
    return 0;
}