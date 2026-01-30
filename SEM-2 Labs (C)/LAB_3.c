/*
 * LAB_3.C - Binary Search with Bubble Sort
 * This program demonstrates binary search on a sorted array.
 * The array is first sorted using bubble sort, then binary search is performed.
 */

#include <stdio.h>

// Function to swap two integers using pointers
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Function to perform Bubble Sort on an array
// Bubble Sort repeatedly swaps adjacent elements if they are in wrong order
void Bubble_Sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Function to perform Binary Search on a sorted array
// Binary Search divides the search interval in half repeatedly
// Returns the index of the key if found, otherwise returns -1
int Binary_Search(int arr[], int n, int key)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
        {
            return mid;
        }

        if (arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

// Main function - Entry point of the program
int main()
{
    int n, key;
    int arr[100];

    printf("Enter the number of elements of the array: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100)
    {
        printf("Invalid array size. Please enter a value between 1 and 100.\n");
        return 1;
    }

    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the element you want to search: ");
    scanf("%d", &key);

    // Sort the array using Bubble Sort
    Bubble_Sort(arr, n);

    // Display the sorted array
    printf("\nSorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Perform Binary Search
    int result = Binary_Search(arr, n, key);

    if (result == -1)
    {
        printf("\nElement not found in the array!\n");
    }
    else
    {
        printf("\nElement found at index: %d\n", result);
    }

    return 0;
}