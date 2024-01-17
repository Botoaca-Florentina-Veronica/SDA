/*﻿

   Fie un tablou de structuri de forma struct angajat(char nume[35]; int salar, int bonus). (Câmpul bonus este setat pe 1 dacă angajatul a primit un bonus, respectiv pe 0 daca nu).
Stiind ca tabloul are dimensiunea N, sa se implementeze cate o funcţie pentru:
a. Mutarea, intr-un mod cat mai eficient, pe primele poziții din vector a angajatilor care au primit bonus,
b. Sortarea in ordine inversa dupa salar, a angajatilor care NU au primit bonus (doar acesti angajati vor fi sortati).
Sa se considere un exemplu de tablou cu minim 5 astfel de angajati si sa se exemplifice cum va arata tabloul dupa apelul fiecareia din functiile de mai sus.
Nota:
Algoritmul poate fi scris in pseudocod (C like).
Este obligatorie comentarea algoritmului si specificarea complexitatii acestuia in termeni de O(f(n)), comentarea structurilor de date alese, precum si justificarea alegerii acestora.
Este obligatorie exemplificarea efectului apelului functiilor implementate pe un exemplu ales.*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct angajat
{
	char nume[35];
	int salariu;
	int bonus;
}angajat;

void swap(angajat* a, angajat* b)
{
	angajat temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void bubbleSort(angajat arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - 1 - i; j++)
		{
			if (arr[j].bonus < arr[j + 1].bonus || (arr[j].bonus == arr[j + 1].bonus && (strcmp (arr[j].nume, arr[j + 1].nume) > 0)))
			{
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

int main(void)
{
	angajat angajati[] = { {"Vera", 2500, 1}, {"Ana", 2100, 1}, {"Oana", 1900, 1}, {"Robert", 1700, 0}, {"Andreea", 2000, 0} };
	int nrAngajati, i;
	nrAngajati = sizeof(angajati) / sizeof(angajati[0]);
	printf("Lista initiala de angajati:\n");
	for (i = 0; i < nrAngajati; i++)
	{
		printf("Nume: %s, Salariu: %d, Bonus: %d\n", angajati[i].nume, angajati[i].salariu, angajati[i].bonus);
	}
	printf("\n\n");
	bubbleSort(angajati, nrAngajati);

	printf("Dupa mutarea angajatilor cu bonus inaintea celor fara bonus: \n");
	for (i = 0; i < nrAngajati; i++)
	{
		printf("Nume: %s, Salariu: %d, Bonus: %d\n", angajati[i].nume, angajati[i].salariu, angajati[i].bonus);
	}
	return 0;
}
