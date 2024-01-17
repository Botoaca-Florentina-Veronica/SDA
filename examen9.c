/*
Fie un tablou de structuri de forma struct film{char nume[35]; int an; int premii). (Câmpul premii este setat pe 1 dacă filmul a fost premiat, respectiv pe 0 daca nu).
Ştiind ca tabloul are dimensiunea N, sa se implementeze cate o funcție pentru:
a. Mutarea, intr-un mod cat mai eficient, pe primele poziții din vector a filmelor care au primit premii, iar pe ultimele cele fara premii.
b. Sortarea in ordine invers alfabetica dupa nume, a filmelor premiate (doar filmele premiate vor fi sortate).
Sa se considere un exemplu de tablou cu minim 5 astfel de filme si sa se exemplifice cum va arata tabloul dupa apelul fiecareia din functiile de mai sus.
Nota:
Algoritmul poate fi scris in pseudocod (C like).
Este obligatorie comentarea algoritmului si specificarea complexitatii acestuia in termeni de O(f(n)), comentarea structurilor de date alese, precum si justificarea alegerii acestora.
Este obligatorie exemplificarea efectului apelului functiilor implementate pe un exemplu ales.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct film
{
	char nume[35];
	int an;
	int premii;  //setat pe 1(cu premii) sau 0(fara premii)
}film;


void swap(film filme[], int low, int high)
{
	film temp;
	temp = filme[low];
	filme[low] = filme[high];
	filme[high] = temp;
}


void quicksort(film filme[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	int pivot = prim;
	while (stanga <= dreapta) //partitionare
	{
		while (stanga <= ultim && strcmp(filme[stanga].nume, filme[pivot].nume) > 0)
		{
			stanga++;
		}
		while (dreapta > 0 && strcmp(filme[dreapta].nume, filme[pivot].nume) < 0)
		{
			dreapta--;
		}
		if (stanga < dreapta)
		{
			swap(filme, stanga++, dreapta--);
		}
		else
		{
			stanga++;
		}
	}
	//mutare pivot la locul sau final
	swap(filme, dreapta, prim);
	//apelurile recursive
	if (prim < dreapta - 1)
	{
		quicksort(filme, prim, dreapta - 1);
	}
	if (dreapta + 1 < ultim)
	{
		quicksort(filme, dreapta + 1, ultim);
	}
}

void afisareFilme(film filme[], int N)
{
	int i;
	for (i = 0; i < N; i++)
	{
		printf("Nume: %s, an: %d, premii: %d\n", filme[i].nume, filme[i].an, filme[i].premii);
	}
	printf("\n");
}


void mutareFilmePremiate(film filme[], int N)
{
	int pozPrim, pozUltim;
	pozPrim = 0;
	pozUltim = N - 1;
	while (pozPrim <= pozUltim)
	{
		while (pozPrim <= N && filme[pozPrim].premii == 1)
		{
			pozPrim++;
		}
		while (pozUltim >0 && filme[pozUltim].premii == 0)
		{
			pozUltim--;
		}
		if (pozPrim < pozUltim)
		{
			swap(filme, pozPrim++, pozUltim--);
		}
	}
}


int main(void)
{
	film filme[] = { {"The silence of the lambs", 1990, 1},
					 {"Avatar", 2000, 1},
					 {"Titanic", 1994, 0},
					 {"Oppenhimer", 2023, 1},
					 {"Barbie", 2020, 0}};
	int N;
	N = sizeof(filme) / sizeof(filme[0]);
	printf("Lista filme initiale:\n");
	afisareFilme(filme, N);

	printf("Lista filme sortate invers alfabetic:\n");
	quicksort(filme, 0, N - 1);
	afisareFilme(filme, N);

	printf("Lista cu filme premiate pe primele pozitii:\n");
	mutareFilmePremiate(filme, N);
	afisareFilme(filme, N);
	return 0;
}
