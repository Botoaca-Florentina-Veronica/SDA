// Heap Sort in C

#include <stdio.h>
// Function to swap the position of two elements

void swap(int* a, int* b)
{
	int temp;
    temp = *a;
	*a = *b;
	*b = temp;
}

// To heapify a subtree rooted with node i which is an index in arr[]. N is size of heap
void heapify(int arr[], int N, int i)
{
	// Find largest among root, left child and right child
	// Initialize largest as root
	int largest = i;
	int left = 2*i;
	int right = 2*i+1;

	// If left child is larger than root
	if (left<N && arr[left]>arr[largest])
    {
		largest = left;
    }
	// If right child is larger than largest so far
	if (right<N && arr[right]>arr[largest])
    {
		largest = right;
    }
	// Swap and continue heapifying if root is not largest
	// If largest is not root:
	if (largest != i) 
    {
        //aici practic ajung daca am gasit intre copii unul mai mare decat parintele, asa ca fac swap
    	swap(&arr[i], &arr[largest]);
		// Recursively heapify the affected sub-tree
		heapify(arr, N, largest);
	}
}

// Main function to do heap sort
/* sorts the given array of n size */
void heapSort(int arr[], int N)
{
    int i;
	// Build max heap
	for (i=N/2; i>=1; i--)
    {
        //aici practic merg la ultimul parinte al arborelui pentru a aplica heapify, dupa merg tot mai in sus
        //catre varful arborelui, pentru a analiza toti parintii
		heapify(arr, N, i);
    }
	// Heap sort
    // sort the max heap
	for (i=N; i>=1; i--) 
    {
        // Move the current root (maximum element) to the end
		swap(&arr[0], &arr[i]);
		//aici practic voi aplica heapify catre toate nodurile din arbore ramase
		heapify(arr, i, 0);
	}
}

void printArray(int arr[], int N)
{
    int i;
	for (i=0; i<N; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main()
{
	int arr[] = { 12, 11, 13, 5, 6, 7, 123, 134, 4, 54 };
	int N = sizeof(arr) / sizeof(arr[0]);
	heapSort(arr, N);
	printf("Sorted array is\n");
	printArray(arr, N);
}
