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
        printf("Invalid Postion! ");
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
    printf("Element inserted successfuly! ");
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
    printf("Enter the postion you want to delete the element at: ");
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
     if (n - 1 == 0) {
        free(arr);
        arr = NULL;
        n = 0;
    }else{
    int *temp = (int *)realloc(arr, sizeof(int) * (n - 1));
    if (temp == NULL)
    {
        printf("Memory Reallocation failed! ");
        return;
    }
    arr = temp;
    n--;
}

    printf("Element successfully deleted! ");
}

// 5. Searching
void Search()
{
    int key;
    int found = 0;
    if (n == 0)
    {
        printf("Element is empty! ");
        return;
    }
    printf("Enter the element you want to find in the array: ");
    scanf("%d", &key);
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            printf("Array found at the index: %d", i);
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        printf("Element not found in the Array! ");
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

    printf("Enter the postion where you want to change the element: ");
    scanf("%d", &index);
    if (index < 0 || index >= n)
    {
        printf("Invalid position! ");
        return;
    }
    printf("Enter the new element: ");
    scanf("%d", &element);
    arr[index] = element;

    printf("Element updated successfully! ");
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
    printf("Array sorted successfully! ");
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
    int* temp = (int*)realloc(arr, sizeof(int) * (n + n2));
    if (temp == NULL)
    {
        printf("Memory Reallocation failed");
        return;
    }
    arr = temp;
    for (int i = 0; i < n2; i++)
    {
        arr[n + i] = arr2[i];
    }
    n = n + n2;
    free(arr2);
}