/*
 * ==================== RADIX SORT ALGORITHM ====================
 * 
 * ALGORITHM: Radix_Sort(arr[], n)
 * 
 * Step 1: Start
 * 
 * Step 2: Find the maximum element (max) in arr[]
 *         Set max = arr[0]
 *         For i = 1 to n-1
 *           If arr[i] > max, then max = arr[i]
 * 
 * Step 3: Initialize exp = 1 (represents digit position: 1s, 10s, 100s, etc.)
 * 
 * Step 4: Repeat Steps 5 to 6 while (max / exp) > 0
 * 
 * Step 5: Call Counting_Sort(arr, n, exp) to sort based on current digit
 *         (Uses counting sort on digit at position exp)
 * 
 * Step 6: Multiply exp by 10 (move to next digit position)
 * 
 * Step 7: Array is now sorted in ascending order
 * 
 * Step 8: Stop
 * 
 * ------------------------------------------------------------------------
 * COUNTING_SORT_BY_DIGIT(arr[], n, exp):
 * 
 * Step 1: Create output array of size n
 * 
 * Step 2: Create count array of size 10 (for digits 0-9), initialize to 0
 * 
 * Step 3: Store count of occurrences of each digit
 *         For i = 0 to n-1
 *           digit = (arr[i] / exp) % 10
 *           Increment count[digit]
 * 
 * Step 4: Create cumulative count array
 *         For i = 1 to 9
 *           count[i] = count[i] + count[i-1]
 * 
 * Step 5: Build output array (traverse from right to maintain stability)
 *         For i = n-1 down to 0
 *           digit = (arr[i] / exp) % 10
 *           output[count[digit] - 1] = arr[i]
 *           Decrement count[digit]
 * 
 * Step 6: Copy output array to arr[]
 *         For i = 0 to n-1
 *           arr[i] = output[i]
 * 
 * ------------------------------------------------------------------------
 * 
 * COMPLEXITY ANALYSIS:
 *  - Time Complexity: O(d × (n + k)) where:
 *      d = number of digits in maximum element
 *      n = number of elements
 *      k = range of digit values (10 for decimal)
 *      For fixed number of digits: O(n)
 *  - Space Complexity: O(n + k) for output and count arrays
 *  - Stability: Stable (maintains relative order of equal elements)
 * 
 * CHARACTERISTICS:
 *  - Non-comparison based sorting algorithm
 *  - Stable sorting algorithm
 *  - Not in-place (requires extra space)
 *  - Processes digits from least significant to most significant (LSD)
 *  - Uses counting sort as subroutine for each digit position
 *  - Efficient for integers with limited number of digits
 *  - Linear time complexity when d is constant
 * 
 * WHEN TO USE:
 *  - Sorting integers with limited number of digits
 *  - When you need a stable sort for numeric data
 *  - When linear time complexity is desired
 *  - Large datasets where comparison-based sorts are slower
 * 
 * HOW IT WORKS:
 *  - Sorts numbers digit by digit starting from least significant digit
 *  - Uses stable counting sort for each digit position
 *  - After sorting by all digits, array is completely sorted
 *  - Example: For 170, 45, 75, 90, 802, 24, 2, 66
 *    Pass 1 (1s): 170, 90, 802, 2, 24, 45, 75, 66
 *    Pass 2 (10s): 802, 2, 24, 45, 66, 170, 75, 90
 *    Pass 3 (100s): 2, 24, 45, 66, 75, 90, 170, 802
 * 
 * ==================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// Global variables shared across functions
int n;          // Size of the array
int *arr;       // Pointer to dynamically allocated array

// Reads input size, validates, allocates array, and loads elements
void create()
{
    // Read desired array size
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    
    // Validate size to avoid invalid/negative lengths
    if (n <= 0)
    {
        printf("Invalid array size! ");
        exit(1);
    }
    
    // Allocate contiguous memory for n integers
    arr = (int *)malloc(sizeof(int) * n);
    
    // Handle allocation failure gracefully
    if (arr == NULL)
    {
        printf("Memory allocation failed! ");
        exit(1);
    }
    
    // Read n elements into the array
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
}

// Finds and returns the maximum element in the array
// This determines how many digit positions we need to process
int get_MAX(int arr[], int n)
{
    // Assume first element is maximum
    int max = arr[0];
    
    // Compare with remaining elements
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    
    return max;
}

// Modified Counting Sort to sort array based on a specific digit position
// exp represents the digit position: 1 for units, 10 for tens, 100 for hundreds, etc.
void Counting_Sort(int arr[], int n, int exp)
{
    int output[n];         // Output array to hold sorted values
    int i, count[10] = {0}; // Count array for digits 0-9 // Count array for digits 0-9

    // Store count of occurrences of each digit at position exp
    for (int i = 0; i < n; i++)
    {
        // Extract the digit at position exp: (arr[i] / exp) % 10
        count[(arr[i] / exp) % 10]++;
    }

    // Create cumulative count array to determine positions
    // count[i] now contains the position where digit i should end
    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    // Build the output array by placing elements at correct positions
    // Traverse from right to left to maintain stability
    for (int i = n - 1; i >= 0; i--)
    {
        // Place arr[i] at its correct position based on current digit
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        // Decrement count for this digit
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the sorted elements back to the original array
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }
}

// Main Radix Sort function that sorts array by processing each digit position
// Uses LSD (Least Significant Digit) approach: sorts from rightmost to leftmost digit
void radix_Sort(int arr[], int n)
{
    // Find the maximum number to determine number of digits
    int m = get_MAX(arr, n);

    // Process each digit position: 1s, 10s, 100s, etc.
    // exp represents the current digit position (1, 10, 100, ...)
    // Continue until we've processed all digits of the maximum number
    for (int exp = 1; m / exp > 0; exp *= 10)
    {
        // Sort array based on current digit position using counting sort
        Counting_Sort(arr, n, exp);
    }
}

// Program entry: build array, sort, display results, and clean up
int main()
{
    create();                    // Read input and allocate array
    radix_Sort(arr, n);          // Sort using radix sort algorithm
    
    // Output the sorted array
    printf("Sorted array:  \n\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    
    // Release allocated memory and avoid dangling pointer
    free(arr);
    arr = NULL;
    return 0;
}
