/*
 * ==================== BUCKET SORT (FLOATS IN [0, 1)) ====================
 *
 * Overview:
 *  - Distributes input values into "buckets" based on value range
 *  - Sorts each bucket individually (here using a sorted linked list insert)
 *  - Concatenates buckets to produce the final sorted array
 *
 * Assumptions:
 *  - Input values are floats in the range [0.0, 1.0)
 *  - Number of buckets equals number of elements (n)
 *
 * Complexity:
 *  - Average Time: O(n) when data is uniformly distributed
 *  - Worst Time: O(n^2) if all elements land in one bucket
 *  - Space: O(n) auxiliary (buckets and nodes)
 *
 * Stability:
 *  - Depends on per-bucket insertion method; sorted insert maintains order
 *
 * Steps:
 *  1. Create n empty buckets
 *  2. Map each value x to bucket index bi = floor(n * x)
 *  3. Insert x into the bucket maintaining sorted order
 *  4. Concatenate buckets back into the array
 *
 * ------------------------------------------------------------------------
 * ALGORITHM (Exam-Style): Bucket_Sort(arr[], n)
 *
 * Step 1: Start
 *
 * Step 2: Create n empty buckets: bucket[0..n-1] ← NULL
 *
 * Step 3: For i ← 0 to n-1 do
 *           bi ← floor(n × arr[i])
 *           Insert arr[i] into bucket[bi] maintaining ascending order
 *
 * Step 4: index ← 0
 *
 * Step 5: For b ← 0 to n-1 do
 *           For each node x in bucket[b] from head to tail do
 *             arr[index] ← x
 *             index ← index + 1
 *
 * Step 6: Stop
 * ------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>

int n;
float *arr;
struct Node
{
    float data;
    struct Node *next;
};

// Reads array size, allocates memory, and loads elements (validated to [0.0, 1.0))
void create()
{
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("Invalid array size! ");
        exit(1);
    }
    arr = (float *)malloc(sizeof(float) * n);
    if (arr == NULL)
    {
        printf("Memory allocation failed! ");
        exit(1);
    }
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &arr[i]);
        // This implementation expects values in [0.0, 1.0);
        // adjust mapping or normalization if your data is outside this range.
        if (arr[i] < 0.0 || arr[i] >= 1.0) {
            printf("This bucket sort code only works for float values between 0.0 and 1.0!");
            exit(1);
        }
    }

    
}
// Inserts value x into a singly linked list pointed by head_ref, keeping it sorted in ascending order
void sorted_Insert(struct Node **head_ref, float x)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = x;
    new_node->next = NULL;

    if (*head_ref == NULL || (*head_ref)->data >= x)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        struct Node *current = *head_ref;
        while (current->next != NULL && current->next->data < x)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

// Performs Bucket Sort on arr[0..n-1]:
//  - Creates n buckets
//  - Maps each value x to bucket index bi = floor(n * x)
//  - Inserts into buckets using sorted insertion
//  - Flattens buckets back to the array and frees nodes
void Bucket_Sort(float arr[], int n)
{
    // Allocate an array of bucket heads (linked lists), initialized to NULL
    struct Node **buckets = (struct Node **)malloc(sizeof(struct Node *) * n);
    for (int i = 0; i < n; i++)
    {
        buckets[i] = NULL;
    }

    // Distribute input values into buckets based on their value
    for (int i = 0; i < n; i++)
    {
        int bi = n * arr[i]; // Index calculation: bi in [0, n-1] for x in [0,1)
        sorted_Insert(&buckets[bi], arr[i]);
    }

    // Concatenate buckets back into arr, freeing nodes as we go
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        struct Node *temp = buckets[i];
        while (temp != NULL)
        {
            arr[index++] = temp->data;
            struct Node *tofree = temp;
            temp = temp->next;
            free(tofree);
        }
    }
    free(buckets);
}

int main()
{
    create();                 // Read input and allocate array
    Bucket_Sort(arr, n);      // Sort using bucket sort

    printf("Sorted array: \n\n");
    for (int i = 0; i < n; i++)
    {
        printf("%.2f ", arr[i]); // Print with 2 decimal places
    }
    free(arr);               // Release allocated memory
    arr =NULL;               // Avoid dangling pointer
    return 0;
}
