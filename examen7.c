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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct echipa
{
	char nume[25];
	int puncte;
	int buget;
	char oras[25];
}echipa;


void swap(echipa echipe[], int low, int high)
{
	echipa temp;
	temp = echipe[low];
	echipe[low] = echipe[high];
	echipe[high] = temp;
}

void quicksort(echipa echipe[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	int pivot = prim;
	while (stanga <= dreapta) //partitionare
	{
		while (stanga >= ultim && strcmp(echipe[stanga].nume, echipe[pivot].nume) < 0)
		{
			stanga++;
		}
		while (dreapta < prim && strcmp(echipe[dreapta].nume, echipe[pivot].nume) > 0)
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
		quicksort(echipe, prim, dreapta - 1);
	}
	if (dreapta + 1 < ultim)
	{
		quicksort(echipe, dreapta + 1, ultim);
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

void mutareEchipe(echipa echipe[], int N)
{
	int pozPrim, pozUltim;
	pozPrim = 0;
	pozUltim = N - 1;
	while (pozPrim <= pozUltim)
	{
		while (pozPrim < N && echipe[pozPrim].puncte > 45)
		{
			pozPrim++;
		}
		while (pozUltim >= 0 &&echipe[pozUltim].puncte < 20)
		{
			pozUltim--;
		}
		if (pozPrim < pozUltim)
		{
			swap(echipe, pozPrim++, pozUltim--);
		}
	}
}

// Functie pentru sortarea echipelor cu buget mai mare decat 100,000 alfabetic dupa nume
void sortareAlfabetica(echipa echipe[], int N)
{
	int  pozPrim, pozUltim;
	pozPrim = 0;
	pozUltim = N - 1;

	while (pozPrim <= pozUltim)
	{
		while (pozPrim <N && echipe[pozPrim].buget > 100000)
		{
			pozPrim++;
		}
		while (pozUltim >= 0 && echipe[pozUltim].buget <= 100000)
		{
			pozUltim--;
		}
		if (pozPrim < pozUltim)
		{
			swap(echipe, pozPrim++, pozUltim--);
		}
	}

	if (pozUltim >= 0)
	{  // Verificare pentru a evita accesarea în afara limitelor
		quicksort(echipe, 0, pozUltim);   // Sortează doar echipele cu buget >100000
	}
}

int main(void)
{
	echipa echipe[] = { {"fcsb", 35, 150000, "Bucuresti"},
					   {"upt", 66, 200, "Timisoara"},
					   {"cluj", 112, 4000, "Cluj-Napoca"},
					   {"dinamo", 3, 3000, "Ilfov"},
					   {"real madrid", 8, 300000, "Severin"} };
	int N;
	N = sizeof(echipe) / sizeof(echipe[0]);
	printf("Lista initiala cu echipe:\n");
	afiseazaEchipe(echipe, N);

	printf("Afisarea echipelor care au peste 45 de puncte pe primele pozitii, iar sub 20 pe ultimele pozitii:\n");
	mutareEchipe(echipe, N);
	afiseazaEchipe(echipe, N);

	printf("Afisarea echipelor alfabetic: \n");
	sortareAlfabetica(echipe, N);
	afiseazaEchipe(echipe, N);
	return 0;
}
