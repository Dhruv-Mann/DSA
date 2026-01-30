// LAB_2.c - Implementation of Selection Sort and Insertion Sort
// This program allows users to input an array and sort it using either Selection Sort or Insertion Sort.
// It demonstrates basic sorting algorithms in C.

#include <stdio.h>
#include <stdlib.h>

// Function to swap two integers using pointers
void swap(int *x, int *y)
{

    int temp = *x;
    *x = *y;
    *y = temp;
}

// Function to perform Selection Sort on an array
// Selection Sort finds the minimum element in the unsorted portion and swaps it with the first unsorted element
void selection(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)  // Outer loop for each position in the array
    {
        int min_idx = i;  // Assume current position has the minimum
        for (j = i + 1; j < n; j++)  // Inner loop to find the actual minimum in the unsorted part
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);  // Swap the found minimum with the current position
    }
    printf("Sorted Array: \n\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to perform Insertion Sort on an array
// Insertion Sort builds the sorted array one element at a time by inserting each element into its correct position
void insertion(int arr[], int n)
{
    int i, j, key;
    for (i = 1; i < n; i++)  // Start from second element
    {
        key = arr[i];  // Element to be inserted
        j = i - 1;
        while (j >= 0 && arr[j] > key)  // Shift elements greater than key to the right
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;  // Insert the key at its correct position
    }
    printf("Sorted Array: \n\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Main function - Entry point of the program
// Takes user input for array size and elements, then provides a menu to choose sorting algorithm
int main()
{
    int n, i;
    int arr[100];
    printf("Enter the number of elements of array: ");
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("Inavlid array size. ");
        return 0;
    }
    printf("Enter the elements of the array: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int choice;

    // Menu-driven loop to allow user to choose sorting method or exit
    do
    {
        printf("Enter 1 to sort the array using Selection Sort. \n");
        printf("Enter 2 to sort the array using Insertion Sort. \n");
        printf("Enter 3 to exit the loop. \n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            selection(arr, n);
            break;
        case 2:
            insertion(arr, n);
            break;
        case 3:
            printf("Exiting the code...");
            break;

        default:
            printf("Invalid Choice.\n");
            break;
        }
    } while (choice != 3);

    
    return 0;
}
