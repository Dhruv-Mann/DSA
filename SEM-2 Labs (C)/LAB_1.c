/*
 * LAB_1.c - Array Operations Program
 * This program demonstrates basic array operations using dynamic memory allocation.
 * Operations include: Create array, Display array, Insert element, Delete element.
 */

#include <stdio.h>
#include <stdlib.h>

// Global variables
int n;          // Number of elements in the array
int *arr;       // Pointer to the dynamically allocated array
// Function to create and initialize the array
void create()
{
    printf("Enter the number of elements of an array: ");
    scanf("%d", &n);
    
    if (n <= 0)
    {
        printf("Invalid number of elements!\n");
        n = 0;
        return;
    }
    
    arr = (int *)malloc(sizeof(int) * n);
    if (arr == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    printf("Enter %d elements of the array: ", n);
    // Loop to read n elements from user input
    // i starts at 0, continues while i < n, increments i each time
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
}

// Function to display the elements of the array
void display()
{
    if (n == 0)
    {
        printf("Array is empty!\n");
    }
    else
    {
        printf("Array elements: ");
        // Loop to print all elements of the array
        // i starts at 0, continues while i < n, increments i each time
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

// Function to insert an element at a specified position in the array
void Insert()
{
    int pos, elem;
    printf("Enter the position where you want to insert the element: ");
    scanf("%d", &pos);

    if (pos < 0 || pos > n)
    {
        printf("Invalid position!\n");
        return;
    }
    
    arr = (int *)realloc(arr, sizeof(int) * (n + 1));
    if (arr == NULL)
    {
        printf("Memory reallocation failed!\n");
        exit(1);
    }

    printf("Enter the element you want to add: ");
    scanf("%d", &elem);

    // Loop to shift elements to the right to make space for new element
    // i starts at n (last index), continues while i > pos, decrements i each time
    for (int i = n; i > pos; i--)
    {
        arr[i] = arr[i - 1];
    }

    arr[pos] = elem;
    n++;
    printf("Inserted successfully!\n");
}

// Function to delete an element at a specified position in the array
void delete()
{
    int pos;
    printf("Enter the position you want to delete the element at: ");
    scanf("%d", &pos);
    if (pos < 0 || pos >= n)
    {
        printf("Invalid position!\n");
        return;
    }
    
    // Loop to shift elements to the left to fill the gap after deletion
    // i starts at pos, continues while i < n-1, increments i each time
    for (int i = pos; i < n - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    
    n--;
    
    if (n > 0)
    {
        arr = (int *)realloc(arr, sizeof(int) * n);
        if (arr == NULL)
        {
            printf("Memory reallocation failed!\n");
            exit(1);
        }
    }
    else
    {
        free(arr);
        arr = NULL;
    }

    printf("Element successfully deleted!\n");
}
// Main function - entry point of the program
int main()
{
    int choice;

    do
    {
        printf("\n-------MENU-------\n");
        printf("1. Create an Array\n");
        printf("2. Display the Array\n");
        printf("3. Insert an Element\n");
        printf("4. Delete an Element\n");
        printf("5. Exit the Program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create();
            break;
        case 2:
            display();
            break;
        case 3:
            Insert();
            break;
        case 4:
            delete();
            break;
        case 5:
            printf("Exiting the program...\n");
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    // Continue the menu loop until user chooses to exit (choice != 5)
    } while (choice != 5);

    // Free allocated memory before exiting
    if (arr != NULL)
    {
        free(arr);
    }

    return 0;
}
