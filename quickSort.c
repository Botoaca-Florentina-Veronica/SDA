//Quick Sort
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void swap(int *a, int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
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

int partition(int arr[], int low, int high)
{
	int pivot = arr[low];
	int i, j;
	i=low;
	j=high;
	while(i<j)
	{
		do
		{
			i++;
		}while(arr[i]<=pivot);

		do
		{
			j--;
		} while (arr[j]>pivot);
		if(i<j)
		{
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[low], &arr[j]);
	return j;
}

void QuickSort(int arr[], int low, int high)
{
	int j;
	if(low<high)
	{
		j=partition(arr, low, high);
		QuickSort(arr, low, j);
		QuickSort(arr, j+1, high);
	}
}


int main(void)
{
	int arr[]={4, 67, 8, 9, 2 ,35, 3, 1, 32 ,45, 5};
	int N=sizeof(arr)/sizeof(arr[0]);
	QuickSort(arr, 0, N);
	print_array(arr, N);
	return 0;
}
