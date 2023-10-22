i//insertion sort
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void print_array(int arr[], int N)
{
	int i;
	for(i=0; i<N; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void insertionSort(int arr[], int N)
{
	int i, j;
	for(i=1; i<N; i++)
	{
		int x = arr[i];
		j=i-1;
		while(j>=0 && arr[j] > x)
		{
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=x;   //adica sa inserez elementul x la pozitia sa de veci statatoare
	}
}

int main(void)
{
	int arr[]={3, 4, 56, 78, 9, 33, 1, 32, 144};
	int N; //the size of the array
	N = sizeof(arr)/sizeof(arr[0]);  //impart numarul de elemente din vectori*4(de la int) la unul 
	//singur*4(de la int) si imi mentin rezultatul sa fie de tip int
	insertionSort(arr, N);
	print_array(arr, N);
	return 0;
}
