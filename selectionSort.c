//selection sort
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void print_array(int arr[], int N)
{
	int i;
	for(i=0; i<N; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


void selectionSort(int arr[], int N)
{
	int i, j, min_index;
	for(i=0; i<N-1; i++)
	{
		min_index = i;
		for(j=i+1; j<N; j++)
		{
			if(arr[j]<arr[min_index])
			{
				min_index = j;
			}
		}
		if(min_index!=i)
		{
			swap(&arr[min_index], &arr[i]);
		}
	}
}

int main(void)
{
	int arr[] = {2, 4, 223, 1, 34, 0, 112, 21, 11, 56, 22};
	int N; //the size of the array
	N = sizeof(arr)/sizeof(arr[0]);
	selectionSort(arr, N);
	print_array(arr, N);
	return 0;
}
