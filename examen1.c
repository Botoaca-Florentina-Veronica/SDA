/*
Fie o aplicatie care gestioneaza o retea de profesionisti din intreaga lume, de tip Linkedin.Pentru o persoana se memoreaza un ID(intreg), un nume(max 35 caractere) si 
ocupatie(max. 35 de caractere), precum si o lista de conexiuni profesionale.
Sa se scrie si sa se implementeze o structura bazata pe lista simplu inlantuita(dinamica) articulata cu tablouri(eficienta din punct de vedere al timpului de rulare) pentru a gestiona persoanele.
Structura va avea urmatoarea componenta : Fiecare persoana reprezinta un nod intr - o lista, si fiecare persoana contine un tablou implementat in mod static, cu conexiunile profesionale pe care 
le are(colegi de echipa, persoane de la resurse umane, etc).
Sa se implementeze structurile de date necesare si urmatoarea functionalitate :
• Adaugare conexiune in lista unei persoane(adaugare in lista secundara)
Sa se aleaga un exemplu de lista care sa cuprinda cel putin 3 persoane, fiecare cu cel putin 5 conexiuni.Sa se reprezinte grafic structura multilista pentru acest exemplu, inainte si dupa apelul functiei adaugareConexiune.
Nota :
	Algoritmul poate fi scris in pseudocod(C like).
	Este obligatorie comentarea algoritmului si specificarea, complexitatii acestuia in termeni de O(f(n)), comentarea structurilor de date alese, precum si justificarea alegerii acestora.
	Este obligatorie exemplificarea efectului apelului functiilor implementate pe un exemplu ales.
	Maximum file size : 5MB, maximum number of files : 3
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct conexiune
{
	int IDconexiune;
	struct conexiune* link;
}conexiune;

typedef struct persoana
{
	int ID;
	char nume[35];
	char ocupatie[35];
	struct persoana* link;
	conexiune *conexiuni;
}persoana;

void printMultilist(persoana* head)
{
	persoana* curr;
	curr = head;
	while (curr != NULL)
	{
		printf("ID: %d, nume: %s, ocupatie: %s\n", curr->ID, curr->nume, curr->ocupatie);
		printf("Conexiuni: \n");
		conexiune* conex = curr->conexiuni;
		while (conex != NULL)
		{
			printf("%d ", conex->IDconexiune);
			conex = conex->link;
		}
		printf("\n\n");
		//verificam fiecare persoana pentru a o afisa
		curr = curr->link;
	}
	printf("\n");
}

void adaugareConexiuneLaPersoana(persoana* head, int IDconexiune)
{
	conexiune* conexiuneNoua;
	conexiuneNoua = (conexiune*)malloc(sizeof(conexiune));
	conexiuneNoua->IDconexiune = IDconexiune;
	conexiuneNoua->link = NULL;

	if (head->conexiuni == NULL)
	{
		head->conexiuni = conexiuneNoua;
		return;
	}

	conexiune* lastNode;
	lastNode = head->conexiuni;
	while (lastNode->link != NULL)
	{
		lastNode = lastNode->link;
	}
	lastNode->link = conexiuneNoua;
}

persoana *creearePersoana(int ID, const char* nume, const char* ocupatie) 
{
    persoana* persoanaNoua = (persoana*)malloc(sizeof(persoana));
    persoanaNoua->ID = ID;
    strncpy(persoanaNoua->nume, nume, 35);
    strncpy(persoanaNoua->ocupatie, ocupatie, 35);
    persoanaNoua->link = NULL;
    persoanaNoua->conexiuni = NULL;

    return persoanaNoua;
}

int main(void)
{
	persoana* p1, * p2, * p3;
	p1 = p2 = p3 = NULL;

	p1 = creearePersoana(1, "Vera", "inginera");
	p2 = creearePersoana(2, "Sandra", "profesoara");
	p3 = creearePersoana(3, "Maria", "doctor");

	adaugareConexiuneLaPersoana(p1, 2);
	adaugareConexiuneLaPersoana(p1, 3);

	adaugareConexiuneLaPersoana(p2, 1);
	adaugareConexiuneLaPersoana(p2, 3);

	adaugareConexiuneLaPersoana(p3, 1);
	adaugareConexiuneLaPersoana(p3, 2);

	p1->link = p2;
	p2->link = p3;

	printf("Lista initiala: \n");
	printMultilist(p1);

	return 0;
}
