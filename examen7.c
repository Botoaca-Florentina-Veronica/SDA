/*
Fie un tablou de structuri de forma struct echipa{char nume[25]; int puncte; int buget, char oras[25]}. Ştiind ca tabloul are dimensiunea N, sa se implementeze cate o funcție pentru:
a. Mutarea pe primele pozitii din vector a echipelor cu punctaj mai mare decat 45, iar pe ultimele pozitii a celor cu punctaj mai mic decat 20. Algoritmul va avea o complexitate de O(n), si nu va folosi un alt tablou auxiliar;
b. Sortarea cat mai eficienta a echipelor cu un buget mai mare decat 100 000 (celalalte echipe nu vor fi sortate pastrandu-si aceleasi pozitii in tablou) alfabetica in functie de nume.
Sa se considere un exemplu de tablou cu minim 5 astfel de echipe și sa se exemplifice cum va arata tabloul dupa apelul fiecareia din functiile de mai sus.
Nota:
Algoritmul poate fi scris in pseudocod (C like).
Este obligatorie comentarea algoritmului si specificarea complexitatii acestuia in termeni de O(f(n)), comentarea structurilor de date alese, precum si justificarea alegerii acestora.
Este obligatorie exemplificarea efectului apelului functiilor implementate pe un exemplu ales.
*/


//codul asta imi sorteaza alfabetic echipele cu bugete > 100 000, dar pe celelalte le afiseaza primele, tot alfabetic
//deci nu respecta 100% cerinta!!!
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct echipa
{
	char nume[25];
	int puncte;
	int buget;
	char oras[25];
}echipa;


//functie speciala pentru quicksort:
void swap(echipa echipe[], int stanga, int dreapta)
{
	echipa temp;
	temp = echipe[stanga];
	echipe[stanga] = echipe[dreapta];
	echipe[dreapta] = temp;
}

void QuickSort(echipa echipe[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	int pivot = prim;
	while (stanga <= dreapta) //partitionare
	{
		while (stanga <= ultim && strcmp(echipe[stanga].nume, echipe[pivot].nume) < 0)
		{
			stanga++;
		}
		while (dreapta > prim && strcmp(echipe[dreapta].nume, echipe[pivot].nume) > 0)
		{
			dreapta--;
		}
		if (stanga < dreapta)
		{
			swap(echipe, stanga++, dreapta--);
		}
		else
		{
			stanga++;
		}
	}
	//mutare pivot la locul sau final
	swap(echipe, dreapta, prim);
	//apelurile recursive
	if (prim < dreapta - 1)
	{
		QuickSort(echipe, prim, dreapta - 1);
	}
	if (dreapta + 1 < ultim)
	{
		QuickSort(echipe, dreapta + 1, ultim);
	}
}

// Functie pentru mutarea echipelor
void mutaEchipe(echipa echipe[], int N) 
{
	int pozPrim = 0, pozUltim = N - 1;

	while (pozPrim <= pozUltim) 
	{
		while (pozPrim < N && echipe[pozPrim].puncte > 45) 
		{
			pozPrim++;
		}

		while (pozUltim >= 0 && echipe[pozUltim].puncte < 20) 
		{
			pozUltim--;
		}
		if (pozPrim < pozUltim) 
		{
			swap(echipe, pozPrim++, pozUltim--);
		}
	}
}

// Functie pentru afisarea echipei
void afiseazaEchipe(echipa echipe[], int N) 
{
	int i;
	for (i = 0; i < N; i++) 
	{
		printf("Nume: %s, puncte: %d, buget: %d, oras: %s\n",
			echipe[i].nume, echipe[i].puncte, echipe[i].buget, echipe[i].oras);
	}
	printf("\n\n");
}


int main(void)
{
	echipa echipe[] = { {"fcsb", 35, 150000, "Bucuresti"},
					   {"upt", 66, 2000, "Timisoara"},
					   {"cluj", 112, 4000, "Cluj-Napoca"},
					   {"dinamo", 3, 300000, "Ilfov"},
					   {"real madrid", 8, 1000000, "Severin"} };
	int N, i;
	N = sizeof(echipe) / sizeof(echipe[0]);
	printf("Lista initiala cu echipe:\n");
	afiseazaEchipe(echipe, N);

	printf("Pe primele pozitii, echipe cu punctaj mai mare decat 45, iar pe ultimele pozitii a celor cu punctaj mai mic decat 20: \n");
	mutaEchipe(echipe, N);
	afiseazaEchipe(echipe, N);

	// Sortarea echipelor cu buget mai mare decat 100000
	int pozPrimaEchipa = -1;
	for (i = 0; i < N; i++)
	{
		if (echipe[i].buget > 100000)
		{
			pozPrimaEchipa = i;
			break;
		}
	}
	if (pozPrimaEchipa != -1)
	{
		QuickSort(echipe, pozPrimaEchipa, N - 1);
	}
	printf("Lista cu echipe dupa aranjarea acestora alfabetic, pentru cei cu un buget > 100 000:\n");
	afiseazaEchipe(echipe, N);
	return 0;
}
