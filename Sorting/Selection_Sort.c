#include <stdio.h>
#include <stdlib.h>

/*
 * ==================== SELECTION SORT ALGORITHM ====================
 * 
 * ALGORITHM: Selection_Sort(arr[], n)
 * 
 * Step 1: Start
 * 
 * Step 2: Initialize loop counter i = 0
 * 
 * Step 3: Repeat Steps 4 to 8 while i < n-1
 * 
 * Step 4: Set min_idx = i (assume current position has minimum element)
 * 
 * Step 5: Initialize inner loop counter j = i+1
 * 
 * Step 6: Repeat Step 7 while j < n
 * 
 * Step 7: If arr[j] < arr[min_idx], then set min_idx = j
 *         (Find the index of minimum element in unsorted portion)
 *         Increment j by 1
 * 
 * Step 8: Swap arr[i] with arr[min_idx]
 *         (Place the minimum element at position i)
 *         Increment i by 1
 * 
 * Step 9: Array is now sorted in ascending order
 * 
 * Step 10: Stop
 * 
 * ==================================================================
 * 
 * COMPLEXITY ANALYSIS:
 *  - Time Complexity: O(n²) for all cases (Best, Average, Worst)
 *  - Space Complexity: O(1) (in-place sorting)
 *  - Stability: Not stable (equal elements may change relative order)
 *  - Number of Swaps: O(n) - at most n-1 swaps
 *  - Number of Comparisons: O(n²) - always (n-1)(n)/2 comparisons
 * 
 * CHARACTERISTICS:
 *  - In-place sorting algorithm
 *  - Not adaptive (doesn't benefit from partially sorted arrays)
 *  - Performs well on small datasets
 *  - Minimizes number of swaps compared to bubble sort
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
    printf("Enter the number of elements of array: ");
    scanf("%d", &n);

    // Validate size to avoid invalid/negative lengths
    if (n <= 0)
    {
        printf("Inavlid array Size!");
        exit(1);
    }

    // Allocate contiguous memory for n integers
    arr = (int *)malloc(sizeof(int) * n);
    if (arr == NULL)
    {
        // Handle allocation failure gracefully
        printf("Memory allocation failed! \n");
        exit(1);
    }

    // Read n elements into the array
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
}

// Sorts the array in ascending order using Selection Sort
void Selection_sort(int arr[], int n)
{
    // Iterate over each position i where the next smallest element should go
    for (int i = 0; i < n - 1; i++)
    {
        // i < n - 1 because the last element is fixed once all others are placed
        int min_idx = i; // Track index of the smallest element in the unsorted region [i..n-1]

        // Find the index of the minimum element in the remaining unsorted portion
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j; // Update min index when a smaller value is found
            }
        }

        // Swap the found minimum element into position i
        // (Swapping with itself when min_idx == i is harmless)
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

// Program entry: build array, sort, display results, and clean up
int main()
{
    create();                         // Read input and allocate array
    Selection_sort(arr, n);           // Sort in ascending order

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