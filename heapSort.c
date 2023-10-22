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

void heapify(int arr[], int N, int i)
{
    int largest = i;
    int left = 2*i;
    int right = 2*i+1;

    if (left<N && arr[left]>arr[largest])
    {
	largest = left;
    }
    if (right<N && arr[right]>arr[largest])
    {
	largest = right;
    }
    if (largest != i) 
    {
        //aici practic ajung daca am gasit intre copii unul mai mare decat parintele, asa ca fac swap
    	swap(&arr[i], &arr[largest]);
	heapify(arr, N, largest);
	//aici cand apelez functia practic parcurg iar arborele la exact acelas nod, dar acum nu voi mai 
	//avea nevoie de swap fiindca deja am sortat nodurile corect, deci voi iesi din functie
     }
}

// Main function to do heap sort
/* sorts the given array of n size */
void heapSort(int arr[], int N)
{
    int i;
    // Build max heap
    for (i=N/2-1; i>=0; i--)
    {
	heapify(arr, N, i);
    }
    //aici cand ies din functie inseamna ca am sortat bine un singur parinte si copii lui
	
    //acum pentru a pune maximele sortate in vector:
    for (i=N-1; i>=0; i--) 
    {
	swap(&arr[0], &arr[i]);
	//aici practic fac schimb cu primul element din vector, fiindca folosind (Max)heapify mai sus, in varful arborelui
	//voi avea cel mai mare numar, deci il pozitionez la final si continui 
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
