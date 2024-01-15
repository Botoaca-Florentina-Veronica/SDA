/*
   Fie un tablou de structuri de forma struct student(char nume[35]; int varsta; int premii).
   (Câmpul premii este setat pe 1 dacă studentul a fost premiat, respectiv pe 0 daca nu).
Ştiind ca tabloul are dimensiunea N, sa se implementeze cate o funcție pentru :
a.Mutarea, intr - un mod cat mai eficient, pe primele poziții din vector a studentilor care au primit premii,
b.Sortarea in ordine invers alfabetica dupa nume, a studentilor premiati(doar studentii premiati vor fi sortati).
Sa se considere un exemplu de tablou cu minim 5 astfel de filme si sa se exemplifice cum va arata tabloul dupa apelul 
fiecareia din functiile de mai sus.
Nota :
	Este obligatorie comentarea algoritmului si specificarea complexitatii acestuia in termeni de O(f(n)), 
	comentarea structurilor de date alese, precum si justificarea alegerii acestora.
	Este obligatorie exemplificarea efectului apelului functiilor implementate pe un exemplu ales.scrie codul in C
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student
{
	char nume[35];
	int varsta;
	int premii;
}student;

// Funcție pentru a schimba pozițiile a două structuri student
void swap(student* a, student* b) 
{
	struct student temp = *a;
	*a = *b;
	*b = temp;
}

// Funcție Bubble Sort
void bubbleSort(struct student arr[], int N) 
{
	int i, j;
	for (i=0; i < N - 1; i++) 
	{
		for (j=0; j < N - i - 1; j++) 
		{
			// Comparăm în funcție de premii și nume
			if (arr[j].premii < arr[j + 1].premii || (arr[j].premii == arr[j + 1].premii && strcmp(arr[j].nume, arr[j + 1].nume) < 0)) 
			{
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

// Funcție pentru mutarea eficientă a studenților premiați pe primele poziții
void mutare_premii_primul(struct student arr[], int N) 
{
	// Sortăm vectorul utilizând Bubble Sort
	bubbleSort(arr, N);
}

int main(void)
{
	//exemplu de tablou cu studenti
	student studenti[] = { {"Ana", 20, 1}, {"Vera", 25, 1}, {"Robert", 18, 0},
		{"Claudiu", 30, 0}, {"Oana", 21, 1} };

	int nrStudenti;
	nrStudenti = sizeof(studenti) / sizeof(studenti[0]);
	//sau nrStudenti = 5;

	mutare_premii_primul(studenti, nrStudenti);
	printf("Dupa mutarea studentilor premiati pe primele pozitii:\n");
	int i;
	for (i = 0; i < nrStudenti; i++) 
	{
		printf("Nume: %s, Varsta: %d, Premii: %d\n", studenti[i].nume, studenti[i].varsta, studenti[i].premii);
	}

	return 0;
}
