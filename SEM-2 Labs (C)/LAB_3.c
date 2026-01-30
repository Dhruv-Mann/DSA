#include <stdio.h>
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void Bubble_Sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i -1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int Binary_Search(int arr[], int n, int key)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {

        int mid = low + (high - low )/2;

        if (arr[mid] == key)
        {
            return mid;
        }

        else if (arr[mid] < key)
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

int main()
{
    int n, key;
    int arr[100];

    printf("Enter the number elements of the array: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invlid array size. ");
        return 0;
    }

    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the element you want to search: ");
    scanf("%d" , &key);

    Bubble_Sort(arr , n);


    int result = Binary_Search(arr , n ,key );

    if(result == -1){
        printf("Element not found at in the array!");
    }else{
    printf("Element found at the index : %d" , result);

    }
    return 0;

}