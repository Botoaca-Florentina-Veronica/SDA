/*﻿
   Fie un tablou de structuri de forma struct agenda{char nume[25]; char telefon[10];int an; int venit}. 
   Ştiind ca tabloul are dimensiunea N, sa se implementeze cate o funcție pentru:
a. Mutarea pe ultimele poziții din vector a primelor două persoane cu un venit mai mic de 1000.
b. Sortarea eficientă, în ordine alfabetică a numelor, a persoanelor cu vârsta între 30 şi 40 de ani.
Sa se considere un exemplu de tablou cu minim 5 astfel de agende și sa se exemplifice cum va arata tabloul dupa apelul fiecareia din functiile de mai
sus.
Nota:
Algoritmul poate fi scris in pseudocod (C like).
Este obligatorie comentarea algoritmului si specificarea complexitatii acestuia in termeni de O(f(n)), 
comentarea structurilor de date alese, precum si justificarea alegerii acestora.
Este obligatorie exemplificarea efectului apelului functiilor implementate pe un exemplu ales.
*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct agenda
{
	char nume[25];
	char telefon[10];
	int an;
	int venit;
}agenda;

//swap special pentru quicksort
void swap(agenda agende[], int low, int high)
{
    agenda temp;
    temp = agende[low];
    agende[low] = agende[high];
    agende[high] = temp;
}

int findPivotmedian(agenda agende[], int low, int high)
{
    int mid = (low + high) / 2;
    
    if (strcmp(agende[low].nume, agende[mid].nume) > 0)
    {
        swap(agende, low, mid);
    }
    
    if (strcmp(agende[low].nume, agende[high].nume) > 0)
    {
        swap(agende, low, high);
    }
    
    if (strcmp(agende[mid].nume, agende[high].nume) > 0)
    {
        swap(agende, mid, high);
    }
    
    return mid;
}

int partition(agenda agende[], int low, int high)
{
    int i, j, pivot;
    i = low;
    j = high;
    pivot = findPivotmedian(agende, low, high);

    while (i < j)
    {
        do {
            i++;
        } while (strcmp(agende[i].nume, agende[pivot].nume) < 0);

        do {
            j--;
        } while (strcmp(agende[j].nume, agende[pivot].nume) > 0);

        if (i < j)
        {
            swap(agende, i, j);
        }
    }
    swap(agende, pivot, j);
    return j;
}

void QuickSort(agenda agende[], int low, int high)
{
    int j;
    if (low < high)
    {
        j = partition(agende, low, high);
        QuickSort(agende, low, j);
        QuickSort(agende, j + 1, high);
    }
}


//implementare quicksort de la profa:
/*void QuickSort(agenda agende[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
    int pivot = (stanga + dreapta)/2;
	//alegere pivot
	swap(agende, prim, pivot);
	//mutare pivot pe prima pozitie
	while (stanga <= dreapta) //partitionare
	{
		while (strcmp(agende[stanga].nume, agende[pivot].nume) < 0)
		{
            stanga++;
        }
		while (strcmp(agende[dreapta].nume, agende[pivot].nume) > 0)
		{
            dreapta--;
        }
		if (stanga < dreapta)
		{
            swap(agende, stanga++ ,dreapta--);
        }
		else
		{
            stanga++;
        }
	}
	//mutare pivot la locul sau final
	swap(agende, dreapta, prim);
	//apelurile recursive
	if (prim < dreapta - 1)
    {	
        QuickSort(agende, prim, dreapta - 1);
    }
	if (dreapta + 1 < ultim)
	{
        QuickSort(agende, dreapta + 1, ultim);
    }
}*/

// Functie pentru mutarea pe ultimele pozitii din vector a primelor doua persoane cu un venit mai mic de 1000
void moveLowIncomeToEnd(agenda agende[], int N)
{
    int lowIncomeCount = 0;

    for (int i = 0; i < N && lowIncomeCount < 2; i++)
    {
        if (agende[i].venit < 1000)
        {
            swap(agende, i, N - lowIncomeCount - 1);
            lowIncomeCount++;
        }
    }
}

int main(void)
{
	agenda agende[] = { {"Vera", "73547002", 35, 2200},
						{"Sandra", "73007798", 37, 100},
		                {"Ana", "79652820", 30, 400} };
	int N, i;
	N = sizeof(agende) / sizeof(agende[0]);

    // Afisam tabloul initial
    printf("Tabloul initial:\n");
    for (i = 0; i < N; i++) 
	{
        printf("%s\t%d\t%d\n", agende[i].nume, agende[i].an, agende[i].venit);
    }

    // Mutam pe ultimele pozitii din vector primele doua persoane cu un venit mai mic de 1000
    moveLowIncomeToEnd(agende, N);

	// Afisam tabloul dupa mutarea persoanelor cu venit mic
    printf("\nTabloul dupa mutarea persoanelor cu venit mai mic de 1000:\n");
    for (i = 0; i < N; i++) 
	{
        printf("%s\t%d\t%d\n", agende[i].nume, agende[i].an, agende[i].venit);
    }

    // Sortam eficient in ordine alfabetica persoanele cu varsta intre 30 si 40 de ani
	QuickSort(agende, 0, N - 1);

	// Afisam tabloul dupa sortarea persoanelor cu varsta intre 30 si 40 de ani
    printf("\nTabloul dupa sortarea persoanelor cu varsta intre 30 si 40 de ani:\n");
    for (i = 0; i < N; i++) 
	{
        printf("%s\t%d\t%d\n", agende[i].nume, agende[i].an, agende[i].venit);
    }

	return 0;
}
