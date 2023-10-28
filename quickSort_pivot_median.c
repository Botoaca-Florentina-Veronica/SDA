// Online C compiler to run C program online
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int findPivotmedian(int arr[], int low, int high)
{
    int mid = (low + high)/2;
    
    if(arr[low]>arr[mid])
    {
        swap(&arr[low], &arr[mid]);
    }
    
    if(arr[low]>arr[high])
    {
        swap(&arr[low], &arr[high]);
    }
    
    if(arr[mid]>arr[high])
    {
        swap(&arr[mid], &arr[high]);
    }
    
    return mid;
}

int partition(int arr[], int low, int high)
{
    int i, j, pivot;
    pivot = findPivotmedian(arr, low, high);
    i=low;
    j=high;
    
    while(i<j)
    {
        do{
            i++;
        }while(arr[i]<=arr[pivot]);
        
        do{
            j--;
        }while(arr[j]>arr[pivot]);
        
        if(i>j)
        {
            return j;
        }
        swap(&arr[i], &arr[j]);
    }
    swap(&arr[pivot], &arr[j]);
    return j;
}

void QuickSort(int arr[], int low, int high)
{
    int j;
    if(low<high)
    {
        j= partition(arr, low, high);
        QuickSort(arr,low, j);
        QuickSort(arr, j+1, high);
    }
}


void print_array(int arr[], int N)
{
    int i;
    for(i=0; i<N; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) 
{
    int arr[]={12, 93, 4, 5, 2, 1, 0};
    int N = sizeof(arr)/sizeof(arr[0]);
    QuickSort(arr, 0, N-1);
    print_array(arr, N);
    return 0;
}
















