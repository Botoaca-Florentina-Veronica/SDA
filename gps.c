/*﻿
   Fie un sistem de gestionare a unor GPS-uri instalate pe camioane in cadrul unor firme de transport.
Firma de transport este caracterizata printr-un nume unic, iar GPS-urile printr-un cod numeric (max 8 cifre).
Sa se scrie si sa se implementeze o structura multilista adecvata pentru gestionarea acestor GPS-uri.
Structura va avea urmatoarea componenta: Fiecare firma de transport reprezinta o intrare separata intr-o lista principala,
si fiecare firma de transport contine o lista secundara ordonata dupa cod a GPS-urilor(corespunzatoare camioanelor fiecarei firme).
Cel putin una din liste va fi implementata dinamic.
Sa se implementeze structurile de date necesare si urmatoarele functionalitati:
  Eliminare GPS - se sterge un GPS indentificat dupa cod din toate firmele.
Sa se aleaga un exemplu de lista care sa cuprinda cel putin 3 firme, fiecare cu cel putin 5 GPS-uri.
Sa se reprezinte grafic structura multilista pentru acest exemplu, inainte si dupa apelul functiei Eliminare GPS.
Nota:
Algoritmul poate fi scris in pseudocod (C like).
Este obligatorie comentarea algoritmului si specificarea complexitatii acestuia in termeni de O(f(n)),
comentarea structurilor de date alese, precum si justificarea alegerii acestora.
Este obligatorie exemplificarea efectului apelului functiilor implementate pe un exemplu ales.
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct GPS
{
	int cod;
	struct GPS* link;
}GPS;

typedef struct firma
{
	char nume[35];
	struct firma* link;
	GPS* gps_uri;
}firma;

void printMultilist(firma* head)
{
	firma* curr;
	curr = head;

	while (curr != NULL)
	{
		printf("Nume firma: %s\n", curr->nume);
		printf("Coduri: \n");
		GPS* gps = curr->gps_uri;
		while (gps != NULL)
		{
			printf(" %d ", gps->cod);
			gps = gps->link;
		}
		printf("\n\n");
		//pentru a parcurge toate firmele ca sa le afisam
		curr = curr->link;
	}
	printf("\n");
}


void adaugaGpsLaFirma(firma* head, int cod)
{
	GPS* gpsNou;
	gpsNou = (GPS*)malloc(sizeof(GPS));
	gpsNou->cod = cod;
	gpsNou->link = NULL;

	if (head->gps_uri == NULL)
	{
		head->gps_uri = gpsNou;
		return;
	}

	GPS* lastNode;
	lastNode = head->gps_uri;
	while (lastNode->link != NULL)
	{
		lastNode = lastNode->link;
	}
	lastNode->link = gpsNou;
}

firma* creeareFirma(const char* nume)
{
	firma* firmaNoua;
	firmaNoua = (firma*)malloc(sizeof(firma));
	strncpy(firmaNoua->nume, nume, 35);
	firmaNoua->link = NULL;
	firmaNoua->gps_uri = NULL;
	return firmaNoua;
}

firma* stergere(firma* head, int cod)
{
    firma* curr = head;
    firma* prevFirma = NULL;

    while (curr != NULL)
    {
        GPS* gps = curr->gps_uri;
        GPS* prevGPS = NULL;
        while (gps != NULL)
        {
            if (gps->cod == cod)
            {
                if (prevGPS == NULL)
                {
                    curr->gps_uri = gps->link;
                    free(gps);
                    gps = curr->gps_uri;
                }
                else
                {
                    prevGPS->link = gps->link;
                    free(gps);
                    gps = prevGPS->link;
                }
            }
            else
            {
                prevGPS = gps;
                gps = gps->link;
            }
        }
        if (curr->gps_uri == NULL)
        {
            if (prevFirma == NULL)
            {
                head = curr->link;
                free(curr);
                curr = head;
            }
            else
            {
                prevFirma->link = curr->link;
                free(curr);
                curr = prevFirma->link;
            }
        }
        else
        {
            prevFirma = curr;
            curr = curr->link;
        }
    }
    return head;
}



int main(void)
{
	firma* f1, * f2, * f3;
	f1 = creeareFirma("Atos");
	f2 = creeareFirma("Hella");
	f3 = creeareFirma("Continental");

	adaugaGpsLaFirma(f1, 34);
	adaugaGpsLaFirma(f1, 30);

	adaugaGpsLaFirma(f2, 54);
	adaugaGpsLaFirma(f2, 55);

	adaugaGpsLaFirma(f3, 60);
	adaugaGpsLaFirma(f3, 65);

	f1->link = f2;
	f2->link = f3;

	printf("Lista initiala:\n");
	printMultilist(f1);

	printf("Lista dupa stergere: \n");
	stergere(f1, 54);
	printMultilist(f1);

	return 0;
}
