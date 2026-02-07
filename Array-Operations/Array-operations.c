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
            printf("Element found at index: %d\n", i);
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
    printf("Enter the elements of the array: ");
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

// 16. Binary Search (requires sorted array)
void Binary_Search()
{
    if (n == 0)
    {
        printf("Array is empty! ");
        return;
    }
    int key, left = 0, right = n - 1, found = 0;
    printf("Enter the element to search: ");
    scanf("%d", &key);

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key)
        {
            printf("Element found at index: %d\n", mid);
            found = 1;
            break;
        }
        else if (arr[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    if (!found)
    {
        printf("Element not found in the array!\n");
    }
}

// 17. Find All Occurrences
void Find_All_Occurrences()
{
    if (n == 0)
    {
        printf("Array is empty! ");
        return;
    }
    int key, found = 0;
    printf("Enter the element to find all occurrences: ");
    scanf("%d", &key);
    printf("Element %d found at indices: ", key);
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            printf("%d ", i);
            found = 1;
        }
    }
    if (!found)
    {
        printf("Not found");
    }
    printf("\n");
}

// 18. Rotate Array Left
void Rotate_Left()
{
    if (n == 0)
    {
        printf("Array is empty! ");
        return;
    }
    int k;
    printf("Enter number of positions to rotate left: ");
    scanf("%d", &k);
    k = k % n; // Handle k > n
    if (k < 0)
        k = k + n;

    // Reverse first k elements
    for (int i = 0; i < k / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[k - 1 - i];
        arr[k - 1 - i] = temp;
    }
    // Reverse remaining elements
    for (int i = k; i < (n + k) / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[n - 1 - (i - k)];
        arr[n - 1 - (i - k)] = temp;
    }
    // Reverse entire array
    for (int i = 0; i < n / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }
    printf("Array rotated left by %d positions successfully!\n", k);
}

// 19. Rotate Array Right
void Rotate_Right()
{
    if (n == 0)
    {
        printf("Array is empty! ");
        return;
    }
    int k;
    printf("Enter number of positions to rotate right: ");
    scanf("%d", &k);
    k = k % n; // Handle k > n
    if (k < 0)
        k = k + n;

    // Reverse entire array
    for (int i = 0; i < n / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }
    // Reverse first k elements
    for (int i = 0; i < k / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[k - 1 - i];
        arr[k - 1 - i] = temp;
    }
    // Reverse remaining elements
    for (int i = k; i < (n + k) / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[n - 1 - (i - k)];
        arr[n - 1 - (i - k)] = temp;
    }
    printf("Array rotated right by %d positions successfully!\n", k);
}

// 20. Remove Duplicates
void Remove_Duplicates()
{
    if (n == 0)
    {
        printf("Array is empty! ");
        return;
    }
    int unique_count = 0;
    int *temp = (int *)malloc(sizeof(int) * n);
    if (temp == NULL)
    {
        printf("Memory allocation failed! ");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        int is_duplicate = 0;
        for (int j = 0; j < unique_count; j++)
        {
            if (arr[i] == temp[j])
            {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate)
        {
            temp[unique_count++] = arr[i];
        }
    }

    // Copy back to original array
    for (int i = 0; i < unique_count; i++)
    {
        arr[i] = temp[i];
    }
    free(temp);

    // Reallocate array
    int *new_arr = (int *)realloc(arr, sizeof(int) * unique_count);
    if (new_arr == NULL && unique_count > 0)
    {
        printf("Memory reallocation failed! ");
        return;
    }
    arr = new_arr;
    n = unique_count;
    printf("Duplicates removed successfully! New size: %d\n", n);
}

// 21. Find Second Largest
void Second_Largest()
{
    if (n < 2)
    {
        printf("Array must have at least 2 elements! ");
        return;
    }
    int first = arr[0], second = -2147483648; // INT_MIN
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > first)
        {
            second = first;
            first = arr[i];
        }
        else if (arr[i] > second && arr[i] != first)
        {
            second = arr[i];
        }
    }
    if (second == -2147483648)
    {
        printf("No second largest element exists (all elements are same)!\n");
    }
    else
    {
        printf("Second largest element: %d\n", second);
    }
}

// 22. Find Second Smallest
void Second_Smallest()
{
    if (n < 2)
    {
        printf("Array must have at least 2 elements! ");
        return;
    }
    int first = arr[0], second = 2147483647; // INT_MAX
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < first)
        {
            second = first;
            first = arr[i];
        }
        else if (arr[i] < second && arr[i] != first)
        {
            second = arr[i];
        }
    }
    if (second == 2147483647)
    {
        printf("No second smallest element exists (all elements are same)!\n");
    }
    else
    {
        printf("Second smallest element: %d\n", second);
    }
}

// 23. Check if Array is Sorted
void Check_Sorted()
{
    if (n == 0)
    {
        printf("Array is empty! ");
        return;
    }
    int ascending = 1, descending = 1;
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
            ascending = 0;
        if (arr[i] < arr[i + 1])
            descending = 0;
    }
    if (ascending)
        printf("Array is sorted in ascending order.\n");
    else if (descending)
        printf("Array is sorted in descending order.\n");
    else
        printf("Array is not sorted.\n");
}

// 24. Frequency Count
void Frequency_Count()
{
    if (n == 0)
    {
        printf("Array is empty! ");
        return;
    }
    int *visited = (int *)calloc(n, sizeof(int));
    if (visited == NULL)
    {
        printf("Memory allocation failed! ");
        return;
    }

    printf("Element Frequency:\n");
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 1)
            continue;
        int count = 1;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
                visited[j] = 1;
            }
        }
        printf("%d -> %d times\n", arr[i], count);
    }
    free(visited);
}

