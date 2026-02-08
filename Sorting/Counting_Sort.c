/*
 * ==================== COUNTING SORT ALGORITHM ====================
 * 
 * ALGORITHM: Counting_Sort(arr[], n)
 * 
 * Step 1: Start
 * 
 * Step 2: Find the maximum element (maxval) in the array arr[]
 *         Initialize maxval = 0
 *         For i = 0 to n-1
 *           If arr[i] > maxval, then maxval = arr[i]
 * 
 * Step 3: Create a count array Cnt_Array of size (maxval + 1)
 *         Initialize all elements of Cnt_Array to 0
 * 
 * Step 4: Store the count of each element in Cnt_Array
 *         For i = 0 to n-1
 *           Increment Cnt_Array[arr[i]] by 1
 *         (Now Cnt_Array[i] contains frequency of element i)
 * 
 * Step 5: Create cumulative count array
 *         For i = 1 to maxval
 *           Cnt_Array[i] = Cnt_Array[i] + Cnt_Array[i-1]
 *         (Now Cnt_Array[i] contains number of elements <= i)
 * 
 * Step 6: Create output array ans[] of size n
 * 
 * Step 7: Build the output array by placing elements at correct positions
 *         For i = n-1 down to 0 (traverse from right to left)
 *           ans[Cnt_Array[arr[i]] - 1] = arr[i]
 *           Decrement Cnt_Array[arr[i]] by 1
 *         (Traversing backwards maintains stability)
 * 
 * Step 8: Copy the sorted elements from ans[] back to arr[]
 *         For i = 0 to n-1
 *           arr[i] = ans[i]
 * 
 * Step 9: Array is now sorted in ascending order
 * 
 * Step 10: Stop
 * 
 * ==================================================================
 * 
 * COMPLEXITY ANALYSIS:
 *  - Time Complexity: O(n + k) where:
 *      n = number of elements in the array
 *      k = range of input values (maximum element)
 *      Best, Average, Worst Case: All O(n + k)
 *  - Space Complexity: O(n + k) for count and output arrays
 *  - Stability: Stable (equal elements maintain relative order)
 *  - Not comparison-based sorting
 * 
 * CHARACTERISTICS:
 *  - Non-comparison based sorting algorithm
 *  - Stable sorting algorithm
 *  - Not in-place (requires extra space)
 *  - Linear time complexity when k = O(n)
 *  - Efficient when range of values is not significantly larger than n
 *  - Works best with non-negative integers
 *  - Used as subroutine in Radix Sort
 * 
 * WHEN TO USE:
 *  - When elements are in a limited range (k is not too large)
 *  - When you need a stable sort
 *  - When working with non-negative integers
 *  - When linear time complexity is required
 * 
 * LIMITATIONS:
 *  - Not suitable when range (k) is much larger than n
 *  - Requires extra space proportional to range
 *  - Only works efficiently with integers or discrete values
 *  - Cannot handle negative numbers without modification
 * 
 * HOW IT WORKS:
 *  - Counts frequency of each distinct element
 *  - Calculates cumulative positions for each element
 *  - Places elements directly at their sorted positions
 *  - No comparisons needed between elements
 * 
 * ==================================================================
 */

// Counting Sort Implementation
// Time Complexity: O(n + k) where n is number of elements and k is the range of input
// Space Complexity: O(k)

#include <stdio.h>
#include <stdlib.h>

int n;           // Global variable to store the size of the array
int *arr;        // Global pointer to store the dynamically allocated array

// Function to take input from user and create the array
void create()
{
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    
    // Validate that array size is positive
    if (n <= 0)
    {
        printf("Invalid array size!");
        exit(1);
    }
    
    // Dynamically allocate memory for the array
    arr = (int *)malloc(sizeof(int) * n);
    
    // Check if memory allocation was successful
    if (arr == NULL)
    {
        printf("Memory allocation failed!");
        exit(1);
    }
    
    // Take array elements as input from user
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
}


// Counting Sort Function
// This function sorts the array in ascending order using the counting sort algorithm
void Counting_Sort(int arr[], int n)
{
    // Find the maximum element in the array
    int maxval = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > maxval)
        {
            maxval = arr[i];
        }
    }

    // Create a count array with size = maxval + 1 and initialize all values to 0
    int *Cnt_Array = (int *)calloc(maxval + 1, sizeof(int));
    
    // Check if memory allocation was successful
    if (Cnt_Array == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Store the count of each element (frequency array)
    for (int i = 0; i < n; i++)
    {
        Cnt_Array[arr[i]]++;
    }

    // Create cumulative count array to determine positions of elements
    // This tells us how many elements are <= each value
    for (int i = 1; i <= maxval; i++)
    {
        Cnt_Array[i] += Cnt_Array[i - 1];
    }

    // Create output array to store sorted elements
    int *ans = (int *)malloc(sizeof(int) * n);
    
    // Check if memory allocation was successful
    if (ans == NULL)
    {
        free(Cnt_Array);  // Clean up previously allocated memory
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    // Place elements in output array at correct sorted positions
    // Traverse from right to left to maintain stability
    for (int i = n - 1; i >= 0; i--)
    {
        // Place arr[i] at its correct position
        ans[Cnt_Array[arr[i]] - 1] = arr[i];
        // Decrement count for this element
        Cnt_Array[arr[i]]--;
    }

    // Copy sorted elements back to original array
    for (int i = 0; i < n; i++)
    {
        arr[i] = ans[i];
    }
    
    // Free allocated memory to prevent memory leaks
    free(Cnt_Array);
    free(ans);
}


// Main function
int main()
{
    // Take array input from user
    create();
    
    // Sort the array using counting sort algorithm
    Counting_Sort(arr, n);
    
    // Print the sorted array
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    // Free the allocated memory and avoid memory leaks
    free(arr);
    arr = NULL;
    
    return 0;
}