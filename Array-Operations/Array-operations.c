#include <stdio.h>
#include <stdlib.h>

int n;
int *arr = NULL;

// 1. Creation / Declaration and Initialization
void create()
{
    if (arr != NULL)
    {
        free(arr);
        arr = NULL;
    }
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("Invalid Size! ");
        exit(1);
    }
    arr = (int *)malloc(sizeof(int) * n);
    if (arr == NULL)
    {
        printf("Memory Allocation failed! ");
        exit(1);
    }
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
}

// 2. Traversal and Display
void Traverse()
{
    if (n == 0)
    {
        printf("Array is Empty! ");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 3. Insertion
void Insert()
{
    int elem, pos;
    printf("Enter the position you want to add the element at: ");
    scanf("%d", &pos);
    if (pos < 0 || pos > n)
    {
        printf("Invalid Position! ");
        return;
    }
    int *temp = (int *)realloc(arr, sizeof(int) * (n + 1));
    if (temp == NULL)
    {
        printf("Memory Reallocation failed! ");
        return;
    }
    arr = temp;

    printf("Enter the element you want to insert: ");
    scanf("%d", &elem);

    for (int i = n; i > pos; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[pos] = elem;
    n++;
    printf("Element inserted successfully!\n");
}

// 4. Deletion
void Delete()
{
    if (n == 0)
    {
        printf("Array is empty!");
        return;
    }
    int pos;
    printf("Enter the position you want to delete the element at: ");
    scanf("%d", &pos);
    if (pos < 0 || pos >= n)
    {
        printf("Invalid position! ");
        return;
    }
    for (int i = pos; i < n - 1; i++)
    {
        arr[i] = arr[i + 1];
    }

    if (n - 1 == 0)
    {
        free(arr);
        arr = NULL;
        n = 0;
    }
    else
    {
        int *temp = (int *)realloc(arr, sizeof(int) * (n - 1));
        if (temp == NULL)
        {
            printf("Memory Reallocation failed! ");
            return;
        }
        arr = temp;
        n--;
    }
    printf("Element successfully deleted!\n");
}

// 5. Searching
void Search()
{
    int key;
    int found = 0;
    if (n == 0)
    {
        printf("Array is empty! ");
        return;
    }
    printf("Enter the element you want to find in the array: ");
    scanf("%d", &key);
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            printf("Elenement found at index: %d\n", i);
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        printf("Element not found in the Array!\n");
    }
}

// 6. Updating/Modification
void Update()
{
    if (n == 0)
    {
        printf("Array is empty! ");
        return;
    }
    int index, element;

    printf("Enter the position where you want to change the element: ");
    scanf("%d", &index);
    if (index < 0 || index >= n)
    {
        printf("Invalid position! ");
        return;
    }
    printf("Enter the new element: ");
    scanf("%d", &element);
    arr[index] = element;

    printf("Element updated successfully!\n");
}

// 7. Sorting
void Bubble_Sort()
{
    if (n == 0)
    {
        printf("Array is empty! ");
        return;
    }
    int temp;
    for (int i = 0; i < n; i++)
    {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0)
        {
            break;
        }
    }
    printf("Array sorted successfully!\n");
}

// 8. Merging
void Merge()
{
    if (n == 0)
    {
        printf("First array is empty! Create it first! ");
        return;
    }
    int n2;
    printf("Enter the size of the second array: ");
    scanf("%d", &n2);
    if (n2 <= 0)
    {
        printf("Invalid Array Size! ");
        return;
    }
    int *arr2 = (int *)malloc(sizeof(int) * n2);
    if (arr2 == NULL)
    {
        printf("Memory allocation for the second array failed! ");
        return;
    }
    printf("Enter the element of the array: ");
    for (int i = 0; i < n2; i++)
    {
        scanf("%d", &arr2[i]);
    }
    int *temp = (int *)realloc(arr, sizeof(int) * (n + n2));
    if (temp == NULL)
    {
        printf("Memory Reallocation failed");
        free(arr2);
        return;
    }
    arr = temp;
    for (int i = 0; i < n2; i++)
    {
        arr[n + i] = arr2[i];
    }
    n = n + n2;
    free(arr2);
    printf("Arrays merged successfully!\n");
}

// 9. Copying
void Copy()
{
    if (n == 0)
    {
        printf("Empty Array cannot be copied! ");
        return;
    }
    int *arr2 = (int *)malloc(sizeof(int) * n);
    if (arr2 == NULL)
    {
        printf("Memory allocation failed! ");
        ;
        return;
    }

    for (int i = 0; i < n; i++)
    {
        arr2[i] = arr[i];
    }
    printf("Array copied successfully! Here is the copy:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr2[i]);
    }
    printf("\n");
    free(arr2);
}

// 10. Reversing
void Reverse()
{
    if (n == 0)
    {
        printf("Empty Array cannot be reversed! ");
        return;
    }
    int start = 0;
    int end = n - 1;
    int temp;
    while (start < end)
    {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
    printf("Array reversed successfully!\n");
}

// 11. Counting Elements
void Counting_Elements()
{
    if (n == 0)
    {
        printf("List is empty! ");
        return;
    }
    printf("Total number of elements in the Array: %d\n", n); // O(1)
    // int count = 0;
    // for(int i = 0; i <n; i++){
    //     count++;
    // }
    // printf("Total number of elements in the array are: %d" , count);  //O(n)
}
// 12. Finding Minimum Element
void Minimum()
{
    if (n == 0)
    {
        printf("List is empty! ");
        return;
    }
    int min = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    printf("Minimum element in the array is: %d\n", min);
}

// 13. Finding Maximum Element
void Maximum()
{
    if (n == 0)
    {
        printf("List is empty! ");
        return;
    }
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    printf("Maximum element in the array is: %d\n", max);
}

// 14. Sum of Elements
void Sum()
{
    if (n == 0)
    {
        printf("List is Empty! ");
        return;
    }
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    printf("Sum of all the elements in the array: %d\n", sum);
}

// 15. Average of Elements
void Average()
{
    if (n == 0)
    {
        printf("List is empty! ");
        return;
    }
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    printf("The Average of the elements in the array is: %.2f\n", (float)sum / n);
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n========== ARRAY OPERATIONS MENU ==========\n");
        printf("1.  Create/Initialize Array\n");
        printf("2.  Traverse/Display Array\n");
        printf("3.  Insert Element\n");
        printf("4.  Delete Element\n");
        printf("5.  Search Element\n");
        printf("6.  Update/Modify Element\n");
        printf("7.  Sort Array (Bubble Sort)\n");
        printf("8.  Merge Two Arrays\n");
        printf("9.  Copy Array\n");
        printf("10. Reverse Array\n");
        printf("11. Count Elements\n");
        printf("12. Find Minimum Element\n");
        printf("13. Find Maximum Element\n");
        printf("14. Sum of Elements\n");
        printf("15. Average of Elements\n");
        printf("0.  Exit\n");
        printf("===========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create();
            break;
        case 2:
            Traverse();
            break;
        case 3:
            Insert();
            break;
        case 4:
            Delete();
            break;
        case 5:
            Search();
            break;
        case 6:
            Update();
            break;
        case 7:
            Bubble_Sort();
            break;
        case 8:
            Merge();
            break;
        case 9:
            Copy();
            break;
        case 10:
            Reverse();
            break;
        case 11:
            Counting_Elements();
            break;
        case 12:
            Minimum();
            break;
        case 13:
            Maximum();
            break;
        case 14:
            Sum();
            break;
        case 15:
            Average();
            break;
        case 0:
            printf("\nExiting program... Thank you!\n");
            if (arr != NULL)
            {
                free(arr);
            }
            exit(0);
        default:
            printf("\nInvalid choice! Please enter a number between 0 and 15.\n");
        }
        printf("\n");
    }

    return 0;
}