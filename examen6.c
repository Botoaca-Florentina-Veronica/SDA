/*﻿
   Fie un tablou de structuri de forma struct agenda{char nume[25]; char telefon[10];int an; int venit}.
   Ştiind ca tabloul are dimensiunea N, sa se implementeze cate o funcție pentru:
a. Mutarea pe ultimele poziții din vector a primelor persoane cu un venit mai mic de 1000.
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

void quicksort(agenda agende[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	int pivot = prim;
	while (stanga <= dreapta) //partitionare
	{
		while (stanga <= ultim && strcmp(agende[stanga].nume, agende[pivot].nume) < 0)
		{
			stanga++;
		}
		while (dreapta > prim && strcmp(agende[dreapta].nume, agende[pivot].nume) > 0)
		{
			dreapta--;
		}
		if (stanga < dreapta)
		{
			swap(agende, stanga++, dreapta--);
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
		quicksort(agende, prim, dreapta - 1);
	}
	if (dreapta + 1 < ultim)
	{
		quicksort(agende, dreapta + 1, ultim);
	}
}


void afiseazaAgende(agenda agende[], int N)
{
	int i;
	for (i = 0; i < N; i++)
	{
		printf("Nume: %s, numar de telefon: %s, varsta: %d, venit: %d\n", agende[i].nume, 
			agende[i].telefon, agende[i].an, agende[i].venit);
	}
	printf("\n");
}

void sortareAlfabetica30_40(agenda agende[], int N) 
{
    int pozPrim = 0, pozUltim = N - 1;

    while (pozPrim <= pozUltim) 
    {
        while (pozPrim < N && (agende[pozPrim].an < 30 || agende[pozPrim].an > 40)) 
        {
            pozPrim++;
        }
        while (pozUltim >= 0 && (agende[pozUltim].an < 30 || agende[pozUltim].an > 40)) 
        {
            pozUltim--;
        }
        if (pozPrim < pozUltim) 
        {
            swap(agende, pozPrim++, pozUltim--);
        } 
        else 
        {
            pozPrim++;
        }
    }

    if (pozUltim >= 0) 
    {  // Verificare pentru a evita accesarea în afara limitelor
        quicksort(agende, 0, pozUltim);   // Sortează doar segmentul cu vârsta între 30 și 40
    }
}

void mutareAgende(agenda agende[], int N)
{
	int pozPrim, pozUltim;
	pozPrim = 0;
	pozUltim = N - 1;
	while (pozPrim <= pozUltim)
	{
		while (agende[pozPrim].venit < 1000)  //adica pe primele pozitii vreau sa fie cei cu venituri <1000
		{
			pozPrim++;
		}
		while (agende[pozUltim].venit > 1000)
		{
			pozUltim--;
		}
		if (pozPrim < pozUltim)
		{
			swap(agende, pozPrim++, pozUltim--);
		}
	}
}



int main(void)
{
	agenda agende[] = { {"Vera", "2470252", 32, 200},
						{"Sandra", "2936421", 34, 1500},
						{"Bogdan", "8796856", 35, 300},
						{"Anca", "49623234", 67, 4000},
						{"Andrei", "40283471", 31, 590},
	};
	int N;
	N = sizeof(agende) / sizeof(agende[0]);
	printf("Lista de agende initiala: \n");
	afiseazaAgende(agende, N);

	printf("Lista de agende sortata alfabetic: \n");
	sortareAlfabetica30_40(agende, N);
	afiseazaAgende(agende, N);

    printf("Lista de agende in care veniturile <1000 sunt prioritare: \n");
    mutareAgende(agende, N);
    afiseazaAgende(agende, N);
	return 0;
}
