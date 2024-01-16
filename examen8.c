/*
Fie un tablou de elemente care a căror valori sunt numere întregi, pozitive sau negative.
Să se aleagă și să se modifice unul din algoritmii de sortare studiaţi, astfel încât:
- valorile negative vor fi aduse la începutul tabloului (rezultatul va fi un tablou cu toate elementele negative la început, și toate elementele pozitive la sfârşit)
- valorile pozitive vor fi sortate crescător
Algoritmul modificat trebuie sa fie cât mai eficient.
Motivați alegerea algoritmului.
Exemplificați funcționearea algoritmului pe un tablou de 6 elemente.
Nota:
Algoritmul poate fi scris in pseudocod (C like).
Este obligatorie comentarea algoritmului si specificarea complexitatii acestuia in termeni de O(f(n)), comentarea structurilor de date alese, precum si justificarea alegerii acestora.
Este obligatorie exemplificarea efectului apelului functiilor implementate pe un exemplu ales.*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void quicksort(int a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	int pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (a[stanga] < pivot)
		{
			stanga++;
		}
		while (pivot < a[dreapta])
		{
			dreapta--;
		}
		if (stanga < dreapta)
		{
			swap(&a[stanga++], &a[dreapta--]);
		}
		else
		{
			stanga++;
		}
	}
	//mutare pivot la locul sau final
	swap(&a[dreapta], &a[prim]);
	//apelurile recursive
	if (prim < dreapta - 1)
	{
		quicksort(a, prim, dreapta - 1);
	}
	if (dreapta + 1 < ultim)
	{
		quicksort(a, dreapta + 1, ultim);
	}
}

void afisareTablou(int arr[], int N)
{
	int i;
	for (i = 0; i < N; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main(void)
{
	int tablou[] = { 12, 3, 5, -8, 1234, -45, 29, -65 };
	int N;
	N = sizeof(tablou) / sizeof(tablou[0]);
	printf("Afisare tablou initial:\n");
	afisareTablou(tablou, N);

	printf("Afisare tablou ordonat crescator:\n");
	quicksort(tablou, 0, N - 1);
	afisareTablou(tablou, N);
	//Complexitatea medie a cazului pentru QuickSort este O(n log n), unde n este numărul de elemente din tablou.
	return 0;
}
