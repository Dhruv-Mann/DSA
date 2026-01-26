/*
 * ==================== INSERTION SORT ALGORITHM ====================
 * 
 * ALGORITHM: Insertion_Sort(arr[], n)
 * 
 * Step 1: Start
 * 
 * Step 2: Initialize outer loop counter i = 1
 *         (Start from second element, as single element is already sorted)
 * 
 * Step 3: Repeat Steps 4 to 10 while i < n
 * 
 * Step 4: Set key = arr[i]
 *         (Store current element to be inserted at correct position)
 * 
 * Step 5: Set j = i - 1
 *         (Start comparing with elements in the sorted portion)
 * 
 * Step 6: Repeat Steps 7 to 8 while j >= 0 AND arr[j] > key
 * 
 * Step 7: Set arr[j+1] = arr[j]
 *         (Shift larger element one position to the right)
 * 
 * Step 8: Decrement j by 1 (j = j - 1)
 * 
 * Step 9: Set arr[j+1] = key
 *         (Insert the key at its correct position in sorted portion)
 * 
 * Step 10: Increment i by 1
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
 *  - Adaptive (efficient for nearly sorted arrays)
 *  - Stable sorting algorithm
 *  - Online algorithm (can sort data as it receives it)
 *  - Best for small datasets or nearly sorted arrays
 *  - More efficient than Bubble Sort and Selection Sort in practice
 * 
 * HOW IT WORKS:
 *  - Divides array into sorted and unsorted portions
 *  - Initially, first element is considered sorted
 *  - Picks elements one by one from unsorted portion
 *  - Inserts each element at its correct position in sorted portion
 *  - Shifts larger elements to the right to make space
 *  - Similar to sorting playing cards in your hand
 * 
 * ==================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// Global variables shared across functions
int n;      // Size of the array
int *arr;   // Pointer to dynamically allocated array

// Reads input size, validates, allocates array, and loads elements
void create(){
    // Read desired array size
    printf("Enter the number of elements of the array: ");
    scanf("%d" , &n);
    
    // Validate size to avoid invalid/negative lengths
    if(n<=0){
        printf("Inavlid array size! \n");
        exit(1);
    }
    
    // Allocate contiguous memory for n integers
    arr = (int *)malloc(sizeof(int) * n);
    
    // Handle allocation failure gracefully
    if(arr==NULL){
        printf("Memory allocaion failed! \n");
        exit(1);
    }
    
    // Read n elements into the array
    printf("Enter the elements of the array: ");
    for(int i = 0; i < n ; i ++){
        scanf("%d" , &arr[i]);
    }
}

// Sorts the array in ascending order using Insertion Sort
void Insertion_Sort(int arr[] , int n){
    // Start from second element (index 1) as first element is already sorted
    for(int i = 1; i < n ; i++){
        // Store current element to be inserted
        int key = arr[i];
        
        // Start comparing with elements in sorted portion (left side)
        int j = i-1;
        
        // Shift elements greater than key one position to the right
        while( j>=0 && arr[j] > key){
            arr[j+1] = arr[j];  // Shift element to the right
            j=j-1;              // Move to the previous element
        }
        
        // Insert key at its correct position in the sorted portion
        arr[j+1] = key;
        
    }
}

// Program entry: build array, sort, display results, and clean up
int main(){
    create();                    // Read input and allocate array
    Insertion_Sort(arr , n);     // Sort in ascending order

    // Output the sorted array
    for(int i = 0 ; i  < n ; i ++){
        printf("%d " , arr[i]);
    }
    
    // Release allocated memory and avoid dangling pointer
    free(arr);
    arr =NULL;
    return 0;
}