// 25. Find Missing Number (1 to n+1 sequence)
void Find_Missing_Number()
{
    if (n == 0)
    {
        printf("Array is empty! ");
        return;
    }
    printf("Note: This assumes array contains numbers from 1 to n+1 with one missing.\n");
    int expected_sum = ((n + 1) * (n + 2)) / 2;
    int actual_sum = 0;
    for (int i = 0; i < n; i++)
    {
        actual_sum += arr[i];
    }
    int missing = expected_sum - actual_sum;
    printf("Missing number: %d\n", missing);
}

// 26. Find All Duplicates
void Find_Duplicates()
{
    if (n == 0)
    {
        printf("Array is empty! ");
        return;
    }
    int *visited = (int *)calloc(n, sizeof(int));
    if (visited == NULL)
    {
        printf("Memory allocation failed! ");
        return;
    }

    int found = 0;
    printf("Duplicate elements: ");
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 1)
            continue;
        int count = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
                visited[j] = 1;
            }
        }
        if (count > 0)
        {
            printf("%d ", arr[i]);
            found = 1;
        }
    }
    if (!found)
    {
        printf("None");
    }
    printf("\n");
    free(visited);
}

// 27. Product of Elements
void Product()
{
    if (n == 0)
    {
        printf("Array is empty! ");
        return;
    }
    long long product = 1;
    for (int i = 0; i < n; i++)
    {
        product *= arr[i];
    }
    printf("Product of all elements: %lld\n", product);
}

// 28. Find Median
void Find_Median()
{
    if (n == 0)
    {
        printf("Array is empty! ");
        return;
    }
    // First sort the array (create a copy to not modify original)
    int *temp = (int *)malloc(sizeof(int) * n);
    if (temp == NULL)
    {
        printf("Memory allocation failed! ");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        temp[i] = arr[i];
    }

    // Bubble sort the copy
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (temp[j] > temp[j + 1])
            {
                int swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    float median;
    if (n % 2 == 0)
    {
        median = (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    }
    else
    {
        median = temp[n / 2];
    }
    printf("Median of the array: %.2f\n", median);
    free(temp);
}

// 29. Standard Deviation
void Standard_Deviation()
{
    if (n == 0)
    {
        printf("Array is empty! ");
        return;
    }
    // Calculate mean
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    float mean = sum / n;

    // Calculate variance
    float variance = 0;
    for (int i = 0; i < n; i++)
    {
        variance += (arr[i] - mean) * (arr[i] - mean);
    }
    variance /= n;

    // Standard deviation is square root of variance
    float std_dev = 0;
    // Simple square root calculation
    if (variance > 0)
    {
        float x = variance;
        float y = 1;
        float e = 0.000001; // Precision
        while (x - y > e)
        {
            x = (x + y) / 2;
            y = variance / x;
        }
        std_dev = x;
    }
    printf("Standard Deviation: %.2f\n", std_dev);
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n============== ARRAY OPERATIONS MENU ==============\n");
        printf("--- BASIC OPERATIONS ---\n");
        printf("1.  Create/Initialize Array\n");
        printf("2.  Traverse/Display Array\n");
        printf("3.  Insert Element\n");
        printf("4.  Delete Element\n");
        printf("5.  Search Element (Linear)\n");
        printf("6.  Update/Modify Element\n");
        printf("\n--- SORTING & SEARCHING ---\n");
        printf("7.  Sort Array (Bubble Sort)\n");
        printf("16. Binary Search (Sorted Array)\n");
        printf("17. Find All Occurrences\n");
        printf("\n--- ARRAY MANIPULATION ---\n");
        printf("8.  Merge Two Arrays\n");
        printf("9.  Copy Array\n");
        printf("10. Reverse Array\n");
        printf("18. Rotate Array Left\n");
        printf("19. Rotate Array Right\n");
        printf("20. Remove Duplicates\n");
        printf("\n--- STATISTICAL OPERATIONS ---\n");
        printf("11. Count Elements\n");
        printf("12. Find Minimum Element\n");
        printf("13. Find Maximum Element\n");
        printf("14. Sum of Elements\n");
        printf("15. Average of Elements\n");
        printf("21. Find Second Largest\n");
        printf("22. Find Second Smallest\n");
        printf("27. Product of Elements\n");
        printf("28. Find Median\n");
        printf("29. Standard Deviation\n");
        printf("\n--- ANALYSIS OPERATIONS ---\n");
        printf("23. Check if Array is Sorted\n");
        printf("24. Frequency Count\n");
        printf("25. Find Missing Number\n");
        printf("26. Find All Duplicates\n");
        printf("\n0.  Exit\n");
        printf("===================================================\n");
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
        case 16:
            Binary_Search();
            break;
        case 17:
            Find_All_Occurrences();
            break;
        case 18:
            Rotate_Left();
            break;
        case 19:
            Rotate_Right();
            break;
        case 20:
            Remove_Duplicates();
            break;
        case 21:
            Second_Largest();
            break;
        case 22:
            Second_Smallest();
            break;
        case 23:
            Check_Sorted();
            break;
        case 24:
            Frequency_Count();
            break;
        case 25:
            Find_Missing_Number();
            break;
        case 26:
            Find_Duplicates();
            break;
        case 27:
            Product();
            break;
        case 28:
            Find_Median();
            break;
        case 29:
            Standard_Deviation();
            break;
        case 0:
            printf("\nExiting program... Thank you!\n");
            if (arr != NULL)
            {
                free(arr);
            }
            exit(0);
        default:
            printf("\nInvalid choice! Please enter a valid option.\n");
        }
        printf("\n");
    }

    return 0;
}