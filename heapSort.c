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
    //heapify imi face practic doar o operatie, imi verifica copiii unui parinte, iar daca unul e mai mare decat acesta, face swap	
    int largest = i;  //la min heap voi avea smallest si in if-uri schimb din > in <
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

/* sorts the given array of n size */
void heapSort(int arr[], int N)
{
    int i;
    // Build max heap
    for (i=N/2-1; i>=0; i--)
    {
	heapify(arr, N, i);
	//de fiecare data cand am i--, ma voi apropia de varful arborelui, si ma voi asigura ca nodurile sunt sortate conform (max)heapify
    }
	
    //acum pentru a pune maximele sortate in vector:
    for (i=N-1; i>=0; i--) 
    {
	swap(&arr[0], &arr[i]);
	//aici practic fac schimb cu primul element din vector, fiindca folosind (Max)heapify mai sus, in varful arborelui
	//voi avea cel mai mare numar, deci il pozitionez la final si continui 
	    
	// la min heap voi avea practic acelasi cod, doar ca acum informatia aflata in varful arborelui binar este cel mai mic element
	//deci cand voi sterge elementul din varf si il voi pozitiona la finalul vectorului, in locul liber ramas, voi crea un sir descrescator
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
