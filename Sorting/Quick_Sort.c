#include <stdio.h>
#include <stdlib.h>

/*
 * ==================== QUICK SORT ALGORITHM ====================
 * 
 * ALGORITHM: Quick_Sort(arr[], low, high)
 * 
 *   Step 1: Check if low < high (base case for recursion)
 * 
 *   Step 2: Call Partition function to find the 'partition index' (pi)
 *           pi = Partition(arr, low, high)
 *           - After this step, arr[pi] is at its correct sorted position
 *           - All elements < arr[pi] are on the left
 *           - All elements > arr[pi] are on the right
 * 
 *   Step 3: Recursively call Quick_Sort for the left subarray:
 *           Quick_Sort(arr, low, pi - 1)
 * 
 *   Step 4: Recursively call Quick_Sort for the right subarray:
 *           Quick_Sort(arr, pi + 1, high)
 * 
 * ------------------------------------------------------------------
 * 
 * PARTITION PROCEDURE: Partition(arr, low, high)
 * 
 *   Step 1: Select a pivot element (e.g., pivot = arr[low])
 * 
 *   Step 2: Initialize pointers: i = low + 1, j = high
 * 
 *   Step 3: Repeat until i > j:
 *           - Increment i while arr[i] <= pivot
 *           - Decrement j while arr[j] > pivot
 *           - If i < j, swap arr[i] and arr[j]
 * 
 *   Step 4: Swap pivot (arr[low]) with arr[j] to place pivot correctly
 * 
 *   Step 5: Return j (the correct position of the pivot)
 * 
 * ==================================================================
 * 
 * COMPLEXITY ANALYSIS:
 * 
 *   - Time Complexity: 
 *       Best Case: O(n log n) - partition splits array evenly
 *       Average Case: O(n log n)
 *       Worst Case: O(n²) - when array is already sorted or reverse sorted
 * 
 *   - Space Complexity: O(log n) (stack space for recursion)
 *   - Stability: Unstable (relative order of equal elements not guaranteed)
 * 
 * ------------------------------------------------------------------
 * 
 * CHARACTERISTICS:
 * 
 *   - Divide and Conquer algorithm
 *   - In-place sorting (requires very little extra memory)
 *   - Usually faster than Merge Sort in practice due to better cache locality
 *   - Preferred for arrays over Merge Sort (Merge Sort is better for Linked Lists)
 * 
 * ------------------------------------------------------------------
 * 
 * HOW IT WORKS:
 * 
 *   - Picks an element as a 'pivot'
 *   - Partitions the array around the pivot
 *   - Recursively sorts the sub-arrays
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
    // Using malloc prevents Stack Overflow for large inputs
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

// Swaps two integer values using pointers
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Partitions the array around a pivot element
// Returns the index where the pivot element is finally placed
int partition(int arr[], int low, int high)
{
    // Choosing the first element as the pivot
    int pivot = arr[low];
    
    // Index scanning from left to right
    int i = low + 1;
    
    // Index scanning from right to left
    int j = high;

    while (i <= j)
    {
        // Find element greater than pivot from the left
        while (i <= high && arr[i] <= pivot)
        {
            i++;
        }

        // Find element smaller than pivot from the right
        while (j >= low && arr[j] > pivot)
        {
            j--;
        }

        // If pointers haven't crossed, swap the elements found above
        if (i < j)
        {
            swap(&arr[i], &arr[j]);
        }
    }

    // Place the pivot in its correct sorted position
    // We swap the pivot (at arr[low]) with arr[j]
    swap(&arr[low], &arr[j]);

    // Return the partitioning index
    return j;
}

// The main recursive Quick Sort function
void Quick_Sort(int arr[], int low, int high)
{
    if (low < high)
    {
        // pi is partitioning index, arr[pi] is now at correct place
        int pi = partition(arr, low, high);

        // Recursively sort elements before partition
        Quick_Sort(arr, low, pi - 1);

        // Recursively sort elements after partition
        Quick_Sort(arr, pi + 1, high);
    }
}

// Program entry: build array, sort, display results, and clean up
int main()
{
    create(); // Read input and allocate array
    
    // Call Quick Sort on the entire array range (0 to n-1)
    Quick_Sort(arr, 0, n - 1);

    // Output the sorted array
    printf("Sorted Array: \n\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Release allocated memory
    free(arr);
    arr = NULL; // Avoid dangling pointer
    
    return 0;
}