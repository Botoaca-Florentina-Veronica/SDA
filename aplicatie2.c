/*
I. Să se implementeze un program care implementează un sistem de rezervare a unor bilete de avion. 
Programul ar trebui sa implementeze următoarele funcționalități:

S1. Să se afișeze un meniu text pentru următoarele operații de bază:
a. Rezervarea unui bilet
b. Anularea unei rezervări
c. Verificarea datelor unei rezervări pe baza unui ID unic al rezervării (să se afișeze numele pasagerului).

S1'. Să se implementeze operațiile următoare, considerând că rezervările se pot face doar pentru un singur zbor, 
menținând informațiile despre rezervări într-o listă simplu înlănțuită, ordonată după numele pasagerilor.
S2. Să se extindă programul precedent, considerînd că pot exista oricâte zboruri, extinzând lista anterioară la o structură multilistă*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pasager 
{
    char nume[50];
    int rezervare_id;
    struct Pasager *link;
} Pasager;

typedef struct Zbor 
{
    char nume_zbor[50];
    Pasager *rezervari;
    struct Zbor *link;
} Zbor_t;


void rezervare_bilet(Zbor_t *zbor, const char *nume_pasager) 
{
    Pasager *pasager_nou;
    pasager_nou = (Pasager *)malloc(sizeof(Pasager));
    strcpy(pasager_nou->nume, nume_pasager);
    if (zbor->rezervari == NULL) 
    {
        pasager_nou->rezervare_id = 1;
        pasager_nou->link = NULL;
    } 
    else 
    {
        pasager_nou->rezervare_id = zbor->rezervari->rezervare_id + 1;
        pasager_nou->link = zbor->rezervari;
    }
    zbor->rezervari = pasager_nou;
    printf("Bilet rezervat cu succes pentru %s la zborul %s!\n", nume_pasager, zbor->nume_zbor);
}

// Functie pentru anularea unei rezervari
void anulare_rezervare(Zbor_t *zbor, int rezervare_id) 
{
    Pasager *curr, *prev; 
	curr = zbor->rezervari;
	prev = NULL;

    //abordam cazul in care chiar capul listei este null:
	if (curr == NULL) 
	{
        printf("Rezervarea cu ID-ul %d nu a fost gasita.\n", rezervare_id);
        return;
    }

    //cat timp nu ajugem la finalul listei, iar nodul nostru contine id-ul diferit de cel cautat, parcurgem lista:
    while (curr != NULL) 
	{
        if(curr->rezervare_id != rezervare_id)
        {
            if (prev == NULL) 
            {
                curr = curr->link;
                free(curr);
                //daca chiar capul listei este chiar nodul cautat atunci il vom sterge
                //intai vom schimba adresa la care pointer ul head  "pointeaza" pentru ca daca o facem inainte
                //riscam sa pierdem informatia pe care acesta o contine
                //si astfel sa pierdem legaturile cu celelalte elemente ale listei
            }
            else 
            {
                //daca ajungem aici inseamna ca id-ul cautat nu se afla in capul listei, deci vom parcurge restul de elemente
                prev->link = curr->link;
                free(curr);
                curr = prev->link;
            }
        }
        else
        //daca ajungem aici inseamna ca am trecut cu bine de posibilitatea de a avea id-ul cautat in lista
        //deci nu ne mai ramane decat sa o parcurgem mai departe
        {
            //nu vrem sa lasam pointerul anterior sa fie egal cu null, trebuie updatat, la fel si curr dupa cum urmeaza:
            prev = curr; 
            curr = curr->link;
        }
    } 
    printf("Rezervarea cu ID-ul %d a fost anulata.\n", rezervare_id);
}

// Functie pentru verificarea datelor unei rezervari
void verificare(Zbor_t *zbor, int rezervare_id) 
{
    Pasager *curr = zbor->rezervari;
    if (curr == NULL) 
	{
        printf("Rezervarea cu ID-ul %d nu a fost gasita.\n", rezervare_id);
        return;
    }
    while (curr != NULL && curr->rezervare_id != rezervare_id) 
	{
        curr = curr->link;
    }
    //daca ies din bucla while, inseamna ca am gasit id-ul pasagerului cautat, deci mai departe le voi afisa:
    printf("Detalii rezervare pentru ID-ul %d:\n", rezervare_id);
    printf("Nume pasager: %s\n", curr->nume);
}

void adaugaZbor(Zbor_t **zbor, const char nume_zbor[50]) 
{
    Zbor_t *newnode = (Zbor_t *)malloc(sizeof(Zbor_t));
    if (newnode == NULL) 
    {
        printf("Eroare la alocarea dinamica a memoriei pentru zbor!\n");
        exit(1);
    }

    strcpy(newnode->nume_zbor, nume_zbor);
    newnode->rezervari = NULL;
    newnode->link = *zbor;

    *zbor = newnode;
}

int main(void) 
{
    Zbor_t *zbor = NULL;
    adaugaZbor(&zbor, "Zbor 1");
    adaugaZbor(&zbor, "Zbor 2");

    rezervare_bilet(zbor, "Vera Botoaca");
    rezervare_bilet(zbor, "Ana Bojan");
    anulare_rezervare(zbor, 1);
    verificare(zbor, 2);

    /*
    // Eliberam memoria
    while (zbor != NULL)
     {
        Zbor_t *temp = zbor;
        zbor = zbor->link;
        
        Pasager *pasager = temp->rezervari;
        while (pasager != NULL) 
        {
            Pasager *pasager_temp = pasager;
            pasager = pasager->link;
            free(pasager_temp);
        }

        free(temp);
    }
    */
   
    return 0;
}
