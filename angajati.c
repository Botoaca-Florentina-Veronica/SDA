/*﻿

   Fie un tablou de structuri de forma struct angajat(char nume[35]; int salar, int bonus). (Câmpul bonus este setat pe 1 dacă angajatul a primit un bonus, respectiv pe 0 daca nu).
Stiind ca tabloul are dimensiunea N, sa se implementeze cate o funcţie pentru:
a. Mutarea, intr-un mod cat mai eficient, pe primele poziții din vector a angajatilor care au primit bonus,
b. Sortarea in ordine inversa dupa salar, a angajatilor care NU au primit bonus (doar acesti angajati vor fi sortati).
Sa se considere un exemplu de tablou cu minim 5 astfel de angajati si sa se exemplifice cum va arata tabloul dupa apelul fiecareia din functiile de mai sus.
Nota:
Algoritmul poate fi scris in pseudocod (C like).
Este obligatorie comentarea algoritmului si specificarea complexitatii acestuia in termeni de O(f(n)), comentarea structurilor de date alese, precum si justificarea alegerii acestora.
Este obligatorie exemplificarea efectului apelului functiilor implementate pe un exemplu ales.
*/

//acum ca algoritm de sortare voi folosi heap sort
//presupun ca imi aranjez angajatii alfabetic dupa nume aici
//muta alfabetic doar angajatii care au salariu intre 3000 si 6000 de lei
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct angajat
{
	char nume[35];
	int salariu;
	int bonus;
}angajat;

void swap(angajat angajati[], int low, int high)
{
	angajat temp;
	temp = angajati[low];
	angajati[low] = angajati[high];
	angajati[high] = temp;
}


/*
void deplasare(angajat angajati[], int stanga, int dreapta)
{
	int fiu = 2 * stanga + 1;
	while (fiu <= dreapta)
	{
		if (fiu < dreapta && strcmp(angajati[fiu].nume, angajati[fiu + 1].nume) < 0)
			//daca al doilea fiu are cheia cea mai mare
		{
			fiu++;								//retinem al doilea fiu
		}
		if (strcmp(angajati[stanga].nume, angajati[fiu].nume) < 0)  //daca este necesar 
		{										 //schimba parinte cu fiu
			swap(angajati, stanga, fiu);			 //si deplaseaza in jos
			stanga = fiu;
			fiu = 2 * stanga + 1;
		}
		else
		{
			fiu = dreapta + 1;
		}
	}
}

void heapsort(angajat angajati[], int n)
{
	int i;
	//algoritmul lui Floyd 
	for (i = n / 2 - 1; i >= 0; i--) //se creaza ansamblul
		deplasare(angajati, i, n - 1);
	//extragerea maximului si refacerea ansamblului
	for (i = n - 1; i >= 1; i--)
	{
		swap(angajati, 0, i);			//mutare element maxim pe pozitia a[i]
		deplasare(angajati, 0, i - 1);		//se reface proprietatea de ansamblu
	}
}

void insertion_sort(angajat angajati[], int n)
{
	int i, j;
	angajat tmp;
	for (i = 1; i < n; i++)
	{
		tmp = angajati[i];
		for (j = i; (j > 0) && (strcmp(tmp.nume, angajati[j - 1].nume) < 0); j--)
		{
			angajati[j] = angajati[j - 1];
		}
		angajati[j] = tmp;
	}
}
*/


void quicksort(angajat angajati[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	int pivot = prim;
	while (stanga <= dreapta) //partitionare
	{
		while (stanga <= ultim && strcmp(angajati[stanga].nume, angajati[pivot].nume) < 0)
		{
			stanga++;
		}
		while (dreapta > prim && strcmp(angajati[dreapta].nume, angajati[pivot].nume) > 0)
		{
			dreapta--;
		}
		if (stanga < dreapta)
		{
			swap(angajati, stanga++, dreapta--);
		}
		else
		{
			stanga++;
		}
	}
	//mutare pivot la locul sau final
	swap(angajati, dreapta, prim);
	//apelurile recursive
	if (prim < dreapta - 1)
	{
		quicksort(angajati, prim, dreapta - 1);
	}
	if (dreapta + 1 < ultim)
	{
		quicksort(angajati, dreapta + 1, ultim);
	}
}


void afiseazaAngazati(angajat angajati[], int N)
{
	int i;
	for (i = 0; i < N; i++)
	{
		printf("Nume: %s, salariu: %d, bonus: %d\n", angajati[i].nume, angajati[i].salariu,
			angajati[i].bonus);
	}
	printf("\n");
}

void mutareAngajati(angajat angajati[], int N)
{
	int pozPrim, pozUltim;
	pozPrim = 0;
	pozUltim = N - 1;

	while (pozPrim <= pozUltim)
	{
		while (pozPrim <= N-1 && angajati[pozPrim].bonus == 1)
		{
			pozPrim++;
		}
		while (pozUltim >= 0 && angajati[pozUltim].bonus == 0)
		{
			pozUltim--;
		}
		if (pozPrim < pozUltim)
		{
			swap(angajati, pozPrim++, pozUltim--);
		}
	}
}


void sortareAlfabeticaSalariu(angajat angajati[], int N)
{
	int pozPrim = 0, pozUltim = N - 1;
	while (pozPrim <= pozUltim)
	{
		while (pozPrim < N && (angajati[pozPrim].salariu > 3000 || angajati[pozPrim].salariu < 6000))
		{
			pozPrim++;
		}
		while (pozUltim >= 0 && (angajati[pozUltim].salariu < 3000 || angajati[pozUltim].salariu > 6000))
		{
			pozUltim--;
		}
		if (pozPrim < pozUltim)
		{
			swap(angajati, pozPrim++, pozUltim--);
		}
		else
		{
			pozPrim++;
		}
	}

	if (pozUltim >= 0)
	{  // Verificare pentru a evita accesarea în afara limitelor
		quicksort(angajati, 0, pozUltim);   // Sortează doar segmentul cu vârsta între 3000 și 6000
	}

	//insertion_sort(angajati, pozUltim + 1);
	//heapsort(angajati, pozUltim + 1);
	printf("\n");
}



int main(void)
{
	angajat angajati[] = { {"Vera", 3500, 1}, {"Ana", 3100, 1}, {"Oana", 9900, 1}, {"Robert", 3700, 0}, {"Andreea", 5000, 0} };
	int N;
	N = sizeof(angajati) / sizeof(angajati[0]);
	printf("Lista de angajati initiali:\n");
	afiseazaAngazati(angajati, N);

	printf("Angajati sortati alfabetic dupa nume si salariu intre (3000, 6000):\n");
	sortareAlfabeticaSalariu(angajati, N);
	afiseazaAngazati(angajati, N);

	printf("Angajati ordonati prioritar dupa bonus:\n");
	mutareAngajati(angajati, N);
	afiseazaAngazati(angajati, N);
	return 0;
}
