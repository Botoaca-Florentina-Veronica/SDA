/*
   Fie un sistem de gestionare a unor paleti din cadrul unor depozite.
   Depozitul este caracterizat printr-un nume unic, iar paletii printr-un cod numeric (max 8 cifre).
   Sa se scrie si sa se implementeze o structura multilista adecvata pentru gestionarea acestor depozite.
   Structura va avea urmatoarea componenta: Fiecare depozit reprezinta o intrare separata intr-o lista principala,
   si fiecare depozit contine o lista secundara ordonata dupa cod a paletilor din acel zbor (cel putin una din liste va
   fi implementata dinamic).
Sa se implementeze structurile de date necesare si urmatoarele functionalitati: Eliminare palet- se sterge un palet
identificat dupa cod din toate depozitele.
Sa se aleaga un exemplu de lista care sa cuprinda cel putin 3 depozite, fiecare cu cel putin 5 paleti.
Sa se reprezinte grafic structura multilista pentru acest exemplu, inainte si dupa apelul functiei Eliminare palet.
Nota:
Algoritmul poate fi scris in pseudocod (C like).
Este obligatorie comentarea algoritmului si specificarea complexitatii acestuia in termeni de O(f(n)), comentarea structurilor de date alese, precum si justificarea alegerii acestora.
Este obligatorie exemplificarea efectului apelului functiilor implementate pe un exemplu ales.
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct palet
{
	int cod;
	struct palet* link;
}palet;


typedef struct depozit
{
	char nume[35];
	struct depozit* link;
	palet* paleti;  //implementare dinamica a listei de paleti
}depozit;


void printMultilist(depozit* head)
{
	depozit* curr;
	curr = head;
	while (curr != NULL)
	{
		palet* palet = curr->paleti;
		printf("Nume depozit: %s\n", curr->nume);
		printf("ID palet: ");
		while (palet != NULL)
		{
			printf("%d ", palet->cod);
			palet = palet->link;
		}
		printf("\n");
		curr = curr->link;
	}
	printf("\n");
}

depozit* creeareDepozit(depozit* head, const char* nume)
{
	depozit* depozitNou;
	depozitNou = (depozit*)malloc(sizeof(depozit));
	depozitNou->link = NULL;
	depozitNou->paleti = NULL;
	strncpy(depozitNou->nume, nume, 35);
	return depozitNou;
}


void adaugarePaletLaDepozit(depozit* head, int cod)
{
	palet* paletNou;
	paletNou = (palet*)malloc(sizeof(palet));
	paletNou->cod = cod;
	paletNou->link = NULL;

	if (head->paleti == NULL)
	{
		head->paleti = paletNou;
		return;
	}

	palet* lastNode;
	lastNode = head->paleti;
	while (lastNode->link != NULL)
	{
		lastNode = lastNode->link;
	}
	lastNode->link = paletNou;
}

depozit* stergere(depozit* head, int cod)
{
	depozit* curr = head;
	depozit* prevDepozit = NULL;

	while (curr != NULL)
	{
		palet* prevPalet = NULL;
		palet* palet = curr->paleti;

		while (palet != NULL)
		{
			if (palet->cod == cod)
			{
				if (prevPalet == NULL)
				{
					curr->paleti = palet->link;
					free(palet);
					palet = curr->paleti;
				}
				else
				{
					prevPalet->link = palet->link;
					free(palet);
					palet = prevPalet->link;
				}
			}
			else
			{
				prevPalet = palet;
				palet = palet->link;
			}

		}
		if (curr->paleti == NULL)
		{
			if (prevDepozit == NULL)
			{
				head = curr->link;
				free(curr);
				curr = head;
			}
			else
			{
				prevDepozit->link = curr->link;
				free(curr);
				curr = prevDepozit->link;
			}
		}
		else
		{
			prevDepozit = curr;
			curr = curr->link;
		}
	}
	return head;
}


int main(void)
{
	depozit* d1, * d2, * d3;
	d1 = d2 = d3 = NULL;

	d1 = creeareDepozit(d1, "Depozit_1");
	d2 = creeareDepozit(d2, "Depozit_2");
	d3 = creeareDepozit(d3, "Depozit_3");

	adaugarePaletLaDepozit(d1, 34);
	adaugarePaletLaDepozit(d1, 30);

	adaugarePaletLaDepozit(d2, 54);
	adaugarePaletLaDepozit(d2, 50);

	adaugarePaletLaDepozit(d3, 6);
	adaugarePaletLaDepozit(d3, 60);

	d1->link = d2;
	d2->link = d3;
	printf("Lista initiala de depozite: \n");
	printMultilist(d1);

	printf("Lista de depozite dupa stergere: \n");
	stergere(d1, 50);
	printMultilist(d1);
	return 0;
}

